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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_BAR_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_BAR_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

class NavigationBarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(NavigationBarTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<NavigationBarTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<NavigationBarTheme> theme = AceType::Claim(new NavigationBarTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->titleColor_ = themeConstants->GetColor(THEME_NAVIGATION_BAR_TITLE_COLOR);
            theme->titleFontSize_ = Dimension(
                themeConstants->GetDimension(THEME_NAVIGATION_BAR_TITLE_FONT_SIZE).Value(), DimensionUnit::VP);
            theme->titleFontSizeBig_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_TITLE_FONT_SIZE_BIG);
            theme->subTitleColor_ = themeConstants->GetColor(THEME_NAVIGATION_BAR_SUBTITLE_COLOR);
            theme->subTitleFontSize_ = Dimension(
                themeConstants->GetDimension(THEME_NAVIGATION_BAR_SUBTITLE_FONT_SIZE).Value(), DimensionUnit::VP);
            theme->height_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_HEIGHT);
            theme->heightEmphasize_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_HEIGHT_EMPHASIZE);
            theme->backResourceId_ = themeConstants->GetResourceId(THEME_NAVIGATION_BAR_RESOURCE_ID_BACK);
            theme->moreResourceId_ = themeConstants->GetResourceId(THEME_NAVIGATION_BAR_RESOURCE_ID_MORE);
            theme->menuZoneSize_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_MENU_ZONE_SIZE);
            theme->menuIconSize_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_MENU_ICON_SIZE);
            theme->logoIconSize_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_LOGO_ICON_SIZE);
            theme->buttonNormalColor_ = themeConstants->GetColor(THEME_NAVIGATION_BAR_BUTTON_NORMAL_COLOR);
            theme->buttonPressedColor_ = themeConstants->GetColor(THEME_NAVIGATION_BAR_BUTTON_PRESSED_COLOR);
            theme->buttonFocusColor_ = themeConstants->GetColor(THEME_NAVIGATION_BAR_BUTTON_FOCUS_COLOR);
            theme->buttonCornerRadius_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_BUTTON_CORNER_RADIUS);
            theme->maxPaddingStart_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_MAX_PADDING_START);
            theme->maxPaddingEnd_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_MAX_PADDING_END);
            theme->defaultPaddingStart_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_DEFAULT_PADDING_START);
            theme->defaultPaddingEnd_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_DEFAULT_PADDING_END);
            theme->menuItemPadding_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_MENU_ITEM_PADDING);
            theme->titleMinPadding_ = themeConstants->GetDimension(THEME_NAVIGATION_BAR_TITLE_MIN_PADDING);
            auto menuCount = themeConstants->GetInt(THEME_NAVIGATION_BAR_MOST_MENU_ITEM_COUNT_IN_BAR);
            theme->mostMenuItemCountInBar_ =
                menuCount < 0 ? theme->mostMenuItemCountInBar_ : static_cast<uint32_t>(menuCount);

            auto themeStyle = themeConstants->GetThemeStyle();
            if (!themeStyle) {
                return theme;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_NAVIGATION_BAR, nullptr);
            if (pattern) {
                theme->titleColor_ = pattern->GetAttr<Color>("title_color", Color::WHITE);
                theme->titleFontSize_  = pattern->GetAttr<Dimension>("title_text_font_size", 0.0_vp);
                theme->titleFontSizeMin_ = pattern->GetAttr<Dimension>("title_text_font_size_min", 0.0_vp);
                theme->titleFontSizeBig_  = pattern->GetAttr<Dimension>("title_text_font_size_big", 0.0_vp);
                theme->subTitleColor_ = pattern->GetAttr<Color>("sub_title_text_color", Color::WHITE);
                theme->subTitleFontSize_  = pattern->GetAttr<Dimension>("sub_title_text_font_size", 0.0_vp);
                theme->menuIconColor_ = pattern->GetAttr<Color>("menu_icon_color", Color::WHITE);
                theme->buttonPressedColor_ = pattern->GetAttr<Color>("button_bg_color_pressed", Color::WHITE);
                theme->buttonFocusColor_ = pattern->GetAttr<Color>("button_bg_color_focused", Color::WHITE);
                theme->buttonHoverColor_ = pattern->GetAttr<Color>("button_bg_color_hovered", Color::WHITE);
                theme->buttonCornerRadius_  = pattern->GetAttr<Dimension>("button_corner_radius", 0.0_vp);
                theme->maxPaddingStart_ = pattern->GetAttr<Dimension>("title_left_spacing", 0.0_vp);
                theme->maxPaddingEnd_ = pattern->GetAttr<Dimension>("title_right_spacing", 0.0_vp);
                theme->defaultPaddingStart_ = pattern->GetAttr<Dimension>("back_button_left_spacing", 0.0_vp);
                theme->backButtonIconColor_ = pattern->GetAttr<Color>("back_button_icon_color", Color::WHITE);
                theme->alphaDisabled_ = pattern->GetAttr<double>("button_alpha_disabled", 0.0);
            }
            return theme;
        }
    };

    ~NavigationBarTheme() override = default;

    const Color& GetTitleColor() const
    {
        return titleColor_;
    }

    const Color& GetSubTitleColor() const
    {
        return subTitleColor_;
    }
    const Dimension& GetTitleFontSizeBig() const
    {
        return titleFontSizeBig_;
    }

    const Dimension& GetTitleFontSize() const
    {
        return titleFontSize_;
    }

    const Dimension& GetTitleFontSizeMin() const
    {
        return titleFontSizeMin_;
    }

    const Dimension& GetSubTitleFontSize() const
    {
        return subTitleFontSize_;
    }
    const Dimension& GetHeight() const
    {
        return height_;
    }
    const Dimension& GetHeightEmphasize() const
    {
        return heightEmphasize_;
    }
    InternalResource::ResourceId GetBackResourceId() const
    {
        return backResourceId_;
    }
    InternalResource::ResourceId GetMoreResourceId() const
    {
        return moreResourceId_;
    }
    const Dimension& GetMenuZoneSize() const
    {
        return menuZoneSize_;
    }
    const Dimension& GetMenuIconSize() const
    {
        return menuIconSize_;
    }
    const Dimension& GetLogoIconSize() const
    {
        return logoIconSize_;
    }
    const Color& GetMenuIconColor() const
    {
        return menuIconColor_;
    }
    const Color& GetButtonNormalColor() const
    {
        return buttonNormalColor_;
    }
    const Color& GetButtonPressedColor() const
    {
        return buttonPressedColor_;
    }
    const Color& GetButtonFocusColor() const
    {
        return buttonFocusColor_;
    }
    const Color& GetButtonHoverColor() const
    {
        return buttonHoverColor_;
    }
    const Dimension& GetButtonCornerRadius() const
    {
        return buttonCornerRadius_;
    }
    const Dimension& GetMaxPaddingStart() const
    {
        return maxPaddingStart_;
    }
    const Dimension& GetDefaultPaddingStart() const
    {
        return defaultPaddingStart_;
    }
    const Dimension& GetDefaultPaddingEnd() const
    {
        return defaultPaddingEnd_;
    }
    const Dimension& GetMaxPaddingEnd() const
    {
        return maxPaddingEnd_;
    }
    const Dimension& GetMenuItemPadding() const
    {
        return menuItemPadding_;
    }
    const Dimension& GetTitleMinPadding() const
    {
        return titleMinPadding_;
    }
    uint32_t GetMostMenuItemCountInBar() const
    {
        return mostMenuItemCountInBar_;
    }
    const Color& GetBackButtonIconColor() const
    {
        return backButtonIconColor_;
    }
    double GetAlphaDisabled() const
    {
        return alphaDisabled_;
    }

protected:
    NavigationBarTheme() = default;

private:
    Color titleColor_;
    Color subTitleColor_;
    Dimension titleFontSizeBig_;
    Dimension titleFontSize_;
    Dimension titleFontSizeMin_;
    Dimension subTitleFontSize_;
    Dimension height_;
    Dimension heightEmphasize_;
    InternalResource::ResourceId backResourceId_ = InternalResource::ResourceId::NO_ID;
    InternalResource::ResourceId moreResourceId_ = InternalResource::ResourceId::NO_ID;
    Dimension menuZoneSize_;
    Dimension menuIconSize_;
    Dimension logoIconSize_;
    Color menuIconColor_;
    Color buttonNormalColor_;
    Color buttonPressedColor_;
    Color buttonFocusColor_;
    Color buttonHoverColor_;
    Dimension buttonCornerRadius_;
    Dimension maxPaddingStart_;
    Dimension maxPaddingEnd_;
    Dimension defaultPaddingStart_;
    Dimension defaultPaddingEnd_;
    Dimension menuItemPadding_;
    Dimension titleMinPadding_;
    uint32_t mostMenuItemCountInBar_ = 0;
    Color backButtonIconColor_;
    double alphaDisabled_ = 0.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_BAR_THEME_H
