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
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_layout_algorithm.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_model.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components_ng/pattern/slider/slider_model_static.h"
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
constexpr float VALUE = 50.0f;
constexpr float MIN_LABEL = 0.0f;
constexpr float MAX_LABEL = 100.0f;
constexpr bool IS_REVERSE = true;
constexpr Color TEST_COLOR = Color(0XFFFF0000);
constexpr double SLIDER_WIDTH = 20.0;
constexpr double SLIDER_HEIGHT = 30.0;
constexpr Dimension SLIDER_TRACK_THICKNESS = Dimension(10.0);
constexpr Dimension SLIDER_STEP_SIZE = Dimension(0.5);
constexpr Dimension SLIDER_TRACK_BORDER_RADIUS = Dimension(10.0);
constexpr Dimension SLIDER_BLOCK_BORDER_WIDTH = Dimension(5.0);
} // namespace
class SliderStaticTestNg : public testing::Test {
public:
    void TearDown() override;

    static void SetUpTestSuite();
    static void TearDownTestSuite();

private:
    void MockCanvasFunction(Testing::MockCanvas& canvas);
    void MockTipsCanvasFunction(Testing::MockCanvas& canvas);
    void MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas);
};

void SliderStaticTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderStaticTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderStaticTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderStaticTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderStaticTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderStaticTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderStaticTestNg001
 * @tc.desc: test Slider SetThickness with outset style
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetThickness.
     * @tc.expected: step3. the property value meet expectations.
     */
    SliderModelStatic::SetSliderMode(frameNode, SliderModel::SliderMode::OUTSET);
    std::optional<Dimension> thickness = std::nullopt;
    SliderModelStatic::SetThickness(frameNode, thickness);
    EXPECT_EQ(layoutProperty->GetThickness(), std::nullopt);

    thickness = SLIDER_TRACK_THICKNESS;
    SliderModelStatic::SetThickness(frameNode, thickness);
    ASSERT_NE(layoutProperty->GetThickness(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetThickness().value(), SLIDER_TRACK_THICKNESS);
}

/**
 * @tc.name: SliderStaticTestNg002
 * @tc.desc: test Slider SetThickness with inset style
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetThickness.
     * @tc.expected: step3. the property value meet expectations.
     */
    SliderModelStatic::SetSliderMode(frameNode, SliderModel::SliderMode::INSET);
    std::optional<Dimension> thickness = std::nullopt;
    SliderModelStatic::SetThickness(frameNode, thickness);
    EXPECT_EQ(layoutProperty->GetThickness(), std::nullopt);

    thickness = SLIDER_TRACK_THICKNESS;
    SliderModelStatic::SetThickness(frameNode, thickness);
    ASSERT_NE(layoutProperty->GetThickness(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetThickness().value(), SLIDER_TRACK_THICKNESS);
}

/**
 * @tc.name: SliderStaticTestNg003
 * @tc.desc: test Slider SetThickness with none style
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetThickness.
     * @tc.expected: step3. the property value meet expectations.
     */
    SliderModelStatic::SetSliderMode(frameNode, SliderModel::SliderMode::NONE);
    std::optional<Dimension> thickness = std::nullopt;
    SliderModelStatic::SetThickness(frameNode, thickness);
    EXPECT_EQ(layoutProperty->GetThickness(), std::nullopt);

    thickness = SLIDER_TRACK_THICKNESS;
    SliderModelStatic::SetThickness(frameNode, thickness);
    ASSERT_NE(layoutProperty->GetThickness(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetThickness().value(), SLIDER_TRACK_THICKNESS);
}

