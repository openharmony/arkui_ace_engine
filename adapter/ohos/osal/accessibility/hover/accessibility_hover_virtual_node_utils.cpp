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

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_virtual_node_utils.h"
#include "adapter/ohos/osal/accessibility/hover/accessibility_hover_virtual_node_utils.h"

#include "base/log/log_wrapper.h"
#include "core/accessibility/accessibility_constants.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/accessibility/utils/accessibility_manager_utils.h"
#include "core/components_ng/property/accessibility_property.h"

namespace {
std::string GetAddChildCycleStr(const std::vector<int32_t>& chain, int32_t startNodeId, int32_t endNodeId)
{
    std::string cycleStr = std::to_string(startNodeId);
    for (auto it = chain.rbegin(); it != chain.rend(); it++) {
        cycleStr += " -> " + std::to_string(*it);
    }
    cycleStr += " -> " + std::to_string(endNodeId);
    cycleStr += " -> (back to " + std::to_string(startNodeId) + ")";
    return cycleStr;
}
} // namespace

namespace OHOS::Ace::NG {

// ============================================================================
// VirtualAccessibilityNode Implementation
// ============================================================================

void VirtualAccessibilityNode::SetRect(const NG::RectT<int32_t>& rect)
{
    rect_ = rect;
}

void VirtualAccessibilityNode::SetRect(int32_t left, int32_t top, int32_t width, int32_t height)
{
    rect_.SetLeft(left);
    rect_.SetTop(top);
    rect_.SetWidth(width);
    rect_.SetHeight(height);
}

const NG::RectT<int32_t>& VirtualAccessibilityNode::GetRect() const
{
    return rect_;
}

bool VirtualAccessibilityNode::ContainsPoint(int32_t x, int32_t y) const
{
    return rect_.IsInRegion(NG::PointT<int32_t>(x, y));
}

bool VirtualAccessibilityNode::Intersects(const NG::RectT<int32_t>& other) const
{
    return rect_.IsIntersectWith(other);
}

bool VirtualAccessibilityNode::CanAccessibilityFocus(
    const RefPtr<VirtualAccessibilityNode>& node, const RefPtr<NG::FrameNode>& containerNode) const
{
    CHECK_NULL_RETURN(node, false);
    CHECK_NULL_RETURN(containerNode, false);

    auto client = Accessibility::AccessibilitySystemAbilityClient::GetInstance();
    CHECK_NULL_RETURN(client, false);

    int64_t virtualNodeAccessibilityId = NG::VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(
        NG::VirtualNodeContainerIdManager::GetInstance().GetContainerId(containerNode), node->GetNodeId());
    auto virtualCheckNode = std::make_shared<Framework::VirtualAccessibilityNodeRulesCheckNode>(
        node, virtualNodeAccessibilityId, containerNode);
    bool isReadable = false;
    auto checkResult = client->CheckNodeIsReadable(virtualCheckNode, isReadable);
    CHECK_NE_RETURN(checkResult, Accessibility::RET_OK, false);
    return isReadable;
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::HitTest(int32_t x, int32_t y) const
{
    if (!ContainsPoint(x, y) && children_.empty()) {
        return nullptr;
    }

    for (auto it = children_.rbegin(); it != children_.rend(); ++it) {
        if (*it) {
            auto result = (*it)->HitTest(x, y);
            if (result) {
                return result;
            }
        }
    }

    return ContainsPoint(x, y) ? AceType::Claim(const_cast<VirtualAccessibilityNode*>(this)) : nullptr;
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::HitTest(float x, float y) const
{
    return HitTest(static_cast<int32_t>(x), static_cast<int32_t>(y));
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::HitTest(const NG::PointF& point) const
{
    return HitTest(static_cast<int32_t>(point.GetX()), static_cast<int32_t>(point.GetY()));
}

void VirtualAccessibilityNode::OnAccessibilityHover(
    const PointF& point, AccessibilityHoverEventType eventType, const RefPtr<FrameNode>& containerNode)
{
    CHECK_NULL_VOID(containerNode);
    if (eventType == AccessibilityHoverEventType::ENTER) {
        lastHovering_ = nullptr;
    }
    auto hitNode = HitTest(point);
    auto lastHovering = lastHovering_.Upgrade();
    int32_t lastHoveringId = lastHovering ? lastHovering->GetNodeId() : INVALID_NODE_ID;
    if (lastHovering && hitNode != lastHovering) {
        int64_t lastVirtualNodeAccessibilityId = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(
            NG::VirtualNodeContainerIdManager::GetInstance().GetContainerId(containerNode), lastHovering->GetNodeId());
        containerNode->OnAccessibilityEventForVirtualNode(
            AccessibilityEventType::HOVER_EXIT_EVENT, lastVirtualNodeAccessibilityId);
    }
    if (hitNode && hitNode->GetNodeId() != lastHoveringId) {
        int64_t hitVirtualNodeAccessibilityId = VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(
            NG::VirtualNodeContainerIdManager::GetInstance().GetContainerId(containerNode), hitNode->GetNodeId());
        containerNode->OnAccessibilityEventForVirtualNode(
            AccessibilityEventType::HOVER_ENTER_EVENT, hitVirtualNodeAccessibilityId);
    }
    lastHovering_ = hitNode;
}

NG::RectT<int32_t> VirtualAccessibilityNode::GetGlobalRect() const
{
    auto globalRect = rect_;
    auto parent = GetParent();
    while (parent) {
        auto parentRect = parent->GetRect();
        globalRect.SetLeft(globalRect.Left() + parentRect.Left());
        globalRect.SetTop(globalRect.Top() + parentRect.Top());
        parent = parent->GetParent();
    }
    return globalRect;
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::FindNodeByPoint(int32_t x, int32_t y) const
{
    if (!ContainsPoint(x, y)) {
        return nullptr;
    }

    RefPtr<VirtualAccessibilityNode> lastHit = nullptr;
    for (const auto& child : children_) {
        if (child) {
            auto result = child->FindNodeByPoint(x, y);
            if (result) {
                lastHit = result;
            }
        }
    }

    return lastHit ? lastHit : AceType::Claim(const_cast<VirtualAccessibilityNode*>(this));
}

bool VirtualAccessibilityNode::AddChild(const RefPtr<VirtualAccessibilityNode>& child)
{
    CHECK_NULL_RETURN(child, false);

    // Case 1: child is this.
    if (AceType::RawPtr(child) == this) {
        TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
            "VirtualAccessibilityNode AddChild reject self-reference, nodeId: %{public}d", nodeId_);
        return false;
    }

    // Case 2: this is already an ancestor of child.
    {
        std::vector<int32_t> chainIfThisIsAncestorOfChild;
        for (auto ancestor = child->parent_.Upgrade(); ancestor; ancestor = ancestor->parent_.Upgrade()) {
            chainIfThisIsAncestorOfChild.push_back(ancestor->nodeId_);
            if (AceType::RawPtr(ancestor) != this) {
                continue;
            }
            std::string cycle = GetAddChildCycleStr(chainIfThisIsAncestorOfChild, nodeId_, child->nodeId_);
            TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
                "VirtualAccessibilityNode AddChild reject cycle, nodeId: %{public}d, cycle: %{public}s",
                nodeId_, cycle.c_str());
            return false;
        }
    }

    // Case 3: child is already an ancestor of this.
    {
        std::vector<int32_t> chainIfChildIsAncestorOfThis;
        for (auto selfAncestor = parent_.Upgrade(); selfAncestor; selfAncestor = selfAncestor->parent_.Upgrade()) {
            chainIfChildIsAncestorOfThis.push_back(selfAncestor->nodeId_);
            if (AceType::RawPtr(selfAncestor) != AceType::RawPtr(child)) {
                continue;
            }
            std::string cycle = GetAddChildCycleStr(chainIfChildIsAncestorOfThis, child->nodeId_, nodeId_);
            TAG_LOGW(AceLogTag::ACE_ACCESSIBILITY,
                "VirtualAccessibilityNode AddChild reject cycle, nodeId: %{public}d, cycle: %{public}s",
                nodeId_, cycle.c_str());
            return false;
        }
    }

    child->parent_ = AceType::WeakClaim(this);
    children_.push_back(child);
    return true;
}

void VirtualAccessibilityNode::RemoveChild(const RefPtr<VirtualAccessibilityNode>& child)
{
    CHECK_NULL_VOID(child);
    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        (*it)->parent_.Reset();
        children_.erase(it);
    }
}

void VirtualAccessibilityNode::ClearChildren()
{
    for (auto& child : children_) {
        if (child) {
            child->parent_.Reset();
        }
    }
    children_.clear();
}

bool VirtualAccessibilityNode::HasChildren() const
{
    return !children_.empty();
}

size_t VirtualAccessibilityNode::GetChildCount() const
{
    return children_.size();
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::GetChild(size_t index) const
{
    if (index >= children_.size()) {
        return nullptr;
    }
    return children_[index];
}

const std::vector<RefPtr<VirtualAccessibilityNode>>& VirtualAccessibilityNode::GetChildren() const
{
    return children_;
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::GetParent() const
{
    return parent_.Upgrade();
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::FindChild(
    const std::function<bool(const RefPtr<VirtualAccessibilityNode>&)>& predicate) const
{
    for (const auto& child : children_) {
        CHECK_NULL_CONTINUE(child);
        if (predicate(child)) {
            return child;
        }
        auto result = child->FindChild(predicate);
        if (result) {
            return result;
        }
    }
    return nullptr;
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::FindNodeById(int32_t nodeId) const
{
    if (nodeId_ == nodeId) {
        return AceType::Claim(const_cast<VirtualAccessibilityNode*>(this));
    }
    for (const auto& child : children_) {
        if (child) {
            auto result = child->FindNodeById(nodeId);
            if (result) {
                return result;
            }
        }
    }
    return nullptr;
}

void VirtualAccessibilityNode::TraverseChildren(
    const std::function<void(const RefPtr<VirtualAccessibilityNode>&)>& visitor) const
{
    for (const auto& child : children_) {
        if (child) {
            visitor(child);
            child->TraverseChildren(visitor);
        }
    }
}

RefPtr<VirtualAccessibilityNode> VirtualAccessibilityNode::CloneTree() const
{
    auto root = AceType::MakeRefPtr<VirtualAccessibilityNode>();
    CHECK_NULL_RETURN(root, nullptr);

    root->nodeId_ = nodeId_;
    root->SetText(GetText());
    root->SetAccessibilityText(GetAccessibilityText());
    root->SetAccessibilityLevel(GetAccessibilityLevel());
    root->SetAccessibilityGroup(GetAccessibilityGroup());
    root->SetRole(GetRole());
    root->SetAccessibilityRole(GetAccessibilityRole());
    root->SetCheckable(GetCheckable());
    root->SetChecked(GetChecked());
    root->SetEnabled(GetEnabled());
    root->SetSelected(GetSelected());
    root->SetClickable(GetClickable());
    root->rect_ = rect_;

    for (const auto& child : children_) {
        CHECK_NULL_CONTINUE(child);
        auto childClone = child->CloneTree();
        CHECK_NULL_CONTINUE(childClone);
        root->AddChild(childClone);
    }

    return root;
}

} // namespace OHOS::Ace::NG
