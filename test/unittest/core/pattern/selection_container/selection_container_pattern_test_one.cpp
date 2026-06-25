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

#define private public
#define protected public

#include "selection_container_test_common.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

/* ==================== GetSelectionText ==================== */

/**
 * @tc.name: GetSelectionText001
 * @tc.desc: Test GetSelectionText returns empty when no children registered.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectionText001, TestSize.Level1)
{
    auto text = pattern_->GetSelectionText();
    EXPECT_TRUE(text.empty());
}

/**
 * @tc.name: GetSelectionText002
 * @tc.desc: Test GetSelectionText with a single child that has non-empty selection text.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectionText002, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    auto text = pattern_->GetSelectionText();
    EXPECT_EQ(text, SCT_TEST_SELECTION_TEXT1);
}

/**
 * @tc.name: GetSelectionText003
 * @tc.desc: Test GetSelectionText with multiple children; verify the separator is inserted between them.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectionText003, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child2_->SetSelectionText(SCT_TEST_SELECTION_TEXT2);
    auto text = pattern_->GetSelectionText();
    auto separator = pattern_->GetTextJoinSeparator();
    std::u16string expected = SCT_TEST_SELECTION_TEXT1 + separator + SCT_TEST_SELECTION_TEXT2;
    EXPECT_EQ(text, expected);
}

/**
 * @tc.name: GetSelectionText004
 * @tc.desc: Test GetSelectionText skips children with empty selection text.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectionText004, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    child1_->SetSelectionText(SCT_TEST_EMPTY_TEXT);
    child2_->SetSelectionText(SCT_TEST_SELECTION_TEXT2);
    auto text = pattern_->GetSelectionText();
    EXPECT_EQ(text, SCT_TEST_SELECTION_TEXT2);
}

/**
 * @tc.name: GetSelectionText005
 * @tc.desc: Test GetSelectionText with DIRECT join style produces no separator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetSelectionText005, TestSize.Level1)
{
    pattern_->RegisterChild(child1_);
    pattern_->RegisterChild(child2_);
    pattern_->SetTextJoinStyle(SelectionContainerTextJoinStyle::DIRECT);
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child2_->SetSelectionText(SCT_TEST_SELECTION_TEXT2);
    auto text = pattern_->GetSelectionText();
    std::u16string expected = SCT_TEST_SELECTION_TEXT1 + SCT_TEST_SELECTION_TEXT2;
    EXPECT_EQ(text, expected);
}

/* ==================== GetHostNode ==================== */

/**
 * @tc.name: GetHostNode001
 * @tc.desc: Test GetHostNode returns the host FrameNode that owns the pattern.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetHostNode001, TestSize.Level1)
{
    auto hostNode = pattern_->GetHostNode();
    EXPECT_EQ(hostNode, containerNode_);
}

/* ==================== GetOrCreateSelectionSelectOverlay ==================== */

/**
 * @tc.name: GetOrCreateOverlay001
 * @tc.desc: Test GetOrCreateSelectionSelectOverlay creates overlay on first call and reuses it.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetOrCreateOverlay001, TestSize.Level1)
{
    auto overlay1 = pattern_->GetOrCreateSelectionSelectOverlay();
    ASSERT_NE(overlay1, nullptr);
    auto overlay2 = pattern_->GetOrCreateSelectionSelectOverlay();
    EXPECT_EQ(overlay1, overlay2);
}

/* ==================== CloseSelectOverlay ==================== */

/**
 * @tc.name: CloseSelectOverlay001
 * @tc.desc: Test CloseSelectOverlay does not crash and creates the overlay internally.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CloseSelectOverlay001, TestSize.Level1)
{
    pattern_->CloseSelectOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== ProcessOverlay ==================== */

/**
 * @tc.name: ProcessOverlay001
 * @tc.desc: Test ProcessOverlay delegates to the overlay without crashing.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ProcessOverlay001, TestSize.Level1)
{
    OverlayRequest request;
    request.animation = true;
    pattern_->ProcessOverlay(request);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== SwitchToOverlayMode ==================== */

/**
 * @tc.name: SwitchToOverlayMode001
 * @tc.desc: Test SwitchToOverlayMode creates overlay and delegates the call.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SwitchToOverlayMode001, TestSize.Level1)
{
    pattern_->SwitchToOverlayMode();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== ToggleMenu ==================== */

/**
 * @tc.name: ToggleMenu001
 * @tc.desc: Test ToggleMenu creates overlay and delegates.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ToggleMenu001, TestSize.Level1)
{
    pattern_->ToggleMenu();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== HideMenu ==================== */

/**
 * @tc.name: HideMenu001
 * @tc.desc: Test HideMenu with noAnimation=false and showSubMenu=false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HideMenu001, TestSize.Level1)
{
    pattern_->HideMenu(false, false);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: HideMenu002
 * @tc.desc: Test HideMenu with noAnimation=true and showSubMenu=true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HideMenu002, TestSize.Level1)
{
    pattern_->HideMenu(true, true);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== DisableMenu ==================== */

/**
 * @tc.name: DisableMenu001
 * @tc.desc: Test DisableMenu delegates to overlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, DisableMenu001, TestSize.Level1)
{
    pattern_->DisableMenu();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== UpdateAISelectMenu ==================== */

/**
 * @tc.name: UpdateAISelectMenu001
 * @tc.desc: Test UpdateAISelectMenu delegates to overlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateAISelectMenu001, TestSize.Level1)
{
    pattern_->UpdateAISelectMenu();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== IsCurrentMenuVisibile ==================== */

/**
 * @tc.name: IsCurrentMenuVisibile001
 * @tc.desc: Test IsCurrentMenuVisibile returns false before overlay is used.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsCurrentMenuVisibile001, TestSize.Level1)
{
    auto result = pattern_->IsCurrentMenuVisibile();
    EXPECT_FALSE(result);
}

/* ==================== GetIsHandleDragging ==================== */

/**
 * @tc.name: GetIsHandleDragging001
 * @tc.desc: Test GetIsHandleDragging returns false when no overlay is set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetIsHandleDragging001, TestSize.Level1)
{
    auto result = pattern_->GetIsHandleDragging();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetIsHandleDragging002
 * @tc.desc: Test GetIsHandleDragging after overlay is created returns its state.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetIsHandleDragging002, TestSize.Level1)
{
    pattern_->GetOrCreateSelectionSelectOverlay();
    auto result = pattern_->GetIsHandleDragging();
    EXPECT_FALSE(result);
}

/* ==================== IsClickAtHandle ==================== */

/**
 * @tc.name: IsClickAtHandle001
 * @tc.desc: Test IsClickAtHandle returns false when overlay is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsClickAtHandle001, TestSize.Level1)
{
    GestureEvent info;
    auto result = pattern_->IsClickAtHandle(info);
    EXPECT_FALSE(result);
}

/* ==================== IsTouchAtHandle ==================== */

/**
 * @tc.name: IsTouchAtHandle001
 * @tc.desc: Test IsTouchAtHandle returns false when overlay is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsTouchAtHandle001, TestSize.Level1)
{
    TouchEventInfo info("touch");
    auto result = pattern_->IsTouchAtHandle(info);
    EXPECT_FALSE(result);
}

/* ==================== UpdateAllHandlesOffset ==================== */

/**
 * @tc.name: UpdateAllHandlesOffset001
 * @tc.desc: Test UpdateAllHandlesOffset does nothing when overlay is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateAllHandlesOffset001, TestSize.Level1)
{
    pattern_->UpdateAllHandlesOffset();
    EXPECT_EQ(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: UpdateAllHandlesOffset002
 * @tc.desc: Test UpdateAllHandlesOffset delegates to overlay when present.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateAllHandlesOffset002, TestSize.Level1)
{
    pattern_->GetOrCreateSelectionSelectOverlay();
    pattern_->UpdateAllHandlesOffset();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== UpdateViewPort ==================== */

/**
 * @tc.name: UpdateViewPort001
 * @tc.desc: Test UpdateViewPort does nothing when overlay is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateViewPort001, TestSize.Level1)
{
    pattern_->UpdateViewPort();
    EXPECT_EQ(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: UpdateViewPort002
 * @tc.desc: Test UpdateViewPort delegates when overlay is present.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateViewPort002, TestSize.Level1)
{
    pattern_->GetOrCreateSelectionSelectOverlay();
    pattern_->UpdateViewPort();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== MarkOverlayDirty ==================== */

