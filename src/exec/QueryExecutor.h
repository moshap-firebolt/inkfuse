#ifndef INKFUSE_QUERYEXECUTOR_H
#define INKFUSE_QUERYEXECUTOR_H

#include "exec/PipelineExecutor.h"
#include <list>

namespace inkfuse {

/// Central query executor responsible for executing a query through incremental fusion.
namespace QueryExecutor {

/// Executor that allows pre-compiling the query (crudely). Needed to get clean perf counters
/// for the evaluation.
struct StepwiseExecutor {
   StepwiseExecutor(PipelineExecutor::QueryControlBlockArc control_block_, PipelineExecutor::ExecutionMode mode, const std::string& qname);

   /// Prepare the query, kicking off compilation.
   void prepareQuery();
   /// Run the query, perfoming the actual execution. Returns aggregated (summed) pipeline statistics.
   PipelineExecutor::PipelineStats runQuery();

   private:
   PipelineExecutor::QueryControlBlockArc control_block;
   PipelineExecutor::ExecutionMode mode;
   const std::string& qname;
   std::list<PipelineExecutor> executors;
};

/// Run a complete query to completion. Returns aggregated (summed) pipeline statistics.
PipelineExecutor::PipelineStats runQuery(PipelineExecutor::QueryControlBlockArc control_block_, PipelineExecutor::ExecutionMode mode, const std::string& qname = "query");

};

}

#endif //INKFUSE_QUERYEXECUTOR_H
