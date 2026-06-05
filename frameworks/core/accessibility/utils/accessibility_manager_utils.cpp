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
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "base/log/log_wrapper.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::NG {

// ============================================================================
// VirtualNodeContainerIdManager Implementation
// ============================================================================

VirtualNodeContainerIdManager& VirtualNodeContainerIdManager::GetInstance()
{
    static VirtualNodeContainerIdManager instance;
    return instance;
}

uint8_t VirtualNodeContainerIdManager::AllocateContainerId(const RefPtr<FrameNode>& containerNode)
{
    CHECK_NULL_RETURN(containerNode, INVALID_CONTAINER_ID);
    std::lock_guard<std::mutex> lock(mutex_);

    // Check if the FrameNode has already been allocated a container ID
    int64_t nodeAccessibilityId = containerNode->GetAccessibilityId();
    auto it = nodeToContainerMap_.find(nodeAccessibilityId);
    if (it != nodeToContainerMap_.end()) {
        // Already allocated, return the existing ID
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "ContainerId already allocated: %{public}d for node %{public}" PRId64,
            it->second, nodeAccessibilityId);
        return it->second;
    }

    // Find the next available ID
    uint8_t containerId = FindNextAvailableId();
    if (containerId == INVALID_CONTAINER_ID) {
        TAG_LOGE(AceLogTag::ACE_ACCESSIBILITY,
            "Failed to allocate containerId: no available IDs");
        return INVALID_CONTAINER_ID;
    }

    // Establish mapping relationship
    idPool_.set(containerId, true);
    containerNodeMap_[containerId] = WeakPtr<FrameNode>(containerNode);
    nodeToContainerMap_[nodeAccessibilityId] = containerId;
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
        "Allocated containerId: %{public}d for node %{public}" PRId64,
        containerId, nodeAccessibilityId);

    return containerId;
}

void VirtualNodeContainerIdManager::ReleaseContainerId(uint8_t containerId)
{
    if (containerId < MIN_CONTAINER_ID || containerId > MAX_CONTAINER_ID) {
        return;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = containerNodeMap_.find(containerId);
    if (it == containerNodeMap_.end()) {
        return;
    }

    // Get the AccessibilityId of the FrameNode
    auto node = it->second.Upgrade();
    if (node) {
        int64_t nodeAccessibilityId = node->GetAccessibilityId();
        nodeToContainerMap_.erase(nodeAccessibilityId);
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "Released containerId: %{public}d for node %{public}" PRId64,
            containerId, nodeAccessibilityId);
    }

    // Clear mapping and release the ID
    containerNodeMap_.erase(it);
    idPool_.set(containerId, false);
}

void VirtualNodeContainerIdManager::ReleaseContainerId(const RefPtr<FrameNode>& containerNode)
{
    CHECK_NULL_VOID(containerNode);

    uint8_t containerId = GetContainerId(containerNode);
    if (containerId != INVALID_CONTAINER_ID) {
        ReleaseContainerId(containerId);
    }
}

RefPtr<FrameNode> VirtualNodeContainerIdManager::GetContainerNode(uint8_t containerId) const
{
    if (containerId < MIN_CONTAINER_ID || containerId > MAX_CONTAINER_ID) {
        return nullptr;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    auto it = containerNodeMap_.find(containerId);
    if (it != containerNodeMap_.end()) {
        return it->second.Upgrade();
    }

    return nullptr;
}

uint8_t VirtualNodeContainerIdManager::GetContainerId(const RefPtr<FrameNode>& containerNode) const
{
    CHECK_NULL_RETURN(containerNode, INVALID_CONTAINER_ID);

    std::lock_guard<std::mutex> lock(mutex_);

    int64_t nodeAccessibilityId = containerNode->GetAccessibilityId();
    auto it = nodeToContainerMap_.find(nodeAccessibilityId);
    if (it != nodeToContainerMap_.end()) {
        return it->second;
    }

    return INVALID_CONTAINER_ID;
}

bool VirtualNodeContainerIdManager::IsVirtualNodeContainer(uint8_t containerId) const
{
    return containerId >= MIN_CONTAINER_ID && containerId <= MAX_CONTAINER_ID;
}

bool VirtualNodeContainerIdManager::IsVirtualNodeContainer(const RefPtr<FrameNode>& containerNode) const
{
    return GetContainerId(containerNode) != INVALID_CONTAINER_ID;
}

void VirtualNodeContainerIdManager::Clear()
{
    std::lock_guard<std::mutex> lock(mutex_);
    containerNodeMap_.clear();
    nodeToContainerMap_.clear();
    idPool_.reset();
    TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "VirtualNodeContainerIdManager cleared");
}

size_t VirtualNodeContainerIdManager::GetContainerCount() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return containerNodeMap_.size();
}

size_t VirtualNodeContainerIdManager::GetAvailableIdCount() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    size_t used = 0;
    for (size_t index = MIN_CONTAINER_ID; index <= MAX_CONTAINER_ID; index++) {
        if (idPool_.test(index)) {
            used++;
        }
    }
    return (MAX_CONTAINER_ID - MIN_CONTAINER_ID + 1) - used;
}

