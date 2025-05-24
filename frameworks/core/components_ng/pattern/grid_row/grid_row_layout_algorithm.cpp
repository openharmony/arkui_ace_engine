
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

bool IsMatchParent(const RefPtr<LayoutProperty>& layoutProp)
{
    CHECK_NULL_RETURN(layoutProp, false);
    auto layoutPolicy = layoutProp->GetLayoutPolicyProperty();
    CHECK_NULL_RETURN(layoutPolicy, false);
    auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_;
    return heightLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) == LayoutCalPolicy::MATCH_PARENT;
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
    auto layoutPolicy = layoutWrapper->GetLayoutProperty()->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    if (widthLayoutPolicy != LayoutCalPolicy::NO_MATCH || heightLayoutPolicy != LayoutCalPolicy::NO_MATCH) {
        auto policySize = MeasureSelfByLayoutPolicy(layoutWrapper, childHeight + padding.Height(),
            widthLayoutPolicy, heightLayoutPolicy);
        idealSize.UpdateSizeWithCheck(policySize);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize.ConvertToSizeT());
    }
}

/* Measure each child and return total height */
float GridRowLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper, double columnUnitWidth,
    double childHeightLimit, std::pair<double, double>& gutter, GridSizeType sizeType, int32_t columnNum)
{
    std::list<RefPtr<LayoutWrapper>> children = layoutWrapper->GetAllChildrenWithBuild();
    SortByGridColOrder(children, sizeType);
    int32_t offset = 0;
    float totalHeight = 0.0;
    float currentRowHeight = 0.0;
    bool hasMatchParent = std::any_of(children.begin(), children.end(), [](const RefPtr<LayoutWrapper>& gridcol) {
        return IsMatchParent(gridcol->GetLayoutProperty());
    });
    if (hasMatchParent) {
        return MeasureNonMatchParentChildren(layoutWrapper, sizeType, children);
    }
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
    gridColChildrenRowsInfo_.clear();
    layoutPolicyChildren_.clear();
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
    MeasureAdaptiveLayoutChildren(layoutWrapper, sizeType);
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

void GridRowLayoutAlgorithm::LayoutChildrenRow(ChildrenRow& row, float width, const OffsetF &paddingOffset,
    bool isRightToLeft, float offsetYAdjust)
{
    for (auto&& pair : row) {
        auto childLayoutWrapper = pair.first;
        auto& newLineOffset = pair.second;
        float offsetWidth = 0.0;
        if (isRightToLeft) {
            offsetWidth = ((newLineOffset.span + newLineOffset.offset) * columnUnitWidth_ +
                            ((newLineOffset.span + newLineOffset.offset) - 1) * gutterInDouble_.first);
            offsetWidth = width - offsetWidth;
        } else {
            offsetWidth = newLineOffset.offset * columnUnitWidth_ + newLineOffset.offset * gutterInDouble_.first;
        }
        OffsetF offset(offsetWidth, newLineOffset.offsetY + offsetYAdjust);
        childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(offset + paddingOffset);
        UpdateChildPositionWidthIgnoreLayoutSafeArea(isRightToLeft, childLayoutWrapper, offset + paddingOffset);
        childLayoutWrapper->Layout();
    }
}

OffsetF GridRowLayoutAlgorithm::GetPaddingOffset(LayoutWrapper* layoutWrapper, bool isRightToLeft)
{
    CHECK_NULL_RETURN(layoutWrapper, {});
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, {});
    auto padding = layoutProperty->CreatePaddingAndBorder();
    if (isRightToLeft) {
        return { -padding.right.value_or(0.0f), padding.top.value_or(0.0f) };
    }
    return { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };
}

void GridRowLayoutAlgorithm::LayoutWithMatchParentInfo(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto realSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToNonNegativeSize(padding, realSize);
    auto matchParentHeight = realSize.Height();
    auto width = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    bool isRightToLeft = IsRightToLeft(layoutWrapper);
    auto paddingOffset = GetPaddingOffset(layoutWrapper, isRightToLeft);
    auto rowIter = gridColChildrenRows_.begin();
    auto rowInfoIter = gridColChildrenRowsInfo_.begin();
    float offsetYAdjust = 0;
    float lastLineOffsetAdjust = 0;
    while (rowIter != gridColChildrenRows_.end() && rowInfoIter != gridColChildrenRowsInfo_.end()) {
        float rowHeightAdjust = rowInfoIter->maxHeight;
        if (rowInfoIter->isMatchParent) {
            rowHeightAdjust = std::max(rowInfoIter->maxHeight, matchParentHeight);
            CalcCrossAxisAlignment(layoutWrapper, *rowIter, rowHeightAdjust);
        }
        offsetYAdjust += lastLineOffsetAdjust * rowInfoIter->newLineCount;
        LayoutChildrenRow(*rowIter, width, paddingOffset, isRightToLeft, offsetYAdjust);
        lastLineOffsetAdjust = rowInfoIter->isMatchParent ? (rowHeightAdjust - rowInfoIter->maxHeight) : 0;
        rowIter++;
        rowInfoIter++;
    }
}

void GridRowLayoutAlgorithm::InitChildrenRowInLayout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(host->GetIgnoreLayoutProcess());
    std::list<RefPtr<LayoutWrapper>> children = layoutWrapper->GetAllChildrenWithBuild();
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    const auto& hostLayoutProperty = layoutWrapper->GetHostNode()->GetLayoutProperty<GridRowLayoutProperty>();
    int32_t offset = 0;
    float totalHeight = 0.0;
    float currentRowHeight = 0.0;
    SizeF maxSize;
    V2::GridSizeType sizeType;
    if (!GetSizeTypeAndMaxSize(layoutWrapper, maxSize, sizeType)) {
        return;
    }
    ParseGridRowParams(layoutWrapper, sizeType, maxSize);
    SortByGridColOrder(children, sizeType);
    for (auto& child : children) {
        if (child->GetHostTag() != V2::GRID_COL_ETS_TAG) {
            continue;
        }
        auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
        if (!gridCol) {
            continue;
        }
        gridCol->UpdateSizeType(sizeType);
        int32_t span = 0;
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
            span = std::min(gridCol->GetSpan(sizeType), columnNum_);
        } else {
            span = gridCol->GetSpan(sizeType) >= 0 ? std::min(gridCol->GetSpan(sizeType), columnNum_) : columnNum_;
        }
        NewLineOffset newLineOffset;
        CalculateOffsetOfNewline(gridCol, span, columnNum_ - offset, columnNum_, sizeType, newLineOffset);
        if (newLineOffset.newLineCount > 0) {
            totalHeight += (currentRowHeight * newLineOffset.newLineCount + gutterInDouble_.second);
        }
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
}

void GridRowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    if (host && !host->GetIgnoreLayoutProcess()) {
        if (GetNeedPostponeForIgnore()) {
            return;
        }
    }
    InitChildrenRowInLayout(layoutWrapper);
    if (gridColChildrenRows_.empty()) {
        return;
    }
    if (!layoutPolicyChildren_.empty()) {
        LayoutWithMatchParentInfo(layoutWrapper);
        return;
    }
    const auto& layoutProperty = DynamicCast<GridRowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto width = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    OffsetF paddingOffset = { padding.left.value_or(0.0f), padding.top.value_or(0.0f) };

    bool firstLine = true;
    float firstLineOffset = 0.0f;
    for (auto&& row : gridColChildrenRows_) {
        for (auto&& pair : row) {
            auto childLayoutWrapper = pair.first;
            auto& newLineOffset = pair.second;
            if (!firstLine) {
                newLineOffset.offsetY -= firstLineOffset;
            }
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
            auto ignoreMatchOffset = UpdateChildPositionWidthIgnoreLayoutSafeArea(
                IsRightToLeft(layoutWrapper), childLayoutWrapper, offset + paddingOffset);
            if (firstLine) {
                auto lineOffset =
                    GreatNotEqual(childLayoutWrapper->GetGeometryNode()->GetFrameSize().Height() - ignoreMatchOffset,
                        layoutWrapper->GetGeometryNode()->GetFrameSize().Height())
                        ? 0.0f
                        : ignoreMatchOffset;
                firstLineOffset = std::max(firstLineOffset, lineOffset);
            }
            childLayoutWrapper->Layout();
        }
        firstLine = false;
    }
}

float GridRowLayoutAlgorithm::UpdateChildPositionWidthIgnoreLayoutSafeArea(
    bool isRtl, const RefPtr<LayoutWrapper>& childLayoutWrapper, const OffsetF& originOffset)
{
    auto childNode = childLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(childNode, 0.0f);
    CHECK_NULL_RETURN(childNode->GetLayoutProperty(), 0.0f);
    CHECK_NULL_RETURN(childNode->GetLayoutProperty()->IsIgnoreOptsValid(), 0.0f);
    IgnoreLayoutSafeAreaOpts& opts = *(childNode->GetLayoutProperty()->GetIgnoreLayoutSafeAreaOpts());
    auto sae = childNode->GetAccumulatedSafeAreaExpand(false, opts);
    auto offsetX = isRtl ? -sae.right.value_or(0.0f) : sae.left.value_or(0.0f);
    auto offsetY = sae.top.value_or(0.0f);
    OffsetF saeTrans = originOffset - OffsetF(offsetX, offsetY);
    childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(saeTrans);
    return childNode->GetLayoutProperty()->IsExpandConstraintNeeded() ? offsetY : 0.0f;
}

OptionalSizeF GridRowLayoutAlgorithm::MeasureSelfByLayoutPolicy(LayoutWrapper* layoutWrapper, float childHeight,
    LayoutCalPolicy widthLayoutPolicy, LayoutCalPolicy heightLayoutPolicy)
{
    OptionalSizeF realSize;
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    auto matchParentSize = ConstrainIdealSizeByLayoutPolicy(layoutConstraint.value(),
        widthLayoutPolicy, heightLayoutPolicy, Axis::HORIZONTAL).ConvertToSizeT();
    realSize.UpdateSizeWithCheck(matchParentSize);
    if (heightLayoutPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        return realSize;
    }
    auto fixIdealSize = UpdateOptionSizeByCalcLayoutConstraint({std::nullopt, childHeight},
        layoutWrapper->GetLayoutProperty()->GetCalcLayoutConstraint(),
        layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->percentReference);
    realSize.SetHeight(fixIdealSize.Height());
    return realSize;
}

void GridRowLayoutAlgorithm::MeasureAdaptiveLayoutChildren(LayoutWrapper* layoutWrapper, V2::GridSizeType sizeType)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto realSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    MinusPaddingToNonNegativeSize(padding, realSize);
    auto host = layoutWrapper->GetHostNode();
    IgnoreLayoutSafeAreaBundle bundle;
    for (const auto& child : layoutPolicyChildren_) {
        auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
        if (!gridCol) {
            continue;
        }
        auto span = gridCol->GetSpan(sizeType) >= 0 ? std::min(gridCol->GetSpan(sizeType), columnNum_) : columnNum_;
        OptionalSize<float> ideaSize;
        ideaSize.SetWidth(columnUnitWidth_ * span + (span - 1) * gutterInDouble_.first);
        LayoutConstraintF parentConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        parentConstraint.UpdateSelfMarginSizeWithCheck(ideaSize);
        parentConstraint.parentIdealSize.SetSize(realSize);
        auto childNode = child->GetHostNode();
        if (childNode && childNode->GetLayoutProperty() && childNode->GetLayoutProperty()->IsExpandConstraintNeeded()) {
            bundle.first.emplace_back(childNode);
            child->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
            SetNeedPostponeForIgnore();
            continue;
        }
        child->Measure(parentConstraint);
    }
    if (host && host->GetContext() && GetNeedPostponeForIgnore()) {
        auto context = host->GetContext();
        bundle.second = host;
        context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
    }
}

void GridRowLayoutAlgorithm::SortByGridColOrder(std::list<RefPtr<LayoutWrapper>>& children, GridSizeType sizeType)
{
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
}

void GridRowLayoutAlgorithm::DisableWidthLayoutPolicy(const RefPtr<LayoutWrapper>& child)
{
    CHECK_NULL_VOID(child);
    auto childLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy);
    if (layoutPolicy.value().widthLayoutPolicy_.has_value()) {
        childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    }
}

void GridRowLayoutAlgorithm::InsertIntoGridRowTable(const RefPtr<LayoutWrapper> &child,
    GridSizeType sizeType, int32_t &currentPosition, NewLineOffset &newLineOffset)
{
    auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
    CHECK_NULL_VOID(gridCol);
    gridCol->UpdateSizeType(sizeType);
    auto span = gridCol->GetSpan(sizeType) >= 0 ? std::min(gridCol->GetSpan(sizeType), columnNum_) : columnNum_;
    CalculateOffsetOfNewline(gridCol, span, columnNum_ - currentPosition, columnNum_, sizeType, newLineOffset);
    if (newLineOffset.newLineCount > 0) {
        gridColChildrenRows_.emplace_back(gridColChildrenOfOneRow_);
        gridColChildrenOfOneRow_.clear();
    } else {
        newLineOffset.offset += currentPosition;
    }
    currentPosition = newLineOffset.offset + newLineOffset.span;
    gridColChildrenOfOneRow_.emplace_back(std::make_pair(child, newLineOffset));
}

float GridRowLayoutAlgorithm::MeasureChild(LayoutWrapper* gridRow, RefPtr<LayoutWrapper> &child,
    GridSizeType sizeType, float totalHeight, bool isMatchParent)
{
    CHECK_NULL_RETURN(gridRow, 0.0);
    CHECK_NULL_RETURN(child, 0.0);
    auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
    CHECK_NULL_RETURN(gridCol, 0);
    if (isMatchParent) {
        layoutPolicyChildren_.emplace_back(child);
        return 0.0f;
    }
    auto span = gridCol->GetSpan(sizeType) >= 0 ? std::min(gridCol->GetSpan(sizeType), columnNum_) : columnNum_;
    OptionalSize<float> ideaSize;
    ideaSize.SetWidth(columnUnitWidth_ * span + (span - 1) * gutterInDouble_.first);
    LayoutConstraintF parentConstraint = gridRow->GetLayoutProperty()->CreateChildConstraint();
    parentConstraint.UpdateSelfMarginSizeWithCheck(ideaSize);
    // the max size need to minus the already allocated height.
    parentConstraint.maxSize.MinusHeight(totalHeight);
    child->Measure(parentConstraint);
    return child->GetGeometryNode()->GetMarginFrameSize().Height();
}

float GridRowLayoutAlgorithm::MeasureNonMatchParentChildren(LayoutWrapper* layoutWrapper, GridSizeType sizeType,
    std::list<RefPtr<LayoutWrapper>>& children)
{
    int32_t currentPosition = 0;
    float totalHeight = 0.0;
    float currentRowHeight = 0.0;
    bool isLastLineHasMatchParent = false;
    int32_t currentNewLineCount = 0;
    for (auto& child : children) {
        if (child->GetHostTag() != V2::GRID_COL_ETS_TAG) {
            continue;
        }
        DisableWidthLayoutPolicy(child);
        auto gridCol = AceType::DynamicCast<GridColLayoutProperty>(child->GetLayoutProperty());
        if (!gridCol) {
            continue;
        }
        bool isMatchParent = IsMatchParent(gridCol);
        NewLineOffset newLineOffset;
        InsertIntoGridRowTable(child, sizeType, currentPosition, newLineOffset);
        if (newLineOffset.newLineCount > 0) {
            totalHeight += (currentRowHeight * newLineOffset.newLineCount + gutterInDouble_.second);
            ChildrenRowInfo info = {isLastLineHasMatchParent, currentRowHeight, currentNewLineCount};
            gridColChildrenRowsInfo_.emplace_back(info);
            if (!isLastLineHasMatchParent) {
                CalcCrossAxisAlignment(layoutWrapper, *gridColChildrenRows_.rbegin(), currentRowHeight);
            }
            isLastLineHasMatchParent = isMatchParent;
            currentRowHeight = MeasureChild(layoutWrapper, child, sizeType, totalHeight, isMatchParent);
            currentNewLineCount = newLineOffset.newLineCount;
        } else {
            isLastLineHasMatchParent |= isMatchParent;
            auto childHeight = MeasureChild(layoutWrapper, child, sizeType, totalHeight, isMatchParent);
            currentRowHeight = std::max(childHeight, currentRowHeight);
        }
        gridColChildrenOfOneRow_.rbegin()->second.offsetY = totalHeight;
    }
    if (!gridColChildrenOfOneRow_.empty()) {
        gridColChildrenRows_.emplace_back(gridColChildrenOfOneRow_);
        ChildrenRowInfo info = {isLastLineHasMatchParent, currentRowHeight, currentNewLineCount};
        gridColChildrenRowsInfo_.emplace_back(info);
        if (!isLastLineHasMatchParent) {
            CalcCrossAxisAlignment(layoutWrapper, *gridColChildrenRows_.rbegin(), currentRowHeight);
        }
        gridColChildrenOfOneRow_.clear();
    }
    return (totalHeight + currentRowHeight);
}
} // namespace OHOS::Ace::NG
