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
const int DOUBLE_DIGIT = 10;
const std::string COLON = ":";
const std::string AM = "上午";
const std::string PM = "下午";
const std::string ZERO = "0";
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

    std::string result;
    auto hour = static_cast<int32_t>(hourPickerColumnPattern->GetCurrentIndex()); // + 1;
    if (!timePickerRowPattern->GetHour24()) {
        hour += 1;
    }
    std::string textHour = std::to_string(hour);
    if (hour < DOUBLE_DIGIT) {
        if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            textHour = ZERO + textHour;
        } else if (timePickerRowPattern->GetHour24()) {
            if (timePickerRowPattern->GetPrefixHour() != ZeroPrefixType::HIDE) {
                textHour = ZERO + textHour;
            }
        } else {
            if (timePickerRowPattern->GetPrefixHour() == ZeroPrefixType::SHOW) {
                textHour = ZERO + textHour;
            }
        }
    }
    result += textHour;

    GetMinuteText(result);
    GetSecondText(result);
    if (!timePickerRowPattern->GetHour24()) {
        auto amPmColumn = allChildNode["amPm"].Upgrade();
        CHECK_NULL_RETURN(amPmColumn, "");
        auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        if (amPmPickerColumnPattern->GetCurrentIndex() == 0) {
            result = AM + result;
        } else {
            result = PM + result;
        }
    }

    if (timePickerRowPattern->GetIsShowInDatePickerDialog()) {
        result = GetShowDatePickerText() + result;
    }

    return result;
}

void TimePickerRowAccessibilityProperty::GetMinuteText(std::string& result) const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<NG::TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    CHECK_NULL_VOID(minuteColumn);

    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_VOID(minutePickerColumnPattern);
    int minute = static_cast<int>(minutePickerColumnPattern->GetCurrentIndex());
    std::string textMinute = std::to_string(minute);
    if (minute < DOUBLE_DIGIT) {
        if (timePickerRowPattern->GetPrefixMinute() != ZeroPrefixType::HIDE) {
            textMinute = ZERO + textMinute;
        }
    }
    result += COLON + textMinute;
}

void TimePickerRowAccessibilityProperty::GetSecondText(std::string& result) const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<NG::TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    if (timePickerRowPattern->GetHasSecond()) {
        auto allChildNode = timePickerRowPattern->GetAllChildNode();
        auto secondColumn = allChildNode["second"].Upgrade();
        CHECK_NULL_VOID(secondColumn);
        auto secondPickerColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_VOID(secondPickerColumnPattern);
        int second = static_cast<int>(secondPickerColumnPattern->GetCurrentIndex());
        std::string textSecond = std::to_string(second);
        if (second < DOUBLE_DIGIT) {
            if (timePickerRowPattern->GetPrefixSecond() != ZeroPrefixType::HIDE) {
                textSecond = ZERO + textSecond;
            }
        }
        result += COLON + textSecond;
    }
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
    std::string result;
    auto it = options.find(monthDaysColumnNode);
    if (it != options.end()) {
        if (it->second.size() <= index) {
            result = "";
        }
        auto date = it->second.at(index);
        result = DatePickerPattern::GetFormatString(date);
        result.append(" ");
    } else {
        result = "";
    }
    return result;
}
} // namespace OHOS::Ace::NG
