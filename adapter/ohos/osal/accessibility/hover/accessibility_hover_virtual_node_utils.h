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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_HOVER_ACCESSIBILITY_HOVER_VIRTUAL_NODE_UTILS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_HOVER_ACCESSIBILITY_HOVER_VIRTUAL_NODE_UTILS_H

#include <functional>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/property/accessibility_property.h"

namespace OHOS::Ace::NG {

class FrameNode;
enum class AccessibilityHoverEventType;

class VirtualAccessibilityNode : public CustomAccessibilityProperty {
    DECLARE_ACE_TYPE(VirtualAccessibilityNode, CustomAccessibilityProperty);
public:
    static constexpr int32_t INVALID_NODE_ID = -1;

    VirtualAccessibilityNode() = default;
    virtual ~VirtualAccessibilityNode() = default;

    // Set node ID
    void SetNodeId(int32_t nodeId)
    {
        nodeId_ = nodeId;
    }

    // Get node ID
    int32_t GetNodeId() const
    {
        return nodeId_;
    }

    void SetAccessibilityFocused(bool focused)
    {
        isAccessibilityFocused_ = focused;
    }

    bool GetAccessibilityFocused() const
    {
        return isAccessibilityFocused_;
    }

    // Set layout rect
    void SetRect(const NG::RectT<int32_t>& rect);

    // Set layout rect by left, top, width, height
    void SetRect(int32_t left, int32_t top, int32_t width, int32_t height);

    // Get layout rect
    const NG::RectT<int32_t>& GetRect() const;

    // Get position and size
    int32_t GetLeft() const { return rect_.Left(); }
    int32_t GetTop() const { return rect_.Top(); }
    int32_t GetWidth() const { return rect_.Width(); }
    int32_t GetHeight() const { return rect_.Height(); }
    int32_t GetRight() const { return rect_.Right(); }
    int32_t GetBottom() const { return rect_.Bottom(); }

    // Check whether the point is inside the node
    bool ContainsPoint(int32_t x, int32_t y) const;

    // Check whether this rect intersects with another
    bool Intersects(const NG::RectT<int32_t>& other) const;

    // Hit test: find virtual node by coordinates (returns the last matching child via right node)
    RefPtr<VirtualAccessibilityNode> HitTest(int32_t x, int32_t y) const;

    // Hit test with float coordinates
    RefPtr<VirtualAccessibilityNode> HitTest(float x, float y) const;

    // Hit test with PointF
    RefPtr<VirtualAccessibilityNode> HitTest(const NG::PointF& point) const;

    // Get global bounding rect (accounting for parent offset)
    NG::RectT<int32_t> GetGlobalRect() const;

    // Find node by coordinates (returns the last matching child via right node)
    RefPtr<VirtualAccessibilityNode> FindNodeByPoint(int32_t x, int32_t y) const;

    // Add child node
    void AddChild(const RefPtr<VirtualAccessibilityNode>& child);

    // Remove child node
    void RemoveChild(const RefPtr<VirtualAccessibilityNode>& child);

    // Clear all child nodes
    void ClearChildren();

    // Check whether the node has children
    bool HasChildren() const;

    // Get child count
    size_t GetChildCount() const;

    // Get child node at index
    RefPtr<VirtualAccessibilityNode> GetChild(size_t index) const;

    // Get all child nodes
    const std::vector<RefPtr<VirtualAccessibilityNode>>& GetChildren() const;

    // Get parent node
    RefPtr<VirtualAccessibilityNode> GetParent() const;

    // Find child node (depth-first search)
    RefPtr<VirtualAccessibilityNode> FindChild(
        const std::function<bool(const RefPtr<VirtualAccessibilityNode>&)>& predicate) const;

    RefPtr<VirtualAccessibilityNode> FindNodeById(int32_t nodeId) const;

    // Traverse all child nodes (depth-first)
    void TraverseChildren(const std::function<void(const RefPtr<VirtualAccessibilityNode>&)>& visitor) const;

    void OnAccessibilityHover(
        const PointF& point, AccessibilityHoverEventType eventType, const RefPtr<FrameNode>& containerNode);

private:
    int32_t nodeId_ = INVALID_NODE_ID;
    NG::RectT<int32_t> rect_;
    std::vector<RefPtr<VirtualAccessibilityNode>> children_;
    WeakPtr<VirtualAccessibilityNode> parent_;
    WeakPtr<VirtualAccessibilityNode> lastHovering_;
    bool isAccessibilityFocused_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_HOVER_ACCESSIBILITY_HOVER_VIRTUAL_NODE_UTILS_H
