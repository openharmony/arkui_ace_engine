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

#include "core/components_ng/pattern/grid/grid_adaptive/grid_adaptive_layout_algorithm.h"

namespace OHOS::Ace::NG {

void GridAdaptiveLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    info_.gridMatrix_.clear();
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    auto layoutDirection = gridLayoutProperty->GetGridDirection().value_or(FlexDirection::ROW);
    auto axis = (layoutDirection == FlexDirection::ROW || layoutDirection == FlexDirection::ROW_REVERSE)
                    ? Axis::HORIZONTAL
                    : Axis::VERTICAL;
    auto idealSize =
        CreateIdealSize(gridLayoutProperty->GetLayoutConstraint().value(), axis, MeasureType::MATCH_CONTENT);
    auto padding = gridLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);

    auto firstChildWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(firstChildWrapper);
    auto layoutConstraint = gridLayoutProperty->CreateChildConstraint();
    firstChildWrapper->Measure(layoutConstraint);
    auto firstChildSize = firstChildWrapper->GetGeometryNode()->GetMarginFrameSize();

    // Calculate grid cell size.
    gridCellSize_ = firstChildSize;
    auto cellLength = gridLayoutProperty->GetCellLength();
    if (cellLength.has_value() && cellLength > 0) {
        auto cellLengthInPx = static_cast<float>(Dimension(cellLength.value(), DimensionUnit::VP).ConvertToPx());
        if (axis == Axis::HORIZONTAL) {
            gridCellSize_.SetHeight(cellLengthInPx);
        } else {
            gridCellSize_.SetWidth(cellLengthInPx);
        }
    }

    // Calculate cell count and display count.
    auto minCount = std::max(gridLayoutProperty->GetMinCount().value_or(1), 1);
    auto maxCount = std::max(gridLayoutProperty->GetMaxCount().value_or(Infinity<int32_t>()), 1);
    if (minCount > maxCount) {
        minCount = 1;
        maxCount = Infinity<int32_t>();
    }
    auto maxSize = gridLayoutProperty->GetLayoutConstraint()->maxSize;
    auto refWidth = idealSize.Width().has_value() ? idealSize.Width().value() : maxSize.Width();
    auto refHeight = idealSize.Height().has_value() ? idealSize.Height().value() : maxSize.Height();
    auto scale = gridLayoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(gridLayoutProperty->GetRowsGap().value_or(0.0_vp), scale, refHeight).value_or(0);
    auto columnsGap = ConvertToPx(gridLayoutProperty->GetColumnsGap().value_or(0.0_vp), scale, refWidth).value_or(0);
    auto childrenCount = layoutWrapper->GetTotalChildCount();
    auto mainGap = (axis == Axis::HORIZONTAL) ? columnsGap : rowsGap;
    auto crossGap = (axis == Axis::HORIZONTAL) ? rowsGap : columnsGap;
    mainCount_ = std::floor((idealSize.MainSize(axis).value_or(maxSize.MainSize(axis)) + mainGap) /
                            (gridCellSize_.MainSize(axis) + mainGap));
    mainCount_ = std::clamp(mainCount_, minCount, maxCount);
    crossCount_ = std::floor((idealSize.CrossSize(axis).value_or(Infinity<float>()) + crossGap) /
                             (gridCellSize_.CrossSize(axis) + crossGap));
    auto maxCrossCount = std::max(static_cast<int32_t>(std::ceil(static_cast<float>(childrenCount) / mainCount_)), 1);
    crossCount_ = std::clamp(crossCount_, 1, maxCrossCount);
    displayCount_ = std::min(childrenCount, mainCount_ * crossCount_);

    // Update frame size.
    auto rowCount = axis == Axis::HORIZONTAL ? crossCount_ : mainCount_;
    auto columnCount = axis == Axis::HORIZONTAL ? mainCount_ : crossCount_;
    rowCount_ = rowCount;
    columnCount_ = columnCount;
    idealSize.UpdateIllegalSizeWithCheck(
        OptionalSizeF(columnCount * gridCellSize_.Width() + (columnCount - 1) * columnsGap,
            rowCount * gridCellSize_.Height() + (rowCount - 1) * rowsGap));
    AddPaddingToSize(padding, idealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.ConvertToSizeT());

    // Create child constraint.
    auto childLayoutConstraint = gridLayoutProperty->CreateChildConstraint();
    childLayoutConstraint.maxSize.UpdateSizeWithCheck(gridCellSize_);

    // Measure children.
    for (int32_t index = 0; index < displayCount_; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            continue;
        }
        childWrapper->Measure(childLayoutConstraint);
    }
}

void GridAdaptiveLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = gridLayoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, frameSize);
    auto direction = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();

    int32_t total = layoutWrapper->GetTotalChildCount();
    for (int32_t index = 0; index < total; ++index) {
        if (index < displayCount_) {
            auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
            if (!childWrapper) {
                continue;
            }
            auto childOffset = CalculateChildOffset(index, layoutWrapper);
            if (direction == TextDirection::RTL) {
                childOffset.SetX(frameSize.CrossSize(Axis::VERTICAL) - childOffset.GetX() -
                                 childWrapper->GetGeometryNode()->GetMarginFrameSize().Width() +
                                 padding.left.value_or(.0f) + padding.right.value_or(.0f));
            }
            childWrapper->GetGeometryNode()->SetMarginFrameOffset(childOffset);
            childWrapper->Layout();
        } else {
            layoutWrapper->RemoveChildInRenderTree(index);
        }
    }

    for (const auto& mainLine : info_.gridMatrix_) {
        int32_t itemIdex = -1;
        for (const auto& crossLine : mainLine.second) {
            // If item index is the same, must be the same GridItem, need't layout again.
            if (itemIdex == crossLine.second) {
                continue;
            }
            itemIdex = crossLine.second;
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(itemIdex);
            if (!wrapper) {
                continue;
            }
            auto layoutProperty = wrapper->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            auto gridItemLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(layoutProperty);
            CHECK_NULL_VOID(gridItemLayoutProperty);
            gridItemLayoutProperty->UpdateMainIndex(mainLine.first);
            gridItemLayoutProperty->UpdateCrossIndex(crossLine.first);
        }
    }
    info_.crossCount_ = columnCount_;
    info_.endIndex_ = displayCount_ - 1;
    info_.startMainLineIndex_ = 0;
    info_.endMainLineIndex_ = rowCount_ - 1;
}

OffsetF GridAdaptiveLayoutAlgorithm::CalculateChildOffset(int32_t index, LayoutWrapper* layoutWrapper)
{
    auto frameSize = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    auto layoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, OffsetF());
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto layoutDirection = layoutProperty->GetGridDirection().value_or(FlexDirection::ROW);
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(layoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap =
        ConvertToPx(layoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);

    int32_t rowIndex = 0;
    int32_t columnIndex = 0;
    switch (layoutDirection) {
        case FlexDirection::ROW:
            rowIndex = index / mainCount_;
            columnIndex = index % mainCount_;
            break;
        case FlexDirection::ROW_REVERSE:
            rowIndex = index / mainCount_;
            columnIndex = mainCount_ - index % mainCount_ - 1;
            break;
        case FlexDirection::COLUMN:
            columnIndex = index / mainCount_;
            rowIndex = index % mainCount_;
            break;
        case FlexDirection::COLUMN_REVERSE:
            columnIndex = index / mainCount_;
            rowIndex = mainCount_ - index % mainCount_ - 1;
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_GRID, "%{public}d is not support", layoutDirection);
            break;
    }
    info_.gridMatrix_[rowIndex][columnIndex] = index;

    auto positionX = columnIndex * (gridCellSize_.Width() + columnsGap);
    auto positionY = rowIndex * (gridCellSize_.Height() + rowsGap);
    return padding.Offset() + OffsetF(positionX, positionY);
}

} // namespace OHOS::Ace::NG