/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"
#include "core/components_ng/pattern/calendar/calendar_month_view.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_calendar_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

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
    JSClass<JSCalendar>::Inherit<JSViewAbstract>();
    JSClass<JSCalendar>::Bind<>(globalObj);
}

void JSCalendar::Create(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto date = JSRef<JSObject>::Cast(obj->GetProperty("date"));
    auto currentData = JSRef<JSObject>::Cast(obj->GetProperty("currentData"));
    auto preData = JSRef<JSObject>::Cast(obj->GetProperty("preData"));
    auto nextData = JSRef<JSObject>::Cast(obj->GetProperty("nextData"));
    auto controllerObj = obj->GetProperty("controller");
    if (Container::IsCurrentUseNewPipeline()) {
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
        NG::CalendarData calendarData;
        calendarData.date = day;
        ObtainedMonth currentMonthData = GetCurrentData(currentData);
        ObtainedMonth preMonthData = GetPreData(preData);
        ObtainedMonth nextMonthData = GetNextData(nextData);
        calendarData.currentData = currentMonthData;
        calendarData.preData = preMonthData;
        calendarData.nextData = nextMonthData;
        if (controllerObj->IsObject()) {
            auto jsCalendarController = JSRef<JSObject>::Cast(controllerObj).Unwrap<JSCalendarController>();
            if (jsCalendarController) {
                auto controller = jsCalendarController->GetControllerNg();
                calendarData.controller = controller;
            }
        }
        NG::CalendarView::Create(calendarData);
        return;
    }

    auto calendarComponent = AceType::MakeRefPtr<OHOS::Ace::CalendarComponentV2>("", "calendar");
    SetDate(date, calendarComponent);
    SetCurrentData(currentData, calendarComponent);
    SetPreData(preData, calendarComponent);
    SetNextData(nextData, calendarComponent);
    if (controllerObj->IsObject()) {
        auto jsCalendarController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSCalendarController>();
        if (jsCalendarController) {
            auto controllerV2 = jsCalendarController->GetController();
            calendarComponent->SetControllerV2(controllerV2);
        }
    }
    auto theme = GetTheme<CalendarTheme>();
    calendarComponent->SetCalendarTheme(theme);
    calendarComponent->SetV2Component(true);
    ViewStackProcessor::GetInstance()->Push(calendarComponent);
}

void JSCalendar::SetCalendarData(
    const JSRef<JSObject>& obj, MonthState monthState, const RefPtr<CalendarComponentV2>& component)
{
    CHECK_NULL_VOID(component);

#if defined(PREVIEW)
    if (obj->IsUndefined()) {
        LOGE("obj is undefined");
        return;
    }
#endif

    auto yearValue = obj->GetProperty("year");
    auto monthValue = obj->GetProperty("month");
    auto arrayValue = obj->GetProperty("data");
    auto data = JsonUtil::ParseJsonString(arrayValue->ToString());
    if (!yearValue->IsNumber() || !monthValue->IsNumber() || !data->IsArray()) {
        return;
    }
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = yearValue->ToNumber<int32_t>();
    obtainedMonth.month = monthValue->ToNumber<int32_t>();
    std::vector<CalendarDay> days;
    auto child = data->GetChild();
    while (child && child->IsValid()) {
        CalendarDay day;
        day.index = child->GetInt("index");
        day.lunarMonth = child->GetString("lunarMonth");
        day.lunarDay = child->GetString("lunarDay");
        day.dayMark = child->GetString("dayMark");
        day.dayMarkValue = child->GetString("dayMarkValue");
        day.month.year = child->GetInt("year");
        day.month.month = child->GetInt("month");
        day.day = child->GetInt("day");
        if (day.day == 1 && obtainedMonth.firstDayIndex == CALENDAR_INVALID) {
            obtainedMonth.firstDayIndex = day.index;
        }
        day.isFirstOfLunar = child->GetBool("isFirstOfLunar");
        day.hasSchedule = child->GetBool("hasSchedule");
        day.markLunarDay = child->GetBool("markLunarDay");
        days.emplace_back(std::move(day));
        child = child->GetNext();
    }
    obtainedMonth.days = days;
    component->SetCalendarData(obtainedMonth);
}

ObtainedMonth JSCalendar::GetCalendarData(const JSRef<JSObject>& obj, MonthState monthState)
{
#if defined(PREVIEW)
    if (obj->IsUndefined()) {
        LOGE("obj is undefined");
        return ObtainedMonth();
    }
#endif

    auto yearValue = obj->GetProperty("year");
    auto monthValue = obj->GetProperty("month");
    auto arrayValue = obj->GetProperty("data");
    auto data = JsonUtil::ParseJsonString(arrayValue->ToString());
    if (!yearValue->IsNumber() || !monthValue->IsNumber() || !data->IsArray()) {
        return ObtainedMonth();
    }
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = yearValue->ToNumber<int32_t>();
    obtainedMonth.month = monthValue->ToNumber<int32_t>();
    std::vector<CalendarDay> days;
    auto child = data->GetChild();
    while (child && child->IsValid()) {
        CalendarDay day;
        day.index = child->GetInt("index");
        day.lunarMonth = child->GetString("lunarMonth");
        day.lunarDay = child->GetString("lunarDay");
        day.dayMark = child->GetString("dayMark");
        day.dayMarkValue = child->GetString("dayMarkValue");
        day.month.year = child->GetInt("year");
        day.month.month = child->GetInt("month");
        day.day = child->GetInt("day");
        if (day.day == 1 && obtainedMonth.firstDayIndex == CALENDAR_INVALID) {
            obtainedMonth.firstDayIndex = day.index;
        }
        day.isFirstOfLunar = child->GetBool("isFirstOfLunar");
        day.hasSchedule = child->GetBool("hasSchedule");
        day.markLunarDay = child->GetBool("markLunarDay");
        days.emplace_back(std::move(day));
        child = child->GetNext();
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
    if (Container::IsCurrentUseNewPipeline()) {
        NG::CalendarView::SetOffDays(result);
        return;
    }
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetOffDays(result);
}

void JSCalendar::SetShowHoliday(const JSCallbackInfo& info)
{
    bool showHoliday = true;
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsBoolean()) {
        showHoliday = info[0]->ToBoolean();
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::CalendarView::SetShowHoliday(showHoliday);
        return;
    }
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetShowHoliday(showHoliday);
}

void JSCalendar::SetShowLunar(const JSCallbackInfo& info)
{
    bool showLunar = false;
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsBoolean()) {
        showLunar = info[0]->ToBoolean();
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::CalendarView::SetShowLunar(showLunar);
        return;
    }
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetShowLunar(showLunar);
}

void JSCalendar::SetStartOfWeek(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsNumber()) {
        auto startOfWeek = info[0]->ToNumber<int32_t>();
        if (Container::IsCurrentUseNewPipeline()) {
            NG::CalendarView::SetStartOfWeek(NG::Week(startOfWeek));
            return;
        }
        auto component = GetComponent();
        CHECK_NULL_VOID(component);

        if (0 <= startOfWeek && startOfWeek < 7) {
            component->SetStartDayOfWeek(startOfWeek);
        }
    }
}

void JSCalendar::SetNeedSlide(const JSCallbackInfo& info)
{
    bool needSlide = false;
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsBoolean()) {
        needSlide = info[0]->ToBoolean();
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::CalendarView::SetNeedSlide(needSlide);
        return;
    }
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetNeedSlide(needSlide);
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
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        auto selectedChangeFuc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto selectedChange = [execCtx = info.GetExecutionContext(), func = std::move(selectedChangeFuc)](
                                  const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            std::vector<std::string> keys = { "year", "month", "day" };
            ACE_SCORING_EVENT("Calendar.onSelectedChange");
            func->Execute(keys, info);
        };
        NG::CalendarView::SetSelectedChangeEvent(selectedChange);
        return;
    }
    auto component = GetComponent();
    if (info[0]->IsFunction() && component) {
        auto selectedChangeFuc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        EventMarker onSelectedChangeId(
            [execCtx = info.GetExecutionContext(), func = std::move(selectedChangeFuc)](const std::string& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                std::vector<std::string> keys = { "year", "month", "day" };
                ACE_SCORING_EVENT("Calendar.onSelectedChange");
                func->Execute(keys, info);
            });
        component->SetSelectedChangeEvent(onSelectedChangeId);
    }
}

