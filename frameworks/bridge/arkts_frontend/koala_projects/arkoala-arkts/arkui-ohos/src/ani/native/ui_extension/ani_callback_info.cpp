/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ani_callback_info.h"

#include "base/log/log_wrapper.h"

namespace OHOS::Ace::Ani {
AniCallbackInfo::AniCallbackInfo(ani_vm* vm, const ani_ref& globalRef)
    : vm_(vm), globalRef_(globalRef)
{}

AniCallbackInfo::~AniCallbackInfo()
{
    ani_env* env = GetEnvRef();
    if (env == nullptr || globalRef_ == nullptr) {
        LOGW("AniCallbackInfo env or globalRef is null");
        return;
    }

    env->GlobalReference_Delete(globalRef_);
    vm_ = nullptr;
    globalRef_ = nullptr;
}

ani_ref AniCallbackInfo::GetOnGlobalRef() const
{
    return globalRef_;
}

ani_env* AniCallbackInfo::GetEnvRef() const
{
    ani_env* env = nullptr;
    if (vm_ == nullptr) {
        return env;
    }

    vm_->GetEnv(ANI_VERSION_1, &env);
    return env;
}
}
