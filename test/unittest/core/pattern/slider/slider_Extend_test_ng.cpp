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
#include "core/components_ng/pattern/slider/slider_tip_paint_method.h"
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
constexpr float MIN_RANGE = MIN + 40.0f;
constexpr float MAX_RANGE = MAX - 30.0f;
constexpr float MIDDLE_OF_RANGE = (MIN_RANGE + MAX_RANGE) / 2;
constexpr float NAN_VALUE = std::numeric_limits<float>::quiet_NaN();
constexpr float INFINITY_VALUE = std::numeric_limits<float>::infinity();
const Color TEST_COLOR = Color::BLUE;
constexpr float MIN_LABEL = 10.0f;
constexpr float MAX_LABEL = 20.0f;
constexpr Dimension WIDTH = 50.0_vp;
constexpr Dimension HEIGHT = 50.0_vp;
constexpr Dimension HUGE_WIDTH = 500000000.0_vp;
constexpr Dimension HUGE_HEIGHT = 500000000.0_vp;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float FRAME_WIDTH = 10.0f;
constexpr float FRAME_HEIGHT = 20.0f;
constexpr Dimension SLIDER_NONE_TRACK_THICKNRESS = Dimension(5.0);
constexpr Dimension SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_TRACK_BORDER_RADIUS = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS = Dimension(20.1);
constexpr Dimension SLIDER_MODEL_NG_STEP_SIZE = Dimension(10.0);
constexpr float SLIDER_WIDTH = 10.0f;
constexpr float SLIDER_HEIGHT = 20.0f;
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
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr Dimension ARROW_WIDTH = 16.0_vp;
constexpr Dimension CIRCULAR_HORIZON_OFFSET = 13.86_vp;
constexpr Dimension TEXT_MAX = 36.0_vp;
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_WIDTH = 92.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_1_HEIGHT = 52.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_1_HEIGHT = 60.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_WIDTH = 96.0_vp;
constexpr Dimension BUBBLE_VERTICAL_SUITABLEAGING_LEVEL_2_HEIGHT = 56.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_WIDTH = 48.0_vp;
constexpr Dimension BUBBLE_HORIZONTAL_SUITABLEAGING_LEVEL_2_HEIGHT = 64.0_vp;
constexpr float SLIDER_CONTENT_WIDTH_1 = 130.0f;
constexpr float SLIDER_CONTENT_HEIGHT_1 = 60.0f;
constexpr float SLIDER_CONTENT_WIDTH_2 = 40.0f;
constexpr float SLIDER_CONTENT_HEIGHT_2 = 100.0f;
} // namespace
class SliderExTestNg : public testing::Test {
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

void SliderExTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderExTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderExTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderExTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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

void SliderExTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderExTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderExTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderModelNgTest001
 * @tc.desc: TEST slider_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetBlockBorderColor(TEST_COLOR);
    sliderModelNG.SetBlockBorderWidth(SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    sliderModelNG.SetStepColor(TEST_COLOR);
    sliderModelNG.SetTrackBorderRadius(SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    sliderModelNG.SetSelectedBorderRadius(SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
    sliderModelNG.SetBlockSize(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
    sliderModelNG.SetBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderModelNG.SetBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE, SLIDER_TEST_BUNDLE_NAME, SLIDER_TEST_MODULE_NAME);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderModelNG.SetBlockShape(basicShape);
    sliderModelNG.SetStepSize(SLIDER_MODEL_NG_STEP_SIZE);
    sliderModelNG.SetShowTips(false, "content");

    std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
    sliderModelNG.SetOnChange(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(NG::ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get the properties of all settings.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderWidth(), SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    EXPECT_EQ(sliderPaintProperty->GetStepColor(), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBorderRadius(), SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderPaintProperty->GetSelectedBorderRadius(), SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
    EXPECT_EQ(sliderPaintProperty->GetBlockType(), SliderModel::BlockStyleType::IMAGE);
    EXPECT_EQ(sliderPaintProperty->GetBlockImage(), SLIDER_MODEL_NG_BLOCK_IMAGE);
    EXPECT_EQ(sliderPaintProperty->GetBlockShape(), basicShape);

    /**
     * @tc.steps: step3. reset the properties.
     */
    sliderModelNG.ResetBlockBorderColor();
    sliderModelNG.ResetBlockBorderWidth();
    sliderModelNG.ResetTrackBorderRadius();
    sliderModelNG.ResetStepColor();
    sliderModelNG.ResetStepSize();
    sliderModelNG.ResetBlockType();
    sliderModelNG.ResetBlockImage();
    sliderModelNG.ResetBlockShape();
    sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step4. check whether the properties is correct.
     * @tc.expected: step4. check whether the properties is correct.
     */
    EXPECT_TRUE(sliderPaintProperty->GetBlockBorderColor().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetBlockBorderWidth().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetTrackBorderRadius().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetStepColor().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetStepSize().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetBlockType().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetBlockImage().has_value());
    EXPECT_TRUE(sliderPaintProperty->GetBlockShape().has_value());
}

/**
 * @tc.name: SliderModelNgTest002
 * @tc.desc: TEST slider_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderModelNgTest002, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create slider.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetBlockSize with invalid parameters.
     * @tc.expected: step2. check the BlockSize property not be set.
     */
    sliderModelNG.SetBlockSize(Dimension(0.0), Dimension(0.0));
    EXPECT_FALSE(sliderLayoutProperty->GetBlockSize().has_value());

    /**
     * @tc.steps: step3. call SetBlockSize with invalid parameters while BlockSize property has been set.
     * @tc.expected: step3. check the BlockSize property has reset.
     */
    sliderModelNG.SetBlockSize(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
    EXPECT_TRUE(sliderLayoutProperty->GetBlockSize().has_value());
    sliderModelNG.SetBlockSize(Dimension(0.0), Dimension(0.0));
    EXPECT_FALSE(sliderLayoutProperty->GetBlockSize().has_value());
}

/**
 * @tc.name: SliderTipModifierTest001
 * @tc.desc: TEST slider_tip_modifier onDraw
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderTipModifierTest001, TestSize.Level1)
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
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); },
            [sliderPattern](){return sliderPattern->OnFinishEventTipSize();});
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call onDraw function.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
    sliderTipModifier.sizeScale_->Set(1.0);
    auto offset = static_cast<float>(BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx());
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), false);
    sliderTipModifier.SetSliderGlobalOffset(OffsetF());
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetY(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), false);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, BLOCK_SIZE_F_ZREO);

    sliderPattern->direction_ = Axis::VERTICAL;
    sliderTipModifier.SetDirection(Axis::VERTICAL);
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), offset);
    EXPECT_EQ(sliderTipModifier.isMask_, true);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), false);
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.onDraw(context);
    EXPECT_EQ(sliderTipModifier.vertex_.GetX(), 0 - offset);
    EXPECT_EQ(sliderTipModifier.isMask_, false);
    EXPECT_EQ(sliderTipModifier.UpdateOverlayRect(SizeF()), false);
    EXPECT_EQ(sliderTipModifier.bubbleSize_, BLOCK_SIZE_F_ZREO);
}

/**
 * @tc.name: SliderPaintPropertyTest001
 * @tc.desc: Test slider_paint_property.h Update function
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPaintPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create sliderPaintProperty.
     */
    RefPtr<SliderPaintProperty> sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. call ToJsonValue.
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    sliderPaintProperty->UpdateTrackBorderRadius(SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    sliderPaintProperty->UpdateSelectedBorderRadius(SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
    sliderPaintProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    sliderPaintProperty->UpdateBlockBorderColor(TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderColorValue(Color::TRANSPARENT), TEST_COLOR);
    sliderPaintProperty->UpdateBlockBorderWidth(SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    EXPECT_EQ(sliderPaintProperty->GetBlockBorderWidthValue(Dimension()), SLIDER_MODEL_NG_BLOCK_BORDER_WIDTH);
    sliderPaintProperty->UpdateStepColor(TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetStepColorValue(Color::TRANSPARENT), TEST_COLOR);
    EXPECT_EQ(sliderPaintProperty->GetTrackBorderRadiusValue(Dimension()), SLIDER_MODEL_NG_TRACK_BORDER_RADIUS);
    EXPECT_EQ(sliderPaintProperty->GetSelectedBorderRadiusValue(Dimension()), SLIDER_MODEL_NG_SELECTED_BORDER_RADIUS);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    EXPECT_EQ(sliderPaintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT),
        SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    std::string defaultImage = "Default";
    EXPECT_EQ(sliderPaintProperty->GetBlockImageValue(defaultImage), SLIDER_MODEL_NG_BLOCK_IMAGE);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::INSET);
    sliderPaintProperty->UpdateBlockShape(basicShape);
    EXPECT_EQ(sliderPaintProperty->GetBlockShapeValue(AceType::MakeRefPtr<BasicShape>()), basicShape);
    sliderPaintProperty->UpdateStepSize(SLIDER_MODEL_NG_STEP_SIZE);
    EXPECT_EQ(sliderPaintProperty->GetStepSizeValue(Dimension()), SLIDER_MODEL_NG_STEP_SIZE);
}

/**
 * @tc.name: SliderLayoutPropertyTest001
 * @tc.desc: Test slider_layout_property.h ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderLayoutPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create sliderPaintProperty.
     */
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    SizeT<Dimension> blockSize;
    sliderLayoutProperty->UpdateBlockSize(blockSize);
    EXPECT_EQ(sliderLayoutProperty->GetBlockSizeValue(SizeF()), SizeF());

    /**
     * @tc.steps: step3. call ToJsonValue when SliderMode = OUTSET/INSET
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    sliderLayoutProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutProperty->ResetBlockSize();
    sliderLayoutProperty->ToJsonValue(json, filter);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: SliderLayoutAlgorithmTest001
 * @tc.desc: Test slider_layout_algorithm Measure and Layout(Reverse=false)
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(childLayoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step2. call Measure and Layout function.
     */
    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    // set SliderMode INSET
    auto host = layoutWrapper->GetHostNode();
    auto hSliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    hSliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));

    auto constraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto width = sliderLayoutAlgorithm.blockSize_.Width();
    auto height = sliderLayoutAlgorithm.blockSize_.Height();
    EXPECT_EQ(constraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(width, height)), true);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}

/**
 * @tc.name: SliderLayoutAlgorithmTest002
 * @tc.desc: Test slider_layout_algorithm.cpp  Measure and Layout(Reverse=true)
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. call Measure and Layout function.
     */
    // set reverse true
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateReverse(true);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(childLayoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());
    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    // set Axis VERTICAL
    auto host = layoutWrapper->GetHostNode();
    auto hSliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    hSliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    // pattern->GetAnimatableBlockCenter() != OffsetF()
    auto pattern = AceType::DynamicCast<SliderPattern>(host->GetPattern());
    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    pattern->sliderContentModifier_->blockCenterX_->Set(POINTF_CENTER.GetX());
    pattern->sliderContentModifier_->blockCenterY_->Set(POINTF_CENTER.GetY());
    sliderLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    auto constraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto width = sliderLayoutAlgorithm.blockSize_.Width();
    auto height = sliderLayoutAlgorithm.blockSize_.Height();
    EXPECT_EQ(constraint.UpdateSelfMarginSizeWithCheck(OptionalSizeF(width, height)), true);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    sliderLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(CONTAINER_SIZE));
}

/**
 * @tc.name: SliderLayoutAlgorithmTest003
 * @tc.desc: Test slider_layout_algorithm MeasureContent
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderLayoutAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. call MeasureContent function.
     */
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateReverse(true);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(childLayoutWrapper);
    WeakPtr<FrameNode> hostNode = AceType::WeakClaim(AceType::RawPtr(frameNode));
    layoutWrapper->Update(hostNode, geometryNode, frameNode->GetLayoutProperty());

