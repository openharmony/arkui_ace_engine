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

#include "bridge/declarative_frontend/jsview/models/calendar_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void CalendarModelImpl::Create(const CalendarModelData& calendarModelData)
{
    auto calendarComponent = AceType::MakeRefPtr<OHOS::Ace::CalendarComponentV2>("", "calendar");
    calendarComponent->SetCalendarDate(calendarModelData.date);
    calendarComponent->SetCalendarData(calendarModelData.currentData);
    calendarComponent->SetCalendarData(calendarModelData.preData);
    calendarComponent->SetCalendarData(calendarModelData.nextData);
    calendarComponent->SetControllerV2(AceType::DynamicCast<CalendarControllerV2>(calendarModelData.controller));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    calendarComponent->SetCalendarTheme(theme);
    calendarComponent->SetV2Component(true);
    ViewStackProcessor::GetInstance()->Push(calendarComponent);
}

void CalendarModelImpl::SetOffDays(const std::string& offDays)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOffDays(offDays);
}

void CalendarModelImpl::SetShowHoliday(const bool showHoliday)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetShowHoliday(showHoliday);
}

void CalendarModelImpl::SetShowLunar(const bool showLunar)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetShowLunar(showLunar);
}

void CalendarModelImpl::SetStartOfWeek(const int32_t startOfWeek)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    int32_t startOfWeekMax = 7;
    int32_t startOfWeekMin = 0;
    if (startOfWeek >= startOfWeekMin && startOfWeek < startOfWeekMax) {
        component->SetStartDayOfWeek(startOfWeek);
    }
}

void CalendarModelImpl::SetNeedSlide(const bool needSlide)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetNeedSlide(needSlide);
}

void CalendarModelImpl::SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto onSelectedChangeId = EventMarker(std::move(selectedChangeEvent));
    component->SetSelectedChangeEvent(onSelectedChangeId);
}

void CalendarModelImpl::SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestData)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto onRequestDataId = EventMarker(std::move(requestData));
    component->SetRequestDataEvent(onRequestDataId);
}

void CalendarModelImpl::SetDirection(const int32_t dir)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    if (dir == 0) {
        component->SetAxis(Axis::VERTICAL);
    } else if (dir == 1) {
        component->SetAxis(Axis::HORIZONTAL);
    }
}

void CalendarModelImpl::SetCurrentDayStyle(const CurrentDayStyleData& currentDayStyleData,
    const CurrentDayStyleData& CurrentDayStyleDataImpl)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();

    if (CurrentDayStyleDataImpl.dayColor.has_value()) {
        theme.dayColor = CurrentDayStyleDataImpl.dayColor.value();
    }

    if (CurrentDayStyleDataImpl.lunarColor.has_value()) {
        theme.lunarColor = CurrentDayStyleDataImpl.lunarColor.value();
    }

    if (CurrentDayStyleDataImpl.markLunarColor.has_value()) {
        theme.markLunarColor = CurrentDayStyleDataImpl.markLunarColor.value();
    }

    if (CurrentDayStyleDataImpl.dayFontSize.has_value()) {
        theme.dayFontSize = CurrentDayStyleDataImpl.dayFontSize.value();
    }

    if (CurrentDayStyleDataImpl.lunarDayFontSize.has_value()) {
        theme.lunarDayFontSize = CurrentDayStyleDataImpl.lunarDayFontSize.value();
    }

    if (CurrentDayStyleDataImpl.dayHeight.has_value()) {
        theme.dayHeight = CurrentDayStyleDataImpl.dayHeight.value();
    }

    if (CurrentDayStyleDataImpl.dayWidth.has_value()) {
        theme.dayWidth = CurrentDayStyleDataImpl.dayWidth.value();
    }

    if (CurrentDayStyleDataImpl.gregorianCalendarHeight.has_value()) {
        theme.gregorianCalendarHeight = CurrentDayStyleDataImpl.gregorianCalendarHeight.value();
    }

    if (CurrentDayStyleDataImpl.lunarHeight.has_value()) {
        theme.lunarHeight = CurrentDayStyleDataImpl.lunarHeight.value();
    }

    if (CurrentDayStyleDataImpl.dayYAxisOffset.has_value()) {
        theme.dayYAxisOffset = CurrentDayStyleDataImpl.dayYAxisOffset.value();
    }

    if (CurrentDayStyleDataImpl.lunarDayYAxisOffset.has_value()) {
        theme.lunarDayYAxisOffset = CurrentDayStyleDataImpl.lunarDayYAxisOffset.value();
    }

    if (CurrentDayStyleDataImpl.underscoreXAxisOffset.has_value()) {
        theme.underscoreXAxisOffset = CurrentDayStyleDataImpl.underscoreXAxisOffset.value();
    }

    if (CurrentDayStyleDataImpl.underscoreYAxisOffset.has_value()) {
        theme.underscoreYAxisOffset = CurrentDayStyleDataImpl.underscoreYAxisOffset.value();
    }

    if (CurrentDayStyleDataImpl.scheduleMarkerXAxisOffset.has_value()) {
        theme.scheduleMarkerXAxisOffset = CurrentDayStyleDataImpl.scheduleMarkerXAxisOffset.value();
    }

    if (CurrentDayStyleDataImpl.scheduleMarkerYAxisOffset.has_value()) {
        theme.scheduleMarkerYAxisOffset = CurrentDayStyleDataImpl.scheduleMarkerYAxisOffset.value();
    }

    if (CurrentDayStyleDataImpl.colSpace.has_value()) {
        theme.colSpace = CurrentDayStyleDataImpl.colSpace.value();
    }

    if (CurrentDayStyleDataImpl.dailyFiveRowSpace.has_value()) {
        theme.dailyFiveRowSpace = CurrentDayStyleDataImpl.dailyFiveRowSpace.value();
    }

    if (CurrentDayStyleDataImpl.dailySixRowSpace.has_value()) {
        theme.dailySixRowSpace = CurrentDayStyleDataImpl.dailySixRowSpace.value();
    }

    if (CurrentDayStyleDataImpl.underscoreWidth.has_value()) {
        theme.underscoreWidth = CurrentDayStyleDataImpl.underscoreWidth.value();
    }

    if (CurrentDayStyleDataImpl.underscoreLength.has_value()) {
        theme.underscoreLength = CurrentDayStyleDataImpl.underscoreLength.value();
    }

    if (CurrentDayStyleDataImpl.scheduleMarkerRadius.has_value()) {
        theme.scheduleMarkerRadius = CurrentDayStyleDataImpl.scheduleMarkerRadius.value();
    }

    if (CurrentDayStyleDataImpl.boundaryRowOffset.has_value()) {
        theme.boundaryRowOffset = CurrentDayStyleDataImpl.boundaryRowOffset.value();
    }

    if (CurrentDayStyleDataImpl.boundaryColOffset.has_value()) {
        theme.boundaryColOffset = CurrentDayStyleDataImpl.boundaryColOffset.value();
    }

    if (CurrentDayStyleDataImpl.touchCircleStrokeWidth.has_value()) {
        theme.touchCircleStrokeWidth = CurrentDayStyleDataImpl.touchCircleStrokeWidth.value();
    }
}

