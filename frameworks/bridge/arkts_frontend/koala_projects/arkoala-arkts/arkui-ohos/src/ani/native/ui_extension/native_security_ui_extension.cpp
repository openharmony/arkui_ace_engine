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

#include "native_security_ui_extension.h"

#include "ani_callback_info.h"
#include "ani_common_want.h"
#include "../utils/ani_utils.h"
#include "base/log/log_wrapper.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_model_static.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/ui_extension_proxy_peer.h"
#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer_base.h"
#endif //WINDOW_SCENE_SUPPORTED
#include "want.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int32_t FOLLOW_HOST_DPI = 0;
const char UI_EXTENSION_PLACEHOLDER_TYPE_INITIAL[] = "initPlaceholder";
const char UI_EXTENSION_PLACEHOLDER_TYPE_UNDEFINED[] = "undefinedPlaceholder";
const char UI_EXTENSION_PLACEHOLDER_TYPE_ROTATION[] = "rotationPlaceholder";
const char UI_EXTENSION_PLACEHOLDER_TYPE_FOLD_TO_EXPAND[] = "flodPlaceholder";
}
ani_status NativeSecurityUiExtension::BindNativeSecurityUiExtension(ani_env *env)
{
    ani_status ret = BindNativeSecurityUiExtensionComponent(env);
    if (ret != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "BindNativeSecurityUiExtensionComponent failed");
        return ret;
    }

    return ANI_OK;
}

ani_status NativeSecurityUiExtension::BindNativeSecurityUiExtensionComponent(ani_env *env)
{
    ani_class cls;
    static const char *className =
        "Larkui/ani/arkts/ui_extension/ArkUIAniUiextensionModal/ArkUIAniSecurityUiextensionModal;";
    auto ani_status = env->FindClass(className, &cls);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "BindNativeSecurityUiExtensionComponent FindClass failed, className: %{public}s", className);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {
            "_SecurityUiextension_Set_Option",
            nullptr, reinterpret_cast<void*>(SetSecurityUiextensionOption)},
        ani_native_function {
            "_SecurityUiextension_Set_Want",
            nullptr, reinterpret_cast<void *>(SetSecurityUiextensionWant)},
        ani_native_function {
            "_SecurityUiextension_Set_OnResultCallback",
            nullptr, reinterpret_cast<void *>(SetSecurityOnResult)},
        ani_native_function {
            "_SecurityUiextension_Set_OnErrorCallback",
            nullptr, reinterpret_cast<void *>(SetSecurityOnError)},
        ani_native_function {
            "_SecurityUiextension_Set_OnReciveCallback",
            nullptr, reinterpret_cast<void *>(SetSecurityOnRecive)},
        ani_native_function {
            "_SecurityUiextension_Set_OnTerminationCallback",
            nullptr, reinterpret_cast<void *>(SetSecurityOnTerminate)},
        ani_native_function {
            "_SecurityUiextension_Set_OnReleaseCallback",
            nullptr, reinterpret_cast<void *>(SetSecurityOnRelease)},
        ani_native_function {
            "_SecurityUiextension_Set_OnDrawReadyCallback",
            nullptr, reinterpret_cast<void *>(SetSecurityOnDrawReady)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "BindNativeSecurityUiExtensionComponent Class_BindNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status NativeSecurityUiExtension::SetSecurityUiextensionOption(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object obj)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityUiextensionOption start");
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION, "frameNode is null when SetSecurityUiextensionOption");
        return ANI_ERROR;
    }
    std::string optionClassName =
        "Larkui/ani/arkts/ui_extension/ArkUIAniUiextensionModal/ArkUIAniUIExtensionOptions;";
    if (!AniUtils::CheckType(env, obj, optionClassName)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "CheckType %{public}s failed when SetSecurityUiextensionOption",
            optionClassName.c_str());
        return ANI_ERROR;
    }
    bool isTransferringCaller = AniUtils::GetBoolOrUndefined(env, obj, "isTransferringCaller");
    bool isWindowModeFollowHost = AniUtils::GetBoolOrUndefined(env, obj, "isWindowModeFollowHost");
    int32_t dpiFollowStrategy = -1;
    if (!AniUtils::GetIntByName(env, obj, "dpiFollowStrategy", dpiFollowStrategy)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "Get dpiFollowStrategy failed when SetSecurityUiextensionOption");
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
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION, "Get placeholder failed.");
            continue;
        }
        auto* frameNodePeerRaw = reinterpret_cast<FrameNodePeer*>(placeholder);
        if (frameNodePeerRaw == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION, "Get FrameNodePeer failed.");
            continue;
        }
        auto nodeWeak = frameNodePeerRaw->weakNode;
        auto upgradePtr = nodeWeak.Upgrade();
        if (!upgradePtr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION, "Get FrameNode RefPtr failed.");
            continue;
        }
        placeholderMap.insert({type, upgradePtr});
    }
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "SetSecurityUiextensionOption isTransferringCaller: %{public}d, dpiFollowStrategy: %{public}d,"
        "isWindowModeFollowHost: %{public}d, placeholderMap size: %{public}d",
        isTransferringCaller, dpiFollowStrategy, isWindowModeFollowHost, static_cast<int32_t>(placeholderMap.size()));
#ifdef WINDOW_SCENE_SUPPORTED
    bool densityDpi = (dpiFollowStrategy == FOLLOW_HOST_DPI) ? true : false;
    NG::SecurityUIExtensionStatic::UpdateSecurityUecConfig(
        frameNode, isTransferringCaller, densityDpi, isWindowModeFollowHost, placeholderMap);
#endif
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,  "NativeUiExtension SetSecurityUiextensionOption end");
    return ANI_OK;
}


ani_status NativeSecurityUiExtension::SetSecurityUiextensionWant(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object obj)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityUiextensionWant start");
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "frameNode is null when SetSecurityUiextensionWant");
        return ANI_ERROR;
    }

    std::string wantClassName =
        "L@ohos/app/ability/Want/Want;";
    if (!AniUtils::CheckType(env, obj, wantClassName)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "CheckType failed when SetUiextensionWant");
        return ANI_ERROR;
    }

    OHOS::AAFwk::Want want;
    bool ret = OHOS::AppExecFwk::UnwrapWant(env, obj, want);
    if (!ret) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "UnwrapWant failed when SetSecurityUiextensionWant");
        return ANI_ERROR;
    }
#ifdef WINDOW_SCENE_SUPPORTED
    NG::SecurityUIExtensionStatic::UpdateSecurityWant(frameNode, want);
#endif //WINDOW_SCENE_SUPPORTED
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityUiextensionWant end");
    return ANI_OK;
}

ani_status NativeSecurityUiExtension::SetSecurityOnError(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnError start");
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "frameNode is null when SetSecurityOnError");
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
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
                "onErrorAniReadyCallbackInfo is nullptr");
            return;
        }
        ani_ref onErrorGlobalRef = onErrorAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onErrorAniReadyCallbackInfo->GetEnvRef();
        if (onErrorGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
                "onErrorGlobalRef or env is nullptr");
            return;
        }
        auto fnObj = reinterpret_cast<ani_fn_object>(onErrorGlobalRef);
        auto codeArgs = AniUtils::CreateDouble(env, code);
        if (codeArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
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
    NG::SecurityUIExtensionStatic::SetSecurityOnError(frameNode, std::move(onErrorCallback));
#endif //WINDOW_SCENE_SUPPORTED
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnError end");
    return ANI_OK;
}

ani_status NativeSecurityUiExtension::SetSecurityOnRecive(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnRecive start");
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "frameNode is null when SetSecurityOnRecive");
        return ANI_ERROR;
    }

    ani_ref onReciveRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onReciveGlobalRef;
    env->GlobalReference_Create(onReciveRef, &onReciveGlobalRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    auto onReciveAniReadyCallbackInfo = std::make_shared<AniCallbackInfo>(vm, onReciveGlobalRef);
    auto onReciveCallback = [onReciveAniReadyCallbackInfo] (const AAFwk::WantParams& params) {
        if (onReciveAniReadyCallbackInfo == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
                "onReciveAniReadyCallbackInfo is nullptr");
            return;
        }

        ani_ref onReciveGlobalRef = onReciveAniReadyCallbackInfo->GetOnGlobalRef();
        ani_env* env = onReciveAniReadyCallbackInfo->GetEnvRef();
        if (onReciveGlobalRef == nullptr || env == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
                "onReciveGlobalRef or env is nullptr");
            return;
        }

        auto fnObj = reinterpret_cast<ani_fn_object>(onReciveGlobalRef);
        auto wantparamArgs = OHOS::AppExecFwk::WrapWantParams(env, params);
        if (wantparamArgs == nullptr) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
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
    NG::SecurityUIExtensionStatic::SetSecurityOnReceive(frameNode, std::move(onReciveCallback));
#endif //WINDOW_SCENE_SUPPORTED
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnRecive end");
    return ANI_OK;
}

ani_status NativeSecurityUiExtension::SetSecurityOnTerminate(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnTerminate start");
    auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
    if (frameNode == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "frameNode is null when SetSecurityOnTerminate");
        return ANI_ERROR;
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
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
                    "onTerminateAniReadyCallbackInfo is nullptr");
                return;
            }
            ani_ref onTerminateGlobalRef = onTerminateAniReadyCallbackInfo->GetOnGlobalRef();
            ani_env* env = onTerminateAniReadyCallbackInfo->GetEnvRef();
            if (onTerminateGlobalRef == nullptr || env == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
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
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
                    "CreateDouble failed when onTerminateCallback");
                return;
            }
            auto wantArgs = OHOS::AppExecFwk::WrapWant(env, want);
            if (wantArgs == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
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
    NG::SecurityUIExtensionStatic::SetSecurityOnTerminated(frameNode, std::move(onTerminateCallback));
#endif //WINDOW_SCENE_SUPPORTED
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnTerminate end");
    return ANI_OK;
}


ani_status NativeSecurityUiExtension::SetSecurityOnRelease(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnRelease not supported now.");
    return ANI_OK;
}

ani_status NativeSecurityUiExtension::SetSecurityOnDrawReady(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurityOnDrawReady not supported now.");
    return ANI_OK;
}

ani_status NativeSecurityUiExtension::SetSecurityOnResult(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object callbackObj)
{
    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
        "NativeUiExtension SetSecurity OnResult not supported now.");
    return ANI_OK;
}

} // namespace OHOS::Ace::Ani