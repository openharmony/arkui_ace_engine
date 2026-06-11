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

#include "adapter/ohos/osal/accessibility/hover/accessibility_hover_virtual_node_utils.h"

#include "base/log/log_wrapper.h"
#include "core/accessibility/accessibility_constants.h"
#include "core/accessibility/utils/accessibility_manager_utils.h"

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

void VirtualAccessibilityNode::AddChild(const RefPtr<VirtualAccessibilityNode>& child)
{
    CHECK_NULL_VOID(child);
    child->parent_ = AceType::WeakClaim(this);
    children_.push_back(child);
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

} // namespace OHOS::Ace::NG
