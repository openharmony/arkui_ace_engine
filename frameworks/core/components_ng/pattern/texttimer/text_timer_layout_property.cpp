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

#include "core/components_ng/pattern/texttimer/text_timer_layout_property.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr double DEFAULT_COUNT = 60000.0;
inline const std::string DEFAULT_FORMAT = "HH:mm:ss.SS";
std::string ConvertFontFamily(const std::vector<std::string>& fontFamily)
{
    std::string result;
    for (const auto& item : fontFamily) {
        result += item;
        result += ",";
    }
    result = result.substr(0, result.size() - 1);
    return result;
}
} // namespace

void TextTimerLayoutProperty::ResetCount()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetCount();
}

inline std::unique_ptr<JsonValue> ConvertShadowToJson(const Shadow& shadow)
{
    auto jsonShadow = JsonUtil::Create(true);
    jsonShadow->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
    jsonShadow->Put("color", shadow.GetColor().ColorToString().c_str());
    jsonShadow->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
    jsonShadow->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
    jsonShadow->Put("type", std::to_string(static_cast<int32_t>(shadow.GetShadowType())).c_str());
    return jsonShadow;
}

std::unique_ptr<JsonValue> ConvertShadowsToJson(const std::vector<Shadow>& shadows)
{
    auto jsonShadows = JsonUtil::CreateArray(true);
    for (const auto& shadow : shadows) {
        jsonShadows->Put(ConvertShadowToJson(shadow));
    }
    return jsonShadows;
}

void TextTimerLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("format", propFormat_.value_or(DEFAULT_FORMAT).c_str());
    json->Put("isCountDown", propIsCountDown_.value_or(false) ? "true" : "false");
    json->Put("count", std::to_string(propInputCount_.value_or(DEFAULT_COUNT)).c_str());
    json->Put("fontSize", GetFontSize().value_or(Dimension()).ToString().c_str());
    json->Put("fontColor", GetTextColor().value_or(Color::BLACK).ColorToString().c_str());
    json->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
    json->Put(
        "fontStyle", V2::ConvertWrapFontStyleToStirng(GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str());
    json->Put("fontFamily", ConvertFontFamily(GetFontFamily().value_or(std::vector<std::string>())).c_str());

    auto shadow = GetTextShadow().value_or(std::vector<Shadow> { Shadow() });
    // Determines if there are multiple textShadows
    auto jsonShadow = (shadow.size() == 1) ? ConvertShadowToJson(shadow.front()) : ConvertShadowsToJson(shadow);
    json->Put("textShadow", jsonShadow);
}
} // namespace OHOS::Ace::NG
