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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
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
const float RK356_WIDTH = 720.0f;
const float RK356_HEIGHT = 1136.0f;
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
} // namespace

class StepperPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static RefPtr<LayoutWrapper> CreateChildLayoutWrapper(
        RefPtr<LayoutWrapper> layoutWrapper, RefPtr<FrameNode> parentNode, RefPtr<FrameNode> childNode);
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

RefPtr<LayoutWrapper> StepperPatternTestNg::CreateChildLayoutWrapper(
    RefPtr<LayoutWrapper> layoutWrapper, RefPtr<FrameNode> parentNode, RefPtr<FrameNode> childNode)
{
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    childGeometryNode->Reset();
    RefPtr<LayoutWrapper> childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        childNode, childGeometryNode, childNode->GetLayoutProperty());
    parentNode->AddChild(childNode);
    layoutWrapper->AppendChild(childLayoutWrapper);
    return childLayoutWrapper;
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
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stepperNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
                    nodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperNode, nullptr);
    RefPtr<StepperNode> newStepperNode = stepperNode->GetOrCreateStepperNode(STEPPER_ITEM_TAG, nodeId, nullptr);
    ASSERT_NE(newStepperNode, nullptr);
    EXPECT_EQ(newStepperNode->GetTag(), stepperNode->GetTag());

    auto nodeIdGet = ElementRegister::GetInstance()->MakeUniqueId();
    auto childStepperNode =  StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG_GET,
                    nodeIdGet, []() { return AceType::MakeRefPtr<StepperPattern>(); });
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
    EXPECT_EQ(stepperPattern->GetCurrentIndex(), INDEX);
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
/**
 * @tc.name: StepperPatternClickEvent001
 * @tc.desc: test Stepper pattern button click event.
 * @tc.type: FUNC
 */
HWTEST_F(StepperPatternTestNg, StepperPatternClickEvent001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        hostNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(leftButtonNode, nullptr);
    hostNode->AddChild(leftButtonNode);
    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(rightButtonNode, nullptr);
    hostNode->AddChild(rightButtonNode);
    stepperPattern->ButtonOnTouch(leftButtonNode, TouchType::DOWN);
    stepperPattern->ButtonOnTouch(leftButtonNode, TouchType::UP);
    auto leftGestureHub = leftButtonNode->GetOrCreateGestureEventHub();
    auto rightGestureHub = rightButtonNode->GetOrCreateGestureEventHub();
    EXPECT_FALSE(leftGestureHub->IsClickable());
    EXPECT_FALSE(rightGestureHub->IsClickable());
    stepperPattern->InitButtonClickEvent();
    EXPECT_TRUE(leftGestureHub->IsClickable());
    EXPECT_TRUE(rightGestureHub->IsClickable());
}
/**
 * @tc.name: StepperPatternHandleClickEvent001
 * @tc.desc: test Stepper pattern handle button click event.
 * @tc.type: FUNC
 */
HWTEST_F(StepperPatternTestNg, StepperPatternHandleClickEvent001, TestSize.Level1)
{
    auto frameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    stepperPattern->CreateLeftButtonNode();
    auto hostNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        hostNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    hostNode->AddChild(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    swiperPattern->controller_ = CREATE_ANIMATOR(hostNode->GetContext());
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
HWTEST_F(StepperPatternTestNg, StepperAlgorithmTest001, TestSize.Level1)
{
    StepperModelNG().Create(INDEX);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    auto stepperFrameNode = AceType::DynamicCast<StepperNode>(stepperPattern->GetHost());
    ASSERT_NE(stepperFrameNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(stepperFrameNode,
        AceType::MakeRefPtr<GeometryNode>(), stepperFrameNode->GetLayoutProperty());
    auto stepperLayoutAlgorithm = stepperPattern->CreateLayoutAlgorithm();
    ASSERT_NE(stepperLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(stepperLayoutAlgorithm));
    
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = SizeF(RK356_WIDTH, RK356_HEIGHT);
    parentLayoutConstraint.percentReference = SizeF(RK356_WIDTH, RK356_HEIGHT);

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto swiperNode = FrameNode::GetOrCreateFrameNode(SWIPER_NODE_TAG,
        stepperFrameNode->GetSwiperId(), []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    RefPtr<LayoutWrapper> swiperLayoutWrapper = CreateChildLayoutWrapper(layoutWrapper,
                                                        stepperFrameNode, swiperNode);

    auto leftButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        stepperFrameNode->GetLeftButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    RefPtr<LayoutWrapper> leftButtonLayoutWrapper = CreateChildLayoutWrapper(layoutWrapper,
                                                        stepperFrameNode, leftButtonNode);
    
    auto rightButtonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        stepperFrameNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    RefPtr<LayoutWrapper> rightButtonLayoutWrapper = CreateChildLayoutWrapper(layoutWrapper,
                                                        stepperFrameNode, rightButtonNode);

    auto rowNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto rowNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
        rowNodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    RefPtr<LayoutWrapper> rowLayoutWrapper = CreateChildLayoutWrapper(leftButtonLayoutWrapper,
                                                        leftButtonNode, rowNode);
    rightButtonNode->AddChild(rowNode);
    rightButtonLayoutWrapper->AppendChild(rowLayoutWrapper);

    auto rightTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<LayoutWrapper> rightTextLayoutWrapper = CreateChildLayoutWrapper(rowLayoutWrapper,
                                                        rowNode, rightTextNode);

    auto leftTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<LayoutWrapper> leftTextLayoutWrapper = CreateChildLayoutWrapper(rowLayoutWrapper,
                                                        rowNode, leftTextNode);

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
HWTEST_F(StepperPatternTestNg, StepperAlgorithmTest002, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(stepperFrameNode, geometryNode, stepperFrameNode->GetLayoutProperty());
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
HWTEST_F(StepperPatternTestNg, StepperAlgorithmTest003, TestSize.Level1)
{
    auto stepperFrameNode = StepperNode::GetOrCreateStepperNode(STEPPER_ITEM_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<StepperPattern>(); });
    ASSERT_NE(stepperFrameNode, nullptr);
    auto stepperPattern = stepperFrameNode->GetPattern<StepperPattern>();
    ASSERT_NE(stepperPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(stepperFrameNode, geometryNode, stepperFrameNode->GetLayoutProperty());
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
HWTEST_F(StepperPatternTestNg, StepperEventHubChangeEvent001, TestSize.Level1)
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
HWTEST_F(StepperPatternTestNg, PerformActionTest001, TestSize.Level1)
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
HWTEST_F(StepperPatternTestNg, GetFocusNode001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG
