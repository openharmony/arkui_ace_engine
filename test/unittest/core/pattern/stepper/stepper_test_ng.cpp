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

#include <cstddef>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
#include "core/components_ng/pattern/stepper/stepper_item_layout_property.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/components_ng/pattern/stepper/stepper_item_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/stepper/stepper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t STEPPER_ERROR = -1;
constexpr int32_t INDEX_NUM = 10;
constexpr float SUIT_AGE_LEVEL_ONE = 1.75f;
constexpr float SUIT_AGE_LEVEL_TWO = 2.0f;
constexpr float SUIT_AGE_LEVEL_THRER = 3.2f;
const std::string FINISH_EVENT_NAME = "FINISH_EVENT";
const std::string SKIP_EVENT_NAME = "SKIP_EVENT";
const std::string CHANGE_EVENT_NAME = "CHANGE_EVENT";
const std::string NEXT_EVENT_NAME = "NEXT_EVENT";
const std::string PREVIOUS_EVENT_NAME = "PREVIOUS_EVENT";
const uint32_t INDEX = 0;
const std::string STEPPER_ITEM_TAG = "StepperTag";
const std::string STEPPER_ITEM_TAG_GET = "StepperTagGet";
const std::string STEPPER_ITEM_TAG_GET_EX = "StepperTagGetEx";
const std::string FRAME_NODE_TAG = "FrameNodeTag";
const std::string SWIPER_NODE_TAG = "SwiperNodeTag";
const int32_t UPDATED_RIGHT_INDEX = 3;
const int32_t UPDATED_RIGHT_INDEX_PLUS = 4;
const std::string LEFT_LABEL = "Previous";
const std::string RIGHT_LABEL = "Next";
const std::string LABEL_STATUS = "normal";
const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
} // namespace

struct TestProperty {
    std::optional<std::string> leftLabelValue = std::nullopt;
    std::optional<std::string> rightLabelValue = std::nullopt;
    std::optional<std::string> labelStatusValue = std::nullopt;
};

class StepperTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void InitStepperTestNg();
    static RefPtr<LayoutWrapperNode> CreateChildLayoutWrapper(
        RefPtr<LayoutWrapperNode> layoutWrapper, RefPtr<FrameNode> parentNode, RefPtr<FrameNode> childNode);
    static RefPtr<FrameNode> CreateStepperItemNode(TestProperty& testProperty);

    RefPtr<StepperNode> frameNode_;
    RefPtr<StepperPattern> stepperPattern_;
    RefPtr<StepperAccessibilityProperty> stepperAccessibilityProperty_;
    RefPtr<FrameNode> swiperNode_;
    RefPtr<SwiperLayoutProperty> swiperLayoutProperty_;
};

void StepperTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    // set StepperTheme to themeManager before using themeManager to get StepperTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<StepperTheme>()));
}

void StepperTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<LayoutWrapperNode> StepperTestNg::CreateChildLayoutWrapper(
    RefPtr<LayoutWrapperNode> layoutWrapper, RefPtr<FrameNode> parentNode, RefPtr<FrameNode> childNode)
{
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childNode, childGeometryNode, childNode->GetLayoutProperty());
    parentNode->AddChild(childNode);
    layoutWrapper->AppendChild(childLayoutWrapper);
    return childLayoutWrapper;
}

RefPtr<FrameNode> StepperTestNg::CreateStepperItemNode(TestProperty& testProperty)
{
    StepperItemModelNG().Create();
    if (testProperty.labelStatusValue.has_value()) {
        StepperItemModelNG().SetStatus(testProperty.labelStatusValue.value());
    }
    if (testProperty.leftLabelValue.has_value()) {
        StepperItemModelNG().SetPrevLabel(testProperty.leftLabelValue.value());
    }
    if (testProperty.rightLabelValue.has_value()) {
        StepperItemModelNG().SetNextLabel(testProperty.rightLabelValue.value());
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

void StepperTestNg::InitStepperTestNg()
{
    frameNode_ = StepperNode::GetOrCreateStepperNode(V2::STEPPER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode_, nullptr);

    stepperPattern_ = frameNode_->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern_, nullptr);

    stepperAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<StepperAccessibilityProperty>();
    ASSERT_NE(stepperAccessibilityProperty_, nullptr);

    swiperNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, frameNode_->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode_, nullptr);
    swiperNode_->MountToParent(frameNode_);

    swiperLayoutProperty_ = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty_, nullptr);
}

