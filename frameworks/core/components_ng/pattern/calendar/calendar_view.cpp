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

#include "core/components_ng/pattern/calendar/calendar_view.h"

#include <cstddef>
#include <string>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_month_view.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void CalendarView::Create(const CalendarData& calendarData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    if (!frameNode->GetChildren().empty()) {
        calendarPattern->SetCalendarDay(calendarData.date);
        calendarPattern->SetPreMonthData(calendarData.preData);
        calendarPattern->SetCurrentMonthData(calendarData.currentData);
        calendarPattern->SetNextMonthData(calendarData.nextData);
        stack->Push(frameNode);
        return;
    }
    auto swiperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, swiperId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateLoop(true);
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);
    swiperPaintProperty->UpdateDisableSwipe(false);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIndex(1);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperController = swiperPattern->GetSwiperController();
    CHECK_NULL_VOID(swiperController);
    swiperNode->MountToParent(frameNode);

    calendarPattern->SetCalendarDay(calendarData.date);
    calendarPattern->SetCurrentMonthData(calendarData.currentData);
    calendarPattern->SetPreMonthData(calendarData.preData);
    calendarPattern->SetNextMonthData(calendarData.nextData);

    auto currentMonthFrameNode = CalendarMonthView::Create();
    auto currentPattern = currentMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(currentPattern);
    auto preMonthFrameNode = CalendarMonthView::Create();
    auto prePattern = preMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(prePattern);
    auto nextMonthFrameNode = CalendarMonthView::Create();
    auto nextPattern = nextMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(nextPattern);
    if (calendarData.controller) {
        calendarData.controller->SetSwiperController(swiperController);
        currentPattern->SetCalendarController(calendarData.controller);
        prePattern->SetCalendarController(calendarData.controller);
        nextPattern->SetCalendarController(calendarData.controller);
    }
    preMonthFrameNode->MountToParent(swiperNode);
    currentMonthFrameNode->MountToParent(swiperNode);
    nextMonthFrameNode->MountToParent(swiperNode);
    swiperNode->MarkModifyDone();
    stack->Push(frameNode);
}

void CalendarView::SetCurrentData(ObtainedMonth& currentData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCurrentMonthData(currentData);
}

void CalendarView::SetPreData(ObtainedMonth& preData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPreMonthData(preData);
}

void CalendarView::SetNextData(ObtainedMonth& nextData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNextMonthData(nextData);
}

void CalendarView::SetCalendarDay(CalendarDay& calendarDay)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCalendarDay(calendarDay);
}

void CalendarView::SetShowLunar(bool showLunar)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateShowLunar(showLunar);
    }
}

void CalendarView::SetShowHoliday(bool showHoliday)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateShowHoliday(showHoliday);
    }
}

void CalendarView::SetNeedSlide(bool needSlide)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto swiperFrameNode = AccessibilityManager::DynamicCast<FrameNode>(swiperNode);
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDisableSwipe(!needSlide);
    swiperFrameNode->MarkModifyDone();
}

void CalendarView::SetStartOfWeek(Week startOfWeek)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateStartOfWeek(startOfWeek);
    }
}

void CalendarView::SetOffDays(const std::string& offDays)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateOffDays(offDays);
    }
}

void CalendarView::SetDirection(Axis direction)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto swiperFrameNode = AccessibilityManager::DynamicCast<FrameNode>(swiperNode);
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateDirection(direction);
    swiperFrameNode->MarkModifyDone();
}

