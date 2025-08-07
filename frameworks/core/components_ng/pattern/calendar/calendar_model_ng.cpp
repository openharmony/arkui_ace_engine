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

#include "core/components_ng/pattern/calendar/calendar_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/calendar/calendar_controller_ng.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void CalendarModelNG::Create(const CalendarModelData& calendarModelData)
{
    CalendarData calendarData;
    calendarData.date = calendarModelData.date;
    calendarData.currentData = calendarModelData.currentData;
    calendarData.preData = calendarModelData.preData;
    calendarData.nextData = calendarModelData.nextData;
    calendarData.controller = AceType::DynamicCast<NG::CalendarControllerNg>(calendarModelData.controller);
    Create(calendarData);
}

void CalendarModelNG::Create(const CalendarData& calendarData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::CALENDAR_ETS_TAG, nodeId);
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
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateLoop(true);
    swiperLayoutProperty->UpdateIndex(1);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperLayoutProperty->UpdateDisableSwipe(true);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperController = swiperPattern->GetSwiperController();
    CHECK_NULL_VOID(swiperController);
    swiperNode->MountToParent(frameNode);

    calendarPattern->SetCalendarDay(calendarData.date);
    calendarPattern->SetCurrentMonthData(calendarData.currentData);
    calendarPattern->SetPreMonthData(calendarData.preData);
    calendarPattern->SetNextMonthData(calendarData.nextData);

    auto currentMonthFrameNode = Create();
    auto currentPattern = currentMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(currentPattern);
    auto preMonthFrameNode = Create();
    auto prePattern = preMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(prePattern);
    auto nextMonthFrameNode = Create();
    auto nextPattern = nextMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_VOID(nextPattern);
    if (calendarData.controller) {
        calendarPattern->SetCalendarControllerNg(calendarData.controller);
    }
    preMonthFrameNode->MountToParent(swiperNode);
    preMonthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    currentMonthFrameNode->MountToParent(swiperNode);
    currentMonthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    nextMonthFrameNode->MountToParent(swiperNode);
    nextMonthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    swiperNode->MarkModifyDone();
    stack->Push(frameNode);
}

RefPtr<FrameNode> CalendarModelNG::Create()
{
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    return frameNode;
}

void CalendarModelNG::SetOffDays(const std::string& offDays)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateOffDays(offDays);
    }
}

void CalendarModelNG::SetShowHoliday(const bool showHoliday)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateShowHoliday(showHoliday);
    }
}

void CalendarModelNG::SetShowLunar(const bool showLunar)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateShowLunar(showLunar);
    }
}

void CalendarModelNG::SetStartOfWeek(const int32_t startOfWeek)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateStartOfWeek(NG::Week(startOfWeek));
    }
}

void CalendarModelNG::SetNeedSlide(const bool needSlide)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateDisableSwipe(!needSlide);
    swiperFrameNode->MarkModifyDone();
}

void CalendarModelNG::SetSelectedChangeEvent(std::function<void(const std::string&)>&& selectedChangeEvent)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto pattern = calendarFrameNode->GetPattern<CalendarMonthPattern>();
        auto calendarEventHub = pattern->GetOrCreateEventHub<CalendarEventHub>();
        CHECK_NULL_VOID(calendarEventHub);
        calendarEventHub->SetSelectedChangeEvent(std::move(selectedChangeEvent));
    }
}

void CalendarModelNG::SetOnRequestDataEvent(std::function<void(const std::string&)>&& requestData)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestDataEvent(std::move(requestData));
}

void CalendarModelNG::SetDirection(const int32_t dir)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateDirection(Axis(dir));
    swiperFrameNode->MarkModifyDone();
}

