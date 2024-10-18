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

#include "list_test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/list/list_item_group_paint_method.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ListLayoutTestNg : public ListTestNg {
public:
    void UpdateContentModifier();
    RefPtr<ListPaintMethod> UpdateOverlayModifier(RefPtr<PaintWrapper> paintWrapper);
    void UpdateDividerMap();
    void PaintDivider(RefPtr<PaintWrapper> paintWrapper, int32_t expectLineNumber, bool isClip = false);
    void GroupPaintDivider(RefPtr<PaintWrapper> paintWrapper, int32_t expectLineNumber);
};

void ListLayoutTestNg::UpdateContentModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateContentModifier(AceType::RawPtr(paintWrapper));
}

RefPtr<ListPaintMethod> ListLayoutTestNg::UpdateOverlayModifier(RefPtr<PaintWrapper> paintWrapper)
{
    auto paintMethod = AceType::DynamicCast<ListPaintMethod>(paintWrapper->nodePaintImpl_);
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return paintMethod;
}

void ListLayoutTestNg::UpdateDividerMap()
{
    int cur = 0;
    for (auto& child : pattern_->itemPosition_) {
        child.second.id += cur;
        cur++;
    }
    UpdateContentModifier();
}

void ListLayoutTestNg::PaintDivider(RefPtr<PaintWrapper> paintWrapper, int32_t expectLineNumber, bool isClip)
{
    auto paintMethod = AceType::DynamicCast<ListPaintMethod>(paintWrapper->nodePaintImpl_);
    auto modifier = paintMethod->GetContentModifier(nullptr);
    auto listContentModifier = AceType::DynamicCast<ListContentModifier>(modifier);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(isClip ? 1 : 0);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(expectLineNumber); // DrawLine
    DrawingContext drawingContext = { canvas, LIST_WIDTH, LIST_HEIGHT };
    paintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    listContentModifier->onDraw(drawingContext);
}

void ListLayoutTestNg::GroupPaintDivider(RefPtr<PaintWrapper> paintWrapper, int32_t expectLineNumber)
{
    auto paintMethod = AceType::DynamicCast<ListItemGroupPaintMethod>(paintWrapper->nodePaintImpl_);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(expectLineNumber); // DrawLine
    paintMethod->PaintDivider(AceType::RawPtr(paintWrapper), canvas);
}

/**
 * @tc.name: GetOverScrollOffset001
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, GetOverScrollOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. !IsScrollSnapAlignCenter
     */
    CreateList();
    CreateListItemGroups(2);
    CreateDone(frameNode_);
    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollTo(ITEM_HEIGHT);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step2. !IsScrollSnapAlignCenter
     */
    ClearOldNodes();
    CreateList();
    CreateListItemGroups(1);
    CreateDone(frameNode_);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 5);
    expectOffset = { 500, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollTo(ITEM_HEIGHT);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step3. IsScrollSnapAlignCenter
     */
    ClearOldNodes();
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    CreateListItemGroups(2);
    CreateDone(frameNode_);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 4);
    expectOffset = { 0, -ITEM_HEIGHT * 3 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step4. has no group, groupAtStart and groupAtEnd are false
     */
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
}

/**
 * @tc.name: ContentEndOffset001
 * @tc.desc: Test ContentEndOffset should change behavior of IsAtBottom
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentEndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    model.SetEdgeEffect(EdgeEffect::FADE, false);
    model.SetContentEndOffset(100);
    // total height = 1600
    CreateListItems(16);
    CreateDone(frameNode_);
    std::vector<int32_t> scrollFromVector = { SCROLL_FROM_NONE, SCROLL_FROM_UPDATE, SCROLL_FROM_ANIMATION,
        SCROLL_FROM_JUMP, SCROLL_FROM_ANIMATION_SPRING, SCROLL_FROM_BAR, SCROLL_FROM_ANIMATION_CONTROLLER,
        SCROLL_FROM_BAR_FLING };

    // ~ -1200 to reach bottom if no contentEndOffset
    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-1195, SCROLL_FROM_UPDATE));
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());

    // contentEndOffset_ takes 100 extra offset to reach bottom
    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-50, SCROLL_FROM_UPDATE));
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(pattern_->IsAtBottom());

    EXPECT_TRUE(pattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: ContentOffset001
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     * @tc.expected: Total Offset is negative contentStartOffset.
     */
    const int32_t itemNumber = 10;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    CreateListItems(itemNumber);
    CreateDone(frameNode_);
    for (int32_t index = 0; index < 3; index++) {
        EXPECT_EQ(GetChildRect(frameNode_, index).GetY(), contentStartOffset + index * ITEM_HEIGHT);
    }

    float offset = pattern_->GetTotalOffset();
    EXPECT_FLOAT_EQ(offset, -contentStartOffset);

    /**
     * @tc.steps: step2. scroll to bottom
     * @tc.expected: Bottom content offset equal to contentEndOffset.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    offset = pattern_->GetTotalOffset();
    EXPECT_FLOAT_EQ(offset, itemNumber * ITEM_HEIGHT - LIST_HEIGHT + contentEndOffset);

    /**
     * @tc.steps: step3. scroll to top
     * @tc.expected: Bottom content offset equal to contentEndOffset.
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    offset = pattern_->GetTotalOffset();
    EXPECT_FLOAT_EQ(offset, -contentStartOffset);
}

/**
 * @tc.name: ContentOffset002
 * @tc.desc: Test scroll to Index with content offset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    CreateListItems(itemNumber);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. scroll to target item align start.
     * @tc.expected: check whether the offset is correct.
     */
    EXPECT_TRUE(ScrollToIndex(0, false, ScrollAlign::START, -contentStartOffset));
    EXPECT_TRUE(ScrollToIndex(1, false, ScrollAlign::START, ITEM_HEIGHT - contentStartOffset));
    EXPECT_TRUE(ScrollToIndex(2, false, ScrollAlign::START, ITEM_HEIGHT * 2 - contentStartOffset));
    ScrollToIndex(0, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetTotalOffset(), -contentStartOffset);
    ScrollToIndex(1, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT - contentStartOffset);
    ScrollToIndex(2, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 2 - contentStartOffset);

    /**
     * @tc.steps: step3. scroll to target item align end.
     * @tc.expected: check whether the offset is correct.
     */
    const float MAX_OFFSET = itemNumber * ITEM_HEIGHT - LIST_HEIGHT + contentEndOffset;
    EXPECT_TRUE(ScrollToIndex(itemNumber - 1, false, ScrollAlign::END, MAX_OFFSET));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 2, false, ScrollAlign::END, MAX_OFFSET - ITEM_HEIGHT));
    EXPECT_TRUE(ScrollToIndex(itemNumber - 3, false, ScrollAlign::END, MAX_OFFSET - ITEM_HEIGHT * 2));
    ScrollToIndex(itemNumber - 1, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetTotalOffset(), MAX_OFFSET);
    ScrollToIndex(itemNumber - 2, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetTotalOffset(), MAX_OFFSET - ITEM_HEIGHT);
    ScrollToIndex(itemNumber - 3, true, ScrollAlign::END);
    EXPECT_EQ(pattern_->GetTotalOffset(), MAX_OFFSET - ITEM_HEIGHT * 2);
}

