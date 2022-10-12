/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"

#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_view.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
} // namespace

RefPtr<FrameNode> DatePickerDialogView::Show(const DialogProperties& dialogProperties,
    std::map<std::string, PickerDate> datePickerProperty, bool isLunar,
    std::map<std::string, NG::DailogEvent> dialogEvent,
    std::map<std::string, NG::DailogGestureEvent> dialogCancalEvent)
{
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto dateNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, dateNodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    CHECK_NULL_RETURN(dateNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(dateNode);
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, nullptr);

    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();

    auto yearId = datePickerPattern->GetYearId();
    auto monthId = datePickerPattern->GetMonthId();
    auto dayId = datePickerPattern->GetDayId();

    auto context = dateNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, nullptr);
    uint32_t showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    datePickerPattern->SetShowCount(showCount);

    auto yearColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, yearId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(yearColumnNode, nullptr);
    if (!hasYearNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(yearColumnNode);
        }
        yearColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(yearColumnNode);
    }

    auto monthColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, monthId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(monthColumnNode, nullptr);
    if (!hasMonthNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(monthColumnNode);
        }
        monthColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(monthColumnNode);
    }

    auto dayColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, dayId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(dayColumnNode, nullptr);
    if (!hasDayNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(dayColumnNode);
        }
        dayColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(dayColumnNode);
    }

    if (!hasYearNode) {
        yearColumnNode->MountToParent(dateNode);
    }
    if (!hasMonthNode) {
        monthColumnNode->MountToParent(dateNode);
    }
    if (!hasDayNode) {
        dayColumnNode->MountToParent(dateNode);
    }
    dateNode->MarkModifyDone();

    PickerDate parseStartDate;
    PickerDate parseEndDate;
    PickerDate parseSelectedDate;
    SetShowLunar(isLunar);
    if (datePickerProperty.find("start") != datePickerProperty.end()) {
        parseStartDate = datePickerProperty["start"];
        SetStartDate(datePickerPattern, parseStartDate);
    }
    if (datePickerProperty.find("end") != datePickerProperty.end()) {
        parseEndDate = datePickerProperty["end"];
        SetEndDate(datePickerPattern, parseEndDate);
    }
    if (datePickerProperty.find("selected") != datePickerProperty.end()) {
        parseSelectedDate = datePickerProperty["selected"];
        SetSelectedDate(datePickerPattern, parseSelectedDate);
    }

    auto changeEvent = dialogEvent["changeId"];
    SetDailogChange(dateNode, std::move(changeEvent));
    auto contentRow = CreateButtonNode(dateNode, dialogEvent, std::move(dialogCancalEvent));
    CHECK_NULL_RETURN(contentRow, nullptr);
    auto buttonTitleNode = CreateTitleButtonNode(dateNode);
    CHECK_NULL_RETURN(buttonTitleNode, nullptr);
    ViewStackProcessor::GetInstance()->Finish();
    buttonTitleNode->MountToParent(contentColumn);
    dateNode->MountToParent(contentColumn);
    contentRow->MountToParent(contentColumn);
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, contentColumn);
    CHECK_NULL_RETURN(dialogNode, nullptr);
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateTitleButtonNode(const RefPtr<FrameNode>& dateNode)
{
    auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(pickerPattern, nullptr);
    auto buttonTitleNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, pickerPattern->GetButtonTitleId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textTitleNodeId = pickerPattern->GetTitleId();
    auto textTitleNode =
        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textTitleNodeId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textTitleNode, nullptr);
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent("");
    textTitleNode->MountToParent(buttonTitleNode);

    return buttonTitleNode;
}

RefPtr<FrameNode> DatePickerDialogView::CreateButtonNode(const RefPtr<FrameNode>& dateNode,
    std::map<std::string, NG::DailogEvent> dialogEvent,
    std::map<std::string, NG::DailogGestureEvent> dialogCancalEvent)
{
    auto acceptEvent = dialogEvent["acceptId"];
    auto cancelEvent = dialogCancalEvent["cancelId"];
    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textConfirmNode, nullptr);
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent("confirm");
    textConfirmNode->MountToParent(buttonConfirmNode);
    auto eventConfirHub = textConfirmNode->GetOrCreateGestureEventHub();

    auto clickCallback = [dateNode, acceptEvent](const GestureEvent& /*info*/) {
        SetDailogAcceptEvent(dateNode, acceptEvent);
        auto pickerPattern = dateNode->GetPattern<DatePickerPattern>();
        auto str = pickerPattern->GetSelectedObject(true);
        CHECK_NULL_VOID(pickerPattern);
        auto datePickerEventHub = pickerPattern->GetEventHub<DatePickerEventHub>();
        CHECK_NULL_VOID(datePickerEventHub);
        datePickerEventHub->FireDailogAcceptEvent(str);
    };
    eventConfirHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));

    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textCancelLayoutProperty, nullptr);
    textCancelLayoutProperty->UpdateContent("cancel");
    textCancelNode->MountToParent(buttonCancelNode);
    auto eventCancelHub = textCancelNode->GetOrCreateGestureEventHub();
    eventCancelHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(std::move(cancelEvent)));

    buttonConfirmNode->MountToParent(contentRow);
    buttonCancelNode->MountToParent(contentRow);
    return contentRow;
}

void DatePickerDialogView::SetStartDate(const RefPtr<DatePickerPattern>& datePickerPattern, const PickerDate& value)
{
    datePickerPattern->SetStartDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, StartDate, datePickerPattern->GetStartDateLunar());
}

void DatePickerDialogView::SetEndDate(const RefPtr<DatePickerPattern>& datePickerPattern, const PickerDate& value)
{
    datePickerPattern->SetEndDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, EndDate, datePickerPattern->GetEndDateLunar());
}

void DatePickerDialogView::SetSelectedDate(const RefPtr<DatePickerPattern>& datePickerPattern, const PickerDate& value)
{
    datePickerPattern->SetSelectDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedDate, datePickerPattern->GetSelectDate());
}

void DatePickerDialogView::SetShowLunar(bool lunar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Lunar, lunar);
}

void DatePickerDialogView::SetDailogChange(const RefPtr<FrameNode>& frameNode, DailogEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDailogChange(std::move(onChange));
}

void DatePickerDialogView::SetDailogAcceptEvent(const RefPtr<FrameNode>& frameNode, DailogEvent onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDailogAcceptEvent(std::move(onChange));
}
} // namespace OHOS::Ace::NG