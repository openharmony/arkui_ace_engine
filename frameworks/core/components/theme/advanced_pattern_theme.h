/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_ADVANCED_PATTERN_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_ADVANCED_PATTERN_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {
/**
 * AdvancePatternTheme defines color and styles of advancedPatternComponent. AdvancePatternTheme should be built
 * using AdvancePatternTheme::Builder.
 */
class AdvancedPatternTheme : public virtual Theme {
    DECLARE_ACE_TYPE(AdvancedPatternTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        static constexpr Dimension DEFAULT_DIMENSION = 0.0_vp;

        RefPtr<AdvancedPatternTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<AdvancedPatternTheme> theme = AceType::MakeRefPtr<AdvancedPatternTheme>();
            if (!themeConstants) {
                return theme;
            }
            ParseColorPattern(themeConstants, theme);
            ParseDimensionPattern(themeConstants, theme);
            return theme;
        }

    private:
        void ParseColorPattern(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<AdvancedPatternTheme>& theme) const
        {
            RefPtr<ThemeStyle> advancedPattern = themeConstants->GetPatternByName(THEME_PATTERN_ADVANCED_PATTERN);
            if (!advancedPattern) {
                return;
            }

            theme->primaryTextColor_ = advancedPattern->GetAttr<Color>("text_color_primary", Color());
            theme->secondaryTextColor_ = advancedPattern->GetAttr<Color>("text_color_secondary", Color());
            theme->activatedColor_ = advancedPattern->GetAttr<Color>("text_primary_activated", Color());
            theme->primaryColor_ = advancedPattern->GetAttr<Color>("color_primary", Color());
            theme->clickColor_ = advancedPattern->GetAttr<Color>("color_click_effect", Color());
            theme->titleBarColor_ = advancedPattern->GetAttr<Color>("color_titlebar_text", Color());
            theme->hoverColor_ = advancedPattern->GetAttr<Color>("color_hover", Color());
            theme->focusedColor_ = advancedPattern->GetAttr<Color>("color_focused_outline", Color());
            theme->subTitleBarColor_ = advancedPattern->GetAttr<Color>("color_titlebar_subtitle_text", Color());
            theme->titleIconColor_ = advancedPattern->GetAttr<Color>("color_titlebar_icon", Color());
            theme->textOffColor_ = advancedPattern->GetAttr<Color>("color_titlebar_text_off", Color());
            theme->tertiaryColor_ = advancedPattern->GetAttr<Color>("color_tertiary", Color());
            theme->fourthColor_ = advancedPattern->GetAttr<Color>("color_fourth", Color());
            theme->separatorColor_ = advancedPattern->GetAttr<Color>("color_list_separator", Color());
            theme->toolBarTextColor_ = advancedPattern->GetAttr<Color>("color_toolbar_text", Color());
            theme->toolBarIconColor_ = advancedPattern->GetAttr<Color>("color_toolbar_icon", Color());
            theme->iconActivedColor_ = advancedPattern->GetAttr<Color>("color_toolbar_icon_actived", Color());
            theme->textActivedColor_ = advancedPattern->GetAttr<Color>("color_toolbar_text_actived", Color());
            theme->toolBarSubBgColor_ = advancedPattern->GetAttr<Color>("color_toolbar_sub_bg", Color());
            theme->toolBarBgColor_ = advancedPattern->GetAttr<Color>("color_toolbar_bg", Color());
            theme->buttonNormalColor_ = advancedPattern->GetAttr<Color>("color_button_normal", Color());
            theme->progressColor_ = advancedPattern->GetAttr<Color>("color_progress", Color());
            theme->emphasizeColor_ = advancedPattern->GetAttr<Color>("color_emphasize", Color());
            theme->primaryContrary_ = advancedPattern->GetAttr<Color>("color_text_primary_contrary", Color());
        }

        void ParseDimensionPattern(
            const RefPtr<ThemeConstants>& themeConstants, const RefPtr<AdvancedPatternTheme>& theme) const
        {
            RefPtr<ThemeStyle> advancedPattern = themeConstants->GetPatternByName(THEME_PATTERN_ADVANCED_PATTERN);
            if (!advancedPattern) {
                return;
            }

            theme->dialogTitleSize_ = advancedPattern->GetAttr<Dimension>("text_size_dialog_tittle", DEFAULT_DIMENSION);
            theme->subTitleSize_ = advancedPattern->GetAttr<Dimension>("text_size_sub_title3", DEFAULT_DIMENSION);
            theme->subTitleTextSize_ = advancedPattern->GetAttr<Dimension>("text_size_sub_title2", DEFAULT_DIMENSION);
            theme->textButtonSize_ = advancedPattern->GetAttr<Dimension>("text_size_button1", DEFAULT_DIMENSION);
            theme->buttonTextSize_ = advancedPattern->GetAttr<Dimension>("text_size_button2", DEFAULT_DIMENSION);
            theme->maxPaddingStart_ = advancedPattern->GetAttr<Dimension>("max_padding_start", DEFAULT_DIMENSION);
            theme->maxPaddingEnd_ = advancedPattern->GetAttr<Dimension>("max_padding_end", DEFAULT_DIMENSION);
            theme->paddingStart_ = advancedPattern->GetAttr<Dimension>("default_padding_start", DEFAULT_DIMENSION);
            theme->paddingEnd_ = advancedPattern->GetAttr<Dimension>("default_padding_end", DEFAULT_DIMENSION);
            theme->clickRadius_ = advancedPattern->GetAttr<Dimension>("corner_radius_clicked", DEFAULT_DIMENSION);
            theme->textMargin_ = advancedPattern->GetAttr<Dimension>("text_margin_horizontal", DEFAULT_DIMENSION);
            theme->textBody_ = advancedPattern->GetAttr<Dimension>("text_size_body1", DEFAULT_DIMENSION);
            theme->textBodySize_ = advancedPattern->GetAttr<Dimension>("text_size_body2", DEFAULT_DIMENSION);
            theme->sizeCaption_ = advancedPattern->GetAttr<Dimension>("text_size_caption", DEFAULT_DIMENSION);
            theme->overLineSize_ = advancedPattern->GetAttr<Dimension>("text_size_over_line", DEFAULT_DIMENSION);
            theme->headerSize_ = advancedPattern->GetAttr<Dimension>("text_size_headline7", DEFAULT_DIMENSION);
            theme->headerLineSize_ = advancedPattern->GetAttr<Dimension>("text_size_headline8", DEFAULT_DIMENSION);
            theme->headerTextSize_ = advancedPattern->GetAttr<Dimension>("text_size_headline9", DEFAULT_DIMENSION);
            theme->radiusDialog_ = advancedPattern->GetAttr<Dimension>("corner_radius_dialog", DEFAULT_DIMENSION);
            theme->radiusSubtab_ = advancedPattern->GetAttr<Dimension>("corner_radius_subtab", DEFAULT_DIMENSION);
        }
    };

    ~AdvancedPatternTheme() override = default;

    const Color& GetPrimaryTextColor() const
    {
        return primaryTextColor_;
    }

    const Color& GetSecondaryTextColor() const
    {
        return secondaryTextColor_;
    }

    const Color& GetActivatedColor() const
    {
        return activatedColor_;
    }

    const Color& GetPrimaryColor() const
    {
        return primaryColor_;
    }

    const Color& GetClickColor() const
    {
        return clickColor_;
    }

    const Color& GetTitleBarColor() const
    {
        return titleBarColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetFocusedColor() const
    {
        return focusedColor_;
    }

    const Color& GetSubTitleBarColor() const
    {
        return subTitleBarColor_;
    }

    const Color& GetTitleIconColor() const
    {
        return titleIconColor_;
    }

    const Color& GetTextOffColor() const
    {
        return textOffColor_;
    }

    const Color& GetTertiaryColor() const
    {
        return tertiaryColor_;
    }

    const Color& GetFourthColor() const
    {
        return fourthColor_;
    }

    const Color& GetSeparatorColor() const
    {
        return separatorColor_;
    }

    const Color& GetToolBarTextColor() const
    {
        return toolBarTextColor_;
    }

    const Color& GetToolBarIconColor() const
    {
        return toolBarIconColor_;
    }

    const Color& GetIconActivedColor() const
    {
        return iconActivedColor_;
    }

    const Color& GetTextActivedColor() const
    {
        return textActivedColor_;
    }

    const Color& GetToolBarSubBgColor() const
    {
        return toolBarSubBgColor_;
    }

    const Color& GetToolBarBgColor() const
    {
        return toolBarBgColor_;
    }

    const Color& GetButtonNormal() const
    {
        return buttonNormalColor_;
    }

    const Color& GetProgress() const
    {
        return progressColor_;
    }

    const Color& GetEmphasizeColor() const
    {
        return emphasizeColor_;
    }

    const Color& GetPrimaryContrary() const
    {
        return primaryContrary_;
    }

    const Dimension& GetDialogTitleSize() const
    {
        return dialogTitleSize_;
    }

    const Dimension& GetSubTitleSize() const
    {
        return subTitleSize_;
    }

    const Dimension& GetSubTitleTextSize() const
    {
        return subTitleTextSize_;
    }

    const Dimension& GetTextButtonSize() const
    {
        return textButtonSize_;
    }

    const Dimension& GetButtonTextSize() const
    {
        return buttonTextSize_;
    }

    const Dimension& GetMaxPaddingStart() const
    {
        return maxPaddingStart_;
    }

    const Dimension& GetMaxPaddingEnd() const
    {
        return maxPaddingEnd_;
    }

    const Dimension& GetPaddingStart() const
    {
        return paddingStart_;
    }

    const Dimension& GetPaddingEnd() const
    {
        return paddingEnd_;
    }

    const Dimension& GetClickRadius() const
    {
        return clickRadius_;
    }

    const Dimension& GetTextMargin() const
    {
        return textMargin_;
    }

    const Dimension& GetTextBody() const
    {
        return textBody_;
    }

    const Dimension& GetTextBodySize() const
    {
        return textBodySize_;
    }

    const Dimension& GetSizeCaption() const
    {
        return sizeCaption_;
    }

    const Dimension& GetOverLineSize() const
    {
        return overLineSize_;
    }

    const Dimension& GetHeaderSize() const
    {
        return headerSize_;
    }

    const Dimension& GetHeaderLineSize() const
    {
        return headerLineSize_;
    }

    const Dimension& GetHeaderTextSize() const
    {
        return headerTextSize_;
    }

    const Dimension& GetRadiusDialog() const
    {
        return radiusDialog_;
    }

    const Dimension& GetRadiusSubtab() const
    {
        return radiusSubtab_;
    }

protected:
    AdvancedPatternTheme() = default;

private:

    Color primaryTextColor_;
    Color secondaryTextColor_;
    Color activatedColor_;
    Color primaryColor_;
    Color clickColor_;
    Color titleBarColor_;
    Color hoverColor_;
    Color focusedColor_;
    Color subTitleBarColor_;
    Color titleIconColor_;
    Color textOffColor_;
    Color tertiaryColor_;
    Color fourthColor_;
    Color separatorColor_;
    Color toolBarTextColor_;
    Color toolBarIconColor_;
    Color iconActivedColor_;
    Color textActivedColor_;
    Color toolBarSubBgColor_;
    Color toolBarBgColor_;
    Color buttonNormalColor_;
    Color progressColor_;
    Color emphasizeColor_;
    Color primaryContrary_;
    Dimension dialogTitleSize_;
    Dimension maxPaddingStart_;
    Dimension maxPaddingEnd_;
    Dimension paddingStart_;
    Dimension paddingEnd_;
    Dimension subTitleSize_;
    Dimension subTitleTextSize_;
    Dimension textButtonSize_;
    Dimension buttonTextSize_;
    Dimension clickRadius_;
    Dimension textMargin_;
    Dimension textBody_;
    Dimension textBodySize_;
    Dimension sizeCaption_;
    Dimension overLineSize_;
    Dimension headerSize_;
    Dimension headerLineSize_;
    Dimension headerTextSize_;
    Dimension radiusDialog_;
    Dimension radiusSubtab_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_THEME_ADVANCED_PATTERN_THEME_H