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

namespace OHOS::Ace::NG {

namespace {} // namespace

class ListLayoutTestNg : public ListTestNg {
public:
    void UpdateContentModifier();
    RefPtr<ListPaintMethod> UpdateOverlayModifier();
    AssertionResult VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY);
};

void ListLayoutTestNg::UpdateContentModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateContentModifier(AceType::RawPtr(paintWrapper));
}

RefPtr<ListPaintMethod> ListLayoutTestNg::UpdateOverlayModifier()
{
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    listPaint->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    return listPaint;
}

AssertionResult ListLayoutTestNg::VerifySticky(int32_t groupIndex, bool isHeader, float expectOffsetY)
{
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, groupIndex);
    float offsetY = isHeader ? GetChildRect(groupNode, 0).GetY() : GetChildRect(groupNode, 1).GetY();
    return IsEqual(offsetY, expectOffsetY);
}

/**
 * @tc.name: ListItemGroup001
 * @tc.desc: Test ListItemGroup rect and itemPosition with V2::ListItemGroupStyle::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemGroup001, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GROUP_LINE_NUMBER * (ITEM_HEIGHT + SPACE) - SPACE + GROUP_HEADER_LEN * 2;
    RectF groupRect = GetChildRect(frameNode_, 0);
    RectF headRect = GetChildRect(groupNode, 0);
    RectF footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqual(groupRect, RectF(0, 0, LIST_WIDTH, groupHeight)));
    EXPECT_TRUE(IsEqual(headRect, RectF(0, 0, LIST_WIDTH, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(footRect, RectF(0, groupHeight - GROUP_HEADER_LEN, LIST_WIDTH, GROUP_HEADER_LEN)));
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, SPACE, GROUP_HEADER_LEN));
}

/**
 * @tc.name: ListItemGroup002
 * @tc.desc: Test ListItemGroup rect and itemPosition with V2::ListItemGroupStyle::CARD
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemGroup002, TestSize.Level1)
{
    Create([](ListModelNG model) { CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::CARD); });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GROUP_LINE_NUMBER * (ITEM_HEIGHT + SPACE) - SPACE + GROUP_HEADER_LEN * 2;
    RectF groupRect = GetChildRect(frameNode_, 0);
    RectF headRect = GetChildRect(groupNode, 0);
    RectF footRect = GetChildRect(groupNode, 1);
    EXPECT_TRUE(IsEqual(groupRect, RectF(12.f, 0, -60.f, groupHeight)));
    EXPECT_TRUE(IsEqual(headRect, RectF(0, 0, 456.f, GROUP_HEADER_LEN)));
    EXPECT_TRUE(IsEqual(footRect, RectF(0, groupHeight - GROUP_HEADER_LEN, 456.f, GROUP_HEADER_LEN)));
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, SPACE, GROUP_HEADER_LEN));
}

/**
 * @tc.name: ListItemGroup003
 * @tc.desc: List set sticky header and footer
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemGroup003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::StickyStyle::HEADER
     * @tc.expected: head is Sticky
     */
    Create([](ListModelNG model) {
        model.SetSticky(V2::StickyStyle::HEADER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    EXPECT_TRUE(VerifySticky(0, true, 0));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(0, true, ITEM_HEIGHT));

    /**
     * @tc.steps: step2. V2::StickyStyle::FOOTER
     * @tc.expected: foot is Sticky
     */
    Create([](ListModelNG model) {
        model.SetSticky(V2::StickyStyle::FOOTER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    float expectOffsetY = LIST_HEIGHT - GetChildRect(frameNode_, 0).Height() - GROUP_HEADER_LEN;
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY + ITEM_HEIGHT));

    /**
     * @tc.steps: step3. V2::StickyStyle::BOTH
     * @tc.expected: head/foot is Sticky
     */
    Create([](ListModelNG model) {
        model.SetSticky(V2::StickyStyle::BOTH);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    EXPECT_TRUE(VerifySticky(0, true, 0));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(0, true, ITEM_HEIGHT));
    ScrollUp();

    expectOffsetY = LIST_HEIGHT - GetChildRect(frameNode_, 0).Height() - GROUP_HEADER_LEN;
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY));
    ScrollDown();
    EXPECT_TRUE(VerifySticky(1, false, expectOffsetY + ITEM_HEIGHT));
}

/**
 * @tc.name: ListItemGroup004
 * @tc.desc: test lanes
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemGroup004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetLanes 2
     * @tc.expected: has 2 lanes items
     */
    int32_t lanes = 2;
    Create([lanes](ListModelNG model) {
        model.SetLanes(lanes);
        CreateGroup(1, Axis::VERTICAL);
    });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float groupHeight = GetChildRect(frameNode_, 0).Height();
    EXPECT_EQ(groupHeight, std::ceil(GROUP_LINE_NUMBER / lanes) * ITEM_HEIGHT);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, lanes, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step2. maxLaneLength > LIST_WIDTH
     * @tc.expected: has 1 lanes items
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(300.f));
        model.SetLaneMaxLength(Dimension(LIST_WIDTH + 100.f));
        CreateGroup(1, Axis::VERTICAL);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    float groupWidth = GetChildRect(frameNode_, 0).Width();
    EXPECT_EQ(groupWidth, LIST_WIDTH);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step3. maxLaneLength < LIST_WIDTH
     * @tc.expected: has 1 lanes items
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(300.f));
        model.SetLaneMaxLength(Dimension(400.f));
        CreateGroup(1, Axis::VERTICAL);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    groupWidth = GetChildRect(frameNode_, 0).Width();
    EXPECT_EQ(groupWidth, LIST_WIDTH);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, DEFAULT_SPACE, DEFAULT_STARTOFFSET));

    /**
     * @tc.steps: step4. SetLanes 2 with header/footer/space ...
     * @tc.expected: has 2 lanes items
     */
    lanes = 2;
    Create([lanes](ListModelNG model) {
        model.SetLanes(lanes);
        CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, lanes, SPACE, GROUP_HEADER_LEN));

    /**
     * @tc.steps: step5. set minLaneLength/maxLaneLength with header/footer/space ...
     * @tc.expected: headWidth would be maxLaneLength
     */
    Create([](ListModelNG model) {
        model.SetLaneMinLength(Dimension(300.f));
        model.SetLaneMaxLength(Dimension(400.f));
        CreateGroupWithSetting(1, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    groupNode = GetChildFrameNode(frameNode_, 0);
    float headWidth = GetChildRect(groupNode, 0).Width();
    EXPECT_EQ(headWidth, LIST_WIDTH);
    EXPECT_TRUE(VerifyPosition(groupNode, GROUP_LINE_NUMBER, DEFAULT_LANES, SPACE, GROUP_HEADER_LEN));
}

/**
 * @tc.name: ListItemGroup005
 * @tc.desc: test SetListItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemGroup005, TestSize.Level1)
{
    /**
     * @tc.steps: step2. V2::ListItemAlign::START
     */
    const float itemWidth = LIST_WIDTH - 100.f;
    Create([itemWidth](ListModelNG model) {
        model.SetListItemAlign(V2::ListItemAlign::START);
        {
            ListItemGroupModelNG groupModel;
            groupModel.Create(V2::ListItemGroupStyle::NONE);
            for (int32_t index = 0; index < GROUP_LINE_NUMBER; index++) {
                ListItemModelNG itemModel;
                itemModel.Create();
                ViewAbstract::SetWidth(CalcLength(itemWidth));
                ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
                ViewStackProcessor::GetInstance()->Pop();
            }
            ViewStackProcessor::GetInstance()->Pop();
        }
    });
    RefPtr<FrameNode> groupNode = GetChildFrameNode(frameNode_, 0);
    float itemOffsetX = GetChildRect(groupNode, 0).GetX();
    EXPECT_EQ(itemOffsetX, 0);

    /**
     * @tc.steps: step2. V2::ListItemAlign::CENTER
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    FlushLayoutTask(frameNode_);
    groupNode = GetChildFrameNode(frameNode_, 0);
    itemOffsetX = GetChildRect(groupNode, 0).GetX();
    EXPECT_EQ(itemOffsetX, (LIST_WIDTH - itemWidth) / 2);

    /**
     * @tc.steps: step3. V2::ListItemAlign::END
     */
    layoutProperty_->UpdateListItemAlign(V2::ListItemAlign::END);
    FlushLayoutTask(frameNode_);
    groupNode = GetChildFrameNode(frameNode_, 0);
    itemOffsetX = GetChildRect(groupNode, 0).GetX();
    EXPECT_EQ(itemOffsetX, LIST_WIDTH - itemWidth);
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
    Create([](ListModelNG model) { CreateGroup(2); });

    OverScrollOffset offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    OverScrollOffset expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step2. !IsScrollSnapAlignCenter
     */
    Create([](ListModelNG model) { CreateGroup(1); });

    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT * 5);
    expectOffset = { 500, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step3. IsScrollSnapAlignCenter
     */
    Create([](ListModelNG model) {
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
        CreateGroup(2);
    });

    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { ITEM_HEIGHT, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    ScrollDown();
    offset = pattern_->GetOverScrollOffset(ITEM_HEIGHT);
    expectOffset = { 0, 0 };
    EXPECT_TRUE(IsEqual(offset, expectOffset));
    offset = pattern_->GetOverScrollOffset(-ITEM_HEIGHT * 4);
    expectOffset = { 0, -ITEM_HEIGHT };
    EXPECT_TRUE(IsEqual(offset, expectOffset));

    /**
     * @tc.steps: step4. has no group, groupAtStart and groupAtEnd are false
     */
    CreateWithItem([](ListModelNG model) {});
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
    Create([](ListModelNG model) {
        // total height = 2000
        CreateItem(20);
        model.SetScrollBar(DisplayMode::ON);
        model.SetEdgeEffect(EdgeEffect::FADE, false);
        model.SetContentEndOffset(100);
    });

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
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateItem(itemNumber);
    });

    for (int32_t index = 0; index < 7; index++) {
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
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateItem(itemNumber);
    });

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
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateGroup(GroupNumber);
    });

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
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });

    /**
     * @tc.steps: step2. Scroll To ListItem in group.
     * @tc.expected: ListItem position is correct.
     */
    ScrollToItemInGroup(1, 1, false, ScrollAlign::START);
    auto group1 = GetChildFrameNode(frameNode_, 1);
    auto groupRect = group1->GetGeometryNode()->GetFrameRect();
    float groupPos = groupRect.Top();
    auto item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset - groupPos);

    ScrollToItemInGroup(2, 2, false, ScrollAlign::END);
    auto group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    auto item2Rect = GetChildRect(group1, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);

    ScrollToItemInGroup(1, 1, true, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupRect = group1->GetGeometryNode()->GetFrameRect();
    groupPos = groupRect.Top();
    item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset - groupPos);

    ScrollToItemInGroup(2, 2, true, ScrollAlign::END);
    group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    item2Rect = GetChildRect(group1, 4);
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
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        model.SetSticky(V2::StickyStyle::BOTH);
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });

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
    EXPECT_EQ(footer1Rect.Bottom(), LIST_HEIGHT - contentEndOffset - groupPos);

    /**
     * @tc.steps: step3. Scroll To ListItem in group.
     * @tc.expected: ListItem position is correct.
     */
    ScrollToItemInGroup(1, 1, false, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    auto item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset + GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(2, 2, false, ScrollAlign::END);
    auto group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    auto item2Rect = GetChildRect(group2, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(1, 1, true, ScrollAlign::START);
    group1 = GetChildFrameNode(frameNode_, 1);
    groupPos = group1->GetGeometryNode()->GetFrameRect().Top();
    item1Rect = GetChildRect(group1, 3);
    EXPECT_EQ(item1Rect.Top(), contentStartOffset + GROUP_HEADER_LEN - groupPos);

    ScrollToItemInGroup(2, 2, true, ScrollAlign::END);
    group2 = GetChildFrameNode(frameNode_, 2);
    groupPos = group2->GetGeometryNode()->GetFrameRect().Top();
    item2Rect = GetChildRect(group2, 4);
    EXPECT_EQ(item2Rect.Bottom(), LIST_HEIGHT - contentEndOffset - GROUP_HEADER_LEN - groupPos);
}

/**
 * @tc.name: ContentOffset006
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, DISABLED_ContentOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List with ScrollSnapAlign START
     * @tc.expected:
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    Create([=](ListModelNG model) {
        model.SetContentStartOffset(contentStartOffset);
        model.SetContentEndOffset(contentEndOffset);
        model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
        CreateItem(itemNumber);
    });

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
    float firstEndSnap = -contentEndOffset; // LIST_HEIGHT % ITEM_HEIGHT - contentEndOffset;
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    layoutProperty_->UpdateScrollSnapAlign(V2::ScrollSnapAlign::END);
    ScrollSnap(-40, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), firstEndSnap);
    ScrollSnap(-110, 0);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT + firstEndSnap);
}

/**
 * @tc.name: PaintMethod001
 * @tc.desc: Test List paint method about UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Not set divider
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    CreateWithItem([](ListModelNG model) {});
    UpdateContentModifier();
    auto dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    auto lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    auto dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step2. Set chainAnimation and divider
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    V2::ItemDivider itemDivider = ITEM_DIVIDER;
    CreateWithItem([itemDivider](ListModelNG model) {
        model.SetDivider(itemDivider);
        model.SetChainAnimation(true);
    });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step3. Set divider strokeWidth less than zero
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.strokeWidth = Dimension(-1);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step4. Set divider strokeWidth Unit as PERCENT
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.strokeWidth = Dimension(STROKE_WIDTH, DimensionUnit::PERCENT);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step5. Not create item
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    Create([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step6. Set divider strokeWidth greater than contentSize(LIST_HEIGHT)
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.strokeWidth = Dimension(LIST_HEIGHT + 1);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step7. Set divider startMargin + endMargin equal to crossSize(LIST_WIDTH)
     * @tc.expected: modifier dividerInfo_ has no value.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.startMargin = Dimension(LIST_WIDTH / 2);
    itemDivider.endMargin = Dimension(LIST_WIDTH / 2);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_TRUE(dividerMap.empty());

    /**
     * @tc.steps: step8. Set divider startMargin + endMargin greater than crossSize(LIST_WIDTH)
     * @tc.expected: modifier dividerInfo_ has value and reset margin to zero.
     */
    itemDivider = ITEM_DIVIDER;
    itemDivider.startMargin = Dimension(LIST_WIDTH / 2);
    itemDivider.endMargin = Dimension(LIST_WIDTH / 2 + 1);
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_FALSE(dividerMap.empty());
    for (auto child : dividerMap) {
        EXPECT_EQ(child.second.offset.GetX(), 0.f);
    }

    /**
     * @tc.steps: step9. Set divider startMargin + endMargin less than crossSize(LIST_WIDTH)
     * @tc.expected: modifier dividerInfo_ has value and margin not change
     */
    itemDivider = ITEM_DIVIDER;
    CreateWithItem([itemDivider](ListModelNG model) { model.SetDivider(itemDivider); });
    UpdateContentModifier();
    dividerList_ = pattern_->listContentModifier_->dividerList_->Get();
    lda = AceType::DynamicCast<ListDividerArithmetic>(dividerList_);
    dividerMap = lda->GetDividerMap();
    EXPECT_FALSE(dividerMap.empty());
    for (auto child : dividerMap) {
        EXPECT_EQ(child.second.offset.GetX(), ITEM_DIVIDER.startMargin.ConvertToPx());
    }
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: Test List paint method about GetForegroundDrawFunction/PaintEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set EdgeEffect::FADE
     */
    CreateWithItem([](ListModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, false); });
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    auto paintWrapper = frameNode_->CreatePaintWrapper();
    Testing::MockCanvas canvas;
    listPaint->GetForegroundDrawFunction(AceType::RawPtr(paintWrapper));
    listPaint->PaintEdgeEffect(AceType::RawPtr(paintWrapper), canvas);
    SUCCEED();
}

