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
#include "napi/native_api.h"
#include "datepicker/datepicker_test.h"
#include "manager/plugin_manager.h"
using namespace ArkUIDatePickerCApiDemo;

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        {"getContext", nullptr, PluginManager::GetContext, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"datePickerTest", nullptr, DatePickerTest::CreateNativeNode, nullptr, nullptr, nullptr, napi_default,
         nullptr},
    };
    
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    ArkUIDatePickerCApiDemo::PluginManager::GetInstance()->Export(env, exports);
    return exports;
}
EXTERN_C_END

static napi_module entry = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&entry);
}