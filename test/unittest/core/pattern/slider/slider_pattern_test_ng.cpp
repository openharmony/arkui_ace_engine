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
constexpr Dimension SLIDER_OUTSET_TRACK_THICKNRESS = Dimension(10.0);
constexpr Dimension SLIDER_INSET_TRACK_THICKNRESS = Dimension(20.0);
constexpr Dimension SLIDER_NONE_TRACK_THICKNRESS = Dimension(5.0);
constexpr Dimension SLIDER_OUTSET_BLOCK_SIZE = Dimension(30.0);
constexpr Dimension SLIDER_INSET_BLOCK_SIZE = Dimension(15.0);
constexpr Dimension RADIUS = Dimension(10.0);
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
constexpr float CONTENT_WIDTH = 100.0f;
constexpr float CONTENT_HEIGHT = 50.0f;
constexpr float HOT_BLOCK_SHADOW_WIDTH = 3.0f;
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
constexpr Dimension TRACK_BORDER_RADIUS = 5.0_px;
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
} // namespace
class SliderPatternTestNg : public testing::Test {
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

void SliderPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void SliderPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void SliderPatternTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderPatternTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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

void SliderPatternTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderPatternTest001
 * @tc.desc: Test slider_pattern UpdateBlock/CreateNodePaintMethod/GetBlockCenter/HandleTouchEvent
 * imageFrameNode_ == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     * @tc.steps: step2. set BlockStyleType IMAGE
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);

    // set TouchType UP
    TouchEventInfo info("onTouchUp");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);

    // call function
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->hotFlag_, false);
    sliderPattern->UpdateBlock();
    sliderPattern->LayoutImageNode();
    sliderPattern->bubbleFlag_ = true;
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    sliderPattern->sliderTipModifier_->getBubbleVertexFunc_();
    sliderPattern->UpdateCircleCenterOffset();
    auto contentSize = sliderPattern->GetHostContentSize();
    EXPECT_EQ(sliderPattern->GetBlockCenter().GetY(), contentSize->Height() * HALF);
}

/**
 * @tc.name: SliderPatternTest002
 * @tc.desc: Test slider_pattern UpdateBlock/CreateNodePaintMethod/GetBlockCenter/HandleTouchEvent
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. set attribute and call function.
     */
    // set BlockStyleType IMAGE
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    // set TouchType UP
    TouchEventInfo info("onTouchUp");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    // set sliderPattern
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    sliderPattern->HandleTouchEvent(info);
    EXPECT_EQ(sliderPattern->hotFlag_, false);
    sliderPattern->UpdateBlock();
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    sliderPattern->imageFrameNode_ =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::DEFAULT);
    sliderPattern->UpdateBlock();
    sliderPattern->UpdateCircleCenterOffset();
    sliderPaintProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->UpdateCircleCenterOffset();
    auto contentSize = sliderPattern->GetHostContentSize();
    EXPECT_EQ(sliderPattern->GetBlockCenter().GetX(), contentSize->Width() * HALF);
}

/**
 * @tc.name: SliderPatternTest003
 * @tc.desc: Test slider pattern OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    layoutWrapper->skipMeasureContent_ = false;
    RefPtr<LayoutWrapperNode> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);

    RefPtr<SliderLayoutAlgorithm> sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    // set theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(20.0f);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(30.0f);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = 40.0f;

    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    sliderPattern->imageFrameNode_ =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    layoutWrapper->AppendChild(secondLayoutWrapper);
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
}

/**
 * @tc.name: SliderPatternTest004
 * @tc.desc: Test slider pattern GetOutsetInnerFocusPaintRect function.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. call GetOutsetInnerFocusPaintRect function.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    RoundRect focusRect;
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::SHAPE);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusDistance = paintWidth * HALF + sliderTheme->GetFocusSideDistance();

    // vaild circle
    basicShape->SetRadius(RADIUS);
    sliderPaintProperty->UpdateBlockShape(basicShape);
    sliderPattern->GetOutsetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        RADIUS.ConvertToPx() + focusDistance.ConvertToPx());
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        RADIUS.ConvertToPx() + focusDistance.ConvertToPx());

    // invalid circle: radius = 0
    basicShape = AceType::MakeRefPtr<Circle>();
    sliderPaintProperty->UpdateBlockShape(basicShape);
    sliderPattern->GetOutsetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        std::min(basicShape->GetWidth(), basicShape->GetHeight()).ConvertToPx() * HALF + focusDistance.ConvertToPx());
    EXPECT_EQ(focusRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        std::min(basicShape->GetWidth(), basicShape->GetHeight()).ConvertToPx() * HALF + focusDistance.ConvertToPx());

    // revert to default
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    sliderPattern->GetOutsetInnerFocusPaintRect(focusRect);
    EXPECT_EQ(focusRect.radius_.GetCorner(0).x, 1.0f);
    EXPECT_EQ(focusRect.radius_.GetCorner(0).y, 1.0f);
}

/**
 * @tc.name: SliderPatternTest005
 * @tc.desc: Test SliderPattern::OnDirtyLayoutWrapperSwap function.
 *           Calculate the value of borderBlank_ in the INSET/OUTSET scenario.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and prepare environment.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    ASSERT_NE(sliderLayoutAlgorithm, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, false, false);
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH, CONTENT_HEIGHT));
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(HOT_BLOCK_SHADOW_WIDTH);

    /**
     * @tc.steps: step2. Calculate in the INSET scenario.
     * @tc.expected: borderBlank_ == block_width / 2 + shadow_width
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_INSET_TRACK_THICKNRESS.Value();
    sliderLayoutAlgorithm->blockSize_ = SizeF(SLIDER_INSET_BLOCK_SIZE.Value(), SLIDER_INSET_BLOCK_SIZE.Value());
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_, SLIDER_INSET_TRACK_THICKNRESS.Value() * HALF + HOT_BLOCK_SHADOW_WIDTH);

    /**
     * @tc.steps: step3. Calculate in the OUTSET scenario.
     * @tc.expected: borderBlank_ == max(block_width, track_thickness) / 2 + shadow_width
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS.Value();
    sliderLayoutAlgorithm->blockSize_ = SizeF(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_BLOCK_SIZE.Value());
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_,
        std::max(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_TRACK_THICKNRESS.Value()) * HALF +
            HOT_BLOCK_SHADOW_WIDTH);
    /**
     * @tc.steps: step4. Calculate in the NONE scenario.
     * @tc.expected: borderBlank_ == 0
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_NONE_TRACK_THICKNRESS.Value();
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_, 0);
}

/**
 * @tc.name: SliderPatternTest006
 * @tc.desc: Test slider_pattern CreateNodePaintMethod/HandlingGestureEvent/OnKeyEvent
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    /**
     * @tc.steps: step2. set attribute and call function.
     */
    // mock theme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));

    // set key event
    auto func = [&sliderPattern]() {
        KeyEvent keyEvent;
        sliderPattern->direction_ = Axis::HORIZONTAL;
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_LEFT;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::UP;
        sliderPattern->OnKeyEvent(keyEvent);
        sliderPattern->OnKeyEvent(keyEvent);

        sliderPattern->direction_ = Axis::VERTICAL;
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_UP;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::DOWN;
        keyEvent.code = KeyCode::KEY_DPAD_DOWN;
        sliderPattern->OnKeyEvent(keyEvent);
        keyEvent.action = KeyAction::UNKNOWN;
        sliderPattern->OnKeyEvent(keyEvent);
    };

    func();
    sliderPattern->showTips_ = true;
    func();

    // set gesture input event
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetOffsetX(-1);
    sliderPattern->HandlingGestureEvent(info);
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    sliderPattern->HandledGestureEvent();
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
}

/**
 * @tc.name: SliderPatternTest007
 * @tc.desc: Test slider_pattern GetBubbleVertexPosition
 * imageFrameNode_ != nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     * @tc.steps: step2. set attribute and call function.
     */
    auto offset = BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx();
    sliderPattern->direction_ = Axis::HORIZONTAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(0, -offset));
    sliderPattern->direction_ = Axis::VERTICAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(-offset, 0));

    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    sliderPattern->direction_ = Axis::HORIZONTAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(0, -offset));
    sliderPattern->direction_ = Axis::VERTICAL;
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(-offset, 0));
}

