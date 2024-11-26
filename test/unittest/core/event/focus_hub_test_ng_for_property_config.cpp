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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/unittest/core/event/frame_node_on_tree.h"

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

    rect = RectF(1, 1, 10, 0);
    projectRect = RectF(1, 1, 0, 0);
    focusHub->GetProjectAreaOnRect(rect, projectRect, step);

    rect = RectF(1, 1, 0, 0);
    projectRect = RectF(1, 1, 10, 0);
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
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_TRUE(focusHub->IsFocusableByTab());
}

/**
 * @tc.name: IsSyncRequestFocusableScope001
 * @tc.desc: Test the function IsSyncRequestFocusableScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsSyncRequestFocusableScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->IsSyncRequestFocusableScope();
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->IsSyncRequestFocusableScope();
    focusHub->parentFocusable_ = false;
    EXPECT_FALSE(focusHub->IsSyncRequestFocusableScope());
}

/**
 * @tc.name: LostFocusToViewRoot002
 * @tc.desc: Test the function LostFocusToViewRoot.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostFocusToViewRoot002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct all kinds of FocusView.
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(rootNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    auto bubblePattern = AceType::MakeRefPtr<BubblePattern>();
    auto bubbleNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, -1, bubblePattern);
    auto bubbleFocusHub = bubbleNode->GetOrCreateFocusHub();
    rootNode->AddChild(bubbleNode);

    auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
    auto dialogNode = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, -1, dialogPattern);
    auto dialogFocusHub = dialogNode->GetOrCreateFocusHub();
    rootNode->AddChild(dialogNode);

    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "Menu", MenuType::MENU);
    auto menuNode = FrameNodeOnTree::CreateFrameNode(V2::MENU_ETS_TAG, -1, menuPattern);
    auto menuFocusHub = menuNode->GetOrCreateFocusHub();
    rootNode->AddChild(menuNode);

    auto modalPattern = AceType::MakeRefPtr<ModalPresentationPattern>(-1, ModalTransition::DEFAULT, nullptr);
    auto modalNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPattern);
    auto modalFocusHub = modalNode->GetOrCreateFocusHub();
    rootNode->AddChild(modalNode);

    auto sheetPattern = AceType::MakeRefPtr<SheetPresentationPattern>(-1, "", nullptr);
    auto sheetNode = FrameNodeOnTree::CreateFrameNode(V2::SHEET_PAGE_TAG, -1, sheetPattern);
    auto sheetFocusHub = sheetNode->GetOrCreateFocusHub();
    rootNode->AddChild(sheetNode);

    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto navigationNode = FrameNodeOnTree::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, -1, navigationPattern);
    auto navigationFocusHub = navigationNode->GetOrCreateFocusHub();

    auto navbarPattern = AceType::MakeRefPtr<NavBarPattern>();
    auto navbarNode = FrameNodeOnTree::CreateFrameNode(V2::NAVBAR_ETS_TAG, -1, navbarPattern);
    auto navbarFocusHub = navbarNode->GetOrCreateFocusHub();

    auto navdestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>(nullptr);
    auto navdestinationNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, -1, navdestinationPattern);
    auto navdestinationFocusHub = navdestinationNode->GetOrCreateFocusHub();

    pageNode->AddChild(navigationNode);
    navigationNode->AddChild(navbarNode);
    navigationNode->AddChild(navdestinationNode);
    pagePattern->FocusViewShow();
    focusHub->LostFocusToViewRoot();
    EXPECT_NE(FocusView::GetCurrentFocusView(), nullptr);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test the function ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, ToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct all kinds of FocusView.
     */
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(rootNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    focusHub->ToJsonValue(focusHub, json, filter);
}

