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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_CROWN_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_CROWN_EVENT_H
#include <map>
#include "core/event/ace_events.h"
#include "core/event/non_pointer_event.h"

namespace OHOS::MMI {
class CrownEvent;
}

namespace OHOS::Ace {

enum class CrownSensitivity: int32_t {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2,
};

enum class CrownAction : int32_t {
    BEGIN,
    UPDATE,
    END,
    UNKNOWN,
};

struct CrownEvent final : public NonPointerEvent {
    std::shared_ptr<MMI::PointerEvent> pointerEvent_;
    CrownAction action = CrownAction::UNKNOWN;
    TimeStamp timeStamp;
    double angularVelocity = 0.0;
    double degree = 0.0;
    int32_t touchEventId = 0;
    bool isInjected = false;

    CrownEvent()
    {
        eventType = UIInputEventType::CROWN;
    }
    CrownEvent(CrownAction action, TimeStamp timeStamp, double angularVelocity, double degree, bool isInjected)
        : action(action), timeStamp(timeStamp), angularVelocity(angularVelocity), degree(degree),
        isInjected(isInjected)
    {}
    CrownEvent(CrownAction action, int64_t timeStamp = 0, double angularVelocity = 0.0, double degree = 0.0,
        bool isInjected = false)
    {
        std::chrono::milliseconds milliseconds(timeStamp);
        TimeStamp time(milliseconds);
        new (this) CrownEvent(action, time, angularVelocity, degree, isInjected);
    }
    ~CrownEvent() = default;

    void SetTimeStamp(int64_t timeInt)
    {
        std::chrono::milliseconds milliseconds(timeInt);
        TimeStamp time(milliseconds);
        timeStamp = time;
    }

    void SetAction(CrownAction crownAction)
    {
        action = crownAction;
    }

    void SetPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
    {
        pointerEvent_ = pointerEvent;
    }

    const std::shared_ptr<MMI::PointerEvent>& GetPointerEvent() const
    {
        return pointerEvent_;
    }
};

class ACE_EXPORT CrownEventInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(CrownEventInfo, BaseEventInfo)

public:
    explicit CrownEventInfo(const CrownEvent& event) : BaseEventInfo("CrownEvent")
    {
        SetTimeStamp(event.timeStamp);
        angularVelocity_ = event.angularVelocity;
        degree_ = event.degree;
        action_ = event.action;
        isInjected_ = event.isInjected;
    };
    ~CrownEventInfo() override = default;

    double GetAngularVelocity() const
    {
        return angularVelocity_;
    }

    double GetDegree() const
    {
        return degree_;
    }

    CrownAction GetAction() const
    {
        return action_;
    }

    bool GetIsInjected() const
    {
        return isInjected_;
    }
private:
    double angularVelocity_ = 0.0;
    double degree_ = 0.0;
    CrownAction action_ = CrownAction::UNKNOWN;
    bool isInjected_ = false;
};

using OnCrownEventFunc = std::function<bool(const CrownEvent&)>;
using OnCrownCallbackFunc = std::function<void(CrownEventInfo&)>;

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_CROWN_EVENT_H
