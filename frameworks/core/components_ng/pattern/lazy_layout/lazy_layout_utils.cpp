/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

static bool IsLazyLayoutScrollableContainer(const std::string& tag)
{
    return tag == V2::SCROLL_ETS_TAG || tag == V2::WATERFLOW_ETS_TAG || tag == V2::LIST_ETS_TAG;
}

bool LazyLayoutUtils::IsAllowedIntermediateNode(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, false);
    const auto& tag = node->GetTag();
    return tag == V2::COMMON_VIEW_ETS_TAG || tag == V2::NODE_CONTAINER_ETS_TAG ||
           tag == "BuilderProxyNode" || tag == V2::FLOW_ITEM_ETS_TAG ||
           tag == V2::LAZY_COLUMN_LAYOUT_ETS_TAG;
}

// FEAT-027: any node that owns a scroll context (ScrollablePattern) or is tagged as one of the lazy scroll
// containers is a hard boundary for the lazy ancestor search. The lazy viewport can only come from the nearest
// such boundary, and the search must never cross one (a crossed scroll boundary would source the viewport from
// the wrong scroll context or leave it undeliverable).
bool LazyLayoutUtils::IsScrollableBoundary(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, false);
    if (IsLazyLayoutScrollableContainer(node->GetTag())) {
        return true;
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetPattern<ScrollablePattern>() != nullptr;
}

bool LazyLayoutUtils::IsVerticalScrollableParent(const RefPtr<UINode>& node)
{
    return IsScrollableParent(node, Axis::VERTICAL);
}

bool LazyLayoutUtils::IsScrollableParent(const RefPtr<UINode>& node, Axis axis)
{
    CHECK_NULL_RETURN(node, false);
    if (!IsLazyLayoutScrollableContainer(node->GetTag())) {
        return false;
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetAxis() == axis;
}

void LazyLayoutUtils::ValidateLazyLayoutParent(
    const RefPtr<FrameNode>& host, const std::string& componentName)
{
    ValidateLazyLayoutParentWithAxis(host, componentName, Axis::VERTICAL);
}

void LazyLayoutUtils::ValidateLazyLayoutParentWithAxis(
    const RefPtr<FrameNode>& host, const std::string& componentName, Axis axis)
{
    CHECK_NULL_VOID(host);
    host->SetNeedLazyLayout(true);
    auto parent = host->GetParent();
    while (parent) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!parentFrameNode) {
            parent = parent->GetParent();
            continue;
        }
        const auto& parentTag = parent->GetTag();
        if (!IsScrollableBoundary(parent)) {
            // FEAT-027: any ordinary FrameNode between the lazy host and its scroll ancestor is a transparent
            // intermediate of the lazy path. Mark it so the viewport (viewPosRef) flows through its content
            // constraint, then keep searching upwards.
            parentFrameNode->SetNeedLazyLayout(true);
            parent = parent->GetParent();
            continue;
        }
        auto scrollable = parentFrameNode->GetPattern<ScrollablePattern>();
        if (!scrollable || !IsLazyLayoutScrollableContainer(parentTag)) {
            // A scroll context that cannot provide the lazy viewport is a boundary the search must not cross.
            LOGF_ABORT("%{public}s cannot be used under the %{public}s",
                componentName.c_str(), parentTag.c_str());
        }
        if (scrollable->GetAxis() == axis) {
            return;
        }
        LOGF_ABORT("%{public}s requires parent %{public}s to be %{public}s direction",
            componentName.c_str(), parentTag.c_str(), axis == Axis::VERTICAL ? "vertical" : "horizontal");
    }
    // Reached the tree root without any scrollable ancestor: no viewport can ever reach this host.
    LOGF_ABORT("%{public}s must be used inside a scrollable container", componentName.c_str());
}

bool LazyLayoutUtils::ValidateAndSetLazyLayoutParent(const RefPtr<FrameNode>& host, Axis axis)
{
    CHECK_NULL_RETURN(host, false);
    // Collect the intermediate chain first; it is marked only when a legal same-axis scroll ancestor exists,
    // so detached estimation paths never publish a lazy path that validation would later reject.
    std::vector<RefPtr<FrameNode>> intermediateChain;
    auto parent = host->GetParentFrameNode();
    while (parent) {
        if (IsScrollableParent(parent, axis)) {
            host->SetNeedLazyLayout(true);
            for (const auto& intermediate : intermediateChain) {
                intermediate->SetNeedLazyLayout(true);
            }
            return true;
        }
        if (IsScrollableBoundary(parent)) {
            // Scroll boundary that cannot provide this axis' viewport: never cross it while estimating.
            return false;
        }
        intermediateChain.emplace_back(parent);
        parent = parent->GetParentFrameNode();
    }
    return false;
}

bool LazyLayoutUtils::ShouldEstimateDetachedLazyLayout(const RefPtr<FrameNode>& host, Axis axis)
{
    CHECK_NULL_RETURN(host, false);
    if (host->IsOnMainTree()) {
        return false;
    }
    auto parent = host->GetParentFrameNode();
    if (parent) {
        return ValidateAndSetLazyLayoutParent(host, axis);
    }
    auto layoutProperty = host->GetLayoutProperty();
    return layoutProperty && layoutProperty->GetNeedLazyLayout();
}

