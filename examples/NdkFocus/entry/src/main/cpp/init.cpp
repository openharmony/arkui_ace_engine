/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <hilog/log.h>

#include "manager.h"


namespace NativeXComponentSample {
EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init", "Init begins");
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "env or exports is null");
        return nullptr;
    }

    napi_property_descriptor desc[] = {
        { "getContext", nullptr, Manager::GetContext, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "createNativeNode", nullptr, Manager::CreateNativeNode, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "upDateNativeNode", nullptr, Manager::UpdateNativeNode, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "requestFocus", nullptr, Manager::RequestFocus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "requestFocusAsync", nullptr, Manager::RequestFocusAsync, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "clearFocus", nullptr, Manager::ClearFocus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "activateFocus", nullptr, Manager::ActivateFocus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setAutoTransfer", nullptr, Manager::SetAutoTransfer, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setKeyProcessingMode", nullptr, Manager::SetKeyProcessingMode, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "setNodeFocusable", nullptr, Manager::SetNodeFocusable, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setNodeFocusOnTouch", nullptr, Manager::SetNodeFocusOnTouch, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "getCurrentFocusNodeId", nullptr, Manager::GetCurrentFocusNodeId, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "setNodeDefaultFocus", nullptr, Manager::SetNodeDefaultFocus, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "setNodeFocusBox", nullptr, Manager::SetNodeFocusBox, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "setNodeNextFocus", nullptr, Manager::SetNodeNextFocus, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "SetKeyProcessingMode", nullptr, Manager::SetKeyProcessingMode, nullptr, nullptr, nullptr, napi_default,
            nullptr },
        { "setNodeTabStop", nullptr, Manager::SetNodeTabStop, nullptr, nullptr, nullptr, napi_default, nullptr } };

    if (napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "napi_define_properties failed");
        return nullptr;
    }

    Manager::GetInstance()->Export(env, exports);
    return exports;
}
EXTERN_C_END

static napi_module nativeNodeModule = { .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "nativeNode",
    .nm_priv = ((void*)0),
    .reserved = { 0 } };

extern "C" __attribute__((constructor)) void RegisterModule(void)
{
    napi_module_register(&nativeNodeModule);
}
} // namespace NativeXComponentSample