/**
 * @tc.name: PaintMethod003
 * @tc.desc: Test List paint method about UpdateOverlayModifier
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set DisplayMode ON
     * @tc.expected: The displayMode is ON, has scrollbar and on the right
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(DisplayMode::ON); });
    RefPtr<ListPaintMethod> paint = UpdateOverlayModifier();
    auto scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    auto scrollBar = paint->scrollBar_.Upgrade();
    ASSERT_NE(scrollBar, nullptr);
    EXPECT_EQ(scrollBar->displayMode_, DisplayMode::ON);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);

    /**
     * @tc.steps: step2. Update axis
     * @tc.expected: The scrollbar and on the bottom
     */
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    FlushLayoutTask(frameNode_);
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::BOTTOM);

    /**
     * @tc.steps: step3. Set DisplayMode::OFF
     * @tc.expected: Has no scrollbar
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(DisplayMode::OFF); });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_EQ(scrollBar, nullptr);

    /**
     * @tc.steps: step4. Set DisplayMode::ON
     * @tc.expected: Has scrollbar and on the right
     */
    CreateWithItem([](ListModelNG model) { model.SetScrollBar(DisplayMode::ON); });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::RIGHT);

    /**
     * @tc.steps: step5. Has no item
     * @tc.expected: UnScrollable, has no scrollbar
     */
    Create([](ListModelNG model) { model.SetScrollBar(DisplayMode::ON); });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_FALSE(scrollBar->NeedPaint());

    /**
     * @tc.steps: step6. Set HORIZONTAL direction
     * @tc.expected: Has scrollbar and on the bottom
     */
    Create([](ListModelNG model) {
        model.SetScrollBar(DisplayMode::ON);
        model.SetListDirection(Axis::HORIZONTAL);
        CreateItem(TOTAL_LINE_NUMBER, Axis::HORIZONTAL);
    });
    paint = UpdateOverlayModifier();
    scrollBarOverlayModifier = paint->scrollBarOverlayModifier_.Upgrade();
    scrollBar = paint->scrollBar_.Upgrade();
    EXPECT_NE(scrollBar, nullptr);
    EXPECT_TRUE(scrollBar->NeedPaint());
    EXPECT_EQ(scrollBarOverlayModifier->positionMode_, PositionMode::BOTTOM);
}

