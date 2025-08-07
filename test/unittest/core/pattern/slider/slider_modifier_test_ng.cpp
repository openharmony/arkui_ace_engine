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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
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
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float FRAME_WIDTH = 10.0f;
constexpr float FRAME_HEIGHT = 20.0f;
constexpr Dimension RADIUS = Dimension(10.0);
constexpr float SLIDER_WIDTH = 10.0f;
constexpr float SLIDER_HEIGHT = 20.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS_DIFF = 1.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL = 8.0f;
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
const Dimension RADIUS_X = Dimension(20.1, DimensionUnit::PX);
const Dimension RADIUS_Y = Dimension(20.1, DimensionUnit::PX);
const Dimension SHAPE_WIDTH = 10.0_vp;
const Dimension SHAPE_HEIGHT = 20.0_vp;
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
constexpr float SLIDER_NEGATIVE = -5.0f;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH = 92.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT = 52.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT = 60.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH = 96.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT = 56.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT = 64.0_vp;
constexpr Dimension SUITABLEAGING_LEVEL_1_TEXT_FONT_SIZE = 25.0_vp;
constexpr Dimension SUITABLEAGING_LEVEL_2_TEXT_FONT_SIZE = 28.0_vp;
constexpr float SCALE_VALUE = 1.5f;
} // namespace
class SliderModifierTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    static void SetUpTestSuite();
    static void TearDownTestSuite();

private:
    void SetSliderContentModifier(SliderContentModifier& sliderContentModifier);
    void MockCanvasFunction(Testing::MockCanvas& canvas);
    void MockTipsCanvasFunction(Testing::MockCanvas& canvas);
    void MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas);
};

void SliderModifierTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderModifierTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderModifierTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
}

void SliderModifierTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderModifierTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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
    sliderContentModifier.SetBlockColor(TEST_COLOR);
    SizeF blockSize;
    sliderContentModifier.SetBlockSize(blockSize);
}

void SliderModifierTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderModifierTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderModifierTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderContentModifierTest001
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = HORIZONTAL, blockType = DEFAULT, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetCircleCenter(POINTF_CENTER);
    // set direction FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    sliderContentModifier.SetCircleCenter(POINTF_CENTER);
    // set animatorStatus default
    sliderContentModifier.SetAnimatorStatus(SliderStatus::DEFAULT);
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetCircleCenter(POINTF_CENTER);
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType DEFAULT
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::DEFAULT));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest002
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.GetBlockCenter();
    sliderContentModifier.GetTrackThickness();
    sliderContentModifier.GetBlockSize();
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.selectedBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest003
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    auto circle = AceType::DynamicCast<Circle>(basicShape);
    circle->SetRadius(RADIUS);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest004
 * @tc.desc: TEST slider_content_modifier onDraw and DrawSelect
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.selectStart = SELECT_START;
    parameters.selectEnd = SELECT_END;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    sliderContentModifier.DrawSelect(context);
    sliderContentModifier.SetDirection(Axis::FREE);
    sliderContentModifier.DrawSelect(context);
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.DrawSelect(context);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.DrawSelect(context);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest005
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest006
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = ELLIPSE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType ELLIPSE
    auto basicShape = AceType::MakeRefPtr<Ellipse>();
    basicShape->SetBasicShapeType(BasicShapeType::ELLIPSE);
    basicShape->SetRadiusX(RADIUS_X);
    basicShape->SetRadiusY(RADIUS_Y);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest007
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = PATH, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType PATH
    auto basicShape = AceType::MakeRefPtr<Path>();
    basicShape->SetBasicShapeType(BasicShapeType::PATH);
    basicShape->SetValue("PATH");
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode INSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    sliderContentModifier.SetBlockSize(SizeF(BLOCK_SIZE_WIDTH.ConvertToPx(), BLOCK_SIZE_HEIGHT.ConvertToPx()));
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest008
 * @tc.desc: TEST slider_content_modifier onDraw
 * direction = FREE, blockType = SHAPE, blockShape = RECT, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis FREE
    sliderContentModifier.SetDirection(Axis::FREE);
    // set BlockStyleType SHAPE
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    // set BasicShapeType RECT
    auto basicShape = AceType::MakeRefPtr<ShapeRect>();
    basicShape->SetBasicShapeType(BasicShapeType::RECT);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    EXPECT_EQ(sliderContentModifier.trackThickness_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS);
    EXPECT_EQ(sliderContentModifier.trackBorderRadius_->Get(), SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::FREE));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::SHAPE));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest009
 * @tc.desc: TEST slider_content_modifier SetBlockShape with invalid circle
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. call SetBlockShape function with invalid circle.
     */
    auto basicShape = AceType::MakeRefPtr<Circle>();
    ASSERT_NE(basicShape, nullptr);
    basicShape->SetRadius(Dimension());
    basicShape->SetWidth(SHAPE_WIDTH);
    basicShape->SetHeight(SHAPE_HEIGHT);
    sliderContentModifier.SetBlockShape(basicShape);
    EXPECT_EQ(sliderContentModifier.circleRadius_->Get(), std::min(SHAPE_WIDTH, SHAPE_HEIGHT).ConvertToPx() * HALF);
}

