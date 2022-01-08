#ifndef INKFUSE_SUBOPERATOR_H
#define INKFUSE_SUBOPERATOR_H

#include "algebra/IU.h"
#include <vector>
#include <set>

namespace inkfuse {

    struct CompilationContext;
    struct FuseChunk;

    /// A suboperator is a fragment of a central operator which has a corresponding vectorized primitive.
    /// An example might be the aggregation of an IU into some aggregation state.
    /// An operator can be a DAG of these fragments which can either be interpreted through the vectorized
    /// primitives or fused together.
    ///
    /// A suboperator is parametrized in two different ways:
    /// - Discrete DoF: the suboperator is parametrized over a finite set of potential values. Examples might be
    ///                 SQL types like UInt8, Date, Timestamp, ...
    /// - Infinite DoF: the suboperator is parametrized over an infinite set of potential values. Examples might be
    ///                 the length of a varchar type, or the offset into an aggregation state.
    ///
    /// When we exectute the query down the line, note that these parameters above are actually *not* degrees of freedom.
    /// This is an important observation, at run time these are all substituted.
    /// Two conclusions can be drawn from this:
    ///      1) In a pipeline-fusing engine, all parameters would be substitued with hard-baked values
    ///      2) In a vectorized engine, there would be fragments over the discrete space spanned by
    ///         the parameters, but the infinite degrees of freedom would be provided through function parameters.
    ///
    /// This concept is baked through the SubstitutableParameter expression type within our IR. When generating code,
    /// the actual operator is able to use both discrete and infinite degrees of freedom in a hard-coded way.
    /// The substitution into either function parameters or baked-in values then happens in the lower parts of the
    /// compilation stack depending on which parameters are provided to the compiler backend.
    ///
    /// This allows switching between vectorized fragments and JIT-fused execution through the same operators,
    /// parameter logic and codegen structure.
    struct Suboperator {

        /// Suboperator constructor. Parametrized as described above and also fitting a certain type.
        Suboperator() {}

        /// Compile this sub-operator into the inkfuse IR. Why does this not fit the traditional produce/consume model?
        /// Great question! Our Suboperator concept actually induces a DAG structure on the suboperators. This leads
        /// to more complex state handling which is handles in the CompilationContext.
        /// Ultimately, our strict breaking into pipelines and considering a suboperator to be a code generation concept
        /// induces far simpler code generation structure. Pipeline code can be just generated by doing a topological
        /// sort on the pipeline subops and then calling compile() in that order.
        ///
        /// The more traditional produce(), consume() interface in the original Neumann paper is effectively an artifact
        /// of needing to support multiple pipelines being generated from the same operators.
        ///
        /// \param required The IUs which actually need to be generated by this .
        virtual void compile(CompilationContext& context, const std::set<IURef>& required) = 0;

        /// Set up the state needed by this operator. In an IncrementalFusion engine it's easiest to actually
        /// make this interpreted.
        virtual void setUpState();
        /// Tear down the state needed by this operator.
        virtual void tearDownState();
        /// Get a raw pointer to the state of this operator.
        virtual void* accessState() = 0;

        /// Build a unique identifier for this suboperator (unique given the parameter set).
        virtual std::string id() const;

        /// Get the IUs produced by this operator. Note that this only refers to those IUs which are actually
        /// generated exclusively by this operator.
        virtual std::set<IURef> collectIUs();
    };

}

#endif //INKFUSE_SUBOPERATOR_H