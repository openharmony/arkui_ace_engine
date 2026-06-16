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

#include "core/components/tab_bar/tab_theme.h"

#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {

namespace {
constexpr double THIRDFONT_DEFAULT_VALUE = 1.45;
constexpr double BIGFONT_DEFAULT_VALUE = 1.75;
constexpr double LARGEFONT_DEFAULT_VALUE = 2.0;
constexpr double MAXFONT_DEFAULT_VALUE = 3.2;
constexpr double ANIMATION_DURATION_DEFAULT = 300.0;
} // namespace

RefPtr<TabTheme> TabTheme::Builder::Build(const RefPtr<ThemeConstants>& themeConstants) const
{
    RefPtr<TabTheme> theme = AceType::MakeRefPtr<TabTheme>();
    if (!themeConstants) {
        return theme;
    }
    ParsePattern(themeConstants, theme);
    return theme;
}

void TabTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TabTheme>& theme) const
{
    RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_TAB);
    if (!pattern) {
        LOGW("find pattern of tab fail");
        return;
    }

    theme->subTabBarHoverToPressDuration_ =
        pattern->GetAttr<double>("sub_tab_bar_hover_to_press_duration", 0.0);
    theme->tabContentAnimationDuration_ =
        pattern->GetAttr<double>("tab_content_animation_duration", ANIMATION_DURATION_DEFAULT);
    theme->tabBarDefaultHeight_ = pattern->GetAttr<Dimension>("tab_bar_default_height", 0.0_vp);
    theme->bottomTabBarDefaultHeight_ = pattern->GetAttr<Dimension>("bottom_tab_bar_default_height", 0.0_vp);
    theme->tabBarDefaultWidth_ = pattern->GetAttr<Dimension>("tab_bar_default_width", 0.0_vp);
    theme->subTabBarMinWidth_ = pattern->GetAttr<Dimension>("sub_tab_bar_min_width", 0.0_vp);
    theme->dividerColor_ = pattern->GetAttr<Color>("divider_color", Color::BLACK);
    theme->tabBarShadowMargin_ = pattern->GetAttr<Dimension>("tab_bar_shadow_margin", 0.0_vp);
    theme->tabBarGradientWidth_ = pattern->GetAttr<Dimension>("tab_bar_gradient_width", 0.0_vp);
    theme->colorBottomTabSubBg_ = pattern->GetAttr<Color>("color_bottom_tab_sub_bg", Color::WHITE);
    theme->colorBottomTabSubBgBlur_ = pattern->GetAttr<Color>("color_bottom_tab_sub_bg_blur", Color::WHITE);
    theme->tabBarColumnGutter_ = pattern->GetAttr<Dimension>("tab_bar_column_gutter", 0.0_vp);
    theme->tabBarColumnMargin_ = pattern->GetAttr<Dimension>("tab_bar_column_margin", 0.0_vp);
    theme->horizontalBottomTabMinWidth_ =
        pattern->GetAttr<Dimension>("horizontal_bottom_tab_min_width", 0.0_vp);
    theme->tabBarDefaultMargin_ = pattern->GetAttr<Dimension>("tab_bar_margin_width", 0.0_vp);
    theme->tabBarFocusedColor_ = pattern->GetAttr<Color>("tab_bar_focused_color", Color::TRANSPARENT);
    theme->subTabTextFocusedColor_ =
        pattern->GetAttr<Color>("subtab_text_focused_color", theme->subTabTextOffColor_);
    theme->focusBoardPadding_ = pattern->GetAttr<Dimension>("tab_bar_board_focus_padding", 0.0_vp);
    theme->subTabItemHorizontalPadding_ = pattern->GetAttr<Dimension>("subtab_item_Horizontal_padding", 0.0_vp);
    theme->focusPadding_ = pattern->GetAttr<Dimension>("tab_bar_focus_padding", 0.0_vp);
    theme->isChangeFocusTextStyle_ = static_cast<bool>(pattern->GetAttr<int>("subtab_focused_style", 0));
    theme->labelPadding_ = pattern->GetAttr<Dimension>("label_padding", 8.0_vp);
    theme->padding_ = pattern->GetAttr<Dimension>("tab_padding", 16.0_vp);
    theme->gradientWidth_ = pattern->GetAttr<Dimension>("tab_gradient_width", 24.0_vp);
    theme->defaultHeight_ = pattern->GetAttr<Dimension>("tab_default_height", 56.0_vp);
    theme->defaultWidth_ = pattern->GetAttr<Dimension>("tab_default_width", 200.0_px);
    theme->defaultItemHeight_ = pattern->GetAttr<Dimension>("tab_default_item_height", 200.0_px);
    theme->activeIndicatorWidth_ = pattern->GetAttr<Dimension>("active_indicator_width", 2.0_vp);
    theme->activeIndicatorMinWidth_ = pattern->GetAttr<Dimension>("active_indicator_min_width", 32.0_vp);
    theme->activeIndicatorPadding_ = pattern->GetAttr<Dimension>("active_indicator_padding", 3.0_vp);
    theme->focusIndicatorHorizontalPadding_ =
        pattern->GetAttr<Dimension>("focus_indicator_horizontal_padding", 0.0_vp);
    theme->focusIndicatorVerticalPadding_ =
        pattern->GetAttr<Dimension>("focus_indicator_vertical_padding", 0.0_vp);
    theme->dialog_radius_level10_ = pattern->GetAttr<Dimension>("dialog_radius_level10", 20.0_vp);
    theme->dialog_iconColor_ = pattern->GetAttr<Color>("dialog_icon_primary", Color(0xff182431));
    theme->dialog_fontColor_ = pattern->GetAttr<Color>("dialog_font_primary", Color(0xff182431));

    ParsePattern2(theme, pattern);
}

