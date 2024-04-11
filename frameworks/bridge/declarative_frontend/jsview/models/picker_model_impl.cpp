/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/picker_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components/picker/picker_time_component.h"

namespace OHOS::Ace::Framework {
void DatePickerModelImpl::CreateDatePicker(RefPtr<PickerTheme> theme)
{
    auto datePicker = AceType::MakeRefPtr<PickerDateComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(datePicker);

    datePicker->SetIsDialog(false);
    datePicker->SetHasButtons(false);
    datePicker->SetTheme(theme);
    ViewStackProcessor::GetInstance()->Push(datePicker);
}

void DatePickerModelImpl::CreateTimePicker(RefPtr<PickerTheme> theme)
{
    auto timePicker = AceType::MakeRefPtr<PickerTimeComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(timePicker);
    timePicker->SetIsDialog(false);
    timePicker->SetHasButtons(false);

    timePicker->SetTheme(theme);
    ViewStackProcessor::GetInstance()->Push(timePicker);
}

void DatePickerModelImpl::SetStartDate(const PickerDate& value)
{
    JSViewSetProperty(&PickerDateComponent::SetStartDate, value);
}

void DatePickerModelImpl::SetEndDate(const PickerDate& value)
{
    JSViewSetProperty(&PickerDateComponent::SetEndDate, value);
}

void DatePickerModelImpl::SetSelectedDate(const PickerDate& value)
{
    JSViewSetProperty(&PickerDateComponent::SetSelectedDate, value);
}

void DatePickerModelImpl::SetSelectedTime(const PickerTime& selectedTime)
{
    JSViewSetProperty(&PickerTimeComponent::SetSelectedTime, selectedTime);
}

void DatePickerModelImpl::SetShowLunar(bool lunar)
{
    JSViewSetProperty(&PickerDateComponent::SetShowLunar, lunar);
}

void DatePickerModelImpl::SetHour24(bool value)
{
    JSViewSetProperty(&PickerTimeComponent::SetHour24, value);
}

void DatePickerModelImpl::SetOnChange(DateChangeEvent&& onChange)
{
    auto datePicker = EventMarker([func = std::move(onChange)](const BaseEventInfo* info) { func(info); });
    JSViewSetProperty(&PickerBaseComponent::SetOnChange, std::move(datePicker));
}

void DatePickerModelImpl::SetBackgroundColor(const Color& color)
{
    auto pickerBase = AceType::DynamicCast<PickerBaseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!pickerBase) {
        LOGE("PickerBaseComponent is null");
        return;
    }

    pickerBase->SetHasBackgroundColor(true);
}

void DatePickerDialogModelImpl::SetDatePickerDialogShow(PickerDialogInfo& pickerDialog,
    NG::DatePickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onDateAccept,
    std::function<void(const std::string&)>&& onDateChange, std::function<void(const std::string&)>&& onChange,
    DatePickerType pickerType, PickerDialogEvent& pickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    std::string name;
    RefPtr<Component> component;
    switch (pickerType) {
        case DatePickerType::TIME: {
            auto timePicker = AceType::MakeRefPtr<PickerTimeComponent>();
            if (pickerDialog.isSelectedDate == true) {
                timePicker->SetSelectedTime(pickerDialog.pickerTime);
            }
            timePicker->SetIsDialog(true);
            timePicker->SetIsCreateDialogComponent(true);
            timePicker->SetHour24(settingData.useMilitary);
            component = timePicker;
            name = "TimePickerDialog";
            break;
        }
        case DatePickerType::DATE: {
            auto datePicker = AceType::MakeRefPtr<PickerDateComponent>();
            auto startDays = pickerDialog.parseStartDate.ToDays();
            auto endDays = pickerDialog.parseEndDate.ToDays();
            auto selectedDays = pickerDialog.parseSelectedDate.ToDays();
            if (startDays > endDays || selectedDays < startDays || selectedDays > endDays) {
                LOGE("date error");
            }
            if (pickerDialog.isStartDate == true) {
                datePicker->SetStartDate(pickerDialog.parseStartDate);
            }
            if (pickerDialog.isEndDate == true) {
                datePicker->SetEndDate(pickerDialog.parseEndDate);
            }
            if (pickerDialog.isSelectedDate) {
                datePicker->SetSelectedDate(pickerDialog.parseSelectedDate);
            }
            datePicker->SetIsDialog(true);
            datePicker->SetIsCreateDialogComponent(true);
            datePicker->SetShowLunar(settingData.isLunar);

            component = datePicker;
            name = "DatePickerDialog";
            break;
        }
        default: {
            LOGE("Undefined date picker type.");
            return;
        }
    }
    auto datePicker = AceType::DynamicCast<PickerBaseComponent>(component);
    DialogProperties properties {};
    properties.alignment = Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) ? DialogAlignment::CENTER
                                                                                          : DialogAlignment::DEFAULT;
    properties.customComponent = datePicker;
    properties.customStyle = true;
    auto acceptId = EventMarker(std::move(onAccept));
    datePicker->SetDialogAcceptEvent(acceptId);
    auto cancelId = EventMarker(std::move(onCancel));
    datePicker->SetDialogCancelEvent(cancelId);
    auto changeId = EventMarker(std::move(onChange));
    datePicker->SetDialogChangeEvent(changeId);
    datePicker->SetDialogName(name);
    datePicker->OpenDialog(properties);
}
} // namespace OHOS::Ace::Framework
