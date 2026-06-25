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

#include "focus_manager.h"

#include <arkui/native_interface.h>
#include <cstdint>
#include <hilog/log.h>

#include "container.h"
#include "arkui/native_interface_focus.h"


namespace NativeXComponentSample {

static ArkUI_NativeNodeAPI_1* g_nodeAPI = nullptr;

int FocusManager::RequestFocus(const char* nodeId)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "RequestFocus: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "RequestFocus: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    // 获取NodeAPI实例
    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "RequestFocus: g_nodeAPI is null");
        return -1;
    }

    // 使用原生接口OH_ArkUI_FocusRequest请求焦点
    ArkUI_ErrorCode result = OH_ArkUI_FocusRequest(nodeHandle);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "RequestFocus: OH_ArkUI_FocusRequest result=%{public}d for node %{public}s", result, nodeId);

    if (result == ARKUI_ERROR_CODE_NO_ERROR) {
        currentFocusNodeId_ = std::string(nodeId);
        RegisterNodeHandle(std::string(nodeId), nodeHandle);
        return 0;
    } else {
        const char* errorMsg = "未知错误";
        switch (result) {
            case ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE:
                errorMsg = "节点不可聚焦";
                break;
            case ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR:
                errorMsg = "节点祖先不可聚焦";
                break;
            case ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT:
                errorMsg = "节点不存在";
                break;
            default:
                errorMsg = "其他错误";
                break;
        }
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "RequestFocus failed: %{public}s (code=%{public}d)", errorMsg, result);
        return result;
    }
}

int FocusManager::RequestFocusAsync(const char* nodeId)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "RequestFocus: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "RequestFocus: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    // 获取NodeAPI实例
    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "RequestFocus: g_nodeAPI is null");
        return -1;
    }

    // 先设置节点为可聚焦
    ArkUI_NumberValue focusableValue[] = { { .i32 = 1 } };
    ArkUI_AttributeItem focusableItem = { focusableValue, 1 };
    g_nodeAPI->setAttribute(nodeHandle, NODE_FOCUSABLE, &focusableItem);
    
    ArkUI_NumberValue requetValue[] = { { .i32 = 1 } };
    ArkUI_AttributeItem requetItem = { requetValue, 1 };
    int result = g_nodeAPI->setAttribute(nodeHandle, NODE_FOCUS_STATUS, &requetItem);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "RequestFocus: NODE_FOCUS_STATUS result=%{public}d for node %{public}s", result, nodeId);
    return result;
}

void FocusManager::ClearFocus(void* uiContext)
{
    // 使用原生接口OH_ArkUI_FocusClear清除焦点到root scope
    if (uiContext) {
        OH_ArkUI_FocusClear(static_cast<ArkUI_ContextHandle>(uiContext));
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager", "ClearFocus: OH_ArkUI_FocusClear called");
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "ClearFocus: uiContext is null");
    }

    currentFocusNodeId_.clear();
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager", "ClearFocus: success");
}

void FocusManager::ActivateFocus(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive)
{
    OH_ArkUI_FocusActivate(uiContext, isActive, !isActive);
    isActive_ = isActive;
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "ActivateFocus: isActive=%{public}d, isAutoInactive=%{public}d", isActive, !isActive);
}

void FocusManager::SetAutoTransfer(void* uiContext, bool autoTransfer)
{
    // 使用原生接口OH_ArkUI_FocusSetAutoTransfer设置焦点自动转移
    if (uiContext) {
        OH_ArkUI_FocusSetAutoTransfer(static_cast<ArkUI_ContextHandle>(uiContext), autoTransfer);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
            "SetAutoTransfer: OH_ArkUI_FocusSetAutoTransfer called with autoTransfer=%{public}d", autoTransfer);
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetAutoTransfer: uiContext is null");
    }

    autoTransfer_ = autoTransfer;
    OH_LOG_Print(
        LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager", "SetAutoTransfer: autoTransfer=%{public}d", autoTransfer);
}

void FocusManager::SetKeyProcessingMode(void* uiContext, FocusKeyProcessingMode mode)
{
    // 将FocusKeyProcessingMode映射到ArkUI_KeyProcessingMode
    ArkUI_KeyProcessingMode arkuiMode;
    switch (mode) {
        case FOCUS_KEY_PROCESSING_MODE_NAVIGATION:
            arkuiMode = ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION;
            break;
        case FOCUS_KEY_PROCESSING_MODE_ANCESTOR_EVENT:
            arkuiMode = ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT;
            break;
        default:
            arkuiMode = ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION;
            break;
    }

    // 使用原生接口OH_ArkUI_FocusSetKeyProcessingMode设置按键处理模式
    if (uiContext) {
        OH_ArkUI_FocusSetKeyProcessingMode(static_cast<ArkUI_ContextHandle>(uiContext), arkuiMode);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
            "SetKeyProcessingMode: OH_ArkUI_FocusSetKeyProcessingMode called with mode=%{public}d", arkuiMode);
    } else {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetKeyProcessingMode: uiContext is null");
    }

    keyProcessingMode_ = mode;
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager", "SetKeyProcessingMode: mode=%{public}d", mode);
}

