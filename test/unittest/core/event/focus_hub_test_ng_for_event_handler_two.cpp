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

/**
 * @tc.name: LostFocusToTabstopTest001
 * @tc.desc: Test LostFocusToTabstop.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostFocusToTabstopTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: CreateTree.
     */
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    pageNode->onMainTree_ = true;
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    context->rootNode_->AddChild(pageNode);
    auto column = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto column2 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto column3 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    column->onMainTree_ = true;
    column2->onMainTree_ = true;
    column3->onMainTree_ = true;
    auto columnFocusHub = column->GetOrCreateFocusHub();
    auto columnFocusHub2 = column2->GetOrCreateFocusHub();
    auto columnFocusHub3 = column3->GetOrCreateFocusHub();
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->onMainTree_ = true;
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    pageNode->AddChild(column);
    column->AddChild(column2);
    column2->AddChild(column3);
    column3->AddChild(buttonNode);
    pagePattern->FocusViewShow();
    context->FlushFocusView();
    pagePattern->TriggerFocusMove();
    EXPECT_EQ(buttonFocusHub->IsCurrentFocus(), true);

    /**
     * @tc.steps2: SetTabStop and test RequestNextFocusOfKeyEsc.
     */
    columnFocusHub->SetTabStop(true);
    columnFocusHub2->SetTabStop(true);
    buttonFocusHub->RequestNextFocusOfKeyEsc();
    EXPECT_EQ(columnFocusHub2->IsCurrentFocus(), true);
    EXPECT_EQ(buttonFocusHub->IsCurrentFocus(), false);
    EXPECT_EQ(columnFocusHub3->IsCurrentFocus(), false);
    columnFocusHub2->RequestNextFocusOfKeyEsc();
    EXPECT_EQ(columnFocusHub->IsCurrentFocus(), true);
    EXPECT_EQ(columnFocusHub2->IsCurrentFocus(), false);
    columnFocusHub3->RequestNextFocusOfKeyEsc();
    EXPECT_EQ(columnFocusHub->IsCurrentFocus(), true);
}

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
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
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
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);

    CrownEvent event;
    EXPECT_FALSE(focusHub->HandleCrownEvent(event));

    OnCrownCallbackFunc onCrownEventCallback = [](CrownEventInfo& info) {};
    focusHub->SetOnCrownCallback(std::move(onCrownEventCallback));

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
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);

    CrownEvent event;
    EXPECT_FALSE(focusHub->ProcessOnCrownEventInternal(event));

    focusHub->currentFocus_ = true;
    auto focus = focusHub->IsCurrentFocus();
    EXPECT_EQ(focus, true);

    OnCrownEventFunc onCrownEventsInternal = [](const CrownEvent& info) -> bool { return true;};
    focusHub->SetOnCrownEventInternal(std::move(onCrownEventsInternal));
    EXPECT_TRUE(focusHub->ProcessOnCrownEventInternal(event));
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

/**
 * @tc.name: DumpFocusScopeTree001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, DumpFocusScopeTree001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    int32_t depth = 1;
    focusHub->focusType_ = FocusType::SCOPE;
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());
}

/**
* @tc.name: DumpFocusNodeTree001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, DumpFocusNodeTree001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    int32_t depth = 1;
    focusHub->focusType_ = FocusType::NODE;
    auto ss = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());
}

/**
* @tc.name: HandleFocusNavigation001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, HandleFocusNavigation001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    auto ret = focusHub->HandleFocusNavigation(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: DumpFocusTree003
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, DumpFocusTree003, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    int32_t depth = 1;
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    focusHub->focusType_ = FocusType::SCOPE;
    auto stream = std::make_unique<std::ostringstream>();
    DumpLog::GetInstance().SetDumpFile(std::move(stream));

    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth, true);
    EXPECT_NE(DumpLog::GetInstance().description_.empty(), true);

    focusHub->focusType_ = FocusType::NODE;
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->currentFocus_ = false;
    focusHub->SetTabStop(true);
    focusHub->focusable_ = false;
    focusHub->DumpFocusTree(depth, true);
    EXPECT_NE(DumpLog::GetInstance().description_.empty(), true);
}

/**
* @tc.name: LostFocusToTabStop001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, LostFocusToTabStop001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusNode->SetCurrentFocus(true);
    focusHub->LostFocusToTabStop(focusNode);
    EXPECT_EQ(focusNode->IsCurrentFocus(), true);
}

/**
* @tc.name: LostFocusToTabStop001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, LostFocusToTabStop002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusNode->SetCurrentFocus(false);
    focusHub->LostFocusToTabStop(focusNode);
    EXPECT_EQ(focusNode->IsCurrentFocus(), false);
}

/**
* @tc.name: LostChildFocusToSelf001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, LostChildFocusToSelf001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetCurrentFocus(false);
    focusHub->LostChildFocusToSelf();
    EXPECT_NE(focusHub->IsCurrentFocus(), true);
}

/**
* @tc.name: IsArrowKeyStepOut001
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, IsArrowKeyStepOut001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::LEFT;
    focusHub->isGroup_ = true;
    focusHub->arrowKeyStepOut_ = false;
    auto ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, true);

    focusHub->isGroup_ = false;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->arrowKeyStepOut_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);
}

/**
* @tc.name: IsArrowKeyStepOut002
* @tc.desc:
* @tc.type: FUNC
*/
HWTEST_F(FocusHubTestNg, IsArrowKeyStepOut002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    FocusStep moveStep = FocusStep::SHIFT_TAB;
    focusHub->isGroup_ = true;
    focusHub->arrowKeyStepOut_ = false;
    auto ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = false;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->arrowKeyStepOut_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);

    focusHub->isGroup_ = true;
    ret = focusHub->IsArrowKeyStepOut(moveStep);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: IsChildOf001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsChildOf001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1,
        AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1,
        AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto parentFocusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto ret = focusHub2->IsChildOf(parentFocusHub2);
    EXPECT_EQ(ret, false);

    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->HandleLastFocusNodeInFocusWindow();
    auto parentFocusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ret = focusHub->IsChildOf(parentFocusHub);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: GetUnfocusableParentFocusNode001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetUnfocusableParentFocusNode001, TestSize.Level1)
{
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
    auto res = focusHub->GetUnfocusableParentFocusNode();
    WeakPtr<FocusHub> FocusHub2 = nullptr;
    EXPECT_EQ(res, FocusHub2);
}

/**
 * @tc.name: CalculatePosition001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, CalculatePosition001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    std::list<RefPtr<FocusHub>> focusNodes;
    focusNode->SetCurrentFocus(true);
    focusNodes.push_front(focusNode);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    auto ret = focusHub->CalculatePosition();
    EXPECT_EQ(ret, true);
}
} // namespace OHOS::Ace::NG
