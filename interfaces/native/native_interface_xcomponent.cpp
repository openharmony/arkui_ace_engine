/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include <new>

#include "native_interface_xcomponent.h"

#include "node/node_model.h"

#include "base/error/error_code.h"
#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "frameworks/core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"
#include "native_error_message_macros.h"

namespace {
int32_t ReturnNativeXComponentParamError(const char* functionName, const char* errorMessage)
{
    SET_ERROR_MESSAGE(OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER, functionName, errorMessage);
    return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
}

int32_t ReturnArkUIParamError(const char* functionName, const char* errorMessage)
{
    SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, functionName, errorMessage);
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t ReturnResultWithFunctionName(int32_t result, int32_t successCode, const char* functionName)
{
    if (result != successCode) {
        SET_ERROR_FUNCTION_NAME(functionName);
    }
    return result;
}

bool IsValidXComponentNode(ArkUI_NodeHandle node)
{
    return OHOS::Ace::NodeModel::IsValidArkUINode(node) &&
        (node->isBindNative || node->type == ARKUI_NODE_XCOMPONENT ||
            node->type == ARKUI_NODE_XCOMPONENT_TEXTURE);
}

bool CheckValidXComponentNode(ArkUI_NodeHandle node, const char* functionName)
{
    if (!IsValidXComponentNode(node)) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            functionName, "Node is invalid or not an XComponent node");
        return false;
    }
    return true;
}

