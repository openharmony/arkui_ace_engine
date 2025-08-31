/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension RESERVE_BOTTOM_HEIGHT = 24.0_vp;

void UpdateChildConstraint(Axis axis, const OptionalSizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(LayoutInfinity<float>());
    } else if (axis == Axis::FREE) {
        contentConstraint.maxSize.SetWidth(LayoutInfinity<float>());
        contentConstraint.maxSize.SetHeight(LayoutInfinity<float>());
    } else {
        contentConstraint.maxSize.SetWidth(LayoutInfinity<float>());
    }
}

} // namespace

void ScrollLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value_or(LayoutConstraintF()), axis, MeasureType::MATCH_CONTENT);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    auto isMainFix = false;
    if (layoutPolicy.has_value()) {
        auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
        auto layoutPolicySize = ConstrainIdealSizeByLayoutPolicy(
            constraint.value_or(LayoutConstraintF()), widthLayoutPolicy, heightLayoutPolicy, axis);
        isMainFix = (axis == Axis::VERTICAL && layoutPolicy.value().IsHeightFix()) ||
                    (axis == Axis::HORIZONTAL && layoutPolicy.value().IsWidthFix());
        idealSize.UpdateIllegalSizeWithCheck(layoutPolicySize);
    }
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);
    // Calculate child layout constraint.
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateChildConstraint(axis, idealSize, childLayoutConstraint);
    // Measure child.
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto childSize = SizeF(0.f, 0.f);
    if (childWrapper) {
        childWrapper->Measure(childLayoutConstraint);
        // Use child size when self idea size of scroll is not setted.
        childSize = childWrapper->GetGeometryNode()->GetMarginFrameSize();
        if (!idealSize.Width()) {
            idealSize.SetWidth(childSize.Width());
        }
        if (!idealSize.Height()) {
            idealSize.SetHeight(childSize.Height());
        }
    }
    AddPaddingToSize(padding, idealSize);
    auto selfSize = idealSize.ConvertToSizeT();
    if (!isMainFix) {
        selfSize.Constrain(constraint->minSize, constraint->maxSize);
    } else {
        auto finalSize = UpdateOptionSizeByCalcLayoutConstraint(
            OptionalSizeF(selfSize), layoutProperty->GetCalcLayoutConstraint(), constraint->percentReference);
        if (finalSize.Width().has_value()) {
            selfSize.SetWidth(finalSize.Width().value());
        }
        if (finalSize.Height().has_value()) {
            selfSize.SetHeight(finalSize.Height().value());
        }
    }
    auto scrollNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (scrollPattern->IsSelectScroll() && scrollPattern->GetHasOptionWidth()) {
        auto selectScrollWidth = scrollPattern->GetSelectScrollWidth();
        selfSize.SetWidth(selectScrollWidth);
    }
    auto lastViewSize = scrollPattern->GetViewSize();
    auto lastViewPortExtent = scrollPattern->GetViewPortExtent();
    if (axis == Axis::VERTICAL && LessNotEqual(selfSize.Height(), lastViewSize.Height())) {
        OnSurfaceChanged(layoutWrapper, selfSize.Height());
    }
    if (layoutWrapper->ConstraintChanged() || lastViewSize != selfSize || lastViewPortExtent != childSize) {
        scrollPattern->AddScrollMeasureInfo(constraint, childLayoutConstraint, selfSize, childSize);
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(selfSize);
    UseInitialOffset(axis, selfSize, layoutWrapper);
}

namespace {
float DimensionToFloat(const CalcDimension& value, float selfLength)
{
    return value.Unit() == DimensionUnit::PERCENT ? -value.Value() * selfLength : -value.ConvertToPx();
}
} // namespace

void ScrollLayoutAlgorithm::UseInitialOffset(Axis axis, SizeF selfSize, LayoutWrapper* layoutWrapper)
{
    auto scrollNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    CHECK_NULL_VOID(scrollPattern);
    if (scrollPattern->NeedSetInitialOffset()) {
        auto initialOffset = scrollPattern->GetInitialOffset();
        if (axis == Axis::VERTICAL) {
            auto offset = initialOffset.GetY();
            currentOffset_ = DimensionToFloat(offset, selfSize.Height());
        } else if (axis == Axis::FREE) {
            currentOffset_ = DimensionToFloat(initialOffset.GetX(), selfSize.Width());
            crossOffset_ = DimensionToFloat(initialOffset.GetY(), selfSize.Height());
        } else {
            currentOffset_ = DimensionToFloat(initialOffset.GetX(), selfSize.Width());
        }
    }
}

