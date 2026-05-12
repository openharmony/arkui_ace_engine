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

#include "base/geometry/dimension.h"
#include "base/resource/internal_resource.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"

namespace OHOS::Ace {

class ThemeConstants;

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

        RefPtr<RatingTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;
    };

    ~RatingTheme() override = default;

    int32_t GetStarNum() const
    {
        return starNum_;
    }

    const Dimension& GetIconBoardDistance() const
    {
        return iconBoardDistance_;
    }

    Color GetUnlitStarFocusColor() const
    {
        return unlitStarFocusColor_;
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

    double GetFocusAndBlurCancleAnimation() const
    {
        return cancelAnimation_;
    }

    const Dimension& GetFocusBorderWidth() const
    {
        return focusBorderWidth_;
    }

    const Dimension& GetFocusBorderRadius() const
    {
        return borderRadius_;
    }

    const Dimension& GetFocusSpace() const
    {
        return focusSpace_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
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

    bool GetIsCircleRadius() const
    {
        return isCircleRadius_;
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
    Dimension focusSpace_;
    Dimension iconBoardDistance_;
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
    Color focusColor_;
    Color unlitStarFocusColor_;
    Dimension focusBorderWidth_;
    Dimension borderRadius_;
    double cancelAnimation_ = 0.0;
    bool isCircleRadius_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RATING_RATING_THEME_H
