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
 * @tc.name: IsCurrentFocusWholePathBranch01
 * @tc.desc: Test IsCurrentFocusWholePath when currentFocus_ is true and focusType_ is NODE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsCurrentFocusWholePathBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with currentFocus_=true and focusType_=NODE
     * @tc.expected: Should return true when focusType_ is NODE and currentFocus_ is true
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set currentFocus_ to true and focusType_ to NODE
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::NODE;

    // @tc.steps: step3. Verify that IsCurrentFocusWholePath returns true for NODE type
    EXPECT_TRUE(focusHub->IsCurrentFocusWholePath());
}

/**
 * @tc.name: IsCurrentFocusWholePathBranch02
 * @tc.desc: Test IsCurrentFocusWholePath when focusType_ is SCOPE, focusDepend_ is SELF, and currentFocus_ is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsCurrentFocusWholePathBranch02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with currentFocus_=true and focusType_=SCOPE
     * @tc.expected: Should return true when focusDepend_ is SELF and currentFocus_ is true
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set currentFocus_ to true, focusType_ to SCOPE, and focusDepend_ to SELF
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::SELF;

    // @tc.steps: step3. Verify that IsCurrentFocusWholePath returns true when focusDepend_ is SELF
    EXPECT_TRUE(focusHub->IsCurrentFocusWholePath());
}

/**
 * @tc.name: IsSyncRequestFocusableScopeBranch01
 * @tc.desc: Test IsSyncRequestFocusableScope when focusDepend_ is SELF
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsSyncRequestFocusableScopeBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with focusType_=SCOPE and focusDepend_=SELF
     * @tc.expected: Should return true when focusDepend_ is SELF and IsSyncRequestFocusableNode returns true
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set focusType_ to SCOPE and focusDepend_ to SELF
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->currentFocus_ = true;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;

    // @tc.steps: step3. Verify that IsSyncRequestFocusableScope returns true when focusDepend_ is SELF
    EXPECT_TRUE(focusHub->IsSyncRequestFocusableScope());
}

/**
 * @tc.name: IsSyncRequestFocusableScopeBranch02
 * @tc.desc: Test IsSyncRequestFocusableScope when focusDepend_ is AUTO and has focusable children
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsSyncRequestFocusableScopeBranch02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a parent FocusHub with focusType_=SCOPE and focusDepend_=AUTO
     * @tc.expected: Should return true when focusDepend_ is AUTO and has focusable children
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set focusType_ to SCOPE and focusDepend_ to AUTO
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->currentFocus_ = true;

    // @tc.steps: step3. Add a focusable child node
    auto childNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    childNode->GetOrCreateFocusHub();
    auto childFocusHub = childNode->GetFocusHub();
    childFocusHub->focusable_ = true;
    childFocusHub->parentFocusable_ = true;
    frameNode->AddChild(childNode);

    // @tc.steps: step4. Verify that IsSyncRequestFocusableScope returns true when has focusable children
    EXPECT_TRUE(focusHub->IsSyncRequestFocusableScope());
}

/**
 * @tc.name: IsFocusableScopeBranch01
 * @tc.desc: Test IsFocusableScope when focusDepend_ is SELF
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsFocusableScopeBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with focusType_=SCOPE and focusDepend_=SELF
     * @tc.expected: Should return true when focusDepend_ is SELF
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set focusType_ to SCOPE, focusDepend_ to SELF, and set focusable properties
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;

    // @tc.steps: step3. Verify that IsFocusableScope returns true when focusDepend_ is SELF
    EXPECT_TRUE(focusHub->IsFocusableScope());
}

/**
 * @tc.name: IsFocusableScopeBranch02
 * @tc.desc: Test IsFocusableScope when focusDepend_ is AUTO and has focusable children
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, IsFocusableScopeBranch02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a parent FocusHub with focusType_=SCOPE and focusDepend_=AUTO
     * @tc.expected: Should return true when focusDepend_ is AUTO and has focusable children
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set focusType_ to SCOPE, focusDepend_ to AUTO, and set focusable properties
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;

    // @tc.steps: step3. Add a focusable child node
    auto childNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    childNode->GetOrCreateFocusHub();
    auto childFocusHub = childNode->GetFocusHub();
    childFocusHub->focusable_ = true;
    childFocusHub->parentFocusable_ = true;
    frameNode->AddChild(childNode);

    // @tc.steps: step4. Verify that IsFocusableScope returns true when has focusable children
    EXPECT_TRUE(focusHub->IsFocusableScope());
}

/**
 * @tc.name: RemoveSelfBranch01
 * @tc.desc: Test RemoveSelf when IsCurrentFocus returns true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RemoveSelfBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with currentFocus_=true
     * @tc.expected: Should enter the LostFocus branch when IsCurrentFocus is true
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set currentFocus_ to true
    focusHub->currentFocus_ = true;

    // @tc.steps: step3. Call RemoveSelf and verify it handles the current focus case
    focusHub->RemoveSelf(BlurReason::FOCUS_SWITCH);

    // @tc.steps: step4. Verify that currentFocus_ is set to false after RemoveSelf
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: SetFocusableBranch01
 * @tc.desc: Test SetFocusable when isExplicit is false and focusable_ is different from focusable
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetFocusableBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with focusable_=true
     * @tc.expected: Should update focusable_ when isExplicit is false and values are different
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set initial focusable_ to true
    focusHub->focusable_ = true;

    // @tc.steps: step3. Call SetFocusable with isExplicit=false and focusable=false
    focusHub->SetFocusable(false, false);

    // @tc.steps: step4. Verify that focusable_ is updated to false
    EXPECT_FALSE(focusHub->focusable_);
}

/**
 * @tc.name: SetFocusableBranch02
 * @tc.desc: Test SetFocusable when isExplicit is true and isFocusableExplicit_ is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetFocusableBranch02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with isFocusableExplicit_=true
     * @tc.expected: Should return early when isExplicit is true and isFocusableExplicit_ is true
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set isFocusableExplicit_ to true
    focusHub->isFocusableExplicit_ = true;

    // @tc.steps: step3. Call SetFocusable with isExplicit=true
    auto initialFocusable = focusHub->focusable_;
    focusHub->SetFocusable(false, true);

    // @tc.steps: step4. Verify that focusable_ is not changed due to early return
    EXPECT_EQ(focusHub->focusable_, initialFocusable);
}

/**
 * @tc.name: SetFocusableBranch03
 * @tc.desc: Test SetFocusable when IsImplicitFocusableScope is true and focusDepend_ is CHILD
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetFocusableBranch03, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with focusDepend_=CHILD
     * @tc.expected: Should update focusDepend_ to AUTO when IsImplicitFocusableScope is true
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    // @tc.steps: step2. Set up the scenario for IsImplicitFocusableScope
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->currentFocus_ = true;
    focusHub->focusable_ = true;

    // @tc.steps: step3. Call SetFocusable with isExplicit=false
    focusHub->SetFocusable(true, false);

    // @tc.steps: step4. Verify that focusDepend_ is updated to AUTO
    EXPECT_EQ(focusHub->focusDepend_, FocusDependence::AUTO);
}

/**
 * @tc.name: GetRootFocusHubBranch01
 * @tc.desc: Test GetRootFocusHub when FocusHub is already a root
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, GetRootFocusHubBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub without parent
     * @tc.expected: Should return itself when it has no parent
     */
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));

    /**
     * @tc.steps: step2. Call GetRootFocusHub on a node without parent
     * @tc.expected: Should return itself since it has no parent
     */
    auto rootFocusHub = focusHub->GetRootFocusHub();
    EXPECT_EQ(rootFocusHub, focusHub);
}

