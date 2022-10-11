
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

#include "grid_row_layout_algorithm.h"

#include <array>

#include "../grid_col/grid_col_layout_property.h"

#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using OHOS::Ace::V2::GridContainerUtils;
using OHOS::Ace::V2::GridSizeType;
using OHOS::Ace::V2::Gutter;
using NewLineOffset = GridRowLayoutAlgorithm::NewLineOffset;
using LayoutPair = std::pair<RefPtr<LayoutWrapper>, NewLineOffset>;

namespace {

bool OrderComparator(const LayoutPair& left, const LayoutPair& right)
{
    auto leftCol = AceType::DynamicCast<GridColLayoutProperty>(left.first->GetLayoutProperty());
    auto rightCol = AceType::DynamicCast<GridColLayoutProperty>(right.first->GetLayoutProperty());
    if (leftCol && rightCol) {
        return (leftCol->GetOrder(leftCol->GetSizeTypeValue()) < rightCol->GetOrder(rightCol->GetSizeTypeValue()));
    }
    return false;
}

// std::string ConvertSizeTypeToString(GridSizeType sizeType)
// {
//     auto index = static_cast<int32_t>(sizeType);
//     std::array<const char*, 7> refs { "xs", "sm", "lg", "md", "xl", "xxl", "undefined" }; // 7 types of size
//     return refs[index];
// }

bool ParseNewLineForLargeOffset(
    int32_t childSpan, int32_t childOffset, int32_t restColumnNum, int32_t totalColumnNum, NewLineOffset& newLineOffset)
{
    if (childOffset <= totalColumnNum) {
        return false;
    }
    auto totalOffsetStartFromNewLine = childOffset - restColumnNum;
    auto lineCountForLargeChildOffset = static_cast<int32_t>(totalOffsetStartFromNewLine / totalColumnNum);
    if (totalOffsetStartFromNewLine > totalColumnNum) {
        // ex. totalColumn 12, restColumn is 4, child offset 26, span 6. Offsets of next 2 lines are 12 and 10
        // then the child will be placed at the third new line with offset 0.
        if ((totalOffsetStartFromNewLine % totalColumnNum) + childSpan > totalColumnNum) {
            newLineOffset.offset = 0;
            lineCountForLargeChildOffset++;
        } else {
            // ex. totalColumn 12, restColumn is 4, child offset 20, span 6. Offsets of next 2 lines are 12 and 4
            // then the child will be placed at the second new line with offset 4.
            newLineOffset.offset = totalOffsetStartFromNewLine % totalColumnNum;
        }
        newLineOffset.newLineCount = lineCountForLargeChildOffset;
        return true;
    }
    if (totalOffsetStartFromNewLine + childSpan > totalColumnNum) {
        newLineOffset.newLineCount += 1;
        newLineOffset.offset = 0;
        return true;
    }
    return false;
}

void CalculateOffsetOfNewline(const RefPtr<GridColLayoutProperty>& gridCol, int32_t currentChildSpan,
    int32_t restColumnNum, int32_t totalColumnNum, GridSizeType sizeType, NewLineOffset& newLineOffset)
{
    newLineOffset.span = currentChildSpan;
    if (restColumnNum < gridCol->GetOffset(sizeType) + currentChildSpan) {
        newLineOffset.newLineCount = 1;
        // ex. if there are 7 columns left and chile span is 4 or 8(< or > than restColumnNum), offset is 5,
        // child will be set on a new row with offset 0
        if (restColumnNum >= gridCol->GetOffset(sizeType)) {
            newLineOffset.offset = 0;
            return;
        }
        // in this case, child will be set on a new row with offset (child offset - restColumnNum)
        if (restColumnNum < gridCol->GetOffset(sizeType) && restColumnNum > currentChildSpan) {
            if (ParseNewLineForLargeOffset(
                    currentChildSpan, gridCol->GetOffset(sizeType), restColumnNum, totalColumnNum, newLineOffset)) {
                return;
            }
            newLineOffset.offset = gridCol->GetOffset(sizeType) - restColumnNum;
            return;
        }
        // in this case, empty line(s) will be placed
        if (restColumnNum < gridCol->GetOffset(sizeType) && restColumnNum < currentChildSpan) {
            if (ParseNewLineForLargeOffset(
                    currentChildSpan, gridCol->GetOffset(sizeType), restColumnNum, totalColumnNum, newLineOffset)) {
                return;
            }
            newLineOffset.offset = gridCol->GetOffset(sizeType) - restColumnNum;
            return;
        }
    }
    // in this case, child can be place at current row
    newLineOffset.offset = gridCol->GetOffset(sizeType);
}

} // namespace

void GridRowLayoutAlgorithm::MeasureSelf(LayoutWrapper* layoutWrapper, SizeF& frameSize)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();

    frameSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize);
}