void JSCalendar::JsOnRequestData(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        auto requestDataFuc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto requestData = [execCtx = info.GetExecutionContext(), func = std::move(requestDataFuc)](
                               const std::string& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Calendar.onRequestData");
            std::vector<std::string> keys = { "year", "month", "currentMonth", "currentYear", "monthState" };
            func->Execute(keys, info);
        };
        NG::CalendarView::SetOnRequestDataEvent(std::move(requestData));
        return;
    }
    auto component = GetComponent();
    if (info[0]->IsFunction() && component) {
        auto requestDataFuc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        EventMarker onRequestDataId(
            [execCtx = info.GetExecutionContext(), func = std::move(requestDataFuc)](const std::string& info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                std::vector<std::string> keys = { "year", "month", "currentMonth", "currentYear", "monthState" };
                ACE_SCORING_EVENT("Calendar.onRequestData");
                func->Execute(keys, info);
            });
        component->SetRequestDataEvent(onRequestDataId);
    }
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
    if (info.Length() < 1) {
        LOGE("The info is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (info[0]->IsNumber()) {
        auto dir = info[0]->ToNumber<int32_t>();
        if (Container::IsCurrentUseNewPipeline()) {
            NG::CalendarView::SetDirection(Axis(dir));
            return;
        }
        auto component = GetComponent();
        CHECK_NULL_VOID(component);
        if (dir == 0) {
            component->SetAxis(Axis::VERTICAL);
        } else if (dir == 1) {
            component->SetAxis(Axis::HORIZONTAL);
        }
    }
}

void JSCalendar::SetCurrentDayStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (Container::IsCurrentUseNewPipeline()) {
        NG::CurrentDayStyle currentDayStyle;
        Color dayColor;
        if (ConvertFromJSValue(obj->GetProperty("dayColor"), dayColor)) {
            currentDayStyle.UpdateDayColor(dayColor);
        }
        Color lunarColor;
        if (ConvertFromJSValue(obj->GetProperty("lunarColor"), lunarColor)) {
            currentDayStyle.UpdateLunarColor(lunarColor);
        }
        Color markLunarColor;
        if (ConvertFromJSValue(obj->GetProperty("markLunarColor"), markLunarColor)) {
            currentDayStyle.UpdateMarkLunarColor(markLunarColor);
        }
        Dimension dayFontSize;
        if (ParseJsDimensionFp(obj->GetProperty("dayFontSize"), dayFontSize)) {
            currentDayStyle.UpdateDayFontSize(dayFontSize);
        }
        Dimension lunarDayFontSize;
        if (ParseJsDimensionFp(obj->GetProperty("lunarDayFontSize"), lunarDayFontSize)) {
            currentDayStyle.UpdateLunarDayFontSize(lunarDayFontSize);
        }
        Dimension dayHeight;
        if (ParseJsDimensionFp(obj->GetProperty("dayHeight"), dayHeight)) {
            currentDayStyle.UpdateDayHeight(dayHeight);
        }
        Dimension dayWidth;
        if (ParseJsDimensionFp(obj->GetProperty("dayWidth"), dayWidth)) {
            currentDayStyle.UpdateDayWidth(dayWidth);
        }
        Dimension gregorianCalendarHeight;
        if (ParseJsDimensionFp(obj->GetProperty("gregorianCalendarHeight"), gregorianCalendarHeight)) {
            currentDayStyle.UpdateGregorianCalendarHeight(gregorianCalendarHeight);
        }
        Dimension lunarHeight;
        if (ParseJsDimensionFp(obj->GetProperty("lunarHeight"), lunarHeight)) {
            currentDayStyle.UpdateLunarHeight(lunarHeight);
        }
        Dimension dayYAxisOffset;
        if (ParseJsDimensionFp(obj->GetProperty("dayYAxisOffset"), dayYAxisOffset)) {
            currentDayStyle.UpdateDayYAxisOffset(dayYAxisOffset);
        }
        Dimension lunarDayYAxisOffset;
        if (ParseJsDimensionFp(obj->GetProperty("lunarDayYAxisOffset"), lunarDayYAxisOffset)) {
            currentDayStyle.UpdateLunarDayYAxisOffset(lunarDayYAxisOffset);
        }
        Dimension underscoreXAxisOffset;
        if (ParseJsDimensionFp(obj->GetProperty("underscoreXAxisOffset"), underscoreXAxisOffset)) {
            currentDayStyle.UpdateUnderscoreXAxisOffset(underscoreXAxisOffset);
        }
        Dimension underscoreYAxisOffset;
        if (ParseJsDimensionFp(obj->GetProperty("underscoreYAxisOffset"), underscoreYAxisOffset)) {
            currentDayStyle.UpdateUnderscoreYAxisOffset(underscoreYAxisOffset);
        }
        Dimension scheduleMarkerXAxisOffset;
        if (ParseJsDimensionFp(obj->GetProperty("scheduleMarkerXAxisOffset"), scheduleMarkerXAxisOffset)) {
            currentDayStyle.UpdateScheduleMarkerXAxisOffset(scheduleMarkerXAxisOffset);
        }
        Dimension scheduleMarkerYAxisOffset;
        if (ParseJsDimensionFp(obj->GetProperty("scheduleMarkerYAxisOffset"), scheduleMarkerYAxisOffset)) {
            currentDayStyle.UpdateScheduleMarkerYAxisOffset(scheduleMarkerYAxisOffset);
        }
        Dimension colSpace;
        if (ParseJsDimensionFp(obj->GetProperty("colSpace"), colSpace)) {
            currentDayStyle.UpdateColSpace(colSpace);
        }
        Dimension dailyFiveRowSpace;
        if (ParseJsDimensionFp(obj->GetProperty("dailyFiveRowSpace"), dailyFiveRowSpace)) {
            currentDayStyle.UpdateDailyFiveRowSpace(dailyFiveRowSpace);
        }
        Dimension dailySixRowSpace;
        if (ParseJsDimensionFp(obj->GetProperty("dailySixRowSpace"), dailySixRowSpace)) {
            currentDayStyle.UpdateDailySixRowSpace(dailySixRowSpace);
        }
        Dimension underscoreWidth;
        if (ParseJsDimensionFp(obj->GetProperty("underscoreWidth"), underscoreWidth)) {
            currentDayStyle.UpdateUnderscoreWidth(underscoreWidth);
        }
        Dimension underscoreLength;
        if (ParseJsDimensionFp(obj->GetProperty("underscoreLength"), underscoreLength)) {
            currentDayStyle.UpdateUnderscoreLength(underscoreLength);
        }
        Dimension scheduleMarkerRadius;
        if (ParseJsDimensionFp(obj->GetProperty("scheduleMarkerRadius"), scheduleMarkerRadius)) {
            currentDayStyle.UpdateScheduleMarkerRadius(scheduleMarkerRadius);
        }
        Dimension boundaryRowOffset;
        if (ParseJsDimensionFp(obj->GetProperty("boundaryRowOffset"), boundaryRowOffset)) {
            currentDayStyle.UpdateBoundaryRowOffset(boundaryRowOffset);
        }
        Dimension boundaryColOffset;
        if (ParseJsDimensionFp(obj->GetProperty("boundaryColOffset"), boundaryColOffset)) {
            currentDayStyle.UpdateBoundaryColOffset(boundaryColOffset);
        }
        NG::CalendarView::SetCurrentDayStyle(currentDayStyle);
        return;
    }
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();
    ConvertFromJSValue(obj->GetProperty("dayColor"), theme.dayColor);
    ConvertFromJSValue(obj->GetProperty("lunarColor"), theme.lunarColor);
    ConvertFromJSValue(obj->GetProperty("markLunarColor"), theme.markLunarColor);
    Dimension dayFontSize;
    if (ParseJsDimensionFp(obj->GetProperty("dayFontSize"), dayFontSize)) {
        theme.dayFontSize = dayFontSize;
    }
    Dimension lunarDayFontSize;
    if (ParseJsDimensionFp(obj->GetProperty("lunarDayFontSize"), lunarDayFontSize)) {
        theme.lunarDayFontSize = lunarDayFontSize;
    }
    ConvertFromJSValue(obj->GetProperty("dayHeight"), theme.dayHeight);
    ConvertFromJSValue(obj->GetProperty("dayWidth"), theme.dayWidth);
    ConvertFromJSValue(obj->GetProperty("gregorianCalendarHeight"), theme.gregorianCalendarHeight);
    ConvertFromJSValue(obj->GetProperty("lunarHeight"), theme.lunarHeight);
    ConvertFromJSValue(obj->GetProperty("dayYAxisOffset"), theme.dayYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("lunarDayYAxisOffset"), theme.lunarDayYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("underscoreXAxisOffset"), theme.underscoreXAxisOffset);
    ConvertFromJSValue(obj->GetProperty("underscoreYAxisOffset"), theme.underscoreYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("scheduleMarkerXAxisOffset"), theme.scheduleMarkerXAxisOffset);
    ConvertFromJSValue(obj->GetProperty("scheduleMarkerYAxisOffset"), theme.scheduleMarkerYAxisOffset);
    ConvertFromJSValue(obj->GetProperty("colSpace"), theme.colSpace);
    ConvertFromJSValue(obj->GetProperty("dailyFiveRowSpace"), theme.dailyFiveRowSpace);
    ConvertFromJSValue(obj->GetProperty("dailySixRowSpace"), theme.dailySixRowSpace);
    ConvertFromJSValue(obj->GetProperty("underscoreWidth"), theme.underscoreWidth);
    ConvertFromJSValue(obj->GetProperty("underscoreLength"), theme.underscoreLength);
    ConvertFromJSValue(obj->GetProperty("scheduleMarkerRadius"), theme.scheduleMarkerRadius);
    ConvertFromJSValue(obj->GetProperty("boundaryRowOffset"), theme.boundaryRowOffset);
    ConvertFromJSValue(obj->GetProperty("boundaryColOffset"), theme.boundaryColOffset);
    ConvertFromJSValue(obj->GetProperty("touchCircleStrokeWidth"), theme.touchCircleStrokeWidth);
}