void CalendarModelNG::SetCurrentDayStyle(const CurrentDayStyleData& currentDayStyleData,
    const CurrentDayStyleData& CurrentDayStyleDataImpl)
{
    NG::CurrentDayStyle currentDayStyle;
    if (currentDayStyleData.dayColor.has_value()) {
        currentDayStyle.UpdateDayColor(currentDayStyleData.dayColor.value());
    }

    if (currentDayStyleData.lunarColor.has_value()) {
        currentDayStyle.UpdateLunarColor(currentDayStyleData.lunarColor.value());
    }

    if (currentDayStyleData.markLunarColor.has_value()) {
        currentDayStyle.UpdateMarkLunarColor(currentDayStyleData.markLunarColor.value());
    }

    if (currentDayStyleData.dayFontSize.has_value()) {
        currentDayStyle.UpdateDayFontSize(currentDayStyleData.dayFontSize.value());
    }

    if (currentDayStyleData.lunarDayFontSize.has_value()) {
        currentDayStyle.UpdateLunarDayFontSize(currentDayStyleData.lunarDayFontSize.value());
    }

    if (currentDayStyleData.dayHeight.has_value()) {
        currentDayStyle.UpdateDayHeight(currentDayStyleData.dayHeight.value());
    }

    if (currentDayStyleData.dayWidth.has_value()) {
        currentDayStyle.UpdateDayWidth(currentDayStyleData.dayWidth.value());
    }

    if (currentDayStyleData.gregorianCalendarHeight.has_value()) {
        currentDayStyle.UpdateGregorianCalendarHeight(currentDayStyleData.gregorianCalendarHeight.value());
    }

    if (currentDayStyleData.lunarHeight.has_value()) {
        currentDayStyle.UpdateLunarHeight(currentDayStyleData.lunarHeight.value());
    }

    if (currentDayStyleData.dayYAxisOffset.has_value()) {
        currentDayStyle.UpdateDayYAxisOffset(currentDayStyleData.dayYAxisOffset.value());
    }

    if (currentDayStyleData.lunarDayYAxisOffset.has_value()) {
        currentDayStyle.UpdateLunarDayYAxisOffset(currentDayStyleData.lunarDayYAxisOffset.value());
    }

    if (currentDayStyleData.underscoreXAxisOffset.has_value()) {
        currentDayStyle.UpdateUnderscoreXAxisOffset(currentDayStyleData.underscoreXAxisOffset.value());
    }

    if (currentDayStyleData.underscoreYAxisOffset.has_value()) {
        currentDayStyle.UpdateUnderscoreYAxisOffset(currentDayStyleData.underscoreYAxisOffset.value());
    }

    if (currentDayStyleData.scheduleMarkerXAxisOffset.has_value()) {
        currentDayStyle.UpdateScheduleMarkerXAxisOffset(currentDayStyleData.scheduleMarkerXAxisOffset.value());
    }

    if (currentDayStyleData.scheduleMarkerYAxisOffset.has_value()) {
        currentDayStyle.UpdateScheduleMarkerYAxisOffset(currentDayStyleData.scheduleMarkerYAxisOffset.value());
    }

    if (currentDayStyleData.colSpace.has_value()) {
        currentDayStyle.UpdateColSpace(currentDayStyleData.colSpace.value());
    }

    if (currentDayStyleData.dailyFiveRowSpace.has_value()) {
        currentDayStyle.UpdateDailyFiveRowSpace(currentDayStyleData.dailyFiveRowSpace.value());
    }

    if (currentDayStyleData.dailySixRowSpace.has_value()) {
        currentDayStyle.UpdateDailySixRowSpace(currentDayStyleData.dailySixRowSpace.value());
    }

    if (currentDayStyleData.underscoreWidth.has_value()) {
        currentDayStyle.UpdateUnderscoreWidth(currentDayStyleData.underscoreWidth.value());
    }

    if (currentDayStyleData.underscoreLength.has_value()) {
        currentDayStyle.UpdateUnderscoreLength(currentDayStyleData.underscoreLength.value());
    }

    if (currentDayStyleData.scheduleMarkerRadius.has_value()) {
        currentDayStyle.UpdateScheduleMarkerRadius(currentDayStyleData.scheduleMarkerRadius.value());
    }

    if (currentDayStyleData.boundaryRowOffset.has_value()) {
        currentDayStyle.UpdateBoundaryRowOffset(currentDayStyleData.boundaryRowOffset.value());
    }

    if (currentDayStyleData.boundaryColOffset.has_value()) {
        currentDayStyle.UpdateBoundaryColOffset(currentDayStyleData.boundaryColOffset.value());
    }

    SetCurrentDayStyle(currentDayStyle);
}

void CalendarModelNG::SetCurrentDayStyle(const CurrentDayStyle& currentDayStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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
            calendarPaintProperty->UpdateScheduleMarkerXAxisOffset(
                currentDayStyle.GetScheduleMarkerXAxisOffsetValue());
        }
        if (currentDayStyle.HasScheduleMarkerYAxisOffset()) {
            calendarPaintProperty->UpdateScheduleMarkerYAxisOffset(
                currentDayStyle.GetScheduleMarkerYAxisOffsetValue());
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

void CalendarModelNG::SetNonCurrentDayStyle(const NonCurrentDayStyleData& nonCurrentDayStyleData)
{
    NG::NonCurrentDayStyle nonCurrentDayStyle;
    if (nonCurrentDayStyleData.nonCurrentMonthDayColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthDayColor(nonCurrentDayStyleData.nonCurrentMonthDayColor.value());
    }

    if (nonCurrentDayStyleData.nonCurrentMonthLunarColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthLunarColor(nonCurrentDayStyleData.nonCurrentMonthLunarColor.value());
    }

    if (nonCurrentDayStyleData.nonCurrentMonthWorkDayMarkColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthWorkDayMarkColor(
            nonCurrentDayStyleData.nonCurrentMonthWorkDayMarkColor.value());
    }

    if (nonCurrentDayStyleData.nonCurrentMonthOffDayMarkColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthOffDayMarkColor(
            nonCurrentDayStyleData.nonCurrentMonthOffDayMarkColor.value());
    }

    SetNonCurrentDayStyle(nonCurrentDayStyle);
}

void CalendarModelNG::SetNonCurrentDayStyle(const NonCurrentDayStyle& nonCurrentDayStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (nonCurrentDayStyle.HasNonCurrentMonthDayColor()) {
            calendarPaintProperty->UpdateNonCurrentMonthDayColor(
                nonCurrentDayStyle.GetNonCurrentMonthDayColorValue());
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

void CalendarModelNG::SetTodayStyle(const TodayStyleData& style)
{
    NG::TodayStyle todayStyle;
    if (style.focusedDayColor.has_value()) {
        todayStyle.UpdateFocusedDayColor(style.focusedDayColor.value());
    }

    if (style.focusedLunarColor.has_value()) {
        todayStyle.UpdateFocusedLunarColor(style.focusedLunarColor.value());
    }

    if (style.focusedAreaBackgroundColor.has_value()) {
        todayStyle.UpdateFocusedAreaBackgroundColor(style.focusedAreaBackgroundColor.value());
    }

    if (style.focusedAreaRadius.has_value()) {
        todayStyle.UpdateFocusedAreaRadius(style.focusedAreaRadius.value());
    }

    SetTodayStyle(todayStyle);
}

void CalendarModelNG::SetTodayStyle(const TodayStyle& todayStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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

void CalendarModelNG::SetWeekStyle(const WeekStyleData& style)
{
    NG::WeekStyle weekStyle;
    if (style.weekColor.has_value()) {
        weekStyle.UpdateWeekColor(style.weekColor.value());
    }

    if (style.weekendDayColor.has_value()) {
        weekStyle.UpdateWeekendDayColor(style.weekendDayColor.value());
    }

    if (style.weekendLunarColor.has_value()) {
        weekStyle.UpdateWeekendLunarColor(style.weekendLunarColor.value());
    }

    if (style.weekFontSize.has_value()) {
        weekStyle.UpdateWeekFontSize(style.weekFontSize.value());
    }

    if (style.weekHeight.has_value()) {
        weekStyle.UpdateWeekHeight(style.weekHeight.value());
    }

    if (style.weekWidth.has_value()) {
        weekStyle.UpdateWeekWidth(style.weekWidth.value());
    }

    if (style.weekAndDayRowSpace.has_value()) {
        weekStyle.UpdateWeekAndDayRowSpace(style.weekAndDayRowSpace.value());
    }

    SetWeekStyle(weekStyle);
}

void CalendarModelNG::SetWeekStyle(const WeekStyle& weekStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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

void CalendarModelNG::SetWorkStateStyle(const WorkStateStyleData& style)
{
    NG::WorkStateStyle workStateStyle;
    if (style.workDayMarkColor.has_value()) {
        workStateStyle.UpdateWorkDayMarkColor(style.workDayMarkColor.value());
    }

    if (style.offDayMarkColor.has_value()) {
        workStateStyle.UpdateOffDayMarkColor(style.offDayMarkColor.value());
    }

    if (style.workDayMarkSize.has_value()) {
        workStateStyle.UpdateWorkDayMarkSize(style.workDayMarkSize.value());
    }

    if (style.offDayMarkSize.has_value()) {
        workStateStyle.UpdateOffDayMarkSize(style.offDayMarkSize.value());
    }

    if (style.workStateWidth.has_value()) {
        workStateStyle.UpdateWorkStateWidth(style.workStateWidth.value());
    }

    if (style.workStateHorizontalMovingDistance.has_value()) {
        workStateStyle.UpdateWorkStateHorizontalMovingDistance(style.workStateHorizontalMovingDistance.value());
    }

    if (style.workStateVerticalMovingDistance.has_value()) {
        workStateStyle.UpdateWorkStateVerticalMovingDistance(style.workStateVerticalMovingDistance.value());
    }

    SetWorkStateStyle(workStateStyle);
}

void CalendarModelNG::SetWorkStateStyle(const WorkStateStyle& workStateStyle)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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

RefPtr<FrameNode> CalendarModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_RETURN(calendarPattern, frameNode);
    auto swiperId = ElementRegister::GetInstance()->MakeUniqueId();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, swiperId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, frameNode);
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, frameNode);
    swiperLayoutProperty->UpdateLoop(true);
    swiperLayoutProperty->UpdateIndex(1);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperLayoutProperty->UpdateDisableSwipe(true);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, frameNode);
    auto swiperController = swiperPattern->GetSwiperController();
    CHECK_NULL_RETURN(swiperController, frameNode);
    swiperNode->MountToParent(frameNode);

    auto currentMonthFrameNode = Create();
    auto currentPattern = currentMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_RETURN(currentPattern, frameNode);
    auto preMonthFrameNode = Create();
    auto prePattern = preMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_RETURN(prePattern, frameNode);
    auto nextMonthFrameNode = Create();
    auto nextPattern = nextMonthFrameNode->GetPattern<CalendarMonthPattern>();
    CHECK_NULL_RETURN(nextPattern, frameNode);
    preMonthFrameNode->MountToParent(swiperNode);
    preMonthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    currentMonthFrameNode->MountToParent(swiperNode);
    currentMonthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    nextMonthFrameNode->MountToParent(swiperNode);
    nextMonthFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    swiperNode->MarkModifyDone();
    return frameNode;
}

void CalendarModelNG::SetOptions(FrameNode* frameNode, const CalendarData& calendarData)
{
    CHECK_NULL_VOID(frameNode);
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(calendarPattern);
    calendarPattern->SetCalendarDay(calendarData.date);
    calendarPattern->SetPreMonthData(calendarData.preData);
    calendarPattern->SetCurrentMonthData(calendarData.currentData);
    calendarPattern->SetNextMonthData(calendarData.nextData);
    if (calendarData.controller) {
        calendarPattern->SetCalendarControllerNg(calendarData.controller);
    }
}

void CalendarModelNG::SetShowLunar(FrameNode* frameNode, bool showLunar)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateShowLunar(showLunar);
    }
}

