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

#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {
const std::vector<WordBreak> WORD_BREAK_TYPES = { WordBreak::NORMAL, WordBreak::BREAK_ALL, WordBreak::BREAK_WORD,
    WordBreak::HYPHENATION };
const std::vector<LineBreakStrategy> LINE_BREAK_STRATEGY_TYPES = { LineBreakStrategy::GREEDY,
    LineBreakStrategy::HIGH_QUALITY, LineBreakStrategy::BALANCED };
TextStyle::TextStyle(const std::vector<std::string>& fontFamilies, double fontSize, FontWeight fontWeight,
    FontStyle fontStyle, const Color& textColor)
    : fontFamilies_(fontFamilies), fontSize_(fontSize), fontWeight_(fontWeight), fontStyle_(fontStyle),
      textColor_(textColor)
{}

bool TextStyle::operator==(const TextStyle& rhs) const
{
    return fontFamilies_ == rhs.fontFamilies_ && fontFeatures_ == rhs.fontFeatures_ &&
           textDecorationStyle_ == rhs.textDecorationStyle_ &&
           preferFontSizes_ == rhs.preferFontSizes_ && fontSize_ == rhs.fontSize_ &&
           adaptMinFontSize_ == rhs.adaptMinFontSize_ && adaptMaxFontSize_ == rhs.adaptMaxFontSize_ &&
           adaptFontSizeStep_ == rhs.adaptFontSizeStep_ && lineHeight_ == rhs.lineHeight_ &&
           fontWeight_ == rhs.fontWeight_ && fontStyle_ == rhs.fontStyle_ && textBaseline_ == rhs.textBaseline_ &&
           textOverflow_ == rhs.textOverflow_ && textAlign_ == rhs.textAlign_ && textColor_ == rhs.textColor_ &&
           textDecoration_ == rhs.textDecoration_ && textShadows_ == rhs.textShadows_ &&
           letterSpacing_ == rhs.letterSpacing_ && maxLines_ == rhs.maxLines_ && adaptTextSize_ == rhs.adaptTextSize_ &&
           allowScale_ == rhs.allowScale_ && wordBreak_ == rhs.wordBreak_ &&
           textDecorationColor_ == rhs.textDecorationColor_ && textCase_ == rhs.textCase_ &&
           baselineOffset_ == rhs.baselineOffset_ && adaptHeight_ == rhs.adaptHeight_ &&
           textIndent_ == rhs.textIndent_ && verticalAlign_ == rhs.verticalAlign_ && wordSpacing_ == rhs.wordSpacing_ &&
           ellipsisMode_ == rhs.ellipsisMode_ && lineBreakStrategy_ == rhs.lineBreakStrategy_ &&
           textBackgroundStyle_ == rhs.textBackgroundStyle_;
}

bool TextStyle::operator!=(const TextStyle& rhs) const
{
    return !(rhs == *this);
}

void TextStyle::SetAdaptTextSize(
    const Dimension& maxFontSize, const Dimension& minFontSize, const Dimension& fontSizeStep)
{
    adaptMaxFontSize_ = maxFontSize;
    adaptMinFontSize_ = minFontSize;
    adaptFontSizeStep_ = fontSizeStep;
    adaptTextSize_ = true;
}

void TextBackgroundStyle::ToJsonValue(std::unique_ptr<JsonValue>& json,
    const std::optional<TextBackgroundStyle>& style, const NG::InspectorFilter& filter)
{
    NG::BorderRadiusProperty defaultRadius;
    TextBackgroundStyle exportStyle = { .backgroundColor = Color::TRANSPARENT, .backgroundRadius = defaultRadius };
    if (style.has_value()) {
        exportStyle.backgroundColor = style.value().backgroundColor.value_or(Color::TRANSPARENT);
        exportStyle.backgroundRadius = style.value().backgroundRadius.value_or(defaultRadius);
    }

    auto styleJson = JsonUtil::Create(true);
    styleJson->Put("color", exportStyle.backgroundColor->ColorToString().c_str());
    auto radiusJson = JsonUtil::Create(true);
    exportStyle.backgroundRadius->ToJsonValue(radiusJson, styleJson, filter);

    json->PutExtAttr("textBackgroundStyle", styleJson, filter);
}

void TextStyle::UpdateColorByResourceId()
{
    textColor_.UpdateColorByResourceId();
    textDecorationColor_.UpdateColorByResourceId();
    if (textBackgroundStyle_.has_value()) {
        textBackgroundStyle_->UpdateColorByResourceId();
    }
    std::for_each(renderColors_.begin(), renderColors_.end(), [](Color& cl) { cl.UpdateColorByResourceId(); });
    std::for_each(textShadows_.begin(), textShadows_.end(), [](Shadow& sd) { sd.UpdateColorByResourceId(); });
}

std::string TextStyle::ToString() const
{
    auto jsonValue = JsonUtil::Create(true);
    JSON_STRING_PUT_STRINGABLE(jsonValue, fontSize_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, textColor_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, lineHeight_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, baselineOffset_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, wordSpacing_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, textIndent_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, letterSpacing_);
    JSON_STRING_PUT_STRINGABLE(jsonValue, lineSpacing_);

    JSON_STRING_PUT_INT(jsonValue, fontWeight_);
    JSON_STRING_PUT_INT(jsonValue, fontStyle_);
    JSON_STRING_PUT_INT(jsonValue, textBaseline_);
    JSON_STRING_PUT_INT(jsonValue, textOverflow_);
    JSON_STRING_PUT_INT(jsonValue, verticalAlign_);
    JSON_STRING_PUT_INT(jsonValue, textAlign_);
    JSON_STRING_PUT_INT(jsonValue, textDecorationStyle_);
    JSON_STRING_PUT_INT(jsonValue, textDecoration_);
    JSON_STRING_PUT_INT(jsonValue, whiteSpace_);
    JSON_STRING_PUT_INT(jsonValue, wordBreak_);
    JSON_STRING_PUT_INT(jsonValue, textCase_);
    JSON_STRING_PUT_INT(jsonValue, ellipsisMode_);
    JSON_STRING_PUT_INT(jsonValue, lineBreakStrategy_);

    std::stringstream ss;
    std::for_each(renderColors_.begin(), renderColors_.end(), [&ss](const Color& c) { ss << c.ToString() << ","; });
    jsonValue->Put("renderColors", ss.str().c_str());
    JSON_STRING_PUT_INT(jsonValue, renderStrategy_);
    JSON_STRING_PUT_INT(jsonValue, effectStrategy_);
    JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, symbolEffectOptions_);

    return jsonValue->ToString();
}

} // namespace OHOS::Ace
