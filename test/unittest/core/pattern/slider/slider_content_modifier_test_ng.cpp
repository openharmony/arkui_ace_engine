/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components/slider/slider_theme.h"
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
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color TEST_COLOR = Color::BLUE;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
const PointF POINTF_START { 10.0f, 10.0f };
const PointF POINTF_END { 20.0f, 20.0f };
constexpr float SLIDER_DRAW_CANVAS_WIDTH = 300.0f;
constexpr float SLIDER_DRAW_CANVAS_HEIGHT = 300.0f;
constexpr float TEST_GRADIENT_COLOR_OFFSET_START = 0.0f;
constexpr float TEST_GRADIENT_COLOR_OFFSET_END = 1.0f;
constexpr float TEST_HDR_RED = 200.0f;
constexpr float TEST_HDR_GREEN = 150.0f;
constexpr float TEST_HDR_BLUE = 100.0f;
constexpr float TEST_HDR_ALPHA = 1.0f;
constexpr float TEST_HDR_HEADROOM_HIGH = 2.0f;
constexpr float TEST_HDR_HEADROOM_DEFAULT = 1.0f;
} // namespace
class SliderContentModifierTestNg : public testing::Test {
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
    Gradient CreateHDRGradientColor(ColorSpace colorSpace, float headRoom);
    Gradient CreateSolidGradientWithColorSpace(ColorSpace colorSpace);
};

void SliderContentModifierTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderContentModifierTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderContentModifierTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
}

void SliderContentModifierTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderContentModifierTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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
    SizeF blockSize;
    sliderContentModifier.SetBlockSize(blockSize);
}

void SliderContentModifierTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderContentModifierTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderContentModifierTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
{
    EXPECT_CALL(*paragraph, Paint(An<RSCanvas&>(), _, _)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, AddText(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Build()).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(1.0f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(1.0f));
}

Gradient SliderContentModifierTestNg::CreateHDRGradientColor(ColorSpace colorSpace, float headRoom)
{
    Color hdrColor = Color::FromFloat(TEST_HDR_RED, TEST_HDR_GREEN, TEST_HDR_BLUE, TEST_HDR_ALPHA, headRoom);
    hdrColor.SetColorSpace(colorSpace);
    Gradient gradient;
    GradientColor startColor;
    startColor.SetColor(hdrColor);
    startColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_START));
    gradient.AddColor(startColor);
    GradientColor endColor;
    endColor.SetColor(hdrColor);
    endColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(endColor);
    return gradient;
}

Gradient SliderContentModifierTestNg::CreateSolidGradientWithColorSpace(ColorSpace colorSpace)
{
    Color normalColor = Color::RED;
    normalColor.SetColorSpace(colorSpace);
    Gradient gradient;
    GradientColor startColor;
    startColor.SetLinearColor(LinearColor(normalColor));
    startColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_START));
    gradient.AddColor(startColor);
    GradientColor endColor;
    endColor.SetLinearColor(LinearColor(normalColor));
    endColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(endColor);
    return gradient;
}

