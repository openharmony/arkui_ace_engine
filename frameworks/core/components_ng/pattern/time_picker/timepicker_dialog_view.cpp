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
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const int32_t MARGIN_HALF = 2;
} // namespace

RefPtr<FrameNode> TimePickerDialogView::Show(const DialogProperties& dialogProperties,
    const TimePickerSettingData& settingData, std::map<std::string, PickerTime> timePickerProperty,
    std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto timeNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, timeNodeId, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ViewStackProcessor::GetInstance()->Push(timePickerNode);
    auto context = timePickerNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto dialogTheme = themeManager->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, nullptr);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);

    uint32_t showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());

    auto hasHourNode = timePickerRowPattern->HasHourNode();
    auto hasMinuteNode = timePickerRowPattern->HasMinuteNode();

    auto hourId = timePickerRowPattern->GetHourId();
    auto minuteId = timePickerRowPattern->GetMinuteId();

    auto hourColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, hourId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    CHECK_NULL_RETURN(hourColumnNode, nullptr);
    if (!hasHourNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(hourColumnNode);
        }
        hourColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(hourColumnNode);
    }

    auto minuteColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, minuteId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
    CHECK_NULL_RETURN(minuteColumnNode, nullptr);
    if (!hasMinuteNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
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
    if (timePickerProperty.find("selected") != timePickerProperty.end()) {
        auto selectedTime = timePickerProperty["selected"];
        SetSelectedTime(timePickerRowPattern, selectedTime);
        SetDialogTitleDate(timePickerRowPattern, settingData.dialogTitleDate);
    }
    SetHour24(timePickerRowPattern, settingData.isUseMilitaryTime);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(timePickerNode, std::move(changeEvent));
    auto contentRow = CreateButtonNode(timePickerNode, timePickerNode, dialogEvent, std::move(dialogCancelEvent));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto buttonTitleNode = CreateTitleButtonNode(timePickerNode);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);
    ViewStackProcessor::GetInstance()->Finish();

    auto timePickerLayoutProperty = timePickerNode->GetLayoutProperty();
    CHECK_NULL_RETURN(timePickerLayoutProperty, nullptr);
    timePickerLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(NG::CalcLength(Dimension(1.0,
        DimensionUnit::PERCENT)), std::nullopt));

    buttonTitleNode->MountToParent(contentColumn);
    timePickerNode->MountToParent(contentColumn);

    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto event = [dialogNode](const GestureEvent& /* info */) {
        auto pipeline = PipelineContext::GetCurrentContext();
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->CloseDialog(dialogNode);
    };
    for (const auto& child : contentRow->GetChildren()) {
        auto firstChild = AceType::DynamicCast<FrameNode>(child);
        auto gesturHub = firstChild->GetOrCreateGestureEventHub();
        auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(event);
        gesturHub->AddClickEvent(onClick);
    }
    contentRow->AddChild(CreateDividerNode(timePickerNode), 1);
    contentRow->MountToParent(contentColumn);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

RefPtr<FrameNode> TimePickerDialogView::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> TimePickerDialogView::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> TimePickerDialogView::CreateDividerNode(const RefPtr<FrameNode>& dateNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerPattern = dateNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, pickerPattern->GetDividerId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_RETURN(dividerRenderContext, nullptr);
    dividerRenderContext->UpdateBackgroundColor(dialogTheme->GetDividerColor());

    MarginProperty margin;
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    dividerNode->GetLayoutProperty()->UpdateMargin(margin);
    dividerNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));

    return dividerNode;
}

RefPtr<FrameNode> TimePickerDialogView::CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto pickerPattern = dateNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    auto buttonTitleNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textTitleNodeId = pickerPattern->GetTitleId();
    auto textTitleNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textTitleNodeId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textTitleNode, nullptr);
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent("");
    textLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    auto titleNodeRenderContext = textTitleNode->GetRenderContext();
    titleNodeRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    textLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);

    textLayoutProperty->UpdateTextColor(pickerTheme->GetTitleStyle().GetTextColor());
    textLayoutProperty->UpdateFontSize(pickerTheme->GetTitleStyle().GetFontSize());
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetTitleStyle().GetFontWeight());
    textLayoutProperty->UpdateTextOverflow(pickerTheme->GetTitleStyle().GetTextOverflow());
    textLayoutProperty->UpdateMaxLines(pickerTheme->GetTitleStyle().GetMaxLines());
    auto buttonTitleRenderContext = buttonTitleNode->GetRenderContext();
    CHECK_NULL_RETURN(buttonTitleRenderContext, nullptr);
    buttonTitleRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    MarginProperty margin;
    margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
    margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
    margin.top = CalcLength(dialogTheme->GetDividerHeight() / MARGIN_HALF);
    margin.bottom = CalcLength(dialogTheme->GetDividerHeight() / MARGIN_HALF);
    buttonTitleNode->GetLayoutProperty()->UpdateMargin(margin);
    textTitleNode->MountToParent(buttonTitleNode);
    return buttonTitleNode;
}

RefPtr<FrameNode> TimePickerDialogView::CreateButtonNode(const RefPtr<FrameNode>& frameNode,
    const RefPtr<FrameNode>& timePickerNode,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto acceptEvent = dialogEvent["acceptId"];
    auto cancelEvent = dialogCancelEvent["cancelId"];
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    CHECK_NULL_RETURN(contentRow, nullptr);
    auto layoutProps = contentRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    auto buttonCancelNode = CreateCancelNode(cancelEvent, timePickerNode);
    auto buttonConfirmNode = CreateConfirmNode(frameNode, timePickerNode, acceptEvent);
    buttonCancelNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);
    return contentRow;
}

RefPtr<FrameNode> TimePickerDialogView::CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& timePickerNode,
    DialogEvent& acceptEvent)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();

    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(buttonConfirmNode, nullptr);
    CHECK_NULL_RETURN(textConfirmNode, nullptr);
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    auto columnPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    columnPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonConfirmEventHub = buttonConfirmNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonConfirmEventHub, nullptr);
    buttonConfirmEventHub->SetStateEffect(true);

    auto buttonConfirmLayoutProperty = buttonConfirmNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    buttonConfirmLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonConfirmLayoutProperty->UpdateFlexShrink(1.0);
    buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    auto buttonConfirmRenderContext = buttonConfirmNode->GetRenderContext();
    buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);

    MarginProperty margin;
    margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    buttonConfirmNode->GetLayoutProperty()->UpdateMargin(margin);

    textConfirmNode->MountToParent(buttonConfirmNode);
    auto eventConfirmHub = buttonConfirmNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    CHECK_NULL_RETURN(dateNode, nullptr);
    SetDialogAcceptEvent(dateNode, std::move(acceptEvent));
    auto clickCallback = [dateNode](const GestureEvent& /* info */) {
        auto pickerPattern = dateNode->GetPattern<TimePickerRowPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto str = pickerPattern->GetSelectedObject(true);
        auto timePickerEventHub = pickerPattern->GetEventHub<TimePickerEventHub>();
        CHECK_NULL_VOID(timePickerEventHub);
        timePickerEventHub->FireDialogAcceptEvent(str);
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    buttonConfirmNode->MarkModifyDone();
    return buttonConfirmNode;
}

RefPtr<FrameNode> TimePickerDialogView::CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
    const RefPtr<FrameNode>& timePickerNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textCancelLayoutProperty, nullptr);
    textCancelLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    textCancelLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textCancelLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textCancelLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    auto columnPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    columnPattern->SetCancelNode(buttonCancelNode);
    textCancelNode->MountToParent(buttonCancelNode);
    auto eventCancelHub = buttonCancelNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventCancelHub, nullptr);
    eventCancelHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(cancelEvent)));

    auto buttonCancelEventHub = buttonCancelNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonCancelEventHub, nullptr);
    buttonCancelEventHub->SetStateEffect(true);

    MarginProperty margin;
    margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
    buttonCancelNode->GetLayoutProperty()->UpdateMargin(margin);

    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonCancelLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    buttonCancelLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonCancelLayoutProperty->UpdateFlexShrink(1.0);
    buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));

    auto buttonCancelRenderContext = buttonCancelNode->GetRenderContext();
    buttonCancelRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonCancelNode->MarkModifyDone();
    return buttonCancelNode;
}

void TimePickerDialogView::SetSelectedTime(
    const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerTime& value)
{
    timePickerRowPattern->SetSelectedTime(value);
}

void TimePickerDialogView::SetDialogTitleDate(
    const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerDate& value)
{
    timePickerRowPattern->SetDialogTitleDate(value);
}

void TimePickerDialogView::SetHour24(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, bool isUseMilitaryTime)
{
    auto timePickerLayoutProperty = timePickerRowPattern->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(timePickerLayoutProperty);
    timePickerLayoutProperty->UpdateIsUseMilitaryTime(isUseMilitaryTime);
}

void TimePickerDialogView::SetDialogChange(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogChange(std::move(onChange));
}

void TimePickerDialogView::SetDialogAcceptEvent(const RefPtr<FrameNode>& frameNode, DialogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDialogAcceptEvent(std::move(onChange));
}

void TimePickerDialogView::SetTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const PickerTextProperties& properties)
{
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);

    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, DisappearFontSize, properties.disappearTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontSize, disappearStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearColor,
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearWeight,
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, FontSize, properties.normalTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, normalStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Color,
        properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, Weight,
        properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, SelectedFontSize, properties.selectedTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontSize, selectedStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedColor,
        properties.selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedWeight,
        properties.selectedTextStyle_.fontWeight.value_or(selectedStyle.GetFontWeight()));
}
} // namespace OHOS::Ace::NG
