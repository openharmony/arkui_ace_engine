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

#include <optional>
#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
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
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/drawing_mock.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
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
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
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
const uint32_t STEP_INDEX = 0;
const PointF SELECT_START { 10.0f, 10.0f };
const PointF SELECT_END { 20.0f, 20.0f };
const PointF POINTF_CENTER { 15.0f, 15.0f };
const OffsetF SLIDER_GLOBAL_OFFSET = { 200.0f, 200.0f };
const SizeF BLOCK_SIZE_F(10.0f, 10.0f);
const SizeF BLOCK_SIZE_F_ZREO(0.0f, 0.0f);
const Offset SLIDER_OFFSET = { 200, 200 };
constexpr float MIN_LABEL = 10.0f;
constexpr float SLIDER_LENGTH = 20.0f;
const std::vector<PointF> HORIZONTAL_STEP_POINTS { { 10, 20 }, { 20, 20 }, { 30, 20 } };
const std::vector<std::pair<std::vector<float>, int32_t>> ACCESSIBILITY_STEP_INDEX_DATA = {
    { { 100, 0, 1, 50 }, 50 }, { { 30, 0, 1.5, 19.5 }, 13 }, { { 80, 10, 8, 70.6 }, 8 }, { { 100, 0, 10, 50 }, 5 }
};
constexpr float PLAY_HAPTIC_FEEDBACK_RATIO = 1.0f;
constexpr float PLAY_HAPTIC_FEEDBACK_RATIO_HALF = 0.5f;
constexpr float PLAY_HAPTIC_FEEDBACK_RATIO_ZERO = 0.0f;
const SliderModel::SliderShowStepOptions OPTIONS_MAP = {
    { 0, "step 0" }, { 50, "step 50" }, { 1, "step 1" }, { 8, "step 8" }, { 5, "step 5" }};
} // namespace
class SliderPatternOneTestNg : public testing::Test {
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

void SliderPatternOneTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void SliderPatternOneTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SliderPatternOneTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderPatternOneTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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

void SliderPatternOneTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternOneTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternOneTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
{
    EXPECT_CALL(*paragraph, Paint(An<RSCanvas&>(), _, _)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Layout(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, AddText(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, Build()).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(1.0f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(1.0f));
}

RefPtr<SliderPattern> SliderPatternOneTestNg::AccessibilityInit(RefPtr<FrameNode>& frameNode)
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
 * @tc.name: SliderPatternAccessibilityTest005
 * @tc.desc: Test slider_pattern GetPointAccessibilityTxt
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest005, TestSize.Level1)
{
    std::vector<std::pair<std::vector<float>, std::string>> testData { { { 1, 0.01, 0, 100 }, "0.01" } };
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    for (const auto& item : testData) {
        /**
         * @tc.steps: step2. Get point accessibility text.
         */
        auto text = sliderPattern->GetPointAccessibilityTxt(item.first[0], item.first[1], item.first[2], item.first[3]);
        EXPECT_EQ(text, item.second);
    }
}

/**
 * @tc.name: SliderPatternAccessibilityTest006
 * @tc.desc: Test slider_pattern SetStepPointAccessibilityVirtualNode/HandleTextOnAccessibilityFocusCallback
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto sliderNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(sliderNode, nullptr);
    auto sliderPattern = sliderNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(sliderNode);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    /**
     * @tc.steps: step2. Set step points virtual node property.
     */
    sliderPattern->SetStepPointAccessibilityVirtualNode(
        frameNode, CONTAINER_SIZE, POINTF_START, SLIDER_MODEL_NG_BLOCK_IMAGE, STEP_INDEX);
    auto pointNodeProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(pointNodeProperty, nullptr);
    auto expectSize = CalcSize(CalcLength(CONTAINER_SIZE.Width()), CalcLength(CONTAINER_SIZE.Height()));
    EXPECT_EQ(pointNodeProperty->calcLayoutConstraint_->selfIdealSize, std::optional<CalcSize>(expectSize));
    EXPECT_EQ(pointNodeProperty->GetContent(),
        std::optional<std::u16string>(StringUtils::Str8ToStr16(SLIDER_MODEL_NG_BLOCK_IMAGE)));

    /**
     * @tc.steps: step3. Get frameNode property.
     */
    auto context = frameNode->GetRenderContext();
    ASSERT_NE(context, nullptr);
    ASSERT_NE(context->GetPosition(), std::nullopt);
    EXPECT_EQ(context->GetPosition()->GetX().Value(), POINTF_START.GetX());
    EXPECT_EQ(context->GetPosition()->GetY().Value(), POINTF_START.GetY());

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityText(), SLIDER_MODEL_NG_BLOCK_IMAGE);

    /**
     * @tc.steps: step4. Trigger accessibility focus callback.
     */
    accessibilityProperty->OnAccessibilityFocusCallback(true);
    auto sliderAccessibilityProperty = sliderNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(sliderAccessibilityProperty, nullptr);
    EXPECT_EQ(sliderAccessibilityProperty->accessibilityLevel_, std::nullopt);
}

/**
 * @tc.name: SliderPatternAccessibilityTest007
 * @tc.desc: Test slider_pattern InitAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;

    sliderPattern->InitAccessibilityVirtualNode();
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    EXPECT_EQ(sliderPattern->pointAccessibilityNodeVec_.size(), HORIZONTAL_STEP_POINTS.size());
}

/**
 * @tc.name: SliderPatternAccessibilityTest009
 * @tc.desc: Test slider_pattern AccessibilityVirtualNodeRenderTask
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateShowSteps(true);

    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->context_ = reinterpret_cast<PipelineContext*>(Referenced::RawPtr(context));
    sliderPattern->InitAccessibilityVirtualNodeTask();
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    EXPECT_EQ(sliderPattern->pointAccessibilityNodeVec_.size(), HORIZONTAL_STEP_POINTS.size());
    sliderPattern->AccessibilityVirtualNodeRenderTask();
}

/**
 * @tc.name: SliderPatternAccessibilityTest010
 * @tc.desc: Test slider_pattern UpdateParentNodeSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    /**
     * @tc.steps: step2. Create virtual parent node.
     */
    if (!sliderPattern->parentAccessibilityNode_) {
        sliderPattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    }
    auto parent = sliderPattern->parentAccessibilityNode_;
    ASSERT_NE(parent, nullptr);
    /**
     * @tc.steps: step3. Init ContentModifier and set step point.
     */
    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;
    /**
     * @tc.steps: step4. Add Slider virtual child node.
     */
    sliderPattern->AddStepPointsAccessibilityVirtualNode();
    /**
     * @tc.steps: step5. Update parent virtualNode width and height.
     */
    sliderPattern->sliderLength_ = SLIDER_LENGTH;
    sliderPattern->UpdateParentNodeSize();
    /**
     * @tc.steps: step6. Set compare value.
     */
    auto hSize = sliderPattern->GetStepPointAccessibilityVirtualNodeSize();
    auto width = hSize.Width() * HORIZONTAL_STEP_POINTS.size();
    auto height = hSize.Height();
    /**
     * @tc.steps: step7. Get CalcLayoutConstraint.
     */
    auto rowProperty = parent->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(rowProperty, nullptr);
    const auto& calConstraint = rowProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calConstraint, nullptr);
    /**
     * @tc.steps: step8. ASSERT Parent node width and height be set successfully.
     */
    EXPECT_EQ(calConstraint->selfIdealSize->Width(), NG::CalcLength(Dimension(width)));
    EXPECT_EQ(calConstraint->selfIdealSize->Height(), NG::CalcLength(Dimension(height)));
}

/**
 * @tc.name: SliderPatternAccessibilityTest011
 * @tc.desc: Test slider_pattern GetOffsetStepIndex
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest011, TestSize.Level1)
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
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateValue(4.1f);
    sliderPaintProperty->UpdateMin(3.0f);
    sliderPaintProperty->UpdateMax(8.0f);
    sliderPaintProperty->UpdateStep(1.5f);
    ASSERT_EQ(sliderPattern->GetOffsetStepIndex(2), 2);
    ASSERT_EQ(sliderPattern->GetOffsetStepIndex(3), 3);
    ASSERT_EQ(sliderPattern->GetOffsetStepIndex(4), 4);
    ASSERT_EQ(sliderPattern->GetOffsetStepIndex(0), -1);
    sliderPaintProperty->UpdateStep(0.0f);
    ASSERT_EQ(sliderPattern->GetOffsetStepIndex(4), 0);
}

/**
 * @tc.name: SliderPatternAccessibilityTest012
 * @tc.desc: Test slider_pattern SetUpdateAccessibilityCallback
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternAccessibilityTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->AttachToFrameNode(frameNode);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FRAME_WIDTH, FRAME_HEIGHT));
    /**
     * @tc.steps: step2. Create virtual parent node.
     */
    if (!sliderPattern->parentAccessibilityNode_) {
        sliderPattern->parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    }
    auto parent = sliderPattern->parentAccessibilityNode_;
    ASSERT_NE(parent, nullptr);
    /**
     * @tc.steps: step3. Add Slider virtual child node.
     */
    sliderPattern->AddStepPointsAccessibilityVirtualNode();
    /**
     * @tc.steps: step4. Init ContentModifier and set step point.
     */
    EXPECT_FALSE(sliderPattern->InitAccessibilityVirtualNode());
    if (!sliderPattern->sliderContentModifier_) {
        sliderPattern->sliderContentModifier_ =
            AceType::MakeRefPtr<SliderContentModifier>(SliderContentModifier::Parameters(), nullptr);
    }
    auto contentModifier = sliderPattern->sliderContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    contentModifier->stepPointVec_ = HORIZONTAL_STEP_POINTS;
    EXPECT_TRUE(sliderPattern->InitAccessibilityVirtualNode());
    sliderPattern->InitAccessibilityVirtualNode();
    ASSERT_NE(contentModifier->updateAccessibilityVirtualNode_, nullptr);
}

