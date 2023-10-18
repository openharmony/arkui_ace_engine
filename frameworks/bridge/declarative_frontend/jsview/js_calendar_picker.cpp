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

#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_picker.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/date_util.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/calendar_picker_model_impl.h"
#include "core/components/calendar/calendar_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
std::unique_ptr<CalendarPickerModel> CalendarPickerModel::instance_ = nullptr;
std::mutex CalendarPickerModel::mutex_;
CalendarPickerModel* CalendarPickerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CalendarPickerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CalendarPickerModelNG());
            } else {
                instance_.reset(new Framework::CalendarPickerModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
double GetMSByDate(const std::string& date)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return 0.0f;
    }

    std::tm dateTime = { 0 };
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.tm_year = year->GetInt() - 1900; // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.tm_mon = month->GetInt() - 1;
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.tm_mday = day->GetInt();
    }
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local = std::localtime(&now);
    CHECK_NULL_RETURN(local, 0.0f);
    dateTime.tm_hour = local->tm_hour;
    dateTime.tm_min = local->tm_min;
    dateTime.tm_sec = local->tm_sec;
    return Date::GetMilliSecondsByDateTime(dateTime);
}

void JSCalendarPicker::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendarPicker>::Declare("CalendarPicker");
    JSClass<JSCalendarPicker>::StaticMethod("create", &JSCalendarPicker::Create, MethodOptions::NONE);
    JSClass<JSCalendarPicker>::StaticMethod("edgeAlign", &JSCalendarPicker::SetEdgeAlign);
    JSClass<JSCalendarPicker>::StaticMethod("textStyle", &JSCalendarPicker::SetTextStyle);
    JSClass<JSCalendarPicker>::StaticMethod("onChange", &JSCalendarPicker::SetOnChange);
    JSClass<JSCalendarPicker>::StaticMethod("border", &JSCalendarPicker::SetBorder);
    JSClass<JSCalendarPicker>::StaticMethod("padding", &JSCalendarPicker::JsPadding);
    JSClass<JSCalendarPicker>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSCalendarPicker::SetBorder(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(info[0]);
    auto valueWidth = object->GetProperty("width");
    if (!valueWidth->IsUndefined()) {
        ParseBorderWidth(valueWidth);
    }

    // use default value when undefined.
    ParseCalendarPickerBorderColor(object->GetProperty("color"));

    auto valueRadius = object->GetProperty("radius");
    if (!valueRadius->IsUndefined()) {
        ParseBorderRadius(valueRadius);
    }
    // use default value when undefined.
    ParseBorderStyle(object->GetProperty("style"));

    info.ReturnSelf();
}

void JSCalendarPicker::ParseCalendarPickerBorderColor(const JSRef<JSVal>& args)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    if (!args->IsObject() && !args->IsNumber() && !args->IsString()) {
        ViewAbstractModel::GetInstance()->SetBorderColor(theme->GetEntryBorderColor());
    } else {
        JSViewAbstract::ParseBorderColor(args);
    }
}

void JSCalendarPicker::SetEdgeAlign(const JSCallbackInfo& info)
{
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset;
    if (!info[0]->IsNumber()) {
        CalendarPickerModel::GetInstance()->SetEdgeAlign(alignType, offset);
        return;
    }
    alignType = static_cast<NG::CalendarEdgeAlign>(info[0]->ToNumber<int32_t>());

    if (!info[1]->IsObject()) {
        CalendarPickerModel::GetInstance()->SetEdgeAlign(alignType, offset);
        return;
    }
    auto offsetObj = JSRef<JSObject>::Cast(info[1]);
    CalcDimension dx;
    auto dxValue = offsetObj->GetProperty("dx");
    ParseJsDimensionVp(dxValue, dx);
    CalcDimension dy;
    auto dyValue = offsetObj->GetProperty("dy");
    ParseJsDimensionVp(dyValue, dy);
    offset = DimensionOffset(dx, dy);

    CalendarPickerModel::GetInstance()->SetEdgeAlign(alignType, offset);
}

void JSCalendarPicker::SetTextStyle(const JSCallbackInfo& info)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    NG::PickerTextStyle textStyle;
    textStyle.fontSize = calendarTheme->GetEntryFontSize();
    textStyle.textColor = calendarTheme->GetEntryFontColor();
    textStyle.fontWeight = FontWeight::NORMAL;
    if (!info[0]->IsObject()) {
        CalendarPickerModel::GetInstance()->SetTextStyle(textStyle);
        return;
    }
    JSCalendarPicker::ParseTextStyle(info[0], textStyle);
    CalendarPickerModel::GetInstance()->SetTextStyle(textStyle);
}