/**
 * @tc.name: MarkOverlayDirty001
 * @tc.desc: Test MarkOverlayDirty is a no-op when overlay is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, MarkOverlayDirty001, TestSize.Level1)
{
    pattern_->MarkOverlayDirty();
    EXPECT_EQ(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: MarkOverlayDirty002
 * @tc.desc: Test MarkOverlayDirty delegates when overlay exists.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, MarkOverlayDirty002, TestSize.Level1)
{
    pattern_->GetOrCreateSelectionSelectOverlay();
    pattern_->MarkOverlayDirty();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== IsShowMouseMenu ==================== */

/**
 * @tc.name: IsShowMouseMenu001
 * @tc.desc: Test IsShowMouseMenu returns false when no overlay exists.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsShowMouseMenu001, TestSize.Level1)
{
    auto result = pattern_->IsShowMouseMenu();
    EXPECT_FALSE(result);
}

/* ==================== UpdateMenuOnWindowSizeChanged ==================== */

/**
 * @tc.name: UpdateMenuOnWindowSizeChanged001
 * @tc.desc: Test UpdateMenuOnWindowSizeChanged is a no-op without overlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateMenuOnWindowSizeChanged001, TestSize.Level1)
{
    pattern_->UpdateMenuOnWindowSizeChanged(WindowSizeChangeReason::RESIZE);
    EXPECT_EQ(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: UpdateMenuOnWindowSizeChanged002
 * @tc.desc: Test UpdateMenuOnWindowSizeChanged delegates when overlay exists.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateMenuOnWindowSizeChanged002, TestSize.Level1)
{
    pattern_->GetOrCreateSelectionSelectOverlay();
    pattern_->UpdateMenuOnWindowSizeChanged(WindowSizeChangeReason::RESIZE);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== SetMouseMenuOffset ==================== */

/**
 * @tc.name: SetMouseMenuOffset001
 * @tc.desc: Test SetMouseMenuOffset creates overlay and delegates.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SetMouseMenuOffset001, TestSize.Level1)
{
    OffsetF offset(SCT_TEST_OFFSET_X, SCT_TEST_OFFSET_Y);
    pattern_->SetMouseMenuOffset(offset);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== IsUsingMouse ==================== */

/**
 * @tc.name: IsUsingMouse001
 * @tc.desc: Test IsUsingMouse returns false when source type is NONE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsUsingMouse001, TestSize.Level1)
{
    pattern_->SetSourceType(SourceType::NONE);
    EXPECT_FALSE(pattern_->IsUsingMouse());
}

/**
 * @tc.name: IsUsingMouse002
 * @tc.desc: Test IsUsingMouse returns true when source type is MOUSE.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsUsingMouse002, TestSize.Level1)
{
    pattern_->SetSourceType(SourceType::MOUSE);
    EXPECT_TRUE(pattern_->IsUsingMouse());
}

/* ==================== OnSelectionMovingChildChange ==================== */

/**
 * @tc.name: OnSelectionMovingChildChange001
 * @tc.desc: Test OnSelectionMovingChildChange with a valid child updates scrollable parent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnSelectionMovingChildChange001, TestSize.Level1)
{
    pattern_->OnSelectionMovingChildChange(child1_);
    EXPECT_FALSE(pattern_->HasScrollableParent());
}

/**
 * @tc.name: OnSelectionMovingChildChange002
 * @tc.desc: Test OnSelectionMovingChildChange with null child does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnSelectionMovingChildChange002, TestSize.Level1)
{
    pattern_->OnSelectionMovingChildChange(nullptr);
    EXPECT_FALSE(pattern_->HasScrollableParent());
}

/* ==================== ResetScrollableParentOnScrollStop ==================== */

/**
 * @tc.name: ResetScrollableParent001
 * @tc.desc: Test ResetScrollableParentOnScrollStop returns early when isStopAutoScroll is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ResetScrollableParent001, TestSize.Level1)
{
    pattern_->isTriggerParentToScroll_ = true;
    pattern_->ResetScrollableParentOnScrollStop(false);
    EXPECT_TRUE(pattern_->isTriggerParentToScroll_);
}

/**
 * @tc.name: ResetScrollableParent002
 * @tc.desc: Test ResetScrollableParentOnScrollStop resets state when isStopAutoScroll is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, ResetScrollableParent002, TestSize.Level1)
{
    pattern_->isTriggerParentToScroll_ = true;
    pattern_->scrollableParentIsInsideContainer_ = true;
    pattern_->ResetScrollableParentOnScrollStop(true);
    EXPECT_FALSE(pattern_->isTriggerParentToScroll_);
    EXPECT_FALSE(pattern_->scrollableParentIsInsideContainer_);
}

/* ==================== UpdateScrollableParentByChild ==================== */

/**
 * @tc.name: UpdateScrollableParent001
 * @tc.desc: Test UpdateScrollableParentByChild with null child is a no-op.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateScrollableParent001, TestSize.Level1)
{
    pattern_->UpdateScrollableParentByChild(nullptr);
    EXPECT_FALSE(pattern_->HasScrollableParent());
}

/**
 * @tc.name: UpdateScrollableParent002
 * @tc.desc: Test UpdateScrollableParentByChild with valid child without scrollable ancestor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateScrollableParent002, TestSize.Level1)
{
    pattern_->UpdateScrollableParentByChild(child1_);
    EXPECT_FALSE(pattern_->HasScrollableParent());
}

/* ==================== IsPointInScrollableViewport ==================== */

/**
 * @tc.name: IsPointInScrollableViewport001
 * @tc.desc: Test IsPointInScrollableViewport returns false when scrollablePattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsPointInScrollableViewport001, TestSize.Level1)
{
    OffsetF globalPoint(SCT_TEST_OFFSET_X, SCT_TEST_OFFSET_Y);
    auto result = pattern_->IsPointInScrollableViewport(nullptr, globalPoint);
    EXPECT_FALSE(result);
}

/* ==================== CheckScrollableParentSize ==================== */

/**
 * @tc.name: CheckScrollableParentSize001
 * @tc.desc: Test CheckScrollableParentSize returns false when scrollablePattern is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CheckScrollableParentSize001, TestSize.Level1)
{
    auto result = pattern_->CheckScrollableParentSize(nullptr);
    EXPECT_FALSE(result);
}

/* ==================== IsTriggerParentToScroll ==================== */

/**
 * @tc.name: IsTriggerParentToScroll001
 * @tc.desc: Test IsTriggerParentToScroll returns false by default.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsTriggerParentToScroll001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->IsTriggerParentToScroll());
}

/**
 * @tc.name: IsTriggerParentToScroll002
 * @tc.desc: Test IsTriggerParentToScroll returns true after being set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, IsTriggerParentToScroll002, TestSize.Level1)
{
    pattern_->isTriggerParentToScroll_ = true;
    EXPECT_TRUE(pattern_->IsTriggerParentToScroll());
}

/* ==================== HasScrollableParent ==================== */

/**
 * @tc.name: HasScrollableParent001
 * @tc.desc: Test HasScrollableParent returns false when no scrollable parent set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HasScrollableParent001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->HasScrollableParent());
}

/* ==================== TriggerScrollableParentToScroll ==================== */

/**
 * @tc.name: TriggerScrollableParent001
 * @tc.desc: Test TriggerScrollableParentToScroll with no scrollable parent and isStopAutoScroll=false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, TriggerScrollableParent001, TestSize.Level1)
{
    OffsetF globalPoint(SCT_TEST_OFFSET_X, SCT_TEST_OFFSET_Y);
    pattern_->TriggerScrollableParentToScroll(globalPoint, false);
    EXPECT_FALSE(pattern_->IsTriggerParentToScroll());
}

/**
 * @tc.name: TriggerScrollableParent002
 * @tc.desc: Test TriggerScrollableParentToScroll with isStopAutoScroll=true and no scrollable parent.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, TriggerScrollableParent002, TestSize.Level1)
{
    OffsetF globalPoint(SCT_TEST_OFFSET_X, SCT_TEST_OFFSET_Y);
    pattern_->TriggerScrollableParentToScroll(globalPoint, true);
    EXPECT_FALSE(pattern_->IsTriggerParentToScroll());
}

/* ==================== EnableMouseLeftSelectionTracking ==================== */

/**
 * @tc.name: EnableMouseLeftTracking001
 * @tc.desc: Test EnableMouseLeftSelectionTracking does nothing when no scrollable parent exists.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, EnableMouseLeftTracking001, TestSize.Level1)
{
    OffsetF globalPoint(SCT_TEST_OFFSET_X, SCT_TEST_OFFSET_Y);
    pattern_->EnableMouseLeftSelectionTracking(globalPoint);
    EXPECT_FALSE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/* ==================== StopMouseLeftSelectionTracking ==================== */

