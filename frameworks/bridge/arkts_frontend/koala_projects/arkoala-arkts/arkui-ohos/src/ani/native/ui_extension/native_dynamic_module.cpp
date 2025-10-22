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

#include "native_dynamic_module.h"

#include "ani_callback_info.h"
#include "../utils/ani_utils.h"
#include "base/log/log_wrapper.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_model_static.h"
#endif //WINDOW_SCENE_SUPPORTED

namespace OHOS::Ace::Ani {
ani_status NativeDynamicModule::BindNativeDynamicModule(ani_env *env)
{
    ani_status ret = BindNativeDynamicComponent(env);
    if (ret != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "BindNativeDynamicComponent failed");
        return ret;
    }

    return ANI_OK;
}

ani_status NativeDynamicModule::BindNativeDynamicComponent(ani_env *env)
{
    ani_class cls;
    static const char *className =
        "arkui.ani.arkts.ui_extension.ArkUIAniDynamicModal.ArkUIAniDynamicModal";
    auto ani_status = env->FindClass(className, &cls);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "BindNativeDynamicComponent FindClass failed, className: %{public}s", className);
        return ANI_ERROR;
    }

    std::array staticMethods = {
        ani_native_function {
            "_Dynamic_Construct",
            nullptr, reinterpret_cast<void*>(DynamicConstruct)},
        ani_native_function {
            "_Dynamic_Set_Option",
            nullptr, reinterpret_cast<void*>(SetDynamicOption)},
        ani_native_function {
            "_Dynamic_Set_OnErrorCallback",
            nullptr, reinterpret_cast<void *>(SetOnError)},
        ani_native_function {
            "_Dynamic_Set_IsReportFrameEvent",
            nullptr, reinterpret_cast<void *>(SetIsReportFrameEvent)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "BindNativeDynamicComponent Class_BindStaticNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_long NativeDynamicModule::DynamicConstruct(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_int id,
    [[maybe_unused]] ani_int flag)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNodePtr = NG::DynamicModelStatic::CreateFrameNodeByIncRefCount(id);
    return reinterpret_cast<ani_long>(frameNodePtr);
#else
    return nullptr;
#endif
}

ani_status NativeDynamicModule::SetDynamicOption(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object obj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "frameNode is null when SetDynamicOption");
        return ANI_ERROR;
    }

    std::string optionClassName =
        "arkui.ani.arkts.ui_extension.ArkUIAniDynamicModal.ArkUIAniDynamicOptions";
    if (!AniUtils::CheckType(env, obj, optionClassName)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "CheckType %{public}s failed when SetDynamicOption",
            optionClassName.c_str());
        return ANI_ERROR;
    }

    NG::DynamicParam param;
    param.backgroundTransparent = AniUtils::GetBoolOrUndefined(env, obj, "backgroundTransparent");
    if (!AniUtils::GetIntByName(env, obj, "workerId", param.workerId)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "Get workerId failed when SetDynamicOption");
        return ANI_ERROR;
    }

    if (!AniUtils::GetStringByName(env, obj, "entryPoint", param.entryPoint)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "Get entryPoint failed when SetDynamicOption");
        return ANI_ERROR;
    }

    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
        "NativeDynamicModule SetDynamicParam %{public}s.", param.ToString().c_str());
#ifdef WINDOW_SCENE_SUPPORTED
    NG::DynamicModelStatic::SetDynamicParam(frameNode, param);
#endif
    return ANI_OK;
}

ani_status NativeDynamicModule::SetOnError(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT, "frameNode is null when SetOnError");
        return ANI_ERROR;
    }
    ani_ref onErrorRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onErrorGlobalRef;
    env->GlobalReference_Create(onErrorRef, &onErrorGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onErrorAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onErrorGlobalRef);
    auto onErrorCallback = [onErrorAniReadyCallbackInfo] (
        int32_t code, const std::string& name, const std::string& message) {
        if (onErrorAniReadyCallbackInfo == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
                "onErrorAniReadyCallbackInfo is nullptr");
            return;
        }
        ani_ref onErrorGlobalRef = onErrorAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onErrorAniReadyCallbackInfo->GetEnvRef();
        if (onErrorGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT, "onErrorGlobalRef or env is nullptr");
            return;
        }
        auto fnObj = reinterpret_cast<ani_fn_object>(onErrorGlobalRef);
        auto codeArgs = AniUtils::CreateDouble(env, code);
        if (codeArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT, "CreateDouble failed when onError");
            return;
        }
        ani_string nameArgs;
        env->String_NewUTF8(name.c_str(), name.size(), &nameArgs);
        ani_string messageArgs;
        env->String_NewUTF8(message.c_str(), message.size(), &messageArgs);
        ani_ref result;
        std::vector<ani_ref> tmp = {
            reinterpret_cast<ani_ref>(codeArgs),
            reinterpret_cast<ani_ref>(nameArgs),
            reinterpret_cast<ani_ref>(messageArgs)
        };
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    };
#ifdef WINDOW_SCENE_SUPPORTED
    NG::DynamicModelStatic::SetOnError(frameNode, std::move(onErrorCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeDynamicModule::SetIsReportFrameEvent(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_boolean value)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT, "frameNode is null when SetIsReportFrameEvent");
        return ANI_ERROR;
    }
#ifdef WINDOW_SCENE_SUPPORTED
    NG::DynamicModelStatic::SetIsReportFrameEvent(frameNode, value);
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}
} // namespace OHOS::Ace::Ani
