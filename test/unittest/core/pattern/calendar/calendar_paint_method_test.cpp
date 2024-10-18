/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "test/unittest/core/pattern/test_ng.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "core/components/calendar/calendar_data_adapter.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/components_ng/pattern/calendar/calendar_month_pattern.h"
#include "core/components_ng/pattern/calendar/calendar_paint_method.h"
#include "core/components_ng/pattern/calendar/calendar_paint_property.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/render/drawing_mock.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
struct TestProperty {};
namespace {
const int32_t JUMP_YEAR = 2023;
const int32_t JUMP_MONTH = 3;
const int32_t FIRST_DAY_INDEX_VALUE = 1;
const std::string LUNAR_MONTH_VALUE = "五月";
const double OFFSET_X = 6.0;
const double OFFSET_Y = 8.0;
const float VALID_LENGTH = 10;
const int32_t START_LENTH = 0;
const int32_t CALEND_DAYS_LENTH = 12;
} // namespace

class CalendarPaintMethTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateCalendarNode(TestProperty& testProperty);
};

void CalendarPaintMethTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void CalendarPaintMethTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

RefPtr<FrameNode> CalendarPaintMethTest::CreateCalendarNode(TestProperty& testProperty)
{
    return nullptr;
}

/**
 * @tc.name: DrawDatesTest001
 * @tc.desc: Test CalendarPaintMethod DrawDates
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawDatesTest001, TestSize.Level1)
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
    paintMethod->weekNumbers_.push_back("weekNumbers");
    /**
     * @tc.steps: step1. call DrawDates.
     * @tc.expected: row count not change.
     */
    paintMethod->DrawDates(rsCanvas, Offset(0, 0));
    EXPECT_EQ(paintMethod->rowCount_, 0);
}

/**
 * @tc.name: DrawDatesTest002
 * @tc.desc: Test CalendarPaintMethod DrawDates
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawDatesTest002, TestSize.Level1)
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
    CalendarDay calendarDays1;
    CalendarDay calendarDays2;
    CalendarDay calendarDays3;
    CalendarDay calendarDays4;
    paintMethod->calendarDays_.push_back(calendarDays1);
    paintMethod->calendarDays_.push_back(calendarDays2);
    paintMethod->calendarDays_.push_back(calendarDays3);
    paintMethod->calendarDays_.push_back(calendarDays4);
    paintMethod->weekNumbers_.push_back("weekNumbers");
    /**
     * @tc.steps: step1. call DrawDates.
     * @tc.expected: row count equal calendarDays_.size()/weekNumbers_.size().
     */
    paintMethod->DrawDates(rsCanvas, Offset(0, 0));
    EXPECT_EQ(paintMethod->rowCount_, 4);
}

/**
 * @tc.name: DrawDatesTest003
 * @tc.desc: Test CalendarPaintMethod DrawDates
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawDatesTest003, TestSize.Level1)
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
    CalendarDay calendarDays;
    for (int i = START_LENTH; i < CALEND_DAYS_LENTH; i++) {
        paintMethod->calendarDays_.push_back(calendarDays);
    }
    paintMethod->weekNumbers_.push_back("weekNumbers");
    /**
     * @tc.steps: step1. call DrawDates.
     * @tc.expected: row count equal calendarDays_.size()/weekNumbers_.size().
     */
    paintMethod->DrawDates(rsCanvas, Offset(0, 0));
    EXPECT_EQ(paintMethod->rowCount_, 12);
}

/**
 * @tc.name: DrawCalendarTest001
 * @tc.desc: Test CalendarPaintMethod DrawCalendar
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarTest001, TestSize.Level1)
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
    CalendarMonth calendarMonth;
    calendarDay.month = calendarMonth;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    Testing::MockCanvas rsCanvas;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    paintMethod->isCalendarDialog_ = false;
    paintMethod->DrawCalendar(rsCanvas, Offset(OFFSET_X, OFFSET_Y), Offset(VALID_LENGTH, VALID_LENGTH), calendarDay);
    EXPECT_EQ(calendarDay.month.month, paintMethod->currentMonth_.month);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest001
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest001, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 1;
    calendarDay.month.month = 1;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_NE(calendarDay.month.year, paintMethod->obtainedMonth_.year);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest002
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest002, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 1;
    calendarDay.month.month = 0;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_NE(calendarDay.month.year, paintMethod->obtainedMonth_.year);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest003
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest003, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 0;
    calendarDay.month.month = 1;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_EQ(calendarDay.month.year, paintMethod->obtainedMonth_.year);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest004
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest004, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 0;
    calendarDay.month.month = 0;
    calendarDay.isSelected = false;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_EQ(calendarDay.month.month, paintMethod->obtainedMonth_.month);
    EXPECT_EQ(calendarDay.month.year, paintMethod->obtainedMonth_.year);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest005
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest005, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 0;
    calendarDay.month.month = 0;
    calendarDay.isPressing = true;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_EQ(calendarDay.month.year, paintMethod->obtainedMonth_.year);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest006
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest006, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 0;
    calendarDay.month.month = 0;
    calendarDay.isHovering = true;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_EQ(calendarDay.month.month, paintMethod->obtainedMonth_.month);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest007
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest007, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 1;
    calendarDay.month.month = 1;
    calendarDay.isKeyFocused = true;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_NE(calendarDay.month.month, paintMethod->obtainedMonth_.month);
}

/**
 * @tc.name: DrawCalendarPickerBackgroundAreaTest008
 * @tc.desc: Test CalendarPaintMethod DrawCalendarPickerBackgroundArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawCalendarPickerBackgroundAreaTest008, TestSize.Level1)
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
    RSCanvas rsCanvas;
    calendarDay.month.year = 1;
    calendarDay.month.month = 1;
    calendarDay.isKeyFocused = false;
    paintMethod->DrawCalendarPickerBackgroundArea(calendarDay, rsCanvas, 1.0, 1.0);
    EXPECT_NE(calendarDay.month.year, paintMethod->obtainedMonth_.year);
}

/**
 * @tc.name: InitTextStyleTest001
 * @tc.desc: Test CalendarPaintMethod InitTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, InitTextStyleTest001, TestSize.Level1)
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
    RSTextStyle dateTextStyle;
    RSTextStyle lunarTextStyle;
    paintMethod->appFontFamilies_.push_back("test");
    paintMethod->InitTextStyle(dateTextStyle, lunarTextStyle);
    EXPECT_TRUE(dateTextStyle.fontSize_ == paintMethod->dayFontSize_);
}

/**
 * @tc.name: SetCalendarPickerDayTextStyleTest001
 * @tc.desc: Test CalendarPaintMethod SetCalendarPickerDayTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarPickerDayTextStyleTest001, TestSize.Level1)
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
    calendarDay.month.month = 1;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    RSTextStyle dateTextStyle;
    paintMethod->SetCalendarPickerDayTextStyle(dateTextStyle, calendarDay);
    EXPECT_TRUE(dateTextStyle.color_ == paintMethod->textSelectedDayColor_);
}

/**
 * @tc.name: SetCalendarPickerDayTextStyleTest002
 * @tc.desc: Test CalendarPaintMethod SetCalendarPickerDayTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarPickerDayTextStyleTest002, TestSize.Level1)
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
    calendarDay.month.month = 2;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    RSTextStyle dateTextStyle;
    paintMethod->SetCalendarPickerDayTextStyle(dateTextStyle, calendarDay);
    EXPECT_TRUE(dateTextStyle.color_ == paintMethod->textNonCurrentMonthColor_);
}

/**
 * @tc.name: SetCalendarPickerDayTextStyleTest003
 * @tc.desc: Test CalendarPaintMethod SetCalendarPickerDayTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarPickerDayTextStyleTest003, TestSize.Level1)
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
    calendarDay.month.month = 1;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    RSTextStyle dateTextStyle;
    paintMethod->SetCalendarPickerDayTextStyle(dateTextStyle, calendarDay);
    EXPECT_TRUE(dateTextStyle.color_ == paintMethod->textSelectedDayColor_);
}

/**
 * @tc.name: SetCalendarPickerDayTextStyleTest004
 * @tc.desc: Test CalendarPaintMethod SetCalendarPickerDayTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarPickerDayTextStyleTest004, TestSize.Level1)
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
    calendarDay.month.month = 2;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    RSTextStyle dateTextStyle;
    paintMethod->calendarDay_ = calendarDay;
    paintMethod->SetCalendarPickerDayTextStyle(dateTextStyle, calendarDay);
    EXPECT_TRUE(dateTextStyle.color_ == paintMethod->textNonCurrentMonthColor_);
}

/**
 * @tc.name: SetCalendarPickerDayTextStyleTest005
 * @tc.desc: Test CalendarPaintMethod SetCalendarPickerDayTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarPickerDayTextStyleTest005, TestSize.Level1)
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
    calendarDay.month.month = 1;
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    RSTextStyle dateTextStyle;
    paintMethod->calendarDay_ = calendarDay;
    paintMethod->SetCalendarPickerDayTextStyle(dateTextStyle, calendarDay);
    EXPECT_TRUE(dateTextStyle.color_ == paintMethod->textSelectedDayColor_);
}

/**
 * @tc.name: SetOffWorkTextStyleTest001
 * @tc.desc: Test CalendarPaintMethod SetOffWorkTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetOffWorkTextStyleTest001, TestSize.Level1)
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
    RSTextStyle offWorkTextStyle;
    paintMethod->appFontFamilies_.push_back("test");
    paintMethod->SetOffWorkTextStyle(offWorkTextStyle, calendarDay);
    EXPECT_NE(offWorkTextStyle.fontSize_, 0);
}

/**
 * @tc.name: SetOffWorkTextStyleTest002
 * @tc.desc: Test CalendarPaintMethod SetOffWorkTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetOffWorkTextStyleTest002, TestSize.Level1)
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
    RSTextStyle offWorkTextStyle;
    paintMethod->appFontFamilies_.push_back("test");
    paintMethod->SetOffWorkTextStyle(offWorkTextStyle, calendarDay);
    EXPECT_EQ(offWorkTextStyle.locale_, Localization::GetInstance()->GetFontLocale());
}

/**
 * @tc.name: SetOffWorkTextStyleTest003
 * @tc.desc: Test CalendarPaintMethod SetOffWorkTextStyle
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetOffWorkTextStyleTest003, TestSize.Level1)
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
    RSTextStyle offWorkTextStyle;
    paintMethod->SetOffWorkTextStyle(offWorkTextStyle, calendarDay);
    EXPECT_EQ(offWorkTextStyle.fontWeight_, static_cast<RSFontWeight>(paintMethod->workStateFontWeight_));
}

/**
 * @tc.name: DrawWeekTest001
 * @tc.desc: Test CalendarPaintMethod DrawWeek
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawWeekTest001, TestSize.Level1)
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
    RSCanvas canvas;
    paintMethod->appFontFamilies_.push_back("test");
    paintMethod->DrawWeek(canvas, Offset(0, 0));
    EXPECT_TRUE(paintMethod->weekNumbers_.size() == 0);
}

/**
 * @tc.name: DrawWeekTest002
 * @tc.desc: Test CalendarPaintMethod DrawWeek
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawWeekTest002, TestSize.Level1)
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
    RSCanvas canvas;
    paintMethod->DrawWeek(canvas, Offset(0, 0));
    EXPECT_TRUE(paintMethod->weekNumbers_.size() == 0);
}

/**
 * @tc.name: DrawWeekTest003
 * @tc.desc: Test CalendarPaintMethod DrawWeek
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, DrawWeekTest003, TestSize.Level1)
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
    RSCanvas canvas;
    paintMethod->appFontFamilies_.push_back("test");
    paintMethod->DrawWeek(canvas, Offset(0, 0));
    EXPECT_TRUE(paintMethod->weekNumbers_.size() == 0);
}

/**
 * @tc.name: SetCalendarThemeTest001
 * @tc.desc: Test CalendarPaintMethod SetCalendarTheme
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarThemeTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    CalendarModelNG calendarModelNG;
    CurrentDayStyle dayStyle;
    dayStyle.UpdateDayColor(Color::BLACK);
    CalendarData calendarData;
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    calendarModelNG.Create(calendarData);
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
    std::vector<CalendarDay> days;
    obtainedMonth.days = days;
    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);
    CalendarDay calendarDay;
    CalendarMonth calendarMonth;
    calendarDay.month = calendarMonth;
    calendarModelNG.SetCalendarDay(calendarDay);
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    calendarPaintProperty->propShowLunar_ = false;
    paintMethod->SetCalendarTheme(calendarPaintProperty);
    EXPECT_TRUE(calendarPaintProperty->propShowLunar_ == false);
    EXPECT_EQ(paintMethod->weekColor_, ToRSColor(theme->GetCalendarTheme().weekColor));
}

/**
 * @tc.name: SetCalendarThemeTest002
 * @tc.desc: Test CalendarPaintMethod SetCalendarTheme
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarThemeTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    theme->GetCalendarTheme().workDayMarkColor = Color::RED;
    theme->GetCalendarTheme().offDayMarkColor = Color::BLUE;
    CalendarModelNG calendarModelNG;
    CurrentDayStyle dayStyle;
    dayStyle.UpdateDayColor(Color::BLACK);
    CalendarData calendarData;
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    calendarModelNG.Create(calendarData);
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
    std::vector<CalendarDay> days;
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
    calendarModelNG.SetCalendarDay(calendarDay);
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    calendarPaintProperty->propOffDays_ = "propOffDays";
    paintMethod->SetCalendarTheme(calendarPaintProperty);
    EXPECT_EQ(paintMethod->workDayMarkColor_, ToRSColor(theme->GetCalendarTheme().workDayMarkColor));
}

/**
 * @tc.name: SetCalendarThemeTest003
 * @tc.desc: Test CalendarPaintMethod SetCalendarTheme
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, SetCalendarThemeTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    RefPtr<CalendarTheme> theme = MockPipelineContext::GetCurrent()->GetTheme<CalendarTheme>();
    theme->GetCalendarTheme().workDayMarkColor = Color::RED;
    theme->GetCalendarTheme().offDayMarkColor = Color::BLUE;
    CalendarModelNG calendarModelNG;
    CurrentDayStyle dayStyle;
    dayStyle.UpdateDayColor(Color::BLACK);
    CalendarData calendarData;
    auto calendarControllerNg = AceType::MakeRefPtr<CalendarControllerNg>();
    calendarData.controller = calendarControllerNg;
    calendarModelNG.Create(calendarData);
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
    calendarModelNG.SetCurrentData(obtainedMonth);
    calendarModelNG.SetPreData(obtainedMonth);
    calendarModelNG.SetNextData(obtainedMonth);
    CalendarDay calendarDay;
    calendarDay.index = 0;
    calendarDay.day = 1;
    calendarDay.today = false;
    calendarDay.focused = true;
    calendarDay.touched = true;
    calendarModelNG.SetCalendarDay(calendarDay);
    auto paintMethod = AceType::MakeRefPtr<CalendarPaintMethod>(obtainedMonth, calendarDay);
    calendarPaintProperty->propStartOfWeek_ = Week::Sat;
    paintMethod->SetCalendarTheme(calendarPaintProperty);
    EXPECT_TRUE(paintMethod->currentMonth_.month == paintMethod->obtainedMonth_.month);
}

/**
 * @tc.name: IsOffDayTest001
 * @tc.desc: Test CalendarPaintMethod IsOffDay
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPaintMethTest, IsOffDayTest001, TestSize.Level1)
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
    calendarDay.index = -10;
    EXPECT_TRUE(paintMethod->IsOffDay(calendarDay));
}
} // namespace OHOS::Ace::NG