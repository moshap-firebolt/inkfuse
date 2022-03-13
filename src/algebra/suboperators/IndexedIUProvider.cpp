#include "algebra/suboperators/IndexedIUProvider.h"
#include "codegen/IRBuilder.h"
#include "runtime/Runtime.h"

namespace inkfuse {

const char* IndexedIUProviderState::name = "IndexedIUProviderState";

void IndexedIUProviderRuntime::registerRuntime() {
   RuntimeStructBuilder{IndexedIUProviderState::name}
      .addMember("start", IR::Pointer::build(IR::Void::build()));
}

}