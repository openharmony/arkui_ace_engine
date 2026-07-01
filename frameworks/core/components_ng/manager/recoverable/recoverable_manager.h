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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_RECOVERABLE_RECOVERABLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_RECOVERABLE_RECOVERABLE_MANAGER_H

#include <cstdint>
#include <string>
#include <functional>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/recoverable/recoverable_declaration.h"

namespace OHOS::Ace::NG {

class PipelineContext;

class RecoverableManager : public virtual AceType {
    DECLARE_ACE_TYPE(RecoverableManager, AceType);
public:
    RecoverableManager() = default;
    ~RecoverableManager() override = default;

    void SetPipelineContext(const WeakPtr<PipelineContext>& pipeline)
    {
        pipeline_ = pipeline;
    }

    int32_t AddRestoreComponent(bool isNavigationType, const int32_t pageId, const std::string& componentId,
        std::function<std::string()> saveCallback);
    void RemoveRestoreComponent(bool isNavigationType, int32_t pageId, int32_t callbackId);
    bool GetRestoreByComponent(bool isNavigationType, int32_t pageId, std::string& componentId, std::string& result);

    void RemoveRestoreByPage(bool isNavigationType, int32_t pageId);
    bool GetRestoreByPage(bool isNavigationType, int32_t pageId, std::string& result);

    std::string GetNavigationHomeInfo(const std::string& navigationId);
    void SetNavigationHomeInfo(const std::string& navigationId, const std::string& homeInfo);

private:
    std::unordered_map<int32_t, std::unordered_map<int32_t, RestoreInfo>>& GetRestoreInfo(bool isNavigationType)
    {
        if (isNavigationType) {
            return navigationRestoreInfos_;
        } else {
            return routerRestoreInfos_;
        }
    }

    WeakPtr<PipelineContext> pipeline_;

    int32_t restoreCallbackId_ = 0;

    std::unordered_map<std::string, std::string> homeNavigationInfo_;
    // restore info: NavDestinationNodeBaseId --> [callbackId --> restoreInfo]
    std::unordered_map<int32_t, std::unordered_map<int32_t, RestoreInfo>> navigationRestoreInfos_;
    // restore info: pageId --> [callbackId --> restoreInfo]
    std::unordered_map<int32_t, std::unordered_map<int32_t, RestoreInfo>> routerRestoreInfos_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_RECOVERABLE_RECOVERABLE_MANAGER_H
