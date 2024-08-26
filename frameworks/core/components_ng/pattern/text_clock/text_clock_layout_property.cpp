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

#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
inline const std::string DEFAULT_FORMAT_API_ELEVEN = "aa hh:mm:ss";
inline const std::string DEFAULT_FORMAT_API_TEN = "hms";
inline int32_t GetSystemTimeZone()
{
    struct timeval currentTime {};
    struct timezone timeZone {};
    gettimeofday(&currentTime, &timeZone);
    int32_t hoursWest = timeZone.tz_minuteswest / TOTAL_MINUTE_OF_HOUR;
    return hoursWest;
}

std::string ConvertFontFamily(const std::vector<std::string>& fontFamily)
{
    std::string result;
    for (const auto& item : fontFamily) {
        result += item;
        result += ",";
    }
    if (!result.empty()) {
        result = result.substr(0, result.size() - 1);
    }
    return result;
}

std::string CovertShadowToString(const Shadow& shadow)
{
    std::string result;
    result += std::string("radius") + std::to_string(shadow.GetBlurRadius());
    result += std::string("color") + shadow.GetColor().ColorToString();
    result += std::string("offsetX") + std::to_string(shadow.GetOffset().GetX());
    result += std::string("offsetY") + std::to_string(shadow.GetOffset().GetY());
    result += std::string("type") + std::to_string(static_cast<int32_t>(shadow.GetShadowType()));
    return result;
}

std::string ConvertTextShadow(const std::vector<Shadow>& textShadow)
{
    std::string result;
    for (const auto& item : textShadow) {
        result += CovertShadowToString(item);
        result += ",";
    }
    if (!result.empty()) {
        result = result.substr(0, result.size() - 1);
    }
    return result;
}

std::string ConvertFeature(const FONT_FEATURES_LIST& fontFeaTures)
{
    std::string result;
    for (const auto& item : fontFeaTures) {
        result += item.first + std::string(" ") + std::to_string(item.second);
        result += ",";
    }
    if (!result.empty()) {
        result = result.substr(0, result.size() - 1);
    }
    return result;
}
} // namespace

void TextClockLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        json->PutExtAttr("format", propFormat_.value_or(DEFAULT_FORMAT_API_ELEVEN).c_str(), filter);
    } else {
        json->PutExtAttr("format", propFormat_.value_or(DEFAULT_FORMAT_API_TEN).c_str(), filter);
    }
    json->PutExtAttr("timeZoneOffset",
        std::to_string(propHoursWest_.value_or(GetSystemTimeZone())).c_str(), filter);
    json->PutExtAttr("fontSize", GetFontSize().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr("fontColor", GetTextColor().value_or(Color::BLACK).ColorToString().c_str(), filter);
    json->PutExtAttr("fontWeight",
        V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::NORMAL)).c_str(), filter);
    json->PutExtAttr("fontStyle",
        V2::ConvertWrapFontStyleToStirng(GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str(), filter);
    json->PutExtAttr("fontFamily",
        ConvertFontFamily(GetFontFamily().value_or(std::vector<std::string>())).c_str(), filter);
    json->PutExtAttr("textShadow",
        ConvertTextShadow(GetTextShadow().value_or(std::vector<Shadow>())).c_str(), filter);
    json->PutExtAttr("fontFeature",
        ConvertFeature(GetFontFeature().value_or(FONT_FEATURES_LIST())).c_str(), filter);
}
} // namespace OHOS::Ace::NG
