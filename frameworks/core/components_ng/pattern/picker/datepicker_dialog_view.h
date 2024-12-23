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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"

namespace OHOS::Ace::NG {
class DateTimeAnimationController;
class CheckBoxPaintProperty;
class ACE_EXPORT DatePickerDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
        const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static void SetStartDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value);
    static void SetEndDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value);
    static void SetSelectedDate(const RefPtr<FrameNode>& frameNode, const PickerDate& value);
    static void SetShowLunar(const RefPtr<FrameNode>& frameNode, bool lunar = false);
    static void SetDateTextProperties(const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties);
    static void SetTimeTextProperties(const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogDateChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogDateAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogSwitchEvent(std::function<bool()> switchEvent, const RefPtr<FrameNode>& pickerStack);
    static RefPtr<FrameNode> CreateButtonNode(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& datePickerNode, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static RefPtr<FrameNode> CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateTitleButtonRowNode();
    static void CreateTitleIconNode(const RefPtr<FrameNode>& titleNode);
    static RefPtr<FrameNode> CreateDividerNode(const RefPtr<FrameNode>& dateNode, bool isCreateDivider = false);
    static RefPtr<FrameNode> CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& datePickerNode, DialogEvent& acceptEvent, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
        const RefPtr<FrameNode>& datePickerNode, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateDateNode(int32_t dateNodeId, std::map<std::string, PickerDate> datePickerProperty,
        const PickerTextProperties& properties, bool isLunar, bool hasTime);
    static RefPtr<FrameNode> CreateColumnNode(int32_t nodeId, uint32_t showCount, bool isDate = true);
    static void CreateNormalDateNode(const RefPtr<FrameNode>& dateNode, uint32_t showCount);
    static void CreateSingleDateNode(const RefPtr<FrameNode>& dateNode, uint32_t showCount);
    static RefPtr<FrameNode> CreateTimeNode(std::map<std::string, PickerTime> timePickerProperty,
        const PickerTextProperties& properties, bool useMilitaryTime);
    static RefPtr<FrameNode> CreateLunarSwitchTextNode();

    static bool switchFlag_;

private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateColumnNode();
    static RefPtr<FrameNode> CreateButtonNode();
    static void UpdateCheckboxPaintProperty(const RefPtr<CheckBoxPaintProperty>& checkboxPaintProps,
    bool isLunar, const CheckboxSettingData& checkboxSettingData);
    static void CreateLunarswitchNode(const RefPtr<FrameNode>& contentColumn, const RefPtr<FrameNode>& dateNode,
        std::function<void(const bool)>&& changeEvent, bool isLunar, const CheckboxSettingData& checkboxSettingData);
    static void SetTitleMouseHoverEvent(const RefPtr<FrameNode>& titleRow);
    static void HandleMouseEvent(const RefPtr<FrameNode>& titleButton, bool isHover);
    static void PlayHoverAnimation(const RefPtr<FrameNode>& titleButton, const Color& color);
    static void MountColumnNodeToPicker(
        const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& pickerNode, uint32_t columnWeight = 1);
    static void UpdateTitleRowLayoutProps(const RefPtr<FrameNode>& titleRow);
    static void SetTimeNodeColumnWeight(const RefPtr<FrameNode>& timeNode, const DatePickerSettingData& settingData);
    static RefPtr<FrameNode> CreateAndMountDateNode(
        const DatePickerSettingData& settingData, const RefPtr<FrameNode>& pickerStack);
    static RefPtr<FrameNode> CreateAndMountButtonTitleNode(
        const RefPtr<FrameNode>& dateNode, const RefPtr<FrameNode>& contentColumn);
    static std::function<void(bool)> CreateLunarChangeEvent(const RefPtr<FrameNode>& dateNode);
    static RefPtr<FrameNode> CreateAndMountMonthDaysNode(const DatePickerSettingData& settingData,
        const RefPtr<FrameNode>& dateNode, const RefPtr<FrameNode>& pickerRow,
        std::function<void(bool)>&& lunarChangeEvent);
    static RefPtr<FrameNode> CreateAndMountTimeNode(const DatePickerSettingData& settingData,
        const RefPtr<FrameNode>& monthDaysNode, const RefPtr<FrameNode>& pickerRow);
    static std::function<void()> CreateAndSetDialogSwitchEvent(const RefPtr<FrameNode>& pickerStack,
        const RefPtr<FrameNode>& contentColumn, const DatePickerSettingData& settingData);
    static void SwitchPickerPage(const RefPtr<FrameNode>& pickerStack, const RefPtr<FrameNode>& contentColumn,
        const RefPtr<DateTimeAnimationController>& animationController, bool useMilitary = false);
    static void SwitchDatePickerPage(const RefPtr<FrameNode>& dateNode, bool IsSwitchByTitle = false);
    static void HideContentChildrenButton(const RefPtr<FrameNode>& contentRow);
    static void SwitchContentRowButton(const RefPtr<FrameNode>& contentRow, bool useMilitary = false);
    static void ShowContentRowButton(const RefPtr<FrameNode>& contentRow, bool isFirstPage = true);
    static void CreateAndAddTitleClickEvent(
        std::function<void()>& titleSwitchEvent, const RefPtr<FrameNode>& buttonTitleNode);
    static void BuildDialogAcceptAndCancelButton(const std::vector<ButtonInfo>& buttonInfos,
        const DatePickerSettingData& settingData, const RefPtr<FrameNode>& acceptNode,
        const RefPtr<FrameNode>& dateNode, const RefPtr<FrameNode>& dialogNode, const RefPtr<FrameNode>& contentColumn,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static void UpdateConfirmButtonTextLayoutProperty(
        const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateButtonLayoutProperty(
        const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateConfirmButtonMargin(
        const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateCancelButtonMargin(
        const RefPtr<ButtonLayoutProperty>& buttonCancelLayoutProperty, const RefPtr<DialogTheme>& dialogTheme);
    static void UpdateNextButtonMargin(const RefPtr<ButtonLayoutProperty>& buttonNextLayoutProperty);
    static void UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext);
    static void UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
        const RefPtr<ButtonTheme>& buttonTheme);
    static void UpdateContentPadding(const RefPtr<FrameNode>& contentColumn);
    static void UpdateButtonDefaultFocus(const std::vector<ButtonInfo>& buttonInfos,
        const RefPtr<FrameNode>& buttonNode, bool isConfirm);
    static RefPtr<FrameNode> CreateNextPrevButtonNode(
        std::function<void()> & switchEvent,
        const RefPtr<FrameNode>& dateNode, const std::vector<ButtonInfo> &buttonInfos,
        const RefPtr<FrameNode>& contentRow);
    static void BuildDialogAcceptAndCancelButtonForAging(
        const std::vector<ButtonInfo> &buttonInfos, const DatePickerSettingData &settingData,
        const RefPtr<FrameNode> &timePickerNode, const RefPtr<FrameNode> &acceptNode,
        const RefPtr<FrameNode> &dateNode, const RefPtr<FrameNode> &dialogNode,
        const RefPtr<FrameNode> &contentColumn, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static bool NeedAdaptForAging();
    static RefPtr<FrameNode> CreateButtonNodeForAging(const DatePickerSettingData& settingData,
        const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& monthAndDayNode,
        const RefPtr<FrameNode>& datePickerNode, const std::vector<ButtonInfo>& buttonInfos,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    static std::function<void()> CreateAndSetTimePickerSwitchEvent(
        const RefPtr<FrameNode>& monthAndDayPickerNode, const RefPtr<FrameNode>& timePickerNode,
        const RefPtr<FrameNode>& contentRow);
    static std::function<void(const GestureEvent&)> CreateNextPrevClickEvent(
        const RefPtr<FrameNode>& textNextPrevNode, const RefPtr<FrameNode>& nextPrevButtonNode,
        const RefPtr<DialogTheme>& dialogTheme, const RefPtr<FrameNode>& dateNode,
        std::function<void()>& switchEvent, const RefPtr<FrameNode>& contentRow);
    static void SwitchTimePickerPage(
        const RefPtr<FrameNode> &monthAndDayPickerNode, const RefPtr<FrameNode> &timePickerNode,
        const RefPtr<FrameNode> &contentRow);
    static bool GetIsUserSetTextProperties(const PickerTextProperties& properties);
    static void SetAnimationProperty(const RefPtr<FrameNode>& pickerStack,
        const RefPtr<FrameNode>& contentColumn, const RefPtr<DateTimeAnimationController>& animationController);
    static std::function<void()> CloseDialogEvent(const RefPtr<FrameNode>& dateNode,
        const RefPtr<FrameNode>& dialogNode);
    static const Dimension ConvertFontSizeLimit(const Dimension& fontSizeValue,
        const Dimension& fontSizeLimit, bool isUserSetFont = false);
    static const Dimension ConvertFontScaleValue(const Dimension& fontSizeValue,
        const Dimension& fontSizeLimit = 0.0_vp, bool isUserSetFont = false);
    static const Dimension ConvertTitleFontScaleValue(const Dimension& fontSizeValue);
    static const Dimension AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale);
    static void GetUserSettingLimit();
    static void UpdateCancelButtonTextLayoutProperty(
        const RefPtr<TextLayoutProperty>& textCancelLayoutProperty, const RefPtr<PickerTheme>& pickerTheme);
    static void UpdateTimePickerChildrenStatus(const RefPtr<FrameNode>& timePickerNode);
    static void SwitchFocusStatus(
        const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& monthAndDayPickerNode);
    static bool switchTimePickerFlag_;
    static bool switchDatePickerFlag_;
    static bool isShowTime_;
    static bool isUserSetFont_;
    static Dimension selectedTextStyleFont_;
    static Dimension normalTextStyleFont_;
    static Dimension disappearTextStyleFont_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_PICKER_DIALOG_VIEW_H