/* Measure each child and return total height */
float GridRowLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper, double columnUnitWidth,
    double childHeightLimit, std::pair<double, double>& gutter, GridSizeType sizeType, int32_t columnNum)
{
    auto context = NG::PipelineContext::GetCurrentContext();
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    int32_t offset = 0;
    float totalHeight = 0.0;
    float currentRowHeight = 0.0;

    /* GridRow's child must be a GridCol */
    for (auto& child : children) {
        if (child->GetHostTag() != V2::GRID_COL_ETS_TAG) {
            LOGE("Not a grid_col component");
            continue;
        }
        auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
        auto span = std::min(gridCol->GetSpan(sizeType), columnNum);
        gridCol->UpdateSizeType(sizeType);

        /* Measure child */
        LayoutConstraintF parentConstraint;
        parentConstraint.Reset();
        SizeF tmpSz(columnUnitWidth * span + (span - 1) * gutter.first, childHeightLimit);
        parentConstraint.UpdateMaxSizeWithCheck(tmpSz);
        tmpSz.SetHeight(0);
        parentConstraint.UpdateMinSizeWithCheck(tmpSz);
        child->Measure(parentConstraint);

        /* Calculate line break */
        NewLineOffset newLineOffset;
        CalculateOffsetOfNewline(gridCol, span, columnNum - offset, columnNum, sizeType, newLineOffset);

        /* accumulate total lines */
        if (newLineOffset.newLineCount > 0) {
            newLineOffset.offsetY = currentRowHeight * newLineOffset.newLineCount + gutter.second;
            totalHeight += newLineOffset.offsetY;
            offset = newLineOffset.offset;
            currentRowHeight = child->GetGeometryNode()->GetFrameSize().Height();
        } else {
            offset += newLineOffset.offset;
            newLineOffset.offsetY = gutter.second;
            auto childHeight = child->GetGeometryNode()->GetFrameSize().Height();
            currentRowHeight = std::max(currentRowHeight, childHeight);
        }

        gridColChildren_.emplace_back(std::make_pair(child, newLineOffset));
    }
    totalHeight += currentRowHeight;
    gridColChildren_.sort(OrderComparator);

    return totalHeight;
}

void GridRowLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());

    auto columnsVal = MakeRefPtr<V2::GridContainerSize>(layoutProperty->GetColumnsValue());
    auto gutterVal = MakeRefPtr<V2::Gutter>(layoutProperty->GetGutterValue());
    auto breakPointsVal = MakeRefPtr<V2::BreakPoints>(layoutProperty->GetBreakPointsValue());

    auto maxSize = CreateIdealSize(
        layoutProperty->GetLayoutConstraint().value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    auto context = NG::PipelineContext::GetCurrentContext();
    auto sizeType = GridContainerUtils::ProcessGridSizeType(breakPointsVal, Size(maxSize.Width(), maxSize.Height()));
    // TODO:
    // if (currentSizeType_ != sizeType) {
    //     auto sizeTypeString = ConvertSizeTypeToString(sizeType);
    //     component->FirebreakPointEvent(sizeTypeString);
    //     currentSizeType_ = sizeType;
    // }
    auto gutter = GridContainerUtils::ProcessGutter(sizeType, gutterVal);
    gutterInDouble_ =
        std::make_pair<double, double>(context->NormalizeToPx(gutter.first), context->NormalizeToPx(gutter.second));
    int32_t columnNum = GridContainerUtils::ProcessColumn(sizeType, columnsVal);
    columnUnitWidth_ = GridContainerUtils::ProcessColumnWidth(gutterInDouble_, columnNum, maxSize.Width());
    float childrenHeight =
        MeasureChildren(layoutWrapper, columnUnitWidth_, maxSize.Height(), gutterInDouble_, sizeType, columnNum);
    maxSize.SetHeight(childrenHeight);
    MeasureSelf(layoutWrapper, maxSize);
}

void GridRowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (gridColChildren_.empty()) {
        return;
    }

    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto directionVal = layoutProperty->GetDirectionValue();

    for (auto&& pair : gridColChildren_) {
        auto childLayoutWrapper = pair.first;
        auto& newLineOffset = pair.second;

        double offsetWidth = 0.0;
        if (directionVal == V2::GridRowDirection::RowReverse) {
            offsetWidth = ((newLineOffset.span + newLineOffset.offset) * columnUnitWidth_ +
                           ((newLineOffset.span + newLineOffset.offset) - 1) * gutterInDouble_.first);
        } else { // V2::GridRowDirection::Row
            offsetWidth = newLineOffset.offset * columnUnitWidth_ + newLineOffset.offset * gutterInDouble_.first;
        }

        OffsetF offset(offsetWidth, newLineOffset.offsetY);
        childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        childLayoutWrapper->Layout();
    }
}

} // namespace OHOS::Ace::NG
