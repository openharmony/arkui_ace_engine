/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_BASE_GESTURE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_BASE_GESTURE_EVENT_H

#include "core/gestures/gesture_info.h"

namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {

class ACE_EXPORT BaseGestureEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(BaseGestureEvent, BaseEventInfo);

public:
    BaseGestureEvent() : BaseEventInfo("baseGesture") {}
    ~BaseGestureEvent() override = default;

    const std::list<FingerInfo>& GetFingerList() const
    {
        return fingerList_;
    }

    void SetFingerList(const std::list<FingerInfo>& fingerList)
    {
        fingerList_ = fingerList;
    }

    InputEventType GetRawInputEventType() const
    {
        return rawInputEventType_;
    }

    void SetRawInputEventType(InputEventType type)
    {
        rawInputEventType_ = type;
    }

    std::shared_ptr<MMI::PointerEvent> GetRawInputEvent() const
    {
        return rawInputEvent_;
    }

    void SetRawInputEvent(std::shared_ptr<MMI::PointerEvent> rawInputEvent)
    {
        rawInputEvent_ = rawInputEvent;
    }

    int64_t GetRawInputDeviceId() const
    {
        return rawInputDeviceId_;
    }

    void SetRawInputDeviceId(int64_t rawInputDeviceId)
    {
        rawInputDeviceId_ = rawInputDeviceId;
    }

    void SetLastAction(int32_t action)
    {
        lastAction_.emplace(action);
    }

    std::optional<int32_t> GetLastAction() const
    {
        return lastAction_;
    }

protected:
    std::list<FingerInfo> fingerList_;
    InputEventType rawInputEventType_ = InputEventType::TOUCH_SCREEN;
    std::shared_ptr<MMI::PointerEvent> rawInputEvent_;
    int64_t rawInputDeviceId_ = 0;
    std::optional<int32_t> lastAction_;
};

class ACE_EXPORT TapGestureEvent : public BaseGestureEvent {
    DECLARE_RELATIONSHIP_OF_CLASSES(TapGestureEvent, BaseGestureEvent);

public:
    TapGestureEvent() = default;
    ~TapGestureEvent() override = default;
};

class ACE_EXPORT LongPressGestureEvent : public BaseGestureEvent {
    DECLARE_RELATIONSHIP_OF_CLASSES(LongPressGestureEvent, BaseGestureEvent);

public:
    LongPressGestureEvent() = default;
    ~LongPressGestureEvent() override = default;

    void SetRepeat(bool repeat)
    {
        repeat_ = repeat;
    }

    bool GetRepeat() const
    {
        return repeat_;
    }

private:
    bool repeat_ = false;
};

class ACE_EXPORT PanGestureEvent : public BaseGestureEvent {
    DECLARE_RELATIONSHIP_OF_CLASSES(PanGestureEvent, BaseGestureEvent);

public:
    PanGestureEvent() = default;
    ~PanGestureEvent() override = default;

    void SetOffsetX(double offsetX)
    {
        offsetX_ = offsetX;
    }

    double GetOffsetX() const
    {
        return offsetX_;
    }

    void SetOffsetY(double offsetY)
    {
        offsetY_ = offsetY;
    }

    double GetOffsetY() const
    {
        return offsetY_;
    }

    void SetVelocity(const Velocity& velocity)
    {
        velocity_ = velocity;
    }

    const Velocity& GetVelocity() const
    {
        return velocity_;
    }

    void SetMainVelocity(double mainVelocity)
    {
        mainVelocity_ = mainVelocity;
    }

    double GetMainVelocity() const
    {
        return mainVelocity_;
    }

private:
    double offsetX_ = 0.0;
    double offsetY_ = 0.0;
    Velocity velocity_;
    double mainVelocity_ = 0.0;
};

class ACE_EXPORT PinchGestureEvent : public BaseGestureEvent {
    DECLARE_RELATIONSHIP_OF_CLASSES(PinchGestureEvent, BaseGestureEvent);

public:
    PinchGestureEvent() = default;
    ~PinchGestureEvent() override = default;

    void SetScale(double scale)
    {
        scale_ = scale;
    }

    double GetScale() const
    {
        return scale_;
    }

    const Offset& GetPinchCenter() const
    {
        return pinchCenter_;
    }

    PinchGestureEvent& SetPinchCenter(const Offset& pinchCenter)
    {
        pinchCenter_ = pinchCenter;
        return *this;
    }

private:
    double scale_ = 1.0;
    Offset pinchCenter_;
};

class ACE_EXPORT RotationGestureEvent : public BaseGestureEvent {
    DECLARE_RELATIONSHIP_OF_CLASSES(RotationGestureEvent, BaseGestureEvent);

public:
    RotationGestureEvent() = default;
    ~RotationGestureEvent() override = default;

    void SetAngle(double angle)
    {
        angle_ = angle;
    }

    double GetAngle() const
    {
        return angle_;
    }

private:
    double angle_ = 0.0;
};

class ACE_EXPORT SwipeGestureEvent : public BaseGestureEvent {
    DECLARE_RELATIONSHIP_OF_CLASSES(SwipeGestureEvent, BaseGestureEvent);

public:
    SwipeGestureEvent() = default;
    ~SwipeGestureEvent() override = default;

    void SetAngle(double angle)
    {
        angle_ = angle;
    }

    double GetAngle() const
    {
        return angle_;
    }

    void SetSpeed(double speed)
    {
        speed_ = speed;
    }

    double GetSpeed() const
    {
        return speed_;
    }

private:
    double angle_ = 0.0;
    double speed_ = 0.0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_BASE_GESTURE_EVENT_H