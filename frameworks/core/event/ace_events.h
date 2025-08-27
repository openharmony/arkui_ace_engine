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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_ACE_EVENTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_ACE_EVENTS_H

#include <chrono>
#include <cstdint>
#include <string>
#include <optional>

#include "base/geometry/dimension_offset.h"
#include "base/geometry/dimension_rect.h"
#include "base/memory/type_info_base.h"
#include "base/utils/type_definition.h"
#include "core/components_ng/event/event_constants.h"

namespace OHOS::Ace {

using ConvertInfo = std::pair<UIInputEventType, UIInputEventType>;

enum class KeyCode : int32_t;

enum class SourceType : int32_t {
    NONE = 0,
    MOUSE = 1,
    TOUCH = 2,
    TOUCH_PAD = 3,
    KEYBOARD = 4,
    JOYSTICK = 5,
    CROWN = 6,
};

enum class SourceTool : int32_t {
    UNKNOWN = 0,
    FINGER = 1,
    PEN = 2,
    RUBBER = 3,
    BRUSH = 4,
    PENCIL = 5,
    AIRBRUSH = 6,
    MOUSE = 7,
    LENS = 8,
    TOUCHPAD = 9,
    JOYSTICK = 10,
};

struct EventTarget final {
    std::string id;
    std::string type;
    DimensionRect area;
    DimensionOffset origin;
};

class BaseEventInfo : public virtual TypeInfoBase {
    DECLARE_RELATIONSHIP_OF_CLASSES(BaseEventInfo, TypeInfoBase);

public:
    explicit BaseEventInfo(const std::string& type) : type_(type) {}
    ~BaseEventInfo() override = default;

    const std::string& GetType() const
    {
        return type_;
    }
    void SetType(const std::string& type)
    {
        type_ = type;
    }

    const TimeStamp& GetTimeStamp() const
    {
        return timeStamp_;
    }
    BaseEventInfo& SetTimeStamp(const TimeStamp& timeStamp)
    {
        timeStamp_ = timeStamp;
        return *this;
    }

    const EventTarget& GetTarget() const
    {
        return target_;
    }
    EventTarget& GetTargetWithModify()
    {
        return target_;
    }

    BaseEventInfo& SetTarget(const EventTarget& target)
    {
        target_ = target;
        return *this;
    }

    int64_t GetDeviceId() const
    {
        return deviceId_;
    }
    void SetDeviceId(int64_t deviceId)
    {
        deviceId_ = deviceId;
    }

    int32_t GetTargetDisplayId() const
    {
        return targetDisplayId_;
    }
    void SetTargetDisplayId(int32_t targetDisplayId)
    {
        targetDisplayId_ = targetDisplayId;
    }

    SourceType GetSourceDevice() const
    {
        return deviceType_;
    }
    void SetSourceDevice(SourceType deviceType)
    {
        deviceType_ = deviceType;
    }

    void SetForce(float force)
    {
        force_ = force;
    }
    float GetForce() const
    {
        return force_;
    }

    void SetTiltX(float tiltX)
    {
        tiltX_ = tiltX;
    }
    std::optional<float> GetTiltX() const
    {
        return tiltX_;
    }

    void SetTiltY(float tiltY)
    {
        tiltY_ = tiltY;
    }
    std::optional<float> GetTiltY() const
    {
        return tiltY_;
    }

    void SetRollAngle(float rollAngle)
    {
        rollAngle_ = rollAngle;
    }
    std::optional<float> GetRollAngle() const
    {
        return rollAngle_;
    }

    void SetSourceTool(SourceTool tool)
    {
        sourceTool_ = tool;
    }
    SourceTool GetSourceTool() const
    {
        return sourceTool_;
    }

    bool IsStopPropagation() const
    {
        return stopPropagation_;
    }
    void SetStopPropagation(bool stopPropagation)
    {
        stopPropagation_ = stopPropagation;
    }

    bool IsPreventDefault() const
    {
        return preventDefault_;
    }
    void SetPreventDefault(bool preventDefault)
    {
        preventDefault_ = preventDefault;
    }

