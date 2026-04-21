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
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "ui/properties/ui_material.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/border_image.h"
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
#include "core/components_ng/pattern/stack/stack_pattern.h"
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
constexpr uint32_t COUNT = 10;
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
    frameNode->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<AccessibilityProperty>();
    auto accessibilityProperty = frameNode->GetOrCreateAccessibilityProperty();
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
    frameNode->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<AccessibilityProperty>();
    auto accessibilityProperty = frameNode->GetOrCreateAccessibilityProperty();
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
    frameNode->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<AccessibilityProperty>();
    auto accessibilityProperty = frameNode->GetOrCreateAccessibilityProperty();
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
    accessibilityNodeOne->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateValidSlideRange(range);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(accessibilityNodeTwo->GetOrCreateAccessibilityProperty()->accessibilityDescription_, std::nullopt);
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
    accessibilityNodeOne->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(accessibilityNodeTwo->GetOrCreateAccessibilityProperty()->accessibilityDescription_, std::nullopt);
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
    accessibilityNodeOne->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    range->fromValue = FLOAT_TEN;
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateValidSlideRange(range);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_EQ(accessibilityNodeOne->GetOrCreateAccessibilityProperty()->accessibilityDescription_, " ");
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
    accessibilityNodeOne->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    auto accessibilityNodeTwo =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SliderPattern>());
    ASSERT_NE(accessibilityNodeTwo, nullptr);
    accessibilityNodeTwo->GetOrCreateAccessibilityProperty() = AceType::MakeRefPtr<TextAccessibilityProperty>();
    sliderPattern->pointAccessibilityNodeVec_ = { accessibilityNodeOne, accessibilityNodeTwo };
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    RefPtr<SliderModel::SliderValidRange> range = AceType::MakeRefPtr<SliderModel::SliderValidRange>();
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPattern->frameNode_ = std::move(frameNode);
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_FALSE(accessibilityNodeOne->GetOrCreateAccessibilityProperty()->isSelected_);
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

/**
 * @tc.name: SliderPatternTwoTest049
 * @tc.desc: Test AdjustStepAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and set contentSize.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FLOAT_FIFTY, FLOAT_FIFTY));
    /**
     * @tc.steps: step2. make start point is negative.
     * @tc.expected: step2. the size of the pointSize will become smaller.
     */
    auto pointSize = SizeF(FLOAT_TEN, FLOAT_TEN);
    auto negativePoint = PointF(-FLOAT_FIVE, -FLOAT_FIVE);
    sliderPattern->AdjustStepAccessibilityVirtualNode(pointSize, negativePoint, COUNT, 0);
    EXPECT_EQ(pointSize, SizeF(FLOAT_FIVE, FLOAT_FIVE));
    /**
     * @tc.steps: step3. make start point is positive.
     * @tc.expected: step3. the size of the pointSize will not change.
     */
    pointSize = SizeF(FLOAT_TEN, FLOAT_TEN);
    auto positivePoint = PointF(FLOAT_FIVE, FLOAT_FIVE);
    sliderPattern->AdjustStepAccessibilityVirtualNode(pointSize, positivePoint, COUNT, 0);
    EXPECT_EQ(pointSize, SizeF(FLOAT_TEN, FLOAT_TEN));
    /**
     * @tc.steps: step4. make end point is enough.
     * @tc.expected: step4. the size of the pointSize will not change.
     */
    auto enoughPoint = PointF(FLOAT_FIFTY - FLOAT_TEN, FLOAT_FIFTY - FLOAT_TEN);
    sliderPattern->AdjustStepAccessibilityVirtualNode(pointSize, enoughPoint, COUNT, COUNT - 1);
    EXPECT_EQ(pointSize, SizeF(FLOAT_TEN, FLOAT_TEN));
    /**
     * @tc.steps: step5. make end point is exceeded.
     * @tc.expected: step5. the size of the pointSize will become smaller.
     */
    auto exceededPoint = PointF(FLOAT_FIFTY - FLOAT_FIVE, FLOAT_FIFTY - FLOAT_FIVE);
    sliderPattern->AdjustStepAccessibilityVirtualNode(pointSize, exceededPoint, COUNT, COUNT - 1);
    EXPECT_EQ(pointSize, SizeF(FLOAT_FIVE, FLOAT_FIVE));
}

