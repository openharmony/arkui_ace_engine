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

#include <cstdint>
#include "base/utils/string_utils.h"
#include "core/common/container.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components_ng/property/border_property.h"

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
            SetSymbolTheme(themeConstants, theme);
            theme->backBtnResourceId_ = InternalResource::ResourceId::TITLEBAR_BACK;
            theme->backResourceId_ = themeConstants->GetResourceId(THEME_NAVIGATION_BAR_RESOURCE_ID_BACK);
            theme->moreResourceId_ = themeConstants->GetResourceId(THEME_NAVIGATION_BAR_RESOURCE_ID_MORE);
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_NAVIGATION_BAR);
            if (pattern) {
                theme->height_ = pattern->GetAttr<Dimension>("navigation_bar_height", 0.0_vp);
                theme->heightEmphasize_ = pattern->GetAttr<Dimension>("navigation_bar_height_emphasize", 0.0_vp);
                theme->menuZoneSize_ = pattern->GetAttr<Dimension>("navigation_bar_menu_zone_size", 0.0_vp);
                theme->menuIconSize_ = pattern->GetAttr<Dimension>("navigation_bar_menu_icon_size", 0.0_vp);
                theme->logoIconSize_ = pattern->GetAttr<Dimension>("navigation_bar_logo_icon_size", 0.0_vp);
                theme->buttonNormalColor_ = pattern->GetAttr<Color>("navigation_bar_button_normal_color", Color());
                theme->defaultPaddingEnd_ = pattern->GetAttr<Dimension>("navigation_bar_default_padding_end", 0.0_vp);
                theme->menuItemPadding_ = pattern->GetAttr<Dimension>("navigation_bar_menu_item_padding", 0.0_vp);
                theme->titleMinPadding_ = pattern->GetAttr<Dimension>("navigation_bar_title_min_padding", 0.0_vp);
                auto menuCount =
                    static_cast<int32_t>(pattern->GetAttr<double>("navigation_bar_most_menu_item_count_in_bar", 0.0));
                theme->mostMenuItemCountInBar_ =
                    menuCount < 0 ? theme->mostMenuItemCountInBar_ : static_cast<uint32_t>(menuCount);
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
                auto dividerShadowEnable = pattern->GetAttr<std::string>("divider_shadow_enable", "0");
                theme->dividerShadowEnable_ = static_cast<uint32_t>(StringUtils::StringToInt(dividerShadowEnable));
                theme->navigationGroupColor_ = pattern->GetAttr<Color>("navigation_group_color", Color::TRANSPARENT);
                auto navBarUnfocusEffectEnable = pattern->GetAttr<std::string>("section_unfocus_effect_enable", "0");
                theme->navBarUnfocusEffectEnable_ = static_cast<uint32_t>(
                    StringUtils::StringToInt(navBarUnfocusEffectEnable));
                theme->navBarUnfocusColor_ = pattern->GetAttr<Color>("color_panel_bg", Color::TRANSPARENT);
                theme->titlebarBackgroundBlurStyle_ = pattern->GetAttr<int>("titlebar_background_blur_style", 0);
                theme->toolbarBackgroundBlurStyle_ = pattern->GetAttr<int>("toolbar_background_blur_style", 0);
                theme->moreMessage_ = pattern->GetAttr<std::string>("navigation_general_more", "null");
            }
            ParsePattern(themeConstants, theme);
            return theme;
        }

    private:
        void SetSymbolTheme(const RefPtr<ThemeConstants>& themeConstants, RefPtr<NavigationBarTheme>& theme) const
        {
            theme->backSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_backward");
            theme->moreSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.dot_grid_2x2");
        }
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<NavigationBarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_NAVIGATION_BAR);
            if (!pattern) {
                return;
            }
            theme->toolbarBgColor_ = pattern->GetAttr<Color>("toolbar_bg_color", Color(0xfff1f3f5));
            theme->toolbarBgColorWithOpacity_ = theme->toolbarBgColor_.BlendOpacity(theme->toolbarBgAlpha_);
            theme->toolbarDividerWidth_ = Dimension(1.0, DimensionUnit::PX);
            theme->toolbarDividerColor_ = pattern->GetAttr<Color>("toolbar_divider_color", Color(0x33182431));
            theme->toolbarItemFocusBorderColor_ =
                pattern->GetAttr<Color>("toolbar_item_focus_color", Color(0xff007dff));
            theme->toolbarItemBorderRadiusValue_ =
                pattern->GetAttr<Dimension>("toolbar_item_bg_button_border_radius", 8.0_vp);
            theme->toolbarItemBorderRadius_.SetRadius(theme->toolbarItemBorderRadiusValue_);
            theme->toolbarItemFontSize_ = pattern->GetAttr<Dimension>("toolbar_item_font_size", 10.0_vp);
            theme->toolbarItemFontColor_ = pattern->GetAttr<Color>("toolbar_item_font_color", Color(0x182431));
            theme->toolbarIconColor_ = pattern->GetAttr<Color>("toolbar_item_icon_color", Color(0x182431));
            theme->toolbarActiveIconColor_ =
                pattern->GetAttr<Color>("toolbar_item_active_icon_color", Color(0xff007dff));
            theme->toolbarActiveTextColor_ =
                pattern->GetAttr<Color>("toolbar_item_active_text_color", Color(0xff007dff));
            auto dividerShadowEnable = pattern->GetAttr<std::string>("divider_shadow_enable", "0");
            theme->dividerShadowEnable_ = static_cast<uint32_t>(StringUtils::StringToInt(dividerShadowEnable));
            theme->navigationDividerColor_ = pattern->GetAttr<Color>("navigation_divider_color", Color(0x33000000));
            theme->navigationGroupColor_ = pattern->GetAttr<Color>("navigation_group_color", Color::TRANSPARENT);
            auto navBarUnfocusEffectEnable = pattern->GetAttr<std::string>("section_unfocus_effect_enable", "0");
            theme->navBarUnfocusEffectEnable_ = static_cast<uint32_t>(
                StringUtils::StringToInt(navBarUnfocusEffectEnable));
            theme->navBarUnfocusColor_ = pattern->GetAttr<Color>("color_panel_bg", Color::TRANSPARENT);
            theme->backgroundBlurColor_ = pattern->GetAttr<Color>("background_blur_color", Color(0x19E6E6E6));
            theme->mainTitleFontColor_ = pattern->GetAttr<Color>("title_primary_color", Color(0xe5000000));
            theme->subTitleFontColor_ = pattern->GetAttr<Color>("title_subheader_color", Color(0x99000000));
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
                SetToolBarTheme(pattern, theme);
                SetNavigationTokenTheme(pattern, theme);
            }
            ParsePatternContinue(themeConstants, theme);
        }

        void SetToolBarTheme(RefPtr<ThemeStyle> pattern, const RefPtr<NavigationBarTheme>& theme) const
        {
            theme->toolbarItemFocusBorderWidth_ =
                pattern->GetAttr<Dimension>("toolbar_item_focus_border_size_api_sixteen", 2.0_vp);
            theme->toolbarItemFocusBorderColor_ =
                pattern->GetAttr<Color>("toolbar_item_focus_color_api_sixteen", Color(0x007dff));
            theme->toolbarItemFontSize_ = pattern->GetAttr<Dimension>("toolbar_item_font_size_api_sixteen", 10.0_fp);
            theme->toolbarItemFontColor_ =
                pattern->GetAttr<Color>("toolbar_item_font_color_api_sixteen", Color(0x66182431));
            theme->toolbarItemBorderRadiusValue_ =
                pattern->GetAttr<Dimension>("toolbar_item_bg_button_border_radius_api_sixteen", 12.0_vp);
            theme->toolbarItemBorderRadius_.SetRadius(theme->toolbarItemBorderRadiusValue_);
            theme->toolbarIconColor_ =
                pattern->GetAttr<Color>("toolbar_item_icon_color_api_sixteen", Color(0x66182431));
            theme->toolbarActiveIconColor_ =
                pattern->GetAttr<Color>("toolbar_item_active_icon_color_api_sixteen", Color(0xff007dff));
            theme->toolbarActiveTextColor_ =
                pattern->GetAttr<Color>("toolbar_item_active_text_color_api_sixteen", Color(0xff007dff));
            theme->toolbarItemHeight_ = 44.0_vp;
            theme->toolbarHeight_ = 48.0_vp;
            theme->toolbarItemHorizontalPadding_ = 4.0_vp;
            theme->toolbarItemVerticalPadding_ = 4.0_vp;
            theme->toolbarItemTopPadding_ = 2.0_vp;
            theme->toolbarItemLeftOrRightPadding_ = 2.0_vp;
            theme->toolbarItemBottomPadding_ = 2.0_vp;
        }

        void SetNavigationTokenTheme(RefPtr<ThemeStyle> pattern, const RefPtr<NavigationBarTheme>& theme) const
        {
            theme->titleColor_ = pattern->GetAttr<Color>("title_color_api_sixteen", Color::WHITE);
            theme->subTitleColor_ = pattern->GetAttr<Color>("sub_title_text_color_api_sixteen", Color::WHITE);
            theme->menuIconColor_ = pattern->GetAttr<Color>("menu_icon_color_api_sixteen", Color::WHITE);
            theme->buttonPressedColor_ = pattern->GetAttr<Color>("button_bg_color_pressed_api_sixteen", Color::WHITE);
            theme->buttonFocusColor_ = pattern->GetAttr<Color>("button_bg_color_focused_api_sixteen", Color::WHITE);
            theme->buttonHoverColor_ = pattern->GetAttr<Color>("button_bg_color_hovered_api_sixteen", Color::WHITE);
            theme->backButtonIconColor_ = pattern->GetAttr<Color>("back_button_icon_color_api_sixteen", Color::WHITE);
            theme->toolbarBgColor_ = pattern->GetAttr<Color>("toolbar_bg_color_api_sixteen", Color(0xfff1f3f5));
            theme->toolbarDividerColor_ =
                pattern->GetAttr<Color>("toolbar_divider_color_api_sixteen", Color(0x33182431));
            theme->navigationDividerColor_ =
                pattern->GetAttr<Color>("navigation_divider_color_api_sixteen", Color(0x33000000));
        }

        void ParsePatternContinue(const RefPtr<ThemeConstants>& themeConstants,
            const RefPtr<NavigationBarTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_NAVIGATION_BAR);
            if (!pattern) {
                return;
            }
            theme->compBackgroundColor_ =
                pattern->GetAttr<Color>("icon_background_color", Color(0x0c000000));
            theme->iconColor_ = pattern->GetAttr<Color>("icon_color", Color(0xe5000000));
            theme->marginLeft_ = pattern->GetAttr<Dimension>("title_margin_left", 16.0_vp);
            theme->marginLeftForBackButton_ = pattern->GetAttr<Dimension>("backbutton_margin_left", 16.0_vp);
            theme->marginRight_ = pattern->GetAttr<Dimension>("title_margin_right", 16.0_vp);
            theme->marginRightForMenu_ = pattern->GetAttr<Dimension>("menu_margin_right", 16.0_vp);
            theme->mainTitleFontSizeL_ = pattern->GetAttr<Dimension>("title_primary_size", 30.0_fp);
            theme->mainTitleFontSizeM_ = pattern->GetAttr<Dimension>("title_secondary_size", 26.0_fp);
            theme->mainTitleFontSizeS_ = pattern->GetAttr<Dimension>("title_tertiary_size", 20.0_fp);
            theme->subTitleFontSizeS_ = pattern->GetAttr<Dimension>("title_subheader_size", 14.0_fp);
            theme->cornerRadius_ = pattern->GetAttr<Dimension>("icon_background_shape", 20.0_vp);
            theme->compPadding_ = pattern->GetAttr<Dimension>("icon_background_space_horizontal", 8.0_vp);
            constexpr double mainTitleDefaultFontWeit = 6.0; // 6.0 is main title default fontweight:FontWeight::W700
            theme->mainTitleFontWeight_ = FontWeight(static_cast<int32_t>(
                pattern->GetAttr<double>("title_primary_weight", mainTitleDefaultFontWeit)));
            constexpr double subTitleDefaultFontWeit = 3.0; // 3.0 is sub title default fontweight:FontWeight::W400
            theme->subTitleFontWeight_ = FontWeight(static_cast<int32_t>(
                pattern->GetAttr<double>("title_subheader_weight", subTitleDefaultFontWeit)));
            theme->iconWidth_ = pattern->GetAttr<Dimension>("icon_width", 24.0_vp);
            theme->iconHeight_ = pattern->GetAttr<Dimension>("icon_height", 24.0_vp);
            theme->backButtonWidth_ = pattern->GetAttr<Dimension>("icon_background_width", 40.0_vp);
            theme->backButtonHeight_ = pattern->GetAttr<Dimension>("icon_background_height", 40.0_vp);
            theme->iconBackgroundWidth_ = pattern->GetAttr<Dimension>("icon_background_width", 40.0_vp);
            theme->iconBackgroundHeight_ = pattern->GetAttr<Dimension>("icon_background_height", 40.0_vp);
            theme->paddingTopTwolines_ = pattern->GetAttr<Dimension>("padding_top_twolines", 8.0_vp);
            theme->titleSpaceVertical_ = pattern->GetAttr<Dimension>("title_sapce_vertical", 2.0_vp);
            theme->iconDisableAlpha_ = pattern->GetAttr<double>("icon_disable_alpha", 0.0);
            theme->backgroundFocusOutlineColor_ = pattern->GetAttr<Color>(
                "icon_background_focus_outline_color", Color(0x0A59F7));
            theme->backgroundFocusOutlineWeight_ = pattern->GetAttr<Dimension>(
                "icon_background_focus_outline_weight", 2.0_vp);
            theme->backgroundDisableAlpha_ = pattern->GetAttr<double>("icon_background_disable_alpha", 0.0);
            theme->backgroundHoverColor_ = pattern->GetAttr<Color>("icon_background_hover_color",
                Color(0x0c000000));
            theme->backgroundPressedColor_ = pattern->GetAttr<Color>("icon_background_pressed_color",
                Color(0x19000000));
            theme->titlebarBackgroundBlurStyle_ = pattern->GetAttr<int>("titlebar_background_blur_style", 0);
            theme->toolbarBackgroundBlurStyle_ = pattern->GetAttr<int>("toolbar_background_blur_style", 0);
            theme->dragBarDefaultColor_ = pattern->GetAttr<Color>("drag_bar_default_color", Color(0xff182431));
            theme->dragBarItemDefaultColor_ = pattern->GetAttr<Color>("drag_bar_item_default_color", Color(0xffffffff));
            theme->dragBarActiveColor_ = pattern->GetAttr<Color>("drag_bar_active_color", Color(0x330A59F7));
            theme->dragBarItemActiveColor_ = pattern->GetAttr<Color>("drag_bar_item_active_color", Color(0xFF007DFF));
            theme->dividerGradientLightBlue_ = pattern->GetAttr<Color>("divider_light_blue", Color(0x7FCEDEFE));
            theme->dividerGradientDarkBlue_ = pattern->GetAttr<Color>("divider_dark_blue", Color(0xFF0A59F7));
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
    InternalResource::ResourceId GetBackBtnResourceId() const
    {
        return backBtnResourceId_;
    }
    uint32_t GetBackSymbolId() const
    {
        return backSymbolId_;
    }
    uint32_t GetMoreSymbolId() const
    {
        return moreSymbolId_;
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

    const Color& GetToolBarBgColor() const
    {
        return toolbarBgColorWithOpacity_;
    }
    const Dimension& GetToolBarDividerWidth() const
    {
        return toolbarDividerWidth_;
    }
    const Color& GetToolBarDividerColor() const
    {
        return toolbarDividerColor_;
    }
    const Color& GetToolBarItemFocusColor() const
    {
        return toolbarItemFocusBorderColor_;
    }
    const Dimension& GetToolBarItemFocusBorderWidth() const
    {
        return toolbarItemFocusBorderWidth_;
    }
    const NG::BorderRadiusProperty& GetToolBarItemBorderRadius() const
    {
        return toolbarItemBorderRadius_;
    }
    const Dimension& GetToolBarItemFontSize() const
    {
        return toolbarItemFontSize_;
    }
    const Dimension& GetToolBarItemMinFontSize() const
    {
        return toolbarItemMinFontSize_;
    }
    const Color& GetToolBarItemFontColor() const
    {
        return toolbarItemFontColor_;
    }
    double GetToolbarItemDisabledAlpha() const
    {
        return toolbarItemDisabledAlpha_;
    }
    const Color& GetToolbarIconColor() const
    {
        return toolbarIconColor_;
    }
    const Dimension& GetToolbarIconSize() const
    {
        return toolbarIconSize_;
    }
    const Dimension& GetToolbarHideTextIconSize() const
    {
        return toolbarHideTextIconSize_;
    }
    const Color& GetToolbarActiveIconColor() const
    {
        return toolbarActiveIconColor_;
    }
    const Color& GetToolBarItemActiveFontColor() const
    {
        return toolbarActiveTextColor_;
    }
    uint32_t GetToolbarItemTextMaxLines() const
    {
        return toolbarItemTextMaxLines_;
    }
    const Dimension& GetToolbarItemSafeInterval() const
    {
        return toolbarItemSafeInterval_;
    }
    const Dimension& GetToolbarItemHorizontalPadding() const
    {
        return toolbarItemHorizontalPadding_;
    }
    const Dimension& GetToolbarItemVerticalPadding() const
    {
        return toolbarItemVerticalPadding_;
    }
    const Dimension& GetToolbarItemTopPadding() const
    {
        return toolbarItemTopPadding_;
    }
    const Dimension& GetToolbarItemLeftOrRightPadding() const
    {
        return toolbarItemLeftOrRightPadding_;
    }
    const Dimension& GetToolbarItemTextLeftOrRightPadding() const
    {
        return ToolbarItemTextLeftOrRightPadding_;
    }
    const Dimension& GetToolbarItemHeigth() const
    {
        return toolbarItemHeight_;
    }
    const Dimension& GetToolbarHeigth() const
    {
        return toolbarHeight_;
    }
    const Dimension& GetToolbarItemBottomPadding() const
    {
        return toolbarItemBottomPadding_;
    }
    const Dimension& GetToolbarItemIconTopPadding() const
    {
        return toolbarItemIconTopPadding_;
    }
    const Dimension& GetToolbarItemMargin() const
    {
        return toolbarItemMargin_;
    }
    const Dimension& GetToolbarItemSpecialMargin() const
    {
        return toolbarItemSpecialMargin_;
    }
    uint32_t GetToolbarRotationLimitGridCount() const
    {
        return toolbarLimitGridCount_;
    }
    uint32_t GetDividerShadowEnable() const
    {
        return dividerShadowEnable_;
    }
    const Color& GetNavigationDividerColor() const
    {
        return navigationDividerColor_;
    }
    const Dimension& GetMarginLeft() const
    {
        return marginLeft_;
    }
    const Dimension& GetMarginLeftForBackButton() const
    {
        return marginLeftForBackButton_;
    }
    const Dimension& GetMarginRight() const
    {
        return marginRight_;
    }
    const Dimension& GetMarginRightForMenu() const
    {
        return marginRightForMenu_;
    }
    const Color& GetNavigationGroupColor() const
    {
        return navigationGroupColor_;
    }
    uint32_t GetNavBarUnfocusEffectEnable() const
    {
        return navBarUnfocusEffectEnable_;
    }
    const Color& GetNavBarUnfocusColor() const
    {
        return navBarUnfocusColor_;
    }
    const Color& GetBackgroundBlurColor() const
    {
        return backgroundBlurColor_;
    }
    const Dimension& GetMainTitleFontSizeL() const
    {
        return mainTitleFontSizeL_;
    }
    const Dimension& GetMainTitleFontSizeM() const
    {
        return mainTitleFontSizeM_;
    }
    const Dimension& GetMainTitleFontSizeS() const
    {
        return mainTitleFontSizeS_;
    }
    const Dimension& GetSubTitleFontSizeS() const
    {
        return subTitleFontSizeS_;
    }
    const Color& GetMainTitleFontColor() const
    {
        return mainTitleFontColor_;
    }
    const Color& GetSubTitleFontColor() const
    {
        return subTitleFontColor_;
    }
    const FontWeight& GetMainTitleFontWeight() const
    {
        return mainTitleFontWeight_;
    }
    const FontWeight& GetSubTitleFontWeight() const
    {
        return subTitleFontWeight_;
    }
    const Dimension& GetCornerRadius() const
    {
        return cornerRadius_;
    }
    const Color& GetCompBackgroundColor() const
    {
        return compBackgroundColor_;
    }
    const Color& GetIconColor() const
    {
        return iconColor_;
    }
    const Dimension& GetCompPadding() const
    {
        return compPadding_;
    }
    const Dimension& GetIconWidth() const
    {
        return iconWidth_;
    }
    const Dimension& GetIconHeight() const
    {
        return iconHeight_;
    }
    const Dimension& GetIconBackgroundWidth() const
    {
        return iconBackgroundWidth_;
    }
    const Dimension& GetIconBackgroundHeight() const
    {
        return iconBackgroundHeight_;
    }
    const Dimension& GetBackButtonWidth() const
    {
        return backButtonWidth_;
    }
    const Dimension& GetBackButtonHeight() const
    {
        return backButtonHeight_;
    }
    const Dimension& GetPaddingTopTwolines() const
    {
        return paddingTopTwolines_;
    }
    const Dimension& GetTitleSpaceVertical() const
    {
        return titleSpaceVertical_;
    }
    const double& GetIconDisableAlpha() const
    {
        return iconDisableAlpha_;
    }
    const Color& GetBackgroundFocusOutlineColor() const
    {
        return backgroundFocusOutlineColor_;
    }
    const Dimension& GetBackgroundFocusOutlineWeight() const
    {
        return backgroundFocusOutlineWeight_;
    }
    const double& GetBackgroundDisableAlpha() const
    {
        return backgroundDisableAlpha_;
    }
    const Color& GetBackgroundHoverColor() const
    {
        return backgroundHoverColor_;
    }
    const Color& GetBackgroundPressedColor() const
    {
        return backgroundPressedColor_;
    }
    const int& GetTitlebarBackgroundBlurStyle() const
    {
        return titlebarBackgroundBlurStyle_;
    }
    const int& GetToolbarBackgroundBlurStyle() const
    {
        return toolbarBackgroundBlurStyle_;
    }
    const Color& GetDragBarDefaultColor() const
    {
        return dragBarDefaultColor_;
    }
    const Color& GetDragBarItemDefaultColor() const
    {
        return dragBarItemDefaultColor_;
    }
    const Color& GetDragBarActiveColor() const
    {
        return dragBarActiveColor_;
    }
    const Color& GetDragBarItemActiveColor() const
    {
        return dragBarItemActiveColor_;
    }
    const Color& GetDviderLightBlueColor() const
    {
        return dividerGradientLightBlue_;
    }
    const Color& GetDviderDarkBlueColor() const
    {
        return dividerGradientDarkBlue_;
    }
    const std::string& GetMoreMessage() const
    {
        return moreMessage_;
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
    InternalResource::ResourceId backBtnResourceId_ = InternalResource::ResourceId::NO_ID;
    InternalResource::ResourceId backResourceId_ = InternalResource::ResourceId::NO_ID;
    InternalResource::ResourceId moreResourceId_ = InternalResource::ResourceId::NO_ID;
    uint32_t backSymbolId_;
    uint32_t moreSymbolId_;
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
    Color toolbarBgColor_;
    Color toolbarBgColorWithOpacity_;
    Dimension toolbarDividerWidth_;
    Color toolbarDividerColor_;
    Color toolbarItemFocusBorderColor_;
    Dimension toolbarItemFocusBorderWidth_ = 2.0_vp;
    Dimension toolbarItemBorderRadiusValue_;
    NG::BorderRadiusProperty toolbarItemBorderRadius_;
    Dimension toolbarItemFontSize_;
    Dimension toolbarItemMinFontSize_ = 9.0_vp;
    Color toolbarItemFontColor_;
    double toolbarItemDisabledAlpha_ = 0.4;
    double toolbarBgAlpha_ = 0.95;
    Color toolbarIconColor_;
    Dimension toolbarIconSize_ = 24.0_vp;
    Dimension toolbarHideTextIconSize_ = 36.0_vp;
    Color toolbarActiveIconColor_;
    Color toolbarActiveTextColor_;
    uint32_t toolbarItemTextMaxLines_ = 2;
    Dimension toolbarItemSafeInterval_ = 8.0_vp;
    Dimension toolbarItemHorizontalPadding_ = 8.0_vp;
    Dimension ToolbarItemTextLeftOrRightPadding_ = 4.0_vp;
    Dimension toolbarItemVerticalPadding_ = 12.0_vp;
    Dimension toolbarItemTopPadding_ = 8.0_vp;
    Dimension toolbarItemLeftOrRightPadding_ = 4.0_vp;
    Dimension toolbarItemHeight_ = 56.0_vp;
    Dimension toolbarHeight_ = 56.0_vp;
    Dimension toolbarItemBottomPadding_ = 4.0_vp;
    Dimension toolbarItemIconTopPadding_ = 4.0_vp;
    Dimension toolbarItemMargin_ = 4.0_vp;
    Dimension toolbarItemSpecialMargin_ = 0.0_vp;
    std::string moreMessage_ = "";
    uint32_t toolbarLimitGridCount_ = 8;
    uint32_t dividerShadowEnable_ = 0;
    Color navigationDividerColor_;
    Color navigationGroupColor_ = Color::TRANSPARENT;
    uint32_t navBarUnfocusEffectEnable_ = 0;
    Color navBarUnfocusColor_ = Color::TRANSPARENT;
    Color backgroundBlurColor_;
    Dimension marginLeft_;
    Dimension marginLeftForBackButton_;
    Dimension marginRight_;
    Dimension marginRightForMenu_;
    Dimension mainTitleFontSizeL_;
    Dimension mainTitleFontSizeM_;
    Dimension mainTitleFontSizeS_;
    Dimension subTitleFontSizeS_;
    Color mainTitleFontColor_;
    Color subTitleFontColor_;
    FontWeight mainTitleFontWeight_ { FontWeight::W700 };
    FontWeight subTitleFontWeight_ { FontWeight::W400 };
    Dimension cornerRadius_;
    Color compBackgroundColor_;
    Dimension compPadding_;
    Color iconColor_;
    Dimension iconWidth_;
    Dimension iconHeight_;
    Dimension backButtonWidth_;
    Dimension backButtonHeight_;
    Dimension iconBackgroundWidth_;
    Dimension iconBackgroundHeight_;
    Dimension paddingTopTwolines_;
    Dimension titleSpaceVertical_;
    double iconDisableAlpha_ = 0.4;
    Color backgroundFocusOutlineColor_;
    Dimension backgroundFocusOutlineWeight_;
    double backgroundDisableAlpha_ = 0.4;
    Color backgroundHoverColor_;
    Color backgroundPressedColor_;
    int titlebarBackgroundBlurStyle_;
    int toolbarBackgroundBlurStyle_;
    Color dragBarDefaultColor_;
    Color dragBarItemDefaultColor_;
    Color dragBarActiveColor_;
    Color dragBarItemActiveColor_;
    Color dividerGradientLightBlue_;
    Color dividerGradientDarkBlue_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_BAR_THEME_H