void JSCalendar::SetNonCurrentDayStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (Container::IsCurrentUseNewPipeline()) {
        NG::NonCurrentDayStyle nonCurrentDayStyle;
        Color nonCurrentMonthDayColor;
        if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthDayColor"), nonCurrentMonthDayColor)) {
            nonCurrentDayStyle.UpdateNonCurrentMonthDayColor(nonCurrentMonthDayColor);
        }
        Color nonCurrentMonthLunarColor;
        if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthLunarColor"), nonCurrentMonthLunarColor)) {
            nonCurrentDayStyle.UpdateNonCurrentMonthLunarColor(nonCurrentMonthLunarColor);
        }
        Color nonCurrentMonthWorkDayMarkColor;
        if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthWorkDayMarkColor"), nonCurrentMonthWorkDayMarkColor)) {
            nonCurrentDayStyle.UpdateNonCurrentMonthWorkDayMarkColor(nonCurrentMonthWorkDayMarkColor);
        }
        Color nonCurrentMonthOffDayMarkColor;
        if (ConvertFromJSValue(obj->GetProperty("nonCurrentMonthOffDayMarkColor"), nonCurrentMonthOffDayMarkColor)) {
            nonCurrentDayStyle.UpdateNonCurrentMonthOffDayMarkColor(nonCurrentMonthOffDayMarkColor);
        }
        NG::CalendarView::SetNonCurrentDayStyle(nonCurrentDayStyle);
        return;
    }

    auto component = GetComponent();
    if (!component) {
        return;
    }
    auto& themePtr = component->GetCalendarTheme();
    if (!themePtr) {
        return;
    }
    auto& theme = themePtr->GetCalendarTheme();
    ConvertFromJSValue(obj->GetProperty("nonCurrentMonthDayColor"), theme.nonCurrentMonthDayColor);
    ConvertFromJSValue(obj->GetProperty("nonCurrentMonthLunarColor"), theme.nonCurrentMonthLunarColor);
    ConvertFromJSValue(obj->GetProperty("nonCurrentMonthWorkDayMarkColor"), theme.nonCurrentMonthWorkDayMarkColor);
    ConvertFromJSValue(obj->GetProperty("nonCurrentMonthOffDayMarkColor"), theme.nonCurrentMonthOffDayMarkColor);
}

