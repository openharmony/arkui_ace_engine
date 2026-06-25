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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_MIXED_MOUNT_REGISTRY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_MIXED_MOUNT_REGISTRY_H

#include <cstdint>

#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class FrameNode;

class MixedMountRegistry final {
public:
    static void RegisterChild(uint64_t childRsNodeId, const WeakPtr<FrameNode>& parent);
    static void UnregisterChild(uint64_t childRsNodeId);
    static RefPtr<FrameNode> GetParent(uint64_t childRsNodeId);
    static void ClearByHost(const RefPtr<FrameNode>& host);

private:
    MixedMountRegistry() = delete;
    ~MixedMountRegistry() = delete;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_MIXED_MOUNT_REGISTRY_H