/**
 * @tc.name: SliderPatternTest023
 * @tc.desc: Test slider_pattern HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest023, TestSize.Level1)
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
     * @tc.steps: step2. call HandleHoverEvent hover true with normal.
     * @tc.expected: step3. sliderPattern->sliderContentModifier_->isHovered_ is true.
     */
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->HandleHoverEvent(true);
    ASSERT_TRUE(sliderPattern->sliderContentModifier_->isHovered_);

    /**
     * @tc.steps: step3. call HandleHoverEvent hover false with focus false.
     * @tc.expected: step4. sliderPattern->sliderContentModifier_->isHovered_ is false.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->axisFlag_ = false;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(false);
    ASSERT_TRUE(sliderPattern->sliderContentModifier_->isHovered_);

    /**
     * @tc.steps: step5. call HandleHoverEvent hover true.
     * @tc.expected: step5. sliderPattern->sliderContentModifier_->isHovered_ is true.
     */
    sliderPattern->bubbleFlag_ = true;
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->mousePressedFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->HandleHoverEvent(true);
    ASSERT_TRUE(sliderPattern->sliderContentModifier_->isHovered_);
}

/**
 * @tc.name: SliderPatternTest024
 * @tc.desc: SliderPattern::HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest024, TestSize.Level1)
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
    EXPECT_EQ(sliderPattern->sliderContentModifier_->isHovered_->Get(), true);
 
    /**
     * @tc.steps: step4. Mouse not on slider block.
     * @tc.expected: step4. sliderPattern->bubbleFlag_ is false.
     */
    sliderPattern->blockSize_ = SizeF(0, 0);
    sliderPattern->HandleMouseEvent(mouseInfo);
    ASSERT_FALSE(sliderPattern->bubbleFlag_);
    EXPECT_EQ(sliderPattern->sliderContentModifier_->isHovered_->Get(), false);
}

/**
 * @tc.name: SliderPatternTest025
 * @tc.desc: SliderPattern::HandleTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest025, TestSize.Level1)
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
     * @tc.steps: step4. Test HandleTouchDown.
     */
    auto localLocation = Offset(MIN, MIN_LABEL);
    TouchEventInfo infoDown("onTouchDown");
    TouchLocationInfo touchDownInfo(0);
    touchDownInfo.SetTouchType(TouchType::DOWN);
    infoDown.AddTouchLocationInfo(std::move(touchDownInfo));
    sliderPattern->fingerId_ = -1;
    sliderPattern->HandleTouchEvent(infoDown);
    sliderPattern->HandleTouchDown(localLocation, SourceType::TOUCH);
    EXPECT_EQ(sliderPattern->axisFlag_, false);
    EXPECT_EQ(sliderPattern->mousePressedFlag_, true);
    EXPECT_EQ(sliderPattern->sliderContentModifier_->isPressed_->Get(), true);
 
    /**
     * @tc.steps: step4. Test HandleTouchUp.
     */
    TouchEventInfo infoUp("onTouchUp");
    TouchLocationInfo touchUpInfo(1);
    touchUpInfo.SetTouchType(TouchType::UP);
    infoUp.AddTouchLocationInfo(std::move(touchUpInfo));
    sliderPattern->HandleTouchEvent(infoUp);
    sliderPattern->HandleTouchUp(localLocation, SourceType::TOUCH);
    EXPECT_EQ(sliderPattern->mousePressedFlag_, false);
    EXPECT_EQ(sliderPattern->sliderContentModifier_->isPressed_->Get(), false);
}