/**
 * @tc.name: RemoveChild001
 * @tc.desc: Test the function RemoveChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RemoveChild001, TestSize.Level1)
{
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(rootNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    focusHub->RemoveChild(focusHub, BlurReason::FOCUS_SWITCH);
}

/**
 * @tc.name: OnKeyEventNode001
 * @tc.desc: Test the function OnKeyEventNode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, OnKeyEventNode001, TestSize.Level1)
{
    auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(rootNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SPACE;
    keyEvent.isRedispatch = false;
    keyEvent.isPreIme = true;

    /**
     * @tc.expected: The return value of OnKeyEvent is false.
     * @tc.steps2: call the function OnKeyEvent with FocusType::NODE.
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
 * @tc.name: HasBackwardFocusMovementInChildren002
 * @tc.desc: Test the function HasBackwardFocusMovementInChildren.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HasBackwardFocusMovementInChildren002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode and add button as its children which focus type is enable.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    /**
     * @tc.steps: step2. Create FocusHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    EXPECT_FALSE(focusHub->HasForwardFocusMovementInChildren());
    EXPECT_FALSE(focusHub->HasBackwardFocusMovementInChildren());
    focusHub->ClearFocusMovementFlagsInChildren();
}

/**
 * @tc.name: FocusHubTestNgtest001
 * @tc.desc: Test the function DumpFocusNodeTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    DumpLog::GetInstance().ostream_.reset();
    focusHub->DumpFocusNodeTree(15);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest002
 * @tc.desc: Test the function DumpFocusNodeTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest002, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE, true);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    auto ss = std::make_unique<std::ostringstream>();
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    eventHub->enabled_ = true;
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    bool result = true;
    focusHub->DumpFocusNodeTree(1);
    focusHub->focusScopeId_ = "abc";
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->DumpFocusNodeTree(1);
    focusHub->focusPriority_ = FocusPriority::PREVIOUS;
    focusHub->DumpFocusNodeTree(1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest003
 * @tc.desc: Test the function DumpFocusScopeTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest003, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    DumpLog::GetInstance().ostream_.reset();
    focusHub->DumpFocusScopeTree(15);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest004
 * @tc.desc: Test the function DumpFocusScopeTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest004, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE, true);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    auto ss = std::make_unique<std::ostringstream>();
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    eventHub->enabled_ = true;
    DumpLog::GetInstance().SetDumpFile(std::move(ss));
    bool result = true;
    focusHub->DumpFocusScopeTree(1);
    focusHub->isFocusScope_ = true;
    focusHub->DumpFocusScopeTree(1);
    focusHub->focusScopeId_ = "abc";
    focusHub->focusPriority_ = FocusPriority::PRIOR;
    focusHub->DumpFocusScopeTree(1);
    focusHub->focusPriority_ = FocusPriority::PREVIOUS;
    focusHub->DumpFocusScopeTree(1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest005
 * @tc.desc: Test the function RequestFocusImmediately.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest005, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    context->isFocusingByTab_ = false;
    focusHub->currentFocus_ = false;
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    eventHub->enabled_ = true;
    focusHub->onPreFocusCallback_ = []() {};
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE, true);
    bool result = true;
    focusHub->RequestFocusImmediately();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest006
 * @tc.desc: Test the function IsSyncRequestFocusableScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest006, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    eventHub->enabled_ = false;
    focusHub->IsSyncRequestFocusableScope();
    eventHub->enabled_ = true;
    focusHub->IsSyncRequestFocusableScope();
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE, true);
    focusHub->IsSyncRequestFocusableScope();
    frameNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE, true);
    focusHub->focusable_ = false;
    focusHub->IsSyncRequestFocusableScope();
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = false;
    focusHub->IsSyncRequestFocusableScope();
    focusHub->parentFocusable_ = true;
    focusHub->IsSyncRequestFocusableScope();
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->IsSyncRequestFocusableScope();
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->IsSyncRequestFocusableScope();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest008
 * @tc.desc: Test the function OnKeyPreIme.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest008, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::BLANK_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    KeyEvent keyEvent;
    auto info = KeyEventInfo(keyEvent);
    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->OnKeyPreIme(info, keyEvent);
    OnKeyConsumeFunc onKeyCallback = [](KeyEventInfo& event) -> bool { return true; };
    focusHub->SetOnKeyPreIme(std::move(onKeyCallback));
    focusHub->OnKeyPreIme(info, keyEvent);
    EXPECT_TRUE(result);
}
/**
 * @tc.name: FocusHubTestNgtest009
 * @tc.desc: Test the function OnKeyPreIme.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest009, TestSize.Level1)
{
    auto frameNode =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::EMBEDDED_COMPONENT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::EMBEDDED_COMPONENT_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    KeyEvent keyEvent;
    auto info = KeyEventInfo(keyEvent);
    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->OnKeyPreIme(info, keyEvent);
    EXPECT_TRUE(result);
}
/**
 * @tc.name: FocusHubTestNgtest010
 * @tc.desc: Test the function OnKeyPreIme.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest010, TestSize.Level1)
{
    auto frameNode =
        AceType::MakeRefPtr<FrameNodeOnTree>(V2::UI_EXTENSION_COMPONENT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto nodeParent = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, -1, AceType::MakeRefPtr<FlexLayoutPattern>());
    ASSERT_NE(nodeParent, nullptr);
    frameNode->GetOrCreateFocusHub();
    nodeParent->GetOrCreateFocusHub();
    frameNode->SetParent(nodeParent);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    KeyEvent keyEvent;
    auto info = KeyEventInfo(keyEvent);
    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->OnKeyPreIme(info, keyEvent);
    EXPECT_TRUE(result);
}
/**
 * @tc.name: FocusHubTestNgtest011
 * @tc.desc: Test the function OnKeyEventScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest011, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode2, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub1, nullptr);
    eventHub->AttachHost(frameNode2);
    eventHub1->AttachHost(frameNode1);
    frameNode->SetParent(frameNode1);
    frameNode1->SetParent(frameNode2);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub1);
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
    keyEvent.code = KeyCode::TV_CONTROL_UP;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::TV_CONTROL_DOWN;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::TV_CONTROL_LEFT;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::TV_CONTROL_RIGHT;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::KEY_TAB;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::KEY_MOVE_HOME;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::KEY_MOVE_END;
    focusHub->HandleEvent(keyEvent);
    keyEvent.code = KeyCode::KEY_MEDIA_PLAY;
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: FocusHubTestNgtest012
 * @tc.desc: Test the function DumpFocusScopeTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest012, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetOrCreateFocusHub();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_HOME);
    FocusEvent focusEvent(keyEvent);
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    MockContainer::SetUp();
    MockContainer::Current()->isDynamicRender_ = true;
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    auto* context = frameNode->GetContext();
    context->focusWindowId_ = 1;
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    MockContainer::Current()->isDynamicRender_ = false;
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    context->focusWindowId_.reset();
    MockContainer::TearDown();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest013
 * @tc.desc: Test the function DumpFocusScopeTree.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest013, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetOrCreateFocusHub();
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    bool result = true;
    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_TAB);
    FocusEvent focusEvent(keyEvent);
    auto* context = frameNode->GetContext();
    context->focusWindowId_.reset();
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    MockContainer::SetUp();
    MockContainer::Current()->isDynamicRender_ = true;
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    context->focusWindowId_ = 1;
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    MockContainer::Current()->isDynamicRender_ = false;
    focusHub->RequestNextFocusOfKeyTab(focusEvent);
    context->focusWindowId_.reset();
    MockContainer::TearDown();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest014
 * @tc.desc: Test the function SwitchFocus.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest014, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub2, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    bool result = false;
    focusHub->SwitchFocus(focusHub2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusHubTestNgtest015
 * @tc.desc: Test the function FocusToHeadOrTailChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest015, TestSize.Level1)
{
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode1);
    frameNode->GetOrCreateFocusHub();
    frameNode1->GetOrCreateFocusHub();
    frameNode->SetParent(frameNode1);
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto focusHub1 = frameNode1->GetFocusHub();
    focusHub->isGroup_ = true;
    focusHub->focusType_ = FocusType::NODE;
    focusHub1->focusType_ = FocusType::NODE;
    focusHub1->focusable_ = true;
    focusHub1->parentFocusable_ = true;
    eventHub->enabled_ = true;
    frameNode1->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE, true);
    focusHub1->isGroup_ = true;
    focusHub->FocusToHeadOrTailChild(true);
    focusHub1->focusType_ = FocusType::SCOPE;
    auto res = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_TRUE(res);
    ;
}

/**
 * @tc.name: FocusHubTestNgtest016
 * @tc.desc: Test the function CalculatePosition.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest016, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode2, nullptr);
    auto frameNode3 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode3, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHub1 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub1, nullptr);
    eventHub->AttachHost(frameNode2);
    eventHub1->AttachHost(frameNode1);

    frameNode->SetParent(frameNode1);
    frameNode1->SetParent(frameNode2);
    frameNode3->AddChild(frameNode2);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub1);
    KeyEvent keyEvent;
    bool result = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    auto itNewFocusNode = focusHub->FlushChildrenFocusHub(focusNodes);
    EXPECT_EQ(itNewFocusNode, focusNodes.end());
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    auto pipeline = PipelineContext::GetCurrentContext();
    focusHub->focusType_ = FocusType::NODE;
    focusHub1->focusType_ = FocusType::NODE;
    focusHub->CalculatePosition();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest017
 * @tc.desc: Test the function OnFocusScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest017, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child2, nullptr);
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub2, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub2);
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    bool result = false;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->focusScopeId_ = "123";
    focusHub->isFocusScope_ = true;
    focusHub->currentFocus_ = true;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    auto lastFocusNode = focusHub->lastWeakFocusNode_.Upgrade();
    lastFocusNode->currentFocus_ = true;
    lastFocusNode->focusType_ = FocusType::NODE;
    lastFocusNode->focusCallbackEvents_ = nullptr;
    focusHub->isGroup_ = true;
    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->focusType_ = FocusType::NODE;
    focusHub->OnFocusScope(true);
    focusHub->OnFocusScope(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusHubTestNgtest018
 * @tc.desc: Test the function RequestFocusByPriorityInScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest018, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child2, nullptr);
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub2, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub2);
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    bool result = false;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->RequestFocusByPriorityInScope();
    focusHub->focusScopeId_ = "123";
    focusHub->RequestFocusByPriorityInScope();
    focusHub->isFocusScope_ = true;
    focusHub->focusScopeId_.clear();
    focusHub->RequestFocusByPriorityInScope();
    focusHub->focusScopeId_ = "123";
    focusHub->RequestFocusByPriorityInScope();
    focusHub->currentFocus_ = true;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    auto lastFocusNode = focusHub->lastWeakFocusNode_.Upgrade();
    lastFocusNode->currentFocus_ = true;
    lastFocusNode->focusType_ = FocusType::NODE;
    lastFocusNode->focusCallbackEvents_ = nullptr;
    focusHub->isGroup_ = true;
    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->focusType_ = FocusType::NODE;
    focusHub->RequestFocusByPriorityInScope();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusHubTestNgtest019
 * @tc.desc: Test the function RequestFocusByPriorityInScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest019, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto child = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child2, nullptr);
    child->GetOrCreateFocusHub();
    child2->GetOrCreateFocusHub();
    frameNode->AddChild(child);
    frameNode->AddChild(child2);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub2, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub2);
    focusHub->currentFocus_ = true;
    std::list<RefPtr<FocusHub>> focusNodes;
    bool result = false;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->focusScopeId_ = "123";
    focusHub->isFocusScope_ = true;
    focusHub->currentFocus_ = true;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    auto lastFocusNode = focusHub->lastWeakFocusNode_.Upgrade();
    lastFocusNode->currentFocus_ = true;
    lastFocusNode->focusType_ = FocusType::DISABLE;
    lastFocusNode->focusCallbackEvents_ = nullptr;
    focusHub->isGroup_ = true;
    focusHub->RequestFocusByPriorityInScope();
    lastFocusNode->focusType_ = FocusType::NODE;
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    frameNode1->GetOrCreateFocusHub();
    frameNode->SetParent(frameNode1);
    auto focusHub2 = frameNode1->GetFocusHub();
    focusHub2->focusType_ = FocusType::SCOPE;
    focusHub2->isGroup_ = true;
    focusHub->RequestFocusByPriorityInScope();
    focusHub->isGroup_ = false;
    focusHub->RequestFocusByPriorityInScope();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusHubTestNgtest020
 * @tc.desc: Test the function AcceptFocusOfPriorityChild.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest020, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub);
    bool result = false;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusScopeId_ = "123";
    focusHub->AcceptFocusOfPriorityChild();
    focusHub->isFocusScope_ = true;
    focusHub->AcceptFocusOfPriorityChild();
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    focusHub->AcceptFocusOfPriorityChild();
    focusHub->isGroup_ = true;
    focusHub->AcceptFocusOfPriorityChild();
    auto frameNode1 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode1, nullptr);
    frameNode1->GetOrCreateFocusHub();
    frameNode->SetParent(frameNode1);
    auto focusHub2 = frameNode1->GetFocusHub();
    ASSERT_NE(focusHub2, nullptr);
    focusHub2->focusType_ = FocusType::SCOPE;
    focusHub2->isGroup_ = true;
    focusHub->AcceptFocusOfPriorityChild();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusHubTestNgtest021
 * @tc.desc: Test the function SetLastWeakFocusToPreviousInFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest021, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub, nullptr);
    auto focusHub1 = AceType::MakeRefPtr<FocusHub>(eventHub);
    ASSERT_NE(focusHub1, nullptr);
    bool result = false;
    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub1));
    focusHub->SetLastWeakFocusToPreviousInFocusView();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusHubTestNgtest022
 * @tc.desc: Test the function SetLastWeakFocusToPreviousInFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode.
     */
    auto frameNode =
        FrameNodeOnTree::CreateFrameNode(V2::COLUMN_ETS_TAG, 108, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(frameNode, nullptr);
    auto child = FrameNodeOnTree::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 109, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(child, nullptr);
    auto child2 = FrameNodeOnTree::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, 110, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(child2, nullptr);
    child->MountToParent(frameNode);
    child2->MountToParent(frameNode);

    auto parentFocusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(parentFocusHub, nullptr);
    parentFocusHub->SetFocusScopeId("scope2", true);

    auto child2FocusHub = child2->GetOrCreateFocusHub();
    ASSERT_NE(child2FocusHub, nullptr);
    child2FocusHub->SetFocusScopePriority("scope2", 2000);

    auto childFocusHub = child->GetOrCreateFocusHub();
    ASSERT_NE(childFocusHub, nullptr);
    childFocusHub->SetFocusScopePriority("scope2", 3000);

    EXPECT_TRUE(parentFocusHub->AcceptFocusOfPriorityChild());
    parentFocusHub->SetLastWeakFocusToPreviousInFocusView();
}

