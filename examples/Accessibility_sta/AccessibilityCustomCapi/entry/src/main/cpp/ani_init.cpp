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

#include "ani/ani.h"
#include <array>

#include "arkui/native_type.h"
#include "arkui/native_node.h"
#include "arkui/native_node_ani.h"
#include "arkui/native_interface.h"
#include "hilog/log.h"

#include "AccessibilityMaker.h"
#include "AccessibilityDialog.h"
#include "AccessibilityDialogSubWindow.h"

static ArkUI_NativeNodeAPI_1 *GetNodeAPI()
{
    return reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
}

static bool GetNodeContentHandle(ani_env *env, ani_object nodeContent, ArkUI_NodeContentHandle &handle)
{
    if ((env == nullptr) || (nodeContent == nullptr)) {
        return false;
    }
    auto ret = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, nodeContent, &handle);
    if (ret != ARKUI_ERROR_CODE_NO_ERROR) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                     "GetNodeContentFromAniValue failed, ret=%{public}d", ret);
        return false;
    }
    return true;
}

static void CreateNativeAccessibilityNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                                          ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCustom", "CreateNativeAccessibilityNode called");
    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    if (!GetNodeContentHandle(env, nodeContent, nodeContentHandle)) {
        return;
    }
    auto *nodeAPI = GetNodeAPI();
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        ArkUI_NodeHandle testNode = AccessibilityMaker::CreateNativeNode();
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, testNode);
    }
}

static void CreateNativeAccessibilityNodeMultiple([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                                                  ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                 "CreateNativeAccessibilityNodeMultiple called");
    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    if (!GetNodeContentHandle(env, nodeContent, nodeContentHandle)) {
        return;
    }
    auto *nodeAPI = GetNodeAPI();
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        ArkUI_NodeHandle testNode = AccessibilityMaker::CreateNativeNode_multiple();
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, testNode);
    }
}

static void CreateNativeAccessibilityNoCustom([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                                              ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                 "CreateNativeAccessibilityNoCustom called");
    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    if (!GetNodeContentHandle(env, nodeContent, nodeContentHandle)) {
        return;
    }
    auto *nodeAPI = GetNodeAPI();
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        ArkUI_NodeHandle testNode = AccessibilityMaker::CreateNativeNoCustom();
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, testNode);
    }
}

static void CreateNativeAccessibilityNodeDialog([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
                                                ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                 "CreateNativeAccessibilityNodeDialog called");
    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    if (!GetNodeContentHandle(env, nodeContent, nodeContentHandle)) {
        return;
    }
    auto *nodeAPI = GetNodeAPI();
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        ArkUI_NodeHandle node = nodeAPI->createNode(ARKUI_NODE_TEXT);
        AccessibilityDialogSubWindow::MainViewMethod(nodeContentHandle);
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, node);
    }
}

static void CreateNativeAccessibilityNodeDialogSubWindow([[maybe_unused]] ani_env *env,
                                                         [[maybe_unused]] ani_object object, ani_object nodeContent)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                 "CreateNativeAccessibilityNodeDialogSubWindow called");
    ArkUI_NodeContentHandle nodeContentHandle = nullptr;
    if (!GetNodeContentHandle(env, nodeContent, nodeContentHandle)) {
        return;
    }
    auto *nodeAPI = GetNodeAPI();
    if (nodeAPI != nullptr && nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
        ArkUI_NodeHandle node = nodeAPI->createNode(ARKUI_NODE_TEXT);
        AccessibilityDialog::MainViewMethod(nodeContentHandle);
        OH_ArkUI_NodeContent_AddNode(nodeContentHandle, node);
    }
}

static ani_status BindNativeMethod(ani_vm *vm, const char *clsName, const char *methodName, void *impl)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_INVALID_VERSION;
    }

    ani_class cls{};
    if (ANI_OK != env->FindClass(clsName, &cls)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                     "FindClass failed: %{public}s", clsName);
        return ANI_INVALID_ARGS;
    }

    const char *sig = "C{arkui.NodeContent.NodeContent}:";
    std::array<ani_native_function, 1> methods = {
        ani_native_function{methodName, sig, impl},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "AccessibilityCustom",
                     "BindStaticNativeMethods failed for %{public}s", clsName);
        return ANI_INVALID_TYPE;
    }
    return ANI_OK;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "AccessibilityCustom", "ANI_Constructor enter");
    BindNativeMethod(vm, "entry.src.main.ets.pages.PageAccessibility.NativeMethods",
                     "createNativeAccessibilityNode",
                     reinterpret_cast<void *>(CreateNativeAccessibilityNode));
    BindNativeMethod(vm, "entry.src.main.ets.pages.PageAccessibilityMultiple.NativeMethods",
                     "CreateNativeAccessibilityNodeMultiple",
                     reinterpret_cast<void *>(CreateNativeAccessibilityNodeMultiple));
    BindNativeMethod(vm, "entry.src.main.ets.pages.PageNoCustom.NativeMethods",
                     "createNativeAccessibilityNoCustom",
                     reinterpret_cast<void *>(CreateNativeAccessibilityNoCustom));
    BindNativeMethod(vm, "entry.src.main.ets.pages.PageCustomDialog.NativeMethods",
                     "CreateNativeAccessibilityNodeDialog",
                     reinterpret_cast<void *>(CreateNativeAccessibilityNodeDialog));
    BindNativeMethod(vm, "entry.src.main.ets.pages.PageCustomDialogSubWindow.NativeMethods",
                     "CreateNativeAccessibilityNodeDialogSubWindow",
                     reinterpret_cast<void *>(CreateNativeAccessibilityNodeDialogSubWindow));
    *result = ANI_VERSION_1;
    return ANI_OK;
}
