/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_ATTRIBUTES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_ATTRIBUTES_H

#include <string>

namespace OHOS::Ace {

// theme attributes
extern const char THEME_ATTR_BG_COLOR[];
extern const char THEME_ATTR_HOVER_COLOR[];

// component patterns
extern const char THEME_PATTERN_BUTTON[];
extern const char THEME_PATTERN_CHECKBOX[];
extern const char THEME_PATTERN_DATA_PANEL[];
extern const char THEME_PATTERN_RADIO[];
extern const char THEME_PATTERN_SWIPER[];
extern const char THEME_PATTERN_SWITCH[];
extern const char THEME_PATTERN_TOOLBAR[];
extern const char THEME_PATTERN_TOGGLE[];
extern const char THEME_PATTERN_TOAST[];
extern const char THEME_PATTERN_DIALOG[];
extern const char THEME_PATTERN_DRAG_BAR[];
extern const char THEME_PATTERN_CLOSE_ICON[];
extern const char THEME_PATTERN_SEMI_MODAL[];
extern const char THEME_PATTERN_BADGE[];
extern const char THEME_PATTERN_CALENDAR[];
extern const char THEME_PATTERN_CAMERA[];
extern const char THEME_PATTERN_CARD[];
extern const char THEME_PATTERN_CLOCK[];
extern const char THEME_PATTERN_COUNTER[];
extern const char THEME_PATTERN_DIVIDER[];
extern const char THEME_PATTERN_FOCUS_ANIMATION[];
extern const char THEME_PATTERN_GRID[];
extern const char THEME_PATTERN_HYPERLINK[];
extern const char THEME_PATTERN_ICON[];
extern const char THEME_PATTERN_IMAGE[];
extern const char THEME_PATTERN_LIST[];
extern const char THEME_PATTERN_LIST_ITEM[];
extern const char THEME_PATTERN_ARC_LIST[];
extern const char THEME_PATTERN_ARC_LIST_ITEM[];
extern const char THEME_PATTERN_MARQUEE[];
extern const char THEME_PATTERN_NAVIGATION_BAR[];
extern const char THEME_PATTERN_PICKER[];
extern const char THEME_PATTERN_PIECE[];
extern const char THEME_PATTERN_POPUP[];
extern const char THEME_PATTERN_PROGRESS[];
extern const char THEME_PATTERN_QRCODE[];
extern const char THEME_PATTERN_RATING[];
extern const char THEME_PATTERN_REFRESH[];
extern const char THEME_PATTERN_SCROLL_BAR[];
extern const char THEME_PATTERN_SEARCH[];
extern const char THEME_PATTERN_STEPPER[];
extern const char THEME_PATTERN_TAB[];
extern const char THEME_PATTERN_SELECT[];
extern const char THEME_PATTERN_SLIDER[];
extern const char THEME_PATTERN_TEXT[];
extern const char THEME_PATTERN_TEXTFIELD[];
extern const char THEME_PATTERN_RICH_EDITOR[];
extern const char THEME_PATTERN_TEXT_OVERLAY[];
extern const char THEME_PATTERN_VIDEO[];
extern const char THEME_PATTERN_INDEXER[];
extern const char THEME_PATTERN_APP_BAR[];
extern const char THEME_PATTERN_ADVANCED_PATTERN[];
extern const char THEME_PATTERN_SECURITY_COMPONENT[];
extern const char THEME_PATTERN_FORM[];
extern const char THEME_PATTERN_SIDE_BAR[];
extern const char THEME_PATTERN_PATTERN_LOCK[];
extern const char THEME_PATTERN_GAUGE[];
extern const char THEME_PATTERN_SHEET[];
extern const char THEME_BLUR_STYLE_COMMON[];
extern const char THEME_PATTERN_SHADOW[];
extern const char THEME_PATTERN_CONTAINER_MODAL[];
extern const char THEME_PATTERN_AGING_ADAPATION_DIALOG[];
extern const char THEME_PATTERN_SCROLLABLE[];
extern const char THEME_PATTERN_APP[];
extern const char THEME_PATTERN_LINEAR_INDICATOR[];
 

// pattern general attributes
extern const char PATTERN_FG_COLOR[];
extern const char PATTERN_BG_COLOR[];
extern const char PATTERN_UNDERLINE_ACTIVED_COLOR[];
extern const char PATTERN_UNDERLINE_TYPING_COLOR[];
extern const char PATTERN_BG_COLOR_HOVERED[];
extern const char PATTERN_BG_COLOR_CLICKED[];
extern const char PATTERN_BG_COLOR_PRESSED[];
extern const char PATTERN_BG_COLOR_SELECTED[];
extern const char PATTERN_BG_COLOR_FOCUSED[];
extern const char PATTERN_BG_COLOR_DISABLED_ALPHA[];
extern const char PATTERN_BG_COLOR_ALPHA[];
extern const char PATTERN_TEXT_COLOR[];
extern const char PATTERN_TEXT_COLOR_BLUR[];
extern const char PATTERN_TEXT_COLOR_ALPHA[];
extern const char PATTERN_TEXT_COLOR_FOCUSED[];
extern const char PATTERN_TEXT_COLOR_SELECTED[];
extern const char PATTERN_TEXT_COLOR_DISABLED[];
extern const char PATTERN_DISABLED_TEXT_COLOR[];
extern const char PATTERN_TEXT_SIZE[];
extern const char PATTERN_WIDTH[];
extern const char PATTERN_HEIGHT[];

// pattern attributes for calendar
extern const char CALENDAR_WEEK_COLOR[];
extern const char CALENDAR_DAY_COLOR[];
extern const char CALENDAR_LUNAR_COLOR[];
extern const char CALENDAR_WEEKEND_DAY_COLOR[];
extern const char CALENDAR_WEEKEND_LUNAR_COLOR[];
extern const char CALENDAR_TODAY_DAY_FOCUS_COLOR[];
extern const char CALENDAR_TODAY_LUNAR_FOCUS_COLOR[];
extern const char CALENDAR_TODAY_DAY_UNFOCUS_COLOR[];
extern const char CALENDAR_TODAY_LUNAR_UNFOCUS_COLOR[];
extern const char CALENDAR_WORK_MARK_COLOR[];
extern const char CALENDAR_OFF_MARK_COLOR[];
extern const char CALENDAR_NONCURRENT_MONTH_WORK_MARK_COLOR[];
extern const char CALENDAR_NONCURRENT_MONTH_OFF_MARK_COLOR[];
extern const char CALENDAR_NONCURRENT_MONTH_DAY_COLOR[];
extern const char CALENDAR_NONCURRENT_MONTH_LUNAR_COLOR[];
extern const char CALENDAR_FOCUS_AREA_BACKGROUND_COLOR[];
extern const char CALENDAR_BLUR_AREA_BACKGROUND_COLOR[];

// pattern attributes for checkable
extern const char RADIO_WIDTH[];
extern const char SWITCH_WIDTH[];
extern const char SWITCH_HEIGHT[];
extern const char SWITCH_SHADOW_WIDTH[];
extern const char SWITCH_HORIZONTAL_PADDING[];
extern const char SWITCH_VERTICAL_PADDING[];
extern const char RADIO_PADDING[];

// pattern attributes for data panel
extern const char DATA_PANEL_COLOR_1_START[];
extern const char DATA_PANEL_COLOR_2_START[];
extern const char DATA_PANEL_COLOR_3_START[];
extern const char DATA_PANEL_COLOR_4_START[];
extern const char DATA_PANEL_COLOR_5_START[];
extern const char DATA_PANEL_COLOR_6_START[];
extern const char DATA_PANEL_COLOR_7_START[];
extern const char DATA_PANEL_COLOR_8_START[];
extern const char DATA_PANEL_COLOR_9_START[];
extern const char DATA_PANEL_COLOR_1_END[];
extern const char DATA_PANEL_COLOR_2_END[];
extern const char DATA_PANEL_COLOR_3_END[];
extern const char DATA_PANEL_COLOR_4_END[];
extern const char DATA_PANEL_COLOR_5_END[];
extern const char DATA_PANEL_COLOR_6_END[];
extern const char DATA_PANEL_COLOR_7_END[];
extern const char DATA_PANEL_COLOR_8_END[];
extern const char DATA_PANEL_COLOR_9_END[];
extern const char DATA_PANEL_LOADING_COLOR_START[];
extern const char DATA_PANEL_LOADING_COLOR_END[];
extern const char DATA_PANEL_PROGRESS_COLOR_START[];
extern const char DATA_PANEL_PROGRESS_COLOR_END[];
extern const char DATA_PANEL_TRACK_SHADOW_RADIU[];

// pattern attributes for dialog
extern const char DIALOG_CONTENT_TOP_PADDING[];
extern const char DIALOG_TITLE_TOP_PADDING[];
extern const char DIALOG_BUTTON_HEIGHT[];
extern const char DIALOG_TITLE_MAX_LINES[];
extern const char DIALOG_COMMON_BUTTON_TEXT_COLOR[];
extern const char DIALOG_MIN_BUTTON_TEXT_SIZE[];
extern const char DIALOG_MAX_BUTTON_WIDTH[];
extern const char DIALOG_MIN_BUTTON_WIDTH[];
extern const char DIALOG_ACTIONS_TOP_PADDING[];
extern const char DIALOG_MASK_COLOR_END[];
extern const char DIALOG_DIVIDER_LENGTH[];
extern const char DIALOG_DIVIDER_BETWEEN_BUTTON_WIDTH[];

// pattern attributes for drag bar
extern const char DRAG_BAR_COLOR[];

// pattern attributes for close icon
extern const char CLOSE_ICON_WIDTH[];
extern const char CLOSE_ICON_Height[];
extern const char CLOSE_ICON_MARGIN_TOP[];
extern const char CLOSE_ICON_MARGIN_RIGHT[];
extern const char CLOSE_ICON_RADIUS[];

// pattern attributes for popup
extern const char POPUP_BORDER_RADIUS[];
extern const char POPUP_HORIZONTAL_PADDING[];
extern const char POPUP_VERTICAL_PADDING[];
extern const char POPUP_BUTTON_TEXT_FONT_SIZE[];

// pattern attributes for badge
extern const char BADGE_BORDER_COLOR[];
extern const char BADGE_BORDER_WIDTH[];
extern const char BADGE_AGE_FONT_SIZE[];
extern const char BADGE_AGE_SIZE[];
extern const char BADGE_AFE_ADD_PADDING[];
extern const char LITTLE_BADGE_SIZE[];
extern const char NUMERICAL_BADGE_PADDING_SIZE[];
// swiper attributes
extern const char INDICATOR_TEXT_FONT_SIZE[];
extern const char INDICATOR_TEXT_FONT_COLOR[];

// textinput attributes
extern const char ERROR_TEXT_UNDERLINE_COLOR[];
extern const char UNDERLINE_COLOR[];
extern const char UNDERLINE_TEXT_COLOR[];
extern const char UNDERLINE_FONT_SIZE[];
extern const char BORDER_RADIUS_SIZE[];
// swiper attributes for arrow
extern const char ARROW_COLOR_BOARDCOLOR_HOVER[];
extern const char ARROW_COLOR_BOARDCOLOR_CLICK[];
extern const char ARROW_COLOR_PRIMARY[];
extern const char ARROW_COLOR_PRIMARY_CONTRARY[];
extern const char ARROW_DISABLED_ALPHA[];
extern const char ARROW_HORIZONTAL_MARGIN[];
extern const char ARROW_VERTICAL_MARGIN[];
extern const char ARROW_COLOR_COMPONENT_NORMAL[];

// pattern attributes for textfield
extern const char PATTERN_FOCUS_BRODER_COLOR[];
extern const char ERROR_UNDERLINE_COLOR[];
extern const char ERROR_UNDERLINE_TEXT_COLOR[];
extern const char ERROR_UNDERLINE_TEXT_SIZE[];
extern const char ERROR_PASSWORD_CONTENT_COLOR[];
extern const char ERROR_PASSWORD_INPUT_COLOR[];
extern const char ERROR_PASSWORD_BORDER_COLOR[];
extern const char ERROR_PASSWORD_TEXT_COLOR[];
extern const char OVER_COUNT_TEXT_COLOR[];
extern const char OVER_COUNT_TEXT_FONT_SIZE[];
extern const char OVER_COUNT_BORDER_COLOR[];
extern const char ERROR_PASSWORD_BORDER_ALPHA[];
extern const char OVER_COUNT_BORDER_COLOR_ALPHA[];
extern const char UNDERLINE_COLOR_ALPHA[];
extern const char INLINE_TEXT_COLOR[];
extern const char INLINE_RADIUS_SIZE[];
extern const char INLINE_BG_COLOR[];
extern const char INLINE_BORDER_COLOR[];
extern const char DISABLE_UNDERLINE_ALPHA[];
extern const char DEFAULT_COUNTER_COLOR[];
extern const char OVER_COUNTER_COLOR[];
extern const char PREVIEW_UNDERLINE_COLOR[];
extern const char PREVIEW_BOARD_COLOR[];

// linear split attributes
extern const char LINEAR_SPLIT_CHILD_MIN_SIZE[];

// stepper attributes
extern const char STEPPER_FOCUS_COLOR[];
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_THEME_ATTRIBUTES_H
