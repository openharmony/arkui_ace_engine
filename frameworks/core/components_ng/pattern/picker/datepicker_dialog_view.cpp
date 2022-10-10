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

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
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
    std::map<std::string, NG::DailogChangeEvent> dialogEvent)
{
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, nullptr);

    auto dialogNodeChild = AccessibilityManager::DynamicCast<FrameNode>(dialogNode->GetChildren().front());

    auto dateNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, dateNodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
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

    SetShowLunar(isLunar);
    auto changeEvent = dialogEvent["changeId"];
    SetDailogChange(dateNode, std::move(changeEvent));
    ViewStackProcessor::GetInstance()->Finish();
    auto childSize = dialogNode->GetChildren().size();
    dateNode->MountToParent(dialogNodeChild, static_cast<int32_t>(childSize) - 2); // place dateNode in front of the button
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
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

void DatePickerDialogView::SetDailogChange(const RefPtr<FrameNode>& frameNode, DailogChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDailogChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG