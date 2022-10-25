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
}
} // namespace OHOS::Ace::NG
