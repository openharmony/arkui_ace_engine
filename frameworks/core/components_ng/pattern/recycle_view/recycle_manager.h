/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECYCLE_VIEW_RECYCLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECYCLE_VIEW_RECYCLE_MANAGER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "core/common/resource/resource_configuration.h"

namespace OHOS::Ace::NG {
class CustomNodeBase;
// record config changes for recyled node.
struct RecycleNodeState {
    ConfigurationChange config;
    WeakPtr<CustomNodeBase> node;
    void MergeConfig(const ConfigurationChange& cfg)
    {
        config.MergeConfig(cfg);
    }
    RecycleNodeState(WeakPtr<CustomNodeBase>&& n) : node(std::move(n)) {}
};
// record recycled node id and mark recycle state
struct RecycleNodeInfo {
    int32_t elemtId = -1;
    bool hasBeenRecyled = false;
    void Recycle(int32_t id)
    {
        elemtId = id;
        hasBeenRecyled = true;
    }
    void Reuse()
    {
        elemtId = -1;
        hasBeenRecyled = false;
    }
};
class RecycleManager {
public:
    static void Push(int32_t elmtId, WeakPtr<CustomNodeBase>&& node);
    static void Pop(int32_t elmtId);
    static void Erase(int32_t elmtId);
    static void Notify(const ConfigurationChange& config);
    static void ClearAll();

private:
    void PushNode(int32_t elmtId, WeakPtr<CustomNodeBase>&& node);
    void ClearAllNodes();
    void PopNode(int32_t elmtId);
    void EraseNode(int32_t elmtId);
    void NotifyConfigurationChange(const ConfigurationChange& config);
    std::unordered_map<int32_t, std::unique_ptr<RecycleNodeState>> recyclePool_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECYCLE_VIEW_RECYCLE_MANAGER_H
