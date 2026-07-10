/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "arkui/native_node_napi.h"
#include "arkui/native_interface.h"
#include "napi/native_api.h"
#include "embedded.h"
//[Start embeddedComponentCTest_start]
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <AbilityKit/ability_base/want.h> //引用元能力want头文件

// 注册事件
void onError(int32_t code, const char *name, const char *message) {}
void onTerminated(int32_t code, AbilityBase_Want *want) {}
const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
#define SIZE_300 300
#define SIZE_401 401
#define SIZE_480 480
//[StartExclude embeddedComponentCTest_start]

napi_value embeddedNode(napi_env env, napi_callback_info info)
{
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "PluginManager", "CreateNativeNode napi_get_cb_info failed");
    }
    ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle);
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI);
    //[EndExclude embeddedComponentCTest_start]
    // 创建节点
    ArkUI_NodeHandle embeddedNode = nodeAPI->createNode(ARKUI_NODE_EMBEDDED_COMPONENT);
    // 设置属性
    AbilityBase_Element Element = {.bundleName = "com.example.uiextensionandaccessibility",
                                   .abilityName = "ExampleEmbeddedAbility",
                                   .moduleName = "entry"};       // 由元能力提供接口
    AbilityBase_Want *want = OH_AbilityBase_CreateWant(Element); // 由元能力提供接口
    if (want == nullptr) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AbilityBase_Want", "~PluginManager");
    }
    ArkUI_AttributeItem itemobjwant = {.object = want};
    nodeAPI->setAttribute(embeddedNode, NODE_EMBEDDED_COMPONENT_WANT, &itemobjwant);

    auto embeddedNode_option = OH_ArkUI_EmbeddedComponentOption_Create();
    auto onErrorCallback = onError;
    auto onTerminatedCallback = onTerminated;
    OH_ArkUI_EmbeddedComponentOption_SetOnError(embeddedNode_option, onErrorCallback);
    OH_ArkUI_EmbeddedComponentOption_SetOnTerminated(embeddedNode_option, onTerminatedCallback);

    ArkUI_AttributeItem itemobjembeddedNode = {.object = embeddedNode_option};
    nodeAPI->setAttribute(embeddedNode, NODE_EMBEDDED_COMPONENT_OPTION, &itemobjembeddedNode);

    // 设置基本属性，如宽高
    ArkUI_NumberValue value[] = {SIZE_480};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    value[0].f32 = SIZE_300;
    nodeAPI->setAttribute(embeddedNode, NODE_WIDTH, &item);
    nodeAPI->setAttribute(embeddedNode, NODE_HEIGHT, &item);

    // 创建Column
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    nodeAPI->setAttribute(column, NODE_WIDTH, &item);
    ArkUI_NumberValue column_bc[] = {{.u32 = 0xFFF00BB}};
    ArkUI_AttributeItem column_item = {column_bc, 1};
    nodeAPI->setAttribute(column, NODE_BACKGROUND_COLOR, &column_item);
    ArkUI_AttributeItem column_id = {.string = "Column_CAPI"};
    nodeAPI->setAttribute(column, NODE_ID, &column_id);

    // 上树
    nodeAPI->addChild(column, embeddedNode);
    //[End embeddedComponentCTest_start]
    int32_t result = OH_ArkUI_NodeContent_AddNode(nodeContentHandle, column);
    napi_value retValue = 0;
    napi_create_int32(env, result, &retValue);
    if (result == SIZE_401) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "OH_ArkUI_NodeContent_AddNode_Result", "result");
    }
    napi_value exports;

    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }
    return exports;
}
