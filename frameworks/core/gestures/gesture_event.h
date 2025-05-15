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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_EVENT_H

#include "core/gestures/gesture_info.h"
#include "core/components/common/layout/constants.h"
namespace OHOS::MMI {
class PointerEvent;
} // namespace OHOS::MMI

namespace OHOS::Ace {

class GestureEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(GestureEvent, BaseEventInfo);

public:
    GestureEvent() : BaseEventInfo("gesture") {}
    ~GestureEvent() override = default;

    void SetRepeat(bool repeat)
    {
        repeat_ = repeat;
    }

    bool GetRepeat() const
    {
        return repeat_;
    }

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

    void SetScale(double scale)
    {
        scale_ = scale;
    }

    double GetScale() const
    {
        return scale_;
    }

    void SetAngle(double angle)
    {
        angle_ = angle;
    }

    double GetAngle() const
    {
        return angle_;
    }

    GestureEvent& SetGlobalPoint(const Point& globalPoint)
    {
        globalPoint_ = globalPoint;
        globalLocation_.SetX(globalPoint.GetX());
        globalLocation_.SetY(globalPoint.GetY());
        return *this;
    }

    const Point& GetGlobalPoint() const
    {
        return globalPoint_;
    }

    GestureEvent& SetScreenLocation(const Offset& screenLocation)
    {
        screenLocation_ = screenLocation;
        return *this;
    }

    const Offset& GetScreenLocation() const
    {
        return screenLocation_;
    }

    GestureEvent& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
        globalPoint_.SetX(globalLocation.GetX());
        globalPoint_.SetY(globalLocation.GetY());
        return *this;
    }
    GestureEvent& SetLocalLocation(const Offset& localLocation)
    {
        localLocation_ = localLocation;
        return *this;
    }

    const Offset& GetLocalLocation() const
    {
        return localLocation_;
    }
    const Offset& GetGlobalLocation() const
    {
        return globalLocation_;
    }

    const Offset& GetPinchCenter() const
    {
        return pinchCenter_;
    }

    GestureEvent& SetPinchCenter(const Offset& pinchCenter)
    {
        pinchCenter_ = pinchCenter;
        return *this;
    }

    const std::list<FingerInfo>& GetFingerList() const
    {
        return fingerList_;
    }

    void SetFingerList(const std::list<FingerInfo>& fingerList)
    {
        fingerList_ = fingerList;
    }

    void SetSpeed(double speed)
    {
        speed_ = speed;
    }

    double GetSpeed() const
    {
        return speed_;
    }

    void SetMainSpeed(double mainSpeed)
    {
        mainSpeed_ = mainSpeed;
    }

    double GetMainSpeed() const
    {
        return mainSpeed_;
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

    void SetPressed(bool pressed)
    {
        pressed_ = pressed;
    }

    bool GetPressed() const
    {
        return pressed_;
    }

    void SetDelta(const Offset& delta)
    {
        delta_ = delta;
    }

    const Offset& GetDelta() const
    {
        return delta_;
    }

    void SetMainDelta(double mainDelta)
    {
        mainDelta_ = mainDelta;
    }

    double GetMainDelta() const
    {
        return mainDelta_;
    }

    void SetInputEventType(InputEventType type)
    {
        inputEventType_ = type;
    }

    InputEventType GetInputEventType() const
    {
        return inputEventType_;
    }
    void SetPointerId(int32_t pointerId)
    {
        pointerId_ = pointerId;
    }

    int32_t GetPointerId() const
    {
        return pointerId_;
    }

    void SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
    {
        pointerEvent_ = pointerEvent;
    }
    const std::shared_ptr<MMI::PointerEvent>& GetPointerEvent() const
    {
        return pointerEvent_;
    }

    void SetRawGlobalLocation(const Offset& rawGlobalLocation)
    {
        rawGlobalLocation_ = rawGlobalLocation;
    }

    const Offset& GetRawGlobalLocation() const
    {
        return rawGlobalLocation_;
    }

    float GetInputXDeltaSlope() const
    {
        return inputXDeltaSlope_;
    }

    float GetInputYDeltaSlope() const
    {
        return inputYDeltaSlope_;
    }

    bool IsInterpolated() const
    {
        return isInterpolated_;
    }

    void SetInputXDeltaSlope(float inputXDeltaSlope)
    {
        inputXDeltaSlope_ = inputXDeltaSlope;
    }

    void SetInputYDeltaSlope(float inputYDeltaSlope)
    {
        inputYDeltaSlope_ = inputYDeltaSlope;
    }

    void SetIsInterpolated(bool isInterpolated)
    {
        isInterpolated_ = isInterpolated;
    }

    void SetPointerEventId(int32_t pointerEventId)
    {
        pointerEventId_ = pointerEventId;
    }

    int32_t GetPointerEventId() const
    {
        return pointerEventId_;
    }

    void SetGestureTypeName(GestureTypeName gestureType)
    {
        gestureType_ = gestureType;
    }

    GestureTypeName GetGestureTypeName() const
    {
        return gestureType_;
    }
#ifdef SECURITY_COMPONENT_ENABLE
    void SetDisplayX(double displayX)
    {
        displayX_ = displayX;
    }

    double GetDisplayX() const
    {
        return displayX_;
    }

    void SetDisplayY(double displayY)
    {
        displayY_ = displayY;
    }

    double GetDisplayY() const
    {
        return displayY_;
    }

    void SetSecCompHandleEvent(const std::shared_ptr<JsonValue>& event)
    {
        secCompHandleEvent_ = event;
    }

    std::shared_ptr<JsonValue> GetSecCompHandleEvent() const
    {
        return secCompHandleEvent_;
    }
#endif
private:
    bool repeat_ = false;
    bool pressed_ = false;
    double offsetX_ = 0.0;
    double offsetY_ = 0.0;
    double scale_ = 1.0;
    double angle_ = 0.0;
    Velocity velocity_;
    double mainVelocity_ = 0.0;
    double speed_ = 0.0;
    double mainSpeed_ = 0.0;
    double mainDelta_ = 0.0;
    // Will be used in drag.
    int32_t pointerId_ = 0;
    int32_t pointerEventId_ = 0;
#ifdef SECURITY_COMPONENT_ENABLE
    double displayX_ = 0.0;
    double displayY_ = 0.0;
    std::shared_ptr<JsonValue> secCompHandleEvent_;
#endif
    std::shared_ptr<MMI::PointerEvent> pointerEvent_;
    Point globalPoint_;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;
    // Will be used in drag.
    Offset screenLocation_;
    // Raw last touchPoint global location.
    Offset rawGlobalLocation_;
    Offset pinchCenter_;
    Offset delta_;
    std::list<FingerInfo> fingerList_;
    InputEventType inputEventType_ = InputEventType::TOUCH_SCREEN;
    // Save historical touch point slope.
    bool isInterpolated_ = false;
    float inputXDeltaSlope_ = 0.0f;
    float inputYDeltaSlope_ = 0.0f;
    GestureTypeName gestureType_ = GestureTypeName::UNKNOWN;
};

using GestureEventFunc = std::function<void(GestureEvent& info)>;
using GestureEventNoParameter = std::function<void()>;

class ACE_EXPORT Gesture : public virtual AceType {
    DECLARE_ACE_TYPE(Gesture, AceType);

public:
    Gesture() = default;
    explicit Gesture(int32_t fingers) : fingers_(fingers) {}
    ~Gesture() override = default;

    void SetOnActionId(const GestureEventFunc& onActionId)
    {
        onActionId_ = std::make_unique<GestureEventFunc>(onActionId);
    }
    void SetOnActionStartId(const GestureEventFunc& onActionStartId)
    {
        onActionStartId_ = std::make_unique<GestureEventFunc>(onActionStartId);
    }
    void SetOnActionUpdateId(const GestureEventFunc& onActionUpdateId)
    {
        onActionUpdateId_ = std::make_unique<GestureEventFunc>(onActionUpdateId);
    }
    void SetOnActionEndId(const GestureEventFunc& onActionEndId)
    {
        onActionEndId_ = std::make_unique<GestureEventFunc>(onActionEndId);
    }
    void SetOnActionCancelId(const GestureEventFunc& onActionCancelId)
    {
        onActionCancelId_ = std::make_unique<GestureEventFunc>(onActionCancelId);
    }
    void SetPriority(GesturePriority priority)
    {
        priority_ = priority;
    }
    void SetGestureMask(GestureMask gestureMask)
    {
        gestureMask_ = gestureMask;
    }

    GesturePriority GetPriority() const
    {
        return priority_;
    }

    GestureMask GetGestureMask() const
    {
        return gestureMask_;
    }

    virtual RefPtr<GestureRecognizer> CreateRecognizer(WeakPtr<PipelineBase> context) = 0;

protected:
    int32_t fingers_ = 1;
    GesturePriority priority_ = GesturePriority::Low;
    GestureMask gestureMask_ = GestureMask::Normal;
    std::unique_ptr<GestureEventFunc> onActionId_;
    std::unique_ptr<GestureEventFunc> onActionStartId_;
    std::unique_ptr<GestureEventFunc> onActionUpdateId_;
    std::unique_ptr<GestureEventFunc> onActionEndId_;
    std::unique_ptr<GestureEventFunc> onActionCancelId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_EVENT_H