/**
 * @tc.name: SliderStaticTestNg004
 * @tc.desc: test Slider SetStepSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetStepSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> stepSize = std::nullopt;
    SliderModelStatic::SetStepSize(frameNode, stepSize);
    EXPECT_EQ(paintProperty->GetStepSize(), std::nullopt);

    stepSize = SLIDER_STEP_SIZE;
    SliderModelStatic::SetStepSize(frameNode, stepSize);
    ASSERT_NE(paintProperty->GetStepSize(), std::nullopt);
    EXPECT_EQ(paintProperty->GetStepSize().value(), SLIDER_STEP_SIZE);
}

/**
 * @tc.name: SliderStaticTestNg005
 * @tc.desc: test Slider SetBlockType
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetBlockType.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<SliderModel::BlockStyleType> blockType = std::nullopt;
    SliderModelStatic::SetBlockType(frameNode, blockType);
    EXPECT_EQ(paintProperty->GetBlockType(), std::nullopt);

    blockType = SliderModelNG::BlockStyleType::SHAPE;
    SliderModelStatic::SetBlockType(frameNode, blockType);
    ASSERT_NE(paintProperty->GetBlockType(), std::nullopt);
    EXPECT_EQ(paintProperty->GetBlockType().value(), SliderModelNG::BlockStyleType::SHAPE);
}

/**
 * @tc.name: SliderStaticTestNg006
 * @tc.desc: test Slider SetBlockSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider layoutProperty.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetBlockSize.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> width = std::nullopt;
    std::optional<Dimension> height = std::nullopt;
    SliderModelStatic::SetBlockSize(frameNode, width, height);
    EXPECT_EQ(layoutProperty->GetBlockSize(), std::nullopt);

    width = Dimension(SLIDER_WIDTH);
    height = Dimension(SLIDER_HEIGHT);
    SliderModelStatic::SetBlockSize(frameNode, width, height);
    SizeT<Dimension> blockSize;
    blockSize.SetWidth(Dimension(SLIDER_WIDTH));
    blockSize.SetHeight(Dimension(SLIDER_HEIGHT));
    ASSERT_NE(layoutProperty->GetBlockSize(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetBlockSize().value(), blockSize);
}

/**
 * @tc.name: SliderStaticTestNg007
 * @tc.desc: test Slider SetTrackBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetTrackBorderRadius.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> trackBorderRadius = std::nullopt;
    SliderModelStatic::SetTrackBorderRadius(frameNode, trackBorderRadius);
    EXPECT_EQ(paintProperty->GetTrackBorderRadius(), std::nullopt);

    trackBorderRadius = SLIDER_TRACK_BORDER_RADIUS;
    SliderModelStatic::SetTrackBorderRadius(frameNode, trackBorderRadius);
    ASSERT_NE(paintProperty->GetTrackBorderRadius(), std::nullopt);
    EXPECT_EQ(paintProperty->GetTrackBorderRadius().value(), SLIDER_TRACK_BORDER_RADIUS);
}

/**
 * @tc.name: SliderStaticTestNg008
 * @tc.desc: test Slider SetStepColor
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetStepColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> stepColor = std::nullopt;
    SliderModelStatic::SetStepColor(frameNode, stepColor);
    EXPECT_EQ(paintProperty->GetStepColor(), std::nullopt);

    stepColor = TEST_COLOR;
    SliderModelStatic::SetStepColor(frameNode, stepColor);
    ASSERT_NE(paintProperty->GetStepColor(), std::nullopt);
    EXPECT_EQ(paintProperty->GetStepColor().value(), TEST_COLOR);
}

/**
 * @tc.name: SliderStaticTestNg009
 * @tc.desc: test Slider SetBlockBorderColor
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetBlockBorderColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> blockBorderColor = std::nullopt;
    SliderModelStatic::SetBlockBorderColor(frameNode, blockBorderColor);
    EXPECT_EQ(paintProperty->GetBlockBorderColor(), std::nullopt);

    blockBorderColor = TEST_COLOR;
    SliderModelStatic::SetBlockBorderColor(frameNode, blockBorderColor);
    ASSERT_NE(paintProperty->GetBlockBorderColor(), std::nullopt);
    EXPECT_EQ(paintProperty->GetBlockBorderColor().value(), TEST_COLOR);
}

/**
 * @tc.name: SliderStaticTestNg010
 * @tc.desc: test Slider SetBlockBorderWidth
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetBlockBorderWidth.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Dimension> blockBorderWidth = std::nullopt;
    SliderModelStatic::SetBlockBorderWidth(frameNode, blockBorderWidth);
    EXPECT_EQ(paintProperty->GetBlockBorderWidth(), std::nullopt);

    blockBorderWidth = SLIDER_BLOCK_BORDER_WIDTH;
    SliderModelStatic::SetBlockBorderWidth(frameNode, blockBorderWidth);
    ASSERT_NE(paintProperty->GetBlockBorderWidth(), std::nullopt);
    EXPECT_EQ(paintProperty->GetBlockBorderWidth().value(), SLIDER_BLOCK_BORDER_WIDTH);
}

/**
 * @tc.name: SliderStaticTestNg011
 * @tc.desc: test Slider SetBlockColor
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetBlockColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> blockColor = std::nullopt;
    SliderModelStatic::SetBlockColor(frameNode, blockColor);
    EXPECT_EQ(paintProperty->GetBlockColor(), std::nullopt);

    blockColor = TEST_COLOR;
    SliderModelStatic::SetBlockColor(frameNode, blockColor);
    ASSERT_NE(paintProperty->GetBlockColor(), std::nullopt);
    EXPECT_EQ(paintProperty->GetBlockColor().value(), TEST_COLOR);
}

/**
 * @tc.name: SliderStaticTestNg012
 * @tc.desc: test Slider SetTrackBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetTrackBackgroundColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Gradient> gradient = std::nullopt;
    SliderModelStatic::SetTrackBackgroundColor(frameNode, gradient, false);
    EXPECT_EQ(paintProperty->GetTrackBackgroundColor(), std::nullopt);

    Gradient defaultGradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::WHITE));
    gradientColor1.SetDimension(Dimension(0.0));
    defaultGradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(0.5));
    defaultGradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor(Color::BLUE));
    gradientColor3.SetDimension(Dimension(1.0));
    defaultGradient.AddColor(gradientColor3);
    std::vector<GradientColor> defaultGradientColors = defaultGradient.GetColors();

    gradient = defaultGradient;
    SliderModelStatic::SetTrackBackgroundColor(frameNode, gradient, false);
    std::optional<Gradient> testGradient = paintProperty->GetTrackBackgroundColor();
    ASSERT_NE(testGradient, std::nullopt);
    std::vector<GradientColor> testGradientColors = testGradient.value().GetColors();

    ASSERT_EQ(defaultGradientColors.size(), testGradientColors.size());
    EXPECT_EQ(defaultGradientColors.at(0).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(0).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(1).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(1).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(2).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(2).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(0).GetDimension(), testGradientColors.at(0).GetDimension());
    EXPECT_EQ(defaultGradientColors.at(1).GetDimension(), testGradientColors.at(1).GetDimension());
    EXPECT_EQ(defaultGradientColors.at(2).GetDimension(), testGradientColors.at(2).GetDimension());
}

/**
 * @tc.name: SliderStaticTestNg013
 * @tc.desc: test Slider SetSelectColor
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelectColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> selectColor = std::nullopt;
    SliderModelStatic::SetSelectColor(frameNode, selectColor);
    EXPECT_EQ(paintProperty->GetSelectColor(), std::nullopt);

    selectColor = TEST_COLOR;
    SliderModelStatic::SetSelectColor(frameNode, selectColor);
    ASSERT_NE(paintProperty->GetSelectColor(), std::nullopt);
    EXPECT_EQ(paintProperty->GetSelectColor().value(), TEST_COLOR);
}

/**
 * @tc.name: SliderStaticTestNg014
 * @tc.desc: test Slider SetSelectColor with gradient
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSelectColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Gradient> gradient = std::nullopt;
    SliderModelStatic::SetSelectColor(frameNode, gradient, false);
    EXPECT_EQ(paintProperty->GetSelectColor(), std::nullopt);

    Gradient defaultGradient;
    GradientColor gradientColor1;
    gradientColor1.SetLinearColor(LinearColor(Color::WHITE));
    gradientColor1.SetDimension(Dimension(0.0));
    defaultGradient.AddColor(gradientColor1);
    GradientColor gradientColor2;
    gradientColor2.SetLinearColor(LinearColor(Color::RED));
    gradientColor2.SetDimension(Dimension(0.5));
    defaultGradient.AddColor(gradientColor2);
    GradientColor gradientColor3;
    gradientColor3.SetLinearColor(LinearColor(Color::BLUE));
    gradientColor3.SetDimension(Dimension(1.0));
    defaultGradient.AddColor(gradientColor3);
    std::vector<GradientColor> defaultGradientColors = defaultGradient.GetColors();

    gradient = defaultGradient;
    SliderModelStatic::SetSelectColor(frameNode, gradient, false);
    std::optional<Gradient> testGradient = paintProperty->GetSelectGradientColor();
    ASSERT_NE(testGradient, std::nullopt);
    std::vector<GradientColor> testGradientColors = testGradient.value().GetColors();

    ASSERT_EQ(defaultGradientColors.size(), testGradientColors.size());
    EXPECT_EQ(defaultGradientColors.at(0).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(0).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(1).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(1).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(2).GetLinearColor().ToColor().GetValue(),
    testGradientColors.at(2).GetLinearColor().ToColor().GetValue());
    EXPECT_EQ(defaultGradientColors.at(0).GetDimension(), testGradientColors.at(0).GetDimension());
    EXPECT_EQ(defaultGradientColors.at(1).GetDimension(), testGradientColors.at(1).GetDimension());
    EXPECT_EQ(defaultGradientColors.at(2).GetDimension(), testGradientColors.at(2).GetDimension());
}

/**
 * @tc.name: SliderStaticTestNg015
 * @tc.desc: test Slider SetSliderInteractionMode
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSliderInteractionMode.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<SliderModel::SliderInteraction> sliderInteractionMode = std::nullopt;
    SliderModelStatic::SetSliderInteractionMode(frameNode, sliderInteractionMode);
    EXPECT_EQ(paintProperty->GetSliderInteractionMode(), std::nullopt);

    sliderInteractionMode = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK;
    SliderModelStatic::SetSliderInteractionMode(frameNode, sliderInteractionMode);
    ASSERT_NE(paintProperty->GetSliderInteractionMode(), std::nullopt);
    EXPECT_EQ(paintProperty->GetSliderInteractionMode().value(), SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
}

/**
 * @tc.name: SliderStaticTestNg016
 * @tc.desc: test Slider SetSliderValue
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSliderValue.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<float> sliderValue = std::nullopt;
    SliderModelStatic::SetSliderValue(frameNode, sliderValue);
    EXPECT_EQ(paintProperty->GetValue(), 0.0f);

    sliderValue = VALUE;
    SliderModelStatic::SetSliderValue(frameNode, sliderValue);
    ASSERT_NE(paintProperty->GetValue(), std::nullopt);
    EXPECT_EQ(paintProperty->GetValue().value(), VALUE);
}

/**
 * @tc.name: SliderStaticTestNg017
 * @tc.desc: test Slider SetMinLabel
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetMinLabel.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<float> minLabel = std::nullopt;
    SliderModelStatic::SetMinLabel(frameNode, minLabel);
    EXPECT_EQ(paintProperty->GetMin(), std::nullopt);

    minLabel = MIN_LABEL;
    SliderModelStatic::SetMinLabel(frameNode, minLabel);
    ASSERT_NE(paintProperty->GetMin(), std::nullopt);
    EXPECT_EQ(paintProperty->GetMin().value(), MIN_LABEL);
}

/**
 * @tc.name: SliderStaticTestNg018
 * @tc.desc: test Slider SetMaxLabel
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetMaxLabel.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<float> maxLabel = std::nullopt;
    SliderModelStatic::SetMaxLabel(frameNode, maxLabel);
    EXPECT_EQ(paintProperty->GetMax(), std::nullopt);

    maxLabel = MAX_LABEL;
    SliderModelStatic::SetMaxLabel(frameNode, maxLabel);
    ASSERT_NE(paintProperty->GetMax(), std::nullopt);
    EXPECT_EQ(paintProperty->GetMax().value(), MAX_LABEL);
}

/**
 * @tc.name: SliderStaticTestNg019
 * @tc.desc: test Slider SetSliderMode
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty and layoutProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetSliderMode.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<SliderModel::SliderMode> sliderMode = std::nullopt;
    SliderModelStatic::SetSliderMode(frameNode, sliderMode);
    EXPECT_EQ(paintProperty->GetSliderMode(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetSliderMode(), std::nullopt);

    sliderMode = SliderModelNG::SliderMode::OUTSET;
    SliderModelStatic::SetSliderMode(frameNode, sliderMode);
    ASSERT_NE(paintProperty->GetSliderMode(), std::nullopt);
    ASSERT_NE(layoutProperty->GetSliderMode(), std::nullopt);
    EXPECT_EQ(paintProperty->GetSliderMode().value(), SliderModelNG::SliderMode::OUTSET);
    EXPECT_EQ(layoutProperty->GetSliderMode().value(), SliderModelNG::SliderMode::OUTSET);
}

/**
 * @tc.name: SliderStaticTestNg020
 * @tc.desc: test Slider SetDirection
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty and layoutProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetDirection.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Axis> direction = std::nullopt;
    SliderModelStatic::SetDirection(frameNode, direction);
    EXPECT_EQ(paintProperty->GetDirection(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetDirection(), std::nullopt);

    direction = Axis::VERTICAL;
    SliderModelStatic::SetDirection(frameNode, direction);
    ASSERT_NE(paintProperty->GetDirection(), std::nullopt);
    ASSERT_NE(layoutProperty->GetDirection(), std::nullopt);
    EXPECT_EQ(paintProperty->GetDirection().value(), Axis::VERTICAL);
    EXPECT_EQ(layoutProperty->GetDirection().value(), Axis::VERTICAL);
}

/**
 * @tc.name: SliderStaticTestNg021
 * @tc.desc: test Slider SetReverse
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty and layoutProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. test SetReverse.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<bool> direction = std::nullopt;
    SliderModelStatic::SetReverse(frameNode, direction);
    EXPECT_EQ(paintProperty->GetReverse(), std::nullopt);
    EXPECT_EQ(layoutProperty->GetReverse(), std::nullopt);

    direction = IS_REVERSE;
    SliderModelStatic::SetReverse(frameNode, direction);
    ASSERT_NE(paintProperty->GetReverse(), std::nullopt);
    ASSERT_NE(layoutProperty->GetReverse(), std::nullopt);
    EXPECT_EQ(paintProperty->GetReverse().value(), IS_REVERSE);
    EXPECT_EQ(layoutProperty->GetReverse().value(), IS_REVERSE);
}

/**
 * @tc.name: SliderStaticTestNg022
 * @tc.desc: test Slider ResetShowTips && ResetShowSteps
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, SliderStaticTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider frameNode.
     */
    auto node = SliderModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::SLIDER_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create slider paintProperty.
     */
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. test ResetShowTips && ResetShowSteps .
     * @tc.expected: step3. the property value meet expectations.
     */
    SliderModelStatic::ResetShowTips(frameNode);
    SliderModelStatic::ResetShowSteps(frameNode);
    EXPECT_FALSE(paintProperty->GetShowSteps());
    EXPECT_FALSE(paintProperty->GetShowTips());
}

/**
 * @tc.name: ResetTrackBackgroundColorTest001
 * @tc.desc: Test Slider ResetTrackBackgroundColor
 * Decrease Slider BackgroundColor to theme color
 * @tc.type: FUNC
 */
HWTEST_F(SliderStaticTestNg, ResetTrackBackgroundColorTest001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    Color testColor = Color::RED;
    sliderTheme->trackBgColor_ = testColor;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));

    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderModelStatic::ResetTrackBackgroundColor(AceType::RawPtr(frameNode));
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto gradientOpt = paintProperty->GetTrackBackgroundColor();
    ASSERT_TRUE(gradientOpt.has_value());
    Gradient expectedGradient = SliderModelNG::CreateSolidGradient(testColor);
    EXPECT_EQ(gradientOpt.value(), expectedGradient);
    EXPECT_TRUE(paintProperty->GetTrackBackgroundIsResourceColor());
}
} // namespace OHOS::Ace::NG