/**
 * @tc.name: SliderContentModifierTest010
 * @tc.desc: TEST slider_content_modifier SetBlockShape with invalid ellipse
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. call SetBlockShape function with invalid ellipse.
     */
    auto basicShape = AceType::MakeRefPtr<Ellipse>();
    ASSERT_NE(basicShape, nullptr);
    basicShape->SetRadiusX(Dimension());
    basicShape->SetRadiusY(Dimension());
    basicShape->SetWidth(SHAPE_WIDTH);
    basicShape->SetHeight(SHAPE_HEIGHT);
    sliderContentModifier.SetBlockShape(basicShape);
    EXPECT_EQ(sliderContentModifier.ellipseRadiusX_->Get(), SHAPE_WIDTH.ConvertToPx() * HALF);
    EXPECT_EQ(sliderContentModifier.ellipseRadiusY_->Get(), SHAPE_HEIGHT.ConvertToPx() * HALF);
}

/**
 * @tc.name: SliderContentModifierTest011
 * @tc.desc: TEST slider_content_modifier DrawBlockShape with invalid shape
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. call SetBlockShape function with invalid shape.
     */
    auto basicShape = AceType::MakeRefPtr<BasicShape>();
    ASSERT_NE(basicShape, nullptr);
    basicShape->SetWidth(SHAPE_WIDTH);
    basicShape->SetHeight(SHAPE_HEIGHT);
    sliderContentModifier.SetBlockShape(basicShape);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    // Draw nothing
    sliderContentModifier.DrawBlockShape(context);
    EXPECT_CALL(canvas, AttachBrush(_)).Times(0);
    EXPECT_CALL(canvas, AttachPen(_)).Times(0);
}

/**
 * @tc.name: SliderContentModifierTest012
 * @tc.desc: TEST slider_content_modifier DrawStep with invalid parameter
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sliderContentModifier.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    sliderContentModifier.isShowStep_->Set(true);
    sliderContentModifier.stepRatio_->Set(.0f);
    /**
     * @tc.steps: step2. call DrawStep function with invalid parameter.
     */
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    // Draw nothing
    sliderContentModifier.DrawStep(context);
    EXPECT_CALL(canvas, AttachBrush(_)).Times(0);
    EXPECT_CALL(canvas, AttachPen(_)).Times(0);
    EXPECT_TRUE(sliderContentModifier.GetStepPointVec().empty());
}

/**
 * @tc.name: SliderContentModifierTest013
 * @tc.desc: Test DrawStep while not show step
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest013, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    auto isShowStep = AceType::MakeRefPtr<PropertyBool>(false);
    sliderContentModifier.isShowStep_ = isShowStep;
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawStep(context);
    EXPECT_FALSE(sliderContentModifier.isShowStep_->Get());
    EXPECT_TRUE(sliderContentModifier.GetStepPointVec().empty());
}

/**
 * @tc.name: SliderContentModifierTest014
 * @tc.desc: Test JudgeNeedAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest014, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    sliderContentModifier.reverse_ = true;
    sliderContentModifier.JudgeNeedAnimate(false);
    EXPECT_EQ(sliderContentModifier.animatorStatus_, SliderStatus::DEFAULT);
    EXPECT_FALSE(sliderContentModifier.reverse_);
}

/**
 * @tc.name: SliderContentModifierTest015
 * @tc.desc: Test SetSelectSize while need needAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest015, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    ASSERT_NE(sliderContentModifier.selectEnd_, nullptr);

    sliderContentModifier.animatorStatus_ = SliderStatus::MOVE;
    sliderContentModifier.SetSelectSize(POINTF_START, POINTF_END);
    EXPECT_EQ(sliderContentModifier.selectEnd_->Get(), POINTF_END - PointF());
}

/**
 * @tc.name: SliderContentModifierTest016
 * @tc.desc: Test SetCircleCenter while needAnimate
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest016, TestSize.Level1)
{
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    ASSERT_NE(sliderContentModifier.blockCenterX_, nullptr);
    ASSERT_NE(sliderContentModifier.blockCenterY_, nullptr);

    sliderContentModifier.animatorStatus_ = SliderStatus::MOVE;
    PointF center(FRAME_WIDTH, FRAME_HEIGHT);
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_HEIGHT);

    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.SetCircleCenter(center);
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_HEIGHT);

    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::NONE));
    sliderContentModifier.SetCircleCenter(PointF(FRAME_WIDTH, FRAME_WIDTH));
    EXPECT_EQ(sliderContentModifier.blockCenterX_->Get(), FRAME_WIDTH);
    EXPECT_EQ(sliderContentModifier.blockCenterY_->Get(), FRAME_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest017
 * @tc.desc: Test DrawBlock while blockType is image
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create content modifier and set image block property.
     */
    SliderContentModifier::Parameters parameters;
    OffsetF value;
    auto updateImageCenterX = [&value](float x) { value.SetX(x); };
    auto updateImageCenterY = [&value](float y) { value.SetY(y); };
    SliderContentModifier sliderContentModifier(parameters, updateImageCenterX, updateImageCenterY);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::IMAGE);

    /**
     * @tc.steps: step2. start SliderContentModifier SetCircleCenter func.
     * @tc.cases: case1. when the block center changes.
     */
    PointF center(FRAME_WIDTH, FRAME_HEIGHT);
    sliderContentModifier.SetCircleCenter(center);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawBlock(context);
    EXPECT_EQ(value.GetY(), FRAME_HEIGHT);

    SliderContentModifier sliderContentModifierPro(parameters, nullptr, nullptr);
    sliderContentModifierPro.SetBlockType(SliderModelNG::BlockStyleType::IMAGE);
    sliderContentModifierPro.DrawBlock(context);
    EXPECT_EQ(sliderContentModifierPro.updateImageCenterX_, nullptr);
    EXPECT_EQ(sliderContentModifierPro.updateImageCenterX_, nullptr);
}

/**
 * @tc.name: SliderContentModifierTest018
 * @tc.desc: Test StopSelectAnimation Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create content modifier and set property callback.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    OffsetF value;
    bool set = false;
    auto animatablePropertySetCallback = [&value, &set](const OffsetF& arg) {
        value = arg;
        set = true;
    };
    auto animatablePropertyGetCallback = [&value]() { return value; };
    sliderContentModifier.selectEnd_->SetUpCallbacks(animatablePropertyGetCallback, animatablePropertySetCallback);

    /**
     * @tc.steps: step2. start SliderContentModifier StopSelectAnimation func.
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_START - PointF();
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_END - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(SELECT_END - PointF());
    sliderContentModifier.targetSelectEnd_ = POINTF_CENTER - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is VERTICAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_START - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(POINTF_CENTER - PointF());
    sliderContentModifier.targetSelectEnd_ = SELECT_END - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.selectEnd_->Set(SELECT_END - PointF());
    sliderContentModifier.targetSelectEnd_ = POINTF_CENTER - PointF();
    set = false;
    sliderContentModifier.StopSelectAnimation();
    ASSERT_TRUE(set);
}

/**
 * @tc.name: SliderContentModifierTest019
 * @tc.desc: Test StopSelectAnimation Function
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create content modifier and set property callback.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    float blockCenterX;
    float blockCenterY;
    bool set = false;
    auto animatablePropertySetCallback = [&blockCenterX, &set](const float& arg) {
        blockCenterX = arg;
        set = true;
    };
    auto animatablePropertyGetCallback = [&blockCenterX]() { return blockCenterX; };
    sliderContentModifier.blockCenterX_->SetUpCallbacks(animatablePropertyGetCallback, animatablePropertySetCallback);

    /**
     * @tc.steps: step2. start SliderContentModifier StopCircleCenterAnimation func.
     * @tc.cases: case1. when sliderPaintProperty's direction is HORIZONTAL.
     */
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::HORIZONTAL));
    sliderContentModifier.blockCenterX_->Set(POINTF_CENTER.GetX());
    sliderContentModifier.targetCenter_ = POINTF_START;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterX_->Set(POINTF_CENTER.GetX());
    sliderContentModifier.targetCenter_ = POINTF_END;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterX_->Set(POINTF_END.GetX());
    sliderContentModifier.targetCenter_ = POINTF_CENTER;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    /**
     * @tc.cases: case2. when sliderPaintProperty's direction is VERTICAL.
     */
    auto animatablePropertySetCallback2 = [&blockCenterY, &set](const float& arg) {
        blockCenterY = arg;
        set = true;
    };
    auto animatablePropertyGetCallback2 = [&blockCenterY]() { return blockCenterY; };
    sliderContentModifier.blockCenterY_->SetUpCallbacks(animatablePropertyGetCallback2, animatablePropertySetCallback2);
    sliderContentModifier.directionAxis_->Set(static_cast<int>(Axis::VERTICAL));
    sliderContentModifier.blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderContentModifier.targetCenter_ = POINTF_START;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderContentModifier.targetCenter_ = POINTF_END;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);

    sliderContentModifier.blockCenterY_->Set(POINTF_END.GetY());
    sliderContentModifier.targetCenter_ = POINTF_CENTER;
    set = false;
    sliderContentModifier.StopCircleCenterAnimation();
    ASSERT_TRUE(set);
}

/**
 * @tc.name: SliderContentModifierTest020
 * @tc.desc: TEST gradient track background
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);

    Gradient gradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::WHITE));
    gradientColor1.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(0.5));
    gradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor(Color::BLUE));
    gradientColor3.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColor3);
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetTrackBackgroundColor(gradient);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);

    Gradient gradient2 = sliderContentModifier.trackBackgroundColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors2 = gradient2.GetColors();

    EXPECT_EQ(gradientColors.size(), gradientColors2.size());
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors2[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors2[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors2[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors2[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors2[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors2[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest021
 * @tc.desc: TEST default track background color
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->trackBgColor_ = Color::RED;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);

    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    sliderPattern->isVisibleArea_ = true;
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    ASSERT_NE(sliderPattern->sliderContentModifier_, nullptr);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Gradient themeGradient = SliderModelNG::CreateSolidGradient(sliderTheme->GetTrackBgColor());
    sliderPaintProperty->UpdateTrackBackgroundColor(themeGradient);
    sliderPattern->sliderContentModifier_->trackBackgroundColor_ =
        AceType::MakeRefPtr<AnimatablePropertyVectorColor>(GradientArithmetic(themeGradient));
    Gradient gradient = sliderPattern->sliderContentModifier_->trackBackgroundColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors = gradient.GetColors();

    Gradient defaultGradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::RED));
    gradientColor1.SetDimension(Dimension(0.0));
    defaultGradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(1.0));
    defaultGradient.AddColor(gradientColor2);
    std::vector<GradientColor> defaultGradientColors = defaultGradient.GetColors();

    EXPECT_EQ(defaultGradientColors.size(), gradientColors.size());
    EXPECT_EQ(defaultGradientColors[0].GetLinearColor(), gradientColors[0].GetLinearColor());
    EXPECT_EQ(defaultGradientColors[1].GetLinearColor(), gradientColors[1].GetLinearColor());
    EXPECT_EQ(defaultGradientColors[0].GetDimension(), gradientColors[0].GetDimension());
    EXPECT_EQ(defaultGradientColors[1].GetDimension(), gradientColors[1].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest022
 * @tc.desc: TEST slider_content_modifier DrawStep
 * direction = HORIZONTAL, blockType = DEFAULT, blockShape = CIRCLE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. Set BackgroundSize call DrawStep function and return.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_START);
    sliderContentModifier.SetShowSteps(true);
    sliderContentModifier.SetStepRatio(1.1);
    auto backStart = sliderContentModifier.backStart_->Get();
    auto backEnd = sliderContentModifier.backEnd_->Get();
    sliderContentModifier.DrawStep(context);
    EXPECT_TRUE(NearEqual(backStart.GetX(), backEnd.GetX()));
    EXPECT_TRUE(NearEqual(backStart.GetY(), backEnd.GetY()));
    EXPECT_TRUE(sliderContentModifier.GetStepPointVec().empty());
    /**
     * @tc.steps: step2. call DrawStep function and test stepSize.
     */
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END_DIFFX);
    sliderContentModifier.SetStepSize(SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    sliderContentModifier.SetTrackThickness(SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS_DIFF);
    sliderContentModifier.DrawStep(context);
    EXPECT_TRUE(NearEqual(backStart.GetX(), backEnd.GetX()));
    EXPECT_FALSE(sliderContentModifier.GetStepPointVec().empty());
    /**
     * @tc.steps: step3. call DrawStep function and test reverse_.
     */
    sliderContentModifier.SetBackgroundSize(POINTF_START_DIFFY, POINTF_END);
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.DrawStep(context);
    EXPECT_TRUE(NearEqual(backStart.GetY(), backEnd.GetY()));
    EXPECT_TRUE(GreatOrEqual(backEnd.GetX(), backStart.GetX()));
    EXPECT_TRUE(GreatOrEqual(backEnd.GetY(), backStart.GetX()));
    EXPECT_FALSE(sliderContentModifier.GetStepPointVec().empty());
}

