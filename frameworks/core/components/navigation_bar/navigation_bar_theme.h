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
#include "base/resource/internal_resource.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/property/border_property.h"

namespace OHOS::Ace {
class ThemeConstants;
class ThemeStyle;
}

namespace OHOS::Ace::NG {
inline Dimension SINGLE_LINE_TITLEBAR_HEIGHT = 56.0_vp;
inline Dimension DOUBLE_LINE_TITLEBAR_HEIGHT = 82.0_vp;
inline Dimension FULL_SINGLE_LINE_TITLEBAR_HEIGHT = 112.0_vp;
inline Dimension FULL_DOUBLE_LINE_TITLEBAR_HEIGHT = 138.0_vp;
inline uint32_t TITLEBAR_MAX_LINES = 2;
inline Dimension MIN_ADAPT_SUBTITLE_FONT_SIZE = 10.0_fp;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace {

class NavigationBarTheme : public virtual Theme {
    DECLARE_ACE_TYPE(NavigationBarTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<NavigationBarTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const;

    protected:
        void InitTheme(const RefPtr<NavigationBarTheme>& theme, const RefPtr<ThemeConstants>& themeConstants) const;

    private:
        void SetSymbolTheme(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<NavigationBarTheme>& theme) const;
        void ParsePattern(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<NavigationBarTheme>& theme) const;
        void SetToolBarTheme(RefPtr<ThemeStyle> pattern, const RefPtr<NavigationBarTheme>& theme) const;
        void SetNavigationTokenTheme(RefPtr<ThemeStyle> pattern, const RefPtr<NavigationBarTheme>& theme) const;
        void ParsePatternContinue(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<NavigationBarTheme>& theme) const;
    };

    ~NavigationBarTheme() override = default;

    const Color& GetTitleColor() const
    {
        return titleColor_;
    }

    void SetTitleColor(const Color& color)
    {
        titleColor_ = color;
    }

    const Color& GetSubTitleColor() const
    {
        return subTitleColor_;
    }

    void SetSubTitleColor(const Color& color)
    {
        subTitleColor_ = color;
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
    void SetMenuIconColor(const Color& color)
    {
        menuIconColor_ = color;
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

    void SetBackButtonIconColor(const Color& color)
    {
        backButtonIconColor_ = color;
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
    void SetToolBarDividerColor(const Color& color)
    {
        toolbarDividerColor_ = color;
    }
    const Color& GetToolBarItemFocusColor() const
    {
        return toolbarItemFocusBorderColor_;
    }
    void SetToolBarItemFocusColor(const Color& color)
    {
        toolbarItemFocusBorderColor_ = color;
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
    void SetToolBarItemFontColor(const Color& color)
    {
        toolbarItemFontColor_ = color;
    }
    double GetToolbarItemDisabledAlpha() const
    {
        return toolbarItemDisabledAlpha_;
    }
    const Color& GetToolbarIconColor() const
    {
        return toolbarIconColor_;
    }
    void SetToolbarIconColor(const Color& color)
    {
        toolbarIconColor_ = color;
    }
    const Dimension& GetToolbarIconSize() const
    {
        return toolbarIconSize_;
    }
    const Color& GetToolbarActiveIconColor() const
    {
        return toolbarActiveIconColor_;
    }
    void SetToolbarActiveIconColor(const Color& color)
    {
        toolbarActiveIconColor_ = color;
    }
    const Color& GetToolBarItemActiveFontColor() const
    {
        return toolbarActiveTextColor_;
    }
    void SetToolBarItemActiveFontColor(const Color& color)
    {
        toolbarActiveTextColor_ = color;
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
    const Dimension& GetToolbarItemIconHideTextTopPadding() const
    {
        return toolbarItemIconTopHideTextPadding_;
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
    void SetNavigationDividerColor(const Color& color)
    {
        navigationDividerColor_ = color;
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
    void SetMainTitleFontColor(const Color& color)
    {
        mainTitleFontColor_ = color;
    }
    const Color& GetSubTitleFontColor() const
    {
        return subTitleFontColor_;
    }
    void SetSubTitleFontColor(const Color& color)
    {
        subTitleFontColor_ = color;
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
    void SetIconColor(const Color& color)
    {
        iconColor_ = color;
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
    void SetToolbarBgColor(const Color& color)
    {
        toolbarBgColor_ = color;
        toolbarBgColorWithOpacity_ = toolbarBgColor_.BlendOpacity(toolbarBgAlpha_);
    }
    const std::string& GetNavigationBack() const
    {
        return navigationBack_;
    }
    const Dimension& GetIconBorderWidth() const
    {
        return iconBorderWidth_;
    }
    const Color& GetIconBorderColor() const
    {
        return iconBorderColor_;
    }
    const Dimension& GetMenuItemFocusPadding() const
    {
        return menuItemFocusPadding_;
    }
    const Color& GetNavigationFocusBlendBgColor() const
    {
        return navigationFocusBlendBgColor_;
    }
    const Dimension& NavigationMiniMinFontSize() const
    {
        return navigationMiniMinFontSize_;
    }
    const Dimension& NavigationFullMinFontSize() const
    {
        return navigationFullMinFontSize_;
    }
    const Dimension& GetMenuButtonPadding() const
    {
        return menuButtonPadding_;
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
    Dimension toolbarItemIconTopPadding_ = 2.0_vp;
    Dimension toolbarItemIconTopHideTextPadding_ = 8.0_vp;
    Dimension toolbarItemMargin_ = 4.0_vp;
    Dimension toolbarItemSpecialMargin_ = 0.0_vp;
    std::string moreMessage_ = "";
    std::string navigationBack_ = "";
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
    Dimension iconBorderWidth_ = 0.0_vp;
    Color iconBorderColor_;
    Dimension menuItemFocusPadding_ = 0.0_vp;
    Color navigationFocusBlendBgColor_;
    Dimension navigationMiniMinFontSize_ = 0.0_vp;
    Dimension navigationFullMinFontSize_ = 0.0_vp;
    Dimension menuButtonPadding_ = 0.0_vp;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NAVIGATION_BAR_NAVIGATION_BAR_THEME_H
