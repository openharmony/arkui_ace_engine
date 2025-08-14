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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_CONTEXT_MODULE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_CONTEXT_MODULE_H

#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "base/utils/noncopyable.h"

typedef class __ani_ref* ani_ref;
namespace OHOS::Ace::Framework {

class AniContextModule {
public:
    AniContextModule() = default;
    ~AniContextModule() = default;

    static AniContextModule* GetInstance();
    static void AddAniContext(int32_t key, ani_ref* value);
    static void RemoveAniContext(int32_t key);
    static ani_ref* GetAniContext(int32_t key);

private:
    static std::unordered_map<int32_t, ani_ref*> aniContexts_;
    static std::shared_mutex aniContextsMutex_;
};

} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_CONTEXT_MODULE_H
