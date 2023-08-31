/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GAUGE_GAUGE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GAUGE_GAUGE_THEME_H

#include "base/i18n/localization.h"

namespace OHOS::Ace::NG {
inline constexpr float DEFAULT_START_DEGREE = 0.0f;
inline constexpr float DEFAULT_END_DEGREE = 360.0f;
inline constexpr float EDGE = 15.0f;
inline constexpr float HEIGHT_OFFSET = 5.0f;
inline constexpr float INDICATOR_STROKE_WIDTH = 5.0f;
inline constexpr int8_t UNSELECT_ALPHA = 125;
inline constexpr float DEFAULT_MIN_VALUE = 0.0f;
inline constexpr float DEFAULT_MAX_VALUE = 100.0f;
inline constexpr float MONOCHROME_CIRCULAR_BACKGROUND_COLOR_OPACITY = 0.2f;
inline constexpr float CALC_INDICATOR_POINT_TOP_LEFT = 0.02f;
inline constexpr float CALC_INDICATOR_POINT_BOTTOM_LEFT_X = 0.11f;
inline constexpr float CALC_INDICATOR_POINT_BOTTOM_LEFT_Y = 0.156f;
inline constexpr float CALC_INDICATOR_CONTROL_POINT_LEFT_X = 0.115f;
inline constexpr float CALC_INDICATOR_CONTROL_POINT_LEFT_Y = 0.178f;
inline constexpr float CALC_INDICATOR_POINT_RIGHT_X = 0.096f;
inline constexpr float CALC_INDICATOR_POINT_RIGHT_Y = 0.19f;
inline constexpr float CALC_INDICATOR_CONTROL_POINT_RIGHT_X = 0.182f;
inline constexpr float CALC_INDICATOR_CONTROL_POINT_RIGHT_Y = 0.002f;
inline constexpr float INDICATOR_BORDER_WIDTH_RATIO = 0.03f;
inline constexpr float DESCRIPTION_NODE_WIDTH_RATIO = 0.4444f;
inline constexpr float DESCRIPTION_NODE_HEIGHT_RATIO = 0.254f;
inline constexpr float DESCRIPTION_IMAGE_NODE_WIDTH_RATIO = 0.286f;
inline constexpr float DESCRIPTION_IMAGE_NODE_HEIGHT_RATIO = 0.286f;
inline constexpr float DESCRIPTION_X = 0.2778f;
inline constexpr float DESCRIPTION_Y = 0.746f;
inline constexpr float DESCRIPTION_IMAGE_X = 0.357f;
inline constexpr float DESCRIPTION_IMAGE_Y = 0.714f;

inline constexpr float LIMIT_VALUE_MIN_OR_MAX_WIDTH_RATIO = 0.247f;
inline constexpr float LIMIT_VALUE_MIN_OR_MAX_HEIGHT_RATIO = 0.2222f;
inline constexpr float LIMIT_VALUE_MIN_X = 0.221f;
inline constexpr float LIMIT_VALUE_Y = 0.722f;
inline constexpr float LIMIT_VALUE_MAX_X = 0.532f;

inline constexpr float DEFAULT_GAUGE_SHADOW_RADIUS = 5.0f;
inline constexpr float DEFAULT_GAUGE_SHADOW_OFFSETX = 5.0f;
inline constexpr float DEFAULT_GAUGE_SHADOW_OFFSETY = 5.0f;
inline constexpr Dimension INDICATOR_DISTANCE_TO_TOP = 8.0_vp;
inline constexpr Dimension LIMIT_VALUE_MAX_FONTSIZE = 40.0_vp;
inline constexpr Dimension LIMIT_VALUE_MIN_FONTSIZE = 10.0_vp;
inline constexpr int32_t COLORS_MAX_COUNT = 9;
inline constexpr float RADIUS_TO_DIAMETER = 2.0f;
inline constexpr float INDICATOR_WIDTH_RADIO = 0.135f;
inline constexpr float INDICATOR_HEIGHT_RADIO = 0.095f;
inline constexpr Color INDICATOR_COLOR(0xFF182431);
inline constexpr Color INDICATOR_BORDER_COLOR(0xFFFFFFFF);
inline const std::vector<Color> GAUGE_DEFAULT_COLOR { Color(0xFF64BB5C), Color(0xFFF7CE00), Color(0xFFE84026) };
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GAUGE_GAUGE_THEME_H