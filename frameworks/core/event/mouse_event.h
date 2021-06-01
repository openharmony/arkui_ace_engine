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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H

#include "core/gestures/touch_event.h"

namespace OHOS::Ace {

static const int32_t MOUSE_BASE_ID = 1000;

enum class MouseAction : int32_t {
    NONE = 0,
    PRESS = 1,
    RELEASE = 2,
    MOVE = 3,
    HOVER_ENTER = 4,
    HOVER_MOVE = 5,
    HOVER_EXIT = 6,
};

enum class MouseState : int32_t {
    NONE = 0,
    HOVER = 1,
};

enum class MouseButton : int32_t {
    NONE_BUTTON = 0,
    LEFT_BUTTON = 1,
    RIGHT_BUTTON = 2,
    MIDDLE_BUTTON = 4,
    BACK_BUTTON = 8,
    FORWARD_BUTTON = 16,
};

struct MouseEvent final {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float deltaX = 0.0f;
    float deltaY = 0.0f;
    float deltaZ = 0.0f;
    float scrollX = 0.0f;
    float scrollY = 0.0f;
    float scrollZ = 0.0f;
    MouseAction action = MouseAction::NONE;
    MouseButton button = MouseButton::NONE_BUTTON;
    int32_t pressedButtons = 0; // combined by MouseButtons
    TimeStamp time;

    Offset GetOffset() const
    {
        return Offset(x, y);
    }

    int32_t GetId() const
    {
        if (pressedButtons > 0) {
            return pressedButtons + MOUSE_BASE_ID;
        } else {
            return (int32_t)button + MOUSE_BASE_ID;
        }
    }

    MouseEvent CreateScaleEvent(float scale) const
    {
        if (NearZero(scale)) {
            return { .x = x,
                .y = y,
                .z = z,
                .deltaX = deltaX,
                .deltaY = deltaY,
                .deltaZ = deltaZ,
                .scrollX = scrollX,
                .scrollY = scrollY,
                .scrollZ = scrollZ,
                .action = action,
                .button = button,
                .pressedButtons = pressedButtons,
                .time = time };
        }

        return { .x = x / scale,
            .y = y / scale,
            .z = z / scale,
            .deltaX = deltaX / scale,
            .deltaY = deltaY / scale,
            .deltaZ = deltaZ / scale,
            .scrollX = scrollX / scale,
            .scrollY = scrollY / scale,
            .scrollZ = scrollZ / scale,
            .action = action,
            .button = button,
            .pressedButtons = pressedButtons,
            .time = time };
    }

    TouchPoint CreateTouchPoint() const
    {
        TouchType type = TouchType::UNKNOWN;
        if (action == MouseAction::PRESS) {
            type = TouchType::DOWN;
        } else if (action == MouseAction::RELEASE) {
            type = TouchType::UP;
        } else if (action == MouseAction::MOVE) {
            type = TouchType::MOVE;
        } else {
            type = TouchType::UNKNOWN;
        }

        int32_t id = GetId();

        return { id, .x = x, .y = y, type, .time = time, .size = 0.0 };
    }

    MouseEvent operator-(const Offset& offset) const
    {
        return { .x = x - offset.GetX(),
            .y = y - offset.GetY(),
            .z = z,
            .deltaX = deltaX,
            .deltaY = deltaY,
            .deltaZ = deltaZ,
            .scrollX = scrollX,
            .scrollY = scrollY,
            .scrollZ = scrollZ,
            .action = action,
            .button = button,
            .pressedButtons = pressedButtons,
            .time = time };
    }
};

class MouseEventTarget : public virtual AceType {
    DECLARE_ACE_TYPE(MouseEventTarget, AceType);

public:
    virtual void HandleEvent(const MouseEvent& event) = 0;
};

using MouseTestResult = std::list<RefPtr<MouseEventTarget>>;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H
