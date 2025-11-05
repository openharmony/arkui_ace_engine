/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr float VALUE = 50.0f;
constexpr float STEP = 1.0f;
constexpr float MIN = 0.0f;
constexpr float MAX = 100.0f;
const Color TEST_COLOR = Color::BLUE;
constexpr float MIN_LABEL = 10.0f;
constexpr float MAX_LABEL = 20.0f;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float HALF = 0.5;
constexpr float CONTAINER_WIDTH = 300.0f;
constexpr float CONTAINER_HEIGHT = 300.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr Dimension BLOCK_SIZE_WIDTH = Dimension(300.0);
constexpr Dimension BLOCK_SIZE_HEIGHT = Dimension(300.0);
const SizeT<Dimension> BLOCK_SIZE(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
const std::string SLIDER_MODEL_NG_BLOCK_IMAGE = "Default Image";
const std::string SLIDER_TEST_BUNDLE_NAME = "com.test.slider";
const std::string SLIDER_TEST_MODULE_NAME = "testModule";
const PointF POINTF_START { 10.0f, 10.0f };
const PointF POINTF_END { 20.0f, 20.0f };
const PointF POINTF_START_DIFFX { 20.0f, 10.0f };
const PointF POINTF_END_DIFFX { 10.0f, 20.0f };
const PointF POINTF_START_DIFFY { 10.0f, 20.0f };
const PointF POINTF_END_DIFFY { 20.0f, 10.0f };
const PointF SELECT_START { 10.0f, 10.0f };
const PointF SELECT_END { 20.0f, 20.0f };
const PointF POINTF_CENTER { 15.0f, 15.0f };
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH = 92.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT = 52.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT = 60.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH = 96.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT = 56.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT = 64.0_vp;
const SizeF TEST_SIZE_200 = SizeF(200.0f, 200.0f);
} // namespace
class SliderOneTestNg : public testing::Test {
public:
    void TearDown() override;

    static void SetUpTestSuite();
    static void TearDownTestSuite();

private:
    void SetSliderContentModifier(SliderContentModifier& sliderContentModifier);
    void MockCanvasFunction(Testing::MockCanvas& canvas);
    void MockTipsCanvasFunction(Testing::MockCanvas& canvas);
    void MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas);
};

void SliderOneTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderOneTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderOneTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderOneTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
{
    sliderContentModifier.InitializeShapeProperty();
    sliderContentModifier.SetTrackThickness(SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    sliderContentModifier.SetTrackBorderRadius(SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    sliderContentModifier.SetSelectedBorderRadius(SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS);
    sliderContentModifier.SetTrackBackgroundColor(SliderModelNG::CreateSolidGradient(TEST_COLOR));
    sliderContentModifier.SetShowSteps(true);
    sliderContentModifier.SetStepSize(SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    sliderContentModifier.SetStepColor(TEST_COLOR);
    sliderContentModifier.SetStepRatio(SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetSelectColor(SliderModelNG::CreateSolidGradient(TEST_COLOR));
    SizeF blockSize;
    sliderContentModifier.SetBlockSize(blockSize);
}

void SliderOneTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
{
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRoundRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawPath(_)).WillRepeatedly(Return());
}

void SliderOneTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
{
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Scale(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, ClipPath(_, _, _)).WillRepeatedly(Return());
}

void SliderOneTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
{
    EXPECT_CALL(*paragraph, Paint(An<RSCanvas&>(), _, _)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, AddText(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Build()).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(1.0f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(1.0f));
}
/**
 * @tc.name: SliderOneTestNgInteractionMode008
 * @tc.desc: Test Slider mouse Event and wheel operation
 *           and InteractionMode is SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgInteractionMode008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->showTips_ = true;
    /**
     * @tc.steps: step2. When the mouse moves into the slider area.
     */
    sliderPattern->HandleHoverEvent(true);
    EXPECT_TRUE(sliderPattern->hotFlag_);
    EXPECT_TRUE(sliderPattern->mouseHoverFlag_);
    /**
     * @tc.steps: step3. When the mouse wheel starts scrolling.
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->bubbleFlag_);
    EXPECT_TRUE(sliderPattern->axisFlag_);
    /**
     * @tc.steps: step4. After the mouse wheel starts scrolling, move the mouse out of the slider area
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->HandleHoverEvent(false);
    EXPECT_FALSE(sliderPattern->hotFlag_);
    EXPECT_FALSE(sliderPattern->mouseHoverFlag_);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_FALSE(sliderPattern->axisFlag_);
    /**
     * @tc.steps: step5. When moving the mouse out of the slider area, mouse wheel starts scrolling quickly.
     * @tc.desc: SliderTips will not show.
     */
    sliderPattern->HandleHoverEvent(true);
    sliderPattern->HandleHoverEvent(false);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_FALSE(sliderPattern->hotFlag_);
    EXPECT_FALSE(sliderPattern->mouseHoverFlag_);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_FALSE(sliderPattern->axisFlag_);
}

/**
 * @tc.name: SliderOneTestNgInteractionMode009
 * @tc.desc: Test Slider mouse Event and wheel operation
 *           and InteractionMode is SLIDE_AND_CLICK
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgInteractionMode009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and set theme.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->showTips_ = true;
    /**
     * @tc.steps: step2. When the mouse moves into the slider area.
     */
    sliderPattern->HandleHoverEvent(true);
    EXPECT_TRUE(sliderPattern->hotFlag_);
    EXPECT_TRUE(sliderPattern->mouseHoverFlag_);
    /**
     * @tc.steps: step3. When the mouse wheel starts scrolling.
     */
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->bubbleFlag_);
    EXPECT_TRUE(sliderPattern->axisFlag_);
    /**
     * @tc.steps: step4. After the mouse wheel starts scrolling, move the mouse out of the slider area
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->HandleHoverEvent(false);
    EXPECT_FALSE(sliderPattern->hotFlag_);
    EXPECT_FALSE(sliderPattern->mouseHoverFlag_);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_FALSE(sliderPattern->axisFlag_);
    /**
     * @tc.steps: step5. When moving the mouse out of the slider area, mouse wheel starts scrolling quickly.
     * @tc.desc: SliderTips will not show.
     */
    sliderPattern->HandleHoverEvent(true);
    sliderPattern->HandleHoverEvent(false);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_FALSE(sliderPattern->hotFlag_);
    EXPECT_FALSE(sliderPattern->mouseHoverFlag_);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_FALSE(sliderPattern->axisFlag_);
}

/**
 * @tc.name: SliderOneTestNgInteractionMode010
 * @tc.desc: Test Slider HandlingGestureEvent
 *           SliderIneraction mode set to SLIDE_AND_CLICK
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgInteractionMode010, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    ASSERT_TRUE(sliderPaintProperty->GetSliderInteractionMode().has_value());
    ASSERT_EQ(
        sliderPaintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);

    /**
     * @tc.cases: case1. InputEventType is AXIS and MoveStep(-1).
     */
    sliderPattern->value_ = 1.0f;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    info.SetOffsetX(.0);
    info.SetOffsetY(1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    EXPECT_EQ(sliderPattern->value_, 1.0);
    /**
     * @tc.cases: case2. InputEventType is AXIS and MoveStep(1).
     */
    info.SetOffsetX(-1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    EXPECT_EQ(sliderPattern->value_, 1.0f);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->valueRatio_, 0);
    /**
     * @tc.cases: case3. InputEventType is not AXIS, direction is HORIZONTAL and revese is false.
     */
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    sliderPattern->sliderLength_ = 52.0f;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 19);
    EXPECT_EQ(sliderPattern->valueChangeFlag_, true);
    /**
     * @tc.cases: case4. InputEventType is not AXIS, direction is VERTICAL and revese is true.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateReverse(true);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, 62);
}

/**
 * @tc.name: SliderOneTestNgInteractionMode011
 * @tc.desc: Test Slider HandlingGestureEvent
 *           SliderIneraction mode set to SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgInteractionMode011, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    ASSERT_TRUE(sliderPaintProperty->GetSliderInteractionMode().has_value());
    ASSERT_EQ(sliderPaintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_ONLY);

    /**
     * @tc.cases: case1. InputEventType is AXIS and MoveStep(-1).
     */
    sliderPattern->value_ = VALUE;
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    info.SetOffsetX(.0);
    info.SetOffsetY(1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    /**
     * @tc.cases: case2. InputEventType is AXIS and MoveStep(1).
     */
    info.SetOffsetX(-1.0);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    sliderPaintProperty->UpdateStep(.0);
    sliderPattern->HandlingGestureEvent(info);
    /**
     * @tc.cases: case3. InputEventType is not AXIS, direction is HORIZONTAL and revese is false.
     */
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    sliderPattern->sliderLength_ = 52.0f;
    sliderPattern->HandlingGestureStart(info);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
    EXPECT_EQ(sliderPattern->valueChangeFlag_, false);
    /**
     * @tc.cases: case4. InputEventType is not AXIS, direction is VERTICAL and revese is true.
     */
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateReverse(true);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(sliderPattern->value_, VALUE);
}

/**
 * @tc.name: SliderOneTestNgInteractionMode012
 * @tc.desc: Test Slider HandlingGestureEvent by Slider block
 *           SliderIneraction mode set to SLIDE_ONLY
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgInteractionMode012, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    frameNode->geometryNode_->SetContentOffset(OffsetF());
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    ASSERT_TRUE(sliderPaintProperty->GetSliderInteractionMode().has_value());
    ASSERT_EQ(sliderPaintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_ONLY);

    /**
     * @tc.cases: case1. InputEventType is not AXIS and drag by block to 20.0
     */
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);

    sliderPattern->value_ = VALUE;
    sliderPattern->sliderLength_ = MAX;
    sliderPattern->valueRatio_ = 0.5;
    sliderPattern->UpdateCircleCenterOffset();

    EXPECT_EQ(sliderPattern->circleCenter_.GetX(), VALUE);
    EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
    info.localLocation_ = Offset(VALUE, 0);

    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    EXPECT_FALSE(sliderPattern->panMoveFlag_);
    EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
    sliderPattern->HandlingGestureStart(info);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));

    info.SetOffsetX(20.0f);
    info.localLocation_ = Offset(VALUE + 20.0f, info.localLocation_.GetY());
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->panMoveFlag_);
    EXPECT_TRUE(sliderPattern->valueChangeFlag_);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));
    EXPECT_NE(sliderPattern->value_, VALUE);
    sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);

    /**
     * @tc.cases: case2. InputEventType is not AXIS and drag by block to -20.0
     */
    sliderPattern->value_ = VALUE;
    sliderPattern->sliderLength_ = MAX;
    sliderPattern->valueRatio_ = 0.5;
    sliderPattern->UpdateCircleCenterOffset();

    EXPECT_EQ(sliderPattern->circleCenter_.GetX(), VALUE);
    EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
    info.localLocation_ = Offset(VALUE, 0);

    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
    sliderPattern->HandlingGestureStart(info);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));

    info.SetOffsetX(-20.0f);
    info.localLocation_ = Offset(VALUE - 20.0f, info.localLocation_.GetY());
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_TRUE(sliderPattern->panMoveFlag_);
    EXPECT_TRUE(sliderPattern->valueChangeFlag_);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(info.GetLocalLocation()));
    EXPECT_NE(sliderPattern->value_, VALUE);
    sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
}