void CalendarView::SetCurrentDayStyle(const CurrentDayStyle& currentDayStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (currentDayStyle.HasDayColor()) {
            calendarPaintProperty->UpdateDayColor(currentDayStyle.GetDayColorValue());
        }
        if (currentDayStyle.HasLunarColor()) {
            calendarPaintProperty->UpdateLunarColor(currentDayStyle.GetLunarColorValue());
        }
        if (currentDayStyle.HasMarkLunarColor()) {
            calendarPaintProperty->UpdateMarkLunarColor(currentDayStyle.GetMarkLunarColorValue());
        }
        if (currentDayStyle.HasDayFontSize()) {
            calendarPaintProperty->UpdateDayFontSize(currentDayStyle.GetDayFontSizeValue());
        }
        if (currentDayStyle.HasLunarDayFontSize()) {
            calendarPaintProperty->UpdateLunarDayFontSize(currentDayStyle.GetLunarDayFontSizeValue());
        }
        if (currentDayStyle.HasDayHeight()) {
            calendarPaintProperty->UpdateDayHeight(currentDayStyle.GetDayHeightValue());
        }
        if (currentDayStyle.HasDayWidth()) {
            calendarPaintProperty->UpdateDayWidth(currentDayStyle.GetDayWidthValue());
        }
        if (currentDayStyle.HasGregorianCalendarHeight()) {
            calendarPaintProperty->UpdateGregorianCalendarHeight(currentDayStyle.GetGregorianCalendarHeightValue());
        }
        if (currentDayStyle.HasDayYAxisOffset()) {
            calendarPaintProperty->UpdateDayYAxisOffset(currentDayStyle.GetDayYAxisOffsetValue());
        }
        if (currentDayStyle.HasLunarDayYAxisOffset()) {
            calendarPaintProperty->UpdateLunarDayYAxisOffset(currentDayStyle.GetLunarDayYAxisOffsetValue());
        }
        if (currentDayStyle.HasUnderscoreXAxisOffset()) {
            calendarPaintProperty->UpdateUnderscoreXAxisOffset(currentDayStyle.GetUnderscoreXAxisOffsetValue());
        }
        if (currentDayStyle.HasUnderscoreYAxisOffset()) {
            calendarPaintProperty->UpdateUnderscoreYAxisOffset(currentDayStyle.GetUnderscoreYAxisOffsetValue());
        }
        if (currentDayStyle.HasScheduleMarkerXAxisOffset()) {
            calendarPaintProperty->UpdateScheduleMarkerXAxisOffset(currentDayStyle.GetScheduleMarkerXAxisOffsetValue());
        }
        if (currentDayStyle.HasScheduleMarkerYAxisOffset()) {
            calendarPaintProperty->UpdateScheduleMarkerYAxisOffset(currentDayStyle.GetScheduleMarkerYAxisOffsetValue());
        }
        if (currentDayStyle.HasColSpace()) {
            calendarPaintProperty->UpdateColSpace(currentDayStyle.GetColSpaceValue());
        }
        if (currentDayStyle.HasDailyFiveRowSpace()) {
            calendarPaintProperty->UpdateDailyFiveRowSpace(currentDayStyle.GetDailyFiveRowSpaceValue());
        }
        if (currentDayStyle.HasDailySixRowSpace()) {
            calendarPaintProperty->UpdateDailySixRowSpace(currentDayStyle.GetDailySixRowSpaceValue());
        }
        if (currentDayStyle.HasLunarHeight()) {
            calendarPaintProperty->UpdateLunarHeight(currentDayStyle.GetLunarHeightValue());
        }
        if (currentDayStyle.HasUnderscoreWidth()) {
            calendarPaintProperty->UpdateUnderscoreWidth(currentDayStyle.GetUnderscoreWidthValue());
        }
        if (currentDayStyle.HasUnderscoreLength()) {
            calendarPaintProperty->UpdateUnderscoreLength(currentDayStyle.GetUnderscoreLengthValue());
        }
        if (currentDayStyle.HasScheduleMarkerRadius()) {
            calendarPaintProperty->UpdateScheduleMarkerRadius(currentDayStyle.GetScheduleMarkerRadiusValue());
        }
        if (currentDayStyle.HasBoundaryRowOffset()) {
            calendarPaintProperty->UpdateBoundaryRowOffset(currentDayStyle.GetBoundaryRowOffsetValue());
        }
        if (currentDayStyle.HasBoundaryColOffset()) {
            calendarPaintProperty->UpdateBoundaryColOffset(currentDayStyle.GetBoundaryColOffsetValue());
        }
    }
}

void CalendarView::SetNonCurrentDayStyle(const NonCurrentDayStyle& nonCurrentDayStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (nonCurrentDayStyle.HasNonCurrentMonthDayColor()) {
            calendarPaintProperty->UpdateNonCurrentMonthDayColor(nonCurrentDayStyle.GetNonCurrentMonthDayColorValue());
        }
        if (nonCurrentDayStyle.HasNonCurrentMonthLunarColor()) {
            calendarPaintProperty->UpdateNonCurrentMonthLunarColor(
                nonCurrentDayStyle.GetNonCurrentMonthLunarColorValue());
        }
        if (nonCurrentDayStyle.HasNonCurrentMonthWorkDayMarkColor()) {
            calendarPaintProperty->UpdateNonCurrentMonthWorkDayMarkColor(
                nonCurrentDayStyle.GetNonCurrentMonthWorkDayMarkColorValue());
        }
        if (nonCurrentDayStyle.HasNonCurrentMonthOffDayMarkColor()) {
            calendarPaintProperty->UpdateNonCurrentMonthOffDayMarkColor(
                nonCurrentDayStyle.GetNonCurrentMonthOffDayMarkColorValue());
        }
    }
}