/**
 * @tc.name: SliderContentModifierTest023
 * @tc.desc: TEST SliderContentModifier DrawDefaultBlock
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call DrawDefaultBlock function.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawDefaultBlock(context);
    /**
     * @tc.steps: step2. set BlockSize attribute and call DrawDefaultBlock function.
     */
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    float blockRadius = std::min(blockSize.Width(), blockSize.Height()) * HALF;
    float radius = blockRadius;
    auto borderWidth = sliderContentModifier.blockBorderWidth_->Get();
    sliderContentModifier.DrawDefaultBlock(context);
    EXPECT_FALSE(GreatOrEqual(borderWidth * HALF, radius));

    /**
     * @tc.steps: step2. set BlockBorderWidth attribute and call DrawDefaultBlock function.
     */
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL);
    borderWidth = sliderContentModifier.blockBorderWidth_->Get();
    sliderContentModifier.DrawDefaultBlock(context);
    EXPECT_TRUE(!NearEqual(borderWidth, .0f));
    EXPECT_TRUE(LessNotEqual(borderWidth * HALF, blockRadius));
}

/**
 * @tc.name: SliderContentModifierTest024
 * @tc.desc: TEST slider_content_modifier DrawBlockShape
 * direction = FREE, blockType = SHAPE, blockShape = ELLIPSE, sliderMode = OUTSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. don't set anything call DrawBlockShape function return.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawBlockShape(context);
    EXPECT_EQ(sliderContentModifier.shape_, nullptr);
}

/**
 * @tc.name: SliderContentModifierTest025
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeCircle
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.selectStart = SELECT_START;
    parameters.selectEnd = SELECT_END;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto circle = AccessibilityManager::DynamicCast<Circle>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(circle);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));

    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    auto scale = std::max(blockSize.Width() / sliderContentModifier.shapeWidth_->Get(),
        blockSize.Height() / sliderContentModifier.shapeHeight_->Get());
    EXPECT_FALSE(NearZero(scale));
}

/**
 * @tc.name: SliderContentModifierTest026
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeEllipse
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = Ellipse, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.selectStart = SELECT_START;
    parameters.selectEnd = SELECT_END;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute.
     */
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Ellipse>();
    basicShape->SetBasicShapeType(BasicShapeType::ELLIPSE);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto ellipse = AccessibilityManager::DynamicCast<Ellipse>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(ellipse);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeEllipse(context, ellipse);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapeEllipse(context, ellipse);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));

    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeEllipse(context, ellipse);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    auto scale = std::max(blockSize.Width() / sliderContentModifier.shapeWidth_->Get(),
        blockSize.Height() / sliderContentModifier.shapeHeight_->Get());
    EXPECT_FALSE(NearZero(scale));
}
/**
 * @tc.name: SliderContentModifierTest027
 * @tc.desc: TEST slider_content_modifier DrawBlockShapePath
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.selectStart = SELECT_START;
    parameters.selectEnd = SELECT_END;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Path>();
    basicShape->SetBasicShapeType(BasicShapeType::PATH);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto path = AccessibilityManager::DynamicCast<Path>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(path);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapePath(context, path);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapePath(context, path);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));
}
/**
 * @tc.name: SliderContentModifierTest028
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeRect
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.selectStart = SELECT_START;
    parameters.selectEnd = SELECT_END;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<ShapeRect>();
    basicShape->SetBasicShapeType(BasicShapeType::RECT);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    auto rect = AccessibilityManager::DynamicCast<ShapeRect>(sliderContentModifier.shape_);
    CHECK_NULL_VOID(rect);

    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeWidth_->Get()));

    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F_ZREO);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    EXPECT_FALSE(NearZero(sliderContentModifier.shapeHeight_->Get()));

    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    auto scale = std::max(blockSize.Width() / sliderContentModifier.shapeWidth_->Get(),
        blockSize.Height() / sliderContentModifier.shapeHeight_->Get());
    EXPECT_FALSE(NearZero(scale));
}

/**
 * @tc.name: SliderModelNgTest001
 * @tc.desc: TEST SliderModelNG::SetShowTips
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetShowTips(false, std::nullopt);
    sliderModelNG.SetBlockSize(BLOCK_SIZE_WIDTH, Dimension(0.0));

    auto frameNode = AceType::DynamicCast<FrameNode>(NG::ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderModelNG.SetMinResponsiveDistance(AceType::RawPtr(frameNode), SLIDER_NEGATIVE);
    Dimension testResult = sliderModelNG.GetThickness(AceType::RawPtr(frameNode));
    EXPECT_EQ(testResult, Dimension(0.0));
}

/**
 * @tc.name: SliderModelNgTest002
 * @tc.desc: TEST SliderModelNG::setModel
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderModelNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetThickness(AceType::RawPtr(frameNode), RADIUS);
    sliderModelNG.SetMinResponsiveDistance(AceType::RawPtr(frameNode), 50.0);
    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Dimension testResult = sliderModelNG.GetThickness(AceType::RawPtr(frameNode));
    EXPECT_EQ(testResult, RADIUS);
}

/**
 * @tc.name: SliderTipModifierTest002
 * @tc.desc: TEST slider_tip_modifier PaintText
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderTipModifierTest002, TestSize.Level1)
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
     * @tc.steps: step2. set sliderTipModifier's axis is HORIZONTAL and call PaintText function.
     * @tc.expected: text's offsetX is equal to half of vertex_'s width.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderTipModifier.axis_ = Axis::HORIZONTAL;
    sliderTipModifier.isMask_ = true;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    sliderTipModifier.SetParagraph(paragraph);
    sliderTipModifier.PaintTip(context);
    SizeF textSize = { 8, 8 };
    /**
     * @tc.steps: step2. set sliderTipModifier's axis is VERTICAL and call PaintText function.
     */
    sliderTipModifier.axis_ = Axis::VERTICAL;
    sliderTipModifier.isMask_ = true;
    sliderTipModifier.PaintText(context);
    sliderTipModifier.axis_ = Axis::HORIZONTAL;
    sliderTipModifier.PaintText(context);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetY(), sliderTipModifier.vertex_.GetY() + textSize.Width() * HALF);
}

