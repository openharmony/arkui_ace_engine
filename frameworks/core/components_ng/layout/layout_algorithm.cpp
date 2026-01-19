/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/layout/layout_algorithm.h"

#include "ui/view/layout/layout_algorithm.h"
#include "base/utils/feature_param.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
namespace {
const std::unordered_set<std::string> OVERFLOW_ENABLED_COMPONENTS = {
    OHOS::Ace::V2::COLUMN_ETS_TAG,
    OHOS::Ace::V2::FLEX_ETS_TAG
};
}

static inline void UnionRect(std::optional<RectF>& unionRect, const RectF& rect)
{
    if (unionRect.has_value()) {
        unionRect->CombineRectTInner(rect);
    } else {
        unionRect = rect;
    }
}

LayoutAlgorithmWrapper::LayoutAlgorithmWrapper(
    const RefPtr<LayoutAlgorithm>& layoutAlgorithmT, bool skipMeasure, bool skipLayout)
    : layoutAlgorithm_(layoutAlgorithmT), skipMeasure_(skipMeasure), skipLayout_(skipLayout)
{}

LayoutAlgorithmWrapper::~LayoutAlgorithmWrapper() = default;

RefPtr<LayoutAlgorithmWrapper> LayoutAlgorithmWrapper::CreateLayoutAlgorithmWrapper(
    const RefPtr<Kit::LayoutAlgorithm>& layoutAlgorithm)
{
    auto layoutAlgorithmWrapper = MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutAlgorithmWrapper->SetAbsLayoutAlgorithm(layoutAlgorithm);
    return layoutAlgorithmWrapper;
}

std::optional<SizeF> LayoutAlgorithmWrapper::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    if (!layoutAlgorithm_) {
        if (absLayoutAlgorithm_) {
            return absLayoutAlgorithm_->MeasureContent(contentConstraint);
        }
        return std::nullopt;
    }
    return layoutAlgorithm_->MeasureContent(contentConstraint, layoutWrapper);
}

Kit::LayoutConstraintInfo GetLayoutConstraint(const std::optional<LayoutConstraintF>& contentConstraint)
{
    Kit::LayoutConstraintInfo layoutConstraintInfo;
    if (contentConstraint.has_value()) {
        layoutConstraintInfo.minWidth = contentConstraint.value().minSize.Width();
        layoutConstraintInfo.minHeight = contentConstraint.value().minSize.Height();
        layoutConstraintInfo.maxWidth = contentConstraint.value().maxSize.Width();
        layoutConstraintInfo.maxHeight = contentConstraint.value().maxSize.Height();
        layoutConstraintInfo.percentReferWidth = contentConstraint.value().percentReference.Width();
        layoutConstraintInfo.percentReferHeight = contentConstraint.value().percentReference.Height();
    }
    return layoutConstraintInfo;
}

void LayoutAlgorithmWrapper::Measure(LayoutWrapper* layoutWrapper)
{
    if (!layoutAlgorithm_) {
        if (absLayoutAlgorithm_) {
            auto layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
            absLayoutAlgorithm_->Measure(GetLayoutConstraint(layoutConstraint));
        }
        return;
    }
    layoutAlgorithm_->Measure(layoutWrapper);
    // automatically reset when layoutAlgorithm_ destruct each frame
    layoutAlgorithm_->SetHasMeasured(true);
}

void LayoutAlgorithmWrapper::Layout(LayoutWrapper* layoutWrapper)
{
    if (!layoutAlgorithm_) {
        if (absLayoutAlgorithm_) {
            absLayoutAlgorithm_->Layout();
        }
        return;
    }
    layoutAlgorithm_->Layout(layoutWrapper);
}

void LayoutAlgorithmWrapper::SetAbsLayoutAlgorithm(const RefPtr<Kit::LayoutAlgorithm>& absLayoutAlgorithm)
{
    absLayoutAlgorithm_ = absLayoutAlgorithm;
}

void LayoutAlgorithm::SetHeightPercentSensitive(LayoutWrapper *layoutWrapper, bool value)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    layoutAlgorithmWrapper->SetPercentHeight(value);
}

