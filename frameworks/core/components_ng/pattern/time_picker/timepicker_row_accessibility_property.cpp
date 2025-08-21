/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/time_picker/timepicker_row_accessibility_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const std::string COLON = ":";
} // namespace

std::string TimePickerRowAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto timePickerRowPattern = frameNode->GetPattern<NG::TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, "");
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto hourColumn = allChildNode["hour"].Upgrade();
    CHECK_NULL_RETURN(hourColumn, "");
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(hourPickerColumnPattern, "");
    auto minuteColumn = allChildNode["minute"].Upgrade();
    CHECK_NULL_RETURN(minuteColumn, "");
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(minutePickerColumnPattern, "");

    std::string result;
    auto options = timePickerRowPattern->GetOptions();
    if (options.find(hourColumn) != options.end()) {
        std::string hour = options[hourColumn][hourPickerColumnPattern->GetCurrentIndex()];
        result += hour;
    }
    if (options.find(minuteColumn) != options.end()) {
        std::string minute = options[minuteColumn][minutePickerColumnPattern->GetCurrentIndex()];
        result += COLON + minute;
    }
    if (timePickerRowPattern->GetHasSecond()) {
        auto secondColumn = allChildNode["second"].Upgrade();
        CHECK_NULL_RETURN(secondColumn, "");
        auto secondPickerColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(secondPickerColumnPattern, "");
        if (options.find(secondColumn) != options.end()) {
            std::string second = options[secondColumn][secondPickerColumnPattern->GetCurrentIndex()];
            result += COLON + second;
        }
    }
    if (!timePickerRowPattern->GetHour24()) {
        auto amPmColumn = allChildNode["amPm"].Upgrade();
        CHECK_NULL_RETURN(amPmColumn, "");
        auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(amPmPickerColumnPattern, "");
        auto optionIndex = amPmPickerColumnPattern->GetCurrentIndex();
        if (optionIndex >= 0) {
            result = timePickerRowPattern->GetOptionValue(amPmColumn, optionIndex).append(" ") + result;
        }
    }

    if (timePickerRowPattern->GetIsShowInDatePickerDialog()) {
        result = GetShowDatePickerText() + result;
    }

    return result;
}

std::string TimePickerRowAccessibilityProperty::GetShowDatePickerText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto parentNode = frameNode->GetParentFrameNode();
    CHECK_NULL_RETURN(parentNode, "");
    auto dateNode = AceType::DynamicCast<FrameNode>(parentNode->GetChildAtIndex(0));
    CHECK_NULL_RETURN(dateNode, "");
    auto pattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild());
    CHECK_NULL_RETURN(stackMonthDays, "");
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    CHECK_NULL_RETURN(blendMonthDays, "");
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    CHECK_NULL_RETURN(monthDaysColumnNode, "");
    auto columnPattern = monthDaysColumnNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(columnPattern, "");
    auto index = columnPattern->GetCurrentIndex();
    auto options = columnPattern->GetOptions();
    std::string result = "";
    auto it = options.find(monthDaysColumnNode);
    if (it != options.end() && index >= 0 && index < it->second.size()) {
        auto date = it->second.at(index);
        result = DatePickerPattern::GetFormatString(date);
        result.append(" ");
    }
    return result;
}
} // namespace OHOS::Ace::NG