/**
 * @tc.name: SliderTipModifierTest003
 * @tc.desc: TEST SliderTipModifier::SetTipFlag
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderTipModifierTest003, TestSize.Level1)
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
     * @tc.steps: step2. set sliderTipModifier's axis is HORIZONTAL and call PaintText function.
     * @tc.expected: text's offsetX is equal to half of vertex_'s width.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    sliderTipModifier.SetTipFlag(false);
    EXPECT_EQ(sliderTipModifier.tipFlag_, true);

    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(false);
    sliderTipModifier.SetTipFlag(true);
    EXPECT_EQ(sliderTipModifier.tipFlag_, true);
}

/**
 * @tc.name: SliderTipModifierTest004
 * @tc.desc: TEST SliderTipModifier::BuildParagraph
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderTipModifierTest00, TestSize.Level1)
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
     * @tc.steps: step2. set sliderTipModifier's axis is HORIZONTAL and call PaintText function.
     * @tc.expected: text's offsetX is equal to half of vertex_'s width.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetFontScale(1.8f);
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    sliderTipModifier.BuildParagraph();
    EXPECT_EQ(sliderTipModifier.textFontSize_, SUITABLEAGING_LEVEL_1_TEXT_FONT_SIZE);

    pipeline->SetFontScale(2.5f);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(false);
    sliderTipModifier.BuildParagraph();
    EXPECT_EQ(sliderTipModifier.textFontSize_, SUITABLEAGING_LEVEL_2_TEXT_FONT_SIZE);
}

/**
 * @tc.name: SliderTipModifierTest005
 * @tc.desc: TEST SliderTipModifier::UpdateBubbleSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderTipModifierTest005, TestSize.Level1)
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
     * @tc.steps: step2. set sliderTipModifier's axis is HORIZONTAL and call PaintText function.
     * @tc.expected: text's offsetX is equal to half of vertex_'s width.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetFontScale(1.8f);
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    sliderTipModifier.UpdateBubbleSize();
    float bubbleSizeHeight = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx());
    float bubbleSizeWidth = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(bubbleSizeHeight, bubbleSizeWidth));
    sliderTipModifier.axis_ = Axis::VERTICAL;
    sliderTipModifier.UpdateBubbleSize();
    bubbleSizeHeight = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH.ConvertToPx());
    bubbleSizeWidth = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT.ConvertToPx());
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(bubbleSizeHeight, bubbleSizeWidth));

    pipeline->SetFontScale(2.5f);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(false);
    sliderTipModifier.UpdateBubbleSize();
    bubbleSizeHeight = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx());
    bubbleSizeWidth = static_cast<float>(BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(bubbleSizeHeight, bubbleSizeWidth));
    sliderTipModifier.axis_ = Axis::HORIZONTAL;
    sliderTipModifier.UpdateBubbleSize();
    bubbleSizeHeight = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH.ConvertToPx());
    bubbleSizeWidth = static_cast<float>(BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT.ConvertToPx());
    EXPECT_EQ(sliderTipModifier.bubbleSize_, SizeF(bubbleSizeHeight, bubbleSizeWidth));
}

/**
 * @tc.name: SliderContentModifierTest029
 * @tc.desc: TEST SliderContentModifier DrawDefaultBlock
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->focusedScaleValue_ = 1.5;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call DrawDefaultBlock function.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawDefaultBlock(context);
    /**
     * @tc.steps: step2. set BlockSize attribute and call DrawDefaultBlock function.
     */
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    float blockRadius = std::min(blockSize.Width(), blockSize.Height()) * HALF;
    float radius = blockRadius;
    sliderContentModifier.isEnlarge_ = true;
    sliderContentModifier.DrawDefaultBlock(context);
    EXPECT_TRUE(GreatOrEqual(radius * SCALE_VALUE, radius * sliderTheme->focusedScaleValue_));
}

