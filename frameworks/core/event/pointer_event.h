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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_POINTER_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_POINTER_EVENT_H

#include <map>

#include "base/geometry/point.h"
#include "core/event/ace_events.h"
#include "core/event/axis_event.h"

namespace OHOS::MMI {
class PointerEvent;
}

namespace OHOS::Ace {

enum class KeyCode : int32_t;

enum class PointerAction : int32_t {
    UNKNOWN = 0,
    CANCEL = 1,
    DOWN = 2,
    MOVE = 3,
    UP = 4,
    AXIS_BEGIN = 5,
    AXIS_UPDATE = 6,
    AXIS_END = 7,
    BUTTON_DOWN = 8,
    BUTTON_UP = 9,
    ENTER_WINDOW = 10,
    LEAVE_WINDOW = 11,
    PULL_DOWN = 12,
    PULL_MOVE = 13,
    PULL_UP = 14,
    PULL_IN_WINDOW = 15,
    PULL_OUT_WINDOW = 16,
    SWIPE_BEGIN = 17,
    SWIPE_UPDATE = 18,
    SWIPE_END = 19,
    POINTER_ACTION_ROTATE_BEGIN = 20,
    POINTER_ACTION_ROTATE_UPDATE = 21,
    POINTER_ACTION_ROTATE_END = 22,
    PULL_CANCEL = 37,
};

struct DragPointerEvent final : public PointerEvent {
    int32_t pointerEventId = 0;
    int32_t pointerId = 0;
    int32_t pullId = -1;
    bool pressed = false;
    int32_t windowX = 0;
    int32_t windowY = 0;
    int32_t displayX = 0;
    int32_t displayY = 0;
    double size = 0.0;
    float force = 0.0f;
    int32_t deviceId = 0;
    TimeStamp downTime;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    int32_t targetWindowId = -1;
    std::shared_ptr<MMI::PointerEvent> rawPointerEvent;
    std::vector<KeyCode> pressedKeyCodes;
    PointerAction action = PointerAction::UNKNOWN;
    std::vector<DragPointerEvent> history;
    int32_t displayId = 0;
    int32_t sourceType = 0;
    int32_t originId = 0;

    DragPointerEvent() = default;
    DragPointerEvent(float x, float y)
        :PointerEvent(x, y)
    {}
    DragPointerEvent(int32_t windowX, int32_t windowY, int32_t displayX, int32_t displayY)
        : windowX(windowX), windowY(windowY), displayX(displayX), displayY(displayY)
    {}
    DragPointerEvent(int32_t pointerEventId, int32_t windowX, int32_t windowY, int32_t displayX, int32_t displayY)
        : pointerEventId(pointerEventId), windowX(windowX), windowY(windowY), displayX(displayX), displayY(displayY)
    {}

    Point GetPoint() const
    {
        if (!x && !y) {
            return Point(windowX, windowY, displayX, displayY);
        } else {
            return Point(x, y, x, y);
        }
    }

    int32_t GetDisplayX() const
    {
        return displayX;
    }

    int32_t GetDisplayY() const
    {
        return displayY;
    }

    void UpdatePressedKeyCodes(std::vector<KeyCode> keyCodes)
    {
        pressedKeyCodes = keyCodes;
    }

    int32_t GetTargetDisplayId() const
    {
        return targetWindowId;
    }
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_POINTER_EVENT_H