void JSCalendar::SetTodayStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (Container::IsCurrentUseNewPipeline()) {
        NG::TodayStyle todayStyle;
        Color focusedDayColor;
        if (ConvertFromJSValue(obj->GetProperty("focusedDayColor"), focusedDayColor)) {
            todayStyle.UpdateFocusedDayColor(focusedDayColor);
        }
        Color focusedLunarColor;
        if (ConvertFromJSValue(obj->GetProperty("focusedLunarColor"), focusedLunarColor)) {
            todayStyle.UpdateFocusedLunarColor(focusedLunarColor);
        }
        Color focusedAreaBackgroundColor;
        if (ConvertFromJSValue(obj->GetProperty("focusedAreaBackgroundColor"), focusedAreaBackgroundColor)) {
            todayStyle.UpdateFocusedAreaBackgroundColor(focusedAreaBackgroundColor);
        }
        Dimension focusedAreaRadius;
        if (ConvertFromJSValue(obj->GetProperty("focusedAreaRadius"), focusedAreaRadius)) {
            todayStyle.UpdateFocusedAreaRadius(focusedAreaRadius);
        }
        NG::CalendarView::SetTodayStyle(todayStyle);
        return;
    }
    auto component = GetComponent();
    if (!component) {
        return;
    }

    auto& themePtr = component->GetCalendarTheme();
    if (!themePtr) {
        return;
    }
    auto& theme = themePtr->GetCalendarTheme();
    ConvertFromJSValue(obj->GetProperty("focusedDayColor"), theme.focusedDayColor);
    ConvertFromJSValue(obj->GetProperty("focusedLunarColor"), theme.focusedLunarColor);
    ConvertFromJSValue(obj->GetProperty("focusedAreaBackgroundColor"), theme.focusedAreaBackgroundColor);
    ConvertFromJSValue(obj->GetProperty("focusedAreaRadius"), theme.focusedAreaRadius);
}

void JSCalendar::SetWeekStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (Container::IsCurrentUseNewPipeline()) {
        NG::WeekStyle weekStyle;
        Color weekColor;
        if (ConvertFromJSValue(obj->GetProperty("weekColor"), weekColor)) {
            weekStyle.UpdateWeekColor(weekColor);
        }
        Color weekendDayColor;
        if (ConvertFromJSValue(obj->GetProperty("weekendDayColor"), weekendDayColor)) {
            weekStyle.UpdateWeekendDayColor(weekendDayColor);
        }
        Color weekendLunarColor;
        if (ConvertFromJSValue(obj->GetProperty("weekendLunarColor"), weekendLunarColor)) {
            weekStyle.UpdateWeekendLunarColor(weekendLunarColor);
        }
        Dimension weekFontSize;
        if (ParseJsDimensionFp(obj->GetProperty("weekFontSize"), weekFontSize)) {
            weekStyle.UpdateWeekFontSize(weekFontSize);
        }
        Dimension weekHeight;
        if (ConvertFromJSValue(obj->GetProperty("weekHeight"), weekHeight)) {
            weekStyle.UpdateWeekHeight(weekHeight);
        }
        Dimension weekWidth;
        if (ConvertFromJSValue(obj->GetProperty("weekWidth"), weekWidth)) {
            weekStyle.UpdateWeekWidth(weekWidth);
        }
        Dimension weekAndDayRowSpace;
        if (ConvertFromJSValue(obj->GetProperty("weekAndDayRowSpace"), weekAndDayRowSpace)) {
            weekStyle.UpdateWeekAndDayRowSpace(weekAndDayRowSpace);
        }
        NG::CalendarView::SetWeekStyle(weekStyle);
        return;
    }
    auto component = GetComponent();
    if (!component) {
        return;
    }

    auto& themePtr = component->GetCalendarTheme();
    if (!themePtr) {
        return;
    }
    auto& theme = themePtr->GetCalendarTheme();
    ConvertFromJSValue(obj->GetProperty("weekColor"), theme.weekColor);
    ConvertFromJSValue(obj->GetProperty("weekendDayColor"), theme.weekendDayColor);
    ConvertFromJSValue(obj->GetProperty("weekendLunarColor"), theme.weekendLunarColor);
    Dimension weekFontSize;
    if (ParseJsDimensionFp(obj->GetProperty("weekFontSize"), weekFontSize)) {
        theme.weekFontSize = weekFontSize;
    }
    ConvertFromJSValue(obj->GetProperty("weekHeight"), theme.weekHeight);
    ConvertFromJSValue(obj->GetProperty("weekWidth"), theme.weekWidth);
    ConvertFromJSValue(obj->GetProperty("weekAndDayRowSpace"), theme.weekAndDayRowSpace);
}

