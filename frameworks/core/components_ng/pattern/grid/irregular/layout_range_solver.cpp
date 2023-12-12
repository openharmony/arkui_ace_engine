#include "core/components_ng/pattern/grid/irregular/layout_range_solver.h"

#include "core/components_ng/pattern/grid/grid_layout_property.h"
namespace OHOS::Ace::NG {
GridLayoutRangeSolver::GridLayoutRangeSolver(GridLayoutInfo* info, LayoutWrapper* wrapper)
    : info_(info), wrapper_(wrapper)
{
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    opts_ = &props->GetLayoutOptions().value();
};

float GridLayoutRangeSolver::FindLayoutRange(float mainGap)
{
    // find starting row
    float start = std::max(-info_->currentOffset_, 0.0f); // start >= 0
    float len = 0.0f;
    int32_t idx = 0;

    float firstRowPos = 0.0f;
    while (len <= start) {
        auto [newRows, addLen] = AddNextRow(mainGap, idx);
        if (len + addLen > start) {
            // while condition guaranteed to break before next iteration
            info_->startMainLineIndex_ = idx;
            firstRowPos = len;
            if (idx > 0) {
                // because we add len with mainGap above the item, [len] is at the bottom of the last item
                firstRowPos += mainGap;
            }
        }
        len += addLen;
        idx += newRows;
    }

    // find ending row
    float mainSize = wrapper_->GetGeometryNode()->GetContentSize().MainSize(info_->axis_);
    float end = start + mainSize;
    while (len < end) {
        len += info_->lineHeightMap_[idx++] + mainGap;
    }
    info_->endMainLineIndex_ = idx - 1;

    return firstRowPos;
}

std::pair<int32_t, float> GridLayoutRangeSolver::AddNextRow(float mainGap, int32_t row)
{
    // consider irregular items occupying multiple rows
    int32_t maxRowCnt = 1;
    for (int c = 0; c < info_->crossCount_; ++c) {
        auto idx = info_->gridMatrix_[row][c];
        if (opts_->irregularIndexes.find(idx) != opts_->irregularIndexes.end()) {
            auto size = opts_->getSizeByIndex(idx);
            maxRowCnt = std::max(maxRowCnt, size.rows);
        }
    }

    float len = info_->lineHeightMap_[row];
    if (row > 0) {
        // always add the main gap above the item in forward layout
        len += mainGap;
    }
    for (int i = 1; i < maxRowCnt; ++i) {
        len += info_->lineHeightMap_[row + i] + mainGap;
    }

    return { maxRowCnt, len };
}
} // namespace OHOS::Ace::NG