uint8_t VirtualNodeContainerIdManager::FindNextAvailableId()
{
    for (size_t index = MIN_CONTAINER_ID; index <= MAX_CONTAINER_ID; index++) {
        if (!idPool_.test(index)) {
            return static_cast<uint8_t>(index);
        }
    }
    return INVALID_CONTAINER_ID;
}

// ============================================================================
// VirtualNodeContainerIdManager Static Utility Methods Implementation
// ============================================================================

int64_t VirtualNodeContainerIdManager::EncodeVirtualNodeAccessibilityId(
    uint8_t containerId, int64_t componentId)
{
    // Preserve full 32-bit pattern of componentId (including sign bit) via unsigned cast
    uint64_t rawComponent = static_cast<uint64_t>(static_cast<uint32_t>(componentId));
    uint64_t containerIdShifted = static_cast<uint64_t>(containerId) << CONTAINER_ID_SHIFT;
    return static_cast<int64_t>(rawComponent | containerIdShifted);
}

void VirtualNodeContainerIdManager::DecodeAccessibilityId(
    int64_t accessibilityId, uint8_t& containerId, int64_t& componentId)
{
    containerId = ExtractContainerId(accessibilityId);
    componentId = ExtractComponentId(accessibilityId);
}

bool VirtualNodeContainerIdManager::IsVirtualNodeContainerId(int64_t accessibilityId)
{
    uint8_t containerId = ExtractContainerId(accessibilityId);
    return (containerId >= MIN_CONTAINER_ID) && (containerId <= MAX_CONTAINER_ID);
}

uint8_t VirtualNodeContainerIdManager::ExtractContainerId(int64_t accessibilityId)
{
    return static_cast<uint8_t>((static_cast<uint64_t>(accessibilityId) & CONTAINER_ID_MASK) >> CONTAINER_ID_SHIFT);
}

int64_t VirtualNodeContainerIdManager::ExtractComponentId(int64_t accessibilityId)
{
    // Sign-extend the lower 32 bits back to int64_t to restore the original componentId
    return static_cast<int64_t>(static_cast<int32_t>(static_cast<uint32_t>(
        static_cast<uint64_t>(accessibilityId) & COMPONENT_ID_MASK)));
}

int64_t VirtualNodeContainerIdManager::GetParentAccessibilityId(int64_t accessibilityId)
{
    // Clear container ID bits (bits 39-32)
    return static_cast<int64_t>(static_cast<uint64_t>(accessibilityId) & ~CONTAINER_ID_MASK);
}

// ============================================================================
// NextFocusRelationController Implementation
// ============================================================================

void NextFocusRelationController::RebuildTargetPrimaryForTarget(
    const std::string& targetInspectorId,
    TargetMap& targetMap,
    std::map<int64_t, NextFocusSourceEntry>& sourceMap,
    std::map<std::string, std::set<int64_t>>& targetSourcesMap)
{
    auto targetIt = targetSourcesMap.find(targetInspectorId);
    if (targetIt == targetSourcesMap.end() || targetIt->second.empty()) {
        targetMap.erase(targetInspectorId);
        return;
    }
    for (auto sourceAccessibilityId : targetIt->second) {
        auto sourceIt = sourceMap.find(sourceAccessibilityId);
        if (sourceIt == sourceMap.end()) {
            continue;
        }
        if (sourceIt->second.targetInspectorId != targetInspectorId) {
            continue;
        }
        targetMap[targetInspectorId] = { sourceAccessibilityId, sourceIt->second.descendantMode };
        return;
    }
    targetMap.erase(targetInspectorId);
}

void NextFocusRelationController::RemoveSourceRelationByAccessibilityId(
    int64_t sourceAccessibilityId,
    TargetMap& targetMap,
    std::map<int64_t, NextFocusSourceEntry>& sourceMap,
    std::map<std::string, std::set<int64_t>>& targetSourcesMap)
{
    auto sourceIt = sourceMap.find(sourceAccessibilityId);
    if (sourceIt == sourceMap.end()) {
        return;
    }
    auto oldTargetInspectorId = sourceIt->second.targetInspectorId;
    sourceMap.erase(sourceIt);
    auto targetIt = targetSourcesMap.find(oldTargetInspectorId);
    if (targetIt != targetSourcesMap.end()) {
        targetIt->second.erase(sourceAccessibilityId);
        if (targetIt->second.empty()) {
            targetSourcesMap.erase(targetIt);
        }
    }
    RebuildTargetPrimaryForTarget(oldTargetInspectorId, targetMap, sourceMap, targetSourcesMap);
}

