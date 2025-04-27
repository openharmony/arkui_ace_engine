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

#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MINFONTSCALE = 0.85f;
constexpr float MAXFONTSCALE = 3.20f;
constexpr Dimension DEFAULT_MARQUEE_STEP_VP = 4.0_vp;
static const std::array<std::string, 6> TEXT_BASE_LINE_TO_STRING = {
    "textBaseline.ALPHABETIC",
    "textBaseline.IDEOGRAPHIC",
    "textBaseline.TOP",
    "textBaseline.BOTTOM",
    "textBaseline.MIDDLE",
    "textBaseline.HANGING",
};

inline std::unique_ptr<JsonValue> CovertShadowToJson(const Shadow& shadow)
{
    auto jsonShadow = JsonUtil::Create(true);
    jsonShadow->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
    jsonShadow->Put("color", shadow.GetColor().ColorToString().c_str());
    jsonShadow->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
    jsonShadow->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
    jsonShadow->Put("type", std::to_string(static_cast<int32_t>(shadow.GetShadowType())).c_str());
    return jsonShadow;
}

std::unique_ptr<JsonValue> CovertShadowsToJson(const std::vector<Shadow>& shadows)
{
    auto jsonShadows = JsonUtil::CreateArray(true);
    for (const auto& shadow : shadows) {
        jsonShadows->Put(CovertShadowToJson(shadow));
    }
    return jsonShadows;
}
} // namespace

std::string TextLayoutProperty::GetCopyOptionString() const
{
    std::string copyOptionString = "CopyOptions.None";
    switch (GetCopyOptionValue(CopyOptions::None)) {
        case CopyOptions::InApp:
            copyOptionString = "CopyOptions.InApp";
            break;
        case CopyOptions::Local:
            copyOptionString = "CopyOptions.Local";
            break;
        case CopyOptions::Distributed:
            copyOptionString = "CopyOptions.Distributed";
            break;
        case CopyOptions::None:
        default:
            break;
    }
    return copyOptionString;
}

std::string TextLayoutProperty::GetTextMarqueeOptionsString() const
{
    auto jsonValue = JsonUtil::Create(true);

    jsonValue->Put("start", GetTextMarqueeStart().value_or(true));
    jsonValue->Put("step",
        StringUtils::DoubleToString(GetTextMarqueeStep().value_or(DEFAULT_MARQUEE_STEP_VP.ConvertToPx())).c_str());
    jsonValue->Put("loop", std::to_string(GetTextMarqueeLoop().value_or(-1)).c_str());
    jsonValue->Put(
        "direction", GetTextMarqueeDirection().value_or(MarqueeDirection::DEFAULT) == MarqueeDirection::DEFAULT
                         ? "MarqueeDirection.DEFAULT"
                         : "MarqueeDirection.DEFAULT_REVERSE");
    jsonValue->Put("delay", std::to_string(GetTextMarqueeDelay().value_or(0)).c_str());
    jsonValue->Put("fadeout", GetTextMarqueeFadeout().value_or(false));
    jsonValue->Put(
        "startPolicy", GetTextMarqueeStartPolicy().value_or(MarqueeStartPolicy::DEFAULT) == MarqueeStartPolicy::DEFAULT
                           ? "MarqueeStartPolicy.DEFAULT"
                           : "MarqueeStartPolicy.ON_FOCUS");

    return jsonValue->ToString();
}

void TextLayoutProperty::UpdateMarqueeOptionsFromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateTextMarqueeStart(json->GetBool("start"));
    UpdateTextMarqueeStep(json->GetDouble("step"));
    UpdateTextMarqueeLoop(json->GetInt("loop"));
    UpdateTextMarqueeDirection(V2::ConvertWrapStringToMarqueeDirection(json->GetString("direction")));
    UpdateTextMarqueeDelay(json->GetInt("delay"));
    UpdateTextMarqueeFadeout(json->GetBool("fadeout"));
    UpdateTextMarqueeStartPolicy(V2::ConvertWrapStringToMarqueeStartPolicy(json->GetString("startPolicy")));
}

void TextLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    json->PutFixedAttr("content", UtfUtils::Str16DebugToStr8(GetContent().value_or(u"")).c_str(), filter,
        FIXED_ATTR_CONTENT);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto themeScopeId = host->GetThemeScopeId();
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>(themeScopeId);
    auto defaultColor = theme ? theme->GetTextStyle().GetTextColor() : Color::BLACK;
    json->PutExtAttr("fontColor",
        GetTextColor().value_or(defaultColor).ColorToString().c_str(), filter);
    json->PutExtAttr("fontStyle", GetFontStyleInJson(GetItalicFontStyle()).c_str(), filter);
    json->PutExtAttr("fontWeight", GetFontWeightInJson(GetFontWeight()).c_str(), filter);
    json->PutExtAttr("fontFamily", GetFontFamilyInJson(GetFontFamily()).c_str(), filter);
    json->PutExtAttr("renderingStrategy",
        GetSymbolRenderingStrategyInJson(GetSymbolRenderingStrategy()).c_str(), filter);
    json->PutExtAttr("effectStrategy", GetSymbolEffectStrategyInJson(GetSymbolEffectStrategy()).c_str(), filter);
    json->Put("symbolEffect", GetSymbolEffectOptionsInJson(
        GetSymbolEffectOptions().value_or(SymbolEffectOptions())).c_str());

    auto jsonDecoration = JsonUtil::Create(true);
    std::string type = V2::ConvertWrapTextDecorationToStirng(GetTextDecoration().value_or(TextDecoration::NONE));
    jsonDecoration->Put("type", type.c_str());
    jsonDecoration->Put("color", GetTextDecorationColor().value_or(Color::BLACK).ColorToString().c_str());
    std::string style =
        V2::ConvertWrapTextDecorationStyleToString(GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID));
    jsonDecoration->Put("style", style.c_str());
    json->PutExtAttr("decoration", jsonDecoration->ToString().c_str(), filter);

    json->PutExtAttr("textCase",
        V2::ConvertWrapTextCaseToStirng(GetTextCase().value_or(TextCase::NORMAL)).c_str(), filter);
    json->PutExtAttr("minFontSize", GetAdaptMinFontSize().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr("maxFontSize", GetAdaptMaxFontSize().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr("letterSpacing", GetLetterSpacing().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr("lineHeight", GetLineHeight().value_or(0.0_vp).ToString().c_str(), filter);
    json->PutExtAttr("textBaseline",
        TEXT_BASE_LINE_TO_STRING.at(static_cast<int32_t>(GetTextBaseline().value_or(TextBaseline::ALPHABETIC)))
            .c_str(), filter);
    json->PutExtAttr("baselineOffset",
        std::to_string(static_cast<int32_t>(GetBaselineOffset().value_or(0.0_vp).Value())).c_str(), filter);
    json->PutExtAttr("textAlign",
        V2::ConvertWrapTextAlignToString(GetTextAlign().value_or(TextAlign::START)).c_str(), filter);
    json->PutExtAttr("textOverflow",
        V2::ConvertWrapTextOverflowToString(GetTextOverflow().value_or(TextOverflow::CLIP)).c_str(), filter);
    json->PutExtAttr("maxLines", std::to_string(GetMaxLines().value_or(UINT32_MAX)).c_str(), filter);

    ToJsonValueForOption(json, filter);
}

void TextLayoutProperty::ToJsonValueForOption(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto shadow = GetTextShadow().value_or(std::vector<Shadow> { Shadow() });
    // Determines if there are multiple textShadows
    auto jsonShadow = (shadow.size() == 1) ? CovertShadowToJson(shadow.front()) : CovertShadowsToJson(shadow);
    json->PutExtAttr("textShadow", jsonShadow, filter);
    json->PutExtAttr("heightAdaptivePolicy", V2::ConvertWrapTextHeightAdaptivePolicyToString(
        GetHeightAdaptivePolicy().value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST)).c_str(), filter);
    json->PutExtAttr("copyOption", GetCopyOptionString().c_str(), filter);
    json->PutExtAttr("wordBreak",
        V2::ConvertWrapWordBreakToString(GetWordBreak().value_or(WordBreak::BREAK_WORD)).c_str(), filter);
    json->PutExtAttr("lineBreakStrategy", V2::ConvertWrapLineBreakStrategyToString(
        GetLineBreakStrategy().value_or(LineBreakStrategy::GREEDY)).c_str(), filter);
    json->PutExtAttr("ellipsisMode",
        V2::ConvertEllipsisModeToString(GetEllipsisMode().value_or(EllipsisMode::TAIL)).c_str(), filter);
    json->PutExtAttr("textSelectable", V2::ConvertWrapTextSelectableToString(
        GetTextSelectableMode().value_or(TextSelectableMode::SELECTABLE_UNFOCUSABLE)).c_str(), filter);
    json->PutExtAttr("marqueeOptions", GetTextMarqueeOptionsString().c_str(), filter);
    auto host = GetHost();
    json->PutExtAttr("privacySensitive", host ? host->IsPrivacySensitive() : false, filter);
    json->PutExtAttr("minFontScale", std::to_string(GetMinFontScale().value_or(MINFONTSCALE)).c_str(), filter);
    json->PutExtAttr("maxFontScale", std::to_string(GetMaxFontScale().value_or(MAXFONTSCALE)).c_str(), filter);
}

void TextLayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateContent(json->GetString("content"));
    UpdateFontSize(Dimension::FromString(json->GetString("fontSize")));
    UpdateTextColor(Color::ColorFromString(json->GetString("fontColor")));
    UpdateFontWeight(V2::ConvertWrapStringToFontWeight(json->GetString("fontWeight")));
    UpdateTextAlign(V2::ConvertWrapStringToTextAlign(json->GetString("textAlign")));
    UpdateTextOverflow(V2::ConvertWrapStringToTextOverflow(json->GetString("textOverflow")));
    UpdateMaxLines(StringUtils::StringToUint(json->GetString("maxLines")));
    UpdateMarqueeOptionsFromJson(json->GetObject("marqueeOptions"));
    LayoutProperty::FromJson(json);
}
} // namespace OHOS::Ace::NG
