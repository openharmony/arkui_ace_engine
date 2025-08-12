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

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class FrameNode;

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
                return true;
            }
        }
        return false;
    }

    void DeleteInstanceNodeAll(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        auto pipeline = frameNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto containerId = pipeline->GetInstanceId();
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            auto& controllerMap = it->second;
            for (auto mapIt = controllerMap.begin(); mapIt != controllerMap.end();) {
                if (WeakPtr(frameNode) == mapIt->first) {
                    mapIt = controllerMap.erase(mapIt);
                } else {
                    ++mapIt;
                }
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

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_MANAGER_UTILS_H
