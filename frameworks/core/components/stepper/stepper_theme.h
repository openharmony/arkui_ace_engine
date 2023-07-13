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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_STEPPER_STEPPER_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_STEPPER_STEPPER_THEME_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"
#include "core/components/theme/theme_constants_defines.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {
namespace {
constexpr Dimension STEPPER_FOCUSED_BORDER_WIDTH = 2.0_vp;
constexpr Dimension STEPPER_SCREEN_MARGIN = 4.0_vp;
} // namespace
/**
 * StepperTheme defines color and styles of StepperComponent. StepperTheme should be built
 * using StepperTheme::Builder.
 */
class StepperTheme : public virtual Theme {
    DECLARE_ACE_TYPE(StepperTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<StepperTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<StepperTheme> theme = AceType::Claim(new StepperTheme());
            if (!themeConstants) {
                return theme;
            }
            theme->textStyle_.SetTextColor(themeConstants->GetColor(THEME_STEPPER_TEXT_COLOR));
            theme->textStyle_.SetFontSize(themeConstants->GetDimension(THEME_STEPPER_TEXT_FONTSIZE));
            theme->textStyle_.SetFontWeight(FontWeight(themeConstants->GetInt(THEME_STEPPER_TEXT_FONTWEIGHT)));
            theme->textStyle_.SetFontStyle(FontStyle::NORMAL);
            theme->textStyle_.SetTextDecoration(TextDecoration::NONE);
            std::vector<std::string> families;
            families.emplace_back("sans-serif");
            theme->textStyle_.SetFontFamilies(families);
            theme->minFontSize_ = themeConstants->GetDimension(THEME_STEPPER_TEXT_FONTSIZE_MIN);
            uint32_t maxlines = static_cast<uint32_t>(themeConstants->GetInt(THEME_STEPPER_TEXT_MAX_LINES));
            theme->textMaxLines_ = maxlines < 0 ? theme->textMaxLines_ : maxlines;
            theme->defaultPaddingStart_ = themeConstants->GetDimension(THEME_STEPPER_DEFAULT_PADDING_START);
            theme->defaultPaddingEnd_ = themeConstants->GetDimension(THEME_STEPPER_DEFAULT_PADDING_END);
            theme->progressColor_ = themeConstants->GetColor(THEME_STEPPER_PROGRESS_COLOR);
            theme->progressDiameter_ = themeConstants->GetDimension(THEME_STEPPER_PROGRESS_DIAMETER);
            theme->arrowWidth_ = themeConstants->GetDimension(THEME_STEPPER_ARROW_WIDTH_DIAMETER);
            theme->arrowHeight_ = themeConstants->GetDimension(THEME_STEPPER_ARROW_HEIGHT_DIAMETER);
            theme->arrowColor_ = themeConstants->GetColor(THEME_STEPPER_ARROW_COLOR);
            theme->disabledColor_ = themeConstants->GetColor(THEME_STEPPER_DISABLED_COLOR);
            theme->radius_ = themeConstants->GetDimension(THEME_STEPPER_RADIUS);
            theme->buttonPressedColor_ = themeConstants->GetColor(THEME_STEPPER_BUTTON_PRESSED_COLOR);
            theme->buttonPressedHeight_ = themeConstants->GetDimension(THEME_STEPPER_BUTTON_PRESSED_HEIGHT);
            theme->controlHeight_ = themeConstants->GetDimension(THEME_STEPPER_CONTROL_HEIGHT);
            theme->controlMargin_ = themeConstants->GetDimension(THEME_STEPPER_CONTROL_MARGIN);
            theme->controlPadding_ = themeConstants->GetDimension(THEME_STEPPER_CONTROL_PADDING);
            theme->focusColor_ = themeConstants->GetColor(THEME_STEPPER_FOCUS_COLOR);
            theme->focusBorderWidth_ = themeConstants->GetDimension(THEME_STEPPER_FOCUS_BORDER_WIDTH);
            theme->mouseHoverColor_ = themeConstants->GetColor(THEME_STEPPER_MOUSE_HOVER_COLOR);
            theme->disabledAlpha_ = themeConstants->GetDouble(THEME_STEPPER_DISABLED_ALPHA);
            auto themeStyle = themeConstants->GetThemeStyle();
            if (themeStyle) {
                auto pattern = themeStyle->GetAttr<RefPtr<ThemeStyle>>("stepper_pattern", nullptr);
                if (pattern) {
                    theme->textStyle_.SetTextColor(pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::RED));
                    theme->textStyle_.SetFontSize(pattern->GetAttr<Dimension>(PATTERN_TEXT_SIZE, 16.0_vp));
                    theme->radius_ = pattern->GetAttr<Dimension>("border_radius", 8.0_vp);
                    theme->buttonPressedColor_ = pattern->GetAttr<Color>("button_bg_color_pressed", Color::RED);
                    theme->mouseHoverColor_ = pattern->GetAttr<Color>("button_bg_color_hovered", Color::RED);
                    theme->defaultPaddingStart_ = pattern->GetAttr<Dimension>("padding_left", 12.0_vp);
                    theme->defaultPaddingEnd_ = pattern->GetAttr<Dimension>("padding_right", 12.0_vp);
                    theme->arrowColor_ = pattern->GetAttr<Color>("arrorw_color", Color::RED);
                    theme->progressColor_ = pattern->GetAttr<Color>("progress_color", Color::RED);
                    theme->disabledColor_ = pattern->GetAttr<Color>("button_bg_color_disabled", Color::RED);
                    theme->disabledAlpha_ = pattern->GetAttr<double>("button_bg_color_disabled_alpha", 0.0);
                    theme->defaultAlpha_ = pattern->GetAttr<double>("attribute_alpha_content_primary", 0.9);
                    theme->focusColor_ = pattern->GetAttr<Color>(STEPPER_FOCUS_COLOR, Color::RED);
                    theme->focusBorderWidth_ = STEPPER_FOCUSED_BORDER_WIDTH;
                    theme->controlMargin_ = STEPPER_SCREEN_MARGIN;
                }
            }
            return theme;
        }
    };

    ~StepperTheme() override = default;

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Dimension& GetMinFontSize() const
    {
        return minFontSize_;
    }

    uint32_t GetTextMaxLines() const
    {
        return textMaxLines_;
    }

    const Dimension& GetDefaultPaddingStart() const
    {
        return defaultPaddingStart_;
    }

    const Dimension& GetDefaultPaddingEnd() const
    {
        return defaultPaddingEnd_;
    }

    const Color& GetProgressColor() const
    {
        return progressColor_;
    }

    const Dimension& GetProgressDiameter() const
    {
        return progressDiameter_;
    }

    const Dimension& GetArrowWidth() const
    {
        return arrowWidth_;
    }

    const Dimension& GetArrowHeight() const
    {
        return arrowHeight_;
    }

    const Color& GetArrowColor() const
    {
        return arrowColor_;
    }

    const Color& GetDisabledColor() const
    {
        return disabledColor_;
    }

    const Dimension& GetRadius() const
    {
        return radius_;
    }

    const Color& GetButtonPressedColor() const
    {
        return buttonPressedColor_;
    }

    const Dimension& GetButtonPressedHeight() const
    {
        return buttonPressedHeight_;
    }

    const Dimension& GetControlHeight() const
    {
        return controlHeight_;
    }

    const Dimension& GetControlMargin() const
    {
        return controlMargin_;
    }

    const Dimension& GetControlPadding() const
    {
        return controlPadding_;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    const Dimension& GetFocusBorderWidth() const
    {
        return focusBorderWidth_;
    }

    const Color& GetMouseHoverColor() const
    {
        return mouseHoverColor_;
    }

    double GetDisabledAlpha() const
    {
        return disabledAlpha_;
    }

    double GetDefaultAlpha() const
    {
        return defaultAlpha_;
    }

protected:
    StepperTheme() = default;

private:
    TextStyle textStyle_;
    Dimension minFontSize_;
    uint32_t textMaxLines_ = 1;
    Dimension defaultPaddingStart_;
    Dimension defaultPaddingEnd_;
    Color progressColor_;
    Dimension progressDiameter_;
    Dimension arrowWidth_;
    Dimension arrowHeight_;
    Color arrowColor_;
    Color disabledColor_;
    Dimension radius_;
    Color buttonPressedColor_;
    Dimension buttonPressedHeight_;
    Dimension controlHeight_;
    Dimension controlMargin_;
    Dimension controlPadding_;
    Color focusColor_;
    Dimension focusBorderWidth_;
    Color mouseHoverColor_;
    double disabledAlpha_ = 0.4;
    double defaultAlpha_ = 0.9;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_STEPPER_STEPPER_THEME_H