/**
 * @tc.name: StopMouseLeftTracking001
 * @tc.desc: Test StopMouseLeftSelectionTracking resets the last mouse point and unregisters listener.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, StopMouseLeftTracking001, TestSize.Level1)
{
    pattern_->lastMouseLeftGlobalPoint_ = OffsetF(SCT_TEST_OFFSET_X, SCT_TEST_OFFSET_Y);
    pattern_->mouseLeftSelectionNodeChangeListenerRegistered_ = true;
    pattern_->StopMouseLeftSelectionTracking();
    EXPECT_FALSE(pattern_->lastMouseLeftGlobalPoint_.has_value());
    EXPECT_FALSE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/* ==================== RegisterMouseLeftSelectionNodeChangeListener ==================== */

/**
 * @tc.name: RegisterMouseLeftListener001
 * @tc.desc: Test RegisterMouseLeftSelectionNodeChangeListener does not register twice.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RegisterMouseLeftListener001, TestSize.Level1)
{
    pattern_->mouseLeftSelectionNodeChangeListenerRegistered_ = true;
    pattern_->RegisterMouseLeftSelectionNodeChangeListener();
    EXPECT_TRUE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/**
 * @tc.name: RegisterMouseLeftListener002
 * @tc.desc: Test RegisterMouseLeftSelectionNodeChangeListener registers when not yet registered.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RegisterMouseLeftListener002, TestSize.Level1)
{
    pattern_->RegisterMouseLeftSelectionNodeChangeListener();
    EXPECT_TRUE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/* ==================== UnregisterMouseLeftSelectionNodeChangeListener ==================== */

/**
 * @tc.name: UnregisterMouseLeftListener001
 * @tc.desc: Test UnregisterMouseLeftSelectionNodeChangeListener is a no-op when not registered.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UnregisterMouseLeftListener001, TestSize.Level1)
{
    pattern_->UnregisterMouseLeftSelectionNodeChangeListener();
    EXPECT_FALSE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/**
 * @tc.name: UnregisterMouseLeftListener002
 * @tc.desc: Test UnregisterMouseLeftSelectionNodeChangeListener unregisters when registered.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UnregisterMouseLeftListener002, TestSize.Level1)
{
    pattern_->mouseLeftSelectionNodeChangeListenerRegistered_ = true;
    pattern_->UnregisterMouseLeftSelectionNodeChangeListener();
    EXPECT_FALSE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/* ==================== RefreshMouseLeftSelectionOnFrameNodeChanged ==================== */

/**
 * @tc.name: RefreshMouseLeftOnFrameNodeChanged001
 * @tc.desc: Test RefreshMouseLeftSelectionOnFrameNodeChanged is a no-op when not registered.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RefreshMouseLeftOnFrameNodeChanged001, TestSize.Level1)
{
    pattern_->RefreshMouseLeftSelectionOnFrameNodeChanged();
    EXPECT_FALSE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/**
 * @tc.name: RefreshMouseLeftOnFrameNodeChanged002
 * @tc.desc: Test RefreshMouseLeftSelectionOnFrameNodeChanged is a no-op when no last point.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, RefreshMouseLeftOnFrameNodeChanged002, TestSize.Level1)
{
    pattern_->mouseLeftSelectionNodeChangeListenerRegistered_ = true;
    pattern_->RefreshMouseLeftSelectionOnFrameNodeChanged();
    EXPECT_TRUE(pattern_->mouseLeftSelectionNodeChangeListenerRegistered_);
}

/* ==================== UpdateMovingChildForHandle ==================== */

/**
 * @tc.name: UpdateMovingChildForHandle001
 * @tc.desc: Test UpdateMovingChildForHandle with first handle; uses start child then moving child.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateMovingChildForHandle001, TestSize.Level1)
{
    pattern_->selectionMovingChild_ = child1_;
    pattern_->UpdateMovingChildForHandle(true);
    EXPECT_EQ(pattern_->GetSelectionMovingChild(), child1_);
}

/**
 * @tc.name: UpdateMovingChildForHandle002
 * @tc.desc: Test UpdateMovingChildForHandle with second handle; uses end child then moving child.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateMovingChildForHandle002, TestSize.Level1)
{
    pattern_->selectionMovingChild_ = child2_;
    pattern_->UpdateMovingChildForHandle(false);
    EXPECT_EQ(pattern_->GetSelectionMovingChild(), child2_);
}

/* ==================== UpdateHandleColor ==================== */

