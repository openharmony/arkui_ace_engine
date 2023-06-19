
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

#include "base/utils/utils.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_property.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_property.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

using OHOS::Ace::V2::GridContainerUtils;
using OHOS::Ace::V2::GridSizeType;
using OHOS::Ace::V2::Gutter;
using LayoutPair = std::pair<RefPtr<LayoutWrapper>, NewLineOffset>;

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

void GridRowLayoutAlgorithm::MeasureSelf(LayoutWrapper* layoutWrapper, float childHeight)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    auto padding = layoutProperty->CreatePaddingAndBorder();

    auto idealSize = CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    idealSize.SetHeight(childHeight + padding.Height());
    idealSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.ConvertToSizeT());
}

/* Measure each child and return total height */
float GridRowLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper, double columnUnitWidth,
    double childHeightLimit, std::pair<double, double>& gutter, GridSizeType sizeType, int32_t columnNum)
{
    auto children = layoutWrapper->GetAllChildrenWithBuild();
    children.sort([sizeType](const RefPtr<LayoutWrapper>& left, const RefPtr<LayoutWrapper>& right) {
        if (left->GetHostTag() != V2::GRID_COL_ETS_TAG || right->GetHostTag() != V2::GRID_COL_ETS_TAG) {
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
        if (child->GetHostTag() != V2::GRID_COL_ETS_TAG) {
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
        LayoutConstraintF parentConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        parentConstraint.UpdateSelfMarginSizeWithCheck(ideaSize);
        child->Measure(parentConstraint);

        if (newLineOffset.newLineCount > 0) {
            gridColChildrenRows_.emplace_back(gridColChildrenOfOneRow_);
            CalcCrossAxisAlignment(layoutWrapper, *gridColChildrenRows_.rbegin(), currentRowHeight);
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
        CalcCrossAxisAlignment(layoutWrapper, *gridColChildrenRows_.rbegin(), currentRowHeight);
        gridColChildrenOfOneRow_.clear();
    }
    return (totalHeight + currentRowHeight);
}

void GridRowLayoutAlgorithm::CalcCrossAxisAlignment(LayoutWrapper* layoutWrapper,
    std::list<std::pair<RefPtr<LayoutWrapper>, NewLineOffset>>& row, float currentRowHeight)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    for (auto& child : row) {
        auto childNode = child.first->GetHostNode();
        auto childSize = child.first->GetGeometryNode()->GetFrameSize();
        const auto& childMargin = child.first->GetGeometryNode()->GetMargin();
        auto childLayoutProperty = child.first->GetLayoutProperty();
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
            LayoutConstraintF parentConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
            parentConstraint.selfIdealSize = OptionalSizeF(childSize.Width(), currentRowHeight);
            child.first->Measure(parentConstraint);
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

void GridRowLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    gridColChildrenRows_.clear();
    gridColChildrenOfOneRow_.clear();
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    const auto& hostLayoutProperty = layoutWrapper->GetHostNode()->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto maxSize = CreateIdealSize(layoutProperty->GetLayoutConstraint().value_or(LayoutConstraintF()),
        Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    CreateChildrenConstraint(maxSize, layoutProperty->CreatePaddingAndBorder());
    auto context = NG::PipelineContext::GetCurrentContext();
    auto sizeType = GridContainerUtils::ProcessGridSizeType(
        layoutProperty->GetBreakPointsValue(), Size(maxSize.Width(), maxSize.Height()));
    if (hostLayoutProperty->GetSizeTypeValue(V2::GridSizeType::UNDEFINED) != sizeType) {
        auto sizeTypeString = ConvertSizeTypeToString(sizeType);
        layoutWrapper->GetHostNode()->GetEventHub<GridRowEventHub>()->FireChangeEvent(sizeTypeString);
        hostLayoutProperty->UpdateSizeType(sizeType);
    }
    auto gutter = GridContainerUtils::ProcessGutter(sizeType, layoutProperty->GetGutterValue());
    gutterInDouble_ =
        std::make_pair<double, double>(context->NormalizeToPx(gutter.first), context->NormalizeToPx(gutter.second));
    int32_t columnNum = GridContainerUtils::ProcessColumn(sizeType, layoutProperty->GetColumnsValue());
    columnUnitWidth_ = GridContainerUtils::ProcessColumnWidth(gutterInDouble_, columnNum, maxSize.Width());
    float childrenHeight =
        MeasureChildren(layoutWrapper, columnUnitWidth_, maxSize.Height(), gutterInDouble_, sizeType, columnNum);
    LOGD("GridRowLayoutAlgorithm::Measure() columnNum=%{public}d, columnUnitWidth_=%{public}f, "
         "childrenHeight=%{public}f, sizeType=%{public}d",
        columnNum, columnUnitWidth_, childrenHeight, static_cast<int>(sizeType));

    MeasureSelf(layoutWrapper, childrenHeight);
}

void GridRowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (gridColChildrenRows_.empty()) {
        return;
    }

    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto directionVal = layoutProperty->GetDirectionValue();
    auto width = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();

    auto padding = layoutProperty->CreatePaddingAndBorder();
    OffsetF paddingOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };

    for (auto&& row : gridColChildrenRows_) {
        for (auto&& pair : row) {
            auto childLayoutWrapper = pair.first;
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
            childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(offset + paddingOffset);
            childLayoutWrapper->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG
