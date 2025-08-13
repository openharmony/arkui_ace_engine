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

#include "core/components_ng/pattern/linear_split/linear_split_layout_algorithm.h"

#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/linear_split/linear_split_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double SPLIT_HEIGHT_RATE = 2.0;
constexpr double DEFAULT_DRAG_REGION_RATE = 2.0;
constexpr Dimension DEFAULT_DRAG_REGION_HALF = 10.0_vp;
constexpr double HALF_SPLIT_HEIGHT = 2.0;
} // namespace

void LinearSplitLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        MeasureBeforeAPI10(layoutWrapper);
        return;
    }
    layoutPolicyChildren_.clear();
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    visibleChildCount_ = GetVisibleChildCount(layoutWrapper);
    OptionalSizeF realSize;
    do {
        // Use idea size first if it is valid.
        realSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (realSize.IsValid()) {
            break;
        }

        if (layoutProperty->GetMeasureType() == MeasureType::MATCH_PARENT) {
            realSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
        }
    } while (false);

    if (!childrenDragPos_.empty() && childrenDragPos_.size() != static_cast<size_t>(visibleChildCount_) + 1U) {
        childrenDragPos_.clear();
    }

    // measure self size.
    auto [childTotalSize, childMaxSize] = MeasureChildren(layoutWrapper);
    if (splitType_ == SplitType::ROW_SPLIT) {
        if (!layoutConstraint->selfIdealSize.Width()) {
            float width = std::max(minSize.Width(), childTotalSize.Width());
            if (maxSize.Width() > 0) {
                width = std::min(maxSize.Width(), width);
            }
            realSize.SetWidth(width);
        }
        if (!layoutConstraint->selfIdealSize.Height()) {
            realSize.SetHeight(std::min(maxSize.Height(), childMaxSize.Height()));
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        if (!layoutConstraint->selfIdealSize.Height()) {
            float height = std::min(maxSize.Height(), childTotalSize.Height());
            realSize.SetHeight(height);
        }
        if (!layoutConstraint->selfIdealSize.Width()) {
            realSize.SetWidth(std::min(maxSize.Width(), childMaxSize.Width()));
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    }
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());
    auto policySize = MeasureSelfByLayoutPolicy(layoutWrapper, childTotalSize, childMaxSize);
    realSize.UpdateSizeWithCheck(policySize);
    layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    MeasureAdaptiveLayoutChildren(layoutWrapper, realSize.ConvertToSizeT());
}

void LinearSplitLayoutAlgorithm::MeasureBeforeAPI10(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& parentIdeaSize = layoutConstraint->parentIdealSize;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto measureType = layoutProperty->GetMeasureType();
    OptionalSizeF realSize;
    do {
        // Use idea size first if it is valid.
        realSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (realSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            realSize.UpdateIllegalSizeWithCheck(parentIdeaSize);
        }
    } while (false);

    // measure self size.
    SizeF childTotalSize = MeasureChildrenBeforeAPI10(layoutWrapper);
    AddPaddingToSize(padding, childTotalSize);
    if (splitType_ == SplitType::ROW_SPLIT) {
        if (!layoutConstraint->selfIdealSize.Width()) {
            float width = std::max(minSize.Width(), childTotalSize.Width());
            if (maxSize.Width() > 0) {
                width = std::min(maxSize.Width(), width);
            }
            realSize.SetWidth(width);
        }
        if (!layoutConstraint->selfIdealSize.Height()) {
            realSize.SetHeight(maxSize.Height());
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        if (!layoutConstraint->selfIdealSize.Height()) {
            float height = std::min(maxSize.Height(), childTotalSize.Height());
            realSize.SetHeight(height);
        }
        if (!layoutConstraint->selfIdealSize.Width()) {
            realSize.SetWidth(maxSize.Width());
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize((realSize.ConvertToSizeT()));
    }
}

std::pair<SizeF, SizeF> LinearSplitLayoutAlgorithm::MeasureChildren(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, {});
    auto padding = layoutProperty->CreatePaddingAndBorder();
    // Get Max Size for children.
    float allocatedSize = 0.0f;
    float crossSize = 0.0f;
    float childMaxWidth = 0.0f;
    float childMaxHeight = 0.0f;
    const auto [startMargin, endMargin] = GetDividerMargin(layoutWrapper);
    auto childConstraint = CreateChildConstraint(layoutWrapper);
    // measure normal node.
    int32_t index = 0;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        const auto& childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        if (childLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::GONE) {
            continue;
        }
        DisableLayoutPolicy(child);
        auto adjustedChildConstraint = GetChildConstrain(layoutWrapper, childConstraint, index);
        if (IsChildMatchParent(child)) {
            layoutPolicyChildren_.emplace_back(child, adjustedChildConstraint);
            continue;
        }
        child->Measure(adjustedChildConstraint);
        float childWidth = child->GetGeometryNode()->GetMarginFrameSize().Width();
        float childHeight = child->GetGeometryNode()->GetMarginFrameSize().Height();
        allocatedSize += childWidth;
        crossSize += childHeight;
        childMaxWidth = childWidth > childMaxWidth ? childWidth : childMaxWidth;
        childMaxHeight = childHeight > childMaxHeight ? childHeight : childMaxHeight;
        index++;
    }

    const auto splitHeightFloat = static_cast<float>(DEFAULT_SPLIT_HEIGHT);
    if (splitType_ == SplitType::ROW_SPLIT) {
        allocatedSize += splitHeightFloat * std::max(0.f, static_cast<float>(visibleChildCount_ - 1));
    } else {
        crossSize +=
            (startMargin + splitHeightFloat + endMargin) * std::max(0.f, static_cast<float>(visibleChildCount_ - 1));
    }

    SizeF childTotalSize = { allocatedSize, crossSize };
    AddPaddingToSize(padding, childTotalSize);
    SizeF childMaxSize = { childMaxWidth, childMaxHeight };
    AddPaddingToSize(padding, childMaxSize);
    return { childTotalSize, childMaxSize };
}

SizeF LinearSplitLayoutAlgorithm::MeasureChildrenBeforeAPI10(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, {});
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& maxSize = layoutConstraint->maxSize;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    // Get Max Size for children.
    OptionalSizeF optionalMaxSize;
    optionalMaxSize.UpdateIllegalSizeWithCheck(maxSize);
    auto maxSizeT = optionalMaxSize.ConvertToSizeT();
    MinusPaddingToSize(padding, maxSizeT);

    const auto& childrenWrappers = layoutWrapper->GetAllChildrenWithBuild();

    auto childConstraint = layoutProperty->CreateChildConstraint();
    childConstraint.maxSize = layoutConstraint->selfIdealSize.ConvertToSizeT();
    if (childConstraint.maxSize.Height() < 0.0) {
        childConstraint.maxSize.SetHeight(maxSize.Height());
    }
    if (childConstraint.maxSize.Width() < 0.0) {
        childConstraint.maxSize.SetWidth(maxSize.Width());
    }

    float allocatedSize = 0.0f;
    float crossSize = 0.0f;
    // measure normal node.
    for (const auto& child : childrenWrappers) {
        child->Measure(childConstraint);
        allocatedSize += child->GetGeometryNode()->GetMarginFrameSize().Width();
        crossSize += child->GetGeometryNode()->GetMarginFrameSize().Height();
    }
    return { allocatedSize, crossSize };
}

LayoutConstraintF LinearSplitLayoutAlgorithm::GetChildConstrain(
    LayoutWrapper* layoutWrapper, LayoutConstraintF childConstrain, int32_t index)
{
    const auto [startMargin, endMargin] = GetDividerMargin(layoutWrapper);
    auto constrain = childConstrain;
    if (!childrenDragPos_.empty() && (index < visibleChildCount_)) {
        float childMaxSize =
            childrenDragPos_[index + 1] - childrenDragPos_[index] - static_cast<float>(DEFAULT_SPLIT_HEIGHT);
        if (splitType_ == SplitType::ROW_SPLIT) {
            if (index == visibleChildCount_ - 1) {
                childMaxSize += static_cast<float>(DEFAULT_SPLIT_HEIGHT);
            }
            constrain.selfIdealSize.SetWidth(childMaxSize);
        } else {
            if (index == 0) {
                childMaxSize -= startMargin;
            } else if (index == visibleChildCount_ - 1) {
                childMaxSize = childMaxSize - endMargin + static_cast<float>(DEFAULT_SPLIT_HEIGHT);
            } else {
                childMaxSize -= startMargin + endMargin;
            }
            constrain.selfIdealSize.SetHeight(childMaxSize);
        }
    }
    return constrain;
}

void LinearSplitLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        LayoutBeforeAPI10(layoutWrapper);
        return;
    }
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    float childTotalWidth = 0.0f;
    float childTotalHeight = 0.0f;
    visibleChildCount_ = GetVisibleChildCount(layoutWrapper);

    childrenConstrains_ = std::vector<float>(visibleChildCount_, 0.0f);
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        const auto& childLayoutProperty = item->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        if (childLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::GONE) {
            continue;
        }
        childTotalWidth += item->GetGeometryNode()->GetMarginFrameSize().Width();
        childTotalHeight += item->GetGeometryNode()->GetMarginFrameSize().Height();
    }

    const auto splitHeightFloat = static_cast<float>(DEFAULT_SPLIT_HEIGHT);
    if (splitType_ == SplitType::ROW_SPLIT) {
        childTotalWidth += splitHeightFloat * std::max(0.f, static_cast<float>(visibleChildCount_ - 1));
    } else {
        const auto [startMargin, endMargin] = GetDividerMargin(layoutWrapper);
        childTotalHeight +=
            (startMargin + splitHeightFloat + endMargin) * std::max(0.f, static_cast<float>(visibleChildCount_ - 1));
    }

    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.Width();
    auto parentHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - padding.Height();

    auto startPointX = (parentWidth - childTotalWidth) / 2 + padding.left.value_or(0.0f);
    auto startPointY = (parentHeight - childTotalHeight) / 2 + padding.top.value_or(0.0f);
    float childOffsetMain = startPointX;
    float childOffsetCross = startPointY;
    if (splitType_ == SplitType::ROW_SPLIT) {
        LayoutRowSplit(layoutWrapper, childOffsetMain, childOffsetCross);
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        LayoutColumnSplit(layoutWrapper, childOffsetMain, childOffsetCross);
    }
}

void LinearSplitLayoutAlgorithm::UpdateChildPositionWidthIgnoreLayoutSafeArea(
    const RefPtr<LayoutWrapper>& childLayoutWrapper, const OffsetF& originOffset)
{
    auto childNode = childLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(childNode);
    const auto& childLayoutProperty = childNode->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    if (!childLayoutProperty->IsIgnoreOptsValid()) {
        return;
    }
    auto saeCorrect = originOffset;
    IgnoreLayoutSafeAreaOpts& opts = *(childLayoutProperty->GetIgnoreLayoutSafeAreaOpts());
    auto sae = childNode->GetAccumulatedSafeAreaExpand(false, opts, IgnoreStrategy::FROM_MARGIN);
    auto offsetX = sae.left.value_or(0.0f);
    auto offsetY = sae.top.value_or(0.0f);
    OffsetF saeTrans = OffsetF(offsetX, offsetY);
    saeCorrect -= saeTrans;
    childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(saeCorrect);
}

void LinearSplitLayoutAlgorithm::LayoutRowSplit(
    LayoutWrapper* layoutWrapper, float childOffsetMain, float childOffsetCross)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto parentHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - padding.Height();
    bool isFirstSetPos = false;
    if (childrenDragPos_.empty()) {
        childrenDragPos_ = std::vector<float>(visibleChildCount_ + 1, 0.0f);
        isFirstSetPos = true;
    }
    splitLength_ = parentHeight;

    if (padding.top.has_value()) {
        childOffsetCross = padding.top.value();
    }
    int32_t index = 0;
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        if (GreatOrEqual(index, static_cast<int32_t>(childrenDragPos_.size()))) {
            return;
        }
        const auto& childLayoutProperty = item->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        if (childLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::GONE) {
            continue;
        }
        auto childMargin = childLayoutProperty->CreateMargin();
        float marginWidth = childMargin.left.value_or(0.f) + childMargin.right.value_or(0.f);
        childrenConstrains_[index] = GetItemMinSize(item, layoutWrapper) + marginWidth;
        if (isFirstSetPos) {
            childrenDragPos_[index] = childOffsetMain;
        } else {
            childOffsetMain = childrenDragPos_[index];
        }
        item->GetGeometryNode()->SetMarginFrameOffset(OffsetF(childOffsetMain, childOffsetCross));
        UpdateChildPositionWidthIgnoreLayoutSafeArea(item, OffsetF(childOffsetMain, childOffsetCross));
        item->Layout();
        childOffsetMain +=
            item->GetGeometryNode()->GetMarginFrameSize().Width() + static_cast<float>(DEFAULT_SPLIT_HEIGHT);
        if (index < visibleChildCount_ - 1) {
            splitRects_.emplace_back(childOffsetMain - DEFAULT_SPLIT_HEIGHT - DEFAULT_DRAG_REGION_HALF.ConvertToPx(),
                childOffsetCross, DEFAULT_DRAG_REGION_HALF.ConvertToPx() * DEFAULT_DRAG_REGION_RATE, parentHeight);
            childrenOffset_.emplace_back(childOffsetMain - HALF_SPLIT_HEIGHT, childOffsetCross);
        }
        index++;
    }
    if (isFirstSetPos) {
        if (GreatOrEqual(index, static_cast<int32_t>(childrenDragPos_.size()))) {
            return;
        }
        childrenDragPos_[index] = childOffsetMain - static_cast<float>(DEFAULT_SPLIT_HEIGHT);
    }
}

void LinearSplitLayoutAlgorithm::LayoutColumnSplit(
    LayoutWrapper* layoutWrapper, float childOffsetMain, float childOffsetCross)
{
    const auto [startMargin, endMargin] = GetDividerMargin(layoutWrapper);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.Width();
    bool isFirstSetPos = false;
    if (childrenDragPos_.empty()) {
        childrenDragPos_ = std::vector<float>(visibleChildCount_ + 1, 0.0f);
        isFirstSetPos = true;
    }
    splitLength_ = parentWidth;

    if (padding.left.has_value()) {
        childOffsetMain = padding.left.value();
    }
    int32_t index = 0;
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        if (GreatOrEqual(index, static_cast<int32_t>(childrenDragPos_.size()))) {
            return;
        }
        const auto& childLayoutProperty = item->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        if (childLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::GONE) {
            continue;
        }
        ColumnSplitChildConstrain(layoutWrapper, item, index);
        if (isFirstSetPos) {
            childrenDragPos_[index] = childOffsetCross;
            if (index != 0) {
                childOffsetCross += startMargin;
            }
        } else {
            childOffsetCross = childrenDragPos_[index];
        }
        item->GetGeometryNode()->SetMarginFrameOffset(OffsetF(childOffsetMain, childOffsetCross));
        UpdateChildPositionWidthIgnoreLayoutSafeArea(item, OffsetF(childOffsetMain, childOffsetCross));
        item->Layout();
        childOffsetCross += item->GetGeometryNode()->GetMarginFrameSize().Height() + endMargin +
                            static_cast<float>(DEFAULT_SPLIT_HEIGHT);
        if (index < visibleChildCount_ - 1) {
            splitRects_.emplace_back(childOffsetMain, childOffsetCross - DEFAULT_DRAG_REGION_HALF.ConvertToPx(),
                parentWidth, DEFAULT_DRAG_REGION_HALF.ConvertToPx() * DEFAULT_DRAG_REGION_RATE);
            childrenOffset_.emplace_back(childOffsetMain, childOffsetCross - HALF_SPLIT_HEIGHT);
        }
        index++;
    }
    if (isFirstSetPos) {
        if (GreatOrEqual(index, static_cast<int32_t>(childrenDragPos_.size()))) {
            return;
        }
        childrenDragPos_[index] = childOffsetCross - static_cast<float>(DEFAULT_SPLIT_HEIGHT) - endMargin;
    }
}

void LinearSplitLayoutAlgorithm::ColumnSplitChildConstrain(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& item, int32_t index)
{
    if (static_cast<uint32_t>(index) >= childrenConstrains_.size()) {
        return;
    }
    const auto [startMargin, endMargin] = GetDividerMargin(layoutWrapper);
    const auto& layoutProperty = item->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto childMargin = layoutProperty->CreateMargin();
    float marginHeight = childMargin.top.value_or(0.f) + childMargin.bottom.value_or(0.f);
    childrenConstrains_[index] = GetItemMinSize(item, layoutWrapper) + marginHeight;
    if (index == 0) {
        childrenConstrains_[index] += startMargin;
    } else if (index == visibleChildCount_) {
        childrenConstrains_[index] += endMargin;
    } else {
        childrenConstrains_[index] += startMargin + endMargin;
    }
}

std::pair<float, float> LinearSplitLayoutAlgorithm::GetDividerMargin(LayoutWrapper* layoutWrapper)
{
    auto listLayoutProperty = AceType::DynamicCast<LinearSplitLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(listLayoutProperty, {});
    ColumnSplitDivider divider;
    if (listLayoutProperty->HasDivider()) {
        divider = listLayoutProperty->GetDivider().value();
    }
    auto startMargin = static_cast<float>(divider.startMargin.ConvertToPx());
    auto endMargin = static_cast<float>(divider.endMargin.ConvertToPx());
    return { startMargin, endMargin };
}

float LinearSplitLayoutAlgorithm::GetLinearSplitChildMinSize(LayoutWrapper* layoutWrapper)
{
    constexpr float DEFAULT_MIN_CHILD_SIZE = 20.f;
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(frameNode, DEFAULT_MIN_CHILD_SIZE);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, DEFAULT_MIN_CHILD_SIZE);
    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, DEFAULT_MIN_CHILD_SIZE);
    auto size = static_cast<float>(theme->GetLinearSplitChildMinSize());
    return size;
}

int32_t LinearSplitLayoutAlgorithm::GetVisibleChildCount(LayoutWrapper* layoutWrapper)
{
    int32_t visibleChildCount = 0;
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        const auto& childLayoutProperty = child->GetLayoutProperty();
        if (childLayoutProperty && childLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::GONE) {
            visibleChildCount++;
        }
    }
    return visibleChildCount;
}

void LinearSplitLayoutAlgorithm::LayoutBeforeAPI10(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    int32_t index = 0;
    float childOffsetMain = 0.0f;
    float childOffsetCross = 0.0f;
    float childTotalWidth = 0.0f;
    float childTotalHeight = 0.0f;
    float childTotalOffsetMain = 0.0f;
    float childTotalOffsetCross = 0.0f;
    if (dragSplitOffset_.empty()) {
        dragSplitOffset_ = std::vector<float>(layoutWrapper->GetTotalChildCount() - 1, 0.0);
    }
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        childTotalWidth += item->GetGeometryNode()->GetFrameSize().Width();
        childTotalHeight += item->GetGeometryNode()->GetFrameSize().Height();
        childTotalOffsetMain += item->GetGeometryNode()->GetFrameSize().Width();
        childTotalOffsetCross += item->GetGeometryNode()->GetFrameSize().Height();
        if (index < layoutWrapper->GetTotalChildCount() - 1) {
            if (splitType_ == SplitType::ROW_SPLIT) {
                childTotalOffsetMain += dragSplitOffset_[index] + DEFAULT_SPLIT_HEIGHT;
            } else {
                childTotalOffsetCross += dragSplitOffset_[index] + DEFAULT_SPLIT_HEIGHT;
            }
        }
        index++;
    }
    index = 0;
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.Width();
    auto parentHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - padding.Height();

    parentOffset_ = layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto startPointX = (parentWidth - childTotalWidth) / 2;
    startPointX = startPointX < 0 ? 0.0f : startPointX;
    startPointX += padding.left.value_or(0.0f);
    auto startPointY = (parentHeight - childTotalHeight) / 2;
    startPointY = startPointY < 0 ? 0.0f : startPointY;
    startPointY += padding.top.value_or(0.0f);
    childOffsetMain += startPointX;
    childOffsetCross += startPointY;
    childTotalOffsetMain += startPointX;
    childTotalOffsetCross += startPointY;
    if (splitType_ == SplitType::ROW_SPLIT) {
        LayoutRowSplitBeforeAPI10(layoutWrapper, childOffsetMain, childOffsetCross, childTotalOffsetMain);
    } else if (splitType_ == SplitType::COLUMN_SPLIT) {
        LayoutColumnSplitBeforeAPI10(layoutWrapper, childOffsetMain, childOffsetCross, childTotalOffsetCross);
    }
}

void LinearSplitLayoutAlgorithm::LayoutRowSplitBeforeAPI10(
    LayoutWrapper* layoutWrapper, float childOffsetMain, float childOffsetCross, float childTotalOffsetMain)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.Width();
    auto parentHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - padding.Height();

    splitLength_ = parentHeight;
    if (GreatOrEqual(childTotalOffsetMain, parentWidth)) {
        isOverParent_ = true;
    }
    int32_t index = 0;
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        if (padding.top.has_value()) {
            childOffsetCross = padding.top.value();
        }
        OffsetF offset = OffsetF(childOffsetMain, childOffsetCross);
        item->GetGeometryNode()->SetMarginFrameOffset(offset);
        childOffsetMain += item->GetGeometryNode()->GetFrameSize().Width();
        if (index < layoutWrapper->GetTotalChildCount() - 1) {
            childOffsetMain += dragSplitOffset_[index];
            childrenOffset_.emplace_back(OffsetF(childOffsetMain, childOffsetCross));
            splitRects_.emplace_back(
                childOffsetMain - DEFAULT_SPLIT_HEIGHT, 0, DEFAULT_SPLIT_HEIGHT * SPLIT_HEIGHT_RATE, parentHeight);
        }
        childOffsetMain += static_cast<float>(DEFAULT_SPLIT_HEIGHT);
        index++;
        item->Layout();
    }
}

void LinearSplitLayoutAlgorithm::LayoutColumnSplitBeforeAPI10(
    LayoutWrapper* layoutWrapper, float childOffsetMain, float childOffsetCross, float childTotalOffsetCross)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto parentWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width() - padding.Width();
    auto parentHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - padding.Height();

    splitLength_ = parentWidth;
    if (GreatOrEqual(childTotalOffsetCross, parentHeight)) {
        isOverParent_ = true;
    }
    int32_t index = 0;
    for (const auto& item : layoutWrapper->GetAllChildrenWithBuild()) {
        if (padding.left.has_value()) {
            childOffsetMain = padding.left.value();
        }
        OffsetF offset = OffsetF(childOffsetMain, childOffsetCross);
        item->GetGeometryNode()->SetMarginFrameOffset(offset);
        childOffsetCross += item->GetGeometryNode()->GetFrameSize().Height();
        if (index < layoutWrapper->GetTotalChildCount() - 1) {
            childOffsetCross += dragSplitOffset_[index];
            childrenOffset_.emplace_back(OffsetF(childOffsetMain, childOffsetCross));
            splitRects_.emplace_back(
                0, childOffsetCross - DEFAULT_SPLIT_HEIGHT, parentWidth, DEFAULT_SPLIT_HEIGHT * SPLIT_HEIGHT_RATE);
        }
        childOffsetCross += static_cast<float>(DEFAULT_SPLIT_HEIGHT);
        index++;
        item->Layout();
    }
}

float LinearSplitLayoutAlgorithm::GetItemMinSize(const RefPtr<LayoutWrapper>& item, LayoutWrapper* layoutWrapper) const
{
    const auto& layoutProperty = item->GetLayoutProperty();
    const auto& minSizeTheme = GetLinearSplitChildMinSize(layoutWrapper);
    CHECK_NULL_RETURN(layoutProperty, minSizeTheme);
    const auto& calcConstraint = layoutProperty->GetCalcLayoutConstraint();

    float minSizeF = 0.0f;
    if (calcConstraint && calcConstraint->minSize.has_value()) {
        auto minSize = layoutProperty->GetLayoutConstraint().value_or(LayoutConstraintF {}).minSize;
        minSizeF = splitType_ == SplitType::ROW_SPLIT ? minSize.Width() : minSize.Height();
    } else {
        minSizeF = minSizeTheme;
    }

    // According to general measure rules, the size of a component can't be less than the sum of border and padding.
    auto paddingWithBorder = layoutProperty->CreatePaddingAndBorder();
    return splitType_ == SplitType::ROW_SPLIT ? std::max(minSizeF, paddingWithBorder.Width())
                                              : std::max(minSizeF, paddingWithBorder.Height());
}

OptionalSizeF LinearSplitLayoutAlgorithm::MeasureSelfByLayoutPolicy(LayoutWrapper* layoutWrapper,
    const SizeF& childTotalSize, const SizeF& childMaxSize)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, {});
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_RETURN(layoutPolicy.has_value(), {});
    OptionalSizeF realSize;
    auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    auto matchParentSize = ConstrainIdealSizeByLayoutPolicy(layoutConstraint.value(),
        widthLayoutPolicy, heightLayoutPolicy, Axis::HORIZONTAL).ConvertToSizeT();
    realSize.UpdateSizeWithCheck(matchParentSize);
    if (widthLayoutPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE &&
        heightLayoutPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        return realSize;
    }
    auto width = splitType_ == SplitType::COLUMN_SPLIT ? childMaxSize.Width() : childTotalSize.Width();
    auto height = splitType_ == SplitType::COLUMN_SPLIT ? childTotalSize.Height() : childMaxSize.Height();
    auto fixIdealSize = UpdateOptionSizeByCalcLayoutConstraint({width, height},
        layoutProperty->GetCalcLayoutConstraint(),
        layoutProperty->GetLayoutConstraint()->percentReference);
    if (widthLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        realSize.SetWidth(fixIdealSize.Width());
    }
    if (heightLayoutPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        realSize.SetHeight(fixIdealSize.Height());
    }
    return realSize;
}

void LinearSplitLayoutAlgorithm::MeasureAdaptiveLayoutChildren(LayoutWrapper* layoutWrapper, SizeF realSize)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToNonNegativeSize(padding, realSize);
    auto host = layoutWrapper->GetHostNode();
    IgnoreLayoutSafeAreaBundle bundle;
    for (auto& pair : layoutPolicyChildren_) {
        auto child = pair.first;
        auto layoutConstraint = pair.second;
        if (splitType_ == SplitType::COLUMN_SPLIT) {
            layoutConstraint.parentIdealSize.SetWidth(realSize.Width());
        } else if (splitType_ == SplitType::ROW_SPLIT) {
            layoutConstraint.parentIdealSize.SetHeight(realSize.Height());
        }
        auto childNode = child->GetHostNode();
        if (childNode && childNode->GetLayoutProperty() && childNode->GetLayoutProperty()->IsExpandConstraintNeeded()) {
            bundle.first.emplace_back(childNode);
            child->SetDelaySelfLayoutForIgnore();
            child->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
            continue;
        }
        child->Measure(layoutConstraint);
    }
    if (host && host->GetContext() && GetNeedPostponeForIgnore() && !bundle.first.empty()) {
        auto context = host->GetContext();
        host->SetDelaySelfLayoutForIgnore();
        bundle.second = host;
        context->AddIgnoreLayoutSafeAreaBundle(std::move(bundle));
    }
}

bool LinearSplitLayoutAlgorithm::IsChildMatchParent(const RefPtr<LayoutWrapper>& child)
{
    CHECK_NULL_RETURN(child, false);
    auto childLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, false);
    auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_RETURN(layoutPolicy, false);
    auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_;
    auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_;
    if (splitType_ == SplitType::ROW_SPLIT) {
        return heightLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) == LayoutCalPolicy::MATCH_PARENT;
    }
    return widthLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) == LayoutCalPolicy::MATCH_PARENT;
}

void LinearSplitLayoutAlgorithm::DisableLayoutPolicy(const RefPtr<LayoutWrapper>& child)
{
    CHECK_NULL_VOID(child);
    auto childLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy);
    if (splitType_ == SplitType::ROW_SPLIT && layoutPolicy.value().widthLayoutPolicy_.has_value()) {
        childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
        return;
    }
    if (splitType_ == SplitType::COLUMN_SPLIT && layoutPolicy.value().heightLayoutPolicy_.has_value()) {
        childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    }
}

LayoutConstraintF LinearSplitLayoutAlgorithm::CreateChildConstraint(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, LayoutConstraintF());
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, LayoutConstraintF());
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    const auto& maxSize = layoutConstraint->maxSize;
    auto padding = layoutProperty->CreatePaddingAndBorder();
    OptionalSizeF optionalMaxSize;
    optionalMaxSize.UpdateIllegalSizeWithCheck(maxSize);
    auto maxSizeT = optionalMaxSize.ConvertToSizeT();
    MinusPaddingToSize(padding, maxSizeT);

    auto childConstraint = layoutProperty->CreateChildConstraint();
    childConstraint.maxSize = layoutConstraint->selfIdealSize.ConvertToSizeT();
    if (childConstraint.maxSize.Height() < 0.0) {
        childConstraint.maxSize.SetHeight(maxSizeT.Height());
    }
    if (childConstraint.maxSize.Width() < 0.0) {
        childConstraint.maxSize.SetWidth(maxSizeT.Width());
    }
    return childConstraint;
}
} // namespace OHOS::Ace::NG