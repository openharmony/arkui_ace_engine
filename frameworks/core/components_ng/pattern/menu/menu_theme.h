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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H

#include <cstdint>

#include "core/components/theme/theme.h"
#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace::NG {
constexpr Dimension GRADIENT_HEIGHT = Dimension(50, DimensionUnit::VP);

constexpr uint8_t GRADIENT_END_GRADIENT = 255;
constexpr uint32_t DEFAULT_BACKGROUND_COLOR = 0xFFFFFFF;
constexpr uint32_t MENU_MIN_GRID_COUNTS = 2;
constexpr uint32_t MENU_MAX_GRID_COUNTS = 6;
constexpr int32_t HOVER_IMAGE_OPACITY_CHANGE_DURATION = 150;
constexpr int32_t HOVER_IMAGE_DELAY_DURATION = 200;
constexpr int32_t HOVER_IMAGE_CUSTOM_PREVIEW_SCALE_DURATION = 650;
constexpr int32_t HOVER_IMAGE_PREVIEW_DISAPPEAR_DURATION = 450;
constexpr double OUTBORDER_RADIUS = 19.75; // Default value of outBorderRadius
constexpr float MENU_BIG_FONT_SIZE_SCALE = 1.75f;
constexpr float MENU_LARGE_FONT_SIZE_SCALE_ = 2.0f;
constexpr float MENU_MAX_FONT_SIZE_SCALE = 3.2f;
constexpr int32_t MENU_TEXT_MAX_LINES = std::numeric_limits<int32_t>::max();

/**
 * MenuTheme defines styles of menu item. MenuTheme should be built
 * using MenuTheme::Builder.
 */
class MenuTheme : public virtual Theme {
    DECLARE_ACE_TYPE(MenuTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<MenuTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<MenuTheme> theme = AceType::Claim(new MenuTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->symbolId_ = themeConstants->GetSymbolByName("sys.symbol.checkmark");
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<MenuTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_SELECT, nullptr);
            if (!pattern) {
                LOGE("Pattern of menu is null, please check!");
                return;
            }
            theme->previewMenuMaskColor_ = pattern->GetAttr<Color>("preview_menu_mask_color", Color(0x33182431));
            theme->bgBlurEffectEnable_ =
                StringUtils::StringToInt(pattern->GetAttr<std::string>("menu_bg_blur_effect_enable", "0"));
            theme->bgEffectSaturation_ = pattern->GetAttr<double>("menu_blur_effect_saturation", 1.0);
            theme->bgEffectBrightness_ = pattern->GetAttr<double>("menu_blur_effect_brightness", 1.0);
            theme->bgEffectRadius_ = pattern->GetAttr<Dimension>("menu_blur_effect_radius", 0.0_vp);
            theme->bgEffectColor_ = pattern->GetAttr<Color>("menu_blur_effect_color", Color::TRANSPARENT);
            theme->doubleBorderEnable_ =
                StringUtils::StringToInt(pattern->GetAttr<std::string>("menu_double_border_enable", "0"));
            theme->outerBorderWidth_ = pattern->GetAttr<double>("menu_outer_border_width", 1.0);
            theme->outerBorderRadius_ = pattern->GetAttr<double>("menu_outer_border_radius", OUTBORDER_RADIUS);
            theme->outerBorderColor_ = pattern->GetAttr<Color>("menu_outer_border_color", Color::TRANSPARENT);
            theme->innerBorderWidth_ = pattern->GetAttr<double>("menu_inner_border_width", 1.0);
            theme->innerBorderRadius_ = pattern->GetAttr<Dimension>("menu_inner_border_radius", 0.0_vp);
            theme->innerBorderColor_ = pattern->GetAttr<Color>("menu_inner_border_color", Color::TRANSPARENT);
            theme->filterAnimationDuration_ = 250;
            theme->previewAnimationDuration_ = 300;
            theme->hoverImageSwitchToPreviewOpacityDuration_ = HOVER_IMAGE_OPACITY_CHANGE_DURATION;
            theme->hoverImageDelayDuration_ = HOVER_IMAGE_DELAY_DURATION;
            theme->hoverImageCustomPreviewScaleDuration_ = HOVER_IMAGE_CUSTOM_PREVIEW_SCALE_DURATION;
            theme->hoverImagePreviewDisappearDuration_ = HOVER_IMAGE_PREVIEW_DISAPPEAR_DURATION;
            theme->previewBeforeAnimationScale_ = 0.95f;
            theme->previewAfterAnimationScale_ = 1.1f;
            theme->menuAnimationScale_ = 0.4f;
            theme->menuDragAnimationScale_ = 0.95f;
            theme->springMotionResponse_ = 0.416f;
            theme->springMotionDampingFraction_ = 0.73f;
            theme->contextMenuAppearDuration_ = 250;
            theme->disappearDuration_ = 250;
            theme->previewDisappearSpringMotionResponse_ = 0.304f;
            theme->previewDisappearSpringMotionDampingFraction_ = 0.97f;
            theme->filterRadius_ = Dimension(100.0f);
            theme->previewBorderRadius_ = 16.0_vp;
            theme->previewMenuScaleNumber_ = 0.95f;
            std::string hasFilter = pattern->GetAttr<std::string>("menu_has_filter", "true");
            theme->hasFilter_ = (hasFilter == "true");
            theme->bigFontSizeScale_ = MENU_BIG_FONT_SIZE_SCALE;
            theme->largeFontSizeScale_ = MENU_LARGE_FONT_SIZE_SCALE_;
            theme->maxFontSizeScale_ = MENU_MAX_FONT_SIZE_SCALE;
            theme->textMaxLines_ = MENU_TEXT_MAX_LINES;
            theme->normalLayout_ = pattern->GetAttr<int>("menu_normal_layout", 1);
            theme->normalPlacement_ = pattern->GetAttr<int>("menu_normal_placement", 1);
            theme->hasBackBlur_ = pattern->GetAttr<int>("menu_back_blur", 1);
            theme->enableDirectionalKeyFocus_ = pattern->GetAttr<int>("menu_focus_directional_key_enable", 0);
            theme->menuShadowStyle_ = static_cast<ShadowStyle>(
                pattern->GetAttr<int>("menu_default_shadow_style", static_cast<int>(ShadowStyle::OuterDefaultMD)));
            theme->menuBackGroundBlurStyle_ =
                pattern->GetAttr<int>("menu_background_blur_style", static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK));
            ParseWideScreenAttrs(theme, pattern);
        }

        void ParseWideScreenAttrs(const RefPtr<MenuTheme>& theme, const RefPtr<ThemeStyle>& pattern) const
        {
            theme->hasBackBlurColor_ = static_cast<bool>(pattern->GetAttr<double>("menu_back_blur_with_color", 0.0f));
            theme->backBlurColor_ = pattern->GetAttr<Color>("menu_back_blur_color", Color::TRANSPARENT);
            theme->borderWidth_ = pattern->GetAttr<Dimension>("menu_border_width", 0.0_vp);
            theme->borderColor_ = pattern->GetAttr<Color>("menu_border_color", Color::BLACK);
            theme->focusStyleType_ = pattern->GetAttr<double>("menu_focus_style_type", 0.0);
        }
    };

    ~MenuTheme() override = default;

    uint32_t GetSymbolId() const
    {
        return symbolId_;
    }

    int32_t GetFilterAnimationDuration() const
    {
        return filterAnimationDuration_;
    }

    int32_t GetPreviewAnimationDuration() const
    {
        return previewAnimationDuration_;
    }

    int32_t GetHoverImageSwitchToPreviewOpacityDuration() const
    {
        return hoverImageSwitchToPreviewOpacityDuration_;
    }

    int32_t GetHoverImageDelayDuration() const
    {
        return hoverImageDelayDuration_;
    }

    int32_t GetHoverImageCustomPreviewScaleDuration() const
    {
        return hoverImageCustomPreviewScaleDuration_;
    }

    int32_t GetHoverImagePreviewDisAppearDuration() const
    {
        return hoverImagePreviewDisappearDuration_;
    }

    float GetPreviewBeforeAnimationScale() const
    {
        return previewBeforeAnimationScale_;
    }

    float GetPreviewAfterAnimationScale() const
    {
        return previewAfterAnimationScale_;
    }

    float GetMenuAnimationScale() const
    {
        return menuAnimationScale_;
    }

    float GetMenuDragAnimationScale() const
    {
        return menuDragAnimationScale_;
    }

    float GetSpringMotionResponse() const
    {
        return springMotionResponse_;
    }

    float GetSpringMotionDampingFraction() const
    {
        return springMotionDampingFraction_;
    }

    int32_t GetContextMenuAppearDuration() const
    {
        return contextMenuAppearDuration_;
    }

    int32_t GetDisappearDuration() const
    {
        return disappearDuration_;
    }

    float GetPreviewDisappearSpringMotionResponse() const
    {
        return previewDisappearSpringMotionResponse_;
    }

    float GetPreviewDisappearSpringMotionDampingFraction() const
    {
        return previewDisappearSpringMotionDampingFraction_;
    }

    float GetPreviewMenuScaleNumber() const
    {
        return previewMenuScaleNumber_;
    }

    Dimension GetFilterRadius() const
    {
        return filterRadius_;
    }

    Dimension GetPreviewBorderRadius() const
    {
        return previewBorderRadius_;
    }

    Color GetPreviewMenuMaskColor() const
    {
        return previewMenuMaskColor_;
    }

    int32_t GetBgBlurEffectEnable() const
    {
        return bgBlurEffectEnable_;
    }

    double GetBgEffectSaturation() const
    {
        return bgEffectSaturation_;
    }

    double GetBgEffectBrightness() const
    {
        return bgEffectBrightness_;
    }

    Dimension GetBgEffectRadius() const
    {
        return bgEffectRadius_;
    }

    Color GetBgEffectColor() const
    {
        return bgEffectColor_;
    }

    int32_t GetDoubleBorderEnable() const
    {
        return doubleBorderEnable_;
    }

    double GetOuterBorderWidth() const
    {
        return outerBorderWidth_;
    }

    double GetOuterBorderRadius() const
    {
        return outerBorderRadius_;
    }

    Color GetOuterBorderColor() const
    {
        return outerBorderColor_;
    }

    double GetInnerBorderWidth() const
    {
        return innerBorderWidth_;
    }

    Dimension GetInnerBorderRadius() const
    {
        return innerBorderRadius_;
    }

    Color GetInnerBorderColor() const
    {
        return innerBorderColor_;
    }

    bool GetHasFilter() const
    {
        return hasFilter_;
    }

    float GetBigFontSizeScale() const
    {
        return bigFontSizeScale_;
    }

    float GetLargeFontSizeScale() const
    {
        return largeFontSizeScale_;
    }

    float GetMaxFontSizeScale() const
    {
        return maxFontSizeScale_;
    }

    int32_t GetTextMaxLines() const
    {
        return textMaxLines_;
    }

    bool GetNormalLayout() const
    {
        return normalLayout_;
    }

    bool GetNormalPlacement() const
    {
        return normalPlacement_;
    }

    bool GetHasBackBlur() const
    {
        return hasBackBlur_;
    }

    bool GetEnableDirectionalKeyFocus() const
    {
        return enableDirectionalKeyFocus_;
    }

    Color GetBorderColor() const
    {
        return borderColor_;
    }

    bool HasBackBlurColor() const
    {
        return hasBackBlurColor_;
    }

    Color GetBackBlurColor() const
    {
        return backBlurColor_;
    }

    Dimension GetBorderWidth() const
    {
        return borderWidth_;
    }

    double GetFocusStyleType() const
    {
        return focusStyleType_;
    }

    ShadowStyle GetMenuShadowStyle() const
    {
        return menuShadowStyle_;
    }
    
    int GetMenuBackgroundBlurStyle() const
    {
        return menuBackGroundBlurStyle_;
    }

protected:
    MenuTheme() = default;

private:
    int32_t filterAnimationDuration_ = 0;
    int32_t previewAnimationDuration_ = 0;
    int32_t hoverImageSwitchToPreviewOpacityDuration_ = 0;
    int32_t hoverImageDelayDuration_ = 0;
    int32_t hoverImageCustomPreviewScaleDuration_ = 0;
    int32_t hoverImagePreviewDisappearDuration_ = 0;
    float previewBeforeAnimationScale_ = 1.0f;
    float previewAfterAnimationScale_ = 1.0f;
    float menuAnimationScale_ = 1.0f;
    float menuDragAnimationScale_ = 1.0f;
    float springMotionResponse_ = 0.0f;
    float springMotionDampingFraction_ = 0.0f;
    int32_t contextMenuAppearDuration_ = 0;
    int32_t disappearDuration_ = 0;
    float previewDisappearSpringMotionResponse_ = 0.0f;
    float previewDisappearSpringMotionDampingFraction_ = 0.0f;
    float previewMenuScaleNumber_ = 0.0f;
    Dimension filterRadius_;
    Dimension previewBorderRadius_;
    Color previewMenuMaskColor_;
    int32_t bgBlurEffectEnable_ = 0;
    double bgEffectSaturation_ = 1.0f;
    double bgEffectBrightness_ = 1.0f;
    Dimension bgEffectRadius_;
    Color bgEffectColor_ = Color::TRANSPARENT;
    int32_t doubleBorderEnable_ = 0;
    double outerBorderWidth_ = 1.0f;
    double outerBorderRadius_ = 19.75f;
    Color outerBorderColor_ = Color::TRANSPARENT;
    double innerBorderWidth_ = 1.0f;
    Dimension innerBorderRadius_;
    Color innerBorderColor_ = Color::TRANSPARENT;
    uint32_t symbolId_;
    bool hasFilter_ = true;
    float bigFontSizeScale_ = 1.75f;
    float largeFontSizeScale_ = 2.0f;
    float maxFontSizeScale_ = 3.2f;
    int32_t textMaxLines_ = std::numeric_limits<int32_t>::max();
    bool normalLayout_ = true;
    bool normalPlacement_ = true;
    bool hasBackBlur_ = true;
    bool enableDirectionalKeyFocus_ = false;
    bool hasBackBlurColor_ = false;
    Dimension borderWidth_;
    Color backBlurColor_ = Color::TRANSPARENT;
    Color borderColor_ = Color::TRANSPARENT;
    double focusStyleType_ = 0.0;
    ShadowStyle menuShadowStyle_ = ShadowStyle::OuterDefaultMD;
    int menuBackGroundBlurStyle_ = static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_THEME_H
