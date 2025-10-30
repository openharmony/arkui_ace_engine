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
const Color TEST_COLOR = Color::BLUE;
constexpr float MAX_WIDTH = 500.0f;
constexpr float MAX_HEIGHT = 500.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
constexpr float SLIDER_WIDTH = 10.0f;
constexpr float SLIDER_HEIGHT = 20.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
constexpr float SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL = 8.0f;
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
constexpr float BLOCK_LINEAR_GRADIENT_COLOR_OFFSET_STARE = 0.0f;
constexpr float BLOCK_LINEAR_GRADIENT_COLOR_OFFSET_BETWEEN = 0.5f;
constexpr float BLOCK_LINEAR_GRADIENT_COLOR_OFFSET_END = 1.0f;
} // namespace
class SliderModifierTwoTestNg : public testing::Test {
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
    Gradient CreateLinearGradientBlockColor();
};

Gradient SliderModifierTwoTestNg::CreateLinearGradientBlockColor()
{
    Gradient gradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::WHITE));
    gradientColor1.SetDimension(Dimension(BLOCK_LINEAR_GRADIENT_COLOR_OFFSET_STARE));
    gradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(BLOCK_LINEAR_GRADIENT_COLOR_OFFSET_BETWEEN));
    gradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor(Color::BLUE));
    gradientColor3.SetDimension(Dimension(BLOCK_LINEAR_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(gradientColor3);
    return gradient;
}

void SliderModifierTwoTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderModifierTwoTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderModifierTwoTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
}

void SliderModifierTwoTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderModifierTwoTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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

void SliderModifierTwoTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderModifierTwoTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderModifierTwoTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderContentModifierTest048
 * @tc.desc: TEST slider_content_modifier DrawBlockShapePath
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTwoTestNg, SliderContentModifierTest048, TestSize.Level1)
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
    SliderContentModifier sliderContentModifier(parameters, nullptr);
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
    ASSERT_NE(path, nullptr);
    Gradient gradient = CreateLinearGradientBlockColor();
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetLinearGradientBlockColor(gradient);
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapePath(context, path);

    Gradient gradient3 = sliderContentModifier.blockGradientColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors3 = gradient3.GetColors();
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors3[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors3[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors3[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors3[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors3[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors3[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest049
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeRect
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTwoTestNg, SliderContentModifierTest049, TestSize.Level1)
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
    SliderContentModifier sliderContentModifier(parameters, nullptr);
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
    ASSERT_NE(rect, nullptr);
    Gradient gradient = CreateLinearGradientBlockColor();
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetLinearGradientBlockColor(gradient);
    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    Gradient gradient3 = sliderContentModifier.blockGradientColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors3 = gradient3.GetColors();
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors3[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors3[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors3[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors3[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors3[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors3[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest050
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeRect
 * direction = HORIZONTAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTwoTestNg, SliderContentModifierTest050, TestSize.Level1)
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
    SliderContentModifier sliderContentModifier(parameters, nullptr);
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
    ASSERT_NE(rect, nullptr);
    Gradient gradient = CreateLinearGradientBlockColor();
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetLinearGradientBlockColor(gradient);
    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.DrawBlockShapeRect(context, rect);
    Gradient gradient3 = sliderContentModifier.blockGradientColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors3 = gradient3.GetColors();
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors3[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors3[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors3[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors3[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors3[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors3[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest051
 * @tc.desc: TEST SliderContentModifier DrawDefaultBlock
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTwoTestNg, SliderContentModifierTest051, TestSize.Level1)
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
    SliderContentModifier sliderContentModifier(parameters, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call DrawDefaultBlock function.
     */
    Gradient gradient = CreateLinearGradientBlockColor();
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetLinearGradientBlockColor(gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.reverse_ = true;
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL);
    sliderContentModifier.DrawDefaultBlock(context);

    Gradient gradient3 = sliderContentModifier.blockGradientColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors3 = gradient3.GetColors();
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors3[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors3[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors3[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors3[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors3[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors3[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest052
 * @tc.desc: TEST SliderContentModifier DrawDefaultBlock
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTwoTestNg, SliderContentModifierTest052, TestSize.Level1)
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
    SliderContentModifier sliderContentModifier(parameters, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call DrawDefaultBlock function.
     */
    Gradient gradient = CreateLinearGradientBlockColor();
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetLinearGradientBlockColor(gradient);
    sliderContentModifier.reverse_ = true;
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.SetBlockBorderWidth(SLIDER_CONTENT_MODIFIER_BLOCK_BORDER_WIDTH_SMALL);
    sliderContentModifier.DrawDefaultBlock(context);

    Gradient gradient3 = sliderContentModifier.blockGradientColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors3 = gradient3.GetColors();
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors3[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors3[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors3[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors3[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors3[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors3[2].GetDimension());
}

/**
 * @tc.name: SliderContentModifierTest053
 * @tc.desc: TEST slider_content_modifier DrawBlockShapeCircle
 * direction = VERTICAL, blockType = SHAPE, blockShape = CIRCLE, sliderMode = INSET
 * @tc.type: FUNC
 */
HWTEST_F(SliderModifierTwoTestNg, SliderContentModifierTest053, TestSize.Level1)
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
    SliderContentModifier sliderContentModifier(parameters, nullptr);
    /**
     * @tc.steps: step2. set sliderContentModifier attribute and call onDraw function.
     */
    sliderContentModifier.SetDirection(Axis::VERTICAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    sliderContentModifier.SetBlockShape(basicShape);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::INSET);

    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_WIDTH, SLIDER_HEIGHT };
    Gradient gradient = CreateLinearGradientBlockColor();
    std::vector<GradientColor> gradientColors = gradient.GetColors();
    sliderContentModifier.SetLinearGradientBlockColor(gradient);
    auto circle = AccessibilityManager::DynamicCast<Circle>(sliderContentModifier.shape_);
    ASSERT_NE(circle, nullptr);
    sliderContentModifier.shapeWidth_->Set(1.0f);
    sliderContentModifier.SetBlockSize(BLOCK_SIZE_F);
    sliderContentModifier.shapeHeight_->Set(1.0f);
    sliderContentModifier.DrawBlockShapeCircle(context, circle);
    Gradient gradient3 = sliderContentModifier.blockGradientColor_->Get().GetGradient();
    std::vector<GradientColor> gradientColors3 = gradient3.GetColors();
    EXPECT_EQ(gradientColors[0].GetLinearColor(), gradientColors3[0].GetLinearColor());
    EXPECT_EQ(gradientColors[1].GetLinearColor(), gradientColors3[1].GetLinearColor());
    EXPECT_EQ(gradientColors[2].GetLinearColor(), gradientColors3[2].GetLinearColor());
    EXPECT_EQ(gradientColors[0].GetDimension(), gradientColors3[0].GetDimension());
    EXPECT_EQ(gradientColors[1].GetDimension(), gradientColors3[1].GetDimension());
    EXPECT_EQ(gradientColors[2].GetDimension(), gradientColors3[2].GetDimension());
}
} // namespace OHOS::Ace::NG
