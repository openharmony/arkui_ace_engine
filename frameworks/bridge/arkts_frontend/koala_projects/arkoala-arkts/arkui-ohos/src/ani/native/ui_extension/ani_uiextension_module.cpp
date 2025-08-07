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

#include "../utils/ani_utils.h"
#include "base/log/log_wrapper.h"
#include "native_dynamic_module.h"
#include "native_security_ui_extension.h"
#include "native_ui_extension.h"
#include "native_ui_extension_common.h"

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "arkuiuiextension_ani ANI_Constructor start");
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "GetEnv failed when ANI_Constructor");
        return ANI_ERROR;
    }

    auto ani_status = OHOS::Ace::Ani::NativeUiExtension::BindNativeUiExtension(env);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtension failed when ANI_Constructor");
        return ani_status;
    }

    ani_status = OHOS::Ace::Ani::NativeSecurityUiExtension::BindNativeSecurityUiExtension(env);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_SECURITYUIEXTENSION,
            "BindNativeSecurityUiExtension failed when ANI_Constructor");
        return ani_status;
    }

    ani_status = OHOS::Ace::Ani::NativeDynamicModule::BindNativeDynamicModule(env);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DYNAMIC_COMPONENT,
            "BindNativeDynamicModule failed when ANI_Constructor");
        return ani_status;
    }

    ani_status = OHOS::Ace::Ani::NativeUiExtensionCommon::BindNativeUiExtensionCommon(env);
    if (ani_status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "BindNativeUiExtensionCommon failed");
        return ani_status;
    }

    *result = ANI_VERSION_1;
    TAG_LOGI(OHOS::Ace::AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "arkuiuiextension_ani ANI_Constructor end");
    return ANI_OK;
}