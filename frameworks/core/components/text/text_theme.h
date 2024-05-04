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
#include "core/components/theme/theme_constants_defines.h"

namespace OHOS::Ace {

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
            theme->selectedColor_ = pattern->GetAttr<Color>(PATTERN_BG_COLOR_SELECTED, Color(0x33007dff));
            auto draggable = pattern->GetAttr<std::string>("draggable", "0");
            theme->draggable_ = StringUtils::StringToInt(draggable);
            constexpr double childMinSize = 20.0;
            theme->linearSplitChildMinSize_ = pattern->GetAttr<double>(LINEAR_SPLIT_CHILD_MIN_SIZE, childMinSize);
            theme->isTextFadeout_ = pattern->GetAttr<std::string>("text_fadeout_enable", "") == "true";
            theme->fadeoutWidth_ = pattern->GetAttr<Dimension>("text_fadeout_width", 16.0_vp);
            RefPtr<ThemeStyle> textfieldPattern = themeConstants->GetPatternByName("textfield_pattern");
            if (!textfieldPattern) {
                LOGW("find pattern of textfield fail");
                return;
            }
            auto textfieldShowHandle = textfieldPattern->GetAttr<std::string>("textfield_show_handle", "0");
            theme->isShowHandle_ = StringUtils::StringToInt(textfieldShowHandle);
        }
    };

    ~TextTheme() override = default;

    TextStyle GetTextStyle() const
    {
        return textStyle_;
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

protected:
    TextTheme() = default;

private:
    TextStyle textStyle_;
    Color selectedColor_;
    bool draggable_ = false;
    double linearSplitChildMinSize_ = 20.0;
    bool isTextFadeout_ = false;
    Dimension fadeoutWidth_;
    bool isShowHandle_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_THEME_H
