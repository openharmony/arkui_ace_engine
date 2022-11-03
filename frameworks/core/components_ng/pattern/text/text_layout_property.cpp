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

#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

void TextLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("content", GetContent().value_or("").c_str());
    json->Put("fontSize", GetFontSize().value_or(10.0_vp).ToString().c_str());
    json->Put("fontColor", GetTextColor().value_or(Color::BLACK).ColorToString().c_str());
    json->Put("fontStyle", GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                               ? "FontStyle.Normal"
                               : "FontStyle.Italic");
    static const std::array<std::string, 15> FONT_WEIGHT_TO_STRING = { "FontWeight.W100", "FontWeight.W200",
        "FontWeight.W300", "FontWeight.W400", "FontWeight.W500", "FontWeight.W600", "FontWeight.W700",
        "FontWeight.W800", "FontWeight.W900", "FontWeight.BOLD", "FontWeight.NORMAL", "FontWeight.BOLDER",
        "FontWeight.LIGHTER", "FontWeight.MEDIUM", "FontWeight.REGULAR" };
    json->Put("fontWeight",
        FONT_WEIGHT_TO_STRING.at(static_cast<int32_t>(GetFontWeight().value_or(FontWeight::W400))).c_str());
    std::vector<std::string> fontFamilyVector =
        GetFontFamily().value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
    std::string fontFamily = '{' + fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    fontFamily += '}';
    json->Put("fontFamily", fontFamily.c_str());
    static const std::array<std::string, 5> TEXT_DECORATION_TO_STRING = {
        "TextDecorationType.None",
        "TextDecorationType.Underline",
        "TextDecorationType.Overline",
        "TextDecorationType.LineThrough",
        "TextDecorationType.Inherit",
    };
    std::string decoration =
        "{type:" +
        TEXT_DECORATION_TO_STRING.at(static_cast<int32_t>(GetTextDecoration().value_or(TextDecoration::NONE))) +
        ",color:" + GetTextDecorationColor().value_or(Color::BLACK).ColorToString() + '}';
    json->Put("decoration", decoration.c_str());
    static const std::array<std::string, 3> TEXT_CASE_TO_STRING = {
        "TextCase.Normal",
        "TextCase.LowerCase",
        "TextCase.UpperCase",
    };
    json->Put(
        "textCase", TEXT_CASE_TO_STRING.at(static_cast<int32_t>(GetTextCase().value_or(TextCase::NORMAL))).c_str());
    if (HasAdaptMinFontSize()) {
        json->Put("minFontSize", GetAdaptMinFontSize().value().ToString().c_str());
    }
    if (HasAdaptMaxFontSize()) {
        json->Put("maxFontSize", GetAdaptMaxFontSize().value().ToString().c_str());
    }
    if (HasLetterSpacing()) {
        json->Put("letterSpacing", GetLetterSpacing().value().ToString().c_str());
    }
    json->Put("lineHeight", GetLineHeight().value_or(0.0_vp).ToString().c_str());
    static const std::array<std::string, 6> TEXT_BASE_LINE_TO_STRING = {
        "textBaseline.ALPHABETIC",
        "textBaseline.IDEOGRAPHIC",
        "textBaseline.TOP",
        "textBaseline.BOTTOM",
        "textBaseline.MIDDLE",
        "textBaseline.HANGING",
    };
    json->Put("textBaseline",
        TEXT_BASE_LINE_TO_STRING.at(static_cast<int32_t>(GetTextBaseline().value_or(TextBaseline::ALPHABETIC)))
            .c_str());
    json->Put("baselineOffset", GetBaselineOffset().value_or(0.0_vp).ToString().c_str());
    static const std::array<std::string, 6> TEXT_ALIGN_TO_STRING = {
        "TextAlign.Left",
        "TextAlign.Right",
        "TextAlign.Center",
        "TextAlign.Justify",
        "TextAlign.Start",
        "TextAlign.End",
    };
    json->Put(
        "textAlign", TEXT_ALIGN_TO_STRING.at(static_cast<int32_t>(GetTextAlign().value_or(TextAlign::START))).c_str());
    static const std::array<std::string, 3> TEXT_OVERFLOW_TO_STRING = {
        "TextOverflow.Clip",
        "TextOverflow.Ellipsis",
        "TextOverflow.None",
    };
    json->Put("textOverflow",
        TEXT_OVERFLOW_TO_STRING.at(static_cast<int32_t>(GetTextOverflow().value_or(TextOverflow::CLIP))).c_str());
    json->Put("maxLines", std::to_string(GetMaxLines().value_or(UINT32_MAX)).c_str());
}

} // namespace OHOS::Ace::NG