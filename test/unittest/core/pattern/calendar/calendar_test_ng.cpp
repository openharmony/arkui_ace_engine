/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_method.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
struct TestProperty {};
namespace {
const InspectorFilter filter;
const Color COLOR_VALUE = Color(0xffbbffff);
const Dimension SIZE_VALUE = 1.2_px;

const int32_t DAY_VALUE = 1;
const int32_t MONTH_VALUE = 1;
const int32_t YEAR_VALUE = 1;
const int32_t INDEX_VALUE = 1;
const int32_t JUMP_YEAR = 2023;
const int32_t JUMP_MONTH = 3;
const int32_t JUMP_DAY_FIRST = 3;
const int32_t JUMP_DAY_SECOND = 13;
const int32_t JUMP_DAY_THIRD = 23;
const int32_t DEFAULT_FOCUS_RADIUS = 15;
const int32_t WEEKS_COUNT_FIVE = 5;
const int32_t WEEKS_COUNT_SIX = 6;
const int32_t FIRST_DAY_INDEX_VALUE = 1;
const std::string LUNAR_MONTH_VALUE = "五月";
const std::string LUNAR_DAY_VALUE = "初五";
const std::string DAY_MARK = "MARK";
const std::string DAY_MARK_VALUE = "MARK_VALUE";
const std::string OFF_DAYS_VALUE = "OFF_DAYS";
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
const float VALID_LENGTH = 10;
const std::string WORK_DAY_MARK = "work";
const std::string OFF_DAY_MARK = "off";

// Day width and Height.
const Dimension DAY_HEIGHT = 48.0_vp;
const Dimension DAY_WIDTH = 48.0_vp;

// GregorianDay YAxis Offset and Height.
const Dimension GREGORIAN_DAY_HEIGHT = 20.0_vp;
const Dimension GREGORIAN_DAY_OFFSET = 4.0_vp;

// Lunar YAxis Offset and Height.
const Dimension LUNAR_DAY_HEIGHT = 10.0_vp;
const Dimension LUNAR_DAY_OFFSET = 2.0_vp;
} // namespace

class CalendarTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateCalendarNode(TestProperty& testProperty);
};

void CalendarTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void CalendarTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CalendarTestNg::CreateCalendarNode(TestProperty& testProperty)
{
    return nullptr;
}

/**
 * @tc.name: CalendarModelNGTest001
 * @tc.desc: Create Calendar.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     *            case: property are all unset
     * @tc.expected: step1. Create Calendar successfully
     */
    CalendarModelData calendarData;
    CalendarModelNG calendarModelNG;
    calendarModelNG.Create(calendarData);
    CurrentDayStyleData dayStyle;
    calendarModelNG.SetCurrentDayStyle(dayStyle, dayStyle);
    NonCurrentDayStyleData nonCurrentDayStyle;
    calendarModelNG.SetNonCurrentDayStyle(nonCurrentDayStyle);
    TodayStyleData todayStyle;
    calendarModelNG.SetTodayStyle(todayStyle);
    WeekStyleData weekStyle;
    calendarModelNG.SetWeekStyle(weekStyle);
    WorkStateStyleData workStateStyle;
    calendarModelNG.SetWorkStateStyle(workStateStyle);

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
    dayStyle.dayColor = std::make_optional(COLOR_VALUE);
    dayStyle.lunarColor = std::make_optional(COLOR_VALUE);
    dayStyle.markLunarColor = std::make_optional(COLOR_VALUE);
    dayStyle.dayFontSize = std::make_optional(SIZE_VALUE);
    dayStyle.lunarDayFontSize = std::make_optional(SIZE_VALUE);
    dayStyle.dayHeight = std::make_optional(SIZE_VALUE);
    dayStyle.dayWidth = std::make_optional(SIZE_VALUE);
    dayStyle.gregorianCalendarHeight = std::make_optional(SIZE_VALUE);
    dayStyle.lunarHeight = std::make_optional(SIZE_VALUE);
    dayStyle.dayYAxisOffset = std::make_optional(SIZE_VALUE);
    dayStyle.lunarDayYAxisOffset = std::make_optional(SIZE_VALUE);
    dayStyle.underscoreXAxisOffset = std::make_optional(SIZE_VALUE);
    dayStyle.underscoreYAxisOffset = std::make_optional(SIZE_VALUE);
    dayStyle.scheduleMarkerXAxisOffset = std::make_optional(SIZE_VALUE);
    dayStyle.scheduleMarkerYAxisOffset = std::make_optional(SIZE_VALUE);
    dayStyle.colSpace = std::make_optional(SIZE_VALUE);
    dayStyle.dailyFiveRowSpace = std::make_optional(SIZE_VALUE);
    dayStyle.dailySixRowSpace = std::make_optional(SIZE_VALUE);
    dayStyle.underscoreWidth = std::make_optional(SIZE_VALUE);
    dayStyle.underscoreLength = std::make_optional(SIZE_VALUE);
    dayStyle.scheduleMarkerRadius = std::make_optional(SIZE_VALUE);
    dayStyle.boundaryRowOffset = std::make_optional(SIZE_VALUE);
    dayStyle.boundaryColOffset = std::make_optional(SIZE_VALUE);
    dayStyle.touchCircleStrokeWidth = std::make_optional(SIZE_VALUE);

    nonCurrentDayStyle.nonCurrentMonthDayColor = std::make_optional(COLOR_VALUE);
    nonCurrentDayStyle.nonCurrentMonthLunarColor = std::make_optional(COLOR_VALUE);
    nonCurrentDayStyle.nonCurrentMonthWorkDayMarkColor = std::make_optional(COLOR_VALUE);
    nonCurrentDayStyle.nonCurrentMonthOffDayMarkColor = std::make_optional(COLOR_VALUE);

    todayStyle.focusedDayColor = std::make_optional(COLOR_VALUE);
    todayStyle.focusedLunarColor = std::make_optional(COLOR_VALUE);
    todayStyle.focusedAreaBackgroundColor = std::make_optional(COLOR_VALUE);
    todayStyle.focusedAreaRadius = std::make_optional(SIZE_VALUE);

    weekStyle.weekColor = std::make_optional(COLOR_VALUE);
    weekStyle.weekendDayColor = std::make_optional(COLOR_VALUE);
    weekStyle.weekendLunarColor = std::make_optional(COLOR_VALUE);
    weekStyle.weekFontSize = std::make_optional(SIZE_VALUE);
    weekStyle.weekHeight = std::make_optional(SIZE_VALUE);
    weekStyle.weekWidth = std::make_optional(SIZE_VALUE);
    weekStyle.weekAndDayRowSpace = std::make_optional(SIZE_VALUE);

    workStateStyle.workDayMarkColor = std::make_optional(COLOR_VALUE);
    workStateStyle.offDayMarkColor = std::make_optional(COLOR_VALUE);
    workStateStyle.workDayMarkSize = std::make_optional(SIZE_VALUE);
    workStateStyle.offDayMarkSize = std::make_optional(SIZE_VALUE);
    workStateStyle.workStateWidth = std::make_optional(SIZE_VALUE);
    workStateStyle.workStateHorizontalMovingDistance = std::make_optional(SIZE_VALUE);
    workStateStyle.workStateVerticalMovingDistance = std::make_optional(SIZE_VALUE);

    // case: controller is not null
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    calendarModelNG.Create(calendarData);
    calendarModelNG.SetCurrentDayStyle(dayStyle, dayStyle);
    calendarModelNG.SetNonCurrentDayStyle(nonCurrentDayStyle);
    calendarModelNG.SetTodayStyle(todayStyle);
    calendarModelNG.SetWeekStyle(weekStyle);
    calendarModelNG.SetWorkStateStyle(workStateStyle);
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

