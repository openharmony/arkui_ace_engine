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
    // find starting row
    float start = std::max(-info_->currentOffset_, 0.0f); // start >= 0

    float len = 0.0f;
    int32_t idx = 0;
    float rowHeight = 0.0f;
    while (len < start) {
        auto [newRows, addLen] = AddNextRows(mainGap, idx);
        if (len + addLen > start) {
            rowHeight = addLen - mainGap;
            break;
        }
        len += addLen;
        idx += newRows;
    }

    // because we add len with mainGap above the item in AddNextRow, [len] is at the bottom of the last item
    if (idx > 0) {
        len += mainGap;
    }
    return StartingRowInfo { idx, len, rowHeight };
}

std::pair<int32_t, float> GridLayoutRangeSolver::AddNextRows(float mainGap, int32_t row)
{
    int32_t maxRowCnt = 1;

    const auto& irregulars = opts_->irregularIndexes;
    // consider irregular items occupying multiple rows
    for (int c = 0; c < info_->crossCount_; ++c) {
        auto idx = info_->gridMatrix_.at(row).at(c);
        if (opts_->getSizeByIndex && irregulars.find(idx) != irregulars.end()) {
            auto size = opts_->getSizeByIndex(idx);
            maxRowCnt = std::max(maxRowCnt, size.rows);
        }
    }

    float len = info_->lineHeightMap_.at(row);
    if (row > 0) {
        // always add the main gap above the item in forward layout
        len += mainGap;
    }
    for (int i = 1; i < maxRowCnt; ++i) {
        len += info_->lineHeightMap_.at(row + i) + mainGap;
    }

    return { maxRowCnt, len };
}
} // namespace OHOS::Ace::NG
