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
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
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
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
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
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
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
    ASSERT_NE(pipeline, nullptr);
    focusHub->currentFocus_ = false;
    auto focusManager = pipeline->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;
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
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;

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
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = true;

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
} // namespace OHOS::Ace::NG