    // set layoutConstraintSizevalid
    LayoutConstraintF layoutConstraintSizevalid;
    layoutConstraintSizevalid.maxSize = MAX_SIZE;
    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(HUGE_WIDTH.ConvertToPx(), HUGE_HEIGHT.ConvertToPx()));
    // set theme
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    // test MeasureContent function
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    auto size = sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, Referenced::RawPtr(layoutWrapper));
    // set Axis VERTICAL(call MeasureContent function)
    auto host = layoutWrapper->GetHostNode();
    auto hSliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    hSliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    size = sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, Referenced::RawPtr(layoutWrapper));

    layoutConstraintSizevalid.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    hSliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    size = sliderLayoutAlgorithm.MeasureContent(layoutConstraintSizevalid, Referenced::RawPtr(layoutWrapper));
    auto maxWidth = layoutConstraintSizevalid.maxSize.Width();
    auto selfWidth = layoutConstraintSizevalid.selfIdealSize.Width().value_or(maxWidth);
    EXPECT_EQ(size->Width(), selfWidth);
}

/**
 * @tc.name: SliderLayoutAlgorithmTest004
 * @tc.desc: Test slider_layout_algorithm Layout without child node
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderLayoutAlgorithmTest004, TestSize.Level1)
{
    auto sliderLayoutProperty = AceType::MakeRefPtr<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    SliderLayoutAlgorithm sliderLayoutAlgorithm;
    // No child node would be layout
    sliderLayoutAlgorithm.Layout(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetContentOffset(), OffsetF());
    EXPECT_EQ(layoutWrapper->GetTotalChildCount(), 0);
}

/**
 * @tc.name: SliderPaintMethodTest001
 * @tc.desc: Test slider_paint_method UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderPaintMethod.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(5.0, 10.0, 10.0, 20.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.trackThickness = static_cast<float>(SLIDER_NONE_TRACK_THICKNRESS.ConvertToPx());
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters, TextDirection::AUTO);
    /**
     * @tc.steps: step2. create paintWrapper.
     */
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(frameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty())
        ->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    /**
     * @tc.steps: step3. call UpdateContentModifier function.
     */
    // set theme
    MockPipelineContext::SetUp();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    Color color = Color::TRANSPARENT;
    sliderTheme->blockColor_ = color;
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderPaintMethod.sliderContentModifier_->blockBorderColor_->Set(LinearColor(sliderTheme->GetBlockColor()));

    // call UpdateContentModifier function
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(
        sliderPaintMethod.sliderContentModifier_->sliderMode_, static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->blockBorderColor_->Get(), LinearColor(Color::TRANSPARENT));
    EXPECT_EQ(
        sliderPaintMethod.sliderContentModifier_->blockType_, static_cast<int>(SliderModelNG::BlockStyleType::IMAGE));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->directionAxis_, static_cast<int>(Axis::HORIZONTAL));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->selectedBorderRadius_->Get(),
        static_cast<float>(SLIDER_NONE_TRACK_THICKNRESS.ConvertToPx()) * HALF);

    //change sliderMode
    sliderPaintMethod.sliderContentModifier_->sliderMode_->Set(static_cast<int>(SliderModelNG::SliderMode::NONE));
    sliderPaintMethod.sliderContentModifier_->selectedBorderRadius_->Set(0.0f);
    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty())
        ->UpdateSliderMode(SliderModelNG::SliderMode::NONE);
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->sliderMode_->Get(),
        static_cast<int>(SliderModelNG::SliderMode::NONE));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->selectedBorderRadius_->Get(), 0);
}

