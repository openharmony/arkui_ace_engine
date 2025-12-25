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
#include "test/unittest/core/event/focus_hub_test_ng.h"
#include "gtest/gtest.h"
#include "core/components_ng/event/focus_event_handler.h"
#include "core/event/focus_axis_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void FocusHubTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "FocusHubTestNg SetUpTestCase";
}

void FocusHubTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "FocusHubTestNg TearDownTestCase";
}

void FocusHubTestNg::SetUp() {}

void FocusHubTestNg::TearDown()
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ASSERT_NE(context->rootNode_, nullptr);
    context->rootNode_->children_.clear();
}

/**
 * @tc.name: FocusHubCreateTest001
 * @tc.desc: Create FocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with passing is null as parameter.
     * @tc.expected: eventHub_ cannot be updated.
     */
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(WeakPtr<EventHub>(nullptr));
    EXPECT_TRUE(focusHub1->GetFrameNode() == nullptr);
    EXPECT_TRUE(focusHub1->IsEnabled());
    EXPECT_TRUE(!focusHub1->IsFocusableNode());

    /**
     * @tc.steps: step2. Create FocusHub with the WeakPtr eventHub_ which does not own frameNode.
     * @tc.expected: eventHub can be updated, but cannot get frameNode and its related properties.
     */
    RefPtr<EventHub> eventHub2 = AceType::MakeRefPtr<EventHub>();
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    EXPECT_TRUE(focusHub2 != nullptr);
    EXPECT_TRUE(focusHub2->GetFrameNode() == nullptr);
    EXPECT_TRUE(focusHub2->GetGeometryNode() == nullptr);
    EXPECT_EQ(focusHub2->GetFrameName(), "NULL");
    EXPECT_EQ(focusHub2->GetInspectorKey(), std::nullopt);

    /**
     * @tc.steps: step3. Invoke GetParentFocusHub without parameter.
     * @tc.expected: FocusHub will return frameNode' parent focusHub which is also nullptr.
     */
    EXPECT_TRUE(focusHub2->GetParentFocusHub() == nullptr);

    /**
     * @tc.steps: step4. Invoke GetParentFocusHub passing node as parameter which does not have parent.
     * @tc.expected: FocusHub will return node' parent focusHub which does not exist.
     */
    auto node = FrameNodeOnTree(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_TRUE(focusHub2->GetParentFocusHub() == nullptr);
}

/**
 * @tc.name: FocusHubCreateTest002
 * @tc.desc: Create FocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubCreateTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with the WeakPtr eventHub_ owning frameNode.
     * @tc.expected: eventHub can be updated and can get frameNode and its related properties.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_TRUE(focusHub->GetFrameNode() != nullptr);
    EXPECT_TRUE(focusHub->GetGeometryNode() != nullptr);
    EXPECT_EQ(focusHub->GetFrameName(), V2::TEXT_ETS_TAG);
    EXPECT_EQ(focusHub->GetInspectorKey(), std::nullopt);

    /**
     * @tc.steps: step2. Invoke GetParentFocusHub without passing parameter.
     * @tc.expected: FocusHub will return frameNode' parent focusHub which is also nullptr.
     */
    EXPECT_TRUE(focusHub->GetParentFocusHub() == nullptr);

    /**
     * @tc.steps: step3. Create focusHub and its frameNode has parent node.
     * @tc.expected: FocusHub will return frameNode' parent focusHub.
     */
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1,
        AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    eventHub->AttachHost(frameNode);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_TRUE(focusHub2->GetParentFocusHub() != nullptr);
}

/**
 * @tc.name: FocusHubFlushChildrenFocusHubTest003
 * @tc.desc: Create FocusHub and invoke FlushChildrenFocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubFlushChildrenFocusHubTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Invoke FlushChildrenFocusHub to get the focusable children.
     * @tc.expected: Button is the focusable child which will be emplace_back in focusNodes_.
     */
    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(focusNodes.size(), FOCUS_NODE_SIZE);
    EXPECT_EQ(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step4. lastWeakFocusNode_ is not nullptr.
     * @tc.expected: itLastFocusNode_ will be assigned the iter corresponding lastWeakFocusNode_ found in focusNodes_.
     */
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    EXPECT_EQ(focusHub->lastWeakFocusNode_.Upgrade(), *(focusNodes.begin()));
}

/**
 * @tc.name: FocusHubRemoveSelfTest004
 * @tc.desc: Create FocusHub and invoke RemoveSelf.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRemoveSelfTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add its parent.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1,
        AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Remove self.
     * @tc.expected: The nodeParent children size is 0.
     */
    focusHub->focusScopeId_="1";
    focusHub->RemoveSelf();
    EXPECT_EQ(nodeParent->GetChildren().size(), NODE_SIZE);
}

/**
 * @tc.name: FocusHubLostFocusTest005
 * @tc.desc: Create FocusHub and invoke LostFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubLostFocusTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Invoke LostFocus, when FocusType is DISABLE and  the blur reason is FOCUS_SWITCH.
     * @tc.expected: currentFocus_ is false.
     */
    focusHub->currentFocus_ = true;
    focusHub->LostFocus(BLUR_REASON_FOCUS_SWITCH);
    EXPECT_EQ(focusHub->blurReason_, BLUR_REASON_FOCUS_SWITCH);
    EXPECT_FALSE(focusHub->currentFocus_);

    /**
     * @tc.steps: step4. Invoke LostFocus, when FocusType is NODE and  the blur reason is WINDOW_BLUR.
     * @tc.expected: currentFocus_ is false.
     */
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::NODE;
    focusHub->LostFocus(BLUR_REASON_WINDOW_BLUR);
    EXPECT_EQ(focusHub->blurReason_, BLUR_REASON_WINDOW_BLUR);
    EXPECT_FALSE(focusHub->currentFocus_);

    /**
     * @tc.steps: step5. Invoke LostFocus, when FocusType is SCOPE and  the blur reason is WINDOW_BLUR.
     * @tc.expected: currentFocus_ is false.
     */
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->LostFocus(BLUR_REASON_WINDOW_BLUR);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubHandleKeyEventTest006
 * @tc.desc: Create FocusHub and invoke HandleKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubHandleKeyEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Focus hub does not currently focused and FocusType is DISABLE.
     * @tc.expected: Do not handle key event.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::TV_CONTROL_UP;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    /**
     * @tc.steps: step4. Focus hub is currently focused, FocusType is DISABLE and key code is TV_CONTROL_UP.
     * @tc.expected: OnKeyEventScope -> RequestNextFocus.
     */
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->currentFocus_ = true;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg007
 * @tc.desc: Test the function IsFocusableScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;

    /**
     * @tc.steps2: call the function SetEnabled with false
     * @tc.expected: The return value of IsFocusableScope is false.
     */
    eventHub->SetEnabled(false);
    EXPECT_FALSE(focusHub->IsFocusableScope());

    /**
     * @tc.steps3: call the function SetEnabled with true.
     * @tc.expected: The return value of IsFocusableScope is false.
     */
    eventHub->SetEnabled(true);
    EXPECT_FALSE(focusHub->IsFocusableScope());
}

/**
 * @tc.name: FocusHubTestNg008
 * @tc.desc: Test the function SetFocusable.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: The default value of focusable_ is false.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_FALSE(focusHub->focusable_);

    /**
     * @tc.steps2: Set focusable_ to true implicitly.
     * @tc.expected: The value of focusable_ is true.
     */
    focusHub->SetFocusable(true, false);
    EXPECT_TRUE(focusHub->focusable_);

    /**
     * @tc.steps3:Set focusable_ to false explicitly.
     * @tc.expected: The value of focusable_ is false.
     */
    focusHub->SetFocusable(false);

    /**
     * @tc.steps4:Set focusable_ to true implicitly.
     * @tc.expected: The value of focusable_ is false.
     */
    focusHub->SetFocusable(true, false);
    EXPECT_FALSE(focusHub->focusable_);

    /**
     * @tc.steps5:Set focusable_ to true explicitly.
     * @tc.expected: The value of focusable_ is true.
     */
    focusHub->SetFocusable(true);
    EXPECT_TRUE(focusHub->focusable_);
}

/**
 * @tc.name: FocusHubTestNg009
 * @tc.desc: Test the function IsFocusable.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    eventHub->SetEnabled(false);

    /**
     * @tc.steps2: call the function IsFocusable with FocusType::NODE
     * @tc.expected: The return value of IsFocusable is false.
     */
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_FALSE(focusHub->IsFocusable());

    /**
     * @tc.steps3: call the function IsFocusable with FocusType::SCOPE
     * @tc.expected: The return value of IsFocusable is false.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_FALSE(focusHub->IsFocusable());

    /**
     * @tc.steps4: call the function IsFocusable with FocusType::DISABLE
     * @tc.expected: The return value of IsFocusable is false.
     */
    focusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_FALSE(focusHub->IsFocusable());
}

/**
 * @tc.name: FocusHubTestNg010
 * @tc.desc: Test the function RequestFocusImmediately.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0010, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps2: call the function SetFocusType with currentFocus_ = false.
     * @tc.expected: The return value of RequestFocusImmediately is false.
     */
    context->SetIsFocusingByTab(true);
    focusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_FALSE(focusHub->RequestFocusImmediately());

    /**
     * @tc.steps3: call the function SetFocusType with currentFocus_ = true
     * @tc.expected: The return value of RequestFocusImmediately is true.
     */
    context->SetIsFocusingByTab(false);
    focusHub->SetFocusType(FocusType::DISABLE);
    focusHub->currentFocus_ = true;
    EXPECT_TRUE(focusHub->RequestFocusImmediately());
}

/**
 * @tc.name: FocusHubTestNg011
 * @tc.desc: Test the function LostFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0011, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function LostFocus with currentFocus_ = false.
     * @tc.expected: The value of blurReason_ is changed to BlurReason::WINDOW_BLUR.
     */
    focusHub->blurReason_ = BlurReason::WINDOW_BLUR;
    focusHub->currentFocus_ = false;
    focusHub->LostFocus(BlurReason::FOCUS_SWITCH);
    EXPECT_EQ(focusHub->blurReason_, BlurReason::WINDOW_BLUR);

    /**
     * @tc.steps3: call the function LostFocus with currentFocus_ = true.
     * @tc.expected: The value of blurReason_ is changed to BlurReason::FOCUS_SWITCH.
     */
    focusHub->currentFocus_ = true;
    focusHub->LostFocus(BlurReason::FOCUS_SWITCH);
    EXPECT_EQ(focusHub->blurReason_, BlurReason::FOCUS_SWITCH);
}

/**
 * @tc.name: FocusHubTestNg012
 * @tc.desc: Test the function LostSelfFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0012, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function LostSelfFocus with currentFocus_ = false.
     * @tc.expected: The value of focusable_ is changed to false.
     */
    focusHub->currentFocus_ = false;
    focusHub->SetFocusable(false);
    focusHub->LostSelfFocus();
    EXPECT_FALSE(focusHub->focusable_);

    /**
     * @tc.steps3: call the function LostSelfFocus with currentFocus_ = true.
     * @tc.expected: The value of focusable_ is changed to true.
     */
    focusHub->currentFocus_ = true;
    focusHub->LostSelfFocus();
    EXPECT_TRUE(focusHub->focusable_);
}

/**
 * @tc.name: FocusHubTestNg013
 * @tc.desc: Test the function SetShow, SetEnabled, SetEnabledNode and SetEnabledScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0013, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    /**
     * @tc.steps2: call the function SetShow with FocusType::NODE.
     * @tc.expected: The value of show_ is changed to true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->SetShow(true);
    focusHub->SetEnabled(true);
    EXPECT_TRUE(focusHub->IsShow());

    /**
     * @tc.steps3: call the function SetShow with FocusType::SCOPE.
     * @tc.expected: The value of show_ is changed to false.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->SetShow(false);
    focusHub->SetEnabled(false);
    frameNode->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    EXPECT_FALSE(focusHub->IsShow());

    /**
     * @tc.steps4: call the function SetShow with FocusType::DISABLE.
     * @tc.expected: The value of show_ is changed to false.
     */
    focusHub->SetFocusType(FocusType::DISABLE);
    focusHub->SetShow(true);
    focusHub->SetEnabled(true);
    EXPECT_FALSE(focusHub->IsShow());
}

/**
 * @tc.name: FocusHubTestNg014
 * @tc.desc: Test functions OnFocus, OnFocusNode and OnFocusScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0014, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function OnFocus with FocusType::SCOPE.
     * @tc.expected: The focusNodes_ is empty.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->OnFocus();
    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_TRUE(focusNodes.empty());

    /**
     * @tc.steps3: call the function OnFocus with FocusType::NODE.
     * @tc.expected: The flagCbk1 and flagCbk2 are changed to true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->OnFocus();
    focusHub->currentFocus_ = true;
    bool flagCbk1 = false;
    bool flagCbk2 = false;
    focusHub->onFocusInternal_ = [&flagCbk1](FocusReason reason) { flagCbk1 = !flagCbk1; };
    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub->SetOnFocusCallback([&flagCbk2]() { flagCbk2 = !flagCbk2; });
    focusHub->OnFocus();
    EXPECT_TRUE(flagCbk1);
    EXPECT_TRUE(flagCbk2);
}

/**
 * @tc.name: FocusHubTestNg015
 * @tc.desc: Test functions OnBlur, OnBlurNode and OnBlurScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0015, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function OnBlur with FocusType::NODE.
     * @tc.expected: The flagCbk1 and flagCbk2 are changed to true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->OnBlur();
    bool flagCbk1 = false;
    bool flagCbk2 = false;
    BlurReason flagReason = BlurReason::WINDOW_BLUR;
    focusHub->onBlurInternal_ = [&flagCbk1]() { flagCbk1 = !flagCbk1; };
    focusHub->onBlurReasonInternal_ = [&flagReason](BlurReason reason) { flagReason = reason; };
    focusHub->SetOnBlurCallback([&flagCbk2]() { flagCbk2 = !flagCbk2; });
    focusHub->OnBlur();
    EXPECT_TRUE(flagCbk1);
    EXPECT_TRUE(flagCbk2);
    EXPECT_EQ(flagReason, BlurReason::FOCUS_SWITCH);

    /**
     * @tc.steps3: call the function OnBlur with FocusType::SCOPE.
     * @tc.expected: The flagCbk1 and flagCbk2 are changed to true.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->OnFocus();
    flagCbk1 = false;
    flagCbk2 = false;
    flagReason = BlurReason::WINDOW_BLUR;
    focusHub->onBlurInternal_ = [&flagCbk1]() { flagCbk1 = !flagCbk1; };
    focusHub->onBlurReasonInternal_ = [&flagReason](BlurReason reason) { flagReason = reason; };
    focusHub->SetOnBlurCallback([&flagCbk2]() { flagCbk2 = !flagCbk2; });
    focusHub->OnBlur();
    EXPECT_TRUE(flagCbk1);
    EXPECT_TRUE(flagCbk2);
    EXPECT_EQ(flagReason, BlurReason::FOCUS_SWITCH);
}

/**
 * @tc.name: FocusHubTestNg016
 * @tc.desc: Test the function OnKeyEvent, OnKeyEventScope and OnKeyEventNode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.isRedispatch = true;
    keyEvent.isPreIme = true;

    /**
     * @tc.steps2: call the function OnKeyEvent with FocusType::NODE.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    /**
     * @tc.steps3: call the function OnKeyEvent with FocusType::SCOPE.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    /**
     * @tc.steps4: call the function OnKeyEvent with FocusType::DISABLE.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    focusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg017
 * @tc.desc: Test the function HandleFocusByTabIndex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0017, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;

    /**
     * @tc.steps2: call the function HandleFocusByTabIndex with code != KeyCode::KEY_TAB and action != KeyAction::DOWN.
     * @tc.expected: The return value of HandleFocusByTabIndex is false.
     */
    keyEvent.action = KeyAction::UNKNOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    EXPECT_FALSE(focusHub->HandleFocusByTabIndex(keyEvent));

    /**
     * @tc.steps3: call the function HandleFocusByTabIndex with code != KeyCode::KEY_TAB and action == KeyAction::DOWN.
     * @tc.expected: The return value of HandleFocusByTabIndex is false.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    EXPECT_FALSE(focusHub->HandleFocusByTabIndex(keyEvent));

    /**
     * @tc.steps4: call the function HandleFocusByTabIndex with code == KeyCode::KEY_TAB and action != KeyAction::DOWN.
     * @tc.expected: The return value of HandleFocusByTabIndex is false.
     */
    keyEvent.action = KeyAction::UNKNOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    EXPECT_FALSE(focusHub->HandleFocusByTabIndex(keyEvent));

    /**
     * @tc.steps5: call the function HandleFocusByTabIndex with code == KeyCode::KEY_TAB and action == KeyAction::DOWN
     *             and curPage == null.
     * @tc.expected: The return value of HandleFocusByTabIndex is false.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    EXPECT_FALSE(focusHub->HandleFocusByTabIndex(keyEvent));

    /**
     * @tc.steps6: call the function HandleFocusByTabIndex with code == KeyCode::KEY_TAB and action == KeyAction::DOWN
     *             and curPage == focusHub.
     * @tc.expected: The return value of HandleFocusByTabIndex is false.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    EXPECT_FALSE(focusHub->HandleFocusByTabIndex(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg018
 * @tc.desc: Test the function HandleFocusByTabIndex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0018, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;

    /**
     * @tc.steps2: call the function GetFocusingTabNodeIdx with the empty TabIndexNodeList.
     * @tc.expected: The return value of the function is NONE_TAB_FOCUSED_INDEX.
     */
    TabIndexNodeList tabIndexNodes;
    EXPECT_EQ(focusHub->GetFocusingTabNodeIdx(tabIndexNodes), DEFAULT_TAB_FOCUSED_INDEX);

    /**
     * @tc.steps3: call the function GetFocusingTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is DEFAULT_TAB_FOCUSED_INDEX.
     */
    int32_t nodeId = 1;
    focusHub->lastTabIndexNodeId_ = nodeId;
    tabIndexNodes.emplace_back(focusHub->GetTabIndex(), focusHub);
    EXPECT_EQ(focusHub->GetFocusingTabNodeIdx(tabIndexNodes), DEFAULT_TAB_FOCUSED_INDEX);

    /**
     * @tc.steps4: call the function GetFocusingTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is 0.
     */
    nodeId = -1;
    focusHub->lastTabIndexNodeId_ = nodeId;
    focusHub->currentFocus_ = true;
    EXPECT_EQ(focusHub->GetFocusingTabNodeIdx(tabIndexNodes), 0);

    /**
     * @tc.steps5: call the function GetFocusingTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is NONE_TAB_FOCUSED_INDEX.
     */
    focusHub->currentFocus_ = false;
    EXPECT_EQ(focusHub->GetFocusingTabNodeIdx(tabIndexNodes), DEFAULT_TAB_FOCUSED_INDEX);
}