/**
 * @tc.name: SliderContentModifierTest030
 * @tc.desc: TEST SliderContentModifier DrawDefaultBlock
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->focusedScaleValue_ = 1.5;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call DrawDefaultBlock function.
     */
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.DrawDefaultBlock(context);
    /**
     * @tc.steps: step2. set BlockSize attribute and call DrawDefaultBlock function.
     */
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    auto blockSize = sliderContentModifier.blockSize_->Get();
    float diameter = std::min(blockSize.Width(), blockSize.Height());
    auto penRadius = (diameter + parameters.hotCircleShadowWidth) * HALF;
    sliderContentModifier.isEnlarge_ = true;
    sliderContentModifier.DrawHoverOrPress(context);
    EXPECT_TRUE(GreatOrEqual(penRadius * SCALE_VALUE, penRadius * sliderTheme->focusedScaleValue_));
}

/**
 * @tc.name: SliderContentModifierTest031
 * @tc.desc: TEST SliderContentModifier SetBoardColor
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest031, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call SetBoardColor function.
     */
    sliderContentModifier.SetIsHovered(false);
    sliderContentModifier.SetBoardColor();
    EXPECT_FALSE(sliderContentModifier.mouseHoverFlag_);
}

/**
 * @tc.name: SliderContentModifierTest032
 * @tc.desc: TEST slider_content_modifier onDraw
 * Pressed = false, Hovered = false, Focused = true
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->focusedScaleValue_ = 1.5;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    SetSliderContentModifier(sliderContentModifier);
    // set Axis HORIZONTAL
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    // set BlockStyleType DEFAULT
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    // set BasicShapeType CIRCLE
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    // set SliderMode OUTSET
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    // set BlockBorderColor TEST_COLOR
    sliderContentModifier.SetBlockBorderColor(TEST_COLOR);
    // set BorderWidth SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
    // set IsPressed false
    sliderContentModifier.SetIsPressed(false);
    // set IsHovered false
    sliderContentModifier.SetIsHovered(false);
    // set IsFocused true
    sliderContentModifier.SetIsFocused(true);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.onDraw(context);
    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_EQ(sliderContentModifier.isEnlarge_, true);
    EXPECT_EQ(sliderContentModifier.isPressed_->Get(), false);
    EXPECT_EQ(sliderContentModifier.isHovered_->Get(), false);
    EXPECT_EQ(sliderContentModifier.isFocused_->Get(), true);
    EXPECT_EQ(sliderContentModifier.isShowStep_->Get(), true);
    EXPECT_EQ(sliderContentModifier.stepSize_->Get(), SLIDER_CONTENT_MODIFIER_STEP_SIZE);
    EXPECT_EQ(sliderContentModifier.stepColor_->Get(), LinearColor(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.stepRatio_->Get(), SLIDER_CONTENT_MODIFIER_STEP_RATIO);
    EXPECT_EQ(sliderContentModifier.directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderContentModifier.selectGradientColor_->Get().GetGradient(),
        SliderModelNG::CreateSolidGradient(TEST_COLOR));
    EXPECT_EQ(sliderContentModifier.blockType_->Get(), static_cast<int>(SliderModelNG::BlockStyleType::DEFAULT));
    EXPECT_EQ(sliderContentModifier.shape_, basicShape);
    EXPECT_EQ(sliderContentModifier.sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier.blockBorderWidth_->Get(), SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderContentModifierTest033
 * @tc.desc: TEST slider_content_modifier AddStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.SetHasPrefix(true);
    sliderContentModifier.SetHasSuffix(true);
    sliderContentModifier.reverse_ = false;
    sliderContentModifier.SetSliderMode(SliderModel::SliderMode::NONE);
    sliderContentModifier.SetStepRatio(.0f);

    Testing::MockCanvas canvas;
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.AddStepPoint(0, 0, 100, 0, context.canvas);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_TRUE(sliderContentModifier.GetStepPointVec().empty());
}

/**
 * @tc.name: SliderContentModifierTest034
 * @tc.desc: TEST SliderContentModifier AddStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.SetHasPrefix(false);
    sliderContentModifier.SetHasSuffix(false);
    sliderContentModifier.reverse_ = false;
    sliderContentModifier.SetSliderMode(SliderModel::SliderMode::INSET);
    sliderContentModifier.SetStepRatio(0.5f);

    Testing::MockCanvas canvas;
    sliderContentModifier.AddStepPoint(0, 0, 100, 0, canvas);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_EQ(sliderContentModifier.GetStepPointVec().size(), 3);
}

/**
 * @tc.name: SliderContentModifierTest035
 * @tc.desc: TEST SliderContentModifier AddStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest035, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.SetHasPrefix(true);
    sliderContentModifier.SetHasSuffix(true);
    sliderContentModifier.SetStepRatio(0.3f);
    sliderContentModifier.AddStepPoint(0, 0, 100, 0, canvas);
    auto& points = sliderContentModifier.GetStepPointVec();

    /**
     * @tc.steps: step3. Check the param value.
     */
    ASSERT_GT(points.size(), 3);
    EXPECT_EQ(points.back(), PointF(0, 0));
}

