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

#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
namespace {
inline constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
inline const std::string DEFAULT_FORMAT = "hms";
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
    result = result.substr(0, result.size() - 1);
    return result;
}
} // namespace

void TextClockLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("format", propFormat_.value_or(DEFAULT_FORMAT).c_str());
    json->Put("timeZoneOffset", std::to_string(propHoursWest_.value_or(GetSystemTimeZone())).c_str());
    json->Put("fontSize", GetFontSize().value_or(Dimension()).ToString().c_str());
    json->Put("fontColor", GetTextColor().value_or(Color::BLACK).ColorToString().c_str());
    json->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
    json->Put(
        "fontStyle", V2::ConvertWrapFontStyleToStirng(GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL)).c_str());
    json->Put("fontFamily", ConvertFontFamily(GetFontFamily().value_or(std::vector<std::string>())).c_str());
}
} // namespace OHOS::Ace::NG