/**
 * @tc.name: StepperFrameNodeCreator001
 * @tc.desc: Test all the event of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperFrameNodeCreator001, TestSize.Level1)
{
    std::string eventName;
    int32_t eventParameterA = -1;
    int32_t eventParameterB = -1;
    StepperModelNG().Create(INDEX);
    StepperModelNG().SetOnChange([&eventName, &eventParameterA, &eventParameterB](int32_t a, int32_t b) {
        eventName = CHANGE_EVENT_NAME;
        eventParameterA = a;
        eventParameterB = b;
    });
    StepperModelNG().SetOnFinish([&eventName]() { eventName = FINISH_EVENT_NAME; });
    StepperModelNG().SetOnNext([&eventName, &eventParameterA, &eventParameterB](int32_t a, int32_t b) {
        eventName = NEXT_EVENT_NAME;
        eventParameterA = a;
        eventParameterB = b;
    });
    StepperModelNG().SetOnPrevious([&eventName, &eventParameterA, &eventParameterB](int32_t a, int32_t b) {
        eventName = PREVIOUS_EVENT_NAME;
        eventParameterA = a;
        eventParameterB = b;
    });
    StepperModelNG().SetOnSkip([&eventName]() { eventName = SKIP_EVENT_NAME; });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireFinishEvent(1);
    EXPECT_EQ(eventName, FINISH_EVENT_NAME);
    eventHub->FireSkipEvent(1);
    EXPECT_EQ(eventName, SKIP_EVENT_NAME);
    eventHub->FireChangeEvent(1, 2);
    EXPECT_EQ(eventName, CHANGE_EVENT_NAME);
    EXPECT_EQ(eventParameterA, 1);
    EXPECT_EQ(eventParameterB, 2);
    eventHub->FireNextEvent(2, 3);
    EXPECT_EQ(eventName, NEXT_EVENT_NAME);
    EXPECT_EQ(eventParameterA, 2);
    EXPECT_EQ(eventParameterB, 3);
    eventHub->FirePreviousEvent(3, 4);
    EXPECT_EQ(eventName, PREVIOUS_EVENT_NAME);
    EXPECT_EQ(eventParameterA, 3);
    EXPECT_EQ(eventParameterB, 4);
}

/**
 * @tc.name: StepperNodeGetOrCreateStepperNode001
 * @tc.desc: test create stepper node.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperNodeGetOrCreateStepperNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stepperNode = StepperNode::GetOrCreateStepperNode(
        STEPPER_ITEM_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperNode, nullptr);
    RefPtr<StepperNode> newStepperNode = stepperNode->GetOrCreateStepperNode(STEPPER_ITEM_TAG, nodeId, nullptr);
    ASSERT_NE(newStepperNode, nullptr);
    EXPECT_EQ(newStepperNode->GetTag(), stepperNode->GetTag());

    auto nodeIdGet = ElementRegister::GetInstance()->MakeUniqueId();
    auto childStepperNode = StepperNode::GetOrCreateStepperNode(
        STEPPER_ITEM_TAG_GET, nodeIdGet, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(childStepperNode, nullptr);
    stepperNode->AddChild(childStepperNode);
    EXPECT_FALSE(stepperNode->children_.empty());

    auto st_stepperNode = ElementRegister::GetInstance()->GetSpecificItemById<StepperNode>(nodeIdGet);
    EXPECT_NE(st_stepperNode, nullptr);

    newStepperNode = stepperNode->GetOrCreateStepperNode(STEPPER_ITEM_TAG_GET_EX, nodeIdGet, nullptr);
    ASSERT_NE(newStepperNode, nullptr);
    EXPECT_TRUE(stepperNode->children_.empty());
    EXPECT_EQ(newStepperNode->GetTag(), STEPPER_ITEM_TAG_GET_EX);
}

/**
 * @tc.name: StepperNodeAddChildToGroup001
 * @tc.desc: test AddChild and DeleteChild methods
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperNodeAddChildToGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get Node Id
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    /**
     * @tc.steps: step2. create Node
     */
    auto frameNode = StepperNode::GetOrCreateStepperNode(FRAME_NODE_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperNode =
        AceType::MakeRefPtr<StepperNode>(STEPPER_ITEM_TAG, nodeId, AceType::MakeRefPtr<StepperPattern>());
    ASSERT_NE(stepperNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, stepperNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    swiperNode->MountToParent(stepperNode);
    EXPECT_FALSE(frameNode->GetParent());
    stepperNode->AddChildToGroup(frameNode);
    EXPECT_TRUE(frameNode->GetParent());
    stepperNode->DeleteChildFromGroup(INDEX);
    EXPECT_FALSE(frameNode->GetParent());
}

/**
 * @tc.name: StepperPatternInitSwiperChangeEvent001
 * @tc.desc: test Stepper pattern UpdateOrCreateRightButtonNode001.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternInitSwiperChangeEvent001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    EXPECT_EQ(stepperPattern->GetCurrentIndex(), INDEX);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    auto swiperEventHub = swiperNode->GetEventHub<SwiperEventHub>();
    EXPECT_NE(swiperEventHub, nullptr);
    EXPECT_FALSE(stepperPattern->swiperChangeEvent_);
    stepperPattern->InitSwiperChangeEvent(swiperEventHub);
    EXPECT_TRUE(stepperPattern->swiperChangeEvent_);
}

/**
 * @tc.name: UpdateOrCreateLeftButtonNode001
 * @tc.desc: test Stepper pattern UpdateOrCreateLeftButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, UpdateOrCreateLeftButtonNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stepperNode
     * @tc.expected: step1. create stepperNode success
     */
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create stepperPattern
     * @tc.expected: step2. create stepperPattern success
     */
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    /**
     * @tc.steps: step3. test OnModifyDone
     * @tc.expected: step3. OnModifyDone OK
     */
    stepperPattern->OnModifyDone();
    /**
     * @tc.steps: step4. test update or create left button node
     * @tc.expected: step4. test update or create left button node
     */
    stepperPattern->UpdateOrCreateLeftButtonNode(INDEX);
    auto oldhostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(oldhostNode, nullptr);
    EXPECT_FALSE(oldhostNode->HasLeftButtonNode());

    auto stepperNodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto stepperItemNode = StepperNode::GetOrCreateStepperNode(
        STEPPER_ITEM_TAG_GET, stepperNodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperItemNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    swiperNode->AddChild(stepperItemNode);
    stepperPattern->UpdateOrCreateLeftButtonNode(stepperNodeId);
    EXPECT_EQ(stepperPattern->index_, stepperNodeId);
}

/**
 * @tc.name: StepperPatternCreateLeftButtonNode001
 * @tc.desc: test Stepper pattern CreateLeftButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternCreateLeftButtonNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create stepperNode
     * @tc.expected: step1. create stepperNode success
     */
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. create stepperPattern
     * @tc.expected: step2. create stepperPattern success
     */
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    /**
     * @tc.steps: step3. test buttonNode
     * @tc.expected: step3.
     */
    auto buttonId = hostNode->GetLeftButtonId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(buttonNode->GetParent(), hostNode);
    auto buttonInputHub = buttonNode->GetOrCreateInputEventHub();
    ASSERT_NE(buttonInputHub, nullptr);
    EXPECT_TRUE(buttonInputHub->hoverEventActuator_);
    auto buttonGestureHub = buttonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(buttonGestureHub, nullptr);
    EXPECT_TRUE(buttonGestureHub->touchEventActuator_);
    /**
     * @tc.steps: step4. test rowNode, imageNode, textNode
     * @tc.expected: step4. test success
     */
    auto rowNode = buttonNode->GetChildAtIndex(0);
    ASSERT_NE(rowNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildAtIndex(0));
    ASSERT_NE(imageNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildAtIndex(1));
    ASSERT_NE(textNode, nullptr);
}
/**
 * @tc.name: UpdateOrCreateRightButtonNode001
 * @tc.desc: test Stepper pattern UpdateOrCreateRightButtonNode001.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, UpdateOrCreateRightButtonNode001, TestSize.Level1)
{
    StepperModelNG().Create(INDEX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->OnModifyDone();
    stepperPattern->UpdateOrCreateRightButtonNode(UPDATED_RIGHT_INDEX);
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    EXPECT_FALSE(hostNode->HasRightButtonNode());
    stepperPattern->UpdateOrCreateRightButtonNode(UPDATED_RIGHT_INDEX_PLUS);
    EXPECT_EQ(stepperPattern->index_, UPDATED_RIGHT_INDEX_PLUS);
}
/**
 * @tc.name: StepperPatternCreateArrowRightButtonNode001
 * @tc.desc: test Stepper pattern CreateArrowRightButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternCreateArrowRightButtonNode001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);

    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    frameNode->AddChild(swiperNode);
    swiperNode->AddChild(stepperItemNode);

    stepperPattern->CreateArrowRightButtonNode(INDEX, false);
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto buttonId = hostNode->GetRightButtonId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(buttonNode->GetParent(), hostNode);
    auto buttonInputHub = buttonNode->GetOrCreateInputEventHub();
    ASSERT_NE(buttonInputHub, nullptr);
    EXPECT_TRUE(buttonInputHub->hoverEventActuator_);
    auto buttonGestureHub = buttonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(buttonGestureHub, nullptr);
    EXPECT_TRUE(buttonGestureHub->touchEventActuator_);
    auto rowNode = buttonNode->GetChildAtIndex(0);
    ASSERT_NE(rowNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildAtIndex(0));
    ASSERT_NE(imageNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(rowNode->GetChildAtIndex(1));
    ASSERT_NE(textNode, nullptr);
}
/**
 * @tc.name: StepperPatternCreateArrowlessRightButtonNode001
 * @tc.desc: test Stepper pattern CreateArrowlessRightButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternCreateArrowlessRightButtonNode001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    frameNode->AddChild(swiperNode);
    swiperNode->AddChild(stepperItemNode);
    auto theme = AceType::MakeRefPtr<StepperTheme>();
    stepperPattern->CreateArrowlessRightButtonNode(INDEX, false, theme->GetStepperStart());
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto buttonId = hostNode->GetRightButtonId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_EQ(buttonNode->GetParent(), hostNode);
    auto buttonInputHub = buttonNode->GetOrCreateInputEventHub();
    ASSERT_NE(buttonInputHub, nullptr);
    EXPECT_TRUE(buttonInputHub->hoverEventActuator_);
    auto buttonGestureHub = buttonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(buttonGestureHub, nullptr);
    EXPECT_TRUE(buttonGestureHub->touchEventActuator_);
    auto textNode = AceType::DynamicCast<FrameNode>(buttonNode->GetChildAtIndex(0));
    ASSERT_NE(textNode, nullptr);
}
/**
 * @tc.name: StepperPatternCreateWaitingRightButtonNode001
 * @tc.desc: test Stepper pattern CreateWaitingRightButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternCreateWaitingRightButtonNode001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateWaitingRightButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto buttonId = hostNode->GetRightButtonId();
    auto loadingProgressNode = FrameNode::GetOrCreateFrameNode(
        V2::LOADING_PROGRESS_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<LoadingProgressPattern>(); });
    ASSERT_NE(loadingProgressNode, nullptr);
    EXPECT_EQ(loadingProgressNode->GetParent(), hostNode);
}

/**
 * @tc.name: StepperPatternHandleClickEvent001
 * @tc.desc: test Stepper pattern handle button click event.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternHandleClickEvent001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, hostNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    hostNode->AddChild(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    swiperPattern->controller_ = CREATE_ANIMATOR(hostNode->GetContextRefPtr());
    auto swiperAnimationController = swiperPattern->GetController();
    ASSERT_NE(swiperAnimationController, nullptr);
    stepperPattern->HandlingLeftButtonClickEvent();
    auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
    ASSERT_NE(swiperController, nullptr);
    swiperAnimationController->status_ = Animator::Status::STOPPED;
    stepperPattern->HandlingLeftButtonClickEvent();
    swiperAnimationController->status_ = Animator::Status::RUNNING;
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    swiperNode->AddChild(stepperItemNode);
    stepperPattern->HandlingRightButtonClickEvent();
    swiperAnimationController->status_ = Animator::Status::STOPPED;
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("skip");
    stepperPattern->HandlingRightButtonClickEvent();
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "skip");
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("normal");
    stepperPattern->HandlingRightButtonClickEvent();
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "normal");
    stepperPattern->index_ = stepperPattern->maxIndex_;
    stepperPattern->HandlingRightButtonClickEvent();
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "normal");
}
/**
 * @tc.name: StepperAlgorithmTest001
 * @tc.desc: test Stepper pattern algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAlgorithmTest001, TestSize.Level1)
{
    StepperModelNG().Create(INDEX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    auto stepperFrameNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(stepperFrameNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        stepperFrameNode, AceType::MakeRefPtr<GeometryNode>(), stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = stepperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(RK356_WIDTH, RK356_HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(RK356_WIDTH, RK356_HEIGHT);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, stepperFrameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        CreateChildLayoutWrapper(layoutWrapper, stepperFrameNode, swiperNode);

    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stepperFrameNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    RefPtr<LayoutWrapperNode> leftButtonLayoutWrapper =
        CreateChildLayoutWrapper(layoutWrapper, stepperFrameNode, leftButtonNode);

    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, stepperFrameNode->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    RefPtr<LayoutWrapperNode> rightButtonLayoutWrapper =
        CreateChildLayoutWrapper(layoutWrapper, stepperFrameNode, rightButtonNode);

    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    RefPtr<LayoutWrapperNode> rowLayoutWrapper =
        CreateChildLayoutWrapper(leftButtonLayoutWrapper, leftButtonNode, rowNode);
    rightButtonNode->AddChild(rowNode);
    rightButtonLayoutWrapper->AppendChild(rowLayoutWrapper);

    auto rightTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<LayoutWrapperNode> rightTextLayoutWrapper =
        CreateChildLayoutWrapper(rowLayoutWrapper, rowNode, rightTextNode);

    auto leftTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<LayoutWrapperNode> leftTextLayoutWrapper = CreateChildLayoutWrapper(rowLayoutWrapper, rowNode, leftTextNode);

    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    stepperLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
}
/**
 * @tc.name: StepperAlgorithmTest002
 * @tc.desc: test Stepper pattern algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAlgorithmTest002, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(stepperFrameNode, geometryNode, stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = stepperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(Infinity<float>(), RK356_HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(Infinity<float>(), RK356_HEIGHT);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
}
/**
 * @tc.name: StepperAlgorithmTest003
 * @tc.desc: test Stepper pattern algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAlgorithmTest003, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(stepperFrameNode, geometryNode, stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = stepperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(RK356_WIDTH, RK356_HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(RK356_WIDTH, RK356_HEIGHT);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
    stepperLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    auto child = stepperFrameNode->GetFirstChild();
    EXPECT_EQ(child, nullptr);
}

/**
 * @tc.name: StepperEventHubChangeEvent001
 * @tc.desc: Test the change event of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperEventHubChangeEvent001, TestSize.Level1)
{
    StepperModelNG().Create(INDEX);
    StepperModelNG().SetOnChangeEvent([](int32_t index) { EXPECT_EQ(index, 1); });

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireChangeEvent(1, 1);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Stepper Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stepper and initialize related properties.
     */
    StepperModelNG().Create(INDEX);

    /**
     * @tc.steps: step2. Get stepper frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get stepper accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto stepperAccessibilityProperty = frameNode->GetAccessibilityProperty<StepperAccessibilityProperty>();
    ASSERT_NE(stepperAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. Call the callback function in stepperAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(stepperAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(stepperAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: GetFocusNode001
 * @tc.desc: test stepper pattern FocusNode
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, GetFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);

    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    frameNode->AddChild(swiperNode);
    swiperNode->AddChild(stepperItemNode);

    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);

    /**
     * @tc.steps: step2. Create ButtonNode.
     */
    stepperPattern->CreateLeftButtonNode();
    stepperPattern->CreateArrowRightButtonNode(INDEX, false);

    /**
     * @tc.steps: step3. Create FocusHub.
     */
    auto buttonFocusHub = stepperItemNode->GetFocusHub();
    ASSERT_NE(buttonFocusHub, nullptr);
    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(leftButtonNode, nullptr);
    auto leftFocusHub = leftButtonNode->GetFocusHub();
    ASSERT_NE(leftFocusHub, nullptr);
    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(rightButtonNode, nullptr);
    auto rightFocusHub = rightButtonNode->GetFocusHub();
    ASSERT_NE(rightFocusHub, nullptr);

    /**
     * @tc.steps: steps4. GetFocusNode
     * @tc.expected: Check the result of GetFocusNode
     */
    auto focusNode = stepperPattern->GetFocusNode(FocusStep::TAB, buttonFocusHub);
    ASSERT_NE(focusNode.Upgrade(), rightFocusHub);
    focusNode = stepperPattern->GetFocusNode(FocusStep::SHIFT_TAB, rightFocusHub);
    ASSERT_NE(focusNode.Upgrade(), buttonFocusHub);
    focusNode = stepperPattern->GetFocusNode(FocusStep::LEFT, leftFocusHub);
    ASSERT_NE(focusNode.Upgrade(), leftFocusHub);
    focusNode = stepperPattern->GetFocusNode(FocusStep::RIGHT, leftFocusHub);
    ASSERT_NE(focusNode.Upgrade(), leftFocusHub);
    focusNode = stepperPattern->GetFocusNode(FocusStep::UP, rightFocusHub);
    ASSERT_NE(focusNode.Upgrade(), rightFocusHub);
    focusNode = stepperPattern->GetFocusNode(FocusStep::DOWN, rightFocusHub);
    ASSERT_NE(focusNode.Upgrade(), leftFocusHub);
}