/**
 * @tc.name: SliderContentModifierTest036
 * @tc.desc: TEST SliderContentModifier AddStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.SetStepRatio(0.25f);
    sliderContentModifier.reverse_ = false;
    sliderContentModifier.AddStepPoint(0, 0, 100, 0, canvas);
    auto& points = sliderContentModifier.GetStepPointVec();

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_EQ(points.back(), PointF(100, 0));
}

/**
 * @tc.name: SliderContentModifierTest037
 * @tc.desc: TEST SliderContentModifier DrawStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;
    
    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.DrawStepPoint(10.0f, 20.0f, 2, canvas, 5);

    /**
     * @tc.steps: step3. Check the param value.
     */
    ASSERT_EQ(sliderContentModifier.GetStepPointVec().size(), 1);
    EXPECT_EQ(sliderContentModifier.GetStepPointVec()[0], PointF(10.0f, 20.0f));
}

/**
 * @tc.name: SliderContentModifierTest038
 * @tc.desc: TEST SliderContentModifier DrawStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;
    sliderContentModifier.SetSliderMode(SliderModel::SliderMode::NONE);

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.DrawStepPoint(10.0f, 20.0f, 1, canvas, 5);
    sliderContentModifier.DrawStepPoint(30.0f, 40.0f, 3, canvas, 5);

    /**
     * @tc.steps: step3. Check the param value.
     */
    ASSERT_EQ(sliderContentModifier.GetStepPointVec().size(), 2);
}

/**
 * @tc.name: SliderContentModifierTest039
 * @tc.desc: TEST SliderContentModifier DrawStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.SetSliderMode(SliderModel::SliderMode::INSET);

    sliderContentModifier.DrawStepPoint(0.0f, 0.0f, 0, canvas, 5);
    sliderContentModifier.DrawStepPoint(100.0f, 0.0f, 4, canvas, 5);

    /**
     * @tc.steps: step3. Check the param value.
     */
    ASSERT_EQ(sliderContentModifier.GetStepPointVec().size(), 2);
}

/**
 * @tc.name: SliderContentModifierTest040
 * @tc.desc: TEST SliderContentModifier DrawStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Mock track background default value
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.SetHasPrefix(false);
    sliderContentModifier.SetHasSuffix(false);
    sliderContentModifier.SetSliderMode(SliderModel::SliderMode::NONE);
    sliderContentModifier.DrawStepPoint(10.0f, 20.0f, 1, canvas, 5);

    /**
     * @tc.steps: step3. Check the param value.
     */
    ASSERT_EQ(sliderContentModifier.GetStepPointVec().size(), 1);
}

/**
 * @tc.name: SliderContentModifierTest041
 * @tc.desc: TEST SliderContentModifier DrawStepPoint
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTestNg, SliderContentModifierTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderContentModifier.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr, nullptr);
    Testing::MockCanvas canvas;

    /**
     * @tc.steps: step2. create frameNode and sliderContentModifier.
     */
    sliderContentModifier.SetHasPrefix(true);
    sliderContentModifier.SetHasSuffix(true);
    sliderContentModifier.SetSliderMode(SliderModel::SliderMode::NONE);
    sliderContentModifier.DrawStepPoint(10.0f, 20.0f, 1, canvas, 5);

    /**
     * @tc.steps: step3. Check the param value.
     */
    ASSERT_EQ(sliderContentModifier.GetStepPointVec().size(), 1);
}
} // namespace OHOS::Ace::NG
