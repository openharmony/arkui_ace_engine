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

#include "interfaces/napi/kits/promptaction/prompt_action.h"

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
        DECLARE_NAPI_FUNCTION("updateCustomDialog", JSPromptUpdateCustomDialog),
        DECLARE_NAPI_FUNCTION("closeCustomDialog", JSPromptCloseCustomDialog),
        DECLARE_NAPI_PROPERTY("ToastShowMode", showMode),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(promptDesc) / sizeof(promptDesc[0]), promptDesc));
    return exports;
}

static napi_module promptActionModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = PromptActionExport,
    .nm_modname = "promptAction",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void PromptActionRegister()
{
    napi_module_register(&promptActionModule);
}

// compatible with api8
static napi_module promptModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = PromptActionExport,
    .nm_modname = "prompt",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void PromptRegister()
{
    napi_module_register(&promptModule);
}
} // namespace OHOS::Ace::Napi
