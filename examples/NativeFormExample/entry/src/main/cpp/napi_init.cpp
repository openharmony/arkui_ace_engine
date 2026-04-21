/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#include "demo/formTest.h"
#include <hilog/log.h>

napi_property_descriptor desc[] = {
    {"initButtonDemo", nullptr, NativeNode::Form::TransTool::InitButtonDemo, nullptr, nullptr, nullptr, napi_default,
     nullptr},
    {"initSliderDemo", nullptr, NativeNode::Form::TransTool::InitSliderDemo, nullptr, nullptr, nullptr, napi_default,
     nullptr},
    {"initCheckboxDemo", nullptr, NativeNode::Form::TransTool::InitCheckboxDemo, nullptr, nullptr, nullptr, napi_default,
     nullptr},
    {"initRadioDemo", nullptr, NativeNode::Form::TransTool::InitRadioDemo, nullptr, nullptr, nullptr, napi_default,
     nullptr},
    {"initToggleDemo", nullptr, NativeNode::Form::TransTool::InitToggleDemo, nullptr, nullptr, nullptr, napi_default,
     nullptr},
    
};

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    if ((env == nullptr) || (exports == nullptr)) {
        return nullptr;
    }

    if (napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc) != napi_ok) {
        return nullptr;
    }
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void *)0),
    .reserved = {0},
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void) { napi_module_register(&demoModule); }