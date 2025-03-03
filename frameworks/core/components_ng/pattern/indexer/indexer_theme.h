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
inline constexpr int32_t INDEXER_BUBBLE_EXIT_DURATION = 400;
inline constexpr int32_t INDEXER_BUBBLE_ENTER_DURATION = 200;
inline constexpr int32_t INDEXER_HOVER_IN_DURATION = 250;
inline constexpr int32_t INDEXER_HOVER_OUT_DURATION = 250;
inline constexpr int32_t INDEXER_PRESS_IN_DURATION = 100;
inline constexpr int32_t INDEXER_PRESS_OUT_DURATION = 100;
inline constexpr int32_t INDEXER_SELECT_DURATION = 100;
inline constexpr int32_t INDEXER_BUBBLE_WAIT_DURATION = 2000;
inline constexpr int32_t INDEXER_BUBBLE_APPEAR_DURATION = 2600;
inline constexpr uint32_t INDEXER_BUBBLE_MAXSIZE = 5;
inline constexpr uint32_t INDEXER_BUBBLE_MAXSIZE_COLLAPSED = 4; // 3 items + 1 letter
inline constexpr uint32_t INDEXER_POPUP_SHADOW_BG_COLOR = 0x4d182431;
inline constexpr float INDEXER_POPUP_SHADOW_RADIUS = 50.0f;
inline constexpr float INDEXER_POPUP_SHADOW_OFFSET_Y = 10.0f;
inline constexpr int32_t INDEXER_NINE_CHARACTERS_CHECK = 9;
inline constexpr int32_t INDEXER_THIRTEEN_CHARACTERS_CHECK = 13;
// data for list mode
inline constexpr double INDEXER_LIST_ITEM_TEXT_SIZE = 12.0; // list mode, font size (FP)
inline constexpr uint32_t INDEXER_LIST_COLOR = 0x99000000;
inline constexpr uint32_t INDEXER_LIST_ACTIVE_COLOR = 0xFF254FF7;
inline constexpr double INDEXER_DEFAULT_PADDING_X = 10.0;
inline constexpr double INDEXER_DEFAULT_PADDING_Y = 16.0;
inline constexpr uint32_t POPUP_LISTITEM_CLICKED_BG = 0x1A000000;
inline constexpr double BUBBLE_BOX_SIZE = 56.0;
inline constexpr double BUBBLE_BOX_RADIUS = 16.0;
inline constexpr double BOX_RADIUS = 6.0;
inline constexpr double ZERO_RADIUS = 0.0;
inline constexpr double POPUP_ITEM_DEFAULT_RADIUS = 24.0;
inline constexpr double ITEM_DEFAULT_RADIUS = 8.0;
inline constexpr double RADIUS_OFFSET = 4.0;
inline constexpr double BUBBLE_FONT_SIZE = 24.0;
inline constexpr double BUBBLE_POSITION_X = 60.0;
inline constexpr double BUBBLE_POSITION_Y = 48.0;
inline constexpr uint32_t BUBBLE_FONT_COLOR = 0xFF254FF7;
inline constexpr uint32_t BUBBLE_BG_COLOR = 0xFFF1F3F5;
inline constexpr double INDEXER_ITEM_SIZE = 16.0;      // circle mode, item size (VP)
inline constexpr double INDEXER_ITEM_TEXT_SIZE = 12.0; // circle, mode font size (VP)
inline constexpr float INDEXER_LIST_DIVIDER = 1.0;
inline constexpr float INDEXER_BUBBLE_INVALID_SPACE = -1.0f;
inline constexpr Dimension DEFAULT_ITEM_SIZE = 16.0_vp;
// data for circle mode
inline constexpr int32_t INDEXER_COLLAPSE_ITEM_COUNT = 4;
inline constexpr double INDEXER_CIRCLE_ITEM_SIZE = 24.0;          // circle mode, item size (VP)
inline constexpr double INDEXER_CIRCLE_ITEM_TEXT_SIZE = 13.0;     // circle, mode font size (VP)
inline constexpr double INDEXER_CIRCLE_ITEM_SHADOW_RADIUS = 27.0; // circle mode, shadow radius (VP)
inline constexpr double BUBBLE_BOX_SIZE_CIRCLE = 46.0;
inline constexpr double BUBBLE_FONT_SIZE_CIRCLE = 19.0;
inline constexpr uint32_t INDEXER_ACTIVE_BG_COLOR = 0x1F0A59F7;
inline constexpr float TEXTVIEW_MIN_SIZE = 42.0f;
inline constexpr float INDEXER_PADDING_TOP = 2.0f;
inline constexpr float INDEXER_PADDING_LEFT = 4.0f;
inline constexpr double BUBBLE_RADIUS = 28.0;
inline constexpr double BUBBLE_ITEM_SIZE = 48.0;
inline constexpr double BUBBLE_ITEM_RADIUS = 24.0;
inline constexpr double INDEXER_DEFAULT_RADIUS = 12.0;
inline constexpr double INDEXER_ITEM_DEFAULT_RADIUS = 8.0;
inline constexpr float BUBBLE_DIVIDER_SIZE = 4.0f;
inline constexpr float BUBBLE_COLUMN_MAX_SIZE = 342.0f;
inline constexpr float BUBBLE_COLLAPSE_COLUMN_MAX_SIZE = 186.0f;
inline constexpr float BUBBLE_LIST_MAX_SIZE = 282.0f;
inline constexpr float BUBBLE_COLLAPSE_LIST_MAX_SIZE = 178.0f;
inline constexpr double GRADIENT_COVER_HEIGHT = 16.0;
inline constexpr uint32_t INDEXER_BUBBLE_MAXSIZE_COLLAPSED_API_TWELVE = 3; // 2 items + 1 letter
inline constexpr float INDEXER_PADDING_TOP_API_TWELVE = 4.0f;
inline constexpr uint32_t POPUP_TITLE_BG_COLOR_SINGLE = 0x00ffffff;
inline constexpr float INDEXER_ZERO_WIDTH = 0.0f;
inline constexpr int32_t INDEXER_COLLAPSE_WAIT_DURATION = 1;

