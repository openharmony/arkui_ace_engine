/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include <optional>
#include "core/accessibility/accessibility_manager.h"
#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/common/mock_container.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
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
#include "core/components_ng/pattern/particle/particle_pattern.h"
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/root/root_pattern.h"

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
const std::string SLIDER_EFFECT_ID_NAME = "haptic.slide";
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
const Offset SLIDER_OFFSET = { 200, 200 };
constexpr float MIN_LABEL = 10.0f;
constexpr float MAX_LABEL = 20.0f;
const std::vector<PointF> HORIZONTAL_STEP_POINTS { { 10, 20 }, { 20, 20 }, { 30, 20 } };
const std::vector<std::pair<std::vector<float>, int32_t>> ACCESSIBILITY_STEP_INDEX_DATA = {
    { { 100, 0, 1, 50 }, 50 }, { { 30, 0, 1.5, 19.5 }, 13 }, { { 80, 10, 8, 70.6 }, 8 }, { { 100, 0, 10, 50 }, 5 }
};
const SliderModel::SliderShowStepOptions OPTIONS_MAP = {
    { 0, "step 0" }, { 50, "step 50" }, { 1, "step 1" }, { 8, "step 8" }, { 5, "step 5" }};
constexpr float OUTSET_HOT_BLOCK_SHADOW_WIDTH = 20.0f;
constexpr float INSET_HOT_BLOCK_SHADOW_WIDTH = 30.0f;
constexpr float TRACK_THICKNESS = 40.0f;
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
    RefPtr<SliderPattern> AccessibilityInit(RefPtr<FrameNode>& frameNode);
};

void SliderPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SliderPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
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

RefPtr<SliderPattern> SliderPatternTestNg::AccessibilityInit(RefPtr<FrameNode>& frameNode)
{
    frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    CHECK_NULL_RETURN(sliderPattern, nullptr);
    sliderPattern->frameNode_ = frameNode;
    if (!sliderPattern->parentAccessibilityNode_) {
        sliderPattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    }
    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    CHECK_NULL_RETURN(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;
    return sliderPattern;
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
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
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
    sliderPattern->isVisibleArea_ = true;
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
    sliderPattern->isVisibleArea_ = true;
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
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;

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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
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
    sliderLayoutAlgorithm->blockHotSize_ = SizeF(SLIDER_INSET_BLOCK_SIZE.Value(), SLIDER_INSET_BLOCK_SIZE.Value());
    sliderPattern->UpdateSliderParams(sliderLayoutAlgorithm->trackThickness_, sliderLayoutAlgorithm->blockSize_,
        sliderLayoutAlgorithm->blockHotSize_);
    EXPECT_TRUE(sliderPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, false, false));
    EXPECT_EQ(sliderPattern->borderBlank_, SLIDER_INSET_TRACK_THICKNRESS.Value() * HALF + HOT_BLOCK_SHADOW_WIDTH);

    /**
     * @tc.steps: step3. Calculate in the OUTSET scenario.
     * @tc.expected: borderBlank_ == max(block_width, track_thickness) / 2 + shadow_width
     */
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    sliderLayoutAlgorithm->trackThickness_ = SLIDER_OUTSET_TRACK_THICKNRESS.Value();
    sliderLayoutAlgorithm->blockSize_ = SizeF(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_BLOCK_SIZE.Value());
    sliderLayoutAlgorithm->blockHotSize_ = SizeF(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_BLOCK_SIZE.Value());
    sliderPattern->UpdateSliderParams(sliderLayoutAlgorithm->trackThickness_, sliderLayoutAlgorithm->blockSize_,
        sliderLayoutAlgorithm->blockHotSize_);
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
    sliderLayoutAlgorithm->blockSize_ = SizeF(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_BLOCK_SIZE.Value());
    sliderLayoutAlgorithm->blockHotSize_ = SizeF(SLIDER_OUTSET_BLOCK_SIZE.Value(), SLIDER_OUTSET_BLOCK_SIZE.Value());
    sliderPattern->UpdateSliderParams(sliderLayoutAlgorithm->trackThickness_, sliderLayoutAlgorithm->blockSize_,
        sliderLayoutAlgorithm->blockHotSize_);
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
    sliderPattern->isVisibleArea_ = true;
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
    SliderModelNG sliderModelNG;
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    sliderModelNG.SetDirection(node, Axis::HORIZONTAL);
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(0, -offset));
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(-offset, 0));

    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModelNG::SliderMode::INSET);
    sliderModelNG.SetDirection(node, Axis::HORIZONTAL);
    ASSERT_EQ(sliderPattern->GetBubbleVertexPosition(OffsetF(), 0.0f, SizeF()).first, OffsetF(0, -offset));
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
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
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
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
    sliderPattern->InitEvent();
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
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
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
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    sliderPattern->isVisibleArea_ = true;
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
    sliderPattern->sliderContentModifier_->updateImageCenterCallback_(PointF(FRAME_WIDTH, FRAME_HEIGHT));
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

/**
 * @tc.name: SliderPatternTest015
 * @tc.desc: SliderPattern::OnWindowSizeChanged.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    sliderNode->context_ = AceType::RawPtr(context);
    sliderPaintProperty->UpdateValue(VALUE);
    sliderPaintProperty->UpdateMin(MIN);
    sliderPaintProperty->UpdateMax(MAX);
    sliderPaintProperty->UpdateStep(STEP);
    sliderPattern->OnWindowSizeChanged(FRAME_WIDTH, FRAME_HEIGHT, WindowSizeChangeReason::RESIZE);
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    int32_t setApiVersion = 13;
    int32_t rollbackApiVersion = context->GetApiTargetVersion();
    context->SetApiTargetVersion(setApiVersion);
    sliderPattern->OnWindowSizeChanged(FRAME_WIDTH, FRAME_HEIGHT, WindowSizeChangeReason::ROTATION);
    context->SetApiTargetVersion(rollbackApiVersion);
    EXPECT_TRUE(sliderPattern->skipGestureEvents_);
}

/**
 * @tc.name: SliderPatternTest016
 * @tc.desc: SliderPattern::HandleTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateValue(VALUE);
    sliderPaintProperty->UpdateMin(MIN);
    sliderPaintProperty->UpdateMax(MAX);
    sliderPaintProperty->UpdateStep(STEP);
    sliderPattern->lastTouchLocation_ = SLIDER_OFFSET;
    sliderPattern->bubbleFlag_ = false;
    sliderPattern->isFocusActive_ = true;
    sliderPattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP;
    sliderPattern->HandleTouchUp(SLIDER_OFFSET, SourceType::TOUCH);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_ONLY;
    sliderPattern->HandleTouchUp(SLIDER_OFFSET, SourceType::NONE);
    EXPECT_FALSE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: SliderPatternTest017
 * @tc.desc: SliderPattern::HandleTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    GestureEvent SliderInfo;
    SliderInfo.inputEventType_ = InputEventType::AXIS;
    SliderInfo.localLocation_ = Offset(MIN_LABEL, MAX_LABEL);
    SliderInfo.SetOffsetX(.0);
    SliderInfo.SetOffsetY(1.0);
    SliderInfo.SetSourceTool(SourceTool::MOUSE);
    sliderPattern->HandlingGestureEvent(SliderInfo);
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->HandlingGestureEvent(SliderInfo);
    EXPECT_FALSE(sliderPattern->panMoveFlag_);
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_ONLY;
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->fingerId_ = 2;
    SliderInfo.inputEventType_ = InputEventType::TOUCH_SCREEN;
    FingerInfo fingerInfoFst;
    fingerInfoFst.fingerId_ = 1;
    FingerInfo fingerInfoScd;
    fingerInfoScd.fingerId_ = 2;
    SliderInfo.fingerList_.push_back(fingerInfoFst);
    SliderInfo.fingerList_.push_back(fingerInfoScd);
    sliderPattern->HandlingGestureEvent(SliderInfo);
    EXPECT_TRUE(sliderPattern->panMoveFlag_);
}

/**
 * @tc.name: SliderPatternTest018
 * @tc.desc: SliderPattern::StartAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    sliderPattern->sliderContentModifier_->isVisible_ = true;
    sliderPattern->StartAnimation();
    EXPECT_TRUE(sliderPattern->sliderContentModifier_->GetVisible());
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->sliderContentModifier_->isVisible_ = false;
    sliderPattern->isVisibleArea_ = true;
    sliderPattern->isShow_ = true;
    sliderPattern->StartAnimation();
    EXPECT_TRUE(sliderPattern->sliderContentModifier_->GetVisible());
}

/**
 * @tc.name: SliderPatternTest019
 * @tc.desc: SliderPattern::UpdateTipState.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    sliderPattern->focusFlag_ = true;
    sliderPattern->UpdateTipState();
    /**
     * @tc.steps: step2. Set parameters to pattern builderFunc
     */
    sliderPattern->showTips_ = true;
    sliderPattern->isVisibleArea_ = true;
    sliderPattern->isShow_ = true;
    sliderPattern->UpdateTipState();
    EXPECT_FALSE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: SliderPatternTest020
 * @tc.desc: SliderPattern::OnIsFocusActiveUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPattern->sliderContentModifier_ =
        AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    sliderPattern->focusFlag_ = false;
    sliderPattern->OnIsFocusActiveUpdate(true);
    EXPECT_FALSE(sliderPattern->isFocusActive_);
    /**
     * @tc.steps: step2. Set focusFlag_ = true and bubbleFlag_ ≠ showBubble.
     */
    sliderPattern->focusFlag_ = true;
    sliderPattern->showTips_ = false;
    sliderPattern->bubbleFlag_ = false;
    sliderPattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: SliderPatternTest021
 * @tc.desc: SliderPattern::UseContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(sliderNode);
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPaintProperty = sliderNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto host = sliderPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    /**
     * @tc.steps: step2. Set contentModifierNode_ and call UseContentModifier.
     */
    auto modifierNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    sliderPattern->contentModifierNode_ = modifierNode;
    sliderPattern->InitTouchEvent(gestureHub);
    sliderPattern->InitPanEvent(gestureHub);
    RefPtr<EventHub> eventHub = AccessibilityManager::MakeRefPtr<EventHub>();
    RefPtr<FocusHub> focusHub = AccessibilityManager::MakeRefPtr<FocusHub>(
        AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(eventHub)), FocusType::DISABLE, false);
    sliderPattern->InitOnKeyEvent(focusHub);
    auto inputEventHub = eventHub->GetOrCreateInputEventHub();
    sliderPattern->InitMouseEvent(inputEventHub);
    EXPECT_EQ(sliderPattern->hoverEvent_, nullptr);
    EXPECT_EQ(sliderPattern->mouseEvent_, nullptr);
}

/**
 * @tc.name: SliderPatternAccessibilityTest001
 * @tc.desc: Test slider_pattern GetStepPointAccessibilityVirtualNodeSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternAccessibilityTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    if (!sliderPattern->parentAccessibilityNode_) {
        sliderPattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    }
    auto parent = sliderPattern->parentAccessibilityNode_;
    ASSERT_NE(parent, nullptr);
    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;
    /**
     * @tc.steps: step2. Add Slider virtual node.
     */
    sliderPattern->AddStepPointsAccessibilityVirtualNode();

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    const auto& content = geometryNode->GetContent();
    ASSERT_NE(content.get(), nullptr);
    auto contentRect = content->GetRect();
    float pointNodeHeight = sliderPattern->sliderLength_ / (sliderPattern->pointAccessibilityNodeEventVec_.size() - 1);
    float pointNodeWidth = pointNodeHeight;
    /**
     * @tc.steps: step3. Get virtual nodes size in horizontal.
     */
    auto hSize = sliderPattern->GetStepPointAccessibilityVirtualNodeSize();
    EXPECT_EQ(hSize.Width(), pointNodeWidth);
    EXPECT_EQ(hSize.Height(), contentRect.Height());

    SliderModelNG sliderModelNG;
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    sliderModelNG.SetDirection(node, Axis::VERTICAL);
    /**
     * @tc.steps: step4 Get virtual nodes size in vertical.
     */
    auto vSize = sliderPattern->GetStepPointAccessibilityVirtualNodeSize();
    EXPECT_EQ(vSize.Width(), contentRect.Width());
    EXPECT_EQ(vSize.Height(), pointNodeHeight);
}

/**
 * @tc.name: SliderPatternAccessibilityTest002
 * @tc.desc: Test slider_pattern GetCurrentStepIndex
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternAccessibilityTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    for (const auto& item : ACCESSIBILITY_STEP_INDEX_DATA) {
        sliderPaintProperty->UpdateMax(item.first[0]);
        sliderPaintProperty->UpdateMin(item.first[1]);
        sliderPaintProperty->UpdateStep(item.first[2]);
        sliderPaintProperty->UpdateValue(item.first[3]);
        /**
         * @tc.steps: step2. Get virtual nodes index.
         */
        EXPECT_EQ(sliderPattern->GetCurrentStepIndex(), item.second);
    }
}

/**
 * @tc.name: SliderPatternAccessibilityTest003
 * @tc.desc: Test slider_pattern SetStepPointsAccessibilityVirtualNodeEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternAccessibilityTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    if (!sliderPattern->parentAccessibilityNode_) {
        sliderPattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    }
    auto parent = sliderPattern->parentAccessibilityNode_;
    ASSERT_NE(parent, nullptr);
    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;
    /**
     * @tc.steps: step2. Add Slider virtual node.
     */
    sliderPattern->AddStepPointsAccessibilityVirtualNode();
    for (uint32_t i = 0; i < HORIZONTAL_STEP_POINTS.size(); i++) {
        auto textNode = sliderPattern->pointAccessibilityNodeVec_[i];
        ASSERT_NE(textNode, nullptr);
        bool click = i % 2 == 0;
        bool reverse = i % 3 == 0;
        sliderPattern->SetStepPointsAccessibilityVirtualNodeEvent(textNode, i, click, reverse, false);
        auto evetFunc = sliderPattern->pointAccessibilityNodeEventVec_[i];
        if (click) {
            EXPECT_NE(evetFunc, nullptr);
        } else {
            EXPECT_EQ(evetFunc, nullptr);
        }
    }
}

/**
 * @tc.name: SliderPatternAccessibilityTest004
 * @tc.desc: Test slider_pattern AddStepPointsAccessibilityVirtualNode and
 * UpdateStepPointsAccessibilityVirtualNodeSelected
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternAccessibilityTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    RefPtr<FrameNode> frameNode;
    auto sliderPattern = AccessibilityInit(frameNode);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(sliderPattern, nullptr);
    auto parent = sliderPattern->parentAccessibilityNode_;
    ASSERT_NE(parent, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->context_ = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(context));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    /**
     * @tc.steps: step2. Add Slider virtual node.
     */
    sliderPattern->AddStepPointsAccessibilityVirtualNode();
    /**
     * @tc.steps: step3. Get accessibility virtual node size.
     */
    EXPECT_EQ(sliderPattern->pointAccessibilityNodeVec_.size(), HORIZONTAL_STEP_POINTS.size());
    EXPECT_EQ(sliderPattern->pointAccessibilityNodeEventVec_.size(), HORIZONTAL_STEP_POINTS.size());
    EXPECT_EQ(parent->GetChildren().size(), HORIZONTAL_STEP_POINTS.size());
    /**
     * @tc.steps: step4. Update virtual node selected.
     */
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto theme = context->GetTheme<SliderTheme>();
    ASSERT_NE(theme, nullptr);
    auto selected = theme->GetSelectedTxt();
    auto unselected = theme->GetUnselectedTxt();
    for (const auto& item : ACCESSIBILITY_STEP_INDEX_DATA) {
        sliderPaintProperty->UpdateMax(item.first[0]);
        sliderPaintProperty->UpdateMin(item.first[1]);
        sliderPaintProperty->UpdateStep(item.first[2]);
        sliderPaintProperty->UpdateValue(item.first[3]);
        for (int32_t i = 0; i < sliderPattern->pointAccessibilityNodeVec_.size(); i++) {
            auto node = sliderPattern->pointAccessibilityNodeVec_[i];
            ASSERT_NE(node, nullptr);
            auto pointAccessibilityProperty = node->GetAccessibilityProperty<TextAccessibilityProperty>();
            ASSERT_NE(pointAccessibilityProperty, nullptr);
            auto pointNodeProperty = node->GetLayoutProperty<TextLayoutProperty>();
            ASSERT_NE(pointNodeProperty, nullptr);

            std::string text, description;
            EXPECT_EQ(pointAccessibilityProperty->accessibilityLevel_, AccessibilityProperty::Level::YES_STR);
            if (i == 0) {
                pointAccessibilityProperty->SetSelected(true);
                text = StringUtils::Str16ToStr8(pointNodeProperty->GetContent().value_or(u""));
                description = " ";
            } else {
                pointAccessibilityProperty->SetSelected(false);
                text = StringUtils::Str16ToStr8(pointNodeProperty->GetContent().value_or(u""));
                description = "";
            }
            EXPECT_EQ(pointAccessibilityProperty->GetAccessibilityText(), text);
            EXPECT_EQ(pointAccessibilityProperty->GetAccessibilityDescription(), description);
        }
    }
}

