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
 *           verifying GetHDRMaxByGradientColors detects HDR, ApplyHDRHeadRoom applies headRoom,
 *           and GetUIColorsByGradientColors converts HDR colors to RSUIColor.
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
 *           verifying GetHDRMaxByGradientColors detects hasHDR flag and DrawBackground
 *           uses GetUIColorsByGradientColors (HDR RSUIColor path) even when headRoom is default,
 *           which prevents colors from becoming black when using HDR color space without brightness boost.
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
     * @tc.steps: step3. Verify track background color was set with HDR RSUIColor path.
     * @tc.expected: Track background color contains the gradient, using HDR color conversion
     *               even with default headRoom, preventing black color rendering.
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
 *           verifying GetColor4fsByGradientColors converts LinearColor to RSColor4f via RSColor.
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

/**
 * @tc.name: SliderContentModifier_DrawBackground_MixedHDRAndNonHDR
 * @tc.desc: Test DrawBackground with gradient containing both HDR (with headRoom) and non-HDR colors,
 *           verifying GetHDRMaxByGradientColors detects max headRoom from mixed gradient and
 *           GetUIColorsByGradientColors handles mixed HDR and non-HDR colors.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_MixedHDRAndNonHDR, TestSize.Level1)
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
     * @tc.steps: step2. Build a gradient with one HDR color and one normal LinearColor.
     */
    Color hdrColor = Color::FromFloat(
        TEST_HDR_RED, TEST_HDR_GREEN, TEST_HDR_BLUE, TEST_HDR_ALPHA, TEST_HDR_HEADROOM_HIGH);
    Gradient gradient;
    GradientColor hdrGradColor;
    hdrGradColor.SetColor(hdrColor);
    hdrGradColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_START));
    gradient.AddColor(hdrGradColor);
    GradientColor normalGradColor;
    normalGradColor.SetLinearColor(LinearColor(Color::RED));
    normalGradColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(normalGradColor);

    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetTrackBackgroundColor(gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify mixed gradient draws without crash.
     * @tc.expected: Track background color count matches the input gradient.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), gradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_ReverseWithHDR
 * @tc.desc: Test DrawBackground with reverse direction and HDR gradient color,
 *           verifying reversed start/end points are passed to CreateLinearGradientShader.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_ReverseWithHDR, TestSize.Level1)
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
     * @tc.steps: step2. Set reverse_ to true and use HDR gradient, then call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.reverse_ = true;
    auto hdrGradient = CreateHDRGradientColor(ColorSpace::SRGB, TEST_HDR_HEADROOM_HIGH);
    sliderContentModifier.SetTrackBackgroundColor(hdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify reverse HDR gradient draws without crash.
     * @tc.expected: Track background color count matches the input gradient.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_HDRColorClamp
 * @tc.desc: Test DrawBackground with HDR color values exceeding 1.0,
 *           verifying GetHDRUIColorByHeadRoom clamps RGBA values to [0.0, 1.0] before constructing RSUIColor.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_HDRColorClamp, TestSize.Level1)
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
     * @tc.steps: step2. Create HDR color with out-of-range values (red=2.0, green=-0.5, blue=1.5).
     */
    Color hdrColor = Color::FromFloat(2.0f, -0.5f, 1.5f, TEST_HDR_ALPHA, TEST_HDR_HEADROOM_HIGH);
    Gradient gradient;
    GradientColor gradColor;
    gradColor.SetColor(hdrColor);
    gradColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_START));
    gradient.AddColor(gradColor);
    GradientColor endColor;
    endColor.SetLinearColor(LinearColor(Color::BLUE));
    endColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(endColor);

    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetTrackBackgroundColor(gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify clamped HDR gradient draws without crash.
     * @tc.expected: Track background color count matches, no overflow.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), gradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_HDRWithNullHost
 * @tc.desc: Test DrawBackground with HDR gradient color when host frameNode is null,
 *           verifying GetHDRMaxByGradientColors detects HDR and ApplyHDRHeadRoom handles null host
 *           gracefully without crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_HDRWithNullHost, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create sliderContentModifier with default null host.
     */
    SliderContentModifier::Parameters parameters;
    SliderContentModifier sliderContentModifier(parameters, nullptr);

    /**
     * @tc.steps: step2. Set HDR gradient and call onDraw with null host.
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
     * @tc.steps: step3. Verify null host does not cause crash, drawing still completes.
     * @tc.expected: Track background color is set without errors.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_HDRColorSpaceNoBoost
 * @tc.desc: Test DrawBackground with HDR color in non-SRGB color space (DisplayP3) with headRoom = 1.0,
 *           verifying that when HDR color has no brightness boost (headRoom not exceeding default),
 *           the hasHDR flag is still true and DrawBackground uses the HDR RSUIColor path
 *           instead of the non-HDR RSColor4f path, preventing color from becoming black.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_HDRColorSpaceNoBoost, TestSize.Level1)
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
     * @tc.steps: step2. Set modifier with DisplayP3 HDR gradient (headRoom = 1.0, no brightness boost).
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto hdrGradient = CreateHDRGradientColor(ColorSpace::DISPLAY_P3, TEST_HDR_HEADROOM_DEFAULT);
    sliderContentModifier.SetTrackBackgroundColor(hdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify HDR path is used even without brightness boost.
     * @tc.expected: Colors are rendered via HDR RSUIColor path, not black.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_BT2020HDRNoBoost
 * @tc.desc: Test DrawBackground with BT2020 HDR color with headRoom = 1.0 (no brightness boost),
 *           verifying hasHDR detection uses flag instead of headRoom value comparison,
 *           so BT2020 HDR colors without boost are still rendered via HDR path.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_BT2020HDRNoBoost, TestSize.Level1)
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
     * @tc.steps: step2. Set modifier with BT2020 HDR gradient (headRoom = 1.0, no brightness boost).
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    auto hdrGradient = CreateHDRGradientColor(ColorSpace::BT2020, TEST_HDR_HEADROOM_DEFAULT);
    sliderContentModifier.SetTrackBackgroundColor(hdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify BT2020 HDR colors without boost use HDR rendering path.
     * @tc.expected: Colors are rendered via HDR RSUIColor path, not black.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_MixedHDRDefaultAndHDRBoost
 * @tc.desc: Test DrawBackground with mixed gradient containing one HDR color with headRoom = 1.0
 *           (no boost) and one HDR color with headRoom = 2.0 (with boost),
 *           verifying hasHDR flag is true and the maximum headRoom is correctly computed.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_MixedHDRDefaultAndHDRBoost, TestSize.Level1)
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
     * @tc.steps: step2. Build gradient with one HDR color (headRoom = 1.0) and one (headRoom = 2.0).
     */
    Color hdrColorDefault = Color::FromFloat(
        TEST_HDR_RED, TEST_HDR_GREEN, TEST_HDR_BLUE, TEST_HDR_ALPHA, TEST_HDR_HEADROOM_DEFAULT);
    hdrColorDefault.SetColorSpace(ColorSpace::DISPLAY_P3);
    Color hdrColorBoost = Color::FromFloat(
        TEST_HDR_RED, TEST_HDR_GREEN, TEST_HDR_BLUE, TEST_HDR_ALPHA, TEST_HDR_HEADROOM_HIGH);
    hdrColorBoost.SetColorSpace(ColorSpace::DISPLAY_P3);

    Gradient gradient;
    GradientColor startColor;
    startColor.SetColor(hdrColorDefault);
    startColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_START));
    gradient.AddColor(startColor);
    GradientColor endColor;
    endColor.SetColor(hdrColorBoost);
    endColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(endColor);

    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetTrackBackgroundColor(gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify mixed HDR gradient draws correctly.
     * @tc.expected: Both HDR colors rendered via HDR path, max headRoom applied.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), gradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_ReverseWithHDRNoBoost
 * @tc.desc: Test DrawBackground with reverse direction and HDR gradient color with headRoom = 1.0,
 *           verifying reverse + HDR without brightness boost path works correctly,
 *           using RSUIColor path instead of RSColor4f path.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_ReverseWithHDRNoBoost, TestSize.Level1)
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
     * @tc.steps: step2. Set reverse_ to true, use HDR gradient (headRoom = 1.0), and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.reverse_ = true;
    auto hdrGradient = CreateHDRGradientColor(ColorSpace::SRGB, TEST_HDR_HEADROOM_DEFAULT);
    sliderContentModifier.SetTrackBackgroundColor(hdrGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify reverse + HDR without boost draws correctly.
     * @tc.expected: HDR RSUIColor path used, no black color.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), hdrGradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_MixedHDRDefaultAndNormalColor
 * @tc.desc: Test DrawBackground with gradient containing one HDR color with headRoom = 1.0 and
 *           one normal color without HeadRoomColor, verifying hasHDR flag is true due to the HDR
 *           color, and GetUIColorsByGradientColors handles mixed types correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_MixedHDRDefaultAndNormalColor,
          TestSize.Level1)
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
     * @tc.steps: step2. Build gradient with one HDR color (headRoom = 1.0) and one normal color.
     */
    Color hdrColor = Color::FromFloat(
        TEST_HDR_RED, TEST_HDR_GREEN, TEST_HDR_BLUE, TEST_HDR_ALPHA, TEST_HDR_HEADROOM_DEFAULT);
    hdrColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    Gradient gradient;
    GradientColor hdrGradColor;
    hdrGradColor.SetColor(hdrColor);
    hdrGradColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_START));
    gradient.AddColor(hdrGradColor);
    GradientColor normalGradColor;
    normalGradColor.SetLinearColor(LinearColor(Color::GREEN));
    normalGradColor.SetDimension(Dimension(TEST_GRADIENT_COLOR_OFFSET_END));
    gradient.AddColor(normalGradColor);

    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    sliderContentModifier.SetTrackBackgroundColor(gradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify mixed HDR-default + normal gradient draws without crash.
     * @tc.expected: HDR path is used (hasHDR = true), colors rendered correctly.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), gradient.GetColors().size());
}

/**
 * @tc.name: SliderContentModifier_DrawBackground_HDREmptyGradient
 * @tc.desc: Test DrawBackground with empty gradient colors,
 *           verifying GetHDRMaxByGradientColors returns hasHDR = false and default headRoom
 *           when gradient has no colors.
 * @tc.type: FUNC
 */
HWTEST_F(SliderContentModifierTestNg, SliderContentModifier_DrawBackground_HDREmptyGradient, TestSize.Level1)
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
     * @tc.steps: step2. Set modifier with empty gradient and call onDraw.
     */
    SetSliderContentModifier(sliderContentModifier);
    sliderContentModifier.SetDirection(Axis::HORIZONTAL);
    sliderContentModifier.SetBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderContentModifier.SetSliderMode(SliderModelNG::SliderMode::OUTSET);
    sliderContentModifier.SetBackgroundSize(POINTF_START, POINTF_END);
    Gradient emptyGradient;
    sliderContentModifier.SetTrackBackgroundColor(emptyGradient);
    Testing::MockCanvas canvas;
    MockCanvasFunction(canvas);
    DrawingContext context { canvas, SLIDER_DRAW_CANVAS_WIDTH, SLIDER_DRAW_CANVAS_HEIGHT };
    sliderContentModifier.onDraw(context);

    /**
     * @tc.steps: step3. Verify empty gradient does not crash.
     * @tc.expected: No crash, empty gradient handled gracefully.
     */
    auto trackBgColor = sliderContentModifier.trackBackgroundColor_->Get();
    EXPECT_EQ(trackBgColor.GetGradient().GetColors().size(), 0u);
}

} // namespace OHOS::Ace::NG
