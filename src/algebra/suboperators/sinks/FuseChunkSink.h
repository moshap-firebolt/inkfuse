#ifndef INKFUSE_FUSECHUNKSINKSAFE_H
#define INKFUSE_FUSECHUNKSINKSAFE_H

#include "algebra/suboperators/Suboperator.h"

namespace inkfuse {

/// Runtime state of a given FuseChunkSink.
struct FuseChunkSinkState {
   static const char* name;

   /// Data sink into which to write.
   void* raw_data;
   /// Size of the chunk.
   uint64_t* size;
};

/// Runtime parameters which are not needed for code generation of the respective operator.
struct FuseChunkSinkStateRuntimeParams {
   void* raw_data;
   uint64_t* size;
};

struct FuseChunkSink : public Suboperator {

   static std::unique_ptr<FuseChunkSink> build(const RelAlgOp* source, const IU& iu_to_write);

   void consume(const IU& iu, CompilationContext& context) override;

   void setUpState(const ExecutionContext& context) override;
   void tearDownState() override;
   void* accessState() const override;

   std::string id() const override;

   /// Register runtime structs and functions.
   static void registerRuntime();

   private:
   FuseChunkSink(const RelAlgOp* source, const IU& iu_to_write);
   /// Runtime state.
   std::unique_ptr<FuseChunkSinkState> state;
};

}


#endif //INKFUSE_FUSECHUNKSINKSAFE_H
