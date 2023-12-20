/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/grid/irregular/grid_layout_range_solver.h"

#include "core/components_ng/pattern/grid/grid_layout_property.h"
namespace OHOS::Ace::NG {
GridLayoutRangeSolver::GridLayoutRangeSolver(GridLayoutInfo* info, LayoutWrapper* wrapper)
    : info_(info), wrapper_(wrapper)
{
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    opts_ = &props->GetLayoutOptions().value();
};

using Result = GridLayoutRangeSolver::StartingRowInfo;
Result GridLayoutRangeSolver::FindStartingRow(float mainGap)
{
    // Negative offset implies scrolling down, so we can start from the previous startIndex_.
    // Otherwise, we have to restart from Row 0 because of irregular items.
    if (info_->currentOffset_ <= 0.0f) {
        return SolveForward(mainGap);
    }
    return SolveBackward(mainGap);
}

Result GridLayoutRangeSolver::SolveForward(float mainGap)
{
    int32_t idx = info_->startMainLineIndex_;
    float start = -info_->currentOffset_;

    float len = 0.0f;
    while (len < start) {
        auto [newRows, addLen] = AddNextRows(mainGap, idx);
        if (len + addLen > start) {
            break;
        }
        len += addLen;
        idx += newRows;
    }

    return { idx, info_->currentOffset_ + len };
}

std::pair<int32_t, float> GridLayoutRangeSolver::AddNextRows(float mainGap, int32_t idx)
{
    int32_t rowCnt = 1;

    const auto& irregulars = opts_->irregularIndexes;
    // consider irregular items occupying multiple rows
    const auto& row = info_->gridMatrix_.at(idx);
    for (int c = 0; c < info_->crossCount_; ++c) {
        if (row.find(c) == row.end()) {
            continue;
        }
        const auto& itemIdx = row.at(c);
        if (itemIdx == -1) {
            continue;
        }
        if (opts_->getSizeByIndex && irregulars.find(itemIdx) != irregulars.end()) {
            auto size = opts_->getSizeByIndex(itemIdx);
            rowCnt = std::max(rowCnt, info_->axis_ == Axis::VERTICAL ? size.rows : size.columns);
        }
    }

    float len = info_->lineHeightMap_.at(idx);
    if (idx > 0) {
        // always add the main gap above the item in forward layout
        len += mainGap;
    }
    for (int i = 1; i < rowCnt; ++i) {
        len += info_->lineHeightMap_.at(idx + i) + mainGap;
    }

    return { rowCnt, len };
}

Result GridLayoutRangeSolver::SolveBackward(float mainGap)
{
    int32_t idx = info_->startMainLineIndex_;
    float len = 0;
    while (idx > 0 && len < info_->currentOffset_) {
        len += info_->lineHeightMap_.at(--idx) + mainGap;
    }

    auto rowCnt = CheckMultiRow(idx);
    idx -= rowCnt - 1;

    float newOffset = info_->currentOffset_ - len;
    for (int i = 0; i < rowCnt - 1; ++i) {
        newOffset -= info_->lineHeightMap_.at(idx + i) + mainGap;
    }
    return { idx, newOffset };
}

int32_t GridLayoutRangeSolver::CheckMultiRow(int32_t idx)
{
    // check multi-row item that occupies Row [idx]
    int32_t rowCnt = 1;
    const auto& mat = info_->gridMatrix_;
    const auto& row = mat.at(idx);
    for (int c = 0; c < info_->crossCount_; ++c) {
        if (row.find(c) == row.end()) {
            continue;
        }

        int32_t r = idx;
        if (row.at(c) == -1) {
            // traverse upwards to find the first row occupied by this item
            while (r > 0 && mat.at(r).at(c) == -1) {
                --r;
            }
            rowCnt = std::max(rowCnt, idx - r + 1);
        }

        // skip the columns occupied by this item
        int32_t itemIdx = mat.at(r).at(c);
        if (opts_->irregularIndexes.find(itemIdx) != opts_->irregularIndexes.end()) {
            if (opts_->getSizeByIndex) {
                auto size = opts_->getSizeByIndex(itemIdx);
                c += (info_->axis_ == Axis::VERTICAL ? size.columns : size.rows) - 1;
            } else {
                // no getSizeByIndex implies itemWidth == crossCount
                break;
            }
        }
    }
    return rowCnt;
}
} // namespace OHOS::Ace::NG
