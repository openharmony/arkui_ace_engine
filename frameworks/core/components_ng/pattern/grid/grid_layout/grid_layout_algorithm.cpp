/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_layout/grid_layout_algorithm.h"

#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
namespace {
void OffsetByAlign(const SizeF& size, float rowLen, float colLen, float& positionX, float& positionY)
{
    // only support Alignment.Center now
    auto width = size.Width();
    positionX += (colLen - width) / 2;
    auto height = size.Height();
    positionY += (rowLen - height) / 2;
}
} // namespace

LayoutConstraintF GridLayoutAlgorithm::CreateChildConstraint(const SizeF& idealSize,
    const RefPtr<GridLayoutProperty>& layoutProperty, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan,
    const RefPtr<LayoutProperty>& childLayoutProperty) const
{
    LayoutConstraintF layoutConstraint = layoutProperty->CreateChildConstraint();

    float rowLen = 0.0;
    for (int32_t i = 0; i < rowSpan; ++i) {
        rowLen += GetItemSize(row + i, col, true);
    }
    rowLen += (rowSpan - 1) * rowsGap_;

    float colLen = 0.0;
    for (int32_t i = 0; i < colSpan; ++i) {
        colLen += GetItemSize(row, col + i, false);
    }
    colLen += (colSpan - 1) * columnsGap_;

    layoutConstraint.maxSize = SizeF(colLen, rowLen);
    layoutConstraint.percentReference = SizeF(colLen, rowLen);
    if (!childLayoutProperty || !childLayoutProperty->GetCalcLayoutConstraint()) {
        layoutConstraint.selfIdealSize.UpdateIllegalSizeWithCheck(layoutConstraint.maxSize);
    }
    return layoutConstraint;
}

void GridLayoutAlgorithm::InitGridCeils(LayoutWrapper* layoutWrapper, const SizeF& idealSize)
{
    auto layoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    rowsGap_ = ConvertToPx(layoutProperty->GetRowsGap().value_or(0.0_vp), scale, idealSize.Height()).value_or(0);
    columnsGap_ = ConvertToPx(layoutProperty->GetColumnsGap().value_or(0.0_vp), scale, idealSize.Width()).value_or(0);
    auto rows = ParseTemplateArgs(GridUtils::ParseArgs(layoutProperty->GetRowsTemplate().value_or("")),
        idealSize.Height(), rowsGap_, layoutWrapper->GetTotalChildCount());
    auto cols = ParseTemplateArgs(GridUtils::ParseArgs(layoutProperty->GetColumnsTemplate().value_or("")),
        idealSize.Width(), columnsGap_, layoutWrapper->GetTotalChildCount());
    auto rowsLen = rows.first;
    auto colsLen = cols.first;
    if (rowsLen.empty()) {
        rowsLen.push_back(idealSize.Height());
    }
    rowsGap_ = rows.second;

    if (colsLen.empty()) {
        colsLen.push_back(idealSize.Width());
    }
    columnsGap_ = cols.second;

    if (static_cast<uint32_t>(mainCount_) != rowsLen.size()) {
        mainCount_ = static_cast<int32_t>(rowsLen.size());
    }
    if (static_cast<uint32_t>(crossCount_) != colsLen.size()) {
        crossCount_ = static_cast<int32_t>(colsLen.size());
        info_.crossCount_ = crossCount_;
    }

    gridCells_.clear();
    int32_t row = 0;
    for (const auto& height : rowsLen) {
        int32_t col = 0;
        for (const auto& width : colsLen) {
            gridCells_[row][col] = SizeF(width, height);
            ++col;
        }
        ++row;
    }
}

bool GridLayoutAlgorithm::CheckGridPlaced(int32_t index, int32_t row, int32_t col, int32_t& rowSpan, int32_t& colSpan)
{
    auto rowIter = info_.gridMatrix_.find(row);
    if (rowIter != info_.gridMatrix_.end()) {
        auto colIter = rowIter->second.find(col);
        if (colIter != rowIter->second.end()) {
            return false;
        }
    }
    rowSpan = std::min(mainCount_ - row, rowSpan);
    colSpan = std::min(crossCount_ - col, colSpan);
    int32_t rSpan = 0;
    int32_t cSpan = 0;
    int32_t retColSpan = 1;
    while (rSpan < rowSpan) {
        rowIter = info_.gridMatrix_.find(rSpan + row);
        if (rowIter != info_.gridMatrix_.end()) {
            cSpan = 0;
            while (cSpan < colSpan) {
                if (rowIter->second.find(cSpan + col) != rowIter->second.end()) {
                    colSpan = cSpan;
                    break;
                }
                ++cSpan;
            }
        } else {
            cSpan = colSpan;
        }
        if (retColSpan > cSpan) {
            break;
        }
        retColSpan = cSpan;
        ++rSpan;
    }

    rowSpan = rSpan;
    colSpan = retColSpan;
    for (int32_t i = row; i < row + rowSpan; ++i) {
        std::map<int32_t, int32_t> rowMap;
        auto iter = info_.gridMatrix_.find(i);
        if (iter != info_.gridMatrix_.end()) {
            rowMap = iter->second;
        }
        for (int32_t j = col; j < col + colSpan; ++j) {
            rowMap.emplace(std::make_pair(j, index));
        }
        info_.gridMatrix_[i] = rowMap;
    }
    return true;
}

