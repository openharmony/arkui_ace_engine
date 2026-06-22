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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LOCAL_SCOPE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LOCAL_SCOPE_H

#include <ani.h>

#include "base/log/log.h"

namespace OHOS::Ace {

constexpr ani_size DEFAULT_ANI_LOCAL_SCOPE_SIZE = 16;

class ScopedAniLocalScope {
public:
    explicit ScopedAniLocalScope(ani_env* env, ani_size size = DEFAULT_ANI_LOCAL_SCOPE_SIZE) : env_(env)
    {
        if (!env_) {
            LOGE("Create ANI local scope failed, env is null");
        } else {
            auto status = env_->CreateLocalScope(size);
            if (status != ANI_OK) {
                LOGE("Create ANI local scope failed, status: %{public}d", status);
            } else {
                active_ = true;
            }
        }
    }

    ~ScopedAniLocalScope()
    {
        if (active_) {
            env_->DestroyLocalScope();
        }
    }

    ScopedAniLocalScope(const ScopedAniLocalScope&) = delete;
    ScopedAniLocalScope& operator=(const ScopedAniLocalScope&) = delete;

private:
    ani_env* env_ = nullptr;
    bool active_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LOCAL_SCOPE_H
