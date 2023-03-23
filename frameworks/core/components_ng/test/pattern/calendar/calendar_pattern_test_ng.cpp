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

#include <cstddef>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

#define private public
#define protected public

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/video/video_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_view.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
struct TestProperty {};
namespace {
const Color COLOR_VALUE = Color(0xffbbffff);
const Dimension SIZE_VALUE = 1.2_px;

const int32_t DAY_VALUE = 1;
const int32_t MONTH_VALUE = 1;
const int32_t YEAR_VALUE = 1;
const int32_t INDEX_VALUE = 1;
const int32_t FIRST_DAY_INDEX_VALUE = 1;
const std::string LUNAR_MONTH_VALUE = "五月";
const std::string LUNAR_DAY_VALUE = "初五";
const std::string DAY_MARK = "MARK";
const std::string DAY_MARK_VALUE = "MARK_VALUE";
const std::string OFF_DAYS_VALUE = "OFF_DAYS";
} // namespace

class CalendarPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateCalendarNode(TestProperty& testProperty);
};

void CalendarPatternTestNg::SetUpTestSuite() {}

void CalendarPatternTestNg::TearDownTestSuite() {}

RefPtr<FrameNode> CalendarPatternTestNg::CreateCalendarNode(TestProperty& testProperty)
{
    return nullptr;
}

