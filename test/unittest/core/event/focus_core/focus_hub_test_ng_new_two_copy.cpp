/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: FocusHubTestNg078
 * @tc.desc: Test the function CalculatePosition.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0078, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    frameNode1->geometryNode_ = nullptr;
    auto res = focusHub->CalculatePosition();
    EXCEPT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg079
 * @tc.desc: Test the function TryRequestFocus.
 * @tc.type: FUNC obsolete
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0079, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    auto res = focusHub->TryRequestFocus(focusHub1, RectF(), FocusStep::LEFT);
    EXCEPT_TRUE(res);
}

/**
 * @tc.name: FocusHubTestNg080
 * @tc.desc: Test the function GoToNextFocusLinear.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0080, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();

    auto frameNode2 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode2->GetOrCreateFocusHub();
    auto focusHub2 = frameNode2->GetFocusHub();

    auto frameNode3 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode3->GetOrCreateFocusHub();
    auto focusHub3 = frameNode3->GetFocusHub();

    auto frameNode4 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode4->GetOrCreateFocusHub();
    auto focusHub4 = frameNode4->GetFocusHub();

    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub4));
    frameNode->children_.push_back(frameNode1);
    frameNode->children_.push_back(frameNode2);
    frameNode->children_.push_back(frameNode3);
    frameNode->children_.push_back(frameNode4);

    focusHub3->focusable_ = false;

    auto res = focusHub->GoToNextFocusLinear(FocusStep::SHIFT_TAB, RectF());
    EXCEPT_TRUE(res);
    focusHub2->focusable_ = false;
    res = focusHub->GoToNextFocusLinear(FocusStep::SHIFT_TAB, RectF());
    EXCEPT_TRUE(res);
    focusHub1->focusable_ = false;
    res = focusHub->GoToNextFocusLinear(FocusStep::SHIFT_TAB, RectF());
    EXCEPT_FALSE(res);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim<FocusHub>(nullptr);
    focusHub4->focusable_ = false;
    res = focusHub->GoToNextFocusLinear(FocusStep::TAB, RectF());
    EXCEPT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg081
 * @tc.desc: Test the function SwitchFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0081, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();

    auto frameNode2 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode2->GetOrCreateFocusHub();
    auto focusHub2 = frameNode2->GetFocusHub();

    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode->children_.push_back(frameNode1);
    frameNode->children_.push_back(frameNode2);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim<FocusHub>(nullptr);
    focusHub->SwitchFocus(focusHub2);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    focusHub1->currentFocus_ = true;
    focusHub->SwitchFocus(focusHub2);
    EXCEPT_FALSE(focusHub1->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg083
 * @tc.desc: Test the function FocusToHeadOrTailChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0083, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto res = focusHub->FocusToHeadOrTailChild(true);
    EXCEPT_TRUE(res);
}

/**
 * @tc.name: FocusHubTestNg0084
 * @tc.desc: Test the function OnKeyEventScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0084, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<EventHub> eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    eventHub1->AttachHost(frameNode1);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub1)));
    KeyEvent keyEvent;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    auto pipeline = PipelineContext::GetCurrentContext();
    focusHub->currentFocus_ = false;
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    pipeline->eventManager_->isTabJustTriggerOnKeyEvent_ = true;
    focusHub->currentFocus_ = true;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::TV_CONTROL_UP;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::TV_CONTROL_DOWN;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::TV_CONTROL_LEFT;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::TV_CONTROL_RIGHT;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_MOVE_HOME;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_MOVE_END;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.code = KeyCode::KEY_FOCUS;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0091
 * @tc.desc: Test the function FocusToHeadOrTailChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0091, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);
    EXCEPT_TRUE(focusHub->IsFocusableNode());
    EXCEPT_TRUE(focusHub->IsFocusableScope());
    focusHub->focusDepend_ = FocusDependence::AUTO;
    EXPECT_TRUE(focusHub->FocusToHeadOrTailChild(true));
    focusHub->focusDepend_ = FocusDependence::SELF;
    EXPECT_TRUE(focusHub->FocusToHeadOrTailChild(false));
    focusHub->focusDepend_ = FocusDependence::CHILD;
    EXPECT_TRUE(focusHub->FocusToHeadOrTailChild(false));
}

/**
 * @tc.name: FocusHubTestNg0093
 * @tc.desc: Test the function IsNeedPaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0093, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);
    EXCEPT_TRUE(focusHub->IsFocusableNode());
    focusHub->currentFocus_ = true;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    EXPECT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
    focusHub->focusDepend_ = FocusDependence::SELF;
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
}

/**
 * @tc.name: FocusHubTestNg0094
 * @tc.desc: Test the function HandleFocusByTabIndex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0094, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    frameNode->children_.push_back(frameNode1);
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub1->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub1->focusable_ = true;
    focusHub1->parentFocusable_ = true;
    focusHub1->focusType_ = FocusType::NODE;
    focusHub1->focusCallbackEvents_->tabIndex_ = 1;
    focusHub1->currentFocus_ = true;
    KeyEvent keyEvent;
    TabIndexNodeList tabIndexNodes;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->eventManager_->isTabJustTriggerOnKeyEvent_ = false;
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    context->isFocusingByTab_ = false;
    EXPECT_TRUE(focusHub->HandleFocusByTabIndex(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0096
 * @tc.desc: Test the function OnFocusScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0096, TestSize.Level1)
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
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->OnFocusScope(true);
    frameNode->Clean(false, false);
    focusNodes.clear();
    EXPECT_TRUE(focusNodes.empty());
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->OnFocusScope(true);
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->OnFocusScope(true);
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg0097
 * @tc.desc: Test the function RequestFocusImmediatelyById.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0097, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("123", 123,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    frameNode1->propInspectorId_ = "123";
    auto frameNode2 = FrameNodeOnTree::CreateFrameNode("frameNode", 102,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode2->GetOrCreateFocusHub();
    auto focusHub2 = frameNode2->GetFocusHub();
    frameNode->children_.push_back(frameNode2);
    frameNode->children_.push_back(frameNode1);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub1->parentFocusable_ = false;
    auto res = focusHub->RequestFocusImmediatelyById("123");
    EXCEPT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg0098
 * @tc.desc: Test functions OnBlurScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0098, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    focusHub->OnBlurScope();
    EXPECT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusHubTestNg0100
 * @tc.desc: Test the function IsImplicitFocusableScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0100, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->SetEnabled(true);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Set focusHub to scope type.
     * @tc.expected: The default value of focusable_ is false.
     */
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->IsImplicitFocusableScope());

    /**
     * @tc.steps3: Set focusable_ to true implicitly.
     * @tc.expected: The value of focusable_ is true.
     */
    focusHub->SetFocusable(true, false);
    EXPECT_TRUE(focusHub->IsImplicitFocusableScope());
}

/**
 * @tc.name: LostFocusToViewRoot001
 * @tc.desc: Test the function LostFocusToViewRoot.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostFocusToViewRoot001, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
     /**
     * @tc.Calling LostFocusToViewRoot to increase coverage
     */
    focusHub->LostFocusToViewRoot();
    EXCEPT_TRUE(focusHub->currentFocus_ == false);
}

/*
 * @tc.name: SetEnabled01
 * @tc.desc: Test the function SetEnabled.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetEnabled001, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    focusHub->currentFocus_ = true;

    focusHub->SetEnabled(false);
    EXCEPT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg0101
 * @tc.desc: Test the function IsSyncRequestFocusable.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0101, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    eventHub->SetEnabled(false);

    /**
     * @tc.steps2: call the function IsSyncRequestFocusable with FocusType::NODE
     * @tc.expected: The return value of IsSyncRequestFocusable is false.
     */
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_FALSE(focusHub->IsSyncRequestFocusable());

    /**
     * @tc.steps3: call the function IsSyncRequestFocusable with FocusType::SCOPE
     * @tc.expected: The return value of IsSyncRequestFocusable is false.
     */
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_FALSE(focusHub->IsSyncRequestFocusable());

    /**
     * @tc.steps4: call the function IsSyncRequestFocusable with FocusType::DISABLE
     * @tc.expected: The return value of IsSyncRequestFocusable is false.
     */
    focusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_FALSE(focusHub->IsSyncRequestFocusable());
}

/**
 * @tc.name: FocusHubTestNg0102
 * @tc.desc: Test the function ScrollByOffsetToParent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0102, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 102,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto textFieldNode = FrameNodeOnTree::CreateFrameNode("frameNode", 103,
        AceType::MakeRefPtr<TextFieldPattern>());
    textFieldNode->GetOrCreateFocusHub();
    auto textFieldFocusHub = textFieldNode->GetFocusHub();
    ASSERT_NE(textFieldNode, nullptr);
    EXCEPT_FALSE(focusHub->ScrollByOffsetToParent(textFieldNode));

    auto listNode = FrameNodeOnTree::CreateFrameNode("frameNode", 104,
        AceType::MakeRefPtr<ListPattern>());
    listNode->GetOrCreateFocusHub();
    auto listFocusHub = listNode->GetFocusHub();
    EXPECT_NE(listFocusHub, nullptr);
    EXCEPT_FALSE(focusHub->ScrollByOffsetToParent(listNode));
}


/**
 * @tc.name: FocusHubTestNg0103
 * @tc.desc: Test the function AcceptFocusOfPriorityChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0103, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, 105,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto child = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        106, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto child2 = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        107, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);

    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);
    parentFocusHub->SetFocusScopeId("scope1", false);

    auto child2FocusHub = child2->GetOrCreateFocusHub();
    ASSERT_NE(child2FocusHub, nullptr);
    child2FocusHub->SetFocusScopePriority("scope1", 2000);
    EXPECT_TRUE(parentFocusHub->AcceptFocusOfPriorityChild());
    EXPECT_EQ(parentFocusHub->lastWeakFocusNode_.Upgrade(), child2FocusHub);
}

/**
 * @tc.name: FocusHubTestNg0104
 * @tc.desc: Test the function AcceptFocusOfPriorityChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0104, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, 108,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto child = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        109, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto child2 = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        110, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);

    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);
    parentFocusHub->SetFocusScopeId("scope2", true);

    auto child2FocusHub = child2->GetOrCreateFocusHub();
    ASSERT_NE(child2FocusHub, nullptr);
    child2FocusHub->SetFocusScopePriority("scope2", 2000);
    EXPECT_TRUE(parentFocusHub->AcceptFocusOfPriorityChild());
    EXPECT_EQ(parentFocusHub->lastWeakFocusNode_.Upgrade(), child2FocusHub);

    auto childFocusHub = child->GetOrCreateFocusHub();
    ASSERT_NE(childFocusHub, nullptr);
    childFocusHub->SetFocusScopePriority("scope2", 3000);
    EXPECT_TRUE(parentFocusHub->AcceptFocusOfPriorityChild());
    EXPECT_EQ(parentFocusHub->lastWeakFocusNode_.Upgrade(), childFocusHub);
}

/**
 * @tc.name: FocusHubTestNg0105
 * @tc.desc: Test the function RequestFocusByPriorityInScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0105, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, 111,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto child = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        112, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto child2 = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        113, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);

    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);
    parentFocusHub->SetFocusScopeId("scope3", false);

    auto child2FocusHub = child2->GetOrCreateFocusHub();
    ASSERT_NE(child2FocusHub, nullptr);
    child2FocusHub->SetFocusScopePriority("scope3", 2000);
    EXPECT_TRUE(parentFocusHub->RequestFocusByPriorityInScope());
    EXPECT_TRUE(child2FocusHub->IsCurrentFocus());
}

/**
 * @tc.name: FocusHubTestNg0106
 * @tc.desc: Test the function RequestFocusByPriorityInScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0106, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, 114,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto child = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        115, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto child2 = FrameNodeOnTree::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        116, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);

    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);
    parentFocusHub->SetFocusScopeId("scope4", true);

    auto child2FocusHub = child2->GetOrCreateFocusHub();
    ASSERT_NE(child2FocusHub, nullptr);
    child2FocusHub->SetFocusScopePriority("scope4", 2000);
    EXPECT_TRUE(parentFocusHub->RequestFocusByPriorityInScope());
    EXPECT_TRUE(child2FocusHub->IsCurrentFocus());

    auto childFocusHub = child->GetOrCreateFocusHub();
    ASSERT_NE(childFocusHub, nullptr);
    childFocusHub->SetFocusScopePriority("scope4", 3000);
    EXPECT_TRUE(parentFocusHub->RequestFocusByPriorityInScope());
    EXPECT_TRUE(childFocusHub->IsCurrentFocus());
}

/**
 * @tc.name: FocusHubTestNg0107
 * @tc.desc: Test the function IsInFocusGroup.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0107, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode =
        FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, 117, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto child = FrameNodeOnTree::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 118, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto child2 = FrameNodeOnTree::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 119, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);

    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);
    parentFocusHub->SetFocusScopeId("scope5", true);

    auto child2FocusHub = child2->GetOrCreateFocusHub();
    ASSERT_NE(child2FocusHub, nullptr);
    child2FocusHub->SetFocusScopePriority("scope5", 2000);
    parentFocusHub->isFocusScope_ = true;
    EXPECT_TRUE(parentFocusHub->RequestFocusByPriorityInScope());
    parentFocusHub->isFocusScope_ = false;
    EXPECT_FALSE(parentFocusHub->RequestFocusByPriorityInScope());
    EXPECT_TRUE(child2FocusHub->IsCurrentFocus());

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
    pipeline->eventManager_->isTabJustTriggerOnKeyEvent_ = true;
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_TAB);
    EXPECT_FALSE(parentFocusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0108
 * @tc.desc: Test the function HasFocusedChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0108, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps2: call the function HasFocusedChild with true and FocusType::SCOPE
     */
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->HasFocusedChild();


    /**
     * @tc.steps3: call the function HasFocusedChild with true and FocusType::DISABLE
     * @tc.expected: The return value of HasFocusedChild is false.
     */
    focusHub->focusType_ = FocusType::DISABLE;
    EXCEPT_FALSE(focusHub->HasFocusedChild());

    /**
     * @tc.steps4: call the function HasFocusedChild with false and FocusType::DISABLE
     * @tc.expected: The return value of HasFocusedChild is false.
     */
    focusHub->currentFocus_ = false;
    focusHub->focusType_ = FocusType::DISABLE;
    EXCEPT_FALSE(focusHub->HasFocusedChild());


    /**
     * @tc.steps5: call the function HasFocusedChild with false and FocusType::SCOPE
     * @tc.expected: The return value of HasFocusedChild is false.
     */
    focusHub->focusType_ = FocusType::SCOPE;
    EXCEPT_FALSE(focusHub->HasFocusedChild());
}

/**
 * @tc.name: FocusHubTestNg0121
 * @tc.desc: Test the function onKeyEventDispatch.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0121, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());

    /**
     * @tc.steps: step2. Create FocusHub and set keyEvent.
     */
    child1->GetOrCreateFocusHub();
    frameNode->AddChild(child1);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->currentFocus_ = true;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.expected: The return value of  is false.
     * @tc.steps3: Default returns false if onKeyEventDispatch is not bound.
     */
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0122
 * @tc.desc: Test the function onKeyEventDispatch.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0122, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());

    /**
     * @tc.steps: step2. Create FocusHub and set keyEvent.
     */
    child1->GetOrCreateFocusHub();
    frameNode->AddChild(child1);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->currentFocus_ = true;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.expected: The return value of onKeyEventDispatch is true.
     * @tc.steps3: call the function onKeyEventDispatch with FocusType::SCOPE.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool {
        return true;
    };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0123
 * @tc.desc: Test the function onKeyEventDispatch.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0123, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());

    /**
     * @tc.steps: step2. Create FocusHub and set keyEvent.
     */
    child1->GetOrCreateFocusHub();
    frameNode->AddChild(child1);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetFocusType(FocusType::SCOPE);
    focusHub->currentFocus_ = true;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.expected: The return value of onKeyEventDispatch is false.
     * @tc.steps3: call the function onKeyEventDispatch with FocusType::SCOPE.
     */
    auto onKeyEventDispatchCallback = [](KeyEventInfo& info) -> bool {
        return false;
    };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0124
 * @tc.desc: Test the function dispatchKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0124, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());

    /**
     * @tc.steps: step2. Create FocusHub and set keyEvent.
     */
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child1);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetFocusType(FocusType::SCOPE);
    RefPtr<EventHub> childEventHub2 = AceType::MakeRefPtr<EventHub>();
    childEventHub2->AttachHost(child2);
    auto childFocusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(childEventHub2)));
    childFocusHub2->SetFocusType(FocusType::NODE);
    focusHub->currentFocus_ = true;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;

    /**
     * @tc.steps: step3. Binds onKeyEventDispatch callback, executes dipatchKeyEvent to dispatch keyevent to child2.
     */
    auto onKeyEventDispatchCallback = [&childFocusHub2, &keyEvent](KeyEventInfo& eventInfo) -> bool {
        childFocusHub2->currentFocus_ = true;
        return childFocusHub2->HandleEvent(keyEvent);
    };
    focusHub->SetOnKeyEventDispatchCallback(std::move(onKeyEventDispatchCallback));

    /**
     * @tc.expected: The return value of child2 onKeyEvent is true.
     * @tc.steps: step4. call the function onKeyEventDispatch and dipatchKeyEvent.
     */
    auto onKeyEventCallback = [](KeyEventInfo& eventInfo) -> bool { return true; };
    childFocusHub2->SetOnKeyCallback(std::move(onKeyEventCallback));
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));
}
} // namespace OHOS::Ace::NG