inline constexpr int32_t ARC_INDEXER_ITEM_MAX_COUNT = 29; // [indexer], default max count
inline const std::u16string ARC_INDEXER_STR_SHARP = StringUtils::Str8ToStr16("#");
inline const std::u16string ARC_INDEXER_STR_EXPANDED = StringUtils::Str8ToStr16(">");
inline const std::u16string ARC_INDEXER_STR_COLLAPSED = StringUtils::Str8ToStr16("<");

inline constexpr float ARC_INDEXER_SIZE = 233.0;
inline constexpr int32_t ARC_INDEXER_EXPANDED_DURATION = 470;
inline constexpr int32_t ARC_INDEXER_COLLAPED_DURATION = 470;
inline constexpr int32_t ARC_INDEXER_BUBBLE_EXIT_DURATION = 400;
inline constexpr int32_t ARC_INDEXER_BUBBLE_ENTER_DURATION = 200;
inline constexpr int32_t ARC_INDEXER_PRESS_IN_DURATION = 100;
inline constexpr int32_t ARC_INDEXER_PRESS_OUT_DURATION = 100;
inline constexpr int32_t ARC_INDEXER_BUBBLE_WAIT_DURATION = 2000;
inline constexpr int32_t ARC_INDEXER_BUBBLE_MAX_TEXT_LINE = 2;

inline constexpr double ARC_BUBBLE_BOX_SIZE = 46.0;
inline constexpr double ARC_BUBBLE_BOX_RADIUS = 23.0;
inline constexpr double ARC_BUBBLE_POSITION_Y = 44.0;
inline constexpr double ARC_INDEXER_ITEM_SIZE = 24.0;      // circle mode, item size (VP)
inline constexpr float ARC_INDEXER_ITEM_TEXT_SIZE = 13.0f; // circle, mode font size (FP)
inline constexpr float ARC_INDEXER_POPUP_TEXT_SIZE = 19.0f; // circle, mode popup font size (FP)

inline constexpr int32_t ARC_INDEXER_COLLAPSE_ITEM_COUNT = 4;
inline constexpr float FULL_CIRCLE_ANGLE = 360.0;
inline constexpr float HALF = 0.5f;
inline constexpr double DOUBLE = 2.0;
inline constexpr float HALF_CIRCLE_ANGLE = 180.0;
inline constexpr uint32_t ARC_INDEXER_STR_DOT_COLOR = 0xA9FFFFFF;
inline constexpr uint32_t ARC_INDEXER_SELECTED_BG_COLOR = 0xFF1F71FF;
inline constexpr uint32_t ARC_POPUP_BG_COLOR = 0xD8404040;
inline constexpr float ARC_INDEXER_PADDING_LEFT = 4.0f;
inline constexpr double ARC_INDEXER_DEFAULT_RADIUS = 12.0;
inline constexpr int32_t ARC_INDEXER_COLLAPSE_WAIT_DURATION = 1;

enum class AlignStyle {
    LEFT = 0,
    RIGHT,
    START,
    END,
};

enum class ArcIndexerBarState {
    INVALID,
    COLLAPSED,
    EXPANDED
};

enum class ArcIndexerCollapsingMode {
    INVALID,
    NONE, // all array should be displayed
    FOUR, // 4 + 1 collapsing mode
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INDEXER_INDEXER_THEME_H
