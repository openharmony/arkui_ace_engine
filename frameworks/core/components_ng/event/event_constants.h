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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CONSTANTS_H

#include <cstdint>
namespace OHOS::Ace::NG {

enum class EventTreeType {
    TOUCH = 0,
    POST_EVENT,
};

enum class AxisModel {
    ABS_X = 0,
    ABS_Y,
    ABS_Z,
    ABS_RZ,
    ABS_GAS,
    ABS_BRAKE,
    ABS_HAT0X,
    ABS_HAT0Y,
};

enum class GestureCallbackType {
    START = 0,
    UPDATE,
    END,
    CANCEL,
};

} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

enum class UIInputEventType {
    NONE = 0,
    TOUCH,
    AXIS,
    KEY,
    FOCUS_AXIS,
};

enum class KeyIntention : int32_t {
    INTENTION_UNKNOWN = -1,
    INTENTION_UP = 1,
    INTENTION_DOWN = 2,
    INTENTION_LEFT = 3,
    INTENTION_RIGHT = 4,
    INTENTION_SELECT = 5,
    INTENTION_ESCAPE = 6,
    INTENTION_BACK = 7,
    INTENTION_FORWARD = 8,
    INTENTION_MENU = 9,
    INTENTION_HOME = 10,
    INTENTION_PAGE_UP = 11,
    INTENTION_PAGE_DOWN = 12,
    INTENTION_ZOOM_OUT = 13,
    INTENTION_ZOOM_IN = 14,

    INTENTION_MEDIA_PLAY_PAUSE = 100,
    INTENTION_MEDIA_FAST_FORWARD = 101,
    INTENTION_MEDIA_FAST_REWIND = 102,
    INTENTION_MEDIA_FAST_PLAYBACK = 103,
    INTENTION_MEDIA_NEXT = 104,
    INTENTION_MEDIA_PREVIOUS = 105,
    INTENTION_MEDIA_MUTE = 106,
    INTENTION_VOLUTE_UP = 107,
    INTENTION_VOLUTE_DOWN = 108,

    INTENTION_CALL = 200,
    INTENTION_ENDCALL = 201,
    INTENTION_REJECTCALL = 202,

    INTENTION_CAMERA = 300,
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_CONSTANTS_H
