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
            // init theme from global data
            theme->padding_ = Edge(themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_VERTICAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_HORIZONTAL),
                themeConstants->GetDimension(THEME_TEXTFIELD_PADDING_VERTICAL));
            theme->height_ = themeConstants->GetDimension(THEME_TEXTFIELD_HEIGHT);
            theme->fontSize_ = themeConstants->GetDimension(THEME_TEXTFIELD_FONT_SIZE);
            theme->fontWeight_ = FontWeight(themeConstants->GetInt(THEME_TEXTFIELD_FONT_WEIGHT));
            theme->borderRadius_ = Radius(themeConstants->GetDimension(THEME_TEXTFIELD_BORDER_RADIUS));

            theme->bgColor_ = themeConstants->GetColor(THEME_TEXTFIELD_BACKGROUND_COLOR);
            theme->placeholderColor_ = themeConstants->GetColor(THEME_TEXTFIELD_PLACEHOLDER_COLOR);
            theme->textColor_ = themeConstants->GetColor(THEME_TEXTFIELD_TEXT_COLOR);
            theme->selectedColor_ = themeConstants->GetColor(THEME_TEXTFIELD_TEXT_SELECTED_COLOR);
            theme->hoverColor_ = themeConstants->GetColor(THEME_TEXTFIELD_HOVER_COLOR);
            theme->pressColor_ = themeConstants->GetColor(THEME_TEXTFIELD_PRESS_COLOR);

            theme->focusBgColor_ = themeConstants->GetColor(THEME_TEXTFIELD_FOCUS_BACKGROUND_COLOR);
            theme->focusPlaceholderColor_ = themeConstants->GetColor(THEME_TEXTFIELD_FOCUS_PLACEHOLDER_COLOR);
            theme->focusTextColor_ = themeConstants->GetColor(THEME_TEXTFIELD_FOCUS_TEXT_COLOR);

            theme->disableOpacityRatio_ = themeConstants->GetDouble(THEME_TEXTFIELD_DISABLE_OPACITY_RATIO);
            theme->disableTextColor_ = themeConstants->GetColor(THEME_TEXTFIELD_TEXT_COLOR_DISABLE);

            theme->overHideLength_ = themeConstants->GetDimension(THEME_TEXTFIELD_OVER_HIDE_LENGTH);

            theme->cursorColor_ = themeConstants->GetColor(THEME_TEXTFIELD_CURSOR_COLOR);
            theme->cursorRadius_ = themeConstants->GetDimension(THEME_TEXTFIELD_CURSOR_RADIUS);
            theme->needFade_ = static_cast<bool>(themeConstants->GetInt(THEME_TEXTFIELD_NEED_FADE));

            theme->iconSize_ = themeConstants->GetDimension(THEME_TEXTFIELD_ICON_SIZE);
            theme->iconHotZoneSize_ = themeConstants->GetDimension(THEME_TEXTFIELD_ICON_HOT_ZONE_SIZE);

            theme->showEllipsis_ = static_cast<bool>(themeConstants->GetInt(THEME_TEXTFIELD_SHOW_ELLIPSIS));

            theme->errorSpacing_ = themeConstants->GetDimension(THEME_TEXTFIELD_ERROR_SPACING);
            theme->errorIsInner_ = static_cast<bool>(themeConstants->GetInt(THEME_TEXTFIELD_ERROR_IS_INNER));
            theme->errorBorderWidth_ = themeConstants->GetDimension(THEME_TEXTFIELD_ERROR_BORDER_WIDTH);
            theme->errorBorderColor_ = themeConstants->GetColor(THEME_TEXTFIELD_ERROR_BORDER_COLOR);
            theme->errorTextStyle_.SetTextColor(themeConstants->GetColor(THEME_TEXTFIELD_ERROR_COLOR));
            theme->errorTextStyle_.SetFontSize(themeConstants->GetDimension(THEME_TEXTFIELD_ERROR_FONT_SIZE));
            theme->errorTextStyle_.SetFontWeight(FontWeight(themeConstants->GetInt(THEME_TEXTFIELD_ERROR_FONT_WEIGHT)));

            theme->countTextStyle_.SetTextColor(themeConstants->GetColor(THEME_TEXTFIELD_COUNT_TEXT_COLOR));
            theme->countTextStyle_.SetFontSize(themeConstants->GetDimension(THEME_TEXTFIELD_COUNT_FONT_SIZE));
            theme->countTextStyle_.SetFontWeight(
                FontWeight(themeConstants->GetInt(THEME_TEXTFIELD_COUNT_FONT_WEIGHT)));
            theme->overCountStyle_.SetTextColor(themeConstants->GetColor(THEME_TEXTFIELD_OVER_COUNT_TEXT_COLOR));
            theme->overCountStyle_.SetFontSize(themeConstants->GetDimension(THEME_TEXTFIELD_OVER_COUNT_FONT_SIZE));
            theme->overCountStyle_.SetFontWeight(
                FontWeight(themeConstants->GetInt(THEME_TEXTFIELD_OVER_COUNT_FONT_WEIGHT)));

            theme->countTextStyleOuter_.SetTextColor(themeConstants->GetColor(THEME_TEXTFIELD_COUNT_TEXT_COLOR));
            theme->countTextStyleOuter_.SetFontSize(
                themeConstants->GetDimension(THEME_TEXTFIELD_COUNT_FONT_SIZE_OUTER));
            theme->countTextStyleOuter_.SetFontWeight(
                FontWeight(themeConstants->GetInt(THEME_TEXTFIELD_COUNT_FONT_WEIGHT)));
            theme->overCountStyleOuter_.SetTextColor(themeConstants->GetColor(THEME_TEXTFIELD_OVER_COUNT_TEXT_COLOR));
            theme->overCountStyleOuter_.SetFontSize(
                themeConstants->GetDimension(THEME_TEXTFIELD_COUNT_FONT_SIZE_OUTER));
            theme->overCountStyleOuter_.SetFontWeight(
                FontWeight(themeConstants->GetInt(THEME_TEXTFIELD_OVER_COUNT_FONT_WEIGHT)));

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
            theme->fontSize_ = pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 0.0_fp);
            theme->textColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color());
            theme->focusTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_FOCUSED, Color());
            theme->placeholderColor_ = pattern->GetAttr<Color>("tips_text_color", Color());
            theme->focusPlaceholderColor_ = pattern->GetAttr<Color>("tips_text_color_focused", Color());
            theme->bgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR, Color());
            theme->focusBgColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_FOCUSED, Color());
            // color of error border blend 60% opacity
            theme->errorBorderColor_ = pattern->GetAttr<Color>("error_text_border_color", Color())
                .BlendOpacity(pattern->GetAttr<double>("error_text_border_color_alpha", defaultErrorAlpha));
            theme->errorUnderlineColor_ = pattern->GetAttr<Color>(ERROR_UNDERLINE_COLOR, Color());
            theme->underlineColor_ = pattern->GetAttr<Color>(UNDERLINE_COLOR, defaultUnderlineColor);
            theme->disableUnderlineColor_ = pattern->GetAttr<Color>(UNDERLINE_COLOR, defaultUnderlineColor)
                .BlendOpacity(pattern->GetAttr<double>(DISABLE_UNDERLINE_ALPHA, defaultDisableUnderlineAlpha));
            theme->underlineTextColor_ = pattern->GetAttr<Color>(UNDERLINE_TEXT_COLOR, defaultUnderlineTextColor);
            theme->underlineFontSize_ = pattern->GetAttr<Dimension>(UNDERLINE_FONT_SIZE, 0.0_fp);
            theme->errorTextStyle_.SetTextColor(pattern->GetAttr<Color>(ERROR_UNDERLINE_TEXT_COLOR, Color()));
            theme->errorTextStyle_.SetFontSize(pattern->GetAttr<Dimension>(ERROR_UNDERLINE_TEXT_SIZE, 0.0_fp));

            theme->countTextStyle_.SetTextColor(pattern->GetAttr<Color>("count_text_color", Color()));
            theme->countTextStyle_.SetFontSize(pattern->GetAttr<Dimension>("count_text_font_size", 0.0_fp));
            theme->overCountStyle_.SetTextColor(pattern->GetAttr<Color>("over_text_color", Color()));
            theme->overCountStyle_.SetFontSize(pattern->GetAttr<Dimension>("over_text_font_size", 0.0_fp));

            theme->countTextStyleOuter_.SetTextColor(pattern->GetAttr<Color>("count_outer_text_color", Color()));
            theme->countTextStyleOuter_.SetFontSize(
                pattern->GetAttr<Dimension>("count_outer_text_font_size", 0.0_fp));
            theme->overCountStyleOuter_.SetTextColor(pattern->GetAttr<Color>("over_outer_text_color", Color()));
            theme->overCountStyleOuter_.SetFontSize(
                pattern->GetAttr<Dimension>("over_outer_text_font_size", 0.0_fp));
            theme->overCountTextStyle_.SetTextColor(pattern->GetAttr<Color>(OVER_COUNT_TEXT_COLOR, Color()));
            theme->overCountTextStyle_.SetFontSize(pattern->GetAttr<Dimension>(OVER_COUNT_TEXT_FONT_SIZE, 0.0_fp));
            theme->selectedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, Color());
            theme->disableTextColor_ = pattern->GetAttr<Color>(PATTERN_TEXT_COLOR_DISABLED, Color());
            theme->underlineActivedColor_ = pattern->GetAttr<Color>(PATTERN_UNDERLINE_ACTIVED_COLOR, Color())
                .BlendOpacity(pattern->GetAttr<double>(UNDERLINE_COLOR_ALPHA, defaultUnderlineAlpha));
            theme->underlineTypingColor_ = pattern->GetAttr<Color>(PATTERN_UNDERLINE_TYPING_COLOR, Color())
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
            theme->passwordErrorBorderColor_ = pattern->GetAttr<Color>(ERROR_PASSWORD_BORDER_COLOR, Color())
                .BlendOpacity(pattern->GetAttr<double>(ERROR_PASSWORD_BORDER_ALPHA, defaultErrorAlpha));
            theme->passwordErrorLableColor_ = pattern->GetAttr<Color>(ERROR_PASSWORD_TEXT_COLOR, Color());
            theme->overCountBorderColor_ = pattern->GetAttr<Color>(OVER_COUNT_BORDER_COLOR, Color())
                .BlendOpacity(pattern->GetAttr<double>(OVER_COUNT_BORDER_COLOR_ALPHA, defaultErrorAlpha));
            theme->inlineTextColor_ =  pattern->GetAttr<Color>(INLINE_TEXT_COLOR, Color());
            theme->inlineRadiusSize_ = Radius(pattern->GetAttr<Dimension>(INLINE_RADIUS_SIZE, 4.0_vp));
            theme->inlineBgColor_ = pattern->GetAttr<Color>(INLINE_BG_COLOR, Color());
            theme->inlineBorderColor_ = pattern->GetAttr<Color>(INLINE_BORDER_COLOR, Color());
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
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

    const Dimension& GetErrorTextCapsuleMargin() const
    {
        return errorTextCapsuleMargin_;
    }

    bool GetDraggable() const
    {
        return draggable_;
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
    Dimension errorTextCapsuleMargin_ = 22.0_vp;

    bool showEllipsis_ = true;
    bool draggable_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_FIELD_TEXTFIELD_THEME_H
