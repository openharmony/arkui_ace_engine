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
#include "gtest/gtest.h"
#include "test/unittest/core/event/focus_hub_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: PaintFocusState0002
 * @tc.desc: Test the function SwitchFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintFocusState0002, TestSize.Level1)
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
    eventHub->AddSupportedState(NG::UI_STATE_FOCUSED);
    ASSERT_NE(eventHub->stateStyleMgr_, nullptr);
    EXPECT_TRUE(focusHub->PaintFocusState(false));
    EXPECT_TRUE(focusHub->PaintFocusState(true));

    eventHub->stateStyleMgr_ = nullptr;
    ASSERT_EQ(eventHub->stateStyleMgr_, nullptr);
    focusManager->isFocusActive_ = true;
    FocusBoxStyle styledStyle;
    styledStyle.strokeColor = Color::RED;
    focusHub->box_.SetStyle(styledStyle);
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
    focusHub->focusStyleType_ = FocusStyleType::NONE;
    EXPECT_FALSE(focusHub->HasFocusStateStyle());
    EXPECT_FALSE(focusHub->PaintFocusState(false));

    focusManager->isFocusActive_ = true;
    EXPECT_TRUE(focusHub->IsNeedPaintFocusState());
    focusHub->focusStyleType_ = FocusStyleType::FORCE_NONE;
    EXPECT_FALSE(focusHub->HasFocusStateStyle());
    EXPECT_TRUE(focusHub->PaintFocusState(false));
}

/**
 * @tc.name: GetRootFocusHub002
 * @tc.desc: Test the function GetRootFocusHub.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetRootFocusHub002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with the WeakPtr eventHub_ owning frameNode.
     * @tc.expected: eventHub can be updated and can get frameNode and its related properties.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps: step2. Create focusHub and its frameNode has parent node.
     * @tc.expected: FocusHub will return frameNode' parent focusHub.
     */
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Expect the result is not nullptr.
     */
    EXPECT_TRUE(focusHub->GetParentFocusHub() != nullptr);
    ASSERT_NE(focusHub->GetRootFocusHub(), nullptr);
}

/**
 * @tc.name: GetFocusLeaf001
 * @tc.desc: Test the function GetFocusLeaf.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetFocusLeaf001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with the WeakPtr eventHub_ owning frameNode.
     * @tc.expected: eventHub can be updated and can get frameNode and its related properties.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    /**
     * @tc.steps: step2. Create focusHub and its frameNode has parent node.
     * @tc.expected: FocusHub will return frameNode' parent focusHub.
     */
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step3. Set the corresponding variables to ensure entry into the target branch.
     * @tc.expected: The result is not nullptr.
     */
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->eventHub_ = nullptr;
    focusHub->frameNode_ = nullptr;
    focusHub->focusDepend_ = FocusDependence::SELF;
    ASSERT_NE(focusHub->GetFocusLeaf(), nullptr);
}

/**
 * @tc.name: LostFocusToTabStop003
 * @tc.desc: LostFocusToTabStop
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostFocusToTabStop003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusNode->SetCurrentFocus(false);
    auto focusHubTest = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusNode->lastWeakFocusNode_ = focusHubTest;

    /**
     * @tc.steps: step3. Make ensure entry into the target branch.
     */
    focusHub->LostFocusToTabStop(focusNode);
    EXPECT_NE(focusNode->lastWeakFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: LostChildFocusToSelf002
 * @tc.desc: LostChildFocusToSelf
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostChildFocusToSelf002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->SetCurrentFocus(true);

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    auto focusHubTest = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->lastWeakFocusNode_ = focusHubTest;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->LostChildFocusToSelf();

    /**
     * @tc.steps: step3. Expect the focusDepend_ is FocusDependence::SELF.
     */
    EXPECT_EQ(focusHub->focusDepend_, FocusDependence::SELF);
}

