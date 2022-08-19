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
    { InternalResource::ResourceId::STEPPER_BACK_ARROW, "stepper_back_arrow" },
    { InternalResource::ResourceId::STEPPER_NEXT_ARROW, "stepper_next_arrow" },
    { InternalResource::ResourceId::TRANSLATE_C2E_SVG, "translate_c2e" },
    { InternalResource::ResourceId::UP_ARROW_SVG, "up_arrow" },
    { InternalResource::ResourceId::WATCH_DOWN_ARROW_SVG, "watch_down_arrow" },
    { InternalResource::ResourceId::WATCH_UP_ARROW_SVG, "watch_up_arrow" },
    { InternalResource::ResourceId::WRONG_SVG, "wrong" }
};
}

RefPtr<IconTheme> IconTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<IconTheme>theme  = AceType::Claim(new IconTheme());
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants->GetThemeStyle(), theme);
    return theme;
}

void IconTheme::Builder::ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<IconTheme>& theme) const
{
    if (!themeStyle) {
        return;
    }
    theme->pattern_ = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_ICON, nullptr);
    if (!theme->pattern_) {
        LOGW("find pattern of icon fail");
    }
}

std::string IconTheme::GetIconPath(const InternalResource::ResourceId& resourceId) const
{
    if (!pattern_) {
        LOGW("pattern of icon is null");
        return "";
    }
    auto iter = RESOURCE_ICON_MAP.find(resourceId);
    if (iter == RESOURCE_ICON_MAP.end()) {
        LOGW("Find resourceId:%{public}d fail in resourceMap", resourceId);
        return "";
    }
    return pattern_->GetAttr<std::string>(iter->second, "");
}
} // namespace OHOS::Ace