/**
 * @tc.name: StepperPatternInitSwiperChangeEvent001
 * @tc.desc: test Stepper pattern CreateRightButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternCreateRightButtonNode001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, hostNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    hostNode->AddChild(swiperNode);
    auto frameNode1 = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    swiperNode->AddChild(frameNode1);
    ASSERT_NE(frameNode1, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    swiperPattern->controller_ = CREATE_ANIMATOR(hostNode->GetContextRefPtr());
    auto swiperAnimationController = swiperPattern->GetController();
    ASSERT_NE(swiperAnimationController, nullptr);
    stepperPattern->HandlingLeftButtonClickEvent();
    auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
    ASSERT_NE(swiperController, nullptr);
    swiperAnimationController->status_ = Animator::Status::STOPPED;
    stepperPattern->HandlingLeftButtonClickEvent();
    swiperAnimationController->status_ = Animator::Status::RUNNING;
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    swiperNode->AddChild(stepperItemNode);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("normal");
    stepperPattern->CreateRightButtonNode(1);
    stepperPattern->maxIndex_ = 1;
    stepperPattern->CreateRightButtonNode(1);
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "normal");
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("disabled");
    stepperPattern->CreateRightButtonNode(1);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("waiting");
    stepperPattern->CreateRightButtonNode(1);
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "waiting");
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("skip");
    stepperPattern->CreateRightButtonNode(1);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("status");
    stepperPattern->CreateRightButtonNode(1);
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "status");
}

/**
 * @tc.name: StepperPatternHandleClickEvent011
 * @tc.desc: test Stepper pattern handle button click event.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternHandleClickEvent011, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, hostNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    hostNode->AddChild(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    swiperPattern->controller_ = CREATE_ANIMATOR(hostNode->GetContextRefPtr());
    auto swiperAnimationController = swiperPattern->GetController();
    ASSERT_NE(swiperAnimationController, nullptr);
    stepperPattern->HandlingLeftButtonClickEvent();
    auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
    ASSERT_NE(swiperController, nullptr);
    swiperAnimationController->status_ = Animator::Status::STOPPED;
    stepperPattern->HandlingLeftButtonClickEvent();
    swiperAnimationController->status_ = Animator::Status::RUNNING;
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    swiperNode->AddChild(stepperItemNode);
    stepperPattern->HandlingRightButtonClickEvent();
    swiperAnimationController->status_ = Animator::Status::STOPPED;
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("skip");
    stepperPattern->HandlingRightButtonClickEvent();
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "skip");
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("normal");
    stepperPattern->HandlingRightButtonClickEvent();
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "normal");
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "normal");
    stepperPattern->maxIndex_ = 5;
    stepperPattern->HandlingRightButtonClickEvent();
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("waiting");
    stepperPattern->HandlingRightButtonClickEvent();
    EXPECT_EQ(stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus(), "waiting");
}

/**
 * @tc.name: StepperPatternOnColorConfigurationUpdate001
 * @tc.desc: test  OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternOnColorConfigurationUpdate001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto frameNode2 = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG_GET,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode2, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(leftButtonNode, nullptr);
    hostNode->AddChild(leftButtonNode);
    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(rightButtonNode, nullptr);
    rightButtonNode->AddChild(frameNode2);
    hostNode->AddChild(rightButtonNode);
    auto leftGestureHub = leftButtonNode->GetOrCreateGestureEventHub();
    auto rightGestureHub = rightButtonNode->GetOrCreateGestureEventHub();
    EXPECT_FALSE(leftGestureHub->IsClickable());
    EXPECT_FALSE(rightGestureHub->IsClickable());
    frameNode2->tag_ = V2::ROW_ETS_TAG;
    stepperPattern->OnColorConfigurationUpdate();
    frameNode2->tag_ = V2::TEXT_ETS_TAG;
    stepperPattern->OnColorConfigurationUpdate();
    frameNode2->tag_ = V2::LINE_ETS_TAG;
    stepperPattern->OnColorConfigurationUpdate();
    hostNode->Clean(false, false);
    stepperPattern->OnColorConfigurationUpdate();
}

/**
 * @tc.name: GetFocusNode002
 * @tc.desc: test stepper pattern GetFocusNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, GetFocusNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);

    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    frameNode->AddChild(swiperNode);
    swiperNode->AddChild(stepperItemNode);
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    stepperPattern->CreateLeftButtonNode();
    stepperPattern->CreateArrowRightButtonNode(INDEX, false);
    auto buttonFocusHub = stepperItemNode->GetFocusHub();
    ASSERT_NE(buttonFocusHub, nullptr);
    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(leftButtonNode, nullptr);
    auto leftFocusHub = leftButtonNode->GetFocusHub();
    ASSERT_NE(leftFocusHub, nullptr);
    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(rightButtonNode, nullptr);
    auto rightFocusHub = rightButtonNode->GetFocusHub();
    ASSERT_NE(rightFocusHub, nullptr);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("skip");
    auto focusNode = stepperPattern->GetFocusNode(FocusStep::RIGHT_END, leftFocusHub);
    ASSERT_NE(focusNode.Upgrade(), leftFocusHub);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("disabled");
    focusNode = stepperPattern->GetFocusNode(FocusStep::SHIFT_TAB, leftFocusHub);
    ASSERT_NE(focusNode.Upgrade(), leftFocusHub);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("waiting");
    focusNode = stepperPattern->GetFocusNode(FocusStep::SHIFT_TAB, leftFocusHub);
    ASSERT_NE(focusNode.Upgrade(), leftFocusHub);
}

/**
 * @tc.name: StepperPatternUpdateOrCreateLeftButtonNode002
 * @tc.desc: test stepper pattern UpdateOrCreateLeftButtonNode.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPatternUpdateOrCreateLeftButtonNode002, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, hostNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    hostNode->AddChild(swiperNode);
    auto frameNode1 = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    swiperNode->AddChild(frameNode1);
    ASSERT_NE(frameNode1, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    swiperPattern->controller_ = CREATE_ANIMATOR(hostNode->GetContextRefPtr());
    auto swiperAnimationController = swiperPattern->GetController();
    ASSERT_NE(swiperAnimationController, nullptr);
    stepperPattern->HandlingLeftButtonClickEvent();
    auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
    ASSERT_NE(swiperController, nullptr);
    swiperAnimationController->status_ = Animator::Status::STOPPED;
    stepperPattern->HandlingLeftButtonClickEvent();
    swiperAnimationController->status_ = Animator::Status::RUNNING;
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    swiperNode->AddChild(stepperItemNode);
    stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->UpdateLabelStatus("normal");
    stepperPattern->UpdateOrCreateLeftButtonNode(1);
    EXPECT_EQ(swiperAnimationController->status_, Animator::Status::RUNNING);
}

/**
 * @tc.name: StepperItemFrameNodeCreator001
 * @tc.desc: Test all the properties of StepperItem.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.leftLabelValue = LEFT_LABEL;
    testProperty.rightLabelValue = RIGHT_LABEL;
    testProperty.labelStatusValue = LABEL_STATUS;

    RefPtr<FrameNode> frameNode = CreateStepperItemNode(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<StepperItemLayoutProperty> layoutProperty = frameNode->GetLayoutProperty<StepperItemLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetLeftLabelValue(), LEFT_LABEL);
    EXPECT_EQ(layoutProperty->GetRightLabelValue(), RIGHT_LABEL);
    EXPECT_EQ(layoutProperty->GetLabelStatus(), LABEL_STATUS);
}

/**
 * @tc.name: StepperItemPatternCreate001
 * @tc.desc: Test All the pattern of StepperItemPattern
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperItemPatternCreate001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.leftLabelValue = LEFT_LABEL;
    testProperty.rightLabelValue = RIGHT_LABEL;
    testProperty.labelStatusValue = LABEL_STATUS;

    RefPtr<FrameNode> frameNode = CreateStepperItemNode(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto stepperItemPattern = frameNode->GetPattern<StepperItemPattern>();
    ASSERT_NE(stepperItemPattern, nullptr);
    bool isAtomicNode = stepperItemPattern->IsAtomicNode();
    EXPECT_FALSE(isAtomicNode);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetCurrentIndex(), STEPPER_ERROR);

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    stepperPattern_->index_ = INDEX_NUM;
    swiperLayoutProperty_->UpdateShowIndicator(false);
    EXPECT_EQ(stepperAccessibilityProperty_->GetCurrentIndex(), INDEX_NUM);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetBeginIndex(), STEPPER_ERROR);

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);
    EXPECT_EQ(stepperAccessibilityProperty_->GetBeginIndex(), 0);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetEndIndex(), STEPPER_ERROR);

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);

    EXPECT_EQ(stepperAccessibilityProperty_->GetEndIndex(), INDEX_NUM);
}

/**
 * @tc.name: StepperAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitStepperTestNg();

    auto swiperLayoutProperty = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateLoop(false);
    EXPECT_FALSE(stepperAccessibilityProperty_->IsScrollable());

    for (int i = 0; i <= INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);
    auto swiperPattern = swiperNode_->GetPattern<SwiperPattern>();
    EXPECT_TRUE(stepperAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: StepperAccessibilityPropertyGetCollectionItemCounts001
 * @tc.desc: Test GetCollectionItemCounts of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAccessibilityPropertyGetCollectionItemCounts001, TestSize.Level1)
{
    InitStepperTestNg();

    EXPECT_EQ(stepperAccessibilityProperty_->GetCollectionItemCounts(), 0);

    for (int i = 0; i < INDEX_NUM; i++) {
        auto indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    swiperLayoutProperty_->UpdateShowIndicator(false);
    EXPECT_EQ(stepperAccessibilityProperty_->GetCollectionItemCounts(), INDEX_NUM);
}

/**
 * @tc.name: StepperAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitStepperTestNg();

    auto swiperLayoutProperty = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateLoop(false);
    swiperLayoutProperty_->UpdateShowIndicator(false);
    for (int index = 0; index <= INDEX_NUM; index++) {
        RefPtr<FrameNode> indicatorNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_INDICATOR_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<SwiperIndicatorPattern>(); });
        ASSERT_NE(indicatorNode, nullptr);
        swiperNode_->AddChild(indicatorNode);
    }
    stepperPattern_->index_ = 1;

    stepperAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = stepperAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);

    swiperLayoutProperty->UpdateLoop(true);
    stepperAccessibilityProperty_->ResetSupportAction();
    supportAceActions = stepperAccessibilityProperty_->GetSupportAction();
    actions = 0;
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
/**
 * @tc.name: StepperAlgorithmTest004
 * @tc.desc: test Stepper pattern algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAlgorithmTest004, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        stepperFrameNode, AceType::MakeRefPtr<GeometryNode>(), stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = AceType::DynamicCast<StepperLayoutAlgorithm>(stepperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));
    auto rightButtonHeight =
        stepperLayoutAlgorithm->CaluateButtonHeight(AccessibilityManager::RawPtr(layoutWrapper), true);
    EXPECT_EQ(rightButtonHeight, 0);
}
/**
 * @tc.name: StepperAlgorithmTest005
 * @tc.desc: test Stepper pattern algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAlgorithmTest005, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        stepperFrameNode, AceType::MakeRefPtr<GeometryNode>(), stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = AceType::DynamicCast<StepperLayoutAlgorithm>(stepperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));
    auto leftButtonHeight =
        stepperLayoutAlgorithm->CaluateButtonHeight(AccessibilityManager::RawPtr(layoutWrapper), false);
    EXPECT_EQ(leftButtonHeight, 0);
}

/**
 * @tc.name: StepperPattrenOnLanguageConfigurationUpdate001
 * @tc.desc: Test OnLanguageConfigurationUpdate of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperPattrenOnLanguageConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode, pattern.
     */
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    frameNode->AddChild(swiperNode);
    swiperNode->AddChild(stepperItemNode);
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    stepperPattern->isRightToLeft_ = false;

    stepperPattern->CreateLeftButtonNode();
    stepperPattern->CreateArrowRightButtonNode(INDEX, false);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    stepperPattern->OnLanguageConfigurationUpdate();

    auto leftImageLayoutProperty = stepperPattern->leftImage_->GetLayoutProperty<ImageLayoutProperty>();
    auto rightImageLayoutProperty = stepperPattern->rightImage_->GetLayoutProperty<ImageLayoutProperty>();
    auto leftimageSourceInfo = leftImageLayoutProperty->GetImageSourceInfo();
    auto rightimageSourceInfo = rightImageLayoutProperty->GetImageSourceInfo();
    EXPECT_EQ(leftimageSourceInfo->GetResourceId(), InternalResource::ResourceId::STEPPER_NEXT_ARROW);
    EXPECT_EQ(rightimageSourceInfo->GetResourceId(), InternalResource::ResourceId::STEPPER_BACK_ARROW);

    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    stepperPattern->OnLanguageConfigurationUpdate();
    leftImageLayoutProperty = stepperPattern->leftImage_->GetLayoutProperty<ImageLayoutProperty>();
    rightImageLayoutProperty = stepperPattern->rightImage_->GetLayoutProperty<ImageLayoutProperty>();
    leftimageSourceInfo = leftImageLayoutProperty->GetImageSourceInfo();
    rightimageSourceInfo = rightImageLayoutProperty->GetImageSourceInfo();
    EXPECT_EQ(leftimageSourceInfo->GetResourceId(), InternalResource::ResourceId::STEPPER_BACK_ARROW);
    EXPECT_EQ(rightimageSourceInfo->GetResourceId(), InternalResource::ResourceId::STEPPER_NEXT_ARROW);
}

