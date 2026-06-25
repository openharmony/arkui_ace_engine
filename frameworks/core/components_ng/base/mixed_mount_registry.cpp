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

#include "core/components_ng/base/mixed_mount_registry.h"

#include <mutex>
#include <unordered_map>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
namespace {
std::unordered_map<uint64_t, WeakPtr<FrameNode>>& MixedChildParentMap()
{
    static std::unordered_map<uint64_t, WeakPtr<FrameNode>> mixedChildParentMap;
    return mixedChildParentMap;
}

std::mutex& MixedRegistryMutex()
{
    static std::mutex mutex;
    return mutex;
}
} // namespace

void MixedMountRegistry::RegisterChild(uint64_t childRsNodeId, const WeakPtr<FrameNode>& parent)
{
    std::lock_guard<std::mutex> lock(MixedRegistryMutex());
    MixedChildParentMap()[childRsNodeId] = parent;
}

void MixedMountRegistry::UnregisterChild(uint64_t childRsNodeId)
{
    std::lock_guard<std::mutex> lock(MixedRegistryMutex());
    MixedChildParentMap().erase(childRsNodeId);
}

RefPtr<FrameNode> MixedMountRegistry::GetParent(uint64_t childRsNodeId)
{
    std::lock_guard<std::mutex> lock(MixedRegistryMutex());
    auto iter = MixedChildParentMap().find(childRsNodeId);
    return iter == MixedChildParentMap().end() ? nullptr : iter->second.Upgrade();
}

void MixedMountRegistry::ClearByHost(const RefPtr<FrameNode>& host)
{
    if (!host) {
        return;
    }
    std::lock_guard<std::mutex> lock(MixedRegistryMutex());
    for (auto iter = MixedChildParentMap().begin(); iter != MixedChildParentMap().end();) {
        auto currentHost = iter->second.Upgrade();
        iter = (!currentHost || currentHost == host) ? MixedChildParentMap().erase(iter) : ++iter;
    }
}
} // namespace OHOS::Ace::NG