void JSCalendarPicker::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CalendarPicker.onChange");
        auto dateObj = JSDate::New(GetMSByDate(info));
        func->ExecuteJS(1, &dateObj);
    };
    CalendarPickerModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSCalendarPicker::JsPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding;
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            left = leftDimen;
        }
        CalcDimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            right = rightDimen;
        }
        CalcDimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            top = topDimen;
        }
        CalcDimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            bottom = bottomDimen;
        }
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            padding = SetPaddings(top, bottom, left, right);
            CalendarPickerModel::GetInstance()->SetPadding(padding);
            return;
        }
    }

    CalcDimension length(-1);
    ParseJsDimensionVp(info[0], length);
    if (length.IsNonNegative()) {
        padding.SetEdges(NG::CalcLength(length));
    }
    CalendarPickerModel::GetInstance()->SetPadding(padding);
}

NG::PaddingProperty JSCalendarPicker::SetPaddings(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left =
                NG::CalcLength(left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right =
                NG::CalcLength(right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }

    return paddings;
}

void JSCalendarPicker::ParseSelectedDateObject(const JSCallbackInfo& info, const JSRef<JSObject>& selectedObject)
{
    JSRef<JSVal> changeEventVal = selectedObject->GetProperty("changeEvent");
    if (!changeEventVal->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("DatePicker.SelectedDateTimeChangeEvent");
        auto dateObj = JSDate::New(GetMSByDate(info));
        func->ExecuteJS(1, &dateObj);
    };
    CalendarPickerModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSCalendarPicker::Create(const JSCallbackInfo& info)
{
    NG::CalendarSettingData settingData;
    RefPtr<CalendarTheme> calendarTheme = GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    CalcDimension dayRadius;
    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        if (!ParseJsDimensionVpNG(obj->GetProperty("hintRadius"), dayRadius)) {
            dayRadius = calendarTheme->GetCalendarDayRadius();
        }
        auto selected = obj->GetProperty("selected");
        if (selected->IsObject()) {
            JSRef<JSObject> selectedDateObj = JSRef<JSObject>::Cast(selected);
            JSRef<JSVal> changeEventVal = selectedDateObj->GetProperty("changeEvent");
            if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
                ParseSelectedDateObject(info, selectedDateObj);
                settingData.selectedDate = ParseDate(selectedDateObj->GetProperty("value"));
            } else {
                settingData.selectedDate = ParseDate(selectedDateObj);
            }
        }
    } else {
        dayRadius = calendarTheme->GetCalendarDayRadius();
    }
    settingData.dayRadius = dayRadius;
    CalendarPickerModel::GetInstance()->Create(settingData);
}

void JSCalendarPicker::ParseTextStyle(const JSRef<JSObject>& paramObj, NG::PickerTextStyle& textStyle)
{
    auto fontColor = paramObj->GetProperty("color");
    auto fontStyle = paramObj->GetProperty("font");

    Color color;
    if (ParseJsColor(fontColor, color)) {
        textStyle.textColor = color;
    }

    if (!fontStyle->IsObject()) {
        return;
    }
    JSRef<JSObject> fontObj = JSRef<JSObject>::Cast(fontStyle);
    auto fontSize = fontObj->GetProperty("size");
    auto fontWeight = fontObj->GetProperty("weight");
    if (fontSize->IsNull() || fontSize->IsUndefined()) {
        textStyle.fontSize = Dimension(-1);
    } else {
        CalcDimension size;
        if (!ParseJsDimensionFp(fontSize, size) || size.Unit() == DimensionUnit::PERCENT) {
            textStyle.fontSize = Dimension(-1);
        } else {
            textStyle.fontSize = size;
        }
    }

    if (!fontWeight->IsNull() && !fontWeight->IsUndefined()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        textStyle.fontWeight = ConvertStrToFontWeight(weight);
    }
}

PickerDate JSCalendarPicker::ParseDate(const JSRef<JSVal>& dateVal)
{
    auto pickerDate = PickerDate::Current();
    if (!dateVal->IsObject()) {
        return pickerDate;
    }
    auto dateObj = JSRef<JSObject>::Cast(dateVal);
    auto yearFuncJsVal = dateObj->GetProperty("getFullYear");
    auto monthFuncJsVal = dateObj->GetProperty("getMonth");
    auto dateFuncJsVal = dateObj->GetProperty("getDate");
    if (!(yearFuncJsVal->IsFunction() && monthFuncJsVal->IsFunction() && dateFuncJsVal->IsFunction())) {
        return pickerDate;
    }
    auto yearFunc = JSRef<JSFunc>::Cast(yearFuncJsVal);
    auto monthFunc = JSRef<JSFunc>::Cast(monthFuncJsVal);
    auto dateFunc = JSRef<JSFunc>::Cast(dateFuncJsVal);
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

void JSCalendarPickerDialog::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendarPickerDialog>::Declare("CalendarPickerDialog");
    JSClass<JSCalendarPickerDialog>::StaticMethod("show", &JSCalendarPickerDialog::Show);
    JSClass<JSCalendarPickerDialog>::Bind<>(globalObj);
}

