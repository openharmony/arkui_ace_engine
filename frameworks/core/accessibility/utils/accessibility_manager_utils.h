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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_MANAGER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_MANAGER_UTILS_H

#include <map>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class FrameNode;
enum class AccessibilityHoverEventType;

class PageEventController {
public:
    void Add(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto containerId = pipeline->GetInstanceId();
        TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY,
            "AddToPageEventController containerId %{public}d, node %{public}"
            PRId64, containerId, frameNode->GetAccessibilityId());

        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            it->second[WeakPtr(frameNode)] = false;
        } else {
            controller_.emplace(
                containerId, std::map<WeakPtr<FrameNode>, bool> {{ WeakPtr(frameNode), false }});
        }
    }

    bool Delete(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_RETURN(frameNode, false);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, false);
        auto containerId = pipeline->GetInstanceId();
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            auto& controllerMap = it->second;
            auto mapIt = controllerMap.find(WeakPtr(frameNode));
            if (mapIt != controllerMap.end()) {
                controllerMap.erase(mapIt);
                return true;
            }
        }
        return false;
    }

    bool CheckNode(const RefPtr<FrameNode>& frameNode, bool deleteController)
    {
        CHECK_NULL_RETURN(frameNode, false);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, false);
        auto containerId = pipeline->GetInstanceId();
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            auto& controllerMap = it->second;
            auto mapIt = controllerMap.find(WeakPtr(frameNode));
            if (mapIt != controllerMap.end()) {
                if (deleteController) {
                    controllerMap.erase(mapIt);
                }
                if (IsHighPriorityNode(frameNode)) {
                    return true;
                }
                return CheckHighPriorityEmpty(containerId);
            }
        }
        return false;
    }

    bool IsHighPriorityNode(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_RETURN(frameNode, false);
        return frameNode->GetTag() == V2::WEB_ETS_TAG;
    }

    bool CheckHighPriorityEmpty(int32_t containerId)
    {
        auto it = controller_.find(containerId);
        if (it == controller_.end()) {
            return true;
        }
        auto& controllerMap = it->second;
        auto findResult = std::any_of(controllerMap.begin(), controllerMap.end(), [&](const auto& pair) {
            auto node = pair.first;
            auto frameNode = node.Upgrade();
            CHECK_NULL_RETURN(frameNode, false);
            return IsHighPriorityNode(frameNode);
        });
        return !findResult;
    }

    void DeleteLowPriorityNode(int32_t containerId)
    {
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            auto& controllerMap = it->second;
            for (auto mapIt = controllerMap.begin(); mapIt != controllerMap.end();) {
                auto node = mapIt->first;
                auto frameNode = node.Upgrade();
                if (frameNode && IsHighPriorityNode(frameNode)) {
                    ++mapIt;
                } else {
                    mapIt = controllerMap.erase(mapIt);
                }
            }
        }
    }

    void DeleteInstanceNodeAllWithPriority(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto containerId = pipeline->GetInstanceId();
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            if (IsHighPriorityNode(frameNode)) {
                controller_.erase(it);
            } else {
                DeleteLowPriorityNode(containerId);
            }
        }
    }

    void Update()
    {
        for (auto it = controller_.begin(); it != controller_.end(); ++it) {
            auto& controllerMap = it->second;
            for (auto mapIt = controllerMap.begin(); mapIt != controllerMap.end();) {
                auto node = mapIt->first;
                auto frameNode = node.Upgrade();
                if (!frameNode) {
                    mapIt = controllerMap.erase(mapIt);
                } else {
                    ++mapIt;
                }
            }
        }
    }

    bool CheckEmpty(int32_t containerId)
    {
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            auto& controllerMap = it->second;
            return controllerMap.size() == 0;
        }
        return true;
    }

    void DeleteInstanceControllerByInstance(int32_t containerId)
    {
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            controller_.erase(it);
        }
    }

    void AddAccessibilityEvent(const int32_t containerId, const int32_t pageId, AccessibilityEvent& event)
    {
        TimeStamp now = std::chrono::steady_clock::now();
        auto& eventList = pageEvent_[containerId];
        eventList.emplace_back(std::make_tuple(pageId, event, now));

        CleanExpiredEvents(containerId, now);
    }

    bool HasAnyAccessibilityEvent(const int32_t containerId) const
    {
        auto mapIt = pageEvent_.find(containerId);
        if (mapIt == pageEvent_.end()) {
            return false;
        }
        return !mapIt->second.empty();
    }

    bool HasAccessibilityEvent(const int32_t containerId, const int32_t pageId) const
    {
        auto mapIt = pageEvent_.find(containerId);
        if (mapIt == pageEvent_.end()) {
            return false;
        }
        const auto& eventList = mapIt->second;
        return std::any_of(eventList.begin(), eventList.end(),
            [pageId](const auto& tuple) {
                return std::get<0>(tuple) == pageId;
            });
    }

    void ReleaseAccessibilityEvent(
        const int32_t containerId,
        const int32_t pageId,
        std::list<std::pair<int32_t, AccessibilityEvent>>& eventListInput)
    {
        auto mapIt = pageEvent_.find(containerId);
        if (mapIt == pageEvent_.end()) {
            return;
        }
        auto& eventList = mapIt->second;
        for (auto it = eventList.begin(); it != eventList.end();) {
            if (std::get<0>(*it) == pageId) {
                eventListInput.emplace_back(std::make_pair(std::get<0>(*it), std::get<1>(*it)));
                it = eventList.erase(it);
            } else {
                ++it;
            }
        }

        if (eventList.empty()) {
            pageEvent_.erase(mapIt);
        }
    }

    void ReleaseAllAccessibilityEvent(
        const int32_t containerId,
        std::list<std::pair<int32_t,
        AccessibilityEvent>>& eventListInput)
    {
        auto mapIt = pageEvent_.find(containerId);
        if (mapIt == pageEvent_.end()) {
            return;
        }
        for (auto& tuple : mapIt->second) {
            eventListInput.emplace_back(std::make_pair(std::get<0>(tuple), std::get<1>(tuple)));
        }

        pageEvent_.erase(mapIt);
    }

