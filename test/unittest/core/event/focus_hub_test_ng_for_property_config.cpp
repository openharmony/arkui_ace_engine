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
 * @tc.name: FocusHubTestNg0109
 * @tc.desc: Test the function IsNestingFocusGroup.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0109, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    /**
     * @tc.steps2: call the function IsNestingFocusGroup with isGroup_ = false
     * @tc.expected: The return value of IsNestingFocusGroup is false.
     */
    focusHub->isGroup_ = false;
    ASSERT_FALSE(focusHub->IsNestingFocusGroup());
}

/**
 * @tc.name: FocusHubTestNg0110
 * @tc.desc: Test the function IsNestingFocusGroup.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0110, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNode>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    /**
     * @tc.steps2: call the function IsNestingFocusGroup with isGroup_ = false
     * @tc.expected: The return value of IsNestingFocusGroup is false.
     */
    focusHub->isGroup_ = false;
    ASSERT_FALSE(focusHub->IsNestingFocusGroup());

    /**
     * @tc.steps3: call the function IsNestingFocusGroup with isGroup_ = true and nodeParent.focusHub.isGroup_ false
     * @tc.expected: The return value of IsNestingFocusGroup is true.
     */
    focusHub->isGroup_ = true;
    ASSERT_FALSE(focusHub->IsNestingFocusGroup());

    /**
     * @tc.steps4: call the function IsNestingFocusGroup with isGroup_ = true and nodeParent.focusHub.isGroup_ true
     * @tc.expected: The return value of IsNestingFocusGroup is true.
     */
    nodeParent->GetFocusHub()->isGroup_ = true;
    ASSERT_TRUE(focusHub->IsNestingFocusGroup());
}

/**
 * @tc.name: FocusHubTestNg0111
 * @tc.desc: Test the function IsInFocusGroup.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0111, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto nodeParent = AceType::MakeRefPtr<FrameNode>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    /**
     * @tc.steps2: call the function IsInFocusGroup with isGroup_ = false
     * @tc.expected: The return value of IsInFocusGroup is false.
     */
    focusHub->isGroup_ = false;
    ASSERT_FALSE(focusHub->IsInFocusGroup());

    /**
     * @tc.steps3: call the function IsInFocusGroup with isGroup_ = false and nodeParent.focusHub.isGroup_ true
     * @tc.expected: The return value of IsInFocusGroup is false.
     */
    focusHub->isGroup_ = false;
    nodeParent->GetFocusHub()->isGroup_ = true;
    ASSERT_TRUE(focusHub->IsInFocusGroup());
}

/**
 * @tc.name: FocusHubTestNg0112
 * @tc.desc: Test the function GetChildPriorfocusNode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0112, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHubNull = AceType::MakeRefPtr<FocusHub>(nullptr);
    ASSERT_EQ(focusHubNull->GetChildPriorfocusNode(focusHub->focusScopeId_).Upgrade(), nullptr);

    /**
     * @tc.steps2: call the function GetChildPriorfocusNode with focusScopeId_ empty
     * @tc.expected: The return value of GetChildPriorfocusNode is nullptr.
     */
    focusHub->isGroup_ = false;
    auto childFocusHub = focusHub->GetChildPriorfocusNode(focusHub->focusScopeId_);
    ASSERT_EQ(childFocusHub.Upgrade(), nullptr);

    /**
     * @tc.steps2: call the function GetChildPriorfocusNode with focusScopeId_ = "1"
     * @tc.expected: The return value of GetChildPriorfocusNode is nullptr.
     */
    focusHub->isGroup_ = false;
    focusHub->focusScopeId_ = "1";
    childFocusHub = focusHub->GetChildPriorfocusNode(focusHub->focusScopeId_);
    ASSERT_EQ(childFocusHub.Upgrade(), nullptr);
}

/**
 * @tc.name: FocusHubTestNg0113
 * @tc.desc: Test the function SetFocusScopePriority.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0113, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    auto focusScopeId = "scope1";
    auto focusScopeId2 = "scope2";

    /**
     * @tc.steps2: call the function SetFocusScopePriority with isFocusScope_ true and focusScopeId not empty
     * @tc.expected: The focusHub->focusScopeId_ NE focusScopeId.
     */
    focusHub->isFocusScope_ = true;
    focusHub->SetFocusScopePriority(focusScopeId, 0);
    ASSERT_NE(focusHub->focusScopeId_, focusScopeId);

    /**
     * @tc.steps3: call the function SetFocusScopePriority with isFocusScope_ false
     * @tc.expected: The focusHub->focusScopeId_ NE focusScopeId.
     */
    focusHub->isFocusScope_ = false;
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->SetFocusScopePriority(focusScopeId, 0);
    ASSERT_EQ(focusHub->focusScopeId_, focusScopeId);
    focusHub->focusPriority_ = FocusPriority::AUTO;
    focusHub->SetFocusScopePriority(focusScopeId, 0);
    ASSERT_EQ(focusHub->focusScopeId_, focusScopeId);

    /**
     * @tc.steps4: call the function SetFocusScopePriority with isFocusScope_ false and focusScopeId_ NE focusScopeId
     * @tc.expected: The focusHub->focusScopeId_ NE focusScopeId2.
     */
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->SetFocusScopePriority(focusScopeId2, 0);
    ASSERT_EQ(focusHub->focusScopeId_, focusScopeId2);
    // focusPriority_ NE FocusPriority::AUTO
    focusHub->focusPriority_ = FocusPriority::AUTO;
    focusHub->SetFocusScopePriority(focusScopeId2, 0);
    ASSERT_EQ(focusHub->focusScopeId_, focusScopeId2);

    /**
     * @tc.steps5: call the function SetFocusScopePriority with isFocusScope_ false and focusScopeId empty
     * @tc.expected: The focusHub->focusScopeId_ EQ focusScopeId.
     */
    focusHub->isFocusScope_ = false;
    focusHub->focusScopeId_ = focusScopeId;
    focusHub->SetFocusScopePriority("", 2000);
    ASSERT_EQ(focusHub->focusScopeId_, "");
    // focusScopeId_ is empty
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->SetFocusScopePriority("", 2000);
    ASSERT_EQ(focusHub->focusPriority_,  FocusPriority::AUTO);
}

/**
 * @tc.name: FocusHubTestNg0114
 * @tc.desc: Test the function RemoveFocusScopeIdAndPriority.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0114, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_EQ(focusHub->GetFocusManager(), nullptr);

    /**
     * @tc.steps2: call the function SetFocusScopePriority with isFocusScope_ true
     * @tc.expected: The focusHub->focusScopeId_ empty.
     */
    focusHub->isFocusScope_ = true;
    focusHub->focusScopeId_ = "";
    focusHub->RemoveFocusScopeIdAndPriority();
    focusHub->focusScopeId_ = "scop1";
    focusHub->RemoveFocusScopeIdAndPriority();
    ASSERT_FALSE(focusHub->focusScopeId_.empty());

    /**
     * @tc.steps3: call the function SetFocusScopePriority with isFocusScope_ false and focusPriority_ PRIOR
     * @tc.expected: The focusHub->focusScopeId_ NE focusScopeId.
     */
    focusHub->isFocusScope_ = false;
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->focusScopeId_ = "";
    focusHub->RemoveFocusScopeIdAndPriority();
    ASSERT_EQ(focusHub->focusScopeId_, "");
    focusHub->focusScopeId_ = "scop1";
    focusHub->RemoveFocusScopeIdAndPriority();
    ASSERT_EQ(focusHub->focusScopeId_, "scop1");

    /**
     * @tc.steps3: call the function SetFocusScopePriority with isFocusScope_ false and focusPriority_ AUTO
     * @tc.expected: The focusHub->focusScopeId_ NE focusScopeId.
     */
    focusHub->focusScopeId_ = "";
    focusHub->focusPriority_ = FocusPriority::AUTO;
    focusHub->RemoveFocusScopeIdAndPriority();
    ASSERT_EQ(focusHub->focusScopeId_, "");
    focusHub->focusScopeId_ = "scop1";
    focusHub->RemoveFocusScopeIdAndPriority();
    ASSERT_EQ(focusHub->focusScopeId_, "scop1");
}

