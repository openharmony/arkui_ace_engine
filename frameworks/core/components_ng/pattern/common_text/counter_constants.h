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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_CONSTANTS_H

#include <cstdint>

#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG {
// ===== counter / border shared constants (RichEditor & TextField) =====
constexpr int32_t COUNTER_DEFAULT_MODE = -1;
constexpr int32_t COUNTER_ILLEGAL_VALUE = 0;
constexpr Dimension OVER_COUNT_BORDER_WIDTH = 1.0_vp;
constexpr float COUNTER_BORDER_OFFSET = 2.0f;
constexpr double COUNTER_VELOCITY = -1000.0;
constexpr double COUNTER_MASS = 1.0;
constexpr double COUNTER_STIFFNESS = 428.0;
constexpr double COUNTER_DAMPING = 10.0;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_CONSTANTS_H