/**
 * @tc.name: ContentOffset003
 * @tc.desc: Test scroll to ListItemGroup with content offset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t GroupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    CreateListItemGroups(GroupNumber);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. scroll to target group align start.
     * @tc.expected: check whether the offset is correct.
     */
    for (int32_t i = 0; i < 3; i++) {
        ScrollToIndex(i, false, ScrollAlign::START);
        EXPECT_EQ(GetChildRect(frameNode_, i).GetY(), contentStartOffset);
    }
    for (int32_t i = 0; i < 3; i++) {
        ScrollToIndex(i, true, ScrollAlign::START);
        EXPECT_EQ(GetChildRect(frameNode_, i).GetY(), contentStartOffset);
    }

    /**
     * @tc.steps: step3. scroll to target group align end.
     * @tc.expected: check whether the offset is correct.
     */
    for (int32_t i = 0; i < 3; i++) {
        int32_t index = GroupNumber - i - 1;
        ScrollToIndex(index, false, ScrollAlign::END);
        auto rect = GetChildRect(frameNode_, index);
        EXPECT_EQ(rect.Bottom(), LIST_HEIGHT - contentEndOffset);
    }
    for (int32_t i = 0; i < 3; i++) {
        int32_t index = GroupNumber - i - 1;
        ScrollToIndex(index, true, ScrollAlign::END);
        auto rect = GetChildRect(frameNode_, index);
        EXPECT_EQ(rect.Bottom(), LIST_HEIGHT - contentEndOffset);
    }
}

/**
 * @tc.name: ContentOffset004
 * @tc.desc: Test ListItemGroup Sticky postion
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t groupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    CreateGroupWithSetting(groupNumber, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Scroll To ListItem in group.
     * @tc.expected: ListItem position is correct.
     */
    ScrollToItemInGroup(1, 0, false, ScrollAlign::START);
    auto group1 = GetChildFrameNode(frameNode_, 1);
    auto groupRect = group1->GetGeometryNode()->GetFrameRect();
    float groupPos = groupRect.Top();
    auto item1Rect = GetChildRect(group1, 2);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset - groupPos);

    ScrollToItemInGroup(2, 1, false, ScrollAlign::END);
    auto group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    auto item2Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);

    ScrollToItemInGroup(1, 0, true, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupRect = group1->GetGeometryNode()->GetFrameRect();
    groupPos = groupRect.Top();
    item1Rect = GetChildRect(group1, 2);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset - groupPos);

    ScrollToItemInGroup(2, 1, true, ScrollAlign::END);
    group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    item2Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);
}

/**
 * @tc.name: ContentOffset005
 * @tc.desc: Test ListItemGroup Sticky postion
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    const int32_t groupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    model.SetSticky(V2::StickyStyle::BOTH);
    CreateGroupWithSetting(groupNumber, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. scroll by 100.
     * @tc.expected: header stick postion and footer sticky postion is correct.
     */
    pattern_->UpdateCurrentOffset(-100, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    auto group0 = GetChildFrameNode(frameNode_, 0);
    auto groupPos = group0->GetGeometryNode()->GetFrameRect().Top();
    auto header0Rect = GetChildRect(group0, 0);
    EXPECT_EQ(header0Rect.Top(), contentStartOffset - groupPos);

    auto group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    auto footer1Rect = GetChildRect(group1, 1);
    EXPECT_EQ(footer1Rect.Bottom(), 100.f);

    /**
     * @tc.steps: step3. Scroll To ListItem in group.
     * @tc.expected: ListItem position is correct.
     */
    ScrollToItemInGroup(1, 0, false, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    auto item1Rect = GetChildRect(group1, 2);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset + GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(2, 1, false, ScrollAlign::END);
    auto group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    auto item2Rect = GetChildRect(group2, 3);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(1, 0, true, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    item1Rect = GetChildRect(group1, 2);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset + GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(2, 1, true, ScrollAlign::END);
    group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    item2Rect = GetChildRect(group2, 3);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - GROUP_HEADER_LEN - groupPos);
}

/**
 * @tc.name: ContentOffset006
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List with ScrollSnapAlign START
     * @tc.expected:
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateListItems(itemNumber);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. scroll snap
     * @tc.expected: item top snap to contentEndOffset.
     */
    ScrollSnap(-120, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT - contentStartOffset);
    ScrollSnap(-80, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT * 2 - contentStartOffset);

    /**
     * @tc.steps: step3. change scroll snap to END
     * @tc.expected: item bottom snap to contentEndOffset.
     */
    ClearOldNodes();
    model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    CreateListItems(itemNumber);
    CreateDone(frameNode_);
    ScrollSnap(-40, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), -100);
    ScrollSnap(-110, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 50);
}

/**
 * @tc.name: ContentOffset007
 * @tc.desc: Test List edge check
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List with ScrollSnapAlign START
     * @tc.expected: not OutOfBoundary
     */
    const float contentStartOffset = 50;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateDone(frameNode_);

    EXPECT_FALSE(pattern_->IsOutOfBoundary());
}

/**
 * @tc.name: ContentOffset008
 * @tc.desc: Test List edge check
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ContentOffset008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List without item
     * @tc.expected: not contentStartOffset
     */
    const float contentStartOffset = 50;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    CreateListItems(0);
    CreateDone(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0.0f);

    /**
     * @tc.steps: step2. add ListItem
     * @tc.expected: ListItem position is correct.
     */
    AddItems(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), -50.0f);
}

