#include "algebra/suboperators/ColumnFilter.h"
#include "algebra/CompilationContext.h"
#include "codegen/Expression.h"
#include "codegen/Statement.h"

namespace inkfuse {

SuboperatorArc ColumnFilterScope::build(const RelAlgOp* source_, const IU& filter_iu_, const IU& pseudo)
{
   return SuboperatorArc{new ColumnFilterScope(source_, filter_iu_, pseudo)};
}

ColumnFilterScope::ColumnFilterScope(const RelAlgOp* source_, const IU& filter_iu_, const IU& pseudo)
: TemplatedSuboperator<EmptyState>(source_, std::vector<const IU*>{&pseudo}, std::vector<const IU*>{&filter_iu_})
{
}

void ColumnFilterScope::consumeAllChildren(CompilationContext& context)
{
   auto& builder = context.getFctBuilder();
   const auto& program = context.getProgram();

   // Resolve incoming operator scope. This is the one where we get source IUs from.
   const auto& decl = context.getIUDeclaration(*source_ius[0]);
   auto expr = IR::VarRefExpr::build(decl);

   // Construct the if - will later be closed in close().
   // All downstream operators will generate their code in the if block.
   opt_if = builder.buildIf(std::move(expr));
   {
      // And notify downstream operators that filtered IUs are now ready.
      context.notifyIUsReady(*this);
   }
}

void ColumnFilterScope::close(CompilationContext& context)
{
   // We can now close the sub-operator, this will terminate the if statement
   // and reinstall the original block.
   opt_if->End();
   opt_if.reset();
   context.notifyOpClosed(*this);
}

std::string ColumnFilterScope::id() const
{
   return "ColumnFilterScope";
}

SuboperatorArc ColumnFilterLogic::build(const RelAlgOp* source_, const IU& pseudo, const IU& incoming_, const IU& redefined, IR::TypeArc filter_type_, bool filters_itself_)
{
   return SuboperatorArc{new ColumnFilterLogic(source_, pseudo, incoming_, redefined, std::move(filter_type_), filters_itself_)};
}

ColumnFilterLogic::ColumnFilterLogic(const RelAlgOp* source_, const IU& pseudo, const IU& incoming, const IU& redefined, IR::TypeArc filter_type_, bool filters_itself_)
   : TemplatedSuboperator<EmptyState>(source_, std::vector<const IU*>{&redefined}, std::vector<const IU*>{&pseudo, &incoming}), filter_type(std::move(filter_type_)), filters_itself(filters_itself_)
{
   // When filtering a ByteArray something subtle happens:
   // The result column becomes a char*. This way we don't have to copy the entire byte array, but rather
   // just pointers. An alternative implementation would be to have variable size sinks and to do
   // memcpys. We didn't benchmark the alternatives, this is fast enough.
   if (dynamic_cast<IR::ByteArray*>(incoming.type.get())) {
      if (redefined.type->id() != "Ptr_Char") {
         throw std::runtime_error("A filtered ByteArray must become a Char*");
      }
   }
}

void ColumnFilterLogic::open(CompilationContext& context)
{
   // First request the incoming IU that gets filtered. This is extremely important as their iterator
   // should be generated outside of the `if`. If we don't descend the DAG this way, then we might generate
   // the variable-size state iterator inside the nested control flow.
   context.requestIU(*this, *source_ius[1]);
   // Only now request generation of the `if`. We know that the variable-sized iterators are outside the `if`.
   context.requestIU(*this, *source_ius[0]);
}

void ColumnFilterLogic::consumeAllChildren(CompilationContext& context)
{
   auto& builder = context.getFctBuilder();

   // Get the definition of the filter IU - this is the second source IU.
   const auto& in = context.getIUDeclaration(*source_ius[1]);
   // Declare the new IU.
   auto declare = IR::DeclareStmt::build(context.buildIUIdentifier(*provided_ius[0]), provided_ius[0]->type);
   auto assign = IR::AssignmentStmt::build(*declare, IR::VarRefExpr::build(in));

   // Register it with the context.
   context.declareIU(*provided_ius[0], *declare);

   // Add the statements to the generated program.
   builder.appendStmt(std::move(declare));
   builder.appendStmt(std::move(assign));

   // And notify consumer that IUs are ready.
   context.notifyIUsReady(*this);
}

std::string ColumnFilterLogic::id() const
{
   if (filters_itself) {
      return "ColumnSelfFilterLogic_" + filter_type->id() + "_" + source_ius[1]->type->id();
   } else {
      return "ColumnFilterLogic_" + filter_type->id() + "_" + source_ius[1]->type->id();
   }
}

}