const ArkUIXComponentModifier* GetArkUIXComponentModifierWithMessage(const char* functionName)
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (impl == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, functionName, "Native module not initialized");
        return nullptr;
    }
    auto nodeModifiers = impl->getNodeModifiers();
    if (nodeModifiers == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, functionName,
            "Node modifiers are not initialized");
        return nullptr;
    }
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    if (xComponentModifier == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, functionName,
            "XComponent modifier is not initialized");
        return nullptr;
    }
    return xComponentModifier;
}
} // namespace

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_NativeXComponent_GetXComponentId(OH_NativeXComponent* component, char* id, uint64_t* size)
{
    if ((component == nullptr) || (id == nullptr) || (size == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    if (((*size) == 0) || ((*size) > (OH_XCOMPONENT_ID_LEN_MAX + 1))) {
        LOGE("The referenced value of 'size' should be in the range "
            "(0, OH_XCOMPONENT_ID_LEN_MAX + 1]");
        return ReturnNativeXComponentParamError(__FUNCTION__, "size is out of range");
    }
    return ReturnResultWithFunctionName(
        component->GetXComponentId(id, size), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetXComponentSize(
    OH_NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height)
{
    if ((component == nullptr) || (window == nullptr) ||
        (width == nullptr) || (height == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetXComponentSize(window, width, height),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetXComponentOffset(
    OH_NativeXComponent* component, const void* window, double* x, double* y)
{
    if ((component == nullptr) || (window == nullptr) || (x == nullptr) || (y == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetXComponentOffset(window, x, y),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_TouchEvent* touchEvent)
{
    if ((component == nullptr) || (window == nullptr) || (touchEvent == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetTouchEvent(window, touchEvent), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointToolType(
    OH_NativeXComponent* component, uint32_t pointIndex, OH_NativeXComponent_TouchPointToolType* toolType)
{
    if ((component == nullptr) || (toolType == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetToolType(pointIndex, toolType), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointTiltX(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltX)
{
    if ((component == nullptr) || (tiltX == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetTiltX(pointIndex, tiltX), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointTiltY(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltY)
{
    if ((component == nullptr) || (tiltY == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetTiltY(pointIndex, tiltY), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointWindowX(OH_NativeXComponent* component, uint32_t pointIndex, float* windowX)
{
    if ((component == nullptr) || (windowX == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetWindowX(pointIndex, windowX),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointWindowY(OH_NativeXComponent* component, uint32_t pointIndex, float* windowY)
{
    if ((component == nullptr) || (windowY == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetWindowY(pointIndex, windowY), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointDisplayX(OH_NativeXComponent* component, uint32_t pointIndex, float* displayX)
{
    if ((component == nullptr) || (displayX == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetDisplayX(pointIndex, displayX), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchPointDisplayY(OH_NativeXComponent* component, uint32_t pointIndex, float* displayY)
{
    if ((component == nullptr) || (displayY == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetDisplayY(pointIndex, displayY),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetHistoricalPoints(OH_NativeXComponent* component, const void* window,
    int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints)
{
    if ((component == nullptr) || (window == nullptr) ||
        (size == nullptr) || (historicalPoints == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetHistoryPoints(window, size, historicalPoints), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetMouseEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_MouseEvent* mouseEvent)
{
    if ((component == nullptr) || (window == nullptr) || (mouseEvent == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "input parameter is null");
    }
    return ReturnResultWithFunctionName(
        component->GetMouseEvent(window, mouseEvent), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterCallback(OH_NativeXComponent* component, OH_NativeXComponent_Callback* callback)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterMouseEventCallback(
    OH_NativeXComponent* component, OH_NativeXComponent_MouseEvent_Callback* callback)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterMouseEventCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterFocusEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterFocusEventCallback(callback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterKeyEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterKeyEventCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterBlurEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterBlurEventCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetKeyEvent(OH_NativeXComponent* component, OH_NativeXComponent_KeyEvent** keyEvent)
{
    if ((component == nullptr) || (keyEvent == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or keyEvent is null");
    }
    return ReturnResultWithFunctionName(
        component->GetKeyEvent(keyEvent), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetKeyEventAction(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyAction* action)
{
    if ((keyEvent == nullptr) || (action == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "keyEvent or action is null");
    }
    (*action) = keyEvent->action;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventCode(OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyCode* code)
{
    if ((keyEvent == nullptr) || (code == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "keyEvent or code is null");
    }
    (*code) = keyEvent->code;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventSourceType(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_EventSourceType* sourceType)
{
    if ((keyEvent == nullptr) || (sourceType == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "keyEvent or sourceType is null");
    }
    (*sourceType) = keyEvent->sourceType;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventDeviceId(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* deviceId)
{
    if ((keyEvent == nullptr) || (deviceId == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "keyEvent or deviceId is null");
    }
    (*deviceId) = keyEvent->deviceId;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventTimestamp(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* timestamp)
{
    if ((keyEvent == nullptr) || (timestamp == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "keyEvent or timestamp is null");
    }
    (*timestamp) = keyEvent->timestamp;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_SetExpectedFrameRateRange(
    OH_NativeXComponent* component, OH_NativeXComponent_ExpectedRateRange* range)
{
    if (component == nullptr || range == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or range is null");
    }
    return ReturnResultWithFunctionName(
        component->SetExpectedFrameRateRange(range), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterOnFrameCallback(OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, uint64_t timestamp, uint64_t targetTimestamp))
{
    if (component == nullptr || callback == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterOnFrameCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_UnregisterOnFrameCallback(OH_NativeXComponent* component)
{
    if (component == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component is null");
    }
    return ReturnResultWithFunctionName(
        component->UnregisterOnFrameCallback(), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_AttachNativeRootNode(
    OH_NativeXComponent* component, ArkUI_NodeHandle root)
{
    if (component == nullptr || root == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or root node is null");
    }
    if (!OHOS::Ace::NodeModel::CheckIsCNode(root)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "root node is not a C node");
    }
    return ReturnResultWithFunctionName(
        component->AttachNativeRootNode(root->uiNodeHandle), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_DetachNativeRootNode(
    OH_NativeXComponent* component, ArkUI_NodeHandle root)
{
    if (component == nullptr || root == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or root node is null");
    }
    if (!OHOS::Ace::NodeModel::CheckIsCNode(root)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "root node is not a C node");
    }
    return ReturnResultWithFunctionName(
        component->DetachNativeRootNode(root->uiNodeHandle), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterUIInputEventCallback(OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event, ArkUI_UIInputEvent_Type type),
    ArkUI_UIInputEvent_Type type)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "component or callback is null");
    }
    if (type == ArkUI_UIInputEvent_Type::ARKUI_UIINPUTEVENT_TYPE_AXIS) {
        return ReturnResultWithFunctionName(
            component->RegisterUIAxisEventCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
    }
    return ReturnArkUIParamError(__FUNCTION__, "event type is not supported");
}

int32_t OH_NativeXComponent_SetNeedSoftKeyboard(OH_NativeXComponent* component, bool needSoftKeyboard)
{
    if (component == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component is null");
    }
    return ReturnResultWithFunctionName(
        component->SetNeedSoftKeyboard(needSoftKeyboard), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterSurfaceShowCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if (component == nullptr || callback == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterSurfaceShowCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterSurfaceHideCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if (component == nullptr || callback == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterSurfaceHideCallback(callback), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterOnTouchInterceptCallback(
    OH_NativeXComponent* component, HitTestMode (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterOnTouchInterceptCallback(callback),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetTouchEventSourceType(
    OH_NativeXComponent* component, int32_t pointId, OH_NativeXComponent_EventSourceType* sourceType)
{
    if (component == nullptr || sourceType == nullptr) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or sourceType is null");
    }
    return ReturnResultWithFunctionName(
        component->GetSourceType(pointId, sourceType), OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

OH_NativeXComponent* OH_NativeXComponent_GetNativeXComponent(ArkUI_NodeHandle node)
{
    if (node == nullptr ||
        (node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
        return nullptr;
    }
    auto nodeModifiers = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers();
    return reinterpret_cast<OH_NativeXComponent*>(
        nodeModifiers->getXComponentModifier()->getNativeXComponent(node->uiNodeHandle));
}

int32_t OH_NativeXComponent_GetNativeAccessibilityProvider(
    OH_NativeXComponent* component, ArkUI_AccessibilityProvider** handle)
{
    if ((component == nullptr) || (handle == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or handle is null");
    }
    return ReturnResultWithFunctionName(
        component->GetAccessibilityProvider(handle),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_NativeXComponent_RegisterKeyEventCallbackWithResult(
    OH_NativeXComponent* component, bool (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return ReturnNativeXComponentParamError(__FUNCTION__, "component or callback is null");
    }
    return ReturnResultWithFunctionName(
        component->RegisterKeyEventCallbackWithResult(callback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_StartImageAnalyzer(ArkUI_NodeHandle node, void* userData,
    void (*callback)(ArkUI_NodeHandle node, ArkUI_XComponent_ImageAnalyzerState statusCode, void* userData))
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (callback == nullptr) {
        return ReturnArkUIParamError(__FUNCTION__, "callback is null");
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    xComponentModifier->startImageAnalyzer(node->uiNodeHandle, node, userData,
        reinterpret_cast<XComponentAnalyzerCallback>(callback));
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_XComponent_StopImageAnalyzer(ArkUI_NodeHandle node)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    xComponentModifier->stopImageAnalyzer(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

OH_ArkUI_SurfaceHolder* OH_ArkUI_SurfaceHolder_Create(ArkUI_NodeHandle node)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return nullptr;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (impl == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Native module not initialized");
        return nullptr;
    }
    auto nodeModifiers = impl->getNodeModifiers();
    if (nodeModifiers == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node modifiers are not initialized");
        return nullptr;
    }
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    if (xComponentModifier == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "XComponent modifier is not initialized");
        return nullptr;
    }
    auto* surfaceHolder =
        reinterpret_cast<OH_ArkUI_SurfaceHolder*>(xComponentModifier->createSurfaceHolder(node->uiNodeHandle));
    if (surfaceHolder == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_INTERNAL_ERROR, __FUNCTION__, "Failed to create surface holder");
        return nullptr;
    }
    surfaceHolder->node_ = node;
    return surfaceHolder;
}

void OH_ArkUI_SurfaceHolder_Dispose(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    if (surfaceHolder == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "surfaceHolder is null");
        return;
    }
    auto node = surfaceHolder->node_;
    if (OHOS::Ace::NodeModel::IsValidArkUINode(node)) {
        const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
        if (impl == nullptr) {
            SET_ERROR_MESSAGE(
                OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Native module not initialized");
            return;
        }
        auto nodeModifiers = impl->getNodeModifiers();
        if (nodeModifiers == nullptr) {
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
                __FUNCTION__, "Node modifiers are not initialized");
            return;
        }
        auto xComponentModifier = nodeModifiers->getXComponentModifier();
        if (xComponentModifier == nullptr) {
            SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
                __FUNCTION__, "XComponent modifier is not initialized");
            return;
        }
        xComponentModifier->dispose(node->uiNodeHandle);
    }
    auto config = surfaceHolder->config_;
    if (config) {
        config->surfaceHolders_.erase(surfaceHolder);
    }
    surfaceHolder->config_ = nullptr;
    delete surfaceHolder;
}

int32_t OH_ArkUI_SurfaceHolder_SetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder, void* userData)
{
    if (surfaceHolder == nullptr) {
        return ReturnArkUIParamError(__FUNCTION__, "surfaceHolder is null");
    }
    surfaceHolder->userData_ = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void* OH_ArkUI_SurfaceHolder_GetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    if (surfaceHolder == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "surfaceHolder is null");
        return nullptr;
    }
    return surfaceHolder->userData_;
}

OH_ArkUI_SurfaceCallback* OH_ArkUI_SurfaceCallback_Create(void)
{
    OH_ArkUI_SurfaceCallback* surfaceCallback = new (std::nothrow) OH_ArkUI_SurfaceCallback();
    if (surfaceCallback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_INTERNAL_ERROR, __FUNCTION__,
            "Failed to create surface callback");
    }
    return surfaceCallback;
}

void OH_ArkUI_SurfaceCallback_Dispose(OH_ArkUI_SurfaceCallback* callback)
{
    if (callback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
        return;
    }
    delete callback;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(
    OH_ArkUI_SurfaceCallback* callback, void (*onSurfaceCreated)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    if (callback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
        return;
    }
    callback->OnSurfaceCreated = onSurfaceCreated;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceChanged)(OH_ArkUI_SurfaceHolder* surfaceHolder, uint64_t width, uint64_t height))
{
    if (callback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
        return;
    }
    callback->OnSurfaceChanged = onSurfaceChanged;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceDestroyed)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    if (callback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
        return;
    }
    callback->OnSurfaceDestroyed = onSurfaceDestroyed;
}

int32_t OH_ArkUI_SurfaceHolder_AddSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder, OH_ArkUI_SurfaceCallback* callback)
{
    if ((surfaceHolder == nullptr) || (callback == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "surfaceHolder or callback is null");
    }
    return ReturnResultWithFunctionName(
        surfaceHolder->AddSurfaceCallback(callback), OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder, OH_ArkUI_SurfaceCallback* callback)
{
    if ((surfaceHolder == nullptr) || (callback == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "surfaceHolder or callback is null");
    }
    return ReturnResultWithFunctionName(
        surfaceHolder->RemoveSurfaceCallback(callback), OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

OHNativeWindow* OH_ArkUI_XComponent_GetNativeWindow(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    if (surfaceHolder == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "surfaceHolder is null");
        return nullptr;
    }
    return surfaceHolder->nativeWindow_;
}

int32_t OH_ArkUI_XComponent_SetAutoInitialize(ArkUI_NodeHandle node, bool autoInitialize)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return ReturnResultWithFunctionName(
        xComponentModifier->setAutoInitialize(node->uiNodeHandle, autoInitialize),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_Initialize(ArkUI_NodeHandle node)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return ReturnResultWithFunctionName(
        xComponentModifier->initialize(node->uiNodeHandle),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_Finalize(ArkUI_NodeHandle node)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return ReturnResultWithFunctionName(
        xComponentModifier->finalize(node->uiNodeHandle), OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_IsInitialized(ArkUI_NodeHandle node, bool* isInitialized)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (isInitialized == nullptr) {
        return ReturnArkUIParamError(__FUNCTION__, "isInitialized is null");
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Bool value = 0;
    auto res = xComponentModifier->isInitialized(node->uiNodeHandle, &value);
    if (res != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    *isInitialized = value;
    return res;
}

int32_t OH_NativeXComponent_GetExtraMouseEventInfo(OH_NativeXComponent* component,
    OH_NativeXComponent_ExtraMouseEventInfo** extraMouseEventInfo)
{
    if ((component == nullptr) || (extraMouseEventInfo == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "component or extraMouseEventInfo is null");
    }
    return ReturnResultWithFunctionName(
        component->GetExtraMouseEventInfo(extraMouseEventInfo), OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_NativeXComponent_GetMouseEventModifierKeyStates(
    OH_NativeXComponent_ExtraMouseEventInfo* ExtraMouseEventInfo, uint64_t* keys)
{
    if ((ExtraMouseEventInfo == nullptr) || (keys == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "extraMouseEventInfo or keys is null");
    }
    (*keys) = ExtraMouseEventInfo->modifierKeyStates;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventModifierKeyStates(OH_NativeXComponent_KeyEvent* keyEvent, uint64_t* keys)
{
    if ((keyEvent == nullptr) || (keys == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "keyEvent or keys is null");
    }
    (*keys) = keyEvent->modifierKeyStates;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventNumLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isNumLockOn)
{
    if ((keyEvent == nullptr) || (isNumLockOn == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "keyEvent or isNumLockOn is null");
    }
    (*isNumLockOn) = keyEvent->isNumLockOn;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventCapsLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isCapsLockOn)
{
    if ((keyEvent == nullptr) || (isCapsLockOn == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "keyEvent or isCapsLockOn is null");
    }
    (*isCapsLockOn) = keyEvent->isCapsLockOn;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventScrollLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isScrollLockOn)
{
    if ((keyEvent == nullptr) || (isScrollLockOn == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "keyEvent or isScrollLockOn is null");
    }
    (*isScrollLockOn) = keyEvent->isScrollLockOn;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_XComponent_SetExpectedFrameRateRange(
    ArkUI_NodeHandle node, OH_NativeXComponent_ExpectedRateRange range)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Int32 min = range.min;
    ArkUI_Int32 max = range.max;
    ArkUI_Int32 expected = range.expected;
    return ReturnResultWithFunctionName(
        xComponentModifier->setExpectedFrameRateRange(node->uiNodeHandle, min, max, expected),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_RegisterOnFrameCallback(ArkUI_NodeHandle node,
    void (*callback)(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp))
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (callback == nullptr) {
        return ReturnArkUIParamError(__FUNCTION__, "callback is null");
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return ReturnResultWithFunctionName(
        xComponentModifier->registerOnFrameCallback(node->uiNodeHandle,
            reinterpret_cast<void(*)(void*, uint64_t, uint64_t)>(callback), node),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_UnregisterOnFrameCallback(ArkUI_NodeHandle node)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return ReturnResultWithFunctionName(
        xComponentModifier->unregisterOnFrameCallback(node->uiNodeHandle),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

int32_t OH_ArkUI_XComponent_SetNeedSoftKeyboard(ArkUI_NodeHandle node, bool needSoftKeyboard)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return ReturnResultWithFunctionName(
        xComponentModifier->setNeedSoftKeyboard(node->uiNodeHandle, needSoftKeyboard),
        OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

ArkUI_AccessibilityProvider* OH_ArkUI_AccessibilityProvider_Create(ArkUI_NodeHandle node)
{
    if (!CheckValidXComponentNode(node, __FUNCTION__)) {
        return nullptr;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return nullptr;
    }
    auto accessibilityProvider = reinterpret_cast<ArkUI_AccessibilityProvider*>(
        xComponentModifier->createAccessibilityProvider(node->uiNodeHandle));
    if (accessibilityProvider == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_INTERNAL_ERROR, __FUNCTION__,
            "Failed to create accessibility provider");
    }
    return accessibilityProvider;
}

void OH_ArkUI_AccessibilityProvider_Dispose(ArkUI_AccessibilityProvider* provider)
{
    if (provider == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "provider is null");
        return;
    }
    auto xComponentModifier = GetArkUIXComponentModifierWithMessage(__FUNCTION__);
    if (xComponentModifier == nullptr) {
        return;
    }
    xComponentModifier->disposeAccessibilityProvider(provider);
}

void OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceShow)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    if (callback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
        return;
    }
    callback->onSurfaceShow = onSurfaceShow;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceHide)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    if (callback == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "callback is null");
        return;
    }
    callback->onSurfaceHide = onSurfaceHide;
}

ArkUI_XComponentSurfaceConfig* OH_ArkUI_XComponentSurfaceConfig_Create()
{
    ArkUI_XComponentSurfaceConfig* surfaceConfig =
        new (std::nothrow) ArkUI_XComponentSurfaceConfig();
    if (surfaceConfig == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_INTERNAL_ERROR, __FUNCTION__,
            "Failed to create XComponent surface config");
    }
    return surfaceConfig;
}

void OH_ArkUI_XComponentSurfaceConfig_Dispose(ArkUI_XComponentSurfaceConfig* config)
{
    if (config == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "config is null");
        return;
    }
    for (auto holder : config->surfaceHolders_) {
        if (holder) {
            holder->config_ = nullptr;
        }
    }
    config->surfaceHolders_.clear();
    delete config;
}

void OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(ArkUI_XComponentSurfaceConfig* config, bool isOpaque)
{
    if (config == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "config is null");
        return;
    }
    config->isOpaque_ = isOpaque;
    for (auto holder : config->surfaceHolders_) {
        if (holder) {
            holder->SetSurfaceConfig(config);
        }
    }
}

int32_t OH_ArkUI_SurfaceHolder_SetSurfaceConfig(
    OH_ArkUI_SurfaceHolder* surfaceHolder, ArkUI_XComponentSurfaceConfig* config)
{
    if ((surfaceHolder == nullptr) || (config == nullptr)) {
        return ReturnArkUIParamError(__FUNCTION__, "surfaceHolder or config is null");
    }
    config->surfaceHolders_.insert(surfaceHolder);
    return ReturnResultWithFunctionName(
        surfaceHolder->SetSurfaceConfig(config), OHOS::Ace::ERROR_CODE_NO_ERROR, __FUNCTION__);
}

#ifdef __cplusplus
};
#endif