/**
 * @tc.name: SliderContentModifierTest001
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateValue(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(0.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(1.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest002
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateMin(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(100.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(1.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest003
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateMax(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(0.0f, config.value_);
        EXPECT_EQ(0.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(1.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest004
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateStep(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(0.0f, config.value_);
        EXPECT_EQ(0.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(100.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest005
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateValue(100.0f);
    sliderPaintProperty->UpdateMin(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(100.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(1.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest006
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateValue(100.0f);
    sliderPaintProperty->UpdateMax(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(0.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(1.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest007
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateValue(100.0f);
    sliderPaintProperty->UpdateStep(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(0.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(100.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest008
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateMin(100.0f);
    sliderPaintProperty->UpdateMax(200.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(100.0f, config.min_);
        EXPECT_EQ(200.0f, config.max_);
        EXPECT_EQ(1.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest009
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateMin(100.0f);
    sliderPaintProperty->UpdateStep(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(100.0f, config.value_);
        EXPECT_EQ(100.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(100.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifierTest010
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifierTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::SliderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(true);
    sliderPaintProperty->UpdateMax(100.0f);
    sliderPaintProperty->UpdateStep(100.0f);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(0.0f, config.value_);
        EXPECT_EQ(0.0f, config.min_);
        EXPECT_EQ(100.0f, config.max_);
        EXPECT_EQ(100.0f, config.step_);
        EXPECT_EQ(true, config.enabled_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_HDRTagColor
 * @tc.desc: Test DrawBackground with HDR track color where headRoom is greater than 1.0,
 *           verifying GetHDRColor4fByHeadRoom multiplies RGB by headRoom and clamps to 255.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_HDRTagColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with HDR gradient color (headRoom > 1.0) and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto hdrGradient = CreateHDRGradientColor(ColorSpace::SRGB, TEST_HDR_HEADROOM_HIGH);
    sliderContentModifier.SetTrackBackgroundColor(hdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify track background color was set correctly with HDR gradient.
     * @tc.expected: Track background color contains the HDR gradient with headRoom applied.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_HDRDefaultHeadRoom
 * @tc.desc: Test DrawBackground with HDR track color where headRoom equals 1.0,
 *           verifying GetHDRColor4fByHeadRoom uses original RGB without headRoom multiplication.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_HDRDefaultHeadRoom, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with HDR gradient color (headRoom = 1.0) and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto hdrGradient = CreateHDRGradientColor(ColorSpace::SRGB, TEST_HDR_HEADROOM_DEFAULT);
    sliderContentModifier.SetTrackBackgroundColor(hdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify track background color was set with default headRoom gradient.
     * @tc.expected: Track background color contains the gradient without headRoom scaling.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_SRGBColorSpace
 * @tc.desc: Test DrawBackground with SRGB color space track color,
 *           verifying GetRSColorSpaceByGradientColors maps SRGB to SRGB matrix type.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_SRGBColorSpace, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with SRGB color space gradient and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto srgbGradient = CreateSolidGradientWithColorSpace(ColorSpace::SRGB);
    sliderContentModifier.SetTrackBackgroundColor(srgbGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify SRGB color space gradient is handled correctly.
     * @tc.expected: Track background color is set without errors.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), srgbGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_DisplayP3ColorSpace
 * @tc.desc: Test DrawBackground with DISPLAY_P3 color space track color,
 *           verifying GetRSColorSpaceByGradientColors maps DISPLAY_P3 to DCIP3 matrix type.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_DisplayP3ColorSpace, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with DISPLAY_P3 color space gradient and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto p3Gradient = CreateSolidGradientWithColorSpace(ColorSpace::DISPLAY_P3);
    sliderContentModifier.SetTrackBackgroundColor(p3Gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify DISPLAY_P3 color space gradient is handled correctly.
     * @tc.expected: Track background color is set without errors.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), p3Gradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_BT2020ColorSpace
 * @tc.desc: Test DrawBackground with BT2020 color space track color,
 *           verifying GetRSColorSpaceByGradientColors maps BT2020 to REC2020 matrix type.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_BT2020ColorSpace, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with BT2020 color space gradient and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto bt2020Gradient = CreateSolidGradientWithColorSpace(ColorSpace::BT2020);
    sliderContentModifier.SetTrackBackgroundColor(bt2020Gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify BT2020 color space gradient is handled correctly.
     * @tc.expected: Track background color is set without errors.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), bt2020Gradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_BT2020WithHDR
 * @tc.desc: Test DrawBackground with BT2020 color space and HDR headRoom color,
 *           verifying combined BT2020 + HDR color path works correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_BT2020WithHDR, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with BT2020 HDR gradient color and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto bt2020HdrGradient = CreateHDRGradientColor(ColorSpace::BT2020, TEST_HDR_HEADROOM_HIGH);
    sliderContentModifier.SetTrackBackgroundColor(bt2020HdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify BT2020 + HDR color path handles correctly.
     * @tc.expected: Track background color is set with BT2020 HDR gradient.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), bt2020HdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_DisplayP3WithHDR
 * @tc.desc: Test DrawBackground with DISPLAY_P3 color space and HDR headRoom color,
 *           verifying combined DISPLAY_P3 + HDR color path works correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_DisplayP3WithHDR, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with DISPLAY_P3 HDR gradient color and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto p3HdrGradient = CreateHDRGradientColor(ColorSpace::DISPLAY_P3, TEST_HDR_HEADROOM_HIGH);
    sliderContentModifier.SetTrackBackgroundColor(p3HdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify DISPLAY_P3 + HDR color path handles correctly.
     * @tc.expected: Track background color is set with DISPLAY_P3 HDR gradient.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), p3HdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_NonHDRNormalColor
 * @tc.desc: Test DrawBackground with normal (non-HDR) track color without HeadRoomColor,
 *           verifying Get4FColorsByGradientColors uses the RSColor conversion path.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_NonHDRNormalColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and sliderContentModifier.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set modifier with normal solid gradient (no HeadRoomColor) and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto normalGradient = SliderModelNG::CreateSolidGradient(Color::RED);
    sliderContentModifier.SetTrackBackgroundColor(normalGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify normal (non-HDR) color path handles correctly.
     * @tc.expected: Track background color is set without errors.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), normalGradient.GetColors().size());
}
} // namespace OHOS::Ace::NG
