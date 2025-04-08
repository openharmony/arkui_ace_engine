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
        auto it = controller_.find(containerId);
        if (it != controller_.end()) {
            it->second[WeakPtr(frameNode)] = false;
        } else {
            controller_.emplace(
                containerId, std::map<WeakPtr<FrameNode>, bool> {{ WeakPtr(frameNode), false }});
        }
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

private:
    std::map<int32_t, std::map<WeakPtr<FrameNode>, bool>> controller_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_MANAGER_UTILS_H