/**
 * @tc.name: PaintMethod001
 * @tc.desc: Test paint method when has no ListItem in List and in ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has no ListItem
     * @tc.expected: UnScrollable, not need paint scrollBar, not DrawLine
     */
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    CreateListItemGroup(V2::ListItemGroupStyle::NONE); // no ListItem in ListItemGroup
    auto paintWrapper = CreateDone(frameNode_);

    /**
     * @tc.steps: step2. UnScrollable List
     * @tc.expected: Not need paint scrollBar
     */
    auto paintMethod = UpdateOverlayModifier(paintWrapper);
    auto scrollBarOverlayModifier = paintMethod->scrollBarOverlayModifier_.Upgrade();
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_FALSE(scrollBar->NeedPaint());
    PaintDivider(paintWrapper, 0);

    /**
     * @tc.steps: step3. No ListItem in ListItemGroup
     * @tc.expected: Not DrawLine
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    GroupPaintDivider(groupPaintWrapper, 0);
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: Test List paint method about UpdateOverlayModifier(scroll bar)
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayMode ON
     * @tc.expected: Has scrollbar and on the right
     */
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    CreateListItems(TOTAL_ITEM_NUMBER);
    auto paintWrapper = CreateDone(frameNode_);
    RefPtr<ListPaintMethod> paintMethod = UpdateOverlayModifier(paintWrapper);
    auto scrollBarOverlayModifier = paintMethod->scrollBarOverlayModifier_.Upgrade();
    auto scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);
    EXPECT_TRUE(scrollBar->NeedPaint());

    /**
     * @tc.steps: step2. Change axis to HORIZONTAL
     * @tc.expected: The scrollbar and on the bottom
     */
    model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    model.SetListDirection(Axis::HORIZONTAL);
    CreateListItems(TOTAL_ITEM_NUMBER);
    paintWrapper = CreateDone(frameNode_);
    paintMethod = UpdateOverlayModifier(paintWrapper);
    scrollBarOverlayModifier = paintMethod->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::BOTTOM);

    /**
     * @tc.steps: step3. Set DisplayMode::OFF
     * @tc.expected: Has no scrollbar
     */
    model = CreateList();
    model.SetScrollBar(DisplayMode::OFF);
    CreateListItems(TOTAL_ITEM_NUMBER);
    paintWrapper = CreateDone(frameNode_);
    paintMethod = UpdateOverlayModifier(paintWrapper);
    scrollBar = paintMethod->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar, nullptr);
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test List paint method about PaintDivider in diff Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set divider
     * @tc.expected: Not DrawLine
     */
    ListModelNG model = CreateList();
    // Group
    ListItemGroupModelNG groupModel = CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItems(2);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    // ListItems
    CreateListItems(2);
    auto paintWrapper = CreateDone(frameNode_);
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 0);
    GroupPaintDivider(groupPaintWrapper, 0);

    /**
     * @tc.steps: step2. Set divider
     * @tc.expected: DrawLine, call times depends on the divider number in view
     */
    model.SetDivider(AceType::RawPtr(frameNode_), ITEM_DIVIDER);
    groupModel.SetDivider(AceType::RawPtr(groupFrameNode), ITEM_DIVIDER);
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 2);
    GroupPaintDivider(groupPaintWrapper, 1);

    /**
     * @tc.steps: step3. Set lanes>1
     * @tc.expected: DrawLine, call times depends on the divider number in view
     */
    model.SetLanes(AceType::RawPtr(frameNode_), 2);
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 2);
    GroupPaintDivider(groupPaintWrapper, 0);

    /**
     * @tc.steps: step4. Set padding
     * @tc.expected: Trigger ClipRect
     */
    ViewAbstract::SetPadding(AceType::RawPtr(frameNode_), CalcLength(10.f));
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 2, true);
    GroupPaintDivider(groupPaintWrapper, 0);
}

