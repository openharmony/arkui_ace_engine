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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RATING_RATING_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RATING_RATING_THEME_H

#include "base/resource/internal_resource.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
namespace {
constexpr Dimension BORDER_RADIUS = 4.0_vp;
constexpr Color STAR_PRESS_COLOR = Color(0x19182431);
constexpr Color STAR_HOVER_COLOR = Color(0x0c182431);
} // namespace
/**
 * RatingTheme defines color and styles of RatingComponent. RatingTheme should be built
 * using RatingTheme::Builder.
 */
class RatingTheme : public virtual Theme {
    DECLARE_ACE_TYPE(RatingTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<RatingTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<RatingTheme> theme = AceType::Claim(new RatingTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->foregroundResourceId_ = themeConstants->GetResourceId(THEME_RATING_RESOURCE_ID_BIG_ON);
            theme->secondaryResourceId_ = themeConstants->GetResourceId(THEME_RATING_RESOURCE_ID_BIG_HALF);
            theme->backgroundResourceId_ = themeConstants->GetResourceId(THEME_RATING_RESOURCE_ID_BIG_OFF);
            theme->foregroundMiniResourceId_ = themeConstants->GetResourceId(THEME_RATING_RESOURCE_ID_MINI_ON);
            theme->secondaryMiniResourceId_ = themeConstants->GetResourceId(THEME_RATING_RESOURCE_ID_MINI_HALF);
            theme->backgroundMiniResourceId_ = themeConstants->GetResourceId(THEME_RATING_RESOURCE_ID_MINI_OFF);

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
            } else {
                LOGW("find pattern of rating fail");
            }
            return theme;
        }
    };

    ~RatingTheme() override = default;

    int32_t GetStarNum() const
    {
        return starNum_;
    }

    const Dimension& GetRatingWidth() const
    {
        return ratingWidth_;
    }

    const Dimension& GetRatingHeight() const
    {
        return ratingHeight_;
    }

    const Dimension& GetRatingMiniWidth() const
    {
        return ratingMiniWidth_;
    }

    const Dimension& GetRatingMiniHeight() const
    {
        return ratingMiniHeight_;
    }

    const Dimension& GetPaddingVertical() const
    {
        return paddingVertical_;
    }

    double GetStepSize() const
    {
        return stepSize_;
    }

    double GetRatingScore() const
    {
        return ratingScore_;
    }

    double GetRatingMiniScore() const
    {
        return ratingMiniScore_;
    }

    const InternalResource::ResourceId& GetForegroundResourceId() const
    {
        return foregroundResourceId_;
    }

    const InternalResource::ResourceId& GetSecondaryResourceId() const
    {
        return secondaryResourceId_;
    }

    const InternalResource::ResourceId& GetBackgroundResourceId() const
    {
        return backgroundResourceId_;
    }

    const InternalResource::ResourceId& GetForegroundMiniResourceId() const
    {
        return foregroundMiniResourceId_;
    }

    const InternalResource::ResourceId& GetSecondaryMiniResourceId() const
    {
        return secondaryMiniResourceId_;
    }

    const InternalResource::ResourceId& GetBackgroundMiniResourceId() const
    {
        return backgroundMiniResourceId_;
    }

    double GetDesignedStarAspectRatio() const
    {
        return designedStarAspectRatio_;
    }

    const Dimension& GetFocusBorderWidth() const
    {
        return focusBorderWidth_;
    }

    const Dimension& GetFocusBorderRadius() const
    {
        return borderRadius_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    const Color& GetStarColorActive() const
    {
        return starColorActive_;
    }

    const Color& GetStarColorInactive() const
    {
        return starColorInactive_;
    }

    double GetHoverAnimationDuration() const
    {
        return hoverAnimationDuration_;
    }

    double GetPressAnimationDuration() const
    {
        return pressAnimationDuration_;
    }

    double GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

protected:
    RatingTheme() = default;

private:
    int32_t starNum_ = 0;
    Dimension ratingWidth_;
    Dimension ratingHeight_;
    Dimension ratingMiniWidth_;
    Dimension ratingMiniHeight_;
    Dimension paddingVertical_;
    double stepSize_ = 0.0;
    double ratingScore_ = 0.0;
    double ratingMiniScore_ = 0.0;
    double designedStarAspectRatio_ = 1.0;
    double hoverAnimationDuration_ = 0.0;
    double pressAnimationDuration_ = 0.0;
    double disabledAlpha_ = 1.0;
    InternalResource::ResourceId foregroundResourceId_ = InternalResource::ResourceId::RATE_STAR_BIG_ON_SVG;
    InternalResource::ResourceId secondaryResourceId_ = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
    InternalResource::ResourceId backgroundResourceId_ = InternalResource::ResourceId::RATE_STAR_BIG_OFF_SVG;
    InternalResource::ResourceId foregroundMiniResourceId_ = InternalResource::ResourceId::RATE_STAR_SMALL_ON_SVG;
    InternalResource::ResourceId secondaryMiniResourceId_ = InternalResource::ResourceId::RATE_STAR_SMALL_ON_SVG;
    InternalResource::ResourceId backgroundMiniResourceId_ = InternalResource::ResourceId::RATE_STAR_SMALL_OFF_SVG;

    // properties for phone platform
    Color hoverColor_;
    Color pressColor_;
    Color starColorActive_;
    Color starColorInactive_;
    Dimension focusBorderWidth_;
    Dimension borderRadius_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RATING_RATING_THEME_H
