/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_calendar.h"

#include <cstdint>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/calendar_model_impl.h"

namespace OHOS::Ace {
std::unique_ptr<CalendarModel> CalendarModel::instance_ = nullptr;
std::once_flag CalendarModel::onceFlag_;

CalendarModel* CalendarModel::GetInstance()
{
    std::call_once(onceFlag_, []() {
#ifdef NG_BUILD
        instance_.reset(new NG::CalendarModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::CalendarModelNG());
        } else {
            instance_.reset(new Framework::CalendarModelImpl());
        }
#endif
    });

    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t CALENDAR_INVALID = -1;
} // namespace

void JSCalendar::JSBind(BindingTarget globalObj)
{
    JSClass<JSCalendar>::Declare("Calendar");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCalendar>::StaticMethod("create", &JSCalendar::Create, opt);
    JSClass<JSCalendar>::StaticMethod("showLunar", &JSCalendar::SetShowLunar, opt);
    JSClass<JSCalendar>::StaticMethod("showHoliday", &JSCalendar::SetShowHoliday, opt);
    JSClass<JSCalendar>::StaticMethod("needSlide", &JSCalendar::SetNeedSlide, opt);
    JSClass<JSCalendar>::StaticMethod("startOfWeek", &JSCalendar::SetStartOfWeek, opt);
    JSClass<JSCalendar>::StaticMethod("offDays", &JSCalendar::SetOffDays, opt);
    JSClass<JSCalendar>::StaticMethod("onSelectChange", &JSCalendar::JsOnSelectedChange, opt);
    JSClass<JSCalendar>::StaticMethod("onRequestData", &JSCalendar::JsOnRequestData, opt);
    JSClass<JSCalendar>::StaticMethod("direction", &JSCalendar::SetDirection, opt);
    JSClass<JSCalendar>::StaticMethod("currentDayStyle", &JSCalendar::SetCurrentDayStyle, opt);
    JSClass<JSCalendar>::StaticMethod("nonCurrentDayStyle", &JSCalendar::SetNonCurrentDayStyle, opt);
    JSClass<JSCalendar>::StaticMethod("todayStyle", &JSCalendar::SetTodayStyle, opt);
    JSClass<JSCalendar>::StaticMethod("weekStyle", &JSCalendar::SetWeekStyle, opt);
    JSClass<JSCalendar>::StaticMethod("workStateStyle", &JSCalendar::SetWorkStateStyle, opt);
    JSClass<JSCalendar>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSCalendar::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto dataJsVal = obj->GetProperty("date");
    auto currentDataJsVal = obj->GetProperty("currentData");
    auto preDataJsVal = obj->GetProperty("preData");
    auto nextDataJsVal = obj->GetProperty("nextData");
    if (!(dataJsVal->IsObject() && currentDataJsVal->IsObject() && preDataJsVal->IsObject() &&
        nextDataJsVal->IsObject())) {
        return;
    }
    auto date = JSRef<JSObject>::Cast(dataJsVal);
    auto currentData = JSRef<JSObject>::Cast(currentDataJsVal);
    auto preData = JSRef<JSObject>::Cast(preDataJsVal);
    auto nextData = JSRef<JSObject>::Cast(nextDataJsVal);
    auto controllerObj = obj->GetProperty("controller");
    auto yearValue = date->GetProperty("year");
    auto monthValue = date->GetProperty("month");
    auto dayValue = date->GetProperty("day");
    if (!yearValue->IsNumber() || !monthValue->IsNumber() || !dayValue->IsNumber()) {
        return;
    }
    CalendarDay day;
    day.month.year = yearValue->ToNumber<int32_t>();
    day.month.month = monthValue->ToNumber<int32_t>();
    day.day = dayValue->ToNumber<int32_t>();
    CalendarModelData calendarData;
    calendarData.date = day;
    ObtainedMonth currentMonthData = GetCurrentData(currentData);
    ObtainedMonth preMonthData = GetPreData(preData);
    ObtainedMonth nextMonthData = GetNextData(nextData);
    calendarData.currentData = currentMonthData;
    calendarData.preData = preMonthData;
    calendarData.nextData = nextMonthData;
    if (controllerObj->IsObject()) {
        auto jsCalendarController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSCalendarController>();
        if (jsCalendarController) {
            jsCalendarController->SetInstanceId(Container::CurrentId());
            calendarData.controller = jsCalendarController->GetController();
        }
    }
    CalendarModel::GetInstance()->Create(calendarData);
}

void JSCalendar::SetCalendarData(
    const JSRef<JSObject>& obj, MonthState monthState, const RefPtr<CalendarComponentV2>& component)
{
    CHECK_NULL_VOID(component);

#if defined(PREVIEW)
    if (obj->IsUndefined()) {
        return;
    }
#endif

    component->SetCalendarData(GetCalendarData(obj, monthState));
}

ObtainedMonth JSCalendar::GetCalendarData(const JSRef<JSObject>& obj, MonthState monthState)
{
#if defined(PREVIEW)
    if (obj->IsUndefined()) {
        return ObtainedMonth();
    }
#endif

    auto yearValue = obj->GetProperty("year");
    auto monthValue = obj->GetProperty("month");
    auto arrayValue = obj->GetProperty("data");
    if (!yearValue->IsNumber() || !monthValue->IsNumber() || !arrayValue->IsArray()) {
        return ObtainedMonth();
    }
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = yearValue->ToNumber<int32_t>();
    obtainedMonth.month = monthValue->ToNumber<int32_t>();
    std::vector<CalendarDay> days;
    JSRef<JSArray> dataArray = JSRef<JSArray>::Cast(arrayValue);
    size_t length = dataArray->Length();
    for (size_t i = 0; i < length; ++i) {
        CalendarDay day;
        JSRef<JSVal> item = dataArray->GetValueAt(i);
        if (!item->IsObject()) {
            days.emplace_back(std::move(day));
            continue;
        }
        JSRef<JSObject> itemObj = JSRef<JSObject>::Cast(item);
        day.index = itemObj->GetPropertyValue<int32_t>("index", 0);
        day.lunarMonth = itemObj->GetPropertyValue<std::string>("lunarMonth", "");
        day.lunarDay = itemObj->GetPropertyValue<std::string>("lunarDay", "");
        day.dayMark = itemObj->GetPropertyValue<std::string>("dayMark", "");
        day.dayMarkValue = itemObj->GetPropertyValue<std::string>("dayMarkValue", "");
        day.month.year = itemObj->GetPropertyValue<int32_t>("year", 0);
        day.month.month = itemObj->GetPropertyValue<int32_t>("month", 0);
        day.day = itemObj->GetPropertyValue<int32_t>("day", 0);
        if (day.day == 1 && obtainedMonth.firstDayIndex == CALENDAR_INVALID) {
            obtainedMonth.firstDayIndex = day.index;
        }
        day.isFirstOfLunar = itemObj->GetPropertyValue<bool>("isFirstOfLunar", false);
        day.hasSchedule = itemObj->GetPropertyValue<bool>("hasSchedule", false);
        day.markLunarDay = itemObj->GetPropertyValue<bool>("markLunarDay", false);
        days.emplace_back(std::move(day));
    }
    obtainedMonth.days = days;
    return obtainedMonth;
}

void JSCalendar::SetCardCalendar(bool cardCalendar)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetCardCalendar(cardCalendar);
}

void JSCalendar::SetDate(const JSRef<JSObject>& obj, const RefPtr<CalendarComponentV2>& component)
{
    if (component) {
        auto yearValue = obj->GetProperty("year");
        auto monthValue = obj->GetProperty("month");
        auto dayValue = obj->GetProperty("day");
        if (!yearValue->IsNumber() || !monthValue->IsNumber() || !dayValue->IsNumber()) {
            return;
        }
        CalendarDay day;
        day.month.year = yearValue->ToNumber<int32_t>();
        day.month.month = monthValue->ToNumber<int32_t>();
        day.day = dayValue->ToNumber<int32_t>();
        component->SetCalendarDate(day);
    }
}

void JSCalendar::SetHolidays(const std::string& holidays)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetHolidays(holidays);
}

void JSCalendar::SetOffDays(int32_t offDays)
{
    uint32_t bit = 0b1;
    std::string result;
    const static int32_t dayOfWeek = 7;
    for (auto i = 0; i < dayOfWeek; ++i) {
        if (bit & static_cast<uint32_t>(offDays)) {
            result += std::to_string(i);
            result += ",";
        }
        bit <<= 1;
    }

    CalendarModel::GetInstance()->SetOffDays(result);
}

void JSCalendar::SetShowHoliday(const JSCallbackInfo& info)
{
    bool showHoliday = true;
    if (info[0]->IsBoolean()) {
        showHoliday = info[0]->ToBoolean();
    }
    CalendarModel::GetInstance()->SetShowHoliday(showHoliday);
}

void JSCalendar::SetShowLunar(const JSCallbackInfo& info)
{
    bool showLunar = false;
    if (info[0]->IsBoolean()) {
        showLunar = info[0]->ToBoolean();
    }
    CalendarModel::GetInstance()->SetShowLunar(showLunar);
}

void JSCalendar::SetStartOfWeek(const JSCallbackInfo& info)
{
    if (info[0]->IsNumber()) {
        auto startOfWeek = info[0]->ToNumber<int32_t>();
        CalendarModel::GetInstance()->SetStartOfWeek(startOfWeek);
    }
}

void JSCalendar::SetNeedSlide(const JSCallbackInfo& info)
{
    bool needSlide = false;
    if (info[0]->IsBoolean()) {
        needSlide = info[0]->ToBoolean();
    }
    CalendarModel::GetInstance()->SetNeedSlide(needSlide);
}

void JSCalendar::SetWorkDays(const std::string& workDays)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetWorkDays(workDays);
}

RefPtr<CalendarComponentV2> JSCalendar::GetComponent()
{
    auto stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<CalendarComponentV2>(stack->GetMainComponent());
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        component->SetTextDirection(TextDirection::RTL);
    }
    return component;
}

void JSCalendar::JsOnSelectedChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    if (info[0]->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto selectedChangeFuc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto selectedChange = [execCtx = info.GetExecutionContext(), func = std::move(selectedChangeFuc),
                                  node = frameNode](const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "year", "month", "day" };
            ACE_SCORING_EVENT("Calendar.onSelectedChange");
            PipelineContext::SetCallBackNode(node);
            func->Execute(keys, info);
        };
        CalendarModel::GetInstance()->SetSelectedChangeEvent(std::move(selectedChange));
    }
}

void JSCalendar::JsOnRequestData(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto requestDataFuc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto requestData = [execCtx = info.GetExecutionContext(), func = std::move(requestDataFuc), node = frameNode](
                           const std::string& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Calendar.onRequestData");
        std::vector<std::string> keys = { "year", "month", "currentMonth", "currentYear", "monthState" };
        PipelineContext::SetCallBackNode(node);
        func->Execute(keys, info);
    };
    CalendarModel::GetInstance()->SetOnRequestDataEvent(std::move(requestData));
}

void JSCalendar::SetCurrentData(const JSRef<JSObject>& obj, const RefPtr<CalendarComponentV2>& component)
{
    SetCalendarData(obj, MonthState::CUR_MONTH, component);
}

ObtainedMonth JSCalendar::GetCurrentData(const JSRef<JSObject>& obj)
{
    return GetCalendarData(obj, MonthState::CUR_MONTH);
}

void JSCalendar::SetPreData(const JSRef<JSObject>& obj, const RefPtr<CalendarComponentV2>& component)
{
    SetCalendarData(obj, MonthState::PRE_MONTH, component);
}

ObtainedMonth JSCalendar::GetPreData(const JSRef<JSObject>& obj)
{
    return GetCalendarData(obj, MonthState::PRE_MONTH);
}