/**
 * @tc.name: PaintMethod004
 * @tc.desc: Test ListItemGroup paint method about PaintDivider with diff args
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod004, TestSize.Level1)
{
    auto itemDivider = ITEM_DIVIDER;
    ListModelNG model = CreateList();
    model.SetDivider(itemDivider);
    // Group
    ListItemGroupModelNG groupModel = CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    groupModel.SetDivider(itemDivider);
    CreateListItems(2);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    // ListItems
    CreateListItems(2);
    auto paintWrapper = CreateDone(frameNode_);
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    auto groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(groupPaintWrapper->nodePaintImpl_);

    /**
     * @tc.steps: step1. strokeWidth > 0
     * @tc.expected: DrawLine, call times depends on the divider number in view
     */
    PaintDivider(paintWrapper, 2);
    GroupPaintDivider(groupPaintWrapper, 1);

    /**
     * @tc.steps: step2. strokeWidth > 0, but PERCENT
     * @tc.expected: Not DrawLine
     */
    itemDivider.strokeWidth = Dimension(STROKE_WIDTH, DimensionUnit::PERCENT);
    model.SetDivider(AceType::RawPtr(frameNode_), itemDivider);
    groupModel.SetDivider(AceType::RawPtr(groupFrameNode), itemDivider);
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 0);
    GroupPaintDivider(groupPaintWrapper, 0);

    /**
     * @tc.steps: step3. strokeWidth < 0
     * @tc.expected: Not DrawLine
     */
    itemDivider.strokeWidth = Dimension(-1);
    model.SetDivider(AceType::RawPtr(frameNode_), itemDivider);
    groupModel.SetDivider(AceType::RawPtr(groupFrameNode), itemDivider);
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 0);
    GroupPaintDivider(groupPaintWrapper, 0);

    /**
     * @tc.steps: step4. startMargin + endMargin == LIST_WIDTH
     * @tc.expected: Not DrawLine
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.startMargin = Dimension(LIST_WIDTH / 2);
    itemDivider.endMargin = Dimension(LIST_WIDTH / 2);
    model.SetDivider(AceType::RawPtr(frameNode_), itemDivider);
    groupModel.SetDivider(AceType::RawPtr(groupFrameNode), itemDivider);
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 0);
    GroupPaintDivider(groupPaintWrapper, 0);

    /**
     * @tc.steps: step5. startMargin + endMargin > LIST_WIDTH
     * @tc.expected: Rest margin and DrawLine
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.startMargin = Dimension(LIST_WIDTH / 2);
    itemDivider.endMargin = Dimension(LIST_WIDTH / 2 + 1);
    model.SetDivider(AceType::RawPtr(frameNode_), itemDivider);
    groupModel.SetDivider(AceType::RawPtr(groupFrameNode), itemDivider);
    paintWrapper = FlushLayoutTask(frameNode_);
    groupPaintWrapper = FlushLayoutTask(groupFrameNode);
    PaintDivider(paintWrapper, 2);
    GroupPaintDivider(groupPaintWrapper, 1);
}

/**
 * @tc.name: PaintMethod005
 * @tc.desc: Test List paint method about UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set divider startMargin and endMargin normal value
     * @tc.expected: offset.GetX() == startMargin and length = LIST_WIDTH - startMargin - endMargin
     */
    auto itemDivider = ITEM_DIVIDER;
    ListModelNG model = CreateList();
    model.SetDivider(itemDivider);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    auto renderContext = frameNode_->GetRenderContext();
    renderContext->UpdatePaintRect(frameNode_->GetGeometryNode()->GetFrameRect());
    UpdateDividerMap();
    auto dividerList = pattern_->listContentModifier_->dividerList_->Get();
    auto dividerMap = AceType::DynamicCast<ListDividerArithmetic>(dividerList)->GetDividerMap();
    EXPECT_EQ(dividerMap.size(), 4);
    auto length = LIST_WIDTH - (ITEM_DIVIDER.startMargin + ITEM_DIVIDER.endMargin).ConvertToPx();
    EXPECT_EQ(pattern_->listContentModifier_->width_, ITEM_DIVIDER.strokeWidth.ConvertToPx());
    for (auto child : dividerMap) {
        EXPECT_EQ(child.second.offset.GetX(), ITEM_DIVIDER.startMargin.ConvertToPx());
        EXPECT_EQ(child.second.length, length);
    }

    /**
     * @tc.steps: step2. Set divider startMargin and endMargin abnormal value
     * @tc.expected: startMargin == 0 and endMargin == 0
     */
    std::vector<V2::ItemDivider> dividerArray = { { Dimension(10), Dimension(-10), Dimension(-10) },
        { Dimension(10), Dimension(LIST_WIDTH), Dimension(LIST_WIDTH) },
        { Dimension(10), Dimension(10, DimensionUnit::PERCENT), Dimension(10, DimensionUnit::PERCENT) } };
    for (auto itemDivider : dividerArray) {
        layoutProperty_->UpdateDivider(itemDivider);
        FlushLayoutTask(frameNode_);
        auto renderContext = frameNode_->GetRenderContext();
        renderContext->UpdatePaintRect(frameNode_->GetGeometryNode()->GetFrameRect());
        UpdateDividerMap();
        dividerList = pattern_->listContentModifier_->dividerList_->Get();
        dividerMap = AceType::DynamicCast<ListDividerArithmetic>(dividerList)->GetDividerMap();
        EXPECT_EQ(dividerMap.size(), 4);
        EXPECT_EQ(pattern_->listContentModifier_->width_, itemDivider.strokeWidth.ConvertToPx());
        for (auto child : dividerMap) {
            EXPECT_EQ(child.second.offset.GetX(), 0.f);
            EXPECT_EQ(child.second.length, LIST_WIDTH);
        }
    }
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test list_pattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set multiSelectable_ to true
     * @tc.expected: InitMouseEvent() triggered by OnModifyDone()
     */
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::ON);
    model.SetMultiSelectable(true);
    CreateListItems(TOTAL_ITEM_NUMBER);
    ViewStackProcessor::GetInstance()->Finish();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    EXPECT_NE(pattern_->GetScrollableEvent(), nullptr);
    ASSERT_NE(pattern_->GetScrollBar(), nullptr);
    EXPECT_EQ(pattern_->GetScrollBar()->GetDisplayMode(), DisplayMode::ON);
    EXPECT_TRUE(pattern_->isMouseEventInit_);

    /**
     * @tc.steps: step2. Call OnDirtyLayoutWrapperSwap()
     * @tc.expected: isInitialized_ would be true
     */
    EXPECT_FALSE(pattern_->isInitialized_);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->isInitialized_);

    /**
     * @tc.steps: step3. When isMouseEventInit_ is true, Call OnModifyDone()
     * @tc.expected: UninitMouseEvent() would not be triggered, isMouseEventInit_ is still be true
     */
    pattern_->OnModifyDone();
    EXPECT_TRUE(pattern_->isMouseEventInit_);

    /**
     * @tc.steps: step4. Change multiSelectable_ to false, call OnModifyDone()
     * @tc.expected: UninitMouseEvent() triggered
     */
    pattern_->SetMultiSelectable(false);
    EXPECT_FALSE(pattern_->multiSelectable_);
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->isMouseEventInit_);
}

/**
 * @tc.name: Pattern003
 * @tc.desc: Test OutBoundaryCallback
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern003, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_NE(pattern_->scrollableEvent_, nullptr);
    auto scrollable = pattern_->scrollableEvent_->GetScrollable();
    EXPECT_NE(scrollable, nullptr);
    scrollable->isTouching_ = true;
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    ScrollTo(ITEM_HEIGHT * 2);
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    UpdateCurrentOffset(-ITEM_HEIGHT * 2);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    ClearOldNodes();
    ListModelNG model = CreateList();
    model.SetChainAnimation(true);
    model.SetChainAnimationOptions({ Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_NE(pattern_->scrollableEvent_, nullptr);
    scrollable = pattern_->scrollableEvent_->GetScrollable();
    EXPECT_NE(scrollable, nullptr);
    scrollable->isTouching_ = true;
    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    UpdateCurrentOffset(ITEM_HEIGHT);
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern006, TestSize.Level1)
{
    int32_t lanes = 2;
    ListModelNG model = CreateList();
    model.SetLanes(lanes);
    CreateListItems(VIEW_ITEM_NUMBER * lanes);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. When lanes > 1, call GetItemIndexByPosition
     * @tc.expected: Would return correct itemIndex
     */
    const Point point = Point(150.f, 250.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 5);
}

/**
 * @tc.name: Pattern007
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has ListItem, position not at any ListItem
     * @tc.expected: Would return the last itemIndex
     */
    CreateList();
    CreateListItems(VIEW_ITEM_NUMBER);
    CreateDone(frameNode_);
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, VIEW_ITEM_NUMBER);
}

