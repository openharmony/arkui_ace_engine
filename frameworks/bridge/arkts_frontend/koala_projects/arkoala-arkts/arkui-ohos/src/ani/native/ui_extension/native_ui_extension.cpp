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

#include "native_ui_extension.h"

#include "ani_callback_info.h"
#include "ani_common_want.h"
#include "../utils/ani_utils.h"
#include "base/log/log_wrapper.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer.h"
#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer_base.h"
#endif //WINDOW_SCENE_SUPPORTED
#include "native_dynamic_module.h"
#include "want.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int32_t FOLLOW_HOST_DPI = 0;
const char UI_EXTENSION_PLACEHOLDER_TYPE_INITIAL[] = "initPlaceholder";
const char UI_EXTENSION_PLACEHOLDER_TYPE_UNDEFINED[] = "undefinedPlaceholder";
const char UI_EXTENSION_PLACEHOLDER_TYPE_ROTATION[] = "rotationPlaceholder";
const char UI_EXTENSION_PLACEHOLDER_TYPE_FOLD_TO_EXPAND[] = "flodPlaceholder";

bool IsNullishObject(ani_env *env, ani_ref objectRef)
{
    ani_boolean isUndefined = false;
    if (ANI_OK != env->Reference_IsNullishValue(objectRef, &isUndefined)) {
        return true;
    }
    return static_cast<bool>(isUndefined);
}
}
ani_status NativeUiExtension::BindNativeUiExtension(ani_env *env)
{
    ani_status ret = BindNativeUiExtensionComponent(env);
    if (ret != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionComponent failed");
        return ret;
    }

    ret = BindNativeUiExtensionProxy(env);
    if (ret != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionProxy failed");
        return ret;
    }

    return ANI_OK;
}

ani_status NativeUiExtension::BindNativeUiExtensionComponent(ani_env *env)
{
    ani_class cls;
    static const char *className =
        "arkui.ani.arkts.ui_extension.ArkUIAniUiextensionModal.ArkUIAniUiextensionModal";
    auto ani_status = env->FindClass(className, &cls);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionComponent FindClass failed, className: %{public}s", className);
        return ANI_ERROR;
    }

    std::array staticMethods = {
        ani_native_function {
            "_Uiextension_Set_Option",
            nullptr, reinterpret_cast<void*>(SetUiextensionOption)},
        ani_native_function {
            "_Uiextension_Set_Want",
            nullptr, reinterpret_cast<void *>(SetUiextensionWant)},
        ani_native_function {
            "_Uiextension_Set_OnResultCallback",
            nullptr, reinterpret_cast<void *>(SetOnResult)},
        ani_native_function {
            "_Uiextension_Set_OnErrorCallback",
            nullptr, reinterpret_cast<void *>(SetOnError)},
        ani_native_function {
            "_Uiextension_Set_OnReciveCallback",
            nullptr, reinterpret_cast<void *>(SetOnRecive)},
        ani_native_function {
            "_Uiextension_Set_OnTerminationCallback",
            nullptr, reinterpret_cast<void *>(SetOnTerminate)},
        ani_native_function {
            "_Uiextension_Set_OnReleaseCallback",
            nullptr, reinterpret_cast<void *>(SetOnRelease)},
        ani_native_function {
            "_Uiextension_Set_OnDrawReadyCallback",
            nullptr, reinterpret_cast<void *>(SetOnDrawReady)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionComponent Class_BindStaticNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status NativeUiExtension::BindNativeUiExtensionProxy(ani_env *env)
{
    static const char *className =
        "arkui.ani.arkts.ui_extension.ArkUIAniUiextensionModal.ArkUIAniUiextensionProxyModal";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionProxy FindClass failed, className: %{public}s", className);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"_Send_Data", nullptr, reinterpret_cast<void *>(SendData)},
        ani_native_function{"_Send_Data_Sync", nullptr, reinterpret_cast<void *>(SendDataSync)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionProxy Class_BindNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };

    return ANI_OK;
}

ani_status NativeUiExtension::SetUiextensionOption(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object obj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetUiextensionOption");
        return ANI_ERROR;
    }

    std::string optionClassName =
        "arkui.ani.arkts.ui_extension.ArkUIAniUiextensionModal.ArkUIAniUIExtensionOptions";
    if (!AniUtils::CheckType(env, obj, optionClassName)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "CheckType %{public}s failed when SetUiextensionOption",
            optionClassName.c_str());
        return ANI_ERROR;
    }

    bool isTransferringCaller = AniUtils::GetBoolOrUndefined(env, obj, "isTransferringCaller");
    bool isWindowModeFollowHost = AniUtils::GetBoolOrUndefined(env, obj, "isWindowModeFollowHost");
    int32_t dpiFollowStrategy = -1;
    if (!AniUtils::GetIntByName(env, obj, "dpiFollowStrategy", dpiFollowStrategy)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "Get dpiFollowStrategy failed when SetUiextensionOption");
        return ANI_ERROR;
    }
    std::map<NG::PlaceholderType, RefPtr<NG::FrameNode>> placeholderMap;

    static const std::map<std::string, NG::PlaceholderType> placeholderTypeTable = {
        { UI_EXTENSION_PLACEHOLDER_TYPE_INITIAL, NG::PlaceholderType::INITIAL },
        { UI_EXTENSION_PLACEHOLDER_TYPE_UNDEFINED, NG::PlaceholderType::UNDEFINED },
        { UI_EXTENSION_PLACEHOLDER_TYPE_ROTATION, NG::PlaceholderType::ROTATION },
        { UI_EXTENSION_PLACEHOLDER_TYPE_FOLD_TO_EXPAND, NG::PlaceholderType::FOLD_TO_EXPAND }
    };
    for (auto [strName, type] : placeholderTypeTable) {
        ani_long placeholder;
        if (ANI_OK != env->Object_GetFieldByName_Long(obj, strName.c_str(), &placeholder)) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Get placeholder failed.");
            continue;
        }
        auto* frameNodePeerRaw = reinterpret_cast<FrameNodePeer*>(placeholder);
        if (frameNodePeerRaw == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Get FrameNodePeer failed.");
            continue;
        }
        auto nodeWeak = frameNodePeerRaw->weakNode;
        auto upgradePtr = nodeWeak.Upgrade();
        if (!upgradePtr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Get FrameNode RefPtr failed.");
            continue;
        }
        placeholderMap.insert({type, upgradePtr});
    }
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "SetUiextensionOption isTransferringCaller: %{public}d, dpiFollowStrategy: %{public}d,"
        "isWindowModeFollowHost: %{public}d, placeholderMap size: %{public}d",
        isTransferringCaller, dpiFollowStrategy, isWindowModeFollowHost, static_cast<int32_t>(placeholderMap.size()));
#ifdef WINDOW_SCENE_SUPPORTED
    bool densityDpi = (dpiFollowStrategy == FOLLOW_HOST_DPI) ? true : false;
    NG::UIExtensionStatic::UpdateUecConfig(
        frameNode, isTransferringCaller, densityDpi, isWindowModeFollowHost, placeholderMap);
#endif
    return ANI_OK;
}

ani_status NativeUiExtension::SetUiextensionWant(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object obj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetUiextensionWant");
        return ANI_ERROR;
    }

    std::string wantClassName =
        "@ohos.app.ability.Want.Want";
    if (!AniUtils::CheckType(env, obj, wantClassName)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "CheckType failed when SetUiextensionWant");
        return ANI_ERROR;
    }

    OHOS::AAFwk::Want want;
    bool ret = OHOS::AppExecFwk::UnwrapWant(env, obj, want);
    if (!ret) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UnwrapWant failed when SetUiextensionWant");
        return ANI_ERROR;
    }

#ifdef WINDOW_SCENE_SUPPORTED
    NG::UIExtensionStatic::UpdateWant(frameNode, want);
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SetOnResult(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetOnResult");
        return ANI_ERROR;
    }
    if (IsNullishObject(env, callbackObj)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "unset the OnResult callback.");
    #ifdef WINDOW_SCENE_SUPPORTED
        NG::UIExtensionStatic::SetOnResult(frameNode, nullptr);
    #endif //WINDOW_SCENE_SUPPORTED
        return ANI_OK;
    }

    ani_ref onResultRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onResultGlobalRef;
    env->GlobalReference_Create(onResultRef, &onResultGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onResultAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onResultGlobalRef);
    auto onResultCallback = [onResultAniReadyCallbackInfo] (int32_t code, const AAFwk::Want& want) {
        if (onResultAniReadyCallbackInfo == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onResultAniReadyCallbackInfo is nullptr");
            return;
        }

        ani_ref onResultGlobalRef = onResultAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onResultAniReadyCallbackInfo->GetEnvRef();
        if (onResultGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onResultGlobalRef or env is nullptr");
            return;
        }

        auto fnObj = reinterpret_cast<ani_fn_object>(onResultGlobalRef);
        auto codeArgs = AniUtils::CreateDouble(env, code);
        if (codeArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "CreateDouble failed when onResultCallback");
            return;
        }

        auto wantArgs = OHOS::AppExecFwk::WrapWant(env, want);
        if (wantArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "WrapWant failed when onResultCallback");
            return;
        }

        ani_ref result;
        std::vector<ani_ref> tmp = {
            reinterpret_cast<ani_ref>(codeArgs), reinterpret_cast<ani_ref>(wantArgs)
        };
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    };
#ifdef WINDOW_SCENE_SUPPORTED
    NG::UIExtensionStatic::SetOnResult(frameNode, std::move(onResultCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SetOnRelease(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetOnRelease");
        return ANI_ERROR;
    }
    if (IsNullishObject(env, callbackObj)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "unset the OnRelease callback.");
    #ifdef WINDOW_SCENE_SUPPORTED
        NG::UIExtensionStatic::SetOnRelease(frameNode, nullptr);
    #endif //WINDOW_SCENE_SUPPORTED
        return ANI_OK;
    }

    ani_ref onReleaseRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onReleaseGlobalRef;
    env->GlobalReference_Create(onReleaseRef, &onReleaseGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onReleaseAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onReleaseGlobalRef);
    auto onReleaseCallback = [onReleaseAniReadyCallbackInfo] (int32_t code) {
        if (onReleaseAniReadyCallbackInfo == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onReleaseAniReadyCallbackInfo is nullptr");
            return;
        }

        ani_ref onReleaseGlobalRef = onReleaseAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onReleaseAniReadyCallbackInfo->GetEnvRef();
        if (onReleaseGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onReleaseGlobalRef or env is nullptr");
            return;
        }

        auto fnObj = reinterpret_cast<ani_fn_object>(onReleaseGlobalRef);
        auto codeArgs = AniUtils::CreateDouble(env, code);
        if (codeArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "CreateDouble failed when onReleaseCallback");
            return;
        }

        ani_ref result;
        std::vector<ani_ref> tmp = {
            reinterpret_cast<ani_ref>(codeArgs)
        };
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    };

#ifdef WINDOW_SCENE_SUPPORTED
    NG::UIExtensionStatic::SetOnRelease(frameNode, std::move(onReleaseCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SetOnDrawReady(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetOnDrawReady");
        return ANI_ERROR;
    }

    ani_ref onDrawReadyRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onDrawReadyGlobalRef;
    env->GlobalReference_Create(onDrawReadyRef, &onDrawReadyGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onDrawAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onDrawReadyGlobalRef);
    auto onDrawReadyCallback = [onDrawAniReadyCallbackInfo] () {
        if (onDrawAniReadyCallbackInfo == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onDrawAniReadyCallbackInfo is nullptr");
            return;
        }

        ani_ref onDrawReadyGlobalRef = onDrawAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onDrawAniReadyCallbackInfo->GetEnvRef();
        if (onDrawReadyGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onDrawReadyGlobalRef or env is nullptr");
            return;
        }

        auto fnObj = reinterpret_cast<ani_fn_object>(onDrawReadyGlobalRef);
        ani_ref result;
        std::vector<ani_ref> tmp = {};
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    };

#ifdef WINDOW_SCENE_SUPPORTED
    NG::UIExtensionStatic::SetOnDrawReady(frameNode, std::move(onDrawReadyCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SetOnError(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetOnError");
        return ANI_ERROR;
    }
    if (IsNullishObject(env, callbackObj)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "unset the OnError callback.");
    #ifdef WINDOW_SCENE_SUPPORTED
        NG::UIExtensionStatic::SetOnError(frameNode, nullptr);
    #endif //WINDOW_SCENE_SUPPORTED
        return ANI_OK;
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
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onErrorAniReadyCallbackInfo is nullptr");
            return;
        }

        ani_ref onErrorGlobalRef = onErrorAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onErrorAniReadyCallbackInfo->GetEnvRef();
        if (onErrorGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onErrorGlobalRef or env is nullptr");
            return;
        }

        auto fnObj = reinterpret_cast<ani_fn_object>(onErrorGlobalRef);
        auto codeArgs = AniUtils::CreateDouble(env, code);
        if (codeArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "CreateDouble failed when onErrorCallback");
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
    NG::UIExtensionStatic::SetOnError(frameNode, std::move(onErrorCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SetOnRecive(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetOnRecive");
        return ANI_ERROR;
    }
    if (IsNullishObject(env, callbackObj)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "unset the OnReceive callback.");
    #ifdef WINDOW_SCENE_SUPPORTED
        NG::UIExtensionStatic::SetOnReceive(frameNode, nullptr);
    #endif //WINDOW_SCENE_SUPPORTED
        return ANI_OK;
    }

    ani_ref onReciveRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onReciveGlobalRef;
    env->GlobalReference_Create(onReciveRef, &onReciveGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onReciveAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onReciveGlobalRef);
    auto onReciveCallback = [onReciveAniReadyCallbackInfo] (const AAFwk::WantParams& params) {
        if (onReciveAniReadyCallbackInfo == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onReciveAniReadyCallbackInfo is nullptr");
            return;
        }

        ani_ref onReciveGlobalRef = onReciveAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onReciveAniReadyCallbackInfo->GetEnvRef();
        if (onReciveGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "onReciveGlobalRef or env is nullptr");
            return;
        }

        auto fnObj = reinterpret_cast<ani_fn_object>(onReciveGlobalRef);
        auto wantparamArgs = OHOS::AppExecFwk::WrapWantParams(env, params);
        if (wantparamArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                "WrapWantParams failed when onReciveCallback");
            return;
        }

        ani_ref result;
        std::vector<ani_ref> tmp = {
            reinterpret_cast<ani_ref>(wantparamArgs)
        };
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    };

#ifdef WINDOW_SCENE_SUPPORTED
    NG::UIExtensionStatic::SetOnReceive(frameNode, std::move(onReciveCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SetOnTerminate(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
{
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "frameNode is null when SetOnTerminate");
        return ANI_ERROR;
    }
    if (IsNullishObject(env, callbackObj)) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT, "unset the OnTerminated callback.");
    #ifdef WINDOW_SCENE_SUPPORTED
        NG::UIExtensionStatic::SetOnTerminated(frameNode, nullptr);
    #endif //WINDOW_SCENE_SUPPORTED
        return ANI_OK;
    }

    ani_ref onTerminateRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onTerminateGlobalRef;
    env->GlobalReference_Create(onTerminateRef, &onTerminateGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onTerminateAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onTerminateGlobalRef);
    auto onTerminateCallback =
        [env, onTerminateAniReadyCallbackInfo] (int32_t code, const RefPtr<WantWrap>& wantWrap) {
            if (onTerminateAniReadyCallbackInfo == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "onTerminateAniReadyCallbackInfo is nullptr");
                return;
            }

            ani_ref onTerminateGlobalRef = onTerminateAniReadyCallbackInfo->GetOnGlobalRef();
            ani_env* env = onTerminateAniReadyCallbackInfo->GetEnvRef();
            if (onTerminateGlobalRef == nullptr || env == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "onTerminateGlobalRef or env is nullptr");
                return;
            }

            AAFwk::Want want;
            if (wantWrap) {
                want = wantWrap->GetWant();
            }
            auto fnObj = reinterpret_cast<ani_fn_object>(onTerminateGlobalRef);
            auto codeArgs = AniUtils::CreateDouble(env, code);
            if (codeArgs == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "CreateDouble failed when onTerminateCallback");
                return;
            }
            auto wantArgs = OHOS::AppExecFwk::WrapWant(env, want);
            if (wantArgs == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "WrapWant failed when onTerminateCallback");
                return;
            }
            ani_ref result;
            std::vector<ani_ref> tmp = {
                reinterpret_cast<ani_ref>(codeArgs), reinterpret_cast<ani_ref>(wantArgs)
            };
            env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
        };