HWTEST_F(CalendarTestNg, CalendarModelNGTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<CalendarPattern> initPattern = AceType::MakeRefPtr<CalendarPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("testNode", 1, initPattern);
    stack->Push(frameNode);
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = YEAR_VALUE;
    obtainedMonth.month = MONTH_VALUE;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;
    CalendarModelNG calendarModelNG;
    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);

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
    calendarModelNG.SetCalendarDay(calendarDay);
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

HWTEST_F(CalendarTestNg, CalendarModelNGTest003, TestSize.Level1)
{
    CalendarModelData calendarData;
    CalendarModelNG calendarModelNG;
    calendarModelNG.Create(calendarData);
    calendarModelNG.SetShowLunar(false);
    calendarModelNG.SetShowHoliday(false);
    calendarModelNG.SetNeedSlide(true);
    calendarModelNG.SetStartOfWeek(static_cast<int32_t>(Week::Sun));
    calendarModelNG.SetOffDays(OFF_DAYS_VALUE);
    calendarModelNG.SetDirection(static_cast<int32_t>(Axis::HORIZONTAL));

    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperNode = stack->GetMainFrameNode()->GetFirstChild();
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    auto swiperPaintProperty = swiperFrameNode->GetPaintProperty<SwiperPaintProperty>();
    auto swiperLayoutProperty = swiperFrameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto calendarFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetFirstChild());
    auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();

    EXPECT_FALSE(calendarPaintProperty->GetShowLunarValue());
    EXPECT_FALSE(calendarPaintProperty->GetShowHolidayValue());
    EXPECT_FALSE(swiperLayoutProperty->GetDisableSwipeValue());
    EXPECT_EQ(calendarPaintProperty->GetStartOfWeekValue(), Week::Sun);
    EXPECT_EQ(calendarPaintProperty->GetOffDaysValue(), OFF_DAYS_VALUE);
    EXPECT_EQ(swiperLayoutProperty->GetDirectionValue(), Axis::HORIZONTAL);
}

/**
 * @tc.name: CalendarTest004
 * @tc.desc: Create calendar, and invoke its JumpTo function to calculate the date.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     * @tc.expected: step1. Create Calendar successfully.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<CalendarPattern> calendar = AceType::MakeRefPtr<CalendarPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("testNode", 1, calendar);
    stack->Push(frameNode);
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = JUMP_YEAR;
    obtainedMonth.month = JUMP_MONTH;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;

    // Add 31 days.
    std::vector<CalendarDay> days;
    for (int32_t i = 0; i < 31; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH;
        day.day = i + 1;
        if (i == 1) {
            day.focused = true;
        }
        days.emplace_back(std::move(day));
    }
    obtainedMonth.days = days;
    CalendarModelNG calendarModelNG;
    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);

    CalendarDay calendarDay;
    calendarDay.index = INDEX_VALUE;
    calendarDay.day = DAY_VALUE;
    calendarDay.today = false;
    calendarDay.focused = true;
    calendarDay.touched = true;

    /**
     * @tc.steps: step2. Jump to destination from 1 to 3.
     * @tc.expected: step2. Jumped successfully, the focused changed from 1 to 3.
     */
    CalendarMonth calendarMonth;
    calendarMonth.year = JUMP_YEAR;
    calendarMonth.month = JUMP_MONTH;
    calendarDay.month = calendarMonth;
    calendarModelNG.SetCalendarDay(calendarDay);

    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNode()->GetPattern<CalendarPattern>();
    pattern->FireGoToRequestData(JUMP_YEAR, JUMP_MONTH, JUMP_DAY_FIRST);
    pattern->JumpTo(pattern->currentMonth_);
    EXPECT_EQ(pattern->currentMonth_.days[JUMP_DAY_FIRST - 1].focused, true);

    /**
     * @tc.steps: step3. Jump to destination from 3 to 13.
     * @tc.expected: step3. Jumped successfully, the focused changed from 3 to 13.
     */
    pattern->FireGoToRequestData(JUMP_YEAR, JUMP_MONTH, JUMP_DAY_SECOND);
    pattern->JumpTo(pattern->currentMonth_);
    EXPECT_EQ(pattern->currentMonth_.days[JUMP_DAY_SECOND - 1].focused, true);

    /**
     * @tc.steps: step4. Jump to destination from 13 to 23.
     * @tc.expected: step4. Jumped successfully, the focused changed from 13 to 23.
     */
    pattern->FireGoToRequestData(JUMP_YEAR, JUMP_MONTH, JUMP_DAY_THIRD);
    pattern->JumpTo(pattern->currentMonth_);
    EXPECT_EQ(pattern->currentMonth_.days[JUMP_DAY_THIRD - 1].focused, true);

    /**
     * @tc.steps: step5. Jump to destination from 23 to 3.
     * @tc.expected: step5. Jumped successfully, the focused changed from 23 to 3.
     */
    pattern->FireGoToRequestData(JUMP_YEAR, JUMP_MONTH, JUMP_DAY_FIRST);
    pattern->JumpTo(pattern->currentMonth_);
    EXPECT_EQ(pattern->currentMonth_.days[JUMP_DAY_FIRST - 1].focused, true);
}

/**
 * @tc.name: CalendarTest005
 * @tc.desc: Create calendar, and check the 6 rows (42 days).
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     * @tc.expected: step1. Create Calendar successfully.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<CalendarPattern> calendar = AceType::MakeRefPtr<CalendarPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("testNode", 1, calendar);
    stack->Push(frameNode);
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = JUMP_YEAR;
    obtainedMonth.month = JUMP_MONTH;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;

    // Add 42 days totally.
    // Add 31 days in March.
    std::vector<CalendarDay> days;
    for (int32_t i = 0; i < 31; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH;
        day.day = i + 1;
        if (i == 1) {
            day.focused = true;
        }
        days.emplace_back(std::move(day));
    }

    // Add 11 days in April.
    for (int32_t i = 31; i < 42; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH + 1;
        day.day = i - 30;
        days.emplace_back(std::move(day));
    }

    obtainedMonth.days = days;
    CalendarModelNG calendarModelNG;
    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);

    CalendarDay calendarDay;
    calendarDay.index = INDEX_VALUE;
    calendarDay.day = DAY_VALUE;
    calendarDay.today = false;
    calendarDay.focused = true;
    calendarDay.touched = true;

    /**
     * @tc.steps: step2. Set 42 days in a month.
     * @tc.expected: step2. The rows of month is 6.
     */
    CalendarMonth calendarMonth;
    calendarMonth.year = JUMP_YEAR;
    calendarMonth.month = JUMP_MONTH;
    calendarDay.month = calendarMonth;
    calendarModelNG.SetCalendarDay(calendarDay);

    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    paintMethod->DrawWeekAndDates(rsCanvas, Offset(0, 0));
    EXPECT_EQ(paintMethod->rowCount_, WEEKS_COUNT_SIX);
}