void JSCalendar::SetWorkStateStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (Container::IsCurrentUseNewPipeline()) {
        NG::WorkStateStyle workStateStyle;
        Color workDayMarkColor;
        if (ConvertFromJSValue(obj->GetProperty("workDayMarkColor"), workDayMarkColor)) {
            workStateStyle.UpdateWorkDayMarkColor(workDayMarkColor);
        }
        Color offDayMarkColor;
        if (ConvertFromJSValue(obj->GetProperty("offDayMarkColor"), offDayMarkColor)) {
            workStateStyle.UpdateOffDayMarkColor(offDayMarkColor);
        }
        Dimension workDayMarkSize;
        if (ConvertFromJSValue(obj->GetProperty("workDayMarkSize"), workDayMarkSize)) {
            workStateStyle.UpdateWorkDayMarkSize(workDayMarkSize);
        }
        Dimension offDayMarkSize;
        if (ConvertFromJSValue(obj->GetProperty("offDayMarkSize"), offDayMarkSize)) {
            workStateStyle.UpdateOffDayMarkSize(offDayMarkSize);
        }
        Dimension workStateWidth;
        if (ConvertFromJSValue(obj->GetProperty("workStateWidth"), workStateWidth)) {
            workStateStyle.UpdateWorkStateWidth(workStateWidth);
        }
        Dimension workStateHorizontalMovingDistance;
        if (ConvertFromJSValue(
                obj->GetProperty("workStateHorizontalMovingDistance"), workStateHorizontalMovingDistance)) {
            workStateStyle.UpdateWorkStateHorizontalMovingDistance(workStateHorizontalMovingDistance);
        }
        Dimension workStateVerticalMovingDistance;
        if (ConvertFromJSValue(obj->GetProperty("workStateVerticalMovingDistance"), workStateVerticalMovingDistance)) {
            workStateStyle.UpdateWorkStateVerticalMovingDistance(workStateVerticalMovingDistance);
        }
        NG::CalendarView::SetWorkStateStyle(workStateStyle);
        return;
    }
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();
    ConvertFromJSValue(obj->GetProperty("workDayMarkColor"), theme.workDayMarkColor);
    ConvertFromJSValue(obj->GetProperty("offDayMarkColor"), theme.offDayMarkColor);
    ConvertFromJSValue(obj->GetProperty("workDayMarkSize"), theme.workDayMarkSize);
    ConvertFromJSValue(obj->GetProperty("offDayMarkSize"), theme.offDayMarkSize);
    ConvertFromJSValue(obj->GetProperty("workStateWidth"), theme.workStateWidth);
    ConvertFromJSValue(obj->GetProperty("workStateHorizontalMovingDistance"), theme.workStateHorizontalMovingDistance);
    ConvertFromJSValue(obj->GetProperty("workStateVerticalMovingDistance"), theme.workStateVerticalMovingDistance);
}

} // namespace OHOS::Ace::Framework
