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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROGRESS_PROGRESS_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROGRESS_PROGRESS_THEME_H

#include "base/geometry/dimension.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

constexpr double CAPSULE_NONE_SHADOW_VALUE = 6.0;
constexpr double CAPSULE_HOVER_EFFECT_SCALE = 2.0;

/**
 * ProgressTheme defines color and styles of ProgressComponent. ProgressTheme should be built
 * using ProgressTheme::Builder.
 */
class ProgressTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ProgressTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ProgressTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ProgressTheme> theme = AceType::Claim(new ProgressTheme());
            if (!themeConstants) {
                return theme;
            }
            // Read style from system.
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<ProgressTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("progress_pattern", nullptr);
            if (!pattern) {
                return;
            }
            const double defaultCachedAlpha = 0.4;
            const double defaultLoadBGAlpha = 0.6;
            const double defaultRingBackgroundOpacity = 0.03;
            Color defaultColor = Color::FromRGBO(18, 24, 31, 1.0);
            theme->trackThickness_ = pattern->GetAttr<Dimension>("progress_thickness", 0.0_vp);
            theme->trackWidth_ = pattern->GetAttr<Dimension>("progress_default_width", 0.0_vp);
            theme->ringThickness_ = pattern->GetAttr<Dimension>("progress_ring_thickness", 0.0_vp);
            theme->ringDiameter_ = pattern->GetAttr<Dimension>("progress_default_diameter", 0.0_vp);
            theme->loadingDiameter_ = pattern->GetAttr<Dimension>("progress_default_diameter", 0.0_vp);
            theme->scaleNumber_ = static_cast<int32_t>(pattern->GetAttr<double>("progress_scale_number", 0.0));
            theme->scaleWidth_ = pattern->GetAttr<Dimension>("progress_scale_width", 0.0_vp);
            theme->scaleLength_ = pattern->GetAttr<Dimension>("progress_stroke_width", 0.0_vp);
            theme->scaleRingDiameter_ = pattern->GetAttr<Dimension>("progress_scale_default_diameter", 0.0_vp);
            theme->moonDiameter_ = pattern->GetAttr<Dimension>("progress_moon_diameter", 0.0_vp);
            theme->moveRatio_ = pattern->GetAttr<double>("progress_loading_move_ratio", 0.0);
            theme->ringRadius_ = pattern->GetAttr<Dimension>("progress_loading_ring_radius", 0.0_vp);
            theme->orbitRadius_ = pattern->GetAttr<Dimension>("progress_loading_orbit_radius", 0.0_vp);
            theme->cometTailLen_ = pattern->GetAttr<double>("progress_loading_comet_tail_len", 0.0);
            theme->bubbleRadius_ = pattern->GetAttr<Dimension>("progress_bubble_radius", 0.0_vp);
            theme->bubbleDiameter_ = pattern->GetAttr<Dimension>("progress_bubble_diameter", 0.0_vp);
            theme->progressHeight_ = pattern->GetAttr<Dimension>("progress_button_download_height", 0.0_vp);
            theme->trackBgColor_ = pattern->GetAttr<Color>("bg_color", Color::RED);
            theme->trackSelectedColor_ = pattern->GetAttr<Color>("fg_color", Color::RED);
            theme->trackCachedColor_ = theme->trackSelectedColor_
                .BlendOpacity(pattern->GetAttr<double>("fg_color_cached_alpha", defaultCachedAlpha));
            theme->progressColor_ = pattern->GetAttr<Color>("fg_progress_color", Color::RED);
            theme->loadingColor_ = pattern->GetAttr<Color>("fg_progress_color", Color::RED);
            theme->moonFrontColor_ = pattern->GetAttr<Color>("moon_progress_fg_color", Color::RED)
                .BlendOpacity(pattern->GetAttr<double>("moon_progress_fg_color_alpha", 1.0));
            theme->moonTrackBackgroundColor_ = pattern->GetAttr<Color>("moon_progress_bg_color", Color::RED)
                .BlendOpacity(pattern->GetAttr<double>("moon_progress_bg_color_alpha", 1.0))
                .BlendOpacity(pattern->GetAttr<double>("moon_progress_bg_color_alpha_ex", 1.0));
            theme->borderColor_ = pattern->GetAttr<Color>("progress_border_color", Color::RED)
                .BlendOpacity(pattern->GetAttr<double>("progress_border_color_alpha", 1.0));
            theme->maskColor_ = pattern->GetAttr<Color>("progress_mask_color", Color::RED);
            theme->borderWidth_ = pattern->GetAttr<Dimension>("progress_border_width", 1.0_vp);
            theme->fontScalePadding_ = pattern->GetAttr<Dimension>("progress_aging_padding_height", 8.0_vp);
            theme->fontScale_ = pattern->GetAttr<double>("progress_aging_font_scale", 1.75);
            theme->textColor_ = pattern->GetAttr<Color>("progress_text_color", defaultColor);
            theme->textSize_ = pattern->GetAttr<Dimension>("progress_text_size", 12.0_fp);
            theme->capsuleSelectColor_ = pattern->GetAttr<Color>("capsule_progress_select_color", Color::RED);
            theme->selectColorAlpha_ = pattern->GetAttr<double>("capsule_progress_default_alpha", 1.0);
            theme->capsuleSelectColor_ = theme->capsuleSelectColor_.BlendOpacity(theme->selectColorAlpha_);
            theme->progressDisable_ = pattern->GetAttr<double>("progress_disabled_alpha", 1.0);
            theme->clickEffect_ = pattern->GetAttr<Color>("progress_click_effect", Color::RED);
            theme->capsuleBgColor_ = pattern->GetAttr<Color>("capsule_progress_bg_color", Color::RED)
                .BlendOpacity(pattern->GetAttr<double>("capsule_progress_bg_alpha", 1.0));
            theme->ringProgressEndSideColor_ =
                pattern->GetAttr<Color>("ring_progress_fg_color_end", theme->trackSelectedColor_);
            theme->ringProgressBeginSideColor_ =
                pattern->GetAttr<Color>("ring_progress_fg_color_begin", theme->trackSelectedColor_);
            theme->ringProgressBackgroundColor_ =
                pattern->GetAttr<Color>("ring_progress_bg_color", Color::GRAY);
            theme->loadingFocusedColor_ =
                pattern->GetAttr<Color>("loading_progress_focused_color", theme->loadingColor_);
            theme->capsuleBgFocusedColor_ =
                pattern->GetAttr<Color>("capsule_progress_bg_focused_color", theme->capsuleBgColor_);
            theme->capsuleTextFocusedColor_ =
                pattern->GetAttr<Color>("capsule_progress_text_focused_color", theme->textColor_);
            theme->capsuleSelectFocusedColor_ =
                pattern->GetAttr<Color>("capsule_progress_select_focused_color", theme->capsuleSelectColor_)
                    .BlendOpacity(pattern->GetAttr<double>("capsule_progress_select_focused_color_alpha", 1.0));
            theme->capsuleInprogressBgColor_ =
                pattern->GetAttr<Color>("capsule_progress_bg_inprogress_color", theme->capsuleBgColor_)
                    .BlendOpacity(pattern->GetAttr<double>("capsule_progress_bg_inprogress_color_alpha", 1.0));
            theme->capsuleInprogressBorderColor_ =
                pattern->GetAttr<Color>("capsule_progress_inprogress_border_color", theme->borderColor_)
                    .BlendOpacity(pattern->GetAttr<double>("capsule_progress_inprogress_border_color_alpha", 1.0));
            theme->capsuleInprogressBorderWidth_ =
                pattern->GetAttr<Dimension>("capsule_progress_inprogress_border_width", theme->borderWidth_);
            theme->hoverBlendColor_ = pattern->GetAttr<Color>("progress_hover_blend_color", Color::TRANSPARENT);
            theme->capsuleHoverEffectType_ = static_cast<int32_t>(
                pattern->GetAttr<double>("capsule_progress_hover_effect_type", CAPSULE_HOVER_EFFECT_SCALE));
            theme->loadingDefaultSize_ = pattern->GetAttr<Dimension>("loading_progress_default_size", 0.0_vp);
            theme->textMargin_ = pattern->GetAttr<Dimension>("progress_text_margin", 8.0_vp);
            theme->ringDefaultPadding_ = pattern->GetAttr<Dimension>("ring_progress_default_padding", 0.0_vp);
            theme->capsuleFocusScale_ = pattern->GetAttr<double>("capsule_progress_focused_scale", 1.0);
            theme->capsuleFocusedShadowStyle_ = static_cast<int32_t>(
                pattern->GetAttr<double>("capsule_progress_focused_shadow_style", CAPSULE_NONE_SHADOW_VALUE));

            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
                theme->capsuleBgColor_ = theme->trackBgColor_;
                theme->capsuleSelectColor_ = theme->trackSelectedColor_;
                theme->ringProgressBackgroundColor_ = theme->trackBgColor_;
                theme->ringProgressBeginSideColor_ = theme->trackSelectedColor_;
                theme->ringProgressEndSideColor_ = theme->trackSelectedColor_;
            } else if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
                theme->capsuleSelectColor_ =
                    pattern->GetAttr<Color>("progress_select_color", Color::RED).BlendOpacity(theme->selectColorAlpha_);
                theme->borderColor_ = theme->capsuleSelectColor_;
                theme->ringProgressBackgroundColor_ = theme->trackBgColor_.ChangeOpacity(defaultRingBackgroundOpacity);
                theme->loadingColor_ = theme->loadingColor_.BlendOpacity(
                    pattern->GetAttr<double>("loading_progress_bg_color_alpha", defaultLoadBGAlpha));
            }
        }
    };

    ~ProgressTheme() override = default;

    const Dimension& GetTrackThickness() const
    {
        return trackThickness_;
    }

    const Dimension& GetTrackWidth() const
    {
        return trackWidth_;
    }

    const Dimension& GetRingThickness() const
    {
        return ringThickness_;
    }

    const Dimension& GetRingDiameter() const
    {
        return ringDiameter_;
    }

    const Color& GetTrackBgColor() const
    {
        return trackBgColor_;
    }

    const Color& GetTrackSelectedColor() const
    {
        return trackSelectedColor_;
    }

    Color GetTrackCachedColor() const
    {
        return trackCachedColor_;
    }

    const Dimension& GetLoadingDiameter() const
    {
        return loadingDiameter_;
    }

    const Color& GetLoadingColor() const
    {
        return loadingColor_;
    }

    const Dimension& GetScaleWidth() const
    {
        return scaleWidth_;
    }

    int32_t GetScaleNumber() const
    {
        return scaleNumber_;
    }

    const Dimension& GetScaleLength() const
    {
        return scaleLength_;
    }

    const Color& GetProgressColor() const
    {
        return progressColor_;
    }

    double GetMoveRatio() const
    {
        return moveRatio_;
    }

    const Dimension& GetRingRadius() const
    {
        return ringRadius_;
    }

    const Dimension& GetOrbitRadius() const
    {
        return orbitRadius_;
    }

    double GetCometTailLen() const
    {
        return cometTailLen_;
    }

    const Dimension& GetScaleRingDiameter() const
    {
        return scaleRingDiameter_;
    }

    const Dimension& GetMoonDiameter() const
    {
        return moonDiameter_;
    }

    const Color& GetMoonBackgroundColor() const
    {
        return moonTrackBackgroundColor_;
    }

    const Color& GetMoonFrontColor() const
    {
        return moonFrontColor_;
    }

    const Dimension& GetBubbleDiameter() const
    {
        return bubbleDiameter_;
    }

    const Dimension& GetBubbleRadius() const
    {
        return bubbleRadius_;
    }

    const Color& GetBorderColor() const
    {
        return borderColor_;
    }

    const Dimension& GetBorderWidth() const
    {
        return borderWidth_;
    }

    const Color& GetMaskColor() const
    {
        return maskColor_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Dimension& GetTextSize() const
    {
        return textSize_;
    }

    const Dimension& GetProgressHeight() const
    {
        return progressHeight_;
    }

    const Color& GetCapsuleSelectColor() const
    {
        return capsuleSelectColor_;
    }

    const float& GetProgressDisable() const
    {
        return progressDisable_;
    }

    const Color& GetClickEffect() const
    {
        return clickEffect_;
    }

    const float& GetSelectColorAlpha() const
    {
        return selectColorAlpha_;
    }

    const Dimension& GetTextMargin() const
    {
        return textMargin_;
    }

    float GetFontScale() const
    {
        return fontScale_;
    }
    
    const Dimension& GetfontScalePadding() const
    {
        return fontScalePadding_;
    }
    
    const Color& GetCapsuleBgColor() const
    {
        return capsuleBgColor_;
    }

    const Color& GetRingProgressEndSideColor() const
    {
        return ringProgressEndSideColor_;
    }

    const Color& GetRingProgressBeginSideColor() const
    {
        return ringProgressBeginSideColor_;
    }

    const Color& GetRingProgressBgColor() const
    {
        return ringProgressBackgroundColor_;
    }

    const Color& GetLoadingFocusedColor() const
    {
        return loadingFocusedColor_;
    }

    const Color& GetCapsuleBgFocusedColor() const
    {
        return capsuleBgFocusedColor_;
    }

    const Color& GetCapsuleTextFocusedColor() const
    {
        return capsuleTextFocusedColor_;
    }

    const Color& GetCapsuleSelectFocusedColor() const
    {
        return capsuleSelectFocusedColor_;
    }

    const Color& GetHoverBlendColor() const
    {
        return hoverBlendColor_;
    }

    const Color& GetCapsuleInprogressBgColor() const
    {
        return capsuleInprogressBgColor_;
    }

    const Color& GetCapsuleInprogressBorderColor() const
    {
        return capsuleInprogressBorderColor_;
    }

    const Dimension& GetCapsuleInprogressBorderWidth() const
    {
        return capsuleInprogressBorderWidth_;
    }

    const Dimension& GetLoadingDefaultSize() const
    {
        return loadingDefaultSize_;
    }

    const Dimension& GetRingDefaultPadding() const
    {
        return ringDefaultPadding_;
    }

    int32_t GetCapsuleHoverEffectType() const
    {
        return capsuleHoverEffectType_;
    }

    int32_t GetCapsuleFocusedShadowStyle() const
    {
        return capsuleFocusedShadowStyle_;
    }

    float GetCapsuleFocusScale() const
    {
        return capsuleFocusScale_;
    }

protected:
    ProgressTheme() = default;

private:
    Dimension trackThickness_;
    Dimension trackWidth_;
    Color trackBgColor_;
    Color trackSelectedColor_;
    Color trackCachedColor_;

    Dimension ringThickness_;
    Dimension ringDiameter_;
    Dimension bubbleDiameter_;
    Dimension bubbleRadius_;

    Dimension loadingDiameter_;
    Color loadingColor_;

    Dimension scaleWidth_;
    int32_t scaleNumber_ = 0;
    Dimension scaleLength_;
    Dimension scaleRingDiameter_;

    Dimension moonDiameter_;
    Color moonTrackBackgroundColor_;
    Color moonFrontColor_;

    // For loading progress in cycle type.
    Color progressColor_;
    double moveRatio_ = 0.0;
    Dimension ringRadius_;
    Dimension orbitRadius_;
    double cometTailLen_ = 0.0;

    Color borderColor_;
    Dimension borderWidth_;
    Color maskColor_;

    // For capsule progress.
    Color textColor_;
    Dimension textSize_;
    Dimension progressHeight_;
    Color capsuleSelectColor_;
    float progressDisable_ = 0.4;
    Color clickEffect_;
    float selectColorAlpha_ = 1.0f;
    Dimension textMargin_ = 8.0_vp;
    Color capsuleBgFocusedColor_;
    Color capsuleTextFocusedColor_;
    Color capsuleSelectFocusedColor_;
    Color hoverBlendColor_;
    Color capsuleInprogressBgColor_;
    Color capsuleInprogressBorderColor_;
    Color loadingFocusedColor_;
    Dimension loadingDefaultSize_;
    Dimension ringDefaultPadding_;
    Dimension capsuleInprogressBorderWidth_;
    int32_t capsuleHoverEffectType_;
    int32_t capsuleFocusedShadowStyle_;
    float capsuleFocusScale_ = 1.0f;
    Color capsuleBgColor_;

    // For ring progress.
    Color ringProgressEndSideColor_;
    Color ringProgressBeginSideColor_;
    Color ringProgressBackgroundColor_;
    float fontScale_ = 1.75f;
    Dimension fontScalePadding_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PROGRESS_PROGRESS_THEME_H
