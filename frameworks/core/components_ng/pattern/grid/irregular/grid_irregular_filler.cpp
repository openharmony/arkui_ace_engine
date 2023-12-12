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

#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"

namespace OHOS::Ace::NG {
GridIrregularFiller::GridIrregularFiller(GridLayoutInfo* info, LayoutWrapper* wrapper) : info_(info), wrapper_(wrapper)
{}

bool GridIrregularFiller::IsFull(float targetLen)
{
    return length_ > targetLen || info_->endIndex_ < wrapper_->GetTotalChildCount() - 1;
}

float GridIrregularFiller::Fill(float targetLength, const std::vector<float>& crossLens, float crossGap)
{
    while (!IsFull(targetLength)) {
        auto [row, col] = LoadOne();
        MeasureNewItem(crossLens, col, crossGap);
    }
    return length_;
}

bool GridIrregularFiller::ItemCanFit(const decltype(GridLayoutInfo::gridMatrix_)::iterator& it, int32_t itemWidth)
{
    return it == info_->gridMatrix_.end() || it->second.size() + itemWidth <= info_->crossCount_;
}

GridItemSize GridIrregularFiller::GetItemSize(int32_t idx)
{
    GridItemSize size { 1, 1 };
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    const auto* layoutOpts = &props->GetLayoutOptions().value();
    if (layoutOpts->irregularIndexes.find(idx) != layoutOpts->irregularIndexes.end()) {
        size = layoutOpts->getSizeByIndex(idx);
        // assume [row] represents crossLength and [column] represents mainLength in this class, so flip sides if
        // horizontal
        if (info_->axis_ == Axis::HORIZONTAL) {
            std::swap(size.rows, size.columns);
        }
    }
    return size;
}

std::pair<int32_t, int32_t> GridIrregularFiller::LoadOne()
{
    /* alias */
    const int32_t idx = ++info_->endIndex_;
    int32_t& row = info_->endMainLineIndex_;

    auto size = GetItemSize(idx);

    auto it = info_->gridMatrix_.find(row);
    while (!ItemCanFit(it, size.columns)) {
        // can't fill at end, find the next available line
        it = info_->gridMatrix_.find(++row);
    }
    if (it == info_->gridMatrix_.end()) {
        // create a new line
        info_->gridMatrix_[row] = {};
    }

    int32_t col = it->second.size();
    // top left square should be set to [idx], the rest to -1
    for (int32_t r = 0; r < size.rows; ++r) {
        for (int32_t c = 0; c < size.columns; ++c) {
            info_->gridMatrix_[row + r][col + c] = -1;
        }
    }

    info_->gridMatrix_[row][col] = idx;

    return { row, col };
}

void GridIrregularFiller::MeasureNewItem(const std::vector<float>& crossLens, int32_t col, float crossGap)
{
    auto child = wrapper_->GetOrCreateChildByIndex(info_->endIndex_);
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    auto constraint = props->CreateChildConstraint();

    auto mainLen = Infinity<float>();

    auto itemSize = GetItemSize(info_->endIndex_);
    float crossLen = 0.0f;
    for (int32_t i = 0; i < itemSize.columns; ++i) {
        crossLen += crossLens[i + col];
    }
    crossLen += crossGap * (itemSize.columns - 1);

    constraint.percentReference.SetCrossSize(crossLen, info_->axis_);
    if (info_->axis_ == Axis::VERTICAL) {
        constraint.maxSize = SizeF { crossLen, mainLen };
        constraint.selfIdealSize = OptionalSizeF(crossLen, std::nullopt);
    } else {
        constraint.maxSize = SizeF { mainLen, crossLen };
        constraint.selfIdealSize = OptionalSizeF(std::nullopt, crossLen);
    }

    child->Measure(constraint);
    child->Layout();

    float childHeight = child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
    float mainGap = GridUtils::GetMainGap(props, wrapper_->GetGeometryNode()->GetContentSize(), info_->axis_);
    // spread height to each row. May be buggy?
    float heightPerRow = (childHeight - (mainGap * (itemSize.rows - 1))) / itemSize.rows;
    const int32_t& row = info_->endMainLineIndex_;
    for (int32_t i = 0; i < itemSize.rows; ++i) {
        info_->lineHeightMap_[row] = std::max(info_->lineHeightMap_[row], heightPerRow);
        // increase length_ when current line is filled
        if (info_->gridMatrix_[row].size() == info_->crossCount_) {
            if (row > 0) {
                // always add the top gap of GridItems, so the first row doesn't have a gap.
                length_ += mainGap;
            }
            length_ += heightPerRow;
        }
    }
}
} // namespace OHOS::Ace::NG