/**
 * @tc.name: HandleFocusNavigationBranch01
 * @tc.desc: Test HandleFocusNavigation when lastFocusNode exists and is current focus
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, HandleFocusNavigationBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub with lastWeakFocusNode_
     * @tc.expected: Should delegate to lastFocusNode's HandleFocusNavigation
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode2->GetOrCreateFocusHub();
    auto focusHub2 = frameNode2->GetFocusHub();
    ASSERT_NE(focusHub2, nullptr);
    focusHub2->currentFocus_ = true;

    focusHub->lastWeakFocusNode_ = AceType::WeakClaim(AceType::RawPtr(focusHub2));

    KeyEvent keyEvent;
    keyEvent.pressedCodes.emplace_back(KeyCode::KEY_TAB);
    FocusEvent focusEvent(keyEvent);
    focusEvent.intension = FocusIntension::TAB;

    /**
     * @tc.steps: step2. Call HandleFocusNavigation
     * @tc.expected: Should delegate to lastFocusNode's HandleFocusNavigation
     */
    auto ret = focusHub->HandleFocusNavigation(focusEvent);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: RequestNextFocusByCustomAlgorithmBranch01
 * @tc.desc: Test RequestNextFocusByCustomAlgorithm when no nextFocusNode is found
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, RequestNextFocusByCustomAlgorithmBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusHub and set up custom focus algorithm
     * @tc.expected: Should return false when custom algorithm returns null
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Set up OnGetNextFocusNodeFunc to return null
     */
    focusHub->SetOnGetNextFocusNodeFunc(
        [](FocusReason reason, const FocusIntension& intension) -> RefPtr<FocusHub> {
            return nullptr;
        });

    /**
     * @tc.steps: step3. Set up required state for RequestNextFocusByCustomAlgorithm
     */
    std::list<RefPtr<FocusHub>> focusNodes;
    focusHub->FlushChildrenFocusHub(focusNodes);

    FocusStep moveStep = FocusStep::LEFT;
    auto frameOffset = frameNode->GetTransformRelativeOffset();
    auto geometryNode = frameNode->GetGeometryNode();
    RectF frameRect = RectF(frameOffset, geometryNode->GetFrameRect().GetSize());

    /**
     * @tc.steps: step4. Call RequestNextFocusByCustomAlgorithm
     * @tc.expected: Should return false when OnGetNextFocusNodeFunc returns null
     */
    auto ret = focusHub->RequestNextFocusByCustomAlgorithm(moveStep, frameRect);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: LostFocusToViewRootBranch01
 * @tc.desc: Test LostFocusToViewRoot when focusHub has currentFocus set to true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, LostFocusToViewRootBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with currentFocus_=true
     * @tc.expected: Should set currentFocus_ to false after calling LostFocusToViewRoot
     */
    auto frameNode = FrameNodeOnTree::CreateFrameNode("frameNode", 101, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    focusHub->currentFocus_ = true;

    /**
     * @tc.steps: step2. Call LostFocusToViewRoot to increase coverage
     */
    focusHub->LostFocusToViewRoot();

    /**
     * @tc.steps: step3. Verify that currentFocus_ is set to false
     */
    ASSERT_TRUE(focusHub->currentFocus_ == false);
}

