
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

#include "grid_row_event_hub.h"

#include "core/components_ng/pattern/grid_col/grid_col_layout_property.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using OHOS::Ace::V2::GridContainerUtils;
using OHOS::Ace::V2::GridSizeType;
using OHOS::Ace::V2::Gutter;
using LayoutPair = std::pair<RefPtr<FrameNode>, NewLineOffset>;

namespace {

std::string ConvertSizeTypeToString(GridSizeType sizeType)
{
    auto index = static_cast<int32_t>(sizeType);
    std::array<const char*, 7> refs { "xs", "sm", "md", "lg", "xl", "xxl", "undefined" }; // 7 types of size
    return refs[index];
}

void ParseNewLineForLargeOffset(
    int32_t childSpan, int32_t childOffset, int32_t restColumnNum, int32_t totalColumnNum, NewLineOffset& newLineOffset)
{
    int32_t totalOffsetStartFromNewLine = childOffset - restColumnNum;
    newLineOffset.newLineCount = totalOffsetStartFromNewLine / totalColumnNum + 1;
    // ex. totalColumn 12, restColumn is 4, child offset 26, span 6. Offsets of next 2 lines are 12 and 10
    // then the child will be placed at the third new line with offset 0.
    if ((totalOffsetStartFromNewLine % totalColumnNum) + childSpan > totalColumnNum) {
        newLineOffset.offset = 0;
        ++newLineOffset.newLineCount;
    } else {
        // ex. totalColumn 12, restColumn is 4, child offset 20, span 6. Offsets of next 2 lines are 12 and 4
        // then the child will be placed at the second new line with offset 4.
        newLineOffset.offset = totalOffsetStartFromNewLine % totalColumnNum;
    }
}

void CalculateOffsetOfNewline(const RefPtr<GridColLayoutProperty>& gridCol, int32_t currentChildSpan,
    int32_t restColumnNum, int32_t totalColumnNum, GridSizeType sizeType, NewLineOffset& newLineOffset)
{
    newLineOffset.span = currentChildSpan;
    int32_t offset = gridCol->GetOffset(sizeType);
    if (restColumnNum < (offset + currentChildSpan)) {
        // ex. if there are 7 columns left and chile span is 4 or 8(< or > than restColumnNum), offset is 5,
        // child will be set on a new row with offset 0
        if (restColumnNum >= offset) {
            newLineOffset.newLineCount = 1;
            newLineOffset.offset = 0;
        } else {
            ParseNewLineForLargeOffset(currentChildSpan, offset, restColumnNum, totalColumnNum, newLineOffset);
        }
    } else {
        // in this case, child can be place at current row
        newLineOffset.newLineCount = 0;
        newLineOffset.offset = offset;
    }
}

} // namespace

void GridRowLayoutAlgorithm::MeasureSelf(FrameNode* frameNode, float childHeight)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(frameNode->GetLayoutProperty());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    auto padding = layoutProperty->CreatePaddingAndBorder();

    auto idealSize = CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    idealSize.SetHeight(childHeight + padding.Height());
    idealSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    frameNode->GetGeometryNode()->SetFrameSize(idealSize.ConvertToSizeT());
}

/* Measure each child and return total height */
float GridRowLayoutAlgorithm::MeasureChildren(FrameNode* frameNode, double columnUnitWidth,
    double childHeightLimit, std::pair<double, double>& gutter, GridSizeType sizeType, int32_t columnNum)
{
    auto children = frameNode->GetAllFrameNodeChildren();
    children.sort([sizeType](const RefPtr<FrameNode>& left, const RefPtr<FrameNode>& right) {
        if (left->GetTag() != V2::GRID_COL_ETS_TAG || right->GetTag() != V2::GRID_COL_ETS_TAG) {
            return false;
        }
        auto leftCol = AceType::DynamicCast<GridColLayoutProperty>(left->GetLayoutProperty());
        auto rightCol = AceType::DynamicCast<GridColLayoutProperty>(right->GetLayoutProperty());
        if (leftCol && rightCol) {
            return (leftCol->GetOrder(sizeType) < rightCol->GetOrder(sizeType));
        }
        return false;
    });

    int32_t offset = 0;
    float totalHeight = 0.0;
    float currentRowHeight = 0.0;
    /* GridRow's child must be a GridCol */
    for (auto& child : children) {
        if (child->GetTag() != V2::GRID_COL_ETS_TAG) {
            LOGE("Not a grid_col component");
            continue;
        }
        auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
        if (!gridCol) {
            continue;
        }
        gridCol->UpdateSizeType(sizeType);

        /* Measure child */
        auto span = std::min(gridCol->GetSpan(sizeType), columnNum);

        /* Calculate line break */
        NewLineOffset newLineOffset;
        CalculateOffsetOfNewline(gridCol, span, columnNum - offset, columnNum, sizeType, newLineOffset);

        /* update total height */
        if (newLineOffset.newLineCount > 0) {
            totalHeight += (currentRowHeight * newLineOffset.newLineCount + gutter.second);
        }

        OptionalSize<float> ideaSize;
        ideaSize.SetWidth(columnUnitWidth * span + (span - 1) * gutter.first);
        LayoutConstraintF parentConstraint = frameNode->GetLayoutProperty()->CreateChildConstraint();
        parentConstraint.UpdateSelfMarginSizeWithCheck(ideaSize);
        // the max size need to minus the already allocated height.
        parentConstraint.maxSize.MinusHeight(totalHeight);
        child->Measure(parentConstraint);

        if (newLineOffset.newLineCount > 0) {
            gridColChildrenRows_.emplace_back(gridColChildrenOfOneRow_);
            CalcCrossAxisAlignment(frameNode, *gridColChildrenRows_.rbegin(), currentRowHeight);
            gridColChildrenOfOneRow_.clear();
            currentRowHeight = child->GetGeometryNode()->GetFrameSize().Height();
        } else {
            newLineOffset.offset += offset;
            auto childHeight = child->GetGeometryNode()->GetMarginFrameSize().Height();
            currentRowHeight = std::max(currentRowHeight, childHeight);
        }

        offset = newLineOffset.offset + newLineOffset.span;
        newLineOffset.offsetY = totalHeight;
        LOGD("GridRowLayoutAlgorithm::MeasureChildren(), height=%{public}f, span=%{public}d, newline=%{public}d, "
             "offsetY=%{public}f, offset=%{public}d",
            currentRowHeight, newLineOffset.span, newLineOffset.newLineCount, newLineOffset.offsetY,
            newLineOffset.offset);

        gridColChildrenOfOneRow_.emplace_back(std::make_pair(child, newLineOffset));
    }
    if (!gridColChildrenOfOneRow_.empty()) {
        gridColChildrenRows_.emplace_back(gridColChildrenOfOneRow_);
        CalcCrossAxisAlignment(frameNode, *gridColChildrenRows_.rbegin(), currentRowHeight);
        gridColChildrenOfOneRow_.clear();
    }
    return (totalHeight + currentRowHeight);
}

void GridRowLayoutAlgorithm::CalcCrossAxisAlignment(FrameNode* frameNode,
    std::list<std::pair<RefPtr<FrameNode>, NewLineOffset>>& row, float currentRowHeight)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    for (auto& child : row) {
        auto childNode = child.first;
        auto childSize = childNode->GetGeometryNode()->GetFrameSize();
        auto childLayoutProperty = childNode->GetLayoutProperty();
        const auto& childMargin = childNode->GetGeometryNode()->GetMargin();
        if (!childLayoutProperty) {
            LOGD("Child %{public}d, tag %{public}s, has no layout property, continue", childNode->GetId(),
                childNode->GetTag().c_str());
            continue;
        }
        auto alignSelf = FlexAlign::FLEX_START;
        auto gridRowAlignItem = layoutProperty->GetAlignItemsValue(FlexAlign::FLEX_START);
        if (childLayoutProperty->GetFlexItemProperty()) {
            alignSelf = childLayoutProperty->GetFlexItemProperty()->GetAlignSelf().value_or(gridRowAlignItem);
            if (alignSelf == FlexAlign::AUTO) {
                alignSelf = gridRowAlignItem;
            }

        } else {
            alignSelf = gridRowAlignItem;
        }
        if (alignSelf == FlexAlign::STRETCH) {
            // this child has height close to row height, not necessary to stretch
            if (NearEqual(currentRowHeight, childSize.Height())) {
                continue;
            }
            LayoutConstraintF parentConstraint = frameNode->GetLayoutProperty()->CreateChildConstraint();
            parentConstraint.selfIdealSize = OptionalSizeF(childSize.Width(), currentRowHeight);
            childNode->Measure(parentConstraint);
        } else {
            float extraOffset = 0.0f;
            if (alignSelf == FlexAlign::CENTER) {
                extraOffset = (currentRowHeight - childSize.Height() - childMargin->top.value_or(0) -
                                  childMargin->bottom.value_or(0.0f)) *
                              0.5f;
            } else if (alignSelf == FlexAlign::FLEX_END) {
                extraOffset = currentRowHeight - childSize.Height() - childMargin->bottom.value_or(0.0f) -
                              childMargin->top.value_or(0.0f);
            }
            if (!NearZero(extraOffset)) {
                child.second.offsetY += extraOffset;
            }
        }
    }
}

void GridRowLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    gridColChildrenRows_.clear();
    gridColChildrenOfOneRow_.clear();
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto maxSize = CreateIdealSize(layoutProperty->GetLayoutConstraint().value_or(LayoutConstraintF()),
        Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    CreateChildrenConstraint(maxSize, layoutProperty->CreatePaddingAndBorder());
    auto context = NG::PipelineContext::GetCurrentContext();
    auto sizeType = GridContainerUtils::ProcessGridSizeType(
        layoutProperty->GetBreakPointsValue(), Size(maxSize.Width(), maxSize.Height()));
    if (layoutProperty->GetSizeTypeValue(V2::GridSizeType::UNDEFINED) != sizeType) {
        auto sizeTypeString = ConvertSizeTypeToString(sizeType);
        frameNode->GetEventHub<GridRowEventHub>()->FireChangeEvent(sizeTypeString);
        layoutProperty->UpdateSizeType(sizeType);
    }
    auto gutter = GridContainerUtils::ProcessGutter(sizeType, layoutProperty->GetGutterValue());
    gutterInDouble_ =
        std::make_pair<double, double>(context->NormalizeToPx(gutter.first), context->NormalizeToPx(gutter.second));
    int32_t columnNum = GridContainerUtils::ProcessColumn(sizeType, layoutProperty->GetColumnsValue());
    columnUnitWidth_ = GridContainerUtils::ProcessColumnWidth(gutterInDouble_, columnNum, maxSize.Width());
    float childrenHeight =
        MeasureChildren(frameNode, columnUnitWidth_, maxSize.Height(), gutterInDouble_, sizeType, columnNum);
    LOGD("GridRowLayoutAlgorithm::Measure() columnNum=%{public}d, columnUnitWidth_=%{public}f, "
         "childrenHeight=%{public}f, sizeType=%{public}d",
        columnNum, columnUnitWidth_, childrenHeight, static_cast<int>(sizeType));

    MeasureSelf(frameNode, childrenHeight);
}

void GridRowLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    if (gridColChildrenRows_.empty()) {
        return;
    }

    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(frameNode->GetLayoutProperty());
    auto directionVal = layoutProperty->GetDirectionValue();
    auto width = frameNode->GetGeometryNode()->GetFrameSize().Width();

    auto padding = layoutProperty->CreatePaddingAndBorder();
    OffsetF paddingOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };

    for (auto&& row : gridColChildrenRows_) {
        for (auto&& pair : row) {
            auto child = pair.first;
            auto& newLineOffset = pair.second;

            float offsetWidth = 0.0;
            if (directionVal == V2::GridRowDirection::RowReverse) {
                offsetWidth = ((newLineOffset.span + newLineOffset.offset) * columnUnitWidth_ +
                               ((newLineOffset.span + newLineOffset.offset) - 1) * gutterInDouble_.first);
                offsetWidth = width - offsetWidth;
            } else { // V2::GridRowDirection::Row
                offsetWidth = newLineOffset.offset * columnUnitWidth_ + newLineOffset.offset * gutterInDouble_.first;
            }

            OffsetF offset(offsetWidth, newLineOffset.offsetY);
            child->GetGeometryNode()->SetMarginFrameOffset(offset + paddingOffset);
            child->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG
