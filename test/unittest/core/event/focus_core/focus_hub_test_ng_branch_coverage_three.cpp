/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

/**
 * @tc.name: FocusPatternCopyConstructor001
 * @tc.desc: Test FocusPattern copy constructor copies all fields
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3FocusPatternCopyConstructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusPattern with all fields set
     * @tc.expected: Copy constructor copies all fields correctly
     */
    FocusPaintParam paintParam;
    paintParam.SetPaintRect(RoundRect(RectF(1, 2, 3, 4), 0.0f, 0.0f));
    paintParam.SetPaintColor(Color(0xFF000000));
    paintParam.SetPaintWidth(Dimension(2.0));
    paintParam.SetFocusPadding(Dimension(1.0));
    FocusPattern original(FocusType::NODE, true, FocusStyleType::OUTER_BORDER, paintParam);
    original.SetIsFocusActiveWhenFocused(true);
    FocusPattern copied(original);
    EXPECT_EQ(copied.GetFocusType(), FocusType::NODE);
    EXPECT_EQ(copied.GetFocusable(), true);
    EXPECT_EQ(copied.GetStyleType(), FocusStyleType::OUTER_BORDER);
    EXPECT_EQ(copied.GetIsFocusActiveWhenFocused(), true);
    EXPECT_NE(copied.GetFocusPaintParams(), nullptr);
}

/**
 * @tc.name: FocusPatternCopyConstructorNullPaint001
 * @tc.desc: Test FocusPattern copy constructor when paint params are null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3FocusPatternCopyConstructorNullPaint001, TestSize.Level1)
{
    FocusPattern original(FocusType::SCOPE, false);
    FocusPattern copied(original);
    EXPECT_EQ(copied.GetFocusType(), FocusType::SCOPE);
    EXPECT_EQ(copied.GetFocusable(), false);
    EXPECT_EQ(copied.GetFocusPaintParams(), nullptr);
}

/**
 * @tc.name: FocusHubConstructorWithFocusPattern001
 * @tc.desc: Test FocusHub constructor with FocusPattern via EventHub
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3FocusHubConstructorWithFocusPattern001, TestSize.Level1)
{
    FocusPaintParam paintParam;
    paintParam.SetPaintColor(Color(0xFF00FF00));
    FocusPattern pattern(FocusType::NODE, true, FocusStyleType::INNER_BORDER, paintParam);
    pattern.SetIsFocusActiveWhenFocused(true);
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHub)), pattern);
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->focusable_, true);
    EXPECT_EQ(focusHub->focusType_, FocusType::NODE);
    EXPECT_EQ(focusHub->focusStyleType_, FocusStyleType::INNER_BORDER);
    EXPECT_EQ(focusHub->isFocusActiveWhenFocused_, true);
}

/**
 * @tc.name: SetFocusPaintParamsPtrNullParam001
 * @tc.desc: Test SetFocusPaintParamsPtr when paramsPtr is null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusPaintParamsPtrNullParam001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusPaintParamsPtr(nullptr);
    EXPECT_EQ(focusHub->focusPaintParamsPtr_, nullptr);
}

/**
 * @tc.name: SetFocusPaintParamsPtrFirstTime001
 * @tc.desc: Test SetFocusPaintParamsPtr when focusPaintParamsPtr_ is null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusPaintParamsPtrFirstTime001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->focusPaintParamsPtr_, nullptr);
    auto paintParam = std::make_unique<FocusPaintParam>();
    paintParam->SetPaintRect(RoundRect(RectF(10, 20, 30, 40), 0.0f, 0.0f));
    focusHub->SetFocusPaintParamsPtr(paintParam);
    EXPECT_NE(focusHub->focusPaintParamsPtr_, nullptr);
    EXPECT_TRUE(focusHub->HasPaintRect());
}

/**
 * @tc.name: SetFocusPaintParamsPtrExisting001
 * @tc.desc: Test SetFocusPaintParamsPtr when focusPaintParamsPtr_ exists
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusPaintParamsPtrExisting001, TestSize.Level1)
{
    FocusPaintParam paintParam;
    paintParam.SetPaintColor(Color(0xFF000000));
    FocusPattern pattern(FocusType::NODE, true, FocusStyleType::OUTER_BORDER, paintParam);
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHub)), pattern);
    ASSERT_NE(focusHub, nullptr);
    EXPECT_NE(focusHub->focusPaintParamsPtr_, nullptr);
    auto newPaintParam = std::make_unique<FocusPaintParam>();
    newPaintParam->SetPaintColor(Color(0x00FF0000));
    focusHub->SetFocusPaintParamsPtr(newPaintParam);
    EXPECT_NE(focusHub->focusPaintParamsPtr_, nullptr);
    EXPECT_TRUE(focusHub->HasPaintColor());
}

/**
 * @tc.name: SetFocusTypeToDisable001
 * @tc.desc: Test SetFocusType when type is DISABLE and focusType_ differs
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusTypeToDisable001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->currentFocus_ = true;
    focusHub->SetFocusType(FocusType::DISABLE);
    EXPECT_EQ(focusHub->focusType_, FocusType::DISABLE);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: SetFocusTypeSameValue001
 * @tc.desc: Test SetFocusType when type is same as current
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusTypeSameValue001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->currentFocus_ = true;
    focusHub->SetFocusType(FocusType::NODE);
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: SetFocusTypeImplicitChildToAuto001
 * @tc.desc: Test SetFocusType with implicit scope and CHILD to AUTO
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusTypeImplicitChildToAuto001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusable_ = true;
    focusHub->implicitFocusable_ = true;
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->SetFocusType(FocusType::SCOPE);
    EXPECT_EQ(focusHub->focusDepend_, FocusDependence::AUTO);
}

/**
 * @tc.name: SetPaintRectWhenNull001
 * @tc.desc: Test SetPaintRect when focusPaintParamsPtr_ is null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetPaintRectWhenNull001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetPaintRect(RoundRect(RectF(5, 10, 15, 20), 0.0f, 0.0f));
    EXPECT_NE(focusHub->focusPaintParamsPtr_, nullptr);
    EXPECT_TRUE(focusHub->HasPaintRect());
}

/**
 * @tc.name: SetPaintColorWhenNull001
 * @tc.desc: Test SetPaintColor when focusPaintParamsPtr_ is null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetPaintColorWhenNull001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetPaintColor(Color(0xFF0000FF));
    EXPECT_NE(focusHub->focusPaintParamsPtr_, nullptr);
    EXPECT_TRUE(focusHub->HasPaintColor());
}

/**
 * @tc.name: LostFocusNotCurrent001
 * @tc.desc: Test LostFocus when IsCurrentFocus is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3LostFocusNotCurrent001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    focusHub->blurReason_ = BlurReason::WINDOW_BLUR;
    focusHub->LostFocus(BlurReason::FOCUS_SWITCH);
    EXPECT_EQ(focusHub->blurReason_, BlurReason::WINDOW_BLUR);
}

/**
 * @tc.name: LostFocusCurrent001
 * @tc.desc: Test LostFocus when IsCurrentFocus is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3LostFocusCurrent001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    focusHub->LostFocus(BlurReason::WINDOW_BLUR);
    EXPECT_FALSE(focusHub->currentFocus_);
    EXPECT_EQ(focusHub->blurReason_, BlurReason::WINDOW_BLUR);
}

/**
 * @tc.name: LostSelfFocusCurrent001
 * @tc.desc: Test LostSelfFocus when currently focused
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3LostSelfFocusCurrent001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    focusHub->focusable_ = true;
    focusHub->LostSelfFocus();
    EXPECT_TRUE(focusHub->focusable_);
}

/**
 * @tc.name: LostSelfFocusNotCurrent001
 * @tc.desc: Test LostSelfFocus when not currently focused
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3LostSelfFocusNotCurrent001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    auto initialFocusable = focusHub->focusable_;
    focusHub->LostSelfFocus();
    EXPECT_EQ(focusHub->focusable_, initialFocusable);
}

/**
 * @tc.name: SetParentFocusableFalse001
 * @tc.desc: Test SetParentFocusable when setting to false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetParentFocusableFalse001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetParentFocusable(false);
    EXPECT_FALSE(focusHub->parentFocusable_);
}

/**
 * @tc.name: IsFocusableDisable001
 * @tc.desc: Test IsFocusable when focusType_ is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableDisable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub->IsFocusable());
}

/**
 * @tc.name: IsFocusableNodeNotFocusable001
 * @tc.desc: Test IsFocusableNode when focusable_ is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableNodeNotFocusable001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusable_ = false;
    EXPECT_FALSE(focusHub->IsFocusableNode());
}

/**
 * @tc.name: IsFocusableNodeNotParentFocusable001
 * @tc.desc: Test IsFocusableNode when parentFocusable_ is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableNodeNotParentFocusable001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = false;
    EXPECT_FALSE(focusHub->IsFocusableNode());
}

/**
 * @tc.name: IsFocusableScopeChildWithChild001
 * @tc.desc: Test IsFocusableScope with CHILD depend and focusable child
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableScopeChildWithChild001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    auto childNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    childNode->GetOrCreateFocusHub();
    auto childFocusHub = childNode->GetFocusHub();
    childFocusHub->focusable_ = true;
    childFocusHub->parentFocusable_ = true;
    frameNode->AddChild(childNode);
    EXPECT_TRUE(focusHub->IsFocusableScope());
}

/**
 * @tc.name: IsFocusableScopeChildNoChild001
 * @tc.desc: Test IsFocusableScope with CHILD depend and no focusable children
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableScopeChildNoChild001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_FALSE(focusHub->IsFocusableScope());
}

/**
 * @tc.name: IsChildFocusableDisable001
 * @tc.desc: Test IsChildFocusable when focusType_ is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsChildFocusableDisable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub->IsChildFocusable());
}

/**
 * @tc.name: IsSyncRequestFocusableDisable001
 * @tc.desc: Test IsSyncRequestFocusable when focusType_ is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsSyncRequestFocusableDisable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub->IsSyncRequestFocusable());
}

/**
 * @tc.name: IsEnabledNoHub001
 * @tc.desc: Test IsEnabled when both frameNode_ and eventHub_ are invalid
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsEnabledNoHub001, TestSize.Level1)
{
    auto focusHub = AceType::MakeRefPtr<FocusHub>(WeakPtr<EventHub>(), FocusType::NODE);
    ASSERT_NE(focusHub, nullptr);
    EXPECT_TRUE(focusHub->IsEnabled());
}

/**
 * @tc.name: SetEnabledFalse001
 * @tc.desc: Test SetEnabled with false value triggers RemoveSelf
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetEnabledFalse001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    focusHub->SetEnabled(false);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: SetShowFalse001
 * @tc.desc: Test SetShow with false value triggers RemoveSelf
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetShowFalse001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    focusHub->SetShow(false);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: IsCurrentFocusWholePathDisable001
 * @tc.desc: Test IsCurrentFocusWholePath when focusType_ is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsCurrentFocusWholePathDisable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    focusHub->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub->IsCurrentFocusWholePath());
}

/**
 * @tc.name: IsCurrentFocusWholePathScopeNoLast001
 * @tc.desc: Test IsCurrentFocusWholePath SCOPE CHILD no last focus
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsCurrentFocusWholePathScopeNoLast001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->currentFocus_ = true;
    focusHub->lastWeakFocusNode_ = nullptr;
    EXPECT_FALSE(focusHub->IsCurrentFocusWholePath());
}

/**
 * @tc.name: HasFocusedChildNotCurrent001
 * @tc.desc: Test HasFocusedChild when currentFocus_ is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3HasFocusedChildNotCurrent001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->currentFocus_ = false;
    EXPECT_FALSE(focusHub->HasFocusedChild());
}

/**
 * @tc.name: IsImplicitFocusableScopeTrue001
 * @tc.desc: Test IsImplicitFocusableScope when SCOPE focusable implicit
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsImplicitFocusableScopeTrue001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusable_ = true;
    focusHub->implicitFocusable_ = true;
    EXPECT_TRUE(focusHub->IsImplicitFocusableScope());
    focusHub->implicitFocusable_ = false;
    EXPECT_FALSE(focusHub->IsImplicitFocusableScope());
}

/**
 * @tc.name: IsFocusStepVerticalAndTab001
 * @tc.desc: Test IsFocusStepVertical and IsFocusStepTab static methods
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusStepVerticalAndTab001, TestSize.Level1)
{
    EXPECT_TRUE(FocusHub::IsFocusStepVertical(FocusStep::UP));
    EXPECT_TRUE(FocusHub::IsFocusStepVertical(FocusStep::DOWN));
    EXPECT_FALSE(FocusHub::IsFocusStepVertical(FocusStep::LEFT));
    EXPECT_TRUE(FocusHub::IsFocusStepTab(FocusStep::TAB));
    EXPECT_TRUE(FocusHub::IsFocusStepTab(FocusStep::SHIFT_TAB));
    EXPECT_FALSE(FocusHub::IsFocusStepTab(FocusStep::LEFT));
}

/**
 * @tc.name: IsHomeOrEndStep001
 * @tc.desc: Test IsHomeOrEndStep static method
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsHomeOrEndStep001, TestSize.Level1)
{
    EXPECT_TRUE(FocusHub::IsHomeOrEndStep(FocusStep::UP_END));
    EXPECT_TRUE(FocusHub::IsHomeOrEndStep(FocusStep::DOWN_END));
    EXPECT_TRUE(FocusHub::IsHomeOrEndStep(FocusStep::LEFT_END));
    EXPECT_TRUE(FocusHub::IsHomeOrEndStep(FocusStep::RIGHT_END));
    EXPECT_FALSE(FocusHub::IsHomeOrEndStep(FocusStep::LEFT));
}

/**
 * @tc.name: GetRealFocusStepByTab001
 * @tc.desc: Test GetRealFocusStepByTab for LTR and RTL
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3GetRealFocusStepByTab001, TestSize.Level1)
{
    EXPECT_EQ(FocusHub::GetRealFocusStepByTab(FocusStep::TAB, false), FocusStep::RIGHT);
    EXPECT_EQ(FocusHub::GetRealFocusStepByTab(FocusStep::SHIFT_TAB, false), FocusStep::LEFT);
    EXPECT_EQ(FocusHub::GetRealFocusStepByTab(FocusStep::TAB, true), FocusStep::LEFT);
    EXPECT_EQ(FocusHub::GetRealFocusStepByTab(FocusStep::SHIFT_TAB, true), FocusStep::RIGHT);
}

/**
 * @tc.name: GetProjectAreaOnRect001
 * @tc.desc: Test GetProjectAreaOnRect for directions and no overlap
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3GetProjectAreaOnRect001, TestSize.Level1)
{
    RectF rect(0, 50, 100, 100);
    RectF projectRect(0, 0, 100, 100);
    EXPECT_GT(FocusHub::GetProjectAreaOnRect(rect, projectRect, FocusStep::UP), 0.0);
    EXPECT_GT(FocusHub::GetProjectAreaOnRect(projectRect, rect, FocusStep::DOWN), 0.0);
    EXPECT_GT(FocusHub::GetProjectAreaOnRect(rect, projectRect, FocusStep::LEFT), 0.0);
    EXPECT_GT(FocusHub::GetProjectAreaOnRect(projectRect, rect, FocusStep::RIGHT), 0.0);
    EXPECT_EQ(FocusHub::GetProjectAreaOnRect(rect, projectRect, FocusStep::NONE), 0.0);
    RectF farRect(200, 200, 100, 100);
    EXPECT_EQ(FocusHub::GetProjectAreaOnRect(farRect, projectRect, FocusStep::UP), 0.0);
}

/**
 * @tc.name: IsArrowKeyStepOut001
 * @tc.desc: Test IsArrowKeyStepOut for various conditions
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsArrowKeyStepOut001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->isGroup_ = true;
    focusHub->arrowKeyStepOut_ = false;
    EXPECT_TRUE(focusHub->IsArrowKeyStepOut(FocusStep::LEFT));
    EXPECT_FALSE(focusHub->IsArrowKeyStepOut(FocusStep::TAB));
    focusHub->isGroup_ = false;
    EXPECT_FALSE(focusHub->IsArrowKeyStepOut(FocusStep::LEFT));
}

/**
 * @tc.name: IsFocusStepKey001
 * @tc.desc: Test IsFocusStepKey for various key codes
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusStepKey001, TestSize.Level1)
{
    EXPECT_TRUE(FocusHub::IsFocusStepKey(KeyCode::KEY_TAB));
    EXPECT_TRUE(FocusHub::IsFocusStepKey(KeyCode::KEY_DPAD_LEFT));
    EXPECT_TRUE(FocusHub::IsFocusStepKey(KeyCode::KEY_DPAD_RIGHT));
    EXPECT_TRUE(FocusHub::IsFocusStepKey(KeyCode::KEY_DPAD_UP));
    EXPECT_TRUE(FocusHub::IsFocusStepKey(KeyCode::KEY_DPAD_DOWN));
    EXPECT_FALSE(FocusHub::IsFocusStepKey(KeyCode::KEY_ENTER));
}

/**
 * @tc.name: IsLeafFocusScope001
 * @tc.desc: Test IsLeafFocusScope for SELF and AUTO depend
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsLeafFocusScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::SELF;
    focusHub->isSwitchByEnter_ = false;
    EXPECT_TRUE(focusHub->IsLeafFocusScope());
    focusHub->focusDepend_ = FocusDependence::AUTO;
    EXPECT_FALSE(focusHub->IsLeafFocusScope());
}

/**
 * @tc.name: AcceptFocusOfSpecifyChild001
 * @tc.desc: Test AcceptFocusOfSpecifyChild for NODE and DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3AcceptFocusOfSpecifyChild001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_TRUE(focusHub->AcceptFocusOfSpecifyChild(FocusStep::TAB));

    RefPtr<EventHub> eventHub2 = AceType::MakeRefPtr<EventHub>();
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub2->AttachHost(frameNode2);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    focusHub2->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub2->AcceptFocusOfSpecifyChild(FocusStep::TAB));

    auto frameNode3 = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<EventHub> eventHub3 = AceType::MakeRefPtr<EventHub>();
    eventHub3->AttachHost(frameNode3);
    auto focusHub3 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub3)));
    focusHub3->focusType_ = FocusType::SCOPE;
    focusHub3->focusDepend_ = FocusDependence::SELF;
    focusHub3->focusable_ = true;
    focusHub3->parentFocusable_ = true;
    EXPECT_TRUE(focusHub3->AcceptFocusOfSpecifyChild(FocusStep::TAB));
}

/**
 * @tc.name: AcceptFocusOfLastFocus001
 * @tc.desc: Test AcceptFocusOfLastFocus for NODE and DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3AcceptFocusOfLastFocus001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_TRUE(focusHub->AcceptFocusOfLastFocus());

    RefPtr<EventHub> eventHub2 = AceType::MakeRefPtr<EventHub>();
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub2->AttachHost(frameNode2);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    focusHub2->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub2->AcceptFocusOfLastFocus());
}

/**
 * @tc.name: CollectTabIndexNodes001
 * @tc.desc: Test CollectTabIndexNodes with positive, zero, and not focusable
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3CollectTabIndexNodes001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetTabIndex(3);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    TabIndexNodeList tabIndexNodes;
    focusHub->CollectTabIndexNodes(tabIndexNodes);
    EXPECT_EQ(tabIndexNodes.size(), 1);
    focusHub->SetTabIndex(0);
    tabIndexNodes.clear();
    focusHub->CollectTabIndexNodes(tabIndexNodes);
    EXPECT_EQ(tabIndexNodes.size(), 0);
    focusHub->SetTabIndex(3);
    focusHub->focusable_ = false;
    tabIndexNodes.clear();
    focusHub->CollectTabIndexNodes(tabIndexNodes);
    EXPECT_EQ(tabIndexNodes.size(), 0);
}

/**
 * @tc.name: SetFocusScopeIdNotScope001
 * @tc.desc: Test SetFocusScopeId when focusType_ is not SCOPE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusScopeIdNotScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->SetFocusScopeId("testScope", false, true);
    EXPECT_FALSE(focusHub->isFocusScope_);
}

/**
 * @tc.name: IsNestingFocusGroup001
 * @tc.desc: Test IsNestingFocusGroup when not a focus group
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsNestingFocusGroup001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->isGroup_ = false;
    EXPECT_FALSE(focusHub->IsNestingFocusGroup());
}

/**
 * @tc.name: IsFocusableWholePath001
 * @tc.desc: Test IsFocusableWholePath when focusable and no parent
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableWholePath001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_TRUE(focusHub->IsFocusableWholePath());
}

/**
 * @tc.name: IsSelfFocusableWholePath001
 * @tc.desc: Test IsSelfFocusableWholePath when focusable and no parent
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsSelfFocusableWholePath001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_TRUE(focusHub->IsSelfFocusableWholePath());
}

/**
 * @tc.name: GetUnfocusableParentFocusNode001
 * @tc.desc: Test GetUnfocusableParentFocusNode when not focusable
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3GetUnfocusableParentFocusNode001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusable_ = false;
    auto result = focusHub->GetUnfocusableParentFocusNode();
    EXPECT_NE(result.Upgrade(), nullptr);
}

/**
 * @tc.name: IsFocusableByTabDisable001
 * @tc.desc: Test IsFocusableByTab when focusType_ is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusableByTabDisable001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub->IsFocusableByTab());
}

/**
 * @tc.name: GetFocusableCount001
 * @tc.desc: Test GetFocusableCount with children and empty
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3GetFocusableCount001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->GetFocusableCount(), 0);
    auto child1 = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    child1->GetOrCreateFocusHub();
    child1->GetFocusHub()->focusable_ = true;
    child1->GetFocusHub()->parentFocusable_ = true;
    frameNode->AddChild(child1);
    auto child2 = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -2, AceType::MakeRefPtr<ButtonPattern>());
    child2->GetOrCreateFocusHub();
    child2->GetFocusHub()->focusable_ = true;
    child2->GetFocusHub()->parentFocusable_ = true;
    frameNode->AddChild(child2);
    EXPECT_EQ(focusHub->GetFocusableCount(), 2);
}

/**
 * @tc.name: FocusToHeadOrTailChildNoChild001
 * @tc.desc: Test FocusToHeadOrTailChild when no child found
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3FocusToHeadOrTailChildNoChild001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto ret = focusHub->FocusToHeadOrTailChild(true);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: LostChildFocusToSelf001
 * @tc.desc: Test LostChildFocusToSelf when not currently focused
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3LostChildFocusToSelf001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->currentFocus_ = false;
    focusHub->LostChildFocusToSelf();
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: SetFocusableExplicitTrue001
 * @tc.desc: Test SetFocusable explicit true after implicit false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusableExplicitTrue001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->isFocusableExplicit_ = true;
    focusHub->SetFocusable(true, false);
    EXPECT_FALSE(focusHub->focusable_);
}

/**
 * @tc.name: SetFocusableImplicitAutoToChild001
 * @tc.desc: Test SetFocusable implicit changes CHILD to AUTO
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusableImplicitAutoToChild001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusable_ = false;
    focusHub->isFocusableExplicit_ = false;
    focusHub->implicitFocusable_ = true;
    focusHub->focusDepend_ = FocusDependence::CHILD;
    focusHub->SetFocusable(true, false);
    EXPECT_EQ(focusHub->focusDepend_, FocusDependence::AUTO);
}

/**
 * @tc.name: PaintFocusStateForceNone001
 * @tc.desc: Test PaintFocusState when focusStyleType_ is FORCE_NONE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3PaintFocusStateForceNone001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusStyleType_ = FocusStyleType::FORCE_NONE;
    focusHub->currentFocus_ = true;
    auto result = focusHub->PaintFocusState();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PaintFocusStateNone001
 * @tc.desc: Test PaintFocusState when focusStyleType_ is NONE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3PaintFocusStateNone001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusStyleType_ = FocusStyleType::NONE;
    focusHub->currentFocus_ = true;
    auto result = focusHub->PaintFocusState();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: FocusBoxStyle001
 * @tc.desc: Test FocusBox constructor and HasCustomStyle
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3FocusBoxStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FocusBox with default constructor.
     * @tc.expected: FocusBox does not have custom style by default.
     */
    FocusBox boxNone;
    EXPECT_FALSE(boxNone.HasCustomStyle());
    /**
     * @tc.steps: step2. Create FocusBox and set custom FocusBoxStyle.
     * @tc.expected: FocusBox has custom style after setting style.
     */
    FocusBoxStyle style;
    style.strokeColor = Color(0xFF000000);
    FocusBox boxCustom;
    boxCustom.SetStyle(style);
    EXPECT_TRUE(boxCustom.HasCustomStyle());
}

/**
 * @tc.name: OnPreFocusFunc001
 * @tc.desc: Test SetOnPreFocusCallback and invocation
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3OnPreFocusFunc001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    bool callbackInvoked = false;
    focusHub->SetOnPreFocusCallback([&callbackInvoked]() { callbackInvoked = true; });
    EXPECT_NE(focusHub->onPreFocusCallback_, nullptr);
    focusHub->onPreFocusCallback_();
    EXPECT_TRUE(callbackInvoked);
}

/**
 * @tc.name: SetIsFocusOnTouch001
 * @tc.desc: Test SetIsFocusOnTouch when no focusCallbackEvents
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetIsFocusOnTouch001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusCallbackEvents_ = nullptr;
    focusHub->SetIsFocusOnTouch(true);
    EXPECT_NE(focusHub->focusCallbackEvents_, nullptr);
}

/**
 * @tc.name: GoToNextFocusLinear001
 * @tc.desc: Test GoToNextFocusLinear with NONE step
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3GoToNextFocusLinear001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_FALSE(focusHub->GoToNextFocusLinear(FocusStep::NONE));
}

/**
 * @tc.name: SwitchFocusNotScope001
 * @tc.desc: Test SwitchFocus when focusType_ is NODE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SwitchFocusNotScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    auto childNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -2, AceType::MakeRefPtr<ButtonPattern>());
    childNode->GetOrCreateFocusHub();
    auto childFocusHub = childNode->GetFocusHub();
    childFocusHub->focusable_ = true;
    focusHub->SwitchFocus(childFocusHub);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: HandleFocusTravel001
 * @tc.desc: Test HandleFocusTravel with NONE intension
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3HandleFocusTravel001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    KeyEvent keyEvent(KeyCode::KEY_UNKNOWN, KeyAction::DOWN);
    FocusEvent focusEvent(keyEvent);
    focusEvent.intension = FocusIntension::NONE;
    EXPECT_FALSE(focusHub->HandleFocusTravel(focusEvent));
}

/**
 * @tc.name: IsComponentDirectionRtl001
 * @tc.desc: Test IsComponentDirectionRtl when no frameNode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsComponentDirectionRtl001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->IsComponentDirectionRtl();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CalculatePosition001
 * @tc.desc: Test CalculatePosition with null lastWeakFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3CalculatePosition001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->lastWeakFocusNode_ = nullptr;
    EXPECT_FALSE(focusHub->CalculatePosition());
}

/**
 * @tc.name: RemoveSelfNoFrameNode001
 * @tc.desc: Test RemoveSelf when frameNode is null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RemoveSelfNoFrameNode001, TestSize.Level1)
{
    auto focusHub = AceType::MakeRefPtr<FocusHub>(WeakPtr<EventHub>(), FocusType::NODE);
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    focusHub->RemoveSelf(BlurReason::FOCUS_SWITCH);
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: RemoveSelfEmptyScopeId001
 * @tc.desc: Test RemoveSelf when focusScopeId_ is empty
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RemoveSelfEmptyScopeId001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusScopeId_ = "";
    focusHub->currentFocus_ = true;
    focusHub->RemoveSelf(BlurReason::FOCUS_SWITCH);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: IsFocusWindowIdSetted001
 * @tc.desc: Test IsFocusWindowIdSetted when focusWindowId_ is not set
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsFocusScopeIdSetted001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusScopeId_ = "";
    EXPECT_TRUE(focusHub->focusScopeId_.empty());
}

/**
 * @tc.name: RemoveChildNullFocusNode001
 * @tc.desc: Test RemoveChild when focusNode is null
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RemoveChildNullFocusNode001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RemoveChild(nullptr, BlurReason::FOCUS_SWITCH);
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: IsViewRootScope001
 * @tc.desc: Test IsViewRootScope when not focus scope
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsViewRootScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->isFocusScope_ = false;
    EXPECT_FALSE(focusHub->IsViewRootScope());
}

/**
 * @tc.name: IsTabStop001
 * @tc.desc: Test IsTabStop when isTabStop_ is true or false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3IsTabStop001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->tabStop_ = true;
    EXPECT_TRUE(focusHub->IsTabStop());
    focusHub->tabStop_ = false;
    EXPECT_FALSE(focusHub->IsTabStop());
}

/**
 * @tc.name: SetFocusGroup001
 * @tc.desc: Test SetFocusGroup and IsFocusGroup
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusGroup001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->isGroup_ = true;
    EXPECT_TRUE(focusHub->isGroup_);
    EXPECT_TRUE(focusHub->GetIsFocusGroup());
    focusHub->isGroup_ = false;
    EXPECT_FALSE(focusHub->isGroup_);
    EXPECT_FALSE(focusHub->GetIsFocusGroup());
}

/**
 * @tc.name: RequestNextFocusOfKeyEnter001
 * @tc.desc: Test RequestNextFocusOfKeyEnter when tab stop and SCOPE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RequestNextFocusOfKeyEnter001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->SetTabStop(true);
    EXPECT_TRUE(focusHub->RequestNextFocusOfKeyEnter());
    EXPECT_TRUE(focusHub->isSwitchByEnter_);
}

/**
 * @tc.name: RequestNextFocusOfKeyEsc001
 * @tc.desc: Test RequestNextFocusOfKeyEsc with null curFocusView
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RequestNextFocusOfKeyEsc001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    EXPECT_FALSE(focusHub->RequestNextFocusOfKeyEsc());
}

/**
 * @tc.name: RequestNextFocusByDefaultAlgorithm001
 * @tc.desc: Test RequestNextFocusByDefaultAlgorithm with HOME step
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RequestNextFocusByDefaultAlgorithm001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_FALSE(focusHub->RequestNextFocusByDefaultAlgorithm(
        FocusStep::LEFT_END, RectF(0, 0, 100, 100)));
}

/**
 * @tc.name: RequestFocusImmediatelyInner001
 * @tc.desc: Test RequestFocusImmediatelyInner when DISABLE and isFocusingByTab
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RequestFocusImmediatelyInner001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    focusHub->SetIsFocusOnTouch(true);
    EXPECT_FALSE(focusHub->RequestFocusImmediatelyInner());
}

/**
 * @tc.name: ModalCheckBeforeRequestFocus001
 * @tc.desc: Test ModalCheckBeforeRequestFocus when no focusManager
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3ModalCheckBeforeRequestFocus001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto result = focusHub->ModalCheckBeforeRequestFocus();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnFocusNode001
 * @tc.desc: Test OnFocusNode when focusable_ is false
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3OnFocusNode001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = false;
    focusHub->OnFocusNode();
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: OnFocusScopeAutoNoFocusable001
 * @tc.desc: Test OnFocusScope with AUTO depend and no focusable child
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3OnFocusScopeAutoNoFocusable001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::SCOPE;
    focusHub->focusDepend_ = FocusDependence::AUTO;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    focusHub->OnFocusScope();
    EXPECT_TRUE(focusHub->currentFocus_);
}

/**
 * @tc.name: HandleEvent001
 * @tc.desc: Test HandleEvent with DISABLE focusType
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3HandleEvent001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::DISABLE;
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN);
    EXPECT_FALSE(focusHub->HandleEvent(keyEvent));
}

/**
 * @tc.name: OnBlurNode001
 * @tc.desc: Test OnBlurNode when not currently focused
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3OnBlurNode001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = false;
    focusHub->OnBlurNode();
    EXPECT_FALSE(focusHub->currentFocus_);
}

/**
 * @tc.name: AcceptFocusOfPriorityChild001
 * @tc.desc: Test AcceptFocusOfPriorityChild when focusType_ is NODE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3AcceptFocusOfPriorityChild001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    EXPECT_FALSE(focusHub->AcceptFocusOfPriorityChild());
}

/**
 * @tc.name: SetFocusScopePriorityNotScope001
 * @tc.desc: Test SetFocusScopePriority when isFocusScope_ is true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusScopePriorityNotScope001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::ROW_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->isFocusScope_ = true;
    focusHub->SetFocusScopePriority("scope1", 0);
    EXPECT_TRUE(focusHub->isFocusScope_);
}

/**
 * @tc.name: AcceptFocusByRectOfLastFocus001
 * @tc.desc: Test AcceptFocusByRectOfLastFocusNode for NODE and DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3AcceptFocusByRectOfLastFocus001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    focusHub->parentFocusable_ = true;
    EXPECT_TRUE(focusHub->AcceptFocusByRectOfLastFocusNode(RectF(0, 0, 100, 100)));

    RefPtr<EventHub> eventHub2 = AceType::MakeRefPtr<EventHub>();
    auto frameNode2 = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub2->AttachHost(frameNode2);
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub2)));
    focusHub2->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(focusHub2->AcceptFocusByRectOfLastFocus(RectF(0, 0, 100, 100)));
}

/**
 * @tc.name: PaintFocusStateToRenderContext001
 * @tc.desc: Test PaintFocusStateToRenderContext with null render context
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3PaintFocusStateToRenderContext001, TestSize.Level1)
{
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusType_ = FocusType::NODE;
    focusHub->focusable_ = true;
    auto result = focusHub->PaintFocusStateToRenderContext();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RequestNextFocusByKey001
 * @tc.desc: Test RequestNextFocusByKey when RequestUserNextFocus true
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RequestNextFocusByKey001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetNextFocus(FocusIntension::TAB,
        AceType::WeakClaim(AceType::RawPtr(frameNode)));
    KeyEvent keyEvent(KeyCode::KEY_TAB, KeyAction::DOWN);
    FocusEvent focusEvent(keyEvent);
    focusEvent.intension = FocusIntension::TAB;
    EXPECT_TRUE(focusHub->RequestNextFocusByKey(focusEvent));
}

/**
 * @tc.name: RequestFocusImmediatelyFromModalUEC001
 * @tc.desc: Test RequestFocusImmediatelyFromModalUEC with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3RequestFocusImmediatelyFromModalUEC001, TestSize.Level1)
{
    auto focusHub = AceType::MakeRefPtr<FocusHub>(WeakPtr<EventHub>(), FocusType::NODE);
    ASSERT_NE(focusHub, nullptr);
    EXPECT_FALSE(focusHub->RequestFocusImmediatelyFromModalUEC());
}

/**
 * @tc.name: GetInspectorKey001
 * @tc.desc: Test GetInspectorKey with and without frameNode
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3GetInspectorKey001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto key = focusHub->GetInspectorKey();
    EXPECT_FALSE(key.has_value());
    auto focusHub2 = AceType::MakeRefPtr<FocusHub>(WeakPtr<EventHub>(), FocusType::NODE);
    auto key2 = focusHub2->GetInspectorKey();
    EXPECT_EQ(key2, std::nullopt);
}

/**
 * @tc.name: SetFocusableSameValue001
 * @tc.desc: Test SetFocusable when setting same value returns early
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusableSameValue001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    frameNode->GetOrCreateFocusHub();
    auto focusHub = frameNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->focusable_ = true;
    focusHub->SetFocusable(true, true);
    EXPECT_TRUE(focusHub->focusable_);
}

/**
 * @tc.name: SetFocusPaintParamsPtrNullParam002
 * @tc.desc: Test SetFocusPaintParamsPtr null with existing params
 * @tc.type: FUNC
 */
HWTEST_F(FocusHubTestNg, Bc3SetFocusPaintParamsPtrNullParam002, TestSize.Level1)
{
    FocusPaintParam paintParam;
    paintParam.SetPaintColor(Color(0xFF000000));
    FocusPattern pattern(FocusType::NODE, true, FocusStyleType::OUTER_BORDER, paintParam);
    auto frameNode = AceType::MakeRefPtr<FrameNodeOnTree>(
        V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<ButtonPattern>());
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(frameNode);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(
        AceType::WeakClaim(AceType::RawPtr(eventHub)), pattern);
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusPaintParamsPtr(nullptr);
    EXPECT_NE(focusHub->focusPaintParamsPtr_, nullptr);
}

} // namespace OHOS::Ace::NG
