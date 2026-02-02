/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_TYPE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_TYPE_H

#include <cstdint>

namespace OHOS::Ace::NG {

enum class FocusType : int32_t {
    DISABLE = 0,
    NODE = 1,
    SCOPE = 2,
};

enum class FocusStyleType : int32_t {
    NONE = -1,
    INNER_BORDER = 0,
    OUTER_BORDER = 1,
    CUSTOM_BORDER = 2,
    CUSTOM_REGION = 3,
    FORCE_BORDER = 4,
    FORCE_NONE = 5,
};

enum class FocusNodeType : int32_t {
    DEFAULT = 0,
    GROUP_DEFAULT = 1,
};
enum class ScopeType : int32_t {
    OTHERS = 0,
    FLEX = 1,
    PROJECT_AREA = 2,
};
enum class FocusStep : int32_t {
    NONE = 0x0,
    LEFT = 0x1,
    UP = 0x2,
    RIGHT = 0x11,
    DOWN = 0x12,
    LEFT_END = 0x3,
    UP_END = 0x4,
    RIGHT_END = 0X13,
    DOWN_END = 0x14,
    SHIFT_TAB = 0x5,
    TAB = 0x15,
};

} // namespace OHOS::Ace::NG

#endif