/**
 * @tc.name: SliderOneTestNgInteractionMode013
 * @tc.desc: Test Slider InteractionMode Set Func
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgInteractionMode013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get SliderIntecationMode.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_EQ(sliderPaintProperty->GetSliderInteractionMode(), SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP);
}

/**
 * @tc.name: SliderOneTestNgMinResponse001
 * @tc.desc: Test Slider MinResponse as default
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgMinResponse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get SliderIntecationMode by default.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_FALSE(sliderPaintProperty->GetMinResponsiveDistance().has_value());
}

/**
 * @tc.name: SliderOneTestNgMinResponse002
 * @tc.desc: Test Slider SetMinResponse
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgMinResponse002, TestSize.Level1)
{
    //first: set value as minResponsiveDistance
    //second: expected return value of minResponsiveDistance
    std::vector<std::pair<float, float>> testMinResponseValue {
        std::make_pair<float, float>(-1.0f, 0.0f),
        std::make_pair<float, float>(0.0f, 0.0f),
        std::make_pair<float, float>(1.0f, 1.0f),
        std::make_pair<float, float>(STEP - 1.0f, STEP - 1.0f),
        std::make_pair<float, float>(static_cast<float>(STEP), static_cast<float>(STEP)),
        std::make_pair<float, float>(STEP * 10, STEP * 10),
        std::make_pair<float, float>(STEP + 1.0f, STEP + 1.0f),
        std::make_pair<float, float>(STEP * 20, STEP * 20),
        std::make_pair<float, float>(static_cast<float>(MAX), static_cast<float>(MAX)),
        std::make_pair<float, float>(MAX + 1.0f, 0.0f),
    };

    for (auto testData : testMinResponseValue) {
        /**
        * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
        */
        SliderModelNG sliderModelNG;
        sliderModelNG.Create(VALUE, STEP, MIN, MAX);
        sliderModelNG.SetMinResponsiveDistance(testData.first);
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        /**
        * @tc.steps: step2. get SliderIntecationMode by default.
        * @tc.expected: step2. check whether the properties is correct.
        */
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
        EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
        EXPECT_TRUE(sliderPaintProperty->GetMinResponsiveDistance().has_value());
        EXPECT_EQ(sliderPaintProperty->GetMinResponsiveDistance().value_or(-10.0f), testData.second);
    }
}

/**
 * @tc.name: SliderOneTestNgMinResponse003
 * @tc.desc: Test Slider MinResponse
 * Increase Slider value by dragging Slider block
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgMinResponse003, TestSize.Level1)
{
    //first: draggin value by Gesture handling
    //second: expected Slider Value after call HandlingGestureEvent
    constexpr float stepValue = 10.0f;
    constexpr float minResponseValue = 20.0f;
    constexpr float startValue = 20.0f;
    std::vector<std::pair<float, float>> testMinResponseDistanceOffset {
        std::pair<float, float>(1.0f, 0.0f),
        std::pair<float, float>(stepValue * HALF - 1, 0.0f),
        std::pair<float, float>(stepValue * HALF, 0.0f),
        std::pair<float, float>(stepValue * HALF + 1, 0.0f),
        std::pair<float, float>(stepValue, 0.0f),
        std::pair<float, float>(stepValue + 1, 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF - 1), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF + 1), 0.0f),
        std::pair<float, float>(minResponseValue - 1, 0.0f),
        std::pair<float, float>(minResponseValue, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 2, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(
            minResponseValue + stepValue * HALF - 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(
            minResponseValue + stepValue * HALF, std::floor((minResponseValue + stepValue) / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + stepValue * HALF + 1,
            std::floor((minResponseValue + stepValue) / stepValue) * stepValue),
    };

    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    for (auto testData : testMinResponseDistanceOffset) {
        SliderModelNG sliderModelNG;

        sliderModelNG.Create(startValue, stepValue, MIN, MAX);
        sliderModelNG.SetMinResponsiveDistance(minResponseValue);
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        frameNode->geometryNode_->SetContentOffset(OffsetF());
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        ASSERT_NE(sliderPaintProperty, nullptr);

        /**
         * @tc.steps: step2. get SliderIntecationMode by default.
         * @tc.expected: step2. check whether the properties is correct.
         */
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), stepValue);
        EXPECT_EQ(sliderPaintProperty->GetValue(), startValue);

        GestureEvent info;
        info.SetSourceDevice(SourceType::TOUCH);
        sliderPattern->value_ = startValue;
        sliderPattern->sliderLength_ = MAX;
        sliderPattern->valueRatio_ = startValue / MAX;
        sliderPattern->UpdateCircleCenterOffset();

        EXPECT_EQ(sliderPattern->circleCenter_.GetX(), startValue);
        EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
        info.localLocation_ = Offset(startValue, 0);

        info.inputEventType_ = InputEventType::TOUCH_SCREEN;
        EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
        sliderPattern->HandlingGestureStart(info);

        info.SetOffsetX(testData.first + startValue);
        info.localLocation_ = Offset(startValue + testData.first, info.localLocation_.GetY());
        sliderPattern->HandlingGestureEvent(info);
        EXPECT_EQ(sliderPattern->value_, testData.second + startValue);
        sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
    }
}