/**
 * @tc.name: SetIsFocusOnTouchBranch01
 * @tc.desc: Test SetIsFocusOnTouch when focusOnTouch is different from current value
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetIsFocusOnTouchBranch01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub
     * @tc.expected: Should update isFocusOnTouch when value is different
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Create FocusCallbackEvents
     */
    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();

    /**
     * @tc.steps: step3. Set isFocusOnTouch to true when it's currently false or unset
     */
    focusHub->SetIsFocusOnTouch(true);

    /**
     * @tc.steps: step4. Verify that isFocusOnTouch_ is set to true
     */
    EXPECT_TRUE(focusHub->focusCallbackEvents_->isFocusOnTouch_.has_value());
    EXPECT_TRUE(focusHub->focusCallbackEvents_->isFocusOnTouch_.value());
}

/**
 * @tc.name: SetIsFocusOnTouchBranch02
 * @tc.desc: Test SetIsFocusOnTouch when isFocusOnTouch is already set to the same value
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, SetIsFocusOnTouchBranch02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FocusHub with isFocusOnTouch already set to true
     * @tc.expected: Should return early when isFocusOnTouch is already set to the same value
     */
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Create FocusCallbackEvents and set isFocusOnTouch_ to true
     */
    focusHub->focusCallbackEvents_ = AceType::MakeRefPtr<FocusCallbackEvents>();
    focusHub->focusCallbackEvents_->isFocusOnTouch_ = true;

    /**
     * @tc.steps: step3. Set isFocusOnTouch to true again
     * @tc.expected: Should return early without changes
     */
    auto initialIsFocusOnTouch = focusHub->focusCallbackEvents_->isFocusOnTouch_;
    focusHub->SetIsFocusOnTouch(true);

    /**
     * @tc.steps: step4. Verify that isFocusOnTouch_ is unchanged
     */
    EXPECT_EQ(focusHub->focusCallbackEvents_->isFocusOnTouch_, initialIsFocusOnTouch);
}

} // namespace OHOS::Ace::NG
