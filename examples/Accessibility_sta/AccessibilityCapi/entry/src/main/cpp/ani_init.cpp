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
#include "manager/AccessibilityManager.h"

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;
#define SIZE_300 300

ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;

struct UserData {
    ArkUI_NodeHandle component1 = nullptr;
    ArkUI_NodeHandle component2 = nullptr;
};

ArkUI_NodeHandle CreateCustomNode(const char *id)
{
    ArkUI_NodeHandle customNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);

    ArkUI_AttributeItem idItem = {.string = id};
    nodeAPI->setAttribute(customNode, NODE_ID, &idItem);

    ArkUI_NumberValue sizeValue[] = {{.f32 = SIZE_300}};
    ArkUI_AttributeItem sizeItem = {sizeValue, sizeof(sizeValue) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(customNode, NODE_WIDTH, &sizeItem);
    nodeAPI->setAttribute(customNode, NODE_HEIGHT, &sizeItem);

    ArkUI_NumberValue bgValue[] = {{.u32 = 0xFFEEEEEE}};
    ArkUI_AttributeItem bgItem = {bgValue, 1};
    nodeAPI->setAttribute(customNode, NODE_BACKGROUND_COLOR, &bgItem);

    RegisterAccessibilityProvider(customNode, id);

    return customNode;
}

static void CreateSingleNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                             ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCapi", "CreateSingleNode called");
    if ((env == nullptr) || (nodeContent == nullptr)) {
        return;
    }
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    auto ret = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, nodeContent, &nodeContentHandle);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityCapi",
                     "GetNodeContentFromAniValue failed, ret=%{public}d", ret);
        return;
    }

    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr) {
        auto *data = new UserData();
        data->component1 = CreateCustomNode("xComponentIdSingle");
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, data->component1);
        OH_ArkUI_NodeContent_SetUserData(nodeContentHandle, data);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCapi", "CreateSingleNode success");
    }
}

static void CreateMultiNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                            ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCapi", "CreateMultiNode called");
    if ((env == nullptr) || (nodeContent == nullptr)) {
        return;
    }
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    auto ret = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, nodeContent, &nodeContentHandle);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityCapi",
                     "GetNodeContentFromAniValue failed, ret=%{public}d", ret);
        return;
    }

    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr) {
        auto *data = new UserData();
        data->component1 = CreateCustomNode("xComponentId1");
        data->component2 = CreateCustomNode("xComponentId2");
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, data->component1);
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, data->component2);
        OH_ArkUI_NodeContent_SetUserData(nodeContentHandle, data);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCapi", "CreateMultiNode success");
    }
}

static void DestroyNativeNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                              ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCapi", "DestroyNativeNode called");
    if ((env == nullptr) || (nodeContent == nullptr)) {
        return;
    }
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    auto ret = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, nodeContent, &nodeContentHandle);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        return;
    }

    if (nodeAPI != nullptr && nodeAPI->disposeNode != nullptr) {
        void *data = OH_ArkUI_NodeContent_GetUserData(nodeContentHandle);
        if (data != nullptr) {
            auto *userData = reinterpret_cast<UserData *>(data);
            if (userData->component1 != nullptr) {
                OH_ArkUI_NodeContent_RemoveNode(nodeContentHandle, userData->component1);
                nodeAPI->disposeNode(userData->component1);
                userData->component1 = nullptr;
            }
            if (userData->component2 != nullptr) {
                OH_ArkUI_NodeContent_RemoveNode(nodeContentHandle, userData->component2);
                nodeAPI->disposeNode(userData->component2);
                userData->component2 = nullptr;
            }
            delete userData;
            OH_ArkUI_NodeContent_SetUserData(nodeContentHandle, nullptr);
        }
    }
}

static ani_status bindCase(ani_vm *vm, const char *clsName)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_INVALID_VERSION;
    }

    ani_class cls{};
    if (ANI_OK != env->FindClass(clsName, &cls)) {
        return ANI_INVALID_ARGS;
    }

    const char *sig = "C{arkui.NodeContent.NodeContent}:";
    std::array<ani_native_function, 3> methods = {
        ani_native_function{"createSingleNode", sig, reinterpret_cast<void *>(CreateSingleNode)},
        ani_native_function{"createMultiNode", sig, reinterpret_cast<void *>(CreateMultiNode)},
        ani_native_function{"destroyNativeNode", sig, reinterpret_cast<void *>(DestroyNativeNode)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        return ANI_INVALID_TYPE;
    };
    return ANI_OK;
}


ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCapi", "entering libentry.so's ANI_Constructor");
    bindCase(vm, "entry.src.main.ets.pages.Index.NativeMethods");
    *result = ANI_VERSION_1;
    return ANI_OK;
}