void JSCalendar::SetNextData(const JSRef<JSObject>& obj, const RefPtr<CalendarComponentV2>& component)
{
    SetCalendarData(obj, MonthState::NEXT_MONTH, component);
}

ObtainedMonth JSCalendar::GetNextData(const JSRef<JSObject>& obj)
{
    return GetCalendarData(obj, MonthState::NEXT_MONTH);
}

void JSCalendar::SetDirection(const JSCallbackInfo& info)
{
    if (info[0]->IsNumber()) {
        auto dir = info[0]->ToNumber<int32_t>();
        CalendarModel::GetInstance()->SetDirection(dir);
    }
}

void JSCalendar::SetCurrentDayStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    CurrentDayStyleData currentDayStyleData;
    Color dayColor;
    if (ConvertFromJSValue(obj->GetProperty("dayColor"), dayColor)) {
        currentDayStyleData.dayColor = dayColor;
    }
    Color lunarColor;
    if (ConvertFromJSValue(obj->GetProperty("lunarColor"), lunarColor)) {
        currentDayStyleData.lunarColor = lunarColor;
    }
    Color markLunarColor;
    if (ConvertFromJSValue(obj->GetProperty("markLunarColor"), markLunarColor)) {
        currentDayStyleData.markLunarColor = markLunarColor;
    }
    CalcDimension dayFontSize;
    if (ParseJsDimensionFp(obj->GetProperty("dayFontSize"), dayFontSize)) {
        currentDayStyleData.dayFontSize = dayFontSize;
    }
    CalcDimension lunarDayFontSize;
    if (ParseJsDimensionFp(obj->GetProperty("lunarDayFontSize"), lunarDayFontSize)) {
        currentDayStyleData.lunarDayFontSize = lunarDayFontSize;
    }
    CalcDimension dayHeight;
    if (ParseJsDimensionFp(obj->GetProperty("dayHeight"), dayHeight)) {
        currentDayStyleData.dayHeight = dayHeight;
    }
    CalcDimension dayWidth;
    if (ParseJsDimensionFp(obj->GetProperty("dayWidth"), dayWidth)) {
        currentDayStyleData.dayWidth = dayWidth;
    }
    CalcDimension gregorianCalendarHeight;
    if (ParseJsDimensionFp(obj->GetProperty("gregorianCalendarHeight"), gregorianCalendarHeight)) {
        currentDayStyleData.gregorianCalendarHeight = gregorianCalendarHeight;
    }
    CalcDimension lunarHeight;
    if (ParseJsDimensionFp(obj->GetProperty("lunarHeight"), lunarHeight)) {
        currentDayStyleData.lunarHeight = lunarHeight;
    }
    CalcDimension dayYAxisOffset;
    if (ParseJsDimensionFp(obj->GetProperty("dayYAxisOffset"), dayYAxisOffset)) {
        currentDayStyleData.dayYAxisOffset = dayYAxisOffset;
    }
    CalcDimension lunarDayYAxisOffset;
    if (ParseJsDimensionFp(obj->GetProperty("lunarDayYAxisOffset"), lunarDayYAxisOffset)) {
        currentDayStyleData.lunarDayYAxisOffset = lunarDayYAxisOffset;
    }
    CalcDimension underscoreXAxisOffset;
    if (ParseJsDimensionFp(obj->GetProperty("underscoreXAxisOffset"), underscoreXAxisOffset)) {
        currentDayStyleData.underscoreXAxisOffset = underscoreXAxisOffset;
    }
    CalcDimension underscoreYAxisOffset;
    if (ParseJsDimensionFp(obj->GetProperty("underscoreYAxisOffset"), underscoreYAxisOffset)) {
        currentDayStyleData.underscoreYAxisOffset = underscoreYAxisOffset;
    }
    CalcDimension scheduleMarkerXAxisOffset;
    if (ParseJsDimensionFp(obj->GetProperty("scheduleMarkerXAxisOffset"), scheduleMarkerXAxisOffset)) {
        currentDayStyleData.scheduleMarkerXAxisOffset = scheduleMarkerXAxisOffset;
    }
    CalcDimension scheduleMarkerYAxisOffset;
    if (ParseJsDimensionFp(obj->GetProperty("scheduleMarkerYAxisOffset"), scheduleMarkerYAxisOffset)) {
        currentDayStyleData.scheduleMarkerYAxisOffset = scheduleMarkerYAxisOffset;
    }
    CalcDimension colSpace;
    if (ParseJsDimensionFp(obj->GetProperty("colSpace"), colSpace)) {
        currentDayStyleData.colSpace = colSpace;
    }
    CalcDimension dailyFiveRowSpace;
    if (ParseJsDimensionFp(obj->GetProperty("dailyFiveRowSpace"), dailyFiveRowSpace)) {
        currentDayStyleData.dailyFiveRowSpace = dailyFiveRowSpace;
    }
    CalcDimension dailySixRowSpace;
    if (ParseJsDimensionFp(obj->GetProperty("dailySixRowSpace"), dailySixRowSpace)) {
        currentDayStyleData.dailySixRowSpace = dailySixRowSpace;
    }
    CalcDimension underscoreWidth;
    if (ParseJsDimensionFp(obj->GetProperty("underscoreWidth"), underscoreWidth)) {
        currentDayStyleData.underscoreWidth = underscoreWidth;
    }
    CalcDimension underscoreLength;
    if (ParseJsDimensionFp(obj->GetProperty("underscoreLength"), underscoreLength)) {
        currentDayStyleData.underscoreLength = underscoreLength;
    }
    CalcDimension scheduleMarkerRadius;
    if (ParseJsDimensionFp(obj->GetProperty("scheduleMarkerRadius"), scheduleMarkerRadius)) {
        currentDayStyleData.scheduleMarkerRadius = scheduleMarkerRadius;
    }
    CalcDimension boundaryRowOffset;
    if (ParseJsDimensionFp(obj->GetProperty("boundaryRowOffset"), boundaryRowOffset)) {
        currentDayStyleData.boundaryRowOffset = boundaryRowOffset;
    }
    CalcDimension boundaryColOffset;
    if (ParseJsDimensionFp(obj->GetProperty("boundaryColOffset"), boundaryColOffset)) {
        currentDayStyleData.boundaryColOffset = boundaryColOffset;
    }

    CurrentDayStyleData CurrentDayStyleDataImpl;
    ConvertFromJSValue(obj->GetProperty("dayColor"), CurrentDayStyleDataImpl.dayColor);
    ConvertFromJSValue(obj->GetProperty("lunarColor"), CurrentDayStyleDataImpl.lunarColor);
    ConvertFromJSValue(obj->GetProperty("markLunarColor"), CurrentDayStyleDataImpl.markLunarColor);
    CalcDimension dayFontSize_impl;
    if (ParseJsDimensionFp(obj->GetProperty("dayFontSize"), dayFontSize_impl)) {
        CurrentDayStyleDataImpl.dayFontSize = dayFontSize_impl;
    }
    CalcDimension lunarDayFontSize_impl;
    if (ParseJsDimensionFp(obj->GetProperty("lunarDayFontSize"), lunarDayFontSize_impl)) {
        CurrentDayStyleDataImpl.lunarDayFontSize = lunarDayFontSize_impl;
    }
    ConvertFromJSValue(obj->GetProperty("dayHeight"), CurrentDayStyleDataImpl.dayHeight);
    ConvertFromJSValue(obj->GetProperty("dayWidth"), CurrentDayStyleDataImpl.dayWidth);
    ConvertFromJSValue(obj->GetProperty("gregorianCalendarHeight"), CurrentDayStyleDataImpl.gregorianCalendarHeight);
    ConvertFromJSValue(obj->GetProperty("lunarHeight"), CurrentDayStyleDataImpl.lunarHeight);
    ConvertFromJSValue(obj->GetProperty("dayYAxisOffset"), CurrentDayStyleDataImpl.dayYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("lunarDayYAxisOffset"), CurrentDayStyleDataImpl.lunarDayYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("underscoreXAxisOffset"), CurrentDayStyleDataImpl.underscoreXAxisOffset);
    ConvertFromJSValue(obj->GetProperty("underscoreYAxisOffset"), CurrentDayStyleDataImpl.underscoreYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("scheduleMarkerXAxisOffset"),
        CurrentDayStyleDataImpl.scheduleMarkerXAxisOffset);
    ConvertFromJSValue(obj->GetProperty("scheduleMarkerYAxisOffset"),
        CurrentDayStyleDataImpl.scheduleMarkerYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("colSpace"), CurrentDayStyleDataImpl.colSpace);
    ConvertFromJSValue(obj->GetProperty("dailyFiveRowSpace"), CurrentDayStyleDataImpl.dailyFiveRowSpace);
    ConvertFromJSValue(obj->GetProperty("dailySixRowSpace"), CurrentDayStyleDataImpl.dailySixRowSpace);
    ConvertFromJSValue(obj->GetProperty("underscoreWidth"), CurrentDayStyleDataImpl.underscoreWidth);
    ConvertFromJSValue(obj->GetProperty("underscoreLength"), CurrentDayStyleDataImpl.underscoreLength);
    ConvertFromJSValue(obj->GetProperty("scheduleMarkerRadius"), CurrentDayStyleDataImpl.scheduleMarkerRadius);
    ConvertFromJSValue(obj->GetProperty("boundaryRowOffset"), CurrentDayStyleDataImpl.boundaryRowOffset);
    ConvertFromJSValue(obj->GetProperty("boundaryColOffset"), CurrentDayStyleDataImpl.boundaryColOffset);
    ConvertFromJSValue(obj->GetProperty("touchCircleStrokeWidth"), CurrentDayStyleDataImpl.touchCircleStrokeWidth);

    CalendarModel::GetInstance()->SetCurrentDayStyle(currentDayStyleData, CurrentDayStyleDataImpl);
}

