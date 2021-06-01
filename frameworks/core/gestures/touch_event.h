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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_TOUCH_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_TOUCH_EVENT_H

#include <list>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

enum class TouchType : size_t {
    DOWN = 0,
    UP,
    MOVE,
    CANCEL,
    UNKNOWN,
};

struct TouchRestrict final {
    static constexpr uint32_t NONE = 0x00000000;
    static constexpr uint32_t CLICK = 0x00000001;
    static constexpr uint32_t LONG_PRESS = 0x00000010;
    static constexpr uint32_t SWIPE_LEFT = 0x00000100;
    static constexpr uint32_t SWIPE_RIGHT = 0x00000200;
    static constexpr uint32_t SWIPE_UP = 0x00000400;
    static constexpr uint32_t SWIPE_DOWN = 0x00000800;
    static constexpr uint32_t SWIPE = 0x00000F00;
    static constexpr uint32_t SWIPE_VERTICAL = 0x0000C00;   // Vertical
    static constexpr uint32_t SWIPE_HORIZONTAL = 0x0000300; // Horizontal
    static constexpr uint32_t TOUCH = 0xFFFFFFFF;

    uint32_t forbiddenType = NONE;

    void UpdateForbiddenType(uint32_t gestureType)
    {
        forbiddenType |= gestureType;
    }
};

struct TouchPoint final {
    // The ID is used to identify the point of contact between the finger and the screen. Different fingers have
    // different ids.
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    TouchType type = TouchType::UNKNOWN;
    TimeStamp time;
    double size = 0.0;
    float pressure = 0.0f;
    int64_t deviceId = 0;

    Offset GetOffset() const
    {
        return Offset(x, y);
    }

    TouchPoint CreateScalePoint(float scale) const
    {
        if (NearZero(scale)) {
            return { id, x, y, type, time, size, pressure, deviceId };
        }
        return { id, x / scale, y / scale, type, time, size, pressure, deviceId };
    }
};

class TouchCallBackInfo : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchCallBackInfo, BaseEventInfo);

public:
    explicit TouchCallBackInfo(TouchType type) : BaseEventInfo("onTouchEvent"), touchType_(type) {}
    ~TouchCallBackInfo() override = default;

    void SetScreenX(float screenX)
    {
        screenX_ = screenX;
    }
    float GetScreenX() const
    {
        return screenX_;
    }
    void SetScreenY(float screenY)
    {
        screenY_ = screenY;
    }
    float GetScreenY() const
    {
        return screenY_;
    }
    void SetLocalX(float localX)
    {
        localX_ = localX;
    }
    float GetLocalX() const
    {
        return localX_;
    }
    void SetLocalY(float localY)
    {
        localY_ = localY;
    }
    float GetLocalY() const
    {
        return localY_;
    }
    void SetTouchType(TouchType type)
    {
        touchType_ = type;
    }
    TouchType GetTouchType() const
    {
        return touchType_;
    }
    void SetTimeStamp(const TimeStamp& time)
    {
        time_ = time;
    }
    TimeStamp GetTimeStamp() const
    {
        return time_;
    }
    void SetPressure(float pressure)
    {
        pressure_ = pressure;
    }
    float GetPressure() const
    {
        return pressure_;
    }
    void SetDeviceId(int64_t deviceId)
    {
        deviceId_ = deviceId;
    }
    int64_t GetDeviceId() const
    {
        return deviceId_;
    }

private:
    float screenX_ = 0.0f;
    float screenY_ = 0.0f;
    float localX_ = 0.0f;
    float localY_ = 0.0f;
    float pressure_ = 0.0f;
    TouchType touchType_ = TouchType::UNKNOWN;
    TimeStamp time_;
    int64_t deviceId_ = 0;
};

class TouchLocationInfo : public TypeInfoBase {
    DECLARE_RELATIONSHIP_OF_CLASSES(TouchLocationInfo, TypeInfoBase);

public:
    explicit TouchLocationInfo(int32_t fingerId) : fingerId_(fingerId) {}
    ~TouchLocationInfo() override = default;

    TouchLocationInfo& SetGlobalLocation(const Offset& globalLocation)
    {
        globalLocation_ = globalLocation;
        return *this;
    }
    TouchLocationInfo& SetLocalLocation(const Offset& localLocation)
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
    int32_t GetFingerId() const
    {
        return fingerId_;
    }

    void SetSize(double size)
    {
        size_ = size;
    }

    double GetSize() const
    {
        return size_;
    }

private:
    // The finger id is used to identify the point of contact between the finger and the screen. Different fingers have
    // different ids.
    int32_t fingerId_ = -1;

    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;

    // finger touch size
    double size_ = 0.0;
};

class TouchEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(TouchEventTarget, AceType);

public:
    virtual bool DispatchEvent(const TouchPoint& point) = 0;
    virtual bool HandleEvent(const TouchPoint& point) = 0;

    void SetTouchRestrict(const TouchRestrict& touchRestrict)
    {
        touchRestrict_ = touchRestrict;
    }

protected:
    TouchRestrict touchRestrict_ { TouchRestrict::NONE };
};

using TouchTestResult = std::list<RefPtr<TouchEventTarget>>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_TOUCH_EVENT_H
