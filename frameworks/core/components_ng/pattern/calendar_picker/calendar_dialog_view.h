/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_DIALOG_VIEW_H

#include "base/utils/macros.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/calendar/calendar_event_hub.h"
#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_pattern.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CalendarDialogView {
public:
    static RefPtr<FrameNode> Show(const DialogProperties& dialogProperties, const CalendarSettingData& settingData,
        const std::vector<ButtonInfo>& buttonInfos, const std::map<std::string, NG::DialogEvent>& dialogEvent,
        const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent);
    static void UpdateIdealSize(const RefPtr<CalendarTheme>& calendarTheme,
        const RefPtr<LinearLayoutProperty>& layoutProps, const RefPtr<LayoutProperty>& calendarLayoutProperty,
        const RefPtr<FrameNode>& calendarNode);
    static void UpdatePaintProperties(const RefPtr<FrameNode>& monthFrameNode, const CalendarSettingData& settingData);
    static void UpdateButtons(
        const RefPtr<FrameNode>& buttonNode, size_t buttonIndex, std::vector<ButtonInfo>& buttonInfos);
    static void SetPreviousOrientation()
    {
        previousOrientation_ = SystemProperties::GetDeviceOrientation();
    }

    static bool CheckOrientationChange()
    {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(pipeline, true);
        return (!(SystemProperties::GetDeviceOrientation() == previousOrientation_)
                    ? Dimension(pipeline->GetRootWidth()).ConvertToVp() < deviceHeightLimit
                    : Dimension(pipeline->GetRootHeight()).ConvertToVp() < deviceHeightLimit);
    }

    static DeviceOrientation GetPreviousOrientation()
    {
        return previousOrientation_;
    }

    static bool ReportChangeEvent(int32_t nodeId, const std::string& compName,
        const std::string& eventName, const PickerDate& pickerDate);
    static bool CanReportChangeEvent(PickerDate& pickerDate, const PickerDate& newPickerDate);
    static bool GetReportChangeEventDate(PickerDate& pickerDate, const std::string& eventData);

private:
    static RefPtr<FrameNode> CreateTitleNode(const RefPtr<FrameNode>& calendarNode,
        const RefPtr<FrameNode>& calendarDialogNode);
    static RefPtr<FrameNode> CreateWeekNode(const RefPtr<FrameNode>& calendarNode);
    static RefPtr<FrameNode> CreateScrollNode();
    static RefPtr<FrameNode> CreateTitleImageNode(
        const RefPtr<FrameNode>& calendarNode, const InternalResource::ResourceId& resourceId);
    static RefPtr<FrameNode> CreateCalendarNode(const RefPtr<FrameNode>& calendarDialogNode,
        const CalendarSettingData& settingData, const std::map<std::string, NG::DialogEvent>& dialogEvent);
    static RefPtr<FrameNode> CreateCalendarSwiperNode();
    static RefPtr<FrameNode> CreateCalendarMonthNode(int32_t calendarNodeId,
        const CalendarSettingData& settingData, const DialogEvent& changeEvent);
    static void UpdateCalendarMonthData(const RefPtr<FrameNode>& calendarDialogNode,
        const RefPtr<FrameNode>& calendarNode, const CalendarMonth& currentMonth);
    static void SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static void SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange);
    static RefPtr<FrameNode> CreateButtonNode(bool isConfirm, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateConfirmNode(
        const RefPtr<FrameNode>& calendarNode, DialogEvent& acceptEvent, const std::vector<ButtonInfo>& buttonInfos);
    static RefPtr<FrameNode> CreateCancelNode(
        const NG::DialogGestureEvent& cancelEvent, const std::vector<ButtonInfo>& buttonInfos);
    static void UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext);
    static RefPtr<FrameNode> CreateDividerNode();
    static RefPtr<FrameNode> CreateOptionsNode(const RefPtr<FrameNode>& dialogNode, const RefPtr<FrameNode>& dateNode,
        const std::map<std::string, NG::DialogEvent>& dialogEvent,
        const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
        const std::vector<ButtonInfo>& buttonInfos);
    static void SetCalendarPaintProperties(const CalendarSettingData& settingData);
    static void InitOnRequestDataEvent(
        const RefPtr<FrameNode>& calendarDialogNode, const RefPtr<FrameNode>& calendarNode);
    static void OnSelectedChangeEvent(int32_t calendarNodeId, const std::string& callbackInfo,
        const DialogEvent& onChange, const CalendarSettingData& settingData);
    static void UpdateBackgroundStyle(const RefPtr<RenderContext>& renderContext,
        const DialogProperties& dialogProperties, const RefPtr<CalendarTheme>& calendarTheme);
    static void UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
        const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
        const RefPtr<ButtonTheme>& buttonTheme);
    static void DisableResetOptionButtonColor(
        const RefPtr<CalendarDialogPattern>& calendarDialogPattern, const std::vector<ButtonInfo>& buttonInfos);
    static void UpdateButtonDefaultFocus(const std::vector<ButtonInfo>& buttonInfos,
        const RefPtr<FrameNode>& buttonNode, bool isConfirm);
    static void UpdateDialogDefaultFocus(const RefPtr<FrameNode>& contentRow,
        const RefPtr<FrameNode>& contentColumn);
    static void UpdateDefaultFocusByButtonInfo(const RefPtr<FrameNode>& optionsNode,
        const RefPtr<FrameNode>& accept, const RefPtr<FrameNode>& cancel);
    static void UpdateButtonLayoutProperty(const RefPtr<FrameNode>& buttonNode, bool isConfirm,
        const std::vector<ButtonInfo>& buttonInfos, const RefPtr<PipelineContext>& pipeline);
    static void UpdateOptionLayoutProps(
        const RefPtr<FrameNode>& contentRow, const RefPtr<PipelineContext>& pipelineContext);
    static void OperationsToPattern(const RefPtr<FrameNode>& frameNode, const CalendarSettingData& settingData,
        const DialogProperties& dialogProperties, const std::vector<ButtonInfo>& buttonInfos);
    static void CreateChildNode(const RefPtr<FrameNode>& contentColumn,
        const RefPtr<FrameNode>& dialogNode, const DialogProperties& dialogProperties);
    static void InitCalendarProperty(const RefPtr<FrameNode>& calendarNode);
    static void SetCalendarIdealSize(
        const RefPtr<CalendarTheme>& theme, const RefPtr<LayoutProperty>& calendarLayoutProperty,
        const Dimension& weekHeight);
    static void SetTitleIdealSize(const RefPtr<CalendarTheme>& theme, const RefPtr<LinearLayoutProperty>& layoutProps);
    static void SetWeekTextDirection(const TextDirection& dialogDirection, const TextDirection& calendarDirection,
        const RefPtr<FrameNode>& weekNode);
    static DialogEvent GetChangeEvent(const CalendarSettingData& settingData, const RefPtr<FrameNode>& frameNode,
        const std::map<std::string, NG::DialogEvent>& dialogEvent);
    static bool ReportChangeEvent(const RefPtr<FrameNode>& frameNode, const std::string& compName,
        const std::string& eventName, const std::string& eventData);
    static constexpr double deviceHeightLimit = 640.0;
    static void UpdateTextLayoutProperty(const RefPtr<TextLayoutProperty>& textLayoutProperty,
        RefPtr<CalendarTheme>& theme);
    static DeviceOrientation previousOrientation_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_DIALOG_VIEW_H