void TabTheme::Builder::ParsePattern2(const RefPtr<TabTheme>& theme, const RefPtr<ThemeStyle> pattern) const
{
    theme->backgroundColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color::WHITE);
    theme->activeIndicatorColor_ = pattern->GetAttr<Color>("active_indicator_color", Color::WHITE);
    theme->focusIndicatorColor_ = pattern->GetAttr<Color>("focus_indicator_color", Color::WHITE);
    theme->focusIndicatorRadius_ = pattern->GetAttr<Dimension>("focus_indicator_radius", 0.0_vp);
    theme->subTabIndicatorHeight_ = pattern->GetAttr<Dimension>("subtab_indicator_height", 0.0_vp);
    theme->subTabTextOnColor_ = pattern->GetAttr<Color>("subtab_text_on_color", Color::WHITE);
    theme->subTabTextOffColor_ = pattern->GetAttr<Color>("subtab_text_off_color", Color::WHITE);
    theme->subTabBoardTextOnColor_ = pattern->GetAttr<Color>("subtab_board_text_on_color", Color::WHITE);
    theme->subTabIndicatorGap_ = pattern->GetAttr<Dimension>("subtab_indicator_gap", 0.0_vp);
    theme->subTabHorizontalPadding_ = pattern->GetAttr<Dimension>("subtab_horizontal_padding", 0.0_vp);
    theme->subTabTopPadding_ = pattern->GetAttr<Dimension>("subtab_top_padding", 0.0_vp);
    theme->subTabBottomPadding_ = pattern->GetAttr<Dimension>("subtab_bottom_padding", 0.0_vp);
    theme->subTabItemPadding_ = pattern->GetAttr<Dimension>("subtab_item_padding", 0.0_vp);
    theme->subTabBarHoverColor_ = pattern->GetAttr<Color>("subtab_hover_color", Color::WHITE);
    theme->subTabBarPressedColor_ = pattern->GetAttr<Color>("subtab_press_color", Color::WHITE);
    theme->subtabTextDefaultFontSize_ = pattern->GetAttr<Dimension>("subtab_text_default_font_size", 0.0_vp);
    theme->subtabLandscapeHorizontalPadding_ =
        pattern->GetAttr<Dimension>("subtab_landscape_horizontal_padding", 0.0_vp);
    theme->bottomTabHorizontalPadding_ = pattern->GetAttr<Dimension>("bottom_tab_horizontal_padding", 0.0_vp);
    theme->bottomTabTextOn_ = pattern->GetAttr<Color>("bottom_tab_text_on", Color::WHITE);
    theme->bottomTabTextOff_ = pattern->GetAttr<Color>("bottom_tab_text_off", Color::WHITE);
    theme->bottomTabIconOn_ = pattern->GetAttr<Color>("bottom_tab_icon", Color::WHITE);
    theme->bottomTabIconOff_ = pattern->GetAttr<Color>("bottom_tab_icon_off", Color::WHITE);
    theme->bottomTabSymbolOn_ = pattern->GetAttr<Color>("bottom_tab_symbol", Color(0xFF007DFF));
    theme->bottomTabSymbolOff_ = pattern->GetAttr<Color>("bottom_tab_symbol_off", Color(0x66182431));
    theme->bottomTabImageSize_ = pattern->GetAttr<Dimension>("bottom_tab_image_size", 0.0_vp);
    theme->bottomTabTextSize_ = pattern->GetAttr<Dimension>("bottom_tab_text_size", 0.0_vp);
    theme->bottomTabHorizontalTextSize_ =
        pattern->GetAttr<Dimension>("bottom_tab_horizontal_text_size", BOTTOM_BAR_HORIZONTAL_TEXT_SIZE);
    theme->bottomTabBackgroundBlurStyle_ = pattern->GetAttr<int>("bottom_tab_bar_bg_blur_style", 0);
    theme->defaultTabBarName_ = pattern->GetAttr<std::string>("default_tab_bar_name", "");
    theme->bottomTabBarSpace_ = pattern->GetAttr<Dimension>("bottom_tab_bar_space", 0.0_vp);
    theme->horizontalBottomTabBarSpace_ =
        pattern->GetAttr<Dimension>("horizontal_bottom_tab_bar_space", 0.0_vp);
    theme->subTabBarHoverDuration_ = pattern->GetAttr<double>("sub_tab_bar_hover_duration", 0.0);
    theme->subTabBarBigFontSizeScale_ =
        pattern->GetAttr<double>("sub_tab_bar_big_font_size_scale", BIGFONT_DEFAULT_VALUE);
    theme->subTabBarLargeFontSizeScale_ =
        pattern->GetAttr<double>("sub_tab_bar_large_font_size_scale", LARGEFONT_DEFAULT_VALUE);
    theme->subTabBarMaxFontSizeScale_ =
        pattern->GetAttr<double>("sub_tab_bar_max_font_size_scale", MAXFONT_DEFAULT_VALUE);
    theme->subTabBarOriginFontSizeScale_ = pattern->GetAttr<double>("sub_tab_bar_origin_font_size_scale", 1.0);
    theme->subTabBarLeftRightMargin_ = pattern->GetAttr<Dimension>("sub_tab_bar_left_right_margin", 12.0_vp);
    theme->subTabBarIndicatorstyleMarginTop_ =
        pattern->GetAttr<Dimension>("sub_tab_bar_indicatorstyle_margin_top", 4.0_vp);
    theme->subTabBarThirdLargeFontSizeScale_ =
        pattern->GetAttr<double>("sub_tab_bar_third_large_font_size_scale", THIRDFONT_DEFAULT_VALUE);
    theme->interactiveFocusColor_ =
        pattern->GetAttr<Color>("interactive_focus", Color::BLACK);
    theme->outlineExtraLarger_ =
        pattern->GetAttr<Dimension>("outline_extra_larger", 2.0_vp);
    theme->iconEmphasize_ =
        pattern->GetAttr<Color>("icon_emphasize", Color::BLACK);
    theme->iconPrimary_ =
        pattern->GetAttr<Color>("icon_primary", Color::BLACK);
    theme->fontEmphasize_ =
        pattern->GetAttr<Color>("font_emphasize", Color::BLACK);
    theme->fontPrimary_ =
        pattern->GetAttr<Color>("font_primary", Color::BLACK);
}

} // namespace OHOS::Ace