void JSCalendar::SetNonCurrentDayStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    NonCurrentDayStyleData nonCurrentDayStyleData;
    Color nonCurrentMonthDayColor;
    if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthDayColor"), nonCurrentMonthDayColor)) {
        nonCurrentDayStyleData.nonCurrentMonthDayColor = nonCurrentMonthDayColor;
    }
    Color nonCurrentMonthLunarColor;
    if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthLunarColor"), nonCurrentMonthLunarColor)) {
        nonCurrentDayStyleData.nonCurrentMonthLunarColor = nonCurrentMonthLunarColor;
    }
    Color nonCurrentMonthWorkDayMarkColor;
    if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthWorkDayMarkColor"), nonCurrentMonthWorkDayMarkColor)) {
        nonCurrentDayStyleData.nonCurrentMonthWorkDayMarkColor = nonCurrentMonthWorkDayMarkColor;
    }
    Color nonCurrentMonthOffDayMarkColor;
    if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthOffDayMarkColor"), nonCurrentMonthOffDayMarkColor)) {
        nonCurrentDayStyleData.nonCurrentMonthOffDayMarkColor = nonCurrentMonthOffDayMarkColor;
    }
    CalendarModel::GetInstance()->SetNonCurrentDayStyle(nonCurrentDayStyleData);
}