namespace {
/**
 * @param alwaysEnabled true if effect should still apply when content length is smaller than viewport.
 * @return adjusted offset
 */
float AdjustOffsetInFreeMode(
    float offset, float scrollableDistance, EdgeEffect effect, EffectEdge appliedEdge, bool alwaysEnabled)
{
    if (!alwaysEnabled && NonPositive(scrollableDistance)) {
        effect = EdgeEffect::NONE;
    }
    const float minOffset = std::min(-scrollableDistance, 0.0f); // Max scroll to end
    if (Positive(offset)) {                                      // over-scroll at start
        if (effect != EdgeEffect::SPRING || appliedEdge == EffectEdge::END) {
            offset = 0.0f;
        }
    } else if (LessNotEqual(offset, minOffset)) { // over-scroll at end
        if (effect != EdgeEffect::SPRING || appliedEdge == EffectEdge::START) {
            offset = minOffset;
        }
    }
    return offset;
}
} // namespace

void ScrollLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    auto scrollNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(scrollNode);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto size = geometryNode->GetFrameSize();

    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    viewSize_ = size;
    MinusPaddingToSize(padding, size);
    viewPort_ = size;
    auto scroll = DynamicCast<ScrollPattern>(scrollNode->GetPattern());
    CHECK_NULL_VOID(scroll);
    float zoomScale = scroll->GetZoomScale();
    auto childSize = childGeometryNode->GetMarginFrameSize() * zoomScale;
    auto contentEndOffset = layoutProperty->GetScrollContentEndOffsetValue(.0f);
    float lastScrollableDistance = scrollableDistance_;
    if (axis == Axis::FREE) { // horizontal is the main axis in Free mode
        scrollableDistance_ = childSize.Width() - viewPort_.Width() + contentEndOffset;
    } else {
        scrollableDistance_ = GetMainAxisSize(childSize, axis) - GetMainAxisSize(viewPort_, axis) + contentEndOffset;
    }
    if (axis == Axis::FREE) {
        const auto effect = scroll->GetEdgeEffect();
        const bool alwaysEnabled = scroll->GetAlwaysEnabled();
        const float verticalSpace = childSize.Height() - viewPort_.Height();
        crossOffset_ = AdjustOffsetInFreeMode(crossOffset_, verticalSpace, effect, EffectEdge::ALL, alwaysEnabled);
        // effectEdge only applies to horizontal axis
        currentOffset_ =
            AdjustOffsetInFreeMode(currentOffset_, scrollableDistance_, effect, scroll->GetEffectEdge(), alwaysEnabled);
    } else if (UnableOverScroll(layoutWrapper)) {
        if (scrollableDistance_ > 0.0f) {
            currentOffset_ = std::clamp(currentOffset_, -scrollableDistance_, 0.0f);
        } else {
            currentOffset_ = Positive(currentOffset_) ? 0.0f : std::clamp(currentOffset_, 0.0f, -scrollableDistance_);
        }
    } else if (LessNotEqual(scrollableDistance_, lastScrollableDistance)) {
        if (GreatOrEqual(scrollableDistance_, 0.f) && LessOrEqual(-currentOffset_, lastScrollableDistance) &&
            GreatNotEqual(-currentOffset_, scrollableDistance_)) {
            currentOffset_ = -scrollableDistance_;
        }
    }
    viewPortExtent_ = childSize;
    viewPortLength_ = axis == Axis::FREE ? viewPort_.Width() : GetMainAxisSize(viewPort_, axis);
    auto currentOffset = axis == Axis::VERTICAL ? OffsetF(0.0f, currentOffset_) : OffsetF(currentOffset_, crossOffset_);
    if (layoutDirection == TextDirection::RTL && axis == Axis::HORIZONTAL) {
        currentOffset = OffsetF(std::min(size.Width() - childSize.Width(), 0.f) - currentOffset_, 0.0f);
    }
    auto scrollAlignment = Alignment::CENTER;
    if (layoutProperty->GetPositionProperty() && layoutProperty->GetPositionProperty()->HasAlignment()) {
        scrollAlignment = layoutProperty->GetPositionProperty()->GetAlignment().value();
    }
    if (layoutDirection == TextDirection::RTL && axis == Axis::VERTICAL) {
        UpdateScrollAlignment(scrollAlignment);
    }
    auto alignmentPosition = Alignment::GetAlignPosition(size, viewPortExtent_, scrollAlignment);
    if (GreatNotEqual(viewPortExtent_.Width(), size.Width()) && layoutDirection == TextDirection::RTL &&
        axis == Axis::VERTICAL) {
        alignmentPosition.SetX(size.Width() - viewPortExtent_.Width());
    }
    if (zoomScale != 1.0) {
        auto allOffset = padding.Offset() + currentOffset + alignmentPosition;
        auto sizeDelta = childSize - childGeometryNode->GetMarginFrameSize();
        allOffset += OffsetF(sizeDelta.Width() / 2, sizeDelta.Height() / 2); /* 2:half */
        childGeometryNode->SetMarginFrameOffset(allOffset);
    } else {
        childGeometryNode->SetMarginFrameOffset(padding.Offset() + currentOffset + alignmentPosition);
    }
    childWrapper->Layout();
    UpdateOverlay(layoutWrapper);
    if (scrollNode && scrollNode->GetSuggestOpIncActivatedOnce()) {
        MarkAndCheckNewOpIncNode(childWrapper, axis);
    }
}

