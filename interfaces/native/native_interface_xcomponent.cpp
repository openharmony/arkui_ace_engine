/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"

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
#ifdef __cplusplus
};
#endif