/**
 * @tc.name: SliderPatternTest026
 * @tc.desc: SliderPattern::SetPrefix.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init Slider node.
     */
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);

    RefPtr<NG::UINode> prefix;
    SliderPrefixOptions options;

    sliderPattern->SetPrefix(prefix, options);

    EXPECT_FALSE(sliderPattern->prefixNodeStack_);
    EXPECT_EQ(sliderPattern->prefix_.Upgrade(), prefix);
}

/**
 * @tc.name: SliderPatternTest028
 * @tc.desc: SliderPattern::UpdateEndsNotShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest028, TestSize.Level1)
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
    PointF testPosition;
    PointF block(100, 50);
    SizeF prefixSize(20, 20);
    float noneOffset = 50;
    float outsetOffset = 40;
    sliderPattern->GetLayoutProperty<SliderLayoutProperty>()->UpdateDirection(Axis::HORIZONTAL);
    sliderPattern->GetLayoutProperty<SliderLayoutProperty>()->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    sliderPattern->UpdateEndsNotShowStepsPosition(testPosition, block, prefixSize, noneOffset, outsetOffset);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_FLOAT_EQ(testPosition.GetX(), 100 - 10 - 40); // block.X - size/2 - outsetOffset
    EXPECT_FLOAT_EQ(testPosition.GetY(), 50 - 10);       // block.Y - size/2
}

/**
 * @tc.name: SliderPatternTest029
 * @tc.desc: SliderPattern::UpdateEndsNotShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest029, TestSize.Level1)
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
    sliderPattern->GetLayoutProperty<SliderLayoutProperty>()->UpdateDirection(Axis::VERTICAL);
    sliderPattern->GetLayoutProperty<SliderLayoutProperty>()->UpdateReverse(true);

    PointF testPosition;
    PointF block(80, 120);
    SizeF suffixSize(30, 30);
    float noneOffset = -50;
    float outsetOffset = -40;

    sliderPattern->UpdateEndsNotShowStepsPosition(testPosition, block, suffixSize, noneOffset, outsetOffset);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_FLOAT_EQ(testPosition.GetX(), 80 - 15);          // block.X - size/2
    EXPECT_FLOAT_EQ(testPosition.GetY(), 120 - 15 - (-40)); // block.Y - size/2 - outsetOffset
}

/**
 * @tc.name: SliderPatternTest030
 * @tc.desc: SliderPattern::UpdateEndsIsShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest030, TestSize.Level1)
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
    sliderPattern->stepPoints_.emplace_back(PointF(10, 20));
    sliderPattern->stepPoints_.emplace_back(PointF(30, 40));
    sliderPattern->stepPoints_.emplace_back(PointF(50, 60));

    sliderPattern->GetPaintProperty<SliderPaintProperty>()->UpdateShowSteps(true);
    sliderPattern->side_ = false;

    PointF testPosition;
    PointF block(0, 0);
    SizeF endsSize(20, 20);
    float outsetOffset = 40;

    sliderPattern->GetLayoutProperty<SliderLayoutProperty>()->UpdateSliderMode(SliderModel::SliderMode::NONE);
    sliderPattern->UpdateEndsIsShowStepsPosition(testPosition, block, endsSize, outsetOffset, false);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_FLOAT_EQ(testPosition.GetX(), 30 - 10); // stepPoints_[1].x - size/2
    EXPECT_FLOAT_EQ(testPosition.GetY(), 40 - 10); // stepPoints_[1].y - size/2
}

/**
 * @tc.name: SliderPatternTest031
 * @tc.desc: SliderPattern::UpdateEndsIsShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest031, TestSize.Level1)
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
    sliderPattern->stepPoints_.clear();
    sliderPattern->GetPaintProperty<SliderPaintProperty>()->UpdateShowSteps(true);

    PointF testPosition;
    PointF block(0, 0);
    SizeF endsSize(20, 20);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_NO_FATAL_FAILURE(sliderPattern->UpdateEndsIsShowStepsPosition(testPosition, block, endsSize, 40, true));
}

/**
 * @tc.name: EnableHapticFeedbackTest001
 * @tc.desc: Test SliderModelNG GetEnableHapticFeedback SetEnableHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, EnableHapticFeedbackTest001, TestSize.Level1)
{
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    sliderModelNG.SetBlockColor(TEST_COLOR);
    sliderModelNG.SetTrackBackgroundColor(SliderModelNG::CreateSolidGradient(TEST_COLOR));
    sliderModelNG.SetSelectColor(TEST_COLOR);
    sliderModelNG.SetEnableHapticFeedback(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(sliderModelNG.GetEnableHapticFeedback(Referenced::RawPtr(frameNode)));
}

/**
 * @tc.name: PlayHapticFeedbackTest001
 * @tc.desc: Test PlayHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, PlayHapticFeedbackTest001, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isEnableHaptic_ = false;
    sliderPattern->PlayHapticFeedback(false);
    sliderPattern->isEnableHaptic_ = true;
    auto host = sliderPattern->GetHost();
    CHECK_NULL_VOID(host);
    host->apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN);
    sliderPattern->valueRatio_ = PLAY_HAPTIC_FEEDBACK_RATIO_HALF;
    sliderPattern->PlayHapticFeedback(true);
    sliderPattern->valueRatio_ = PLAY_HAPTIC_FEEDBACK_RATIO_ZERO;
    sliderPattern->PlayHapticFeedback(false);
    sliderPattern->valueRatio_ = PLAY_HAPTIC_FEEDBACK_RATIO;
    sliderPattern->PlayHapticFeedback(true);
    EXPECT_TRUE(sliderPattern->isEnableHaptic_);
}

/**
 * @tc.name: SliderPatternTest032
 * @tc.desc: SliderPattern::CreateNodePaintMethod&endsInitFlag_.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest032, TestSize.Level1)
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
    sliderPattern->endsInitFlag_ = false;
    sliderPattern->CreateNodePaintMethod();

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_EQ(sliderPattern->endsInitFlag_, false);
}

/**
 * @tc.name: SliderPatternTest033
 * @tc.desc: SliderPattern::UpdateEndsIsShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest033, TestSize.Level1)
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
    sliderPattern->stepPoints_.clear();
    sliderPattern->GetPaintProperty<SliderPaintProperty>()->UpdateShowSteps(true);

    PointF testPosition;
    PointF block(20, 20);
    SizeF endsSize(20, 20);

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_NO_FATAL_FAILURE(sliderPattern->UpdateEndsIsShowStepsPosition(testPosition, block, endsSize, 40, true));
}

/**
 * @tc.name: PlayHapticFeedbackTest002
 * @tc.desc: Test PlayHapticFeedback
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, PlayHapticFeedbackTest002, TestSize.Level1)
{
    RefPtr<SliderPattern> sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->SetEnableHapticFeedback(true);
    sliderPattern->PlayHapticFeedback(false);
    sliderPattern->PlayHapticFeedback(true);
    EXPECT_TRUE(sliderPattern->isEnableHaptic_);
}

/**
 * @tc.name: SliderPatternTest034
 * @tc.desc: SliderPattern::UpdateEndsIsShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest034, TestSize.Level1)
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
    sliderPattern->stepPoints_.clear();
    sliderPattern->GetPaintProperty<SliderPaintProperty>()->UpdateShowSteps(true);

    PointF testPosition(0, 0);
    PointF block(0, 0);
    SizeF endsSize(0, 0);
    bool side = true;

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_NO_FATAL_FAILURE(sliderPattern->UpdateEndsIsShowStepsPosition(testPosition, block, endsSize, 0, side));
}

/**
 * @tc.name: SliderPatternTest035
 * @tc.desc: SliderPattern::UpdateEndsIsShowStepsPosition.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest035, TestSize.Level1)
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
    sliderPattern->stepPoints_.clear();
    sliderPattern->GetPaintProperty<SliderPaintProperty>()->UpdateShowSteps(true);

    PointF testPosition(0, 0);
    PointF block(0, 0);
    SizeF endsSize(0, 0);
    bool side = false;

    /**
     * @tc.steps: step3. Check the param value.
     */
    EXPECT_NO_FATAL_FAILURE(sliderPattern->UpdateEndsIsShowStepsPosition(testPosition, block, endsSize, 0, side));
}