LazyLayoutMeasureMode LazyLayoutUtils::ResolveMeasureMode(const RefPtr<FrameNode>& host, Axis axis,
    const std::optional<ViewPosReference>& viewPosRef, int32_t totalItemCount, int32_t lanes,
    bool hasMeasuredBaseline)
{
    if (totalItemCount <= std::max(lanes, 1)) {
        return LazyLayoutMeasureMode::NORMAL;
    }
    if (viewPosRef.has_value()) {
        if (hasMeasuredBaseline || viewPosRef->axis != axis ||
            viewPosRef->referenceEdge != ReferenceEdge::START || !viewPosRef->deadline.has_value()) {
            return LazyLayoutMeasureMode::NORMAL;
        }
        // mainSize is unknown on the first pass. For a START reference, zero is sufficient to decide whether the
        // parent's viewport plus its 0.5-screen predictive extent still reaches this host's leading edge.
        return GreatOrEqual(CalculateViewRange(viewPosRef.value(), 0.0f).end, 0.0f)
            ? LazyLayoutMeasureMode::ESTIMATE : LazyLayoutMeasureMode::NORMAL;
    }
    if (!ShouldEstimateDetachedLazyLayout(host, axis)) {
        return LazyLayoutMeasureMode::NORMAL;
    }
    return hasMeasuredBaseline ? LazyLayoutMeasureMode::SKIP : LazyLayoutMeasureMode::ESTIMATE;
}

int32_t LazyLayoutUtils::CalculateEstimateSampleCount(int32_t totalItemCount, int32_t lanes)
{
    if (totalItemCount <= 0) {
        return 0;
    }
    const int64_t laneCount = std::max(lanes, 1);
    const int64_t sampleCount = std::min<int64_t>(totalItemCount, laneCount * 2);
    return static_cast<int32_t>(sampleCount);
}

float LazyLayoutUtils::EstimateTotalMainSize(float averageMainSize, int32_t itemCount, float space)
{
    const int32_t count = std::max(itemCount, 0);
    return averageMainSize * static_cast<float>(count) + space * static_cast<float>(std::max(count - 1, 0));
}

ViewPosReference LazyLayoutUtils::CreateEstimateViewPosReference(Axis axis)
{
    return ViewPosReference {
        .viewPosStart = 0.0f,
        .viewPosEnd = 1.0f,
        .referencePos = 0.0f,
        .referenceEdge = ReferenceEdge::START,
        .axis = axis,
    };
}

bool IsInExtraTags(const std::string& tag, const std::vector<std::string>& extraAllowedTags)
{
    for (const auto& allowedTag : extraAllowedTags) {
        if (tag == allowedTag) {
            return true;
        }
    }
    return false;
}

std::optional<ViewPosReference> LazyLayoutUtils::GetViewPosReference(
    const RefPtr<FrameNode>& frameNode, const std::vector<std::string>& extraAllowedTags)
{
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    // FEAT-027: nodes marked needLazyLayout (the lazy host plus any intermediate FrameNode of its lazy path)
    // participate in the viewport chain; legacy whitelisted tags and caller-provided tags stay accepted so
    // pre-marking orderings keep working.
    if (!IsAllowedIntermediateNode(frameNode) && !IsInExtraTags(frameNode->GetTag(), extraAllowedTags)) {
        auto layoutProperty = frameNode->GetLayoutProperty();
        if (!layoutProperty || !layoutProperty->GetNeedLazyLayout()) {
            return std::nullopt;
        }
    }
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto geometry = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, std::nullopt);
    auto constraintOpt = geometry->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraintOpt, std::nullopt);
    auto& constraint = constraintOpt.value();
    if (constraint.viewPosRef.has_value()) {
        auto viewPosRef = constraint.viewPosRef.value();
        layoutProperty->ConstraintViewPosRef(viewPosRef);
        return viewPosRef;
    }
    auto viewPosRefOpt = GetViewPosReference(frameNode->GetAncestorNodeOfFrame(true), extraAllowedTags);
    CHECK_NULL_RETURN(viewPosRefOpt, std::nullopt);
    layoutProperty->ConstraintViewPosRef(viewPosRefOpt.value());
    return viewPosRefOpt;
}

RefPtr<LazyLayoutPattern> LazyLayoutUtils::GetLazyLayoutPattern(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    if (frameNode) {
        auto pattern = frameNode->GetPattern<LazyLayoutPattern>();
        if (pattern) {
            return pattern;
        }
        auto layoutProperty = frameNode->GetLayoutProperty();
        if (!layoutProperty || !layoutProperty->GetNeedLazyLayout()) {
            return nullptr;
        }
    }
    // FEAT-027: a marked intermediate may hold the lazy host in any child slot (ordinary siblings are allowed
    // before/between/after lazy nodes), so descend through every child instead of a first-child spine.
    for (const auto& child : node->GetChildren()) {
        auto pattern = GetLazyLayoutPattern(child);
        if (pattern) {
            return pattern;
        }
    }
    return nullptr;
}

bool LazyLayoutUtils::HasDirectWaterFlowAncestor(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto parent = frameNode->GetAncestorNodeOfFrame(true);
    while (parent) {
        if (parent->GetTag() == V2::FLOW_ITEM_ETS_TAG) {
            return false;
        }
        if (parent->GetTag() == V2::WATERFLOW_ETS_TAG) {
            return true;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return false;
}

std::optional<WaterFlowAncestorInfo> LazyLayoutUtils::FindWaterFlowAncestorInfo(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, std::nullopt);
    auto parent = frameNode->GetAncestorNodeOfFrame(true);
    WaterFlowAncestorInfo info;
    while (parent) {
        if (parent->GetTag() == V2::FLOW_ITEM_ETS_TAG) {
            info.throughFlowItem = true;
        }
        if (parent->GetTag() == V2::WATERFLOW_ETS_TAG) {
            info.node = parent;
            return info;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return std::nullopt;
}

} // namespace OHOS::Ace::NG
