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
    auto minuteColumn = allChildNode["minute"].Upgrade();
    CHECK_NULL_RETURN(minuteColumn, "");
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(hourPickerColumnPattern, "");
    int hour = hourPickerColumnPattern->GetCurrentIndex(); // + 1;
    if (!timePickerRowPattern->GetHour24()) {
        hour += 1;
    }
    std::string textHour = std::to_string(hour);
    if (hour < DOUBLE_DIGIT) {
        textHour = ZERO + textHour;
    }
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(minutePickerColumnPattern, "");
    int minute = minutePickerColumnPattern->GetCurrentIndex();

    std::string textMinute = std::to_string(minute);
    if (minute < DOUBLE_DIGIT) {
        textMinute = ZERO + textMinute;
    }

    if (!timePickerRowPattern->GetHour24()) {
        auto amPmColumn = allChildNode["amPm"].Upgrade();
        CHECK_NULL_RETURN(amPmColumn, "");
        auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        if (amPmPickerColumnPattern->GetCurrentIndex() == 0) {
            return AM + textHour + COLON + textMinute;
        } else {
            return PM + textHour + COLON + textMinute;
        }
    }
    return textHour + COLON + textMinute;
}
} // namespace OHOS::Ace::NG