void JSCalendarPickerDialog::Show(const JSCallbackInfo& info)
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    CHECK_NULL_VOID(scopedDelegate);
    if (!info[0]->IsObject()) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto dialogEvent = ChangeDialogEvent(info);
        auto dialogCancelEvent = DialogCancelEvent(info);
        CalendarPickerDialogShow(paramObject, dialogEvent, dialogCancelEvent);
    }
}

std::map<std::string, NG::DialogEvent> JSCalendarPickerDialog::ChangeDialogEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogEvent> dialogEvent;
    if (!info[0]->IsObject()) {
        return dialogEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onChange = paramObject->GetProperty("onChange");
    if (!onChange->IsUndefined() && onChange->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onChange));
        auto changeId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onChange");
            auto dateObj = JSDate::New(GetMSByDate(info));
            func->ExecuteJS(1, &dateObj);
        };
        dialogEvent["changeId"] = changeId;
    }
    auto onAccept = paramObject->GetProperty("onAccept");
    if (!onAccept->IsUndefined() && onAccept->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAccept));
        auto acceptId = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onAccept");
            auto dateObj = JSDate::New(GetMSByDate(info));
            func->ExecuteJS(1, &dateObj);
        };
        dialogEvent["acceptId"] = acceptId;
    }
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> JSCalendarPickerDialog::DialogCancelEvent(const JSCallbackInfo& info)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (!info[0]->IsObject()) {
        return dialogCancelEvent;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto onCancel = paramObject->GetProperty("onCancel");
    if (!onCancel->IsUndefined() && onCancel->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCancel));
        auto cancelId = [execCtx = info.GetExecutionContext(),
            func = std::move(jsFunc)](const GestureEvent& /* info */) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CalendarDialog.onCancel");
            func->Execute();
        };
        dialogCancelEvent["cancelId"] = cancelId;
    }
    return dialogCancelEvent;
}

PickerDate JSCalendarPickerDialog::ParseDate(const JSRef<JSVal>& dateVal)
{
    auto pickerDate = PickerDate();
    if (!dateVal->IsObject()) {
        return pickerDate;
    }
    auto dateObj = JSRef<JSObject>::Cast(dateVal);

    auto yearFuncJsVal = dateObj->GetProperty("getFullYear");
    auto monthFuncJsVal = dateObj->GetProperty("getMonth");
    auto dateFuncJsVal = dateObj->GetProperty("getDate");
    if (!(yearFuncJsVal->IsFunction() && monthFuncJsVal->IsFunction() && dateFuncJsVal->IsFunction())) {
        return pickerDate;
    }
    auto yearFunc = JSRef<JSFunc>::Cast(yearFuncJsVal);
    auto monthFunc = JSRef<JSFunc>::Cast(monthFuncJsVal);
    auto dateFunc = JSRef<JSFunc>::Cast(dateFuncJsVal);
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

void JSCalendarPickerDialog::CalendarPickerDialogShow(const JSRef<JSObject>& paramObj,
    const std::map<std::string, NG::DialogEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(executor);

    auto theme = GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    auto calendarTheme = pipelineContext->GetTheme<CalendarTheme>();
    NG::CalendarSettingData settingData;
    auto selectedDate = paramObj->GetProperty("selected");
    auto parseSelectedDate = ParseDate(selectedDate);

    if (selectedDate->IsObject()) {
        settingData.selectedDate = parseSelectedDate;
    }

    CalcDimension radius;
    if (ParseJsDimensionVpNG(paramObj->GetProperty("hintRadius"), radius)) {
        settingData.dayRadius = radius;
    }

    DialogProperties properties;
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        properties.alignment = DialogAlignment::BOTTOM;
    } else {
        properties.alignment = DialogAlignment::CENTER;
    }
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    NG::BorderRadiusProperty dialogRadius;
    dialogRadius.SetRadius(calendarTheme->GetDialogBorderRadius());
    properties.borderRadius = dialogRadius;

    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowCalendarDialog(properties, settingData, dialogEvent, dialogCancelEvent);
        },
        TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::Framework
