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

#include "web_module_methods.h"

#include "load.h"

namespace OHOS::Ace::Ani {

static ani_env* GetAniEnv(ani_vm* vm)
{
    if (!vm) {
        return nullptr;
    }
    ani_env* env = nullptr;
    ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
    if (status != ANI_OK) {
        return nullptr;
    }
    return env;
}

static void GetCommonFunc(ani_vm* vm, ani_ref savePtr,
    std::function<long()> &getNativePtrFunc, std::function<void()> &releaseRefFunc)
{
    getNativePtrFunc = [vm, object = savePtr]() -> long {
        ani_long nativePtr = 0;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Long(
            reinterpret_cast<ani_object>(object), "innerGetThisVar", ":J", &nativePtr) != ANI_OK) {
            return 0;
        }
        return static_cast<long>(nativePtr);
    };
    releaseRefFunc = [vm, object = savePtr]() {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        envTemp->GlobalReference_Delete(object);
    };
}

void SetWebOptions(ani_env* env, ani_class aniClass, ani_long node, ani_object object)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env || !arkNode) {
        return;
    }

    ani_vm* vm = nullptr;
    ani_ref savePtr;
    if (env->GetVM(&vm) != ANI_OK ||
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &savePtr) != ANI_OK) {
        return;
    }

    auto setWebIdFunc = [vm, object = savePtr](int32_t nwebId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "_setNWebId", "D:V", static_cast<ani_double>(nwebId)) != ANI_OK) {
            return;
        }
    };
    auto setHapPathFunc = [vm, object = savePtr](const std::string& hapPath) {
        ani_string aniHapPath = nullptr;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        if (envTemp->String_NewUTF8(hapPath.c_str(), hapPath.size(), &aniHapPath) != ANI_OK ||
            envTemp->Object_CallMethodByName_Void(
                reinterpret_cast<ani_object>(object), "_setHapPath", "Lstd/core/String;:V", aniHapPath) != ANI_OK) {
            envTemp->GlobalReference_Delete(object);
            return;
        }
        envTemp->GlobalReference_Delete(object);
    };
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    GetCommonFunc(vm, savePtr, getNativePtrFunc, releaseRefFunc);
    modifier->getWebAniModifier()->setWebOptions(arkNode, {
        .setWebIdFunc = std::move(setWebIdFunc),
        .setHapPathFunc = std::move(setHapPathFunc),
        .getNativePtrFunc = std::move(getNativePtrFunc),
        .releaseRefFunc = std::move(releaseRefFunc),
    });
}

void SetWebControllerControllerHandler(ani_env* env, ani_class aniClass, ani_long handler, ani_object object)
{
    void* controllerHandler = reinterpret_cast<void*>(handler);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env || !controllerHandler) {
        return;
    }

    ani_vm* vm = nullptr;
    ani_ref savePtr;
    if (env->GetVM(&vm) != ANI_OK ||
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &savePtr) != ANI_OK) {
        return;
    }

    auto getWebIdFunc = [vm, object = savePtr]() -> int32_t {
        ani_double nwebId;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Double(
            reinterpret_cast<ani_object>(object), "getWebId", ":D", &nwebId) != ANI_OK) {
            return -1;
        }
        return static_cast<int32_t>(nwebId);
    };
    auto completeWindowNewFunc = [vm, object = savePtr](int32_t parentId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        envTemp->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "innerCompleteWindowNew", "I:V", static_cast<ani_int>(parentId));
    };
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    GetCommonFunc(vm, savePtr, getNativePtrFunc, releaseRefFunc);
    modifier->getWebAniModifier()->setWebControllerControllerHandler(controllerHandler, {
        .getWebIdFunc = std::move(getWebIdFunc),
        .completeWindowNewFunc = std::move(completeWindowNewFunc),
        .getNativePtrFunc = std::move(getNativePtrFunc),
        .releaseRefFunc = std::move(releaseRefFunc),
    });
}
} // namespace OHOS::Ace::Ani
