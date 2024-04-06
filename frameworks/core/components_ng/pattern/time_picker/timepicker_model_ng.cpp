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
constexpr uint8_t PIXEL_ROUND = 18;
} // namespace
void TimePickerModelNG::CreateTimePicker(RefPtr<PickerTheme> pickerTheme, bool hasSecond)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TIME_PICKER_ETS_TAG, nodeId);
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
        auto columnBlendNode = CreateColumnNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackHourNode);
        hourColumnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackHourNode);
        auto layoutProperty = stackHourNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackHourNode->MountToParent(timePickerNode);
        hourColumnNode->GetLayoutProperty<LayoutProperty>()->UpdatePixelRound(PIXEL_ROUND);
    }
    if (!hasMinuteNode) {
        auto stackMinuteNode = CreateStackNode();
        auto columnBlendNode = CreateColumnNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackMinuteNode);
        minuteColumnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackMinuteNode);
        auto layoutProperty = stackMinuteNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackMinuteNode->MountToParent(timePickerNode);
        minuteColumnNode->GetLayoutProperty<LayoutProperty>()->UpdatePixelRound(PIXEL_ROUND);
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

RefPtr<FrameNode> TimePickerModelNG::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> TimePickerModelNG::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> TimePickerModelNG::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TIME_PICKER_ETS_TAG, nodeId);
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });

    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, timePickerNode);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, timePickerNode);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, timePickerNode);
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetPickerTag(true);
    auto hasHourNode = timePickerRowPattern->HasHourNode();
    auto hasMinuteNode = timePickerRowPattern->HasMinuteNode();
    auto hourId = timePickerRowPattern->GetHourId();
    auto minuteId = timePickerRowPattern->GetMinuteId();
    SetDefaultAttributes(timePickerNode, pickerTheme);

    auto hourColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, hourId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    CHECK_NULL_RETURN(hourColumnNode, timePickerNode);
    if (!hasHourNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, timePickerNode);
            textNode->MountToParent(hourColumnNode);
        }
        hourColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(hourColumnNode);
    }

    auto minuteColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, minuteId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    CHECK_NULL_RETURN(minuteColumnNode, timePickerNode);
    if (!hasMinuteNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, timePickerNode);
            textNode->MountToParent(minuteColumnNode);
        }
        minuteColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(minuteColumnNode);
    }
    if (!hasHourNode) {
        auto stackHourNode = CreateStackNode();
        auto columnBlendNode = CreateColumnNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackHourNode);
        hourColumnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackHourNode);
        auto layoutProperty = stackHourNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackHourNode->MountToParent(timePickerNode);
        hourColumnNode->GetLayoutProperty<LayoutProperty>()->UpdatePixelRound(PIXEL_ROUND);
    }
    if (!hasMinuteNode) {
        auto stackMinuteNode = CreateStackNode();
        auto columnBlendNode = CreateColumnNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackMinuteNode);
        minuteColumnNode->MountToParent(columnBlendNode);
        columnBlendNode->MountToParent(stackMinuteNode);
        auto layoutProperty = stackMinuteNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackMinuteNode->MountToParent(timePickerNode);
        minuteColumnNode->GetLayoutProperty<LayoutProperty>()->UpdatePixelRound(PIXEL_ROUND);
    }
    timePickerRowPattern->SetHasSecond(false);
    return timePickerNode;
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
    timePickerRowPattern->SetHour24(isUseMilitaryTime);
}

void TimePickerModelNG::SetWheelModeEnabled(bool wheelModeEnabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Loop, wheelModeEnabled);
}

