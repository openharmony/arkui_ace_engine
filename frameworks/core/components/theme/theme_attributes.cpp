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

#include "core/components/theme/theme_attributes.h"

namespace OHOS::Ace {

// theme attributes
const char THEME_ATTR_BG_COLOR[] = "bg_color";
const char THEME_ATTR_HOVER_COLOR[] = "hover_color";

// component patterns
const char THEME_PATTERN_BUTTON[] = "button_pattern";
const char THEME_PATTERN_CHECKBOX[] = "checkbox_pattern";
const char THEME_PATTERN_DATA_PANEL[] = "data_panel_pattern";
const char THEME_PATTERN_RADIO[] = "radio_pattern";
const char THEME_PATTERN_SWIPER[] = "swiper_pattern";
const char THEME_PATTERN_SWITCH[] = "switch_pattern";
const char THEME_PATTERN_TOOLBAR[] = "toolbar_pattern";
const char THEME_PATTERN_TOGGLE[] = "toggle_pattern";
const char THEME_PATTERN_TOAST[] = "toast_pattern";
const char THEME_PATTERN_DIALOG[] = "dialog_pattern";
const char THEME_PATTERN_DRAG_BAR[] = "drag_bar_pattern";
const char THEME_PATTERN_CLOSE_ICON[] = "close_icon_pattern";
const char THEME_PATTERN_SEMI_MODAL[] = "semi_modal_pattern";
const char THEME_PATTERN_BADGE[] = "badge_pattern";
const char THEME_PATTERN_CALENDAR[] = "calendar_pattern";
const char THEME_PATTERN_CAMERA[] = "camera_pattern";
const char THEME_PATTERN_CARD[] = "card_pattern";
const char THEME_PATTERN_CLOCK[] = "clock_pattern";
const char THEME_PATTERN_COUNTER[] = "counter_pattern";
const char THEME_PATTERN_DIVIDER[] = "divider_pattern";
const char THEME_PATTERN_FOCUS_ANIMATION[] = "focus_animation_pattern";
const char THEME_PATTERN_GRID[] = "grid_pattern";
const char THEME_PATTERN_HYPERLINK[] = "hyperlink_pattern";
const char THEME_PATTERN_ICON[] = "icon_pattern";
const char THEME_PATTERN_IMAGE[] = "image_pattern";
const char THEME_PATTERN_LIST[] = "list_pattern";
const char THEME_PATTERN_LIST_ITEM[] = "list_item_pattern";
const char THEME_PATTERN_MARQUEE[] = "marquee_pattern";
const char THEME_PATTERN_NAVIGATION_BAR[] = "navigation_bar_pattern";
const char THEME_PATTERN_PICKER[] = "picker_pattern";
const char THEME_PATTERN_PIECE[] = "piece_pattern";
const char THEME_PATTERN_POPUP[] = "popup_pattern";
const char THEME_PATTERN_PROGRESS[] = "progress_pattern";
const char THEME_PATTERN_QRCODE[] = "qrcode_pattern";
const char THEME_PATTERN_RATING[] = "rating_pattern";
const char THEME_PATTERN_REFRESH[] = "refresh_pattern";
const char THEME_PATTERN_SCROLL_BAR[] = "scroll_bar_pattern";
const char THEME_PATTERN_SEARCH[] = "search_pattern";
const char THEME_PATTERN_STEPPER[] = "stepper_pattern";
const char THEME_PATTERN_TAB[] = "tab_pattern";
const char THEME_PATTERN_SELECT[] = "select_pattern";
const char THEME_PATTERN_SLIDER[] = "slider_pattern";
const char THEME_PATTERN_TEXT[] = "text_pattern";
const char THEME_PATTERN_TEXTFIELD[] = "textfield_pattern";
const char THEME_PATTERN_RICH_EDITOR[] = "rich_editor_pattern";
const char THEME_PATTERN_TEXT_OVERLAY[] = "text_overlay_pattern";
const char THEME_PATTERN_VIDEO[] = "video_pattern";
const char THEME_PATTERN_INDEXER[] = "indexer_pattern";
const char THEME_PATTERN_APP_BAR[] = "app_bar_pattern";
const char THEME_PATTERN_ADVANCED_PATTERN[] = "advanced_pattern";
const char THEME_PATTERN_SECURITY_COMPONENT[] = "security_component_pattern";
const char THEME_PATTERN_FORM[] = "form_pattern";
const char THEME_PATTERN_SIDE_BAR[] = "side_bar_pattern";
const char THEME_PATTERN_PATTERN_LOCK[] = "pattern_lock_pattern";
const char THEME_PATTERN_GAUGE[] = "gauge_pattern";
const char THEME_PATTERN_SHEET[] = "sheet_pattern";
const char THEME_PATTERN_AGING_ADAPATION_DIALOG[] = "aging_adapation_dialog_pattern";
const char THEME_PATTERN_LINEAR_INDICATOR[] = "linear_indicator_pattern";

const char THEME_BLUR_STYLE_COMMON[] = "blur_style_common";
const char THEME_PATTERN_SHADOW[] = "shadow_pattern";
const char THEME_PATTERN_CONTAINER_MODAL[] = "container_modal_pattern";
const char THEME_PATTERN_SCROLLABLE[] = "scrollable_pattern";

// pattern general attributes
const char PATTERN_FG_COLOR[] = "fg_color";
const char PATTERN_BG_COLOR[] = "bg_color";
const char PATTERN_UNDERLINE_ACTIVED_COLOR[] = "underline_actived_color";
const char PATTERN_UNDERLINE_TYPING_COLOR[] = "underline_typing_color";
const char PATTERN_BG_COLOR_HOVERED[] = "bg_color_hovered";
const char PATTERN_BG_COLOR_CLICKED[] = "bg_color_clicked";
const char PATTERN_BG_COLOR_PRESSED[] = "bg_color_pressed";
const char PATTERN_BG_COLOR_SELECTED[] = "bg_color_selected";
const char PATTERN_BG_COLOR_FOCUSED[] = "bg_color_focused";
const char PATTERN_BG_COLOR_DISABLED_ALPHA[] = "bg_color_disabled_alpha";
const char PATTERN_BG_COLOR_ALPHA[] = "bg_color_alpha";
const char PATTERN_TEXT_COLOR[] = "text_color";
const char PATTERN_TEXT_COLOR_BLUR[] = "text_color_blur_style";
const char PATTERN_TEXT_COLOR_ALPHA[] = "text_color_alpha";
const char PATTERN_TEXT_COLOR_FOCUSED[] = "text_color_focused";
const char PATTERN_TEXT_COLOR_SELECTED[] = "text_color_selected";
const char PATTERN_TEXT_COLOR_DISABLED[] = "text_color_disabled";
const char PATTERN_DISABLED_TEXT_COLOR[] = "disabled_text_color";
const char PATTERN_TEXT_SIZE[] = "text_font_size";
const char PATTERN_WIDTH[] = "width";
const char PATTERN_HEIGHT[] = "height";

// pattern attributes for checkable
const char SWITCH_WIDTH[] = "switch_width";
const char SWITCH_HEIGHT[] = "switch_height";
const char SWITCH_SHADOW_WIDTH[] = "switch_shadow_width";
const char RADIO_WIDTH[] = "radio_width";
const char SWITCH_HORIZONTAL_PADDING[] = "switch_horizontal_padding";
const char SWITCH_VERTICAL_PADDING[] = "switch_vertical_padding";
const char RADIO_PADDING[] = "radio_padding";

// pattern attributes for calendar
const char CALENDAR_WEEK_COLOR[] = "week_color";
const char CALENDAR_DAY_COLOR[] = "day_color";
const char CALENDAR_LUNAR_COLOR[] = "lunar_color";
const char CALENDAR_WEEKEND_DAY_COLOR[] = "weekend_day_color";
const char CALENDAR_WEEKEND_LUNAR_COLOR[] = "weekend_lunar_color";
const char CALENDAR_TODAY_DAY_FOCUS_COLOR[] = "today_day_focus_color";
const char CALENDAR_TODAY_LUNAR_FOCUS_COLOR[] = "today_lunar_focus_color";
const char CALENDAR_TODAY_DAY_UNFOCUS_COLOR[] = "today_day_unfocus_color";
const char CALENDAR_TODAY_LUNAR_UNFOCUS_COLOR[] = "today_lunar_unfocus_color";
const char CALENDAR_WORK_MARK_COLOR[] = "work_mark_color";
const char CALENDAR_OFF_MARK_COLOR[] = "off_mark_color";
const char CALENDAR_NONCURRENT_MONTH_WORK_MARK_COLOR[] = "non_current_month_work_mark_color";
const char CALENDAR_NONCURRENT_MONTH_OFF_MARK_COLOR[] = "non_current_month_off_mark_color";
const char CALENDAR_NONCURRENT_MONTH_DAY_COLOR[] = "non_current_month_day_color";
const char CALENDAR_NONCURRENT_MONTH_LUNAR_COLOR[] = "non_current_month_lunar_color";
const char CALENDAR_FOCUS_AREA_BACKGROUND_COLOR[] = "focus_area_background_color";
const char CALENDAR_BLUR_AREA_BACKGROUND_COLOR[] = "blur_area_background_color";

// data panel attributes
const char DATA_PANEL_COLOR_1_START[] = "rainbow_fg_color_1_start";
const char DATA_PANEL_COLOR_2_START[] = "rainbow_fg_color_2_start";
const char DATA_PANEL_COLOR_3_START[] = "rainbow_fg_color_3_start";
const char DATA_PANEL_COLOR_4_START[] = "rainbow_fg_color_4_start";
const char DATA_PANEL_COLOR_5_START[] = "rainbow_fg_color_5_start";
const char DATA_PANEL_COLOR_6_START[] = "rainbow_fg_color_6_start";
const char DATA_PANEL_COLOR_7_START[] = "rainbow_fg_color_7_start";
const char DATA_PANEL_COLOR_8_START[] = "rainbow_fg_color_8_start";
const char DATA_PANEL_COLOR_9_START[] = "rainbow_fg_color_9_start";
const char DATA_PANEL_COLOR_1_END[] = "rainbow_fg_color_1_end";
const char DATA_PANEL_COLOR_2_END[] = "rainbow_fg_color_2_end";
const char DATA_PANEL_COLOR_3_END[] = "rainbow_fg_color_3_end";
const char DATA_PANEL_COLOR_4_END[] = "rainbow_fg_color_4_end";
const char DATA_PANEL_COLOR_5_END[] = "rainbow_fg_color_5_end";
const char DATA_PANEL_COLOR_6_END[] = "rainbow_fg_color_6_end";
const char DATA_PANEL_COLOR_7_END[] = "rainbow_fg_color_7_end";
const char DATA_PANEL_COLOR_8_END[] = "rainbow_fg_color_8_end";
const char DATA_PANEL_COLOR_9_END[] = "rainbow_fg_color_9_end";
const char DATA_PANEL_LOADING_COLOR_START[] = "loading_fg_color_start";
const char DATA_PANEL_LOADING_COLOR_END[] = "loading_fg_color_end";
const char DATA_PANEL_PROGRESS_COLOR_START[] = "progress_fg_color_start";
const char DATA_PANEL_PROGRESS_COLOR_END[] = "progress_fg_color_end";
const char DATA_PANEL_TRACK_SHADOW_RADIU[] = "track_shadow_radiu";

// pattern attributes for toggle
const char DIALOG_CONTENT_TOP_PADDING[] = "dialog_content_top_padding";
const char DIALOG_TITLE_TOP_PADDING[] = "dialog_title_top_padding";
const char DIALOG_BUTTON_HEIGHT[] = "dialog_button_height";
const char DIALOG_TITLE_MAX_LINES[] = "dialog_title_max_lines";
const char DIALOG_COMMON_BUTTON_TEXT_COLOR[] = "dialog_common_button_text_color";
const char DIALOG_MIN_BUTTON_TEXT_SIZE[] = "dialog_min_button_text_size";
const char DIALOG_MAX_BUTTON_WIDTH[] = "dialog_max_button_width";
const char DIALOG_MIN_BUTTON_WIDTH[] = "dialog_min_button_width";
const char DIALOG_ACTIONS_TOP_PADDING[] = "dialog_actions_top_padding";
const char DIALOG_MASK_COLOR_END[] = "dialog_mask_color_end";
const char DIALOG_DIVIDER_LENGTH[] = "dialog_divider_length";
const char DIALOG_DIVIDER_BETWEEN_BUTTON_WIDTH[] = "dialog_divider_between_button_width";

// pattern attributes for drag bar
const char DRAG_BAR_COLOR[] = "drag_bar_color";

// pattern attributes for close icon
const char CLOSE_ICON_WIDTH[] = "close_icon_width";
const char CLOSE_ICON_Height[] = "close_icon_height";
const char CLOSE_ICON_MARGIN_TOP[] = "close_icon_margin_top";
const char CLOSE_ICON_MARGIN_RIGHT[] = "close_icon_margin_right";
const char CLOSE_ICON_RADIUS[] = "close_icon_radius";

// pattern attributes for popup
const char POPUP_BORDER_RADIUS[] = "popup_border_radius";
const char POPUP_HORIZONTAL_PADDING[] = "popup_horizontal_padding";
const char POPUP_VERTICAL_PADDING[] = "popup_vertical_padding";
const char POPUP_BUTTON_TEXT_FONT_SIZE[] = "popup_button_text_font_size";

// pattern attributes for badge
const char BADGE_BORDER_COLOR[] = "border_color";
const char BADGE_BORDER_WIDTH[] = "border_width";
const char BADGE_AGE_FONT_SIZE[] = "text_age_font_size";
const char BADGE_AGE_SIZE[] = "badge_age_size";
const char BADGE_AFE_ADD_PADDING[] = "badge_age_add_padding";
// swiper attributes
const char INDICATOR_TEXT_FONT_SIZE[] = "indicator_text_font_size";
const char INDICATOR_TEXT_FONT_COLOR[] = "indicator_text_font_color";

// textinput attributes
const char ERROR_TEXT_UNDERLINE_COLOR[] = "error_text_underline_color";
const char UNDERLINE_COLOR[] = "underline_color";
const char UNDERLINE_TEXT_COLOR[] = "underline_text_color";
const char UNDERLINE_FONT_SIZE[] = "text_font_size";
const char BORDER_RADIUS_SIZE[] = "border_radius_size";
// swiper attributes for arrow
const char ARROW_COLOR_BOARDCOLOR_HOVER[] = "arrow_color_boardColor_hover";
const char ARROW_COLOR_BOARDCOLOR_CLICK[] = "arrow_color_boardColor_click";
const char ARROW_COLOR_PRIMARY[] = "arrow_color_primary";
const char ARROW_COLOR_PRIMARY_CONTRARY[] = "arrow_color_primary_contrary";
const char ARROW_DISABLED_ALPHA[] = "arrow_disabled_alpha";
const char ARROW_HORIZONTAL_MARGIN[] = "arrow_horizontal_margin";
const char ARROW_VERTICAL_MARGIN[] = "arrow_vertical_margin";
const char ARROW_COLOR_COMPONENT_NORMAL[] = "arrow_color_component_normal";

// textfield attributes
const char ERROR_UNDERLINE_COLOR[] = "error_underline_color";
const char ERROR_UNDERLINE_TEXT_COLOR[] = "error_underline_text_color";
const char ERROR_UNDERLINE_TEXT_SIZE[] = "error_underline_text_size";
const char ERROR_PASSWORD_CONTENT_COLOR[] = "error_password_content_color";
const char ERROR_PASSWORD_INPUT_COLOR[] = "error_password_input_color";
const char ERROR_PASSWORD_BORDER_COLOR[] = "error_password_border_color";
const char ERROR_PASSWORD_TEXT_COLOR[] = "error_password_text_color";
const char OVER_COUNT_TEXT_COLOR[] = "over_count_text_color";
const char OVER_COUNT_TEXT_FONT_SIZE[] = "over_count_text_font_size";
const char OVER_COUNT_BORDER_COLOR[] = "over_count_border_color";
const char ERROR_PASSWORD_BORDER_ALPHA[] = "error_password_border_alpha";
const char OVER_COUNT_BORDER_COLOR_ALPHA[] = "over_count_border_color_alpha";
const char UNDERLINE_COLOR_ALPHA[] = "underline_color_alpha";
const char INLINE_TEXT_COLOR[] = "inline_text_color";
const char INLINE_RADIUS_SIZE[] = "inline_radius_size";
const char INLINE_BG_COLOR[] = "inline_bg_color";
const char INLINE_BORDER_COLOR[] = "inline_border_color";
const char DISABLE_UNDERLINE_ALPHA[] = "disable_underline_alpha";

const char DEFAULT_COUNTER_COLOR[] = "default_counter_color";
const char OVER_COUNTER_COLOR[] = "over_counter_color";

const char PREVIEW_UNDERLINE_COLOR[] = "preview_underline_color";
const char PREVIEW_BOARD_COLOR[] = "preview_board_color";

// linear split attributes
const char LINEAR_SPLIT_CHILD_MIN_SIZE[] = "linear_split_child_min_size";

// stepper attributes
const char STEPPER_FOCUS_COLOR[] = "stepper_focus_color";
} // namespace OHOS::Ace
