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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H

#include <cstdint>

#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace::NG {

constexpr Dimension OUT_PADDING = 4.0_vp;
constexpr float OPTION_MIN_WIDTH = 204.0f;

constexpr Dimension GRADIENT_HEIGHT = Dimension(50, DimensionUnit::VP);
constexpr uint8_t GRADIENT_END_GRADIENT = 255;
constexpr uint32_t DEFAULT_BACKGROUND_COLOR = 0xFFFFFFF;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H