int FocusManager::SetNodeFocusable(const char* nodeId, bool focusable)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeFocusable: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "SetNodeFocusable: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeFocusable: g_nodeAPI is null");
        return -1;
    }

    // 设置节点可聚焦属性
    ArkUI_NumberValue focusableValue[] = { { .i32 = focusable ? 1 : 0 } };
    ArkUI_AttributeItem focusableItem = { focusableValue, 1 };
    g_nodeAPI->setAttribute(nodeHandle, NODE_FOCUSABLE, &focusableItem);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "SetNodeFocusable: success for node %{public}s, focusable=%{public}d", nodeId, focusable);
    return 0;
}

std::string FocusManager::GetCurrentFocusNodeId() const
{
    return currentFocusNodeId_;
}

void FocusManager::RegisterNodeHandle(const std::string& nodeId, ArkUI_NodeHandle nodeHandle)
{
    nodeHandleMap_[nodeId] = nodeHandle;
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager", "RegisterNodeHandle: registered node %{public}s",
        nodeId.c_str());
}

int FocusManager::SetFocusOnTouch(const char* nodeId, bool focusOnTouch)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "RequestFocus: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "RequestFocus: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    // 获取NodeAPI实例
    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    // 设置FocusOnTouch
    ArkUI_NumberValue focusValue[] = { { .i32 = focusOnTouch ? 1 : 0 } };
    ArkUI_AttributeItem focusItem = { focusValue, 1 };
    int result = g_nodeAPI->setAttribute(nodeHandle, NODE_FOCUS_ON_TOUCH, &focusItem);
    return result;
}

int FocusManager::SetNodeDefaultFocus(const char* nodeId, bool isDefault)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeDefaultFocus: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "SetNodeDefaultFocus: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeDefaultFocus: g_nodeAPI is null");
        return -1;
    }

    // 设置默认焦点
    ArkUI_NumberValue defaultValue[] = { { .i32 = isDefault ? 1 : 0 } };
    ArkUI_AttributeItem defaultItem = { defaultValue, 1 };
    int result = g_nodeAPI->setAttribute(nodeHandle, NODE_DEFAULT_FOCUS, &defaultItem);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "SetNodeDefaultFocus: result=%{public}d for node %{public}s, isDefault=%{public}d", result, nodeId, isDefault);
    return result;
}

int FocusManager::SetNodeFocusBox(const char* nodeId, float distance, float width, uint32_t color)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeFocusBox: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "SetNodeFocusBox: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeFocusBox: g_nodeAPI is null");
        return -1;
    }

    // 设置焦点框样式 - 根据CAPI定义：distance, width, color
    ArkUI_NumberValue focusBoxValues[] = {
        { .f32 = distance }, // 焦点框距离组件边缘的距离
        { .f32 = width },    // 焦点框宽度
        { .u32 = color }     // 焦点框颜色
    };
    ArkUI_AttributeItem focusBoxItem = { focusBoxValues, 3 };
    int result = g_nodeAPI->setAttribute(nodeHandle, NODE_FOCUS_BOX, &focusBoxItem);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "SetNodeFocusBox: result=%{public}d for node %{public}s, distance=%{public}f, width=%{public}f, "
        "color=%{public}u",
        result, nodeId, distance, width, color);
    return result;
}

int FocusManager::SetNodeNextFocus(const char* nodeId, const char* nextNodeId, int direction)
{
    if (!nodeId || !nextNodeId) {
        OH_LOG_Print(
            LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeNextFocus: nodeId or nextNodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "SetNodeNextFocus: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    ArkUI_NodeHandle nextNodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nextNodeId, &nextNodeHandle);
    if (!nextNodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "SetNodeNextFocus: nextNodeHandle is null for id %{public}s", nextNodeId);
        return -1;
    }

    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeNextFocus: g_nodeAPI is null");
        return -1;
    }

    // 设置下一个焦点 - 根据CAPI定义：direction和next node handle
    ArkUI_NumberValue directionValue[] = { { .i32 = direction } };
    ArkUI_AttributeItem nextFocusItem = { .value = directionValue, .size = 1, .object = nextNodeHandle };

    int result = g_nodeAPI->setAttribute(nodeHandle, NODE_NEXT_FOCUS, &nextFocusItem);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "SetNodeNextFocus: result=%{public}d for node %{public}s -> %{public}s, direction=%{public}d", result, nodeId,
        nextNodeId, direction);
    return result;
}

int FocusManager::SetNodeTabStop(const char* nodeId, bool tabStop)
{
    if (!nodeId) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeTabStop: nodeId is null");
        return -1;
    }

    ArkUI_NodeHandle nodeHandle;
    OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(nodeId, &nodeHandle);
    if (!nodeHandle) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager",
            "SetNodeTabStop: nodeHandle is null for id %{public}s", nodeId);
        return -1;
    }

    if (!g_nodeAPI) {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeAPI);
    }

    if (!g_nodeAPI) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "FocusManager", "SetNodeTabStop: g_nodeAPI is null");
        return -1;
    }

    // 设置Tab停止属性
    ArkUI_NumberValue tabStopValue[] = { { .i32 = tabStop ? 1 : 0 } };
    ArkUI_AttributeItem tabStopItem = { tabStopValue, 1 };
    int result = g_nodeAPI->setAttribute(nodeHandle, NODE_TAB_STOP, &tabStopItem);

    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "FocusManager",
        "SetNodeTabStop: result=%{public}d for node %{public}s, tabStop=%{public}d", result, nodeId, tabStop);
    return result;
}

} // namespace NativeXComponentSample
