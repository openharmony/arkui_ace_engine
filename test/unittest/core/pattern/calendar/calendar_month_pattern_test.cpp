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
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {};

namespace {
const int32_t CALEND_OBTAIN_DAYS_MONTH_LENTH = 28;
const int32_t CALEND_MONTH_LENTH = 35;
const int32_t CALEND_OBTAIN_MONTH_DAYS_LENTH = 42;
const int32_t START_LENTH = 0;
} // namespace

class CalendarMonthTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateCalendarNode(TestProperty& testProperty);
};

void CalendarMonthTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void CalendarMonthTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> CalendarMonthTestNg::CreateCalendarNode(TestProperty& testProperty)
{
    return nullptr;
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapTest001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnDirtyLayoutWrapperSwapTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->SetCalendarDialogFlag(true);
    EXPECT_FALSE(calendarMonthPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: SetColRowSpaceTest001
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->SetColRowSpace();
    EXPECT_FALSE(frameNode->GetLayoutProperty()->GetLayoutConstraint().has_value());
}

/**
 * @tc.name: SetColRowSpaceTest002
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest002, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    calendarMonthPattern->SetColRowSpace();
    EXPECT_TRUE(calendarMonthPattern->GetHost()->GetLayoutProperty());
    EXPECT_TRUE(calendarMonthPattern->obtainedMonth_.days.size() == 0);
}

/**
 * @tc.name: SetColRowSpaceTest003
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest003, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->SetColRowSpace();
    EXPECT_EQ(pipelineContext->GetTheme<CalendarTheme>(), nullptr);
}

/**
 * @tc.name: SetColRowSpaceTest004
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest004, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->SetColRowSpace();
    EXPECT_TRUE(calendarMonthPattern->obtainedMonth_.days.size() == 0);
}

/**
 * @tc.name: SetColRowSpaceTest005
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest005, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },
        .selfIdealSize = { 10, 10 } // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = calendarMonthPattern->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto value = paintProperty->GetColSpaceValue(Dimension());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    calendarMonthPattern->SetColRowSpace();
    EXPECT_NE(paintProperty->GetColSpaceValue(Dimension()), value);
}

/**
 * @tc.name: SetColRowSpaceTest006
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest006, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },
        .selfIdealSize = { 2, 2 } // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = calendarMonthPattern->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto value = paintProperty->GetColSpaceValue(Dimension());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    calendarMonthPattern->SetColRowSpace();
    EXPECT_EQ(paintProperty->GetColSpaceValue(Dimension()), value);
}

/**
 * @tc.name: SetColRowSpaceTest007
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest007, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },
        .selfIdealSize = { 10, 10 } // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = calendarMonthPattern->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto value = paintProperty->GetColSpaceValue(Dimension());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay;
    for (int i = START_LENTH; i < CALEND_OBTAIN_DAYS_MONTH_LENTH; i++) {
        calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    calendarMonthPattern->SetColRowSpace();
    EXPECT_NE(paintProperty->GetColSpaceValue(Dimension()), value);
}

/**
 * @tc.name: SetColRowSpaceTest008
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest008, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },
        .selfIdealSize = { 10, 10 } // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = calendarMonthPattern->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto value = paintProperty->GetColSpaceValue(Dimension());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay;
    for (int i = START_LENTH; i < CALEND_OBTAIN_MONTH_DAYS_LENTH; i++) {
        calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    calendarMonthPattern->SetColRowSpace();
    EXPECT_NE(paintProperty->GetColSpaceValue(Dimension()), value);
}

/**
 * @tc.name: SetColRowSpaceTest009
 * @tc.desc: Test SetColRowSpace
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetColRowSpaceTest009, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },
        .selfIdealSize = { 10, 10 } // 2 is the parentIdealSize of width and height
    };
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto paintProperty = calendarMonthPattern->GetPaintProperty<CalendarPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto value = paintProperty->GetColSpaceValue(Dimension());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay;
    for (int i = START_LENTH; i < CALEND_MONTH_LENTH; i++) {
        calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    }
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    calendarMonthPattern->SetColRowSpace();
    EXPECT_NE(paintProperty->GetColSpaceValue(Dimension()), value);
}

/**
 * @tc.name: InitCurrentVirtualNodeTest001
 * @tc.desc: Test InitCurrentVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCurrentVirtualNodeTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->InitCurrentVirtualNode();
    EXPECT_TRUE(calendarMonthPattern->isInitVirtualNode_ == true);
}

/**
 * @tc.name: InitCurrentVirtualNodeTest002
 * @tc.desc: Test InitCurrentVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCurrentVirtualNodeTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->isInitVirtualNode_ = true;
    calendarMonthPattern->InitCurrentVirtualNode();
    EXPECT_TRUE(calendarMonthPattern->deviceOrientation_ == DeviceOrientation::PORTRAIT);
}

/**
 * @tc.name: InitCalendarVirtualNodeTest001
 * @tc.desc: Test InitCalendarVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCalendarVirtualNodeTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(stack, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    calendarMonthPattern->isFirstEnter_ = true;
    EXPECT_TRUE(calendarMonthPattern->InitCalendarVirtualNode());
    EXPECT_FALSE(calendarMonthPattern->deviceOrientation_ == DeviceOrientation::PORTRAIT);
}

/**
 * @tc.name: InitCalendarVirtualNodeTest002
 * @tc.desc: Test InitCalendarVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCalendarVirtualNodeTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    OHOS::Ace::CalendarDay day;
    calendarMonthPattern->obtainedMonth_.days.push_back(day);
    calendarMonthPattern->obtainedMonth_.days[0].isSelected = true;
    calendarMonthPattern->isFirstEnter_ = true;
    calendarMonthPattern->obtainedMonth_.days[0].isSelected = false;
    EXPECT_TRUE(calendarMonthPattern->InitCalendarVirtualNode());
    EXPECT_FALSE(calendarMonthPattern->deviceOrientation_ == DeviceOrientation::PORTRAIT);
}

/**
 * @tc.name: InitCalendarVirtualNodeTest003
 * @tc.desc: Test InitCalendarVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCalendarVirtualNodeTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    OHOS::Ace::CalendarDay day;
    calendarMonthPattern->obtainedMonth_.days.push_back(day);
    calendarMonthPattern->obtainedMonth_.days[0].isSelected = false;
    calendarMonthPattern->isFirstEnter_ = true;
    EXPECT_TRUE(calendarMonthPattern->InitCalendarVirtualNode());
    EXPECT_FALSE(calendarMonthPattern->deviceOrientation_ == DeviceOrientation::PORTRAIT);
}

/**
 * @tc.name: InitCalendarVirtualNodeTest004
 * @tc.desc: Test InitCalendarVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCalendarVirtualNodeTest004, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    OHOS::Ace::CalendarDay day;
    calendarMonthPattern->obtainedMonth_.days.push_back(day);
    calendarMonthPattern->obtainedMonth_.days[0].isSelected = true;
    calendarMonthPattern->isFirstEnter_ = true;
    EXPECT_TRUE(calendarMonthPattern->InitCalendarVirtualNode());
    EXPECT_FALSE(calendarMonthPattern->isFirstEnter_);
}

/**
 * @tc.name: InitCalendarVirtualNodeTest005
 * @tc.desc: Test InitCalendarVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, InitCalendarVirtualNodeTest005, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    OHOS::Ace::CalendarDay day;
    calendarMonthPattern->obtainedMonth_.days.push_back(day);
    calendarMonthPattern->obtainedMonth_.days[0].isSelected = true;
    calendarMonthPattern->obtainedMonth_.days[0].index = 1;
    calendarMonthPattern->isFirstEnter_ = true;
    EXPECT_TRUE(calendarMonthPattern->InitCalendarVirtualNode());
}

/**
 * @tc.name: ChangeVirtualNodeStateTest001
 * @tc.desc: Test ChangeVirtualNodeState
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, ChangeVirtualNodeStateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. call ChangeVirtualNodeState.
     * @tc.expected: selectedIndex_ > accessibilityPropertyVec_.size(), so immediately return.
     */
    const CalendarDay calendarDay;
    calendarMonthPattern->selectedIndex_ = 1;
    calendarMonthPattern->ChangeVirtualNodeState(calendarDay);
    EXPECT_TRUE(calendarMonthPattern->selectedIndex_ >
                static_cast<int32_t>(calendarMonthPattern->accessibilityPropertyVec_.size()));
}

/**
 * @tc.name: SetCalendarAccessibilityLevelTest001
 * @tc.desc: Test SetCalendarAccessibilityLevel
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetCalendarAccessibilityLevelTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    const std::string level = "level";
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> host;
    calendarMonthPattern->SetCalendarAccessibilityLevel(level);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_NE(accessibilityProperty->GetAccessibilityLevel(), level);
}

/**
 * @tc.name: FireModifyAccessibilityVirtualNodeTest001
 * @tc.desc: Test FireModifyAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, FireModifyAccessibilityVirtualNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. call FireModifyAccessibilityVirtualNode.
     * @tc.expected: currentData.days is empty, so immediately return.
     */
    ObtainedMonth currentData;
    calendarMonthPattern->isInitVirtualNode_ = true;
    calendarMonthPattern->FireModifyAccessibilityVirtualNode(currentData);
    EXPECT_TRUE(currentData.days.empty());
}
/**
 * @tc.name: FireModifyAccessibilityVirtualNodeTest002
 * @tc.desc: Test FireModifyAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, FireModifyAccessibilityVirtualNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. call FireModifyAccessibilityVirtualNode.
     * @tc.expected: isInitVirtualNode_ is false, so immediately return.
     */
    ObtainedMonth currentData;
    calendarMonthPattern->isInitVirtualNode_ = false;
    calendarMonthPattern->FireModifyAccessibilityVirtualNode(currentData);
    EXPECT_FALSE(calendarMonthPattern->isInitVirtualNode_);
}

