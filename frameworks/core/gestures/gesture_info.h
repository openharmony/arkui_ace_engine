/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_INFO_H

#include <functional>
#include <string>
#include <vector>

#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/type_definition.h"

namespace OHOS::Ace {

class GestureRecognizer;
class PipelineContext;

enum class GesturePriority {
    Begin = -1,
    Low = 0,
    High,
    Parallel,
    End,
};

enum class GestureMask {
    Begin = -1,
    Normal = 0,
    IgnoreInternal,
    End,
};

enum class GestureMode {
    Begin = -1,
    Sequence = 0,
    Parallel,
    Exclusive,
    End,
};

enum class Direction {
    BEGIN = -1,
    ALL = 0,
    HORIZONTAL,
    VERTICAL,
    END,
};

class GestureEvent {
public:
    GestureEvent() {}
    ~GestureEvent() = default;

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

    GestureEvent& SetTimeStamp(const TimeStamp& timeStamp)
    {
        timeStamp_ = timeStamp;
        return *this;
    }

    const TimeStamp& GetTimeStamp() const
    {
        return timeStamp_;
    }

    GestureEvent& SetGlobalPoint(const Point& globalPoint)
    {
        globalPoint_ = globalPoint;
        return *this;
    }

    const Point& GetGlobalPoint() const
    {
        return globalPoint_;
    }

    GestureEvent& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
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

private:
    bool repeat_ = false;
    double offsetX_ = 0.0;
    double offsetY_ = 0.0;
    double scale_ = 1.0;
    double angle_ = 0.0;
    TimeStamp timeStamp_;
    Point globalPoint_;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;
};

using GestureEventFunc = std::function<void(const GestureEvent& info)>;
using GestureEventNoParameter = std::function<void()>;

class ACE_EXPORT Gesture : public virtual AceType {
    DECLARE_ACE_TYPE(Gesture, AceType);

public:
    Gesture() = default;
    explicit Gesture(int32_t fingers) : fingers_(fingers) {};
    ~Gesture() override = default;

    void SetOnActionId(const GestureEventFunc&& onActionId)
    {
        onActionId_ = std::make_unique<GestureEventFunc>(onActionId);
    }
    void SetOnActionStartId(const GestureEventFunc&& onActionStartId)
    {
        onActionStartId_ = std::make_unique<GestureEventFunc>(onActionStartId);
    }
    void SetOnActionUpdateId(const GestureEventFunc&& onActionUpdateId)
    {
        onActionUpdateId_ = std::make_unique<GestureEventFunc>(onActionUpdateId);
    }
    void SetOnActionEndId(const GestureEventFunc&& onActionEndId)
    {
        onActionEndId_ = std::make_unique<GestureEventFunc>(onActionEndId);
    }
    void SetOnActionCancelId(const GestureEventNoParameter& onActionCancelId)
    {
        onActionCancelId_ = std::make_unique<GestureEventNoParameter>(onActionCancelId);
    }
    void SetPriority(GesturePriority priority)
    {
        priority_ = priority;
    }
    void SetGestureMask(GestureMask gestureMask)
    {
        gestureMask_ = gestureMask;
    }

    virtual RefPtr<GestureRecognizer> CreateRecognizer(WeakPtr<PipelineContext> context) = 0;

protected:
    int32_t fingers_ = 1;
    GesturePriority priority_ = GesturePriority::Low;
    GestureMask gestureMask_ = GestureMask::Normal;
    std::unique_ptr<GestureEventFunc> onActionId_;
    std::unique_ptr<GestureEventFunc> onActionStartId_;
    std::unique_ptr<GestureEventFunc> onActionUpdateId_;
    std::unique_ptr<GestureEventFunc> onActionEndId_;
    std::unique_ptr<GestureEventNoParameter> onActionCancelId_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_INFO_H
