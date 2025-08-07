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

#include "native_ui_extension_common.h"

#include "ani_callback_info.h"
#include "ani_common_want.h"
#include "../utils/ani_utils.h"
#include "base/log/log_wrapper.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_model_static.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/ui_extension_proxy_peer.h"
#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer_base.h"
#endif //WINDOW_SCENE_SUPPORTED
#include "want.h"

namespace OHOS::Ace::Ani {


ani_status NativeUiExtensionCommon::BindNativeUiExtensionCommon(ani_env *env)
{
    ani_status ret = BindNativeUiExtensionProxy(env);
    if (ret != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionProxy failed");
        return ret;
    }

    return ANI_OK;
}

ani_status NativeUiExtensionCommon::BindNativeUiExtensionProxy(ani_env *env)
{
    static const char *className =
        "Larkui/ani/arkts/ui_extension/ArkUIAniUiextensionModal/ArkUIAniUiextensionProxyModal;";
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

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionProxy Class_BindNativeMethods failed,"
            " className: %{public}s", className);
        return ANI_ERROR;
    };

    return ANI_OK;
}

ani_status NativeUiExtensionCommon::SendData(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object paramObj)
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

ani_object NativeUiExtensionCommon::SendDataSync(
    [[maybe_unused]] ani_env* env,
    [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer,
    [[maybe_unused]] ani_object paramObj)
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