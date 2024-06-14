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
const int32_t TITLE_ROWS_TWO = 2;
const int32_t DIVIDER_ROWS_THREE = 3;
const int32_t MARGIN_HALF = 2;
const int32_t BUFFER_NODE_NUMBER = 2;
constexpr Dimension PICKER_DIALOG_MARGIN_FORM_EDGE = 24.0_vp;
constexpr uint8_t PIXEL_ROUND = 18;
constexpr size_t ACCEPT_BUTTON_INDEX = 0;
constexpr size_t CANCEL_BUTTON_INDEX = 1;
} // namespace
bool TimePickerDialogView::switchFlag_ = false;

RefPtr<FrameNode> TimePickerDialogView::Show(const DialogProperties& dialogProperties,
    const TimePickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    if ((NeedadaptForAging() && (!settingData.isUseMilitaryTime)
        && (!GetIsUserSetTextProperties(settingData.properties)))) {
        return ShowForAging(
            dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    }

    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto timeNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TIME_PICKER_ETS_TAG, timeNodeId);
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

    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto timePickerLayout = timePickerNode->GetLayoutProperty<TimePickerLayoutProperty>();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ZeroPrefixType hourOptions = settingData.dateTimeOptions.hourType;
        ZeroPrefixType minuteOptions = settingData.dateTimeOptions.minuteType;
        if ((timePickerRowPattern->GetPrefixHour() != hourOptions) ||
            (timePickerRowPattern->GetPrefixMinute() != minuteOptions)) {
            timePickerRowPattern->SetDateTimeOptionUpdate(true);
        }
        timePickerRowPattern->SetPrefixHour(hourOptions);
        timePickerRowPattern->SetPrefixMinute(minuteOptions);
        timePickerLayout->UpdatePrefixHour(static_cast<int32_t>(hourOptions));
        timePickerLayout->UpdatePrefixMinute(static_cast<int32_t>(minuteOptions));
    }

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
    auto it = timePickerProperty.find("selected");
    if (it != timePickerProperty.end()) {
        auto selectedTime = it->second;
        SetSelectedTime(timePickerRowPattern, selectedTime);
        SetDialogTitleDate(timePickerRowPattern, settingData.dialogTitleDate);
    }
    SetHour24(timePickerRowPattern, settingData.isUseMilitaryTime);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(timePickerNode, std::move(changeEvent));
    auto contentRow =
        CreateButtonNode(timePickerNode, timePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto buttonTitleNode = CreateTitleButtonNode(timePickerNode);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);
    ViewStackProcessor::GetInstance()->Finish();

    auto timePickerLayoutProperty = timePickerNode->GetLayoutProperty();
    CHECK_NULL_RETURN(timePickerLayoutProperty, nullptr);

    MarginProperty margin;
    margin.left = CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
    margin.right = CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
    timePickerLayoutProperty->UpdateMargin(margin);

    buttonTitleNode->MountToParent(contentColumn);
    timePickerNode->MountToParent(contentColumn);

    contentRow->SetNeedCallChildrenUpdate(false);
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    timePickerPattern->SetContentRowNode(contentRow);
    timePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    auto buttonTitlePattern = buttonTitleNode->GetPattern<ButtonPattern>();
    CHECK_NULL_RETURN(buttonTitlePattern, nullptr);
    buttonTitlePattern->SetSkipColorConfigurationUpdate();

    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto event = [weak = WeakPtr<FrameNode>(dialogNode)](const GestureEvent& /* info */) {
        auto dialogNode = weak.Upgrade();
        CHECK_NULL_VOID(dialogNode);
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

RefPtr<FrameNode> TimePickerDialogView::ShowForAging(const DialogProperties& dialogProperties,
    const TimePickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto timeNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TIME_PICKER_ETS_TAG, timeNodeId);
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

    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    auto timePickerLayout = timePickerNode->GetLayoutProperty<TimePickerLayoutProperty>();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ZeroPrefixType hourOptions = settingData.dateTimeOptions.hourType;
        ZeroPrefixType minuteOptions = settingData.dateTimeOptions.minuteType;
        if ((timePickerRowPattern->GetPrefixHour() != hourOptions) ||
            (timePickerRowPattern->GetPrefixMinute() != minuteOptions)) {
            timePickerRowPattern->SetDateTimeOptionUpdate(true);
        }
        timePickerRowPattern->SetPrefixHour(hourOptions);
        timePickerRowPattern->SetPrefixMinute(minuteOptions);
        timePickerLayout->UpdatePrefixHour(static_cast<int32_t>(hourOptions));
        timePickerLayout->UpdatePrefixMinute(static_cast<int32_t>(minuteOptions));
    }

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
    auto it = timePickerProperty.find("selected");
    if (it != timePickerProperty.end()) {
        auto selectedTime = it->second;
        SetSelectedTime(timePickerRowPattern, selectedTime);
        SetDialogTitleDate(timePickerRowPattern, settingData.dialogTitleDate);
    }
    SetHour24(timePickerRowPattern, settingData.isUseMilitaryTime);
    SetTextProperties(pickerTheme, settingData.properties);
    auto changeEvent = dialogEvent["changeId"];
    SetDialogChange(timePickerNode, std::move(changeEvent));

    auto contentRow = CreateButtonNodeForAging(
        timePickerNode, timePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto buttonTitleNode = CreateTitleButtonNode(timePickerNode);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);
    ViewStackProcessor::GetInstance()->Finish();

    auto timePickerLayoutProperty = timePickerNode->GetLayoutProperty();
    CHECK_NULL_RETURN(timePickerLayoutProperty, nullptr);

    MarginProperty margin;
    margin.left = CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
    margin.right = CalcLength(PICKER_DIALOG_MARGIN_FORM_EDGE);
    timePickerLayoutProperty->UpdateMargin(margin);

    buttonTitleNode->MountToParent(contentColumn);
    timePickerNode->MountToParent(contentColumn);

    contentRow->SetNeedCallChildrenUpdate(false);
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    timePickerPattern->SetContentRowNode(contentRow);
    timePickerPattern->SetbuttonTitleNode(buttonTitleNode);
    auto buttonTitlePattern = buttonTitleNode->GetPattern<ButtonPattern>();
    CHECK_NULL_RETURN(buttonTitlePattern, nullptr);
    buttonTitlePattern->SetSkipColorConfigurationUpdate();
    auto hourNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(1));
    CHECK_NULL_RETURN(hourNode, nullptr);
    hourNode->SetActive(false);
    auto hourLayoutProperty = hourNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(hourLayoutProperty, nullptr);
    hourLayoutProperty->UpdateVisibility(VisibleType::GONE);

    auto minuteNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(2));
    CHECK_NULL_RETURN(minuteNode, nullptr);
    minuteNode->SetActive(false);
    auto minuteLayoutProperty = minuteNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(minuteLayoutProperty, nullptr);
    minuteLayoutProperty->UpdateVisibility(VisibleType::GONE);

    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto event = [weak = WeakPtr<FrameNode>(dialogNode)](const GestureEvent& /* info */) {
        auto dialogNode = weak.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        auto pipeline = PipelineContext::GetCurrentContext();
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->CloseDialog(dialogNode);
    };

    auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(event);
    auto cancelButtonNode = AceType::DynamicCast<FrameNode>(contentRow->GetChildAtIndex(0));
    CHECK_NULL_RETURN(cancelButtonNode, nullptr);
    auto cancelButtonGesturHub = cancelButtonNode->GetOrCreateGestureEventHub();
    cancelButtonGesturHub->AddClickEvent(onClick);
    auto confirmButtonNode = AceType::DynamicCast<FrameNode>(contentRow->GetLastChild());
    CHECK_NULL_RETURN(confirmButtonNode, nullptr);
    auto confirmButtonGesturHub = confirmButtonNode->GetOrCreateGestureEventHub();
    confirmButtonGesturHub->AddClickEvent(onClick);
    contentRow->MountToParent(contentColumn);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

