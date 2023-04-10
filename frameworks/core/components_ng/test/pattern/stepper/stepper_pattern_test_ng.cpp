/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"
#include "core/components_ng/pattern/stepper/stepper_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_item_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
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
} // namespace

class StepperPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void StepperPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    // set StepperTheme to themeManager before using themeManager to get StepperTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<StepperTheme>()));
}

void StepperPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: StepperFrameNodeCreator001
 * @tc.desc: Test all the event of stepper.
 * @tc.type: FUNC
 */
HWTEST_F(StepperPatternTestNg, StepperFrameNodeCreator001, TestSize.Level1)
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
    eventHub->FireFinishEvent();
    EXPECT_EQ(eventName, FINISH_EVENT_NAME);
    eventHub->FireSkipEvent();
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
HWTEST_F(StepperPatternTestNg, StepperNodeGetOrCreateStepperNode001, TestSize.Level1)
{
    std::string stepperTag = STEPPER_ITEM_TAG;
    std::string stepperTagGet = STEPPER_ITEM_TAG_GET;
    std::string stepperTagGetEx = STEPPER_ITEM_TAG_GET_EX;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stepperNode = AceType::MakeRefPtr<StepperNode>(stepperTag, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stepperNode, nullptr);
    RefPtr<StepperNode> newStepperNode = stepperNode->GetOrCreateStepperNode(stepperTag, nodeId, nullptr);
    ASSERT_NE(newStepperNode, nullptr);
    EXPECT_EQ(newStepperNode->GetTag(), stepperNode->GetTag());

    auto nodeIdGet = ElementRegister::GetInstance()->MakeUniqueId();
    auto parentStepperNode =  FrameNode::GetOrCreateFrameNode(
        stepperTagGet, nodeIdGet, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(parentStepperNode, nullptr);
    stepperNode->AddChild(parentStepperNode);
    EXPECT_FALSE(stepperNode->children_.empty());

    newStepperNode = stepperNode->GetOrCreateStepperNode(stepperTagGetEx, nodeIdGet, nullptr);
    ASSERT_NE(newStepperNode, nullptr);
    auto parent = parentStepperNode->GetParent();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(newStepperNode->GetTag(), stepperTagGetEx);
    EXPECT_NE(newStepperNode->GetParent(), stepperNode);
}

/**
 * @tc.name: StepperNodeAddChildToGroup001
 * @tc.desc: test AddChild and DeleteChild methods
 * @tc.type: FUNC
 */
HWTEST_F(StepperPatternTestNg, StepperNodeAddChildToGroup001, TestSize.Level1)
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
    auto stepperNode = AceType::MakeRefPtr<StepperNode>(STEPPER_ITEM_TAG,
        nodeId, AceType::MakeRefPtr<StepperPattern>());
    ASSERT_NE(stepperNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        stepperNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
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
HWTEST_F(StepperPatternTestNg, StepperPatternInitSwiperChangeEvent001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
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
HWTEST_F(StepperPatternTestNg, UpdateOrCreateLeftButtonNode001, TestSize.Level1)
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
    auto stepperItemNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG_GET,
       stepperNodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperItemNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
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
HWTEST_F(StepperPatternTestNg, StepperPatternCreateLeftButtonNode001, TestSize.Level1)
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
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
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
HWTEST_F(StepperPatternTestNg, UpdateOrCreateRightButtonNode001, TestSize.Level1)
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
HWTEST_F(StepperPatternTestNg, StepperPatternCreateArrowRightButtonNode001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
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
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
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
HWTEST_F(StepperPatternTestNg, StepperPatternCreateArrowlessRightButtonNode001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);

    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        frameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);
    StepperItemModelNG().Create();
    auto stepperItemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(stepperItemNode, nullptr);
    frameNode->AddChild(swiperNode);
    swiperNode->AddChild(stepperItemNode);
    stepperPattern->CreateArrowlessRightButtonNode(INDEX,
        Localization::GetInstance()->GetEntryLetters("stepper.start"));
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto buttonId = hostNode->GetRightButtonId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
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
HWTEST_F(StepperPatternTestNg, StepperPatternCreateWaitingRightButtonNode001, TestSize.Level1)
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
    auto loadingProgressNode = FrameNode::GetOrCreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG,
        buttonId, []() { return AceType::MakeRefPtr<LoadingProgressPattern>(); });
    ASSERT_NE(loadingProgressNode, nullptr);
    EXPECT_EQ(loadingProgressNode->GetParent(), hostNode);
}
/**
 * @tc.name: StepperPatternButtonOnHover001
 * @tc.desc: test Stepper pattern ButtonOnHover.
 * @tc.type: FUNC
 */
HWTEST_F(StepperPatternTestNg, StepperPatternButtonOnHover001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto buttonId = hostNode->GetLeftButtonId();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    EXPECT_FALSE(stepperPattern->leftIsHover_);
    stepperPattern->ButtonOnHover(buttonNode, true, true);
    EXPECT_TRUE(stepperPattern->leftIsHover_);
    stepperPattern->ButtonOnHover(buttonNode, true, true);
    EXPECT_TRUE(stepperPattern->leftIsHover_);
    stepperPattern->ButtonOnHover(buttonNode, false, true);
    EXPECT_FALSE(stepperPattern->leftIsHover_);
    EXPECT_FALSE(stepperPattern->rightIsHover_);
    stepperPattern->ButtonOnHover(buttonNode, true, false);
    EXPECT_TRUE(stepperPattern->rightIsHover_);
    stepperPattern->ButtonOnHover(buttonNode, true, false);
    EXPECT_TRUE(stepperPattern->rightIsHover_);
    stepperPattern->ButtonOnHover(buttonNode, false, false);
    EXPECT_FALSE(stepperPattern->rightIsHover_);
}
} // namespace OHOS::Ace::NG
