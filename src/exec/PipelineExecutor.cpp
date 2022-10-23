#include "exec/PipelineExecutor.h"
#include "algebra/suboperators/sources/FuseChunkSource.h"
#include "algebra/suboperators/sinks/FuseChunkSink.h"
#include "exec/InterruptableJob.h"
#include "exec/runners/CompiledRunner.h"
#include "exec/runners/InterpretedRunner.h"
#include "runtime/MemoryRuntime.h"

namespace inkfuse {

PipelineExecutor::PipelineExecutor(Pipeline& pipe_, ExecutionMode mode, std::string full_name_)
   : pipe(pipe_), context(pipe), mode(mode), full_name(std::move(full_name_)) {
   assert(pipe.getSubops()[0]->isSource());
   assert(pipe.getSubops().back()->isSink());
   for (const auto& op: pipe.getSubops()) {
      op->setUpState(context);
   }
}

PipelineExecutor::~PipelineExecutor() {
   for (auto& op : pipe.getSubops()) {
      op->tearDownState();
   }
}

const ExecutionContext& PipelineExecutor::getExecutionContext() const {
   return context;
}

void PipelineExecutor::runPipeline() {
   // Scope guard for memory context and flags.
   ExecutionContext::RuntimeGuard guard{context};
   if (mode == ExecutionMode::Fused) {
      while (runFusedMorsel()) {}
   } else if (mode == ExecutionMode::Interpreted) {
      while (runInterpretedMorsel()) {}
   } else {
      // Set up interpreted first to avoid races in parallel setup.
      setUpInterpreted();
      // Now we can happily compile in the background. Note that we need to cancel compilation if
      // interpretation finishes before compilation is done.
      InterruptableJob compilation_interrupt;
      auto compiled_job = setUpFusedAsync(compilation_interrupt);
      bool fused_ready = false;
      bool terminate = false;
      while (!fused_ready && !terminate) {
         terminate = !runInterpretedMorsel();
         fused_ready = fused_set_up.load();
      }
      // Code is ready - switch over.
      while (!terminate) {
         terminate = !runFusedMorsel();
      }
      // Stop the backing compilation job (if not finished) and clean up.
      compilation_interrupt.interrupt();
      compiled_job.join();
   }
}

bool PipelineExecutor::runMorsel() {
   // Scope guard for memory context and flags.
   ExecutionContext::RuntimeGuard guard{context};
   if (mode == ExecutionMode::Fused || (mode == ExecutionMode::Hybrid)) {
      return runFusedMorsel();
   } else {
      return runInterpretedMorsel();
   }
}

void PipelineExecutor::setUpInterpreted() {
   auto count = pipe.getSubops().size();
   interpreters.reserve(count);

   auto isFuseChunkOp = [](const Suboperator* op) {
     if (dynamic_cast<const FuseChunkSink*>(op)) {
        return true;
     }
     if (dynamic_cast<const FuseChunkSourceIUProvider*>(op)) {
        return true;
     }
     return false;
   };

   for (size_t k = 0; k < count; ++k) {
      const auto& op = *pipe.getSubops()[k];
      if (!op.outgoingStrongLinks() && !isFuseChunkOp(&op)) {
         // Only operators without outgoing strong links have to be interpreted.
         interpreters.push_back(std::make_unique<InterpretedRunner>(pipe, k, context));
         interpreters.back()->prepare();
      }
   }
   interpreted_set_up = true;
}

std::thread PipelineExecutor::setUpFusedAsync(InterruptableJob& interrupt)
{
   return std::thread([&]() {
     // Set up runner.
     auto repiped = pipe.repipeRequired(0, pipe.getSubops().size());
     auto runner = std::make_unique<CompiledRunner>(std::move(repiped), context, std::move(full_name));
     // And Compile.
     bool done = runner->prepare(interrupt);
     if (done) {
        compiled[{0, pipe.getSubops().size()}] = std::move(runner);
        fused_set_up.store(true);
     }
   });
}

void PipelineExecutor::setUpFused() {
   // We go through the asynchronous interface but never cancel.
   InterruptableJob compilation_interrupt;
   auto thread = setUpFusedAsync(compilation_interrupt);
   thread.join();
}

void PipelineExecutor::cleanUp() {
   context.clear();
   // Reset the restart flag to have a clean slate for the next morsel.
   ExecutionContext::getInstalledRestartFlag() = false;
}

bool PipelineExecutor::runFusedMorsel() {
   if (!fused_set_up) {
      setUpFused();
      while(!fused_set_up.load()) {}
   }
   // Run the whole compiled executor.
   if (compiled.at({0, pipe.getSubops().size()})->runMorsel(true)) {
      cleanUp();
      return true;
   }
   return false;
}

bool PipelineExecutor::runInterpretedMorsel() {
   if (!interpreted_set_up) {
      setUpInterpreted();
   }

   // Run a morsel and retry it if the `restart_flag` gets set to true.
   // This is needed to defend against e.g. hash table resizes without
   // massively complicating the generated code. 
   auto runMorselWithRetry = [&](PipelineRunner& runner, bool force_pick) {
      // The restart flag was installed by the current context in `runPipeline` or `runMorsel`.
      bool& restart_flag = ExecutionContext::getInstalledRestartFlag();
      assert(!restart_flag);

      // Run the morsel until the flag is not set. The flag can be set multiple times if e.g.
      // multiple hash table resizes happen for the same chunk.
      bool pickResult = runner.runMorsel(force_pick);
      while (restart_flag) {
         restart_flag = false;
         runner.prepareForRerun();
         runner.runMorsel(false);
      }

      return pickResult;
   };

   // Only the first interpreter is allowed to pick a morsel - the morsel of that source is then
   // fixed for all remaining interpreters in the pipeline.
   bool pickResult = runMorselWithRetry(*interpreters[0], true);
   if (pickResult) {
      for (auto interpreter = interpreters.begin() + 1; interpreter < interpreters.end(); ++interpreter) {
         runMorselWithRetry(**interpreter, false);
      }
      cleanUp();
   }
   return pickResult;
}

}