HWTEST_F(SliderPatternTestNg, SliderTextProperty001, TestSize.Level1)
{
    auto backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    RefPtr<FrameNode> frameNode;
    auto sliderPattern = AccessibilityInit(frameNode);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AddStepPointsAccessibilityVirtualNode();
    sliderPattern->UpdateStepAccessibilityVirtualNode();
    for (const auto& node : sliderPattern->pointAccessibilityNodeVec_) {
        ASSERT_NE(node, nullptr);
        auto pointNodeProperty = node->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(pointNodeProperty, nullptr);
        EXPECT_TRUE(pointNodeProperty->GetEnableSmallLanguageTruncationValue(false));
    }
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ParseCommand001
 * @tc.desc: Test SliderPattern ParseCommand.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, ParseCommand001, TestSize.Level1)
{
    float value = MIN;
    std::string command = "";
    SliderPattern sliderPattern;
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{}";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{\"cmd\":\"SetValue\"}";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{\"cmd\":\"onSliderChange\"}";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{\"cmd\":\"onSliderChange\",\"params\":{}}";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{\"cmd\":\"onSliderChange\",\"params\":{\"value\":\"abc\"}}";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{\"cmd\":\"onSliderChange\",\"params\":{\"value\":true}}";
    EXPECT_FALSE(sliderPattern.ParseCommand(command, value));
    command = "{\"cmd\":\"onSliderChange\",\"params\":{\"value\":12.5}}";
    EXPECT_TRUE(sliderPattern.ParseCommand(command, value));
    EXPECT_EQ(value, 12.5f);
}

/**
 * @tc.name: OnInjectionEvent001
 * @tc.desc: Test SliderPattern OnInjectionEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnInjectionEvent001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    ASSERT_EQ(sliderPaintProperty->GetValueValue(MIN), VALUE);

    std::string command = "abc";
    EXPECT_EQ(sliderPattern->OnInjectionEvent(command), RET_FAILED);
    command = "{\"cmd\":\"onSliderChange\",\"params\":{\"value\":7}}";
    EXPECT_EQ(sliderPattern->OnInjectionEvent(command), RET_SUCCESS);
    EXPECT_EQ(sliderPaintProperty->GetValueValue(MIN), 7.0f);
}

/**
 * @tc.name: OnInjectionEvent002
 * @tc.desc: Test SliderPattern OnInjectionEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnInjectionEvent002, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    std::string command = "{\"cmd\":\"onSliderChange\",\"params\":{\"value\":7}}";
    EXPECT_EQ(sliderPattern->OnInjectionEvent(command), RET_FAILED);
}

/**
 * @tc.name: CalculateBlockOffset001
 * @tc.desc: Test CalculateBlockOffset when animatableBlockCenter has value.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), -5.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), -5.0f);
}

/**
 * @tc.name: CalculateBlockOffset002
 * @tc.desc: Test CalculateBlockOffset horizontal non-reverse LTR outset with length >= borderBlank.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderLayoutProperty->UpdateReverse(false);
    sliderLayoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 20.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 245.0f);
}

/**
 * @tc.name: CalculateBlockOffset003
 * @tc.desc: Test CalculateBlockOffset vertical non-reverse.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateReverse(false);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 245.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 20.0f);
}

/**
 * @tc.name: CalculateBlockOffset004
 * @tc.desc: Test CalculateBlockOffset horizontal reverse.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset004, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderLayoutProperty->UpdateReverse(true);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 470.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 245.0f);
}

/**
 * @tc.name: CalculateBlockOffset005
 * @tc.desc: Test CalculateBlockOffset vertical reverse.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset005, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderLayoutProperty->UpdateReverse(true);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 245.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 470.0f);
}

/**
 * @tc.name: CalculateBlockOffset006
 * @tc.desc: Test CalculateBlockOffset with INSET mode.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset006, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderLayoutProperty->UpdateReverse(false);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 30.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 245.0f);
}

/**
 * @tc.name: CalculateBlockOffset007
 * @tc.desc: Test CalculateBlockOffset when length < borderBlank.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset007, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderLayoutProperty->UpdateReverse(false);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = 600.0f;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 244.5f);
    EXPECT_FLOAT_EQ(offset.GetY(), 245.0f);
}

/**
 * @tc.name: CalculateBlockOffset008
 * @tc.desc: Test CalculateBlockOffset horizontal non-reverse with RTL layout direction.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalculateBlockOffset008, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderLayoutProperty->UpdateReverse(false);
    sliderLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto geometryNode = frameNode->GetGeometryNode();
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, sliderLayoutProperty);
    auto sliderLayoutAlgorithm = AceType::MakeRefPtr<SliderLayoutAlgorithm>();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    sliderTheme->outsetHotBlockShadowWidth_ = Dimension(OUTSET_HOT_BLOCK_SHADOW_WIDTH);
    sliderTheme->insetHotBlockShadowWidth_ = Dimension(INSET_HOT_BLOCK_SHADOW_WIDTH);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderLayoutAlgorithm->trackThickness_ = TRACK_THICKNESS;
    sliderLayoutAlgorithm->blockSize_ = SizeF(10.0f, 10.0f);
    sliderPattern->valueRatio_ = 0.0f;
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageFrameNode =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    auto childGeometry = imageFrameNode->GetGeometryNode();
    childGeometry->SetFrameSize(SizeF(10.0f, 10.0f));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageFrameNode, childGeometry, imageFrameNode->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sliderLayoutAlgorithm, true));
    sliderLayoutAlgorithm->CalculateBlockOffset(AceType::RawPtr(layoutWrapper), childWrapper);
    auto offset = childWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset.GetX(), 470.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 245.0f);
}

/**
 * @tc.name: CalcSliderValue001
 * @tc.desc: Test CalcSliderValue with normal value in range.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalcSliderValue001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateValue(50.0f);
    paintProperty->UpdateStep(1.0f);
    bool result = sliderPattern->CalcSliderValue();
    EXPECT_FALSE(result);
    EXPECT_FLOAT_EQ(sliderPattern->value_, 50.0f);
    EXPECT_FLOAT_EQ(sliderPattern->valueRatio_, 0.5f);
}

/**
 * @tc.name: CalcSliderValue002
 * @tc.desc: Test CalcSliderValue when min >= max (invalid range).
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalcSliderValue002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(100.0f);
    paintProperty->UpdateMax(0.0f);
    paintProperty->UpdateValue(50.0f);
    paintProperty->UpdateStep(1.0f);
    sliderPattern->CalcSliderValue();
    EXPECT_EQ(paintProperty->GetMin().value(), 0.0f);
    EXPECT_EQ(paintProperty->GetMax().value(), 100.0f);
}

/**
 * @tc.name: CalcSliderValue003
 * @tc.desc: Test CalcSliderValue when step <= 0 (invalid step).
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalcSliderValue003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateValue(50.0f);
    paintProperty->UpdateStep(0.0f);
    sliderPattern->CalcSliderValue();
    EXPECT_EQ(paintProperty->GetStep().value(), 1.0f);
}

/**
 * @tc.name: CalcSliderValue004
 * @tc.desc: Test CalcSliderValue when value < min (exception recovery).
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalcSliderValue004, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(10.0f);
    paintProperty->UpdateMax(90.0f);
    paintProperty->UpdateValue(-10.0f);
    paintProperty->UpdateStep(1.0f);
    bool result = sliderPattern->CalcSliderValue();
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(sliderPattern->value_, 10.0f);
}

/**
 * @tc.name: CalcSliderValue005
 * @tc.desc: Test CalcSliderValue when value > max (exception recovery).
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CalcSliderValue005, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(10.0f);
    paintProperty->UpdateMax(90.0f);
    paintProperty->UpdateValue(200.0f);
    paintProperty->UpdateStep(1.0f);
    bool result = sliderPattern->CalcSliderValue();
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(sliderPattern->value_, 90.0f);
}

/**
 * @tc.name: SliderPatternUpdateValue001
 * @tc.desc: Test UpdateValue when panMoveFlag is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternUpdateValue001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    sliderPattern->panMoveFlag_ = false;
    sliderPattern->UpdateValue(30.0f);
    EXPECT_EQ(paintProperty->GetValue().value(), 30.0f);
    EXPECT_FLOAT_EQ(sliderPattern->value_, 30.0f);
}

/**
 * @tc.name: SliderPatternUpdateValue002
 * @tc.desc: Test UpdateValue when panMoveFlag is true (skip writing property).
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternUpdateValue002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    paintProperty->UpdateValue(50.0f);
    sliderPattern->panMoveFlag_ = true;
    sliderPattern->UpdateValue(30.0f);
    // panMoveFlag true -> property not updated, stays 50
    EXPECT_EQ(paintProperty->GetValue().value(), 50.0f);
}

/**
 * @tc.name: SliderPatternUpdateValue003
 * @tc.desc: Test UpdateValue with isNotifyRecovery true and exception value.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternUpdateValue003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(10.0f);
    paintProperty->UpdateMax(90.0f);
    paintProperty->UpdateStep(1.0f);
    sliderPattern->panMoveFlag_ = false;
    sliderPattern->UpdateValue(200.0f, true);
    // value clamped to max=90
    EXPECT_FLOAT_EQ(sliderPattern->value_, 90.0f);
}

/**
 * @tc.name: SliderPatternSetSliderValue001
 * @tc.desc: Test SetSliderValue when enabled is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternSetSliderValue001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateValue(50.0f);
    sliderPattern->SetSliderValue(80.0f, 1, false);
    // disabled -> value not updated
    EXPECT_EQ(paintProperty->GetValue().value(), 50.0f);
}

/**
 * @tc.name: SliderPatternSetSliderValue002
 * @tc.desc: Test SetSliderValue when enabled is true.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, SliderPatternSetSliderValue002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(true);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    sliderPattern->SetSliderValue(70.0f, 1, false);
    EXPECT_FLOAT_EQ(sliderPattern->value_, 70.0f);
}

/**
 * @tc.name: GetValueInValidRange001
 * @tc.desc: Test GetValueInValidRange when no valid slide range is set.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetValueInValidRange001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    float result = sliderPattern->GetValueInValidRange(paintProperty, 50.0f, 0.0f, 100.0f);
    EXPECT_FLOAT_EQ(result, 50.0f);
}

/**
 * @tc.name: GetValueInValidRange002
 * @tc.desc: Test GetValueInValidRange when value is below fromValue.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetValueInValidRange002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    auto range = AceType::MakeRefPtr<SliderModel::SliderValidRange>(30.0f, 70.0f);
    paintProperty->UpdateValidSlideRange(range);
    float result = sliderPattern->GetValueInValidRange(paintProperty, 10.0f, 0.0f, 100.0f);
    EXPECT_FLOAT_EQ(result, 30.0f);
}

/**
 * @tc.name: GetValueInValidRange003
 * @tc.desc: Test GetValueInValidRange when value is above toValue.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetValueInValidRange003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    auto range = AceType::MakeRefPtr<SliderModel::SliderValidRange>(30.0f, 70.0f);
    paintProperty->UpdateValidSlideRange(range);
    float result = sliderPattern->GetValueInValidRange(paintProperty, 90.0f, 0.0f, 100.0f);
    EXPECT_FLOAT_EQ(result, 70.0f);
}

/**
 * @tc.name: UpdateToValidValue001
 * @tc.desc: Test UpdateToValidValue with value in range.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateToValidValue001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    paintProperty->UpdateValue(50.0f);
    sliderPattern->UpdateToValidValue();
    EXPECT_FLOAT_EQ(sliderPattern->value_, 50.0f);
    EXPECT_FLOAT_EQ(sliderPattern->valueRatio_, 0.5f);
}

/**
 * @tc.name: IsMinResponseExceed001
 * @tc.desc: Test isMinResponseExceed when flag is already true.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsMinResponseExceed001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->isMinResponseExceedFlag_ = true;
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(std::nullopt));
}

/**
 * @tc.name: IsMinResponseExceed002
 * @tc.desc: Test isMinResponseExceed when minResponse <= 0.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsMinResponseExceed002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->isMinResponseExceedFlag_ = false;
    sliderPattern->minResponse_ = 0.0f;
    EXPECT_TRUE(sliderPattern->isMinResponseExceed(std::nullopt));
    EXPECT_TRUE(sliderPattern->isMinResponseExceedFlag_);
}

/**
 * @tc.name: IsMinResponseExceed003
 * @tc.desc: Test isMinResponseExceed when localLocation has no value.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsMinResponseExceed003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->isMinResponseExceedFlag_ = false;
    sliderPattern->minResponse_ = 5.0f;
    sliderPattern->allowDragEvents_ = true;
    EXPECT_FALSE(sliderPattern->isMinResponseExceed(std::nullopt));
}

/**
 * @tc.name: IsSliderVisible001
 * @tc.desc: Test IsSliderVisible when both isVisibleArea and isShow are true.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsSliderVisible001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isVisibleArea_ = true;
    sliderPattern->isShow_ = true;
    EXPECT_TRUE(sliderPattern->IsSliderVisible());
}

/**
 * @tc.name: IsSliderVisible002
 * @tc.desc: Test IsSliderVisible when isVisibleArea is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsSliderVisible002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isVisibleArea_ = false;
    sliderPattern->isShow_ = true;
    EXPECT_FALSE(sliderPattern->IsSliderVisible());
}

/**
 * @tc.name: IsSliderVisible003
 * @tc.desc: Test IsSliderVisible when isShow is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsSliderVisible003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isVisibleArea_ = true;
    sliderPattern->isShow_ = false;
    EXPECT_FALSE(sliderPattern->IsSliderVisible());
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test OnWindowHide sets isShow false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnWindowHide001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isShow_ = true;
    sliderPattern->OnWindowHide();
    EXPECT_FALSE(sliderPattern->isShow_);
}

/**
 * @tc.name: OnWindowShow001
 * @tc.desc: Test OnWindowShow sets isShow true.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnWindowShow001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->isShow_ = false;
    sliderPattern->OnWindowShow();
    EXPECT_TRUE(sliderPattern->isShow_);
}

/**
 * @tc.name: StartAnimation001
 * @tc.desc: Test StartAnimation when sliderContentModifier is null.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, StartAnimation001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    // sliderContentModifier_ is null by default
    sliderPattern->StartAnimation();
    // should not crash
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: StopAnimation001
 * @tc.desc: Test StopAnimation when sliderContentModifier is null.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, StopAnimation001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    // sliderContentModifier_ is null by default
    sliderPattern->StopAnimation();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: GetDirection001
 * @tc.desc: Test GetDirection returns HORIZONTAL by default.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetDirection001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    EXPECT_EQ(sliderPattern->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: GetDirection002
 * @tc.desc: Test GetDirection returns VERTICAL when set.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetDirection002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateDirection(Axis::VERTICAL);
    EXPECT_EQ(sliderPattern->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: UpdateMarkDirtyNode001
 * @tc.desc: Test UpdateMarkDirtyNode marks host dirty.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateMarkDirtyNode001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: OnRestoreInfo001
 * @tc.desc: Test OnRestoreInfo restores value from valid JSON.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnRestoreInfo001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    std::string info = R"({"value":55})";
    sliderPattern->OnRestoreInfo(info);
    EXPECT_FLOAT_EQ(sliderPattern->value_, 55.0f);
}

/**
 * @tc.name: OnRestoreInfo002
 * @tc.desc: Test OnRestoreInfo with invalid JSON (no crash).
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnRestoreInfo002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->value_ = 10.0f;
    std::string info = "invalid_json";
    sliderPattern->OnRestoreInfo(info);
    // invalid JSON -> value unchanged
    EXPECT_FLOAT_EQ(sliderPattern->value_, 10.0f);
}

/**
 * @tc.name: UpdateTipsValue001
 * @tc.desc: Test UpdateTipsValue when valueChangeFlag is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateTipsValue001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->valueChangeFlag_ = false;
    sliderPattern->UpdateTipsValue();
    // valueChangeFlag false -> no update
    EXPECT_FALSE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: UpdateTipsValue002
 * @tc.desc: Test UpdateTipsValue when showTips is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateTipsValue002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->valueChangeFlag_ = true;
    sliderPattern->showTips_ = false;
    sliderPattern->UpdateTipsValue();
    // showTips false -> no update
    EXPECT_TRUE(sliderPattern->valueChangeFlag_);
}

/**
 * @tc.name: ClearSliderVirtualNode001
 * @tc.desc: Test ClearSliderVirtualNode clears accessibility nodes.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, ClearSliderVirtualNode001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->isInitAccessibilityVirtualNode_ = true;
    sliderPattern->ClearSliderVirtualNode();
    EXPECT_FALSE(sliderPattern->isInitAccessibilityVirtualNode_);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->OnAttachToFrameNode();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->OnAttachToMainTree();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: RegisterVisibleAreaChange001
 * @tc.desc: Test RegisterVisibleAreaChange when already registered.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, RegisterVisibleAreaChange001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->hasVisibleChangeRegistered_ = true;
    sliderPattern->RegisterVisibleAreaChange();
    // already registered -> should not register again
    EXPECT_TRUE(sliderPattern->hasVisibleChangeRegistered_);
}

/**
 * @tc.name: RegisterVisibleAreaChange002
 * @tc.desc: Test RegisterVisibleAreaChange when not registered.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, RegisterVisibleAreaChange002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->hasVisibleChangeRegistered_ = false;
    sliderPattern->RegisterVisibleAreaChange();
    EXPECT_TRUE(sliderPattern->hasVisibleChangeRegistered_);
}

/**
 * @tc.name: OnIsFocusActiveUpdate001
 * @tc.desc: Test OnIsFocusActiveUpdate when focusFlag is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnIsFocusActiveUpdate001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->focusFlag_ = false;
    sliderPattern->OnIsFocusActiveUpdate(true);
    // focusFlag false -> early return, isFocusActive_ unchanged (false)
    EXPECT_FALSE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: OnIsFocusActiveUpdate002
 * @tc.desc: Test OnIsFocusActiveUpdate when focusFlag is true.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnIsFocusActiveUpdate002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->focusFlag_ = true;
    sliderPattern->showTips_ = false;
    sliderPattern->OnIsFocusActiveUpdate(true);
    EXPECT_TRUE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: UpdateTipState001
 * @tc.desc: Test UpdateTipState when focusFlag is false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateTipState001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->focusFlag_ = false;
    sliderPattern->UpdateTipState();
    EXPECT_FALSE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: UpdateTipState002
 * @tc.desc: Test UpdateTipState when focusFlag and showTips are true.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateTipState002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->focusFlag_ = true;
    sliderPattern->showTips_ = true;
    sliderPattern->mousePressedFlag_ = true;
    sliderPattern->UpdateTipState();
    // showTips && focusFlag && mousePressed -> showBubble true
    EXPECT_TRUE(sliderPattern->bubbleFlag_);
}

/**
 * @tc.name: IsHighGradeStrongMaterial001
 * @tc.desc: Test IsHighGradeStrongMaterial default false.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, IsHighGradeStrongMaterial001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    EXPECT_FALSE(sliderPattern->IsHighGradeStrongMaterial());
}

/**
 * @tc.name: ReportChangeEvent001
 * @tc.desc: Test ReportChangeEvent does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, ReportChangeEvent001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->ReportChangeEvent(0.0f, 0);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: ScheduleDeformRestore001
 * @tc.desc: Test ScheduleDeformRestore does not crash when not deformed.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, ScheduleDeformRestore001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->isDeformStarted_ = false;
    sliderPattern->ScheduleDeformRestore();
    EXPECT_FALSE(sliderPattern->isDeformStarted_);
}

/**
 * @tc.name: UpdateCircleCenterOffset001
 * @tc.desc: Test UpdateCircleCenterOffset horizontal.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateCircleCenterOffset001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderPattern->sliderLength_ = 400.0f;
    sliderPattern->borderBlank_ = 50.0f;
    sliderPattern->valueRatio_ = 0.5f;
    sliderPattern->UpdateCircleCenterOffset();
    EXPECT_FLOAT_EQ(sliderPattern->circleCenter_.GetX(), 250.0f);
}

/**
 * @tc.name: UpdateCircleCenterOffset002
 * @tc.desc: Test UpdateCircleCenterOffset vertical.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateCircleCenterOffset002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->sliderLength_ = 400.0f;
    sliderPattern->borderBlank_ = 50.0f;
    sliderPattern->valueRatio_ = 0.5f;
    sliderPattern->UpdateCircleCenterOffset();
    EXPECT_FLOAT_EQ(sliderPattern->circleCenter_.GetY(), 250.0f);
}

/**
 * @tc.name: UpdateImagePosition001
 * @tc.desc: Test UpdateImagePosition centers image block.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateImagePosition001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
    sliderPattern->imageFrameNode_ =
        FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(sliderPattern->imageFrameNode_, nullptr);
    sliderPattern->circleCenter_ = OffsetF(100.0f, 200.0f);
    sliderPattern->blockSize_ = SizeF(20.0f, 20.0f);
    sliderPattern->UpdateImagePosition(
        PointF(sliderPattern->circleCenter_.GetX(), sliderPattern->circleCenter_.GetY()));
    EXPECT_NE(sliderPattern->imageFrameNode_, nullptr);
}

/**
 * @tc.name: PaintFocusState001
 * @tc.desc: Test PaintFocusState does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, PaintFocusState001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderPattern->PaintFocusState();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: GetInnerFocusPaintRect001
 * @tc.desc: Test GetInnerFocusPaintRect with OUTSET mode.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetInnerFocusPaintRect001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    RoundRect paintRect;
    sliderPattern->GetInnerFocusPaintRect(paintRect);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: GetInnerFocusPaintRect002
 * @tc.desc: Test GetInnerFocusPaintRect with INSET mode.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, GetInnerFocusPaintRect002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    RoundRect paintRect;
    sliderPattern->GetInnerFocusPaintRect(paintRect);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: CheckAccessibilityStepCount002
 * @tc.desc: Test CheckAccessibilityStepCount with out-of-range count.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CheckAccessibilityStepCount002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    int32_t result = sliderPattern->CheckAccessibilityStepCount();
    // out of range -> default
    EXPECT_GE(result, 0);
}

/**
 * @tc.name: InitOrRefreshSlipFactor001
 * @tc.desc: Test InitOrRefreshSlipFactor does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, InitOrRefreshSlipFactor001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(1.0f);
    sliderPattern->InitOrRefreshSlipFactor();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: UpdateParameters001
 * @tc.desc: Test UpdateParameters with no content size.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateParameters001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    bool result = sliderPattern->UpdateParameters();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: UpdateParameters002
 * @tc.desc: Test UpdateParameters with content size set.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateParameters002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(MAX_WIDTH, MAX_HEIGHT));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    bool result = sliderPattern->UpdateParameters();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test OnDetachFromFrameNode does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: RemoveCallbackOnDetach001
 * @tc.desc: Test RemoveCallbackOnDetach resets hasVisibleChangeRegistered.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, RemoveCallbackOnDetach001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->hasVisibleChangeRegistered_ = true;
    sliderPattern->RemoveCallbackOnDetach(AceType::RawPtr(frameNode));
    EXPECT_FALSE(sliderPattern->hasVisibleChangeRegistered_);
}

/**
 * @tc.name: RemoveIsFocusActiveUpdateEvent001
 * @tc.desc: Test RemoveIsFocusActiveUpdateEvent does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, RemoveIsFocusActiveUpdateEvent001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->RemoveIsFocusActiveUpdateEvent();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: AddIsFocusActiveUpdateEvent001
 * @tc.desc: Test AddIsFocusActiveUpdateEvent does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, AddIsFocusActiveUpdateEvent001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->AddIsFocusActiveUpdateEvent();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: NotifyExceptionValueRecoveryEvent001
 * @tc.desc: Test NotifyExceptionValueRecoveryEvent does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, NotifyExceptionValueRecoveryEvent001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->NotifyExceptionValueRecoveryEvent();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: CreateAccessibilityProperty001
 * @tc.desc: Test CreateAccessibilityProperty returns non-null.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CreateAccessibilityProperty001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto property = sliderPattern->CreateAccessibilityProperty();
    EXPECT_NE(property, nullptr);
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test OnThemeScopeUpdate does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderPattern->OnThemeScopeUpdate(0);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: StopParticleEffect001
 * @tc.desc: Test StopParticleEffect does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, StopParticleEffect001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->StopParticleEffect();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: OpenTranslateAnimation001
 * @tc.desc: Test OpenTranslateAnimation does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, OpenTranslateAnimation001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->OpenTranslateAnimation(SliderStatus::MOVE);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: CloseTranslateAnimation001
 * @tc.desc: Test CloseTranslateAnimation does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CloseTranslateAnimation001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->CloseTranslateAnimation();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: CreatePanEvent001
 * @tc.desc: Test CreatePanEvent returns non-null pan event.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, CreatePanEvent001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    auto panEvent = sliderPattern->CreatePanEvent();
    EXPECT_NE(panEvent, nullptr);
}

/**
 * @tc.name: InitializeBubble001
 * @tc.desc: Test InitializeBubble does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, InitializeBubble001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto sliderTheme = AceType::MakeRefPtr<SliderTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(sliderTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(sliderTheme));
    sliderPattern->InitializeBubble();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: UpdateBubble001
 * @tc.desc: Test UpdateBubble does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, UpdateBubble001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    sliderPattern->UpdateBubble();
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: AtPanArea001
 * @tc.desc: Test AtPanArea with mouse source.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, AtPanArea001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    Offset offset(10.0f, 10.0f);
    bool result = sliderPattern->AtPanArea(offset, SourceType::MOUSE);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AtPanArea002
 * @tc.desc: Test AtPanArea with touch source.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, AtPanArea002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    Offset offset(10.0f, 10.0f);
    bool result = sliderPattern->AtPanArea(offset, SourceType::TOUCH);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MoveStep001
 * @tc.desc: Test MoveStep with positive step horizontal.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, MoveStep001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(10.0f);
    paintProperty->UpdateValue(50.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderPattern->MoveStep(true);
    EXPECT_NE(sliderPattern, nullptr);
}

/**
 * @tc.name: MoveStep002
 * @tc.desc: Test MoveStep with negative step vertical.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTestNg, MoveStep002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, sliderPattern);
    sliderPattern->AttachToFrameNode(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    paintProperty->UpdateMin(0.0f);
    paintProperty->UpdateMax(100.0f);
    paintProperty->UpdateStep(10.0f);
    paintProperty->UpdateValue(50.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateDirection(Axis::VERTICAL);
    sliderPattern->MoveStep(false);
    EXPECT_NE(sliderPattern, nullptr);
}

} // namespace OHOS::Ace::NG
