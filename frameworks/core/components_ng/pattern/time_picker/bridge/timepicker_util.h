/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIMEPICKER_BRIDGE_TIME_PICKER_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIMEPICKER_BRIDGE_TIME_PICKER_UTIL_H

#include <map>
#include <string>
#include <functional>


#include "ui/base/referenced.h"

#include "core/components_ng/pattern/picker/picker_data.h"

struct Ark_TimePickerDialogOptions;
namespace OHOS::Ace {
enum class VisibleType;
class Dimension;
class GestureEvent;
class PickerTheme;
struct ButtonInfo;
struct DialogProperties;

namespace NG {
class FrameNode;
struct DatePickerSettingData;
struct PickerTextProperties;
struct TimePickerSettingData;

namespace TimePickerUtil {
constexpr int32_t BUFFER_NODE_NUMBER = 2;
const char TIME_PICKER_ETS_TAG[] = "TimePicker";
const char COLUMN_ETS_TAG[] = "Column";
const char TEXT_ETS_TAG[] = "Text";
const char STACK_ETS_TAG[] = "Stack";
const char BUTTON_ETS_TAG[] = "Button";
const char DIVIDER_ETS_TAG[] = "Divider";

struct TimePickerNodeInfo {
    bool hasHourNode;
    bool hasMinuteNode;
    uint32_t showCount;
    int32_t hourId;
    int32_t minuteId;
    RefPtr<FrameNode> timePickerNode;
};

struct TimePickerDialogInfo {
    const DialogProperties& dialogProperties;
    const TimePickerSettingData& settingData;
    const std::vector<ButtonInfo>& buttonInfos;
    RefPtr<FrameNode> timePickerNode;
};
struct TimepickerCustomModifier {
    std::string (*getShowTimePickerText)(const RefPtr<FrameNode>& frameNode);
    std::optional<PickerTime> (*getTimepickerCurrentTime)(const RefPtr<FrameNode>& frameNode);
    bool (*setTimepickerFocusDisable)(const RefPtr<FrameNode>& frameNode);
    bool (*setTimepickerFocusEnable)(const RefPtr<FrameNode>& frameNode);
    bool (*setTimepickerRowPatternStopHaptic)(const RefPtr<FrameNode>& frameNode);
    bool (*setTimeNode)(const RefPtr<FrameNode>& frameNode, const DatePickerSettingData& settingData);
    bool (*setOnChangeForDatePicker)(const RefPtr<FrameNode>& frameNode, std::function<void()>&& changeEvent);
    bool (*updateVisibility)(const RefPtr<FrameNode>& frameNode, const VisibleType& value);
    bool (*createTimeNode)(int32_t nodeId, TimePickerNodeInfo& info, bool isEnableHapticFeedback);
    bool (*setColumn)(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& columnNode);
    bool (*setSelectedTime)(const RefPtr<FrameNode>& frameNode, const PickerTime& value);
    bool (*setHour24)(const RefPtr<FrameNode>& frameNode, bool value);
    void (*createTimePickerColumnPattern)(int32_t nodeId, RefPtr<FrameNode>& columnNode);
    void (*setTimeTextProperties)(const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties,
        Dimension disappearTextStyleFont, Dimension normalTextStyleFont, Dimension selectedTextStyleFont);
    void (*setTimePickerDialogViewShow)(TimePickerDialogInfo& info,
        std::map<std::string, PickerTime> timePickerProperty,
        std::map<std::string, std::function<void(const std::string&)>> dialogEvent,
        std::map<std::string, std::function<void(const GestureEvent& info)>> dialogCancelEvent);
};

struct ArkUITimePickerDialogModifier {
    void (*showTimePickerDialog)(const Ark_TimePickerDialogOptions* options);
};
} // namespace TimePickerUtil
} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIMEPICKER_BRIDGE_TIME_PICKER_UTIL_H