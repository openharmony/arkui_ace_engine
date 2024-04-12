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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H

#include <cstdint>
#include <functional>
#include <map>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class NavigationManager : public virtual AceType {
    DECLARE_ACE_TYPE(NavigationManager, AceType);
public:
    using DumpLogDepth = int;
    using DumpCallback = std::function<void(DumpLogDepth)>;
    NavigationManager() = default;
    ~NavigationManager() = default;

    void AddNavigationDumpCallback(int32_t nodeId, int32_t depth, const DumpCallback& callback);
    void RemoveNavigationDumpCallback(int32_t nodeId, int32_t depth);

    void OnDumpInfo();

    void AddNavigationUpdateCallback(std::function<void()> callback)
    {
        updateCallbacks_.emplace_back(callback);
    }

    void FireNavigationUpdateCallback();

private:
    struct DumpMapKey {
        int32_t nodeId;
        int32_t depth;

        DumpMapKey(int32_t n, int32_t d) : nodeId(n), depth(d) {}
        bool operator< (const DumpMapKey& o) const
        {
            if (depth != o.depth) {
                return depth < o.depth;
            }
            return nodeId < o.nodeId;
        }
    };
    std::map<DumpMapKey, DumpCallback> dumpMap_;
    std::vector<std::function<void()>> updateCallbacks_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_NAVIGATION_MANAGER_H
