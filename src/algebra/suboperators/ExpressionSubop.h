#ifndef INKFUSE_EXPRESSION_SUBOP_H
#define INKFUSE_EXPRESSION_SUBOP_H

#include "algebra/ExpressionOp.h"
#include "algebra/suboperators/Suboperator.h"

namespace inkfuse {

/// Basic expression sub-operator, taking a set of input IUs and producing one output IU.
struct ExpressionSubop : public TemplatedSuboperator<EmptyState, EmptyState> {

   /// Constructor for directly building a smart pointer.
   static SuboperatorArc build(const RelAlgOp* source_, std::unordered_set<const IU*> provided_ius_, std::vector<const IU*> operands_, ExpressionOp::ComputeNode::Type type_);
   /// Constructor.
   ExpressionSubop(const RelAlgOp* source_, std::unordered_set<const IU*> provided_ius_, std::vector<const IU*> operands_, ExpressionOp::ComputeNode::Type type_);

   /// Consume once all IUs are ready.
   void consumeAllChildren(CompilationContext& context) override;

   std::string id() const override;

   private:
   // Operands of the expression - order matters!
   std::vector<const IU*> operands;
   // Which expression type to evaluate.
   ExpressionOp::ComputeNode::Type type;

};

}

#endif //INKFUSE_EXPRESSION_SUBOP_H