/**
 * @tc.name: PaintMethod004
 * @tc.desc: Test List paint method about PaintDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod004, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).Times(3);
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(6);
    DrawingContext ctx = { canvas, 1, 1 };

    /**
     * @tc.steps: step1. Set divider
     */
    Create([](ListModelNG model) {
        model.SetDivider(ITEM_DIVIDER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
        CreateItem(TOTAL_LINE_NUMBER);
    });
    UpdateContentModifier();
    pattern_->listContentModifier_->onDraw(ctx);

    /**
     * @tc.steps: step2. Set lanes greater than 1
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        model.SetDivider(ITEM_DIVIDER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
        CreateItem(TOTAL_LINE_NUMBER);
    });
    UpdateContentModifier();
    pattern_->listContentModifier_->onDraw(ctx);

    /**
     * @tc.steps: step3. Set lanes greater than 1 and lastIsItemGroup
     */
    Create([](ListModelNG model) {
        model.SetLanes(2);
        model.SetDivider(ITEM_DIVIDER);
        CreateItem(TOTAL_LINE_NUMBER);
        CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE);
    });
    UpdateContentModifier();
    pattern_->listContentModifier_->onDraw(ctx);
}

/**
 * @tc.name: PaintMethod005
 * @tc.desc: Test ListItemGroup paint method about PaintDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, PaintMethod005, TestSize.Level1)
{
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(6);

    Create(
        [](ListModelNG model) { CreateGroupWithSetting(GROUP_NUMBER, Axis::VERTICAL, V2::ListItemGroupStyle::NONE); });
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<NodePaintMethod> paint = groupPattern->CreateNodePaintMethod();
    RefPtr<ListItemGroupPaintMethod> groupPaint = AceType::DynamicCast<ListItemGroupPaintMethod>(paint);
    auto paintWrapper = groupFrameNode->CreatePaintWrapper();
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_.strokeWidth = Dimension(-1);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_.strokeWidth = Dimension(STROKE_WIDTH, DimensionUnit::PERCENT);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_ = ITEM_DIVIDER;
    groupPaint->divider_.startMargin = Dimension(LIST_WIDTH / 2);
    groupPaint->divider_.endMargin = Dimension(LIST_WIDTH / 2);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);

    groupPaint->divider_ = ITEM_DIVIDER;
    groupPaint->divider_.startMargin = Dimension(LIST_WIDTH / 2);
    groupPaint->divider_.endMargin = Dimension(LIST_WIDTH / 2 + 1);
    groupPaint->PaintDivider(AceType::RawPtr(paintWrapper), canvas);
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
    ListModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    model.SetScrollBar(DisplayMode::ON);
    model.SetMultiSelectable(true);
    CreateItem(TOTAL_LINE_NUMBER);
    GetInstance();
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
    CreateWithItem([](ListModelNG model) {});
    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    ScrollDown();
    EXPECT_FALSE(pattern_->OutBoundaryCallback());
    ScrollDown();
    EXPECT_TRUE(pattern_->OutBoundaryCallback());

    CreateWithItem([](ListModelNG model) {
        model.SetChainAnimation(true);
        model.SetChainAnimationOptions({ Dimension(0), Dimension(10), 0, 0, 0, DEFAULT_STIFFNESS, DEFAULT_DAMPING });
    });
    EXPECT_NE(pattern_->springProperty_, nullptr);
    EXPECT_NE(pattern_->chainAnimation_, nullptr);
    pattern_->OutBoundaryCallback();
    EXPECT_TRUE(pattern_->dragFromSpring_);
}

/**
 * @tc.name: Pattern006
 * @tc.desc: Test GetItemIndexByPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern006, TestSize.Level1)
{
    Create([](ListModelNG model) {
        model.SetLanes(2);
        CreateItem(VIEW_LINE_NUMBER);
    });

    /**
     * @tc.steps: step1. When lanes > 1, call GetItemIndexByPosition
     * @tc.expected: Would return correct itemIndex
     */
    const Point point = Point(300.f, 250.f);
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
    Create([](ListModelNG model) { CreateItem(VIEW_LINE_NUMBER); });
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, VIEW_LINE_NUMBER);
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
    Create([](ListModelNG model) {});
    const Point point = Point(0, 1000.f);
    int32_t itemIndex = pattern_->GetItemIndexByPosition(point.GetX(), point.GetY());
    EXPECT_EQ(itemIndex, 0);
}

