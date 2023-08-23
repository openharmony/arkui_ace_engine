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

#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"

#include <cstdint>

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BUFFER_NODE_NUMBER = 2;
} // namespace
void TimePickerModelNG::CreateTimePicker(RefPtr<PickerTheme> pickerTheme, bool hasSecond)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });

    CHECK_NULL_VOID(pickerTheme);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetPickerTag(true);
    auto hasHourNode = timePickerRowPattern->HasHourNode();
    auto hasMinuteNode = timePickerRowPattern->HasMinuteNode();
    auto hourId = timePickerRowPattern->GetHourId();
    auto minuteId = timePickerRowPattern->GetMinuteId();

    auto hourColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, hourId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    CHECK_NULL_VOID(hourColumnNode);
    if (!hasHourNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(hourColumnNode);
        }
        hourColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(hourColumnNode);
    }

    auto minuteColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, minuteId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    CHECK_NULL_VOID(minuteColumnNode);
    if (!hasMinuteNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(minuteColumnNode);
        }
        minuteColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(minuteColumnNode);
    }

    if (!hasHourNode) {
        auto stackHourNode = CreateStackNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackHourNode);
        hourColumnNode->MountToParent(stackHourNode);
        auto layoutProperty = stackHourNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackHourNode->MountToParent(timePickerNode);
    }
    if (!hasMinuteNode) {
        auto stackMinuteNode = CreateStackNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackMinuteNode);
        minuteColumnNode->MountToParent(stackMinuteNode);
        auto layoutProperty = stackMinuteNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackMinuteNode->MountToParent(timePickerNode);
    }
    timePickerRowPattern->SetHasSecond(hasSecond);
    stack->Push(timePickerNode);
}

RefPtr<FrameNode> TimePickerModelNG::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> TimePickerModelNG::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

void TimePickerModelNG::SetSelectedTime(const PickerTime& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->SetSelectedTime(value);
}

void TimePickerModelNG::SetHour24(bool isUseMilitaryTime)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, IsUseMilitaryTime, isUseMilitaryTime);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->ClearOptionsHour();
}

void TimePickerModelNG::SetWheelModeEnabled(bool wheelModeEnabled)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->SetWheelModeEnabled(wheelModeEnabled);
}

void TimePickerModelNG::SetOnChange(TimeChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TimePickerModelNG::SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto disappearStyle = theme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearColor, value.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearWeight, value.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontFamily, value.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontStyle, value.fontStyle.value_or(disappearStyle.GetFontStyle()));
}

void TimePickerModelNG::SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto normalStyle = theme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, normalStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()));
}

void TimePickerModelNG::SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto selectedStyle = theme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedColor, value.textColor.value_or(selectedStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedWeight, value.fontWeight.value_or(selectedStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedFontFamily, value.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void TimePickerModelNG::SetBackgroundColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->SetBackgroundColor(color);
}

void TimePickerModelNG::SetChangeEvent(TimeChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void TimePickerDialogModelNG::SetTimePickerDialogShow(PickerDialogInfo& pickerDialog,
    NG::TimePickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange)
{
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return;
    }
    auto executor = pipelineContext->GetTaskExecutor();
    if (!executor) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    if (!theme) {
        LOGE("DialogTheme is null");
        return;
    }
    ButtonInfo buttonInfo;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    dialogEvent["changeId"] = onChange;
    dialogEvent["acceptId"] = onAccept;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    auto func = [onCancel](const GestureEvent& /* info */) {
        if (onCancel) {
            onCancel();
        }
    };
    dialogCancelEvent["cancelId"] = func;
    DialogProperties properties;
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    if (pickerDialog.alignment.has_value()) {
        properties.alignment = pickerDialog.alignment.value();
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    if (pickerDialog.offset.has_value()) {
        properties.offset = pickerDialog.offset.value();
    }

    properties.maskRect = pickerDialog.maskRect;

    std::map<std::string, PickerTime> timePickerProperty;
    if (pickerDialog.isSelectedTime == true) {
        timePickerProperty["selected"] = pickerDialog.pickerTime;
    }
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTimeDialog(properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG
