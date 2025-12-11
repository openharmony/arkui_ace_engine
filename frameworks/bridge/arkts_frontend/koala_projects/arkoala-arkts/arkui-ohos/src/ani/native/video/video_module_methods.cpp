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

#include "video_module_methods.h"

#include "base/utils/utils.h"
#include "pixel_map_taihe_ani.h"
#include "load.h"
#include "common/common_module.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {

namespace {
ani_object CreateError(ani_env* env, const std::string &msg)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_status status = ANI_ERROR;
    ani_string aniMsg = nullptr;
    if ((status = env->String_NewUTF8(msg.c_str(), msg.size(), &aniMsg)) != ANI_OK) {
        return nullptr;
    }
    ani_ref undefRef;
    if ((status = env->GetUndefined(&undefRef)) != ANI_OK) {
        return nullptr;
    }
    ani_class cls {};
    if ((status = env->FindClass("escompat.Error", &cls)) != ANI_OK) {
        return nullptr;
    }
    ani_method method {};
    if ((status = env->Class_FindMethod(
        cls, "<ctor>", "C{std.core.String}C{escompat.ErrorOptions}:", &method)) != ANI_OK) {
        return nullptr;
    }
    ani_object obj = nullptr;
    if ((status = env->Object_New(cls, method, &obj, aniMsg, undefRef)) != ANI_OK) {
        return nullptr;
    }
    return obj;
}

ani_object CreateBusinessError(ani_env* env, int32_t code, const std::string& message)
{
    CHECK_NULL_RETURN(env, nullptr);

    ani_class cls {};
    ani_status status = env->FindClass("@ohos.base.BusinessError", &cls);
    if (status != ANI_OK) {
        return nullptr;
    }
    ani_method method {};
    status = env->Class_FindMethod(cls, "<ctor>", "iC{escompat.Error}:", &method);
    if (status != ANI_OK) {
        return nullptr;
    }
    ani_object error = CreateError(env, message);
    if (error == nullptr) {
        return nullptr;
    }
    ani_object obj = nullptr;
    status = env->Object_New(cls, method, &obj, code, error);
    if (status != ANI_OK) {
        return nullptr;
    }
    return obj;
}
} // namespace

void SetVideoOnErrorErrorCallback(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node, ani_fn_object callback)
{
    CHECK_NULL_VOID(env);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto videoModifier = modifier->getArkUIAniVideoModifier();
    CHECK_NULL_VOID(videoModifier);
    auto parseErrorFunc = videoModifier->parseVideoError;
    auto callbackRef = std::make_shared<CommonModuleCallbackAni>(env, static_cast<ani_ref>(callback));
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onError = [vm, func = callbackRef, parseErrorFunc](const std::string& jsonStr) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(func);
        CHECK_NULL_VOID(parseErrorFunc);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);
        int32_t code = 0;
        std::string msg = "";
        parseErrorFunc(jsonStr, code, msg);
        auto businessError = CreateBusinessError(env, code, msg);
        std::vector<ani_ref> params = { static_cast<ani_ref>(businessError) };
        ani_ref ret = nullptr;
        func->Call(env, params.size(), params.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
    videoModifier->setOnError(arkNode, std::move(onError));
}

void SetVideoOnErrorVoidCallback(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node, ani_fn_object callback)
{
    CHECK_NULL_VOID(env);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto videoModifier = modifier->getArkUIAniVideoModifier();
    CHECK_NULL_VOID(videoModifier);
    auto callbackRef = std::make_shared<CommonModuleCallbackAni>(env, static_cast<ani_ref>(callback));
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onError = [vm, func = callbackRef](const std::string& param) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(func);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);
        std::vector<ani_ref> params = {};
        ani_ref ret = nullptr;
        func->Call(env, params.size(), params.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
    videoModifier->setOnError(arkNode, std::move(onError));
}

} // namespace OHOS::Ace::Ani
