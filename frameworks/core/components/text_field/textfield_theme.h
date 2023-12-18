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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/radius.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

/**
 * TextFieldTheme defines color and styles of SliderComponent. TextFieldTheme should be built
 * using TextFieldTheme::Builder.
 */
class TextFieldTheme : public virtual Theme {
    DECLARE_ACE_TYPE(TextFieldTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<TextFieldTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<TextFieldTheme> theme = AceType::Claim(new TextFieldTheme());
            if (!themeConstants) {
                return theme;
            }
            ParsePattern(themeConstants->GetThemeStyle(), theme);
            return theme;
        }

    private:
        void ParsePattern(const RefPtr<ThemeStyle>& themeStyle, const RefPtr<TextFieldTheme>& theme) const
        {
            if (!themeStyle || !theme) {
                return;
            }
            auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("textfield_pattern", nullptr);
            if (!pattern) {
                LOGW("find pattern of textfield fail");
                return;
            }
            const double defaultErrorAlpha = 0.6;
            const double defaultUnderlineAlpha = 0.6;
            const double defaultDisableUnderlineAlpha = 0.4;
            const Color defaultUnderlineColor = Color(0x33182431);
            const Color defaultUnderlineTextColor = Color(0x99182431);
            const Color defaultCounterColor = Color(0x66182431);
            const Color overCounterColor = Color(0x99FA2A2D);
            theme->padding_ = Edge(pattern->GetAttr<Dimension>("textfield_padding_horizontal", 0.0_vp),
                pattern->GetAttr<Dimension>("textfield_padding_vertical", 0.0_vp),
                pattern->GetAttr<Dimension>("textfield_padding_horizontal", 0.0_vp),
                pattern->GetAttr<Dimension>("textfield_padding_vertical", 0.0_vp));
            theme->fontWeight_ =
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_font_weight", 0.0)));
            theme->borderRadius_ = Radius(pattern->GetAttr<Dimension>("textfield_border_radius", 0.0_vp));
            theme->disableOpacityRatio_ = pattern->GetAttr<double>("textfield_disable_opacity_ratio", 0.0);
            theme->overHideLength_ = pattern->GetAttr<Dimension>("textfield_over_hide_length", 0.0_vp);
            theme->cursorRadius_ = pattern->GetAttr<Dimension>("textfield_cursor_radius", 0.0_vp);
            theme->needFade_ = static_cast<bool>(pattern->GetAttr<double>("textfield_need_fade", 0.0));
            theme->iconSize_ = pattern->GetAttr<Dimension>("textfield_icon_size", 0.0_vp);
            theme->iconHotZoneSize_ = pattern->GetAttr<Dimension>("textfield_icon_hot_zone_size", 0.0_vp);
            theme->showEllipsis_ = static_cast<bool>(pattern->GetAttr<double>("textfield_show_ellipsis", 0.0));
            theme->errorSpacing_ = pattern->GetAttr<Dimension>("textfield_error_spacing", 0.0_vp);
            theme->errorIsInner_ = static_cast<bool>(pattern->GetAttr<double>("textfield_error_is_inner", 0.0));
            theme->errorBorderWidth_ = pattern->GetAttr<Dimension>("textfield_error_border_width", 0.0_vp);
            theme->errorTextStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_error_font_weight", 0.0))));
            theme->countTextStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_count_font_weight", 0.0))));
            theme->overCountStyle_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_over_count_font_weight", 0.0))));
            theme->countTextStyleOuter_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_count_font_weight", 0.0))));
            theme->overCountStyleOuter_.SetFontWeight(
                FontWeight(static_cast<int32_t>(pattern->GetAttr<double>("textfield_over_count_font_weight", 0.0))));
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 0.0_fp);
            theme->textColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color());
            theme->focusTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_FOCUSED, Color());
            theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color());
            theme->focusPlaceholderColor_ = pattern->GetAttr<Color>("tips_text_color_focused", Color());
            theme->bgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color());
            theme->focusBgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_FOCUSED, Color());
            // color of error border blend 60% opacity
            theme->errorBorderColor_ =
                pattern->GetAttr<Color>("error_text_border_color", Color())
                    .BlendOpacity(pattern->GetAttr<double>("error_text_border_color_alpha", defaultErrorAlpha));
            theme->errorUnderlineColor_ = pattern->GetAttr<Color>(ERROR_UNDERLINE_COLOR, Color());
            theme->underlineColor_ = pattern->GetAttr<Color>(UNDERLINE_COLOR, defaultUnderlineColor);
            theme->disableUnderlineColor_ =
                pattern->GetAttr<Color>(UNDERLINE_COLOR, defaultUnderlineColor)
                    .BlendOpacity(pattern->GetAttr<double>(DISABLE_UNDERLINE_ALPHA, defaultDisableUnderlineAlpha));
            theme->underlineTextColor_ = pattern->GetAttr<Color>(UNDERLINE_TEXT_COLOR, defaultUnderlineTextColor);
            theme->defaultCounterColor_ = pattern->GetAttr<Color>(DEFAULT_COUNTER_COLOR, defaultCounterColor);
            theme->overCounterColor_ = pattern->GetAttr<Color>(OVER_COUNTER_COLOR, overCounterColor);
            theme->underlineFontSize_ = pattern->GetAttr<Dimension>(UNDERLINE_FONT_SIZE, 0.0_fp);
            theme->errorTextStyle_.SetTextColor(pattern->GetAttr<Color>(ERROR_UNDERLINE_TEXT_COLOR, Color()));
            theme->errorTextStyle_.SetFontSize(pattern->GetAttr<Dimension>(ERROR_UNDERLINE_TEXT_SIZE, 0.0_fp));

            theme->countTextStyle_.SetTextColor(pattern->GetAttr<Color>("count_text_color", Color()));
            theme->countTextStyle_.SetFontSize(pattern->GetAttr<Dimension>("count_text_font_size", 0.0_fp));
            theme->overCountStyle_.SetTextColor(pattern->GetAttr<Color>("over_text_color", Color()));
            theme->overCountStyle_.SetFontSize(pattern->GetAttr<Dimension>("over_text_font_size", 0.0_fp));

            theme->countTextStyleOuter_.SetTextColor(pattern->GetAttr<Color>("count_outer_text_color", Color()));
            theme->countTextStyleOuter_.SetFontSize(pattern->GetAttr<Dimension>("count_outer_text_font_size", 0.0_fp));
            theme->overCountStyleOuter_.SetTextColor(pattern->GetAttr<Color>("over_outer_text_color", Color()));
            theme->overCountStyleOuter_.SetFontSize(pattern->GetAttr<Dimension>("over_outer_text_font_size", 0.0_fp));
            theme->overCountTextStyle_.SetTextColor(pattern->GetAttr<Color>(OVER_COUNT_TEXT_COLOR, Color()));
            theme->overCountTextStyle_.SetFontSize(pattern->GetAttr<Dimension>(OVER_COUNT_TEXT_FONT_SIZE, 0.0_fp));
            theme->selectedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, Color());
            theme->disableTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_DISABLED, Color());
            theme->underlineActivedColor_ =
                pattern->GetAttr<Color>(PATTERN_UNDERLINE_ACTIVED_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(UNDERLINE_COLOR_ALPHA, defaultUnderlineAlpha));
            theme->underlineTypingColor_ =
                pattern->GetAttr<Color>(PATTERN_UNDERLINE_TYPING_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(UNDERLINE_COLOR_ALPHA, defaultUnderlineAlpha));
            theme->textColorDisable_ = pattern->GetAttr<Color>(PATTERN_DISABLED_TEXT_COLOR, Color());
            theme->cursorColor_ = pattern->GetAttr<Color>("cursor_color", Color());
            theme->cursorWidth_ = pattern->GetAttr<Dimension>("cursor_width", 1.5_vp);
            theme->hoverColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_HOVERED, Color());
            theme->pressColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_PRESSED, Color());
            theme->borderRadiusSize_ = Radius(pattern->GetAttr<Dimension>(BORDER_RADIUS_SIZE, 20.0_vp));
            theme->disabledIconFillColor_ = theme->bgColor_.BlendOpacity(theme->disableOpacityRatio_);
            theme->passwordErrorTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color());
            theme->passwordErrorInputColor_ = pattern->GetAttr<Color>(ERROR_PASSWORD_INPUT_COLOR, Color());
            theme->passwordErrorBorderColor_ =
                pattern->GetAttr<Color>(ERROR_PASSWORD_BORDER_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(ERROR_PASSWORD_BORDER_ALPHA, defaultErrorAlpha));
            theme->passwordErrorLableColor_ = pattern->GetAttr<Color>(ERROR_PASSWORD_TEXT_COLOR, Color());
            theme->overCountBorderColor_ =
                pattern->GetAttr<Color>(OVER_COUNT_BORDER_COLOR, Color())
                    .BlendOpacity(pattern->GetAttr<double>(OVER_COUNT_BORDER_COLOR_ALPHA, defaultErrorAlpha));
            theme->inlineTextColor_ = pattern->GetAttr<Color>(INLINE_TEXT_COLOR, Color());
            theme->inlineRadiusSize_ = Radius(pattern->GetAttr<Dimension>(INLINE_RADIUS_SIZE, 4.0_vp));
            theme->inlineBgColor_ = pattern->GetAttr<Color>(INLINE_BG_COLOR, Color());
            theme->inlineBorderColor_ = pattern->GetAttr<Color>(INLINE_BORDER_COLOR, Color());
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
            theme->height_ = pattern->GetAttr<Dimension>("textinput_default_height", 48.0_vp);
        }
    };

    ~TextFieldTheme() override = default;

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const Dimension& GetFontSize() const
    {
        return fontSize_;
    }

    const Dimension& GetUnderlineFontSize() const
    {
        return underlineFontSize_;
    }

    const FontWeight& GetFontWeight() const
    {
        return fontWeight_;
    }

    const Radius& GetBorderRadius() const
    {
        return borderRadius_;
    }

    const Color& GetBgColor() const
    {
        return bgColor_;
    }

    const Color& GetPlaceholderColor() const
    {
        return placeholderColor_;
    }

    const Color& GetFocusBgColor() const
    {
        return focusBgColor_;
    }

    const Color& GetFocusPlaceholderColor() const
    {
        return focusPlaceholderColor_;
    }

    const Color& GetFocusTextColor() const
    {
        return focusTextColor_;
    }

    const Color& GetTextColor() const
    {
        return textColor_;
    }

    const Color& GetDisableTextColor() const
    {
        return disableTextColor_;
    }

    const Color& GetTextColorDisable() const
    {
        return textColorDisable_;
    }

    const Color& GetUnderlineActivedColor() const
    {
        return underlineActivedColor_;
    }

    const Color& GetUnderlineTypingColor() const
    {
        return underlineTypingColor_;
    }

    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }

    const Color& GetHoverColor() const
    {
        return hoverColor_;
    }

    const Color& GetPressColor() const
    {
        return pressColor_;
    }

    const Radius& GetBorderRadiusSize() const
    {
        return borderRadiusSize_;
    }

    double GetDisableOpacityRatio() const
    {
        return disableOpacityRatio_;
    }

    const Color& GetDisabledIconFillColor() const
    {
        return disabledIconFillColor_;
    }

    const Dimension& GetOverHideLength() const
    {
        return overHideLength_;
    }

    const Color& GetCursorColor() const
    {
        return cursorColor_;
    }

    const Dimension& GetCursorRadius() const
    {
        return cursorRadius_;
    }

    const Dimension& GetCursorWidth() const
    {
        return cursorWidth_;
    }

    bool NeedFade() const
    {
        return needFade_;
    }

    const Dimension& GetIconSize() const
    {
        return iconSize_;
    }

    const Dimension& GetIconHotZoneSize() const
    {
        return iconHotZoneSize_;
    }

    bool ShowEllipsis() const
    {
        return showEllipsis_;
    }

    const Dimension& GetErrorSpacing() const
    {
        return errorSpacing_;
    }

    bool GetErrorIsInner() const
    {
        return errorIsInner_;
    }

    const Dimension& GetErrorBorderWidth() const
    {
        return errorBorderWidth_;
    }

    const Color& GetErrorBorderColor() const
    {
        return errorBorderColor_;
    }

    const Color& GetErrorUnderlineColor() const
    {
        return errorUnderlineColor_;
    }

    const Color& GetUnderlineColor() const
    {
        return underlineColor_;
    }

    const Color& GetDisableUnderlineColor() const
    {
        return disableUnderlineColor_;
    }

    const Color& GetUnderlineTextColor() const
    {
        return underlineTextColor_;
    }

    const Color& GetOverCountBorderColor() const
    {
        return overCountBorderColor_;
    }

    const TextStyle& GetErrorTextStyle() const
    {
        return errorTextStyle_;
    }

    const TextStyle& GetCountTextStyle() const
    {
        return countTextStyle_;
    }

    const TextStyle& GetOverCountStyle() const
    {
        return overCountStyle_;
    }

    const TextStyle& GetCountTextStyleOuter() const
    {
        return countTextStyleOuter_;
    }

    const TextStyle& GetOverCountStyleOuter() const
    {
        return overCountStyleOuter_;
    }

    const Color& GetPasswordErrorTextColor() const
    {
        return passwordErrorTextColor_;
    }

    const Color& GetPasswordErrorInputColor() const
    {
        return passwordErrorInputColor_;
    }

    const Color& GetPasswordErrorBorderColor() const
    {
        return passwordErrorBorderColor_;
    }

    const Color& GetPasswordErrorLableColor() const
    {
        return passwordErrorLableColor_;
    }

    const TextStyle& GetOverCountTextStyle() const
    {
        return overCountTextStyle_;
    }

    const Color& GetInlineTextColor() const
    {
        return inlineTextColor_;
    }

    const Radius& GetInlineRadiusSize() const
    {
        return inlineRadiusSize_;
    }

    const Color& GetInlineBgColor() const
    {
        return inlineBgColor_;
    }

    const Color& GetInlineBorderColor() const
    {
        return inlineBorderColor_;
    }

    const Dimension& GetInlineBorderWidth() const
    {
        return inlineBorderWidth_;
    }

    bool GetDraggable() const
    {
        return draggable_;
    }

    const Color& GetDefaultCounterColor() const
    {
        return defaultCounterColor_;
    }

    const Color& GetOverCounterColor() const
    {
        return overCounterColor_;
    }

    const Dimension& GetPasswordTypeHeight() const
    {
        return passwordTypeHeight_;
    }

