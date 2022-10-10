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
#include "core/components_ng/pattern/picker/datepicker_view.h"

#include <utility>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
} // namespace

void DatePickerView::CreateDatePicker()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);

    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();

    auto yearId = datePickerPattern->GetYearId();
    auto monthId = datePickerPattern->GetMonthId();
    auto dayId = datePickerPattern->GetDayId();

    auto context = dateNode->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    uint32_t showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
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
        yearColumnNode->MountToParent(dateNode);
    }
    if (!hasMonthNode) {
        monthColumnNode->MountToParent(dateNode);
    }
    if (!hasDayNode) {
        dayColumnNode->MountToParent(dateNode);
    }
    stack->Push(dateNode);
}

void DatePickerView::SetShowLunar(bool lunar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Lunar, lunar);
}

void DatePickerView::SetStartDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetStartDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, StartDate, datePickerPattern->GetStartDateLunar());
}

void DatePickerView::SetEndDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEndDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, EndDate, datePickerPattern->GetEndDateLunar());
}

void DatePickerView::SetSelectedDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetSelectDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedDate, datePickerPattern->GetSelectDate());
}

void DatePickerView::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG