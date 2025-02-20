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
            ParsePattern(themeConstants, theme);
            return theme;
        }

    protected:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<ToggleTheme>& theme) const
        {
            RefPtr<ThemeStyle> togglePattern = themeConstants->GetPatternByName(THEME_PATTERN_TOGGLE);
            if (!togglePattern) {
                return;
            }
            theme->textStyle_.SetFontSize(togglePattern->GetAttr<Dimension>("toggle_text_font_size", 0.0_fp));
            theme->textStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(togglePattern->GetAttr<double>("toggle_text_font_weight", 0.0))));
            theme->height_ = togglePattern->GetAttr<Dimension>("toggle_height", 0.0_vp);
            theme->padding_ = Edge(togglePattern->GetAttr<Dimension>("toggle_padding_horizontal", 0.0_vp).Value(),
                togglePattern->GetAttr<Dimension>("toggle_padding_vertical", 0.0_vp).Value(),
                togglePattern->GetAttr<Dimension>("toggle_padding_horizontal", 0.0_vp).Value(),
                togglePattern->GetAttr<Dimension>("toggle_padding_vertical", 0.0_vp).Value(),
                togglePattern->GetAttr<Dimension>("toggle_padding_vertical", 0.0_vp).Unit());
            theme->disabledAlpha_ = togglePattern->GetAttr<double>("toggle_disable_alpha", 0.0);
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
            theme->shadowNormal_ = static_cast<uint32_t>(
                togglePattern->GetAttr<double>("shadow_default_status_button", SHADOW_NONE));
            theme->shadowFocus_ = static_cast<uint32_t>(
                togglePattern->GetAttr<double>("shadow_focus_status_button", SHADOW_NONE));
            theme->scaleFocus_ = togglePattern->GetAttr<double>("scale_focus_status_button", 1.0);
            theme->borderWidth_ = togglePattern->GetAttr<Dimension>("border_width_status_button", Dimension());
            theme->borderColorChecked_ = togglePattern->GetAttr<Color>("border_color_status_button_checked", Color());
            theme->borderColorUnchecked_ = togglePattern->GetAttr<Color>(
                "border_color_status_button_unchecked", Color());
            theme->bgColorFocusChecked_ = togglePattern->GetAttr<Color>(
                "bg_color_focus_status_button_checked", Color())
                .BlendOpacity(togglePattern->GetAttr<double>("bg_color_checked_focus_alpha", 0.0));
            theme->bgColorFocusUnchecked_ = togglePattern->GetAttr<Color>(
                "bg_color_focus_status_button_unchecked", Color());
            theme->textColorFocus_ = togglePattern->GetAttr<Color>("status_button_text_color_focus", Color());
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

    const Dimension& GetBorderWidth() const
    {
        return borderWidth_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Color& GetTextColorFocus() const
    {
        return textColorFocus_;
    }

    const Color& GetBorderColorChecked() const
    {
        return borderColorChecked_;
    }

    const Color& GetBorderColorUnchecked() const
    {
        return borderColorUnchecked_;
    }

    const Color& GetBackgroundColorFocusChecked() const
    {
        return bgColorFocusChecked_;
    }

    const Color& GetBackgroundColorFocusUnchecked() const
    {
        return bgColorFocusUnchecked_;
    }

    uint32_t GetShadowNormal() const
    {
        return shadowNormal_;
    }

    uint32_t GetShadowFocus() const
    {
        return shadowFocus_;
    }

    float GetScaleFocus() const
    {
        return scaleFocus_;
    }

protected:
    ToggleTheme() = default;
    Color backgroundColor_;
    Color checkedColor_;

private:
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
    Dimension borderWidth_;
    Color textColor_;
    Color borderColorUnchecked_;
    Color borderColorChecked_;
    Color bgColorFocusChecked_;
    Color bgColorFocusUnchecked_;
    Color textColorFocus_;
    uint32_t shadowNormal_;
    uint32_t shadowFocus_;
    float scaleFocus_;
    static constexpr double SHADOW_NONE = 6.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TOGGLE_TOGGLE_THEME_H
