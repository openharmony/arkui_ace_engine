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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_CHILD_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_CHILD_REPORT_H

#include <functional>
#include <limits>

#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/event/json_report.h"
#include "core/gestures/click_info.h"
#include "frameworks/core/gestures/gesture_event.h"
#include "frameworks/core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
class TapJsonReport : public JsonReport {
public:
    void SetCount(int32_t count)
    {
        count_ = count;
    }

    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    int32_t count_;
};

class LongPressJsonReport : public JsonReport {
public:
    void SetDuration(long long duration)
    {
        duration_ = duration;
    }

    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    long long duration_;
};

class PanJsonReport : public JsonReport {
public:
    void SetPanDirection(int32_t direction)
    {
        direction_ = direction;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    int32_t direction_;
};

class PinchJsonReport : public JsonReport {
public:
    void SetScale(double scale)
    {
        scale_ = scale;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    double scale_;
};

class RotationJsonReport : public JsonReport {
public:
    void SetAngle(double angle)
    {
        angle_ = angle;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    double angle_;
};

class SwipeJsonReport : public JsonReport {
public:
    void SetSwipeDirection(int32_t direction)
    {
        direction_ = direction;
    }

    void SetTouchEvents(std::map<int32_t, TouchEvent> touchEvents)
    {
        touchEvents_ = touchEvents;
    }

    void SetSpeed(double speed)
    {
        speed_ = speed;
    }

    void SetActualSpeed(double actualSpeed)
    {
        actualSpeed_ = actualSpeed;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    int32_t direction_;
    std::map<int32_t, TouchEvent> touchEvents_;
    double speed_;
    double actualSpeed_;
};

class ClickJsonReport : public JsonReport {
public:
    void SetCount(int32_t count)
    {
        count_ = count;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    int32_t count_;
};

class DragJsonReport : public JsonReport {
public:
    void SetHostName(std::string hostName)
    {
        hostName_ = hostName;
    }

    void SetActualDuration(int64_t actualDuration)
    {
        actualDuration_ = actualDuration;
    }

    void SetStartPoint(Point startPoint)
    {
        startPoint_ = startPoint;
    }

    void SetEndPoint(Point endPoint)
    {
        endPoint_ = endPoint;
    }

    void SetDropResult(DropResult dropResult)
    {
        dropResult_ = dropResult;
    }

    void SetDragReporterPharse(DragReporterPharse pharse)
    {
        pharse_ = pharse;
    }

    void SetStartId(int32_t startId)
    {
        startId_ = startId;
    }

    void SetDropId(int32_t dropId)
    {
        dropId_ = dropId;
    }

    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    std::string hostName_;
    int64_t actualDuration_;
    int32_t startId_;
    int32_t dropId_;
    Point startPoint_;
    Point endPoint_;
    DropResult dropResult_;
    DragReporterPharse pharse_;
};

class TouchJsonReport : public JsonReport {
public:
    void SetEventType(std::string eventType)
    {
        eventType_ = eventType;
    }
    void SetAction(std::string action)
    {
        action_ = action;
    }
    void SetTime(TimeStamp time)
    {
        time_ = time;
    }
    void SetWindowID(int32_t windowID)
    {
        windowID_ = windowID;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    TimeStamp time_;
    std::string eventType_;
    std::string action_;
    int32_t windowID_;
};

class MouseJsonReport : public JsonReport {
public:
    void SetWindowID(int32_t windowID)
    {
        windowID_ = windowID;
    }
    void SetEventType(std::string eventType)
    {
        eventType_ = eventType;
    }
    void SetTime(TimeStamp time)
    {
        time_ = time;
    }
    void SetAction(std::string action)
    {
        action_ = action;
    }
    void SetMouseButton(std::string mouseButton)
    {
        mouseButton_ = mouseButton;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    TimeStamp time_;
    std::string eventType_;
    std::string action_;
    std::string mouseButton_;
    int32_t windowID_;
};

class KeyJsonReport : public JsonReport {
public:
    void SetWindowID(int32_t windowID)
    {
        windowID_ = windowID;
    }
    void SetEventType(std::string eventType)
    {
        eventType_ = eventType;
    }
    void SetTime(TimeStamp time)
    {
        time_ = time;
    }
    void SetKeyCode(int32_t keyCode)
    {
        keyCode_ = keyCode;
    }
    void SetAction(std::string action)
    {
        action_ = action;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    TimeStamp time_;
    std::string eventType_;
    std::string action_;
    int32_t windowID_;
    int32_t keyCode_;
};

struct AxisValue {
    double horizontalAxis = 0.0;
    double verticalAxis = 0.0;
    double pinchAxisScale = 0.0;
    double rotateAxisAngle = 0.0;
};

class AxisJsonReport : public JsonReport {
public:
    void SetWindowID(int32_t windowID)
    {
        windowID_ = windowID;
    }
    void SetEventType(std::string eventType)
    {
        eventType_ = eventType;
    }
    void SetTime(TimeStamp time)
    {
        time_ = time;
    }
    void SetAction(std::string action)
    {
        action_ = action;
    }
    void SetPoint(Point point)
    {
        point_ = point;
    }
    void SetAxisValues(AxisValue axisValues)
    {
        axisValues_ = axisValues;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    AxisValue axisValues_;
    TimeStamp time_;
    std::string eventType_;
    std::string action_;
    int32_t windowID_;
    Point point_;
};

class FocusJsonReport : public JsonReport {
public:
    void SetWindowID(int32_t windowID)
    {
        windowID_ = windowID;
    }
    void SetEventType(std::string eventType)
    {
        eventType_ = eventType;
    }
    void SetTime(TimeStamp time)
    {
        time_ = time;
    }
    void SetIsFocus(bool isFocus)
    {
        isFocus_ = isFocus;
    }

    void SetAction(std::string action)
    {
        action_ = action;
    }
    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    std::string eventType_;
    std::string action_;
    TimeStamp time_;
    int32_t windowID_;
    bool isFocus_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_CHILD_REPORT_H