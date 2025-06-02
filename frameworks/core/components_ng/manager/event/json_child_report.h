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

    std::shared_ptr<InspectorJsonValue> GetJsonData() const override;

private:
    std::string hostName_;
    int64_t actualDuration_;
    Point startPoint_;
    Point endPoint_;
    DropResult dropResult_;
    DragReporterPharse pharse_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_EVENT_JSON_CHILD_REPORT_H