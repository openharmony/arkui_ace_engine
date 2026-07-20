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

#include "common.h"
#include "function.h"
#include "napi/native_api.h"
#include <arkui/native_interface.h>
#include <arkui/native_key_event.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <arkui/native_type.h>
#include <cstdint>
#include <cstdio>
#include <hilog/log.h>
#include <iostream>
#include <string>

#include "manager.h"

static ArkUI_NativeNodeAPI_1* nodeAPI = nullptr;

namespace NativeXComponentSample {

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;

Manager Manager::manager_;

Manager::~Manager()
{
    DisposeRootNode();
}

void Manager::DisposeRootNode()
{
    if (contentHandle_ != nullptr && rootNode_ != nullptr) {
        // 从NodeContent上卸载组件
        OH_ArkUI_NodeContent_RemoveNode(contentHandle_, rootNode_);
        nodeAPI->disposeNode(rootNode_);
        rootNode_ = nullptr;
    }
}

// 示例入口函数，创建根节点和初始化UI界面
void SampleEntry(ArkUI_NodeContentHandle contentHandle)
{
    // 根节点
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    SetWidthPercent(column, 1);
    SetHeightPercent(column, 1);
    SetColumnJustifyContent(column, ARKUI_FLEX_ALIGNMENT_START);
    SetColumnAlignItem(column, ARKUI_HORIZONTAL_ALIGNMENT_START);

    FirstModule(column);

    // 添加Native组件到NodeContent上用于挂载显示
    OH_ArkUI_NodeContent_AddNode(contentHandle, column);
}

// 创建原生节点N-API接口，接收NodeContent对象并初始化UI
napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }

    size_t argc = 1;
    napi_value args[1] = { nullptr };
    if (napi_get_cb_info(env, info, &argc, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
        return nullptr;
    }

    if (argc < 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }

    // 获取NodeContent
    ArkUI_NodeContentHandle contentHandle;
    if (OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &contentHandle) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager",
            "CreateNativeNode GetNodeContentFromNapiValue failed");
        return nullptr;
    }

    // 获取NodeAPI
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);

    auto manager = Manager::GetInstance();
    manager->SetContentHandle(contentHandle);

    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        // 调用FirstModule创建UI
        SampleEntry(contentHandle);

        // 保持Native侧对象到管理类中，维护生命周期
        // 注意：这里实际创建的根节点是column，但在SampleEntry中没有保存
        // 如果需要保存，需要在SampleEntry中返回column句柄
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "Input event sample UI created successfully");
    }

    return nullptr;
}

// 销毁原生节点N-API接口
napi_value Manager::DestroyNativeNode(napi_env env, napi_callback_info info)
{
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "DestroyNativeNode env or info is null");
        return nullptr;
    }

    auto manager = Manager::GetInstance();
    if (manager != nullptr) {
        manager->DisposeRootNode();
    }

    return nullptr;
}
} // namespace NativeXComponentSample