/**
 * @tc.name: SliderPatternTest008
 * @tc.desc: Test SliderPattern GetInsetAndNoneInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slider and prepare environment.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    ASSERT_NE(sliderTheme, nullptr);
    auto appTheme = AceType::MakeRefPtr<AppTheme>();
    ASSERT_NE(appTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(SliderTheme::TypeId())).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(AppTheme::TypeId())).WillRepeatedly(Return(appTheme));
    auto focusDistance =
        sliderTheme->GetFocusSideDistance().ConvertToPx() + (appTheme->GetFocusWidthVp().ConvertToPx() * HALF);
    RoundRect roundRect;
    sliderPattern->trackThickness_ = SLIDER_HEIGHT;
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(CONTENT_WIDTH, CONTENT_HEIGHT));

    /**
     * @tc.steps: step2. call GetInsetAndNoneInnerFocusPaintRect without TrackBorderRadius property.
     * @tc.expected: step2. radius == (TrackThickness / 2 + focusWidth).
     */
    sliderPattern->direction_ = Axis::HORIZONTAL;
    sliderPattern->GetInsetAndNoneInnerFocusPaintRect(roundRect);
    auto radius = roundRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    EXPECT_EQ(radius.x, (SLIDER_HEIGHT * HALF) + focusDistance);
    EXPECT_EQ(radius.y, (SLIDER_HEIGHT * HALF) + focusDistance);

    /**
     * @tc.steps: step3. call GetInsetAndNoneInnerFocusPaintRect with TrackBorderRadius property.
     * @tc.expected: step3. radius == (TrackBorderRadius + focusWidth).
     */
    sliderPattern->direction_ = Axis::VERTICAL;
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateTrackBorderRadius(TRACK_BORDER_RADIUS);
    sliderPattern->GetInsetAndNoneInnerFocusPaintRect(roundRect);
    radius = roundRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS);
    EXPECT_EQ(radius.x, TRACK_BORDER_RADIUS.ConvertToPx() + focusDistance);
    EXPECT_EQ(radius.y, TRACK_BORDER_RADIUS.ConvertToPx() + focusDistance);
}

/**
 * @tc.name: SliderPatternTest009
 * @tc.desc: Test slider_pattern onBlurInternal_ HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     * @tc.steps: step2. call focusHub onBlurInternal callback.
     * @tc.expected: step2. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    auto focusHub = frameNode->GetOrCreateFocusHub();
    sliderPattern->OnModifyDone();
    focusHub->onBlurInternal_();
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step3. Mouse on slider block.
     * @tc.expected: step3. sliderPattern->bubbleFlag_ is true.
     */
    MouseInfo mouseInfo;
    sliderPattern->blockSize_ = SizeF(MAX_WIDTH, MAX_HEIGHT);
    sliderPattern->showTips_ = true;
    sliderPattern->HandleMouseEvent(mouseInfo);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step4. Mouse not on slider block.
     * @tc.expected: step4. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->blockSize_ = SizeF(0, 0);
    sliderPattern->HandleMouseEvent(mouseInfo);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderPatternTest010
 * @tc.desc: Test slider_pattern HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));

    /**
     * @tc.steps: step2. call HandleHoverEvent hover false with normal.
     * @tc.expected: step2. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step3. call HandleHoverEvent hover false with mouse pressed.
     * @tc.expected: step3. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->mousePressedFlag_ = true;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step4. call HandleHoverEvent hover false with focus.
     * @tc.expected: step4. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = true;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);

    /**
     * @tc.steps: step5. call HandleHoverEvent hover true.
     * @tc.expected: step5. sliderPattern->bubbleFlag_ is true.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(true);
    ASSERT_TRUE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderPatternTest011
 * @tc.desc: Test slider_pattern AtMousePanArea
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);

    /**
     * @tc.steps: step3. modify circleCenter and blockSize.
     */
    sliderPattern->blockSize_.SetWidth(SLIDER_OUTSET_BLOCK_SIZE.ConvertToPx());
    sliderPattern->blockSize_.SetHeight(SLIDER_OUTSET_BLOCK_SIZE.ConvertToPx());
    sliderPattern->circleCenter_.SetX(sliderPattern->blockSize_.Width() * HALF);
    sliderPattern->circleCenter_.SetY(sliderPattern->blockSize_.Height() * HALF);

    /**
     * @tc.cases: case1. the offset(1,1) is not in circle block.
     */
    Offset offsetInFrame(1, 1);
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::DEFAULT);
    ASSERT_FALSE(sliderPattern->AtMousePanArea(offsetInFrame));

    /**
     * @tc.cases: case2. the offset(1,1) is in rect block.
     */
    sliderPaintProperty->UpdateBlockType(SliderModelNG::BlockStyleType::SHAPE);
    ASSERT_TRUE(sliderPattern->AtMousePanArea(offsetInFrame));
}