/**
 * @tc.name: Pattern008
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has no ListItem, call GetItemIndexByPosition
     * @tc.expected: Would return 0
     */
    CreateList();
    CreateDone(frameNode_);
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: ListSize001
 * @tc.desc: Test List size in diff condition
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set size to List, but no ListItems
     * @tc.expected: List with is rootWidth
     */
    const float rootWidth = MockPipelineContext::GetCurrent()->rootWidth_;
    ListModelNG model;
    model.Create();
    GetList();
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), rootWidth);

    /**
     * @tc.steps: step2. Not set size to List and has ListItems
     * @tc.expected: List with is rootWidth
     */
    model.Create();
    CreateListItems(TOTAL_ITEM_NUMBER);
    GetList();
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), rootWidth);

    /**
     * @tc.steps: step3. Set List width to Infinity
     * @tc.expected: List with is Infinity
     */
    CreateList();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), Infinity<float>());

    /**
     * @tc.steps: step4. Set List width to Infinity, but no ListItems
     * @tc.expected: List with is 0
     */
    ClearOldNodes();
    CreateList();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    CreateDone(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0.f);
}

/**
 * @tc.name: Pattern011
 * @tc.desc: Test ContentStartOffset and ContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern011, TestSize.Level1)
{
    /**
     * @tc.cases: contentStartOffset_ + contentEndOffset_ < contentMainSize
     * @tc.expected: contentStartOffset_ = 10.f and contentEndOffset_ = 10.f
     */
    ListModelNG model = CreateList();
    model.SetContentStartOffset(10.f);
    model.SetContentEndOffset(10.f);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_EQ(layoutProperty_->GetContentStartOffsetValue(), 10.f);
    EXPECT_EQ(layoutProperty_->GetContentEndOffsetValue(), 10.f);
    EXPECT_EQ(pattern_->contentStartOffset_, 10.f);
    EXPECT_EQ(pattern_->contentEndOffset_, 10.f);
    EXPECT_EQ(pattern_->GetOffsetWithLimit(5.f), 0.f);
    EXPECT_EQ(pattern_->GetOffsetWithLimit(0.f), 0.f);
    EXPECT_EQ(pattern_->GetOffsetWithLimit(-5.f), -5.f);

    /**
     * @tc.cases: contentStartOffset_ + contentEndOffset_ >= contentMainSize
     * @tc.expected: contentStartOffset_ = 0.f and contentEndOffset_ = 0.f
     */
    model = CreateList();
    model.SetContentStartOffset(0.5f * LIST_HEIGHT);
    model.SetContentEndOffset(0.5f * LIST_HEIGHT);
    CreateListItems(20);
    CreateDone(frameNode_);
    EXPECT_EQ(layoutProperty_->GetContentStartOffsetValue(), 0.5f * LIST_HEIGHT);
    EXPECT_EQ(layoutProperty_->GetContentEndOffsetValue(), 0.5f * LIST_HEIGHT);
    EXPECT_EQ(pattern_->contentStartOffset_, 0.f);
    EXPECT_EQ(pattern_->contentEndOffset_, 0.f);
}

/**
 * @tc.name: Pattern014
 * @tc.desc: Test add a listItem and scroll to the added listItem within the same frame
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create an empty list
     */
    ListModelNG model = CreateList();
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. add a listItem and scroll to the added listItem within the same frame.
     * @tc.expected: layoutDirection = LayoutDirection::NONE
     */
    ViewStackProcessor::GetInstance()->Push(frameNode_);
    CreateListItems(1);
    auto startIndex = pattern_->GetStartIndex();
    ScrollToIndex(0, true, ScrollAlign::END);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 1);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, frameNode_->GetGeometryNode(), layoutProperty_);
    auto layoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    auto layoutDirection = layoutAlgorithm->LayoutDirectionForTargetIndex(&layoutWrapper, startIndex);
    EXPECT_EQ(layoutDirection, LayoutDirection::NONE);

    CreateListItems(1);
    startIndex = pattern_->GetStartIndex();
    ScrollToIndex(1, true, ScrollAlign::END);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 2);
    layoutAlgorithm = AceType::DynamicCast<ListLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutDirection = layoutAlgorithm->LayoutDirectionForTargetIndex(&layoutWrapper, startIndex);
    EXPECT_EQ(layoutDirection, LayoutDirection::NONE);
    ViewStackProcessor::GetInstance()->Pop();
}

/**
 * @tc.name: ListItemGroupCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemGroupCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItemGroup.
     * @tc.expected: step2. create a card style ListItemGroup success.
     */
    ListItemGroupModelNG groupModel;
    groupModel.Create(V2::ListItemGroupStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(pattern->GetListItemGroupStyle(), V2::ListItemGroupStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(GROUP_MARGIN));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right.value(), CalcLength(GROUP_MARGIN));
}

/**
 * @tc.name: ListItemCreateForCardModeTest001
 * @tc.desc: Test the initialization of listItem in card mode.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemCreateForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(pattern->GetListItemStyle(), V2::ListItemStyle::CARD);

    /**
     * @tc.steps: step3. compare the obtained value with the set value.
     * @tc.expected: step3. the obtained value is equal to the set value.
     */
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::WHITE);
}

/**
 * @tc.name: ListItemHoverEventForCardModeTest001
 * @tc.desc: Test the hover event when the hover status of card mode listItem is true.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemHoverEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to true.
     * @tc.expected: step3. the hover status is true.
     */
    pattern->HandleHoverEvent(true, frameNode);
    EXPECT_TRUE(pattern->isHover_);

    /**
     * @tc.steps: step3. call function HandleHoverEvent and Set hover status to false.
     * @tc.expected: step3. the hover status is false.
     */
    pattern->HandleHoverEvent(false, frameNode);
    EXPECT_FALSE(pattern->isHover_);
}

