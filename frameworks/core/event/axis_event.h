/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H

#include <list>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

constexpr double MOUSE_WHEEL_DEGREES = 15.0;
constexpr double DP_PER_LINE_DESKTOP = 40.0;
constexpr int32_t LINE_NUMBER_DESKTOP = 3;
constexpr int32_t DP_PER_LINE_PHONE = 64;
constexpr int32_t LINE_NUMBER_PHONE = 1;

enum class AxisDirection : int32_t {
    NONE = 0,
    UP = 1,
    DOWN = 2,
    LEFT = 4,
    RIGHT = 8,
    UP_LEFT = 5,
    UP_RIGHT = 9,
    DOWN_LEFT = 6,
    DOWN_RIGHT = 10,
};

enum class AxisAction : int32_t {
    NONE = 0,
    BEGIN,
    UPDATE,
    END,
};

struct AxisEvent final {
    float x = 0.0;
    float y = 0.0;
    double verticalAxis = 0.0;
    double horizontalAxis = 0.0;
    double pinchAxisScale = 0.0;
    AxisAction action;
    TimeStamp time;
    int64_t deviceId = 0;
    SourceType sourceType = SourceType::NONE;

    AxisEvent CreateScaleEvent(float scale) const
    {
        if (NearZero(scale)) {
            return { .x = x,
                .y = y,
                .verticalAxis = verticalAxis,
                .horizontalAxis = horizontalAxis,
                .pinchAxisScale = pinchAxisScale,
                .action = action,
                .time = time,
                .deviceId = deviceId,
                .sourceType = sourceType };
        }
        return { .x = x / scale,
            .y = y / scale,
            .verticalAxis = verticalAxis,
            .horizontalAxis = horizontalAxis,
            .pinchAxisScale = pinchAxisScale,
            .action = action,
            .time = time,
            .deviceId = deviceId,
            .sourceType = sourceType };
    }
    AxisDirection GetDirection() const
    {
        uint32_t verticalFlag = 0;
        uint32_t horizontalFlag = 0;
        if (LessNotEqual(verticalAxis, 0.0)) {
            verticalFlag = static_cast<uint32_t>(AxisDirection::UP);
        } else if (GreatNotEqual(verticalAxis, 0.0)) {
            verticalFlag = static_cast<uint32_t>(AxisDirection::DOWN);
        }
        if (LessNotEqual(horizontalAxis, 0.0)) {
            horizontalFlag = static_cast<uint32_t>(AxisDirection::LEFT);
        } else if (GreatNotEqual(horizontalAxis, 0.0)) {
            horizontalFlag = static_cast<uint32_t>(AxisDirection::RIGHT);
        }
        return static_cast<AxisDirection>(verticalFlag | horizontalFlag);
    }
    static bool IsDirectionUp(AxisDirection direction)
    {
        return (static_cast<int32_t>(direction) & static_cast<int32_t>(AxisDirection::UP));
    }
    static bool IsDirectionDown(AxisDirection direction)
    {
        return (static_cast<int32_t>(direction) & static_cast<int32_t>(AxisDirection::DOWN));
    }
    static bool IsDirectionLeft(AxisDirection direction)
    {
        return (static_cast<int32_t>(direction) & static_cast<int32_t>(AxisDirection::LEFT));
    }
    static bool IsDirectionRight(AxisDirection direction)
    {
        return (static_cast<int32_t>(direction) & static_cast<int32_t>(AxisDirection::RIGHT));
    }
};

class AxisEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(AxisEventTarget, AceType);

public:
    virtual void HandleEvent(const AxisEvent& event) = 0;
};

using AxisTestResult = std::list<RefPtr<AxisEventTarget>>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_AXIS_EVENT_H