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

#include "frameworks/bridge/arkts_frontend/ani_context_module.h"

#include <ani.h>

#include "base/log/log.h"
#include "frameworks/core/common/container.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
namespace OHOS::Ace::Framework {

thread_local std::unordered_map<int32_t, std::shared_ptr<ani_ref>> AniContextModule::aniContexts_;

AniContextModule* AniContextModule::GetInstance()
{
    static AniContextModule instance;
    return &instance;
}

std::shared_ptr<ani_ref> AniContextModule::GetAniContext()
{
    int32_t currentInstance = Container::CurrentIdSafely();
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (currentInstance >= MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = PluginManager::GetInstance().GetPluginParentContainerId(currentInstance);
    }
#endif

    if (currentInstance >= MIN_SUBCONTAINER_ID && currentInstance < MIN_PLUGIN_SUBCONTAINER_ID) {
        // currentInstance = SubwindowManager::GetInstance()->GetParentContainerId(currentInstance);
    }

    if (currentInstance <= 0) {
        currentInstance = CONTAINER_ID_DIVIDE_SIZE;
    }
    auto it = aniContexts_.find(currentInstance);
    if (it != aniContexts_.end()) {
        return it->second;
    }
    int32_t currentInstanceBak = currentInstance;

    // Try to get the active container.
    auto container = Container::GetActive();
    if (container) {
        currentInstance = container->GetInstanceId();
        it = aniContexts_.find(currentInstance);
        if (it != aniContexts_.end()) {
            return it->second;
        } else {
            TAG_LOGW(AceLogTag::ACE_DEFAULT_DOMAIN, "Context not found, id:%{public}d, active:%{public}d",
                currentInstanceBak, currentInstance);
        }
    }
    return nullptr;
}

void AniContextModule::AddAniContext(int32_t key, const std::shared_ptr<ani_ref>& value)
{
    if (aniContexts_.find(key) != aniContexts_.end()) {
        LOGW("AniContext exists for key %d", key);
        return;
    }
    aniContexts_.emplace(key, value);
}

void AniContextModule::RemoveAniContext(int32_t key)
{
    auto it = aniContexts_.find(key);
    if (it != aniContexts_.end()) {
        aniContexts_.erase(it);
    }
}
} // namespace OHOS::Ace::Framework