/**
 * @tc.name: ListItemPressEventForCardModeTest001
 * @tc.desc: Test the press event when the TouchType is DOWN.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemPressEventForCardModeTest001, TestSize.Level1)
{
    CreateList();
    CreateListItem(V2::ListItemStyle::CARD);
    CreateDone(frameNode_);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, 0);
    auto handleHoverEvent = itemPattern->hoverEvent_->GetOnHoverEventFunc();
    auto itemNode = GetChildFrameNode(frameNode_, 0);
    auto gesture = itemNode->GetOrCreateGestureEventHub();
    auto handlePressEvent = gesture->touchEventActuator_->touchEvents_.back()->GetTouchEventCallback();

    /**
     * @tc.steps: step1. Hover and Touch Down/Move/Up
     */
    handleHoverEvent(true);
    EXPECT_TRUE(itemPattern->isHover_);
    EXPECT_EQ(itemPattern->GetBlendGgColor(), HOVER_COLOR);

    TouchEventInfo info = CreateTouchEventInfo(TouchType::DOWN, Offset());
    handlePressEvent(info);
    EXPECT_TRUE(itemPattern->isPressed_);
    EXPECT_EQ(itemPattern->GetBlendGgColor(), PRESS_COLOR);

    info = CreateTouchEventInfo(TouchType::MOVE, Offset());
    handlePressEvent(info);
    EXPECT_TRUE(itemPattern->isPressed_);
    EXPECT_EQ(itemPattern->GetBlendGgColor(), PRESS_COLOR);

    info = CreateTouchEventInfo(TouchType::UP, Offset());
    handlePressEvent(info);
    EXPECT_FALSE(itemPattern->isPressed_);
    EXPECT_EQ(itemPattern->GetBlendGgColor(), HOVER_COLOR);

    handleHoverEvent(false);
    EXPECT_FALSE(itemPattern->isHover_);
    EXPECT_EQ(itemPattern->GetBlendGgColor(), Color::TRANSPARENT);

    /**
     * @tc.steps: step2. Touch Down/Cancel
     */
    info = CreateTouchEventInfo(TouchType::DOWN, Offset());
    handlePressEvent(info);
    EXPECT_TRUE(itemPattern->isPressed_);

    info = CreateTouchEventInfo(TouchType::CANCEL, Offset());
    handlePressEvent(info);
    EXPECT_FALSE(itemPattern->isPressed_);
}

/**
 * @tc.name: ListItemDisableEventForCardModeTest001
 * @tc.desc: Test InitDisableEvent
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemDisableEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ListItem in card mode.
     * @tc.expected: create a card style ListItem success and set enable status to false.
     */
    CreateList();
    CreateListItem(V2::ListItemStyle::CARD);
    CreateDone(frameNode_);
    auto itemNode = GetChildFrameNode(frameNode_, 0);
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, 0);
    auto itemEventHub = GetChildEventHub<ListItemEventHub>(frameNode_, 0);
    auto itemRenderContext = itemNode->GetRenderContext();
    EXPECT_TRUE(itemEventHub->IsEnabled());
    EXPECT_TRUE(itemEventHub->IsDeveloperEnabled());
    EXPECT_EQ(itemRenderContext->GetOpacity(), 1.0);

    itemEventHub->SetEnabled(false);
    itemPattern->OnModifyDone(); // Test InitDisableEvent
    EXPECT_FALSE(itemPattern->Selectable());
    EXPECT_FALSE(itemEventHub->IsEnabled());
    EXPECT_FALSE(itemEventHub->IsDeveloperEnabled());
    EXPECT_EQ(itemRenderContext->GetOpacity(), 0.4);

    itemPattern->OnModifyDone();
    EXPECT_FALSE(itemPattern->Selectable());

    itemEventHub->SetEnabled(true);
    itemPattern->OnModifyDone();
    EXPECT_FALSE(itemPattern->Selectable());
    EXPECT_EQ(itemRenderContext->GetOpacity(), 0.4);
}

/**
 * @tc.name: ListPattern_GetItemRect001
 * @tc.desc: Test the GetItemRect function of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListPattern_GetItemRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List then slide List by Scroller.
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone(frameNode_);
    pattern_->ScrollBy(ITEM_HEIGHT / 2.0f);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid ListItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(TOTAL_ITEM_NUMBER * 2 - 1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(TOTAL_ITEM_NUMBER * 2), Rect()));

    /**
     * @tc.steps: step3. Get ListItem Rect by GetItemRectInGroup.
     * @tc.expected: Return 0 when get ListItem Rect by GetItemRectInGroup.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect()));

    /**
     * @tc.steps: step4. Get valid ListItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(
        IsEqual(pattern_->GetItemRect(1), Rect(0, -ITEM_HEIGHT / 2.0f, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(3),
        Rect(0, -ITEM_HEIGHT / 2.0f + ITEM_HEIGHT * 2, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step5. Slide List by Scroller.
     */
    pattern_->ScrollToIndex(8);
    FlushLayoutTask(frameNode_);
    /**
     * @tc.steps: step6. Get invalid ListItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(7), Rect()));

    /**
     * @tc.steps: step7. Get valid ListItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(pattern_->GetEndIndex()),
        Rect(0, LIST_HEIGHT - ITEM_HEIGHT, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
}

/**
 * @tc.name: ListPattern_GetItemIndex001
 * @tc.desc: Test the GetItemIndex function of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListPattern_GetItemIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List then slide List by Scroller.
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone(frameNode_);
    pattern_->ScrollBy(ITEM_HEIGHT / 2.0f);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid ListItem index.
     * @tc.expected: Return -1 when input invalid x and y.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(100000, -100000), -1));

    /**
     * @tc.steps: step3. Get valid ListItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndex(FILL_LENGTH.Value() * LIST_WIDTH /2, ITEM_HEIGHT * 0.2), 1));
}

/**
 * @tc.name: ListPattern_GetItemIndexInGroup001
 * @tc.desc: Test the GetItemIndexInGroup function of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListPattern_GetItemIndexInGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List then slide List by Scroller.
     */
    ListModelNG model = CreateList();
    CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    pattern_->ScrollTo(ITEM_HEIGHT * 2);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid group item index.
     * @tc.expected: Return {-1, -1, -1} when input invalid group x and y.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemIndexInGroup(100000, -100000), {-1, -1, -1}));

    /**
     * @tc.steps: step3. Get valid group item index.
     * @tc.expected: Return actual index when input valid group x and y.
     */
    EXPECT_TRUE(IsEqual(
        pattern_->GetItemIndexInGroup(FILL_LENGTH.Value() * LIST_WIDTH* 0.9, ITEM_HEIGHT* 0.9), {0, 1, 2}));
}

/**
 * @tc.name: ListPattern_GetItemRectInGroup001
 * @tc.desc: Test the GetItemRectInGroup function of List.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListPattern_GetItemRectInGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List then slide List by Scroller.
     */
    ListModelNG model = CreateList();
    CreateListItemGroup(V2::ListItemGroupStyle::NONE);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    pattern_->ScrollTo(ITEM_HEIGHT * 2);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid group item Rect.
     * @tc.expected: Return 0 when input invalid group index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(-1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(2, -1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, TOTAL_ITEM_NUMBER), Rect()));

    /**
     * @tc.steps: step3. Get valid group item Rect.
     * @tc.expected: Return actual Rect when input valid group index.
     */
    EXPECT_TRUE(IsEqual(
        pattern_->GetItemRectInGroup(0, 2), Rect(0, 0, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step4. Get valid ListItemGroup Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0),
        Rect(0, -ITEM_HEIGHT * 2, LIST_WIDTH, ITEM_HEIGHT * TOTAL_ITEM_NUMBER)));
}

