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
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
} // namespace

RefPtr<FrameNode> TimePickerDialogView::Show(const DialogProperties& dialogProperties,
    std::map<std::string, PickerTime> timePickerProperty, bool isUseMilitaryTime,
    std::map<std::string, NG::DailogChangeEvent> dialogEvent)
{
    auto dialogNode = DialogView::CreateDialogNode(dialogProperties, nullptr);
    auto dialogNodeChild = AccessibilityManager::DynamicCast<FrameNode>(dialogNode->GetChildren().front());

    auto timeNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, timeNodeId, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ViewStackProcessor::GetInstance()->Push(timePickerNode);

    auto context = timePickerNode->GetContext();
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
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetShowCount(showCount);

    auto hasHourNode = timePickerRowPattern->HasHourNode();
    auto hasMinuteNode = timePickerRowPattern->HasMinuteNode();

    auto hourId = timePickerRowPattern->GetHourId();
    auto minuteId = timePickerRowPattern->GetMinuteId();

    if (!hasHourNode) {
        auto hourColumnNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, hourId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
        CHECK_NULL_RETURN(hourColumnNode, nullptr);
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(hourColumnNode);
        }
        hourColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(hourColumnNode);
        hourColumnNode->MountToParent(timePickerNode);
    }

    if (!hasMinuteNode) {
        auto minuteColumnNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, minuteId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
        CHECK_NULL_RETURN(minuteColumnNode, nullptr);
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, nullptr);
            textNode->MountToParent(minuteColumnNode);
        }
        minuteColumnNode->MarkModifyDone();
        timePickerRowPattern->SetColumn(minuteColumnNode);
        minuteColumnNode->MountToParent(timePickerNode);
    }
    if (timePickerProperty.find("selected") != timePickerProperty.end()) {
        auto selectedTime = timePickerProperty["selected"];
        SetSelectedTime(timePickerRowPattern, selectedTime);
    }
    SetHour24(timePickerRowPattern, isUseMilitaryTime);
    auto changeEvent = dialogEvent["changeId"];
    SetDailogChange(timePickerNode, std::move(changeEvent));
    ViewStackProcessor::GetInstance()->Finish();
    auto childSize = dialogNode->GetChildren().size();
    timePickerNode->MountToParent(dialogNodeChild, static_cast<int32_t>(childSize) - 2); // place timePickerNode in front of the button
    dialogNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return dialogNode;
}

void TimePickerDialogView::SetSelectedTime(
    const RefPtr<TimePickerRowPattern>& timePickerRowPattern, const PickerTime& value)
{
    timePickerRowPattern->SetSelectedTime(value);
}

void TimePickerDialogView::SetHour24(const RefPtr<TimePickerRowPattern>& timePickerRowPattern, bool isUseMilitaryTime)
{
    timePickerRowPattern->SetHour24(isUseMilitaryTime);
}

void TimePickerDialogView::SetDailogChange(const RefPtr<FrameNode>& frameNode, DailogChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDailogChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG