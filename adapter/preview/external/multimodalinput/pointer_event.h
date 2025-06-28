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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_POINTER_EVENT_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_POINTER_EVENT_H

#include <list>
#include <memory>
#include <set>
#include <array>
#include <vector>
#include <optional>
#include <functional>

#include "adapter/preview/external/multimodalinput/common_type.h"

namespace OHOS {
namespace MMI {

enum class TouchType : size_t {
    DOWN = 0,
    UP,
    MOVE,
    CANCEL,
    PULL_DOWN,
    PULL_UP,
    PULL_MOVE,
    PULL_IN_WINDOW,
    PULL_OUT_WINDOW,
    UNKNOWN,
};

struct TouchPoint final {
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    double globalDisplayX = 0.0;
    double globalDisplayY = 0.0;
    TimeStamp downTime;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    SourceTool sourceTool = SourceTool::UNKNOWN;
    bool isPressed = false;
};

class PointerEvent {
public:
    PointerEvent() = default;
    ~PointerEvent() = default;

public:
    int32_t id = 0;
    float x = 0.0f;
    float y = 0.0f;
    float screenX = 0.0f;
    float screenY = 0.0f;
    double globalDisplayX = 0.0;
    double globalDisplayY = 0.0;
    TouchType type = TouchType::UNKNOWN;
    TouchType pullType = TouchType::UNKNOWN;
    TimeStamp time;
    double size = 0.0;
    float force = 0.0f;
    std::optional<float> tiltX;
    std::optional<float> tiltY;
    int64_t deviceId = 0;
    int32_t sourceType = 0; // SOURCE_TYPE_UNKNOWN == SourceType::NONE == 0
    SourceTool sourceTool = SourceTool::UNKNOWN;
    std::vector<TouchPoint> pointers;

    // pointerAction_
    static constexpr int32_t POINTER_ACTION_UNKNOWN = 0;
    static constexpr int32_t POINTER_ACTION_CANCEL = 1;
    static constexpr int32_t POINTER_ACTION_DOWN = 2;
    static constexpr int32_t POINTER_ACTION_MOVE = 3;
    static constexpr int32_t POINTER_ACTION_UP = 4;
    static constexpr int32_t POINTER_ACTION_AXIS_BEGIN = 5;
    static constexpr int32_t POINTER_ACTION_AXIS_UPDATE = 6;
    static constexpr int32_t POINTER_ACTION_AXIS_END = 7;
    static constexpr int32_t POINTER_ACTION_BUTTON_DOWN = 8;
    static constexpr int32_t POINTER_ACTION_BUTTON_UP = 9;
    static constexpr int32_t POINTER_ACTION_ENTER_WINDOW = 10;
    static constexpr int32_t POINTER_ACTION_LEAVE_WINDOW = 11;
    static constexpr int32_t POINTER_ACTION_PULL_DOWN = 12;
    static constexpr int32_t POINTER_ACTION_PULL_MOVE = 13;
    static constexpr int32_t POINTER_ACTION_PULL_UP = 14;
    static constexpr int32_t POINTER_ACTION_PULL_IN_WINDOW = 15;
    static constexpr int32_t POINTER_ACTION_PULL_OUT_WINDOW = 16;
    static constexpr int32_t POINTER_ACTION_SWIPE_BEGIN = 17;
    static constexpr int32_t POINTER_ACTION_SWIPE_UPDATE = 18;
    static constexpr int32_t POINTER_ACTION_SWIPE_END = 19;
    static constexpr int32_t POINTER_ACTION_ROTATE_BEGIN = 20;
    static constexpr int32_t POINTER_ACTION_ROTATE_UPDATE = 21;
    static constexpr int32_t POINTER_ACTION_ROTATE_END = 22;

    // sourceType
    static constexpr int32_t SOURCE_TYPE_UNKNOWN = 0;
    static constexpr int32_t SOURCE_TYPE_MOUSE = 1;
    static constexpr int32_t SOURCE_TYPE_TOUCHSCREEN = 2;
    static constexpr int32_t SOURCE_TYPE_TOUCHPAD = 3;
    static constexpr int32_t SOURCE_TYPE_JOYSTICK = 4;
    static constexpr int32_t SOURCE_TYPE_CROWN = 5;

    // buttonId_
    static constexpr int32_t BUTTON_NONE = -1;
    static constexpr int32_t MOUSE_BUTTON_LEFT = 0;
    static constexpr int32_t MOUSE_BUTTON_RIGHT = 1;
    static constexpr int32_t MOUSE_BUTTON_MIDDLE = 2;
    static constexpr int32_t MOUSE_BUTTON_SIDE = 3;
    static constexpr int32_t MOUSE_BUTTON_EXTRA = 4;
    static constexpr int32_t MOUSE_BUTTON_FORWARD = 5;
    static constexpr int32_t MOUSE_BUTTON_BACK = 6;
    static constexpr int32_t MOUSE_BUTTON_TASK = 7;

    enum AxisType {
        AXIS_TYPE_UNKNOWN,
        AXIS_TYPE_SCROLL_VERTICAL,
        AXIS_TYPE_SCROLL_HORIZONTAL,
        AXIS_TYPE_PINCH,
        AXIS_TYPE_ROTATE,
        AXIS_TYPE_ABS_X,
        AXIS_TYPE_ABS_Y,
        AXIS_TYPE_ABS_Z,
        AXIS_TYPE_ABS_RZ,
        AXIS_TYPE_ABS_GAS,
        AXIS_TYPE_ABS_BRAKE,
        AXIS_TYPE_ABS_HAT0X,
        AXIS_TYPE_ABS_HAT0Y,
        AXIS_TYPE_ABS_THROTTLE,
        AXIS_TYPE_MAX
    };

    int32_t pointerAction_ { POINTER_ACTION_UNKNOWN };
    int32_t buttonId_ { -1 };
    std::set<int32_t> pressedButtons_;
    std::array<double, AXIS_TYPE_MAX> axisValues_ {};
    int32_t targetDisplayId_ { -1 }; // InputEvent
};

} // namespace MMI
} // namespace OHOS
#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_POINTER_EVENT_H
