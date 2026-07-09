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

#include "ani/ani.h"
#include <array>

#include "arkui/native_type.h"
#include "arkui/native_node.h"
#include "arkui/native_node_ani.h"
#include "arkui/native_interface.h"
#include "hilog/log.h"
//[Start embeddedComponentCTest_start]
#include <arkui/native_node.h>
#include <arkui/native_type.h>

void onError(int32_t code, const char *name, const char *message) {}
void onTerminated(int32_t code, void *want) {}
const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
#define SIZE_300 300
#define SIZE_401 401
#define SIZE_480 480

ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;

struct UserData {
    ArkUI_NodeHandle component = nullptr;
};

ArkUI_NodeHandle CreateEmbeddedNode()
{
    ArkUI_NodeHandle embeddedNode = nodeAPI->createNode(ARKUI_NODE_EMBEDDED_COMPONENT);

    ArkUI_NumberValue sizeValue[] = {SIZE_300};
    ArkUI_AttributeItem sizeItem = {sizeValue, sizeof(sizeValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(embeddedNode, NODE_WIDTH, &sizeItem);
    nodeAPI->setAttribute(embeddedNode, NODE_HEIGHT, &sizeItem);

    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    nodeAPI->setAttribute(column, NODE_WIDTH, &sizeItem);
    ArkUI_NumberValue column_bc[] = {{.u32 = 0xFFF00BB}};
    ArkUI_AttributeItem column_item = {column_bc, 1};
    nodeAPI->setAttribute(column, NODE_BACKGROUND_COLOR, &column_item);
    ArkUI_AttributeItem column_id = {.string = "Column_CAPI"};
    nodeAPI->setAttribute(column, NODE_ID, &column_id);

    nodeAPI->addChild(column, embeddedNode);
    return column;
}
//[End embeddedComponentCTest_start]

static void CreateNativeNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                             ani_object nodeContent)
{
    if ((env == nullptr) || (nodeContent == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent", "CreateNativeNode failed");
        return;
    }
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;

    auto ret = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, nodeContent, &nodeContentHandle);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent",
                     "CreateNativeNode get NodeContentHandle failed");
    }

    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr) {
            ArkUI_NodeHandle component = CreateEmbeddedNode();
            OH_ArkUI_NodeContent_AddNode(nodeContentHandle, component);
            auto *data = new UserData();
            data->component = component;
            OH_ArkUI_NodeContent_SetUserData(nodeContentHandle, data);
        }
    }
}

static void DestroyNativeNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                              ani_object nodeContent)
{
    if ((env == nullptr) || (nodeContent == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent", "DestroyNativeNode failed");
        return;
    }
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;

    auto ret = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, nodeContent, &nodeContentHandle);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent",
                     "DestroyNativeNode get NodeContentHandle failed");
    }

    if (nodeAPI != nullptr && nodeAPI->disposeNode != nullptr) {
        void *data = OH_ArkUI_NodeContent_GetUserData(nodeContentHandle);
        if (data != nullptr) {
            auto *userData = reinterpret_cast<UserData *>(data);
            OH_ArkUI_NodeContent_RemoveNode(nodeContentHandle, userData->component);
            nodeAPI->disposeNode(userData->component);
            userData->component = nullptr;
            delete userData;
            userData = nullptr;
            OH_ArkUI_NodeContent_SetUserData(nodeContentHandle, nullptr);
            data = nullptr;
        }
    }
}

static ani_status bindCase(ani_vm *vm, const char *clsName)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent", "Unsupported ANI_VERSION_1");
        return ANI_INVALID_VERSION;
    }

    ani_class cls{};
    if (ANI_OK != env->FindClass(clsName, &cls)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent", "Not found %{public}s", clsName);
        return ANI_INVALID_ARGS;
    }

    const char *createNativeNodeSignature = "C{arkui.NodeContent.NodeContent}:";
    const char *destroyNativeNodeSignature = "C{arkui.NodeContent.NodeContent}:";
    std::array<ani_native_function, 2> methods = {
        ani_native_function{"createNativeNode", createNativeNodeSignature, reinterpret_cast<void *>(CreateNativeNode)},
        ani_native_function{"destroyNativeNode", destroyNativeNodeSignature,
                            reinterpret_cast<void *>(DestroyNativeNode)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent",
                     "Cannot bind native methods to %{public}s", clsName);
        return ANI_INVALID_TYPE;
    };
    return ANI_OK;
}


ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "EmbeddedComponent", "entering libentry.so's ANI_Constructor");
    bindCase(vm, "entry.src.main.ets.pages.ShowEmbeddedComponent.ShowPage.NativeMethods");
    *result = ANI_VERSION_1;
    return ANI_OK;
}