void CalendarModelNG::SetShowHoliday(FrameNode* frameNode, bool showHoliday)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateShowHoliday(showHoliday);
    }
}

void CalendarModelNG::SetNeedSlide(FrameNode* frameNode, bool needSlide)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateDisableSwipe(!needSlide);
    swiperFrameNode->MarkModifyDone();
}

void CalendarModelNG::SetStartOfWeek(FrameNode* frameNode, int32_t startOfWeek)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        calendarPaintProperty->UpdateStartOfWeek(NG::Week(startOfWeek));
    }
}

void CalendarModelNG::SetOffDays(FrameNode* frameNode, const std::optional<std::string>& offDays)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (offDays) {
            calendarPaintProperty->UpdateOffDays(*offDays);
        } else {
            calendarPaintProperty->ResetOffDays();
        }
    }
}

void CalendarModelNG::SetDirection(FrameNode* frameNode, const std::optional<Axis>& dir)
{
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    CHECK_NULL_VOID(swiperFrameNode);
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (dir) {
        swiperLayoutProperty->UpdateDirection(*dir);
    } else {
        swiperLayoutProperty->ResetDirection();
    }
    swiperFrameNode->MarkModifyDone();
}

static void UpdateColors(CurrentDayStyle& currentDayStyle, const CurrentDayStyleData& dataStyle)
{
    if (dataStyle.dayColor.has_value()) {
        currentDayStyle.UpdateDayColor(dataStyle.dayColor.value());
    }
    if (dataStyle.lunarColor.has_value()) {
        currentDayStyle.UpdateLunarColor(dataStyle.lunarColor.value());
    }
    if (dataStyle.markLunarColor.has_value()) {
        currentDayStyle.UpdateMarkLunarColor(dataStyle.markLunarColor.value());
    }
}

static void UpdateDimensions1(CurrentDayStyle& currentDayStyle, const CurrentDayStyleData& dataStyle)
{
    if (dataStyle.dayFontSize.has_value()) {
        currentDayStyle.UpdateDayFontSize(dataStyle.dayFontSize.value());
    }
    if (dataStyle.lunarDayFontSize.has_value()) {
        currentDayStyle.UpdateLunarDayFontSize(dataStyle.lunarDayFontSize.value());
    }
    if (dataStyle.dayHeight.has_value()) {
        currentDayStyle.UpdateDayHeight(dataStyle.dayHeight.value());
    }
    if (dataStyle.dayWidth.has_value()) {
        currentDayStyle.UpdateDayWidth(dataStyle.dayWidth.value());
    }
    if (dataStyle.gregorianCalendarHeight.has_value()) {
        currentDayStyle.UpdateGregorianCalendarHeight(dataStyle.gregorianCalendarHeight.value());
    }
    if (dataStyle.lunarHeight.has_value()) {
        currentDayStyle.UpdateLunarHeight(dataStyle.lunarHeight.value());
    }
    if (dataStyle.dayYAxisOffset.has_value()) {
        currentDayStyle.UpdateDayYAxisOffset(dataStyle.dayYAxisOffset.value());
    }
    if (dataStyle.lunarDayYAxisOffset.has_value()) {
        currentDayStyle.UpdateLunarDayYAxisOffset(dataStyle.lunarDayYAxisOffset.value());
    }
    if (dataStyle.underscoreXAxisOffset.has_value()) {
        currentDayStyle.UpdateUnderscoreXAxisOffset(dataStyle.underscoreXAxisOffset.value());
    }
    if (dataStyle.underscoreYAxisOffset.has_value()) {
        currentDayStyle.UpdateUnderscoreYAxisOffset(dataStyle.underscoreYAxisOffset.value());
    }
    if (dataStyle.scheduleMarkerXAxisOffset.has_value()) {
        currentDayStyle.UpdateScheduleMarkerXAxisOffset(dataStyle.scheduleMarkerXAxisOffset.value());
    }
    if (dataStyle.scheduleMarkerYAxisOffset.has_value()) {
        currentDayStyle.UpdateScheduleMarkerYAxisOffset(dataStyle.scheduleMarkerYAxisOffset.value());
    }
}

static void UpdateDimensions2(CurrentDayStyle& currentDayStyle, const CurrentDayStyleData& dataStyle)
{
    if (dataStyle.colSpace.has_value()) {
        currentDayStyle.UpdateColSpace(dataStyle.colSpace.value());
    }
    if (dataStyle.dailyFiveRowSpace.has_value()) {
        currentDayStyle.UpdateDailyFiveRowSpace(dataStyle.dailyFiveRowSpace.value());
    }
    if (dataStyle.dailySixRowSpace.has_value()) {
        currentDayStyle.UpdateDailySixRowSpace(dataStyle.dailySixRowSpace.value());
    }
    if (dataStyle.underscoreWidth.has_value()) {
        currentDayStyle.UpdateUnderscoreWidth(dataStyle.underscoreWidth.value());
    }
    if (dataStyle.underscoreLength.has_value()) {
        currentDayStyle.UpdateUnderscoreLength(dataStyle.underscoreLength.value());
    }
    if (dataStyle.scheduleMarkerRadius.has_value()) {
        currentDayStyle.UpdateScheduleMarkerRadius(dataStyle.scheduleMarkerRadius.value());
    }
    if (dataStyle.boundaryRowOffset.has_value()) {
        currentDayStyle.UpdateBoundaryRowOffset(dataStyle.boundaryRowOffset.value());
    }
    if (dataStyle.boundaryColOffset.has_value()) {
        currentDayStyle.UpdateBoundaryColOffset(dataStyle.boundaryColOffset.value());
    }
}

static inline CurrentDayStyle ConvertCurrentDayStyle(const CurrentDayStyleData& dataStyle)
{
    CurrentDayStyle currentDayStyle;
    UpdateColors(currentDayStyle, dataStyle);
    UpdateDimensions1(currentDayStyle, dataStyle);
    UpdateDimensions2(currentDayStyle, dataStyle);
    return currentDayStyle;
}

static void UpdatePaintProperties1(RefPtr<CalendarPaintProperty> calendarPaintProperty,
    const CurrentDayStyle& currentDayStyle)
{
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
        calendarPaintProperty->UpdateScheduleMarkerXAxisOffset(
            currentDayStyle.GetScheduleMarkerXAxisOffsetValue());
    }
    if (currentDayStyle.HasScheduleMarkerYAxisOffset()) {
        calendarPaintProperty->UpdateScheduleMarkerYAxisOffset(
            currentDayStyle.GetScheduleMarkerYAxisOffsetValue());
    }
}

static void UpdatePaintProperties2(RefPtr<CalendarPaintProperty> calendarPaintProperty,
    const CurrentDayStyle& currentDayStyle)
{
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

static inline void UpdatePaintProperty(RefPtr<CalendarPaintProperty> calendarPaintProperty,
    const CurrentDayStyle& currentDayStyle)
{
    UpdatePaintProperties1(calendarPaintProperty, currentDayStyle);
    UpdatePaintProperties2(calendarPaintProperty, currentDayStyle);
}

void CalendarModelNG::SetCurrentDayStyle(FrameNode* frameNode, const CurrentDayStyleData& dataStyle)
{
    auto currentDayStyle = ConvertCurrentDayStyle(dataStyle);
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        UpdatePaintProperty(calendarPaintProperty, currentDayStyle);
    }
}

