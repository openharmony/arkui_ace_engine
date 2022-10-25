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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INDEXER_INDEXER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INDEXER_INDEXER_THEME_H

#include "base/i18n/localization.h"
#include "base/utils/string_utils.h"
#include "base/utils/system_properties.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace::NG {
// common data
inline constexpr int32_t INDEXER_INVALID_INDEX = -1;
inline constexpr int32_t INDEXER_ITEM_MAX_COUNT = 29; // [indexer], default max count
inline constexpr uint8_t DEFAULT_OPACITY = 255;
inline constexpr uint8_t ZERO_OPACITY = 0;
inline const std::u16string INDEXER_STR_DOT = StringUtils::Str8ToStr16("•");
inline const std::u16string INDEXER_STR_DOT_EX = StringUtils::Str8ToStr16(".");
inline const std::u16string INDEXER_STR_SHARP = StringUtils::Str8ToStr16("#");

inline constexpr float KEYFRAME_BEGIN = 0.0;
inline constexpr float KEYFRAME_HALF = 0.5;
inline constexpr float KEYFRAME_END = 1.0;
inline constexpr double DEFAULT_OPACITY_IN_PERCENT = 1.0;
inline constexpr double NINETY_OPACITY_IN_PERCENT = 0.9;
inline constexpr double ZERO_OPACITY_IN_PERCENT = 0.0;
inline constexpr int32_t INDEXER_BUBBLE_ANIMATION_DURATION = 3000;
inline constexpr int32_t INDEXER_BUBBLE_MAXSIZE = 6;
// data for list mode
inline constexpr double INDEXER_LIST_ITEM_TEXT_SIZE = 12.0; // list mode, font size (FP)
inline constexpr uint32_t INDEXER_LIST_COLOR = 0x99000000;
inline constexpr uint32_t INDEXER_LIST_ACTIVE_COLOR = 0xFF254FF7;
inline constexpr double INDEXER_DEFAULT_PADDING_X = 10.0;
inline constexpr double INDEXER_DEFAULT_PADDING_Y = 16.0;
inline constexpr double BUBBLE_BOX_SIZE = 56.0;
inline constexpr double BUBBLE_BOX_RADIUS = 12.0;
inline constexpr double BOX_RADIUS = 6.0;
inline constexpr double ZERO_RADIUS = 0.0;
inline constexpr double BUBBLE_FONT_SIZE = 24.0;
inline constexpr double BUBBLE_POSITION_X = -96.0;
inline constexpr double BUBBLE_POSITION_Y = 48.0;
inline constexpr uint32_t BUBBLE_FONT_COLOR = 0xFF254FF7;
inline constexpr uint32_t BUBBLE_BG_COLOR = 0xFFF1F3F5;
inline constexpr double INDEXER_ITEM_SIZE = 24.0;      // circle mode, item size (VP)
inline constexpr double INDEXER_ITEM_TEXT_SIZE = 12.0; // circle, mode font size (VP)
// data for circle mode
inline constexpr int32_t INDEXER_COLLAPSE_ITEM_COUNT = 4;
inline constexpr double INDEXER_CIRCLE_ITEM_SIZE = 24.0;          // circle mode, item size (VP)
inline constexpr double INDEXER_CIRCLE_ITEM_TEXT_SIZE = 13.0;     // circle, mode font size (VP)
inline constexpr double INDEXER_CIRCLE_ITEM_SHADOW_RADIUS = 27.0; // circle mode, shadow radius (VP)
inline constexpr double BUBBLE_BOX_SIZE_CIRCLE = 46.0;
inline constexpr double BUBBLE_FONT_SIZE_CIRCLE = 19.0;
inline constexpr uint32_t INDEXER_ACTIVE_BG_COLOR = 0x1F0A59F7;

enum class AlignStyle {
    LEFT = 0,
    RIGHT,
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INDEXER_INDEXER_THEME_H