/**
 * @tc.name: CalendarTest006
 * @tc.desc: Create calendar, and check the 5 rows (35 days).
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     * @tc.expected: step1. Create Calendar successfully.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    RefPtr<CalendarPattern> calendar = AceType::MakeRefPtr<CalendarPattern>();
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("testNode", 1, calendar);
    stack->Push(frameNode);
    ObtainedMonth obtainedMonth;
    obtainedMonth.year = JUMP_YEAR;
    obtainedMonth.month = JUMP_MONTH;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;

    // Add 35 days totally.
    // Add 31 days in March.
    std::vector<CalendarDay> days;
    for (int32_t i = 0; i < 31; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH;
        day.day = i + 1;
        if (i == 1) {
            day.focused = true;
        }
        days.emplace_back(std::move(day));
    }

    // Add 4 days in April.
    for (int32_t i = 31; i < 35; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH + 1;
        day.day = i - 30;
        days.emplace_back(std::move(day));
    }

    obtainedMonth.days = days;
    CalendarModelNG calendarModelNG;
    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);

    CalendarDay calendarDay;
    calendarDay.index = INDEX_VALUE;
    calendarDay.day = DAY_VALUE;

    /**
     * @tc.steps: step2. Set 35days in a month.
     * @tc.expected: step2. The rows of month is 5.
     */
    CalendarMonth calendarMonth;
    calendarMonth.year = JUMP_YEAR;
    calendarMonth.month = JUMP_MONTH;
    calendarDay.month = calendarMonth;
    calendarModelNG.SetCalendarDay(calendarDay);

    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    paintMethod->DrawWeekAndDates(rsCanvas, Offset(0, 0));
    EXPECT_EQ(paintMethod->rowCount_, WEEKS_COUNT_FIVE);
}

/**
 * @tc.name: CalendarTest007
 * @tc.desc: Create calendar, and check the todayStyle focus status.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     * @tc.expected: step1. Create Calendar successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    // Today style.
    TodayStyle todayStyle;
    Color focusedDayColor = Color::WHITE;
    todayStyle.UpdateFocusedDayColor(focusedDayColor);
    Color focusedLunarColor = Color::WHITE;
    todayStyle.UpdateFocusedLunarColor(focusedLunarColor);
    Color focusedAreaBackgroundColor = Color::BLUE;
    todayStyle.UpdateFocusedAreaBackgroundColor(focusedAreaBackgroundColor);
    Dimension focusedAreaRadius = Dimension(DEFAULT_FOCUS_RADIUS, DimensionUnit::VP);
    todayStyle.UpdateFocusedAreaRadius(focusedAreaRadius);

    // Day style of current month.
    CurrentDayStyle dayStyle;
    dayStyle.UpdateDayColor(Color::BLACK);

    CalendarModelData calendarData;
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    CalendarModelNG calendarModelNG;
    calendarModelNG.Create(calendarData);
    calendarModelNG.SetTodayStyle(todayStyle);
    calendarModelNG.SetCurrentDayStyle(dayStyle);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();

    EXPECT_EQ(element->GetTag(), V2::CALENDAR_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    auto swiperNode = frameNode->GetChildren().front();
    auto calendarFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().front());
    auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();

    ObtainedMonth obtainedMonth;
    obtainedMonth.year = JUMP_YEAR;
    obtainedMonth.month = JUMP_MONTH;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;

    // Add 31 days.
    std::vector<CalendarDay> days;
    for (int32_t i = 0; i < 31; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH;
        day.day = i + 1;
        if (i == 0) {
            day.focused = true;
        }
        days.emplace_back(std::move(day));
    }
    obtainedMonth.days = days;

    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);

    CalendarDay calendarDay;
    calendarDay.index = INDEX_VALUE;
    calendarDay.day = DAY_VALUE;
    calendarDay.today = false;
    calendarDay.focused = true;
    calendarDay.touched = true;

    /**
     * @tc.steps: step2. Set the first day focused, check the first day text style.
     * @tc.expected: step2. The text color is 0xffffffff.
     */
    CalendarMonth calendarMonth;
    calendarMonth.year = JUMP_YEAR;
    calendarMonth.month = JUMP_MONTH;
    calendarDay.month = calendarMonth;
    calendarModelNG.SetCalendarDay(calendarDay);

    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    paintMethod->SetCalendarTheme(calendarPaintProperty);
    RSTextStyle dateTextStyle;
    RSTextStyle lunarTextStyle;
    paintMethod->InitTextStyle(dateTextStyle, lunarTextStyle);

    paintMethod->SetDayTextStyle(dateTextStyle, lunarTextStyle, obtainedMonth.days[0]);

#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(dateTextStyle.color_, RSColor(0xffffffff));
    EXPECT_EQ(lunarTextStyle.color_, RSColor(0xffffffff));
#else
    EXPECT_EQ(dateTextStyle.color, RSColor(0xffffffff));
    EXPECT_EQ(lunarTextStyle.color, RSColor(0xffffffff));
#endif

    /**
     * @tc.steps: step3. Set the first day focused, check the second day text style.
     * @tc.expected: step3. The text color is 0xff000000.
     */
    paintMethod->SetDayTextStyle(dateTextStyle, lunarTextStyle, obtainedMonth.days[1]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(dateTextStyle.color_, RSColor(0xff000000));
    EXPECT_EQ(lunarTextStyle.color_, RSColor(0xff000000));
#else
    EXPECT_EQ(dateTextStyle.color, RSColor(0xff000000));
    EXPECT_EQ(lunarTextStyle.color, RSColor(0xff000000));
#endif
}

/**
 * @tc.name: CalendarTest008
 * @tc.desc: Create calendar, and check the gregorianDayYAxisOffset.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     * @tc.expected: step1. Create Calendar successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    // Today style.
    TodayStyle todayStyle;
    Color focusedDayColor = Color::WHITE;
    todayStyle.UpdateFocusedDayColor(focusedDayColor);
    Color focusedLunarColor = Color::WHITE;
    todayStyle.UpdateFocusedLunarColor(focusedLunarColor);
    Color focusedAreaBackgroundColor = Color::BLUE;
    todayStyle.UpdateFocusedAreaBackgroundColor(focusedAreaBackgroundColor);
    Dimension focusedAreaRadius = Dimension(DEFAULT_FOCUS_RADIUS, DimensionUnit::VP);
    todayStyle.UpdateFocusedAreaRadius(focusedAreaRadius);

    // Day style of current month.
    CurrentDayStyle dayStyle;
    dayStyle.UpdateDayColor(Color::BLACK);
    dayStyle.UpdateLunarColor(COLOR_VALUE);
    dayStyle.UpdateDayHeight(DAY_HEIGHT);
    dayStyle.UpdateDayWidth(DAY_WIDTH);
    dayStyle.UpdateGregorianCalendarHeight(GREGORIAN_DAY_HEIGHT);
    dayStyle.UpdateDayYAxisOffset(GREGORIAN_DAY_OFFSET);
    dayStyle.UpdateLunarDayYAxisOffset(LUNAR_DAY_OFFSET);
    dayStyle.UpdateLunarHeight(LUNAR_DAY_HEIGHT);

    CalendarData calendarData;
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    CalendarModelNG calendarModel;
    calendarModel.Create(calendarData);
    calendarModel.SetTodayStyle(todayStyle);
    calendarModel.SetCurrentDayStyle(dayStyle);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();

    EXPECT_EQ(element->GetTag(), V2::CALENDAR_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    auto swiperNode = frameNode->GetChildren().front();
    auto calendarFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().front());
    auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();

    /**
     * @tc.steps: step1. Check the offset and height.
     * @tc.expected: step1. Get the offset and height successfully.
     */
    EXPECT_EQ(calendarPaintProperty->GetDayHeightValue(SIZE_VALUE), DAY_HEIGHT);
    EXPECT_EQ(calendarPaintProperty->GetDayWidthValue(SIZE_VALUE), DAY_WIDTH);
    EXPECT_EQ(calendarPaintProperty->GetGregorianCalendarHeightValue(SIZE_VALUE), GREGORIAN_DAY_HEIGHT);
    EXPECT_EQ(calendarPaintProperty->GetDayYAxisOffsetValue(SIZE_VALUE), GREGORIAN_DAY_OFFSET);
    EXPECT_EQ(calendarPaintProperty->GetLunarDayYAxisOffsetValue(SIZE_VALUE), LUNAR_DAY_OFFSET);
    EXPECT_EQ(calendarPaintProperty->GetLunarHeightValue(SIZE_VALUE), LUNAR_DAY_HEIGHT);
}

