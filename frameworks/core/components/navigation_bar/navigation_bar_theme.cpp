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

#include "core/components/navigation_bar/navigation_bar_theme.h"

#include "base/utils/string_utils.h"
#include "core/common/container.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

RefPtr<NavigationBarTheme> NavigationBarTheme::Builder::Build(
    const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<NavigationBarTheme> theme = AceType::MakeRefPtr<NavigationBarTheme>();
    InitTheme(theme, themeConstants);
    return theme;
}

void NavigationBarTheme::Builder::InitTheme(
    const RefPtr<NavigationBarTheme>& theme, const RefPtr<ThemeConstants>& themeConstants) const
{
    CHECK_NULL_VOID(themeConstants);
    SetSymbolTheme(themeConstants, theme);
    theme->backBtnResourceId_ = InternalResource::ResourceId::TITLEBAR_BACK;
    theme->backResourceId_ = InternalResource::ResourceId::IC_BACK;
    theme->moreResourceId_ = InternalResource::ResourceId::IC_MORE;
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
        theme->titleFontSize_ = pattern->GetAttr<Dimension>("title_text_font_size", 0.0_vp);
        theme->titleFontSizeMin_ = pattern->GetAttr<Dimension>("title_text_font_size_min", 0.0_vp);
        theme->titleFontSizeBig_ = pattern->GetAttr<Dimension>("title_text_font_size_big", 0.0_vp);
        theme->subTitleColor_ = pattern->GetAttr<Color>("sub_title_text_color", Color::WHITE);
        theme->subTitleFontSize_ = pattern->GetAttr<Dimension>("sub_title_text_font_size", 0.0_vp);
        theme->menuIconColor_ = pattern->GetAttr<Color>("menu_icon_color", Color::WHITE);
        theme->buttonPressedColor_ = pattern->GetAttr<Color>("button_bg_color_pressed", Color::WHITE);
        theme->buttonFocusColor_ = pattern->GetAttr<Color>("button_bg_color_focused", Color::WHITE);
        theme->buttonHoverColor_ = pattern->GetAttr<Color>("button_bg_color_hovered", Color::WHITE);
        theme->buttonCornerRadius_ = pattern->GetAttr<Dimension>("button_corner_radius", 0.0_vp);
        theme->maxPaddingStart_ = pattern->GetAttr<Dimension>("title_left_spacing", 0.0_vp);
        theme->maxPaddingEnd_ = pattern->GetAttr<Dimension>("title_right_spacing", 0.0_vp);
        theme->defaultPaddingStart_ = pattern->GetAttr<Dimension>("back_button_left_spacing", 0.0_vp);
        theme->backButtonIconColor_ = pattern->GetAttr<Color>("back_button_icon_color", Color::WHITE);
        theme->alphaDisabled_ = pattern->GetAttr<double>("button_alpha_disabled", 0.0);
        auto dividerShadowEnable = pattern->GetAttr<std::string>("divider_shadow_enable", "0");
        theme->dividerShadowEnable_ = static_cast<uint32_t>(StringUtils::StringToInt(dividerShadowEnable));
        theme->navigationGroupColor_ = pattern->GetAttr<Color>("navigation_group_color", Color::TRANSPARENT);
        auto navBarUnfocusEffectEnable = pattern->GetAttr<std::string>("section_unfocus_effect_enable", "0");
        theme->navBarUnfocusEffectEnable_ =
            static_cast<uint32_t>(StringUtils::StringToInt(navBarUnfocusEffectEnable));
        theme->navBarUnfocusColor_ = pattern->GetAttr<Color>("color_panel_bg", Color::TRANSPARENT);
        theme->titlebarBackgroundBlurStyle_ = pattern->GetAttr<int>("titlebar_background_blur_style", 0);
        theme->toolbarBackgroundBlurStyle_ = pattern->GetAttr<int>("toolbar_background_blur_style", 0);
        theme->moreMessage_ = pattern->GetAttr<std::string>("navigation_general_more", "null");
    }
    ParsePattern(themeConstants, theme);
}

void NavigationBarTheme::Builder::SetSymbolTheme(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<NavigationBarTheme>& theme) const
{
    theme->backSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.chevron_backward");
    theme->moreSymbolId_ = themeConstants->GetSymbolByName("sys.symbol.dot_grid_2x2");
}

void NavigationBarTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<NavigationBarTheme>& theme) const
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
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        SetNavigationTokenTheme(pattern, theme);
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_NINETEEN)) {
        SetToolBarTheme(pattern, theme);
    }
    ParsePatternContinue(themeConstants, theme);
}

