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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * ToggleTheme defines color and styles of ToggleComponent. ToggleTheme should be built
 * using ToggleTheme::Builder.
 */
class ToggleTheme : public virtual Theme {
    DECLARE_ACE_TYPE(ToggleTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<ToggleTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<ToggleTheme> theme = AceType::Claim(new ToggleTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->backgroundColor_ = themeConstants->GetColor(THEME_TOGGLE_BACKGROUND_COLOR);
            theme->checkedColor_ = themeConstants->GetColor(THEME_TOGGLE_CHECKED_COLOR);
            theme->textStyle_.SetTextColor(themeConstants->GetColor(THEME_TOGGLE_TEXT_COLOR));
            theme->textStyle_.SetFontSize(themeConstants->GetDimension(THEME_TOGGLE_TEXT_FONTSIZE));
            theme->textStyle_.SetFontWeight(FontWeight(themeConstants->GetInt(THEME_TOGGLE_TEXT_FONTWEIGHT)));
            theme->height_ = themeConstants->GetDimension(THEME_TOGGLE_HEIGHT);
            theme->padding_ = Edge(themeConstants->GetDimension(THEME_TOGGLE_PADDING_HORIZONTAL).Value(),
                themeConstants->GetDimension(THEME_TOGGLE_PADDING_VERTICAL).Value(),
                themeConstants->GetDimension(THEME_TOGGLE_PADDING_HORIZONTAL).Value(),
                themeConstants->GetDimension(THEME_TOGGLE_PADDING_VERTICAL).Value(),
                themeConstants->GetDimension(THEME_TOGGLE_PADDING_VERTICAL).Unit());
            theme->disabledAlpha_ = themeConstants->GetDouble(THEME_TOGGLE_DISABLED_ALPHA);
            theme->pressedBlendColor_ = themeConstants->GetColor(THEME_TOGGLE_PRESSED_BLEND_COLOR);
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<ToggleTheme>& theme) const
        {
            if (!themeStyle) {
                return;
            }
            auto togglePattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>(THEME_PATTERN_TOGGLE, nullptr);
            if (!togglePattern) {
                return;
            }
            theme->backgroundColor_ = togglePattern->GetAttr<Color>(PATTERN_BG_COLOR, Color());
            theme->checkedColor_ = togglePattern->GetAttr<Color>("bg_color_checked", Color())
                .BlendOpacity(togglePattern->GetAttr<double>("bg_color_checked_alpha", 0.0));
            theme->textStyle_.SetTextColor(togglePattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color()));
            theme->pressedBlendColor_ = togglePattern->GetAttr<Color>("bg_color_pressed_blend", Color());
            theme->textMargin_ = togglePattern->GetAttr<Dimension>("text_margin", Dimension());
            theme->buttonMargin_ = togglePattern->GetAttr<Dimension>("button_margin", Dimension());
            theme->buttonHeight_ = togglePattern->GetAttr<Dimension>("button_height", Dimension());
            theme->buttonRadius_ = togglePattern->GetAttr<Dimension>("button_radius", Dimension());
            theme->textFontSize_ = togglePattern->GetAttr<Dimension>("text_font_size", Dimension());
            theme->textColor_ = togglePattern->GetAttr<Color>("text_color", Color());
        }
    };

    ~ToggleTheme() override = default;

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetCheckedColor() const
    {
        return checkedColor_;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Color& GetPressedBlendColor() const
    {
        return pressedBlendColor_;
    }

    double GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

    const Dimension& GetTextMargin() const
    {
        return textMargin_;
    }

    const Dimension& GetButtonMargin() const
    {
        return buttonMargin_;
    }

    const Dimension& GetButtonHeight() const
    {
        return buttonHeight_;
    }

    const Dimension& GetButtonRadius() const
    {
        return buttonRadius_;
    }

    const Dimension& GetTextFontSize() const
    {
        return textFontSize_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }


protected:
    ToggleTheme() = default;

private:
    Color backgroundColor_;
    Color checkedColor_;
    Color pressedBlendColor_;
    TextStyle textStyle_;
    Dimension height_;
    Edge padding_;
    double disabledAlpha_ { 1.0 };
    Dimension textMargin_;
    Dimension buttonMargin_;
    Dimension buttonHeight_;
    Dimension buttonRadius_;
    Dimension textFontSize_;
    Color textColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H