/**
 * @tc.name: CalendarPatternTest001
 * @tc.desc: Test CalendarPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPatternTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    EXPECT_FALSE(calendarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, true, true));
}

/**
 * @tc.name: CalendarPatternTest002
 * @tc.desc: Test CalendarPattern OnModifyDone ChangeDoneEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPatternTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    swiperNode->MountToParent(frameNode);
    for (int i = 0; i < 3; i++) {
        auto monthNode =
            FrameNode::GetOrCreateFrameNode(V2::CALENDAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
        monthNode->MountToParent(swiperNode);
    }
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);

    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(swiperNode);
    ASSERT_NE(swiperFrameNode, nullptr);
    auto swiperEventHub = swiperFrameNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(swiperEventHub, nullptr);
    auto calendarEventHub = frameNode->GetEventHub<CalendarEventHub>();
    ASSERT_NE(calendarEventHub, nullptr);

    calendarPattern->initialize_ = true;
    calendarPattern->currentMonth_.days.clear();
    auto currentMonth = calendarPattern->calendarDay_.month;
    std::string infoDetail;
    auto initRequestDataEvent = [&](std::string info) { infoDetail = std::move(info); };
    calendarEventHub->SetOnRequestDataEvent(initRequestDataEvent);
    calendarPattern->OnModifyDone();
    auto json = JsonUtil::ParseJsonString(infoDetail);
    EXPECT_EQ(json->GetInt("currentYear"), currentMonth.year);
    EXPECT_EQ(json->GetInt("currentMonth"), currentMonth.month);
    EXPECT_EQ(json->GetInt("year"), currentMonth.year);
    EXPECT_EQ(json->GetInt("month"), currentMonth.month);
    EXPECT_EQ(json->GetInt("MonthState"), 0);
    swiperEventHub->FireChangeEvent(1, 2, false);
    swiperEventHub->FireChangeDoneEvent(true);
    json = JsonUtil::ParseJsonString(infoDetail);
    EXPECT_EQ(json->GetInt("MonthState"), 2);
    EXPECT_EQ(json->GetInt("year"), calendarPattern->nextMonth_.year);
    EXPECT_EQ(json->GetInt("month"), calendarPattern->nextMonth_.month);
    EXPECT_EQ(json->GetInt("currentYear"), currentMonth.year);
    EXPECT_EQ(json->GetInt("currentMonth"), currentMonth.month);
    EXPECT_EQ(calendarPattern->GetMoveDirection(), NG::Direction::NEXT);
    swiperEventHub->FireChangeEvent(2, 1, false);
    swiperEventHub->FireChangeDoneEvent(false);
    json = JsonUtil::ParseJsonString(infoDetail);
    EXPECT_EQ(json->GetInt("MonthState"), 1);
    EXPECT_EQ(json->GetInt("year"), calendarPattern->preMonth_.year);
    EXPECT_EQ(json->GetInt("month"), calendarPattern->preMonth_.month);
    EXPECT_EQ(json->GetInt("currentYear"), currentMonth.year);
    EXPECT_EQ(json->GetInt("currentMonth"), currentMonth.month);
    EXPECT_EQ(calendarPattern->GetMoveDirection(), NG::Direction::PRE);

    swiperFrameNode->children_.clear();
    calendarPattern->OnModifyDone();
}

/**
 * @tc.name: CalendarPatternTest003
 * @tc.desc: Test CalendarPattern OnModifyDone currentIndex switch
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPatternTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    swiperNode->MountToParent(frameNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateShowIndicator(false);
    for (int i = 0; i < 3; i++) {
        auto monthNode =
            FrameNode::GetOrCreateFrameNode(V2::CALENDAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
        monthNode->MountToParent(swiperNode);
    }
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);

    auto preFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().front());
    ASSERT_NE(preFrameNode, nullptr);
    auto prePattern = preFrameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(prePattern, nullptr);
    auto iterator = swiperNode->GetChildren().begin();
    auto currentFrameNode = AceType::DynamicCast<FrameNode>(*(++iterator));
    ASSERT_NE(currentFrameNode, nullptr);
    auto currentPattern = currentFrameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(currentPattern, nullptr);
    auto nextFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().back());
    ASSERT_NE(nextFrameNode, nullptr);
    auto nextPattern = nextFrameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(nextPattern, nullptr);

    calendarPattern->backToToday_ = true;
    calendarPattern->goTo_ = true;
    CalendarDay calendarDay;
    calendarDay.month.year = calendarPattern->goToCalendarYear_;
    calendarDay.month.month = calendarPattern->goToCalendarMonth_;
    calendarDay.day = calendarPattern->goToCalendarDay_;
    CalendarDay calendarDay2;
    calendarDay2.day = calendarPattern->goToCalendarDay_ + 1;
    calendarPattern->currentMonth_.days.clear();
    calendarPattern->currentMonth_.days.emplace_back(calendarDay);
    calendarPattern->currentMonth_.days.emplace_back(calendarDay2);

    swiperPattern->currentIndex_ = 0;
    calendarPattern->initialize_ = false;
    calendarPattern->OnModifyDone();
    EXPECT_TRUE(calendarPattern->currentMonth_.days.front().focused);
    EXPECT_FALSE(calendarPattern->currentMonth_.days.back().focused);
    EXPECT_EQ(prePattern->obtainedMonth_.firstDayIndex, calendarPattern->currentMonth_.firstDayIndex);
    EXPECT_EQ(prePattern->monthState_, MonthState::CUR_MONTH);
    EXPECT_EQ(currentPattern->obtainedMonth_.firstDayIndex, calendarPattern->nextMonth_.firstDayIndex);
    EXPECT_EQ(currentPattern->monthState_, MonthState::NEXT_MONTH);
    EXPECT_EQ(nextPattern->obtainedMonth_.firstDayIndex, calendarPattern->preMonth_.firstDayIndex);
    EXPECT_EQ(nextPattern->monthState_, MonthState::PRE_MONTH);
    EXPECT_EQ(prePattern->GetCalendarDay().day, calendarPattern->GetCalendarDay().day);

    calendarPattern->OnModifyDone();
    EXPECT_EQ(prePattern->obtainedMonth_.firstDayIndex, calendarPattern->currentMonth_.firstDayIndex);
    EXPECT_EQ(prePattern->monthState_, MonthState::CUR_MONTH);
    EXPECT_EQ(currentPattern->obtainedMonth_.firstDayIndex, calendarPattern->nextMonth_.firstDayIndex);
    EXPECT_EQ(currentPattern->monthState_, MonthState::NEXT_MONTH);
    EXPECT_EQ(nextPattern->obtainedMonth_.firstDayIndex, calendarPattern->preMonth_.firstDayIndex);
    EXPECT_EQ(nextPattern->monthState_, MonthState::PRE_MONTH);

    swiperPattern->currentIndex_ = 1;
    calendarPattern->backToToday_ = true;
    calendarPattern->goTo_ = true;
    calendarPattern->OnModifyDone();
    EXPECT_EQ(prePattern->obtainedMonth_.firstDayIndex, calendarPattern->preMonth_.firstDayIndex);
    EXPECT_EQ(prePattern->monthState_, MonthState::PRE_MONTH);
    EXPECT_EQ(currentPattern->obtainedMonth_.firstDayIndex, calendarPattern->currentMonth_.firstDayIndex);
    EXPECT_EQ(currentPattern->monthState_, MonthState::CUR_MONTH);
    EXPECT_EQ(nextPattern->obtainedMonth_.firstDayIndex, calendarPattern->nextMonth_.firstDayIndex);
    EXPECT_EQ(nextPattern->monthState_, MonthState::NEXT_MONTH);
    EXPECT_EQ(currentPattern->GetCalendarDay().day, calendarPattern->GetCalendarDay().day);

    calendarPattern->OnModifyDone();
    EXPECT_EQ(prePattern->obtainedMonth_.firstDayIndex, calendarPattern->preMonth_.firstDayIndex);
    EXPECT_EQ(prePattern->monthState_, MonthState::PRE_MONTH);
    EXPECT_EQ(currentPattern->obtainedMonth_.firstDayIndex, calendarPattern->currentMonth_.firstDayIndex);
    EXPECT_EQ(currentPattern->monthState_, MonthState::CUR_MONTH);
    EXPECT_EQ(nextPattern->obtainedMonth_.firstDayIndex, calendarPattern->nextMonth_.firstDayIndex);
    EXPECT_EQ(nextPattern->monthState_, MonthState::NEXT_MONTH);

    swiperPattern->currentIndex_ = 2;
    calendarPattern->backToToday_ = true;
    calendarPattern->goTo_ = true;
    calendarPattern->OnModifyDone();
    EXPECT_EQ(prePattern->obtainedMonth_.firstDayIndex, calendarPattern->nextMonth_.firstDayIndex);
    EXPECT_EQ(prePattern->monthState_, MonthState::NEXT_MONTH);
    EXPECT_EQ(currentPattern->obtainedMonth_.firstDayIndex, calendarPattern->preMonth_.firstDayIndex);
    EXPECT_EQ(currentPattern->monthState_, MonthState::PRE_MONTH);
    EXPECT_EQ(nextPattern->obtainedMonth_.firstDayIndex, calendarPattern->currentMonth_.firstDayIndex);
    EXPECT_EQ(nextPattern->monthState_, MonthState::CUR_MONTH);
    EXPECT_EQ(nextPattern->GetCalendarDay().day, calendarPattern->GetCalendarDay().day);

    calendarPattern->OnModifyDone();
    EXPECT_EQ(prePattern->obtainedMonth_.firstDayIndex, calendarPattern->nextMonth_.firstDayIndex);
    EXPECT_EQ(prePattern->monthState_, MonthState::NEXT_MONTH);
    EXPECT_EQ(currentPattern->obtainedMonth_.firstDayIndex, calendarPattern->preMonth_.firstDayIndex);
    EXPECT_EQ(currentPattern->monthState_, MonthState::PRE_MONTH);
    EXPECT_EQ(nextPattern->obtainedMonth_.firstDayIndex, calendarPattern->currentMonth_.firstDayIndex);
    EXPECT_EQ(nextPattern->monthState_, MonthState::CUR_MONTH);
    EXPECT_EQ(nextPattern->GetCalendarDay().day, calendarPattern->GetCalendarDay().day);

    swiperPattern->currentIndex_ = 3;
    calendarPattern->backToToday_ = true;
    calendarPattern->goTo_ = true;
    calendarPattern->OnModifyDone();
    calendarPattern->OnModifyDone();
}

/**
 * @tc.name: CalendarPatternTest004
 * @tc.desc: Test CalendarPattern FlushFocus
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPatternTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);

    ObtainedMonth obtainedMonth;
    CalendarDay calendarDay;
    calendarDay.month.year = calendarPattern->calendarDay_.month.year;
    calendarDay.month.month = calendarPattern->calendarDay_.month.month;
    calendarDay.day = calendarPattern->calendarDay_.day;
    calendarDay.focused = false;
    obtainedMonth.days.emplace_back(calendarDay);
    calendarPattern->FlushFocus(obtainedMonth);
    EXPECT_TRUE(obtainedMonth.days[0].focused);

    calendarDay.month.year = calendarPattern->calendarDay_.month.year + 1;
    calendarDay.focused = false;
    calendarPattern->FlushFocus(obtainedMonth);
    EXPECT_TRUE(obtainedMonth.days[0].focused);
}

/**
 * @tc.name: CalendarPatternTest005
 * @tc.desc: Test CalendarPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPatternTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    swiperNode->MountToParent(frameNode);
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    ASSERT_NE(calendarPattern, nullptr);

    auto json = JsonUtil::Create(true);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    ASSERT_NE(swiperPaintProperty, nullptr);

    swiperLayoutProperty->UpdateDisableSwipe(true);
    swiperLayoutProperty->UpdateDirection(Axis::VERTICAL);
    calendarPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("needSlide"), "false");
    EXPECT_EQ(json->GetString("direction"), "0");

    swiperLayoutProperty->UpdateDisableSwipe(false);
    swiperLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    json = JsonUtil::Create(true);
    calendarPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("needSlide"), "true");
    EXPECT_EQ(json->GetString("direction"), "1");

    std::optional<bool> disableSwipe;
    std::optional<Axis> direction;
    swiperLayoutProperty->propDisableSwipe_ = disableSwipe;
    swiperLayoutProperty->propDirection_ = direction;
    json = JsonUtil::Create(true);
    calendarPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("needSlide"), "true");
    EXPECT_EQ(json->GetString("direction"), "1");
}

/**
 * @tc.name: CalendarMonthPatternTest001
 * @tc.desc: Test CalendarMonthPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarMonthPatternTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig config;
    config.skipMeasure = true;
    layoutWrapper->skipMeasureContent_ = std::make_optional<bool>(true);
    EXPECT_FALSE(calendarMonthPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    config.skipMeasure = false;
    layoutWrapper->skipMeasureContent_ = std::make_optional<bool>(false);
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<LayoutAlgorithm>());
    layoutAlgorithm->skipMeasure_ = false;
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithm;
    EXPECT_TRUE(calendarMonthPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: CalendarMonthPatternTest002
 * @tc.desc: Test CalendarMonthPattern ClickCallback
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarMonthPatternTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthEventHub = frameNode->GetEventHub<CalendarEventHub>();
    ASSERT_NE(calendarMonthEventHub, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    auto gesture = frameNode->GetOrCreateGestureEventHub();
    calendarMonthPattern->OnModifyDone();
    auto clickCallback = gesture->clickEventActuator_->clickEvents_.back()->callback_;

    std::string infoDetail;
    auto initRequestDataEvent = [&](std::string info) { infoDetail = std::move(info); };
    calendarMonthEventHub->SetSelectedChangeEvent(initRequestDataEvent);
    calendarMonthPattern->OnModifyDone();

    ObtainedMonth obtainedMonth;
    calendarMonthPattern->obtainedMonth_ = obtainedMonth;
    GestureEvent gestureEvent;
    FingerInfo fingerInfo;
    fingerInfo.localLocation_ = Offset(OFFSET_X, OFFSET_Y);
    calendarMonthPattern->OnClick(fingerInfo.localLocation_, calendarMonthPattern->obtainedMonth_);
    EXPECT_TRUE(obtainedMonth.days.empty());

    for (int i = 0; i < 3; i++) {
        CalendarDay calendarDay;
        calendarDay.focused = true;
        obtainedMonth.days.emplace_back(calendarDay);
    }
    calendarMonthPattern->obtainedMonth_ = obtainedMonth;
    gestureEvent.fingerList_.clear();
    gestureEvent.fingerList_.emplace_back(fingerInfo);
    frameNode->geometryNode_->SetFrameSize(SizeF(VALID_LENGTH, VALID_LENGTH));
    paintProperty->UpdateDayHeight(Dimension(VALID_LENGTH));
    paintProperty->UpdateDayWidth(Dimension(VALID_LENGTH));
    calendarMonthPattern->OnClick(fingerInfo.localLocation_, calendarMonthPattern->obtainedMonth_);
    EXPECT_TRUE(calendarMonthPattern->obtainedMonth_.days[0].focused);
    EXPECT_FALSE(calendarMonthPattern->obtainedMonth_.days[1].focused);
    EXPECT_FALSE(calendarMonthPattern->obtainedMonth_.days[2].focused);
    auto json = JsonUtil::ParseJsonString(infoDetail);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(json->GetInt("day"), obtainedMonth.days[i].day);
        EXPECT_EQ(json->GetInt("month"), obtainedMonth.days[i].month.month);
        EXPECT_EQ(json->GetInt("year"), obtainedMonth.days[i].month.year);
    }
}

/**
 * @tc.name: CalendarMonthPatternTest003
 * @tc.desc: Test CalendarMonthPattern JudgeArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarMonthPatternTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    for (int i = 0; i < 4; i++) {
        double offsetX = 0.0;
        double offsetY = 0.0;
        float maxWidth = VALID_LENGTH;
        float maxHeight = VALID_LENGTH;
        if (i == 0) {
            offsetX = OFFSET_X;
        } else if (i == 1) {
            offsetX = -1;
        } else if (i == 2) {
            offsetX = VALID_LENGTH + 1.0;
        } else {
            maxWidth = -VALID_LENGTH;
            offsetX = -VALID_LENGTH + 1.0;
        }

        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                maxHeight = VALID_LENGTH;
                offsetY = OFFSET_Y;
            } else if (j == 1) {
                offsetY = -1;
            } else if (j == 2) {
                offsetY = VALID_LENGTH + 1.0;
            } else {
                maxHeight = -VALID_LENGTH;
                offsetY = -VALID_LENGTH + 1.0;
            }

            for (int k = 3; k >= 0; k--) {
                if (k == 3) {
                    frameNode->geometryNode_->SetFrameSize(SizeF(maxWidth, maxHeight));
                    paintProperty->UpdateDayHeight(Dimension(0.0));
                    paintProperty->UpdateDayWidth(Dimension(0.0));
                    EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(offsetX, offsetY)), -1);
                } else if (k == 2) {
                    frameNode->geometryNode_->SetFrameSize(SizeF(maxWidth, maxHeight));
                    paintProperty->UpdateDayHeight(Dimension(VALID_LENGTH));
                    paintProperty->UpdateDayWidth(Dimension(0.0));
                    EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(offsetX, offsetY)), -1);
                } else if (k == 1) {
                    frameNode->geometryNode_->SetFrameSize(SizeF(maxWidth, maxHeight));
                    paintProperty->UpdateDayHeight(Dimension(0.0));
                    paintProperty->UpdateDayWidth(Dimension(VALID_LENGTH));
                    EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(offsetX, offsetY)), -1);
                } else {
                    frameNode->geometryNode_->SetFrameSize(SizeF(maxWidth, maxHeight));
                    paintProperty->UpdateDayHeight(Dimension(VALID_LENGTH));
                    paintProperty->UpdateDayWidth(Dimension(VALID_LENGTH));
                    if (i == 0 && j == 0) {
                        EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(offsetX, offsetY)), 0);
                    } else {
                        EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(offsetX, offsetY)), -1);
                    }
                }
            }
        }
    }

    frameNode->geometryNode_->SetFrameSize(SizeF(VALID_LENGTH, VALID_LENGTH));
    paintProperty->UpdateDayHeight(Dimension(VALID_LENGTH));
    paintProperty->UpdateDayWidth(Dimension(VALID_LENGTH));
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(OFFSET_X, OFFSET_Y)), 6);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    EXPECT_EQ(calendarMonthPattern->JudgeArea(Offset(OFFSET_X, OFFSET_Y)), 0);
}

/**
 * @tc.name: CalendarMonthPatternTest004
 * @tc.desc: Test CalendarMonthPattern GetDaySize
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarMonthPatternTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);

    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    EXPECT_EQ(calendarMonthPattern->GetDaySize(theme).ConvertToVp(), 0.0);
}

/**
 * @tc.name: CalendarMonthPatternTest005
 * @tc.desc: Test CalendarMonthPattern VirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarMonthPatternTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.case: case1 InitVirtualNode.
     */
    CalendarDay today;
    today.month.month = JUMP_MONTH;
    today.month.year = JUMP_YEAR;
    today.day = DAY_VALUE;
    calendarMonthPattern->calendarDay_ = today;
    ObtainedMonth obtainedMonth;
    for (int i = DAY_VALUE; i < WEEKS_COUNT_SIX; i++) {
        CalendarDay calendarDay;
        calendarDay.month.month = JUMP_MONTH;
        calendarDay.month.year = JUMP_YEAR;
        calendarDay.day = i;
        calendarDay.index = i;
        obtainedMonth.days.emplace_back(calendarDay);
    }
    calendarMonthPattern->obtainedMonth_ = obtainedMonth;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    calendarMonthPattern->CreateNodePaintMethod();
    EXPECT_TRUE(calendarMonthPattern->accessibilityPropertyVec_.size() > 0);
    /**
     * @tc.case: case2 HandleAccessibilityHoverEvent.
     */
    AccessibilityHoverInfo hoverInfo;
    hoverInfo.SetActionType(AccessibilityHoverAction::HOVER_ENTER);
    calendarMonthPattern->HandleAccessibilityHoverEvent(true, hoverInfo);

    EXPECT_TRUE(calendarMonthPattern->isOnHover_ == true);
    calendarMonthPattern->accessibilityPropertyVec_[0]->OnAccessibilityFocusCallback(true);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(calendarMonthPattern->isOnHover_ == true);
    AccessibilityHoverInfo enHoverinfo;
    enHoverinfo.SetActionType(AccessibilityHoverAction::HOVER_CANCEL);
    calendarMonthPattern->HandleAccessibilityHoverEvent(false, enHoverinfo);
    EXPECT_TRUE(calendarMonthPattern->isOnHover_ == false);
    /**
     * @tc.case: case3 SetVirtualNodeUserSelected.
     */
    std::string infoDetail;
    auto initRequestDataEvent = [&](std::string info) { infoDetail = std::move(info); };
    auto calendarMonthEventHub = frameNode->GetEventHub<CalendarEventHub>();
    ASSERT_NE(calendarMonthEventHub, nullptr);
    calendarMonthEventHub->SetSelectedChangeEvent(initRequestDataEvent);
    calendarMonthPattern->OnModifyDone();
    calendarMonthPattern->SetVirtualNodeUserSelected(0);
    auto json = JsonUtil::ParseJsonString(infoDetail);
    EXPECT_EQ(json->GetInt("day"), obtainedMonth.days[0].day);
    EXPECT_EQ(json->GetInt("month"), obtainedMonth.days[0].month.month);
    EXPECT_EQ(json->GetInt("year"), obtainedMonth.days[0].month.year);
}