private:
    void CleanExpiredEvents(int32_t containerId, TimeStamp now)
    {
        auto mapIt = pageEvent_.find(containerId);
        if (mapIt == pageEvent_.end()) {
            return;
        }
        auto& eventList = mapIt->second;
        auto isExpired = std::any_of(eventList.begin(), eventList.end(),
            [&](const auto& tuple) {
                uint64_t duration =
                    static_cast<uint64_t>(
                        std::chrono::duration_cast<std::chrono::milliseconds>(now - std::get<2>(tuple)).count());
                return duration > EXPIRATION_TIME;
            });
        if (isExpired) {
            TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
                "page cache event expired over %{public}d ms", EXPIRATION_TIME);
            pageEvent_.erase(mapIt);
            DeleteInstanceControllerByInstance(containerId); // remove controller
        }
    }

    static const int EXPIRATION_TIME = 5000; // 5s
    std::map<int32_t, std::map<WeakPtr<FrameNode>, bool>> controller_;
    // tuple with (pageId, event, timestamp) in different containerId
    std::map<int32_t, std::list<std::tuple<int32_t, AccessibilityEvent, TimeStamp>>> pageEvent_;
};

class HoverTransparentCallbackController {
public:
    bool AddToHoverTransparentCallbackList(const RefPtr<FrameNode>& frameNode)
    {
        UpdateHoverTransparentCallbackList();
        CHECK_NULL_RETURN(frameNode, false);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, false);
        auto containerId = pipeline->GetInstanceId();
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            auto& controllerList = it->second;
            for (const auto& nodeWptr : controllerList) {
                auto node = nodeWptr.Upgrade();
                if (node == nullptr) {
                    continue;
                }
                if (node->GetAccessibilityId() == frameNode->GetAccessibilityId()) {
                    return false;
                }
            }
            it->second.emplace_back(WeakPtr(frameNode));
        } else {
            controller_.emplace(
                containerId, std::list<WeakPtr<FrameNode>> { WeakPtr(frameNode) });
        }
        return true;
    }

    void UpdateHoverTransparentCallbackList()
    {
        for (auto it = controller_.begin(); it != controller_.end(); ++it) {
            auto& controllerList = it->second;
            for (auto controllerListIt = controllerList.begin(); controllerListIt != controllerList.end();) {
                auto node = (*controllerListIt).Upgrade();
                if (!node) {
                    controllerListIt = controllerList.erase(controllerListIt);
                } else {
                    ++controllerListIt;
                }
            }
        }
    }

    bool IsInHoverTransparentCallbackList(const RefPtr<FrameNode>& frameNode)
    {
        UpdateHoverTransparentCallbackList();
        CHECK_NULL_RETURN(frameNode, false);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, false);
        auto containerId = pipeline->GetInstanceId();
        auto it = controller_.find(containerId);
        if (it == controller_.end()) {
            return false;
        }
        auto& controllerList = it->second;
        for (const auto& nodeWptr : controllerList) {
            auto node = nodeWptr.Upgrade();
            if (!node) {
                continue;
            }
            if (node->GetAccessibilityId() == frameNode->GetAccessibilityId()) {
                return true;
            }
        }
        return false;
    }

    bool CheckHoverTransparentCallbackListEmpty(int32_t containerId)
    {
        UpdateHoverTransparentCallbackList();
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            return it->second.empty();
        }
        return true;
    }