/**
 * @tc.name: FocusHubTestNg0115
 * @tc.desc: Test the function SetFocusScopeId.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0115, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusScopeId_ = "scop1";

    /**
     * @tc.steps2: call the function SetFocusScopeId with focusType_  FocusType::DISABLE
     * @tc.expected: The focusHub->focusScopeId_ not change
     */
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->SetFocusScopeId("scop2", true);
    ASSERT_EQ(focusHub->focusScopeId_, "scop1");

    /**
     * @tc.steps3: call the function SetFocusScopeId with focusType_  FocusType::SCOPE and focusScopeId empty
     * @tc.expected: The focusHub->focusScopeId_ not change
     */
    focusHub->focusType_ = FocusType::SCOPE;
    // focusScopeId_ empty
    focusHub->focusScopeId_ = "";
    focusHub->SetFocusScopeId("", true);
    ASSERT_FALSE(focusHub->isFocusScope_);
    focusHub->focusScopeId_ = "scop1";
    focusHub->SetFocusScopeId("", true);
    ASSERT_EQ(focusHub->focusScopeId_, "");
    ASSERT_FALSE(focusHub->isFocusScope_);
    ASSERT_FALSE(focusHub->isGroup_);
}

/**
 * @tc.name: FocusHubTestNg0116
 * @tc.desc: Test the function RefreshFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0116, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps2: call the function RefreshFocus with currentFocus_  false
     * @tc.expected: The focusHub->currentFocus_ not change
     */
    focusHub->currentFocus_ = false;
    focusHub->RefreshFocus();
    ASSERT_FALSE(focusHub->currentFocus_);


    /**
     * @tc.steps3: call the function RefreshFocus with currentFocus_  true and don't has parent
     * @tc.expected: The focusHub->currentFocus_ false
     */
    focusHub->currentFocus_ = true;
    focusHub->RefreshFocus();
    ASSERT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: FocusHubTestNg0117
 * @tc.desc: Test the function RefreshFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0117, TestSize.Level1)
{
     /**
     * @tc.steps: step4. Create frameNode.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 114,
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto child = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        115, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto child2 = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        116, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);
    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    frameNode->eventHub_->enabled_ = false;

    parentFocusHub->RefreshFocus();
}

/**
 * @tc.name: FocusHubTestNg0119
 * @tc.desc: Test the function IsFocusAbleChildOf.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0119, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    
    ASSERT_FALSE(focusHub->IsFocusAbleChildOf(nullptr));
}


/**
 * @tc.name: FocusHubTestNg0120
 * @tc.desc: Test the function SetLastWeakFocusNodeToPreviousNode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNg0120, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);

    focusHub->focusType_ = FocusType::SCOPE;
    ASSERT_FALSE(focusHub->SetLastWeakFocusNodeToPreviousNode());
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->isFocusScope_ = true;
    ASSERT_FALSE(focusHub->SetLastWeakFocusNodeToPreviousNode());
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->isFocusScope_ = true;
    ASSERT_FALSE(focusHub->SetLastWeakFocusNodeToPreviousNode());
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusScopeId_ = "scop1";
    focusHub->isFocusScope_ = false;
    ASSERT_FALSE(focusHub->SetLastWeakFocusNodeToPreviousNode());
    focusHub->isFocusScope_ = true;
    ASSERT_FALSE(focusHub->SetLastWeakFocusNodeToPreviousNode());
}

/**
 * @tc.name: IsCurrentFocusWholePath001
 * @tc.desc: Test the function IsCurrentFocusWholePath.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsCurrentFocusWholePath001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);

    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::SELF;
    ASSERT_TRUE(focusHub->IsCurrentFocusWholePath());
    focusHub->focusDepend_ = FocusDependence::AUTO;
    ASSERT_TRUE(focusHub->IsCurrentFocusWholePath());
    focusHub->focusDepend_ = FocusDependence::CHILD;
    ASSERT_FALSE(focusHub->IsCurrentFocusWholePath());
}

/**
 * @tc.name: OnKeyPreIme001
 * @tc.desc: Test the function OnKeyPreIme.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, OnKeyPreIme001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_TAB;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    auto info = KeyEventInfo(keyEvent);
    ASSERT_FALSE(focusHub->OnKeyPreIme(info, keyEvent));
}

/**
 * @tc.name: GetProjectAreaOnRect001
 * @tc.desc: Test the function GetProjectAreaOnRect.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetProjectAreaOnRect001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    FocusStep step = FocusStep::UP;
    RectF rect = RectF(1, 1, 0, 10);
    RectF projectRect = RectF(1, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    rect = RectF(1, 1, 0, 0);
    projectRect = RectF(10, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    step = FocusStep::DOWN;
    rect = RectF(1, 1, 0, 10);
    projectRect = RectF(1, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    rect = RectF(1, 1, 0, 0);
    projectRect = RectF(10, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    step = FocusStep::LEFT;
    rect = RectF(1, 1, 0, 10);
    projectRect = RectF(1, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    rect = RectF(1, 1, 0, 0);
    projectRect = RectF(10, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    step = FocusStep::RIGHT;
    rect = RectF(1, 1, 0, 10);
    projectRect = RectF(1, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    rect = RectF(1, 1, 0, 0);
    projectRect = RectF(10, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);
    ASSERT_EQ(step, FocusStep::RIGHT);
}

/**
 * @tc.name: GetFirstChildFocusView001
 * @tc.desc: Test the function GetFirstChildFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetFirstChildFocusView001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    RefPtr<FocusView> result = focusHub->GetFirstChildFocusView();
    ASSERT_EQ(result, nullptr);
}

/**
 * @tc.name: DumpFocusTree001
 * @tc.desc: Test the function DumpFocusTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, DumpFocusTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());

    /**
     * @tc.steps: step2. Create FocusHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);

    /**
     * @tc.steps: step3. test function DumpFocusNodeTree.
     * @tc.expected: After DumpFocusTree, the DumpLog.description_ is empty.
     */
    int32_t depth = 1;
    focusHub->focusScopeId_ = "TEST";
    focusHub->isFocusScope_ = true;
    /**
     * @tc.steps: step4. test function DumpFocusScopeTree.
     * @tc.expected: After DumpFocusTree, the DumpLog.description_ is empty.
     */
    DumpLog::GetInstance().description_.push_back("test");
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->currentFocus_ = true;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());

    DumpLog::GetInstance().description_.push_back("PREVIOUS");
    focusHub->focusPriority_ = FocusPriority::PREVIOUS;
    focusHub->currentFocus_ = true;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());

    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->currentFocus_ = true;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());

    DumpLog::GetInstance().description_.push_back("PREVIOUS");
    focusHub->focusPriority_ = FocusPriority::PREVIOUS;
    focusHub->currentFocus_ = true;
    focusHub->DumpFocusTree(depth);
    EXPECT_TRUE(DumpLog::GetInstance().description_.empty());
}

/**
 * @tc.name: CheckFocusStateStyle001
 * @tc.desc: Test the function CheckFocusStateStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, CheckFocusStateStyle001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    focusHub->CheckFocusStateStyle(true);
}
} // namespace OHOS::Ace::NG123456