/**
 * @tc.name: CalendarMonthPatternTest006
 * @tc.desc: Test CalendarMonthPattern GetCalendarDay
 * @tc.type: FUNC
 */

HWTEST_F(CalendarTestNg, CalendarMonthPatternTest006, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.case: case1 InitVirtualNode.
     */
    CalendarDay today;
    today.month.month = JUMP_MONTH;
    today.month.year = JUMP_YEAR;
    today.day = DAY_VALUE;
    calendarMonthPattern->calendarDay_ = today;
    ObtainedMonth obtainedMonth;
    for (int i = DAY_VALUE; i < WEEKS_COUNT_SIX; i++) {
        CalendarDay calendarDay;
        calendarDay.month.month = JUMP_MONTH;
        calendarDay.month.year = JUMP_YEAR;
        calendarDay.day = i;
        calendarDay.index = i;
        obtainedMonth.days.emplace_back(calendarDay);
    }
    calendarMonthPattern->obtainedMonth_ = obtainedMonth;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    calendarMonthPattern->CreateNodePaintMethod();
    EXPECT_TRUE(calendarMonthPattern->accessibilityPropertyVec_.size() > 0);
    auto property = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    auto level = property->GetAccessibilityLevel();
    EXPECT_EQ(level, AccessibilityProperty::Level::NO_STR);
}