/**
 * @tc.name: CalendarViewTest001
 * @tc.desc: Create Calendar.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPatternTestNg, CalendarViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     *            case: property are all unset
     * @tc.expected: step1. Create Calendar successfully
     */
    CalendarData calendarData;
    CalendarView::Create(calendarData);
    CurrentDayStyle dayStyle;
    CalendarView::SetCurrentDayStyle(dayStyle);
    NonCurrentDayStyle nonCurrentDayStyle;
    CalendarView::SetNonCurrentDayStyle(nonCurrentDayStyle);
    TodayStyle todayStyle;
    CalendarView::SetTodayStyle(todayStyle);
    WeekStyle weekStyle;
    CalendarView::SetWeekStyle(weekStyle);
    WorkStateStyle workStateStyle;
    CalendarView::SetWorkStateStyle(workStateStyle);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_ETS_TAG);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(element);
    auto calendarPattern = frameNode1->GetPattern<CalendarPattern>();
    EXPECT_TRUE(calendarPattern);
    EXPECT_FALSE(calendarPattern->calendarControllerNg_);

    /**
     * @tc.steps: step2. Create Calendar
     *            case: properties are all set
     * @tc.expected: step2. Create Calendar successfully & properties are set successfully
     */
    // properties related with color are all set to COLOR_VALUE, related with size are all set to SIZE_VALUE
    dayStyle.UpdateDayColor(COLOR_VALUE);
    dayStyle.UpdateLunarColor(COLOR_VALUE);
    dayStyle.UpdateMarkLunarColor(COLOR_VALUE);
    dayStyle.UpdateDayFontSize(SIZE_VALUE);
    dayStyle.UpdateLunarDayFontSize(SIZE_VALUE);
    dayStyle.UpdateDayHeight(SIZE_VALUE);
    dayStyle.UpdateDayWidth(SIZE_VALUE);
    dayStyle.UpdateGregorianCalendarHeight(SIZE_VALUE);
    dayStyle.UpdateDayYAxisOffset(SIZE_VALUE);
    dayStyle.UpdateLunarDayYAxisOffset(SIZE_VALUE);
    dayStyle.UpdateUnderscoreXAxisOffset(SIZE_VALUE);
    dayStyle.UpdateUnderscoreYAxisOffset(SIZE_VALUE);
    dayStyle.UpdateScheduleMarkerXAxisOffset(SIZE_VALUE);
    dayStyle.UpdateScheduleMarkerYAxisOffset(SIZE_VALUE);
    dayStyle.UpdateColSpace(SIZE_VALUE);
    dayStyle.UpdateDailyFiveRowSpace(SIZE_VALUE);
    dayStyle.UpdateDailySixRowSpace(SIZE_VALUE);
    dayStyle.UpdateLunarHeight(SIZE_VALUE);
    dayStyle.UpdateUnderscoreWidth(SIZE_VALUE);
    dayStyle.UpdateUnderscoreLength(SIZE_VALUE);
    dayStyle.UpdateScheduleMarkerRadius(SIZE_VALUE);
    dayStyle.UpdateBoundaryRowOffset(SIZE_VALUE);
    dayStyle.UpdateBoundaryColOffset(SIZE_VALUE);

    nonCurrentDayStyle.UpdateNonCurrentMonthDayColor(COLOR_VALUE);
    nonCurrentDayStyle.UpdateNonCurrentMonthLunarColor(COLOR_VALUE);
    nonCurrentDayStyle.UpdateNonCurrentMonthWorkDayMarkColor(COLOR_VALUE);
    nonCurrentDayStyle.UpdateNonCurrentMonthOffDayMarkColor(COLOR_VALUE);

    todayStyle.UpdateFocusedDayColor(COLOR_VALUE);
    todayStyle.UpdateFocusedLunarColor(COLOR_VALUE);
    todayStyle.UpdateFocusedAreaBackgroundColor(COLOR_VALUE);
    todayStyle.UpdateFocusedAreaRadius(SIZE_VALUE);

    weekStyle.UpdateWeekColor(COLOR_VALUE);
    weekStyle.UpdateWeekendDayColor(COLOR_VALUE);
    weekStyle.UpdateWeekendLunarColor(COLOR_VALUE);
    weekStyle.UpdateWeekFontSize(SIZE_VALUE);
    weekStyle.UpdateWeekHeight(SIZE_VALUE);
    weekStyle.UpdateWeekWidth(SIZE_VALUE);
    weekStyle.UpdateWeekAndDayRowSpace(SIZE_VALUE);

    workStateStyle.UpdateWorkDayMarkColor(COLOR_VALUE);
    workStateStyle.UpdateOffDayMarkColor(COLOR_VALUE);
    workStateStyle.UpdateWorkDayMarkSize(SIZE_VALUE);
    workStateStyle.UpdateOffDayMarkSize(SIZE_VALUE);
    workStateStyle.UpdateWorkStateWidth(SIZE_VALUE);
    workStateStyle.UpdateWorkStateHorizontalMovingDistance(SIZE_VALUE);
    workStateStyle.UpdateWorkStateVerticalMovingDistance(SIZE_VALUE);

    // case: controller is not null
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    CalendarView::Create(calendarData);
    CalendarView::SetCurrentDayStyle(dayStyle);
    CalendarView::SetNonCurrentDayStyle(nonCurrentDayStyle);
    CalendarView::SetTodayStyle(todayStyle);
    CalendarView::SetWeekStyle(weekStyle);
    CalendarView::SetWorkStateStyle(workStateStyle);
    element = ViewStackProcessor::GetInstance()->Finish();

    EXPECT_EQ(element->GetTag(), V2::CALENDAR_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_TRUE(frameNode);
    calendarPattern = frameNode->GetPattern<CalendarPattern>();
    EXPECT_TRUE(calendarPattern);
    EXPECT_TRUE(calendarPattern->calendarControllerNg_);
    auto swiperNode = frameNode->GetChildren().front();
    ASSERT_TRUE(swiperNode);
    auto calendarFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().front());
    ASSERT_TRUE(calendarFrameNode);
    auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();

    // CurrentDayStyle
    EXPECT_EQ(calendarPaintProperty->GetDayColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetLunarColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetMarkLunarColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetDayFontSizeValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetLunarDayFontSizeValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetDayHeightValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetDayWidthValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetGregorianCalendarHeightValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetDayYAxisOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetLunarDayYAxisOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetUnderscoreXAxisOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetUnderscoreYAxisOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetScheduleMarkerXAxisOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetScheduleMarkerYAxisOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetColSpaceValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetDailyFiveRowSpaceValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetDailySixRowSpaceValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetLunarHeightValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetUnderscoreWidthValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetUnderscoreLengthValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetScheduleMarkerRadiusValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetBoundaryRowOffsetValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetBoundaryColOffsetValue(1.0_px), SIZE_VALUE);

    // NonCurrentDayStyle
    EXPECT_EQ(calendarPaintProperty->GetNonCurrentMonthDayColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetNonCurrentMonthLunarColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetNonCurrentMonthWorkDayMarkColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetNonCurrentMonthOffDayMarkColorValue(Color::RED), COLOR_VALUE);

    // TodayStyle
    EXPECT_EQ(calendarPaintProperty->GetFocusedDayColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetFocusedLunarColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetFocusedAreaBackgroundColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetFocusedAreaRadiusValue(1.0_px), SIZE_VALUE);

    // WeekStyle
    EXPECT_EQ(calendarPaintProperty->GetWeekColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWeekendDayColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWeekendLunarColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWeekFontSizeValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWeekHeightValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWeekWidthValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWeekAndDayRowSpaceValue(1.0_px), SIZE_VALUE);

    // WorkStateStyle
    EXPECT_EQ(calendarPaintProperty->GetWorkDayMarkColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetOffDayMarkColorValue(Color::RED), COLOR_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWorkDayMarkSizeValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetOffDayMarkSizeValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWorkStateWidthValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWorkStateHorizontalMovingDistanceValue(1.0_px), SIZE_VALUE);
    EXPECT_EQ(calendarPaintProperty->GetWorkStateVerticalMovingDistanceValue(1.0_px), SIZE_VALUE);
}