void CalendarView::SetTodayStyle(const TodayStyle& todayStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (todayStyle.HasFocusedDayColor()) {
            calendarPaintProperty->UpdateFocusedDayColor(todayStyle.GetFocusedDayColorValue());
        }
        if (todayStyle.HasFocusedLunarColor()) {
            calendarPaintProperty->UpdateFocusedLunarColor(todayStyle.GetFocusedLunarColorValue());
        }
        if (todayStyle.HasFocusedAreaBackgroundColor()) {
            calendarPaintProperty->UpdateFocusedAreaBackgroundColor(todayStyle.GetFocusedAreaBackgroundColorValue());
        }
        if (todayStyle.HasFocusedAreaRadius()) {
            calendarPaintProperty->UpdateFocusedAreaRadius(todayStyle.GetFocusedAreaRadiusValue());
        }
    }
}

void CalendarView::SetWeekStyle(const WeekStyle& weekStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (weekStyle.HasWeekColor()) {
            calendarPaintProperty->UpdateWeekColor(weekStyle.GetWeekColorValue());
        }
        if (weekStyle.HasWeekendDayColor()) {
            calendarPaintProperty->UpdateWeekendDayColor(weekStyle.GetWeekendDayColorValue());
        }
        if (weekStyle.HasWeekendLunarColor()) {
            calendarPaintProperty->UpdateWeekendLunarColor(weekStyle.GetWeekendLunarColorValue());
        }
        if (weekStyle.HasWeekFontSize()) {
            calendarPaintProperty->UpdateWeekFontSize(weekStyle.GetWeekFontSizeValue());
        }
        if (weekStyle.HasWeekHeight()) {
            calendarPaintProperty->UpdateWeekHeight(weekStyle.GetWeekHeightValue());
        }
        if (weekStyle.HasWeekWidth()) {
            calendarPaintProperty->UpdateWeekWidth(weekStyle.GetWeekWidthValue());
        }
        if (weekStyle.HasWeekAndDayRowSpace()) {
            calendarPaintProperty->UpdateWeekAndDayRowSpace(weekStyle.GetWeekAndDayRowSpaceValue());
        }
    }
}

void CalendarView::SetWorkStateStyle(const WorkStateStyle& workStateStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (workStateStyle.HasWorkDayMarkColor()) {
            calendarPaintProperty->UpdateWorkDayMarkColor(workStateStyle.GetWorkDayMarkColorValue());
        }
        if (workStateStyle.HasOffDayMarkColor()) {
            calendarPaintProperty->UpdateOffDayMarkColor(workStateStyle.GetOffDayMarkColorValue());
        }
        if (workStateStyle.HasWorkDayMarkSize()) {
            calendarPaintProperty->UpdateWorkDayMarkSize(workStateStyle.GetWorkDayMarkSizeValue());
        }
        if (workStateStyle.HasOffDayMarkSize()) {
            calendarPaintProperty->UpdateOffDayMarkSize(workStateStyle.GetOffDayMarkSizeValue());
        }
        if (workStateStyle.HasWorkStateWidth()) {
            calendarPaintProperty->UpdateWorkStateWidth(workStateStyle.GetWorkStateWidthValue());
        }
        if (workStateStyle.HasWorkStateHorizontalMovingDistance()) {
            calendarPaintProperty->UpdateWorkStateHorizontalMovingDistance(
                workStateStyle.GetWorkStateHorizontalMovingDistanceValue());
        }
        if (workStateStyle.HasWorkStateVerticalMovingDistance()) {
            calendarPaintProperty->UpdateWorkStateVerticalMovingDistance(
                workStateStyle.GetWorkStateVerticalMovingDistanceValue());
        }
    }
}

void CalendarView::SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AccessibilityManager::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto pattern = calendarFrameNode->GetPattern<CalendarMonthPattern>();
        auto eventHub = calendarFrameNode->GetEventHub<EventHub>();
        auto calendarEventHub = AccessibilityManager::DynamicCast<CalendarEventHub>(eventHub);
        CHECK_NULL_VOID(calendarEventHub);
        calendarEventHub->SetSelectedChangeEvent(std::move(selectedChangeEvent));
    }
}

void CalendarView::SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestDataEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestDataEvent(std::move(requestDataEvent));
}

} // namespace OHOS::Ace::NG