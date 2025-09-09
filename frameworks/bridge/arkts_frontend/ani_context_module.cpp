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

#include <mutex>

#include "base/log/log.h"
namespace OHOS::Ace::Framework {

std::unordered_map<int32_t, ani_ref*> AniContextModule::aniContexts_;
std::shared_mutex AniContextModule::aniContextsMutex_;

AniContextModule* AniContextModule::GetInstance()
{
    static AniContextModule instance;
    return &instance;
}

ani_ref* AniContextModule::GetAniContext(int32_t key)
{
    std::shared_lock<std::shared_mutex> lock(aniContextsMutex_);
    auto it1 = aniContexts_.find(key);
    if (it1 != aniContexts_.end()) {
        return it1->second;
    }
    return nullptr;
}

void AniContextModule::AddAniContext(int32_t key, ani_ref* value)
{
    std::unique_lock<std::shared_mutex> lock(aniContextsMutex_);
    if (aniContexts_.find(key) != aniContexts_.end()) {
        LOGW("AniContext exists for key %d", key);
        return;
    }
    aniContexts_.emplace(key, value);
}

void AniContextModule::RemoveAniContext(int32_t key)
{
    std::unique_lock<std::shared_mutex> lock(aniContextsMutex_);
    auto it = aniContexts_.find(key);
    if (it != aniContexts_.end()) {
        aniContexts_.erase(it);
    }
}
} // namespace OHOS::Ace::Framework
