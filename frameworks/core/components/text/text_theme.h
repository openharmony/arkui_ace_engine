/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "ui/base/utils/utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
namespace {
constexpr float DRAG_BACKGROUND_OPACITY = 0.95f;
constexpr float URL_DISA_OPACITY = 0.4f;
constexpr double DEFAULT_TEXT_OPACITY = 0.9;
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
            RefPtr<TextTheme> theme = AceType::MakeRefPtr<TextTheme>();
            if (!themeConstants) {
                return theme;
            }
            InitThemeDefaults(theme);
            ParsePattern(themeConstants, theme);
            return theme;
        }
    protected:
        void InitThemeDefaults(const RefPtr<TextTheme>& theme) const
        {
            // Styles below do not need to get from ThemeConstants, directly set at here.
            theme->textStyle_.SetFontStyle(FontStyle::NORMAL);
            theme->textStyle_.SetFontWeight(FontWeight::NORMAL);
            theme->textStyle_.SetTextDecoration(TextDecoration::NONE);
            theme->textStyle_.SetLineThicknessScale(1.0f);
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TextTheme>& theme) const;
    };

    ~TextTheme() override = default;

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    TextDecoration GetTextDecoration() const
    {
        return textStyle_.GetTextDecoration().size() > 0 ?
            textStyle_.GetTextDecoration()[0] : TextDecoration::NONE;
    }

    const Color& GetCaretColor() const
    {
        return caretColor_;
    }

    const Color& GetTextClockFontColor() const
    {
        return textClockFontColor_;
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

    bool GetIsTextFadeout() const
    {
        return isTextFadeout_;
    }

    const Dimension& GetFadeoutWidth() const
    {
        return fadeoutWidth_;
    }

    bool IsShowHandle() const
    {
        return isShowHandle_;
    }

    bool IsShowTranslate() const
    {
        return isShowTranslate_;
    }

    bool IsShowSearch() const
    {
        return isShowSearch_;
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

    MarqueeStartPolicy GetMarqueeStartPolicy() const
    {
        return marqueeStartPolicy_;
    }

    bool IsSupportAskCelia() const
    {
        return isSupportAskCelia_;
    }

protected:
    TextTheme() = default;
    TextStyle textStyle_;
    Color textClockFontColor_ = Color::BLACK;
    Color dragBackgroundColor_ = Color::WHITE;

private:
    Color caretColor_;
    Color selectedColor_;
    bool draggable_ = false;
    double linearSplitChildMinSize_ = 20.0;
    bool isShowHandle_ = false;
    bool isShowTranslate_ = false;
    bool isShowSearch_ = false;
    bool isTextFadeout_ = false;
    Dimension fadeoutWidth_;
    MarqueeStartPolicy marqueeStartPolicy_ = MarqueeStartPolicy::DEFAULT;
    Color urlDisabledColor_;
    Color urlDefaultColor_;
    Color urlHoverColor_;
    Color urlPressColor_;
    bool isSupportAskCelia_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_THEME_H