void NextFocusRelationController::HandleExistingContext(
    std::map<int32_t, TargetMap>::iterator& targetMapIt,
    std::map<int32_t, std::map<int64_t, NextFocusSourceEntry>>::iterator& sourceMapIt,
    std::map<int32_t, std::map<std::string, std::set<int64_t>>>::iterator& targetSourcesIt,
    const std::string& nextFocusInspectorKey, int64_t sourceAccessibilityId, bool descendantMode)
{
    auto& targetMap = targetMapIt->second;
    auto& sourceMap = sourceMapIt->second;
    auto& targetSourcesMap = targetSourcesIt->second;

    RemoveSourceRelationByAccessibilityId(sourceAccessibilityId, targetMap, sourceMap, targetSourcesMap);
    if (nextFocusInspectorKey.empty()) {
        return;
    }
    sourceMap[sourceAccessibilityId] = { nextFocusInspectorKey, descendantMode };
    targetSourcesMap[nextFocusInspectorKey].insert(sourceAccessibilityId);
    targetMap[nextFocusInspectorKey] = { sourceAccessibilityId, descendantMode }; // latest source wins
}

void NextFocusRelationController::UpdateNextFocusIdMap(
    int32_t containerId, const std::string& nextFocusInspectorKey, int64_t sourceAccessibilityId, bool descendantMode)
{
    auto targetFindIt = nextFocusMapWithSubWindow_.find(containerId);
    auto sourceFindIt = nextFocusSourceMapWithSubWindow_.find(containerId);
    auto targetSourcesFindIt = nextFocusTargetSourcesWithSubWindow_.find(containerId);
    if (targetFindIt == nextFocusMapWithSubWindow_.end() &&
        sourceFindIt == nextFocusSourceMapWithSubWindow_.end() &&
        targetSourcesFindIt == nextFocusTargetSourcesWithSubWindow_.end() &&
        nextFocusInspectorKey.empty()) {
        return;
    }

    auto targetIt = nextFocusMapWithSubWindow_.try_emplace(containerId).first;
    auto sourceIt = nextFocusSourceMapWithSubWindow_.try_emplace(containerId).first;
    auto targetSourcesIt = nextFocusTargetSourcesWithSubWindow_.try_emplace(containerId).first;
    HandleExistingContext(
        targetIt, sourceIt, targetSourcesIt, nextFocusInspectorKey, sourceAccessibilityId, descendantMode);

    if (targetIt->second.empty() && sourceIt->second.empty() && targetSourcesIt->second.empty()) {
        nextFocusMapWithSubWindow_.erase(targetIt);
        nextFocusSourceMapWithSubWindow_.erase(containerId);
        nextFocusTargetSourcesWithSubWindow_.erase(containerId);
    }
}

bool NextFocusRelationController::GetNextFocusDescendantMode(int32_t containerId, const std::string& inspectorId) const
{
    if (inspectorId.empty()) {
        return false;
    }
    auto containerIt = nextFocusMapWithSubWindow_.find(containerId);
    if (containerIt == nextFocusMapWithSubWindow_.end()) {
        return false;
    }
    auto it = containerIt->second.find(inspectorId);
    if (it != containerIt->second.end()) {
        return it->second.descendantMode;
    }
    return false;
}

const NextFocusRelationController::TargetMap& NextFocusRelationController::GetTargetMap(int32_t containerId) const
{
    auto containerIt = nextFocusMapWithSubWindow_.find(containerId);
    if (containerIt == nextFocusMapWithSubWindow_.end()) {
        return emptyTargetMap_;
    }
    return containerIt->second;
}

// ============================================================================
// AccessibilityEventBlockerInAction Implementation
// ============================================================================

void AccessibilityEventBlockerInAction::AddBlockedEvent(int64_t actionId, AccessibilityEventType event)
{
    CHECK_EQUAL_VOID(actionId, -1);
    if (currentActionId_ == -1) {
        currentActionId_ = actionId;
    }
    if (currentActionId_ != actionId) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "AddBlockedEvent fail by currentActionId_ %{public}" PRId64
            " actionId: %{public}" PRId64, currentActionId_, actionId);
        return;
    }
    blockedEvents_.insert(static_cast<uint32_t>(event));
}

void AccessibilityEventBlockerInAction::SetBlockedEvents(int64_t actionId,
    const std::vector<AccessibilityEventType>& events)
{
    CHECK_EQUAL_VOID(actionId, -1);
    if (currentActionId_ == -1) {
        currentActionId_ = actionId;
    }
    if (currentActionId_ != actionId) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "SetBlockedEvents fail by currentActionId_ %{public}" PRId64
            " actionId: %{public}" PRId64, currentActionId_, actionId);
        return;
    }
    blockedEvents_.clear();
    blockedEvents_.reserve(events.size());
    
    for (const auto& event : events) {
        blockedEvents_.insert(static_cast<uint32_t>(event));
    }
}


bool AccessibilityEventBlockerInAction::ShouldBlock(int64_t actionId, AccessibilityEventType eventType) const
{
    CHECK_EQUAL_RETURN(actionId, -1, false);
    CHECK_NE_RETURN(actionId, currentActionId_, false);
    CHECK_NE_RETURN(blockedEvents_.find(static_cast<uint32_t>(eventType)), blockedEvents_.end(), true);
    return false;
}

void AccessibilityEventBlockerInAction::Reset()
{
    currentActionId_ = -1;
    blockedEvents_.clear();
}

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
    if (!ContainsPoint(x, y) && (children_.size() == 0)) {
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
    int32_t lastHoveringId = lastHovering ? lastHovering->GetNodeId() : -1;
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