HWTEST_F(CalendarPatternTestNg, CalendarViewTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<CalendarPattern> initPattern = AceType::MakeRefPtr<CalendarPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("testNode", 1, initPattern);
    stack->Push(frameNode);
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = YEAR_VALUE;
    obtainedMonth.month = MONTH_VALUE;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;
    CalendarView::SetCurrentData(obtainedMonth);
    CalendarView::SetPreData(obtainedMonth);
    CalendarView::SetNextData(obtainedMonth);

    CalendarDay calendarDay;
    calendarDay.index = INDEX_VALUE;
    calendarDay.day = DAY_VALUE;
    calendarDay.weekend = true;
    calendarDay.today = false;
    calendarDay.focused = false;
    calendarDay.touched = true;
    calendarDay.isFirstOfLunar = false;
    calendarDay.hasSchedule = true;
    calendarDay.markLunarDay = false;
    calendarDay.lunarMonth = LUNAR_MONTH_VALUE;
    calendarDay.lunarDay = LUNAR_DAY_VALUE;
    calendarDay.dayMark = DAY_MARK;
    calendarDay.dayMarkValue = DAY_MARK_VALUE;
    CalendarMonth calendarMonth;
    calendarMonth.year = YEAR_VALUE;
    calendarMonth.month = MONTH_VALUE;
    calendarDay.month = calendarMonth;
    CalendarView::SetCalendarDay(calendarDay);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNode()->GetPattern<CalendarPattern>();

    EXPECT_EQ(pattern->GetCurrentMonthData().year, YEAR_VALUE);
    EXPECT_EQ(pattern->GetCurrentMonthData().month, MONTH_VALUE);
    EXPECT_EQ(pattern->GetCurrentMonthData().firstDayIndex, FIRST_DAY_INDEX_VALUE);
    EXPECT_EQ(pattern->GetPreMonthData().year, YEAR_VALUE);
    EXPECT_EQ(pattern->GetPreMonthData().month, MONTH_VALUE);
    EXPECT_EQ(pattern->GetPreMonthData().firstDayIndex, FIRST_DAY_INDEX_VALUE);
    EXPECT_EQ(pattern->GetNextMonthData().year, YEAR_VALUE);
    EXPECT_EQ(pattern->GetNextMonthData().month, MONTH_VALUE);
    EXPECT_EQ(pattern->GetNextMonthData().firstDayIndex, FIRST_DAY_INDEX_VALUE);

    EXPECT_EQ(pattern->GetCalendarDay().index, INDEX_VALUE);
    EXPECT_EQ(pattern->GetCalendarDay().day, DAY_VALUE);
    EXPECT_TRUE(pattern->GetCalendarDay().weekend);
    EXPECT_FALSE(pattern->GetCalendarDay().today);
    EXPECT_FALSE(pattern->GetCalendarDay().focused);
    EXPECT_TRUE(pattern->GetCalendarDay().touched);
    EXPECT_FALSE(pattern->GetCalendarDay().isFirstOfLunar);
    EXPECT_TRUE(pattern->GetCalendarDay().hasSchedule);
    EXPECT_FALSE(pattern->GetCalendarDay().markLunarDay);
    EXPECT_EQ(pattern->GetCalendarDay().lunarMonth, LUNAR_MONTH_VALUE);
    EXPECT_EQ(pattern->GetCalendarDay().lunarDay, LUNAR_DAY_VALUE);
    EXPECT_EQ(pattern->GetCalendarDay().dayMark, DAY_MARK);
    EXPECT_EQ(pattern->GetCalendarDay().dayMarkValue, DAY_MARK_VALUE);
    EXPECT_EQ(pattern->GetCalendarDay().month.year, YEAR_VALUE);
    EXPECT_EQ(pattern->GetCalendarDay().month.month, MONTH_VALUE);
}

HWTEST_F(CalendarPatternTestNg, CalendarViewTest003, TestSize.Level1)
{
    CalendarData calendarData;
    CalendarView::Create(calendarData);
    CalendarView::SetShowLunar(false);
    CalendarView::SetShowHoliday(false);
    CalendarView::SetNeedSlide(true);
    CalendarView::SetStartOfWeek(Week::Sun);
    CalendarView::SetOffDays(OFF_DAYS_VALUE);
    CalendarView::SetDirection(Axis::HORIZONTAL);

    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetFirstChild();
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto calendarFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetFirstChild());
    auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();

    EXPECT_FALSE(calendarPaintProperty->GetShowLunarValue());
    EXPECT_FALSE(calendarPaintProperty->GetShowHolidayValue());
    EXPECT_FALSE(swiperPaintProperty->GetDisableSwipeValue());
    EXPECT_EQ(calendarPaintProperty->GetStartOfWeekValue(), Week::Sun);
    EXPECT_EQ(calendarPaintProperty->GetOffDaysValue(), OFF_DAYS_VALUE);
    EXPECT_EQ(swiperLayoutProperty->GetDirectionValue(), Axis::HORIZONTAL);
}
} // namespace OHOS::Ace::NG