RefPtr<FrameNode> TimePickerDialogView::CreateNextPrevButtonNode(std::function<void()>& timePickerSwitchEvent,
    const RefPtr<FrameNode>& timeNode, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();

    auto nextPrevButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(nextPrevButtonNode, nullptr);
    auto textNextPrevNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNextPrevNode, nullptr);
    auto textLayoutProperty = textNextPrevNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.next"));
    textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    auto nextPrevButtonPattern = nextPrevButtonNode->GetPattern<ButtonPattern>();

    MarginProperty margin;
    margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
    margin.top = CalcLength(dialogTheme->GetDividerHeight());
    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());

    auto buttonNextPrevLayoutProperty = nextPrevButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonNextPrevLayoutProperty->UpdateMargin(margin);
    buttonNextPrevLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    buttonNextPrevLayoutProperty->UpdateFlexShrink(1.0);
    buttonNextPrevLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonNextPrevLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    auto buttonNextPrevRenderContext = nextPrevButtonNode->GetRenderContext();
    buttonNextPrevRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateConfirmButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
    UpdateButtonDefaultFocus(buttonInfos, nextPrevButtonNode, true);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonNextPrevLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, nullptr);
        buttonNextPrevLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }

    textNextPrevNode->MountToParent(nextPrevButtonNode);
    auto eventNextPrevmHub = nextPrevButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventNextPrevmHub, nullptr);
    CHECK_NULL_RETURN(timeNode, nullptr);
    auto onClickCallback = [weak = WeakPtr<FrameNode>(timeNode), textWeak = WeakPtr<FrameNode>(textNextPrevNode),
                            nextPrevButtonNodeWeak = WeakPtr<FrameNode>(nextPrevButtonNode),
                            dialogThemeWeak = WeakPtr<DialogTheme>(dialogTheme),
                            func = std::move(timePickerSwitchEvent)](const GestureEvent& /* info */) {
        auto timeNode = weak.Upgrade();
        CHECK_NULL_VOID(timeNode);
        auto textNode = textWeak.Upgrade();
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto pickerPattern = timeNode->GetPattern<TimePickerRowPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto timePickerEventHub = pickerPattern->GetEventHub<TimePickerEventHub>();
        CHECK_NULL_VOID(timePickerEventHub);
        auto nextPrevButtonNode = nextPrevButtonNodeWeak.Upgrade();
        CHECK_NULL_VOID(nextPrevButtonNode);
        auto dialogTheme = dialogThemeWeak.Upgrade();
        CHECK_NULL_VOID(dialogTheme);
        auto buttonNextPrevLayoutProperty
                                = nextPrevButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(buttonNextPrevLayoutProperty);
        timePickerEventHub->FireDialogAcceptEvent(pickerPattern->GetSelectedObject(true));
        func();
        if (textLayoutProperty->GetContent() == Localization::GetInstance()->GetEntryLetters("common.next")) {
            UpdateCancelButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
            textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.prev"));
        } else {
            UpdateConfirmButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
            textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.next"));
        }
        timeNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    };
    eventNextPrevmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(onClickCallback));
    nextPrevButtonNode->MarkModifyDone();
    return nextPrevButtonNode;
}

RefPtr<FrameNode> TimePickerDialogView::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> TimePickerDialogView::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> TimePickerDialogView::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> TimePickerDialogView::CreateDividerNode(const RefPtr<FrameNode>& dateNode, bool isCreateDivider)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto pickerPattern = dateNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    int32_t dividerNodeId = 0;
    if (isCreateDivider) {
        dividerNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    } else {
        dividerNodeId = pickerPattern->GetDividerId();
    }
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, dividerNodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    CHECK_NULL_RETURN(dividerNode, nullptr);

    auto dividerPaintProps = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(dividerPaintProps, nullptr);
    dividerPaintProps->UpdateDividerColor(dialogTheme->GetDividerColor());

    auto dividerLayoutProps = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_RETURN(dividerLayoutProps, nullptr);
    dividerLayoutProps->UpdateVertical(true);

    dividerLayoutProps->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        MarginProperty margin;
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        dividerLayoutProps->UpdateMargin(margin);
        dividerLayoutProps->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(dialogTheme->GetDividerWidth()), CalcLength(dialogTheme->GetDividerHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        auto dividerWrapper = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_RETURN(dividerWrapper, nullptr);
        auto layoutProps = dividerWrapper->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        layoutProps->UpdateMainAxisAlign(FlexAlign::SPACE_AROUND);
        layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
        layoutProps->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(dialogTheme->GetActionsPadding().Bottom()), CalcLength(buttonTheme->GetHeight())));
        dividerNode->MountToParent(dividerWrapper);
        return dividerWrapper;
    }

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
    textLayoutProperty->UpdateMaxLines(
        NeedadaptForAging() ? TITLE_ROWS_TWO : pickerTheme->GetTitleStyle().GetMaxLines());

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
    const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos,
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
    auto buttonCancelNode = CreateCancelNode(cancelEvent, timePickerNode, buttonInfos);
    auto buttonConfirmNode = CreateConfirmNode(frameNode, timePickerNode, buttonInfos, acceptEvent);
    buttonCancelNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);
    return contentRow;
}

RefPtr<FrameNode> TimePickerDialogView::CreateButtonNodeForAging(const RefPtr<FrameNode>& frameNode,
    const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos,
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

    auto buttonCancelNode = CreateCancelNode(cancelEvent, timePickerNode, buttonInfos);
    CHECK_NULL_RETURN(buttonCancelNode, nullptr);

    auto buttonConfirmNode = CreateConfirmNode(frameNode, timePickerNode, buttonInfos, acceptEvent);
    CHECK_NULL_RETURN(buttonConfirmNode, nullptr);

    auto cancelNextDividerNode = CreateDividerNode(timePickerNode, true);
    CHECK_NULL_RETURN(cancelNextDividerNode, nullptr);
    auto nextConfirmDividerNode = CreateDividerNode(timePickerNode, true);
    CHECK_NULL_RETURN(nextConfirmDividerNode, nullptr);

    auto timePickerSwitchEvent = CreateAndSetTimePickerSwitchEvent(timePickerNode, buttonCancelNode, buttonConfirmNode,
        cancelNextDividerNode, nextConfirmDividerNode);
    auto buttonNextPreNode = CreateNextPrevButtonNode(timePickerSwitchEvent, timePickerNode, buttonInfos);
    CHECK_NULL_RETURN(buttonNextPreNode, nullptr);
    buttonCancelNode->MountToParent(contentRow);
    buttonNextPreNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);
    contentRow->AddChild(cancelNextDividerNode, 1);
    contentRow->AddChild(nextConfirmDividerNode, DIVIDER_ROWS_THREE);

    switchFlag_ = false;
    for (const auto& child : contentRow->GetChildren()) {
        auto firstChild = AceType::DynamicCast<FrameNode>(child);
        firstChild->SetActive(true);
        auto layoutProperty = firstChild->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }

    buttonConfirmNode->SetActive(false);
    auto layoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    nextConfirmDividerNode->SetActive(false);
    auto nextConfirmDividerProperty = nextConfirmDividerNode->GetLayoutProperty<LayoutProperty>();
    nextConfirmDividerProperty->UpdateVisibility(VisibleType::GONE);
    return contentRow;
}

std::function<void()> TimePickerDialogView::CreateAndSetTimePickerSwitchEvent(const RefPtr<FrameNode>& timePickerNode,
    const RefPtr<FrameNode>& buttonCancelNode, const RefPtr<FrameNode>& buttonConfirmNode,
    const RefPtr<FrameNode>& cancelNextDividerNode, const RefPtr<FrameNode>& nextConfirmDividerNode)
{
    auto timePickerSwitchEvent = [weakTimePickerNode = AceType::WeakClaim(AceType::RawPtr(timePickerNode)),
                                     weakbuttonCancelNode = AceType::WeakClaim(AceType::RawPtr(buttonCancelNode)),
                                     weakcancelNextDividerNode =
                                         AceType::WeakClaim(AceType::RawPtr(cancelNextDividerNode)),
                                     weaknextConfirmDividerNode =
                                         AceType::WeakClaim(AceType::RawPtr(nextConfirmDividerNode)),
                                     weakbuttonConfirmNode = AceType::WeakClaim(AceType::RawPtr(buttonConfirmNode))]() {
        auto timePickerNode = weakTimePickerNode.Upgrade();
        CHECK_NULL_VOID(timePickerNode);
        auto buttonCancelNode = weakbuttonCancelNode.Upgrade();
        CHECK_NULL_VOID(buttonCancelNode);
        auto buttonConfirmNode = weakbuttonConfirmNode.Upgrade();
        CHECK_NULL_VOID(buttonConfirmNode);
        auto cancelNextDividerNode = weakcancelNextDividerNode.Upgrade();
        CHECK_NULL_VOID(cancelNextDividerNode);
        auto nextConfirmDividerNode = weaknextConfirmDividerNode.Upgrade();
        CHECK_NULL_VOID(nextConfirmDividerNode);
        SwitchTimePickerPage(timePickerNode, buttonCancelNode, buttonConfirmNode,
            cancelNextDividerNode, nextConfirmDividerNode);
    };

    return timePickerSwitchEvent;
}
void TimePickerDialogView::SwitchTimePickerPage(const RefPtr<FrameNode> &timePickerNode,
                                                const RefPtr<FrameNode> &buttonCancelNode,
                                                const RefPtr<FrameNode> &buttonConfirmNode,
                                                const RefPtr<FrameNode>& cancelNextDividerNode,
                                                const RefPtr<FrameNode>& nextConfirmDividerNode)
{
    auto ampmNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(ampmNode);
    ampmNode->SetActive(switchFlag_ ? true : false);
    auto ampmLayoutProperty = ampmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(ampmLayoutProperty);
    ampmLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    ampmNode->MarkDirtyNode();

    auto hourNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(1));
    CHECK_NULL_VOID(hourNode);
    hourNode->SetActive(switchFlag_ ? false : true);
    auto hourLayoutProperty = hourNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(hourLayoutProperty);
    hourLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);

    auto minuteNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(2));
    CHECK_NULL_VOID(minuteNode);
    minuteNode->SetActive(switchFlag_ ? false : true);
    auto minuteLayoutProperty = minuteNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(minuteLayoutProperty);
    minuteLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
    hourNode->MarkDirtyNode();
    minuteNode->MarkDirtyNode();

    buttonCancelNode->SetActive(switchFlag_ ? true : false);
    auto cancelButtonLayoutProperty = buttonCancelNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    cancelButtonLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    buttonCancelNode->MarkDirtyNode();

    cancelNextDividerNode->SetActive(switchFlag_ ? true : false);
    auto cancelNextLayoutProperty = cancelNextDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(cancelNextLayoutProperty);
    cancelNextLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);

    buttonConfirmNode->SetActive(switchFlag_ ? false : true);
    auto confirmButtonLayoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(confirmButtonLayoutProperty);
    confirmButtonLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);

    nextConfirmDividerNode->SetActive(switchFlag_ ? false : true);
    auto nextConfirmLayoutProperty = nextConfirmDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(nextConfirmLayoutProperty);
    nextConfirmLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);

    switchFlag_ = !switchFlag_;
}
RefPtr<FrameNode> TimePickerDialogView::CreateConfirmNode(const RefPtr<FrameNode>& dateNode,
    const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos, DialogEvent& acceptEvent)
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
    CHECK_NULL_RETURN(buttonConfirmLayoutProperty, nullptr);
    UpdateButtonLayoutProperty(buttonConfirmLayoutProperty, pickerTheme);
    auto buttonConfirmRenderContext = buttonConfirmNode->GetRenderContext();
    buttonConfirmRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateButtonStyles(buttonInfos, ACCEPT_BUTTON_INDEX, buttonConfirmLayoutProperty, buttonConfirmRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonConfirmNode, true);

    textConfirmNode->MountToParent(buttonConfirmNode);
    auto eventConfirmHub = buttonConfirmNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    CHECK_NULL_RETURN(dateNode, nullptr);
    SetDialogAcceptEvent(dateNode, std::move(acceptEvent));
    auto clickCallback = [weak = WeakPtr<FrameNode>(dateNode)](const GestureEvent& /* info */) {
        auto dateNode = weak.Upgrade();
        CHECK_NULL_VOID(dateNode);
        auto pickerPattern = dateNode->GetPattern<TimePickerRowPattern>();
        CHECK_NULL_VOID(pickerPattern);
        auto timePickerEventHub = pickerPattern->GetEventHub<TimePickerEventHub>();
        CHECK_NULL_VOID(timePickerEventHub);
        timePickerEventHub->FireDialogAcceptEvent(pickerPattern->GetSelectedObject(true));
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    buttonConfirmNode->MarkModifyDone();
    return buttonConfirmNode;
}

void TimePickerDialogView::UpdateButtonLayoutProperty(
    const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(buttonConfirmLayoutProperty);
    buttonConfirmLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.ok"));
    buttonConfirmLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    buttonConfirmLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonConfirmLayoutProperty->UpdateFlexShrink(1.0);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    UpdateConfirmButtonMargin(buttonConfirmLayoutProperty, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_VOID(buttonTheme);
        buttonConfirmLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
}

void TimePickerDialogView::UpdateConfirmButtonMargin(
    const RefPtr<ButtonLayoutProperty>& buttonConfirmLayoutProperty, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        margin.left = CalcLength(0.0_vp);
    } else {
        margin.right = CalcLength(dialogTheme->GetActionsPadding().Right());
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.left = CalcLength(0.0_vp);
    }
    buttonConfirmLayoutProperty->UpdateMargin(margin);
}

void TimePickerDialogView::UpdateCancelButtonMargin(
    const RefPtr<ButtonLayoutProperty>& buttonCancelLayoutProperty, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
        margin.top = CalcLength(dialogTheme->GetDividerHeight());
        margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
        margin.right = CalcLength(0.0_vp);
    } else {
        margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
        margin.top = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
        margin.right = CalcLength(0.0_vp);
    }
    buttonCancelLayoutProperty->UpdateMargin(margin);
}

RefPtr<FrameNode> TimePickerDialogView::CreateCancelNode(NG::DialogGestureEvent& cancelEvent,
    const RefPtr<FrameNode>& timePickerNode, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
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

    auto buttonCancelLayoutProperty = buttonCancelNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonCancelLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    buttonCancelLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    buttonCancelLayoutProperty->UpdateType(ButtonType::CAPSULE);
    buttonCancelLayoutProperty->UpdateFlexShrink(1.0);
    UpdateCancelButtonMargin(buttonCancelLayoutProperty, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        buttonCancelLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }

    auto buttonCancelRenderContext = buttonCancelNode->GetRenderContext();
    buttonCancelRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateButtonStyles(buttonInfos, CANCEL_BUTTON_INDEX, buttonCancelLayoutProperty, buttonCancelRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, buttonCancelNode, false);
    buttonCancelNode->MarkModifyDone();
    return buttonCancelNode;
}

void TimePickerDialogView::UpdateButtonStyles(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    auto buttonTheme = PipelineBase::GetCurrentContext()->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].type.has_value()) {
        buttonLayoutProperty->UpdateType(buttonInfos[index].type.value());
    }
    UpdateButtonStyleAndRole(buttonInfos, index, buttonLayoutProperty, buttonRenderContext, buttonTheme);
    if (buttonInfos[index].fontSize.has_value()) {
        buttonLayoutProperty->UpdateFontSize(buttonInfos[index].fontSize.value());
    }
    if (buttonInfos[index].fontColor.has_value()) {
        buttonLayoutProperty->UpdateFontColor(buttonInfos[index].fontColor.value());
    }
    if (buttonInfos[index].fontWeight.has_value()) {
        buttonLayoutProperty->UpdateFontWeight(buttonInfos[index].fontWeight.value());
    }
    if (buttonInfos[index].fontStyle.has_value()) {
        buttonLayoutProperty->UpdateFontStyle(buttonInfos[index].fontStyle.value());
    }
    if (buttonInfos[index].fontFamily.has_value()) {
        buttonLayoutProperty->UpdateFontFamily(buttonInfos[index].fontFamily.value());
    }
    if (buttonInfos[index].borderRadius.has_value()) {
        buttonLayoutProperty->UpdateBorderRadius(buttonInfos[index].borderRadius.value());
    }
    if (buttonInfos[index].backgroundColor.has_value()) {
        buttonRenderContext->UpdateBackgroundColor(buttonInfos[index].backgroundColor.value());
    }
}