/**
 * @tc.name: UpdateHandleColor001
 * @tc.desc: Test UpdateHandleColor creates overlay and delegates.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, UpdateHandleColor001, TestSize.Level1)
{
    pattern_->UpdateHandleColor();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== FireOnWillCopy ==================== */

/**
 * @tc.name: FireOnWillCopy001
 * @tc.desc: Test FireOnWillCopy returns true when no event hub callback is set (default allows copy).
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, FireOnWillCopy001, TestSize.Level1)
{
    auto result = pattern_->FireOnWillCopy(SCT_TEST_SELECTION_TEXT1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FireOnWillCopy002
 * @tc.desc: Test FireOnWillCopy invokes event hub callback and returns its result (true).
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, FireOnWillCopy002, TestSize.Level1)
{
    bool callbackCalled = false;
    auto eventHub = containerNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnWillCopy([&callbackCalled](const std::u16string& text) {
        callbackCalled = true;
        return true;
    });
    auto result = pattern_->FireOnWillCopy(SCT_TEST_SELECTION_TEXT1);
    EXPECT_TRUE(result);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: FireOnWillCopy003
 * @tc.desc: Test FireOnWillCopy invokes event hub callback and returns its result (false).
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, FireOnWillCopy003, TestSize.Level1)
{
    auto eventHub = containerNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnWillCopy([](const std::u16string& text) { return false; });
    auto result = pattern_->FireOnWillCopy(SCT_TEST_SELECTION_TEXT1);
    EXPECT_FALSE(result);
}

/* ==================== FireOnCopy ==================== */

/**
 * @tc.name: FireOnCopy001
 * @tc.desc: Test FireOnCopy invokes the event hub callback.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, FireOnCopy001, TestSize.Level1)
{
    bool callbackCalled = false;
    auto eventHub = containerNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnCopy([&callbackCalled](const std::u16string& text) { callbackCalled = true; });
    pattern_->FireOnCopy(SCT_TEST_SELECTION_TEXT1);
    EXPECT_TRUE(callbackCalled);
}

/* ==================== OnSelectionRangeChanged ==================== */

/**
 * @tc.name: OnSelectionRangeChanged001
 * @tc.desc: Test OnSelectionRangeChanged returns early when state equals lastSelectionState_.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnSelectionRangeChanged001, TestSize.Level1)
{
    std::vector<std::u16string> selectedTexts = { SCT_TEST_SELECTION_TEXT1 };
    std::vector<ChildSelectionInfo> selectionState = { { SCT_TEST_NODE_ID_CHILD1, SCT_TEST_START_INDEX,
        SCT_TEST_END_INDEX } };
    pattern_->lastSelectionState_ = selectionState;
    bool callbackCalled = false;
    auto eventHub = containerNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnTextSelectionChange(
        [&callbackCalled](const std::vector<std::u16string>& texts) { callbackCalled = true; });
    pattern_->OnSelectionRangeChanged(selectedTexts, selectionState);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: OnSelectionRangeChanged002
 * @tc.desc: Test OnSelectionRangeChanged fires event when state differs from lastSelectionState_.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnSelectionRangeChanged002, TestSize.Level1)
{
    std::vector<std::u16string> selectedTexts = { SCT_TEST_SELECTION_TEXT1 };
    std::vector<ChildSelectionInfo> selectionState = { { SCT_TEST_NODE_ID_CHILD1, SCT_TEST_START_INDEX,
        SCT_TEST_END_INDEX } };
    bool callbackCalled = false;
    auto eventHub = containerNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnTextSelectionChange(
        [&callbackCalled](const std::vector<std::u16string>& texts) { callbackCalled = true; });
    pattern_->OnSelectionRangeChanged(selectedTexts, selectionState);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(pattern_->lastSelectionState_, selectionState);
}

/* ==================== HandleOnCopy ==================== */

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: Test HandleOnCopy with no children and no selection; clipboard text is empty so menu hides.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopy001, TestSize.Level1)
{
    pattern_->HandleOnCopy();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== HandleOnCopyFromAI ==================== */

/**
 * @tc.name: HandleOnCopyFromAI001
 * @tc.desc: Test HandleOnCopyFromAI with null child is a no-op.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopyFromAI001, TestSize.Level1)
{
    pattern_->HandleOnCopyFromAI(nullptr);
    EXPECT_FALSE(child1_->GetOnCopyFired());
}

/**
 * @tc.name: HandleOnCopyFromAI002
 * @tc.desc: Test HandleOnCopyFromAI with child that has empty selection text returns early.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopyFromAI002, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_EMPTY_TEXT);
    pattern_->HandleOnCopyFromAI(child1_);
    EXPECT_FALSE(child1_->GetOnCopyFired());
}

/**
 * @tc.name: HandleOnCopyFromAI003
 * @tc.desc: Test HandleOnCopyFromAI with child having CopyOptions::None returns early.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopyFromAI003, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetCopyOption(CopyOptions::None);
    pattern_->HandleOnCopyFromAI(child1_);
    EXPECT_FALSE(child1_->GetOnCopyFired());
}

/**
 * @tc.name: HandleOnCopyFromAI004
 * @tc.desc: Test HandleOnCopyFromAI when child's OnWillCopy returns false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopyFromAI004, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetCopyOption(CopyOptions::InApp);
    child1_->SetOnWillCopyAllowed(false);
    pattern_->HandleOnCopyFromAI(child1_);
    EXPECT_FALSE(child1_->GetOnCopyFired());
}

/**
 * @tc.name: HandleOnCopyFromAI005
 * @tc.desc: Test HandleOnCopyFromAI when container's OnWillCopy returns false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopyFromAI005, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetCopyOption(CopyOptions::InApp);
    child1_->SetOnWillCopyAllowed(true);
    auto eventHub = containerNode_->GetEventHub<SelectionContainerEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnWillCopy([](const std::u16string& text) { return false; });
    pattern_->HandleOnCopyFromAI(child1_);
    EXPECT_FALSE(child1_->GetOnCopyFired());
}

/**
 * @tc.name: HandleOnCopyFromAI006
 * @tc.desc: Test HandleOnCopyFromAI full path: both OnWillCopy allow, OnCopy is fired.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, HandleOnCopyFromAI006, TestSize.Level1)
{
    child1_->SetSelectionText(SCT_TEST_SELECTION_TEXT1);
    child1_->SetCopyOption(CopyOptions::InApp);
    child1_->SetOnWillCopyAllowed(true);
    child1_->ResetOnCopyFired();
    pattern_->HandleOnCopyFromAI(child1_);
    EXPECT_TRUE(child1_->GetOnCopyFired());
}

/* ==================== SelectOverlayIsOn ==================== */

/**
 * @tc.name: SelectOverlayIsOn001
 * @tc.desc: Test SelectOverlayIsOn returns false when no overlay is set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SelectOverlayIsOn001, TestSize.Level1)
{
    EXPECT_FALSE(pattern_->SelectOverlayIsOn());
}

/* ==================== OnFrameNodeChanged ==================== */

/**
 * @tc.name: OnFrameNodeChanged001
 * @tc.desc: Test OnFrameNodeChanged does not crash when overlay is null.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnFrameNodeChanged001, TestSize.Level1)
{
    pattern_->OnFrameNodeChanged(FRAME_NODE_CHANGE_INFO_NONE);
    EXPECT_EQ(pattern_->selectionSelectOverlay_, nullptr);
}

/**
 * @tc.name: OnFrameNodeChanged002
 * @tc.desc: Test OnFrameNodeChanged with overlay set delegates to OnAncestorNodeChanged.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnFrameNodeChanged002, TestSize.Level1)
{
    pattern_->GetOrCreateSelectionSelectOverlay();
    pattern_->OnFrameNodeChanged(FRAME_NODE_CHANGE_INFO_NONE);
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== SetSelectionHoldCallback ==================== */

/**
 * @tc.name: SetSelectionHoldCallback001
 * @tc.desc: Test SetSelectionHoldCallback creates overlay and delegates.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, SetSelectionHoldCallback001, TestSize.Level1)
{
    pattern_->SetSelectionHoldCallback();
    EXPECT_NE(pattern_->selectionSelectOverlay_, nullptr);
}

/* ==================== GetClientHost / BetweenSelectedPosition ==================== */

/**
 * @tc.name: GetClientHost001
 * @tc.desc: Test GetClientHost returns the host FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetClientHost001, TestSize.Level1)
{
    auto clientHost = pattern_->GetClientHost();
    EXPECT_EQ(clientHost, containerNode_);
}

/**
 * @tc.name: BetweenSelectedPosition001
 * @tc.desc: Test BetweenSelectedPosition when no children return true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, BetweenSelectedPosition001, TestSize.Level1)
{
    child1_->SetBetweenSelectedPosition(false);
    pattern_->RegisterChild(child1_);
    Offset globalOffset;
    auto result = pattern_->BetweenSelectedPosition(globalOffset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BetweenSelectedPosition002
 * @tc.desc: Test BetweenSelectedPosition when a child returns true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, BetweenSelectedPosition002, TestSize.Level1)
{
    child1_->SetBetweenSelectedPosition(true);
    pattern_->RegisterChild(child1_);
    Offset globalOffset;
    auto result = pattern_->BetweenSelectedPosition(globalOffset);
    EXPECT_TRUE(result);
}

/* ==================== Misc getters ==================== */

/**
 * @tc.name: EnableHapticFeedback001
 * @tc.desc: Test SetEnableHapticFeedback and GetEnableHapticFeedback round-trip.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, EnableHapticFeedback001, TestSize.Level1)
{
    pattern_->SetEnableHapticFeedback(false);
    EXPECT_FALSE(pattern_->GetEnableHapticFeedback());
    pattern_->SetEnableHapticFeedback(true);
    EXPECT_TRUE(pattern_->GetEnableHapticFeedback());
}

/**
 * @tc.name: GetTextJoinSeparator001
 * @tc.desc: Test GetTextJoinSeparator returns newline by default (NEWLINE style).
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetTextJoinSeparator001, TestSize.Level1)
{
    EXPECT_EQ(pattern_->GetTextJoinSeparator(), u"\n");
}

/**
 * @tc.name: GetTextJoinSeparator002
 * @tc.desc: Test GetTextJoinSeparator returns empty when DIRECT style.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetTextJoinSeparator002, TestSize.Level1)
{
    pattern_->SetTextJoinStyle(SelectionContainerTextJoinStyle::DIRECT);
    EXPECT_TRUE(pattern_->GetTextJoinSeparator().empty());
}

/**
 * @tc.name: OnChildResponseTypeChanged001
 * @tc.desc: Test OnChildResponseTypeChanged stores the response type.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnChildResponseTypeChanged001, TestSize.Level1)
{
    pattern_->OnChildResponseTypeChanged(TextResponseType::SELECTED_BY_MOUSE);
    EXPECT_EQ(pattern_->textResponseType_, TextResponseType::SELECTED_BY_MOUSE);
}

/**
 * @tc.name: OnChildSelectedTypeSave001
 * @tc.desc: Test OnChildSelectedTypeSave delegates to SaveOldSelectedType.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, OnChildSelectedTypeSave001, TestSize.Level1)
{
    pattern_->selectedType_ = TextSpanType::IMAGE;
    pattern_->OnChildSelectedTypeSave();
    EXPECT_EQ(pattern_->oldSelectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: CreateLayoutProperty001
 * @tc.desc: Test CreateLayoutProperty returns SelectionContainerLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CreateLayoutProperty001, TestSize.Level1)
{
    auto property = pattern_->CreateLayoutProperty();
    auto selectionProperty = AceType::DynamicCast<SelectionContainerLayoutProperty>(property);
    EXPECT_TRUE(selectionProperty != nullptr);
}

/**
 * @tc.name: CreateEventHub001
 * @tc.desc: Test CreateEventHub returns SelectionContainerEventHub.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, CreateEventHub001, TestSize.Level1)
{
    auto eventHub = pattern_->CreateEventHub();
    auto selectionEventHub = AceType::DynamicCast<SelectionContainerEventHub>(eventHub);
    EXPECT_TRUE(selectionEventHub != nullptr);
}

/**
 * @tc.name: GetFocusPattern001
 * @tc.desc: Test GetFocusPattern returns SCOPE focus type with OUTER_BORDER style.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetFocusPattern001, TestSize.Level1)
{
    auto focusPattern = pattern_->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::SCOPE);
    EXPECT_EQ(focusPattern.styleType_, FocusStyleType::OUTER_BORDER);
}

/**
 * @tc.name: GetContainerPaintOffset001
 * @tc.desc: Test GetContainerPaintOffsetWithTransform returns an offset.
 * @tc.type: FUNC
 */
HWTEST_F(SelectionContainerPatternTestNg, GetContainerPaintOffset001, TestSize.Level1)
{
    auto offset = pattern_->GetContainerPaintOffsetWithTransform();
    EXPECT_FLOAT_EQ(offset.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(offset.GetY(), 0.0f);
}

} // namespace OHOS::Ace::NG
