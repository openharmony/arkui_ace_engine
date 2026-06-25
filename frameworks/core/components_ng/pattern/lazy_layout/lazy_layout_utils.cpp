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
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

bool LazyLayoutUtils::IsAllowedIntermediateNode(const RefPtr<UINode>& node)
{
    CHECK_NULL_RETURN(node, false);
    const auto& tag = node->GetTag();
    return tag == V2::COMMON_VIEW_ETS_TAG || tag == V2::NODE_CONTAINER_ETS_TAG ||
           tag == "BuilderProxyNode" || tag == V2::FLOW_ITEM_ETS_TAG ||
           tag == V2::LAZY_COLUMN_LAYOUT_ETS_TAG;
}

bool LazyLayoutUtils::IsVerticalScrollableParent(const RefPtr<UINode>& node)
{
    return IsScrollableParent(node, Axis::VERTICAL);
}

bool LazyLayoutUtils::IsScrollableParent(const RefPtr<UINode>& node, Axis axis)
{
    CHECK_NULL_RETURN(node, false);
    const auto& tag = node->GetTag();
    if (tag != V2::SCROLL_ETS_TAG && tag != V2::WATERFLOW_ETS_TAG && tag != V2::LIST_ETS_TAG) {
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
        auto frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            parent = parent->GetParent();
            continue;
        }
        if (IsAllowedIntermediateNode(parent)) {
            frameNode->SetNeedLazyLayout(true);
            parent = parent->GetParent();
            continue;
        }
        if (IsScrollableParent(parent, axis)) {
            return;
        }
        LOGF_ABORT("%{public}s cannot be used under the %{public}s",
            componentName.c_str(), parent->GetTag().c_str());
    }
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
    if (!IsAllowedIntermediateNode(frameNode) && !IsInExtraTags(frameNode->GetTag(), extraAllowedTags)) {
        return std::nullopt;
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