/**
 * @tc.name: UpdateStepPointsAccessibilityText001
 * @tc.desc: Test slider_pattern UpdateStepPointsAccessibilityText001
 * UpdateStepPointsAccessibilityText
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, UpdateStepPointsAccessibilityText001, TestSize.Level1)
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
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    auto options = OPTIONS_MAP;
    for (const auto& item : ACCESSIBILITY_STEP_INDEX_DATA) {
        sliderPaintProperty->UpdateMax(item.first[0]);
        sliderPaintProperty->UpdateMin(item.first[1]);
        sliderPaintProperty->UpdateStep(item.first[2]);
        sliderPaintProperty->UpdateValue(item.first[3]);
        for (int32_t i = 0; i < sliderPattern->pointAccessibilityNodeVec_.size(); i++) {
            auto node = sliderPattern->pointAccessibilityNodeVec_[i];
            ASSERT_NE(node, nullptr);
            sliderPattern->UpdateStepPointsAccessibilityText(node, i, options);
            auto pointAccessibilityProperty = node->GetAccessibilityProperty<TextAccessibilityProperty>();
            ASSERT_NE(pointAccessibilityProperty, nullptr);
            auto pointNodeProperty = node->GetLayoutProperty<TextLayoutProperty>();
            ASSERT_NE(pointNodeProperty, nullptr);
            auto text = options.find(i) != options.end() ?
                options[i] : StringUtils::Str16ToStr8(pointNodeProperty->GetContent().value_or(u""));
            EXPECT_EQ(pointAccessibilityProperty->GetAccessibilityText(), text);
        }
    }
}

/**
 * @tc.name: SliderPatternTest036
 * @tc.desc: Test Slider OnDetachFromFrameNodeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest036, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->OnDetachFromFrameNodeMultiThread();
}

/**
 * @tc.name: SliderPatternTest037
 * @tc.desc: Test Slider OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest037, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->OnDetachFromMainTree();
}

/**
 * @tc.name: SliderPatternTest038
 * @tc.desc: Test Slider OnDetachFromMainTreeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, SliderPatternTest038, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, -1, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->OnDetachFromMainTreeMultiThread(frameNode);
}

/**
 * @tc.name: UpdateSliderComponentColor001
 * @tc.desc: test UpdateSliderComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, UpdateSliderComponentColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdateSliderComponentColor under different system color change and rerenderable states.
     * @tc.expected: step2. All slider component colors are updated to RED when system color changes and node is
     * rerenderable.
     */
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        frameNode->SetRerenderable(pair.second);
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            Gradient gradientRes;
            gradientRes.AddColor(GradientColor(Color::RED));
            pattern->UpdateSliderComponentColor(Color::RED, SliderColorType::BLOCK_COLOR, gradientRes);
            auto ret = paintProperty->GetBlockColor();
            EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
            pattern->UpdateSliderComponentColor(Color::RED, SliderColorType::SELECT_COLOR, gradientRes);
            ret = paintProperty->GetSelectColor();
            EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
            pattern->UpdateSliderComponentColor(Color::RED, SliderColorType::BLOCK_BORDER_COLOR, gradientRes);
            ret = paintProperty->GetBlockBorderColor();
            EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
            pattern->UpdateSliderComponentColor(Color::RED, SliderColorType::STEP_COLOR, gradientRes);
            ret = paintProperty->GetStepColor();
            EXPECT_EQ(ret.value_or(Color::BLACK), Color::RED);
            pattern->UpdateSliderComponentColor(Color::RED, SliderColorType::TRACK_COLOR, gradientRes);
            auto gradientRet = paintProperty->GetTrackBackgroundColor();
            EXPECT_EQ(gradientRet, gradientRes);
        }
    }
}

/**
 * @tc.name: UpdateSliderComponentString001
 * @tc.desc: test UpdateSliderComponentString.
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternOneTestNg, UpdateSliderComponentString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create slider frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    SliderModelNG sliderModelNG;
    sliderModelNG.Create(VALUE, STEP, MIN, MAX);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto pattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdateSliderComponentString under different system color change and rerenderable states.
     * @tc.expected: step2. Slider shows tips when system color changes and node is rerenderable.
     */
    std::vector<std::pair<bool, bool>> vec { { true, true }, { true, false }, { false, true }, { false, false } };
    for (const auto& pair : vec) {
        pipelineContext->SetIsSystemColorChange(pair.first);
        frameNode->SetRerenderable(pair.second);
        if (pipelineContext->IsSystmColorChange() && pair.second) {
            pattern->UpdateSliderComponentMedia();
            pattern->UpdateSliderComponentString(true, "test");
            EXPECT_TRUE(paintProperty->GetShowTips());
        }
    }
}
} // namespace OHOS::Ace::NG
