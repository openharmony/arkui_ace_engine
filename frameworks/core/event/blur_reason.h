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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_BLUR_REASON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_BLUR_REASON_H

#include <cstdint>

namespace OHOS::Ace {

enum class BlurReason : int32_t {
    FOCUS_SWITCH = 0,
    WINDOW_BLUR = 1,
    FRAME_DESTROY = 2,
    VIEW_SWITCH = 3,
    CLEAR_FOCUS = 4,
    BACK_TO_TABSTOP = 5,
};

enum class FocusReason : int32_t {
    DEFAULT = 0,
    FOCUS_TRAVEL = 1,
    FOCUS_TOUCH = 2,
    WINDOW_FOCUS = 3,
    VIEW_SWITCH = 4,
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_BLUR_REASON_H