void GridLayoutAlgorithm::GetNextGrid(int32_t& curRow, int32_t& curCol) const
{
    if (isVertical_) {
        ++curCol;
        if (curCol >= crossCount_) {
            curCol = 0;
            ++curRow;
        }
    } else {
        ++curRow;
        if (curRow >= mainCount_) {
            curRow = 0;
            ++curCol;
        }
    }
}

OffsetF GridLayoutAlgorithm::ComputeItemPosition(LayoutWrapper* layoutWrapper, int32_t row, int32_t col,
    int32_t& rowSpan, int32_t& colSpan, const RefPtr<LayoutWrapper>& childLayoutWrapper) const
{
    auto layoutProperty = DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, OffsetF());
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), frameSize);

    // Calculate the position for current child.
    float positionX = 0.0f;
    float positionY = 0.0f;
    for (int32_t i = 0; i < row; ++i) {
        positionY += GetItemSize(i, 0, true);
    }
    positionY += row * rowsGap_;
    for (int32_t i = 0; i < col; ++i) {
        positionX += GetItemSize(0, i, false);
    }
    positionX += col * columnsGap_;

    // Calculate the size for current child.
    float rowLen = 0.0f;
    float colLen = 0.0f;
    for (int32_t i = 0; i < rowSpan; ++i) {
        rowLen += GetItemSize(row + i, col, true);
    }
    rowLen += (rowSpan - 1) * rowsGap_;
    for (int32_t i = 0; i < colSpan; ++i) {
        colLen += GetItemSize(row, col + i, false);
    }
    colLen += (colSpan - 1) * columnsGap_;

    if (childLayoutWrapper) {
        auto childSize = childLayoutWrapper->GetGeometryNode()->GetMarginFrameSize();
        OffsetByAlign(childSize, rowLen, colLen, positionX, positionY);
    }

    // If RTL, place the item from right.
    if (rightToLeft_) {
        positionX = frameSize.Width() - positionX - colLen;
    }
    return OffsetF(positionX, positionY);
}

float GridLayoutAlgorithm::GetItemSize(int32_t row, int32_t col, bool height) const
{
    auto nextC = gridCells_.find(row);
    if (nextC != gridCells_.end()) {
        auto nextCol = nextC->second;
        auto nextColRow = nextCol.find(col);
        if (nextColRow != nextCol.end()) {
            return height ? nextColRow->second.Height() : nextColRow->second.Width();
        }
    }
    return 0.0;
}

GridItemRect GridLayoutAlgorithm::GetItemRect(const RefPtr<GridLayoutProperty>& gridLayoutProperty,
    const RefPtr<GridItemLayoutProperty>& childLayoutProperty, int32_t index) const
{
    GridItemRect rect;
    if (gridLayoutProperty->GetLayoutOptions().has_value()) {
        const auto& options = *gridLayoutProperty->GetLayoutOptions();
        if (options.getRectByIndex) {
            rect = options.getRectByIndex(index);
            rect.rowSpan = std::max(rect.rowSpan, 1);
            rect.columnSpan = std::max(rect.columnSpan, 1);
        }
    } else {
        if (childLayoutProperty) {
            rect.rowStart = childLayoutProperty->GetRowStart().value_or(-1);
            rect.columnStart = childLayoutProperty->GetColumnStart().value_or(-1);
            rect.rowSpan = std::max(childLayoutProperty->GetRowEnd().value_or(-1) - rect.rowStart + 1, 1);
            rect.columnSpan = std::max(childLayoutProperty->GetColumnEnd().value_or(-1) - rect.columnStart + 1, 1);
        }
    }
    return rect;
}

void GridLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    Axis axis = info_.axis_;
    auto idealSize =
        CreateIdealSize(gridLayoutProperty->GetLayoutConstraint().value(), axis, MeasureType::MATCH_PARENT, true);
    if (GreatOrEqual(GetMainAxisSize(idealSize, axis), Infinity<float>())) {
        idealSize = gridLayoutProperty->GetLayoutConstraint().value().percentReference;
        TAG_LOGI(AceLogTag::ACE_GRID, "size of main axis value is infinity, use percent reference");
    }
    rightToLeft_ = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection() == TextDirection::RTL;

    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    MinusPaddingToSize(gridLayoutProperty->CreatePaddingAndBorder(), idealSize);
    InitGridCeils(layoutWrapper, idealSize);

    int32_t rowIndex = 0;
    int32_t colIndex = 0;
    int32_t itemIndex = 0;
    itemsPosition_.clear();
    info_.gridMatrix_.clear();
    info_.startIndex_ = 0;
    info_.hasBigItem_ = false;
    for (int32_t index = 0; index < mainCount_ * crossCount_; ++index) {
        auto childLayoutWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childLayoutWrapper) {
            break;
        }
        auto layoutProperty = childLayoutWrapper->GetLayoutProperty();
        if (!layoutProperty) {
            break;
        }

        auto childLayoutProperty = DynamicCast<GridItemLayoutProperty>(layoutProperty);
        auto rect = GetItemRect(gridLayoutProperty, childLayoutProperty, index);
        int32_t itemRowStart = rect.rowStart;
        int32_t itemColStart = rect.columnStart;
        int32_t itemRowSpan = rect.rowSpan;
        int32_t itemColSpan = rect.columnSpan;
        if (itemRowSpan > 1 || itemColSpan > 1) {
            info_.hasBigItem_ = true;
        }

        if (itemRowStart >= 0 && itemRowStart < mainCount_ && itemColStart >= 0 && itemColStart < crossCount_ &&
            CheckGridPlaced(itemIndex, itemRowStart, itemColStart, itemRowSpan, itemColSpan)) {
            childLayoutWrapper->Measure(CreateChildConstraint(idealSize, gridLayoutProperty, itemRowStart, itemColStart,
                itemRowSpan, itemColSpan, childLayoutProperty));
            itemsPosition_.try_emplace(index, ComputeItemPosition(layoutWrapper, itemRowStart, itemColStart,
                                                  itemRowSpan, itemColSpan, childLayoutWrapper));
        } else {
            while (!CheckGridPlaced(itemIndex, rowIndex, colIndex, itemRowSpan, itemColSpan)) {
                GetNextGrid(rowIndex, colIndex);
                if (rowIndex >= mainCount_ || colIndex >= crossCount_) {
                    break;
                }
            }
            if (rowIndex >= mainCount_ || colIndex >= crossCount_) {
                continue;
            }
            childLayoutWrapper->Measure(CreateChildConstraint(
                idealSize, gridLayoutProperty, rowIndex, colIndex, itemRowSpan, itemColSpan, childLayoutProperty));
            itemsPosition_.try_emplace(index,
                ComputeItemPosition(layoutWrapper, rowIndex, colIndex, itemRowSpan, itemColSpan, childLayoutWrapper));

            PrintConflictingPositionLog(itemIndex, rect, rowIndex, colIndex, itemRowSpan, itemColSpan);
        }

        if (childLayoutProperty) {
            childLayoutProperty->UpdateRealRowSpan(itemRowSpan);
            childLayoutProperty->UpdateRealColumnSpan(itemColSpan);
        }

        ++itemIndex;
    }
    info_.endIndex_ = itemIndex - 1;
    info_.startMainLineIndex_ = 0;
    auto iter = info_.gridMatrix_.rbegin();
    info_.endMainLineIndex_ = (iter == info_.gridMatrix_.rend() ? -1 : iter->first);
}

void GridLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, frameSize);
    layoutWrapper->RemoveAllChildInRenderTree();
    for (int32_t index = 0; index < mainCount_ * crossCount_; ++index) {
        OffsetF childOffset;
        auto childPosition = itemsPosition_.find(index);
        if (childPosition != itemsPosition_.end()) {
            auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            if (!childWrapper) {
                break;
            }
            childOffset = childPosition->second;
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(padding.Offset() + childOffset);
            childWrapper->Layout();
        }
    }

    for (const auto& mainLine : info_.gridMatrix_) {
        int32_t itemIndex = -1;
        for (const auto& crossLine : mainLine.second) {
            // If item index is the same, must be the same GridItem, needn't layout again.
            if (itemIndex == crossLine.second) {
                continue;
            }
            itemIndex = crossLine.second;
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(itemIndex);
            if (!wrapper) {
                break;
            }
            auto layoutProperty = wrapper->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            auto gridItemLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(layoutProperty);
            CHECK_NULL_VOID(gridItemLayoutProperty);
            gridItemLayoutProperty->UpdateMainIndex(mainLine.first);
            gridItemLayoutProperty->UpdateCrossIndex(crossLine.first);
            UpdateRealGridItemPositionInfo(wrapper, mainLine.first, crossLine.first);
        }
    }
}

void GridLayoutAlgorithm::PrintConflictingPositionLog(
    int32_t itemIndex, GridItemRect rect, int32_t rowIndex, int32_t colIndex, int32_t rowSpan, int32_t colSpan)
{
    if (!(rect.rowStart == -1 && rect.columnStart == -1 && rect.rowSpan == 1 && rect.columnSpan == 1)) {
        TAG_LOGI(AceLogTag::ACE_GRID,
            "item index:%{public}d has been set to a conflicting position row:%{public}d, col:%{public}d, "
            "rowSpan:%{public}d, colSpan:%{public}d. reset to [%{public}d, %{public}d, %{public}d, %{public}d]",
            itemIndex, rect.rowStart, rect.columnStart, rect.rowSpan, rect.columnSpan, rowIndex, colIndex, rowSpan,
            colSpan);
    }
}
} // namespace OHOS::Ace::NG