/**
 * @tc.name: SliderOneTestNgMinResponse004
 * @tc.desc: Test Slider MinResponse
 * Decrease Slider value by dragging Slider block
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgMinResponse004, TestSize.Level1)
{
    //first: draggin value by Gesture handling
    //second: expected Slider Value after call HandlingGestureEvent
    constexpr float stepValue = 10.0f;
    constexpr float minResponseValue = 20.0f;
    constexpr float startValue = 70.0f;
    std::vector<std::pair<float, float>> testMinResponseDistanceOffset {
        std::pair<float, float>(1.0f, 0.0f),
        std::pair<float, float>(stepValue * HALF - 1, 0.0f),
        std::pair<float, float>(stepValue * HALF, 0.0f),
        std::pair<float, float>(stepValue * HALF + 1, 0.0f),
        std::pair<float, float>(stepValue, 0.0f),
        std::pair<float, float>(stepValue + 1, 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF - 1), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF), 0.0f),
        std::pair<float, float>(stepValue + (stepValue * HALF + 1), 0.0f),
        std::pair<float, float>(minResponseValue - 1, 0.0f),
        std::pair<float, float>(minResponseValue, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + 2, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(
            minResponseValue + stepValue * HALF - 1, std::floor(minResponseValue / stepValue) * stepValue),
        std::pair<float, float>(minResponseValue + stepValue * HALF + 1,
            std::floor((minResponseValue + stepValue) / stepValue) * stepValue),
    };

    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    for (auto testData : testMinResponseDistanceOffset) {
        SliderModelNG sliderModelNG;

        sliderModelNG.Create(startValue, stepValue, MIN, MAX);
        sliderModelNG.SetMinResponsiveDistance(minResponseValue);
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        frameNode->geometryNode_->SetContentOffset(OffsetF());
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        ASSERT_NE(sliderPaintProperty, nullptr);

        /**
         * @tc.steps: step2. get SliderIntecationMode by default.
         * @tc.expected: step2. check whether the properties is correct.
         */
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), stepValue);
        EXPECT_EQ(sliderPaintProperty->GetValue(), startValue);

        GestureEvent info;
        info.SetSourceDevice(SourceType::TOUCH);
        sliderPattern->value_ = startValue;
        sliderPattern->sliderLength_ = MAX;
        sliderPattern->valueRatio_ = startValue / MAX;
        sliderPattern->UpdateCircleCenterOffset();

        EXPECT_EQ(sliderPattern->circleCenter_.GetX(), startValue);
        EXPECT_EQ(sliderPattern->circleCenter_.GetY(), 0);
        info.localLocation_ = Offset(startValue, 0);

        info.inputEventType_ = InputEventType::TOUCH_SCREEN;
        EXPECT_TRUE(sliderPattern->AtPanArea(info.GetLocalLocation(), info.GetSourceDevice()));
        sliderPattern->HandlingGestureStart(info);

        info.SetOffsetX(startValue - testData.first);
        info.localLocation_ = Offset(startValue - testData.first, info.localLocation_.GetY());
        sliderPattern->HandlingGestureEvent(info);
        EXPECT_EQ(sliderPattern->value_, startValue - testData.second);
        sliderPattern->FireChangeEvent(SliderPattern::SliderChangeMode::End);
    }
}