/**
 * @tc.name: FocusHubTestNg019
 * @tc.desc: Test the function RequestFocusImmediatelyById and GetChildFocusNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0019, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function RequestFocusImmediatelyById with the empty id.
     * @tc.expected: The return value of the function is false.
     */
    const std::string nullStr("");
    EXPECT_FALSE(focusHub->RequestFocusImmediatelyById(nullStr));

    /**
     * @tc.steps3: call the function RequestFocusImmediatelyById with the idStr.
     * @tc.expected: The return value of the function is false.
     */
    const std::string idStr(V2::TEXT_ETS_TAG);
    EXPECT_FALSE(focusHub->RequestFocusImmediatelyById(idStr));

    /**
     * @tc.steps4: call the function RequestFocusImmediatelyById with the idStr and FocusType::NODE.
     * @tc.expected: The return value of the function is false.
     */
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_FALSE(focusHub->RequestFocusImmediatelyById(idStr));

    /**
     * @tc.steps5: call the function RequestFocusImmediatelyById with the idStr and FocusType::SCOPE.
     * @tc.expected: The return value of the function is false.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_FALSE(focusHub->RequestFocusImmediatelyById(idStr));
}

/**
 * @tc.name: FocusHubTestNg020
 * @tc.desc: Test the function GetChildFocusNodeByType.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0020, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->SetEnabled(true);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function GetChildFocusNodeByType with FocusNodeType::DEFAULT.
     * @tc.expected: The return value of the function is focusHub.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->SetShow(true);
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->SetIsDefaultFocus(true);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::DEFAULT), focusHub);

    /**
     * @tc.steps3: call the function GetChildFocusNodeByType with FocusNodeType::DEFAULT and show_ = false.
     * @tc.expected: The return value of the function is nullptr.
     */
    focusHub->focusable_ = false;
    focusHub->SetShow(false);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::DEFAULT), nullptr);

    /**
     * @tc.steps4: call the function GetChildFocusNodeByType with FocusNodeType::DEFAULT and IsDefaultFocus = false.
     * @tc.expected: The return value of the function is nullptr.
     */
    focusHub->SetIsDefaultFocus(false);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::DEFAULT), nullptr);

    /**
     * @tc.steps5: call the function GetChildFocusNodeByType with FocusNodeType::DEFAULT and show_ = true.
     * @tc.expected: The return value of the function is focusHub.
     */
    focusHub->SetShow(true);
    focusHub->focusable_ = true;
    focusHub->SetIsDefaultGroupFocus(true);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT), focusHub);

    /**
     * @tc.steps6: call the function GetChildFocusNodeByType with FocusNodeType::DEFAULT and show_ = false.
     * @tc.expected: The return value of the function is nullptr.
     */
    focusHub->focusable_ = false;
    focusHub->SetShow(false);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT), nullptr);

    /**
     * @tc.steps7: call the function GetChildFocusNodeByType with FocusNodeType::DEFAULT and show_ = true and
     *             IsDefaultGroupFocus = false.
     * @tc.expected: The return value of the function is nullptr.
     */
    focusHub->SetShow(true);
    focusHub->SetIsDefaultGroupFocus(false);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT), nullptr);

    /**
     * @tc.steps8: call the function GetChildFocusNodeByType with FocusType::SCOPE.
     * @tc.expected: The return value of the function is nullptr.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_EQ(focusHub->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT), nullptr);
}

/**
 * @tc.name: FocusHubTestNg021
 * @tc.desc: Test the function GoToFocusByTabNodeIdx.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0021, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->SetEnabled(true);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function GoToFocusByTabNodeIdx with the empty TabIndexNodeList.
     * @tc.expected: The return value of the function is false.
     */
    TabIndexNodeList tabIndexNodes;
    EXPECT_FALSE(focusHub->GoToFocusByTabNodeIdx(tabIndexNodes, 0));

    /**
     * @tc.steps3: call the function GoToFocusByTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is false.
     */
    tabIndexNodes.emplace_back(focusHub->GetTabIndex(), nullptr);
    EXPECT_FALSE(focusHub->GoToFocusByTabNodeIdx(tabIndexNodes, 0));

    /**
     * @tc.steps4: call the function GoToFocusByTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is false.
     */
    tabIndexNodes.emplace_back(focusHub->GetTabIndex(), focusHub);
    EXPECT_FALSE(focusHub->GoToFocusByTabNodeIdx(tabIndexNodes, 1));

    /**
     * @tc.steps5: call the function GoToFocusByTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is false.
     */
    focusHub->SetIsDefaultGroupHasFocused(false);
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_FALSE(focusHub->GoToFocusByTabNodeIdx(tabIndexNodes, 1));

    /**
     * @tc.steps6: call the function GoToFocusByTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is false.
     */
    focusHub->SetIsDefaultGroupHasFocused(true);
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_FALSE(focusHub->GoToFocusByTabNodeIdx(tabIndexNodes, 1));

    /**
     * @tc.steps7: call the function GoToFocusByTabNodeIdx with the unempty TabIndexNodeList.
     * @tc.expected: The return value of the function is true.
     */
    focusHub->SetShow(true);
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_TRUE(focusHub->GoToFocusByTabNodeIdx(tabIndexNodes, 1));
}

/**
 * @tc.name: FocusHubTestNg022
 * @tc.desc: Test the function IsFocusableByTab, IsFocusableNodeByTab and IsFocusableScopeByTab.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0022, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: call the function IsFocusableByTab with FocusType::NODE.
     * @tc.expected: The return value of the function is true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_TRUE(focusHub->IsFocusableByTab());

    /**
     * @tc.steps3: call the function IsFocusableByTab with FocusType::SCOPE.
     * @tc.expected: The return value of the function is true.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_TRUE(focusHub->IsFocusableByTab());

    /**
     * @tc.steps4: call the function IsFocusableByTab with FocusType::DISABLE.
     * @tc.expected: The return value of the function is false.
     */
    focusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_FALSE(focusHub->IsFocusableByTab());
}
} // namespace OHOS::Ace::NG