/**
 * @tc.name: RequestNextFocusOfKeyTab002
 * @tc.desc: RequestNextFocusOfKeyTab
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RequestNextFocusOfKeyTab002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->isGroup_ = false;
    EXPECT_EQ(focusHub->IsInFocusGroup(), false);
    focusEvent.intension = FocusIntension::TAB;
    focusHub->GetFrameNode()->GetContext()->focusWindowId_ = 32;

    /**
     * @tc.steps: step3. Expect the ret is false.
     */
    auto ret = focusHub->RequestNextFocusOfKeyTab(focusEvent);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step4. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->isGroup_ = false;
    EXPECT_EQ(focusHub->IsInFocusGroup(), false);
    focusEvent.intension = FocusIntension::SHIFT_TAB;
    focusHub->GetFrameNode()->GetContext()->focusWindowId_ = 32;

    /**
     * @tc.steps: step3. Expect the ret is false.
     */
    ret = focusHub->RequestNextFocusOfKeyTab(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: RequestNextFocus002
 * @tc.desc: RequestNextFocus
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RequestNextFocus002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    auto focusNode = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    std::list<RefPtr<FocusHub>> focusNodes;
    focusNode->SetCurrentFocus(true);
    focusNodes.push_front(focusNode);
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(*(focusNodes.begin())));
    auto ret = focusHub->CalculatePosition();
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step3. Expect the result is false.
     */
    auto result = focusHub->RequestNextFocus(FocusStep::DOWN);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: TryRequestFocus002
 * @tc.desc: Test the function TryRequestFocus.
 * @tc.type: FUNC obsolete
 */
HWTEST_F(FocusHubTestNg, TryRequestFocus002, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps1: Build parameters.
     */
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();

    /**
     * @tc.steps: step3. Expect the ret is true.
     */
    auto res = focusHub->TryRequestFocus(focusHub1, RectF(), FocusStep::LEFT);
    ASSERT_TRUE(res);
}

/**
 * @tc.name: RequestNextFocusByCustomAlgorithm002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RequestNextFocusByCustomAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps2: Build parameters.
     */
    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    /**
     * @tc.steps: step3. Set the corresponding variables to ensure entry into the target branch.
     */
    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);
    focusHub->lastWeakFocusNode_ = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step4. Expect the ret is false.
     */
    auto ret = focusHub->RequestNextFocusByCustomAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: PaintFocusStateToRenderContext001
 * @tc.desc: Test the function PaintFocusStateToRenderContext.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, PaintFocusStateToRenderContext001, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub.
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    bool result = focusHub->PaintFocusStateToRenderContext();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsNeedPaintFocusState001
 * @tc.desc: Test the function IsNeedPaintFocusState.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsNeedPaintFocusState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->focusType_ = FocusType::SCOPE;
    frameNode1->parent_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    frameNode->children_.push_back(frameNode1);
    ASSERT_TRUE(focusHub->IsFocusableNode());

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->currentFocus_ = false;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    ASSERT_NE(focusHub->lastWeakFocusNode_.Upgrade(), nullptr);
    focusHub->lastWeakFocusNode_.Upgrade()->focusable_ = true;
    focusHub->lastWeakFocusNode_.Upgrade()->parentFocusable_ = true;
    focusHub->lastWeakFocusNode_.Upgrade()->frameNode_ = nullptr;
    focusHub->lastWeakFocusNode_.Upgrade()->eventHub_ = nullptr;
    focusHub->lastWeakFocusNode_.Upgrade()->currentFocus_ = true;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->lastWeakFocusNode_.Upgrade()->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->IsNeedPaintFocusState());
}

