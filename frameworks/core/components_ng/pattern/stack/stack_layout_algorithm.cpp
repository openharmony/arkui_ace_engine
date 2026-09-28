/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/pattern/stack/stack_layout_algorithm.h"

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

StackLayoutAlgorithm::StackLayoutAlgorithm() = default;

void StackLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
    HandleStackContentOverflow(layoutWrapper);
}

// Called to perform layout render node and child.
void StackLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& stackLayoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(stackLayoutProperty);
    const auto& padding = stackLayoutProperty->CreatePaddingAndBorder();
    auto layoutDirection = stackLayoutProperty->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    auto contentSize = frameSize;
    MinusPaddingToSize(padding, contentSize);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    auto layoutProperty = DynamicCast<StackLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        auto rawAlign = layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
        align = Alignment::GetAlignment(layoutDirection, rawAlign.GetAlignmentStr(TextDirection::AUTO));
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childAlign = align;
        auto childLayoutProperty = child->GetLayoutProperty();
        if (childLayoutProperty && childLayoutProperty->GetPositionProperty() &&
            childLayoutProperty->GetPositionProperty()->HasLayoutGravity()) {
            auto rawChildAlign =
                childLayoutProperty->GetPositionProperty()->GetLayoutGravity().value_or(Alignment::CENTER);
            childAlign = Alignment::GetAlignment(layoutDirection, rawChildAlign.GetAlignmentStr(TextDirection::AUTO));
        }
        auto childNode = child->GetHostNode();
        auto host = layoutWrapper->GetHostNode();
        if (host && childNode && childNode->GetLayoutProperty() &&
            childNode->GetLayoutProperty()->IsIgnoreOptsValid()) {
            IgnoreLayoutSafeAreaOpts& opts = *(childNode->GetLayoutProperty()->GetIgnoreLayoutSafeAreaOpts());
            auto sae = host->GetAccumulatedSafeAreaExpand(true, opts);
            auto adjustContentSize = contentSize + sae.Size();
            auto translate =
                CalculateStackAlignment(adjustContentSize, child->GetGeometryNode()->GetMarginFrameSize(), childAlign) +
                paddingOffset;
            translate -= sae.Offset();
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
        } else {
            auto translate =
                CalculateStackAlignment(contentSize, child->GetGeometryNode()->GetMarginFrameSize(), childAlign) +
                paddingOffset;
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
        }
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = CalculateStackAlignment(contentSize, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}

NG::OffsetF StackLayoutAlgorithm::CalculateStackAlignment(
    const NG::SizeF& parentSize, const NG::SizeF& childSize, const Alignment& alignment)
{
    NG::OffsetF offset;
    offset.SetX((1.0 + alignment.GetHorizontal()) * (parentSize.Width() - childSize.Width()) / 2.0);
    offset.SetY((1.0 + alignment.GetVertical()) * (parentSize.Height() - childSize.Height()) / 2.0);
    return offset;
}

static bool IsSafeImplicitAsync(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = AceType::DynamicCast<StackLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto syncLoad = layoutProperty->GetSyncLoad().value_or(false);
    // If user explicitly disable this ferature, we can not try to apply it.
    if (syncLoad) {
        ACE_SCOPED_TRACE("ImplicitSplit:reject syncLoad");
        return false;
    }
    // Changed constraint invalidates the last-frame size as evidence: children may resolve to a
    // different size this frame, and a deferred tail would then cause a visible reflow jump.
    if (layoutWrapper->ConstraintChanged()) {
        ACE_SCOPED_TRACE("ImplicitSplit:reject ConstraintChanged");
        return false;
    }
    const auto& geometry = layoutWrapper->GetGeometryNode();
    // Without a geometry node there is no measure history to base the safety argument on.
    if (!geometry) {
        ACE_SCOPED_TRACE("ImplicitSplit:reject geometry");
        return false;
    }
    const auto& lc = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    // Never constrained means the node has not been through layout: no cap exists to pin the size.
    if (!lc.has_value()) {
        ACE_SCOPED_TRACE("ImplicitSplit:reject lc");
        return false;
    }
    const auto& prev = geometry->GetFrameSize();
    // Never measured (fresh container): deferring its children would flash an empty box, and the
    // resulting size is unknown, so the no-reflow guarantee cannot hold.
    if (NonPositive(prev.Width()) || NonPositive(prev.Height())) {
        ACE_SCOPED_TRACE("ImplicitSplit:reject NonPositive");
        return false;
    }
    // Size is pinned at the constraint cap: existing children already reach maxSize and new ones can
    // only push into the clamp, so the final size provably equals the previous one (no parent re-layout).
    const auto& host = layoutWrapper->GetHostNode();
    int32_t id = host ? host->GetId() : -1;
    if (!(NearEqual(prev.Width(), lc->maxSize.Width()) && NearEqual(prev.Height(), lc->maxSize.Height()))) {
        ACE_SCOPED_TRACE("ImplicitSplit:reject notAtCap id[%d] prev[%.1f x %.1f] max[%.1f x %.1f]", id, prev.Width(),
            prev.Height(), lc->maxSize.Width(), lc->maxSize.Height());
        return false;
    }
    ACE_SCOPED_TRACE("ImplicitSplit:admit id[%d]", id);
    return true;
}

bool StackLayoutAlgorithm::IsAsyncLoadAvailable(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    if (PipelineContext::GetCurrentContext() && AnimationUtils::IsImplicitAnimationOpen()) {
        // Avoid splitting in animation closure. Fast check on the early stage of layout
        return false;
    }

    const auto& layoutProperty = AceType::DynamicCast<StackLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto syncLoad = layoutProperty->GetSyncLoad().value_or(true);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    if (!syncLoad && layoutConstraint.has_value() && layoutConstraint.value().selfIdealSize.IsValid()) {
        return true;
    }

    return IsSafeImplicitAsync(layoutWrapper);
}

bool StackLayoutAlgorithm::MeasureInNextFrame() const
{
    return measureInNextFrame_;
}
} // namespace OHOS::Ace::NG
