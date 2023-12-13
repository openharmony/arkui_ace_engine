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

#ifndef _NATIVE_INTERFACE_XCOMPONENT_IMPL_
#define _NATIVE_INTERFACE_XCOMPONENT_IMPL_

#include <functional>
#include <string>
#include <unistd.h>
#include <vector>

#include "interfaces/native/native_interface_xcomponent.h"

#include "base/memory/ace_type.h"

struct XComponentTouchPoint {
    float tiltX = 0.0f;
    float tiltY = 0.0f;
    OH_NativeXComponent_TouchPointToolType sourceToolType =
        OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
};

struct OH_NativeXComponent_KeyEvent {
    OH_NativeXComponent_KeyAction action = OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    OH_NativeXComponent_KeyCode code = OH_NativeXComponent_KeyCode::KEY_UNKNOWN;
    OH_NativeXComponent_EventSourceType sourceType =
        OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    int64_t deviceId {};
    int64_t timestamp {};
};

namespace OHOS::Ace {
class NativeXComponentImpl : public virtual AceType {
    DECLARE_ACE_TYPE(NativeXComponentImpl, AceType);
    using NativeXComponent_Callback = void (*)(OH_NativeXComponent*, void*);
    using SetExpectedRateRangeEvent_Callback  = std::function<void()>;
    using SetOnFrameEvent_Callback = std::function<void()>;
    using SetUnregisterOnFrameEvent_Callback = std::function<void()>;
    using OnFrame_Callback = void (*)(OH_NativeXComponent*, uint64_t, uint64_t);

public:
    NativeXComponentImpl() {}

    ~NativeXComponentImpl() {}

    void SetXComponentId(const std::string& id)
    {
        xcomponentId_ = id;
    }

    const std::string& GetXComponentId() const
    {
        return xcomponentId_;
    }

    void SetXComponentWidth(const int width)
    {
        width_ = width;
    }

    int GetXComponentWidth() const
    {
        return width_;
    }

    void SetXComponentHeight(const int height)
    {
        height_ = height;
    }

    int GetXComponentHeight() const
    {
        return height_;
    }

    void SetXComponentOffsetX(const double x)
    {
        x_ = x;
    }

    double GetXComponentOffsetX() const
    {
        return x_;
    }

    void SetXComponentOffsetY(const double y)
    {
        y_ = y;
    }

    double GetXComponentOffsetY() const
    {
        return y_;
    }

    void SetSurface(void* window)
    {
        window_ = window;
    }

    const void* GetSurface() const
    {
        return window_;
    }

    void SetCallback(OH_NativeXComponent_Callback* callback)
    {
        callback_ = callback;
    }

    const OH_NativeXComponent_Callback* GetCallback() const
    {
        return callback_;
    }

    void SetMouseEventCallback(OH_NativeXComponent_MouseEvent_Callback* callback)
    {
        mouseEventCallback_ = callback;
    }

    const OH_NativeXComponent_MouseEvent_Callback* GetMouseEventCallback()
    {
        return mouseEventCallback_;
    }

    void SetTouchEvent(const OH_NativeXComponent_TouchEvent touchEvent)
    {
        touchEvent_ = touchEvent;
    }

    void SetTouchPoint(const std::vector<XComponentTouchPoint>& xComponentTouchPoints)
    {
        touchPoints_ = xComponentTouchPoints;
    }

    void SetHistoricalPoint(const std::vector<OH_NativeXComponent_HistoricalPoint>& historicalPoints)
    {
        historicalPoints_ = historicalPoints;
    }

    void SetKeyEvent(const OH_NativeXComponent_KeyEvent keyEvent)
    {
        keyEvent_ = keyEvent;
    }

    void SetMouseEvent(const OH_NativeXComponent_MouseEvent mouseEvent)
    {
        mouseEvent_ = mouseEvent;
    }

    const OH_NativeXComponent_TouchEvent GetTouchEvent() const
    {
        return touchEvent_;
    }

    void GetHistoryPoints(int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints)
    {
        int32_t historicalPointsSize = (int32_t)(historicalPoints_.size());
        *size = historicalPointsSize;
        *historicalPoints = &(historicalPoints_[0]);
    }

    void GetHistoryPointsSize(int32_t* size) const
    {
        *size = (int32_t)(historicalPoints_.size());
    }

    const OH_NativeXComponent_MouseEvent GetMouseEvent() const
    {
        return mouseEvent_;
    }

    void SetToolType(size_t pointIndex, OH_NativeXComponent_TouchPointToolType toolType)
    {
        if (pointIndex >= OH_MAX_TOUCH_POINTS_NUMBER || pointIndex >= touchPoints_.size()) {
            return;
        }
        touchPoints_[pointIndex].sourceToolType = toolType;
    }

    OH_NativeXComponent_TouchPointToolType GetToolType(size_t pointIndex) const
    {
        if (pointIndex >= OH_MAX_TOUCH_POINTS_NUMBER || pointIndex >= touchPoints_.size()) {
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
        }
        return touchPoints_[pointIndex].sourceToolType;
    }

    float GetTiltX(size_t pointIndex) const
    {
        if (pointIndex >= OH_MAX_TOUCH_POINTS_NUMBER || pointIndex >= touchPoints_.size()) {
            return 0.0f;
        }
        return touchPoints_[pointIndex].tiltX;
    }

