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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/rosen/mock_canvas.h"

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
#include "core/components_ng/pattern/root/root_pattern.h"
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
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color TEST_COLOR = Color::BLUE;
const PointF POINTF_START { 10.0f, 10.0f };
const PointF POINTF_END { 20.0f, 20.0f };
constexpr Dimension SLIDER_THICKNRESS = Dimension(10.0);
constexpr Dimension BORDER_WIDTH = Dimension(15.0);
constexpr Dimension STEP_SIZE = Dimension(2.0);
constexpr Dimension TRACK_BORDER_RADIUS = Dimension(5.0);
constexpr Dimension SELECT_BORDER_RADIUS = Dimension(5.0);
constexpr Dimension BLOCK_SIZE_WIDTH = Dimension(300.0);
constexpr Dimension BLOCK_SIZE_HEIGHT = Dimension(300.0);
constexpr int32_t NODE_ID = 1;
constexpr int32_t FRAMENODE_ID = 2;
constexpr int32_t MUMBER_ONE = 1;
constexpr int32_t MUMBER_TWO = 2;
constexpr float FLOAT_ZERO = 0.0f;
constexpr float FLOAT_ONE = 1.0f;
constexpr float FLOAT_FIVE = 5.0f;
constexpr float FLOAT_TEN = 10.0f;
constexpr float FLOAT_TWENTY = 20.0f;
constexpr float FLOAT_FIFTY = 50.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_SELECTED_BORDER_RADIUS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_SIZE = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_TRACK_THICKNESS = 10.0f;
constexpr float SLIDER_CONTENT_MODIFIER_STEP_RATIO = 10000.0f;
const std::string SLIDER_MODEL_NG_BLOCK_IMAGE = "Default Image";
const SizeT<Dimension> BLOCK_SIZE(BLOCK_SIZE_WIDTH, BLOCK_SIZE_HEIGHT);
} // namespace

class SliderPatternTwoTestNg : public testing::Test {
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

void SliderPatternTwoTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SliderTheme>()));
}

void SliderPatternTwoTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SliderPatternTwoTestNg::TearDown()
{
    MockParagraph::TearDown();
}

void SliderPatternTwoTestNg::SetSliderContentModifier(SliderContentModifier& sliderContentModifier)
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

void SliderPatternTwoTestNg::MockCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternTwoTestNg::MockTipsCanvasFunction(Testing::MockCanvas& canvas)
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

void SliderPatternTwoTestNg::MockParagraphFunction(RefPtr<MockParagraph>& paragraph, Testing::MockCanvas& canvas)
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
 * @tc.name: SliderPatternTwoTest001
 * @tc.desc: Test HandleEnabled
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest001, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPattern);
    sliderPattern->HandleEnabled();
    EXPECT_TRUE(sliderPattern->UseContentModifier());
}

/**
 * @tc.name: SliderPatternTwoTest002
 * @tc.desc: Test HandleEnabled
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest002, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    sliderPattern->HandleEnabled();
    EXPECT_FALSE(sliderPattern->UseContentModifier());
}

/**
 * @tc.name: SliderPatternTwoTest003
 * @tc.desc: Test HandleEnabled
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest003, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(frameNode->eventHub_, nullptr);
    frameNode->eventHub_->enabled_ = true;
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    ASSERT_NE(frameNode->renderContext_, nullptr);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->HandleEnabled();
    EXPECT_FALSE(sliderPattern->UseContentModifier());
}

/**
 * @tc.name: SliderPatternTwoTest004
 * @tc.desc: Test HandleEnabled
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest004, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(frameNode->eventHub_, nullptr);
    frameNode->eventHub_->enabled_ = false;
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    auto renderContext = frameNode->renderContext_;
    ASSERT_NE(renderContext, nullptr);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->HandleEnabled();
    EXPECT_FALSE(renderContext->propOpacity_.has_value());
}

/**
 * @tc.name: SliderPatternTwoTest005
 * @tc.desc: Test InitAccessibilityHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest005, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityProperty_ = AceType::MakeRefPtr<AccessibilityProperty>();
    auto accessibilityProperty = frameNode->accessibilityProperty_;
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->accessibilityLevel_ = AccessibilityProperty::Level::NO_HIDE_DESCENDANTS;
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->InitAccessibilityHoverEvent();
    EXPECT_TRUE(sliderPattern->pointAccessibilityNodeVec_.empty());
    EXPECT_TRUE(sliderPattern->pointAccessibilityNodeEventVec_.empty());
    EXPECT_FALSE(sliderPattern->isInitAccessibilityVirtualNode_);
}

/**
 * @tc.name: SliderPatternTwoTest006
 * @tc.desc: Test InitAccessibilityVirtualNodeTask
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest006, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isInitAccessibilityVirtualNode_ = true;
    sliderPattern->InitAccessibilityVirtualNodeTask();
    EXPECT_FALSE(sliderPattern->CheckCreateAccessibilityVirtualNode());
}

/**
 * @tc.name: SliderPatternTwoTest007
 * @tc.desc: Test AccessibilityVirtualNodeRenderTask
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest007, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isInitAccessibilityVirtualNode_ = true;
    sliderPattern->AccessibilityVirtualNodeRenderTask();
    EXPECT_FALSE(sliderPattern->CheckCreateAccessibilityVirtualNode());
}

/**
 * @tc.name: SliderPatternTwoTest008
 * @tc.desc: Test CheckCreateAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest008, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = AceType::MakeRefPtr<SliderPaintProperty>();
    ASSERT_NE(frameNode->paintProperty_, nullptr);
    frameNode->accessibilityProperty_ = AceType::MakeRefPtr<AccessibilityProperty>();
    auto accessibilityProperty = frameNode->accessibilityProperty_;
    ASSERT_NE(accessibilityProperty, nullptr);
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    sliderPattern->contentModifierNode_ = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPattern);
    sliderPattern->frameNode_ = std::move(frameNode);
    EXPECT_FALSE(sliderPattern->CheckCreateAccessibilityVirtualNode());
}

/**
 * @tc.name: SliderPatternTwoTest009
 * @tc.desc: Test CheckCreateAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest009, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->paintProperty_ = AceType::MakeRefPtr<SliderPaintProperty>();
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    frameNode->accessibilityProperty_ = AceType::MakeRefPtr<AccessibilityProperty>();
    auto accessibilityProperty = frameNode->accessibilityProperty_;
    ASSERT_NE(accessibilityProperty, nullptr);
    AceApplicationInfo::GetInstance().isAccessibilityEnabled_ = true;
    sliderPattern->contentModifierNode_ = nullptr;
    sliderPaintProperty->UpdateShowSteps(true);
    accessibilityProperty->accessibilityLevel_ = AccessibilityProperty::Level::NO_HIDE_DESCENDANTS;
    sliderPattern->frameNode_ = std::move(frameNode);
    EXPECT_FALSE(sliderPattern->CheckCreateAccessibilityVirtualNode());
}

/**
 * @tc.name: SliderPatternTwoTest010
 * @tc.desc: Test UpdateParentNodeSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest010, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->parentAccessibilityNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    sliderPattern->parentAccessibilityNode_->layoutProperty_ = AceType::MakeRefPtr<LinearLayoutProperty>(true);
    auto rowProperty = sliderPattern->parentAccessibilityNode_->layoutProperty_;
    ASSERT_NE(rowProperty, nullptr);
    sliderPattern->UpdateParentNodeSize();
    EXPECT_EQ(rowProperty->propertyChangeFlag_, MUMBER_ONE);
}

/**
 * @tc.name: SliderPatternTwoTest011
 * @tc.desc: Test ModifyAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest011, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.clear();
    sliderPattern->ModifyAccessibilityVirtualNode();
    EXPECT_TRUE(sliderPattern->pointAccessibilityNodeVec_.empty());
}

/**
 * @tc.name: SliderPatternTwoTest012
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest012, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPatternOne = AceType::MakeRefPtr<SliderPattern>();
    sliderPattern->parentAccessibilityNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPatternOne);
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    auto accessibilityNodeOne =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeOne, nullptr);
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_ZERO);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(sliderPattern->pointAccessibilityNodeVec_.size(), MUMBER_TWO);
}

/**
 * @tc.name: SliderPatternTwoTest013
 * @tc.desc: Test GetStepPointAccessibilityVirtualNodeSize
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest013, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->GetStepPointAccessibilityVirtualNodeSize();
    EXPECT_EQ(sliderPattern->GetStepPointAccessibilityVirtualNodeSize().width_, 0.0f);
}

/**
 * @tc.name: SliderPatternTwoTest014
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest014, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    sliderPattern->panEvent_ = nullptr;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    WeakPtr<EventHub> eventHubWeakPtr = std::move(eventHub);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    sliderPattern->InitPanEvent(gestureHub);
    sliderPattern->contentModifierNode_ = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPattern);
    sliderPattern->panEvent_ = AceType::MakeRefPtr<PanEvent>(
        [](const GestureEvent& event) {}, [](const GestureEvent& event) {}, [](const GestureEvent& event) {}, []() {});
    sliderPattern->InitPanEvent(gestureHub);
    EXPECT_EQ(sliderPattern->panEvent_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest015
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest015, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    sliderPattern->direction_ = Axis::VERTICAL;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    WeakPtr<EventHub> eventHubWeakPtr = std::move(eventHub);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    sliderPattern->InitPanEvent(gestureHub);
    EXPECT_NE(sliderPattern->panEvent_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest016
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest016, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    sliderPattern->panEvent_ = nullptr;
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->isInitAccessibilityVirtualNode_ = true;
    sliderPattern->frameNode_ = std::move(frameNode);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    WeakPtr<EventHub> eventHubWeakPtr = std::move(eventHub);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    sliderPattern->InitPanEvent(gestureHub);
    EXPECT_TRUE(sliderPattern->pointAccessibilityNodeVec_.empty());
    EXPECT_TRUE(sliderPattern->pointAccessibilityNodeEventVec_.empty());
    EXPECT_FALSE(sliderPattern->isInitAccessibilityVirtualNode_);
}

/**
 * @tc.name: SliderPatternTwoTest017
 * @tc.desc: Test InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest017, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    sliderPattern->panEvent_ = nullptr;
    sliderPattern->direction_ = Axis::VERTICAL;
    sliderPattern->isInitAccessibilityVirtualNode_ = false;
    sliderPattern->frameNode_ = std::move(frameNode);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    WeakPtr<EventHub> eventHubWeakPtr = std::move(eventHub);
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHubWeakPtr);
    sliderPattern->InitPanEvent(gestureHub);
    EXPECT_EQ(sliderPattern->direction_, Axis::HORIZONTAL);
}

/**
 * @tc.name: SliderPatternTwoTest018
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest018, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateValue(FLOAT_ONE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Value: 1.000000\n");
}

/**
 * @tc.name: SliderPatternTwoTest019
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest019, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, 12, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateMin(FLOAT_ZERO);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Min: 0.000000\n");
}

/**
 * @tc.name: SliderPatternTwoTest020
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest020, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateMax(FLOAT_FIFTY);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Max: 50.000000\n");
}

/**
 * @tc.name: SliderPatternTwoTest021
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest021, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Step: 5.000000\n");
}

/**
 * @tc.name: SliderPatternTwoTest022
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest022, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Style: OUTSET\n");
}

/**
 * @tc.name: SliderPatternTwoTest023
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest023, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Direction: HORIZONTAL\n");
}

/**
 * @tc.name: SliderPatternTwoTest024
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest024, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateReverse(true);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Reverse: true\n");
}

/**
 * @tc.name: SliderPatternTwoTest025
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest025, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateBlockColor(Color::RED);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockColor: #FFFF0000\n");
}

/**
 * @tc.name: SliderPatternTwoTest026
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest026, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Gradient gradient;
    GradientColor color(Color::BLACK);
    gradient.AddColor(color);
    sliderPaintProperty->UpdateTrackBackgroundColor(gradient);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "TrackBackgroundColor: #00000000 \n");
}

/**
 * @tc.name: SliderPatternTwoTest027
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest027, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateSelectColor(Color::GRAY);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "SelectColor: #FFC0C0C0\n");
}

/**
 * @tc.name: SliderPatternTwoTest028
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest028, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateMinResponsiveDistance(FLOAT_TWENTY);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "MinResponsiveDistance: 20.000000\n");
}

/**
 * @tc.name: SliderPatternTwoTest029
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest029, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateShowSteps(true);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "ShowSteps: true\n");
}

/**
 * @tc.name: SliderPatternTwoTest030
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest030, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateShowTips(true);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "ShowTips: true\n");
}

/**
 * @tc.name: SliderPatternTwoTest031
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest031, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateThickness(SLIDER_THICKNRESS);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "Thickness: 10.00px\n");
}

/**
 * @tc.name: SliderPatternTwoTest032
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest032, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateBlockBorderColor(Color::BLUE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockBorderColor: #FF0000FF\n");
}

/**
 * @tc.name: SliderPatternTwoTest033
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest033, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateBlockBorderWidth(BORDER_WIDTH);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockBorderWidth: 15.00px\n");
}

/**
 * @tc.name: SliderPatternTwoTest034
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest034, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateStepColor(Color::GREEN);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "StepColor: #FF00FF00\n");
}

/**
 * @tc.name: SliderPatternTwoTest035
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest035, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateStepSize(STEP_SIZE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "StepSize: 2.00px\n");
}

/**
 * @tc.name: SliderPatternTwoTest036
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest036, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateTrackBorderRadius(TRACK_BORDER_RADIUS);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "TrackBorderRadius: 5.00px\n");
}

/**
 * @tc.name: SliderPatternTwoTest037
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest037, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateSelectedBorderRadius(SELECT_BORDER_RADIUS);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "SelectedBorderRadius: 5.00px\n");
}

/**
 * @tc.name: SliderPatternTwoTest038
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest038, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    layoutProperty->UpdateBlockSize(BLOCK_SIZE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockSize: [300.00px x 300.00px]\n");
}

/**
 * @tc.name: SliderPatternTwoTest039
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest039, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateBlockType(SliderModel::BlockStyleType::SHAPE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockType: SHAPE\n");
}

/**
 * @tc.name: SliderPatternTwoTest040
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest040, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateBlockImage(SLIDER_MODEL_NG_BLOCK_IMAGE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockImage: Default Image\n");
}

/**
 * @tc.name: SliderPatternTwoTest041
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest041, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    paintProperty->UpdateSliderInteractionMode(SliderModel::SliderInteraction::SLIDE_AND_CLICK);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "SliderInteractionMode: SLIDE_AND_CLICK\n");
}

/**
 * @tc.name: SliderPatternTwoTest042
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest042, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    paintProperty->UpdateValidSlideRange(range);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "SlideRange: from: nan to: nan\n");
}

/**
 * @tc.name: SliderPatternTwoTest043
 * @tc.desc: DumpSubInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest043, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<SliderPaintProperty> paintProperty = AceType::MakeRefPtr<SliderPaintProperty>();
    RefPtr<BasicShape> shape = AceType::MakeRefPtr<BasicShape>();
    paintProperty->UpdateBlockShape(shape);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpSubInfo(paintProperty);
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockShape: NONE\n");
}

/**
 * @tc.name: SliderPatternTwoTest044
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest044, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPatternOne = AceType::MakeRefPtr<SliderPattern>();
    sliderPattern->parentAccessibilityNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPatternOne);
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    auto accessibilityNodeOne =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeOne, nullptr);
    accessibilityNodeOne->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateValidSlideRange(range);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(accessibilityNodeTwo->accessibilityProperty_->accessibilityDescription_, std::nullopt);
}

/**
 * @tc.name: SliderPatternTwoTest045
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest045, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPatternOne = AceType::MakeRefPtr<SliderPattern>();
    sliderPattern->parentAccessibilityNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPatternOne);
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    auto accessibilityNodeOne =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeOne, nullptr);
    accessibilityNodeOne->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(accessibilityNodeTwo->accessibilityProperty_->accessibilityDescription_, std::nullopt);
}

/**
 * @tc.name: SliderPatternTwoTest046
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest046, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPatternOne = AceType::MakeRefPtr<SliderPattern>();
    sliderPattern->parentAccessibilityNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPatternOne);
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    auto accessibilityNodeOne =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeOne, nullptr);
    accessibilityNodeOne->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    range->fromValue = FLOAT_TEN;
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateValidSlideRange(range);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(accessibilityNodeOne->accessibilityProperty_->accessibilityDescription_, " ");
}

/**
 * @tc.name: SliderPatternTwoTest047
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest047, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    auto frameNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(frameNodeTwo, nullptr);
    sliderPattern->prefix_ = std::move(frameNodeTwo);
    auto sliderPatternOne = AceType::MakeRefPtr<SliderPattern>();
    sliderPattern->parentAccessibilityNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPatternOne);
    ASSERT_NE(sliderPattern->parentAccessibilityNode_, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    auto accessibilityNodeOne =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeOne, nullptr);
    accessibilityNodeOne->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->accessibilityProperty_ = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_FALSE(accessibilityNodeOne->accessibilityProperty_->isSelected_);
}

/**
 * @tc.name: SliderPatternTwoTest048
 * @tc.desc: Test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest048, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, FRAMENODE_ID, sliderPattern);
    ASSERT_NE(frameNode, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Gradient gradient;
    GradientColor color(Color::BLACK);
    gradient.AddColor(color);
    sliderPaintProperty->UpdateBlockGradientColor(gradient);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.back(), "BlockLinearGradientColor: #00000000 \n");
}
} // namespace OHOS::Ace::NG
