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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_SCROLLABLE_PROPERTIES_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_SCROLLABLE_PROPERTIES_H

namespace OHOS::Ace {

enum class ScrollSource {
    DRAG = 0,           // constexpr int32_t SCROLL_FROM_UPDATE = 1;
    FLING,              // constexpr int32_t SCROLL_FROM_ANIMATION = 2;
    EDGE_EFFECT,        // constexpr int32_t SCROLL_FROM_ANIMATION_SPRING = 4;
    OTHER_USER_INPUT,   // constexpr int32_t SCROLL_FROM_AXIS = 11;
    SCROLL_BAR,         // constexpr int32_t SCROLL_FROM_BAR = 6;
    SCROLL_BAR_FLING,   // constexpr int32_t SCROLL_FROM_BAR_FLING = 13;
    SCROLLER,           // constexpr int32_t SCROLL_FROM_JUMP = 3;
    SCROLLER_ANIMATION, // constexpr int32_t SCROLL_FROM_ANIMATION_CONTROLLER = 12;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_SCROLLABLE_PROPERTIES_H