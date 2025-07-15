/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/time_picker/timepicker_model_static.h"

#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
void TimePickerModelStatic::SetHasSecond(FrameNode* frameNode, bool hasSecond)
{
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->SetHasSecond(hasSecond);
}

void TimePickerModelStatic::SetDigitalCrownSensitivity(FrameNode* frameNode, const std::optional<int32_t>& valueOpt)
{
    if (!valueOpt) {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DigitalCrownSensitivity, frameNode);
        return;
    }
    auto crownSensitivity = *valueOpt;
    if (crownSensitivity < CROWN_SENSITIVITY_MIN || crownSensitivity > CROWN_SENSITIVITY_MAX) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto timePickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerPattern);
    timePickerPattern->SetDigitalCrownSensitivity(crownSensitivity);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DigitalCrownSensitivity, crownSensitivity, frameNode);
}

void TimePickerModelStatic::SetChangeEvent(FrameNode* frameNode, TimeChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void TimePickerModelStatic::SetSelectedTime(FrameNode* frameNode, const int64_t& value)
{
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);

    std::time_t time = static_cast<std::time_t>(value / 1000);
    std::tm local_tm{};
#ifdef WINDOWS_PLATFORM
    errno_t err = localtime_s(&local_tm, &time);
    if (err != 0) {
        LOGE("Failed to convert time to local time, error code: %{public}d", err);
        return;
    }
#else
    localtime_r(&time, &local_tm);
#endif

    auto hour = local_tm.tm_hour;
    const auto minute = local_tm.tm_min;
    const auto second = local_tm.tm_sec;
    if (!timePickerRowPattern->GetHour24()) {
        hour = (hour % 12 == 0) ? 12 : hour % 12; // Convert to 12-hour format
    }
    PickerTime pickerTime(hour, minute, second);
    timePickerRowPattern->SetSelectedTime(pickerTime);
}
} // namespace OHOS::Ace::NG
