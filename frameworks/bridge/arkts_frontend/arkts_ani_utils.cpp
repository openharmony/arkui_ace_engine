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

#include "bridge/arkts_frontend/arkts_ani_utils.h"

#include <ani.h>
#include <sstream>
#include <iostream>

#include "base/log/log.h"

namespace OHOS::Ace {
int32_t ArktsAniUtils::CreateAniBoolean(ani_env* env, bool value, ani_object& result)
{
    ani_status state;
    ani_class booleanClass;
    if ((state = env->FindClass("Lstd/core/Boolean;", &booleanClass)) != ANI_OK) {
        LOGE("FindClass std/core/Boolean failed, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    ani_method booleanClassCtor;
    if ((state = env->Class_FindMethod(booleanClass, "<ctor>", "Z:V", &booleanClassCtor)) != ANI_OK) {
        LOGE("Class_FindMethod Boolean ctor failed, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    ani_boolean aniValue = value;
    if ((state = env->Object_New(booleanClass, booleanClassCtor, &result, aniValue)) != ANI_OK) {
        LOGE("New Boolean object failed, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    return static_cast<int32_t>(state);
}

int32_t ArktsAniUtils::GetNearestNonBootRuntimeLinker(ani_env* env, ani_ref& result)
{
    ani_module stdCoreModule;
    auto state = env->FindModule("Lstd/core;", &stdCoreModule);
    if (state != ANI_OK) {
        LOGE("Find module core failed, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    ani_function fn;
    state = env->Module_FindFunction(stdCoreModule, "getNearestNonBootRuntimeLinker", ":Lstd/core/RuntimeLinker;", &fn);
    if (state != ANI_OK) {
        LOGE("Find function getNearestNonBootRuntimeLinker failed, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    state = env->Function_Call_Ref(fn, &result);
    if (state != ANI_OK) {
        LOGE("Call getNearestNonBootRuntimeLinker failed, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    ani_boolean isUndef = ANI_FALSE;
    state = env->Reference_IsUndefined(result, &isUndef);
    if (isUndef == ANI_TRUE) {
        LOGE("Result of getNearestNonBootRuntimeLinker is undefined, %{public}d", state);
        return static_cast<int32_t>(state);
    }
    return static_cast<int32_t>(state);
}

void ArktsAniUtils::ClearAniPendingError(ani_env* env)
{
    ani_boolean result = ANI_FALSE;
    env->ExistUnhandledError(&result);
    if (result != ANI_FALSE) {
        std::ostringstream oss;
        auto rdbufBak = std::cerr.rdbuf(oss.rdbuf());
        env->DescribeError();
        std::cerr.rdbuf(rdbufBak);
        LOGE("ani pending error: %{public}s", oss.str().c_str());
        env->ResetError();
    }
}

ani_env* ArktsAniUtils::GetAniEnv(ani_vm* vm)
{
    if (!vm) {
        LOGW("GetAniEnv from null vm");
        return nullptr;
    }
    ani_env* env = nullptr;
    ani_status status;
    if ((status = vm->GetEnv(ANI_VERSION_1, &env)) != ANI_OK) {
        LOGW("GetAniEnv from vm failed, status: %{public}d", status);
        return nullptr;
    }
    return env;
}
} // namespace OHOS::Ace
