/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_MODEL_NG_H

#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"

namespace OHOS::Ace::NG {
using TimeChangeEvent = std::function<void(const BaseEventInfo* info)>;

class ACE_EXPORT TimePickerModelNG : public TimePickerModel {
public:
    void CreateTimePicker(RefPtr<PickerTheme> pickerTheme, bool hasSecond = false) override;
    void SetStartTime(const PickerTime& value) override;
    void SetEndTime(const PickerTime& value) override;
    void SetSelectedTime(const PickerTime& value) override;
    void SetOnChange(TimeChangeEvent&& onChange) override;
    void SetOnEnterSelectedArea(TimeChangeEvent&& onEnterSelectedArea) override;
    void SetHour24(bool isUseMilitaryTime) override;
    void SetIsEnableHapticFeedback(bool isEnableHapticFeedback) override;
    void SetDateTimeOptions(ZeroPrefixType& hourType,
        ZeroPrefixType& minuteType, ZeroPrefixType& secondType) override;
    void SetWheelModeEnabled(bool wheelModeEnabled) override;
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value) override;
    void HasUserDefinedDisappearFontFamily(bool isUserDefined) override;
    void HasUserDefinedNormalFontFamily(bool isUserDefined) override;
    void HasUserDefinedSelectedFontFamily(bool isUserDefined) override;
    void SetEnableCascade(bool isEnableCascade) override;
    void SetBackgroundColor(const Color& color) override;
    void SetChangeEvent(TimeChangeEvent&& onChange) override;
    void HasUserDefinedOpacity() override;
    static void SetOnChange(FrameNode* frameNode, TimeChangeEvent&& onChange);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);

    static void SetStartTime(FrameNode* frameNode, const PickerTime& value);
    static void SetEndTime(FrameNode* frameNode, const PickerTime& value);
    static void SetSelectedTime(FrameNode* frameNode, const PickerTime& value);
    static void SetDisappearTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value);
    static void SetNormalTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value);
    static void SetSelectedTextStyle(
        FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& color);
    static void SetHour24(FrameNode* frameNode, bool isUseMilitaryTime);
    static void SetDateTimeOptions(FrameNode* frameNode, ZeroPrefixType& hourType,
        ZeroPrefixType& minuteType, ZeroPrefixType& secondType);
    static void SetIsEnableHapticFeedback(FrameNode* frameNode, bool isEnableHapticFeedback);
    static PickerTextStyle getSelectedTextStyle(FrameNode* frameNode);
    static PickerTextStyle getNormalTextStyle(FrameNode* frameNode);
    static PickerTextStyle getDisappearTextStyle(FrameNode* frameNode);
    static PickerTime getTimepickerStart(FrameNode* frameNode);
    static PickerTime getTimepickerEnd(FrameNode* frameNode);
    static PickerTime getTimepickerSelected(FrameNode* frameNode);
    static uint32_t getTimepickerBackgroundColor(FrameNode* frameNode);
    static int32_t getTimepickerUseMilitaryTime(FrameNode* frameNode);
    static int32_t getTimepickerEnableCascade(FrameNode* frameNode);
    static int32_t getEnableHapticFeedback(FrameNode* frameNode);
    static void SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme);
    static void SetWheelModeEnabled(FrameNode* frameNode, bool wheelModeEnabled);
    static void SetEnableCascade(FrameNode* frameNode, bool isEnableCascade);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue);
private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
};

class ACE_EXPORT TimePickerDialogModelNG : public TimePickerDialogModel {
public:
    void SetTimePickerDialogShow(PickerDialogInfo& pickerDialog, NG::TimePickerSettingData& settingData,
        std::function<void()>&& onCancel, std::function<void(const std::string&)>&& onAccept,
        std::function<void(const std::string&)>&& onChange,
        std::function<void(const std::string&)>&& onEnterSelectedArea, TimePickerDialogEvent& timePickerDialogEvent,
        const std::vector<ButtonInfo>& buttonInfos) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_MODEL_NG_H
