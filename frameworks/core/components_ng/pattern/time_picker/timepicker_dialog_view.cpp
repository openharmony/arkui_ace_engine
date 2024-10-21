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
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t DIVIDER_ROWS_THREE = 3;
const int32_t MARGIN_HALF = 2;
const int32_t BUFFER_NODE_NUMBER = 2;
constexpr Dimension PICKER_DIALOG_MARGIN_FORM_EDGE = 24.0_vp;
constexpr Dimension TITLE_BUTTON_HEIGHT = 32.0_vp;
constexpr size_t ACCEPT_BUTTON_INDEX = 0;
constexpr size_t CANCEL_BUTTON_INDEX = 1;
} // namespace
bool TimePickerDialogView::switchFlag_ = false;
Dimension TimePickerDialogView::selectedTextStyleFont_ = 40.0_fp;
Dimension TimePickerDialogView::normalTextStyleFont_ = 32.0_fp;
Dimension TimePickerDialogView::disappearTextStyleFont_ = 28.0_fp;

RefPtr<FrameNode> TimePickerDialogView::Show(const DialogProperties& dialogProperties,
    const TimePickerSettingData& settingData, const std::vector<ButtonInfo>& buttonInfos,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    auto isNeedAging = (NeedAdaptForAging() && (!settingData.isUseMilitaryTime));
    GetUserSettingLimit();
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
    timePickerRowPattern->SetIsShowInDialog(true);
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetBackgroundColor(dialogTheme->GetBackgroundColor());
    timePickerRowPattern->SetTextProperties(settingData.properties);
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
    }
    timePickerRowPattern->SetHasSecond(settingData.showSecond);
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
    RefPtr<FrameNode> contentRow = nullptr;
    auto buttonTitleNode = CreateTitleButtonNode(timePickerNode);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);

    if (isNeedAging) {
        contentRow = CreateButtonNodeForAging(buttonTitleNode,
            timePickerNode, timePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
    } else {
        contentRow = CreateButtonNode(
            timePickerNode, timePickerNode, buttonInfos, dialogEvent, std::move(dialogCancelEvent));
        contentRow->AddChild(CreateDividerNode(timePickerNode), 1);
    }
    CHECK_NULL_RETURN(contentRow, nullptr);
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

    if (isNeedAging) {
        for (uint32_t i = 1; i < timePickerNode->GetChildren().size(); i++) {
            auto childStackNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(i));
            CHECK_NULL_RETURN(childStackNode, nullptr);
            for (uint32_t j = 0; j < childStackNode->GetChildren().size(); j++) {
                auto childNode = AceType::DynamicCast<FrameNode>(childStackNode->GetChildAtIndex(j));
                CHECK_NULL_RETURN(childNode, nullptr);
                auto childLayoutProperty = childNode->GetLayoutProperty<LayoutProperty>();
                CHECK_NULL_RETURN(childLayoutProperty, nullptr);
                childLayoutProperty->UpdateVisibility(VisibleType::GONE);
                childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
            }
            auto layoutProperty = childStackNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_RETURN(layoutProperty, nullptr);
            layoutProperty->UpdateAlignment(Alignment::CENTER);
            layoutProperty->UpdateLayoutWeight(0);
        }
    }
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, nullptr);
    dialogPattern->SetIsPickerDiaglog(true);
    auto closeDiaglogEvent = CloseDiaglogEvent(timePickerPattern, dialogNode);
    auto event = [func = std::move(closeDiaglogEvent)](const GestureEvent& /* info */) {
        func();
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

std::function<void()> TimePickerDialogView::CloseDiaglogEvent(const RefPtr<TimePickerRowPattern>& timePickerPattern,
    const RefPtr<FrameNode>& dialogNode)
{
    auto event = [weak = WeakPtr<FrameNode>(dialogNode),
        weakPattern = WeakPtr<TimePickerRowPattern>(timePickerPattern)]() {
        auto dialogNode = weak.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->SetIsPickerDiaglog(false);
        auto timePickerPattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(timePickerPattern);
        if (timePickerPattern->GetIsShowInDialog()) {
            auto pipeline = PipelineContext::GetCurrentContext();
            auto overlayManager = pipeline->GetOverlayManager();
            overlayManager->CloseDialog(dialogNode);
            timePickerPattern->SetIsShowInDialog(false);
        }
    };
    timePickerPattern->updateFontConfigurationEvent(event);
    return event;
}

RefPtr<FrameNode> TimePickerDialogView::CreateNextPrevButtonNode(std::function<void()>& timePickerSwitchEvent,
    const RefPtr<FrameNode>& timeNode, const std::vector<ButtonInfo>& buttonInfos)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto nextPrevButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(nextPrevButtonNode, nullptr);
    auto textNextPrevNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNextPrevNode, nullptr);
    auto textNextPrevLayoutProperty = textNextPrevNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textNextPrevLayoutProperty, nullptr);
    textNextPrevLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.next"));
    textNextPrevLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    textNextPrevLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textNextPrevLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    textNextPrevNode->MountToParent(nextPrevButtonNode);
    auto eventNextPrevHub = nextPrevButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventNextPrevHub, nullptr);
    auto event = UpdateTimePickerSwitchEvent(timeNode, textNextPrevNode, dialogTheme, nextPrevButtonNode,
        timePickerSwitchEvent);
    eventNextPrevHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(event)));
    auto buttonNextPrevEventHub = nextPrevButtonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonNextPrevEventHub, nullptr);
    buttonNextPrevEventHub->SetStateEffect(true);
    auto buttonNextPrevLayoutProperty = nextPrevButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    buttonNextPrevLayoutProperty->UpdateLabel(Localization::GetInstance()->GetEntryLetters("common.next"));
    buttonNextPrevLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_MAIN_AXIS);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonNextPrevLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonNextPrevLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
    buttonNextPrevLayoutProperty->UpdateFlexShrink(1.0);
    UpdateConfirmButtonMargin(buttonNextPrevLayoutProperty, dialogTheme);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            buttonNextPrevLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetButtonWidth()), CalcLength(pickerTheme->GetButtonHeight())));
    } else {
        buttonNextPrevLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(buttonTheme->GetHeight())));
    }
    auto buttonNextPrevRenderContext = nextPrevButtonNode->GetRenderContext();
    buttonNextPrevRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    UpdateButtonStyles(buttonInfos, CANCEL_BUTTON_INDEX, buttonNextPrevLayoutProperty, buttonNextPrevRenderContext);
    UpdateButtonDefaultFocus(buttonInfos, nextPrevButtonNode, false);
    nextPrevButtonNode->MarkModifyDone();
    return nextPrevButtonNode;
}

std::function<void(const GestureEvent&)> TimePickerDialogView::UpdateTimePickerSwitchEvent(
    const RefPtr<FrameNode>& timeNode, const RefPtr<FrameNode>& textNode, const RefPtr<DialogTheme>& dialogTheme,
    const RefPtr<FrameNode>& buttonNode, const std::function<void()>& timePickerSwitchEvent)
{
    auto nextPrevEvent = [weak = WeakPtr<FrameNode>(timeNode), textWeak = WeakPtr<FrameNode>(textNode),
                        nextPrevButtonNodeWeak = WeakPtr<FrameNode>(buttonNode),
                        dialogThemeWeak = WeakPtr<DialogTheme>(dialogTheme),
                        func = std::move(timePickerSwitchEvent)](const GestureEvent&) {
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
    return nextPrevEvent;
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
    textLayoutProperty->UpdateFontSize(
        ConvertTitleFontScaleValue(pickerTheme->GetTitleStyle().GetFontSize()));
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
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonTitleNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(std::nullopt, CalcLength(TITLE_BUTTON_HEIGHT)));
    }
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

RefPtr<FrameNode> TimePickerDialogView::CreateButtonNodeForAging(const RefPtr<FrameNode>& buttonTitleNode,
    const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& timePickerNode,
    const std::vector<ButtonInfo>& buttonInfos, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
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

    auto timePickerSwitchEvent = CreateAndSetTimePickerSwitchEvent(buttonTitleNode, timePickerNode, buttonCancelNode,
        buttonConfirmNode, cancelNextDividerNode, nextConfirmDividerNode);
    auto buttonNextPreNode = CreateNextPrevButtonNode(timePickerSwitchEvent, timePickerNode, buttonInfos);
    CHECK_NULL_RETURN(buttonNextPreNode, nullptr);
    buttonCancelNode->MountToParent(contentRow);
    buttonNextPreNode->MountToParent(contentRow);
    buttonConfirmNode->MountToParent(contentRow);
    contentRow->AddChild(cancelNextDividerNode, 1);
    contentRow->AddChild(nextConfirmDividerNode, DIVIDER_ROWS_THREE);

    switchFlag_ = false;
    auto layoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateVisibility(VisibleType::GONE);
    auto nextConfirmDividerProperty = nextConfirmDividerNode->GetLayoutProperty<LayoutProperty>();
    nextConfirmDividerProperty->UpdateVisibility(VisibleType::GONE);
    return contentRow;
}

std::function<void()> TimePickerDialogView::CreateAndSetTimePickerSwitchEvent(const RefPtr<FrameNode>& buttonTitleNode,
    const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& buttonCancelNode,
    const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<FrameNode>& cancelNextDividerNode,
    const RefPtr<FrameNode>& nextConfirmDividerNode)
{
    auto timePickerSwitchEvent = [weakButtonTitleNode = AceType::WeakClaim(AceType::RawPtr(buttonTitleNode)),
                                     weakTimePickerNode = AceType::WeakClaim(AceType::RawPtr(timePickerNode)),
                                     weakbuttonCancelNode = AceType::WeakClaim(AceType::RawPtr(buttonCancelNode)),
                                     weakcancelNextDividerNode =
                                         AceType::WeakClaim(AceType::RawPtr(cancelNextDividerNode)),
                                     weaknextConfirmDividerNode =
                                         AceType::WeakClaim(AceType::RawPtr(nextConfirmDividerNode)),
                                     weakbuttonConfirmNode = AceType::WeakClaim(AceType::RawPtr(buttonConfirmNode))]() {
        auto buttonTitleNode =   weakButtonTitleNode.Upgrade();
        CHECK_NULL_VOID(buttonTitleNode);
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
        SwitchTimePickerPage(buttonTitleNode, timePickerNode, buttonCancelNode, buttonConfirmNode,
            cancelNextDividerNode, nextConfirmDividerNode);
    };

    return timePickerSwitchEvent;
}

void TimePickerDialogView::SwitchTimePickerPage(const RefPtr<FrameNode>& buttonTitleNode,
    const RefPtr<FrameNode>& timePickerNode, const RefPtr<FrameNode>& buttonCancelNode,
    const RefPtr<FrameNode>& buttonConfirmNode, const RefPtr<FrameNode>& cancelNextDividerNode,
    const RefPtr<FrameNode>& nextConfirmDividerNode)
{
    for (uint32_t i = 0; i < timePickerNode->GetChildren().size(); i++) {
        auto childStackNode = AceType::DynamicCast<FrameNode>(timePickerNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(childStackNode);
        auto layoutProperty = childStackNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        for (uint32_t j = 0; j < childStackNode->GetChildren().size(); j++) {
            auto childNode = AceType::DynamicCast<FrameNode>(childStackNode->GetChildAtIndex(j));
            CHECK_NULL_VOID(childNode);
            auto childLayoutProperty = childNode->GetLayoutProperty<LayoutProperty>();
            CHECK_NULL_VOID(childLayoutProperty);
            if (i == 0) {
                childLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
                layoutProperty->UpdateLayoutWeight(switchFlag_ ? 1 : 0);
            } else {
                childLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
                layoutProperty->UpdateLayoutWeight(switchFlag_ ? 0 : 1);
            }
            childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        }
    }

    auto cancelButtonLayoutProperty = buttonCancelNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    cancelButtonLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    buttonCancelNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto cancelNextLayoutProperty = cancelNextDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(cancelNextLayoutProperty);
    cancelNextLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::VISIBLE : VisibleType::GONE);
    cancelNextDividerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto confirmButtonLayoutProperty = buttonConfirmNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(confirmButtonLayoutProperty);
    confirmButtonLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
    buttonConfirmNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);

    auto nextConfirmLayoutProperty = nextConfirmDividerNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(nextConfirmLayoutProperty);
    nextConfirmLayoutProperty->UpdateVisibility(switchFlag_ ? VisibleType::GONE : VisibleType::VISIBLE);
    nextConfirmDividerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    auto focusHub = buttonTitleNode->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocus();
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    timePickerRowPattern->SetCurrentFocusKeyID(switchFlag_ ? 0 : 1);
    timePickerRowPattern->SetCurrentPage(switchFlag_ ? 0 : 1);
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
    UpdateConfirmButtonTextLayoutProperty(textLayoutProperty, pickerTheme);
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
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonConfirmLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonConfirmLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
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
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, true, ModuleDialogType::TIMEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(isRtl, margin, dialogTheme, false, ModuleDialogType::TIMEPICKER_DIALOG);
    }
    buttonConfirmLayoutProperty->UpdateMargin(margin);
}

void TimePickerDialogView::UpdateConfirmButtonTextLayoutProperty(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.ok"));
    textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    if (!NeedAdaptForAging()) {
        textLayoutProperty->UpdateMaxFontScale(pickerTheme->GetNormalFontScale());
    }
    textLayoutProperty->UpdateFontSize(
        ConvertFontScaleValue(pickerTheme->GetOptionStyle(false, false).GetFontSize()));
    textLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
}

void TimePickerDialogView::UpdateCancelButtonMargin(
    const RefPtr<ButtonLayoutProperty>& buttonCancelLayoutProperty, const RefPtr<DialogTheme>& dialogTheme)
{
    MarginProperty margin;
    bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, true, ModuleDialogType::TIMEPICKER_DIALOG);
    } else {
        DialogTypeMargin::UpdateDialogMargin(!isRtl, margin, dialogTheme, false,
            ModuleDialogType::TIMEPICKER_DIALOG);
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
    UpdateCancelButtonTextLayoutProperty(textCancelLayoutProperty, pickerTheme);
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
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
        buttonCancelLayoutProperty->UpdateType(ButtonType::ROUNDED_RECTANGLE);
    } else {
        buttonCancelLayoutProperty->UpdateType(ButtonType::CAPSULE);
    }
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

void TimePickerDialogView::UpdateCancelButtonTextLayoutProperty(
    const RefPtr<TextLayoutProperty>& textCancelLayoutProperty, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(textCancelLayoutProperty);
    textCancelLayoutProperty->UpdateContent(Localization::GetInstance()->GetEntryLetters("common.cancel"));
    textCancelLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    if (!NeedAdaptForAging()) {
        textCancelLayoutProperty->UpdateMaxFontScale(pickerTheme->GetNormalFontScale());
    }
    textCancelLayoutProperty->UpdateFontSize(pickerTheme->GetOptionStyle(false, false).GetFontSize());
    textCancelLayoutProperty->UpdateFontWeight(pickerTheme->GetOptionStyle(true, false).GetFontWeight());
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
        buttonLayoutProperty->UpdateFontSize(ConvertFontScaleValue(buttonInfos[index].fontSize.value()));
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
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);

    SetTextDisappearProperties(pickerTheme, properties);

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize,
            ConvertFontScaleValue(properties.normalTextStyle_.fontSize.value(), normalTextStyleFont_, true));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, FontSize,
            ConvertFontScaleValue(normalStyle.GetFontSize()));
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
            TimePickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(properties.selectedTextStyle_.fontSize.value(), selectedTextStyleFont_, true));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(selectedStyle.GetFontSize()));
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

void TimePickerDialogView::SetTextDisappearProperties(
    const RefPtr<PickerTheme>& pickerTheme, const PickerTextProperties& properties)
{
    CHECK_NULL_VOID(pickerTheme);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();

    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            TimePickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(properties.disappearTextStyle_.fontSize.value(), disappearTextStyleFont_, true));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(disappearStyle.GetFontSize()));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearColor,
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearWeight,
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontFamily,
        properties.disappearTextStyle_.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(TimePickerLayoutProperty, DisappearFontStyle,
        properties.disappearTextStyle_.fontStyle.value_or(disappearStyle.GetFontStyle()));
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
bool TimePickerDialogView::NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    auto follow = pipeline->IsFollowSystem();
    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale()) &&
        Dimension(pipeline->GetRootHeight()).ConvertToVp() > pickerTheme->GetDeviceHeightLimit() &&
        (follow && (GreatOrEqual(maxAppFontScale, pickerTheme->GetMaxOneFontScale())))) {
        return true;
    }
    return false;
}

const Dimension TimePickerDialogView::AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    auto adjustedScale = std::clamp(fontScale, pickerTheme->GetNormalFontScale(),
        pickerTheme->GetMaxTwoFontScale());
    return fontSizeValue * adjustedScale;
}

const Dimension TimePickerDialogView::ConvertFontScaleValue(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);
    float fontSizeScale = pipeline->GetFontScale();
    Dimension fontSizeValueResult = fontSizeValue;
    Dimension fontSizeValueResultVp(fontSizeLimit.Value(), DimensionUnit::VP);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();

    if (fontSizeValue.Unit() == DimensionUnit::VP) {
        return isUserSetFont ? std::min(fontSizeValueResultVp, fontSizeValue) : fontSizeValue;
    }
    fontSizeScale = std::clamp(fontSizeScale, 0.0f, maxAppFontScale);

    if (NeedAdaptForAging()) {
        if (isUserSetFont) {
            if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontSizeScale,
                fontSizeLimit.ConvertToPx()) && (fontSizeScale != 0.0f)) {
                fontSizeValueResult = fontSizeLimit / fontSizeScale;
            } else {
                fontSizeValueResult = fontSizeValue;
            }
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxThirdFontScale())) {
                fontSizeScale = pickerTheme->GetMaxTwoFontScale() / pickerTheme->GetMaxThirdFontScale();
                fontSizeValueResult = fontSizeValue * fontSizeScale;
            }
        }
    } else {
        if (isUserSetFont) {
            fontSizeValueResult = ConvertFontSizeLimit(fontSizeValueResult, fontSizeLimit, isUserSetFont);
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxOneFontScale()) &&
                 (!NearZero(fontSizeScale))) {
                fontSizeValueResult = fontSizeValueResult / fontSizeScale;
            }
        }
    }
    return fontSizeValueResult;
}

const Dimension TimePickerDialogView::ConvertFontSizeLimit(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    if (isUserSetFont == false) {
        return fontSizeValue;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto fontScale = pipeline->GetFontScale();
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    fontScale = std::clamp(fontScale, 0.0f, maxAppFontScale);

    Dimension fontSizeValueResult = fontSizeValue;
    if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontScale, fontSizeLimit.ConvertToPx())) {
        if (!NearZero(fontScale)) {
            fontSizeValueResult = fontSizeLimit / fontScale;
        }
    }
    return fontSizeValueResult;
}

const Dimension TimePickerDialogView::ConvertTitleFontScaleValue(const Dimension& fontSizeValue)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);

    auto fontScale = pipeline->GetFontScale();
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    fontScale = std::clamp(fontScale, 0.0f, maxAppFontScale);
    if (NearZero(fontScale)) {
        return fontSizeValue;
    }
    if (NeedAdaptForAging()) {
        if (fontSizeValue.Unit() == DimensionUnit::VP) {
            return (fontSizeValue * pickerTheme->GetTitleFontScaleLimit());
        } else {
            if (GreatOrEqualCustomPrecision(fontScale, pickerTheme->GetTitleFontScaleLimit()) &&
             (fontScale != 0.0f)) {
                auto fontSizeScale = pickerTheme->GetTitleFontScaleLimit() / fontScale;
                return (fontSizeValue * fontSizeScale);
            }
        }
    } else {
        if (GreatOrEqualCustomPrecision(fontScale, pickerTheme->GetMaxOneFontScale()) &&
            fontSizeValue.Unit() != DimensionUnit::VP && (fontScale != 0.0f)) {
            return (fontSizeValue / fontScale);
        }
    }
    return fontSizeValue;
}

void TimePickerDialogView::GetUserSettingLimit()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    selectedTextStyleFont_ = pickerTheme->GetUseSetSelectedTextStyle();
    normalTextStyleFont_ = pickerTheme->GetUserSetNormalTextStyle();
    disappearTextStyleFont_ = pickerTheme->GetUserSetDisappearTextStyle();
}

} // namespace OHOS::Ace::NG