/**
 * @tc.name: CalendarLayoutAlgorithmTest001
 * @tc.desc: Test CalendarLayoutAlgorithm MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarLayoutAlgorithmTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    auto pipeline = frameNode->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    pipeline->rootWidth_ = OFFSET_X;
    pipeline->rootHeight_ = OFFSET_Y;

    CalendarLayoutAlgorithm calendarLayoutAlgorithm;
    LayoutConstraintF contentConstraint;
    EXPECT_EQ(
        calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Width(), OFFSET_X);
    EXPECT_EQ(
        calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Height(), OFFSET_Y);

    contentConstraint.maxSize.SetWidth(VALID_LENGTH);
    contentConstraint.maxSize.SetHeight(Infinity<float>());
    EXPECT_EQ(
        calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Width(), OFFSET_X);
    EXPECT_EQ(
        calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Height(), OFFSET_Y);

    contentConstraint.maxSize.SetWidth(Infinity<float>());
    contentConstraint.maxSize.SetHeight(VALID_LENGTH);
    EXPECT_EQ(
        calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Width(), OFFSET_X);
    EXPECT_EQ(
        calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Height(), OFFSET_Y);

    contentConstraint.maxSize.SetWidth(VALID_LENGTH);
    contentConstraint.maxSize.SetHeight(VALID_LENGTH);
    EXPECT_EQ(calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Width(),
        VALID_LENGTH);
    EXPECT_EQ(calendarLayoutAlgorithm.MeasureContent(contentConstraint, AceType::RawPtr(layoutWrapper))->Height(),
        VALID_LENGTH);
}

/**
 * @tc.name: CalendarPaintMethodTest001
 * @tc.desc: Test CalendarPaintMethod GetContentDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPaintMethodTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto calendarPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(calendarPaintProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, calendarPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    ObtainedMonth obtainedMonth;
    CalendarDay calendarDay;
    CalendarPaintMethod calendarPaintMethod(obtainedMonth, calendarDay);
    auto paintFunc = calendarPaintMethod.GetContentDrawFunction(paintWrapper);
    EXPECT_EQ(calendarPaintMethod.frameSize_, geometryNode->GetFrameSize());
}

/**
 * @tc.name: CalendarPaintMethodTest002
 * @tc.desc: Test CalendarPaintMethod PaintContent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPaintMethodTest002, TestSize.Level1)
{
    auto calendarPaintProperty = AceType::MakeRefPtr<CalendarPaintProperty>();
    ASSERT_NE(calendarPaintProperty, nullptr);
    ObtainedMonth obtainedMonth;
    CalendarDay calendarDay;
    CalendarPaintMethod calendarPaintMethod(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    calendarPaintMethod.PaintContent(rsCanvas, calendarPaintProperty);
    EXPECT_TRUE(calendarPaintMethod.obtainedMonth_.days.empty());
    EXPECT_TRUE(calendarPaintMethod.calendarDays_.empty());
}

/**
 * @tc.name: CalendarPaintMethodTest003
 * @tc.desc: Test CalendarPaintMethod DrawCalendar
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPaintMethodTest003, TestSize.Level1)
{
    ObtainedMonth obtainedMonth;
    CalendarDay calendarDay;
    CalendarMonth calendarMonth;
    calendarDay.month = calendarMonth;
    CalendarPaintMethod calendarPaintMethod(obtainedMonth, calendarDay);
    calendarPaintMethod.currentMonth_ = calendarMonth;

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    calendarDay.focused = true;
    calendarPaintMethod.DrawCalendar(
        rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_TRUE(calendarDay.focused && calendarDay.month.month == calendarPaintMethod.currentMonth_.month);
    EXPECT_TRUE(calendarPaintMethod.IsToday(calendarDay));

    calendarPaintMethod.calendarDay_.day = calendarDay.day + 1;
    calendarPaintMethod.DrawCalendar(
        rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_FALSE(calendarPaintMethod.IsToday(calendarDay));

    calendarPaintMethod.showLunar_ = false;
    calendarDay.lunarDay.clear();
    calendarPaintMethod.DrawCalendar(
        rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_FALSE(calendarPaintMethod.showLunar_ && !calendarDay.lunarDay.empty());

    calendarPaintMethod.showLunar_ = false;
    calendarDay.lunarDay = LUNAR_DAY_VALUE;
    calendarPaintMethod.DrawCalendar(
        rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_FALSE(calendarPaintMethod.showLunar_ && !calendarDay.lunarDay.empty());

    calendarPaintMethod.showLunar_ = true;
    calendarDay.lunarDay.clear();
    calendarPaintMethod.DrawCalendar(
        rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_FALSE(calendarPaintMethod.showLunar_ && !calendarDay.lunarDay.empty());

    calendarPaintMethod.showLunar_ = true;
    calendarDay.lunarDay = LUNAR_DAY_VALUE;
    calendarPaintMethod.DrawCalendar(
        rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_TRUE(calendarPaintMethod.showLunar_ && !calendarDay.lunarDay.empty());
}

/**
 * @tc.name: CalendarPaintMethodTest004
 * @tc.desc: Test CalendarPaintMethod PaintDay
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPaintMethodTest004, TestSize.Level1)
{
    ObtainedMonth obtainedMonth;
    CalendarDay calendarDay;
    CalendarMonth calendarMonth;
    calendarDay.month = calendarMonth;
    CalendarPaintMethod calendarPaintMethod(obtainedMonth, calendarDay);
    calendarPaintMethod.currentMonth_ = calendarMonth;

    Testing::MockCanvas rsCanvas;
    RSTextStyle rsTextStyle;
    calendarDay.dayMark.clear();
    calendarPaintMethod.showHoliday_ = false;
    calendarPaintMethod.PaintDay(rsCanvas, Offset(OFFSET_X, OFFSET_Y), calendarDay, rsTextStyle);
    EXPECT_FALSE(!calendarDay.dayMark.empty() && calendarPaintMethod.showHoliday_);

    calendarDay.dayMark = WORK_DAY_MARK;
    calendarPaintMethod.PaintDay(rsCanvas, Offset(OFFSET_X, OFFSET_Y), calendarDay, rsTextStyle);
    EXPECT_FALSE(!calendarDay.dayMark.empty() && calendarPaintMethod.showHoliday_);

    calendarPaintMethod.showHoliday_ = true;
    calendarPaintMethod.PaintDay(rsCanvas, Offset(OFFSET_X, OFFSET_Y), calendarDay, rsTextStyle);
    EXPECT_TRUE(!calendarDay.dayMark.empty() && calendarPaintMethod.showHoliday_);

    calendarDay.dayMark = OFF_DAY_MARK;
    calendarPaintMethod.PaintDay(rsCanvas, Offset(OFFSET_X, OFFSET_Y), calendarDay, rsTextStyle);

    calendarPaintMethod.currentMonth_.month = calendarDay.month.month + 1;
    calendarDay.focused = true;
    calendarPaintMethod.PaintDay(rsCanvas, Offset(OFFSET_X, OFFSET_Y), calendarDay, rsTextStyle);

    calendarDay.dayMark = WORK_DAY_MARK;
    calendarDay.touched = true;
    calendarPaintMethod.PaintDay(rsCanvas, Offset(OFFSET_X, OFFSET_Y), calendarDay, rsTextStyle);
}

/**
 * @tc.name: CalendarPaintMethodTest005
 * @tc.desc: Create calendar, and check today off or work status.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPaintMethodTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Calendar
     * @tc.expected: step1. Create Calendar successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));

    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    theme->GetCalendarTheme().workDayMarkColor = Color::RED;
    theme->GetCalendarTheme().offDayMarkColor = Color::BLUE;

    // Today style.
    TodayStyle todayStyle;
    Color focusedDayColor = Color::GREEN;
    todayStyle.UpdateFocusedDayColor(focusedDayColor);
    Color focusedLunarColor = Color::WHITE;
    todayStyle.UpdateFocusedLunarColor(focusedLunarColor);
    Color focusedAreaBackgroundColor = Color::BLUE;
    todayStyle.UpdateFocusedAreaBackgroundColor(focusedAreaBackgroundColor);
    Dimension focusedAreaRadius = Dimension(DEFAULT_FOCUS_RADIUS, DimensionUnit::VP);
    todayStyle.UpdateFocusedAreaRadius(focusedAreaRadius);

    // Day style of current month.
    CalendarModelNG calendarModelNG;
    CurrentDayStyle dayStyle;
    dayStyle.UpdateDayColor(Color::BLACK);

    CalendarData calendarData;
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    calendarModelNG.Create(calendarData);
    calendarModelNG.SetTodayStyle(todayStyle);
    calendarModelNG.SetCurrentDayStyle(dayStyle);
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();

    EXPECT_EQ(element->GetTag(), V2::CALENDAR_ETS_TAG);
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    auto calendarPattern = frameNode->GetPattern<CalendarPattern>();
    auto swiperNode = frameNode->GetChildren().front();
    auto calendarFrameNode = AceType::DynamicCast<FrameNode>(swiperNode->GetChildren().front());
    auto calendarPaintProperty = calendarFrameNode->GetPaintProperty<CalendarPaintProperty>();

    ObtainedMonth obtainedMonth;
    obtainedMonth.year = JUMP_YEAR;
    obtainedMonth.month = JUMP_MONTH;
    obtainedMonth.firstDayIndex = FIRST_DAY_INDEX_VALUE;

    // Add 31 days.
    std::vector<CalendarDay> days;
    for (int32_t i = 0; i < 31; i++) {
        CalendarDay day;
        day.index = i;
        day.month.year = JUMP_YEAR;
        day.month.month = JUMP_MONTH;
        day.day = i + 1;
        if (i == 0) {
            day.focused = true;
        }
        // Saturday and Sunday set off days. Others set work days.
        if ((i % 6 == 5) || (i % 6 == 0)) {
            day.dayMark = "off";
        } else {
            day.dayMark = "work";
        }
        days.emplace_back(std::move(day));
    }
    obtainedMonth.days = days;

    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);

    CalendarDay calendarDay;
    calendarDay.index = 0;
    calendarDay.day = 1;
    calendarDay.today = false;
    calendarDay.focused = true;
    calendarDay.touched = true;

    /**
     * @tc.steps: step2. Set the first day focused, check the first day text style.
     * @tc.expected: step2. The text color is 0xffffffff.
     */
    CalendarMonth calendarMonth;
    calendarMonth.year = JUMP_YEAR;
    calendarMonth.month = JUMP_MONTH;
    calendarDay.month = calendarMonth;
    calendarModelNG.SetCalendarDay(calendarDay);

    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    paintMethod->SetCalendarTheme(calendarPaintProperty);

    RSTextStyle workOffTextStyle;
    /**
     * @tc.steps: step3. Set the first day focused, check the offWork color.
     * @tc.expected: step3. The focused text color is same as text color, expected 0xff00ff00.
     */
    paintMethod->SetOffWorkTextStyle(workOffTextStyle, obtainedMonth.days[0]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(workOffTextStyle.color_, RSColor(0xff00ff00));
#else
    EXPECT_EQ(workOffTextStyle.color, RSColor(0xff00ff00));
#endif

    /**
     * @tc.steps: step4. Check the offWork color.
     * @tc.expected: step4. The text color expected 0xffff0000, it is work.
     */
    paintMethod->SetOffWorkTextStyle(workOffTextStyle, obtainedMonth.days[2]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(workOffTextStyle.color_, RSColor(0xffff0000));
#else
    EXPECT_EQ(workOffTextStyle.color, RSColor(0xffff0000));
#endif

    /**
     * @tc.steps: step5. Check the offWork color.
     * @tc.expected: step5. The text color expected 0xffff0000, it is off.
     */
    paintMethod->SetOffWorkTextStyle(workOffTextStyle, obtainedMonth.days[5]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(workOffTextStyle.color_, RSColor(0xff0000ff));
#else
    EXPECT_EQ(workOffTextStyle.color, RSColor(0xff0000ff));
#endif

    /**
     * @tc.steps: step6. Check the offWork color.
     * @tc.expected: step6. The text color expected 0xffff0000, it is off.
     */
    paintMethod->SetOffWorkTextStyle(workOffTextStyle, obtainedMonth.days[6]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(workOffTextStyle.color_, RSColor(0xff0000ff));
#else
    EXPECT_EQ(workOffTextStyle.color, RSColor(0xff0000ff));
#endif

    /**
     * @tc.steps: step7. Check the offWork color.
     * @tc.expected: step7. The text color expected 0xffff0000, it is work.
     */
    paintMethod->SetOffWorkTextStyle(workOffTextStyle, obtainedMonth.days[7]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(workOffTextStyle.color_, RSColor(0xffff0000));
#else
    EXPECT_EQ(workOffTextStyle.color, RSColor(0xffff0000));
#endif

    /**
     * @tc.steps: step8. Check the offWork color.
     * @tc.expected: step8. The text color expected 0xffff0000, it is work.
     */
    paintMethod->SetOffWorkTextStyle(workOffTextStyle, obtainedMonth.days[9]);
#ifndef USE_GRAPHIC_TEXT_GINE
    EXPECT_EQ(workOffTextStyle.color_, RSColor(0xffff0000));
#else
    EXPECT_EQ(workOffTextStyle.color, RSColor(0xffff0000));
#endif
}

/**
 * @tc.name: CalendarPaintMethodTest006
 * @tc.desc: Test CalendarPaintMethod DrawWeekAndDates
 * @tc.type: FUNC
 */
HWTEST_F(CalendarTestNg, CalendarPaintMethodTest006, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarPattern>(); });
    auto calendarPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(calendarPaintProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, calendarPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    ObtainedMonth obtainedMonth;
    CalendarDay calendarDay;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    paintMethod->DrawWeekAndDates(rsCanvas, Offset(0, 0));

    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    paintMethod->DrawWeekAndDates(rsCanvas, Offset(0, 0));
}
} // namespace OHOS::Ace::NG