/**
 * @tc.name: HandleFocusTravel002
 * @tc.desc: HandleFocusTravel
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HandleFocusTravel002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    focusEvent.intension = FocusIntension::LEFT;

    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    focusHub->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode1));

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->currentFocus_ = true;
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    focusHub->GetFrameNode()->GetContext()->eventManager_->isTabJustTriggerOnKeyEvent_ = true;
    auto node = focusHub->GetFrameNode();
    EXPECT_NE(node, nullptr);
    auto* pipeline = node->GetContext();
    EXPECT_NE(pipeline, nullptr);
    EXPECT_TRUE(pipeline->GetIsFocusActive());
    EXPECT_TRUE(pipeline->IsTabJustTriggerOnKeyEvent());

    auto ret = focusHub->HandleFocusTravel(focusEvent);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step3. Set the corresponding variables to ensure entry into the target branch.
     */
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    focusHub->GetFrameNode()->GetContext()->focusManager_ = nullptr;
    node = focusHub->GetFrameNode();
    EXPECT_NE(node, nullptr);
    auto* pipelineone = node->GetContext();
    EXPECT_NE(pipelineone, nullptr);
    EXPECT_FALSE(pipelineone->GetIsFocusActive());

    ret = focusHub->HandleFocusTravel(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: DumpFocusUie001
 * @tc.desc: Test the function DumpFocusUie.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, DumpFocusUie001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto frameNode1 =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::UI_EXTENSION_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode1));
    auto node = focusHub->GetFrameNode();
    EXPECT_NE(node, nullptr);
    auto pattern = node->GetPattern();
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(node->GetTag(), V2::UI_EXTENSION_COMPONENT_TAG);
    focusHub->DumpFocusUie();
}

/**
 * @tc.name: SetEnabledAndSetShow002
 * @tc.desc: Test the function SetEnabled and SetShow.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetEnabledAndSetShow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    bool show = false;
    SystemProperties::debugEnabled_ = true;
    focusHub->SetEnabled(show);
    focusHub->SetShow(show);
    EXPECT_TRUE(SystemProperties::GetDebugEnabled());
}

/**
 * @tc.name: RequestNextFocusOfKeyEscTest002
 * @tc.desc: Test the function RequestNextFocusOfKeyEsc
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RequestNextFocusOfKeyEscTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create focusHub
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->GetFrameNode()->GetContext()->isWindowHasFocused_ = true;
    focusHub->GetFrameNode()->GetContext()->onFocus_ = true;
    focusHub->FocusToHeadOrTailChild(true);
    focusHub->HandleLastFocusNodeInFocusWindow();

    auto framenode = focusHub->GetFrameNode();
    EXPECT_NE(framenode, nullptr);
    auto* context = framenode->GetContext();
    EXPECT_NE(context, nullptr);
    EXPECT_EQ(context->IsWindowFocused(), true);
}

/**
 * @tc.name: AcceptFocusOfSpecifyChild01
 * @tc.desc: Test the function AcceptFocusOfSpecifyChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, AcceptFocusOfSpecifyChild01, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub.
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto frameNode1 = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode1->GetOrCreateFocusHub();
    frameNode->children_.push_back(frameNode1);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::SELF;
    EXPECT_EQ(focusHub->IsFocusableScope(), true);
    auto res = focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB);
    ASSERT_TRUE(res);
}

/**
 * @tc.name: ScrollByOffsetToParent001
 * @tc.desc: Test the function ScrollByOffsetToParent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, ScrollByOffsetToParent001, TestSize.Level1)
{
    /**
     * @tc.steps1: create focusHub.
     */
    auto listNode = FrameNodeOnTree::CreateFrameNode(
        V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    auto listItemGroupNode =
        FrameNodeOnTree::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<ListItemGroupPattern>(nullptr, V2::ListItemGroupStyle::NONE));
    auto listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr);
    auto listItemNode = FrameNodeOnTree::CreateFrameNode(
        V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), listItemPattern);
    auto buttonNode = FrameNodeOnTree::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(listNode, nullptr);
    ASSERT_NE(listItemGroupNode, nullptr);
    ASSERT_NE(listItemPattern, nullptr);
    ASSERT_NE(listItemNode, nullptr);
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->MountToParent(listItemNode);
    listItemNode->MountToParent(listItemGroupNode);
    listItemGroupNode->MountToParent(listNode);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto listPattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    EXPECT_NE(listPattern->targetIndexInGroup_, 0);
    listItemPattern->indexInListItemGroup_ = 0;

    /**
     * @tc.steps: step2. Set the corresponding variables to ensure entry into the target branch.
     */
    focusHub->ScrollByOffsetToParent(listNode);
    EXPECT_EQ(listPattern->targetIndexInGroup_, 0);
}
} // namespace OHOS::Ace::NG