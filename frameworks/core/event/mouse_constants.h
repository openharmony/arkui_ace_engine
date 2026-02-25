/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_CONSTANTS_H

#include <cstdint>

namespace OHOS::Ace {

enum class AccessibilityHoverAction : int32_t {
    UNKNOWN = -1,
    HOVER_ENTER,
    HOVER_MOVE,
    HOVER_EXIT,
    HOVER_CANCEL
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
    SIDE_BUTTON = 32,
    EXTRA_BUTTON = 64,
    TASK_BUTTON = 128,
};

enum class HoverEffectType : int32_t {
    NONE,
    OPACITY,
    SCALE,
    BOARD,
    AUTO,
    UNKNOWN,
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_MOUSE_EVENT_H