/**
 * @tc.name: SliderPatternTwoTest050
 * @tc.desc: Test InitSliderEnds when sliderContentModifier_ is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest050, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->sliderContentModifier_ = nullptr;
    sliderPattern->InitSliderEnds();
    EXPECT_EQ(sliderPattern->sliderContentModifier_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest051
 * @tc.desc: Test InitSliderEnds with prefixNodeStack_ and suffixNodeStack_
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest051, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    sliderPattern->prefixNodeStack_ = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    sliderPattern->suffixNodeStack_ = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    sliderPattern->InitSliderEnds();
    EXPECT_NE(sliderPattern->prefixNodeStack_, nullptr);
    EXPECT_NE(sliderPattern->suffixNodeStack_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest052
 * @tc.desc: Test OnColorConfigurationUpdate when ConfigChangePerform is false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest052, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    g_isConfigChangePerform = false;
    sliderPattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(SystemProperties::ConfigChangePerform());
}

/**
 * @tc.name: SliderPatternTwoTest053
 * @tc.desc: Test OnColorConfigurationUpdate when ConfigChangePerform is true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest053, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    g_isConfigChangePerform = true;
    sliderPaintProperty->UpdateBlockColorSetByUser(false);
    sliderPaintProperty->UpdateTrackBackgroundColorSetByUser(false);
    sliderPaintProperty->UpdateSelectColorSetByUser(false);
    sliderPattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(SystemProperties::ConfigChangePerform());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SliderPatternTwoTest054
 * @tc.desc: Test OnColorConfigurationUpdate with user set colors
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest054, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    g_isConfigChangePerform = true;
    sliderPaintProperty->UpdateBlockColorSetByUser(true);
    sliderPaintProperty->UpdateTrackBackgroundColorSetByUser(true);
    sliderPaintProperty->UpdateSelectColorSetByUser(true);
    sliderPattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(SystemProperties::ConfigChangePerform());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SliderPatternTwoTest055
 * @tc.desc: Test UpdateStepPointsAccessibilityVirtualNodeSelected with empty pointAccessibilityNodeVec_
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest055, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->pointAccessibilityNodeVec_.clear();
    sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
    EXPECT_TRUE(sliderPattern->pointAccessibilityNodeVec_.empty());
}

/**
 * @tc.name: SliderPatternTwoTest056
 * @tc.desc: Test SetStepPointsAccessibilityVirtualNodeEvent with isDisabledDesc true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest056, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto pointNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pointNode, nullptr);
    bool isClickAbled = false;
    bool reverse = false;
    bool isDisabledDesc = true;
    sliderPattern->SetStepPointsAccessibilityVirtualNodeEvent(pointNode, 0, isClickAbled, reverse, isDisabledDesc);
    EXPECT_TRUE(isDisabledDesc);
}

/**
 * @tc.name: SliderPatternTwoTest057
 * @tc.desc: Test SetStepPointsAccessibilityVirtualNodeEvent with isClickAbled true and no existing event
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest057, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto pointNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pointNode, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back(nullptr);
    bool isClickAbled = true;
    bool reverse = false;
    bool isDisabledDesc = false;
    sliderPattern->SetStepPointsAccessibilityVirtualNodeEvent(pointNode, 0, isClickAbled, reverse, isDisabledDesc);
    EXPECT_NE(sliderPattern->pointAccessibilityNodeEventVec_[0], nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest058
 * @tc.desc: Test SetStepPointsAccessibilityVirtualNodeEvent with isClickAbled false and existing event
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest058, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto pointNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pointNode, nullptr);
    sliderPattern->pointAccessibilityNodeEventVec_.push_back([](GestureEvent& info) {});
    ASSERT_NE(sliderPattern->pointAccessibilityNodeEventVec_[0], nullptr);
    bool isClickAbled = false;
    bool reverse = false;
    bool isDisabledDesc = false;
    sliderPattern->SetStepPointsAccessibilityVirtualNodeEvent(pointNode, 0, isClickAbled, reverse, isDisabledDesc);
    EXPECT_EQ(sliderPattern->pointAccessibilityNodeEventVec_[0], nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest059
 * @tc.desc: Test UpdateSliderComponentColor with BLOCK_COLOR type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest059, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Color color = Color::RED;
    Gradient gradient;
    SliderColorType sliderColorType = SliderColorType::BLOCK_COLOR;
    sliderPattern->UpdateSliderComponentColor(color, sliderColorType, gradient);
    EXPECT_NE(sliderPaintProperty, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest060
 * @tc.desc: Test UpdateSliderComponentColor with TRACK_COLOR type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest060, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Color color = Color::BLUE;
    Gradient gradient;
    GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    SliderColorType sliderColorType = SliderColorType::TRACK_COLOR;
    sliderPattern->UpdateSliderComponentColor(color, sliderColorType, gradient);
    EXPECT_NE(sliderPaintProperty, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest061
 * @tc.desc: Test UpdateSliderComponentColor with SELECT_COLOR type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest061, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Color color = Color::GREEN;
    Gradient gradient;
    GradientColor gradientColor(Color::BLACK);
    gradient.AddColor(gradientColor);
    SliderColorType sliderColorType = SliderColorType::SELECT_COLOR;
    sliderPattern->UpdateSliderComponentColor(color, sliderColorType, gradient);
    EXPECT_NE(sliderPaintProperty, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest062
 * @tc.desc: Test UpdateSliderComponentColor with BLOCK_BORDER_COLOR type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest062, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Color color = Color::GRAY;
    Gradient gradient;
    SliderColorType sliderColorType = SliderColorType::BLOCK_BORDER_COLOR;
    sliderPattern->UpdateSliderComponentColor(color, sliderColorType, gradient);
    EXPECT_NE(sliderPaintProperty, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest063
 * @tc.desc: Test UpdateSliderComponentColor with STEP_COLOR type
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest063, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    Color color = Color::RED;
    Gradient gradient;
    SliderColorType sliderColorType = SliderColorType::STEP_COLOR;
    sliderPattern->UpdateSliderComponentColor(color, sliderColorType, gradient);
    EXPECT_NE(sliderPaintProperty, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest064
 * @tc.desc: Test UpdateSliderComponentMedia
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest064, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->UpdateSliderComponentMedia();
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest065
 * @tc.desc: Test UpdateSliderComponentString with isShowTips true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest065, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    bool isShowTips = true;
    std::string value = "test";
    sliderPattern->UpdateSliderComponentString(isShowTips, value);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest066
 * @tc.desc: Test UpdateSliderComponentString with isShowTips false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest066, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    bool isShowTips = false;
    std::string value = "";
    sliderPattern->UpdateSliderComponentString(isShowTips, value);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest067
 * @tc.desc: Test HandleTouchEvent with TouchType::DOWN
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest067, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->fingerId_ = -1;
    TouchEventInfo touchEventInfo("touch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.fingerId_ = 0;
    touchLocationInfo.localLocation_ = Offset(FLOAT_TEN, FLOAT_TEN);
    touchEventInfo.changedTouches_.emplace_back(touchLocationInfo);
    touchEventInfo.SetSourceDevice(SourceType::TOUCH);
    sliderPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_NE(sliderPattern->fingerId_, -1);
}

/**
 * @tc.name: SliderPatternTwoTest068
 * @tc.desc: Test HandleTouchEvent with TouchType::UP
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest068, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->fingerId_ = 0;
    TouchEventInfo touchEventInfo("touch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UP;
    touchLocationInfo.fingerId_ = 0;
    touchLocationInfo.localLocation_ = Offset(FLOAT_TEN, FLOAT_TEN);
    touchEventInfo.changedTouches_.emplace_back(touchLocationInfo);
    touchEventInfo.SetSourceDevice(SourceType::TOUCH);
    sliderPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(sliderPattern->fingerId_, -1);
}

/**
 * @tc.name: SliderPatternTwoTest069
 * @tc.desc: Test HandleTouchDown with SLIDE_AND_CLICK mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest069, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    sliderPattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK;
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    Offset location(FLOAT_TEN, FLOAT_TEN);
    sliderPattern->HandleTouchDown(location, SourceType::TOUCH);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
}

/**
 * @tc.name: SliderPatternTwoTest070
 * @tc.desc: Test HandleTouchDown with SLIDE_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest070, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_ONLY);
    sliderPattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_ONLY;
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    Offset location(FLOAT_TEN, FLOAT_TEN);
    sliderPattern->HandleTouchDown(location, SourceType::TOUCH);
    EXPECT_FALSE(sliderPattern->allowDragEvents_);
}

/**
 * @tc.name: SliderPatternTwoTest071
 * @tc.desc: Test HandleTouchUp with SLIDE_AND_CLICK_UP mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest071, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateSliderInteractionMode(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP);
    sliderPattern->sliderInteractionMode_ = SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP;
    sliderPattern->lastTouchLocation_ = Offset(FLOAT_TEN, FLOAT_TEN);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    Offset location(FLOAT_TEN, FLOAT_TEN);
    sliderPattern->HandleTouchUp(location, SourceType::TOUCH);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
}

/**
 * @tc.name: SliderPatternTwoTest072
 * @tc.desc: Test HandlingGestureStart with non-AXIS input event
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest072, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->allowDragEvents_ = true;
    sliderPattern->minResponse_ = FLOAT_TEN;
    GestureEvent info;
    info.inputEventType_ = InputEventType::TOUCH_SCREEN;
    info.localLocation_ = Offset(FLOAT_TEN, FLOAT_TEN);
    sliderPattern->HandlingGestureStart(info);
    EXPECT_TRUE(sliderPattern->allowDragEvents_);
}

/**
 * @tc.name: SliderPatternTwoTest073
 * @tc.desc: Test HandlingGestureEvent with AXIS input event and MOUSE source tool
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest073, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::MOUSE;
    info.SetOffsetX(FLOAT_TEN);
    info.SetOffsetY(FLOAT_ZERO);
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(info.GetSourceTool(), SourceTool::MOUSE);
}

/**
 * @tc.name: SliderPatternTwoTest074
 * @tc.desc: Test HandlingGestureEvent with AXIS input event and non-MOUSE source tool
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest074, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    GestureEvent info;
    info.inputEventType_ = InputEventType::AXIS;
    info.sourceTool_ = SourceTool::UNKNOWN;
    info.SetOffsetX(FLOAT_ZERO);
    info.SetOffsetY(FLOAT_TEN);
    sliderPattern->axisOffset_ = FLOAT_ZERO;
    sliderPattern->slipfactor_ = FLOAT_TEN;
    sliderPattern->HandlingGestureEvent(info);
    EXPECT_EQ(info.GetSourceTool(), SourceTool::UNKNOWN);
}

/**
 * @tc.name: SliderPatternTwoTest075
 * @tc.desc: Test GetInsetAndNoneInnerFocusPaintRect with INSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest075, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FLOAT_FIFTY, FLOAT_FIFTY));
    sliderPattern->trackThickness_ = FLOAT_TEN;
    sliderPattern->sliderLength_ = FLOAT_TWENTY;
    sliderPattern->borderBlank_ = FLOAT_FIVE;
    RoundRect paintRect;
    sliderPattern->GetInsetAndNoneInnerFocusPaintRect(paintRect);
    EXPECT_NE(geometryNode, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest076
 * @tc.desc: Test GetInsetAndNoneInnerFocusPaintRect with NONE mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest076, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(FLOAT_FIFTY, FLOAT_FIFTY));
    sliderPattern->trackThickness_ = FLOAT_TEN;
    sliderPattern->sliderLength_ = FLOAT_TWENTY;
    sliderPattern->borderBlank_ = FLOAT_FIVE;
    RoundRect paintRect;
    sliderPattern->GetInsetAndNoneInnerFocusPaintRect(paintRect);
    EXPECT_NE(geometryNode, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest077
 * @tc.desc: Test UpdatePaintRect with ShowFocusFrame true and INSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest077, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::INSET);
    RoundRect paintRect;
    RectF rect(FLOAT_ZERO, FLOAT_ZERO, FLOAT_TEN, FLOAT_TEN);
    float rectRadius = FLOAT_FIVE;
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<SliderTheme>();
    ASSERT_NE(theme, nullptr);
    SliderModel::SliderMode sliderMode = SliderModel::SliderMode::INSET;
    sliderPattern->UpdatePaintRect(theme, sliderMode, paintRect, rect, rectRadius);
    EXPECT_NE(theme, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest078
 * @tc.desc: Test MoveStep with positive stepCount
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest078, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateMin(FLOAT_ZERO);
    sliderPaintProperty->UpdateMax(FLOAT_FIFTY);
    sliderPaintProperty->UpdateValue(FLOAT_TEN);
    sliderPattern->value_ = FLOAT_TEN;
    int32_t stepCount = 1;
    bool result = sliderPattern->MoveStep(stepCount);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SliderPatternTwoTest079
 * @tc.desc: Test MoveStep with negative stepCount
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest079, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateMin(FLOAT_ZERO);
    sliderPaintProperty->UpdateMax(FLOAT_FIFTY);
    sliderPaintProperty->UpdateValue(FLOAT_TEN);
    sliderPattern->value_ = FLOAT_TEN;
    int32_t stepCount = -1;
    bool result = sliderPattern->MoveStep(stepCount);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SliderPatternTwoTest080
 * @tc.desc: Test MoveStep with zero step
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest080, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateStep(FLOAT_ZERO);
    int32_t stepCount = 1;
    bool result = sliderPattern->MoveStep(stepCount);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SliderPatternTwoTest081
 * @tc.desc: Test InitMouseEvent with UseContentModifier true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest081, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ =
        AceType::MakeRefPtr<FrameNode>(V2::SLIDER_ETS_TAG, NODE_ID, sliderPattern);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<InputEventHub> inputEventHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    sliderPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](bool isHover) {});
    sliderPattern->mouseEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo& info) {});
    sliderPattern->InitMouseEvent(inputEventHub);
    EXPECT_TRUE(sliderPattern->UseContentModifier());
}

/**
 * @tc.name: SliderPatternTwoTest082
 * @tc.desc: Test InitMouseEvent with UseContentModifier false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest082, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->contentModifierNode_ = nullptr;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<InputEventHub> inputEventHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    sliderPattern->InitMouseEvent(inputEventHub);
    EXPECT_NE(sliderPattern->hoverEvent_, nullptr);
    EXPECT_NE(sliderPattern->mouseEvent_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest083
 * @tc.desc: Test HandleHoverEvent with isHover true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest083, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    sliderPattern->mouseHoverFlag_ = true;
    sliderPattern->axisFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->mousePressedFlag_ = false;
    bool isHover = true;
    sliderPattern->HandleHoverEvent(isHover);
    EXPECT_TRUE(sliderPattern->hotFlag_);
}

/**
 * @tc.name: SliderPatternTwoTest084
 * @tc.desc: Test HandleHoverEvent with isHover false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest084, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    sliderPattern->mouseHoverFlag_ = false;
    sliderPattern->axisFlag_ = false;
    sliderPattern->isFocusActive_ = false;
    sliderPattern->mousePressedFlag_ = false;
    bool isHover = false;
    sliderPattern->HandleHoverEvent(isHover);
    EXPECT_FALSE(sliderPattern->hotFlag_);
}

/**
 * @tc.name: SliderPatternTwoTest085
 * @tc.desc: Test UpdatePrefixPosition with sliderContentModifier_ nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest085, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->sliderContentModifier_ = nullptr;
    sliderPattern->UpdatePrefixPosition();
    EXPECT_EQ(sliderPattern->sliderContentModifier_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest086
 * @tc.desc: Test UpdateSuffixPosition with sliderContentModifier_ nullptr
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest086, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->sliderContentModifier_ = nullptr;
    sliderPattern->UpdateSuffixPosition();
    EXPECT_EQ(sliderPattern->sliderContentModifier_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest087
 * @tc.desc: Test UpdateEndsIsShowStepsPosition with empty stepPoints_
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest087, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderPattern->stepPoints_.clear();
    PointF position(0.0f, 0.0f);
    PointF block(FLOAT_TEN, FLOAT_TEN);
    SizeF size(FLOAT_TEN, FLOAT_TEN);
    float outsetOffset = FLOAT_FIVE;
    bool side = true;
    sliderPattern->UpdateEndsIsShowStepsPosition(position, block, size, outsetOffset, side);
    EXPECT_TRUE(sliderPattern->stepPoints_.empty());
}

/**
 * @tc.name: SliderPatternTwoTest088
 * @tc.desc: Test UpdateEndsIsShowStepsPosition with NONE mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest088, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    sliderPattern->stepPoints_ = { PointF(FLOAT_TEN, FLOAT_TEN), PointF(FLOAT_TWENTY, FLOAT_TWENTY) };
    PointF position(0.0f, 0.0f);
    PointF block(FLOAT_TEN, FLOAT_TEN);
    SizeF size(FLOAT_TEN, FLOAT_TEN);
    float outsetOffset = FLOAT_FIVE;
    bool side = true;
    sliderPattern->UpdateEndsIsShowStepsPosition(position, block, size, outsetOffset, side);
    EXPECT_EQ(sliderPattern->stepPoints_.size(), MUMBER_TWO);
}

/**
 * @tc.name: SliderPatternTwoTest089
 * @tc.desc: Test SetPrefix with valid prefix node
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest089, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto prefixNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(prefixNode, nullptr);
    RefPtr<NG::UINode> uiNode = prefixNode;
    NG::SliderPrefixOptions options;
    sliderPattern->SetPrefix(uiNode, options);
    EXPECT_TRUE(sliderPattern->HasPrefix());
}

/**
 * @tc.name: SliderPatternTwoTest090
 * @tc.desc: Test SetPrefix with nullptr prefix node
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest090, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    RefPtr<NG::UINode> uiNode = nullptr;
    NG::SliderPrefixOptions options;
    sliderPattern->SetPrefix(uiNode, options);
    EXPECT_FALSE(sliderPattern->HasPrefix());
}

/**
 * @tc.name: SliderPatternTwoTest091
 * @tc.desc: Test SetSuffix with valid suffix node
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest091, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto suffixNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(suffixNode, nullptr);
    RefPtr<NG::UINode> uiNode = suffixNode;
    NG::SliderSuffixOptions options;
    sliderPattern->SetSuffix(uiNode, options);
    EXPECT_TRUE(sliderPattern->HasSuffix());
}

/**
 * @tc.name: SliderPatternTwoTest092
 * @tc.desc: Test SetSuffix with nullptr suffix node
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest092, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    RefPtr<NG::UINode> uiNode = nullptr;
    NG::SliderSuffixOptions options;
    sliderPattern->SetSuffix(uiNode, options);
    EXPECT_FALSE(sliderPattern->HasSuffix());
}

/**
 * @tc.name: SliderPatternTwoTest093
 * @tc.desc: Test AddIsFocusActiveUpdateEvent
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest093, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->isFocusActiveUpdateEvent_ = nullptr;
    sliderPattern->AddIsFocusActiveUpdateEvent();
    EXPECT_NE(sliderPattern->isFocusActiveUpdateEvent_, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest094
 * @tc.desc: Test FireBuilder without makeFunc_
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest094, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->makeFunc_ = std::nullopt;
    sliderPattern->FireBuilder();
    EXPECT_FALSE(sliderPattern->makeFunc_.has_value());
}

/**
 * @tc.name: SliderPatternTwoTest095
 * @tc.desc: Test FireBuilder with makeFunc_
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest095, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderPaintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    ASSERT_NE(sliderPaintProperty, nullptr);
    sliderPaintProperty->UpdateMin(FLOAT_ZERO);
    sliderPaintProperty->UpdateMax(FLOAT_FIFTY);
    sliderPaintProperty->UpdateStep(FLOAT_FIVE);
    sliderPaintProperty->UpdateValue(FLOAT_TEN);
    sliderPattern->makeFunc_ = [](const SliderConfiguration& config) -> RefPtr<FrameNode> {
        return nullptr;
    };
    sliderPattern->FireBuilder();
    EXPECT_TRUE(sliderPattern->makeFunc_.has_value());
}

/**
 * @tc.name: SliderPatternTwoTest096
 * @tc.desc: Test OnIsFocusActiveUpdate with focusFlag_ false
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest096, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->focusFlag_ = false;
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    bool isFocusActive = true;
    sliderPattern->OnIsFocusActiveUpdate(isFocusActive);
    EXPECT_FALSE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: SliderPatternTwoTest097
 * @tc.desc: Test OnIsFocusActiveUpdate with focusFlag_ true and showTips_ true
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest097, TestSize.Level1)
{
    auto sliderPattern = AceType::MakeRefPtr<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    sliderPattern->focusFlag_ = true;
    sliderPattern->showTips_ = true;
    sliderPattern->mousePressedFlag_ = false;
    SliderContentModifier::Parameters parameters;
    sliderPattern->sliderContentModifier_ = AceType::MakeRefPtr<SliderContentModifier>(parameters, nullptr);
    bool isFocusActive = true;
    sliderPattern->OnIsFocusActiveUpdate(isFocusActive);
    EXPECT_TRUE(sliderPattern->isFocusActive_);
}

/**
 * @tc.name: SliderPatternTwoTest098
 * @tc.desc: Test UpdateEndsNotShowStepsPosition with HORIZONTAL axis and OUTSET mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest098, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::OUTSET);
    sliderLayoutProperty->UpdateDirection(Axis::HORIZONTAL);
    PointF position(0.0f, 0.0f);
    PointF block(FLOAT_TEN, FLOAT_TEN);
    SizeF size(FLOAT_TEN, FLOAT_TEN);
    float noneOffset = FLOAT_TEN;
    float outsetOffset = FLOAT_FIVE;
    sliderPattern->UpdateEndsNotShowStepsPosition(position, block, size, noneOffset, outsetOffset);
    EXPECT_NE(sliderLayoutProperty, nullptr);
}

/**
 * @tc.name: SliderPatternTwoTest099
 * @tc.desc: Test UpdateEndsNotShowStepsPosition with VERTICAL axis and NONE mode
 * @tc.type: FUNC
 */
HWTEST_F(SliderPatternTwoTestNg, SliderPatternTwoTest099, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SLIDER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SliderPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto sliderPattern = frameNode->GetPattern<SliderPattern>();
    ASSERT_NE(sliderPattern, nullptr);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    ASSERT_NE(sliderLayoutProperty, nullptr);
    sliderLayoutProperty->UpdateSliderMode(SliderModel::SliderMode::NONE);
    sliderLayoutProperty->UpdateDirection(Axis::VERTICAL);
    PointF position(0.0f, 0.0f);
    PointF block(FLOAT_TEN, FLOAT_TEN);
    SizeF size(FLOAT_TEN, FLOAT_TEN);
    float noneOffset = FLOAT_TEN;
    float outsetOffset = FLOAT_FIVE;
    sliderPattern->UpdateEndsNotShowStepsPosition(position, block, size, noneOffset, outsetOffset);
    EXPECT_NE(sliderLayoutProperty, nullptr);
}
} // namespace OHOS::Ace::NG