/**
 * @tc.name: SliderPaintMethodTest002
 * @tc.desc: Test slider_paint_method UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderPaintMethod.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(5.0, 10.0, 10.0, 20.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters, TextDirection::AUTO);
    /**
     * @tc.steps: step2. create paintWrapper.
     */
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(frameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    /**
     * @tc.steps: step3. call UpdateOverlayModifier function.
     */
    // set theme
    MockPipelineContext::SetUp();
    auto pipeline = PipelineBase::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    Testing::MockCanvas canvas;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    MockParagraphFunction(paragraph, canvas);

    // call UpdateOverlayModifier function
    auto pattern = frameNode->GetPattern<SliderPattern>();
    SliderTipPaintMethod sliderTipPaintMethod(pattern, tipParameters, sliderTipModifier, parameters);
    sliderTipPaintMethod.UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderTipModifier->axis_, Axis::VERTICAL);

    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->paintProperty_)->UpdateDirection(Axis::HORIZONTAL);
    sliderTipPaintMethod.UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderTipModifier->axis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SliderPaintMethodTest003
 * @tc.desc: Test slider_paint_method UpdateContentDirtyRect
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPaintMethodTest003, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    /**
     * @tc.steps: step1. create paintWrapper and sliderContentModifier.
     */
    auto sliderContentModifier =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    SliderPaintMethod sliderPaintMethod(sliderContentModifier, SliderContentModifier::Parameters(), 1.0f, 1.0f, nullptr,
        SliderPaintMethod::TipParameters(), TextDirection::AUTO);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto paintWrapper1 = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    sliderPaintProperty->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    sliderPaintProperty->UpdateDirection(Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. call UpdateContentModifier function.
     */
    sliderContentModifier->sliderMode_->Set(static_cast<int>(SliderModelNG::SliderMode::INSET));
    RectF rectValue;
    rectValue.SetSize(SizeF(SLIDER_CONTENT_WIDTH_1, SLIDER_CONTENT_HEIGHT_1));
    sliderPaintMethod.sliderContentModifier_->SetBoundsRect(rectValue);
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper1));
    EXPECT_EQ(sliderContentModifier->sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier->directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    auto rect1 = sliderContentModifier->GetBoundsRect();
    EXPECT_EQ(rect1->Width(), 130.0f);
    EXPECT_EQ(rect1->Height(), 60.0f);
    sliderPaintProperty->UpdateSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    auto paintWrapper2 = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    sliderContentModifier->sliderMode_ =
        AceType::MakeRefPtr<PropertyInt>(static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    sliderContentModifier->SetDirection(Axis::VERTICAL);
    RectF rectValue2;
    rectValue2.SetSize(SizeF(SLIDER_CONTENT_WIDTH_2, SLIDER_CONTENT_HEIGHT_2));
    sliderPaintMethod.sliderContentModifier_->SetBoundsRect(rectValue2);
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper2));
    EXPECT_EQ(sliderContentModifier->sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier->directionAxis_->Get(), static_cast<int>(Axis::VERTICAL));
    auto rect2 = sliderContentModifier->GetBoundsRect();
    EXPECT_EQ(rect2->Width(), 40.0f);
    EXPECT_EQ(rect2->Height(), 100.0f);
}

/**
 * @tc.name: SliderAccessibilityPropertyTest001
 * @tc.desc: Test the HasRange and RangeInfo properties of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderAccessibilityPropertyTest001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_TRUE(sliderAccessibilityProperty->HasRange());
    EXPECT_EQ(sliderAccessibilityProperty->GetAccessibilityValue().current, VALUE);
    EXPECT_EQ(sliderAccessibilityProperty->GetAccessibilityValue().max, MAX);
    EXPECT_EQ(sliderAccessibilityProperty->GetAccessibilityValue().min, MIN);
}

/**
 * @tc.name: SliderAccessibilityPropertyTest002
 * @tc.desc: Test the Text property of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderAccessibilityPropertyTest002, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_EQ(sliderAccessibilityProperty->GetText(), std::to_string(VALUE));
}

/**
 * @tc.name: SliderAccessibilityPropertyTest003
 * @tc.desc: Test the IsScrollable and SupportAction properties of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderAccessibilityPropertyTest003, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_TRUE(sliderAccessibilityProperty->IsScrollable());

    sliderAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = sliderAccessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: SliderPatternChangeEventTestNg001
 * @tc.desc: Test the Text property of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPatternChangeEventTestNg001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    std::function<void(float)> eventOnChange = [](float floatValue) { EXPECT_EQ(floatValue, 1.0); };
    sliderModelNG.SetOnChangeEvent(std::move(eventOnChange));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderEventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    ASSERT_NE(sliderEventHub, nullptr);
    ASSERT_NE(sliderEventHub->onChangeEvent_, nullptr);
    sliderEventHub->FireChangeEvent(1.0, 1);
    sliderEventHub->SetOnChangeEvent(nullptr);
    ASSERT_EQ(sliderEventHub->onChangeEvent_, nullptr);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Slider Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider and initialize related properties.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);

    /**
     * @tc.steps: step2. Get slider frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->showTips_ = false;
    sliderPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get slider accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto sliderAccessibilityProperty = frameNode->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When slider is not showTips, call the callback function in sliderAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When slider is showTips, call the callback function in sliderAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    sliderPattern->showTips_ = true;
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(sliderAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: SliderPatternDistributed001
 * @tc.desc: Test the distributed capability of Slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPatternDistributed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = sliderPattern->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step2. Get pattern and set value.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    sliderPaintProperty->UpdateValue(40);
    std::string ret = sliderPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"value":40})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"value":40})";
    sliderPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(sliderPaintProperty->GetValue().value_or(0), 40);
    restoreInfo_ = R"({"value":2})";
    sliderPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(sliderPaintProperty->GetValue().value_or(0), 2);
    restoreInfo_ = "invalid_json_string";
    sliderPattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(sliderPaintProperty->GetValue().value_or(0), 2);
}

/**
 * @tc.name: SliderPatternOnIsFocusActiveUpdate001
 * @tc.desc: Test Is not Focus when slider active update
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPatternOnIsFocusActiveUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = sliderPattern->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);

    /**
     * @tc.steps: step2. slider is focus,showtip is true.expect bubbleFlag_ is true.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    sliderPaintProperty->UpdateShowTips(true);
    sliderPattern->OnModifyDone();
    sliderPattern->focusFlag_ = true;
    sliderPattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderTipModifierPaintText001
 * @tc.desc: Test offset of text on slider
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderTipModifierPaintText001, TestSize.Level1)
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
    auto arrowSizeWidth = static_cast<float>(ARROW_WIDTH.ConvertToPx());
    auto arrowSizeHeight = static_cast<float>(ARROW_HEIGHT.ConvertToPx());
    auto circularOffset = static_cast<float>(CIRCULAR_HORIZON_OFFSET.ConvertToPx());
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
    SizeF textSize = { 0, 0 };
    textSize =
        SizeF(std::min(sliderTipModifier.paragraph_->GetLongestLine(), static_cast<float>(TEXT_MAX.ConvertToPx())),
            sliderTipModifier.paragraph_->GetHeight());
    EXPECT_EQ(sliderTipModifier.textOffset_.GetX(), sliderTipModifier.vertex_.GetX() - textSize.Width() * HALF);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetY(),
        sliderTipModifier.vertex_.GetY() -
            (sliderTipModifier.bubbleSize_.Height() + textSize.Height() + arrowSizeHeight) * HALF);
    /**
     * @tc.steps: step2. set sliderTipModifier's axis is VERTICAL and call PaintText function.
     */
    sliderTipModifier.axis_ = Axis::VERTICAL;
    sliderTipModifier.PaintText(context);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetY(), sliderTipModifier.vertex_.GetY() - textSize.Height() * HALF);
    EXPECT_EQ(sliderTipModifier.textOffset_.GetX(),
        sliderTipModifier.vertex_.GetX() - (sliderTipModifier.bubbleSize_.Width() + textSize.Width() + arrowSizeHeight +
                                               circularOffset - arrowSizeWidth) *
                                               HALF);
}