void ScrollLayoutAlgorithm::MarkAndCheckNewOpIncNode(const RefPtr<LayoutWrapper>& layoutWrapper, Axis axis)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(layoutWrapper);
    if (frameNode && !frameNode->GetSuggestOpIncActivatedOnce()) {
        frameNode->SetSuggestOpIncActivatedOnce();
        for (auto childIndex = 0; childIndex < frameNode->GetTotalChildCount(); ++childIndex) {
            auto childWrapper = layoutWrapper->GetChildByIndex(childIndex);
            if (!childWrapper) {
                continue;
            }
            auto childNode = AceType::DynamicCast<FrameNode>(childWrapper);
            if (childNode) {
                childNode->MarkAndCheckNewOpIncNode(axis);
            }
        }
    }
}

bool ScrollLayoutAlgorithm::UnableOverScroll(LayoutWrapper* layoutWrapper) const
{
    auto scrollNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(scrollNode, false);
    auto scrollPattern = AceType::DynamicCast<ScrollPattern>(scrollNode->GetPattern());
    return (Positive(currentOffset_) && !scrollPattern->CanOverScrollStart(scrollPattern->GetScrollSource())) ||
           (Negative(currentOffset_) && GreatNotEqual(-currentOffset_, scrollableDistance_) &&
               !scrollPattern->CanOverScrollEnd(scrollPattern->GetScrollSource()));
}

void ScrollLayoutAlgorithm::UpdateOverlay(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->GetFadingEdge().value_or(false)) {
        return;
    }
    auto overlayNode = frameNode->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto scrollFrameSize = geometryNode->GetFrameSize(true);
    auto overlayGeometryNode = overlayNode->GetGeometryNode();
    CHECK_NULL_VOID(overlayGeometryNode);
    overlayGeometryNode->SetFrameSize(scrollFrameSize);
}

void ScrollLayoutAlgorithm::UpdateScrollAlignment(Alignment& scrollAlignment)
{
    if (scrollAlignment == Alignment::TOP_LEFT) {
        scrollAlignment = Alignment::TOP_RIGHT;
    } else if (scrollAlignment == Alignment::TOP_RIGHT) {
        scrollAlignment = Alignment::TOP_LEFT;
    } else if (scrollAlignment == Alignment::BOTTOM_LEFT) {
        scrollAlignment = Alignment::BOTTOM_RIGHT;
    } else if (scrollAlignment == Alignment::BOTTOM_RIGHT) {
        scrollAlignment = Alignment::BOTTOM_LEFT;
    } else if (scrollAlignment == Alignment::CENTER_RIGHT) {
        scrollAlignment = Alignment::CENTER_LEFT;
    } else if (scrollAlignment == Alignment::CENTER_LEFT) {
        scrollAlignment = Alignment::CENTER_RIGHT;
    }
}

void ScrollLayoutAlgorithm::OnSurfaceChanged(LayoutWrapper* layoutWrapper, float contentMainSize)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    // textField not in Scroll
    if (!focusHub->IsCurrentFocus()) {
        return;
    }
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    // only when textField is onFocus
    auto textField = textFieldManager->GetOnFocusTextField().Upgrade();
    CHECK_NULL_VOID(textField);
    auto textFieldHost = textField->GetHost();
    CHECK_NULL_VOID(textFieldHost);
    auto textBase = DynamicCast<TextBase>(textField);
    CHECK_NULL_VOID(textBase);
    auto caretPos = textFieldHost->GetTransformRelativeOffset().GetY() + textBase->GetCaretRect().Bottom();
    auto globalOffset = host->GetTransformRelativeOffset();
    auto offset = contentMainSize + globalOffset.GetY() - caretPos - RESERVE_BOTTOM_HEIGHT.ConvertToPx();
    if (LessOrEqual(offset, 0.0)) {
        // negative offset to scroll down
        currentOffset_ += static_cast<float>(offset);
        TAG_LOGI(AceLogTag::ACE_SCROLL, "update offset on virtual keyboard height change, %{public}f", offset);
    }
}
} // namespace OHOS::Ace::NG