void CalendarModelImpl::SetNonCurrentDayStyle(const NonCurrentDayStyleData& nonCurrentDayStyleData)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();

    if (nonCurrentDayStyleData.nonCurrentMonthDayColor.has_value()) {
        theme.nonCurrentMonthDayColor = nonCurrentDayStyleData.nonCurrentMonthDayColor.value();
    }

    if (nonCurrentDayStyleData.nonCurrentMonthLunarColor.has_value()) {
        theme.nonCurrentMonthLunarColor = nonCurrentDayStyleData.nonCurrentMonthLunarColor.value();
    }

    if (nonCurrentDayStyleData.nonCurrentMonthWorkDayMarkColor.has_value()) {
        theme.nonCurrentMonthWorkDayMarkColor = nonCurrentDayStyleData.nonCurrentMonthWorkDayMarkColor.value();
    }

    if (nonCurrentDayStyleData.nonCurrentMonthOffDayMarkColor.has_value()) {
        theme.nonCurrentMonthOffDayMarkColor = nonCurrentDayStyleData.nonCurrentMonthOffDayMarkColor.value();
    }
}

void CalendarModelImpl::SetTodayStyle(const TodayStyleData& style)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();

    if (style.focusedDayColor.has_value()) {
        theme.focusedDayColor = style.focusedDayColor.value();
    }

    if (style.focusedLunarColor.has_value()) {
        theme.focusedLunarColor = style.focusedLunarColor.value();
    }

    if (style.focusedAreaBackgroundColor.has_value()) {
        theme.focusedAreaBackgroundColor = style.focusedAreaBackgroundColor.value();
    }

    if (style.focusedAreaRadius.has_value()) {
        theme.focusedAreaRadius = style.focusedAreaRadius.value();
    }
}

void CalendarModelImpl::SetWeekStyle(const WeekStyleData& style)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();

    if (style.weekColor.has_value()) {
        theme.weekColor = style.weekColor.value();
    }

    if (style.weekendDayColor.has_value()) {
        theme.weekendDayColor = style.weekendDayColor.value();
    }

    if (style.weekendLunarColor.has_value()) {
        theme.weekendLunarColor = style.weekendLunarColor.value();
    }

    if (style.weekFontSize.has_value()) {
        theme.weekFontSize = style.weekFontSize.value();
    }
    if (style.weekHeight.has_value()) {
        theme.weekHeight = style.weekHeight.value();
    }

    if (style.weekWidth.has_value()) {
        theme.weekWidth = style.weekWidth.value();
    }

    if (style.weekAndDayRowSpace.has_value()) {
        theme.weekAndDayRowSpace = style.weekAndDayRowSpace.value();
    }
}

void CalendarModelImpl::SetWorkStateStyle(const WorkStateStyleData& style)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto& themePtr = component->GetCalendarTheme();
    CHECK_NULL_VOID(themePtr);
    auto& theme = themePtr->GetCalendarTheme();

    if (style.workDayMarkColor.has_value()) {
        theme.workDayMarkColor = style.workDayMarkColor.value();
    }

    if (style.offDayMarkColor.has_value()) {
        theme.offDayMarkColor = style.offDayMarkColor.value();
    }

    if (style.workDayMarkSize.has_value()) {
        theme.workDayMarkSize = style.workDayMarkSize.value();
    }

    if (style.offDayMarkSize.has_value()) {
        theme.offDayMarkSize = style.offDayMarkSize.value();
    }
    if (style.workStateWidth.has_value()) {
        theme.workStateWidth = style.workStateWidth.value();
    }

    if (style.workStateHorizontalMovingDistance.has_value()) {
        theme.workStateHorizontalMovingDistance = style.workStateHorizontalMovingDistance.value();
    }

    if (style.workStateVerticalMovingDistance.has_value()) {
        theme.workStateVerticalMovingDistance = style.workStateVerticalMovingDistance.value();
    }
}

RefPtr<CalendarComponentV2> CalendarModelImpl::GetComponent()
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
} // namespace OHOS::Ace::Framework
