
/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "grid_row_event_hub.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace OHOS::Ace::NG {

using OHOS::Ace::V2::GridContainerUtils;
using OHOS::Ace::V2::GridSizeType;
using OHOS::Ace::V2::Gutter;
using LayoutPair = std::pair<RefPtr<LayoutWrapper>, NewLineOffset>;

namespace {
constexpr int32_t DEFAULT_COLUMN_NUMBER = 12;

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

void GridRowLayoutAlgorithm::MeasureSelf(LayoutWrapper* layoutWrapper, float childHeight, float selfHeight)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    auto padding = layoutProperty->CreatePaddingAndBorder();

    auto idealSize = CreateIdealSize(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    if (layoutConstraint->selfIdealSize.Height() &&
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        idealSize.SetHeight(selfHeight + padding.Height());
    } else {
        idealSize.SetHeight(childHeight + padding.Height());
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        idealSize.Constrain(layoutConstraint->minSize, layoutConstraint->maxSize);
    } else {
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(idealSize,
            layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
            layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
        idealSize.SetWidth(finalSize.Width());
        idealSize.SetHeight(finalSize.Height());
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.ConvertToSizeT());
}

/* Measure each child and return total height */
float GridRowLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper, double columnUnitWidth,
    double childHeightLimit, std::pair<double, double>& gutter, GridSizeType sizeType, int32_t columnNum)
{
    std::list<RefPtr<LayoutWrapper>> children = layoutWrapper->GetAllChildrenWithBuild();
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
        // the max size need to minus the already allocated height.
        parentConstraint.maxSize.MinusHeight(totalHeight);
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

        gridColChildrenOfOneRow_.emplace_back(std::make_pair(child, newLineOffset));
    }
    if (!gridColChildrenOfOneRow_.empty()) {
        gridColChildrenRows_.emplace_back(gridColChildrenOfOneRow_);
        CalcCrossAxisAlignment(layoutWrapper, *gridColChildrenRows_.rbegin(), currentRowHeight);
        gridColChildrenOfOneRow_.clear();
    }
    return (totalHeight + currentRowHeight);
}

FlexAlign GridRowLayoutAlgorithm::GetChildAlignment(LayoutWrapper* gridRow,
    const RefPtr<LayoutProperty>& childLayoutProperty)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(gridRow->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, FlexAlign::FLEX_START);
    CHECK_NULL_RETURN(childLayoutProperty, FlexAlign::FLEX_START);
    auto alignSelf = FlexAlign::FLEX_START;
    auto gridRowAlignItem = layoutProperty->GetAlignItemsValue(FlexAlign::FLEX_START);
    if (!childLayoutProperty->GetFlexItemProperty()) {
        return gridRowAlignItem;
    }
    alignSelf = childLayoutProperty->GetFlexItemProperty()->GetAlignSelf().value_or(gridRowAlignItem);
    return alignSelf == FlexAlign::AUTO ? gridRowAlignItem : alignSelf;
}

float GridRowLayoutAlgorithm::CalcCrossAxisOffset(LayoutWrapper* gridRow, RefPtr<LayoutWrapper> &child,
    FlexAlign alignSelf, float currentRowHeight)
{
    CHECK_NULL_RETURN(child, 0.0f);
    CHECK_NULL_RETURN(gridRow, 0.0f);
    auto childSize = child->GetGeometryNode()->GetFrameSize();
    const auto& childMargin = child->GetGeometryNode()->GetMargin();
    switch (alignSelf) {
        case FlexAlign::STRETCH:
            if (!NearEqual(currentRowHeight, childSize.Height())) {
                auto parentConstraint = gridRow->GetLayoutProperty()->CreateChildConstraint();
                parentConstraint.selfIdealSize = OptionalSizeF(childSize.Width(), currentRowHeight);
                child->Measure(parentConstraint);
            }
            return 0.0f;
        case FlexAlign::CENTER:
            return (currentRowHeight - childSize.Height() - childMargin->top.value_or(0) -
                childMargin->bottom.value_or(0.0f)) * 0.5f;
        case FlexAlign::FLEX_END:
            return currentRowHeight - childSize.Height() - childMargin->bottom.value_or(0.0f) -
                childMargin->top.value_or(0.0f);
        default:
            return 0.0f;
    }
}

void GridRowLayoutAlgorithm::CalcCrossAxisAlignment(LayoutWrapper* layoutWrapper,
    std::list<std::pair<RefPtr<LayoutWrapper>, NewLineOffset>>& row, float currentRowHeight)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    for (auto& child : row) {
        auto childNode = child.first->GetHostNode();
        auto childLayoutProperty = child.first->GetLayoutProperty();
        if (!childLayoutProperty) {
            continue;
        }
        auto alignSelf = GetChildAlignment(layoutWrapper, childLayoutProperty);
        auto extraOffset = CalcCrossAxisOffset(layoutWrapper, child.first, alignSelf, currentRowHeight);
        if (!NearZero(extraOffset)) {
            child.second.offsetY += extraOffset;
        }
    }
}

void GridRowLayoutAlgorithm::OnBreakPointChange(LayoutWrapper* layoutWrapper, const V2::GridSizeType& sizeType)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto task = [weak = WeakClaim(RawPtr(frameNode)), sizeType]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        auto sizeTypeString = GridRowLayoutAlgorithm::ConvertSizeTypeToString(sizeType);
        auto hostLayoutProperty = host->GetLayoutProperty<GridRowLayoutProperty>();
        CHECK_NULL_VOID(hostLayoutProperty);
        auto hostEventHub = host->GetOrCreateEventHub<GridRowEventHub>();
        CHECK_NULL_VOID(hostEventHub);
        hostLayoutProperty->UpdateSizeType(sizeType);
        TAG_LOGD(AceLogTag::ACE_GRIDROW,
            "[%{public}s-%{public}d] breakpoint has changed to a new sizeType:%{public}s and breakpoint reference "
            "%{public}d",
            host->GetTag().c_str(), host->GetId(), sizeTypeString.c_str(),
            hostLayoutProperty->GetBreakPointsValue().reference);
        hostEventHub->FireChangeEvent(sizeTypeString);
    };
    context->AddAfterLayoutTask(task);
}

bool GridRowLayoutAlgorithm::GetSizeTypeAndMaxSize(LayoutWrapper* layoutWrapper,
    SizeF &maxSize, V2::GridSizeType& sizeType)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    const auto& hostLayoutProperty = layoutWrapper->GetHostNode()->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    maxSize = CreateIdealSize(layoutProperty->GetLayoutConstraint().value_or(LayoutConstraintF()),
        Axis::HORIZONTAL, MeasureType::MATCH_PARENT, true);
    CreateChildrenConstraint(maxSize, layoutProperty->CreatePaddingAndBorder());
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, false);
    auto mode = windowManager->GetWindowMode();
    sizeType = GridContainerUtils::ProcessGridSizeType(layoutProperty->GetBreakPointsValue(),
        Size(maxSize.Width(), maxSize.Height()), mode, PipelineBase::GetCurrentContextSafelyWithCheck());
    return true;
}

void GridRowLayoutAlgorithm::ParseGridRowParams(LayoutWrapper *layoutWrapper, const V2::GridSizeType &sizeType,
    const SizeF &maxSize)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto gutter = GridContainerUtils::ProcessGutter(sizeType, layoutProperty->GetGutterValue());
    gutterInDouble_ =
        std::make_pair<double, double>(context->NormalizeToPx(gutter.first), context->NormalizeToPx(gutter.second));
    columnNum_ = GridContainerUtils::ProcessColumn(sizeType, layoutProperty->GetColumnsValue());
    if (columnNum_ <= 0) {
        columnNum_ = DEFAULT_COLUMN_NUMBER;
    }
    columnUnitWidth_ = GridContainerUtils::ProcessColumnWidth(gutterInDouble_, columnNum_, maxSize.Width());
}

void GridRowLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    gridColChildrenRows_.clear();
    gridColChildrenOfOneRow_.clear();
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    const auto& hostLayoutProperty = layoutWrapper->GetHostNode()->GetLayoutProperty<GridRowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    SizeF maxSize;
    V2::GridSizeType sizeType;
    if (!GetSizeTypeAndMaxSize(layoutWrapper, maxSize, sizeType)) {
        return;
    }
    if (hostLayoutProperty->GetSizeTypeValue(V2::GridSizeType::UNDEFINED) != sizeType) {
        OnBreakPointChange(layoutWrapper, sizeType);
    }
    ParseGridRowParams(layoutWrapper, sizeType, maxSize);
    float childrenHeight =
        MeasureChildren(layoutWrapper, columnUnitWidth_, maxSize.Height(), gutterInDouble_, sizeType, columnNum_);
    float selfHeight = maxSize.Height();
    MeasureSelf(layoutWrapper, childrenHeight, selfHeight);
}

bool GridRowLayoutAlgorithm::IsRightToLeft(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto directionVal = layoutProperty->GetDirectionValue();
    auto textDirection = layoutProperty->GetLayoutDirection();
    if (textDirection == TextDirection::AUTO) {
        textDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    return ((directionVal == V2::GridRowDirection::RowReverse) && (textDirection == TextDirection::LTR)) ||
                ((directionVal == V2::GridRowDirection::Row) && (textDirection == TextDirection::RTL));
}

void GridRowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (gridColChildrenRows_.empty()) {
        return;
    }
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto width = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    OffsetF paddingOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };

    for (auto&& row : gridColChildrenRows_) {
        for (auto&& pair : row) {
            auto childLayoutWrapper = pair.first;
            auto& newLineOffset = pair.second;

            float offsetWidth = 0.0;
            if (IsRightToLeft(layoutWrapper)) {
                offsetWidth = ((newLineOffset.span + newLineOffset.offset) * columnUnitWidth_ +
                               ((newLineOffset.span + newLineOffset.offset) - 1) * gutterInDouble_.first);
                offsetWidth = width - offsetWidth;
                paddingOffset = { -padding.right.value_or(0.0f), padding.top.value_or(0.0f) };
            } else {
                offsetWidth = newLineOffset.offset * columnUnitWidth_ + newLineOffset.offset * gutterInDouble_.first;
            }
            OffsetF offset(offsetWidth, newLineOffset.offsetY);
            childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(offset + paddingOffset);
            childLayoutWrapper->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG
