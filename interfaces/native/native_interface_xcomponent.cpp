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

#include "native_interface_xcomponent.h"

#include "node/node_model.h"

#include "base/error/error_code.h"
#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "frameworks/core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "frameworks/core/accessibility/native_interface_accessibility_provider.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_NativeXComponent_GetXComponentId(OH_NativeXComponent* component, char* id, uint64_t* size)
{
    if ((component == nullptr) || (id == nullptr) || (size == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    if (((*size) == 0) || ((*size) > (OH_XCOMPONENT_ID_LEN_MAX + 1))) {
        LOGE("The referenced value of 'size' should be in the range (0, OH_XCOMPONENT_ID_LEN_MAX + 1]");
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetXComponentId(id, size);
}

int32_t OH_NativeXComponent_GetXComponentSize(
    OH_NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height)
{
    if ((component == nullptr) || (window == nullptr) || (width == nullptr) || (height == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetXComponentSize(window, width, height);
}

int32_t OH_NativeXComponent_GetXComponentOffset(
    OH_NativeXComponent* component, const void* window, double* x, double* y)
{
    if ((component == nullptr) || (window == nullptr) || (x == nullptr) || (y == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetXComponentOffset(window, x, y);
}

int32_t OH_NativeXComponent_GetTouchEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_TouchEvent* touchEvent)
{
    if ((component == nullptr) || (window == nullptr) || (touchEvent == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetTouchEvent(window, touchEvent);
}

int32_t OH_NativeXComponent_GetTouchPointToolType(
    OH_NativeXComponent* component, uint32_t pointIndex, OH_NativeXComponent_TouchPointToolType* toolType)
{
    if ((component == nullptr) || (toolType == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetToolType(pointIndex, toolType);
}

int32_t OH_NativeXComponent_GetTouchPointTiltX(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltX)
{
    if ((component == nullptr) || (tiltX == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetTiltX(pointIndex, tiltX);
}

int32_t OH_NativeXComponent_GetTouchPointTiltY(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltY)
{
    if ((component == nullptr) || (tiltY == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetTiltY(pointIndex, tiltY);
}

int32_t OH_NativeXComponent_GetTouchPointWindowX(OH_NativeXComponent* component, uint32_t pointIndex, float* windowX)
{
    if ((component == nullptr) || (windowX == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetWindowX(pointIndex, windowX);
}

int32_t OH_NativeXComponent_GetTouchPointWindowY(OH_NativeXComponent* component, uint32_t pointIndex, float* windowY)
{
    if ((component == nullptr) || (windowY == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetWindowY(pointIndex, windowY);
}

int32_t OH_NativeXComponent_GetTouchPointDisplayX(OH_NativeXComponent* component, uint32_t pointIndex, float* displayX)
{
    if ((component == nullptr) || (displayX == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetDisplayX(pointIndex, displayX);
}

int32_t OH_NativeXComponent_GetTouchPointDisplayY(OH_NativeXComponent* component, uint32_t pointIndex, float* displayY)
{
    if ((component == nullptr) || (displayY == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetDisplayY(pointIndex, displayY);
}

int32_t OH_NativeXComponent_GetHistoricalPoints(OH_NativeXComponent* component, const void* window,
    int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints)
{
    if ((component == nullptr) || (window == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetHistoryPoints(window, size, historicalPoints);
}

int32_t OH_NativeXComponent_GetMouseEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_MouseEvent* mouseEvent)
{
    if ((component == nullptr) || (window == nullptr) || (mouseEvent == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetMouseEvent(window, mouseEvent);
}

int32_t OH_NativeXComponent_RegisterCallback(OH_NativeXComponent* component, OH_NativeXComponent_Callback* callback)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterCallback(callback);
}

int32_t OH_NativeXComponent_RegisterMouseEventCallback(
    OH_NativeXComponent* component, OH_NativeXComponent_MouseEvent_Callback* callback)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterMouseEventCallback(callback);
}

int32_t OH_NativeXComponent_RegisterFocusEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterFocusEventCallback(callback);
}

int32_t OH_NativeXComponent_RegisterKeyEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterKeyEventCallback(callback);
}

int32_t OH_NativeXComponent_RegisterBlurEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterBlurEventCallback(callback);
}

int32_t OH_NativeXComponent_GetKeyEvent(OH_NativeXComponent* component, OH_NativeXComponent_KeyEvent** keyEvent)
{
    if ((component == nullptr) || (keyEvent == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetKeyEvent(keyEvent);
}

int32_t OH_NativeXComponent_GetKeyEventAction(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyAction* action)
{
    if ((keyEvent == nullptr) || (action == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*action) = keyEvent->action;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventCode(OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyCode* code)
{
    if ((keyEvent == nullptr) || (code == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*code) = keyEvent->code;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventSourceType(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_EventSourceType* sourceType)
{
    if ((keyEvent == nullptr) || (sourceType == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*sourceType) = keyEvent->sourceType;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventDeviceId(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* deviceId)
{
    if ((keyEvent == nullptr) || (deviceId == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*deviceId) = keyEvent->deviceId;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_GetKeyEventTimestamp(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* timestamp)
{
    if ((keyEvent == nullptr) || (timestamp == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*timestamp) = keyEvent->timestamp;
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent_SetExpectedFrameRateRange(
    OH_NativeXComponent* component, OH_NativeXComponent_ExpectedRateRange* range)
{
    if (component == nullptr || range == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->SetExpectedFrameRateRange(range);
}

int32_t OH_NativeXComponent_RegisterOnFrameCallback(OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, uint64_t timestamp, uint64_t targetTimestamp))
{
    if (component == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterOnFrameCallback(callback);
}

int32_t OH_NativeXComponent_UnregisterOnFrameCallback(OH_NativeXComponent* component)
{
    if (component == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->UnregisterOnFrameCallback();
}

int32_t OH_NativeXComponent_AttachNativeRootNode(
    OH_NativeXComponent* component, ArkUI_NodeHandle root)
{
    if ((component == nullptr) || (root == nullptr) || !OHOS::Ace::NodeModel::CheckIsCNode(root)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->AttachNativeRootNode(root->uiNodeHandle);
}

int32_t OH_NativeXComponent_DetachNativeRootNode(
    OH_NativeXComponent* component, ArkUI_NodeHandle root)
{
    if ((component == nullptr) || (root == nullptr) || !OHOS::Ace::NodeModel::CheckIsCNode(root)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->DetachNativeRootNode(root->uiNodeHandle);
}

int32_t OH_NativeXComponent_RegisterUIInputEventCallback(OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event, ArkUI_UIInputEvent_Type type),
    ArkUI_UIInputEvent_Type type)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (type == ArkUI_UIInputEvent_Type::ARKUI_UIINPUTEVENT_TYPE_AXIS) {
        return component->RegisterUIAxisEventCallback(callback);
    }
    return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
}

int32_t OH_NativeXComponent_SetNeedSoftKeyboard(OH_NativeXComponent* component, bool needSoftKeyboard)
{
    return component ? component->SetNeedSoftKeyboard(needSoftKeyboard) : OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
}

int32_t OH_NativeXComponent_RegisterSurfaceShowCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    return (component && callback) ? component->RegisterSurfaceShowCallback(callback)
        : OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
}

int32_t OH_NativeXComponent_RegisterSurfaceHideCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window))
{
    return (component && callback) ? component->RegisterSurfaceHideCallback(callback)
        : OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
}

int32_t OH_NativeXComponent_RegisterOnTouchInterceptCallback(
    OH_NativeXComponent* component, HitTestMode (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return component->RegisterOnTouchInterceptCallback(callback);
}

int32_t OH_NativeXComponent_GetTouchEventSourceType(
    OH_NativeXComponent* component, int32_t pointId, OH_NativeXComponent_EventSourceType* sourceType)
{
    return (component && sourceType) ? component->GetSourceType(pointId, sourceType)
                                     : OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
}

OH_NativeXComponent* OH_NativeXComponent_GetNativeXComponent(ArkUI_NodeHandle node)
{
    if (node == nullptr || (node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
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
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }

    return component->GetAccessibilityProvider(handle);
}

int32_t OH_NativeXComponent_RegisterKeyEventCallbackWithResult(
    OH_NativeXComponent* component, bool (*callback)(OH_NativeXComponent* component, void* window))
{
    if ((component == nullptr) || (callback == nullptr)) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterKeyEventCallbackWithResult(callback);
}

int32_t OH_ArkUI_XComponent_StartImageAnalyzer(ArkUI_NodeHandle node, void* userData,
    void (*callback)(ArkUI_NodeHandle node, ArkUI_XComponent_ImageAnalyzerState statusCode, void* userData))
{
    if ((!OHOS::Ace::NodeModel::IsValidArkUINode(node)) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE) ||
        (callback == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto nodeModifiers = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers();
    nodeModifiers->getXComponentModifier()->startImageAnalyzer(node->uiNodeHandle, node, userData,
        reinterpret_cast<XComponentAnalyzerCallback>(callback));
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_XComponent_StopImageAnalyzer(ArkUI_NodeHandle node)
{
    if ((!OHOS::Ace::NodeModel::IsValidArkUINode(node)) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto nodeModifiers = OHOS::Ace::NodeModel::GetFullImpl()->getNodeModifiers();
    nodeModifiers->getXComponentModifier()->stopImageAnalyzer(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

OH_ArkUI_SurfaceHolder* OH_ArkUI_SurfaceHolder_Create(ArkUI_NodeHandle node)
{
    if (!OHOS::Ace::NodeModel::IsValidArkUINode(node) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
        return nullptr;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto nodeModifiers = impl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, nullptr);
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, nullptr);
    auto* surfaceHolder =
        reinterpret_cast<OH_ArkUI_SurfaceHolder*>(xComponentModifier->createSurfaceHolder(node->uiNodeHandle));
    CHECK_NULL_RETURN(surfaceHolder, nullptr);
    surfaceHolder->node_ = node;
    return surfaceHolder;
}

void OH_ArkUI_SurfaceHolder_Dispose(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    if (surfaceHolder) {
        auto node = surfaceHolder->node_;
        if (OHOS::Ace::NodeModel::IsValidArkUINode(node)) {
            const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
            CHECK_NULL_VOID(impl);
            auto nodeModifiers = impl->getNodeModifiers();
            CHECK_NULL_VOID(nodeModifiers);
            auto xComponentModifier = nodeModifiers->getXComponentModifier();
            CHECK_NULL_VOID(xComponentModifier);
            xComponentModifier->dispose(node->uiNodeHandle);
        }
    }
    delete surfaceHolder;
}

int32_t OH_ArkUI_SurfaceHolder_SetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder, void* userData)
{
    if (surfaceHolder == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    surfaceHolder->userData_ = userData;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void* OH_ArkUI_SurfaceHolder_GetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    if (surfaceHolder == nullptr) {
        return nullptr;
    }
    return surfaceHolder->userData_;
}

OH_ArkUI_SurfaceCallback* OH_ArkUI_SurfaceCallback_Create(void)
{
    OH_ArkUI_SurfaceCallback* surfaceCallback = new OH_ArkUI_SurfaceCallback();
    return surfaceCallback;
}

void OH_ArkUI_SurfaceCallback_Dispose(OH_ArkUI_SurfaceCallback* callback)
{
    delete callback;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(
    OH_ArkUI_SurfaceCallback* callback, void (*onSurfaceCreated)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    CHECK_NULL_VOID(callback);
    callback->OnSurfaceCreated = onSurfaceCreated;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceChanged)(OH_ArkUI_SurfaceHolder* surfaceHolder, uint64_t width, uint64_t height))
{
    CHECK_NULL_VOID(callback);
    callback->OnSurfaceChanged = onSurfaceChanged;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceDestroyed)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    CHECK_NULL_VOID(callback);
    callback->OnSurfaceDestroyed = onSurfaceDestroyed;
}

int32_t OH_ArkUI_SurfaceHolder_AddSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder, OH_ArkUI_SurfaceCallback* callback)
{
    if ((surfaceHolder == nullptr) || (callback == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return surfaceHolder->AddSurfaceCallback(callback);
}

int32_t OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder, OH_ArkUI_SurfaceCallback* callback)
{
    if ((surfaceHolder == nullptr) || (callback == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return surfaceHolder->RemoveSurfaceCallback(callback);
}

OHNativeWindow* OH_ArkUI_XComponent_GetNativeWindow(OH_ArkUI_SurfaceHolder* surfaceHolder)
{
    if (surfaceHolder == nullptr) {
        return nullptr;
    }
    return surfaceHolder->nativeWindow_;
}

int32_t OH_ArkUI_XComponent_SetAutoInitialize(ArkUI_NodeHandle node, bool autoInitialize)
{
    if (!OHOS::Ace::NodeModel::IsValidArkUINode(node) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = impl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    return xComponentModifier->setAutoInitialize(node->uiNodeHandle, autoInitialize);
}

int32_t OH_ArkUI_XComponent_Initialize(ArkUI_NodeHandle node)
{
    if (!OHOS::Ace::NodeModel::IsValidArkUINode(node) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = impl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    return xComponentModifier->initialize(node->uiNodeHandle);
}

int32_t OH_ArkUI_XComponent_Finalize(ArkUI_NodeHandle node)
{
    if (!OHOS::Ace::NodeModel::IsValidArkUINode(node) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = impl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    return xComponentModifier->finalize(node->uiNodeHandle);
}

int32_t OH_ArkUI_XComponent_IsInitialized(ArkUI_NodeHandle node, bool* isInitialized)
{
    if (!OHOS::Ace::NodeModel::IsValidArkUINode(node) ||
        (!node->isBindNative && node->type != ARKUI_NODE_XCOMPONENT && node->type != ARKUI_NODE_XCOMPONENT_TEXTURE) ||
        !isInitialized) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto nodeModifiers = impl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    ArkUI_Bool value = 0;
    auto res = xComponentModifier->isInitialized(node->uiNodeHandle, &value);
    *isInitialized = value;
    return res;
}

int32_t OH_NativeXComponent_GetExtraMouseEventInfo(OH_NativeXComponent* component,
    OH_NativeXComponent_ExtraMouseEventInfo** extraMouseEventInfo)
{
    if ((component == nullptr) || (extraMouseEventInfo == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    return component->GetExtraMouseEventInfo(extraMouseEventInfo);
}

int32_t OH_NativeXComponent_GetMouseEventModifierKeyStates(
    OH_NativeXComponent_ExtraMouseEventInfo* ExtraMouseEventInfo, uint64_t* keys)
{
    if ((ExtraMouseEventInfo == nullptr) || (keys == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    (*keys) = ExtraMouseEventInfo->modifierKeyStates;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventModifierKeyStates(OH_NativeXComponent_KeyEvent* keyEvent, uint64_t* keys)
{
    if ((keyEvent == nullptr) || (keys == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    (*keys) = keyEvent->modifierKeyStates;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventNumLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isNumLockOn)
{
    if ((keyEvent == nullptr) || (isNumLockOn == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    (*isNumLockOn) = keyEvent->isNumLockOn;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventCapsLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isCapsLockOn)
{
    if ((keyEvent == nullptr) || (isCapsLockOn == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    (*isCapsLockOn) = keyEvent->isCapsLockOn;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_NativeXComponent_GetKeyEventScrollLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isScrollLockOn)
{
    if ((keyEvent == nullptr) || (isScrollLockOn == nullptr)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    (*isScrollLockOn) = keyEvent->isScrollLockOn;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

const ArkUIXComponentModifier* GetArkUIXComponentModifier()
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto nodeModifiers = impl->getNodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, nullptr);
    auto xComponentModifier = nodeModifiers->getXComponentModifier();
    return xComponentModifier;
}

bool IsValidXComponentNode(ArkUI_NodeHandle node)
{
    return OHOS::Ace::NodeModel::IsValidArkUINode(node) &&
        (node->isBindNative || node->type == ARKUI_NODE_XCOMPONENT || node->type == ARKUI_NODE_XCOMPONENT_TEXTURE);
}

int32_t OH_ArkUI_XComponent_SetExpectedFrameRateRange(
    ArkUI_NodeHandle node, OH_NativeXComponent_ExpectedRateRange range)
{
    if (!IsValidXComponentNode(node)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    ArkUI_Int32 min = range.min;
    ArkUI_Int32 max = range.max;
    ArkUI_Int32 expected = range.expected;
    auto res = xComponentModifier->setExpectedFrameRateRange(node->uiNodeHandle, min, max, expected);
    return res;
}

int32_t OH_ArkUI_XComponent_RegisterOnFrameCallback(ArkUI_NodeHandle node,
    void (*callback)(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp))
{
    if (!IsValidXComponentNode(node)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto res = xComponentModifier->registerOnFrameCallback(node->uiNodeHandle,
        reinterpret_cast<void(*)(void*, uint64_t, uint64_t)>(callback), node);
    return res;
}

int32_t OH_ArkUI_XComponent_UnregisterOnFrameCallback(ArkUI_NodeHandle node)
{
    if (!IsValidXComponentNode(node)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto res = xComponentModifier->unregisterOnFrameCallback(node->uiNodeHandle);
    return res;
}

int32_t OH_ArkUI_XComponent_SetNeedSoftKeyboard(ArkUI_NodeHandle node, bool needSoftKeyboard)
{
    if (!IsValidXComponentNode(node)) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto xComponentModifier = GetArkUIXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto res = xComponentModifier->setNeedSoftKeyboard(node->uiNodeHandle, needSoftKeyboard);
    return res;
}

ArkUI_AccessibilityProvider* OH_ArkUI_AccessibilityProvider_Create(ArkUI_NodeHandle node)
{
    if (!IsValidXComponentNode(node)) {
        return nullptr;
    }
    auto xComponentModifier = GetArkUIXComponentModifier();
    CHECK_NULL_RETURN(xComponentModifier, nullptr);
    auto accessibilityProvider = reinterpret_cast<ArkUI_AccessibilityProvider*>(
        xComponentModifier->createAccessibilityProvider(node->uiNodeHandle));
    return accessibilityProvider;
}

void OH_ArkUI_AccessibilityProvider_Dispose(ArkUI_AccessibilityProvider* provider)
{
    if (provider == nullptr) {
        return;
    }
    auto xComponentModifier = GetArkUIXComponentModifier();
    CHECK_NULL_VOID(xComponentModifier);
    xComponentModifier->disposeAccessibilityProvider(provider);
}

void OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceShow)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    CHECK_NULL_VOID(callback);
    callback->onSurfaceShow = onSurfaceShow;
}

void OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceHide)(OH_ArkUI_SurfaceHolder* surfaceHolder))
{
    CHECK_NULL_VOID(callback);
    callback->onSurfaceHide = onSurfaceHide;
}

#ifdef __cplusplus
};
#endif