/**
 * @tc.name: SliderModelNgTest003
 * @tc.desc: TEST slider_model_ng SetShowTips
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderModelNgTest003, TestSize.Level2)
{
    /**
     * @tc.steps: step1. create slider.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto rawPtr = AceType::RawPtr(frameNode);
    rawPtr->IncRefCount();
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetBlockSize with invalid parameters.
     * @tc.expected: step2. check the BlockSize property not be set.
     */
    sliderModelNG.SetBlockSize(rawPtr, Dimension(0.0), Dimension(0.0));
    EXPECT_FALSE(sliderLayoutProperty->GetBlockSize().has_value());

    /**
     * @tc.steps: step3. call SetBlockSize with invalid parameters while BlockSize property has been set.
     * @tc.expected: step3. check the BlockSize property has reset.
     */
    sliderModelNG.SetBlockSize(rawPtr, BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);

    sliderModelNG.SetShowTips(rawPtr, false, "content");

    sliderModelNG.SetThickness(rawPtr, Dimension(-1));
    sliderModelNG.SetThickness(rawPtr, Dimension(1));
    EXPECT_TRUE(sliderLayoutProperty->GetBlockSize().has_value());
}

/**
 * @tc.name: SliderValidRangeTest001
 * @tc.desc: check value of slider valid range by default
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest001, TestSize.Level1)
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
     * @tc.steps: step2. get SliderValidRange by default.
     * @tc.expected: step2. check whether the properties is correct.
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
    EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
    EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);
    EXPECT_EQ(sliderPaintProperty->GetValue(), VALUE);
    EXPECT_FALSE(sliderPaintProperty->GetValidSlideRange().has_value());
}

/**
 * @tc.name: SliderValidRangeTest002
 * @tc.desc: Update Slider value by Slider valid range
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest002, TestSize.Level1)
{
    struct TestData {
        float value { 0.0f };
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    std::vector<std::pair<TestData, TestData>> testSliderValidRangeData {
        std::make_pair<TestData, TestData>(
            { MIN, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN + 10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN_RANGE - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX - 10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX_RANGE + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIN_RANGE + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE + 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MAX_RANGE - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE - 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, MAX_RANGE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, MAX) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(NAN_VALUE, MAX + 1.0f) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MAX, MIN) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MAX_RANGE, MIN_RANGE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN - 1.0f, MAX) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX + 1.0f) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(INFINITY_VALUE, INFINITY_VALUE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, INFINITY_VALUE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(INFINITY_VALUE, MAX_RANGE) },
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, MAX_RANGE) }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
        std::make_pair<TestData, TestData>(
            { MIDDLE_OF_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN - 1.0f, NAN_VALUE) },
            { MIDDLE_OF_RANGE, nullptr }),
    };

    for (auto testData : testSliderValidRangeData) {
        /**
         * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
         */
        SliderModelNG sliderModelNG;
        auto setValue = testData.first.value;
        auto checkValue = testData.second.value;
        auto setRangeValue = testData.first.range;
        auto checkRangeValue = testData.second.range;
        sliderModelNG.Create(setValue, STEP, MIN, MAX);
        if (setRangeValue.get()) {
            sliderModelNG.SetValidSlideRange(setRangeValue.get()->GetFromValue(), setRangeValue.get()->GetToValue());
        }
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. get SliderValidRange.
         * @tc.expected: step2. check whether the properties is correct.
         */
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), STEP);

        if (checkRangeValue.get()) {
            EXPECT_TRUE(sliderPaintProperty->GetValidSlideRange().has_value());
            auto rangeValue = sliderPaintProperty->GetValidSlideRange().value();
            EXPECT_EQ(rangeValue->GetFromValue(), checkRangeValue.get()->GetFromValue());
            EXPECT_EQ(rangeValue->GetToValue(), checkRangeValue.get()->GetToValue());
        } else {
            EXPECT_FALSE(sliderPaintProperty->GetValidSlideRange().has_value());
        }
        EXPECT_EQ(sliderPaintProperty->GetValue(), checkValue);
    }
}

/**
 * @tc.name: SliderValidRangeTest003
 * @tc.desc: Check touch events with Slider valid range
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest003, TestSize.Level1)
{
    struct TestInputData {
        float value { 0.0f };
        float touchOffset { 0.0f };
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    struct TestOutputData {
        float value;
    };

    std::vector<std::pair<TestInputData, TestOutputData>> testSliderValidRangeData {
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE - 1.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE - 10.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, 1.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE + 1.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, 10.0f, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIDDLE_OF_RANGE + 10.0f }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -MIDDLE_OF_RANGE,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, -MIDDLE_OF_RANGE + 1.0f,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MIN_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, MIN_RANGE, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, MAX - MIDDLE_OF_RANGE - 1.0f,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE }),
        std::make_pair<TestInputData, TestOutputData>(
            { MIDDLE_OF_RANGE, MAX - MIDDLE_OF_RANGE,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { MAX_RANGE }),
    };

    for (auto testData : testSliderValidRangeData) {
        /**
         * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
         */
        SliderModelNG sliderModelNG;
        float setValue = testData.first.value;
        float touchOffset = testData.first.touchOffset;
        auto setRangeValue = testData.first.range;
        sliderModelNG.Create(setValue, STEP, MIN, MAX);
        if (setRangeValue.get()) {
            sliderModelNG.SetValidSlideRange(setRangeValue.get()->GetFromValue(), setRangeValue.get()->GetToValue());
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);
        frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        ASSERT_NE(sliderPaintProperty, nullptr);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
        auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
        EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
        sliderPattern->sliderLength_ = MIN_LABEL * MIN_LABEL;
        sliderPattern->blockHotSize_ = SizeF(setValue, MIN_LABEL);

        /**
         * @tc.steps: step2. initialize touch information.
         * @tc.desc:  when TouchType is DOWN, SourceType is touch.
         */
        TouchLocationInfo LInfo(0);
        LInfo.touchType_ = TouchType::DOWN;
        LInfo.localLocation_ = Offset(setValue + touchOffset, MAX_LABEL);
        TouchEventInfo infoDown("");
        infoDown.SetSourceDevice(SourceType::TOUCH);
        infoDown.changedTouches_.emplace_back(LInfo);

        /**
         * @tc.steps: step2. initialize touch information.
         * @tc.desc:  when TouchType is UP, SourceType is touch.
         */
        TouchLocationInfo UpInfo(0);
        UpInfo.touchType_ = TouchType::UP;
        UpInfo.localLocation_ = Offset(setValue + touchOffset, MAX_LABEL);
        TouchEventInfo infoUp("");
        infoUp.SetSourceDevice(SourceType::TOUCH);
        infoUp.changedTouches_.emplace_back(UpInfo);

        /**
         * @tc.cases: case1. check Slider value after touch down
         */
        sliderPattern->lastTouchLocation_ = Offset(setValue + touchOffset, MAX_LABEL);
        sliderPattern->fingerId_ = LInfo.GetFingerId();
        sliderPattern->HandleTouchEvent(infoDown);

        /**
         * @tc.cases: case2. check Slider value after touch up
         */
        sliderPattern->HandleTouchEvent(infoUp);
        EXPECT_TRUE(NearEqual(sliderPattern->value_, setValue));
    }
}

