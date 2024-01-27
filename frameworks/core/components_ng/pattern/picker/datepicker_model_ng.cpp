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
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"

#include <utility>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t BUFFER_NODE_NUMBER = 2;
} // namespace
void DatePickerModelNG::CreateDatePicker(RefPtr<PickerTheme> pickerTheme)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DATE_PICKER_ETS_TAG, nodeId);
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetPickerTag(true);
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();

    auto yearId = datePickerPattern->GetYearId();
    auto monthId = datePickerPattern->GetMonthId();
    auto dayId = datePickerPattern->GetDayId();

    CHECK_NULL_VOID(pickerTheme);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);

    auto yearColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, yearId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_VOID(yearColumnNode);
    if (!hasYearNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(yearColumnNode);
        }
        yearColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(yearColumnNode);
    }

    auto monthColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, monthId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_VOID(monthColumnNode);
    if (!hasMonthNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(monthColumnNode);
        }
        monthColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(monthColumnNode);
    }

    auto dayColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, dayId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_VOID(dayColumnNode);
    if (!hasDayNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(dayColumnNode);
        }
        dayColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(dayColumnNode);
    }

    if (!hasYearNode) {
        auto stackYearNode = CreateStackNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackYearNode);
        yearColumnNode->MountToParent(stackYearNode);
        auto layoutProperty = stackYearNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackYearNode->MountToParent(dateNode);
    }
    if (!hasMonthNode) {
        auto stackMonthNode = CreateStackNode();
        auto buttonMonthNode = CreateButtonNode();
        buttonMonthNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
        buttonMonthNode->MountToParent(stackMonthNode);
        monthColumnNode->MountToParent(stackMonthNode);
        auto layoutProperty = stackMonthNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackMonthNode->MountToParent(dateNode);
    }
    if (!hasDayNode) {
        auto stackDayNode = CreateStackNode();
        auto buttonDayNode = CreateButtonNode();
        buttonDayNode->GetRenderContext()->UpdateBackgroundColor(Color::GRAY);
        buttonDayNode->MountToParent(stackDayNode);
        dayColumnNode->MountToParent(stackDayNode);
        auto layoutProperty = stackDayNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackDayNode->MountToParent(dateNode);
    }
    stack->Push(dateNode);
}

RefPtr<FrameNode> DatePickerModelNG::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> DatePickerModelNG::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

void DatePickerModelNG::SetShowLunar(bool lunar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Lunar, lunar);
}

void DatePickerModelNG::SetStartDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetStartDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, StartDate, datePickerPattern->GetStartDateLunar());
}

void DatePickerModelNG::SetEndDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEndDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, EndDate, datePickerPattern->GetEndDateLunar());
}

void DatePickerModelNG::SetSelectedDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetSelectDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedDate, datePickerPattern->GetSelectDate());
}

void DatePickerModelNG::SetOnChange(DateChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void DatePickerModelNG::SetOnDateChange(DateChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}

void DatePickerModelNG::SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto disappearStyle = theme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearColor, value.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearWeight, value.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontFamily, value.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontStyle, value.fontStyle.value_or(disappearStyle.GetFontStyle()));
}

void DatePickerModelNG::SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto normalStyle = theme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize, normalStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()));
}

void DatePickerModelNG::SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto selectedStyle = theme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontSize, value.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedColor, value.textColor.value_or(selectedStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedWeight, value.fontWeight.value_or(selectedStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontFamily, value.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void DatePickerModelNG::SetBackgroundColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetBackgroundColor(color);
}

void DatePickerModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetBackgroundColor(color);
}

void DatePickerModelNG::SetStartDate(FrameNode* frameNode, const PickerDate& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetStartDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, StartDate, datePickerPattern->GetStartDateLunar());
}

void DatePickerModelNG::SetEndDate(FrameNode* frameNode, const PickerDate& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEndDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, EndDate, datePickerPattern->GetEndDateLunar());
}

void DatePickerModelNG::SetSelectedDate(FrameNode* frameNode, const PickerDate& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetSelectDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedDate, datePickerPattern->GetSelectDate());
}

void DatePickerModelNG::SetChangeEvent(DateChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void DatePickerDialogModelNG::SetDatePickerDialogShow(PickerDialogInfo& pickerDialog,
    NG::DatePickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange,
    std::function<void(const std::string&)>&& onDateAccept, std::function<void(const std::string&)>&& onDateChange,
    DatePickerType pickerType)
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
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogEvent["changeId"] = onChange;
    dialogEvent["acceptId"] = onAccept;
    dialogEvent["dateChangeId"] = onDateChange;
    dialogEvent["dateAcceptId"] = onDateAccept;
    auto func = [onCancel](const GestureEvent& /* info */) {
        if (onCancel) {
            onCancel();
        }
    };
    dialogCancelEvent["cancelId"] = func;
    ButtonInfo buttonInfo;
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

    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    } else {
        if (properties.alignment == DialogAlignment::DEFAULT) {
            if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
                properties.alignment = DialogAlignment::BOTTOM;
                properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
            } else {
                properties.alignment = DialogAlignment::CENTER;
            }
        }
    }
    if (pickerDialog.offset.has_value()) {
        properties.offset = pickerDialog.offset.value();
    }

    properties.maskRect = pickerDialog.maskRect;

    std::map<std::string, PickerDate> datePickerProperty;
    std::map<std::string, PickerTime> timePickerProperty;
    if (pickerDialog.isStartDate == true) {
        settingData.datePickerProperty["start"] = pickerDialog.parseStartDate;
    }
    if (pickerDialog.isEndDate == true) {
        settingData.datePickerProperty["end"] = pickerDialog.parseEndDate;
    }
    if (pickerDialog.isSelectedDate == true) {
        settingData.datePickerProperty["selected"] = pickerDialog.parseSelectedDate;
        settingData.timePickerProperty["selected"] = pickerDialog.pickerTime;
    }
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowDateDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
}

void DatePickerModelNG::SetSelectedTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto selectedStyle = theme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, SelectedFontSize, value.fontSize.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedColor, value.textColor.value_or(selectedStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedWeight,
        value.fontWeight.value_or(selectedStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontFamily,
        value.fontFamily.value_or(selectedStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontStyle,
        value.fontStyle.value_or(selectedStyle.GetFontStyle()), frameNode);
}

void DatePickerModelNG::SetNormalTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto normalStyle = theme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize, value.fontSize.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize, normalStyle.GetFontSize(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()), frameNode);
}

void DatePickerModelNG::SetDisappearTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    auto disappearStyle = theme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, DisappearFontSize, value.fontSize.value(), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearColor,
        value.textColor.value_or(disappearStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearWeight,
        value.fontWeight.value_or(disappearStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontFamily,
        value.fontFamily.value_or(disappearStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontStyle,
        value.fontStyle.value_or(disappearStyle.GetFontStyle()), frameNode);
}

void DatePickerModelNG::SetShowLunar(FrameNode* frameNode, bool lunar)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Lunar, lunar, frameNode);
}
} // namespace OHOS::Ace::NG
