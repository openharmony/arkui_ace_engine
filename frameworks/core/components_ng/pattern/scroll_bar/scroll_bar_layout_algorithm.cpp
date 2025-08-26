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

#include "core/components_ng/pattern/scroll_bar/scroll_bar_layout_algorithm.h"

#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

void UpdateChildConstraint(Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(Infinity<float>());
    } else {
        contentConstraint.maxSize.SetWidth(Infinity<float>());
    }
}

void UpdateIdealSize(Axis axis, const SizeF& childSize, const OptionalSizeF& parentSize, OptionalSizeF& idealSize,
    LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        const auto& layoutConstraint = layoutProperty->GetLayoutConstraint().value();
        auto isVertical = axis == Axis::VERTICAL;
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto isCrossWrap = (isVertical ? widthLayoutPolicy : heightLayoutPolicy) == LayoutCalPolicy::WRAP_CONTENT;
        auto isCrossFix = (isVertical ? widthLayoutPolicy : heightLayoutPolicy) == LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
        auto layoutPolicySize =
            ConstrainIdealSizeByLayoutPolicy(layoutConstraint, widthLayoutPolicy, heightLayoutPolicy, axis);
        idealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
        if (isCrossWrap) {
            idealSize.SetCrossSize(std::min(childSize.CrossSize(axis), layoutConstraint.maxSize.CrossSize(axis)), axis);
        } else if (isCrossFix) {
            idealSize.SetCrossSize(childSize.CrossSize(axis), axis);
        }
    }
    if (axis == Axis::HORIZONTAL) {
        if (!idealSize.Height()) {
            if (childSize.Height()) {
                idealSize.SetHeight(childSize.Height());
            } else {
                idealSize.SetHeight(theme->GetDefaultHeight().ConvertToPx());
            }
        }
        if (!idealSize.Width() && parentSize.Width().has_value()) {
            idealSize.SetWidth(parentSize.Width().value());
        }
        return;
    }
    if (!idealSize.Width()) {
        if (childSize.Width()) {
            idealSize.SetWidth(childSize.Width());
        } else {
            idealSize.SetWidth(theme->GetDefaultWidth().ConvertToPx());
        }
    }
    if (!idealSize.Height() && parentSize.Height().has_value()) {
        idealSize.SetHeight(parentSize.Height().value());
    }
}

} // namespace

void ScrollBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value_or(LayoutConstraintF()), axis, MeasureType::MATCH_CONTENT);
    auto parentSize = CreateIdealSize(constraint.value_or(LayoutConstraintF()), axis, MeasureType::MATCH_PARENT);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);
    MinusPaddingToSize(padding, parentSize);

    // Calculate child layout constraint.
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateChildConstraint(axis, idealSize, childLayoutConstraint);

    // Measure child.
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto scrollBarPattern = AceType::DynamicCast<ScrollBarPattern>(layoutWrapper->GetHostNode()->GetPattern());
    if (scrollBarPattern) {
        if (!childWrapper && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            auto size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
            UpdateIdealSize(axis, size, parentSize, idealSize, layoutWrapper);
            scrollBarPattern->SetChild(false);
        } else {
            CHECK_NULL_VOID(childWrapper);
            childWrapper->Measure(childLayoutConstraint);
            // Use child size when self idea size of scroll is not setted.
            auto childSize = childWrapper->GetGeometryNode()->GetMarginFrameSize();
            UpdateIdealSize(axis, childSize, parentSize, idealSize, layoutWrapper);
            scrollBarPattern->SetChild(true);
        }
    }
    AddPaddingToSize(padding, idealSize);
    auto selfSize = idealSize.ConvertToSizeT();
    selfSize.Constrain(constraint->minSize, constraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(selfSize);
}

void ScrollBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto size = geometryNode->GetFrameSize();

    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto childSize = childGeometryNode->GetMarginFrameSize();
    scrollableDistance_ = GetMainAxisSize(size, axis) - GetMainAxisSize(childSize, axis);
    auto scrollBarPattern = AceType::DynamicCast<ScrollBarPattern>(layoutWrapper->GetHostNode()->GetPattern());
    auto controlDistance = scrollBarPattern->GetControlDistance();
    auto scrollableNodeOffset = scrollBarPattern->GetScrollableNodeOffset();
    scrollBarPattern->SetChildOffset(GetMainAxisSize(childSize, axis));
    float currentOffset = 0.0f;
    if (!NearZero(controlDistance) && GreatNotEqual(scrollableDistance_, 0.0f)) {
        currentOffset = scrollableNodeOffset * scrollableDistance_ / controlDistance;
        currentOffset = std::clamp(currentOffset, 0.0f, scrollableDistance_);
    }
    currentOffset_ = currentOffset;
    scrollBarPattern->SetCurrentPosition(currentOffset_);
    auto scrollBarAlignment = Alignment::TOP_LEFT;
    if (layoutProperty->GetPositionProperty()) {
        scrollBarAlignment = layoutProperty->GetPositionProperty()->GetAlignment().value_or(scrollBarAlignment);
    }
    auto alignmentPosition = Alignment::GetAlignPosition(size, childSize, scrollBarAlignment);
    auto currentAxisOffset = axis == Axis::VERTICAL ? OffsetF(alignmentPosition.GetX(), currentOffset_)
                                                    : OffsetF(currentOffset_, alignmentPosition.GetY());
    childGeometryNode->SetMarginFrameOffset(padding.Offset() + currentAxisOffset);
    childWrapper->Layout();
    scrollBarPattern->SetChildRect(childGeometryNode->GetFrameRect());
}

} // namespace OHOS::Ace::NG
