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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H

#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
using ItalicFontStyle = Ace::FontStyle;

struct FontStyle {
    ACE_DEFINE_STRUCT_PROPERTY(FontSize, Dimension);
    ACE_DEFINE_STRUCT_PROPERTY(TextColor, Color);
    ACE_DEFINE_STRUCT_PROPERTY(ItalicFontStyle, ItalicFontStyle);
    ACE_DEFINE_STRUCT_PROPERTY(FontWeight, FontWeight);
    ACE_DEFINE_STRUCT_PROPERTY(FontFamily, std::vector<std::string>);
};

struct TextLineStyle {
    ACE_DEFINE_STRUCT_PROPERTY(LineHeight, Dimension);
    ACE_DEFINE_STRUCT_PROPERTY(TextBaseline, TextBaseline);
    ACE_DEFINE_STRUCT_PROPERTY(BaselineOffset, Dimension);
    ACE_DEFINE_STRUCT_PROPERTY(TextOverflow, TextOverflow);
    ACE_DEFINE_STRUCT_PROPERTY(TextAlign, TextAlign);
    ACE_DEFINE_STRUCT_PROPERTY(MaxLines, uint32_t);
};

TextStyle CreateTextStyleUsingTheme(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, const RefPtr<TextTheme>& textTheme);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H