private:
    std::map<int32_t, std::list<WeakPtr<FrameNode>>> controller_;
};

class NextFocusRelationController {
public:
    struct NextFocusMapEntry {
        int64_t sourceAccessibilityId = -1;
        bool descendantMode = false;
    };

    struct NextFocusSourceEntry {
        std::string targetInspectorId;
        bool descendantMode = false;
    };

    using TargetMap = std::map<std::string, NextFocusMapEntry>;

    void UpdateNextFocusIdMap(int32_t containerId,
        const std::string& nextFocusInspectorKey, int64_t sourceAccessibilityId, bool descendantMode);

    bool GetNextFocusDescendantMode(int32_t containerId, const std::string& inspectorId) const;

    const TargetMap& GetTargetMap(int32_t containerId) const;

    size_t GetContainerCount() const
    {
        return nextFocusMapWithSubWindow_.size();
    }

private:
    void RebuildTargetPrimaryForTarget(
        const std::string& targetInspectorId, TargetMap& targetMap,
        std::map<int64_t, NextFocusSourceEntry>& sourceMap,
        std::map<std::string, std::set<int64_t>>& targetSourcesMap);

    void RemoveSourceRelationByAccessibilityId(
        int64_t sourceAccessibilityId, TargetMap& targetMap,
        std::map<int64_t, NextFocusSourceEntry>& sourceMap,
        std::map<std::string, std::set<int64_t>>& targetSourcesMap);

    void HandleExistingContext(
        std::map<int32_t, TargetMap>::iterator& targetMapIt,
        std::map<int32_t, std::map<int64_t, NextFocusSourceEntry>>::iterator& sourceMapIt,
        std::map<int32_t, std::map<std::string, std::set<int64_t>>>::iterator& targetSourcesIt,
        const std::string& nextFocusInspectorKey, int64_t sourceAccessibilityId, bool descendantMode);

    // targetInspectorId -> primary source info (used by prev-focus lookup and descendantMode query by target)
    std::map<int32_t, TargetMap> nextFocusMapWithSubWindow_;
    // sourceAccessibilityId -> source->target edge info
    std::map<int32_t, std::map<int64_t, NextFocusSourceEntry>> nextFocusSourceMapWithSubWindow_;
    // targetInspectorId -> set of sourceAccessibilityId that point to this target
    std::map<int32_t, std::map<std::string, std::set<int64_t>>> nextFocusTargetSourcesWithSubWindow_;
    TargetMap emptyTargetMap_;
};

class AccessibilityEventBlockerInAction {
public:
    // 构造函数
    AccessibilityEventBlockerInAction() = default;
    ~AccessibilityEventBlockerInAction() = default;
    void AddBlockedEvent(int64_t actionId, AccessibilityEventType event);
    void SetBlockedEvents(int64_t actionId,
        const std::vector<AccessibilityEventType>& events);
    bool ShouldBlock(int64_t actionId, AccessibilityEventType eventType) const;
    void Reset();

private:
    int64_t currentActionId_ = -1;
    std::unordered_set<uint32_t> blockedEvents_;
};

class VirtualNodeContainerIdManager {
public:
    static VirtualNodeContainerIdManager& GetInstance();