static NonCurrentDayStyle ConvertNonCurrentDayStyle(const NonCurrentDayStyleData& dataStyle)
{
    NG::NonCurrentDayStyle nonCurrentDayStyle;
    if (dataStyle.nonCurrentMonthDayColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthDayColor(dataStyle.nonCurrentMonthDayColor.value());
    }

    if (dataStyle.nonCurrentMonthLunarColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthLunarColor(dataStyle.nonCurrentMonthLunarColor.value());
    }

    if (dataStyle.nonCurrentMonthWorkDayMarkColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthWorkDayMarkColor(
            dataStyle.nonCurrentMonthWorkDayMarkColor.value());
    }

    if (dataStyle.nonCurrentMonthOffDayMarkColor.has_value()) {
        nonCurrentDayStyle.UpdateNonCurrentMonthOffDayMarkColor(
            dataStyle.nonCurrentMonthOffDayMarkColor.value());
    }

    return nonCurrentDayStyle;
}

void CalendarModelNG::SetNonCurrentDayStyle(FrameNode* frameNode, const NonCurrentDayStyleData& dataStyle)
{
    auto nonCurrentDayStyle = ConvertNonCurrentDayStyle(dataStyle);
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
        CHECK_NULL_VOID(calendarFrameNode);
        auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();
        CHECK_NULL_VOID(calendarPaintProperty);
        if (nonCurrentDayStyle.HasNonCurrentMonthDayColor()) {
            calendarPaintProperty->UpdateNonCurrentMonthDayColor(
                nonCurrentDayStyle.GetNonCurrentMonthDayColorValue());
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

static TodayStyle ConvertTodayStyle(const TodayStyleData& dataStyle)
{
    NG::TodayStyle todayStyle;
    if (dataStyle.focusedDayColor.has_value()) {
        todayStyle.UpdateFocusedDayColor(dataStyle.focusedDayColor.value());
    }

    if (dataStyle.focusedLunarColor.has_value()) {
        todayStyle.UpdateFocusedLunarColor(dataStyle.focusedLunarColor.value());
    }

    if (dataStyle.focusedAreaBackgroundColor.has_value()) {
        todayStyle.UpdateFocusedAreaBackgroundColor(dataStyle.focusedAreaBackgroundColor.value());
    }

    if (dataStyle.focusedAreaRadius.has_value()) {
        todayStyle.UpdateFocusedAreaRadius(dataStyle.focusedAreaRadius.value());
    }

    return todayStyle;
}

void CalendarModelNG::SetTodayStyle(FrameNode* frameNode, const TodayStyleData& dataStyle)
{
    auto todayStyle = ConvertTodayStyle(dataStyle);
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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

static WeekStyle ConvertWeekStyle(const WeekStyleData& dataStyle)
{
    NG::WeekStyle weekStyle;
    if (dataStyle.weekColor.has_value()) {
        weekStyle.UpdateWeekColor(dataStyle.weekColor.value());
    }

    if (dataStyle.weekendDayColor.has_value()) {
        weekStyle.UpdateWeekendDayColor(dataStyle.weekendDayColor.value());
    }

    if (dataStyle.weekendLunarColor.has_value()) {
        weekStyle.UpdateWeekendLunarColor(dataStyle.weekendLunarColor.value());
    }

    if (dataStyle.weekFontSize.has_value()) {
        weekStyle.UpdateWeekFontSize(dataStyle.weekFontSize.value());
    }

    if (dataStyle.weekHeight.has_value()) {
        weekStyle.UpdateWeekHeight(dataStyle.weekHeight.value());
    }

    if (dataStyle.weekWidth.has_value()) {
        weekStyle.UpdateWeekWidth(dataStyle.weekWidth.value());
    }

    if (dataStyle.weekAndDayRowSpace.has_value()) {
        weekStyle.UpdateWeekAndDayRowSpace(dataStyle.weekAndDayRowSpace.value());
    }

    return weekStyle;
}

void CalendarModelNG::SetWeekStyle(FrameNode* frameNode, const WeekStyleData& dataStyle)
{
    auto weekStyle = ConvertWeekStyle(dataStyle);
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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

static WorkStateStyle ConvertWorkStateStyle(const WorkStateStyleData& dataStyle)
{
    NG::WorkStateStyle workStateStyle;
    if (dataStyle.workDayMarkColor.has_value()) {
        workStateStyle.UpdateWorkDayMarkColor(dataStyle.workDayMarkColor.value());
    }

    if (dataStyle.offDayMarkColor.has_value()) {
        workStateStyle.UpdateOffDayMarkColor(dataStyle.offDayMarkColor.value());
    }

    if (dataStyle.workDayMarkSize.has_value()) {
        workStateStyle.UpdateWorkDayMarkSize(dataStyle.workDayMarkSize.value());
    }

    if (dataStyle.offDayMarkSize.has_value()) {
        workStateStyle.UpdateOffDayMarkSize(dataStyle.offDayMarkSize.value());
    }

    if (dataStyle.workStateWidth.has_value()) {
        workStateStyle.UpdateWorkStateWidth(dataStyle.workStateWidth.value());
    }

    if (dataStyle.workStateHorizontalMovingDistance.has_value()) {
        workStateStyle.UpdateWorkStateHorizontalMovingDistance(dataStyle.workStateHorizontalMovingDistance.value());
    }

    if (dataStyle.workStateVerticalMovingDistance.has_value()) {
        workStateStyle.UpdateWorkStateVerticalMovingDistance(dataStyle.workStateVerticalMovingDistance.value());
    }

    return workStateStyle;
}

void CalendarModelNG::SetWorkStateStyle(FrameNode* frameNode, const WorkStateStyleData& dataStyle)
{
    auto workStateStyle = ConvertWorkStateStyle(dataStyle);
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = frameNode->GetChildren().front();
    CHECK_NULL_VOID(swiperNode);
    for (const auto& calendarNode : swiperNode->GetChildren()) {
        auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
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

void CalendarModelNG::SetOnSelectChange(FrameNode* frameNode,
    std::function<void(const std::string&)>&& selectedChangeEvent)
{
    // CHECK_NULL_VOID(frameNode);
    // auto swiperNode = frameNode->GetChildren().front();
    // CHECK_NULL_VOID(swiperNode);
    // for (const auto& calendarNode : swiperNode->GetChildren()) {
    //     auto calendarFrameNode = AceType::DynamicCast<FrameNode>(calendarNode);
    //     CHECK_NULL_VOID(calendarFrameNode);
    //     auto pattern = calendarFrameNode->GetPattern<CalendarMonthPattern>();
    //     auto calendarEventHub = pattern->GetEventHub<CalendarEventHub>();
    //     CHECK_NULL_VOID(calendarEventHub);
    //     calendarEventHub->SetSelectedChangeEvent(std::move(selectedChangeEvent));
    // }
}

void CalendarModelNG::SetOnRequestData(FrameNode* frameNode, std::function<void(const std::string&)>&& requestData)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CalendarEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRequestDataEvent(std::move(requestData));
}

void CalendarModelNG::SetCurrentData(const ObtainedMonth& currentData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCurrentMonthData(currentData);
}

void CalendarModelNG::SetPreData(const ObtainedMonth& preData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPreMonthData(preData);
}

void CalendarModelNG::SetNextData(const ObtainedMonth& nextData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNextMonthData(nextData);
}

void CalendarModelNG::SetCalendarDay(const CalendarDay& calendarDay)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CalendarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCalendarDay(calendarDay);
}
} // namespace OHOS::Ace::NG
