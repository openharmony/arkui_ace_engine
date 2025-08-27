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

#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"

#include "securec.h"

#include "base/error/error_code.h"

int32_t OH_NativeXComponent::GetXComponentId(char* id, uint64_t* size)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto xcomponentId = xcomponentImpl_->GetXComponentId();
    uint64_t idSize = static_cast<uint64_t>(xcomponentId.size());
    if (idSize > (uint64_t)(OH_XCOMPONENT_ID_LEN_MAX)) {
        LOGE("Length of XComponent id should be no more than OH_XCOMPONENT_ID_LEN_MAX");
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    if (strncpy_s(id, (*size), xcomponentId.c_str(), idSize) == 0) {
        (*size) = idSize;
        return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
    } else {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
}

int32_t OH_NativeXComponent::GetNativeWindow(void** window)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto surface = const_cast<void*>(xcomponentImpl_->GetSurface());
    if (surface) {
        (*window) = surface;
        return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
    } else {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
}

int32_t OH_NativeXComponent::GetXComponentSize(const void* window, uint64_t* width, uint64_t* height)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto surfaceWindow = const_cast<void*>(xcomponentImpl_->GetSurface());
    if (window != surfaceWindow) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    (*width) = static_cast<uint64_t>(xcomponentImpl_->GetXComponentWidth());
    (*height) = static_cast<uint64_t>(xcomponentImpl_->GetXComponentHeight());

    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetXComponentOffset(const void* window, double* x, double* y)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto surfaceWindow = const_cast<void*>(xcomponentImpl_->GetSurface());
    if (window != surfaceWindow) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    (*x) = static_cast<double>(xcomponentImpl_->GetXComponentOffsetX());
    (*y) = static_cast<double>(xcomponentImpl_->GetXComponentOffsetY());

    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetHistoryPoints(const void* window,
    int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto surfaceWindow = const_cast<void*>(xcomponentImpl_->GetSurface());
    if (window != surfaceWindow) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    xcomponentImpl_->GetHistoryPoints(size, historicalPoints);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetTouchEvent(const void* window, OH_NativeXComponent_TouchEvent* touchEvent)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto surfaceWindow = const_cast<void*>(xcomponentImpl_->GetSurface());
    if (window != surfaceWindow) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    (*touchEvent) = xcomponentImpl_->GetTouchEvent();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetToolType(size_t pointIndex, OH_NativeXComponent_TouchPointToolType* toolType)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*toolType) = xcomponentImpl_->GetToolType(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetTiltX(size_t pointIndex, float* tiltX)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*tiltX) = xcomponentImpl_->GetTiltX(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetTiltY(size_t pointIndex, float* tiltY)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*tiltY) = xcomponentImpl_->GetTiltY(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetWindowX(size_t pointIndex, float* windowX)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*windowX) = xcomponentImpl_->GetWindowX(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetWindowY(size_t pointIndex, float* windowY)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*windowY) = xcomponentImpl_->GetWindowY(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetDisplayX(size_t pointIndex, float* displayX)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*displayX) = xcomponentImpl_->GetDisplayX(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetDisplayY(size_t pointIndex, float* displayY)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*displayY) = xcomponentImpl_->GetDisplayY(pointIndex);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetMouseEvent(const void* window, OH_NativeXComponent_MouseEvent* mouseEvent)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    auto surfaceWindow = const_cast<void*>(xcomponentImpl_->GetSurface());
    if (window != surfaceWindow) {
        return OH_NATIVEXCOMPONENT_RESULT_FAILED;
    }
    (*mouseEvent) = xcomponentImpl_->GetMouseEvent();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterCallback(OH_NativeXComponent_Callback* callback)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterMouseEventCallback(OH_NativeXComponent_MouseEvent_Callback* callback)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetMouseEventCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterFocusEventCallback(void (*callback)(OH_NativeXComponent* component, void* window))
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetFocusEventCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterKeyEventCallback(void (*callback)(OH_NativeXComponent* component, void* window))
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetKeyEventCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterKeyEventCallbackWithResult(
    bool (*callback)(OH_NativeXComponent* component, void* window))
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetKeyEventCallbackWithResult(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterBlurEventCallback(void (*callback)(OH_NativeXComponent* component, void* window))
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetBlurEventCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetKeyEvent(OH_NativeXComponent_KeyEvent** keyEvent)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    (*keyEvent) = xcomponentImpl_->GetKeyEvent();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::SetExpectedFrameRateRange(OH_NativeXComponent_ExpectedRateRange* range)
{
    if (xcomponentImpl_ == nullptr || range == nullptr || !xcomponentImpl_->setExpectedRateRangeCallback_) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    int32_t min = range->min;
    int32_t max = range->max;
    int32_t expected = range->expected;

    if (!(min <= max && expected >= min && expected <= max)) {
        LOGE("Xcomponent Expeted FrameRateRange Error.");
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetRateRange(range);
    xcomponentImpl_->setExpectedRateRangeCallback_();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterOnFrameCallback(
    void (*callback)(OH_NativeXComponent* component, uint64_t timestamp, uint64_t targetTimestamp))
{
    if (xcomponentImpl_ == nullptr || !xcomponentImpl_->setOnFrameEventCallback_) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetOnFrameCallback(callback);
    xcomponentImpl_->setOnFrameEventCallback_();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::UnregisterOnFrameCallback()
{
    if (xcomponentImpl_ == nullptr || !xcomponentImpl_->setUnregisterOnFrameEventCallback_) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetOnFrameCallback(nullptr);
    xcomponentImpl_->setUnregisterOnFrameEventCallback_();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::AttachNativeRootNode(void* root)
{
    if (root == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->AttachContainer(root);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::DetachNativeRootNode(void* root)
{
    if (root == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->DetachContainer(root);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterUIAxisEventCallback(
    void (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event, ArkUI_UIInputEvent_Type type))
{
    if (xcomponentImpl_ == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    xcomponentImpl_->SetUIAxisEventCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::SetNeedSoftKeyboard(bool needSoftKeyboard)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetNeedSoftKeyboard(needSoftKeyboard);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterSurfaceShowCallback(NativeXComponent_Surface_Callback callback)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetSurfaceShowCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterSurfaceHideCallback(NativeXComponent_Surface_Callback callback)
{
    if (xcomponentImpl_ == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }
    xcomponentImpl_->SetSurfaceHideCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::RegisterOnTouchInterceptCallback(
    HitTestMode (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event))
{
    if (xcomponentImpl_ == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    xcomponentImpl_->SetOnTouchInterceptCallback(callback);
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetSourceType(int32_t pointId, OH_NativeXComponent_EventSourceType* sourceType)
{
    return (xcomponentImpl_ && xcomponentImpl_->GetSourceType(pointId, sourceType))
               ? OH_NATIVEXCOMPONENT_RESULT_SUCCESS
               : OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
}

int32_t OH_NativeXComponent::GetAccessibilityProvider(ArkUI_AccessibilityProvider** handle)
{
    if (xcomponentImpl_ == nullptr || handle == nullptr) {
        return OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
    }

    (*handle) = xcomponentImpl_->GetAccessbilityProvider().get();
    return OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
}

int32_t OH_NativeXComponent::GetExtraMouseEventInfo(OH_NativeXComponent_ExtraMouseEventInfo** extraMouseEventInfo)
{
    if (xcomponentImpl_ == nullptr || extraMouseEventInfo == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    (*extraMouseEventInfo) = xcomponentImpl_->GetExtraMouseEventInfo();
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}