/**
 * @tc.name: Pattern010
 * @tc.desc: Test layout
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, Pattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. do not set selfIdealSize, 0 listItem
     */
    ListModelNG listModelNG_1;
    listModelNG_1.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), LIST_WIDTH);

    /**
     * @tc.steps: step1. do not set selfIdealSize, TOTAL_LINE_NUMBER listItem
     */
    ListModelNG listModelNG_2;
    listModelNG_2.Create();
    ViewAbstract::SetWidth(CalcLength(LIST_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateItem(TOTAL_LINE_NUMBER);
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), LIST_WIDTH);

    /**
     * @tc.steps: step1. set width Infinity
     */
    ListModelNG listModelNG_3;
    listModelNG_3.Create();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    CreateItem(TOTAL_LINE_NUMBER);
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), Infinity<float>());

    /**
     * @tc.steps: step1. set width Infinity, but no item
     */
    ListModelNG listModelNG_4;
    listModelNG_4.Create();
    ViewAbstract::SetWidth(CalcLength(Infinity<float>()));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize().Width(), 0);
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
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemPattern>();

    /**
     * @tc.steps: step3. call function HandlePressEvent, set TouchType to DOWN and set hover status is true.
     * @tc.expected: step3. the color is different from the initial color when the listItem is pressed with the mouse.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_TRUE(pattern->isPressed_);

    /**
     * @tc.steps: step4. call function HandlePressEvent, set TouchType to DOWN and set hover status is false.
     * @tc.expected: step4. the color is different from the initial color when the listItem is pressed with gesture.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(true, frameNode);
    EXPECT_TRUE(pattern->isPressed_);

    /**
     * @tc.steps: step5. call function HandlePressEvent, set TouchType to UP and set hover status is true.
     * @tc.expected: step5. the color differs from the initial color when mouse hovers over listItem after pressing.
     */
    pattern->isHover_ = true;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_FALSE(pattern->isPressed_);

    /**
     * @tc.steps: step6. call function HandlePressEvent, set TouchType to UP and set hover status is false.
     * @tc.expected: step6. the color returns to its original color after pressing on listItem through gestures.
     */
    pattern->isHover_ = false;
    pattern->HandlePressEvent(false, frameNode);
    EXPECT_FALSE(pattern->isPressed_);
}

