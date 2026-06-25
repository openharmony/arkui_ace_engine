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
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme.h"

namespace OHOS::Ace {
class ThemeConstants;
class ThemeStyle;

class TabTheme : public virtual Theme {
    DECLARE_ACE_TYPE(TabTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        static constexpr Dimension BOTTOM_BAR_HORIZONTAL_TEXT_SIZE = 12.0_vp;

        RefPtr<TabTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TabTheme>& theme) const;

    private:
        void ParsePattern2(const RefPtr<TabTheme>& theme, const RefPtr<ThemeStyle> pattern) const;
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

    const Color& GetSubTabTextOnColor() const
    {
        return subTabTextOnColor_;
    }

    const Color& GetSubTabTextOffColor() const
    {
        return subTabTextOffColor_;
    }

    const Color& GetSubTabBoardTextOnColor() const
    {
        return subTabBoardTextOnColor_;
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

    const Dimension& GetSubTabItemPadding() const
    {
        return subTabItemPadding_;
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

    const Color& GetBottomTabSymbolOn() const
    {
        return bottomTabSymbolOn_;
    }

    const Color& GetBottomTabSymbolOff() const
    {
        return bottomTabSymbolOff_;
    }

    const Dimension& GetBottomTabImageSize() const
    {
        return bottomTabImageSize_;
    }

    const Dimension& GetBottomTabTextSize() const
    {
        return bottomTabTextSize_;
    }

    const Dimension& GetBottomTabHorizontalTextSize() const
    {
        return bottomTabHorizontalTextSize_;
    }

    const int& GetBottomTabBackgroundBlurStyle() const
    {
        return bottomTabBackgroundBlurStyle_;
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

    float GetsubTabBarThirdLargeFontSizeScale() const
    {
        return subTabBarThirdLargeFontSizeScale_;
    }

    const Dimension& GetHorizontalBottomTabMinWidth() const
    {
        return horizontalBottomTabMinWidth_;
    }
    const Dimension& GetBottomTabBarDefaultWidth() const
    {
        return bottomTabBarDefaultHeight_;
    }
    const Dimension& GetDialogRadiusLevel10() const
    {
        return dialog_radius_level10_;
    }
    const Color& GetDialogIconColor() const
    {
        return dialog_iconColor_;
    }
    const Color& GetDialogFontColor() const
    {
        return dialog_fontColor_;
    }
    float GetSubTabBarBigFontSizeScale() const
    {
        return subTabBarBigFontSizeScale_;
    }
    float GetSubTabBarLargeFontSizeScale() const
    {
        return subTabBarLargeFontSizeScale_;
    }
    float GetSubTabBarMaxFontSizeScale() const
    {
        return subTabBarMaxFontSizeScale_;
    }
    float GetSubTabBarOriginFontSizeScale() const
    {
        return subTabBarOriginFontSizeScale_;
    }
    const Dimension& GetSubTabBarLeftRightMargin() const
    {
        return subTabBarLeftRightMargin_;
    }
    const Dimension& GetSubTabBarIndicatorstyleMarginTop() const
    {
        return subTabBarIndicatorstyleMarginTop_;
    }

    const Dimension& GetSubTabItemHorizontalPadding() const
    {
        return subTabItemHorizontalPadding_;
    }

    const Dimension& GetBoardFocusPadding() const
    {
        return focusBoardPadding_;
    }

    const Dimension& GetFocusPadding() const
    {
        return focusPadding_;
    }

    const Dimension& GetTabBarDefaultMargin() const
    {
        return tabBarDefaultMargin_;
    }

    const Color& GetTabBarFocusedColor() const
    {
        return tabBarFocusedColor_;
    }

    const Color& GetSubTabTextFocusedColor() const
    {
        return subTabTextFocusedColor_;
    }

    bool GetIsChangeFocusTextStyle() const
    {
        return isChangeFocusTextStyle_;
    }

    const Color& GetInteractiveFocusColor() const
    {
        return interactiveFocusColor_;
    }

    const Dimension& GetOutlineExtraLarger() const
    {
        return outlineExtraLarger_;
    }

    const Color& GetIconEmphasize() const
    {
        return iconEmphasize_;
    }
    const Color& GetIconPrimary() const
    {
        return iconPrimary_;
    }
    const Color& GetFontEmphasize() const
    {
        return fontEmphasize_;
    }
    const Color& GetFontPrimary() const
    {
        return fontPrimary_;
    }
    
protected:
    TabTheme() = default;

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
    Color subTabTextOnColor_;
    Color subTabTextOffColor_;
    Color subTabBoardTextOnColor_;
    Dimension subTabIndicatorHeight_;
    Dimension subTabIndicatorGap_;
    Dimension subTabHorizontalPadding_;
    Dimension subTabTopPadding_;
    Dimension subTabBottomPadding_;
    Dimension subTabItemPadding_;
    Color subTabBarHoverColor_;
    Color subTabBarPressedColor_;
    Dimension subtabTextDefaultFontSize_;
    Dimension subtabLandscapeHorizontalPadding_;
    Dimension bottomTabHorizontalPadding_;
    Color bottomTabTextOn_;
    Color bottomTabTextOff_;
    Color bottomTabIconOn_;
    Color bottomTabIconOff_;
    Color bottomTabSymbolOn_;
    Color bottomTabSymbolOff_;
    Dimension bottomTabImageSize_;
    Dimension bottomTabTextSize_;
    Dimension bottomTabHorizontalTextSize_;
    std::string defaultTabBarName_;
    Dimension bottomTabBarSpace_;
    Dimension horizontalBottomTabBarSpace_;
    double subTabBarHoverDuration_;
    double subTabBarHoverToPressDuration_;
    double tabContentAnimationDuration_;
    Dimension tabBarDefaultHeight_;
    Dimension bottomTabBarDefaultHeight_;
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
    Dimension dialog_radius_level10_;
    Color dialog_iconColor_;
    Color dialog_fontColor_;
    int bottomTabBackgroundBlurStyle_;
    float subTabBarBigFontSizeScale_ = 1.75f;
    float subTabBarLargeFontSizeScale_ = 2.0f;
    float subTabBarMaxFontSizeScale_ = 3.2f;
    float subTabBarOriginFontSizeScale_ = 1.0f;
    Dimension subTabBarLeftRightMargin_;
    Dimension subTabBarIndicatorstyleMarginTop_;
    float subTabBarThirdLargeFontSizeScale_ = 1.45f;
    Dimension tabBarDefaultMargin_;
    Dimension focusPadding_;
    Dimension subTabItemHorizontalPadding_;
    Dimension focusBoardPadding_;
    Color tabBarFocusedColor_;
    Color subTabTextFocusedColor_;
    bool isChangeFocusTextStyle_;
    Color interactiveFocusColor_;
    Dimension outlineExtraLarger_;
    Color iconEmphasize_;
    Color iconPrimary_;
    Color fontEmphasize_;
    Color fontPrimary_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TAB_THEME_H
