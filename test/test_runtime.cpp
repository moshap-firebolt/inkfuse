#include "algebra/suboperators/sources/TableScanSource.h"
#include "codegen/Expression.h"
#include "codegen/IR.h"
#include "codegen/Type.h"
#include "codegen/Value.h"
#include "codegen/backend_c/BackendC.h"
#include "exec/InterruptableJob.h"
#include <unordered_set>
#include <gtest/gtest.h>

namespace inkfuse {

/// Tests for whether the runtime can be integrated into the system.
/// Created runtime structs and functions and checks if mutual calls are possible.

/// Testing function runtime integration.
TEST(test_runtime, runtime_hashing) {
   IR::Program program("test_hashing_runtime", false);

   auto ir_builder = program.getIRBuilder();
   auto& runtime = *program.getIncludes()[0];

   // Set up runtime parameter the new function will receive.
   // In this case a void pointer for the data and a size value.
   auto arg_data = IR::DeclareStmt::build("data", IR::Pointer::build(IR::Void::build()));
   auto arg_size = IR::DeclareStmt::build("len", IR::UnsignedInt::build(8));
   std::vector<IR::StmtPtr> params;
   params.push_back(std::move(arg_data));
   params.push_back(std::move(arg_size));

   // Function we are building.
   auto fct = std::make_shared<IR::Function>("test_hash", std::move(params), std::vector<bool>{false, false}, IR::UnsignedInt::build(8));
   auto fct_builder = ir_builder.createFunctionBuilder(std::move(fct));

   // Return the size by accessing the respective member in ColumnScanState.
   std::vector<IR::ExprPtr> args;
   args.emplace_back(IR::VarRefExpr::build(fct_builder.getArg(0)));
   args.emplace_back(IR::VarRefExpr::build(fct_builder.getArg(1)));
   auto hash_fct = runtime.getFunction("hash");

   auto invoke = IR::InvokeFctExpr::build(*hash_fct, std::move(args));
   auto stmt = IR::ReturnStmt::build(std::move(invoke));

   fct_builder.appendStmt(std::move(stmt));
   fct_builder.finalize();

   // Set up the c-backend.
   BackendC backend;
   auto c_program = backend.generate(program);

   // Compile it.
   InterruptableJob interrupt;
   c_program->compileToMachinecode(interrupt);

   // Get a handle to the function.
   auto fct_compiled = reinterpret_cast<uint64_t (*)(void*, uint64_t)>(c_program->getFunction("test_hash"));
   ASSERT_TRUE(fct_compiled);

   std::unordered_set<uint64_t> seen;
   for (uint64_t k = 0; k < 100; ++k) {
      uint64_t hash = fct_compiled(&k, 8);
      EXPECT_FALSE(seen.count(hash));
      seen.insert(hash);
   }
}

/// Testing struct runtime integration.
TEST(test_runtime, runtime_extstruct) {
}

/// Complex runtime tests using both structs and functions.
TEST(test_runtime, runtime_complex) {
}

/// Real inkfuse runtime with all operators and runtime structs attached.
TEST(test_runtime, runtime_real) {
   // IR program which is not compiled in standalone mode - as a result, the runtime gets included.
   IR::Program program("test_runtime_test_real", false);

   auto ir_builder = program.getIRBuilder();
   auto& runtime = *program.getIncludes()[0];
   // Set up runtime parameter the new function will receive.
   // In this case a void pointer which we will cast to a ColumnScanState pointer down the line.
   // Note that this is also how .
   auto arg = IR::DeclareStmt::build("runtime_param", IR::Pointer::build(IR::Void::build()));
   std::vector<IR::StmtPtr> params;
   params.push_back(std::move(arg));
   // Function we are building.
   auto fct = std::make_shared<IR::Function>("test_fct", std::move(params), std::vector<bool>{false}, IR::UnsignedInt::build(8));
   auto fct_builder = ir_builder.createFunctionBuilder(std::move(fct));

   // Return the size by accessing the respective member in ColumnScanState.
   auto expr = IR::StructAccessExpr::build(
      // Cast the first argument to a pointer to the ColumnScanState
      IR::CastExpr::build(
         IR::VarRefExpr::build(fct_builder.getArg(0)),
         IR::Pointer::build(runtime.getStruct(LoopDriverState::name))),
      "start");
   auto stmt = IR::ReturnStmt::build(std::move(expr));
   fct_builder.appendStmt(std::move(stmt));

   // Add the function.
   fct_builder.finalize();

   // Set up the c-backend.
   BackendC backend;
   auto c_program = backend.generate(program);

   // Compile it.
   InterruptableJob interrupt;
   c_program->compileToMachinecode(interrupt);

   // Get a handle to the function.
   auto fct_compiled = reinterpret_cast<uint64_t (*)(LoopDriverState*)>(c_program->getFunction("test_fct"));

   for (uint64_t i : {1, 100, 1000, 42, 311}) {
      // Set up actual parameter.
      LoopDriverState param{
         .start = i,
         .end = 2 * i,
      };

      // Invoke the test function multiple times.
      ASSERT_EQ(i, fct_compiled(&param));
   }
}

}
