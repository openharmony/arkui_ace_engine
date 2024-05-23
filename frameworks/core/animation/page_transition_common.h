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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PAGE_TRANSITION_PAGE_TRANSITION_COMMON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PAGE_TRANSITION_PAGE_TRANSITION_COMMON_H

#include "frameworks/base/memory/referenced.h"

namespace OHOS::Ace {

class Curve;

enum class PageTransitionType {
    ENTER,      // current page enter not specify route type.
    EXIT,       // current page exit not specify route type.
    ENTER_POP,  // top page pop from route stack, current page on top.
    ENTER_PUSH, // current page push into route stack.
    EXIT_POP,   // current page pop from route stack.
    EXIT_PUSH,  // another page push info route stack.
    NONE,
};

enum class RouteType {
    NONE,
    PUSH,
    POP,
};

enum class SlideEffect {
    NONE,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    START,
    END,
};

struct PageTransitionOption {
    RouteType routeType = RouteType::NONE;
    int32_t duration = 0;
    int32_t delay = 0;
    RefPtr<Curve> curve;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PAGE_TRANSITION_PAGE_TRANSITION_COMMON_H