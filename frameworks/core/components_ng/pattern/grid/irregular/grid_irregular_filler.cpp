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

namespace OHOS::Ace::NG {
GridIrregularFiller::GridIrregularFiller(GridLayoutInfo* info, LayoutWrapper* wrapper) : info_(info), wrapper_(wrapper)
{
    // init starting pos
    InitPos();
}

void GridIrregularFiller::InitPos()
{
    const auto& row = info_->gridMatrix_.find(info_->startMainLineIndex_);
    if (row == info_->gridMatrix_.end()) {
        // implies empty matrix
        return;
    }
    for (auto& [col, idx] : row->second) {
        if (idx == info_->startIndex_) {
            posY_ = info_->startMainLineIndex_;
            // to land on the first item after advancing once
            posX_ = col - 1;
            return;
        }
    }
}

bool GridIrregularFiller::IsFull(float targetLen)
{
    return length_ > targetLen || info_->endIndex_ == wrapper_->GetTotalChildCount() - 1;
}

float GridIrregularFiller::Fill(const FillParameters& params)
{
    while (!IsFull(params.targetLen)) {
        int32_t prevRow = posY_;
        if (!FindNextItem(++info_->endIndex_)) {
            FillOne();
        }

        if (posY_ > prevRow) {
            // previous row has been filled
            UpdateLength(prevRow, params.mainGap);
        }

        MeasureNewItem(params, posX_);
    }
    info_->endMainLineIndex_ = posY_;
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
    const auto& opts = *props->GetLayoutOptions();
    if (opts.irregularIndexes.find(idx) != opts.irregularIndexes.end()) {
        if (!opts.getSizeByIndex) {
            // default irregular size = [1, full cross length]
            return { 1, info_->crossCount_ };
        }

        size = opts.getSizeByIndex(idx);

        // assume [row] represents crossLength and [column] represents mainLength in this class, so flip sides if
        // horizontal
        if (info_->axis_ == Axis::HORIZONTAL) {
            std::swap(size.rows, size.columns);
        }
    }
    return size;
}

void GridIrregularFiller::FillOne()
{
    /* alias */
    const int32_t idx = info_->endIndex_;
    int32_t row = posY_;

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

    posY_ = row;
    posX_ = col;
}

bool GridIrregularFiller::FindNextItem(int32_t target)
{
    const auto& mat = info_->gridMatrix_;
    while (AdvancePos()) {
        if (mat.at(posY_).at(posX_) == target) {
            return true;
        }
    }
    return false;
}

bool GridIrregularFiller::AdvancePos()
{
    ++posX_;
    if (posX_ == info_->crossCount_) {
        // go to next row
        ++posY_;
        posX_ = 0;
    }

    const auto& mat = info_->gridMatrix_;
    if (mat.find(posY_) == mat.end()) {
        return false;
    }

    const auto& row = mat.at(posY_);
    return row.find(posX_) != row.end();
}

void GridIrregularFiller::UpdateLength(int32_t prevRow, float mainGap)
{
    length_ += info_->lineHeightMap_[prevRow];
    for (int32_t row = prevRow + 1; row < posY_; ++row) {
        // always add the top gap of GridItems, so the first row doesn't have a gap.
        length_ += info_->lineHeightMap_[row] + mainGap;
    }
}

void GridIrregularFiller::MeasureNewItem(const FillParameters& params, int32_t col)
{
    auto child = wrapper_->GetOrCreateChildByIndex(info_->endIndex_);
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper_->GetLayoutProperty());
    auto constraint = props->CreateChildConstraint();

    auto mainLen = Infinity<float>();

    auto itemSize = GetItemSize(info_->endIndex_);
    float crossLen = 0.0f;
    for (int32_t i = 0; i < itemSize.columns; ++i) {
        crossLen += params.crossLens[i + col];
    }
    crossLen += params.crossGap * (itemSize.columns - 1);

    constraint.percentReference.SetCrossSize(crossLen, info_->axis_);
    if (info_->axis_ == Axis::VERTICAL) {
        constraint.maxSize = SizeF { crossLen, mainLen };
        constraint.selfIdealSize = OptionalSizeF(crossLen, std::nullopt);
    } else {
        constraint.maxSize = SizeF { mainLen, crossLen };
        constraint.selfIdealSize = OptionalSizeF(std::nullopt, crossLen);
    }

    child->Measure(constraint);

    float childHeight = child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
    // spread height to each row. May be buggy?
    float heightPerRow = (childHeight - (params.mainGap * (itemSize.rows - 1))) / itemSize.rows;
    for (int32_t i = 0; i < itemSize.rows; ++i) {
        info_->lineHeightMap_[posY_] = std::max(info_->lineHeightMap_[posY_], heightPerRow);
    }
}
} // namespace OHOS::Ace::NG