/**
 * @tc.name: ListLayout_SafeArea001
 * @tc.desc: Test list layout with expandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListLayout_SafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone(frameNode_);
    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea)
        .Times(1)
        .WillOnce(Return(SafeAreaInsets { {}, {}, {}, { .start = 0, .end = 100 } }));
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 100);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: ListLayout_SafeArea002
 * @tc.desc: Test list layout with expandSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListLayout_SafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(1);
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone(frameNode_);
    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea).Times(0);
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}

/**
 * @tc.name: PostListItemPressStyleTask001
 * @tc.desc: Test list layout with PostListItemPressStyleTask.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PostListItemPressStyleTask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetDivider(ITEM_DIVIDER);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    int cur = 0;
    for (auto& child : pattern_->itemPosition_) {
        child.second.id += cur;
        cur++;
    }
    auto renderContext = frameNode_->GetRenderContext();
    renderContext->UpdatePaintRect(frameNode_->GetGeometryNode()->GetFrameRect());
    UpdateContentModifier();
    auto dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    auto lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    auto dividerMap = lda->GetDividerMap();
    EXPECT_EQ(dividerMap.size(), 4);

    auto listItemNode = GetChildFrameNode(frameNode_, 0);
    auto listItemNodeId = listItemNode->GetId();
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(listItemNode);
    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_PRESSED);
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    for (auto child : listPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_TRUE(child.second.isPressed);
        }
    }

    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_EQ(dividerMap.size(), 3);
}

/**
 * @tc.name: PostListItemPressStyleTask002
 * @tc.desc: Test listItemGroup layout with PostListItemPressStyleTask.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PostListItemPressStyleTask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    model.SetDivider(ITEM_DIVIDER);
    CreateListItemGroups(TOTAL_ITEM_NUMBER);
    CreateDone(frameNode_);
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    int cur = 0;
    for (auto& child : groupPattern->itemPosition_) {
        child.second.id += cur;
        cur++;
    }

    auto listItemNode = GetChildFrameNode(groupFrameNode, 0);
    auto listItemNodeId = listItemNode->GetId();
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(listItemNode);
    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_PRESSED);
    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);
    for (auto child : groupPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_TRUE(child.second.isPressed);
        }
    }
}

/**
 * @tc.name: ChildrenMainSize005
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ChildrenMainSize005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     * @tc.expected: Default Size is 0
     */
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(0);
    childrenSize->ChangeData(0, 2, { 100.f, 100.f });
    childrenSize->ChangeData(4, 1, { 200.f });
    childrenSize->ChangeData(5, 8, { 100.f, 100.f, 100.f, 100.f, 100.f, 100.f, 100.f, 100.f });
    CreateListItems(2);
    CreateItemWithSize(2, SizeT<Dimension>(FILL_LENGTH, Dimension(0.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(8);
    CreateDone(frameNode_);
    EXPECT_TRUE(ScrollToIndex(1, false, ScrollAlign::START, 100.f));
    EXPECT_TRUE(ScrollToIndex(2, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(3, false, ScrollAlign::START, 200.f));
    EXPECT_TRUE(ScrollToIndex(4, false, ScrollAlign::START, 200.f));
}

/**
 * @tc.name: ChildrenMainSize006
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ChildrenMainSize006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create list
     * @tc.expected: Default Size is 100
     */
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(2, 2, { -100.f, 200.f });
    CreateListItems(2);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(-100.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(8);
    CreateDone(frameNode_);
    EXPECT_TRUE(ScrollToIndex(3, false, ScrollAlign::START, ITEM_HEIGHT));
    EXPECT_TRUE(ScrollToIndex(4, false, ScrollAlign::START, 300.f));

    /**
     * @tc.steps: step2. insert data
     * @tc.expected: childrenSize_.size() == 10
     */
    ClearOldNodes();
    model = CreateList();
    childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(8, 0, { 50.f, 200.f });
    CreateListItems(8);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->childrenSize_->childrenSize_.size(), 10);
    EXPECT_TRUE(ScrollToIndex(8, false, ScrollAlign::END, 450.f));
    EXPECT_TRUE(ScrollToIndex(9, false, ScrollAlign::END, 650.f));
}

/**
 * @tc.name: ListRepeatCacheCount001
 * @tc.desc: List cacheCount
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListRepeatCacheCount001, TestSize.Level1)
{
    ListModelNG model = CreateList();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    CreateRepeatVirtualScrollNode(10, [this](int32_t idx) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    });
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Check Repeat frameCount
     */
    auto repeat = AceType::DynamicCast<RepeatVirtualScrollNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_NE(repeat, nullptr);
    int32_t frameCount = repeat->FrameCount();
    EXPECT_EQ(frameCount, 10);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: ListItem 4 is cached
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    FlushIdleTask(listPattern);
    int32_t childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 5);
    auto cachedItem = frameNode_->GetChildByIndex(4)->GetHostNode();
    EXPECT_EQ(cachedItem->IsActive(), false);
    EXPECT_EQ(GetChildY(frameNode_, 4), LIST_HEIGHT);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: ListItem 1 and 7 is cached, ListItem 2,3,4,5,6 is active.
     */
    UpdateCurrentOffset(-250);
    FlushIdleTask(listPattern);
    childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 7);
    cachedItem = frameNode_->GetChildByIndex(1)->GetHostNode();
    EXPECT_EQ(cachedItem->IsActive(), false);
    cachedItem = frameNode_->GetChildByIndex(7)->GetHostNode();
    EXPECT_EQ(cachedItem->IsActive(), false);
    EXPECT_EQ(GetChildY(frameNode_, 1), -150.0f);
    EXPECT_EQ(GetChildY(frameNode_, 7), 450.0f);
}

