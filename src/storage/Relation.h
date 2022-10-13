#ifndef INKFUSE_COLUMN_H
#define INKFUSE_COLUMN_H

#include "codegen/Type.h"
#include "runtime/MemoryRuntime.h"
#include <cstddef>
#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace inkfuse {

/// Base column class over a certain type.
class BaseColumn {
   public:
   /// Constructor.
   explicit BaseColumn(bool nullable_);

   /// Virtual base destructor
   virtual ~BaseColumn() = default;

   /// Get number of rows within the column.
   virtual size_t length() const = 0;

   /// Is the column nullable?
   bool isNullable();

   /// Load a value based on a string representation into the column.
   virtual void loadValue(const char* str, uint32_t strLen) = 0;

   /// Get a pointer to the backing raw data.
   virtual void* getRawData() = 0;

   /// Get the type of this .
   virtual IR::TypeArc getType() const = 0;


   protected:
   bool nullable;
};

class StringColumn final : public BaseColumn {
   public:
   explicit StringColumn(bool nullable_) : BaseColumn(nullable_) {
      offsets.reserve(1'000'000);
   }

   /// Get number of rows within the column.
   size_t length() const override {
      return offsets.size();
   };

   void* getRawData() override {
      return offsets.data();
   }

   IR::TypeArc getType() const override {
      return IR::String::build();
   };

   void loadValue(const char* str, uint32_t strLen) override;

   private:
   /// Actual vector of data that stores the char* that are passed through the runtime.
   std::vector<char*> offsets;
   /// Backing storage for the strings. `offsets` points into this allocator.
   MemoryRuntime::MemoryRegion storage;
};

/// Specific column over a certain type.
template <typename T>
class TypedColumn final : public BaseColumn {
   public:
   explicit TypedColumn(bool nullable_) : BaseColumn(nullable_) {
      storage.reserve(1'000'000);
   };

   /// Get number of rows within the column.
   size_t length() const override {
      return storage.size();
   };

   /// Get backing storage. May be modified.
   std::vector<T>& getStorage() {
      return storage;
   };

   void loadValue(const char* str, uint32_t strLen) override {
      auto val = std::stoll(str);
      getStorage().push_back(val);
   };

   void* getRawData() override {
      return storage.data();
   }

   IR::TypeArc getType() const override;

   private:
   /// Backing storage.
   std::vector<T> storage;
};

using BaseColumnPtr = std::unique_ptr<BaseColumn>;

/// Relation (for now) is just a vector containing column names to columns.
class StoredRelation {
   public:
   // Virtual base destructor.
   virtual ~StoredRelation() = default;

   /// Get a column based on the name.
   BaseColumn& getColumn(std::string_view name) const;

   /// Get a column id.
   size_t getColumnId(std::string_view name) const;

   /// Get a column based on the offset. Result has lifetime of columns vector retaining pointer stability.
   std::pair<std::string_view, BaseColumn&> getColumn(size_t index) const;

   /// Get the number of columns.
   size_t columnCount() const;

   /// Emplace a new column into a relation.
   template <typename T>
   TypedColumn<T>& attachTypedColumn(std::string_view name, bool nullable = false) {
      for (const auto& [n, _] : columns) {
         if (n == name) {
            throw std::runtime_error("Column name in StoredRelation must be unique");
         }
      }
      auto& res = columns.template emplace_back(name, std::make_unique<TypedColumn<T>>(nullable));
      return reinterpret_cast<TypedColumn<T>&>(*res.second);
   }

   /// Load .tbl rows into the table until the table is exhausted.
   void loadRows(std::istream& stream);

   /// Load a single .tbl row into the table, advancing the ifstream past the next newline.
   void loadRow(const std::string& str);

   /// Add a row to the back of the active bitvector.
   void appendRow();

   private:
   /// Backing columns.
   /// We use a vector to exploit ordering during the scan.
   std::vector<std::pair<std::string, std::unique_ptr<BaseColumn>>> columns;
};

} // namespace inkfuse

#endif // INKFUSE_COLUMN_H
