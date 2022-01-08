#include "algebra/ColumnScan.h"
#include "exec/FuseChunk.h"

namespace inkfuse {

    ColumnScan::ColumnScan(ColumnScanParameters params_, IURef provided_iu_, const BaseColumn& column_)
        : params(std::move(params_)), provided_iu(provided_iu_), column(column_)
    {

    }

    void ColumnScan::compile(CompilationContext &context, const std::set<IURef> &required)
    {

    }

    void ColumnScan::interpret(FuseChunk* src, FuseChunk *dst)
    {

    }

    void ColumnScan::setUpState()
    {
        state = std::make_unique<ColumnScanState>(ColumnScanState{
            .data = column.getRawData(),
            .size = column.length(),
            });
    }

    void ColumnScan::tearDownState()
    {
        state.reset();
    }

    std::string ColumnScan::id() const
    {
        /// Only have to parametrize over the type.
        return "column_scan_" + params.type->id();
    }

}