protected:
    TextFieldTheme() = default;

private:
    Edge padding_;
    Dimension height_;
    Dimension fontSize_;
    Dimension underlineFontSize_;
    FontWeight fontWeight_ = FontWeight::NORMAL;
    Radius borderRadius_;

    Color bgColor_;
    Radius borderRadiusSize_;
    Color placeholderColor_;
    Color focusBgColor_;
    Color focusPlaceholderColor_;
    Color focusTextColor_;
    Color textColor_;
    Color disableTextColor_;
    Color underlineActivedColor_;
    Color underlineTypingColor_;
    Color textColorDisable_;
    Color selectedColor_;
    Color hoverColor_;
    Color pressColor_;
    Color disabledIconFillColor_;
    Dimension errorSpacing_;
    bool errorIsInner_ = false;
    Dimension errorBorderWidth_;
    Color errorBorderColor_;
    Color overCountBorderColor_;
    Color errorUnderlineColor_;
    Color underlineColor_;
    Color disableUnderlineColor_;
    Color underlineTextColor_;
    Color passwordErrorTextColor_;
    Color passwordErrorInputColor_;
    Color passwordErrorBorderColor_;
    Color passwordErrorLableColor_;
    TextStyle errorTextStyle_;
    TextStyle countTextStyle_;
    TextStyle overCountStyle_;
    TextStyle countTextStyleOuter_;
    TextStyle overCountStyleOuter_;
    TextStyle overCountTextStyle_;
    Color inlineTextColor_;
    Radius inlineRadiusSize_;
    Color inlineBgColor_;
    Color inlineBorderColor_;
    Color defaultCounterColor_;
    Color overCounterColor_;

    // UX::disable state: opacity is set to 38% of the default
    double disableOpacityRatio_ = 1.0;

    // UX::over length state
    Dimension overHideLength_;

    // UX::cursor state cursor-color=#000000, cursor blur-radius=0.9, cursor-width=2, cursor-height=24, cursor-radius=1
    Color cursorColor_;
    Dimension cursorRadius_;
    Dimension cursorWidth_;
    bool needFade_ = false;

    // UX::icon size = 24, hotZoneSize = 36
    Dimension iconSize_;
    Dimension iconHotZoneSize_;
    Dimension inlineBorderWidth_ = 2.0_vp;

    bool showEllipsis_ = true;
    bool draggable_ = false;
    Dimension passwordTypeHeight_ = 40.0_vp;;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H