void LayoutAlgorithm::SetWidthPercentSensitive(LayoutWrapper *layoutWrapper, bool value)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    layoutAlgorithmWrapper->SetPercentWidth(value);
}
void OverflowCollector::AccumulateFromWrapper(const RefPtr<LayoutWrapper>& child)
{
    CHECK_NULL_VOID(child);
    auto frameNode = AceType::DynamicCast<FrameNode>(child->GetHostNode());
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    bool hasSafeAreaProp = layoutProperty->IsIgnoreOptsValid() || frameNode->SelfExpansive();
    overflowCollectResult_.overflowDisabled |= hasSafeAreaProp;
    if (earlyBreakWhenDisabled_ && overflowCollectResult_.overflowDisabled) {
        stop_ = true;
        return;
    }
    auto geometryNode = child->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    UnionRect(overflowCollectResult_.totalChildFrameRect, geometryNode->GetMarginFrameRect());
}

bool LayoutAlgorithm::ShouldDoOverflowWork()
{
    return isOverflowWarningEnabled_ || FeatureParam::IsPageOverflowEnabled();
}

OverflowCollectResult LayoutAlgorithm::CollectOverflowFromFrameNode(
    FrameNode* hostNode, bool earlyBreakWhenDisabled)
{
    OverflowCollector collector(earlyBreakWhenDisabled);
    CHECK_NULL_RETURN(hostNode, collector.Result());
    int32_t childCount = hostNode->GetTotalChildCount();
    for (int32_t i = 0; i < childCount; i++) {
        auto child = hostNode->GetChildByIndex(i);
        CHECK_NULL_CONTINUE(child);
        if (child->IsOutOfLayout() || !child->IsActive()) {
            continue;
        }
        collector.AccumulateFromWrapper(child);
        if (collector.Stopped()) {
            break;
        }
    }
    return collector.Result();
}

bool LayoutAlgorithm::IsContentOverflow(LayoutWrapper* layoutWrapper, OverflowCollector& collector)
{
    if (!ShouldDoOverflowWork()) {
        return false;
    }
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, false);
    if (OVERFLOW_ENABLED_COMPONENTS.find(hostNode->GetTag()) == OVERFLOW_ENABLED_COMPONENTS.end()
            && hostNode->GetTag() != V2::ROW_ETS_TAG) {
        return false;
    }
    auto pattern = hostNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    const auto& vOverflowHandler = pattern->GetOrCreateVerticalOverflowHandler(
        AceType::WeakClaim(AceType::RawPtr(hostNode)));
    CHECK_NULL_RETURN(vOverflowHandler, false);
    const auto& result = collector.Result();
    vOverflowHandler->SetTotalChildFrameRect(result.totalChildFrameRect.value_or(RectF()));
    vOverflowHandler->SetOverflowDisabledFlag(result.overflowDisabled);
    FrameNode* host = AceType::RawPtr(hostNode);
    CHECK_NULL_RETURN(host, false);
    if (!isOverflowWarningEnabled_) {
        return false;
    }
    vOverflowHandler->CreateContentRect();
    return vOverflowHandler->IsOverflow();
}

void LayoutAlgorithm::HandleContentOverflow(LayoutWrapper* layoutWrapper)
{
    if (!FeatureParam::IsPageOverflowEnabled()) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    if (OVERFLOW_ENABLED_COMPONENTS.find(hostNode->GetTag()) == OVERFLOW_ENABLED_COMPONENTS.end()) {
        return;
    }
    auto pattern = hostNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    const auto &vOverflowHandler =
        pattern->GetOrCreateVerticalOverflowHandler(AceType::WeakClaim(AceType::RawPtr(hostNode)));
    CHECK_NULL_VOID(vOverflowHandler);
    
    vOverflowHandler->SetOverflowDisabledFlag(
        vOverflowHandler->IsOverflowDisabled() || hostNode->IsAncestorScrollable());
    vOverflowHandler->HandleContentOverflow();
}
} // namespace OHOS::Ace::NG