/**
 * @tc.name: FocusHubTestNgtest023
 * @tc.desc: Test the function IsFocusAbleChildOf.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest023, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto frameNodeFir = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeFir, nullptr);
    auto frameNodeSec = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeSec, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHubFir = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHubFir, nullptr);
    eventHub->AttachHost(frameNode);
    eventHubFir->AttachHost(frameNodeFir);
    frameNode->eventHub_ = eventHub;
    frameNodeFir->eventHub_ = eventHubFir;
    frameNode->MountToParent(frameNodeFir);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    auto focusHubFir = frameNodeFir->GetOrCreateFocusHub();
    auto focusHubSec = frameNodeSec->GetOrCreateFocusHub();
    bool result = true;
    focusHubFir->focusType_ = FocusType::SCOPE;
    focusHubFir->SetFocusScopeId("scope2", true);
    focusHub->SetFocusScopePriority("scope2", 2000);
    focusHub->IsFocusAbleChildOf(focusHubFir);
    focusHub->IsFocusAbleChildOf(focusHubSec);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest024
 * @tc.desc: Test the function SetLastWeakFocusNodeWholeScope.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest024, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto frameNodeFir = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeFir, nullptr);
    auto frameNodeSec = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeSec, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto eventHubFir = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHubFir, nullptr);
    eventHub->AttachHost(frameNode);
    eventHubFir->AttachHost(frameNodeFir);
    frameNode->eventHub_ = eventHub;
    frameNodeFir->eventHub_ = eventHubFir;
    frameNode->MountToParent(frameNodeFir);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    auto focusHubFir = frameNodeFir->GetOrCreateFocusHub();
    auto focusHubSec = frameNodeSec->GetOrCreateFocusHub();
    bool result = true;
    focusHubFir->focusType_ = FocusType::SCOPE;
    focusHubFir->SetFocusScopeId("scope2", true);
    focusHub->SetFocusScopePriority("scope2", 2000);
    focusHub->SetLastWeakFocusNodeWholeScope("scope2");
    focusHub->SetLastWeakFocusNodeWholeScope("scope");
    focusHubFir->isFocusScope_ = false;
    focusHub->SetLastWeakFocusNodeWholeScope("scope");
    focusHub->SetLastWeakFocusNodeWholeScope("scope2");
    focusHubSec->SetLastWeakFocusNodeWholeScope("scope2");
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest025
 * @tc.desc: Test the function SetFocusScopePriority.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest025, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    frameNode->eventHub_ = eventHub;
    auto focusHub = frameNode->GetOrCreateFocusHub();
    bool result = true;
    focusHub->focusScopeId_ = "123";
    focusHub->SetFocusScopePriority("", 2000);
    focusHub->focusScopeId_ = "123";
    focusHub->SetFocusScopePriority("scope2", 2000);
    focusHub->focusScopeId_.clear();
    focusHub->SetFocusScopePriority("scope2", 3000);
    focusHub->SetFocusScopePriority("scope2", 0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest026
 * @tc.desc: Test the function IsInFocusGroup.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest026, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->AttachHost(frameNode);
    frameNode->eventHub_ = eventHub;
    auto focusHub = frameNode->GetOrCreateFocusHub();
    bool result = true;
    focusHub->isGroup_ = true;
    focusHub->IsInFocusGroup();
    auto frameNodeFir = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNodeFir, nullptr);
    frameNodeFir->GetOrCreateFocusHub();
    frameNode->SetParent(frameNodeFir);
    auto focusHubSec = frameNodeFir->GetFocusHub();
    ASSERT_NE(focusHubSec, nullptr);
    focusHubSec->focusType_ = FocusType::SCOPE;
    focusHubSec->isGroup_ = true;
    focusHub->IsInFocusGroup();
    focusHub->isGroup_ = false;
    focusHub->IsInFocusGroup();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FocusHubTestNgtest027
 * @tc.desc: Test the function ScrollByOffsetToParent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest027, TestSize.Level1)
{
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 102, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto listNode = FrameNodeOnTree::CreateFrameNode("frameNode", 104, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    listNode->GetOrCreateFocusHub();
    auto listFocusHub = listNode->GetFocusHub();
    ASSERT_NE(listFocusHub, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    auto mockRenderContextSec = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContextSec, nullptr);
    mockRenderContextSec->rect_ = RectF(10, 3, 2, 2);
    frameNode->renderContext_ = mockRenderContextSec;
    listNode->renderContext_ = mockRenderContext;
    mockRenderContext->rect_ = RectF(10, 5, 10, 10);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    frameNode->geometryNode_->SetFrameSize(SizeF(2, 2));
    listNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    listNode->geometryNode_->SetFrameSize(SizeF(10, 10));

    ASSERT_TRUE(focusHub->ScrollByOffsetToParent(listNode));
}

/**
 * @tc.name: FocusHubTestNgtest028
 * @tc.desc: Test the function ScrollByOffsetToParent.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, FocusHubTestNgtest028, TestSize.Level1)
{
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 102, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto listNode = FrameNodeOnTree::CreateFrameNode("frameNode", 104, AceType::MakeRefPtr<ListPattern>());
    ASSERT_NE(listNode, nullptr);
    listNode->GetOrCreateFocusHub();
    auto listFocusHub = listNode->GetFocusHub();
    ASSERT_NE(listFocusHub, nullptr);
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    auto mockRenderContext2 = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext2, nullptr);
    mockRenderContext2->rect_ = RectF(10, -5, 5, 5);
    frameNode->renderContext_ = mockRenderContext2;
    listNode->renderContext_ = mockRenderContext;
    mockRenderContext->rect_ = RectF(10, 10, 15, 15);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    frameNode->geometryNode_->SetFrameSize(SizeF(5, 5));
    listNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    listNode->geometryNode_->SetFrameSize(SizeF(15, 15));
    ASSERT_TRUE(focusHub->ScrollByOffsetToParent(listNode));
    frameNode->geometryNode_->SetFrameSize(SizeF(25, 25));
    EXPECT_FALSE(focusHub->ScrollByOffsetToParent(listNode));
}

/**
 * @tc.name: GetUnicodeTest001
 * @tc.desc: Test GetUnicode.
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetUnicodeTest001, TestSize.Level1)
{
    KeyEvent keyEvent;
    auto defaultInfo = KeyEventInfo(keyEvent);
    /**
     * @tc.steps: step1. Get the default unicode.
     * @tc.expected: default unicode is 0.
     */
    EXPECT_EQ(defaultInfo.GetUnicode(), 0);

    /**
     * @tc.steps: step2. Set the Unicode value to 98.
     * @tc.expected: get unicode value is 98.
     */
    keyEvent.unicode = 98;
    auto info = KeyEventInfo(keyEvent);
    EXPECT_EQ(info.GetUnicode(), 98);
}
} // namespace OHOS::Ace::NG