/**
 * @tc.name: SliderValidRangeTest004
 * @tc.desc: Check set Valid Slide Range depends on Slider STEP
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest004, TestSize.Level1)
{
    struct TestInputData {
        float stepValue { 1.0f };
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    struct TestOutputData {
        std::shared_ptr<SliderModel::SliderValidRange> range { nullptr };
    };
    constexpr float STEP_10 = 10.0f;
    constexpr float STEP_3 = 3.0f;
    constexpr float STEP_7 = 7.0f;
    constexpr float STEP_2 = 2.0f;
    std::vector<std::pair<TestInputData, TestOutputData>> testSliderValidRangeData {
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + 1.0f, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + 2.0f, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + STEP_10 / 2, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(STEP_10 + 1.0f + STEP_10 / 2, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(2 * STEP_10 - 1.0f, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_10, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + 2.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + STEP_10 / 2) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_10,
                std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE - STEP_10 + STEP_10 / 2 + 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_7, std::make_shared<SliderModel::SliderValidRange>(STEP_7 * 5 + 1.0f, STEP_7 * 10 - 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_7 * 5, STEP_7 * 10) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_7, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_7 * 5, MAX_RANGE) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_3, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE, MAX_RANGE) },
            { std::make_shared<SliderModel::SliderValidRange>(STEP_3 * 13, STEP_3 * 24) }),
        std::make_pair<TestInputData, TestOutputData>(
            { STEP_2, std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE - 1.0f, MAX_RANGE - 1.0f) },
            { std::make_shared<SliderModel::SliderValidRange>(MIN_RANGE - STEP_2, MAX_RANGE) }),
    };
    for (auto testData : testSliderValidRangeData) {
        /**
         * @tc.steps: step1. create slider and set the properties ,and then get frameNode.
         */
        SliderModelNG sliderModelNG;
        auto stepValue = testData.first.stepValue;
        auto setRangeValue = testData.first.range;
        auto checkRangeValue = testData.second.range;
        sliderModelNG.Create(VALUE, stepValue, MIN, MAX);
        if (setRangeValue.get()) {
            sliderModelNG.SetValidSlideRange(setRangeValue.get()->GetFromValue(), setRangeValue.get()->GetToValue());
        }
        std::function<void(float, int32_t)> eventOnChange = [](float floatValue, int32_t intValue) {};
        sliderModelNG.SetOnChange(std::move(eventOnChange));
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        EXPECT_NE(frameNode, nullptr);

        /**
         * @tc.steps: step2. get SliderValidRange.
         * @tc.expected: step2. check whether the properties is correct.
         */
        auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
        EXPECT_NE(sliderPaintProperty, nullptr);
        EXPECT_EQ(sliderPaintProperty->GetMax(), MAX);
        EXPECT_EQ(sliderPaintProperty->GetMin(), MIN);
        EXPECT_EQ(sliderPaintProperty->GetStep(), stepValue);

        if (checkRangeValue.get()) {
            EXPECT_TRUE(sliderPaintProperty->GetValidSlideRange().has_value());
            auto rangeValue = sliderPaintProperty->GetValidSlideRange().value();
            EXPECT_EQ(rangeValue->GetFromValue(), checkRangeValue.get()->GetFromValue());
            EXPECT_EQ(rangeValue->GetToValue(), checkRangeValue.get()->GetToValue());
        } else {
            //should not never call. If you are here test FAILED
            ASSERT_TRUE(sliderPaintProperty->GetValidSlideRange().has_value());
        }
    }
}

/**
 * @tc.name: SliderValidRangeTest005
 * @tc.desc: Check changes by KeyPad keys and Slider Valid Range values
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest005, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(MIN_RANGE, STEP, MIN, MAX);
    sliderModelNG.SetValidSlideRange(MIN_RANGE, MAX_RANGE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<SliderPattern> sliderPattern = frameNode->GetPattern<SliderPattern>();
    EXPECT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_NE(sliderLayoutProperty, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    EXPECT_NE(sliderPaintProperty, nullptr);
    sliderPattern->value_ = sliderPaintProperty->GetValue().value_or(0.0f);

    /**
     * @tc.cases: case1. event.action != KeyAction::DOWN.
     */
    KeyEvent event;
    event.action = KeyAction::UP;
    EXPECT_FALSE(sliderPattern->OnKeyEvent(event));
    /**
     * @tc.cases: case2. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT, MoveStep(-1).
     */
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_DPAD_LEFT;
    sliderPattern->value_ = MIN_RANGE;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MIN_RANGE);

    /**
     * @tc.cases: case3. direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_RIGHT;
    sliderPattern->value_ = MIN_RANGE;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MIN_RANGE + STEP);
    /**
     * @tc.cases: case4. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP, MoveStep(-1).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->value_ = MAX_RANGE;
    event.code = KeyCode::KEY_DPAD_UP;
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MAX_RANGE - STEP);
    /**
     * @tc.cases: case5. direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN, MoveStep(1).
     */
    event.code = KeyCode::KEY_DPAD_DOWN;
    sliderPattern->value_ = MAX_RANGE;
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    EXPECT_TRUE(sliderPattern->OnKeyEvent(event));
    EXPECT_EQ(sliderPattern->value_, MAX_RANGE);
}