/**
 * @tc.name: ModifyAccessibilityVirtualNodeTest001
 * @tc.desc: Test ModifyAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, ModifyAccessibilityVirtualNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. call ModifyAccessibilityVirtualNode.
     * @tc.expected: buttonAccessibilityNodeVec_ is empty, so immediately return.
     */
    ObtainedMonth currentData;
    calendarMonthPattern->ModifyAccessibilityVirtualNode(currentData);
    EXPECT_TRUE(calendarMonthPattern->buttonAccessibilityNodeVec_.empty());
}

/**
 * @tc.name: ModifyAccessibilityVirtualNodeTest002
 * @tc.desc: Test ModifyAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, ModifyAccessibilityVirtualNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode1 = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode1, nullptr);
    auto calendarMonthPattern = frameNode1->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode1, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapper, nullptr);
    auto frameNode2 = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode2, nullptr);
    /**
     * @tc.steps: step2. call ModifyAccessibilityVirtualNode.
     * @tc.expected: currentData.days is empty, so immediately return.
     */
    ObtainedMonth currentData;
    calendarMonthPattern->buttonAccessibilityNodeVec_.push_back(frameNode1);
    calendarMonthPattern->buttonAccessibilityNodeVec_.push_back(frameNode2);
    calendarMonthPattern->ModifyAccessibilityVirtualNode(currentData);
    EXPECT_TRUE(currentData.days.empty());
}

/**
 * @tc.name: SetVirtualNodeUserSelectedTest001
 * @tc.desc: Test SetVirtualNodeUserSelected
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetVirtualNodeUserSelectedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call SetVirtualNodeUserSelected.
     * @tc.expected: accessibilityText_ is empty, so immediately return.
     */
    int32_t index = 1;
    calendarMonthPattern->SetVirtualNodeUserSelected(index);
    EXPECT_TRUE(calendarMonthPattern->accessibilityPropertyVec_.size() == 0);
}

