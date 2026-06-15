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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LOCAL_SCOPE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LOCAL_SCOPE_H

#include <ani.h>

namespace OHOS::Ace {

constexpr ani_size DEFAULT_ANI_LOCAL_SCOPE_SIZE = 16;

class ScopedAniLocalScope {
public:
    explicit ScopedAniLocalScope(ani_env* env, ani_size size = DEFAULT_ANI_LOCAL_SCOPE_SIZE) : env_(env)
    {
        active_ = env_ && env_->CreateLocalScope(size) == ANI_OK;
    }

    ~ScopedAniLocalScope()
    {
        if (active_) {
            env_->DestroyLocalScope();
        }
    }

    ScopedAniLocalScope(const ScopedAniLocalScope&) = delete;
    ScopedAniLocalScope& operator=(const ScopedAniLocalScope&) = delete;

    bool IsActive() const
    {
        return active_;
    }

private:
    ani_env* env_ = nullptr;
    bool active_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ANI_LOCAL_SCOPE_H
