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
    std::string ToHtml(const SpanString& spanString);
    std::string ToHtml(std::vector<uint8_t> &values);
private:
    std::string NormalStyleToHtml(const NG::FontStyle &fontStyle);
    std::string ImageToHtml(RefPtr<NG::SpanItem> item);
    std::string FontStyleToHtml(const std::optional<Ace::FontStyle>& value);
    std::string FontSizeToHtml(const std::optional<Dimension>& value);
    std::string FontWeightToHtml(const std::optional<FontWeight>& value);
    std::string ColorToHtml(const std::optional<Color>& value);
    std::string FontFamilyToHtml(const std::optional<std::vector<std::string>>& value);
    std::string TextDecorationToHtml(TextDecoration decoration);
    std::string TextDecorationStyleToHtml(TextDecorationStyle decorationStyle);
    std::string ToHtml(const std::string &key, const std::optional<Dimension> &space);
    std::string DeclarationToHtml(const NG::FontStyle &fontStyle);
    std::string ToHtml(const std::optional<std::vector<Shadow>> &shadows);
    std::string ToHtml(const std::string &key, const std::optional<CalcDimension>& dimesion);
    std::string ToHtml(const std::optional<ImageSpanSize>& size);
    std::string ToHtml(const std::optional<OHOS::Ace::TextAlign> &object);
    std::string ToHtml(const std::optional<OHOS::Ace::WordBreak> &object);
    std::string ToHtml(const std::optional<OHOS::Ace::TextOverflow> &object);
    std::string ToHtml(const std::optional<OHOS::Ace::NG::BorderRadiusProperty>& borderRadius);
    std::string ToHtml(const std::string &key, const std::optional<OHOS::Ace::NG::MarginProperty>& prop);
    std::string ToHtml(const std::optional<ImageFit>& objectFit);
    std::string ToHtml(const std::optional<VerticalAlign>& verticalAlign);
    std::string ParagraphStyleToHtml(const OHOS::Ace::NG::TextLineStyle &textLineStyle);
    std::string LeadingMarginToHtml(const OHOS::Ace::NG::TextLineStyle &style);

    std::string ToHtmlAttribute(const std::string &key, const std::optional<CalcDimension>& dimesion);
};
}; // namespace OHOS::Ace
#endif