#include "algebra/suboperators/ColumnFilter.h"
#include "algebra/CompilationContext.h"
#include "codegen/Expression.h"
#include "codegen/Statement.h"

namespace inkfuse {

SuboperatorArc ColumnFilterScope::build(const RelAlgOp* source_, std::vector<const IU*> source_ius_, const IU& filter_iu_, const IU& pseudo)
{
   return SuboperatorArc{new ColumnFilterScope(source_, std::move(source_ius_), filter_iu_, pseudo)};
}

ColumnFilterScope::ColumnFilterScope(const RelAlgOp* source_, std::vector<const IU*> source_ius_, const IU& filter_iu_, const IU& pseudo)
: TemplatedSuboperator<EmptyState, EmptyState>(source_, std::vector<const IU*>{&pseudo}, std::move(source_ius_)), filter_iu(filter_iu_)
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

SuboperatorArc ColumnFilterLogic::build(const RelAlgOp* source_, const IU& pseudo, const IU& incoming_, const IU& redefined)
{
   return SuboperatorArc{new ColumnFilterLogic(source_, pseudo, incoming_, redefined)};
}

ColumnFilterLogic::ColumnFilterLogic(const RelAlgOp* source_, const IU& pseudo, const IU& incoming_, const IU& redefined)
   : TemplatedSuboperator<EmptyState, EmptyState>(source_, std::vector<const IU*>{&redefined}, std::vector<const IU*>{&pseudo}), incoming(incoming_)
{
}

void ColumnFilterLogic::consumeAllChildren(CompilationContext& context)
{
   auto& builder = context.getFctBuilder();

   const auto& in = context.getIUDeclaration(incoming);
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
   return "ColumnFilterLogic_" + incoming.type->id();
}

}