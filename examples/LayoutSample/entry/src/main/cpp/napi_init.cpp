/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "napi/native_api.h"
#include "NativeEntry.h"

// C语言链接声明开始
EXTERN_C_START

#define REGISTER_COMPONENT(name) \
    {"Create" #name "NativeRoot", nullptr, NativeModule::Create##name##NativeRoot, \
        nullptr, nullptr, nullptr, napi_default, nullptr}, \
    {"Destroy" #name "NativeRoot", nullptr, NativeModule::Destroy##name##NativeRoot, \
        nullptr, nullptr, nullptr, napi_default, nullptr}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        // 布局相关组件
        REGISTER_COMPONENT(LayoutConstraint),
        REGISTER_COMPONENT(AlignRuleOption),
        REGISTER_COMPONENT(GuidelineOption),
        REGISTER_COMPONENT(BarrierOption),
        
        // 列表和对齐相关组件
        REGISTER_COMPONENT(ListChildrenMainSize),
        REGISTER_COMPONENT(ItemAlignment),
        REGISTER_COMPONENT(RelativeLayoutChain),
        
        // 基础布局组件
        REGISTER_COMPONENT(Flex),
        REGISTER_COMPONENT(Stack),
        REGISTER_COMPONENT(Row),
        REGISTER_COMPONENT(Column),
        
        // 位置和区域相关组件
        REGISTER_COMPONENT(LayoutPosition),
        REGISTER_COMPONENT(SafeArea),
        REGISTER_COMPONENT(RefreshOffsetEvent),
        
        // 策略和边缘相关组件
        REGISTER_COMPONENT(LayoutPolicy),
        REGISTER_COMPONENT(PositionEdges),
        REGISTER_COMPONENT(PixelRound)
    };

    // 定义NAPI属性
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

// C语言链接声明结束
EXTERN_C_END

// 定义NAPI模块
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