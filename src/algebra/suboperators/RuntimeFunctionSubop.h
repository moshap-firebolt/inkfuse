#ifndef INKFUSE_RUNTIMEFUNCTIONSUBOP_H
#define INKFUSE_RUNTIMEFUNCTIONSUBOP_H

#include "algebra/suboperators/Suboperator.h"

namespace inkfuse {

/// Runtime state of a given RuntimeFunctionSubop.
struct RuntimeFunctionSubopState {
   static const char* name;

   /// Backing object used as the first argument in the call.
   void* this_object;
};

/// RuntimeFunctionSubop calls a runtime function on a given object.
/// Takes an argument as input IU and computes an output IU given a runtime function.
/// An example is a hash-table lookup.
/// TODO(benjamin) this is not very tidy code:
///   - It would be cleaner to separate the this_object out of the suboperator state.
///   - Additionally we should clean up the argument/return type mess. For example the implicit derefing is really nasty.
struct RuntimeFunctionSubop : public TemplatedSuboperator<RuntimeFunctionSubopState> {
   static const bool hasConsume = false;
   static const bool hasConsumeAll = true;

   /// Build an insert function for a hash table.
   static std::unique_ptr<RuntimeFunctionSubop> htInsert(const RelAlgOp* source, const IU* pointers_, const IU& key_, std::vector<const IU*> pseudo_ius_, void* hash_table_ = nullptr);

   /// Build a hash table lookup function that disables every found slot.
   static std::unique_ptr<RuntimeFunctionSubop> htLookupDisable(const RelAlgOp* source, const IU& pointers_, const IU& key_, std::vector<const IU*> pseudo_ius_, void* hash_table_ = nullptr);

   /// Build a hash table lookup function.
   template <class HashTable>
   static std::unique_ptr<RuntimeFunctionSubop> htLookup(const RelAlgOp* source, const IU& pointers_, const IU& key_, std::vector<const IU*> pseudo_ius_, void* hash_table_ = nullptr) {
      std::string fct_name = "ht_" + HashTable::ID + "_lookup";
      std::vector<const IU*> in_ius{&key_};
      for (auto pseudo : pseudo_ius_) {
         // Pseudo IUs are used as input IUs in the backing graph, but do not influence arguments.
         in_ius.push_back(pseudo);
      }
      std::vector<bool> ref{key_.type->id() != "ByteArray" && key_.type->id() != "Ptr_Char"};
      std::vector<const IU*> out_ius_{&pointers_};
      std::vector<const IU*> args{&key_};
      const IU* out = &pointers_;
      return std::unique_ptr<RuntimeFunctionSubop>(
         new RuntimeFunctionSubop(
            source,
            std::move(fct_name),
            std::move(in_ius),
            std::move(out_ius_),
            std::move(args),
            std::move(ref),
            out,
            hash_table_));
   }

   /// Build a hash table lookup or insert function.
   template <class HashTable>
   static std::unique_ptr<RuntimeFunctionSubop> htLookupOrInsert(const RelAlgOp* source, const IU* pointers_, const IU& key_, std::vector<const IU*> pseudo_ius_, void* hash_table_ = nullptr) {
      std::string fct_name = "ht_" + HashTable::ID + "_lookup_or_insert";
      std::vector<const IU*> in_ius{&key_};
      for (auto pseudo : pseudo_ius_) {
         // Pseudo IUs are used as input IUs in the backing graph, but do not influence arguments.
         in_ius.push_back(pseudo);
      }
      // The argument needs to be referenced if we directly use a non-packed IU as argument.
      std::vector<bool> ref{key_.type->id() != "ByteArray" && key_.type->id() != "Ptr_Char"};
      std::vector<const IU*> out_ius_;
      if (pointers_) {
         out_ius_.push_back(pointers_);
      }
      std::vector<const IU*> args{&key_};
      return std::unique_ptr<RuntimeFunctionSubop>(
         new RuntimeFunctionSubop(
            source,
            std::move(fct_name),
            std::move(in_ius),
            std::move(out_ius_),
            std::move(args),
            std::move(ref),
            pointers_,
            hash_table_));
   }

   /// Build a lookup function for a hash table with a 0-byte key.
   static std::unique_ptr<RuntimeFunctionSubop> htNoKeyLookup(const RelAlgOp* source, const IU& pointers_, const IU& input_dependency, void* hash_table_ = nullptr);

   static void registerRuntime();

   void consumeAllChildren(CompilationContext& context) override;

   void setUpStateImpl(const ExecutionContext& context) override;

   std::string id() const override;

   protected:
   RuntimeFunctionSubop(
      const RelAlgOp* source,
      std::string fct_name_,
      std::vector<const IU*> in_ius_,
      std::vector<const IU*> out_ius_,
      std::vector<const IU*> args_,
      std::vector<bool> ref_,
      const IU* out_,
      void* this_object_);

   /// The function name.
   std::string fct_name;
   /// The object passed as first argument to the runtime function.
   void* this_object;
   /// The IUs used as arguments.
   std::vector<const IU*> args;
   /// Reference annotations - which of the arguments need to be referenced before being passed to the function.
   std::vector<bool> ref;
   /// Optional output IU.
   const IU* out;
};


}

#endif //INKFUSE_RUNTIMEFUNCTIONSUBOP_H
