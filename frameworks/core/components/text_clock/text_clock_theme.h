/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_CLOCK_TEXT_CLOCK_THEME_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_CLOCK_TEXT_CLOCK_THEME_H

#include "core/components/theme/theme.h"
#include "core/components/theme/theme_constants.h"

namespace OHOS::Ace {
namespace {
constexpr float ERR_TEXT_COLOR_ALPHA = 0.9f;
} // namespace

class TextClockTheme : public virtual Theme {
    DECLARE_ACE_TYPE(TextClockTheme, Theme);

public:
    class Builder {
    public:
        Builder() = default;
        virtual ~Builder() = default;

        RefPtr<TextClockTheme> Build(const RefPtr<ThemeConstants>& themeConstants) const
        {
            RefPtr<TextClockTheme> theme = AceType::MakeRefPtr<TextClockTheme>();
            if (!themeConstants) {
                return theme;
            }
            InitThemeDefaultsClock(theme);
            ParsePattern(themeConstants, theme);
            return theme;
        }

    protected:
        void InitThemeDefaultsClock(const RefPtr<TextClockTheme>& theme) const
        {
            CHECK_NULL_VOID(theme);
            // Styles below do not need to get from ThemeConstants, directly set at here.
            theme->textStyleClock_.SetFontStyle(FontStyle::NORMAL);
            theme->textStyleClock_.SetFontWeight(FontWeight::NORMAL);
            theme->textStyleClock_.SetTextDecoration(TextDecoration::NONE);
        }

        void ParsePattern(const RefPtr<ThemeConstants>& themeConstants, const RefPtr<TextClockTheme>& theme) const
        {
            CHECK_NULL_VOID(themeConstants);
            CHECK_NULL_VOID(theme);
            RefPtr<ThemeStyle> pattern = themeConstants->GetPatternByName(THEME_PATTERN_TEXT);
            if (!pattern) {
                LOGW("find pattern of textclock fail");
                return;
            }
            theme->textStyleClock_.SetTextColor(
                pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::GRAY)
                    .BlendOpacity(pattern->GetAttr<double>(PATTERN_TEXT_COLOR_ALPHA, ERR_TEXT_COLOR_ALPHA)));
            theme->textStyleClock_.SetFontSize(pattern->GetAttr<Dimension>("text_font_size", 0.0_vp));
            theme->SetTextParseFailedColor(
                pattern->GetAttr<Color>(PATTERN_TEXT_COLOR, Color::BLACK)
                    .BlendOpacity(pattern->GetAttr<double>(PATTERN_TEXT_COLOR_ALPHA, ERR_TEXT_COLOR_ALPHA)));
        }
    };

    ~TextClockTheme() override = default;

    const TextStyle& GetTextStyleClock() const
    {
        return textStyleClock_;
    }

    const Color& GetTextParseFailedColor() const
    {
        return textClockParseFailedColor_;
    }

    void SetTextParseFailedColor(const Color& textColor)
    {
        textClockParseFailedColor_ = textColor;
    }

protected:
    TextClockTheme() = default;
    TextStyle textStyleClock_;

private:
    // For Parse Failed
    Color textClockParseFailedColor_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_CLOCK_TEXT_CLOCK_THEME_H
