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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_GESTURES_GESTURE_INFO_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_GESTURES_GESTURE_INFO_H

#include "ui/base/geometry/point.h"
#include "ui/base/geometry/offset.h"
#include "ui/gestures/velocity.h"
#include "ui/event/ace_events.h"

namespace OHOS::Ace {

class GestureRecognizer;
class PipelineBase;

enum class InputEventType {
    TOUCH_SCREEN = 0,
    TOUCH_PAD,
    MOUSE_BUTTON,
    AXIS,
    KEYBOARD,
};

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

struct FingerInfo {
    int32_t fingerId_ = -1;
    int32_t operatingHand_ = 0;
    // global position at which the touch point contacts the screen.
    Offset globalLocation_;
    // Different from global location, The local location refers to the location of the contact point relative to the
    // current node which has the recognizer.
    Offset localLocation_;

    //screen position at which the touch point contacts the screen.
    Offset screenLocation_;
    // The location where the touch point touches the screen when there are multiple screens.
    Offset globalDisplayLocation_;
    SourceType sourceType_ = SourceType::NONE;
    SourceTool sourceTool_ = SourceTool::UNKNOWN;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_GESTURES_GESTURE_INFO_H
