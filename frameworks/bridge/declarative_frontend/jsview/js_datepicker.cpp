/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/declarative_frontend/jsview/js_datepicker.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/picker/picker_time_component.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace::Framework {
void JSDatePicker::JSBind(BindingTarget globalObj)
{
    JSClass<JSDatePicker>::Declare("DatePicker");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSDatePicker>::StaticMethod("create", &JSDatePicker::Create, opt);
    JSClass<JSDatePicker>::StaticMethod("lunar", &JSDatePicker::SetLunar);
    JSClass<JSDatePicker>::StaticMethod("onChange", &JSDatePicker::OnChange);
    JSClass<JSDatePicker>::StaticMethod("useMilitaryTime", &JSDatePicker::UseMilitaryTime);
    JSClass<JSDatePicker>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSDatePicker>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSDatePicker>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSDatePicker>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSDatePicker>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSDatePicker>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSDatePicker>::Inherit<JSViewAbstract>();
    JSClass<JSDatePicker>::Bind(globalObj);
}

void JSDatePicker::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("DatePicker create error, info is non-valid");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    DatePickerType pickerType = DatePickerType::TIME;
    auto type = paramObject->GetProperty("type");
    if (type->IsNumber()) {
        pickerType = static_cast<DatePickerType>(type->ToNumber<int32_t>());
    }
    switch (pickerType) {
        case DatePickerType::TIME: {
            CreateTimePicker(paramObject);
            break;
        }
        case DatePickerType::DATE: {
            CreateDatePicker(paramObject);
            break;
        }
        default: {
            LOGE("Undefined date picker type.");
            break;
        }
    }
}

void JSDatePicker::SetLunar(bool isLunar)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto datePicker = AceType::DynamicCast<PickerDateComponent>(component);
    if (!datePicker) {
        LOGE("PickerDateComponent is null");
        return;
    }
    datePicker->SetShowLunar(isLunar);
}
void JSDatePicker::UseMilitaryTime(bool isUseMilitaryTime)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto timePicker = AceType::DynamicCast<PickerTimeComponent>(component);
    if (!timePicker) {
        LOGE("PickerTimeComponent is null");
        return;
    }
    timePicker->SetHour24(isUseMilitaryTime);
}

void JSDatePicker::OnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("info[0] is not a function.");
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto datePicker = AceType::DynamicCast<PickerBaseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    auto onChangeId =
        EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "year", "month", "day", "hour", "minute", "second" };
            func->Execute(keys, info);
        });
    if (datePicker) {
        datePicker->SetOnChange(onChangeId);
    }
}

PickerDate JSDatePicker::ParseDate(const JSRef<JSVal>& dateVal)
{
    auto pickerDate = PickerDate();
    if (!dateVal->IsObject()) {
        return pickerDate;
    }
    auto dateObj = JSRef<JSObject>::Cast(dateVal);
    auto yearFunc = JSRef<JSFunc>::Cast(dateObj->GetProperty("getFullYear"));
    auto monthFunc = JSRef<JSFunc>::Cast(dateObj->GetProperty("getMonth"));
    auto dateFunc = JSRef<JSFunc>::Cast(dateObj->GetProperty("getDate"));
    JSRef<JSVal> year = yearFunc->Call(dateObj);
    JSRef<JSVal> month = monthFunc->Call(dateObj);
    JSRef<JSVal> date = dateFunc->Call(dateObj);

    if (year->IsNumber() && month->IsNumber() && date->IsNumber()) {
        pickerDate.SetYear(year->ToNumber<int32_t>());
        pickerDate.SetMonth(month->ToNumber<int32_t>() + 1); // 0-11 means 1 to 12 months
        pickerDate.SetDay(date->ToNumber<int32_t>());
    }
    return pickerDate;
}

PickerTime JSDatePicker::ParseTime(const JSRef<JSVal>& timeVal)
{
    auto pickerTime = PickerTime();
    if (!timeVal->IsObject()) {
        return pickerTime;
    }
    auto timeObj = JSRef<JSObject>::Cast(timeVal);
    auto hourFunc = JSRef<JSFunc>::Cast(timeObj->GetProperty("getHours"));
    auto minuteFunc = JSRef<JSFunc>::Cast(timeObj->GetProperty("getMinutes"));
    auto secondFunc = JSRef<JSFunc>::Cast(timeObj->GetProperty("getSeconds"));
    JSRef<JSVal> hour = hourFunc->Call(timeObj);
    JSRef<JSVal> minute = minuteFunc->Call(timeObj);
    JSRef<JSVal> second = secondFunc->Call(timeObj);

    if (hour->IsNumber() && minute->IsNumber() && second->IsNumber()) {
        pickerTime.SetHour(hour->ToNumber<int32_t>());
        pickerTime.SetMinute(minute->ToNumber<int32_t>());
        pickerTime.SetSecond(second->ToNumber<int32_t>());
    }
    return pickerTime;
}

void JSDatePicker::CreateDatePicker(const JSRef<JSObject>& paramObj)
{
    auto datePicker = AceType::MakeRefPtr<PickerDateComponent>();
    auto startDate = paramObj->GetProperty("start");
    auto endDate = paramObj->GetProperty("end");
    auto selectedDate = paramObj->GetProperty("selected");
    if (startDate->IsObject()) {
        datePicker->SetStartDate(ParseDate(startDate));
    }
    if (endDate->IsObject()) {
        datePicker->SetEndDate(ParseDate(endDate));
    }
    if (selectedDate->IsObject()) {
        datePicker->SetSelectedDate(ParseDate(selectedDate));
    }

    datePicker->SetIsDialog(false);
    datePicker->SetHasButtons(false);

    auto theme = GetTheme<PickerTheme>();
    if (!theme) {
        LOGE("datePicker Theme is null");
        return;
    }

    datePicker->SetTheme(theme);
    ViewStackProcessor::GetInstance()->Push(datePicker);
}

void JSDatePicker::CreateTimePicker(const JSRef<JSObject>& paramObj)
{
    auto timePicker = AceType::MakeRefPtr<PickerTimeComponent>();
    auto selectedTime = paramObj->GetProperty("selected");
    if (selectedTime->IsObject()) {
        timePicker->SetSelectedTime(ParseTime(selectedTime));
    }
    timePicker->SetIsDialog(false);
    timePicker->SetHasButtons(false);

    auto theme = GetTheme<PickerTheme>();
    if (!theme) {
        LOGE("timePicker Theme is null");
        return;
    }

    timePicker->SetTheme(theme);
    ViewStackProcessor::GetInstance()->Push(timePicker);
}

void JSDatePickerDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSDatePickerDialog>::Declare("DatePickerDialog");
    JSClass<JSDatePickerDialog>::StaticMethod("show", &JSDatePickerDialog::Show);

    JSClass<JSDatePickerDialog>::Bind<>(globalObj);
}

void JSDatePickerDialog::Show(const JSCallbackInfo& info)
{
    if (info.Length() < 2 || !info[0]->IsObject() || !info[1]->IsFunction()) {
        LOGE("DatePicker Show dialog error, info is non-valid");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    DatePickerType pickerType = DatePickerType::TIME;
    auto type = paramObject->GetProperty("type");
    if (type->IsNumber()) {
        pickerType = static_cast<DatePickerType>(type->ToNumber<int32_t>());
    }

    RefPtr<Component> component;
    switch (pickerType) {
        case DatePickerType::TIME: {
            CreateTimePicker(component, paramObject);
            break;
        }
        case DatePickerType::DATE: {
            CreateDatePicker(component, paramObject);
            break;
        }
        default: {
            LOGE("Undefined date picker type.");
            return;
        }
    }

    auto datePicker = AceType::DynamicCast<PickerBaseComponent>(component);
    DialogProperties properties {};
    properties.alignment = DialogAlignment::CENTER;
    properties.customComponent = datePicker;

    if (info[1]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
        auto resultId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                std::vector<std::string> keys = { "year", "month", "day", "hour", "minute", "second", "status"};
                func->Execute(keys, info);
            });
        datePicker->SetDialogResult(resultId);
    }

    datePicker->OpenDialog(properties);
}

void JSDatePickerDialog::CreateDatePicker(RefPtr<Component> &component, const JSRef<JSObject>& paramObj)
{
    auto datePicker = AceType::MakeRefPtr<PickerDateComponent>();
    auto startDate = paramObj->GetProperty("start");
    auto endDate = paramObj->GetProperty("end");
    auto selectedDate = paramObj->GetProperty("selected");
    auto lunar = paramObj->GetProperty("lunar");
    bool isLunar = lunar->ToBoolean();
    if (startDate->IsObject()) {
        datePicker->SetStartDate(ParseDate(startDate));
    }
    if (endDate->IsObject()) {
        datePicker->SetEndDate(ParseDate(endDate));
    }
    if (selectedDate->IsObject()) {
        datePicker->SetSelectedDate(ParseDate(selectedDate));
    }
    datePicker->SetIsDialog(false);
    datePicker->SetIsCreateDialogComponent(true);
    datePicker->SetShowLunar(isLunar);
    component = datePicker;
}

void JSDatePickerDialog::CreateTimePicker(RefPtr<Component> &component, const JSRef<JSObject>& paramObj)
{
    auto timePicker = AceType::MakeRefPtr<PickerTimeComponent>();
    auto selectedTime = paramObj->GetProperty("selected");
    auto useMilitaryTime = paramObj->GetProperty("useMilitaryTime");
    bool isUseMilitaryTime = useMilitaryTime->ToBoolean();
    if (selectedTime->IsObject()) {
        timePicker->SetSelectedTime(ParseTime(selectedTime));
    }
    timePicker->SetIsDialog(false);
    timePicker->SetIsCreateDialogComponent(true);
    timePicker->SetHour24(isUseMilitaryTime);
    component = timePicker;
}

PickerDate JSDatePickerDialog::ParseDate(const JSRef<JSVal>& dateVal)
{
    auto pickerDate = PickerDate();
    if (!dateVal->IsObject()) {
        return pickerDate;
    }
    auto dateObj = JSRef<JSObject>::Cast(dateVal);
    auto yearFunc = JSRef<JSFunc>::Cast(dateObj->GetProperty("getFullYear"));
    auto monthFunc = JSRef<JSFunc>::Cast(dateObj->GetProperty("getMonth"));
    auto dateFunc = JSRef<JSFunc>::Cast(dateObj->GetProperty("getDate"));
    JSRef<JSVal> year = yearFunc->Call(dateObj);
    JSRef<JSVal> month = monthFunc->Call(dateObj);
    JSRef<JSVal> date = dateFunc->Call(dateObj);

    if (year->IsNumber() && month->IsNumber() && date->IsNumber()) {
        pickerDate.SetYear(year->ToNumber<int32_t>());
        pickerDate.SetMonth(month->ToNumber<int32_t>() + 1); // 0-11 means 1 to 12 months
        pickerDate.SetDay(date->ToNumber<int32_t>());
    }
    return pickerDate;
}

PickerTime JSDatePickerDialog::ParseTime(const JSRef<JSVal>& timeVal)
{
    auto pickerTime = PickerTime();
    if (!timeVal->IsObject()) {
        return pickerTime;
    }
    auto timeObj = JSRef<JSObject>::Cast(timeVal);
    auto hourFunc = JSRef<JSFunc>::Cast(timeObj->GetProperty("getHours"));
    auto minuteFunc = JSRef<JSFunc>::Cast(timeObj->GetProperty("getMinutes"));
    auto secondFunc = JSRef<JSFunc>::Cast(timeObj->GetProperty("getSeconds"));
    JSRef<JSVal> hour = hourFunc->Call(timeObj);
    JSRef<JSVal> minute = minuteFunc->Call(timeObj);
    JSRef<JSVal> second = secondFunc->Call(timeObj);

    if (hour->IsNumber() && minute->IsNumber() && second->IsNumber()) {
        pickerTime.SetHour(hour->ToNumber<int32_t>());
        pickerTime.SetMinute(minute->ToNumber<int32_t>());
        pickerTime.SetSecond(second->ToNumber<int32_t>());
    }
    return pickerTime;
}
} // namespace OHOS::Ace::Framework
