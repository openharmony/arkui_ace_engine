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

void FocusHubTestNg::TearDown() {}

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

/**
 * @tc.name: FocusHubHandleDumpFocusTreeTest023
 * @tc.desc: Test the function DumpFocusTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubHandleDumpFocusTreeTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
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
     * @tc.steps: step3. test function DumpFocusNodeTree.
     * @tc.expected: After DumpFocusTree, the DumpLog.description_ is empty.
     */
    int32_t depth = 1;
    focusHub->focusType_ = FocusType::NODE;
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    focusHub->currentFocus_ = true;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());

    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());

    /**
     * @tc.steps: step4. test function DumpFocusScopeTree.
     * @tc.expected: After DumpFocusTree, the DumpLog.description_ is empty.
     */
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->currentFocus_ = true;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());

    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());
}

/**
 * @tc.name: FocusHubRemoveChildTest001
 * @tc.desc: Test the function RemoveChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRemoveChildTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1,
        AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    frameNode2->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    frameNode2->SetParent(nodeParent);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Get parentFocusHub.
     */
    focusHub->currentFocus_ = true;
    auto parent = focusHub->GetParentFocusHub();

    /**
     * @tc.steps: step4. Test RemoveChild and parentFocusHub RemoveSelf.
     * @tc.expected: focusHub and parentFocusHub both lostFocus.
     */
    parent->currentFocus_ = true;
    parent->RemoveChild(focusHub);
    EXPECT_EQ(parent->blurReason_, BlurReason::FRAME_DESTROY);
    EXPECT_EQ(focusHub->blurReason_, BlurReason::FRAME_DESTROY);
}

/**
 * @tc.name: FocusHubSetIsFocusOnTouch001
 * @tc.desc: Test the function SetIsFocusOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubSetIsFocusOnTouch001, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps3: test SetIsFocusOnTouch.
     * @tc.expected: create touchEvents and set FocusOnTouch success.
     */
    focusHub->SetIsFocusOnTouch(true);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    EXPECT_FALSE(gesture->touchEventActuator_->touchEvents_.empty());

    /**
     * @tc.steps4: test SetIsFocusOnTouch.
     * @tc.expected: when touchEvents has been set, return.
     */
    focusHub->SetIsFocusOnTouch(true);
    EXPECT_TRUE(focusHub->IsFocusOnTouch().value());

    /**
     * @tc.steps4: test SetIsFocusOnTouch.
     * @tc.expected: set touchEvents false.
     */
    focusHub->SetIsFocusOnTouch(false);
    EXPECT_TRUE(gesture->touchEventActuator_->touchEvents_.empty());

    /**
     * @tc.steps5: test SetIsFocusOnTouch.
     * @tc.expected: set focusOnTouchListener_ success.
     */
    focusHub->SetIsFocusOnTouch(false);
    focusHub->focusOnTouchListener_ = nullptr;
    focusHub->SetIsFocusOnTouch(true);
    EXPECT_TRUE(focusHub->focusOnTouchListener_);
    auto touchCallback = focusHub->focusOnTouchListener_;
    TouchEventInfo touchEventInfo("onTouchUp");
    (*touchCallback)(touchEventInfo);
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->focusable_ = true;
    (*touchCallback)(touchEventInfo);
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubOnKeyEvent002
 * @tc.desc: Test the function OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubOnKeyEvent002, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.steps3: call the function OnKeyEvent with FocusType::NODE.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->currentFocus_ = true;
    auto onKeyEventCallback = [](KeyEventInfo& eventInfo) -> bool {
        eventInfo.SetStopPropagation(true);
        return false;
    };
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return true; };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
    focusHub->SetOnKeyCallback(std::move(onKeyEventCallback));
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubOnKeyEvent003
 * @tc.desc: Test the function OnKeyEvent.
 * @tc.type: FUNC obsolete
 */
HWTEST_F(FocusHubTestNg, FocusHubOnKeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    frameNode->AddChild(child);

    /**
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps3: create lastWeakFocusNode_.
     */
    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));

    /**
     * @tc.steps4: create keyEvent.
     */
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.steps5: create lastFocusNode.
     */
    focusHub->currentFocus_ = true;
    focusHub->SetFocusType(FocusType::SCOPE);
    auto onKeyEvent = [](const KeyEvent& event) -> bool { return true; };

    /**
     * @tc.steps6: call the function OnKeyEvent with FocusType::SCOPE.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    auto lastFocusNode = focusHub->lastWeakFocusNode_.Upgrade();
    lastFocusNode->currentFocus_ = true;
    lastFocusNode->SetOnKeyEventInternal(onKeyEvent);
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));

    /**
     * @tc.steps7: call the function OnKeyEvent with FocusType::SCOPE.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    lastFocusNode->currentFocus_ = false;
    focusHub->SetOnKeyEventInternal(onKeyEvent);
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubOnKeyEvent004
 * @tc.desc: Test the function OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubOnKeyEvent004, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
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
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto childEventHub = AceType::MakeRefPtr<EventHub>();
    childEventHub->AttachHost(child);

    /**
     * @tc.steps3: create lastWeakFocusNode_.
     */
    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    auto childFocusHub = *focusNodes.begin();
    childFocusHub->eventHub_ = childEventHub;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(childFocusHub));

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;

    /**
     * @tc.steps5: test keyEvent with keyEvent.code == KeyCode::TV_CONTROL_UP.
     * @tc.expected: The return value of OnKeyEvent is false.
     */
    keyEvent.code = KeyCode::TV_CONTROL_UP;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::TV_CONTROL_DOWN;
    focusHub->SetScopeFocusAlgorithm();
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::TV_CONTROL_LEFT;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::TV_CONTROL_RIGHT;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::KEY_TAB;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_TAB);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::KEY_MOVE_HOME;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::KEY_MOVE_END;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));

    keyEvent.code = KeyCode::KEY_SPACE;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubGoToNextFocusLinear001
 * @tc.desc: Test the function GoToNextFocusLinear.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubGoToNextFocusLinear001, TestSize.Level1)
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

    focusHub->currentFocus_ = true;

    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);

    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    EXPECT_TRUE(focusHub->GoToNextFocusLinear(FocusStep::TAB));
}

/**
 * @tc.name: FocusHubPaintFocusState001
 * @tc.desc: Test the function PaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintFocusState001, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    frameNode->AddChild(child);

    /**
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps3: create KeyEvent.
     */
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_EQ(focusHub->focusStyleType_, FocusStyleType::NONE);
}

/**
 * @tc.name: FocusHubSetIsDefaultFocus001
 * @tc.desc: Test the function SetIsDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetIsDefaultFocus001, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto manager = pipeline->GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    auto rootNode = pipeline->GetRootElement();
    EXPECT_NE(rootNode, nullptr);

    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->SetIsDefaultGroupFocus(false);
    EXPECT_NE(focusHub->focusCallbackEvents_, nullptr);
}

/**
 * @tc.name: FocusHubTestDisableFocus001
 * @tc.desc: Test disable functions Onfocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestDisableFocus001, TestSize.Level1)
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
     * @tc.steps2: call the function OnFocus with FocusType::NODE.
     * @tc.expected: The result is right.
     */
    focusHub->SetFocusType(FocusType::NODE);
    std::string result;
    auto onFocus = [&result]() { result = RESULT_SUCCESS_ONE; };
    focusHub->SetOnFocusCallback(onFocus);
    focusHub->currentFocus_ = true;
    EXPECT_NE(focusHub->GetOnFocusCallback(), nullptr);

    focusHub->OnFocus();
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);

    /**
     * @tc.steps3: clear the function.
     * @tc.expected: The result is nullptr.
     */
    focusHub->ClearOnFocusCallback();
    EXPECT_EQ(focusHub->GetOnFocusCallback(), nullptr);

    /**
     * @tc.steps3: set the function again.
     * @tc.expected: The result is right.
     */
    auto onFocus2 = [&result]() { result = RESULT_SUCCESS_TWO; };
    focusHub->SetOnFocusCallback(onFocus2);
    focusHub->currentFocus_ = true;
    EXPECT_NE(focusHub->GetOnFocusCallback(), nullptr);

    focusHub->OnFocus();
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: FocusHubTestDisableBlur001
 * @tc.desc: Test disable functions OnBlur.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestDisableBlur001, TestSize.Level1)
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
     * @tc.expected: The result is right.
     */
    focusHub->SetFocusType(FocusType::NODE);
    std::string result;
    auto onBlur = [&result]() { result = RESULT_SUCCESS_ONE; };
    focusHub->SetOnBlurCallback(onBlur);
    EXPECT_NE(focusHub->GetOnBlurCallback(), nullptr);

    focusHub->OnBlur();
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);

    /**
     * @tc.steps3: clear the function OnBlur.
     * @tc.expected: The result is nullptr.
     */
    focusHub->ClearOnBlurCallback();
    EXPECT_EQ(focusHub->GetOnBlurCallback(), nullptr);

    /**
     * @tc.steps3: set the function OnBlur again.
     * @tc.expected: The result is right.
     */
    auto onBlur2 = [&result]() { result = RESULT_SUCCESS_TWO; };
    focusHub->SetOnBlurCallback(onBlur2);
    EXPECT_NE(focusHub->GetOnBlurCallback(), nullptr);

    focusHub->OnBlur();
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: FocusHubTestDisableKey001
 * @tc.desc: Test disable functions OnKey.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestDisableKey001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->host_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps2: call the function OnKey with FocusType::NODE.
     * @tc.expected: The result is right.
     */
    focusHub->SetFocusType(FocusType::NODE);
    std::string result;
    auto onKey = [&result](KeyEventInfo& info) -> bool {
        result = RESULT_SUCCESS_ONE;
        return false;
    };
    focusHub->SetOnKeyCallback(onKey);
    EXPECT_NE(focusHub->GetOnKeyCallback(), nullptr);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UP;
    focusHub->HandleEvent(keyEvent);
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);

    /**
     * @tc.steps3: clear the function OnKey.
     * @tc.expected: The result is nullptr.
     */
    focusHub->ClearOnKeyCallback();
    EXPECT_EQ(focusHub->GetOnKeyCallback(), nullptr);

    /**
     * @tc.steps4: set the function OnKey again.
     * @tc.expected: The result is right.
     */
    auto onKey2 = [&result](KeyEventInfo& info) -> bool {
        result = RESULT_SUCCESS_TWO;
        return false;
    };
    focusHub->SetOnKeyCallback(onKey2);
    EXPECT_NE(focusHub->GetOnKeyCallback(), nullptr);

    focusHub->HandleEvent(keyEvent);
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: FocusHubTestNg0030
 * @tc.desc: Test the function GoToNextFocusLinear.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0030, TestSize.Level1)
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    EXPECT_FALSE(focusHub->GoToNextFocusLinear(FocusStep::NONE));
}

/**
 * @tc.name: FocusHubTestNg0031
 * @tc.desc: Test the function IsNeedPaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0031, TestSize.Level1)
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->IsNeedPaintFocusState();
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    focusHub->IsNeedPaintFocusState();
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
}

/**
 * @tc.name: FocusHubTestNg0032
 * @tc.desc: Test the function PaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0032, TestSize.Level1)
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    EXPECT_FALSE(focusHub->PaintFocusState(true));
    EXPECT_FALSE(focusHub->PaintFocusState(false));
}

/**
 * @tc.name: FocusHubTestNg0033
 * @tc.desc: Test the function AcceptFocusOfSpecifyChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0033, TestSize.Level1)
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->focusType_ = FocusType::DISABLE;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB);
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->AcceptFocusOfSpecifyChild(FocusStep::SHIFT_TAB));
    EXPECT_FALSE(focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB));
}

/**
 * @tc.name: FocusHubTestNg0034
 * @tc.desc: Test the function ClearFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->onClearFocusStateCallback_ = []() {};
    focusHub->ClearFocusState(true);
    focusHub->ClearFocusState(false);
    EXPECT_NE(focusHub->focusStyleType_, FocusStyleType::NONE);
}

/**
 * @tc.name: FocusHubTestNg0035
 * @tc.desc: Test the function RequestFocusImmediately.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0035, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    context->SetIsFocusingByTab(true);
    focusHub->SetFocusType(FocusType::DISABLE);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->currentFocus_ = false;
    focusHub->onPreFocusCallback_ = []() {};
    EXPECT_FALSE(focusHub->RequestFocusImmediately());
    EXPECT_FALSE(focusHub->RequestFocusImmediately());
    context->SetIsFocusingByTab(false);
    focusHub->SetFocusType(FocusType::DISABLE);
    focusHub->currentFocus_ = true;
    EXPECT_TRUE(focusHub->RequestFocusImmediately());
}

/**
 * @tc.name: FocusHubTestNg0036
 * @tc.desc: Test the function OnFocusScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0036, TestSize.Level1)
{
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->OnFocusScope();
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg0037
 * @tc.desc: Test the function IsFocusableScopeByTab.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0037, TestSize.Level1)
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
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    EXPECT_TRUE(focusHub->IsFocusableScopeByTab());
}

/**
 * @tc.name: FocusHubTestNg0038
 * @tc.desc: Test the function IsCurrentFocusWholePath.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    EXPECT_FALSE(focusHub->IsCurrentFocusWholePath());
    focusHub->currentFocus_ = true;
    EXPECT_FALSE(focusHub->IsCurrentFocusWholePath());
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_TRUE(focusHub->IsCurrentFocusWholePath());
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->IsCurrentFocusWholePath());
}

/**
 * @tc.name: FocusHubTestNg0039
 * @tc.desc: Test the function DumpFocusTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    int32_t depth = 1;
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->DumpFocusTree(depth);
}

/**
 * @tc.name: FocusHubTestNg0040
 * @tc.desc: Test the function AcceptFocusOfLastFocus and AcceptFocusByRectOfLastFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    RectF childRect;
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->AcceptFocusOfLastFocus());
    EXPECT_FALSE(focusHub->AcceptFocusByRectOfLastFocus(childRect));
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_FALSE(focusHub->AcceptFocusOfLastFocus());
    EXPECT_FALSE(focusHub->AcceptFocusByRectOfLastFocus(childRect));
    focusHub->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub->AcceptFocusOfLastFocus());
    EXPECT_FALSE(focusHub->AcceptFocusByRectOfLastFocus(childRect));
}

/**
 * @tc.name: FocusHubTestNg0041
 * @tc.desc: Test the function SetShow, SetEnabled, SetEnabledNode and SetEnabledScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    auto frameNode_test = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_COMPONENT_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    frameNode->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    AceType::DynamicCast<FrameNodeOnTree>(frameNode->GetParent())
        ->GetLayoutProperty()
        ->UpdateVisibility(VisibleType::INVISIBLE);
    focusHub->IsShow();
}

/**
 * @tc.name: FocusHubTestNg0042
 * @tc.desc: Test the function OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0042, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    focusHub->SetOnClickCallback([](GestureEvent&) { return; });
    EXPECT_TRUE(focusHub->OnClick(keyEvent));
}

/**
 * @tc.name: HasBackwardFocusMovementInChildren001
 * @tc.desc: Test the function HasBackwardFocusMovementInChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasBackwardFocusMovementInChildren001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    ASSERT_FALSE(focusHub->HasBackwardFocusMovementInChildren());
}

/**
 * @tc.name: HasForwardFocusMovementInChildren001
 * @tc.desc: Test the function HasForwardFocusMovementInChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasForwardFocusMovementInChildren001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    ASSERT_FALSE(focusHub->HasForwardFocusMovementInChildren());
}

/**
 * @tc.name: ClearFocusMovementFlagsInChildren001
 * @tc.desc: Test the function ClearFocusMovementFlagsInChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, ClearFocusMovementFlagsInChildren001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    ASSERT_FALSE(focusHub->HasBackwardFocusMovement());
}

/**
 * @tc.name: SetLastWeakFocusToPreviousInFocusView001
 * @tc.desc: Test the function SetLastWeakFocusToPreviousInFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetLastWeakFocusToPreviousInFocusView001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    focusHub->SetLastWeakFocusToPreviousInFocusView();
    ASSERT_FALSE(focusHub->lastWeakFocusNode_.Upgrade());
}

/**
 * @tc.name: FocusHubFlushChildrenFocusHubTest001
 * @tc.desc: Test the function SetTabStop and IsTabStop
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubSetTabStopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_EQ(focusHub->IsTabStop(), false);
    focusHub->SetTabStop(true);
    EXPECT_EQ(focusHub->IsTabStop(), true);
    focusHub->SetTabStop(false);
    EXPECT_EQ(focusHub->IsTabStop(), false);
}

/**
 * @tc.name: FocusHubRequestNextFocusOfKeyEnterTest001
 * @tc.desc: Test the function RequestNextFocusOfKeyEnter
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRequestNextFocusOfKeyEnterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEnter(), false);
    focusHub->SetTabStop(true);
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEnter(), false);
    focusHub->SetTabStop(true);
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEnter(), true);
}

/**
 * @tc.name: FocusHubRequestNextFocusOfKeyEscTest001
 * @tc.desc: Test the function RequestNextFocusOfKeyEsc
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubRequestNextFocusOfKeyEscTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode
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

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEsc(), false);

    focusHub->SetTabStop(true);
    EXPECT_EQ(focusHub->RequestNextFocusOfKeyEsc(), false);

    focusHub->SetTabStop(false);
    RefPtr<EventHub> eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(child);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub1)));
    focusHub1->SetTabStop(true);
    EXPECT_EQ(focusHub1->RequestNextFocusOfKeyEsc(), false);
}

/**
 * @tc.name: FocusHubOnFocusAxisEvent001
 * @tc.desc: Test the function OnFocusKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubOnFocusAxisEvent001, TestSize.Level1)
{
    /**
     * @tc.steps1: create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps2: create eventHub and focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    FocusAxisEvent focusAxisEvent;
    focusAxisEvent.absXValue = 0.5;
    focusAxisEvent.absYValue = 0.5;
    focusAxisEvent.absZValue = 0.5;
    focusAxisEvent.absRzValue = 0.5;
    focusAxisEvent.absHat0XValue = 1;
    focusAxisEvent.absHat0YValue = 1;
    focusAxisEvent.absBrakeValue = 0.5;
    focusAxisEvent.absGasValue = 0.5;
    focusAxisEvent.sourceType = SourceType::MOUSE;
    focusAxisEvent.sourceTool = SourceTool::JOYSTICK;
    focusAxisEvent.deviceId = 10;
    std::chrono::microseconds microseconds(GetSysTimestamp());
    TimeStamp time(microseconds);
    focusAxisEvent.time = time;
    focusAxisEvent.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);

    /**
     * @tc.steps3: call the function OnKeyEvent with FocusType::NODE.
     * @tc.expected: The return value of OnKeyEvent is true.
     */
    focusHub->SetFocusType(FocusType::NODE);
    focusHub->currentFocus_ = true;
    FocusAxisEventInfo axisEventInfo({});
    auto onFocusAxisEventCallback = [&axisEventInfo](FocusAxisEventInfo& eventInfo) {
        eventInfo.SetStopPropagation(true);
        axisEventInfo = eventInfo;
    };
    focusHub->SetOnFocusAxisCallback(std::move(onFocusAxisEventCallback));
    EXPECT_TRUE(focusHub->HandleEvent(focusAxisEvent));
    EXPECT_EQ(axisEventInfo.GetAbsXValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsYValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsZValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsRzValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsHat0XValue(), 1);
    EXPECT_EQ(axisEventInfo.GetAbsHat0YValue(), 1);
    EXPECT_EQ(axisEventInfo.GetAbsBrakeValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetAbsGasValue(), 0.5);
    EXPECT_EQ(axisEventInfo.GetSourceDevice(), SourceType::MOUSE);
    EXPECT_EQ(axisEventInfo.GetSourceTool(), SourceTool::JOYSTICK);
    EXPECT_EQ(axisEventInfo.GetDeviceId(), 10);
    EXPECT_EQ(axisEventInfo.GetTimeStamp().time_since_epoch().count(), time.time_since_epoch().count());
    EXPECT_EQ(axisEventInfo.GetPressedKeyCodes().size(), 1);
    EXPECT_EQ(axisEventInfo.IsStopPropagation(), true);
}

/**
 * @tc.name: FocusHubHandleFocusNavigation001
 * @tc.desc: FocusNavigation
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubHandleFocusNavigation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    focusHub->lastWeakFocusNode_ = nullptr;
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step3. Expect the result is false.
     */
    auto result = focusHub->HandleFocusNavigation(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasCustomKeyEventDispatch001
 * @tc.desc: Test the function when event.event.eventType is UIInputEventType::KEY
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasCustomKeyEventDispatch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.isPreIme = true;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Expect the result is false.
     */
    auto result = focusHub->HasCustomKeyEventDispatch(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HasCustomKeyEventDispatch002
 * @tc.desc: Test the function when event.event.eventType is not UIInputEventType::KEY, keyEvent.isPreIme is false and
 * GetOnKeyEventDispatchCallback is not null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasCustomKeyEventDispatch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.isPreIme = false;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return true; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is true.
     */
    auto result = focusHub->HasCustomKeyEventDispatch(focusEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HasCustomKeyEventDispatch003
 * @tc.desc: Test the function when event.event.eventType is not UIInputEventType::KEY, keyEvent.isPreIme is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasCustomKeyEventDispatch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.isPreIme = true;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return true; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is false.
     */
    auto result = focusHub->HasCustomKeyEventDispatch(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleCustomEventDispatch001
 * @tc.desc: Test the function when onKeyEventDispatchCallback is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HandleCustomEventDispatch001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return true; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is true.
     */
    auto result = focusHub->HandleCustomEventDispatch(focusEvent);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleCustomEventDispatch002
 * @tc.desc: Test the function when onKeyEventDispatchCallback is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HandleCustomEventDispatch002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusEvent.
     */
    KeyEvent keyEvent;
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Set the SetOnKeyEventDispatchCallback.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool { return false; };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.steps: step4. Expect the result is true.
     */
    auto result = focusHub->HandleCustomEventDispatch(focusEvent);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetKeyProcessingMode001
 * @tc.desc: GetKeyProcessingMode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetKeyProcessingMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Expect the result is static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION).
     */
    auto result = focusHub->GetKeyProcessingMode();
    EXPECT_EQ(result, static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION));
}

/**
 * @tc.name: GetKeyProcessingMode002
 * @tc.desc: GetKeyProcessingMode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetKeyProcessingMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step1. Set keyProcessingMode_.
     */
    ASSERT_NE(focusHub->GetFrameNode(), nullptr);
    ASSERT_NE(focusHub->GetFrameNode()->GetContextRefPtr(), nullptr);
    ASSERT_NE(focusHub->GetFrameNode()->GetContextRefPtr()->GetOrCreateFocusManager(), nullptr);
    focusHub->GetFrameNode()->GetContextRefPtr()->GetOrCreateFocusManager()->keyProcessingMode_ =
        KeyProcessingMode::ANCESTOR_EVENT;

    /**
     * @tc.steps: step3. Expect the result is static_cast<int32_t>(KeyProcessingMode::ANCESTOR_EVENT).
     */
    auto result = focusHub->GetKeyProcessingMode();
    EXPECT_EQ(result, static_cast<int32_t>(KeyProcessingMode::ANCESTOR_EVENT));
}

/**
 * @tc.name: FocusHubPaintColorTest001
 * @tc.desc: Test the function GetPaintColorFromBox
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubPaintColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    Color expectPaintColor;
    Color resultPaintColor;

    /**
     * @tc.steps: step2. Test without anything.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = context->GetTheme<AppTheme>();
    appTheme->focusColor_ = Color::GREEN;
    expectPaintColor = Color::GREEN;
    focusHub->GetPaintColorFromBox(resultPaintColor);
    EXPECT_EQ(expectPaintColor, resultPaintColor);

    /**
     * @tc.steps: step3. Test with custom paintColor.
     */
    auto testFocusPaintParams = std::make_unique<FocusPaintParam>();
    testFocusPaintParams->paintColor = Color::BLACK;
    expectPaintColor = Color::BLACK;
    focusHub->focusPaintParamsPtr_ = std::move(testFocusPaintParams);
    focusHub->GetPaintColorFromBox(resultPaintColor);
    EXPECT_EQ(expectPaintColor, resultPaintColor);

    /**
     * @tc.steps: step4. Test with custom paintColor and focusbox.
     */
    FocusBoxStyle style = { Color::RED };
    expectPaintColor = Color::RED;
    focusHub->GetFocusBox().SetStyle(style);
    focusHub->GetPaintColorFromBox(resultPaintColor);
    EXPECT_EQ(expectPaintColor, resultPaintColor);
}

/**
 * @tc.name: FocusHubIsLeafFocusScopeTest001
 * @tc.desc: Test IsLeafFocusScope returns true when focusDepend_ is SELF
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubIsLeafFocusScopeTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a page node and add a button child node.
     */
    auto pageNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::PAGE_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto button1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    button1->GetOrCreateFocusHub();
    pageNode->AddChild(button1);

    /**
     * @tc.steps2: Create EventHub and FocusHub for the page node.
     */
    RefPtr<EventHub> pageEventHub = AceType::MakeRefPtr<EventHub>();
    pageEventHub->AttachHost(pageNode);
    auto pageFocusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(pageEventHub)));

    /**
     * @tc.steps3: Set page visibility to INVISIBLE, set lastWeakFocusNode_ and focusDepend_ to SELF.
     * @tc.expected: IsLeafFocusScope returns true.
     */
    pageNode->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    RefPtr<FocusHub> childFocusHub = button1->GetFocusHub();
    ASSERT_NE(childFocusHub, nullptr);
    pageFocusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(childFocusHub));
    pageFocusHub->focusDepend_ = FocusDependence::SELF;
    bool isLeaf = pageFocusHub->IsLeafFocusScope();
    EXPECT_TRUE(isLeaf);
    EXPECT_EQ(pageFocusHub->lastWeakFocusNode_.Upgrade(), childFocusHub);

    /**
     * @tc.steps4: Set page visibility to VISIBLE, and simulate key event delivery.
     * @tc.expected: Key event is successfully handled.
     */
    pageNode->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;
    childFocusHub->SetOnKeyEventInternal([](const KeyEvent&) { return true; });
    childFocusHub->currentFocus_ = true;
    pageFocusHub->focusType_ = FocusType::SCOPE;
    pageFocusHub->currentFocus_ = true;
    EXPECT_TRUE(pageFocusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubUpdateFocusViewTest001
 * @tc.desc: Test UpdateFocusView when the current node is not on the main tree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubUpdateFocusViewTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode with onMainTree_ set to false.
     */
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, pattern);
    frameNode->onMainTree_ = false;

    /**
     * @tc.steps2: Create EventHub and FocusHub, and set currentFocus_ to true.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps3: Call UpdateFocusView and expect it to return true even if not on main tree.
     * @tc.expected: UpdateFocusView returns true.
     */
    EXPECT_TRUE(focusHub->UpdateFocusView());
}

/**
 * @tc.name: FocusEventHandlerOnFocusEventTest001
 * @tc.desc: Test that OnFocusEvent returns false when the node is not focused.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusEventHandlerOnFocusEventTest001, TestSize.Level1)
{
     /**
     * @tc.steps1: Create a FrameNode and attach it to an EventHub.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps2: Create a FocusHub with no current focus.
     */
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

     /**
     * @tc.steps3: Simulate a SPACE key event and wrap it in a FocusEvent.
     */
    KeyEvent keyEvent;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.action = KeyAction::DOWN;
    FocusEvent focusEvent(keyEvent);

     /**
     * @tc.steps4: Call OnFocusEvent when the node is not focused.
     * @tc.expected: The return value is false, indicating no handling.
     */
    EXPECT_FALSE(focusHub->OnFocusEvent(focusEvent));
}

/**
 * @tc.name: FocusHubOnClickOnlyFocusActiveTest001
 * @tc.desc: Test that onClick event only triggers when in FocusActive state.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubOnClickOnlyFocusActiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a column node and a button child node.
     */
    auto column = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto button1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub1->AttachHost(button1);
    column->AddChild(button1);

    /**
     * @tc.steps2: Configure the button node with focus properties and onClick callback.
     */
    auto button1Hub = button1->GetOrCreateFocusHub();
    ASSERT_NE(button1Hub, nullptr);
    button1Hub->SetFocusType(FocusType::NODE);
    button1Hub->focusable_ = true;
    button1Hub->currentFocus_ = true;
    bool clicked = false;
    button1Hub->SetOnClickCallback([&clicked](GestureEvent&) { clicked = true; });

    /**
     * @tc.steps3: Simulate a SPACE key down event.
     */
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.steps4: Set up focusManager and themeManager, disable focusHandleClick.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = pipeline->GetTheme<AppTheme>();
    appTheme->focusHandleClick_ = false;
    EXPECT_FALSE(appTheme->NeedFocusHandleClick());

    /**
     * @tc.steps5: Set focus state to inactive, expect onClick not triggered.
     * @tc.expected: HandleKeyEvent returns false, clicked is false.
     */
    focusManager->SetIsFocusActive(false);
    EXPECT_FALSE(pipeline->GetIsFocusActive());
    clicked = false;
    EXPECT_FALSE(button1Hub->HandleKeyEvent(keyEvent, FocusIntension::SPACE));
    EXPECT_FALSE(clicked);

    /**
     * @tc.steps6: Set focus state to active, expect onClick triggered.
     * @tc.expected: HandleKeyEvent returns true, clicked is true.
     */
    focusManager->SetIsFocusActive(true);
    EXPECT_TRUE(pipeline->GetIsFocusActive());
    clicked = false;
    EXPECT_TRUE(button1Hub->HandleKeyEvent(keyEvent, FocusIntension::SPACE));
    EXPECT_TRUE(clicked);
}

/**
 * @tc.name: FocusHubFixRefocusTest001
 * @tc.desc: Test refocus logic and ensure Enter key triggers next focus with correct priority.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubFixRefocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a frame node and attach it to an EventHub and FocusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Set focusHub to SCOPE type, enable tab stop, set focusDepend_ to SELF, isSwitchByEnter_ to true.
     * @tc.expected: IsLeafFocusScope returns false, focusDepend_ updated to AUTO.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->SetTabStop(true);
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->isSwitchByEnter_ = true;
    EXPECT_FALSE(focusHub->IsLeafFocusScope());
    EXPECT_EQ(focusHub->focusDepend_, FocusDependence::AUTO);

    /**
     * @tc.steps3: Add a focusable child node to the frame, and set focusHub as currently focused.
     */
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    focusHub->currentFocus_ = true;

    /**
     * @tc.steps4: Request focus switch via Enter key.
     * @tc.expected: Child node gains focus successfully.
     */
    EXPECT_TRUE(focusHub->RequestNextFocusOfKeyEnter());
    EXPECT_TRUE(child->GetFocusHub()->IsCurrentFocus());

    /**
     * @tc.steps5: Call OnFocusScope again and verify no redundant focus callback is triggered.
     * @tc.expected: Focus callback count remains 0.
     */
    int32_t callbackCount = 0;
    focusHub->SetOnFocusCallback([&callbackCount]() { callbackCount++; });
    focusHub->OnFocusScope(true);
    EXPECT_EQ(callbackCount, 0);
}

/**
 * @tc.name: FocusHubCalculateRect001
 * @tc.desc: Test that CalculateRect does not return false when childHub is not null.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubCalculateRect001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and attach it to EventHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps2: Create a parent FocusHub and a child FocusHub sharing the same EventHub.
     */
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    RefPtr<FocusHub> childHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps3: Call CalculateRect with a valid childHub.
     * @tc.expected: Function returns true, indicating rect calculation continues instead of returning false on check.
     */
    RectF rect;
    EXPECT_TRUE(focusHub->CalculateRect(childHub, rect));
}

/**
 * @tc.name: FocusHubPaintFocusStateWithMarginTest001
 * @tc.desc: Test that margin property in focusBox style takes effect when focus style is CUSTOM_REGION.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubPaintFocusStateWithMarginTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and bind it to EventHub and FocusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Set up pipeline context, theme manager, and get AppTheme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    EXPECT_NE(focusManager, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto appTheme = pipeline->GetTheme<AppTheme>();

    /**
     * @tc.steps3: Set focus style to CUSTOM_REGION and assign boxStyle with margin.
     */
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    focusHub->currentFocus_ = true;

    FocusBoxStyle boxStyle;
    boxStyle.margin = Dimension(20.0_vp);
    boxStyle.strokeColor = Color::RED;
    boxStyle.strokeWidth = Dimension(5.0_vp);
    focusHub->box_.paintStyle_ = boxStyle;

    /**
     * @tc.steps4: Activate focus and call PaintInnerFocusState.
     * @tc.expected: Function returns true, indicating margin takes effect successfully.
     */
    focusManager->SetIsFocusActive(true);
    RoundRect rect;
    bool result = focusHub->PaintInnerFocusState(rect, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubClearFocusStateTest001
 * @tc.desc: Test that ClearFocusState properly triggers or skips callback depending on input flags.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubClearFocusStateTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create a FrameNode and attach EventHub and FocusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Register a focus clear callback to validate invocation.
     */
    bool callbackCalled = false;
    focusHub->SetOnClearFocusStateInternal([&callbackCalled]() { callbackCalled = true; });

    /**
     * @tc.steps3: Test ClearFocusState(true, true), should trigger callback.
     * @tc.expected: callbackCalled is true.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(true, true);
    EXPECT_TRUE(callbackCalled);

    /**
     * @tc.steps4: Test ClearFocusState(true, false), should skip callback.
     * @tc.expected: callbackCalled is false.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(true, false);
    EXPECT_FALSE(callbackCalled);

    /**
     * @tc.steps5: Test ClearFocusState(false, true), should trigger callback.
     * @tc.expected: callbackCalled is true.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(false, true);
    EXPECT_TRUE(callbackCalled);

    /**
     * @tc.steps6: Test ClearFocusState(false, false), should skip callback.
     * @tc.expected: callbackCalled is false.
     */
    callbackCalled = false;
    focusHub->ClearFocusState(false, false);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: FocusEventGetFocusIntensionTest001
 * @tc.desc: Test that various key combinations correctly map to FocusIntension values.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusEventGetFocusIntensionTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Prepare a key event with type KEY, action DOWN, not pre-IME.
     */
    KeyEvent keyEvent;
    keyEvent.eventType = UIInputEventType::KEY;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.isPreIme = false;
    NonPointerEvent& event = keyEvent;

    /**
     * @tc.steps2: Test plain UP key without modifiers.
     * @tc.expected: FocusIntension::UP
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.pressedCodes.clear();
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::UP);

    /**
     * @tc.steps3: Test UP key with Shift modifier.
     * @tc.expected: FocusIntension::UP
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::UP);

    /**
     * @tc.steps4: Test DOWN key with Shift modifier.
     * @tc.expected: FocusIntension::DOWN
     */
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::DOWN);

    /**
     * @tc.steps5: Test LEFT key with Shift modifier.
     * @tc.expected: FocusIntension::LEFT
     */
    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::LEFT);

    /**
     * @tc.steps6: Test RIGHT key with Shift modifier.
     * @tc.expected: FocusIntension::RIGHT
     */
    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT };
    EXPECT_EQ(FocusEvent::GetFocusIntension(event), FocusIntension::RIGHT);

    /**
     * @tc.steps7: Test Shift + Tab key combination.
     * @tc.expected: FocusIntension::SHIFT_TAB
     */
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_TAB };
    EXPECT_EQ(FocusEvent::GetFocusIntension(keyEvent), FocusIntension::SHIFT_TAB);
}
} // namespace OHOS::Ace::NG 
