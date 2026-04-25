/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components/rating/rating_theme.h"

#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

namespace {
constexpr Dimension BORDER_RADIUS = 4.0_vp;
constexpr Color STAR_PRESS_COLOR = Color(0x19182431);
constexpr Color STAR_HOVER_COLOR = Color(0x0c182431);
} // namespace

RefPtr<RatingTheme> RatingTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<RatingTheme> theme = AceType::MakeRefPtr<RatingTheme>();
    if (!themeConstants) {
        return theme;
    }
    theme->foregroundResourceId_ = InternalResource::ResourceId::RATE_STAR_BIG_ON_SVG;
    theme->secondaryResourceId_ = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
    theme->backgroundResourceId_ = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
    theme->foregroundMiniResourceId_ = InternalResource::ResourceId::RATE_STAR_SMALL_ON_SVG;
    theme->secondaryMiniResourceId_ = InternalResource::ResourceId::RATE_STAR_SMALL_OFF_SVG;
    theme->backgroundMiniResourceId_ = InternalResource::ResourceId::RATE_STAR_SMALL_OFF_SVG;

    RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_RATING);
    if (pattern) {
        theme->starNum_ = static_cast<int32_t>(pattern->GetAttr<double>("rating_start_num", 0.0));
        theme->ratingScore_ = pattern->GetAttr<double>("rating_score", 0.0);
        theme->ratingMiniScore_ = pattern->GetAttr<double>("rating_mini_score", 0.0);
        theme->stepSize_ = pattern->GetAttr<double>("rating_step_size", 0.0);
        theme->paddingVertical_ = pattern->GetAttr<Dimension>("rating_padding_vertical", 0.0_vp);
        theme->ratingWidth_ = pattern->GetAttr<Dimension>("rating_big_width", 0.0_vp);
        theme->ratingHeight_ = pattern->GetAttr<Dimension>("rating_big_height", 0.0_vp);
        theme->ratingMiniWidth_ = pattern->GetAttr<Dimension>("rating_mini_width", 0.0_vp);
        theme->ratingMiniHeight_ = pattern->GetAttr<Dimension>("rating_mini_height", 0.0_vp);
        theme->designedStarAspectRatio_ = pattern->GetAttr<double>("rating_designed_start_aspect_ratio", 0.0);
        theme->focusBorderWidth_ = pattern->GetAttr<Dimension>("rating_focus_border_width", 0.0_vp);
        theme->hoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, STAR_HOVER_COLOR);
        theme->pressColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_PRESSED, STAR_PRESS_COLOR);
        theme->starColorActive_ = pattern->GetAttr<Color>("icon_color_active", Color::RED);
        theme->starColorInactive_ = pattern->GetAttr<Color>("icon_color_inactive", Color::GRAY);
        theme->borderRadius_ = pattern->GetAttr<Dimension>("hover_radius_size", BORDER_RADIUS);
        theme->hoverAnimationDuration_ = pattern->GetAttr<double>("hover_animation_duration", 0.0);
        theme->pressAnimationDuration_ = pattern->GetAttr<double>("press_animation_duration", 0.0);
        theme->disabledAlpha_ = pattern->GetAttr<double>("rating_disable_alpha", 0.0);
        theme->iconBoardDistance_ = pattern->GetAttr<Dimension>("rating_icon_board_distance", 0.0_vp);
        theme->focusColor_ = pattern->GetAttr<Color>("rating_focus_bgcolor", Color());
        theme->focusSpace_ = pattern->GetAttr<Dimension>("rating_focus_space", 0.0_vp);
        theme->cancelAnimation_ = pattern->GetAttr<double>("rating_focus_blur_cancel_animation", 0.0);
        theme->isCircleRadius_ = static_cast<bool>(pattern->GetAttr<double>("rating_apply_circle_radius", 0.0));
        theme->unlitStarFocusColor_ = pattern->GetAttr<Color>("rating_unlit_star_focus_color", Color());
    } else {
        LOGW("find pattern of rating fail");
    }
    return theme;
}

} // namespace OHOS::Ace
