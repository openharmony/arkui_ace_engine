/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
const char THEME_ATTR_BG_COLOR[] = "attribute_color_background";
const char THEME_ATTR_COLOR_ACCENT[] = "attribute_color_emphasize";
const char THEME_ATTR_COLOR_APPBAR_TITLE[] = "attribute_color_titlebar_text";
const char THEME_ATTR_COLOR_APPBAR_SUBTITLE[] = "attribute_color_titlebar_subtitle_text";
const char THEME_ATTR_COLOR_APPBAR_ICON[] = "attribute_color_titlebar_icon";
const char THEME_ATTR_COLOR_BADGE_RED[] = "attribute_color_badge_red";
const char THEME_ATTR_COLOR_CLICK_EFFECT[] = "attribute_color_click_effect";
const char THEME_ATTR_COLOR_FOCUSED[] = "attribute_color_focused_outline";
const char THEME_ATTR_COLOR_HOVER[] = "attribute_color_hover";
const char THEME_ATTR_COLOR_SUBTAB_LINE_ON[] = "attribute_color_subtab_line_on";
const char THEME_ATTR_COLOR_TAB_BACKGROUND[] = "attribute_color_subtab_bg";
const char THEME_ATTR_COLOR_PRIMARY[] = "attribute_color_primary";
const char THEME_ATTR_COLOR_TOAST_BG[] = "attribute_color_instant_tip_bg";
const char THEME_ATTR_CLICK_CORNER_RADIUS[] = "attribute_corner_radius_clicked";
const char THEME_ATTR_DEFAULT_PADDING_START[] = "attribute_default_padding_top";
const char THEME_ATTR_DEFAULT_PADDING_END[] = "attribute_default_padding_end";
const char THEME_ATTR_SUBHEADER_DIVIDER[] = "attribute_color_subheading_separator";
const char THEME_ATTR_TEXT_COLOR_PRIMARY[] = "attribute_color_text_primary";
const char THEME_ATTR_TEXT_COLOR_PRIMARY_INVERSE[] = "attribute_color_text_primary_contrary";
const char THEME_ATTR_TEXT_COLOR_SECONDARY[] = "attribute_color_text_secondary";
const char THEME_ATTR_TEXT_SIZE_BODY2[] = "attribute_text_size_body2";
const char THEME_ATTR_TEXT_SIZE_CAPTION[] = "attribute_text_size_caption";
const char THEME_ATTR_TEXT_SIZE_HEADLINE6[] = "attribute_text_size_headline6";
const char THEME_ATTR_TEXT_SIZE_HEADLINE7[] = "attribute_text_size_headline7";
const char THEME_ATTR_TEXT_SIZE_OVERLINE[] = "attribute_text_size_over_line";
const char THEME_ATTR_FOURTH_CONTENT_ALPHA[] = "attribute_alpha_content_fourth";
const char THEME_ATTR_HIGHLIGHT_BACKGROUND_ALPHA[] = "attribute_alpha_highlight_bg";
const char THEME_ATTR_DISABLED_ALPHA[] = "attribute_alpha_disabled";
const char THEME_ATTR_TOOLBAR_ICON_COLOR[] = "attribute_color_toolbar_icon";
const char THEME_ATTR_TOOLBAR_TEXT_COLOR[] = "attribute_color_toolbar_text";
const char THEME_ATTR_TOOLBAR_BG_COLOR[] = "attribute_color_toolbar_bg";
const char THEME_ATTR_TOOLBAR_SUB_BG_COLOR[] = "attribute_color_toolbar_sub_bg";
const char THEME_ATTR_TEXT_SIZE_BUTTON1[] = "attribute_text_size_button1";
const char THEME_ATTR_COLOR_PROGRESS[] = "attribute_color_progress";
const char THEME_ATTR_COLOR_COMPONENT_NORMAL[] = "attribute_color_component_normal";
const char THEME_ATTR_COLOR_EMPHASIZE[] = "attribute_color_emphasize";
const char THEME_ATTR_COLOR_DIALOG_BG[] = "attribute_color_dialog_bg";
const char THEME_ATTR_COLOR_FOREGROUND[] = "attribute_color_foreground";
const char THEME_ATTR_COLOR_TIPS_BG[] = "attribute_color_help_tip_bg";
const char THEME_ATTR_COLOR_LIST_DIVIDER[] = "attribute_color_list_separator";
const char THEME_ATTR_TEXT_COLOR_HIGHLIGHT[] = "attribute_color_text_highlight_bg";
const char THEME_ATTRPALETTE_COLOR11[] = "attribute_color_palette11";
const char THEME_ATTR_COLOR_SPINNER_ICON[] = "attribute_color_spinner_icon";
const char THEME_ATTR_COLOR_CONTROL_ACTIVE[] = "attr_color_control_actived";
const char THEME_ATTR_COLOR_TEXT_PRIMARY_ACTIVATED[] = "attribute_color_text_primary_activated";
const char THEME_ATTR_COLOR_TERTIARY[] = "attribute_color_tertiary";
const char THEME_ATTR_COLOR_FOURTH[] = "attribute_color_fourth";

