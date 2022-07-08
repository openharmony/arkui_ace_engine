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
#define DEFINE_STYLE_UPDATE(group, name, func)           \
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
        DEFINE_STYLE_UPDATE(fontStyle, FontSize, SetFontSize);
        DEFINE_STYLE_UPDATE(fontStyle, TextColor, SetTextColor);
        DEFINE_STYLE_UPDATE(fontStyle, ItalicFontStyle, SetFontStyle);
        DEFINE_STYLE_UPDATE(fontStyle, FontWeight, SetFontWeight);
        DEFINE_STYLE_UPDATE(fontStyle, FontFamily, SetFontFamilies);
    }
    if (textLineStyle) {
        DEFINE_STYLE_UPDATE(textLineStyle, LineHeight, SetLineHeight);
        DEFINE_STYLE_UPDATE(textLineStyle, TextBaseline, SetTextBaseline);
        DEFINE_STYLE_UPDATE(textLineStyle, BaselineOffset, SetBaselineOffset);
        DEFINE_STYLE_UPDATE(textLineStyle, TextOverflow, SetTextOverflow);
        DEFINE_STYLE_UPDATE(textLineStyle, TextAlign, SetTextAlign);
        DEFINE_STYLE_UPDATE(textLineStyle, MaxLines, SetMaxLines);
    }
    return textStyle;
}
} // namespace OHOS::Ace::NG