/**
 * @tc.name: PaintHorizontalBubbleSuitableAgingTest001
 * @tc.desc: TEST slider_tip_modifier PaintHorizontalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, PaintHorizontalBubbleSuitableAgingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call PaintHorizontalBubbleSuitableAging function.
     * @tc.cases: sliderGlobalOffset_ = SLIDER_GLOBAL_OFFSET, suitable aging level = 1.
     */
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
        BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    RSPath path1;
    auto vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock1 = vertexPair.second;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock1, path1);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx()));
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    /**
     * @tc.cases: sliderGlobalOffset_ = OffsetF(), suitable aging level = 1.
     */
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
        BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock2 = vertexPair.second;
    RSPath path2;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock2, path2);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: PaintHorizontalBubbleSuitableAgingTest002
 * @tc.desc: TEST slider_tip_modifier PaintHorizontalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, PaintHorizontalBubbleSuitableAgingTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call PaintHorizontalBubbleSuitableAging function.
     * @tc.cases: sliderGlobalOffset_ = SLIDER_GLOBAL_OFFSET, suitable aging level = 2.
     */
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
        BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    RSPath path1;
    auto vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock1 = vertexPair.second;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock1, path1);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx()));
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    /**
     * @tc.cases: sliderGlobalOffset_ = OffsetF(), suitable aging level = 2.
     */
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock2 = vertexPair.second;
    RSPath path2;
    sliderTipModifier.PaintHorizontalBubbleSuitableAging(vertexOffsetFromBlock2, path2);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
                                                 BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: PaintVerticalBubbleSuitableAgingTest001
 * @tc.desc: TEST slider_tip_modifier PaintVerticalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, PaintVerticalBubbleSuitableAgingTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call PaintVerticalBubbleSuitableAging function.
     * @tc.cases: sliderGlobalOffset_ = OffsetF(), suitable aging level = 1.
     */
    SliderModelNG sliderModelNG;
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
    sliderTipModifier.SetDirection(Axis::VERTICAL);
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
        BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    RSPath path1;
    auto vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock1 = vertexPair.second;
    sliderTipModifier.PaintVerticalBubbleSuitableAging(vertexOffsetFromBlock1, path1);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
                                                 BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx()));
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    /**
     * @tc.cases: sliderGlobalOffset_ = SLIDER_GLOBAL_OFFSET, suitable aging level = 1.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock2 = vertexPair.second;
    RSPath path2;
    sliderTipModifier.PaintVerticalBubbleSuitableAging(vertexOffsetFromBlock2, path2);
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx(),
                                                 BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: PaintVerticalBubbleSuitableAgingTest002
 * @tc.desc: TEST slider_tip_modifier PaintVerticalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, PaintVerticalBubbleSuitableAgingTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderTipModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SliderTipModifier sliderTipModifier(
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call PaintVerticalBubbleSuitableAging function.
     * @tc.cases: sliderGlobalOffset_ = OffsetF(), suitable aging level = 2.
     */
    SliderModelNG sliderModelNG;
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
    sliderTipModifier.SetDirection(Axis::VERTICAL);
    sliderTipModifier.bubbleSize_ = SizeF(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
        BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    RSPath path1;
    auto vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock1 = vertexPair.second;
    sliderTipModifier.PaintVerticalBubbleSuitableAging(vertexOffsetFromBlock1, path1);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
                                                 BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx()));
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    /**
     * @tc.cases: sliderGlobalOffset_ = SLIDER_GLOBAL_OFFSET, suitable aging level = 2.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    vertexPair = sliderTipModifier.GetBubbleVertex();
    sliderTipModifier.vertex_ = vertexPair.first;
    auto vertexOffsetFromBlock2 = vertexPair.second;
    RSPath path2;
    sliderTipModifier.PaintVerticalBubbleSuitableAging(vertexOffsetFromBlock2, path2);
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx(),
                                                 BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SliderOneTestNgMeasureContent0001
 * @tc.desc: Test Slider MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgMeasureContent0001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    SliderModelNG sliderModelNG;
    constexpr float stepValue = 10.0f;
    constexpr float startValue = 70.0f;
    sliderModelNG.Create(startValue, stepValue, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set sliderLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    ASSERT_NE(sliderLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm));

    /**
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step3. ret Width is equal to TEST_SIZE_200 Width.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto ret = sliderLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret->Width(), TEST_SIZE_200.Width());
}

/**
 * @tc.name: SliderOneTestNgMeasureContent0002
 * @tc.desc: Test Slider MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderOneTestNgMeasureContent0002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    SliderModelNG sliderModelNG;
    constexpr float stepValue = 10.0f;
    constexpr float startValue = 70.0f;
    sliderModelNG.Create(startValue, stepValue, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapperNode and set sliderLayoutAlgorithm.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    ASSERT_NE(sliderLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm));

    /**
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to null.
     * @tc.expected: step3. ret Width is equal to TEST_SIZE_200 Width.
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_SIZE_200);
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto ret = sliderLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(ret, TEST_SIZE_200);

    /**
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to FIX_AT_IDEAL_SIZE.
     * @tc.expected: step3. ret Width is equal to TEST_SIZE_200 Width.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = sliderLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, BLOCK_SIZE_F_ZREO);

    /**
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to FIX_AT_IDEAL_SIZE.
     * @tc.expected: step3. ret Width is equal to TEST_SIZE_200 Width.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::WRAP_CONTENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    ret = sliderLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(ret, BLOCK_SIZE_F_ZREO);
}

/**
 * @tc.name: ColorTypeToStringTest001
 * @tc.desc: test ColorTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, ColorTypeToStringTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare test data with SliderColorType and expected string mappings.
     * @tc.expected: step1. Test data contains valid color type to string mappings.
     */
    std::vector<std::pair<SliderColorType, std::string>> types = { { SliderColorType::BLOCK_COLOR, "BlockColor" },
        { SliderColorType::TRACK_COLOR, "TrackColor" }, { SliderColorType::SELECT_COLOR, "SelectColor" },
        { SliderColorType::BLOCK_BORDER_COLOR, "BlockBorderColor" }, { SliderColorType::STEP_COLOR, "StepColor" },
        { static_cast<SliderColorType>(5), "Unknown" } };

    /**
     * @tc.steps: step2. Iterate through each test pair and call ColorTypeToString.
     * @tc.expected: step2. The function returns the expected string for each color type.
     */
    for (const auto& [type, val] : types) {
        auto ret = SliderModelNG::ColorTypeToString(type);
        EXPECT_EQ(val, ret);
    }
}