// component patterns
const char THEME_PATTERN_BUTTON[] = "button_pattern";
const char THEME_PATTERN_CHECKBOX[] = "checkbox_pattern";
const char THEME_PATTERN_DATA_PANEL[] = "data_panel_pattern";
const char THEME_PATTERN_RADIO[] = "radio_pattern";
const char THEME_PATTERN_SWIPER[] = "swiper_pattern";
const char THEME_PATTERN_SWITCH[] = "switch_pattern";
const char THEME_PATTERN_TOOLBAR[] = "toolbar_pattern";
const char THEME_PATTERN_TOGGLE[] = "toggle_pattern";

// pattern general attributes
const char PATTERN_BG_COLOR[] = "background_color";
const char PATTERN_TEXT_SIZE[] = "text_size";
const char PATTERN_WIDTH[] = "width";
const char PATTERN_HEIGHT[] = "height";

// pattern attributes for piece
const char PIECE_TEXT_COLOR[] = "attribute_color_text_primary";
const char PIECE_TEXT_FONT_SIZE[] = "attribute_text_size_button2";
const char PIECE_BACKGROUND_COLOR[] = "attribute_color_foreground";
const char PIECE_BACKGROUND_COLOR_ALPHA[] = "attribute_alpha_inapptip_bg";
const char PIECE_HOVER_COLOR[] = "attribute_color_hover";

// pattern attributes for popup
const char POPUP_BACKGROUND_COLOR[] = "attribute_color_help_tip_bg";

// pattern attributes for search
const char SEARCH_PLACEHOLDER_COLOR[] = "attribute_color_text_hint";
const char SEARCH_TEXT_COLOR[] = "attribute_color_text_primary";
const char SEARCH_TEXT_FONT_SIZE[] = "attribute_text_size_body1";

// pattern attributes for textfield
const char TEXTFIELD_BACKGROUND_COLOR[] = "attribute_color_text_field_sub_bg";
const char TEXTFIELD_FONT_SIZE[] = "attribute_text_size_body1";
const char TEXTFIELD_HINT_TEXT_COLOR[] = "attribute_color_text_hint";
const char TEXTFIELD_TEXT_COLOR[] = "attribute_color_text_primary";
const char TEXTFIELD_TEXT_COLOR_DISABLE[] = "attribute_color_text_tertiary";
const char TEXTFIELD_ERROR_COLOR[] = "attribute_color_alert";
const char TEXTFIELD_ERROR_TEXT_FONT_SIZE[] = "attribute_text_size_body3";
const char TEXTFIELD_COUNT_TEXT_COLOR[] = "attribute_color_text_tertiary";
const char TEXTFIELD_COUNT_TEXT_FONT_SIZE[] = "attribute_text_size_caption";
const char TEXTFIELD_COUNT_TEXT_FONT_SIZE_OUTER[] = "attribute_text_size_body3";
const char TEXTFIELD_CURSOR_COLOR[] = "attribute_color_text_primary_activated";
const char TEXTFIELD_HOVER_COLOR[] = "attribute_color_hover";
const char TEXTFIELD_PRESS_COLOR[] = "attribute_color_click_effect";
const char TEXTFIELD_SELECTED_COLOR[] = "attribute_color_text_highlight_bg";

