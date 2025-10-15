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

    PickerTime pickerTime(local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec);
    timePickerRowPattern->SetSelectedTime(pickerTime);
}

void TimePickerModelStatic::SetOnChange(FrameNode* frameNode, TimeChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TimePickerModelStatic::SetOnEnterSelectedArea(FrameNode* frameNode, TimeChangeEvent&& onEnterSelectedArea)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEnterSelectedArea(std::move(onEnterSelectedArea));
}

void TimePickerModelStatic::SetEnableCascade(FrameNode* frameNode, const std::optional<bool>& isEnableCascade)
{
    CHECK_NULL_VOID(frameNode);
    if (isEnableCascade) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, IsEnableCascade, isEnableCascade.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, IsEnableCascade, frameNode);
    }
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->SetEnableCascade(isEnableCascade.value_or(false));
}

void TimePickerModelStatic::SetLoop(FrameNode* frameNode, const std::optional<bool>& loop)
{
    CHECK_NULL_VOID(frameNode);
    if (loop) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Loop, loop.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Loop, frameNode);
    }
}

void TimePickerModelStatic::SetUseMilitaryTime(FrameNode* frameNode, const std::optional<bool>& isUseMilitaryTime)
{
    CHECK_NULL_VOID(frameNode);
    if (isUseMilitaryTime) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, IsUseMilitaryTime, isUseMilitaryTime.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, IsUseMilitaryTime, frameNode);
    }
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->ClearOptionsHour();
    timePickerRowPattern->SetHour24(isUseMilitaryTime.value_or(false));
}

void TimePickerModelStatic::ResetDateTimeOptions(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    auto prefixHour = ZeroPrefixType::AUTO;
    timePickerRowPattern->SetPrefixHour(prefixHour);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, PrefixHour, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, PrefixMinute, frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, PrefixSecond, frameNode);
}
} // namespace OHOS::Ace::NG
