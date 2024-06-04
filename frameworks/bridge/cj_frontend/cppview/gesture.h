/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_GESTURE_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_GESTURE_H

#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/event/ace_event_handler.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT Gesture : public virtual AceType {
public:
    enum class CJGestureEvent { ACTION, START, UPDATE, END, CANCEL };

    static void Create(GesturePriority priority, GestureMask gestureMask);
    static void Pop();
    static void Finish();

    static void HandlerOnAction(const std::function<void(const GestureEvent& event)>& callback);
    static void HandlerOnActionStart(const std::function<void(const GestureEvent& event)>& callback);
    static void HandlerOnActionUpdate(const std::function<void(const GestureEvent& event)>& callback);
    static void HandlerOnActionEnd(const std::function<void(const GestureEvent& event)>& callback);
    static void HandlerOnActionCancel(const std::function<void(const GestureEvent& event)>& callback);
    static void HandlerOnGestureEvent(
        const CJGestureEvent& action, const std::function<void(const GestureEvent& event)>& callback);
}; // Gesture

class ACE_EXPORT TapGesture : public Gesture {
public:
    static void Create(int32_t count, int32_t fingers);
};

class ACE_EXPORT LongPressGesture : public Gesture {
public:
    static void Create(int32_t fingers, bool repeat, int32_t duration);
};

class ACE_EXPORT PinchGesture : public Gesture {
public:
    static void Create(int32_t fingers, double distance);
};

class ACE_EXPORT SwipeGesture : public Gesture {
public:
    static void Create(int32_t fingers, const SwipeDirection& swipeDirection, double speed);
};

class ACE_EXPORT RotationGesture : public Gesture {
public:
    static void Create(int32_t fingers, double angle);
};

class ACE_EXPORT GestureGroup : public Gesture {
public:
    static void Create(const GestureMode& mode);
};

class ACE_EXPORT NativePanGestureOption : public OHOS::FFI::FFIData {
    DECL_TYPE(NativePanGestureOption, OHOS::FFI::FFIData)
public:
    NativePanGestureOption(int32_t fingers, const PanDirection& panDirection, double distance);
    ~NativePanGestureOption() override;
    void SetDirection(const PanDirection& panDirection);
    void SetDistance(double distance);
    void SetFingers(int32_t fingers);

    void SetPanGestureOption(const RefPtr<PanGestureOption>& panGestureOption)
    {
        panGestureOption_ = panGestureOption;
    }

    RefPtr<PanGestureOption> GetPanGestureOption() const
    {
        return panGestureOption_;
    }

private:
    RefPtr<PanGestureOption> panGestureOption_;
};

class ACE_EXPORT PanGesture : public Gesture {
public:
    static void Create(int32_t fingers, const PanDirection& panDirection, double distance);
    static void Create(const sptr<NativePanGestureOption>& panGestureOption);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_GESTURE_H