    float GetTiltY(size_t pointIndex) const
    {
        if (pointIndex >= OH_MAX_TOUCH_POINTS_NUMBER || pointIndex >= touchPoints_.size()) {
            return 0.0f;
        }
        return touchPoints_[pointIndex].tiltY;
    }

    OH_NativeXComponent_KeyEvent* GetKeyEvent()
    {
        return &keyEvent_;
    }

    NativeXComponent_Callback GetFocusEventCallback() const
    {
        return focusEventCallback_;
    }

    NativeXComponent_Callback GetKeyEventCallback() const
    {
        return keyEventCallback_;
    }

    NativeXComponent_Callback GetBlurEventCallback() const
    {
        return blurEventCallback_;
    }

    void SetFocusEventCallback(NativeXComponent_Callback callback)
    {
        focusEventCallback_ = callback;
    }

    void SetKeyEventCallback(NativeXComponent_Callback callback)
    {
        keyEventCallback_ = callback;
    }

    void SetBlurEventCallback(NativeXComponent_Callback callback)
    {
        blurEventCallback_ = callback;
    }

    void SetOnFrameCallback(OnFrame_Callback callback)
    {
        onFrameCallback_ = callback;
    }

    OnFrame_Callback GetOnFrameCallback()
    {
        return onFrameCallback_;
    }

    OH_NativeXComponent_ExpectedRateRange* GetRateRange()
    {
        return rateRange_;
    }

    void SetRateRange(OH_NativeXComponent_ExpectedRateRange* rateRange)
    {
        rateRange_ = rateRange;
    }

    void SetExpectedRateRangeEventCallback(SetExpectedRateRangeEvent_Callback callback)
    {
        setExpectedRateRangeCallback_ = callback;
    }

    void SetOnFrameEventCallback(SetOnFrameEvent_Callback callback)
    {
        setOnFrameEventCallback_ = callback;
    }

    void SetUnregisterOnFrameEventCallback(SetUnregisterOnFrameEvent_Callback callback)
    {
        setUnregisterOnFrameEventCallback_ = callback;
    }

    SetExpectedRateRangeEvent_Callback setExpectedRateRangeCallback_;

    SetOnFrameEvent_Callback setOnFrameEventCallback_;

    SetUnregisterOnFrameEvent_Callback setUnregisterOnFrameEventCallback_;

private:
    std::string xcomponentId_;
    void* window_ = nullptr;
    int width_ = 0;
    int height_ = 0;
    double x_ = 0.0;
    double y_ = 0.0;
    OH_NativeXComponent_TouchEvent touchEvent_;
    OH_NativeXComponent_MouseEvent mouseEvent_;
    OH_NativeXComponent_KeyEvent keyEvent_;
    OH_NativeXComponent_Callback* callback_ = nullptr;
    OH_NativeXComponent_MouseEvent_Callback* mouseEventCallback_ = nullptr;
    NativeXComponent_Callback focusEventCallback_ = nullptr;
    NativeXComponent_Callback keyEventCallback_ = nullptr;
    NativeXComponent_Callback blurEventCallback_ = nullptr;
    std::vector<XComponentTouchPoint> touchPoints_;
    std::vector<OH_NativeXComponent_HistoricalPoint> historicalPoints_;
    OnFrame_Callback onFrameCallback_ = nullptr;
    OH_NativeXComponent_ExpectedRateRange* rateRange_ = nullptr;
};
} // namespace OHOS::Ace

struct OH_NativeXComponent {
    explicit OH_NativeXComponent(OHOS::Ace::NativeXComponentImpl* xComponentImpl) : xcomponentImpl_(xComponentImpl) {}
    ~OH_NativeXComponent() {}
    int32_t GetXComponentId(char* id, uint64_t* size);
    int32_t GetNativeWindow(void** window);
    int32_t GetXComponentSize(const void* window, uint64_t* width, uint64_t* height);
    int32_t GetXComponentOffset(const void* window, double* x, double* y);
    int32_t GetTouchEvent(const void* window, OH_NativeXComponent_TouchEvent* touchEvent);
    int32_t GetMouseEvent(const void* window, OH_NativeXComponent_MouseEvent* mouseEvent);
    int32_t GetHistoryPoints(const void* window, int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints);
    int32_t RegisterCallback(OH_NativeXComponent_Callback* callback);
    int32_t RegisterMouseEventCallback(OH_NativeXComponent_MouseEvent_Callback* callback);
    int32_t GetToolType(size_t pointIndex, OH_NativeXComponent_TouchPointToolType* toolType);
    int32_t GetTiltX(size_t pointIndex, float* tiltX);
    int32_t GetTiltY(size_t pointIndex, float* tiltY);
    int32_t RegisterFocusEventCallback(void (*callback)(OH_NativeXComponent* component, void* window));
    int32_t RegisterKeyEventCallback(void (*callback)(OH_NativeXComponent* component, void* window));
    int32_t RegisterBlurEventCallback(void (*callback)(OH_NativeXComponent* component, void* window));
    int32_t GetKeyEvent(OH_NativeXComponent_KeyEvent** keyEvent);
    int32_t SetExpectedFrameRateRange(OH_NativeXComponent_ExpectedRateRange* range);
    int32_t RegisterOnFrameCallback(
        void (*callback)(OH_NativeXComponent* component, uint64_t timestamp, uint64_t targetTimestamp));
    int32_t UnregisterOnFrameCallback();

private:
    OHOS::Ace::NativeXComponentImpl* xcomponentImpl_ = nullptr;
};

#endif // _NATIVE_INTERFACE_XCOMPONENT_IMPL_