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

#include "core/components/theme/icon_theme.h"

namespace OHOS::Ace {
namespace {
static std::unordered_map<InternalResource::ResourceId, std::string> RESOURCE_ICON_MAP = {
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_CLOSE, "container_modal_window_close" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_CLOSE, "container_modal_window_defocus_close" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MAXIMIZE,
        "container_modal_window_defocus_maximize" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_MINIMIZE,
        "container_modal_window_defocus_minimize" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_RECOVER, "container_modal_window_defocus_recover" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_DEFOCUS_SPLIT_LEFT,
        "container_modal_window_defocus_split_left" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MAXIMIZE, "container_modal_window_maximize" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_MINIMIZE, "container_modal_window_minimize" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_RECOVER, "container_modal_window_recover" },
    { InternalResource::ResourceId::CONTAINER_MODAL_WINDOW_SPLIT_LEFT, "container_modal_window_split_left" },
    { InternalResource::ResourceId::CLOSE_SVG, "close" },
    { InternalResource::ResourceId::CORRECT_SVG, "correct" },
    { InternalResource::ResourceId::DOWN_ARROW_SVG, "down_arrow" },
    { InternalResource::ResourceId::FA_BLACK_CLOCK_WIDGET_HOUR, "fa_black_clock_widget_hour" },
    { InternalResource::ResourceId::FA_BLACK_CLOCK_WIDGET_MINUTE, "fa_black_clock_widget_minute" },
    { InternalResource::ResourceId::FA_BLACK_CLOCK_WIDGET_SECOND, "fa_black_clock_widget_second" },
    { InternalResource::ResourceId::FA_CLOCK_WIDGET_HOUR, "fa_clock_widget_hour" },
    { InternalResource::ResourceId::FA_CLOCK_WIDGET_MINUTE, "fa_clock_widget_minute" },
    { InternalResource::ResourceId::FA_CLOCK_WIDGET_SECOND, "fa_clock_widget_second" },
    { InternalResource::ResourceId::FULLSCREEN_SVG, "full_screen" },
    { InternalResource::ResourceId::HIDE_PASSWORD_SVG, "hide_password" },
    { InternalResource::ResourceId::TITLEBAR_BACK, "titlebar_back" },
    { InternalResource::ResourceId::IC_BACK, "ic_back" },
    { InternalResource::ResourceId::IC_MORE, "ic_more" },
    { InternalResource::ResourceId::INDEXER_ARROW_PNG, "indexer_arrow" },
    { InternalResource::ResourceId::LEFT_ARROW_SVG, "left_arrow" },
    { InternalResource::ResourceId::PAUSE_SVG, "pause" },
    { InternalResource::ResourceId::PIECE_DELETE_SVG, "piece_delete" },
    { InternalResource::ResourceId::PLAY_SVG, "play" },
    { InternalResource::ResourceId::QUIT_FULLSCREEN_SVG, "exit_full_screen" },
    { InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG, "rate_star_big_off" },
    { InternalResource::ResourceId::RATE_STAR_BIG_ON_SVG, "rate_star_big_on" },
    { InternalResource::ResourceId::RATE_STAR_SMALL_OFF_SVG, "rate_star_small_off" },
    { InternalResource::ResourceId::RATE_STAR_SMALL_ON_SVG, "rate_star_small_on" },
    { InternalResource::ResourceId::RIGHT_ARROW_SVG, "right_arrow" },
    { InternalResource::ResourceId::SEARCH_SVG, "search" },
    { InternalResource::ResourceId::SELECT_ARROW_DISABLED_PNG, "select_arrow_disabled" },
    { InternalResource::ResourceId::SELECT_ARROW_NORMAL_PNG, "select_arrow_normal" },
    { InternalResource::ResourceId::SEMI_MODAL_BAR_DOWN_SVG, "semi_modal_bar_down" },
    { InternalResource::ResourceId::SEMI_MODAL_BAR_MIDDLE_SVG, "semi_modal_bar_middle" },
    { InternalResource::ResourceId::SHARE_SVG, "share" },
    { InternalResource::ResourceId::SHOW_PASSWORD_SVG, "show_password" },
    { InternalResource::ResourceId::SIDE_BAR, "ic_public_drawer" },
    { InternalResource::ResourceId::SPINNER, "ic_public_spinner" },
    { InternalResource::ResourceId::SPINNER_DISABLE, "ic_public_spinner_disable" },
    { InternalResource::ResourceId::STEPPER_BACK_ARROW, "stepper_back_arrow" },
    { InternalResource::ResourceId::STEPPER_NEXT_ARROW, "stepper_next_arrow" },
    { InternalResource::ResourceId::TRANSLATE_C2E_SVG, "translate_c2e" },
    { InternalResource::ResourceId::UP_ARROW_SVG, "up_arrow" },
    { InternalResource::ResourceId::WATCH_DOWN_ARROW_SVG, "watch_down_arrow" },
    { InternalResource::ResourceId::WATCH_UP_ARROW_SVG, "watch_up_arrow" },
    { InternalResource::ResourceId::WRONG_SVG, "wrong" },
    { InternalResource::ResourceId::INPUT_SEARCH_SVG, "ic_public_input_search" },
    { InternalResource::ResourceId::APP_BAR_BACK_SVG, "app_bar_back" },
    { InternalResource::ResourceId::APP_BAR_FA_SVG, "app_bar_fa" },
    { InternalResource::ResourceId::APP_BAR_MENU_SVG, "app_bar_menu" },
    { InternalResource::ResourceId::APP_BAR_CLOSE_SVG, "app_bar_close" },
    { InternalResource::ResourceId::MENU_OK_SVG, "ic_public_ok" },
    { InternalResource::ResourceId::LOCATION_BUTTON_FILLED_SVG, "location_button_filled"},
    { InternalResource::ResourceId::LOCATION_BUTTON_LINE_SVG, "location_button_line"},
    { InternalResource::ResourceId::PASTE_BUTTON_LINE_SVG, "paste_button_line"},
    { InternalResource::ResourceId::SAVE_BUTTON_FILLED_SVG, "save_button_filled"},
    { InternalResource::ResourceId::SAVE_BUTTON_LINE_SVG, "save_button_line"},
    { InternalResource::ResourceId::SAVE_BUTTON_PICTURE_SVG, "save_button_picture"},
    { InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG, "ic_public_arrow_left" },
    { InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG, "ic_public_arrow_right" },
    { InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG, "ic_public_arrow_up" },
    { InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG, "ic_public_arrow_down" },
    { InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_LEFT_SVG, "ic_public_double_arrow_left" },
    { InternalResource::ResourceId::IC_PUBLIC_DOUBLE_ARROW_RIGHT_SVG, "ic_public_double_arrow_right" },
    { InternalResource::ResourceId::IC_CUT_SVG, "ic_public_cut" },
    { InternalResource::ResourceId::IC_COPY_SVG, "ic_public_copy" },
    { InternalResource::ResourceId::IC_PASTE_SVG, "ic_public_paste" },
    { InternalResource::ResourceId::IC_SELECT_ALL_SVG, "ic_public_select_all" },
    { InternalResource::ResourceId::IC_SHARE_SVG, "ic_public_share" },
    { InternalResource::ResourceId::IC_TRANSLATE_SVG, "ic_public_translate_c2e" },
    { InternalResource::ResourceId::IC_SEARCH_SVG, "ic_public_search_filled" },
    { InternalResource::ResourceId::IC_AI_WRITE_SVG, "ic_public_ai_write" },
    { InternalResource::ResourceId::MENU_OK_SVG, "ic_public_ok" },
    { InternalResource::ResourceId::IC_WINDOW_CLOSE, "ic_window_close" },
    { InternalResource::ResourceId::IC_WINDOW_MAX, "ic_window_max" },
    { InternalResource::ResourceId::IC_WINDOW_MENU_FULLSCREEN, "ic_window_menu_fullscreen" },
    { InternalResource::ResourceId::IC_WINDOW_MENU_MAXIMIZE, "ic_window_menu_maximize" },
    { InternalResource::ResourceId::IC_WINDOW_MENU_OK, "ic_window_menu_ok" },
    { InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_L, "ic_window_menu_screen_l" },
    { InternalResource::ResourceId::IC_WINDOW_MENU_SCREEN_N, "ic_window_menu_screen_n" },
    { InternalResource::ResourceId::IC_WINDOW_MIN, "ic_window_min" },
    { InternalResource::ResourceId::IC_WINDOW_RESTORES, "ic_window_restores" },
    { InternalResource::ResourceId::IC_BOTTOMSHEET_CLOSE_SVG, "ic_bottomsheet_close" },
    { InternalResource::ResourceId::IC_CANCEL_SVG, "ic_public_cancel" },
    { InternalResource::ResourceId::RADIO_TICK_SVG, "radio_tick_svg" },
    { InternalResource::ResourceId::RADIO_DOT_SVG, "radio_dot_svg" },
    { InternalResource::ResourceId::IC_TAKEPHOTO_SVG, "ic_public_camera" }
};
}

RefPtr<IconTheme> IconTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<IconTheme>theme  = AceType::Claim(new IconTheme());
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants, theme);
    return theme;
}

void IconTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<IconTheme>& theme) const
{
    theme->pattern_ = themeConstants->GetPatternByName(THEME_PATTERN_ICON);
}

std::string IconTheme::GetIconPath(const InternalResource::ResourceId& resourceId) const
{
    if (!pattern_) {
        return "";
    }
    auto iter = RESOURCE_ICON_MAP.find(resourceId);
    if (iter == RESOURCE_ICON_MAP.end()) {
        TAG_LOGW(AceLogTag::ACE_THEME, "Find iconPath fail in resourceMap, resourceId:%{public}d", resourceId);
        return "";
    }
    return pattern_->GetAttr<std::string>(iter->second, "");
}
} // namespace OHOS::Ace