/**
 * @tc.name: ListItemDisableEventForCardModeTest001
 * @tc.desc: Test disable event when the enable status of the listItem is false.
 * @tc.type: FUNC
 */
HWTEST_F(ListLayoutTestNg, ListItemDisableEventForCardModeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. create ListItem in card mode.
     * @tc.expected: step2. create a card style ListItem success and set enable status to false.
     */
    ListItemModelNG itemModel;
    itemModel.Create([](int32_t) {}, V2::ListItemStyle::CARD);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<ListItemPattern>();
    auto eventHub = frameNode->GetEventHub<ListItemEventHub>();
    eventHub->SetEnabled(false);
    pattern->selectable_ = true;

    /**
     * @tc.steps: step3. call function InitDisableEvent.
     * @tc.expected: step3. the background color has been updated and selectable has been set to false.
     */
    pattern->InitDisableEvent();
    EXPECT_FALSE(pattern->selectable_);
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
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    pattern_->ScrollBy(ITEM_HEIGHT / 2.0f);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid ListItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(-1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(TOTAL_LINE_NUMBER * 2 - 1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(TOTAL_LINE_NUMBER * 2), Rect()));

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
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(9),
        Rect(0, -ITEM_HEIGHT / 2.0f + ITEM_HEIGHT * 8, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
    /**
     * @tc.steps: step5. Slide List by Scroller.
     */
    pattern_->ScrollToIndex(10);
    FlushLayoutTask(frameNode_);
    /**
     * @tc.steps: step6. Get invalid ListItem Rect.
     * @tc.expected: Return 0 when input invalid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(9), Rect()));

    /**
     * @tc.steps: step7. Get valid ListItem Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(pattern_->GetEndIndex()),
        Rect(0, LIST_HEIGHT - ITEM_HEIGHT, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));
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
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateGroup(TOTAL_LINE_NUMBER, Axis::VERTICAL);
    });
    pattern_->ScrollBy(ITEM_HEIGHT * 2);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Get invalid group item Rect.
     * @tc.expected: Return 0 when input invalid group index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(-1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(2, -1), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(0, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(TOTAL_LINE_NUMBER - 1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, 0), Rect()));
    EXPECT_TRUE(IsEqual(pattern_->GetItemRectInGroup(1, GROUP_LINE_NUMBER), Rect()));

    /**
     * @tc.steps: step3. Get valid group item Rect.
     * @tc.expected: Return actual Rect when input valid group index.
     */
    EXPECT_TRUE(IsEqual(
        pattern_->GetItemRectInGroup(2, 0), Rect(0, ITEM_HEIGHT * 2, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT)));

    /**
     * @tc.steps: step4. Get valid ListItemGroup Rect.
     * @tc.expected: Return actual Rect when input valid index.
     */
    EXPECT_TRUE(IsEqual(pattern_->GetItemRect(2),
        Rect(0, ITEM_HEIGHT * 2, FILL_LENGTH.Value() * LIST_WIDTH, ITEM_HEIGHT * GROUP_LINE_NUMBER)));
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
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

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
    Create([](ListModelNG model) {
        model.SetInitialIndex(1);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });

    EXPECT_CALL(*MockPipelineContext::pipeline_, GetSafeArea).Times(0);
    layoutProperty_->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP });
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->contentEndOffset_, 0);
    EXPECT_TRUE(IsEqual(frameNode_->geometryNode_->GetFrameSize(), SizeF(LIST_WIDTH, LIST_HEIGHT)));
}
} // namespace OHOS::Ace::NG
