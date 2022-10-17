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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_THEME_H

#include <cstdint>

#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace::NG {

const Dimension ROUND_RADIUS_PHONE = 12.0_vp;
constexpr float DEFAULT_STROKE_WIDTH = 1.0f;
constexpr uint32_t DIVIDER_COLOR = 0x33000000;

constexpr uint32_t DEFAULT_BACKGROUND_COLOR = 0xFFFFFFF;
constexpr uint32_t DEFAULT_HOVER_BACKGROUND_COLOR = 0x0C000000;

constexpr Dimension VERTICAL_INTERVAL_PHONE = 14.4_vp;
constexpr Dimension HORIZONTAL_INTERVAL_PHONE = 12.0_vp;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_THEME_H