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

#include "bridge/declarative_frontend/jsview/models/timepicker_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components/picker/picker_time_component.h"

namespace OHOS::Ace::Framework {
void TimePickerModelImpl::CreateTimePicker(RefPtr<PickerTheme> pickerTheme, bool hasSecond)
{
    auto timePicker = AceType::MakeRefPtr<PickerTimeComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(timePicker);

    timePicker->SetIsDialog(false);
    timePicker->SetHasButtons(false);
    timePicker->SetTheme(pickerTheme);
    ViewStackProcessor::GetInstance()->Push(timePicker);
}

void TimePickerModelImpl::SetHour24(bool isUseMilitaryTime)
{
    JSViewSetProperty(&PickerTimeComponent::SetHour24, isUseMilitaryTime);
}

void TimePickerModelImpl::SetSelectedTime(const PickerTime& value)
{
    JSViewSetProperty(&PickerTimeComponent::SetSelectedTime, value);
}

void TimePickerModelImpl::SetOnChange(ChangeEvent&& onChange)
{
    auto datePicker = EventMarker([func = std::move(onChange)](const BaseEventInfo* info) { func(info); });
    JSViewSetProperty(&PickerBaseComponent::SetOnChange, std::move(datePicker));
}

void TimePickerModelImpl::SetBackgroundColor(const Color& color)
{
    auto pickerBase = AceType::DynamicCast<PickerBaseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!pickerBase) {
        LOGE("PickerBaseComponent is null");
        return;
    }

    pickerBase->SetHasBackgroundColor(true);
}

void TimePickerDialogModelImpl::SetTimePickerDialogShow(PickerDialogInfo& pickerDialog,
    NG::TimePickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange,
    TimePickerDialogEvent& timePickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    RefPtr<Component> component;
    auto timePicker = AceType::MakeRefPtr<PickerTimeComponent>();
    bool isUseMilitaryTime = pickerDialog.isUseMilitaryTime;
    if (pickerDialog.isSelectedTime == true) {
        timePicker->SetSelectedTime(pickerDialog.pickerTime);
    }
    timePicker->SetIsDialog(true);
    timePicker->SetIsCreateDialogComponent(true);
    timePicker->SetHour24(isUseMilitaryTime);
    component = timePicker;

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
    datePicker->SetDialogName("TimePickerDialog");
    datePicker->OpenDialog(properties);
}
} // namespace OHOS::Ace::Framework
