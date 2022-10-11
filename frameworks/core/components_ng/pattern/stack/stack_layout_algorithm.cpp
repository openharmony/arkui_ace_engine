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

#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"

#include <algorithm>
#include <optional>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void StackLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_CONTENT, true);
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);

    // Measure children
    bool hasNonPositionedItem = false;
    RefPtr<LayoutWrapper> firstChild;
    std::list<RefPtr<LayoutWrapper>> percentChild;
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    auto childConstraint = layoutProperty->CreateChildConstraint();
    for (const auto& item : children) {
        if (IsPercentSize(item)) {
            percentChild.emplace_back(item);
        }
        if (!IsPositionItem(item)) {
            hasNonPositionedItem = true;
            MakeNonPositionedLayoutConstraint(firstChild, idealSize, constraint.value(), childConstraint);
            item->Measure(childConstraint);
        } else {
            MakePositionedLayoutConstraint(item, firstChild, idealSize, constraint.value(), childConstraint);
            item->Measure(childConstraint);
        }
        if (!firstChild) {
            firstChild = item;
        }
    }

    // determine the stack size
    DetermineStackSize(layoutWrapper, hasNonPositionedItem);

    // secondary layout for percent child.
    for (const auto& item : percentChild) {
        childConstraint.percentReference = layoutWrapper->GetGeometryNode()->GetFrameSize();
        childConstraint.maxSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        item->Measure(childConstraint);
    }
}

void StackLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& item : children) {
        auto itemSize = item->GetGeometryNode()->GetFrameSize();
        auto align = Alignment::CENTER;
        if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
            align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
        }
        if (!IsPositionItem(item)) {
            item->GetGeometryNode()->SetMarginFrameOffset(
                GetNonPositionedChildOffset(frameSize, itemSize, align) + padding.Offset());
            item->Layout();
            continue;
        }

        auto offset = GetPositionedChildOffset(frameSize, item, align);
        if (LessNotEqual(offset.GetX(), 0) || LessNotEqual(offset.GetY(), 0.0) ||
            GreatNotEqual(offset.GetX() + itemSize.Width(), frameSize.Width()) ||
            GreatNotEqual(offset.GetY() + itemSize.Height(), frameSize.Height())) {
            isChildOverflow_ = true;
        }
        item->GetGeometryNode()->SetMarginFrameOffset(offset + padding.Offset());
        item->Layout();
    }
}

bool StackLayoutAlgorithm::IsPercentSize(const RefPtr<LayoutWrapper>& wrapper) const
{
    CHECK_NULL_RETURN(wrapper, false);
    auto layoutProperty = wrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(calcLayoutConstraint, false);
    auto selfIdealSize = calcLayoutConstraint->selfIdealSize;
    CHECK_NULL_RETURN(selfIdealSize, false);
    auto width = selfIdealSize->Width();
    if (width && width->IsPercentLength()) {
        return true;
    }

    auto height = selfIdealSize->Height();
    return height && height->IsPercentLength();
}

bool StackLayoutAlgorithm::IsPositionItem(const RefPtr<LayoutWrapper>& wrapper) const
{
    CHECK_NULL_RETURN(wrapper, false);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    return renderContext->HasPosition();
}

void StackLayoutAlgorithm::DetermineStackSize(LayoutWrapper* layoutWrapper, bool hasNonPositioned)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    OptionalSizeF frameSize;
    frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->selfIdealSize);
    if (frameSize.IsValid()) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    auto maxSize = layoutConstraint->maxSize;
    if (mainStackSize_ == MainStackSize::MAX) {
        frameSize.UpdateIllegalSizeWithCheck(maxSize);
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    float maxWidth = 0.0f;
    float maxHeight = 0.0f;
    auto minSize = layoutConstraint->minSize;
    auto width = minSize.Width();
    auto height = minSize.Height();
    float lastChildHeight = height;

    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    for (const auto& item : children) {
        if (IsPercentSize(item)) {
            continue;
        }
        auto itemSize = item->GetGeometryNode()->GetFrameSize();
        auto constrainedWidth = std::clamp(itemSize.Width(), minSize.Width(), maxSize.Width());
        auto constrainedHeight = std::clamp(itemSize.Height(), minSize.Height(), maxSize.Height());
        width = std::max(width, constrainedWidth);
        height = std::max(height, constrainedHeight);
        lastChildHeight = constrainedHeight;
        auto position = GetPositionOffset(item);
        maxWidth = std::max(maxWidth, itemSize.Width() + position.GetX());
        maxHeight = std::max(maxHeight, itemSize.Height() + position.GetY());
    }

    for (const auto& item : children) {
        if (IsPercentSize(item)) {
            if (maxWidth == 0 || maxHeight == 0) {
                auto itemSize = item->GetGeometryNode()->GetFrameSize();
                auto constrainedWidth = std::clamp(itemSize.Width(), minSize.Width(), maxSize.Width());
                auto constrainedHeight = std::clamp(itemSize.Height(), minSize.Height(), maxSize.Height());
                width = std::max(width, constrainedWidth);
                height = std::max(height, constrainedHeight);
                lastChildHeight = constrainedHeight;
                maxWidth = std::max(maxWidth, itemSize.Width());
                maxHeight = std::max(maxHeight, itemSize.Height());
                auto position = GetPositionOffset(item);
                maxWidth = std::max(maxWidth, itemSize.Width() + position.GetX());
                maxHeight = std::max(maxHeight, itemSize.Height() + position.GetY());
            }
        }
    }

    if (mainStackSize_ == MainStackSize::NORMAL && !hasNonPositioned) {
        frameSize.UpdateIllegalSizeWithCheck(maxSize);
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    // Usually used in SemiModal for determining current height.
    if (mainStackSize_ == MainStackSize::LAST_CHILD_HEIGHT) {
        frameSize.UpdateIllegalSizeWithCheck(SizeF(maxSize.Width(), lastChildHeight));
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    if (mainStackSize_ == MainStackSize::MATCH_CHILDREN) {
        frameSize.UpdateIllegalSizeWithCheck(SizeF(maxWidth, maxHeight));
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    if (mainStackSize_ == MainStackSize::MAX_X) {
        frameSize.UpdateIllegalSizeWithCheck(SizeF(maxSize.Width(), maxHeight));
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    if (mainStackSize_ == MainStackSize::MAX_Y) {
        frameSize.UpdateIllegalSizeWithCheck(SizeF(maxWidth, maxSize.Height()));
        layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
        return;
    }

    frameSize.UpdateIllegalSizeWithCheck(SizeF(width, height));
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void StackLayoutAlgorithm::MakeNonPositionedLayoutConstraint(const RefPtr<LayoutWrapper>& firstChild,
    const SizeF& idealSize, const LayoutConstraintF& constraint, LayoutConstraintF& childConstraint) const
{
    childConstraint.UpdatePercentReference(idealSize);
    switch (fit_) {
        case StackFit::STRETCH:
            break;
            childConstraint.UpdateIllegalSelfMarginSizeWithCheck(OptionalSizeF(constraint.maxSize));
        case StackFit::KEEP:
            childConstraint.UpdateMaxSizeWithCheck(constraint.maxSize);
            break;
        case StackFit::INHERIT:
            childConstraint = constraint;
            break;
        case StackFit::FIRST_CHILD:
            childConstraint = constraint;
            if (firstChild) {
                childConstraint.UpdateMaxSizeWithCheck(firstChild->GetGeometryNode()->GetFrameSize());
            }
            break;
        default:
            childConstraint.UpdateMaxSizeWithCheck(constraint.maxSize);
            break;
    }
}

void StackLayoutAlgorithm::MakePositionedLayoutConstraint(const RefPtr<LayoutWrapper>& item,
    const RefPtr<LayoutWrapper>& firstChild, const SizeF& idealSize, const LayoutConstraintF& constraint,
    LayoutConstraintF& childConstraint) const
{
    auto childLayoutProperty = item->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    auto childLayoutConstraint = childLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(childLayoutConstraint);
    auto childIdealSize = childLayoutConstraint->selfIdealSize;
    auto width = childIdealSize.Width();
    auto height = childIdealSize.Height();
    if (!width && height) {
        childLayoutConstraint->maxSize = SizeF(Infinity<float>(), height.value());
    } else if (width && !height) {
        childLayoutConstraint->maxSize = SizeF(width.value(), Infinity<float>());
    } else if (!width && !height) {
        MakeNonPositionedLayoutConstraint(firstChild, idealSize, constraint, childConstraint);
    }
}

OffsetF StackLayoutAlgorithm::GetNonPositionedChildOffset(
    const SizeF& frameSize, const SizeF& childSize, Alignment align)
{
    OffsetF offset(0.0f, 0.0f);
    auto coefficients = IsRightToLeft() ? -1.0f : 1.0f;

    if (GreatOrEqual(frameSize.Width(), childSize.Width())) {
        offset.SetX((1.0 + coefficients * align.GetHorizontal()) * (frameSize.Width() - childSize.Width()) / 2.0);
    }
    if (GreatOrEqual(frameSize.Height(), childSize.Height())) {
        offset.SetY((1.0 + align.GetVertical()) * (frameSize.Height() - childSize.Height()) / 2.0);
    }
    return offset;
}

OffsetF StackLayoutAlgorithm::GetPositionedChildOffset(
    const SizeF& frameSize, const RefPtr<LayoutWrapper>& item, Alignment align)
{
    auto position = GetPosition(item);
    if (!position.has_value()) {
        return GetNonPositionedChildOffset(frameSize, item->GetGeometryNode()->GetFrameSize(), align);
    }

    auto layoutProperty = item->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, OffsetF());
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, OffsetF());
    auto positionLeft = ConvertToPx(position->GetX(), layoutConstraint->scaleProperty).value_or(0);
    auto positionTop = ConvertToPx(position->GetY(), layoutConstraint->scaleProperty).value_or(0);
    return OffsetF(positionLeft, positionTop);
}

OffsetF StackLayoutAlgorithm::GetPositionOffset(const RefPtr<LayoutWrapper>& wrapper) const
{
    OffsetF offset;
    auto position = GetPosition(wrapper);
    if (!position.has_value()) {
        return offset;
    }

    auto layoutProperty = wrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, offset);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, offset);
    auto positionX = ConvertToPx(position->GetX(), layoutConstraint->scaleProperty).value_or(0);
    auto positionY = ConvertToPx(position->GetY(), layoutConstraint->scaleProperty).value_or(0);
    return OffsetF(positionX, positionY);
}

std::optional<OffsetT<Dimension>> StackLayoutAlgorithm::GetPosition(const RefPtr<LayoutWrapper>& wrapper) const
{
    auto host = wrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, std::nullopt);
    return renderContext->GetPosition();
}

} // namespace OHOS::Ace::NG
