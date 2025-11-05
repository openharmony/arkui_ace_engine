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
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
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

const int32_t DAY_VALUE = 1;
const int32_t INDEX_VALUE = 1;
const int32_t JUMP_YEAR = 2023;
const int32_t JUMP_MONTH = 3;
const int32_t DEFAULT_FOCUS_RADIUS = 15;
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

// Day width and Height.

} // namespace

class CalendarPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateCalendarNode(TestProperty& testProperty);
};

void CalendarPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void CalendarPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CalendarPatternTestNg::CreateCalendarNode(TestProperty& testProperty)
{
    return nullptr;
}

/**
 * @tc.name: CalendarTest007
 * @tc.desc: Create calendar, and check the todayStyle focus status.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPatternTestNg, CalendarTest007, TestSize.Level1)
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
    PickerDate defaultDate;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay, defaultDate, defaultDate);
    Testing::MockCanvas rsCanvas;
    paintMethod->SetCalendarTheme(calendarPaintProperty);
    RSTextStyle dateTextStyle;
    RSTextStyle lunarTextStyle;
    paintMethod->InitTextStyle(dateTextStyle, lunarTextStyle);

    paintMethod->SetDayTextStyle(dateTextStyle, lunarTextStyle, obtainedMonth.days[0]);

    EXPECT_EQ(dateTextStyle.color, RSColor(0xffffffff));
    EXPECT_EQ(lunarTextStyle.color, RSColor(0xffffffff));

    /**
     * @tc.steps: step3. Set the first day focused, check the second day text style.
     * @tc.expected: step3. The text color is 0xff000000.
     */
    paintMethod->SetDayTextStyle(dateTextStyle, lunarTextStyle, obtainedMonth.days[1]);
    EXPECT_EQ(dateTextStyle.color, RSColor(0xff000000));
    EXPECT_EQ(lunarTextStyle.color, RSColor(0xff000000));
}

/**
 * @tc.name: CalendarPatternTest001
 * @tc.desc: Test CalendarPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPatternTestNg, CalendarPatternTest001, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarPatternTest002, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarPatternTest003, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarPatternTest004, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarPatternTest005, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarMonthPatternTest001, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarMonthPatternTest002, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarMonthPatternTest003, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarMonthPatternTest004, TestSize.Level1)
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
HWTEST_F(CalendarPatternTestNg, CalendarMonthPatternTest005, TestSize.Level1)
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

HWTEST_F(CalendarPatternTestNg, CalendarMonthPatternTest006, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
