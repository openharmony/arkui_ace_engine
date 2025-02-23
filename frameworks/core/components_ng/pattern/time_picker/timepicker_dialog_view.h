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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_DIALOG_VIEW_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TimePickerDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProperties, const TimePickerSettingData& settingData,
        const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, PickerTime> timePickerProperty,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static void SetStartTime(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerTime& value);
    static void SetEndTime(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerTime& value);
    static void SetSelectedTime(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerTime& value);
    static void SetDialogTitleDate(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerDate& value);
    static void SetHour24(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, bool isUseMilitaryTime = false);
    static void SetEnableCascade(
        const RefPtr<TimePickerRowPattern>& timePickerRowPattern, bool isEnableCascade = false);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogEnterSelectedArea(const RefPtr<FrameNode>& frameNode, DialogEvent&& onEnterSelectedArea);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& frameNode,
        const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static RefPtr<FrameNode> CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateDividerNode(const RefPtr<FrameNode>& dateNode, bool isCreateDivider = false);
    static RefPtr<FrameNode> CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos, DialogEvent& acceptEvent);
    static RefPtr<FrameNode> CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
        const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateBoxNode();

private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static void UpdateButtonLayoutProperty(
        const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateConfirmButtonMargin(
        const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateCancelButtonMargin(
        const RefPtr<ButtonLayoutProperty>& buttonCancelLayoutProperty, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext);
    static void UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
        const RefPtr<ButtonTheme>& buttonTheme);
    static void SetTextProperties(const RefPtr<PickerTheme>& pickerTheme, const PickerTextProperties& properties);
    static void UpdateButtonDefaultFocus(
        const std::vector<ButtonInfo>& buttonInfos, const RefPtr<FrameNode>& buttonNode, bool isConfirm);
    static void BuildDialogAcceptAndCancelButton(const std::vector<ButtonInfo>& buttonInfos,
        const TimePickerSettingData& settingData, const RefPtr<FrameNode>& acceptNode,
        const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& dialogNode,
        const RefPtr<FrameNode>& contentColumn, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);

    static RefPtr<FrameNode> CreateNextPrevButtonNode(std::function<void()>& timePickerSwitchEvent,
        const RefPtr<FrameNode>& timeNode, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateButtonNodeForAging(const RefPtr<FrameNode>& buttonTitleNode,
        const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& timePickerNode,
        const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static bool NeedAdaptForAging();
    static std::function<void()> CreateAndSetTimePickerSwitchEvent(const RefPtr<FrameNode>& buttonTitleNode,
        const RefPtr<FrameNode>& timePicker, const RefPtr<FrameNode>& buttonCancelNode,
        const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<FrameNode>& cancelNextDividerNode,
        const RefPtr<FrameNode>& nextConfirmDividerNode);
    static void SwitchTimePickerPage(const RefPtr<FrameNode>& buttonTitleNode, const RefPtr<FrameNode>& timePickerNode,
        const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<FrameNode>& buttonConfirmNode,
        const RefPtr<FrameNode>& cancelNextDividerNode, const RefPtr<FrameNode>& nextConfirmDividerNode);
    static bool GetIsUserSetTextProperties(const PickerTextProperties& properties);
    static std::function<void(const GestureEvent&)> UpdateTimePickerSwitchEvent(
        const RefPtr<FrameNode>& timeNode, const RefPtr<FrameNode>& textNode, const RefPtr<DialogTheme>& dialogTheme,
        const RefPtr<FrameNode>& buttonNode, const std::function<void()>& timePickerSwitchEvent);
    static std::function<void()> CloseDialogEvent(const RefPtr<TimePickerRowPattern>& timePickerPattern,
        const RefPtr<FrameNode>& dialogNode);
    static const Dimension ConvertFontSizeLimit(const Dimension& fontSizeValue,
        const Dimension& fontSizeLimit, bool isUserSetFont = false);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue,
        const Dimension& fontSizeLimit = 0.0_vp, bool isUserSetFont = false);
    static const Dimension ConvertTitleFontScaleValue(const Dimension& fontSizeValue);
    static const Dimension AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale);
    static void GetUserSettingLimit();
    static void SetTextDisappearProperties(const RefPtr<PickerTheme>& pickerTheme,
        const PickerTextProperties& properties);
    static void UpdateConfirmButtonTextLayoutProperty(
        const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateCancelButtonTextLayoutProperty(
        const RefPtr<TextLayoutProperty>& textCancelLayoutProperty, const RefPtr<PickerTheme>& pickerTheme);
    static thread_local bool switchFlag_;
    static thread_local Dimension selectedTextStyleFont_;
    static thread_local Dimension normalTextStyleFont_;
    static thread_local Dimension disappearTextStyleFont_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TIME_PICKER_TIME_PICKER_DIALOG_VIEW_H