/**
 * @tc.name: SetVirtualNodeUserSelectedTest002
 * @tc.desc: Test SetVirtualNodeUserSelected
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetVirtualNodeUserSelectedTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    int32_t index = 1;
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    calendarMonthPattern->accessibilityPropertyVec_.push_back(accessibilityProperty);
    CalendarDay calendarDay;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    calendarMonthPattern->SetVirtualNodeUserSelected(index);
    EXPECT_NE(calendarMonthPattern->selectedIndex_, index);
}

/**
 * @tc.name: SetVirtualNodeUserSelectedTest003
 * @tc.desc: Test SetVirtualNodeUserSelected
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetVirtualNodeUserSelectedTest003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);

    auto accessibilityProperty1 = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty1, nullptr);
    auto accessibilityProperty2 = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty2, nullptr);
    int32_t index = 1;
    calendarMonthPattern->accessibilityPropertyVec_.push_back(accessibilityProperty1);
    calendarMonthPattern->accessibilityPropertyVec_.push_back(accessibilityProperty2);
    CalendarDay calendarDay1;
    CalendarDay calendarDay2;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay2);
    calendarMonthPattern->obtainedMonth_.days[1].month.month = 1;
    calendarMonthPattern->obtainedMonth_.month = 1;
    calendarMonthPattern->obtainedMonth_.year = 1970;
    calendarMonthPattern->SetVirtualNodeUserSelected(index);
    auto textDirection = frameNode->GetLayoutProperty()->GetNonAutoLayoutDirection();
    auto remainderWeek = index % 7;
    int32_t selectedIndex = (textDirection == TextDirection::RTL ? (7 - remainderWeek * 2 + index - 1) : index);
    EXPECT_TRUE(calendarMonthPattern->obtainedMonth_.days[selectedIndex].focused);
}

/**
 * @tc.name: SetVirtualNodeUserSelectedTest004
 * @tc.desc: Test SetVirtualNodeUserSelected
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetVirtualNodeUserSelectedTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call SetVirtualNodeUserSelected.
     * @tc.expected: accessibilityText_ is empty, so selectedIndex_ not equal to index.
     */
    int32_t index = 1;
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    calendarMonthPattern->accessibilityPropertyVec_.push_back(accessibilityProperty);
    calendarMonthPattern->SetVirtualNodeUserSelected(index);
    EXPECT_NE(calendarMonthPattern->selectedIndex_, index);
}

/**
 * @tc.name: SetVirtualNodeUserSelectedTest005
 * @tc.desc: Test SetVirtualNodeUserSelected
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, SetVirtualNodeUserSelectedTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto accessibilityProperty1 = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty1, nullptr);
    auto accessibilityProperty2 = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty2, nullptr);
    /**
     * @tc.steps: step2. call SetVirtualNodeUserSelected.
     * @tc.expected: accessibilityText_ is not empty, so selectedIndex_ equal index
     */
    int32_t index = 1;
    accessibilityProperty2->accessibilityText_ = "test";
    calendarMonthPattern->accessibilityPropertyVec_.push_back(accessibilityProperty1);
    calendarMonthPattern->accessibilityPropertyVec_.push_back(accessibilityProperty2);
    CalendarDay calendarDay1;
    CalendarDay calendarDay2;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay2);
    calendarMonthPattern->obtainedMonth_.days[1].month.month = 1;
    calendarMonthPattern->obtainedMonth_.month = 1;
    calendarMonthPattern->obtainedMonth_.year = 1970;
    calendarMonthPattern->SetVirtualNodeUserSelected(index);
    EXPECT_TRUE(calendarMonthPattern->selectedIndex_ == index);
}

/**
 * @tc.name: JudgeAreaTest001
 * @tc.desc: Test JudgeArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, JudgeAreaTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    CalendarDay calendarDay;
    for (int i = START_LENTH; i < CALEND_OBTAIN_DAYS_MONTH_LENTH; i++) {
        calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    }
    auto localLocation = Offset(1, 1);
    auto ret = calendarMonthPattern->JudgeArea(localLocation);
    EXPECT_TRUE(ret < 0);
}

/**
 * @tc.name: JudgeAreaTest002
 * @tc.desc: Test JudgeArea
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, JudgeAreaTest002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    CalendarDay calendarDay;
    for (int i = START_LENTH; i < CALEND_MONTH_LENTH; i++) {
        calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    }
    auto localLocation = Offset(1, 1);
    auto ret = calendarMonthPattern->JudgeArea(localLocation);
    EXPECT_TRUE(ret < 0);
}

/**
 * @tc.name: OnTouchEventTest001
 * @tc.desc: Test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnTouchEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnTouchEvent.
     * @tc.expected: isCalendarDialog_ is false, so immediately return.
     */
    auto localLocation = Offset(1, 1);
    calendarMonthPattern->OnTouchEvent(localLocation, false);
    EXPECT_FALSE(calendarMonthPattern->isCalendarDialog_);
}

/**
 * @tc.name: OnTouchEventTest002
 * @tc.desc: Test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnTouchEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnTouchEvent.
     * @tc.expected: isCalendarDialog_ is false, so immediately return.
     */
    CalendarDay calendarDay;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    auto localLocation = Offset(1, 1);
    calendarMonthPattern->OnTouchEvent(localLocation, false);
    EXPECT_FALSE(calendarMonthPattern->isCalendarDialog_);
}

/**
 * @tc.name: OnTouchEventTest003
 * @tc.desc: Test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnTouchEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnTouchEvent.
     * @tc.expected: obtainedMonth_.days is empty, so immediately return.
     */
    calendarMonthPattern->isCalendarDialog_ = true;
    auto localLocation = Offset(1, 1);
    calendarMonthPattern->OnTouchEvent(localLocation, false);
    EXPECT_TRUE(calendarMonthPattern->obtainedMonth_.days.empty());
}

/**
 * @tc.name: OnTouchEventTest004
 * @tc.desc: Test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnTouchEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnTouchEvent.
     * @tc.expected: JudgeArea(localLocation) return negative, so immediately return.
     */
    calendarMonthPattern->isCalendarDialog_ = true;
    CalendarDay calendarDay;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    auto localLocation = Offset(1, 1);
    calendarMonthPattern->OnTouchEvent(localLocation, false);
    EXPECT_TRUE(calendarMonthPattern->JudgeArea(localLocation) < 0);
}

/**
 * @tc.name: OnTouchEventTest005
 * @tc.desc: Test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnTouchEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnTouchEvent.
     * @tc.expected: JudgeArea(localLocation) return negative, so immediately return.
     */
    calendarMonthPattern->isCalendarDialog_ = true;
    CalendarDay calendarDay;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    auto localLocation = Offset(0.0, 0.0);
    calendarMonthPattern->OnTouchEvent(localLocation, false);
    EXPECT_TRUE(calendarMonthPattern->JudgeArea(localLocation) < 0);
}

/**
 * @tc.name: OnHoverEventTest001
 * @tc.desc: Test OnHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnHoverEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnHoverEvent.
     * @tc.expected: isCalendarDialog_ is false, so immediately return.
     */
    calendarMonthPattern->isCalendarDialog_ = false;
    CalendarDay calendarDay;
    auto localLocation = Offset(0.0, 0.0);
    calendarMonthPattern->OnHoverEvent(localLocation, false);
    EXPECT_FALSE(calendarMonthPattern->isCalendarDialog_);
}

/**
 * @tc.name: OnHoverEventTest002
 * @tc.desc: Test OnHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnHoverEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnHoverEvent.
     * @tc.expected: obtainedMonth_.days is empty, so immediately return.
     */
    calendarMonthPattern->isCalendarDialog_ = true;
    CalendarDay calendarDay;
    auto localLocation = Offset(0.0, 0.0);
    calendarMonthPattern->OnHoverEvent(localLocation, false);
    EXPECT_TRUE(calendarMonthPattern->obtainedMonth_.days.empty());
}

