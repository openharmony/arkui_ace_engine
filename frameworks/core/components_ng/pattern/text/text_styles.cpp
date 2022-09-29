/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {
#define UPDATE_TEXT_STYLE(group, name, func)             \
    do {                                                 \
        if ((group)->prop##name.has_value()) {           \
            textStyle.func((group)->prop##name.value()); \
        }                                                \
    } while (false)

TextStyle CreateTextStyleUsingTheme(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, const RefPtr<TextTheme>& textTheme)
{
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    if (fontStyle) {
        UPDATE_TEXT_STYLE(fontStyle, FontSize, SetFontSize);
        UPDATE_TEXT_STYLE(fontStyle, TextColor, SetTextColor);
        UPDATE_TEXT_STYLE(fontStyle, ItalicFontStyle, SetFontStyle);
        UPDATE_TEXT_STYLE(fontStyle, FontWeight, SetFontWeight);
        UPDATE_TEXT_STYLE(fontStyle, FontFamily, SetFontFamilies);
        UPDATE_TEXT_STYLE(fontStyle, TextDecoration, SetTextDecoration);
        UPDATE_TEXT_STYLE(fontStyle, TextDecorationColor, SetTextDecorationColor);
        UPDATE_TEXT_STYLE(fontStyle, TextCase, SetTextCase);
        UPDATE_TEXT_STYLE(fontStyle, AdaptMinFontSize, SetAdaptMinFontSize);
        UPDATE_TEXT_STYLE(fontStyle, AdaptMaxFontSize, SetAdaptMaxFontSize);
    }
    if (textLineStyle) {
        UPDATE_TEXT_STYLE(textLineStyle, LineHeight, SetLineHeight);
        UPDATE_TEXT_STYLE(textLineStyle, TextBaseline, SetTextBaseline);
        UPDATE_TEXT_STYLE(textLineStyle, BaselineOffset, SetBaselineOffset);
        UPDATE_TEXT_STYLE(textLineStyle, TextOverflow, SetTextOverflow);
        UPDATE_TEXT_STYLE(textLineStyle, TextAlign, SetTextAlign);
        UPDATE_TEXT_STYLE(textLineStyle, MaxLines, SetMaxLines);
        UPDATE_TEXT_STYLE(textLineStyle, LetterSpacing, SetLetterSpacing);
    }
    return textStyle;
}
} // namespace OHOS::Ace::NG