/**
 * @tc.name: ListRepeatCacheCount002
 * @tc.desc: List lanes cacheCount
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListRepeatCacheCount002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetLanes(2);
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(GetElmtId());
    CreateRepeatVirtualScrollNode(20, [this](int32_t idx) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    });
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Check Repeat frameCount
     */
    auto repeat = AceType::DynamicCast<RepeatVirtualScrollNode>(frameNode_->GetChildAtIndex(0));
    EXPECT_NE(repeat, nullptr);
    int32_t frameCount = repeat->FrameCount();
    EXPECT_EQ(frameCount, 20);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: ListItem 8,9 is cached
     */
    auto listPattern = frameNode_->GetPattern<ListPattern>();
    FlushIdleTask(listPattern);
    int32_t childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 10);
    auto item8 = frameNode_->GetChildByIndex(8)->GetHostNode();
    EXPECT_EQ(item8->IsActive(), false);
    EXPECT_EQ(GetChildX(frameNode_, 8), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 8), LIST_HEIGHT);
    auto item9 = frameNode_->GetChildByIndex(9)->GetHostNode();
    EXPECT_EQ(item9->IsActive(), false);
    EXPECT_EQ(GetChildX(frameNode_, 9), LIST_WIDTH / 2);
    EXPECT_EQ(GetChildY(frameNode_, 9), LIST_HEIGHT);

    /**
     * @tc.steps: step2. Flush Idle Task
     * @tc.expected: ListItem 2,3,14,15 is cached, ListItem 4-13 active.
     */
    UpdateCurrentOffset(-250);
    FlushIdleTask(listPattern);
    childrenCount = repeat->GetChildren().size();
    EXPECT_EQ(childrenCount, 14);
    auto item2 = frameNode_->GetChildByIndex(2)->GetHostNode();
    EXPECT_EQ(item2->IsActive(), false);
    EXPECT_EQ(GetChildX(frameNode_, 2), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 2), -150.0f);
    auto item3 = frameNode_->GetChildByIndex(3)->GetHostNode();
    EXPECT_EQ(item3->IsActive(), false);
    EXPECT_EQ(GetChildX(frameNode_, 3), LIST_WIDTH / 2);
    EXPECT_EQ(GetChildY(frameNode_, 3), -150.0f);
    auto item14 = frameNode_->GetChildByIndex(14)->GetHostNode();
    EXPECT_EQ(item14->IsActive(), false);
    EXPECT_EQ(GetChildX(frameNode_, 14), 0.0f);
    EXPECT_EQ(GetChildY(frameNode_, 14), 450.0f);
    auto item15 = frameNode_->GetChildByIndex(15)->GetHostNode();
    EXPECT_EQ(item15->IsActive(), false);
    EXPECT_EQ(GetChildX(frameNode_, 15), LIST_WIDTH / 2);
    EXPECT_EQ(GetChildY(frameNode_, 15), 450.0f);
}

/**
 * @tc.name: SetHeaderFooterComponent01
 * @tc.desc: Test HeaderComponent/FooterComponent of ListItemGroup
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, SetHeaderFooterComponent01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List group with ComponentContent
     */
    const int32_t groupNumber = 5;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    model.SetSticky(V2::StickyStyle::BOTH);
    CreateGroupWithSettingWithComponentContent(groupNumber, V2::ListItemGroupStyle::NONE);
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. Get the count of group
     * @tc.expected: header and footer can be added successfully.
     */
    auto group0 = GetChildFrameNode(frameNode_, 0);
    auto group1 = GetChildFrameNode(frameNode_, 1);
    auto group0Children = group0->GetChildren();
    auto group1Children = group1->GetChildren();
    auto group0Pattern = group0->GetPattern<ListItemGroupPattern>();
    EXPECT_EQ(group0Children.size(), 4);
    EXPECT_EQ(group1Children.size(), 4);

    /**
     * @tc.steps: step3. Update header and footer
     * @tc.expected: new header and footer can be set.
     */
    bool headerResult = false;
    bool footerResult = false;
    group0Pattern->AddHeader(CreateCustomNode("NewHeader"));
    group0Pattern->AddFooter(CreateCustomNode("NewFooter"));
    const char newFooter[] = "NewFooter";
    const char newHeader[] = "NewHeader";
    auto children = group0->GetChildren();
    for (auto child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode->GetTag() == newHeader) {
            headerResult = true;
        }
        if (childFrameNode->GetTag() == newFooter) {
            footerResult = true;
        }
    }
    EXPECT_TRUE(headerResult);
    EXPECT_TRUE(footerResult);

    /**
     * @tc.steps: step4. Remove group0 header and footer
     * @tc.expected: header and footer can be removed successfully.
     */
    group0Pattern->RemoveHeader();
    group0Pattern->RemoveFooter();
    group0Children = group0->GetChildren();
    EXPECT_EQ(group0Children.size(), 2);
}

/**
 * @tc.name: ListScrollOffsetTest001
 * @tc.desc: list scroll offset test
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListScrollOffsetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List
     * @tc.expected: current offset is 250
     */
    ListModelNG model = CreateList();
    model.SetInitialIndex(4);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    for (int32_t i = 0; i < 9; i++) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone(frameNode_);
    EXPECT_EQ(pattern_->currentOffset_, 250);

    /**
     * @tc.steps: step2. Update center index height
     * @tc.expected: current offset is 260
     */
    auto centerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    ViewAbstract::SetHeight(AceType::RawPtr(centerNode), CalcLength(120));
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->currentOffset_, 260);

    /**
     * @tc.steps: step3. Update center index height
     * @tc.expected: current offset is 175
     */
    for (int32_t i = 3; i <= 5; i++) {
        auto centerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(i));
        ViewAbstract::SetHeight(AceType::RawPtr(centerNode), CalcLength(50));
    }
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->currentOffset_, 175);
}

/**
 * @tc.name: ListScrollOffsetTest002
 * @tc.desc: list scroll offset test
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListScrollOffsetTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List
     */
    ListModelNG model = CreateList();
    for (int32_t i = 0; i < 9; i++) {
        CreateListItem();
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone(frameNode_);

    /**
     * @tc.steps: step2. ScrollTo item2
     * @tc.expected: current offset is 250
     */
    UpdateCurrentOffset(-250);
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->currentOffset_, 250);

    /**
     * @tc.steps: step3. Update item1 height and scroll to item1
     * @tc.expected: current offset is 170
     */
    auto centerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(1));
    ViewAbstract::SetHeight(AceType::RawPtr(centerNode), CalcLength(120));
    UpdateCurrentOffset(100);
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->currentOffset_, 170);
}
} // namespace OHOS::Ace::NG