/**
 * @tc.name: OnHoverEventTest003
 * @tc.desc: Test OnHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnHoverEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create calendar frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<CalendarTheme>()));
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    /**
     * @tc.steps: step2. call OnHoverEvent.
     * @tc.expected: JudgeArea(localLocation) return negative, so immediately return.
     */
    calendarMonthPattern->isCalendarDialog_ = true;
    CalendarDay calendarDay;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay);
    auto localLocation = Offset(0.0, 0.0);
    calendarMonthPattern->OnHoverEvent(localLocation, false);
    EXPECT_TRUE(calendarMonthPattern->JudgeArea(localLocation) < 0);
}

/**
 * @tc.name: BeforeSyncGeometryProperties001
 * @tc.desc: Test BeforeSyncGeometryProperties
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, BeforeSyncGeometryProperties001, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    DirtySwapConfig config;
    calendarMonthPattern->BeforeSyncGeometryProperties(config);
    EXPECT_NE(pipelineContext->GetTheme<CalendarTheme>(), nullptr);
}

/**
 * @tc.name: OnLanguageConfigurationUpdate001
 * @tc.desc: Test OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnLanguageConfigurationUpdate001, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->OnLanguageConfigurationUpdate();
    EXPECT_NE(pipelineContext->GetTheme<CalendarTheme>(), nullptr);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->OnColorConfigurationUpdate();
    EXPECT_NE(pipelineContext->GetTheme<CalendarTheme>(), nullptr);
}

/**
 * @tc.name: CalendarDialogLayoutAlgorithmTest001
 * @tc.desc: CalendarDialog LayoutAlgorithm Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, CalendarDialogLayoutAlgorithmTest001, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->OnColorConfigurationUpdate();
    EXPECT_NE(pipelineContext->GetTheme<CalendarTheme>(), nullptr);

    auto layoutAlgorithmPattern = AceType::DynamicCast<CalendarMonthPattern>(frameNode->GetPattern());
    ASSERT_NE(layoutAlgorithmPattern, nullptr);

    auto calendarPickerLayoutAlgorithm = layoutAlgorithmPattern->CreateLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(calendarPickerLayoutAlgorithm));

    calendarPickerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(calendarPickerLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: CalendarDialogLayoutAlgorithmTest002
 * @tc.desc: CalendarDialog LayoutAlgorithm Measure Function Test
 * @tc.type: FUNC
 */
HWTEST_F(CalendarMonthTestNg, CalendarDialogLayoutAlgorithmTest002, TestSize.Level1)
{
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 1, 1 },
        .maxSize = { 10, 10 },        // 10 is the maxSize of width and height
        .percentReference = { 5, 5 }, // 5 is the percentReference of width and height
        .parentIdealSize = { 2, 2 },  // 2 is the parentIdealSize of width and height
    };
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<CalendarMonthPattern>(); });
    auto calendarMonthPattern = frameNode->GetPattern<CalendarMonthPattern>();
    ASSERT_NE(calendarMonthPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, AceType::MakeRefPtr<LayoutProperty>());
    calendarMonthPattern->GetHost()->GetLayoutProperty()->layoutConstraint_ = layoutConstraintF;
    CalendarDay calendarDay1;
    calendarMonthPattern->obtainedMonth_.days.push_back(calendarDay1);
    calendarMonthPattern->OnColorConfigurationUpdate();
    EXPECT_NE(pipelineContext->GetTheme<CalendarTheme>(), nullptr);

    auto layoutAlgorithmPattern = AceType::DynamicCast<CalendarMonthPattern>(frameNode->GetPattern());
    ASSERT_NE(layoutAlgorithmPattern, nullptr);

    auto calendarPickerLayoutAlgorithm = layoutAlgorithmPattern->CreateLayoutAlgorithm();
    ASSERT_NE(calendarPickerLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(calendarPickerLayoutAlgorithm));

    calendarPickerLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(calendarPickerLayoutAlgorithm, nullptr);
}
} // namespace OHOS::Ace::NG