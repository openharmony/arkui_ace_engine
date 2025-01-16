/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "interfaces/napi/kits/promptaction/js_prompt_controller.h"
#include "interfaces/napi/kits/promptaction/prompt_action.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

extern const char _binary_promptaction_js_start[];
extern const char _binary_promptaction_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_promptaction_js_end[];
extern const char _binary_promptaction_abc_end[];
#else
extern const char* _binary_promptaction_js_end;
extern const char* _binary_promptaction_abc_end;
#endif

namespace OHOS::Ace::Napi {
static constexpr uint32_t DEFAULT = 0;
static constexpr uint32_t TOP_MOST = 1;
static constexpr uint32_t SYSTEM_TOP_MOST = 2;
static napi_value PromptActionExport(napi_env env, napi_value exports)
{
    napi_value showMode = nullptr;
    napi_create_object(env, &showMode);
    napi_value prop = nullptr;
    napi_create_uint32(env, DEFAULT, &prop);
    napi_set_named_property(env, showMode, "DEFAULT", prop);
    napi_create_uint32(env, TOP_MOST, &prop);
    napi_set_named_property(env, showMode, "TOP_MOST", prop);
    napi_create_uint32(env, SYSTEM_TOP_MOST, &prop);
    napi_set_named_property(env, showMode, "SYSTEM_TOP_MOST", prop);

    napi_property_descriptor promptDesc[] = {
        DECLARE_NAPI_FUNCTION("showToast", JSPromptShowToast),
        DECLARE_NAPI_FUNCTION("openToast", JSPromptOpenToast),
        DECLARE_NAPI_FUNCTION("closeToast", JSPromptCloseToast),
        DECLARE_NAPI_FUNCTION("showDialog", JSPromptShowDialog),
        DECLARE_NAPI_FUNCTION("showActionMenu", JSPromptShowActionMenu),
        DECLARE_NAPI_FUNCTION("openCustomDialog", JSPromptOpenCustomDialog),
        DECLARE_NAPI_FUNCTION("openCustomDialogWithController", JSPromptOpenCustomDialogWithController),
        DECLARE_NAPI_FUNCTION("presentCustomDialog", JSPromptPresentCustomDialog),
        DECLARE_NAPI_FUNCTION("updateCustomDialog", JSPromptUpdateCustomDialog),
        DECLARE_NAPI_FUNCTION("closeCustomDialog", JSPromptCloseCustomDialog),
        DECLARE_NAPI_PROPERTY("ToastShowMode", showMode),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(promptDesc) / sizeof(promptDesc[0]), promptDesc));
    NAPI_CALL(env, JSPromptController::Define(env, exports));
    return exports;
}

extern "C" __attribute__((visibility("default"))) void NAPI_promptaction_GetJSCode(const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_promptaction_js_start;
    }

    if (bufLen != nullptr) {
        *bufLen = _binary_promptaction_js_end - _binary_promptaction_js_start;
    }
}

extern "C" __attribute__((visibility("default"))) void NAPI_promptaction_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_promptaction_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_promptaction_abc_end - _binary_promptaction_abc_start;
    }
}

static napi_module_with_js promptActionModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = PromptActionExport,
    .nm_modname = "promptAction",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_promptaction_GetABCCode,
    .nm_get_js_code = NAPI_promptaction_GetJSCode,
};

extern "C" __attribute__((constructor)) void PromptActionRegister()
{
    napi_module_with_js_register(&promptActionModule);
}
} // namespace OHOS::Ace::Napi