/**
 * @tc.name: SliderValidRangeTest006
 * @tc.desc: Slide by slider block and check Slider value by Slider Valid Range
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest006, TestSize.Level1)
{
    struct TestData {
        float startValue { 1.0f };
        float offsetValue { 0.0f };
        float valueAfterSlide { 0.0f };
        float valueAfteTouchUp { 0.0f };
    };
    std::vector<TestData> testSliderValidRangeData {
        { VALUE, -7.0f, VALUE - 7.0f, VALUE - 7.0f },
        { VALUE, 7.0f, VALUE + 7.0f, VALUE + 7.0f },
        { VALUE, -40.0f, VALUE - 40.0f, MIN_RANGE },
        { VALUE, 40.0f, VALUE + 40.0f, MAX_RANGE },
    };
    for (auto testData : testSliderValidRangeData) {
        auto startValue = testData.startValue;
        auto touchOffset = testData.offsetValue;
        auto valueEndSlide = testData.valueAfterSlide;
        auto endValue = testData.valueAfteTouchUp;
        SliderModelNG sliderModelNG;
        sliderModelNG.Create(startValue, STEP, MIN, MAX);
        sliderModelNG.SetValidSlideRange(MIN_RANGE, MAX_RANGE);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        ASSERT_NE(frameNode, nullptr);
        frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
        auto sliderPattern = frameNode->GetPattern<SliderPattern>();
        ASSERT_NE(sliderPattern, nullptr);
        sliderPattern->sliderLength_ = MIN_LABEL * MIN_LABEL;
        sliderPattern->blockHotSize_ = SizeF(startValue, MIN_LABEL);

        /**
         * @tc.cases: case1. InputEventType is not AXIS and drag by block to 20.0
         */
        GestureEvent info;
        info.SetSourceDevice(SourceType::TOUCH);
        sliderPattern->UpdateCircleCenterOffset();

        EXPECT_EQ(sliderPattern->circleCenter_.GetX(), startValue);
        info.localLocation_ = Offset(startValue, MIN_LABEL);

        info.inputEventType_ = InputEventType::TOUCH_SCREEN;
        sliderPattern->HandlingGestureStart(info);

        info.SetOffsetX(touchOffset);
        info.localLocation_ = Offset(startValue + touchOffset, info.localLocation_.GetY());
        sliderPattern->HandlingGestureEvent(info);
        EXPECT_TRUE(NearEqual(sliderPattern->value_, valueEndSlide));
        sliderPattern->HandledGestureEvent();
        sliderPattern->UpdateToValidValue();
        EXPECT_TRUE(NearEqual(sliderPattern->value_, endValue));
    }
}

/**
 * @tc.name: SliderValidRangeTest007
 * @tc.desc: Check "GetValidSlideRange" API
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderValidRangeTest007, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetValidSlideRange(MIN_RANGE, MAX_RANGE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto validRange = SliderModelNG::GetValidSlideRange(Referenced::RawPtr(frameNode));
    EXPECT_TRUE(validRange && validRange->HasValidValues());
    EXPECT_EQ(validRange->GetFromValue(), MIN_RANGE);
    EXPECT_EQ(validRange->GetToValue(), MAX_RANGE);
}

/**
 * @tc.name: PaintHorizontalBubbleSuitableAgingTest001
 * @tc.desc: TEST slider_tip_modifier PaintHorizontalBubbleSuitableAging
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, PaintHorizontalBubbleSuitableAgingTest001, TestSize.Level1)
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
HWTEST_F(SliderExTestNg, PaintHorizontalBubbleSuitableAgingTest002, TestSize.Level1)
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
HWTEST_F(SliderExTestNg, PaintVerticalBubbleSuitableAgingTest001, TestSize.Level1)
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
    sliderPattern->direction_ = Axis::VERTICAL;
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
HWTEST_F(SliderExTestNg, PaintVerticalBubbleSuitableAgingTest002, TestSize.Level1)
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
    sliderPattern->direction_ = Axis::VERTICAL;
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
 * @tc.name: SliderTrackBackgroundColor001
 * @tc.desc: Check "SetTrackBackgroundColor" an "GetTrackBackgroundColor"  API
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderTrackBackgroundColor001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);

    Gradient defaultGradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::GREEN));
    gradientColor1.SetDimension(Dimension(0.0));
    defaultGradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(1.0));
    defaultGradient.AddColor(gradientColor2);
    std::vector<GradientColor> defaultGradientColors = defaultGradient.GetColors();

    SliderModelNG::SetTrackBackgroundColor(Referenced::RawPtr(frameNode), defaultGradient);
    Gradient testGradient = SliderModelNG::GetTrackBackgroundColor(Referenced::RawPtr(frameNode));
    std::vector<GradientColor> testGradientColors = testGradient.GetColors();

    EXPECT_EQ(defaultGradientColors.size(), testGradientColors.size());
    EXPECT_EQ(defaultGradientColors.at(0).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(0).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(1).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(1).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(0).GetDimension(), testGradientColors.at(0).GetDimension());
    EXPECT_EQ(defaultGradientColors.at(1).GetDimension(), testGradientColors.at(1).GetDimension());
}

/**
 * @tc.name: SliderPaintMethodTest004
 * @tc.desc: Test slider_paint_method UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPaintMethodTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and sliderPaintMethod.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(5.0, 10.0, 10.0, 20.0);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    parameters.trackThickness = static_cast<float>(SLIDER_NONE_TRACK_THICKNRESS.ConvertToPx());
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr, nullptr);
    auto sliderTipModifier = AceType::MakeRefPtr<SliderTipModifier>(nullptr);
    SliderPaintMethod::TipParameters tipParameters;
    SliderPaintMethod sliderPaintMethod(
        sliderContentModifier, parameters, 1.0f, 1.0f, sliderTipModifier, tipParameters, TextDirection::AUTO);
    /**
     * @tc.steps: step2. create paintWrapper.
     */
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(frameNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty())
        ->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    /**
     * @tc.steps: step3. call UpdateContentModifier function.
     */
    // set theme
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    Color color = Color::RED;
    sliderTheme->markerColor_ = color;
    sliderPaintMethod.sliderContentModifier_->stepColor_ =
       AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(sliderTheme->markerColor_));
    // call UpdateContentModifier function
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderPaintMethod.sliderContentModifier_->stepColor_->Get(), LinearColor(Color::RED));
}
} // namespace OHOS::Ace::NG