/**
 * @tc.name: StepperAlgorithmTest006
 * @tc.desc: Test StepperAlgorithmLayout.LayoutRightButton And LayoutLeftButton of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperAlgorithmTest006, TestSize.Level1)
{
    StepperModelNG().Create(INDEX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    auto stepperFrameNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(stepperFrameNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        stepperFrameNode, AceType::MakeRefPtr<GeometryNode>(), stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = stepperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(RK356_WIDTH, RK356_HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(RK356_WIDTH, RK356_HEIGHT);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        SWIPER_NODE_TAG, stepperFrameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        CreateChildLayoutWrapper(layoutWrapper, stepperFrameNode, swiperNode);

    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stepperFrameNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    RefPtr<LayoutWrapperNode> leftButtonLayoutWrapper =
        CreateChildLayoutWrapper(layoutWrapper, stepperFrameNode, leftButtonNode);

    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, stepperFrameNode->GetRightButtonId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    RefPtr<LayoutWrapperNode> rightButtonLayoutWrapper =
        CreateChildLayoutWrapper(layoutWrapper, stepperFrameNode, rightButtonNode);

    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    RefPtr<LayoutWrapperNode> rowLayoutWrapper =
        CreateChildLayoutWrapper(leftButtonLayoutWrapper, leftButtonNode, rowNode);
    rightButtonNode->AddChild(rowNode);
    rightButtonLayoutWrapper->AppendChild(rowLayoutWrapper);

    auto rightTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<LayoutWrapperNode> rightTextLayoutWrapper =
        CreateChildLayoutWrapper(rowLayoutWrapper, rowNode, rightTextNode);

    auto leftTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<LayoutWrapperNode> leftTextLayoutWrapper = CreateChildLayoutWrapper(rowLayoutWrapper, rowNode, leftTextNode);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    stepperLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));

    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(hostNode->HasRightButtonNode());
    auto Rightindex = hostNode->GetChildIndexById(hostNode->GetRightButtonId());
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(Rightindex);
    CHECK_NULL_VOID(hostNode->HasLeftButtonNode());
    auto leftindex = hostNode->GetChildIndexById(hostNode->GetLeftButtonId());
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(leftindex);
    auto rightButtonOffsetOld = rightButtonWrapper->GetGeometryNode()->GetMarginFrameOffset();
    auto leftButtonOffsetOld = leftButtonWrapper->GetGeometryNode()->GetMarginFrameOffset();
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    stepperLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_NE(rightButtonOffsetOld,
        layoutWrapper->GetOrCreateChildByIndex(Rightindex)->GetGeometryNode()->GetMarginFrameOffset());
    ASSERT_NE(leftButtonOffsetOld,
        layoutWrapper->GetOrCreateChildByIndex(leftindex)->GetGeometryNode()->GetMarginFrameOffset());
}

/**
 * @tc.name: StepperLayoutAlgorithmMeasure001
 * @tc.desc: Increase the coverage of StepperLayoutAlgorithm::Measure function..
 * @tc.type: FUNC
 */
HWTEST_F(StepperTestNg, StepperLayoutAlgorithmMeasure001, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(stepperFrameNode, geometryNode, stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = stepperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = SizeF(RK356_HEIGHT, RK356_HEIGHT);
    layoutConstraint.percentReference = layoutConstraint.maxSize;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), layoutConstraint.maxSize);

    PipelineBase::GetCurrentContext()->fontScale_ = SUIT_AGE_LEVEL_THRER;
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), layoutConstraint.maxSize);

    PipelineBase::GetCurrentContext()->fontScale_ = SUIT_AGE_LEVEL_TWO;
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), layoutConstraint.maxSize);

    PipelineBase::GetCurrentContext()->fontScale_ = SUIT_AGE_LEVEL_ONE;
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), layoutConstraint.maxSize);

    layoutConstraint.maxSize = SizeF(RK356_HEIGHT, Infinity<float>());
    layoutConstraint.percentReference = layoutConstraint.maxSize;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());

    layoutConstraint.maxSize = SizeF(Infinity<float>(), RK356_HEIGHT);
    layoutConstraint.percentReference = layoutConstraint.maxSize;
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraint);
    stepperLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF());
}
} // namespace OHOS::Ace::NG