void TimePickerDialogView::UpdateButtonStyleAndRole(const std::vector<ButtonInfo>& buttonInfos, size_t index,
    const RefPtr<ButtonLayoutProperty>& buttonLayoutProperty, const RefPtr<RenderContext>& buttonRenderContext,
    const RefPtr<ButtonTheme>& buttonTheme)
{
    if (index >= buttonInfos.size()) {
        return;
    }
    CHECK_NULL_VOID(buttonLayoutProperty);
    CHECK_NULL_VOID(buttonRenderContext);
    CHECK_NULL_VOID(buttonTheme);
    if (buttonInfos[index].role.has_value()) {
        buttonLayoutProperty->UpdateButtonRole(buttonInfos[index].role.value());
        ButtonStyleMode buttonStyleMode;
        if (buttonInfos[index].buttonStyle.has_value()) {
            buttonStyleMode = buttonInfos[index].buttonStyle.value();
        } else {
            buttonStyleMode = buttonLayoutProperty->GetButtonStyle().value_or(ButtonStyleMode::EMPHASIZE);
        }
        auto bgColor = buttonTheme->GetBgColor(buttonStyleMode, buttonInfos[index].role.value());
        auto textColor = buttonTheme->GetTextColor(buttonStyleMode, buttonInfos[index].role.value());
        buttonRenderContext->UpdateBackgroundColor(bgColor);
        buttonLayoutProperty->UpdateFontColor(textColor);
    }
    if (buttonInfos[index].buttonStyle.has_value()) {
        buttonLayoutProperty->UpdateButtonStyle(buttonInfos[index].buttonStyle.value());
        ButtonRole buttonRole = buttonLayoutProperty->GetButtonRole().value_or(ButtonRole::NORMAL);
        auto bgColor = buttonTheme->GetBgColor(buttonInfos[index].buttonStyle.value(), buttonRole);
        auto textColor = buttonTheme->GetTextColor(buttonInfos[index].buttonStyle.value(), buttonRole);
        buttonRenderContext->UpdateBackgroundColor(bgColor);
        buttonLayoutProperty->UpdateFontColor(textColor);
    }
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

void TimePickerDialogView::SetTextProperties(
    const RefPtr<PickerTheme>& pickerTheme, const PickerTextProperties& properties)
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
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontFamily,
        properties.disappearTextStyle_.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontStyle,
        properties.disappearTextStyle_.fontStyle.value_or(disappearStyle.GetFontStyle()));

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, properties.normalTextStyle_.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize, normalStyle.GetFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, Color, properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        TimePickerLayoutProperty, Weight, properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontFamily,
        properties.normalTextStyle_.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontStyle,
        properties.normalTextStyle_.fontStyle.value_or(normalStyle.GetFontStyle()));

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
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontFamily,
        properties.selectedTextStyle_.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontStyle,
        properties.selectedTextStyle_.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void TimePickerDialogView::UpdateButtonDefaultFocus(
    const std::vector<ButtonInfo>& buttonInfos, const RefPtr<FrameNode>& buttonNode, bool isConfirm)
{
    bool setDefaultFocus = false;
    if (buttonInfos.size() > CANCEL_BUTTON_INDEX) {
        if (buttonInfos[ACCEPT_BUTTON_INDEX].isPrimary && buttonInfos[CANCEL_BUTTON_INDEX].isPrimary) {
            return;
        }
        auto index = isConfirm ? ACCEPT_BUTTON_INDEX : CANCEL_BUTTON_INDEX;
        if (buttonInfos[index].isPrimary) {
            setDefaultFocus = true;
        }
    } else if (buttonInfos.size() == CANCEL_BUTTON_INDEX) {
        bool isAcceptButtonPrimary = (buttonInfos[0].isAcceptButton && isConfirm && buttonInfos[0].isPrimary);
        bool isCancelButtonPrimary = (!buttonInfos[0].isAcceptButton && !isConfirm && buttonInfos[0].isPrimary);
        if (isAcceptButtonPrimary || isCancelButtonPrimary) {
            setDefaultFocus = true;
        }
    }
    if (setDefaultFocus && buttonNode) {
        auto focusHub = buttonNode->GetOrCreateFocusHub();
        if (focusHub) {
            focusHub->SetIsDefaultFocus(true);
        }
    }
}

bool TimePickerDialogView::GetIsUserSetTextProperties(const PickerTextProperties& properties)
{
    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        return true;
    }

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        return true;
    }
    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        return true;
    }
    return false;
}
bool TimePickerDialogView::NeedadaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (GreatOrEqual(pipeline->GetFontScale(), 1.75f)) {
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