    const std::string& GetPatternName() const
    {
        return patternName_;
    }
    void SetPatternName(const std::string& patternName)
    {
        patternName_ = patternName;
    }

    const std::vector<KeyCode>& GetPressedKeyCodes() const
    {
        return pressedKeyCodes_;
    }

    void SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
    {
        pressedKeyCodes_ = pressedKeyCodes;
    }

    bool IsKeyPressed(KeyCode code) const
    {
        return (std::find(pressedKeyCodes_.begin(), pressedKeyCodes_.end(), code) != pressedKeyCodes_.end());
    }

    int32_t GetPostEventNodeId() const
    {
        return postEventNodeId_;
    }

    void SetPostEventNodeId(int32_t postEventNodeId)
    {
        postEventNodeId_ = postEventNodeId;
    }

    bool GetIsPostEventResult() const
    {
        return isPostEventResult_;
    }

    void SetIsPostEventResult(bool isPostEventResult)
    {
        isPostEventResult_ = isPostEventResult;
    }

    int32_t GetOperatingHand() const
    {
        return operatingHand_;
    }

    void SetOperatingHand(int32_t operatingHand)
    {
        operatingHand_ = operatingHand;
    }

    float GetHorizontalAxis() const
    {
        return horizontalAxis_;
    }

    float GetVerticalAxis() const
    {
        return verticalAxis_;
    }

    float GetPinchAxisScale() const
    {
        return pinchAxisScale_;
    }

    void SetHorizontalAxis(float axis)
    {
        horizontalAxis_ = axis;
    }

    void SetVerticalAxis(float axis)
    {
        verticalAxis_ = axis;
    }

    void SetPinchAxisScale(float scale)
    {
        pinchAxisScale_ = scale;
    }

    void CopyConvertInfoFrom(const ConvertInfo& info)
    {
        convertInfo = info;
    }

    UIInputEventType GetOriginUIInputEventType() const
    {
        return convertInfo.first;
    }

    UIInputEventType GetCurrentUIInputEventType() const
    {
        return convertInfo.second;
    }
protected:
    // Event type like onTouchDown, onClick and so on.
    std::string type_;
    // The origin event time stamp.
    TimeStamp timeStamp_;
    EventTarget target_;
    // Will be used in drag.
    SourceType deviceType_ = SourceType::NONE;
    float force_ = 0.0f;
    std::optional<float> tiltX_;
    std::optional<float> tiltY_;
    std::optional<float> rollAngle_;
    SourceTool sourceTool_ = SourceTool::UNKNOWN;
    int64_t deviceId_ = 0;
    // Will be used in drag.
    int32_t targetDisplayId_ = 0;
    bool stopPropagation_ = false;
    bool preventDefault_ = false;
    std::string patternName_;
    std::vector<KeyCode> pressedKeyCodes_;
    bool isPostEventResult_ = false;
    int32_t postEventNodeId_ = -1;
    int32_t operatingHand_ = 0;
    float horizontalAxis_ = 0.0;
    float verticalAxis_ = 0.0;
    float pinchAxisScale_ = 0.0;
    ConvertInfo convertInfo = { UIInputEventType::NONE, UIInputEventType::NONE };
};

class PropagationEventInfo : public virtual TypeInfoBase {
    DECLARE_RELATIONSHIP_OF_CLASSES(PropagationEventInfo, TypeInfoBase);

public:
    bool IsStopPropagation() const
    {
        return stopPropagation_;
    }
    void SetStopPropagation(bool stopPropagation)
    {
        stopPropagation_ = stopPropagation;
    }

private:
    bool stopPropagation_ = false;
};

class EventToJSONStringAdapter : public virtual TypeInfoBase {
    DECLARE_RELATIONSHIP_OF_CLASSES(EventToJSONStringAdapter, TypeInfoBase);

public:
    EventToJSONStringAdapter() = default;
    ~EventToJSONStringAdapter() = default;

    virtual std::string ToJSONString() const = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_ACE_EVENTS_H
