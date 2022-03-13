#ifndef INKFUSE_EXPRESSIONOP_H
#define INKFUSE_EXPRESSIONOP_H

#include "algebra/RelAlgOp.h"
#include "codegen/Value.h"
#include <unordered_set>
#include <vector>

namespace inkfuse {

/// Relational algebra operator for evaluating a set of expressions.
struct ExpressionOp : public RelAlgOp {
   struct Node {
      virtual ~Node() = default;
   };

   using NodePtr = std::unique_ptr<Node>;

   /// Constant expression.
   struct ConstantNode : public Node {
      ConstantNode(IR::ValuePtr val);

      IR::ValuePtr value;
      IU iu;
   };

   /// Reference to a provided IU.
   struct IURefNode : public Node {
      IURefNode(const IU* child_);

      const IU* child;
   };

   /// Single compute node which is part of a larger expression tree.
   struct ComputeNode : public Node {
      /// ExpressionOp types.
      enum class Type {
         Add,
         Cast,
         Subtract,
         Multiply,
         Divide,
         Eq,
         Less,
         LessEqual,
         Greater,
         GreaterEqual,
      };

      ComputeNode(Type code, std::vector<Node*> children);
      ComputeNode(IR::TypeArc casted, Node* child);

      // Which expression?
      Type code;
      // Output IU on this node.
      IU out;
      // Children of this expression. Pointers are useful for DAG-shaped expression trees.
      std::vector<Node*> children;
   };

   ExpressionOp(
      std::vector<std::unique_ptr<RelAlgOp>> children_,
      std::string op_name_,
      std::vector<Node*>
         out_,
      std::vector<NodePtr>
         nodes_);

   void decay(std::vector<const IU*> required, PipelineDAG& dag) const override;

   protected:
   void addIUs(std::vector<const IU*>& set) const override;

   /// Helper for decaying the expression DAG without duplicate subops.
   void decayNode(
      Node* node,
      std::unordered_map<Node*, const IU*>& built,
      PipelineDAG& dag) const;

   private:
   // Output nodes which actually generate columns.
   std::vector<Node*> out;
   /// Compute nodes which have to be evaluated.
   std::vector<NodePtr> nodes;
};

}

#endif //INKFUSE_EXPRESSIONOP_H