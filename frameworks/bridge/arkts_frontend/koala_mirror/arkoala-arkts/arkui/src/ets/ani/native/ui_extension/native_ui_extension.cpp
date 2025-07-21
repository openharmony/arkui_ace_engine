// /*
//  * Copyright (c) 2025 Huawei Device Co., Ltd.
//  * Licensed under the Apache License, Version 2.0 (the "License");
//  * you may not use this file except in compliance with the License.
//  * You may obtain a copy of the License at
//  *
//  * http://www.apache.org/licenses/LICENSE-2.0
//  *
//  * Unless required by applicable law or agreed to in writing, software
//  * distributed under the License is distributed on an "AS IS" BASIS,
//  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  * See the License for the specific language governing permissions and
//  * limitations under the License.
//  */

// #include "native_ui_extension.h"

// #include "ani_common_want.h"
// #include "../ani_utils.h"
// #include "base/log/log_wrapper.h"
// #ifdef WINDOW_SCENE_SUPPORTED
// #include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_adapter.h"
// #include "core/interfaces/native/implementation/ui_extension_proxy_peer.h"
// #include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer_base.h"
// #endif //WINDOW_SCENE_SUPPORTED
// #include "want.h"

// namespace OHOS::Ace::Ani {
// namespace {
// constexpr int32_t FOLLOW_HOST_DPI = 0;
// }
// ani_status NativeUiExtension::BindNativeUiExtension(ani_env *env)
// {
//     ani_status ret = BindNativeUiExtensionComponent(env);
//     if (ret != ANI_OK) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtensionComponent failed");
//         return ret;
//     }

//     ret = BindNativeUiExtensionProxy(env);
//     if (ret != ANI_OK) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtensionProxy failed");
//         return ret;
//     }

//     return ANI_OK;
// }

// ani_status NativeUiExtension::BindNativeUiExtensionComponent(ani_env *env)
// {
//     ani_class cls;
//     static const char *className =
//         "Larkui/ani/ui_extension/ArkUIAniUiextensionModal/ArkUIAniUiextensionModal;";
//     auto ani_status = env->FindClass(className, &cls);
//     if (ani_status != ANI_OK) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtensionComponent FindClass failed, className: %{public}s", className);
//         return ANI_ERROR;
//     }

//     std::array methods = {
//         ani_native_function {
//             "_Uiextension_Set_Option",
//             nullptr,
//             reinterpret_cast<void*>(SetUiextensionOption)},
//         ani_native_function {
//             "_Uiextension_Set_Want",
//             nullptr,
//             reinterpret_cast<void *>(SetUiextensionWant)},
//         ani_native_function {
//             "_Uiextension_Set_OnResultCallback",
//             nullptr,
//             reinterpret_cast<void *>(SetOnResult)},
//         ani_native_function {
//             "_Uiextension_Set_OnErrorCallback",
//             nullptr,
//             reinterpret_cast<void *>(SetOnError)},
//         ani_native_function {
//             "_Uiextension_Set_OnReciveCallback",
//             nullptr,
//             reinterpret_cast<void *>(SetOnRecive)},
//         ani_native_function {
//             "_Uiextension_Set_OnTerminationCallback",
//             nullptr,
//             reinterpret_cast<void *>(SetOnTerminate)},
//         ani_native_function {
//             "_Uiextension_Set_OnReleaseCallback",
//             nullptr,
//             reinterpret_cast<void *>(SetOnRelease)},
//     };

//     if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtensionComponent Class_BindNativeMethods failed,"
//             " className: %{public}s", className);
//         return ANI_ERROR;
//     };
//     return ANI_OK;
// }

// ani_status NativeUiExtension::BindNativeUiExtensionProxy(ani_env *env)
// {
//     static const char *className =
//         "Larkui/ani/ui_extension/ArkUIAniUiextensionModal/ArkUIAniUiextensionProxyModal;";
//     ani_class cls;
//     if (ANI_OK != env->FindClass(className, &cls)) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtensionProxy FindClass failed, className: %{public}s", className);
//         return ANI_ERROR;
//     }

//     std::array methods = {
//         ani_native_function{"_Send_Data", nullptr, reinterpret_cast<void *>(SendData)},
//         ani_native_function{"_Send_Data_Sync", nullptr, reinterpret_cast<void *>(SendDataSync)},
//     };

//     if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtensionProxy Class_BindNativeMethods failed,"
//             " className: %{public}s", className);
//         return ANI_ERROR;
//     };

//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetUiextensionOption(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object obj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetUiextensionOption");
//         return ANI_ERROR;
//     }

//     std::string optionClassName =
//         "Larkui/ani/ui_extension/ArkUIAniUiextensionModal/ArkUIAniUIExtensionOptions;";
//     if (!AniUtils::CheckType(env, obj, optionClassName)) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "CheckType %{public}s failed when SetUiextensionOption",
//             optionClassName.c_str());
//         return ANI_ERROR;
//     }

//     bool isTransferringCaller = AniUtils::GetBoolOrUndefined(env, obj, "isTransferringCaller");
//     int32_t dpiFollowStrategy = -1;
//     if (!AniUtils::GetIntByName(env, obj, "dpiFollowStrategy", dpiFollowStrategy)) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "Get dpiFollowStrategy failed when SetUiextensionOption");
//         return ANI_ERROR;
//     }

//     TAG_LOGI(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//         "SetUiextensionOption isTransferringCaller: %{public}d, dpiFollowStrategy: %{public}d",
//         isTransferringCaller, dpiFollowStrategy);
// #ifdef WINDOW_SCENE_SUPPORTED
//     bool densityDpi = (dpiFollowStrategy == FOLLOW_HOST_DPI) ? true : false;
//     NG::UIExtensionAdapter::UpdateUecConfig(frameNode, isTransferringCaller, densityDpi);
// #endif
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetUiextensionWant(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object obj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetUiextensionWant");
//         return ANI_ERROR;
//     }

//     std::string wantClassName =
//         "L@ohos/app/ability/Want/Want;";
//     if (!AniUtils::CheckType(env, obj, wantClassName)) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "CheckType failed when SetUiextensionWant");
//         return ANI_ERROR;
//     }

//     OHOS::AAFwk::Want want;
//     bool ret = OHOS::AppExecFwk::UnwrapWant(env, obj, want);
//     if (!ret) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "UnwrapWant failed when SetUiextensionWant");
//         return ANI_ERROR;
//     }

// #ifdef WINDOW_SCENE_SUPPORTED
//     NG::UIExtensionAdapter::UpdateWant(frameNode, want);
// #endif //WINDOW_SCENE_SUPPORTED
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetOnResult(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetOnResult");
//         return ANI_ERROR;
//     }

//     ani_ref onResultRef = reinterpret_cast<ani_ref>(callbackObj);
//     ani_ref onResultGlobalRef;
//     env->GlobalReference_Create(onResultRef, &onResultGlobalRef);
//     auto onResultCallback = [env, onResultGlobalRef] (int32_t code, const AAFwk::Want& want) {
//         auto fnObj = reinterpret_cast<ani_fn_object>(onResultGlobalRef);
//         auto codeArgs = AniUtils::CreateDouble(env, code);
//         if (codeArgs == nullptr) {
//             TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                 "CreateDouble failed when onResultCallback");
//             return;
//         }

//         auto wantArgs = OHOS::AppExecFwk::WrapWant(env, want);
//         if (wantArgs == nullptr) {
//             TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                 "WrapWant failed when onResultCallback");
//             return;
//         }

//         ani_ref result;
//         std::vector<ani_ref> tmp =
//             { reinterpret_cast<ani_ref>(codeArgs), reinterpret_cast<ani_ref>(wantArgs)};
//         env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
//     };

// #ifdef WINDOW_SCENE_SUPPORTED
//     NG::UIExtensionAdapter::SetOnResult(frameNode, std::move(onResultCallback));
// #endif //WINDOW_SCENE_SUPPORTED
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetOnRelease(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetOnRelease");
//         return ANI_ERROR;
//     }

//     ani_ref onReleaseRef = reinterpret_cast<ani_ref>(callbackObj);
//     ani_ref onReleaseGlobalRef;
//     env->GlobalReference_Create(onReleaseRef, &onReleaseGlobalRef);
//     auto onReleaseCallback = [env, onReleaseGlobalRef] (int32_t code) {
//         auto fnObj = reinterpret_cast<ani_fn_object>(onReleaseGlobalRef);
//         auto codeArgs = AniUtils::CreateDouble(env, code);
//         if (codeArgs == nullptr) {
//             TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                 "CreateDouble failed when onReleaseCallback");
//             return;
//         }

//         ani_ref result;
//         std::vector<ani_ref> tmp = { reinterpret_cast<ani_ref>(codeArgs) };
//         env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
//     };

// #ifdef WINDOW_SCENE_SUPPORTED
//     NG::UIExtensionAdapter::SetOnRelease(frameNode, std::move(onReleaseCallback));
// #endif //WINDOW_SCENE_SUPPORTED
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetOnError(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetOnError");
//         return ANI_ERROR;
//     }

//     ani_ref onErrorRef = reinterpret_cast<ani_ref>(callbackObj);
//     ani_ref onErrorGlobalRef;
//     env->GlobalReference_Create(onErrorRef, &onErrorGlobalRef);
//     auto onErrorCallback = [env, onErrorGlobalRef] (
//         int32_t code, const std::string& name, const std::string& message) {
//         auto fnObj = reinterpret_cast<ani_fn_object>(onErrorGlobalRef);
//         auto codeArgs = AniUtils::CreateDouble(env, code);
//         if (codeArgs == nullptr) {
//             TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                 "CreateDouble failed when onErrorCallback");
//             return;
//         }

//         ani_string nameArgs;
//         env->String_NewUTF8(name.c_str(), name.size(), &nameArgs);
//         ani_string messageArgs;
//         env->String_NewUTF8(message.c_str(), message.size(), &messageArgs);

//         ani_ref result;
//         std::vector<ani_ref> tmp = {
//             reinterpret_cast<ani_ref>(codeArgs),
//             reinterpret_cast<ani_ref>(nameArgs),
//             reinterpret_cast<ani_ref>(messageArgs)
//         };
//         env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
//     };

// #ifdef WINDOW_SCENE_SUPPORTED
//     NG::UIExtensionAdapter::SetOnError(frameNode, std::move(onErrorCallback));
// #endif //WINDOW_SCENE_SUPPORTED
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetOnRecive(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetOnRecive");
//         return ANI_ERROR;
//     }

//     ani_ref onReciveRef = reinterpret_cast<ani_ref>(callbackObj);
//     ani_ref onReciveGlobalRef;
//     env->GlobalReference_Create(onReciveRef, &onReciveGlobalRef);
//     auto onReciveCallback = [env, onReciveGlobalRef] (const AAFwk::WantParams& params) {
//         auto fnObj = reinterpret_cast<ani_fn_object>(onReciveGlobalRef);
//         auto wantparamArgs = OHOS::AppExecFwk::WrapWantParams(env, params);
//         if (wantparamArgs == nullptr) {
//             TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                 "WrapWantParams failed when onReciveCallback");
//             return;
//         }

//         ani_ref result;
//         std::vector<ani_ref> tmp = {
//             reinterpret_cast<ani_ref>(wantparamArgs)
//         };
//         env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
//     };

// #ifdef WINDOW_SCENE_SUPPORTED
//     NG::UIExtensionAdapter::SetOnReceive(frameNode, std::move(onReciveCallback));
// #endif //WINDOW_SCENE_SUPPORTED
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SetOnTerminate(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj)
// {
//     auto frameNode = reinterpret_cast<NG::FrameNode *>(pointer);
//     if (frameNode == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "frameNode is null when SetOnTerminate");
//         return ANI_ERROR;
//     }

//     ani_ref onTerminateRef = reinterpret_cast<ani_ref>(callbackObj);
//     ani_ref onTerminateGlobalRef;
//     env->GlobalReference_Create(onTerminateRef, &onTerminateGlobalRef);
//     auto onTerminateCallback =
//         [env, onTerminateGlobalRef] (int32_t code, const RefPtr<WantWrap>& wantWrap) {
//             AAFwk::Want want;
//             if (wantWrap) {
//                 want = wantWrap->GetWant();
//             } else {
//                 want.SetParam("djctest", 5689);
//             }
//             LOGI("djc-cpp-Handle onTerminateCallback %{public}d , want: %{public}s; start",
//                 code, want.ToString().c_str());
//             auto fnObj = reinterpret_cast<ani_fn_object>(onTerminateGlobalRef);
//             auto codeArgs = AniUtils::CreateDouble(env, code);
//             if (codeArgs == nullptr) {
//                 TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                     "CreateDouble failed when onTerminateCallback");
//                 return;
//             }
//             LOGI("djc-cpp-Handle onTerminateCallback %{public}d 111", code);
//             auto wantArgs = OHOS::AppExecFwk::WrapWant(env, want);
//             if (wantArgs == nullptr) {
//                 TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//                     "WrapWant failed when onTerminateCallback");
//                 return;
//             }
//             LOGI("djc-cpp-Handle onTerminateCallback %{public}d 222", code);
//             ani_ref result;
//             std::vector<ani_ref> tmp =
//                 { reinterpret_cast<ani_ref>(codeArgs), reinterpret_cast<ani_ref>(wantArgs)};
//             LOGI("djc-cpp-Handle onTerminateCallback %{public}d 4444", code);
//             env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
//             LOGI("djc-cpp-Handle onTerminateCallback %{public}d end", code);
//         };
// #ifdef WINDOW_SCENE_SUPPORTED
//     NG::UIExtensionAdapter::SetOnTerminated(frameNode, std::move(onTerminateCallback));
// #endif //WINDOW_SCENE_SUPPORTED
//     return ANI_OK;
// }

// ani_status NativeUiExtension::SendData(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object paramObj)
// {
//     auto uIExtensionProxyPeer =
//         reinterpret_cast<NG::GeneratedModifier::UIExtensionProxyPeerBase *>(pointer);
//     if (uIExtensionProxyPeer == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "uIExtensionProxyPeer is null when SendData");
//         return ANI_ERROR;
//     }

//     OHOS::AAFwk::WantParams requestParams;
//     bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, paramObj, requestParams);
//     if (!ret) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "UnwrapWantParams failed when SendData");
//         return ANI_ERROR;
//     }

//     uIExtensionProxyPeer->SendData(requestParams);
//     return ANI_OK;
// }

// ani_object NativeUiExtension::SendDataSync(
//     [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
//     [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object paramObj)
// {
//     ani_object result_obj = {};
//     auto uIExtensionProxyPeer =
//         reinterpret_cast<NG::GeneratedModifier::UIExtensionProxyPeerBase *>(pointer);
//     if (uIExtensionProxyPeer == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "uIExtensionProxyPeer is null when SendDataSync");
//         return result_obj;
//     }

//     OHOS::AAFwk::WantParams requestParams;
//     bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, paramObj, requestParams);
//     if (!ret) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "UnwrapWantParams failed when SendDataSync");
//         return result_obj;
//     }

//     OHOS::AAFwk::WantParams replyParams;
//     uIExtensionProxyPeer->SendDataSync(requestParams, replyParams);
//     ani_ref wantParamsObj = OHOS::AppExecFwk::WrapWantParams(env, replyParams);
//     if (wantParamsObj == nullptr) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "WrapWantParams failed when SendDataSync");
//         return result_obj;
//     }

//     return static_cast<ani_object>(wantParamsObj);
// }
// } // namespace OHOS::Ace::Ani

// ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
// {
//     TAG_LOGI(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//         "arkuiuiextension_ani ANI_Constructor start");
//     ani_env* env;
//     if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "GetEnv failed when ANI_Constructor");
//         return ANI_ERROR;
//     }

//     auto ani_status = OHOS::Ace::Ani::NativeUiExtension::BindNativeUiExtension(env);
//     if (ani_status != ANI_OK) {
//         TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//             "BindNativeUiExtension failed when ANI_Constructor");
//         return ani_status;
//     }

//     *result = ANI_VERSION_1;
//     TAG_LOGI(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
//         "arkuiuiextension_ani ANI_Constructor end");
//     return ANI_OK;
// }