/**
 * @tc.name: SliderPatternTest012
 * @tc.desc: Test slider_pattern InitPanEvent and event callback.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto hub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);

    /**
     * @tc.steps: step2. start SliderPattern InitPanEvent func.
     */
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr, nullptr);
    GestureEvent info = GestureEvent();
    sliderPattern->InitPanEvent(gestureHub);

    /**
     * @tc.steps: step3. call event callback func.
     */
    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::DEFAULT;
    sliderPattern->panEvent_->actionStart_(info);
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::MOVE);

    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::DEFAULT;
    sliderPattern->panEvent_->actionUpdate_(info);
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::MOVE);

    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::MOVE;
    sliderPattern->panEvent_->actionEnd_(info);
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::DEFAULT);

    sliderPattern->sliderContentModifier_->animatorStatus_ = SliderStatus::MOVE;
    sliderPattern->panEvent_->actionCancel_();
    ASSERT_EQ(sliderPattern->sliderContentModifier_->animatorStatus_, SliderStatus::DEFAULT);
}

/**
 * @tc.name: SliderPatternTest013
 * @tc.desc: Test slider_pattern InitPanEvent and event callback.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    ASSERT_NE(sliderPattern->CreateNodePaintMethod(), nullptr);
    ASSERT_NE(sliderPattern->sliderContentModifier_, nullptr);

    /**
     * @tc.steps: step2. set BlockStyleType IMAGE
     */
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockType(SliderModel::BlockStyleType::IMAGE);
    sliderPaintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    sliderPattern->UpdateBlock();
    ASSERT_NE(sliderPattern->imageFrameNode_, nullptr);

    /**
     * @tc.steps: step3. update block center.
     */
    sliderPattern->sliderContentModifier_->updateImageCenterX_(FRAME_WIDTH);
    sliderPattern->sliderContentModifier_->updateImageCenterY_(FRAME_HEIGHT);
    auto imageGeometryNode = sliderPattern->imageFrameNode_->GetGeometryNode();
    ASSERT_NE(imageGeometryNode, nullptr);
    auto offset = imageGeometryNode->GetMarginFrameOffset();
    ASSERT_EQ(offset.GetX(), (FRAME_WIDTH - sliderPattern->blockSize_.Width() * HALF));
    ASSERT_EQ(offset.GetY(), (FRAME_HEIGHT - sliderPattern->blockSize_.Height() * HALF));
}

/**
 * @tc.name: SliderPatternTest014
 * @tc.desc: SetBuilderFunc and get value
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest014, TestSize.Level1)
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
    sliderPaintProperty->UpdateValue(VALUE);
    sliderPaintProperty->UpdateMin(MIN);
    sliderPaintProperty->UpdateMax(MAX);
    sliderPaintProperty->UpdateStep(STEP);
    auto node = [](SliderConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(VALUE, config.value_);
        EXPECT_EQ(MIN, config.min_);
        EXPECT_EQ(MAX, config.max_);
        EXPECT_EQ(STEP, config.step_);
        return nullptr;
    };

    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->SetBuilderFunc(node);
    sliderPattern->BuildContentModifierNode();
}
} // namespace OHOS::Ace::NG
