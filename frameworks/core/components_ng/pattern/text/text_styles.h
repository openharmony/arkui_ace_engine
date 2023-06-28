/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
constexpr Dimension TEXT_DEFAULT_FONT_SIZE = 16.0_fp;

struct FontStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextShadow, Shadow);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ItalicFontStyle, Ace::FontStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontWeight, FontWeight);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FontFamily, std::vector<std::string>);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecoration, TextDecoration);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecorationColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextDecorationStyle, TextDecorationStyle);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextCase, TextCase);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AdaptMinFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AdaptMaxFontSize, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LetterSpacing, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ForegroundColor, Color);
};

struct TextLineStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LineHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextBaseline, TextBaseline);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BaselineOffset, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextOverflow, TextOverflow);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextAlign, TextAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxLength, uint32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxLines, uint32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HeightAdaptivePolicy, TextHeightAdaptivePolicy);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextIndent, Dimension);
};

TextStyle CreateTextStyleUsingTheme(const std::unique_ptr<FontStyle>& fontStyle,
    const std::unique_ptr<TextLineStyle>& textLineStyle, const RefPtr<TextTheme>& textTheme);

TextStyle CreateTextStyleUsingThemeWithText(const RefPtr<FrameNode> frameNode,
    const std::unique_ptr<FontStyle>& fontStyle, const std::unique_ptr<TextLineStyle>& textLineStyle,
    const RefPtr<TextTheme>& textTheme);

std::string GetFontFamilyInJson(const std::optional<std::vector<std::string>>& value);
std::string GetFontStyleInJson(const std::optional<Ace::FontStyle>& value);
std::string GetFontWeightInJson(const std::optional<FontWeight>& value);
std::string GetFontSizeInJson(const std::optional<Dimension>& value);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_STYLES_H