void TimePickerModelNG::SetOnChange(TimeChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void TimePickerModelNG::SetOnChange(FrameNode* frameNode, TimeChangeEvent&& onChange)
{
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
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange,
    TimePickerDialogEvent& timePickerDialogEvent)
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
    CHECK_NULL_VOID(theme);
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
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogLifeCycleEvent["didAppearId"] = timePickerDialogEvent.onDidAppear;
    dialogLifeCycleEvent["didDisappearId"] = timePickerDialogEvent.onDidDisappear;
    dialogLifeCycleEvent["willAppearId"] = timePickerDialogEvent.onWillAppear;
    dialogLifeCycleEvent["willDisappearId"] = timePickerDialogEvent.onWillDisappear;
    DialogProperties properties;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
            properties.alignment = DialogAlignment::BOTTOM;
        } else {
            properties.alignment = DialogAlignment::CENTER;
        }
    }
    if (pickerDialog.alignment.has_value()) {
        properties.alignment = pickerDialog.alignment.value();
    }

    if (pickerDialog.backgroundColor.has_value()) {
        properties.backgroundColor = pickerDialog.backgroundColor.value();
    }
    if (pickerDialog.backgroundBlurStyle.has_value()) {
        properties.backgroundBlurStyle = pickerDialog.backgroundBlurStyle.value();
    }
    if (pickerDialog.shadow.has_value()) {
        properties.shadow = pickerDialog.shadow.value();
    }
    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    }
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
        [properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTimeDialog(
                properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent);
        },
        TaskExecutor::TaskType::UI);
}

void TimePickerModelNG::SetSelectedTime(FrameNode* frameNode, const PickerTime& value)
{
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->SetSelectedTime(value);
}

void TimePickerModelNG::SetDisappearTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto disappearStyle = theme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, DisappearFontSize, value.fontSize.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearColor,
        value.textColor.value_or(disappearStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearWeight,
        value.fontWeight.value_or(disappearStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontFamily,
        value.fontFamily.value_or(disappearStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontStyle,
        value.fontStyle.value_or(disappearStyle.GetFontStyle()), frameNode);
}
void TimePickerModelNG::SetNormalTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto normalStyle = theme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, value.fontSize.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, normalStyle.GetFontSize(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()), frameNode);
}
void TimePickerModelNG::SetSelectedTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto selectedStyle = theme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, SelectedFontSize, value.fontSize.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedColor,
        value.textColor.value_or(selectedStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedWeight,
        value.fontWeight.value_or(selectedStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedFontFamily,
        value.fontFamily.value_or(selectedStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()), frameNode);
}

void TimePickerModelNG::SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme)
{
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedColor, selectedStyle.GetTextColor(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedWeight, selectedStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedFontFamily, selectedStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, SelectedFontStyle, selectedStyle.GetFontStyle(), frameNode);

    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearColor, disappearStyle.GetTextColor(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearWeight, disappearStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontFamily, disappearStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, DisappearFontStyle, disappearStyle.GetFontStyle(), frameNode);

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, normalStyle.GetFontSize(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Color, normalStyle.GetTextColor(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Weight, normalStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontFamily, normalStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontStyle, normalStyle.GetFontStyle(), frameNode);
}

void TimePickerModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->SetBackgroundColor(color);
}

void TimePickerModelNG::SetHour24(FrameNode* frameNode, bool isUseMilitaryTime)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TimePickerLayoutProperty, IsUseMilitaryTime, isUseMilitaryTime, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->ClearOptionsHour();
    timePickerRowPattern->SetHour24(isUseMilitaryTime);
}

PickerTextStyle TimePickerModelNG::getDisappearTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetDisappearOptionStyle();
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, DisappearFontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, DisappearColor, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, DisappearWeight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TimePickerLayoutProperty, DisappearFontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TimePickerLayoutProperty, DisappearFontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

PickerTextStyle TimePickerModelNG::getNormalTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetOptionStyle(false, false);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, FontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, Color, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, Weight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TimePickerLayoutProperty, FontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TimePickerLayoutProperty, FontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

PickerTextStyle TimePickerModelNG::getSelectedTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetOptionStyle(true, false);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, SelectedFontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, SelectedColor, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        TimePickerLayoutProperty, SelectedWeight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TimePickerLayoutProperty, SelectedFontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(TimePickerLayoutProperty, SelectedFontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

PickerTime TimePickerModelNG::getTimepickerSelected(FrameNode* frameNode)
{
    PickerTime pickerTime;
    CHECK_NULL_RETURN(frameNode, pickerTime);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    return timePickerRowPattern->GetSelectedTime();
}

uint32_t TimePickerModelNG::getTimepickerBackgroundColor(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, 0);
    return timePickerRowPattern->GetBackgroundColor().GetValue();
}

int32_t TimePickerModelNG::getTimepickerUseMilitaryTime(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetLayoutProperty<TimePickerLayoutProperty>()->GetIsUseMilitaryTimeValue(false);
}

} // namespace OHOS::Ace::NG