/**
 * @tc.name: UpdateComponentColorTest001
 * @tc.desc: test UpdateComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, UpdateComponentColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider model and validate frame node, context and paint property.
     * @tc.expected: step1. Frame node, pipeline context and paint property are created and valid.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. Test individual color updates for all SliderColorType values.
     * @tc.expected: step2. Each color property is updated and retrievable with the set value.
     */
    paintProperty->UpdateBlockColor(Color::RED);
    auto ret = paintProperty->GetBlockColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);

    Gradient gradientRet;
    gradientRet.AddColor(GradientColor(Color::RED));
    paintProperty->UpdateTrackBackgroundColor(gradientRet);
    EXPECT_TRUE(paintProperty->GetTrackBackgroundColor().has_value());
    ret = paintProperty->GetTrackBackgroundColor()->GetColors().front().GetColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);

    paintProperty->UpdateBlockBorderColor(Color::RED);
    ret = paintProperty->GetBlockBorderColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);

    paintProperty->UpdateStepColor(Color::RED);
    ret = paintProperty->GetStepColor();
    EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);

    /**
     * @tc.steps: step3. Test UpdateComponentColor under different system color change and rerenderable states.
     * @tc.expected: step3. When system color changes and node is rerenderable, color properties are reset.
     */
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        frameNode->SetRerenderable(pair.second);
        sliderModelNG.UpdateComponentColor(frameNode, static_cast<SliderColorType>(5));
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            sliderModelNG.UpdateComponentColor(frameNode, SliderColorType::BLOCK_COLOR);
            ret = paintProperty->GetBlockColor();
            EXPECT_FALSE(ret.has_value());
            sliderModelNG.UpdateComponentColor(frameNode, SliderColorType::SELECT_COLOR);
            ret = paintProperty->GetSelectColor();
            EXPECT_FALSE(ret.has_value());
            sliderModelNG.UpdateComponentColor(frameNode, SliderColorType::BLOCK_BORDER_COLOR);
            ret = paintProperty->GetBlockBorderColor();
            EXPECT_FALSE(ret.has_value());
            sliderModelNG.UpdateComponentColor(frameNode, SliderColorType::STEP_COLOR);
            ret = paintProperty->GetStepColor();
            EXPECT_FALSE(ret.has_value());
            sliderModelNG.UpdateComponentColor(frameNode, SliderColorType::TRACK_COLOR);
            auto gradientRe = paintProperty->GetTrackBackgroundColor();
            EXPECT_FALSE(gradientRe.has_value());
        }
    }
}

/**
 * @tc.name: CreateWithColorResourceObj
 * @tc.desc: Test Slider CreateWithColorResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, CreateWithColorResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider model and validate frame node.
     * @tc.expected: step1. Frame node is created and not null.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    std::cout << "frameNode addr " << frameNode << std::endl;

    /**
     * @tc.steps: step2. Create color resource object and associate with SELECT_COLOR type.
     * @tc.expected: step2. Resource object is created and associated with the correct key in resource manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    sliderModelNG.CreateWithColorResourceObj(resObj, SliderColorType::SELECT_COLOR);

    /**
     * @tc.steps: step3. Validate resource object is registered in pattern's resource manager.
     * @tc.expected: step3. Resource manager contains exactly one entry with the generated key.
     */
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    std::cout << "pattern addr" << AceType::RawPtr(pattern) << std::endl;
    std::string key = "slider" + sliderModelNG.ColorTypeToString(SliderColorType::SELECT_COLOR);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithMediaResourceObj
 * @tc.desc: Test Slider CreateWithMediaResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, CreateWithMediaResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider model and validate frame node.
     * @tc.expected: step1. Frame node is created and not null.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create media resource object with specified bundle and module names.
     * @tc.expected: step2. Resource object is created and registered with correct key in resource manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    sliderModelNG.CreateWithMediaResourceObj(resObj, "bundleName", "ModuleName");

    /**
     * @tc.steps: step3. Validate resource object is registered in pattern's resource manager.
     * @tc.expected: step3. Resource manager contains exactly one entry with the key "sliderImage".
     */
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "sliderImage";
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: CreateWithStringResourceObj
 * @tc.desc: Test Slider CreateWithStringResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, CreateWithStringResourceObj, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider model and validate frame node.
     * @tc.expected: step1. Frame node is created and not null.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create string resource object with specified parameter.
     * @tc.expected: step2. Resource object is created and registered with correct key in resource manager.
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    sliderModelNG.CreateWithStringResourceObj(resObj, true);

    /**
     * @tc.steps: step3. Validate resource object is registered in pattern's resource manager.
     * @tc.expected: step3. Resource manager contains exactly one entry with the key "sliderShowTips".
     */
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    std::string key = "sliderShowTips";
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    auto count = resMgr->resMap_.count(key);
    EXPECT_EQ(count, 1);
}

/**
 * @tc.name: SliderContentModifierTest
 * @tc.desc: Test SliderContentModifier Constructor
 * @tc.type: FUNC
 */
HWTEST_F(SliderOneTestNg, SliderContentModifierTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parameters.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.blockColor = std::nullopt;
    parameters.blockGradientColor = SliderModelNG::CreateSolidGradient(TEST_COLOR);
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    std::vector<GradientColor> gradientColors = sliderPattern->sliderContentModifier_->GetBlockColor();
    for (size_t i = 0; i < gradientColors.size(); i++) {
        EXPECT_EQ(gradientColors[i].GetLinearColor().ToColor(), TEST_COLOR);
    }
    parameters.blockColor = TEST_COLOR;
    parameters.blockGradientColor = std::nullopt;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    gradientColors = sliderPattern->sliderContentModifier_->GetBlockColor();
    for (size_t i = 0; i < gradientColors.size(); i++) {
        EXPECT_EQ(gradientColors[i].GetLinearColor().ToColor(), TEST_COLOR);
    }
    parameters.blockGradientColor = std::nullopt;
    parameters.blockColor = std::nullopt;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SliderTheme>();
    ASSERT_NE(theme, nullptr);
    Color themeColor = theme->GetBlockColor();
    gradientColors = sliderPattern->sliderContentModifier_->GetBlockColor();
    for (size_t i = 0; i < gradientColors.size(); i++) {
        EXPECT_EQ(gradientColors[i].GetLinearColor().ToColor(), themeColor);
    }
}
} // namespace OHOS::Ace::NG
