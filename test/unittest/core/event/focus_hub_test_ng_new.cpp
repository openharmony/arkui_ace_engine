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
 * @tc.name: FocusHubTestNg0043
 * @tc.desc: Test the function SwitchFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0043, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_COMPONENT_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1,
        AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    frameNode2->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    frameNode2->SetParent(nodeParent);

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto parent = focusHub->GetParentFocusHub();
    parent->focusType_ = FocusType::NODE;
    parent->SwitchFocus(focusHub);
    parent->focusType_ = FocusType::SCOPE;
    parent->SwitchFocus(focusHub);
    EXPECT_NE(focusHub->focusType_, FocusType::SCOPE);
    parent->currentFocus_ = true;
    frameNode->AddChild(frameNode2);
    frameNode2->focusHub_ = focusHub;
    parent->SwitchFocus(focusHub);
    EXPECT_TRUE(parent->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg0046
 * @tc.desc: Test the function TriggerFocusScroll.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0046, TestSize.Level1)
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
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->isFocusActive_ = true;
    focusHub->isFocusUnit_ = true;
    auto parentNode = FrameNodeOnTree::CreateFrameNode(V2::ROW_ETS_TAG, 1,
        AceType::MakeRefPtr<Pattern>());
    auto parentFocusHub = parentNode->GetOrCreateFocusHub();
    parentFocusHub->focusType_ = FocusType::SCOPE;
    frameNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parentNode));
    focusHub->onPaintFocusStateCallback_ = []() { return true; };
    focusHub->PaintAllFocusState();
    focusHub->TriggerFocusScroll();
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->isFocusUnit_ = false;
    focusHub->TriggerFocusScroll();
    EXPECT_FALSE(focusHub->isFocusUnit_);
}

/**
 * @tc.name: FocusHubTestNg0047
 * @tc.desc: Test the function CalculatePosition and PaintAllFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    eventHub1->AttachHost(frameNode1);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetOrCreateFocusHub();
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->ClearAllFocusState();
    focusHub->PaintAllFocusState();
    focusHub->CalculatePosition();
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    EXPECT_FALSE(focusHub->CalculatePosition());
    focusHub->focusStyleType_ = FocusStyleType::NONE;
    focusHub->isFocusActiveWhenFocused_ = true;
    EXPECT_FALSE(focusHub->PaintAllFocusState());
    EXPECT_FALSE(focusHub->CalculatePosition());
}

/**
 * @tc.name: FocusHubTestNg0048
 * @tc.desc: Test the function ClearFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
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
    RoundRect focusRectInner;
    context->isFocusActive_ = true;
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_FALSE(focusHub->PaintInnerFocusState(focusRectInner));
    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));
    focusHub->focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
    focusHub->focusPaintParamsPtr_->paintColor = Color::RED;
    focusHub->focusPaintParamsPtr_->paintWidth = Dimension(10);
    EXPECT_TRUE(focusHub->PaintInnerFocusState(focusRectInner));
}

/**
 * @tc.name: FocusHubTestNg0049
 * @tc.desc: Test the function PaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
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
    context->isFocusActive_ = true;
    focusHub->focusType_ = FocusType::NODE;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    RoundRect paintRect;
    focusHub->getInnerFocusRectFunc_ = [](RoundRect) {};
    EXPECT_FALSE(focusHub->PaintFocusState(false));
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_BORDER;
    EXPECT_FALSE(focusHub->PaintFocusState(false));
    focusHub->focusPaintParamsPtr_ = std::make_unique<FocusPaintParam>();
    focusHub->focusPaintParamsPtr_->paintColor = Color::RED;
    focusHub->focusPaintParamsPtr_->paintWidth = Dimension(10);
    focusHub->focusPaintParamsPtr_->paintRect = RoundRect(RectF(), 0.0f, 0.0f);
    EXPECT_TRUE(focusHub->PaintFocusState(false));
    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    EXPECT_TRUE(focusHub->PaintFocusState(false));
    focusHub->focusStyleType_ = FocusStyleType::INNER_BORDER;
    EXPECT_TRUE(focusHub->PaintFocusState(false));
    focusHub->focusPaintParamsPtr_->focusPadding = Dimension(10);
    EXPECT_TRUE(focusHub->PaintFocusState(false));
}

/**
 * @tc.name: FocusHubTestNg0050
 * @tc.desc: Test the function ScrollToLastFocusIndex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0050, TestSize.Level1)
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
    focusHub->currentFocus_ = true;
    auto parentNode = FrameNodeOnTree::CreateFrameNode(V2::ROW_ETS_TAG, 1,
        AceType::MakeRefPtr<Pattern>());
    auto parentFocusHub = parentNode->GetOrCreateFocusHub();
    parentFocusHub->focusType_ = FocusType::SCOPE;
    frameNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parentNode));
    focusHub->SetLastFocusNodeIndex(focusHub);
    focusHub->ScrollToLastFocusIndex();
    focusHub->lastFocusNodeIndex_ = 1;
    focusHub->ScrollToLastFocusIndex();
    EXPECT_NE(focusHub->focusType_, FocusType::SCOPE);
}

/**
 * @tc.name: FocusHubTestNg0051
 * @tc.desc: Test the function RequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0051, TestSize.Level1)
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
    focusHub->RequestFocus();
    focusHub->currentFocus_ = true;
    focusHub->RequestFocus();
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg0052
 * @tc.desc: Test the function FocusToHeadOrTailChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0052, TestSize.Level1)
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
    auto parentNode = FrameNodeOnTree::CreateFrameNode(V2::ROW_ETS_TAG, 1,
        AceType::MakeRefPtr<Pattern>());
    auto parentFocusHub = parentNode->GetOrCreateFocusHub();
    parentFocusHub->focusType_ = FocusType::SCOPE;
    frameNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parentNode));
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_FALSE(focusHub->FocusToHeadOrTailChild(true));
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->FocusToHeadOrTailChild(false));
}

/**
 * @tc.name: FocusHubTestNg0054
 * @tc.desc: Test the function GoToNextFocusLinear.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0054, TestSize.Level1)
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
    EXPECT_FALSE(focusHub->GoToNextFocusLinear(FocusStep::LEFT));
}

/**
 * @tc.name: FocusHubTestNg0055
 * @tc.desc: Test the function OnKeyEventScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0055, TestSize.Level1)
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
    pipeline->isFocusActive_ = true;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    pipeline->eventManager_->isTabJustTriggerOnKeyEvent_ = true;
    focusHub->currentFocus_ = true;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_TAB);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0056
 * @tc.desc: Test the function RequestNextFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0056, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<EventHub> eventHub1 = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub1)));
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->focusAlgorithm_.scopeType = ScopeType::PROJECT_AREA;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    EXPECT_FALSE(focusHub->RequestNextFocus(FocusStep::LEFT));
    EXPECT_FALSE(focusHub->RequestNextFocus(FocusStep::SHIFT_TAB));
    focusHub->focusAlgorithm_.getNextFocusNode = [](FocusStep, const WeakPtr<FocusHub>&, WeakPtr<FocusHub>&)
        -> bool { return false; };
    EXPECT_FALSE(focusHub->RequestNextFocus(FocusStep::TAB));
}

/**
 * @tc.name: FocusHubTestNg0057
 * @tc.desc: Test the function GetNearestNodeByProjectArea.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0057, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto frameNode2 = FrameNodeOnTree::CreateFrameNode(V2::ROW_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1,
        AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<EventHub> eventHub2 = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    eventHub2->AttachHost(frameNode2);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    focusNodes.emplace_back(focusHub2);
    EXPECT_EQ(focusHub->GetNearestNodeByProjectArea(focusNodes, FocusStep::NONE), nullptr);
    EXPECT_EQ(focusHub->GetNearestNodeByProjectArea(focusNodes, FocusStep::TAB), nullptr);
    EXPECT_EQ(focusHub->GetNearestNodeByProjectArea(focusNodes, FocusStep::SHIFT_TAB), nullptr);
}

/**
 * @tc.name: FocusHubTestNg058
 * @tc.desc: Test the function HandleFocusByTabIndex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0058, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    TabIndexNodeList tabIndexNodes;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    focusHub->currentFocus_ = true;
    EXPECT_FALSE(focusHub->HandleFocusByTabIndex(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg059
 * @tc.desc: Test the function HandleFocusByTabIndex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0059, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    frameNode->geometryNode_->SetFrameSize(SizeF(20, 20));
    frameNode->geometryNode_->SetFrameOffset(OffsetF(20, 20));
    ASSERT_NE(focusHub, nullptr);
    std::list<RefPtr<FocusHub>> allNodes;

    auto focus1 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim<EventHub>(nullptr), FocusType::NODE, true);

    auto frameNode2 = FrameNodeOnTree::CreateFrameNode("frameNode2", 102,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode2->GetOrCreateFocusHub();
    auto focusHub2 = frameNode2->GetFocusHub();
    frameNode2->geometryNode_->SetFrameOffset(OffsetF(15, 15));
    frameNode2->geometryNode_->SetFrameSize(SizeF(30, 30));

    auto frameNode3 = FrameNodeOnTree::CreateFrameNode("frameNode3", 103,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode3->GetOrCreateFocusHub();
    auto focusHub3 = frameNode3->GetFocusHub();
    frameNode3->geometryNode_->SetFrameOffset(OffsetF(20, 20));
    frameNode3->geometryNode_->SetFrameSize(SizeF(30, 30));

    auto frameNode4 = FrameNodeOnTree::CreateFrameNode("frameNode4", 104,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode4->GetOrCreateFocusHub();
    auto focusHub4 = frameNode4->GetFocusHub();
    frameNode4->geometryNode_->SetFrameOffset(OffsetF(10, 20));
    frameNode4->geometryNode_->SetFrameSize(SizeF(20, 20));

    auto frameNode5 = FrameNodeOnTree::CreateFrameNode("frameNode5", 105,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode5->GetOrCreateFocusHub();
    auto focusHub5 = frameNode5->GetFocusHub();
    frameNode5->geometryNode_->SetFrameOffset(OffsetF(20, 20));
    frameNode5->geometryNode_->SetFrameSize(SizeF(30, 30));

    allNodes.push_back(nullptr);
    allNodes.push_back(focus1);
    allNodes.push_back(focusHub);
    allNodes.push_back(focusHub2);
    allNodes.push_back(focusHub3);
    allNodes.push_back(focusHub4);
    allNodes.push_back(focusHub5);

    auto res = focusHub->GetNearestNodeByProjectArea(allNodes, FocusStep::UP);
    ASSERT_NE(res, nullptr);
    res = focusHub->GetNearestNodeByProjectArea(allNodes, FocusStep::DOWN);
    ASSERT_NE(res, nullptr);
    res = focusHub->GetNearestNodeByProjectArea(allNodes, FocusStep::LEFT);
    ASSERT_NE(res, nullptr);
    res = focusHub->GetNearestNodeByProjectArea(allNodes, FocusStep::RIGHT);
    ASSERT_NE(res, nullptr);
}

/**
 * @tc.name: FocusHubTestNg064
 * @tc.desc: Test the function CollectTabIndexNodes.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0064, TestSize.Level1)
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

    TabIndexNodeList list;
    focusHub->CollectTabIndexNodes(list);
    ASSERT_FALSE(list.empty());

    focusHub->focusCallbackEvents_->tabIndex_ = 1;
    focusHub->CollectTabIndexNodes(list);
    ASSERT_FALSE(list.empty());
}

/**
 * @tc.name: FocusHubTestNg065
 * @tc.desc: Test the function AcceptFocusByRectOfLastFocusFlex.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0065, TestSize.Level1)
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

    focusHub1->focusable_ = false;
    frameNode2->geometryNode_ = nullptr;
    focusHub3->currentFocus_ = true;

    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode->children_.push_back(frameNode1);
    frameNode->children_.push_back(frameNode2);
    frameNode->children_.push_back(frameNode3);
    frameNode->children_.push_back(frameNode4);

    auto res = focusHub->AcceptFocusByRectOfLastFocusFlex(RectF(0, 0, -1, -1));
    ASSERT_FALSE(res);
    focusHub->AcceptFocusByRectOfLastFocusFlex(RectF());
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->focusType_ = FocusType::DISABLE;
    res = focusHub->AcceptFocusByRectOfLastFocusFlex(RectF(0, 0, -1, -1));
    ASSERT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg067
 * @tc.desc: Test the function GetChildFocusNodeByType.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0067, TestSize.Level1)
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

    focusHub1->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub2->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub3->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();

    focusHub3->focusCallbackEvents_->isDefaultGroupFocus_ = false;
    focusHub1->focusCallbackEvents_->isDefaultGroupFocus_ = true;

    focusHub->focusType_ = FocusType::SCOPE;
    frameNode->children_.push_back(frameNode3);
    frameNode->children_.push_back(frameNode1);

    auto res = focusHub->GetChildFocusNodeByType(FocusNodeType::GROUP_DEFAULT);
    ASSERT_NE(res, nullptr);
}

/**
 * @tc.name: FocusHubTestNg068
 * @tc.desc: Test the function GoToFocusByTabNodeIdx.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0068, TestSize.Level1)
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

    focusHub1->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub2->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub3->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub4->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();

    frameNode4->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode2));
    focusHub1->focusType_ = FocusType::SCOPE;
    focusHub2->focusType_ = FocusType::SCOPE;
    focusHub3->focusCallbackEvents_->isDefaultGroupFocus_ = true;
    focusHub4->focusCallbackEvents_->isDefaultGroupFocus_ = true;
    focusHub2->focusable_ = false;

    frameNode1->children_.push_back(frameNode3);
    frameNode2->children_.push_back(frameNode4);

    TabIndexNodeList list;
    list.push_back({1, AceType::WeakClaim(AceType::RawPtr(focusHub1))});
    list.push_back({2, AceType::WeakClaim(AceType::RawPtr(focusHub2))});

    focusHub->focusType_ = FocusType::SCOPE;
    auto res = focusHub->GoToFocusByTabNodeIdx(list, 0);
    ASSERT_TRUE(res);
    res = focusHub->GoToFocusByTabNodeIdx(list, 1);
    ASSERT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg069
 * @tc.desc: Test the function CollectTabIndexNodes.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0069, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    focusHub->focusable_ = false;
    focusHub->focusType_ = FocusType::SCOPE;
    TabIndexNodeList list;
    focusHub->CollectTabIndexNodes(list);
    ASSERT_TRUE(list.empty());
}

/**
 * @tc.name: FocusHubTestNg070
 * @tc.desc: Test the function IsFocusableWholePath.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0070, TestSize.Level1)
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

    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);

    ASSERT_TRUE(focusHub->IsFocusableNode());
    ASSERT_TRUE(focusHub->IsFocusableScope());
    auto res = focusHub1->IsFocusableWholePath();
    ASSERT_TRUE(res);
}

/**
 * @tc.name: FocusHubTestNg071
 * @tc.desc: Test the function IsFocusableScopeByTab.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0071, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub->focusCallbackEvents_->tabIndex_ = 1;

    auto res = focusHub->IsFocusableScopeByTab();
    ASSERT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg072
 * @tc.desc: Test the function AcceptFocusOfSpecifyChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0072, TestSize.Level1)
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

    focusHub1->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub2->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();

    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB);
    frameNode->children_.push_back(frameNode1);
    frameNode->children_.push_back(frameNode2);
    focusHub1->focusable_ = false;
    auto res = focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB);
    ASSERT_TRUE(res);
    res = focusHub->AcceptFocusOfSpecifyChild(FocusStep::SHIFT_TAB);
    ASSERT_TRUE(res);
    res = focusHub->AcceptFocusOfSpecifyChild(FocusStep::DOWN);
    ASSERT_FALSE(res);
    focusHub2->focusable_ = false;
    res = focusHub->AcceptFocusOfSpecifyChild(FocusStep::SHIFT_TAB);
    ASSERT_FALSE(res);
    res = focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB);
    ASSERT_FALSE(res);
}

/**
 * @tc.name: FocusHubTestNg073
 * @tc.desc: Test the function ClearAllFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0073, TestSize.Level1)
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
    focusHub->ClearAllFocusState();
    ASSERT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);

    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
}

/**
 * @tc.name: FocusHubTestNg074
 * @tc.desc: Test the function PaintAllFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0074, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    context->isFocusActive_ = true;

    focusHub->focusStyleType_ = FocusStyleType::OUTER_BORDER;
    auto res = focusHub->PaintAllFocusState();
    ASSERT_TRUE(res);
}

/**
 * @tc.name: FocusHubTestNg075
 * @tc.desc: Test the function PaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0075, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    context->isFocusActive_ = true;

    auto func = [](RoundRect& rect) { rect.rect_ = RectF(); };
    focusHub->getInnerFocusRectFunc_ = func;
    focusHub->focusStyleType_ = FocusStyleType::CUSTOM_REGION;
    auto res = focusHub->PaintFocusState();
    ASSERT_TRUE(res);
}

/**
 * @tc.name: FocusHubTestNg076
 * @tc.desc: Test the function OnFocusScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0076, TestSize.Level1)
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

    focusHub1->focusable_ =false;
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode->children_.push_back(frameNode1);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    focusHub->OnFocusScope();
    ASSERT_FALSE(focusHub1->focusable_);
}

/**
 * @tc.name: FocusHubTestNg077
 * @tc.desc: Test the function OnFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0077, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub and construct allNodes.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101,
        AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->OnFocus();
    ASSERT_EQ(focusHub->focusType_, FocusType::DISABLE);
}

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
    ASSERT_FALSE(res);
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
    ASSERT_TRUE(res);
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
    ASSERT_TRUE(res);
    focusHub2->focusable_ = false;
    res = focusHub->GoToNextFocusLinear(FocusStep::SHIFT_TAB, RectF());
    ASSERT_TRUE(res);
    focusHub1->focusable_ = false;
    res = focusHub->GoToNextFocusLinear(FocusStep::SHIFT_TAB, RectF());
    ASSERT_FALSE(res);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim<FocusHub>(nullptr);
    focusHub4->focusable_ = false;
    res = focusHub->GoToNextFocusLinear(FocusStep::TAB, RectF());
    ASSERT_FALSE(res);
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
    ASSERT_FALSE(focusHub1->currentFocus_);
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
    ASSERT_TRUE(res);
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
    pipeline->isFocusActive_ = true;
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
    ASSERT_TRUE(focusHub->IsFocusableNode());
    ASSERT_TRUE(focusHub->IsFocusableScope());
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
    ASSERT_TRUE(focusHub->IsFocusableNode());
    focusHub->currentFocus_ = true;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    ASSERT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);
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
    ASSERT_FALSE(res);
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
    ASSERT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);
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
    ASSERT_TRUE(focusHub->currentFocus_ == false);
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
    ASSERT_FALSE(focusHub->currentFocus_);
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
    ASSERT_FALSE(focusHub->ScrollByOffsetToParent(textFieldNode));

    auto listNode = FrameNodeOnTree::CreateFrameNode("frameNode", 104,
        AceType::MakeRefPtr<ListPattern>());
    listNode->GetOrCreateFocusHub();
    auto listFocusHub = listNode->GetFocusHub();
    ASSERT_NE(listFocusHub, nullptr);
    ASSERT_FALSE(focusHub->ScrollByOffsetToParent(listNode));
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
    pipeline->isFocusActive_ = true;
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
    ASSERT_FALSE(focusHub->HasFocusedChild());

    /**
     * @tc.steps4: call the function HasFocusedChild with false and FocusType::DISABLE
     * @tc.expected: The return value of HasFocusedChild is false.
     */
    focusHub->currentFocus_ = false;
    focusHub->focusType_ = FocusType::DISABLE;
    ASSERT_FALSE(focusHub->HasFocusedChild());


    /**
     * @tc.steps5: call the function HasFocusedChild with false and FocusType::SCOPE
     * @tc.expected: The return value of HasFocusedChild is false.
     */
    focusHub->focusType_ = FocusType::SCOPE;
    ASSERT_FALSE(focusHub->HasFocusedChild());
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

/**
 * @tc.name: FocusHubTestNg0125
 * @tc.desc: Test the function dispatchKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0125, TestSize.Level1)
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
     * @tc.expected: The return value of child2 onKeyEvent is false.
     * @tc.steps: step4. call the function onKeyEventDispatch and dipatchKeyEvent.
     */
    auto onKeyEventCallback = [](KeyEventInfo& eventInfo) -> bool { return false; };
    childFocusHub2->SetOnKeyCallback(std::move(onKeyEventCallback));
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNg0126
 * @tc.desc: Test the function dispatchKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0126, TestSize.Level1)
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
     * @tc.expected: The return value of child2 onKeyEvent SetStopPropagation true.
     * @tc.steps: step6. call the function onKeyEventDispatch and dipatchKeyEvent.
     */
    auto onKeyEventCallback = [](KeyEventInfo& eventInfo) -> bool {
        eventInfo.SetStopPropagation(true);
        return false;
    };
    childFocusHub2->SetOnKeyCallback(std::move(onKeyEventCallback));
    EXPECT_TRUE(focusHub->HandleEvent(keyEvent));
}

#ifdef SUPPORT_DIGITAL_CROWN
/**
 * @tc.name: FocusHubTestNg0999
 * @tc.desc: Test the function OnFocusEventNode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0999, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 120, AceType::MakeRefPtr<ButtonPattern>());
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);

    /**
     * @tc.steps2: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);
    NonPointerEvent nonPointerEvent;
    nonPointerEvent.sourceType = SourceType::CROWN;
    FocusEvent focusEvent(nonPointerEvent);
    EXPECT_FALSE(focusHub->OnFocusEventNode(focusEvent));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);
}

/**
 * @tc.name: FocusHubTestNg01000
 * @tc.desc: Test the function HandleCrownEvent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg01000, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 120, AceType::MakeRefPtr<ButtonPattern>());
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);

    /**
     * @tc.steps2: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);

    CrownEvent event;
    EXPECT_FALSE(focusHub->HandleCrownEvent(event));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);
}

/**
 * @tc.name: FocusHubTestNg01001
 * @tc.desc: Test the function ProcessOnCrownEventInternal.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg01001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 120, AceType::MakeRefPtr<ButtonPattern>());
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);

    /**
     * @tc.steps2: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);

    CrownEvent event;
    EXPECT_FALSE(focusHub->ProcessOnCrownEventInternal(event));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);
}
#endif

/**
 * @tc.name: GetRootFocusHub001
 * @tc.desc: Test the function GetRootFocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetRootFocusHub001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);
}

/**
 * @tc.name: SetFocusable001
 * @tc.desc: Test the function SetFocusable.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetFocusable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusable_ = true;
    focusHub->implicitFocusable_ = true;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->SetFocusable(true, true);
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->SetFocusable(true, true);
    ASSERT_NE(focusHub->focusDepend_, FocusDependence::CHILD);
}
} // namespace OHOS::Ace::NG