// pattern attributes for button
const char BUTTON_CLICK_BLEND_COLOR[] = "click_mask_color";
const char BUTTON_HOVER_COLOR[] = "attribute_color_hover";
const char BUTTON_TEXT_COLOR[] = "emphasize_button_text_color";
const char BUTTON_NORMAL_TEXT_COLOR[] = "text_button_text_color";
const char BUTTON_DOWNLOAD_BG_COLOR[] = "attribute_color_background";
const char BUTTON_DOWNLOAD_TEXT_COLOR[] = "download_button_text_color";
const char BUTTON_DOWNLOAD_BORDER_COLOR[] = "download_button_border_color";
const char BUTTON_BORDER_COLOR[] = "border_color";
const char BUTTON_BORDER_WIDTH[] = "border_width";

// pattern attributes for toolbar
const char TOOLBAR_ICON_MORE_COLOR[] = "toolbar_icon_more_color";

// pattern attributes for checkable
const char HOVER_EFFECT_COLOR[] = "hover_effect_color";
const char HOVER_EFFECT_RADIUS[] = "hover_effect_radius";
const char BORDER_RADIUS[] = "border_radius";
const char FG_COLOR_CHECKED[] = "fg_color_checked";
const char BG_COLOR_CHECKED[] = "bg_color_checked";
const char FG_COLOR_UNCHECKED[] = "fg_color_unchecked";
const char BG_COLOR_UNCHECKED[] = "bg_color_unchecked";

// pattern attributes for swiper
const char INDICATOR_MASK_COLOR[] = "indicator_mask_color";
const char INDICATOR_COLOR_SELECTED[] = "indicator_color_selected";
const char INDICATOR_COLOR_UNSELECTED[] = "indicator_color_unselected";
const char INDICATOR_TEXT_COLOR[] = "indicator_text_color";
const char INDICATOR_TEXT_COLOR_FOCUS[] = "indicator_text_color_focus";

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
const char DATA_PANEL_TRACK_COLOR[] = "track_bg_color";

// pattern attributes for text overlay
const char TEXT_OVERLAY_HANDLE_COLOR[] = "attribute_color_emphasize";
const char TEXT_OVERLAY_HANDLE_COLOR_INNER[] = "attribute_color_dialog_bg";
const char TEXT_OVERLAY_TOOL_BAR_FONT_SIZE[] = "attribute_text_size_button2";
const char TEXT_OVERLAY_TOOL_BAR_TEXT_COLOR[] = "attribute_color_text_primary";
const char TEXT_OVERLAY_TOOL_BAR_ICON_COLOR[] = "attribute_color_primary";
const char TEXT_OVERLAY_TOOL_BAR_BACKGROUND_COLOR[] = "attribute_color_dialog_bg";
const char TEXT_OVERLAY_TOOL_BAR_BUTTON_HOVER_COLOR[] = "attribute_color_hover";
const char TEXT_OVERLAY_TOOL_BAR_BUTTON_PRESS_COLOR[] = "attribute_color_click_effect";
const char TEXT_OVERLAY_MENU_ICON_COLOR[] = "attribute_color_secondary";

// pattern attributes for toggle
const char TOGGLE_BACKGROUND_COLOR[] = "attribute_color_button_normal";
const char TOGGLE_CHECKED_COLOR[] = "toggle_checked_color";
const char TOGGLE_TEXT_COLOR[] = "toggle_text_color";

} // namespace OHOS::Ace