void JSCalendar::SetTodayStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    TodayStyleData todayStyle;
    Color focusedDayColor;
    if (ConvertFromJSValue(obj->GetProperty("focusedDayColor"), focusedDayColor)) {
        todayStyle.focusedDayColor = focusedDayColor;
    }
    Color focusedLunarColor;
    if (ConvertFromJSValue(obj->GetProperty("focusedLunarColor"), focusedLunarColor)) {
        todayStyle.focusedLunarColor = focusedLunarColor;
    }
    Color focusedAreaBackgroundColor;
    if (ConvertFromJSValue(obj->GetProperty("focusedAreaBackgroundColor"), focusedAreaBackgroundColor)) {
        todayStyle.focusedAreaBackgroundColor = focusedAreaBackgroundColor;
    }
    CalcDimension focusedAreaRadius;
    if (ConvertFromJSValue(obj->GetProperty("focusedAreaRadius"), focusedAreaRadius)) {
        todayStyle.focusedAreaRadius = focusedAreaRadius;
    }
    CalendarModel::GetInstance()->SetTodayStyle(todayStyle);
}

void JSCalendar::SetWeekStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    WeekStyleData weekStyle;
    Color weekColor;
    if (ConvertFromJSValue(obj->GetProperty("weekColor"), weekColor)) {
        weekStyle.weekColor = weekColor;
    }
    Color weekendDayColor;
    if (ConvertFromJSValue(obj->GetProperty("weekendDayColor"), weekendDayColor)) {
        weekStyle.weekendDayColor = weekendDayColor;
    }
    Color weekendLunarColor;
    if (ConvertFromJSValue(obj->GetProperty("weekendLunarColor"), weekendLunarColor)) {
        weekStyle.weekendLunarColor = weekendLunarColor;
    }
    CalcDimension weekFontSize;
    if (ParseJsDimensionFp(obj->GetProperty("weekFontSize"), weekFontSize)) {
        weekStyle.weekFontSize = weekFontSize;
    }
    CalcDimension weekHeight;
    if (ConvertFromJSValue(obj->GetProperty("weekHeight"), weekHeight)) {
        weekStyle.weekHeight = weekHeight;
    }
    CalcDimension weekWidth;
    if (ConvertFromJSValue(obj->GetProperty("weekWidth"), weekWidth)) {
        weekStyle.weekWidth = weekWidth;
    }
    CalcDimension weekAndDayRowSpace;
    if (ConvertFromJSValue(obj->GetProperty("weekAndDayRowSpace"), weekAndDayRowSpace)) {
        weekStyle.weekAndDayRowSpace = weekAndDayRowSpace;
    }
    CalendarModel::GetInstance()->SetWeekStyle(weekStyle);
}

void JSCalendar::SetWorkStateStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    WorkStateStyleData workStateStyle;
    Color workDayMarkColor;
    if (ConvertFromJSValue(obj->GetProperty("workDayMarkColor"), workDayMarkColor)) {
        workStateStyle.workDayMarkColor = workDayMarkColor;
    }
    Color offDayMarkColor;
    if (ConvertFromJSValue(obj->GetProperty("offDayMarkColor"), offDayMarkColor)) {
        workStateStyle.offDayMarkColor = offDayMarkColor;
    }
    CalcDimension workDayMarkSize;
    if (ConvertFromJSValue(obj->GetProperty("workDayMarkSize"), workDayMarkSize)) {
        workStateStyle.workDayMarkSize = workDayMarkSize;
    }
    CalcDimension offDayMarkSize;
    if (ConvertFromJSValue(obj->GetProperty("offDayMarkSize"), offDayMarkSize)) {
        workStateStyle.offDayMarkSize = offDayMarkSize;
    }
    CalcDimension workStateWidth;
    if (ConvertFromJSValue(obj->GetProperty("workStateWidth"), workStateWidth)) {
        workStateStyle.workStateWidth = workStateWidth;
    }
    CalcDimension workStateHorizontalMovingDistance;
    if (ConvertFromJSValue(
        obj->GetProperty("workStateHorizontalMovingDistance"), workStateHorizontalMovingDistance)) {
        workStateStyle.workStateHorizontalMovingDistance = workStateHorizontalMovingDistance;
    }
    CalcDimension workStateVerticalMovingDistance;
    if (ConvertFromJSValue(obj->GetProperty("workStateVerticalMovingDistance"), workStateVerticalMovingDistance)) {
        workStateStyle.workStateVerticalMovingDistance = workStateVerticalMovingDistance;
    }
    CalendarModel::GetInstance()->SetWorkStateStyle(workStateStyle);
}
} // namespace OHOS::Ace::Framework
