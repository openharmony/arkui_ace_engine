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
    json->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
    std::vector<std::string> fontFamilyVector =
        GetFontFamily().value_or<std::vector<std::string>>({ "HarmonyOS Sans" });
    if (fontFamilyVector.empty()) {
        fontFamilyVector = std::vector<std::string>({ "HarmonyOS Sans" });
    }
    std::string fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    json->Put("fontFamily", fontFamily.c_str());

    auto jsonDecoration = JsonUtil::Create(true);
    std::string type = V2::ConvertWrapTextDecorationToStirng(GetTextDecoration().value_or(TextDecoration::NONE));
    jsonDecoration->Put("type", type.c_str());
    jsonDecoration->Put("color", GetTextDecorationColor().value_or(Color::BLACK).ColorToString().c_str());
    json->Put("decoration", jsonDecoration->ToString().c_str());

    json->Put("textCase", V2::ConvertWrapTextCaseToStirng(GetTextCase().value_or(TextCase::NORMAL)).c_str());
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
    json->Put(
        "baselineOffset", std::to_string(static_cast<int32_t>(GetBaselineOffset().value_or(0.0_vp).Value())).c_str());
    json->Put("textAlign", V2::ConvertWrapTextAlignToString(GetTextAlign().value_or(TextAlign::START)).c_str());
    json->Put(
        "textOverflow", V2::ConvertWrapTextOverflowToString(GetTextOverflow().value_or(TextOverflow::CLIP)).c_str());
    json->Put("maxLines", std::to_string(GetMaxLines().value_or(UINT32_MAX)).c_str());
}

} // namespace OHOS::Ace::NG