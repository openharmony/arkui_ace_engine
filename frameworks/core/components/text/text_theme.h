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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_THEME_H

#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
namespace {
constexpr float DRAG_BACKGROUND_OPACITY = 0.95f;
constexpr float URL_DISA_OPACITY = 0.4f;
} // namespace

/**
 * TextTheme defines color and styles of ThemeComponent. TextTheme should be built
 * using TextTheme::Builder.
 */
class TextTheme : public virtual Theme {
    DECLARE_ACE_TYPE(TextTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        ~Builder() = default;

        RefPtr<TextTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<TextTheme> theme = AceType::Claim(new TextTheme());
            if (!themeConstants) {
                return theme;
            }
            // Styles below do not need to get from ThemeConstants, directly set at here.
            theme->textStyle_.SetFontStyle(FontStyle::NORMAL);
            theme->textStyle_.SetFontWeight(FontWeight::NORMAL);
            theme->textStyle_.SetTextDecoration(TextDecoration::NONE);
            ParsePattern(themeConstants, theme);
            return theme;
        }
    private:
        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TextTheme>& theme) const
        {
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_TEXT);
            if (!pattern) {
                LOGW("find pattern of text fail");
                return;
            }
            theme->textStyle_.SetTextColor(pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK)
                                               .BlendOpacity(pattern->GetAttr<double>(PATTERN_TEXT_COLOR_ALPHA, 0.9)));
            theme->textStyle_.SetFontSize(pattern->GetAttr<Dimension>("text_font_size", 0.0_vp));
            theme->caretColor_ = pattern->GetAttr<Color>("text_caret_color", Color(0xff006cde));
            theme->selectedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, Color(0x33007dff));
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
            auto dragBackgroundColor = pattern->GetAttr<Color>("drag_background_color", Color::WHITE);
            if (SystemProperties::GetColorMode() == ColorMode::DARK) {
                dragBackgroundColor = dragBackgroundColor.ChangeOpacity(DRAG_BACKGROUND_OPACITY);
            }
            theme->dragBackgroundColor_ = dragBackgroundColor;
            constexpr double childMinSize = 20.0;
            theme->linearSplitChildMinSize_ = pattern->GetAttr<double>(LINEAR_SPLIT_CHILD_MIN_SIZE, childMinSize);
            auto textShowHandle = pattern->GetAttr<std::string>("text_show_handle", "0");
            theme->isShowHandle_ = StringUtils::StringToInt(textShowHandle);
            auto disabledOpacity = pattern->GetAttr<double>("interactive_disable", URL_DISA_OPACITY);
            theme->urlDefaultColor_ = pattern->GetAttr<Color>("font_emphasize", Color(0xff007dff));
            theme->urlDisabledColor_ = theme->urlDefaultColor_.BlendOpacity(disabledOpacity);
            theme->urlHoverColor_ = pattern->GetAttr<Color>("interactive_hover", Color(0x33007dff));
            theme->urlPressColor_ = pattern->GetAttr<Color>("interactive_pressed", Color(0x19182431));
        }
    };

    ~TextTheme() override = default;

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    const Color& GetCaretColor() const
    {
        return caretColor_;
    }

    const Color& GetSelectedColor() const
    {
        return selectedColor_;
    }

    bool GetDraggable() const
    {
        return draggable_;
    }

    double GetLinearSplitChildMinSize() const
    {
        return linearSplitChildMinSize_;
    }

    bool IsShowHandle() const
    {
        return isShowHandle_;
    }

    const Color& GetDragBackgroundColor() const
    {
        return dragBackgroundColor_;
    }
    const Color& GetUrlDisabledColor() const
    {
        return urlDisabledColor_;
    }

    const Color& GetUrlDefaultColor() const
    {
        return urlDefaultColor_;
    }

    const Color& GetUrlHoverColor() const
    {
        return urlHoverColor_;
    }

    const Color& GetUrlPressColor() const
    {
        return urlPressColor_;
    }

protected:
    TextTheme() = default;

private:
    TextStyle textStyle_;
    Color caretColor_;
    Color selectedColor_;
    Color dragBackgroundColor_ = Color::WHITE;
    bool draggable_ = false;
    double linearSplitChildMinSize_ = 20.0;
    bool isShowHandle_ = false;
    Color urlDisabledColor_;
    Color urlDefaultColor_;
    Color urlHoverColor_;
    Color urlPressColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_THEME_H