#ifdef WINDOW_SCENE_SUPPORTED
    NG::UIExtensionStatic::SetOnTerminated(frameNode, std::move(onTerminateCallback));
#endif //WINDOW_SCENE_SUPPORTED
    return ANI_OK;
}

ani_status NativeUiExtension::SendData(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object paramObj)
{
    auto uIExtensionProxyPeer =
        reinterpret_cast<NG::GeneratedModifier::UIExtensionProxyPeerBase *>(pointer);
    if (uIExtensionProxyPeer == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "uIExtensionProxyPeer is null when SendData");
        return ANI_ERROR;
    }

    OHOS::AAFwk::WantParams requestParams;
    bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, paramObj, requestParams);
    if (!ret) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UnwrapWantParams failed when SendData");
        return ANI_ERROR;
    }

    uIExtensionProxyPeer->SendData(requestParams);
    return ANI_OK;
}

ani_object NativeUiExtension::SendDataSync(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object paramObj)
{
    ani_object result_obj = {};
    auto uIExtensionProxyPeer =
        reinterpret_cast<NG::GeneratedModifier::UIExtensionProxyPeerBase *>(pointer);
    if (uIExtensionProxyPeer == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "uIExtensionProxyPeer is null when SendDataSync");
        return result_obj;
    }

    OHOS::AAFwk::WantParams requestParams;
    bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, paramObj, requestParams);
    if (!ret) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UnwrapWantParams failed when SendDataSync");
        return result_obj;
    }

    OHOS::AAFwk::WantParams replyParams;
    uIExtensionProxyPeer->SendDataSync(requestParams, replyParams);
    ani_ref wantParamsObj = OHOS::AppExecFwk::WrapWantParams(env, replyParams);
    if (wantParamsObj == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "WrapWantParams failed when SendDataSync");
        return result_obj;
    }

    return static_cast<ani_object>(wantParamsObj);
}
} // namespace OHOS::Ace::Ani