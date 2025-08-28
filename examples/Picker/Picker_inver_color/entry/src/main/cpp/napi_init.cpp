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
#include <arkui/native_node.h>
#include <arkui/native_interface.h>
#include <cstdint>

constexpr int32_t ALPHA_OFFSET = 24;
constexpr int32_t RED_OFFSET = 16;
constexpr int32_t GREEN_OFFSET = 8;
constexpr int32_t COLOR_MASK = 255;

static uint32_t ColorInvertFuncA(uint32_t color)
{
    uint8_t alpha = (color >> ALPHA_OFFSET) & 0xFF;
    uint8_t red = (color >> RED_OFFSET) & 0xFF;
    uint8_t green = (color >> GREEN_OFFSET) & 0xFF;
    uint8_t blue = color & 0xFF;
    
    // 重新构造新的颜色值（保留Alpha通道不变）
    return (static_cast<uint32_t>(alpha) << ALPHA_OFFSET) |
           (static_cast<uint32_t>(blue) << RED_OFFSET) |
           (static_cast<uint32_t>(green) << GREEN_OFFSET) |
           static_cast<uint32_t>(red);
}

static uint32_t ColorInvertFuncB(uint32_t color)
{
    uint8_t alpha = (color >> ALPHA_OFFSET) & 0xFF;
    uint8_t red = (color >> RED_OFFSET) & 0xFF;
    uint8_t green = (color >> GREEN_OFFSET) & 0xFF;
    uint8_t blue = color & 0xFF;
    
    red = COLOR_MASK - red;
    green = COLOR_MASK - green;
    blue = COLOR_MASK - blue;
    
    // 重新构造新的颜色值（保留Alpha通道不变）
    return (static_cast<uint32_t>(alpha) << ALPHA_OFFSET) |
           (static_cast<uint32_t>(blue) << RED_OFFSET) |
           (static_cast<uint32_t>(green) << GREEN_OFFSET) |
           static_cast<uint32_t>(red);
}

static napi_value Enable(napi_env env, napi_callback_info info)
{
    OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1");
    
    // 6种测试场景，测试时，使能一种，其他场景注释
    
    // 1. 使能所有控件，默认反色算法
    OH_ArkUI_SetForceDarkConfig(nullptr, true, ArkUI_NodeType::ARKUI_NODE_UNDEFINED, nullptr);
    
    // 2. 使能所有控件，自定义反色算法
    OH_ArkUI_SetForceDarkConfig(nullptr, true, ArkUI_NodeType::ARKUI_NODE_UNDEFINED, &ColorInvertFuncA);
    
    // 3. 仅对TimePicker使能默认反色算法
    OH_ArkUI_SetForceDarkConfig(nullptr, true, ArkUI_NodeType::ARKUI_NODE_TIME_PICKER, nullptr);
    
    // 4. 仅对TextPicker使能自定义反色算法
    OH_ArkUI_SetForceDarkConfig(nullptr, true, ArkUI_NodeType::ARKUI_NODE_TEXT_PICKER, &ColorInvertFuncA);
    
    // 5. 对所有控件使能反色算法A，对控件DatePicker使能反色算法B
    OH_ArkUI_SetForceDarkConfig(nullptr, true, ArkUI_NodeType::ARKUI_NODE_UNDEFINED, &ColorInvertFuncA);
    OH_ArkUI_SetForceDarkConfig(nullptr, true, ArkUI_NodeType::ARKUI_NODE_DATE_PICKER, &ColorInvertFuncB);
    
    // 6. 不使能反色能力，对控件DatePicker使能反色算法A
    OH_ArkUI_SetForceDarkConfig(nullptr, false, ArkUI_NodeType::ARKUI_NODE_DATE_PICKER, &ColorInvertFuncA);
    
    return nullptr;
}

static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        { "add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr },
        { "enable", nullptr, Enable, nullptr, nullptr, nullptr, napi_default, nullptr }
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
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
    napi_module_register(&demoModule);
}