    // Allocate container ID. Return value: 1-255 on success, 0 on failure
    uint8_t AllocateContainerId(const RefPtr<FrameNode>& containerNode);

    // Release container ID
    void ReleaseContainerId(uint8_t containerId);

    // Release container ID by FrameNode
    void ReleaseContainerId(const RefPtr<FrameNode>& containerNode);

    // Find FrameNode by container ID
    RefPtr<FrameNode> GetContainerNode(uint8_t containerId) const;

    // Find container ID by FrameNode. Return value: 1-255 if found, 0 if not found
    uint8_t GetContainerId(const RefPtr<FrameNode>& containerNode) const;

    // Check whether the given ID belongs to a virtual node container
    bool IsVirtualNodeContainer(uint8_t containerId) const;

    // Check whether the given FrameNode is a virtual node container
    bool IsVirtualNodeContainer(const RefPtr<FrameNode>& containerNode) const;

    // Clear all mappings
    void Clear();

    // Get statistics
    size_t GetContainerCount() const;
    size_t GetAvailableIdCount() const;
    
    // Static utility methods: ID encoding / decoding

    /* Encode accessibility ID for virtual node container.
     * containerId: container ID (1-255)
     * componentId: component ID (lower 32 bits of parent FrameNode's accessibility ID)
     * Return: complete 64-bit accessibility ID
     */
    static int64_t EncodeVirtualNodeAccessibilityId(uint8_t containerId, int64_t componentId);

    // Decode accessibility ID to extract container ID and component ID
    static void DecodeAccessibilityId(int64_t accessibilityId, uint8_t& containerId, int64_t& componentId);

    // Check whether the accessibility ID belongs to a virtual node container
    static bool IsVirtualNodeContainerId(int64_t accessibilityId);

    // Extract container ID from accessibility ID
    static uint8_t ExtractContainerId(int64_t accessibilityId);

    // Extract component ID from accessibility ID (clear container ID bits)
    static int64_t ExtractComponentId(int64_t accessibilityId);

    // Get parent FrameNode's full accessibility ID (clear container ID bits)
    static int64_t GetParentAccessibilityId(int64_t accessibilityId);

private:
    VirtualNodeContainerIdManager() = default;
    ~VirtualNodeContainerIdManager() = default;
    
    // Disallow copy and assignment
    VirtualNodeContainerIdManager(const VirtualNodeContainerIdManager&) = delete;
    VirtualNodeContainerIdManager& operator=(const VirtualNodeContainerIdManager&) = delete;

    // Find next available container ID
    uint8_t FindNextAvailableId();

    // Container ID range
    static constexpr uint8_t MIN_CONTAINER_ID = 1;
    static constexpr uint8_t MAX_CONTAINER_ID = 255;
    static constexpr uint8_t INVALID_CONTAINER_ID = 0;

    static constexpr size_t CONTAINER_ID_POOL_SIZE = 256;

    // ID encoding constants
    // Bit 39-32: containerId (uint8)
    // Bit 31-0: componentId (int32)
    // To avoid truncating componentId's sign bit, encode and decode via unsigned cast.
    static constexpr uint64_t CONTAINER_ID_MASK = 0x000000FF00000000ULL;
    static constexpr int CONTAINER_ID_SHIFT = 32;
    static constexpr uint64_t COMPONENT_ID_MASK = 0x00000000FFFFFFFFULL;

    // Member variables
    mutable std::mutex mutex_;

    std::bitset<CONTAINER_ID_POOL_SIZE> idPool_;

    // Container ID to FrameNode mapping
    std::unordered_map<uint8_t, WeakPtr<FrameNode>> containerNodeMap_;

    // FrameNode accessibility ID to container ID mapping
    std::unordered_map<int64_t, uint8_t> nodeToContainerMap_;
};

class VirtualAccessibilityNode : public CustomAccessibilityProperty {
    DECLARE_ACE_TYPE(VirtualAccessibilityNode, CustomAccessibilityProperty);
public:
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
    int32_t nodeId_ = -1;
    NG::RectT<int32_t> rect_;
    std::vector<RefPtr<VirtualAccessibilityNode>> children_;
    WeakPtr<VirtualAccessibilityNode> parent_;
    WeakPtr<VirtualAccessibilityNode> lastHovering_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_MANAGER_UTILS_H
