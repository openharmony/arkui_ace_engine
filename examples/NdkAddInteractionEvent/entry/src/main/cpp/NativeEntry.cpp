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

// NativeEntry.cpp

#include <arkui/native_node_napi.h>
#include <hilog/log.h>
#include <js_native_api.h>
#include "Common.h"
#include "Function.h"
#include "LongPressAndSwipeGesture.h"
#include "LongPressAndFlickGesture.h"
#include "NativeEntry.h"
#include "NormalTextListExample.h"
#include "SwipeAndPinchExclusiveGesture.h"


namespace NativeModule {

napi_value CreateNativeNode(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);

    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetBorderWidth(column, DEFAULT_BORDER_WIDTH);
    SetColumnJustifyContent(column, ARKUI_FLEX_ALIGNMENT_START);
    SetColumnAlignItem(column, ARKUI_HORIZONTAL_ALIGNMENT_START);
    SetPadding(column, BLANK_10);

    FirstModule(column);

    auto blank1 = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetHeight(blank1, BLANK_20);
    nodeAPI->addChild(column, blank1);
    SecondModule(column);
    OH_ArkUI_NodeContent_AddNode(contentHandle, column);
    return nullptr;
}

napi_value CreateNativeNodeForGesture(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    // [Start get_module_interface]
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    // [End get_module_interface]
    
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    
    SetBorderWidth(column, DEFAULT_BORDER_WIDTH);
    SetColumnJustifyContent(column, ARKUI_FLEX_ALIGNMENT_START);
    SetColumnAlignItem(column, ARKUI_HORIZONTAL_ALIGNMENT_START);
    SetPadding(column, BLANK_10);
    
    FirstModuleForGesture(column);
    OH_ArkUI_NodeContent_AddNode(contentHandle, column);
    return nullptr;
}

napi_value CreateNativeNodeForLongPressAndSwipe(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto column = LongPressAndSwipeGesture();
    OH_ArkUI_NodeContent_AddNode(contentHandle, column);
    return nullptr;
}

napi_value CreateNativeNodeForLongPressAndFlick(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto column = LongPressAndFlickGesture();
    OH_ArkUI_NodeContent_AddNode(contentHandle, column);
    return nullptr;
}

napi_value CreateNativeNodeForSwipeAndPinchExclusive(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    auto column = SwipeAndPinchExclusiveGesture();
    OH_ArkUI_NodeContent_AddNode(contentHandle, column);
    return nullptr;
}

napi_value CreateNativeRoot(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};

    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle);
    NativeEntry::GetInstance()->SetContentHandle(contentHandle);

    // 创建文本列表
    auto list = CreateTextListExample();

    // 保持Native侧对象到管理类中，维护生命周期。
    NativeEntry::GetInstance()->SetRootNode(list);
    return nullptr;
}

napi_value DestroyNativeRoot(napi_env env, napi_callback_info info)
{
    // 从管理类中释放Native侧对象。
    NativeEntry::GetInstance()->DisposeRootNode();
    return nullptr;
}
} // namespace NativeModule
