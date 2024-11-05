/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_HTML_HTML_CONVERT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_HTML_HTML_CONVERT_H

#include "core/components_ng/pattern/text/span/span_string.h"
namespace OHOS::Ace {
class SpanToHtml {
public:
    static std::string ToHtml(const SpanString& spanString);
    static std::string ToHtml(std::vector<uint8_t>& values);

private:
    static std::string NormalStyleToHtml(
        const NG::FontStyle& fontStyle, const OHOS::Ace::NG::TextLineStyle& textLineStyle);
    static std::string ImageToHtml(RefPtr<NG::SpanItem> item);
    static std::string FontStyleToHtml(const std::optional<Ace::FontStyle>& value);
    static std::string FontSizeToHtml(const std::optional<Dimension>& value);
    static std::string FontWeightToHtml(const std::optional<FontWeight>& value);
    static std::string ColorToHtml(const std::optional<Color>& value);
    static std::string FontFamilyToHtml(const std::optional<std::vector<std::string>>& value);
    static std::string TextDecorationToHtml(TextDecoration decoration);
    static std::string TextDecorationStyleToHtml(TextDecorationStyle decorationStyle);
    static std::string ToHtml(const std::string& key, const std::optional<Dimension>& value);
    static std::string DeclarationToHtml(const NG::FontStyle& fontStyle);
    static std::string ToHtml(const std::optional<std::vector<Shadow>>& shadows);
    static std::string ToHtml(const std::string& key, const std::optional<CalcDimension>& dimesion);
    static std::string ToHtml(const std::optional<ImageSpanSize>& size);
    static std::string ToHtml(const std::optional<OHOS::Ace::TextAlign>& object);
    static std::string ToHtml(const std::optional<OHOS::Ace::WordBreak>& object);
    static std::string ToHtml(const std::optional<OHOS::Ace::TextOverflow>& object);
    static std::string ToHtml(const std::optional<OHOS::Ace::NG::BorderRadiusProperty>& borderRadius);
    static std::string ToHtml(const std::string& key, const std::optional<OHOS::Ace::NG::MarginProperty>& prop);
    static std::string ToHtml(const std::optional<ImageFit>& objectFit);
    static std::string ToHtml(const std::optional<VerticalAlign>& verticalAlign);
    static std::string ParagraphStyleToHtml(const OHOS::Ace::NG::TextLineStyle& textLineStyle);
    static std::string LeadingMarginToHtml(const OHOS::Ace::NG::TextLineStyle& style);
    static int WriteLocalFile(RefPtr<PixelMap> pixelMap, std::string& filePath, std::string& fileUri);
    static std::string ToHtmlImgSizeAttribute(const std::string& key, const std::optional<CalcDimension>& dimesion);

    static void ToHtmlColor(std::string& color);
    static std::string DimensionToString(const Dimension& dimension);
    static std::string DimensionToStringWithoutUnit(const Dimension& dimension);
    static std::string ToHtmlStyleFormat(const std::string& key, const std::string& value)
    {
        return key + std::string(": ") + value + ";";
    }

    static std::string ToHtmlAttributeFormat(const std::string& key, const std::string& value)
    {
        return key + "=\"" + value + "\" ";
    }

    static bool CreateDirectory(const std::string& path);
};
}; // namespace OHOS::Ace
#endif