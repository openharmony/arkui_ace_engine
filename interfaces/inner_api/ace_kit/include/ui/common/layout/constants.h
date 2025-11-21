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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_COMMON_LAYOUT_CONSTANTS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_COMMON_LAYOUT_CONSTANTS_H

#include <cstdint>
#include <string>

namespace OHOS::Ace {

enum class GestureTypeName {
    UNKNOWN = -1,
    TAP_GESTURE = 0,
    LONG_PRESS_GESTURE = 1,
    PAN_GESTURE = 2,
    PINCH_GESTURE = 3,
    SWIPE_GESTURE = 4,
    ROTATION_GESTURE = 5,
    DRAG = 6,
    CLICK = 7,
    BOXSELECT = 8,
    WEBSCROLL = 9,
    TEXTFIELD_BOXSELECT = 10,
    CONTEXT_MENU_HOVER = 11,
};

enum class TextDirection {
    LTR,
    RTL,
    INHERIT,
    AUTO,
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_COMMON_LAYOUT_CONSTANTS_H
