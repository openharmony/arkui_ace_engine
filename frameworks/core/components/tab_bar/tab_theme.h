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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * TabTheme defines color and styles of tab. TabTheme should be built
 * using TabTheme::Builder.
 */
class TabTheme : public virtual Theme {
    DECLARE_ACE_TYPE(TabTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<TabTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<TabTheme> theme = AceType::Claim(new TabTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->labelPadding_ = themeConstants->GetDimension(THEME_TAB_LABEL_PADDING);
            theme->padding_ = themeConstants->GetDimension(THEME_TAB_PADDING);
            theme->gradientWidth_ = themeConstants->GetDimension(THEME_TAB_GRADIENT_WIDTH);
            theme->defaultHeight_ = themeConstants->GetDimension(THEME_TAB_DEFAULT_HEIGHT);
            theme->defaultWidth_ = themeConstants->GetDimension(THEME_TAB_DEFAULT_WIDTH);
            theme->defaultItemHeight_ = themeConstants->GetDimension(THEME_TAB_DEFAULT_ITEM_HEIGHT);
            theme->backgroundColor_ = themeConstants->GetColor(THEME_TAB_BACKGROUND_COLOR);
            theme->activeIndicatorColor_ = themeConstants->GetColor(THEME_TAB_ACTIVE_INDICATOR_COLOR);
            theme->activeIndicatorWidth_ = themeConstants->GetDimension(THEME_TAB_ACTIVE_INDICATOR_WIDTH);
            theme->activeIndicatorMinWidth_ = themeConstants->GetDimension(THEME_TAB_ACTIVE_INDICATOR_MIN_WIDTH);
            theme->activeIndicatorPadding_ = themeConstants->GetDimension(THEME_TAB_ACTIVE_INDICATOR_PADDING);
            theme->focusIndicatorColor_ = themeConstants->GetColor(THEME_TAB_FOCUS_INDICATOR_COLOR);
            theme->focusIndicatorRadius_ = themeConstants->GetDimension(THEME_TAB_FOCUS_INDICATOR_RADIUS);
            theme->focusIndicatorHorizontalPadding_ =
                themeConstants->GetDimension(THEME_TAB_FOCUS_INDICATOR_HORIZONTAL_PADDING);
            theme->focusIndicatorVerticalPadding_ =
                themeConstants->GetDimension(THEME_TAB_FOCUS_INDICATOR_VERTICAL_PADDING);
            theme->dividerColor_ = themeConstants->GetColor(THEME_DIVIDER_COLOR);
            auto themeStyle = themeConstants->GetThemeStyle();
            if (!themeStyle) {
                return theme;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_TAB, nullptr);
            if (pattern) {
                theme->backgroundColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color::WHITE);
                theme->activeIndicatorColor_ = pattern->GetAttr<Color>("active_indicator_color", Color::WHITE);
                theme->focusIndicatorColor_ = pattern->GetAttr<Color>("focus_indicator_color", Color::WHITE);
                theme->focusIndicatorRadius_ = pattern->GetAttr<Dimension>("focus_indicator_radius", 0.0_vp);
                theme->subTabIndicatorHeight_ = pattern->GetAttr<Dimension>("subtab_indicator_height", 0.0_vp);
                theme->subTabTextOffColor_ = pattern->GetAttr<Color>("subtab_text_off_color", Color::WHITE);
                theme->subTabIndicatorGap_ = pattern->GetAttr<Dimension>("subtab_indicator_gap", 0.0_vp);
                theme->subTabHorizontalPadding_ = pattern->GetAttr<Dimension>("subtab_horizontal_padding", 0.0_vp);
                theme->subTabTopPadding_ = pattern->GetAttr<Dimension>("subtab_top_padding", 0.0_vp);
                theme->subTabBottomPadding_ = pattern->GetAttr<Dimension>("subtab_bottom_padding", 0.0_vp);
                theme->subTabBarHoverColor_ = pattern->GetAttr<Color>("subtab_hover_color", Color::WHITE);
                theme->subTabBarPressedColor_ = pattern->GetAttr<Color>("subtab_press_color", Color::WHITE);
                theme->subtabTextDefaultFontSize_ =
                    pattern->GetAttr<Dimension>("subtab_text_default_font_size", 0.0_vp);
                theme->subtabLandscapeHorizontalPadding_ =
                    pattern->GetAttr<Dimension>("subtab_landscape_horizontal_padding", 0.0_vp);
                theme->bottomTabHorizontalPadding_ =
                    pattern->GetAttr<Dimension>("bottom_tab_horizontal_padding", 0.0_vp);
                theme->bottomTabTextOn_ = pattern->GetAttr<Color>("bottom_tab_text_on", Color::WHITE);
                theme->bottomTabTextOff_ = pattern->GetAttr<Color>("bottom_tab_text_off", Color::WHITE);
                theme->bottomTabIconOn_ = pattern->GetAttr<Color>("bottom_tab_icon", Color::WHITE);
                theme->bottomTabIconOff_ = pattern->GetAttr<Color>("bottom_tab_icon_off", Color::WHITE);
                theme->bottomTabImageSize_ = pattern->GetAttr<Dimension>("bottom_tab_image_size", 0.0_vp);
                theme->bottomTabTextSize_ = pattern->GetAttr<Dimension>("bottom_tab_text_size", 0.0_vp);
                theme->defaultTabBarName_ = pattern->GetAttr<std::string>("default_tab_bar_name", "");
                theme->bottomTabBarSpace_ = pattern->GetAttr<Dimension>("bottom_tab_bar_space", 0.0_vp);
                theme->horizontalBottomTabBarSpace_ =
                    pattern->GetAttr<Dimension>("horizontal_bottom_tab_bar_space", 0.0_vp);
                theme->subTabBarHoverDuration_ = pattern->GetAttr<double>("sub_tab_bar_hover_duration", 0.0);
                theme->subTabBarHoverToPressDuration_ =
                    pattern->GetAttr<double>("sub_tab_bar_hover_to_press_duration", 0.0);
                theme->tabContentAnimationDuration_ =
                    pattern->GetAttr<double>("tab_content_animation_duration", 0.0);
                theme->tabBarDefaultHeight_ = pattern->GetAttr<Dimension>("tab_bar_default_height", 0.0_vp);
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
            } else {
                LOGW("find pattern of tab fail");
            }
            return theme;
        }
    };

    ~TabTheme() override = default;

    const Dimension& GetLabelPadding() const
    {
        return labelPadding_;
    }

    const Dimension& GetPadding() const
    {
        return padding_;
    }

    const Dimension& GetGradientWidth() const
    {
        return gradientWidth_;
    }

    const Dimension& GetDefaultHeight() const
    {
        return defaultHeight_;
    }

    const Dimension& GetDefaultWidth() const
    {
        return defaultWidth_;
    }

    const Dimension& GetDefaultItemHeight() const
    {
        return defaultItemHeight_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetActiveIndicatorColor() const
    {
        return activeIndicatorColor_;
    }

    const Dimension& GetActiveIndicatorWidth() const
    {
        return activeIndicatorWidth_;
    }

    const Dimension& GetActiveIndicatorMinWidth() const
    {
        return activeIndicatorMinWidth_;
    }

    const Dimension& GetActiveIndicatorPadding() const
    {
        return activeIndicatorPadding_;
    }

    const Color& GetFocusIndicatorColor() const
    {
        return focusIndicatorColor_;
    }

    const Dimension& GetFocusIndicatorRadius() const
    {
        return focusIndicatorRadius_;
    }

    const Dimension& GetFocusIndicatorHorizontalPadding() const
    {
        return focusIndicatorHorizontalPadding_;
    }

    const Dimension& GetFocusIndicatorVerticalPadding() const
    {
        return focusIndicatorVerticalPadding_;
    }

    const Color& GetSubTabTextOffColor() const
    {
        return subTabTextOffColor_;
    }

    const Dimension& GetSubTabIndicatorHeight() const
    {
        return subTabIndicatorHeight_;
    }

    const Dimension& GetSubTabIndicatorGap() const
    {
        return subTabIndicatorGap_;
    }

    const Dimension& GetSubTabHorizontalPadding() const
    {
        return subTabHorizontalPadding_;
    }

    const Dimension& GetSubTabTopPadding() const
    {
        return subTabTopPadding_;
    }

    const Dimension& GetSubTabBottomPadding() const
    {
        return subTabBottomPadding_;
    }

    const Color& GetSubTabBarHoverColor() const
    {
        return subTabBarHoverColor_;
    }

    const Color& GetSubTabBarPressedColor() const
    {
        return subTabBarPressedColor_;
    }

    const Dimension& GetSubTabTextDefaultFontSize() const
    {
        return subtabTextDefaultFontSize_;
    }

    const Dimension& GetSubtabLandscapeHorizontalPadding() const
    {
        return subtabLandscapeHorizontalPadding_;
    }

    const Dimension& GetBottomTabHorizontalPadding() const
    {
        return bottomTabHorizontalPadding_;
    }

    const Color& GetBottomTabTextOn() const
    {
        return bottomTabTextOn_;
    }

    const Color& GetBottomTabTextOff() const
    {
        return bottomTabTextOff_;
    }

    const Color& GetBottomTabIconOn() const
    {
        return bottomTabIconOn_;
    }

    const Color& GetBottomTabIconOff() const
    {
        return bottomTabIconOff_;
    }

    const Dimension& GetBottomTabImageSize() const
    {
        return bottomTabImageSize_;
    }

    const Dimension& GetBottomTabTextSize() const
    {
        return bottomTabTextSize_;
    }

    const std::string& GetDefaultTabBarName() const
    {
        return defaultTabBarName_;
    }

    const Dimension& GetBottomTabBarSpace() const
    {
        return bottomTabBarSpace_;
    }

    const Dimension& GetHorizontalBottomTabBarSpace() const
    {
        return horizontalBottomTabBarSpace_;
    }

    double GetSubTabBarHoverDuration() const
    {
        return subTabBarHoverDuration_;
    }

    double GetSubTabBarHoverToPressDuration() const
    {
        return subTabBarHoverToPressDuration_;
    }

    double GetTabContentAnimationDuration() const
    {
        return tabContentAnimationDuration_;
    }

    const Dimension& GetTabBarDefaultHeight() const
    {
        return tabBarDefaultHeight_;
    }

    const Dimension& GetTabBarDefaultWidth() const
    {
        return tabBarDefaultWidth_;
    }

    const Dimension& GetSubTabBarMinWidth() const
    {
        return subTabBarMinWidth_;
    }

    const Color& GetDividerColor() const
    {
        return dividerColor_;
    }

    const Dimension& GetTabBarShadowMargin() const
    {
        return tabBarShadowMargin_;
    }

    const Dimension& GetTabBarGradientWidth() const
    {
        return tabBarGradientWidth_;
    }

    const Color& GetColorBottomTabSubBg() const
    {
        return colorBottomTabSubBg_;
    }

    const Color& GetColorBottomTabSubBgBlur() const
    {
        return colorBottomTabSubBgBlur_;
    }

    const Dimension& GetTabBarColumnGutter() const
    {
        return tabBarColumnGutter_;
    }

    const Dimension& GetTabBarColumnMargin() const
    {
        return tabBarColumnMargin_;
    }

    const Dimension& GetHorizontalBottomTabMinWidth() const
    {
        return horizontalBottomTabMinWidth_;
    }

protected:
    TabTheme() = default;

private:
    Dimension labelPadding_;
    Dimension padding_;
    Dimension gradientWidth_;
    Dimension defaultHeight_;
    Dimension defaultWidth_;
    Dimension defaultItemHeight_;
    Color backgroundColor_;
    Color activeIndicatorColor_;
    Dimension activeIndicatorWidth_;
    Dimension activeIndicatorMinWidth_;
    Dimension activeIndicatorPadding_;
    Color focusIndicatorColor_;
    Dimension focusIndicatorRadius_;
    Dimension focusIndicatorHorizontalPadding_;
    Dimension focusIndicatorVerticalPadding_;
    Color subTabTextOffColor_;
    Dimension subTabIndicatorHeight_;
    Dimension subTabIndicatorGap_;
    Dimension subTabHorizontalPadding_;
    Dimension subTabTopPadding_;
    Dimension subTabBottomPadding_;
    Color subTabBarHoverColor_;
    Color subTabBarPressedColor_;
    Dimension subtabTextDefaultFontSize_;
    Dimension subtabLandscapeHorizontalPadding_;
    Dimension bottomTabHorizontalPadding_;
    Color bottomTabTextOn_;
    Color bottomTabTextOff_;
    Color bottomTabIconOn_;
    Color bottomTabIconOff_;
    Dimension bottomTabImageSize_;
    Dimension bottomTabTextSize_;
    std::string defaultTabBarName_;
    Dimension bottomTabBarSpace_;
    Dimension horizontalBottomTabBarSpace_;
    double subTabBarHoverDuration_;
    double subTabBarHoverToPressDuration_;
    double tabContentAnimationDuration_;
    Dimension tabBarDefaultHeight_;
    Dimension tabBarDefaultWidth_;
    Dimension subTabBarMinWidth_;
    Color dividerColor_;
    Dimension tabBarShadowMargin_;
    Dimension tabBarGradientWidth_;
    Color colorBottomTabSubBg_;
    Color colorBottomTabSubBgBlur_;
    Dimension tabBarColumnGutter_;
    Dimension tabBarColumnMargin_;
    Dimension horizontalBottomTabMinWidth_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_THEME_H
