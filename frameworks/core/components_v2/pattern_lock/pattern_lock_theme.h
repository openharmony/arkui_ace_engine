/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_PATTERN_LOCK_PATTERN_LOCK_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_PATTERN_LOCK_PATTERN_LOCK_THEME_H
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"
namespace OHOS::Ace::V2 {
class PatternLockTheme : public virtual Theme {
    DECLARE_ACE_TYPE(PatternLockTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        static constexpr Dimension DEFAULT_SIDE_LENGTH = 288.0_vp;
        static constexpr Dimension DEFAULT_CIRCLE_RADIUS = 6.0_vp;
        static constexpr Dimension DEFAULT_PATH_STROKE_WIDTH = 12.0_vp;
        static constexpr Dimension DEFAULT_ACTIVE_CIRCLE_RADIUS = 7.0_vp;
        static constexpr Dimension DEFAULT_BACKGROUND_CIRCLE_RADIUS = 11.0_vp;
        static constexpr Dimension DEFAULT_LIGHT_RING_CIRCLE_RADIUS_START = 6.0_vp;
        static constexpr Dimension DEFAULT_LIGHT_RING_CIRCLE_RADIUS_END = 37.5_vp;
        static constexpr Dimension DEFAULT_HOVER_CIRCLE_RADIUS = 11.0_vp;
        static constexpr Dimension HOTSPOT_CIRCLE_RADIUS = 48.0_vp;
        static constexpr Dimension FOCUS_PADDING_RADIUS = 2.0_vp;
        static constexpr Dimension FOCUS_PAINT_WIDTH = 2.0_vp;

        static constexpr Dimension DEFAULT_SIDE_LENGTH_API9 = 300.0_vp;
        static constexpr Dimension DEFAULT_CIRCLE_RADIUS_API9 = 14.0_vp;
        static constexpr Dimension DEFAULT_PATH_STROKE_WIDTH_API9 = 34.0_vp;
        static constexpr Dimension DEFAULT_ACTIVE_CIRCLE_RADIUS_API9 = 16.0_vp;
        static constexpr Dimension DEFAULT_BACKGROUND_CIRCLE_RADIUS_API9 = 26.0_vp;

        RefPtr<PatternLockTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<PatternLockTheme> theme = AceType::Claim(new PatternLockTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->wrongColor_ = Color::RED;
            theme->correctColor_ = Color::BLUE;
            theme->hoverColor_ = Color::BLACK;
            theme->focusColor_ = Color::BLACK;
            theme->lightRingRadiusStart_ = DEFAULT_LIGHT_RING_CIRCLE_RADIUS_START;
            theme->lightRingRadiusEnd_ = DEFAULT_LIGHT_RING_CIRCLE_RADIUS_END;
            theme->hoverRadius_ = DEFAULT_HOVER_CIRCLE_RADIUS;
            theme->hotSpotCircleRadius_ = HOTSPOT_CIRCLE_RADIUS;
            theme->focusPaddingRadius_ = FOCUS_PADDING_RADIUS;
            theme->focusPaintWidth_ = FOCUS_PAINT_WIDTH;
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
                theme->regularColor_ = Color::BLACK;
                theme->activeColor_ = Color::BLACK;
                theme->selectedColor_ = Color::BLACK;
                theme->pathColor_ = Color::BLUE;
                theme->sideLength_ = DEFAULT_SIDE_LENGTH_API9;
                theme->circleRadius_ = DEFAULT_CIRCLE_RADIUS_API9;
                theme->pathStrokeWidth_ = DEFAULT_PATH_STROKE_WIDTH_API9;
                theme->activeCircleRadius_ = DEFAULT_ACTIVE_CIRCLE_RADIUS_API9;
                theme->backgroundCircleRadius_ = DEFAULT_BACKGROUND_CIRCLE_RADIUS_API9;
            } else {
                theme->circleRadius_ = DEFAULT_CIRCLE_RADIUS;
                theme->pathStrokeWidth_ = DEFAULT_PATH_STROKE_WIDTH;
                theme->activeCircleRadius_ = DEFAULT_ACTIVE_CIRCLE_RADIUS;
                theme->backgroundCircleRadius_ = DEFAULT_BACKGROUND_CIRCLE_RADIUS;
                ParsePattern(themeConstants, theme);
            }
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<PatternLockTheme>& theme) const
        {
            if (theme == nullptr) {
                return;
            }
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_PATTERN_LOCK);
            if (pattern) {
                theme->regularColor_ = pattern->GetAttr<Color>("regular_color", Color::BLACK);
                theme->activeColor_ = pattern->GetAttr<Color>("selected_color", Color::BLACK);
                theme->selectedColor_ = pattern->GetAttr<Color>("selected_color", Color::BLACK);
                theme->wrongColor_ = pattern->GetAttr<Color>("wrong_color", Color::BLACK);
                theme->correctColor_ = pattern->GetAttr<Color>("correct_color", Color::BLACK);
                theme->pathColor_ = pattern->GetAttr<Color>("path_color", Color::BLACK);
                theme->hoverColor_ = pattern->GetAttr<Color>("hover_color", Color::BLACK);
                theme->focusColor_ = pattern->GetAttr<Color>("focus_color", Color::BLACK);
                theme->passPointTxt_ = pattern->GetAttr<std::string>("pass_point", "");
                theme->sideLength_ = pattern->GetAttr<Dimension>("patternlock_side_length", DEFAULT_SIDE_LENGTH);
            }
        }
    };
    ~PatternLockTheme() override = default;
    const Color& GetRegularColor() const
    {
        return regularColor_;
    }
    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }
    const Color& GetActiveColor() const
    {
        return activeColor_;
    }
    const Color& GetPathColor() const
    {
        return pathColor_;
    }

    const Color& GetWrongColor() const
    {
        return wrongColor_;
    }

    const Color& GetCorrectColor() const
    {
        return correctColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    Dimension GetSideLength() const
    {
        return sideLength_;
    }

    Dimension GetCircleRadius() const
    {
        return circleRadius_;
    }

    Dimension GetPathStrokeWidth() const
    {
        return pathStrokeWidth_;
    }

    float GetActiveCircleRadiusScale() const
    {
        if (!NearZero(circleRadius_.Value())) {
            return activeCircleRadius_.Value() / circleRadius_.Value();
        }
        return 1;
    }

    float GetBackgroundRadiusScale() const
    {
        if (!NearZero(circleRadius_.Value())) {
            return backgroundCircleRadius_.Value() / circleRadius_.Value();
        }
        return 1;
    }

    float GetLightRingCircleRadiusStartScale() const
    {
        if (!NearZero(circleRadius_.Value())) {
            return lightRingRadiusStart_.Value() / circleRadius_.Value();
        }
        return 1;
    }

    float GetLightRingCircleRadiusEndScale() const
    {
        if (!NearZero(circleRadius_.Value())) {
            return lightRingRadiusEnd_.Value() / circleRadius_.Value();
        }
        return 1;
    }

    float GetHoverRadiusScale() const
    {
        if (!NearZero(circleRadius_.Value())) {
            return hoverRadius_.Value() / circleRadius_.Value();
        }
        return 1;
    }

    Dimension GetHotSpotCircleRadius() const
    {
        return hotSpotCircleRadius_;
    }

    Dimension GetFocusPaddingRadius() const
    {
        return focusPaddingRadius_;
    }

    Dimension GetFocusPaintWidth() const
    {
        return focusPaintWidth_;
    }

    std::string GetPassPointTxt() const
    {
        return passPointTxt_;
    }
protected:
    PatternLockTheme() = default;

private:
    Color regularColor_;
    Color selectedColor_;
    Color activeColor_;
    Color pathColor_;
    Color wrongColor_;
    Color correctColor_;
    Color hoverColor_;
    Color focusColor_;
    Dimension sideLength_;
    Dimension circleRadius_;
    Dimension pathStrokeWidth_;
    Dimension activeCircleRadius_;
    Dimension backgroundCircleRadius_;
    Dimension lightRingRadiusStart_;
    Dimension lightRingRadiusEnd_;
    Dimension hoverRadius_;
    Dimension hotSpotCircleRadius_;
    Dimension focusPaddingRadius_;
    Dimension focusPaintWidth_;
    std::string passPointTxt_;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_PATTERN_LOCK_PATTERN_LOCK_THEME_H
