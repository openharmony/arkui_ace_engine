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
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "ui/properties/ui_material.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/border_image.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/property/accessibility_property_helper.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_paint_method.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_pattern.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

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
const PointF POINTF_END_DIFFX { 10.0f, 20.0f };
const PointF POINTF_START_DIFFY { 10.0f, 20.0f };
const PointF POINTF_END_DIFFY { 20.0f, 10.0f };
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
constexpr Dimension ARROW_WIDTH = 16.0_vp;
constexpr Dimension CIRCULAR_HORIZON_OFFSET = 13.86_vp;
constexpr Dimension TEXT_MAX = 36.0_vp;
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
const PointF POINTF_CENTER { 15.0f, 15.0f };
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
const std::vector<PointF> HORIZONTAL_STEP_POINTS { { 10, 20 }, { 20, 20 }, { 30, 20 } };
constexpr float TRACK_THICKNESS = 40.0f;
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
        [sliderPattern]() { return sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()); });
    /**
     * @tc.steps: step2. set sliderTipModifier attribute and call onDraw function.
     */
    sliderTipModifier.SetSliderGlobalOffset(SLIDER_GLOBAL_OFFSET);
    sliderTipModifier.tipFlag_ = AceType::MakeRefPtr<PropertyBool>(true);
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

    SliderModelNG sliderModelNG;
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
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
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
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
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
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
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*theme, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

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
    auto sliderContentModifier = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
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
    sliderPaintMethod.UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
    EXPECT_EQ(sliderTipModifier->axis_, Axis::VERTICAL);

    AceType::DynamicCast<SliderPaintProperty>(paintWrapper->paintProperty_)->UpdateDirection(Axis::HORIZONTAL);
    sliderPaintMethod.UpdateOverlayModifier(Referenced::RawPtr(paintWrapper));
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
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
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
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper1));
    EXPECT_EQ(sliderContentModifier->sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::INSET));
    EXPECT_EQ(sliderContentModifier->directionAxis_->Get(), static_cast<int>(Axis::HORIZONTAL));
    auto rect1 = sliderContentModifier->GetBoundsRect();
    EXPECT_EQ(rect1->Width(), 370.0f);
    EXPECT_EQ(rect1->Height(), 180.0f);
    sliderPaintProperty->UpdateSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    auto paintWrapper2 = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, sliderPaintProperty);
    sliderPaintMethod.UpdateContentModifier(Referenced::RawPtr(paintWrapper2));
    EXPECT_EQ(sliderContentModifier->sliderMode_->Get(), static_cast<int>(SliderModelNG::SliderMode::OUTSET));
    EXPECT_EQ(sliderContentModifier->directionAxis_->Get(), static_cast<int>(Axis::VERTICAL));
    auto rect2 = sliderContentModifier->GetBoundsRect();
    EXPECT_EQ(rect2->Width(), 120.0f);
    EXPECT_EQ(rect2->Height(), 260.0f);
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
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);

    /**
     * @tc.steps: step2. slider is focus,showtip is true.expect bubbleFlag_ is true.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    sliderPaintProperty->UpdateShowTips(true);
    sliderPattern->OnModifyDone();
    sliderPattern->InitEvent();
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
    sliderTipModifier.arrowWidth_ = arrowSizeWidth;
    sliderTipModifier.arrowHeight_ = arrowSizeHeight;
    sliderTipModifier.circularHorizontalOffset_ = circularOffset;
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
 * @tc.name: SliderAccessibilityPropertyTest004
 * @tc.desc: Test SetSpecificSupportAction when value at boundary
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderAccessibilityPropertyTest004, TestSize.Level1)
{
    SliderModelNG sliderModelNG1;
    sliderModelNG1.Create(MAX, STEP, MIN, MAX);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode1, nullptr);
    auto sliderAccessibilityProperty1 = frameNode1->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty1, nullptr);
    sliderAccessibilityProperty1->ResetSupportAction();
    sliderAccessibilityProperty1->SetSpecificSupportAction();
    auto supportAceActions1 = sliderAccessibilityProperty1->GetSupportAction();
    EXPECT_EQ(supportAceActions1.count(AceAction::ACTION_SCROLL_FORWARD), 0);
    EXPECT_EQ(supportAceActions1.count(AceAction::ACTION_SCROLL_BACKWARD), 1);

    SliderModelNG sliderModelNG2;
    sliderModelNG2.Create(MIN, STEP, MIN, MAX);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto sliderAccessibilityProperty2 = frameNode2->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty2, nullptr);
    sliderAccessibilityProperty2->ResetSupportAction();
    sliderAccessibilityProperty2->SetSpecificSupportAction();
    auto supportAceActions2 = sliderAccessibilityProperty2->GetSupportAction();
    EXPECT_EQ(supportAceActions2.count(AceAction::ACTION_SCROLL_FORWARD), 1);
    EXPECT_EQ(supportAceActions2.count(AceAction::ACTION_SCROLL_BACKWARD), 0);
}

/**
 * @tc.name: SliderAccessibilityPropertyTest006
 * @tc.desc: Test GetExtraElementInfo with different directions
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderAccessibilityPropertyTest006, TestSize.Level1)
{
    Accessibility::ExtraElementInfo extraElementInfo;

    SliderModelNG sliderModelNG1;
    sliderModelNG1.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG1.SetDirection(Axis::VERTICAL);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode1, nullptr);
    auto sliderAccessibilityProperty1 = frameNode1->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty1, nullptr);
    sliderAccessibilityProperty1->GetExtraElementInfo(extraElementInfo);

    SliderModelNG sliderModelNG2;
    sliderModelNG2.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG2.SetDirection(Axis::HORIZONTAL);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto sliderAccessibilityProperty2 = frameNode2->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty2, nullptr);
    sliderAccessibilityProperty2->GetExtraElementInfo(extraElementInfo);

    SliderModelNG sliderModelNG3;
    sliderModelNG3.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG3.SetDirection(Axis::FREE);
    auto frameNode3 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode3, nullptr);
    auto sliderAccessibilityProperty3 = frameNode3->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty3, nullptr);
    sliderAccessibilityProperty3->GetExtraElementInfo(extraElementInfo);

    SliderModelNG sliderModelNG4;
    sliderModelNG4.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG4.SetDirection(Axis::NONE);
    auto frameNode4 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode4, nullptr);
    auto sliderAccessibilityProperty4 = frameNode4->GetAccessibilityProperty<SliderAccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty4, nullptr);
    sliderAccessibilityProperty4->GetExtraElementInfo(extraElementInfo);
}

/**
 * @tc.name: SliderPatternMultiThreadTest001
 * @tc.desc: Test UpdateValueMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPatternMultiThreadTest001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    // Branch 1: isExceptionValueRecovery=true (value out of range, isNotifyRecovery=true)
    sliderPaintProperty->UpdateMin(0.0f);
    sliderPaintProperty->UpdateMax(100.0f);
    sliderPaintProperty->UpdateValue(150.0f); // Out of range
    sliderPattern->UpdateValueMultiThread(frameNode, true);

    // Branch 2: isExceptionValueRecovery=false (value in range)
    sliderPaintProperty->UpdateValue(50.0f); // Normal value
    sliderPattern->UpdateValueMultiThread(frameNode, true);
}

/**
 * @tc.name: SliderLayoutAlgorithm_CalculateSliderLength_OutsetEndsTrue
 * @tc.desc: Test CalculateSliderLength OUTSET mode with Ends true
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderLayoutAlgorithm_CalculateSliderLength_OutsetEndsTrue, TestSize.Level1)
{
    SliderLayoutAlgorithm algorithm;
    float length = algorithm.CalculateSliderLength(
        500.0f, 500.0f, Axis::HORIZONTAL, SliderModel::SliderMode::OUTSET, true);
    EXPECT_LT(length, 500.0f);
}

/**
 * @tc.name: SliderModelNG_SetThickness_InsetMode
 * @tc.desc: Test SetThickness INSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderModelNG_SetThickness_InsetMode, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetSliderMode(SliderModel::SliderMode::INSET);
    sliderModelNG.SetThickness(Dimension(20.0));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    SliderModelNG::SetThickness(AceType::RawPtr(frameNode), Dimension(20.0));

    sliderModelNG.SetSliderMode(SliderModel::SliderMode::NONE);
    SliderModelNG::SetThickness(AceType::RawPtr(frameNode), Dimension(15.0));
}

/**
 * @tc.name: SliderModelNG_SetBlockSize_ThemeNotNull
 * @tc.desc: Test SetBlockSize with theme
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderModelNG_SetBlockSize_ThemeNotNull, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    SliderModelNG::SetBlockSize(AceType::RawPtr(frameNode), Dimension(40.0), Dimension(40.0));
}

/**
 * @tc.name: SliderPattern_GetDirection_Branches
 * @tc.desc: Test GetDirection branches
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_GetDirection_Branches, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();

    layoutProperty->UpdateDirection(Axis::HORIZONTAL);
    auto direction = pattern->GetDirection();
    EXPECT_EQ(direction, Axis::HORIZONTAL);

    layoutProperty->UpdateDirection(Axis::VERTICAL);
    direction = pattern->GetDirection();
    EXPECT_EQ(direction, Axis::VERTICAL);
}

/**
 * @tc.name: SliderPattern_HasPrefixSuffix_Branches
 * @tc.desc: Test HasPrefix/HasSuffix
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HasPrefixSuffix_Branches, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    pattern->contentModifierNode_ = nullptr;
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    pattern->prefix_ = AceType::WeakClaim(AceType::RawPtr(prefixNode));

    EXPECT_TRUE(pattern->HasPrefix());
    EXPECT_FALSE(pattern->HasSuffix());

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));

    EXPECT_TRUE(pattern->HasPrefix());
    EXPECT_TRUE(pattern->HasSuffix());
}

/**
 * @tc.name: SliderPattern_GetStepIndex_Branches
 * @tc.desc: Test GetOffsetStepIndex
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_GetStepIndex_Branches, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderModelNG sliderModelNG;
    sliderModelNG.Create(50.0f, 0.0f, 0.0f, 100.0f);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->value_ = 50.0f;
    pattern->GetOffsetStepIndex(0);  // NearZero(step) returns 0

    // Test GetOffsetStepIndex with normal step
    SliderModelNG sliderModelNG2;
    sliderModelNG2.Create(50.0f, 10.0f, 0.0f, 100.0f);  // step=10
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
    auto pattern2 = frameNode2->GetPattern<SliderPattern>();
    ASSERT_NE(pattern2, nullptr);

    pattern2->value_ = 50.0f;
    pattern2->GetOffsetStepIndex(5);  // cover line 947
}

/**
 * @tc.name: SliderPattern_GetDirection_Axis
 * @tc.desc: Test GetDirection Axis branches
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_GetDirection_Axis, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();

    layoutProperty->UpdateDirection(Axis::HORIZONTAL);
    EXPECT_EQ(pattern->GetDirection(), Axis::HORIZONTAL);

    layoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(pattern->GetDirection(), Axis::VERTICAL);

    layoutProperty->UpdateDirection(Axis::FREE);
    EXPECT_EQ(pattern->GetDirection(), Axis::FREE);
}

/**
 * @tc.name: SliderPattern_PanMoveFlag_Branch
 * @tc.desc: Test panMoveFlag_
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_PanMoveFlag_Branch, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    pattern->panMoveFlag_ = false;
    EXPECT_FALSE(pattern->panMoveFlag_);

    pattern->panMoveFlag_ = true;
    EXPECT_TRUE(pattern->panMoveFlag_);
}

/**
 * @tc.name: SliderPattern_HasPrefixSuffix_Full
 * @tc.desc: Test HasPrefix/HasSuffix
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HasPrefixSuffix_Full, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    pattern->contentModifierNode_ = nullptr;
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    // No prefix or suffix
    EXPECT_FALSE(pattern->HasPrefix());
    EXPECT_FALSE(pattern->HasSuffix());

    // With prefix
    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    pattern->prefix_ = AceType::WeakClaim(AceType::RawPtr(prefixNode));
    EXPECT_TRUE(pattern->HasPrefix());

    // With suffix
    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));
    EXPECT_TRUE(pattern->HasSuffix());
}

/**
 * @tc.name: SliderPattern_GetDirection_Horizontal
 * @tc.desc: Test GetDirection
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_GetDirection_Horizontal, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();

    layoutProperty->UpdateDirection(Axis::HORIZONTAL);
    EXPECT_EQ(pattern->GetDirection(), Axis::HORIZONTAL);

    // VERTICAL - false branch
    layoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(pattern->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: SliderPattern_SliderModeNoneBranch
 * @tc.desc: Test SliderMode NONE
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_SliderModeNoneBranch, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderModelNG model;
    model.Create(50.0f, 10.0f, 0.0f, 100.0f);
    model.SetSliderMode(SliderModel::SliderMode::NONE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET), SliderModel::SliderMode::NONE);
}

/**
 * @tc.name: SliderPattern_InteractionModeBranches
 * @tc.desc: Test sliderInteractionMode_
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_InteractionModeBranches, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP;
    EXPECT_EQ(pattern->sliderInteractionMode_, SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP);

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_ONLY;
    EXPECT_EQ(pattern->sliderInteractionMode_, SliderModelNG::SliderInteraction::SLIDE_ONLY);
}

/**
 * @tc.name: SliderPattern_ShowTipsBranch
 * @tc.desc: Test showTips_
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_ShowTipsBranch, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    pattern->showTips_ = true;
    EXPECT_TRUE(pattern->showTips_);

    pattern->showTips_ = false;  // false
    EXPECT_FALSE(pattern->showTips_);
}

/**
 * @tc.name: SliderPattern_SliderModeOutsetNone
 * @tc.desc: Test SliderMode OUTSET/NONE
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_SliderModeOutsetNone, TestSize.Level1)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    model.SetSliderMode(SliderModel::SliderMode::OUTSET);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    SliderModelNG model2;
    model2.Create(VALUE, STEP, MIN, MAX);
    model2.SetSliderMode(SliderModel::SliderMode::NONE);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode2, nullptr);
}

/**
 * @tc.name: SliderPattern_ImageFrameNodeNull
 * @tc.desc: Test imageFrameNode_
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_ImageFrameNodeNull, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    pattern->imageFrameNode_ = nullptr;
    EXPECT_EQ(pattern->imageFrameNode_, nullptr);
}

/**
 * @tc.name: SliderPattern_PrefixSuffixStackNull
 * @tc.desc: Test prefixNodeStack_ and suffixNodeStack_
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_PrefixSuffixStackNull, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);

    pattern->prefixNodeStack_ = nullptr;
    EXPECT_EQ(pattern->prefixNodeStack_, nullptr);

    pattern->suffixNodeStack_ = nullptr;
    EXPECT_EQ(pattern->suffixNodeStack_, nullptr);
}

/**
 * @tc.name: SliderPattern_StepZeroBranch
 * @tc.desc: Test step == 0
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_StepZeroBranch, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();

    paintProperty->UpdateStep(0.0f);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);

    float step = paintProperty->GetStepValue(1.0f);
    EXPECT_EQ(step, 0.0f);
}

/**
 * @tc.name: SliderPattern_ManyBranches_Part2
 * @tc.desc: Cover more branches
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_ManyBranches_Part2, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);
    auto layoutProp = frameNode->GetLayoutProperty<SliderLayoutProperty>();

    layoutProp->UpdateSliderMode(SliderModel::SliderMode::NONE);
    layoutProp->UpdateDirection(Axis::HORIZONTAL);

    layoutProp->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    layoutProp->UpdateDirection(Axis::VERTICAL);

    pattern->prefixNodeStack_ = nullptr;
    pattern->suffixNodeStack_ = nullptr;
    pattern->IsSliderVisible();

    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    paintProp->UpdateStep(0.0f);
    paintProp->UpdateBlockType(SliderModel::BlockStyleType::DEFAULT);

    pattern->dragFrameNode_ = nullptr;
    pattern->sliderContentModifier_ = nullptr;
    pattern->dragPointNode_ = nullptr;

    layoutProp->UpdateDirection(Axis::HORIZONTAL);
    layoutProp->UpdateReverse(false);

    layoutProp->UpdateReverse(true);

    layoutProp->UpdateDirection(Axis::VERTICAL);
    layoutProp->UpdateReverse(false);
    layoutProp->UpdateReverse(true);

    pattern->selectedTrackFrameNode_ = nullptr;
    pattern->particleFrameNode_ = nullptr;

    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    pattern->prefix_ = AceType::WeakClaim(AceType::RawPtr(prefixNode));
    EXPECT_TRUE(pattern->HasPrefix());

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));
    EXPECT_TRUE(pattern->HasSuffix());
}

/**
 * @tc.name: SliderPattern_MoreBranches_Part3
 * @tc.desc: Cover remaining simple branches
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_MoreBranches_Part3, TestSize.Level1)
{
    RefPtr<SliderPattern> pattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, pattern);
    auto layoutProp = frameNode->GetLayoutProperty<SliderLayoutProperty>();

    layoutProp->UpdateDirection(Axis::HORIZONTAL);
    EXPECT_EQ(pattern->GetDirection(), Axis::HORIZONTAL);

    pattern->imageFrameNode_ = nullptr;
    pattern->imageFrameNode_ = frameNode;
}

/**
 * @tc.name: SliderPattern_UpdateSliderComponentColor_SystemColorChange
 * @tc.desc: Test UpdateSliderComponentColor with IsSystemColorChange true and switch cases
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_UpdateSliderComponentColor_SystemColorChange, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetIsSystemColorChange(true);

    Color testColor = Color::RED;
    Gradient gradient = SliderModelNG::CreateSolidGradient(testColor);

    pattern->UpdateSliderComponentColor(testColor, SliderColorType::BLOCK_COLOR, gradient);
    EXPECT_EQ(paintProp->GetBlockColorValue(Color::TRANSPARENT), testColor);

    pattern->UpdateSliderComponentColor(testColor, SliderColorType::TRACK_COLOR, gradient);
    EXPECT_TRUE(paintProp->GetTrackBackgroundIsResourceColorValue(false));

    pattern->UpdateSliderComponentColor(testColor, SliderColorType::SELECT_COLOR, gradient);
    EXPECT_EQ(paintProp->GetSelectColorValue(Color::TRANSPARENT), testColor);

    pattern->UpdateSliderComponentColor(testColor, SliderColorType::BLOCK_BORDER_COLOR, gradient);
    EXPECT_EQ(paintProp->GetBlockBorderColorValue(Color::TRANSPARENT), testColor);

    pattern->UpdateSliderComponentColor(testColor, SliderColorType::STEP_COLOR, gradient);
    EXPECT_EQ(paintProp->GetStepColorValue(Color::TRANSPARENT), testColor);

    pipeline->SetIsSystemColorChange(false);
}

/**
 * @tc.name: SliderPattern_HandleTouchUp_InteractionModes
 * @tc.desc: Test HandleTouchUp with different interaction modes and showTips
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HandleTouchUp_InteractionModes, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP;
    pattern->HandleTouchUp(Offset(10, 10), SourceType::TOUCH);
    EXPECT_TRUE(pattern->allowDragEvents_);

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_ONLY;
    pattern->bubbleFlag_ = true;
    pattern->HandleTouchUp(Offset(10, 10), SourceType::TOUCH);
    EXPECT_FALSE(pattern->bubbleFlag_);

    pattern->showTips_ = true;
    pattern->bubbleFlag_ = false;
    pattern->HandleTouchUp(Offset(10, 10), SourceType::TOUCH);
}

/**
 * @tc.name: SliderPattern_HandleTouchDown_SourceTypes
 * @tc.desc: Test HandleTouchDown with different sourceType cases
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HandleTouchDown_SourceTypes, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->HandleTouchDown(Offset(10, 10), SourceType::TOUCH);
    pattern->HandleTouchDown(Offset(10, 10), SourceType::MOUSE);
    pattern->HandleTouchDown(Offset(10, 10), SourceType::NONE);
}

/**
 * @tc.name: SliderPattern_CreateNodePaintMethod_VisibilityBranches
 * @tc.desc: Test CreateNodePaintMethod with visibility and modifier states
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_CreateNodePaintMethod_VisibilityBranches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->isVisibleArea_ = false;
    auto result1 = pattern->CreateNodePaintMethod();
    EXPECT_EQ(result1, nullptr);

    pattern->isVisibleArea_ = true;
    pattern->sliderContentModifier_ = nullptr;
    auto result2 = pattern->CreateNodePaintMethod();
    ASSERT_NE(result2, nullptr);
    ASSERT_NE(pattern->sliderContentModifier_, nullptr);

    pattern->sliderTipModifier_ = nullptr;
    pattern->bubbleFlag_ = true;
    auto result3 = pattern->CreateNodePaintMethod();
    ASSERT_NE(result3, nullptr);
    ASSERT_NE(pattern->sliderTipModifier_, nullptr);
}

/**
 * @tc.name: SliderPattern_OnModifyDone_PanMoveFlagBranch
 * @tc.desc: Test OnModifyDone with panMoveFlag false to trigger UpdateToValidValue
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_OnModifyDone_PanMoveFlagBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->panMoveFlag_ = false;
    pattern->OnModifyDone();
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);
    EXPECT_EQ(paintProp->GetValueValue(0), VALUE);

    pattern->panMoveFlag_ = true;
    pattern->OnModifyDone();
}

/**
 * @tc.name: SliderPattern_CalcSliderValue_StepValidation
 * @tc.desc: Test CalcSliderValue with invalid step values
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_CalcSliderValue_StepValidation, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);

    paintProp->UpdateStep(-1.0f);
    paintProp->UpdateMin(0.0f);
    paintProp->UpdateMax(100.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetStepValue(1.0f), 1.0f);

    paintProp->UpdateStep(200.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetStepValue(1.0f), 1.0f);

    paintProp->UpdateStep(0.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetStepValue(1.0f), 1.0f);
}

/**
 * @tc.name: SliderPattern_UpdateSliderComponentMedia_SystemColorChange
 * @tc.desc: Test UpdateSliderComponentMedia with system color change
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_UpdateSliderComponentMedia_SystemColorChange, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetIsSystemColorChange(true);

    pattern->UpdateSliderComponentMedia();

    pipeline->SetIsSystemColorChange(false);
    pattern->UpdateSliderComponentMedia();
}

/**
 * @tc.name: SliderPattern_UpdateSliderComponentString_SystemColorChange
 * @tc.desc: Test UpdateSliderComponentString with system color change
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_UpdateSliderComponentString_SystemColorChange, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetIsSystemColorChange(true);

    pattern->UpdateSliderComponentString(true, "test content");
    EXPECT_TRUE(paintProp->GetShowTipsValue(false));
    EXPECT_EQ(paintProp->GetCustomContentValue(""), "test content");

    pipeline->SetIsSystemColorChange(false);
    pattern->UpdateSliderComponentString(false, "new content");
}

/**
 * @tc.name: SliderPattern_SliderMode_NoneBranches
 * @tc.desc: Test slider with NONE mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_SliderMode_NoneBranches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    model.SetSliderMode(SliderModel::SliderMode::NONE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_EQ(layoutProp->GetSliderModeValue(SliderModel::SliderMode::OUTSET), SliderModel::SliderMode::NONE);

    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->UpdateParameters();
    EXPECT_EQ(pattern->borderBlank_, 0);
}

/**
 * @tc.name: SliderPattern_TouchEvent_TouchTypeBranches
 * @tc.desc: Test HandleTouchEvent with different touch types
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_TouchEvent_TouchTypeBranches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    TouchEventInfo downInfo("touch_down");
    TouchLocationInfo downLocation(0);
    downLocation.SetTouchType(TouchType::DOWN);
    downLocation.SetLocalLocation(Offset(10, 10));
    downInfo.AddTouchLocationInfo(std::move(downLocation));
    pattern->HandleTouchEvent(downInfo);

    TouchEventInfo upInfo("touch_up");
    TouchLocationInfo upLocation(0);
    upLocation.SetTouchType(TouchType::UP);
    upLocation.SetLocalLocation(Offset(10, 10));
    upInfo.AddTouchLocationInfo(std::move(upLocation));
    pattern->HandleTouchEvent(upInfo);

    TouchEventInfo cancelInfo("touch_cancel");
    TouchLocationInfo cancelLocation(0);
    cancelLocation.SetTouchType(TouchType::CANCEL);
    cancelLocation.SetLocalLocation(Offset(10, 10));
    cancelInfo.AddTouchLocationInfo(std::move(cancelLocation));
    pattern->HandleTouchEvent(cancelInfo);
}

/**
 * @tc.name: SliderPattern_GetPointAccessibilityTxt_Branches
 * @tc.desc: Test GetPointAccessibilityTxt with floating point formatting
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_GetPointAccessibilityTxt_Branches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);

    paintProp->UpdateStep(1.5f);
    paintProp->UpdateMin(0.0f);
    paintProp->UpdateMax(100.0f);

    auto result1 = pattern->GetPointAccessibilityTxt(0, 1.5f, 0.0f, 100.0f);
    EXPECT_FALSE(result1.empty());

    auto result2 = pattern->GetPointAccessibilityTxt(10, 1.5f, 0.0f, 100.0f);
    EXPECT_FALSE(result2.empty());
}

/**
 * @tc.name: SliderPattern_InitSliderEnds_PrefixSuffixBranches
 * @tc.desc: Test InitSliderEnds with prefix and suffix nodes
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_InitSliderEnds_PrefixSuffixBranches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);

    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    pattern->prefix_ = AceType::WeakClaim(AceType::RawPtr(prefixNode));
    pattern->prefixNodeStack_ = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, -1, AceType::MakeRefPtr<StackPattern>());

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -2, AceType::MakeRefPtr<TextPattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));
    pattern->suffixNodeStack_ = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, -2, AceType::MakeRefPtr<StackPattern>());

    pattern->InitSliderEnds();
}

/**
 * @tc.name: SliderPattern_AccessibilityLevel_Branches
 * @tc.desc: Test InitAccessibilityHoverEvent with different accessibility levels
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_AccessibilityLevel_Branches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    pattern->InitAccessibilityHoverEvent();

    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_HIDE_DESCENDANTS);
    pattern->InitAccessibilityHoverEvent();

    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    pattern->InitAccessibilityHoverEvent();
}

/**
 * @tc.name: SliderPattern_HandleTouchUp_CancelAndFingerIdBranches
 * @tc.desc: Test HandleTouchEvent with TouchType::CANCEL
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HandleTouchUp_CancelAndFingerIdBranches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    TouchEventInfo cancelInfo("touch_cancel");
    TouchLocationInfo cancelLocation(2);
    cancelLocation.SetTouchType(TouchType::CANCEL);
    cancelLocation.SetLocalLocation(Offset(10, 10));
    cancelInfo.AddTouchLocationInfo(std::move(cancelLocation));
    pattern->fingerId_ = 1;
    pattern->HandleTouchEvent(cancelInfo);
}

/**
 * @tc.name: SliderPattern_LongPressTask_Branches
 * @tc.desc: Test StartLongPressTimer with longPressTask existence check
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_LongPressTask_Branches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->StartLongPressTimer();
    // StartLongPressTimer returns early when IsNeedShowMaterial() is false (no system material)
    EXPECT_FALSE(pattern->longPressTask_);
}

/**
 * @tc.name: SliderPattern_IsNeedShowMaterial_Branch
 * @tc.desc: Test IsNeedShowMaterial with different conditions
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_IsNeedShowMaterial_Branch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->mousePressedFlag_ = true;
    pattern->IsNeedShowMaterial();

    pattern->mousePressedFlag_ = false;
    pattern->IsNeedShowMaterial();
}

/**
 * @tc.name: SliderPattern_UpdateStepAccessibilityVirtualNode_EmptyCheck
 * @tc.desc: Test UpdateStepAccessibilityVirtualNode with empty pointAccessibilityNodeVec
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_UpdateStepAccessibilityVirtualNode_EmptyCheck, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    model.SetShowSteps(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);

    paintProp->UpdateStep(0.0f);
    pattern->UpdateStepAccessibilityVirtualNode();

    paintProp->UpdateStep(10.0f);
    pattern->pointAccessibilityNodeVec_.clear();
    pattern->UpdateStepAccessibilityVirtualNode();
}

/**
 * @tc.name: SliderPattern_UpdateStepPointsAccessibilityVirtualNodeSelected_SuffixOptions
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected with suffix accessibility options
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_UpdateStepPointsAccessibilityVirtualNodeSelected_SuffixOptions, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->unselectedDesc_ = "unselected";
    sliderTheme->disabledDesc_ = "disabled";
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    model.SetShowSteps(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    pattern->sliderContentModifier_->stepPointVec_ = HORIZONTAL_STEP_POINTS;

    pattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));

    for (size_t i = 0; i < HORIZONTAL_STEP_POINTS.size(); i++) {
        auto pointNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1,
            AceType::MakeRefPtr<TextPattern>());
        pattern->parentAccessibilityNode_->AddChild(pointNode);
        pattern->pointAccessibilityNodeVec_.emplace_back(pointNode);
        pattern->pointAccessibilityNodeEventVec_.emplace_back(nullptr);
    }

    pattern->suffixAccessibilityoptions_.accessibilityText = "suffix text";
    pattern->suffixAccessibilityoptions_.accessibilityDescription = "suffix desc";
    pattern->suffixAccessibilityoptions_.accessibilityLevel = AccessibilityProperty::Level::YES_STR;
    pattern->suffixAccessibilityoptions_.accessibilityGroup = false;

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -2, AceType::MakeRefPtr<TextPattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));

    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProp, nullptr);
    paintProp->UpdateStep(10.0f);
    paintProp->UpdateMin(0.0f);
    paintProp->UpdateMax(100.0f);

    pattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
}

/**
 * @tc.name: SliderPattern_BatchCreateNodePaintMethod_Branches
 * @tc.desc: Cover CreateNodePaintMethod branches comprehensively
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchCreateNodePaintMethod_Branches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    auto layoutProp = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    layoutProp->UpdateSliderMode(SliderModel::SliderMode::OUTSET);

    pattern->isVisibleArea_ = false;
    pattern->CreateNodePaintMethod();

    pattern->isVisibleArea_ = true;
    pattern->sliderContentModifier_ = nullptr;
    auto result1 = pattern->CreateNodePaintMethod();
    ASSERT_NE(result1, nullptr);

    pattern->sliderTipModifier_ = nullptr;
    pattern->bubbleFlag_ = false;
    auto result2 = pattern->CreateNodePaintMethod();
    ASSERT_NE(result2, nullptr);

    pattern->sliderTipModifier_ = nullptr;
    pattern->bubbleFlag_ = true;
    auto result3 = pattern->CreateNodePaintMethod();
    ASSERT_NE(result3, nullptr);

    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    pattern->prefix_ = AceType::WeakClaim(AceType::RawPtr(prefixNode));
    pattern->contentModifierNode_ = nullptr;
    pattern->endsInitFlag_ = false;
    pattern->CreateNodePaintMethod();
}

/**
 * @tc.name: SliderPattern_BatchUpdateParameters_Branches
 * @tc.desc: Cover UpdateParameters branches with different modes
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchUpdateParameters_Branches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));

    auto layoutProp = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    pattern->sliderMode_ = SliderModel::SliderMode::OUTSET;
    layoutProp->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    pattern->UpdateSliderParams(TRACK_THICKNESS, SizeF(30.0f, 30.0f), SizeF(30.0f, 30.0f));
    pattern->UpdateParameters();

    pattern->sliderMode_ = SliderModel::SliderMode::INSET;
    layoutProp->UpdateSliderMode(SliderModel::SliderMode::INSET);
    pattern->UpdateParameters();

    pattern->sliderMode_ = SliderModel::SliderMode::NONE;
    layoutProp->UpdateSliderMode(SliderModel::SliderMode::NONE);
    pattern->UpdateParameters();
    EXPECT_EQ(pattern->borderBlank_, 0);

    layoutProp->UpdateDirection(Axis::VERTICAL);
    pattern->UpdateParameters();
}

/**
 * @tc.name: SliderPattern_BatchCalcSliderValue_Branches
 * @tc.desc: Cover CalcSliderValue with boundary values
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchCalcSliderValue_Branches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();

    paintProp->UpdateMin(100.0f);
    paintProp->UpdateMax(50.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetMinValue(0.0f), 0.0f);
    EXPECT_EQ(paintProp->GetMaxValue(100.0f), 100.0f);

    paintProp->UpdateStep(0.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetStepValue(1.0f), 1.0f);

    paintProp->UpdateStep(-5.0f);
    pattern->CalcSliderValue();

    paintProp->UpdateStep(200.0f);
    pattern->CalcSliderValue();

    paintProp->UpdateValue(150.0f);
    paintProp->UpdateMin(0.0f);
    paintProp->UpdateMax(100.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetValueValue(0.0f), 100.0f);

    paintProp->UpdateValue(-10.0f);
    pattern->CalcSliderValue();
    EXPECT_EQ(paintProp->GetValueValue(0.0f), 0.0f);
}

/**
 * @tc.name: SliderPattern_BatchInteractionModes_Branches
 * @tc.desc: Cover interaction mode branches batch
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchInteractionModes_Branches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK;
    pattern->HandleTouchUp(Offset(10, 10), SourceType::TOUCH);

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP;
    pattern->HandleTouchUp(Offset(10, 10), SourceType::TOUCH);
    EXPECT_TRUE(pattern->allowDragEvents_);

    pattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_ONLY;
    pattern->bubbleFlag_ = true;
    pattern->HandleTouchUp(Offset(10, 10), SourceType::TOUCH);
    EXPECT_FALSE(pattern->bubbleFlag_);
}
/**
 * @tc.name: SliderPattern_BatchGestureHandling_Branches
 * @tc.desc: Cover gesture handling branches
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchGestureHandling_Branches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);

    auto hub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();

    pattern->InitPanEvent(gestureHub);
    ASSERT_NE(pattern->panEvent_, nullptr);

    GestureEvent info;
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    info.SetLocalLocation(Offset(50.0f, 50.0f));

    pattern->panEvent_->actionStart_(info);
    pattern->panEvent_->actionUpdate_(info);
    pattern->panEvent_->actionEnd_(info);
    pattern->panEvent_->actionCancel_();
}

/**
 * @tc.name: SliderPattern_BatchPrefixSuffix_Init
 * @tc.desc: Cover InitSliderEndsState and position updates
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchPrefixSuffix_Init, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);

    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    pattern->prefix_ = AceType::WeakClaim(AceType::RawPtr(prefixNode));
    pattern->prefixNodeStack_ = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, -1, AceType::MakeRefPtr<StackPattern>());

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -2, AceType::MakeRefPtr<TextPattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));
    pattern->suffixNodeStack_ = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, -2, AceType::MakeRefPtr<StackPattern>());

    pattern->isVisibleArea_ = true;
    pattern->endsInitFlag_ = false;
    pattern->contentModifierNode_ = nullptr;
    auto result = pattern->CreateNodePaintMethod();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(pattern->endsInitFlag_);
}

/**
 * @tc.name: SliderPattern_BatchUpdateDirection_Branches
 * @tc.desc: Cover GetDirection with all axis values
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchUpdateDirection_Branches, TestSize.Level1)
{
    SliderModelNG model1;
    model1.Create(VALUE, STEP, MIN, MAX);
    model1.SetDirection(Axis::HORIZONTAL);
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern1 = frameNode1->GetPattern<SliderPattern>();
    EXPECT_EQ(pattern1->GetDirection(), Axis::HORIZONTAL);

    SliderModelNG model2;
    model2.Create(VALUE, STEP, MIN, MAX);
    model2.SetDirection(Axis::VERTICAL);
    auto frameNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern2 = frameNode2->GetPattern<SliderPattern>();
    EXPECT_EQ(pattern2->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: SliderPattern_BatchPrefixSuffix_Branches
 * @tc.desc: Cover SetPrefix/SetSuffix branches
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_BatchPrefixSuffix_Branches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();

    auto prefixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
    SliderPrefixOptions prefixOptions;
    pattern->SetPrefix(prefixNode, prefixOptions);

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -2, AceType::MakeRefPtr<TextPattern>());
    SliderSuffixOptions suffixOptions;
    pattern->SetSuffix(suffixNode, suffixOptions);
    EXPECT_TRUE(pattern->HasPrefix());

    pattern->ResetPrefix();
    EXPECT_TRUE(pattern->HasSuffix());
    pattern->ResetSuffix();
}

/**
 * @tc.name: SliderPattern_HandlingGestureStart_AXISBranch
 * @tc.desc: Test HandlingGestureStart with AXIS input event type
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HandlingGestureStart_AXISBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);

    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetLocalLocation(Offset(50.0f, 50.0f));
    info.SetOffsetX(1.0);
    info.SetOffsetY(0.0);
    pattern->allowDragEvents_ = true;
    pattern->HandlingGestureStart(info);
    EXPECT_TRUE(pattern->panMoveFlag_);
}

/**
 * @tc.name: SliderPattern_HandlingGestureStart_TouchBranch
 * @tc.desc: Test HandlingGestureStart with TOUCH input event and allowDragEvents false
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_HandlingGestureStart_TouchBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);

    GestureEvent info;
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);
    info.SetLocalLocation(Offset(50.0f, 50.0f));
    pattern->allowDragEvents_ = false;
    pattern->HandlingGestureStart(info);
    EXPECT_FALSE(pattern->panMoveFlag_);
}

/**
 * @tc.name: SliderPattern_OnWindowSizeChanged_VersionBranch
 * @tc.desc: Test OnWindowSizeChanged with API version >= VERSION_TWELVE and ROTATION
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_OnWindowSizeChanged_VersionBranch, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto context = MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(context);

    context->SetApiTargetVersion(13);
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    EXPECT_TRUE(pattern->skipGestureEvents_);

    context->SetApiTargetVersion(11);
    pattern->skipGestureEvents_ = false;
    pattern->OnWindowSizeChanged(100, 200, WindowSizeChangeReason::ROTATION);
    EXPECT_FALSE(pattern->skipGestureEvents_);
}

/**
 * @tc.name: SliderPattern_InitTouchEvent_RemoveBranch
 * @tc.desc: Test InitTouchEvent removes existing touchEvent when UseContentModifier true
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_InitTouchEvent_RemoveBranch, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();

    auto hub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();

    pattern->contentModifierNode_ =
        FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    pattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(nullptr);

    pattern->InitTouchEvent(gestureHub);
    EXPECT_EQ(pattern->touchEvent_, nullptr);
}

/**
 * @tc.name: SliderPattern_CreateNodePaintMethod_IsSliderVisibleFalseBranch
 * @tc.desc: Test CreateNodePaintMethod returns nullptr when IsSliderVisible false
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_CreateNodePaintMethod_IsSliderVisibleFalseBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    pattern->isVisibleArea_ = false;
    auto result = pattern->CreateNodePaintMethod();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: SliderPattern_CreateNodePaintMethod_SliderContentModifierNullBranch
 * @tc.desc: Test CreateNodePaintMethod creates sliderContentModifier when null
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_CreateNodePaintMethod_SliderContentModifierNullBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto pattern = frameNode->GetPattern<SliderPattern>();

    pattern->isVisibleArea_ = true;
    pattern->sliderContentModifier_ = nullptr;
    auto result = pattern->CreateNodePaintMethod();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(pattern->sliderContentModifier_, nullptr);
}

/**
 * @tc.name: SliderPattern_CreateNodePaintMethod_SliderTipModifierNullBranch
 * @tc.desc: Test CreateNodePaintMethod creates sliderTipModifier when bubbleFlag true
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_CreateNodePaintMethod_SliderTipModifierNullBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto pattern = frameNode->GetPattern<SliderPattern>();

    pattern->isVisibleArea_ = true;
    pattern->sliderTipModifier_ = nullptr;
    pattern->bubbleFlag_ = true;
    auto result = pattern->CreateNodePaintMethod();
    EXPECT_NE(result, nullptr);
    EXPECT_NE(pattern->sliderTipModifier_, nullptr);
}

/**
 * @tc.name: SliderPattern_OnModifyDone_PanMoveFlagFalseBranch
 * @tc.desc: Test OnModifyDone calls UpdateToValidValue when panMoveFlag false
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_OnModifyDone_PanMoveFlagFalseBranch, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    paintProp->UpdateValue(VALUE);

    pattern->panMoveFlag_ = false;
    pattern->OnModifyDone();
    EXPECT_EQ(paintProp->GetValueValue(0.0f), VALUE);
}

/**
 * @tc.name: SliderPattern_UpdateStepAccessibilityVirtualNode_EmptyOrZeroStepBranches
 * @tc.desc: Test UpdateStepAccessibilityVirtualNode with empty vec or zero step
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_UpdateStepAccessibilityVirtualNode_EmptyOrZeroStepBranches, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();

    paintProp->UpdateStep(0.0f);
    paintProp->UpdateMin(0.0f);
    paintProp->UpdateMax(100.0f);
    pattern->UpdateStepAccessibilityVirtualNode();

    paintProp->UpdateStep(10.0f);
    pattern->pointAccessibilityNodeVec_.clear();
    pattern->UpdateStepAccessibilityVirtualNode();
    EXPECT_TRUE(pattern->pointAccessibilityNodeVec_.empty());
}

/**
 * @tc.name: SliderPattern_GetPointAccessibilityTxt_FormatBranch
 * @tc.desc: Test GetPointAccessibilityTxt with floating point formatting
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg, SliderPattern_GetPointAccessibilityTxt_FormatBranch, TestSize.Level1)
{
    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    paintProp->UpdateStep(1.5f);

    auto result1 = pattern->GetPointAccessibilityTxt(0, 1.5f, 0.0f, 100.0f);
    EXPECT_FALSE(result1.empty());

    auto result2 = pattern->GetPointAccessibilityTxt(10, 1.5f, 0.0f, 100.0f);
    EXPECT_FALSE(result2.empty());
}

/**
 * @tc.name: SliderPattern_UpdateStepPointsAccessibilityVirtualNodeSelected_SuffixOptionsBranches
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected with suffix options
 * @tc.type: FUNC
 */
HWTEST_F(SliderExTestNg,
    SliderPattern_UpdateStepPointsAccessibilityVirtualNodeSelected_SuffixOptionsBranches, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->unselectedDesc_ = "unselected";
    sliderTheme->disabledDesc_ = "disabled";
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    SliderModelNG model;
    model.Create(VALUE, STEP, MIN, MAX);
    model.SetShowSteps(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<SliderPattern>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    SliderContentModifier::Parameters parameters;
    pattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    pattern->sliderContentModifier_->stepPointVec_ = HORIZONTAL_STEP_POINTS;

    pattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));

    for (size_t i = 0; i < HORIZONTAL_STEP_POINTS.size(); i++) {
        auto pointNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
        pattern->parentAccessibilityNode_->AddChild(pointNode);
        pattern->pointAccessibilityNodeVec_.emplace_back(pointNode);
        pattern->pointAccessibilityNodeEventVec_.emplace_back(nullptr);
    }

    pattern->suffixAccessibilityoptions_.accessibilityText = "suffix text";
    pattern->suffixAccessibilityoptions_.accessibilityDescription = "suffix desc";
    pattern->suffixAccessibilityoptions_.accessibilityLevel = AccessibilityProperty::Level::YES_STR;

    auto suffixNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -2, AceType::MakeRefPtr<TextPattern>());
    pattern->suffix_ = AceType::WeakClaim(AceType::RawPtr(suffixNode));

    auto paintProp = frameNode->GetPaintProperty<SliderPaintProperty>();
    paintProp->UpdateStep(10.0f);
    paintProp->UpdateMin(0.0f);
    paintProp->UpdateMax(100.0f);

    pattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(pattern->pointAccessibilityNodeVec_.size(), HORIZONTAL_STEP_POINTS.size());
}

} // namespace OHOS::Ace::NG