void NavigationBarTheme::Builder::SetToolBarTheme(
    RefPtr<ThemeStyle> pattern, const RefPtr<NavigationBarTheme>& theme) const
{
    theme->toolbarItemFocusBorderWidth_ =
        pattern->GetAttr<Dimension>("toolbar_item_focus_border_size_api_sixteen", 2.0_vp);
    theme->toolbarItemFocusBorderColor_ =
        pattern->GetAttr<Color>("toolbar_item_focus_color_api_sixteen", Color(0x007dff));
    theme->toolbarItemBorderRadiusValue_ =
        pattern->GetAttr<Dimension>("toolbar_item_bg_button_border_radius_api_sixteen", 12.0_vp);
    theme->toolbarItemBorderRadius_.SetRadius(theme->toolbarItemBorderRadiusValue_);
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
    theme->toolbarItemTextMaxLines_ = 1;
}

void NavigationBarTheme::Builder::SetNavigationTokenTheme(
    RefPtr<ThemeStyle> pattern, const RefPtr<NavigationBarTheme>& theme) const
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

void NavigationBarTheme::Builder::ParsePatternContinue(
    const RefPtr<ThemeConstants>& themeConstants,
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
    constexpr double mainTitleDefaultFontWeit = 6.0;
    theme->mainTitleFontWeight_ = FontWeight(static_cast<int32_t>(
        pattern->GetAttr<double>("title_primary_weight", mainTitleDefaultFontWeit)));
    constexpr double subTitleDefaultFontWeit = 3.0;
    theme->subTitleFontWeight_ = FontWeight(static_cast<int32_t>(
        pattern->GetAttr<double>("title_subheader_weight", subTitleDefaultFontWeit)));
    theme->iconWidth_ = pattern->GetAttr<Dimension>("icon_width", 24.0_vp);
    theme->iconHeight_ = pattern->GetAttr<Dimension>("icon_height", 24.0_vp);
    theme->backButtonWidth_ = pattern->GetAttr<Dimension>("icon_background_width", 40.0_vp);
    theme->backButtonHeight_ = pattern->GetAttr<Dimension>("icon_background_height", 40.0_vp);
    theme->iconBackgroundWidth_ = pattern->GetAttr<Dimension>("icon_background_width", 40.0_vp);
    theme->iconBackgroundHeight_ = pattern->GetAttr<Dimension>("icon_background_height", 40.0_vp);
    theme->paddingTopTwolines_ = pattern->GetAttr<Dimension>("padding_top_twolines", 8.0_vp);
    theme->titleSpaceVertical_ = pattern->GetAttr<Dimension>("title_space_vertical", 2.0_vp);
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
    theme->navigationBack_ = pattern->GetAttr<std::string>("navigation_back", "");
    NG::SINGLE_LINE_TITLEBAR_HEIGHT = pattern->GetAttr<Dimension>("single_line_titlebar_height", 56.0_vp);
    NG::DOUBLE_LINE_TITLEBAR_HEIGHT = pattern->GetAttr<Dimension>("double_line_titlebar_height", 82.0_vp);
    NG::FULL_SINGLE_LINE_TITLEBAR_HEIGHT =
        pattern->GetAttr<Dimension>("full_single_line_titlebar_height", 112.0_vp);
    NG::FULL_DOUBLE_LINE_TITLEBAR_HEIGHT =
        pattern->GetAttr<Dimension>("full_double_line_titlebar_height", 138.0_vp);
    theme->iconBorderWidth_ = pattern->GetAttr<Dimension>("titlebar_icon_border_width", 0.0_vp);
    theme->iconBorderColor_ = pattern->GetAttr<Color>("titlebar_icon_border_color", Color(0x00000000));
    theme->menuItemFocusPadding_ = pattern->GetAttr<Dimension>("menuitem_focus_padding", 0.0_vp);
    theme->navigationFocusBlendBgColor_ =
        pattern->GetAttr<Color>("navigation_focus_blend_bg_color", Color(0x00000000));
    theme->navigationMiniMinFontSize_ = pattern->GetAttr<Dimension>("navigation_mini_min_font_size", 14.0_fp);
    theme->navigationFullMinFontSize_ = pattern->GetAttr<Dimension>("navigation_full_min_font_size", 14.0_fp);
    NG::TITLEBAR_MAX_LINES = static_cast<uint32_t>(pattern->GetAttr<double>("titlebar_max_lines", 2.0));
    NG::MIN_ADAPT_SUBTITLE_FONT_SIZE = pattern->GetAttr<Dimension>("min_adapt_subtitle_font_size", 10.0_fp);
    theme->menuButtonPadding_ = pattern->GetAttr<Dimension>("menu_button_padding", 8.0_vp);
}

} // namespace OHOS::Ace
