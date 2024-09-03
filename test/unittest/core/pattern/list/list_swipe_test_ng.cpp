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

namespace {
constexpr int32_t FIRSTITEM_INDEX = 0;
} // namespace

class ListSwipeTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: SwiperItem001
 * @tc.desc: Set startNode, List can swipe start but cannot swipe end.
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const int32_t startNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, LIST_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeStartRect = RectF(START_NODE_LEN, 0, LIST_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = START_NODE_LEN * SWIPER_TH;
    const float obviousSwipeDelta = START_NODE_LEN * SWIPER_TH + 1;
    const float exceedSwipeDelta = START_NODE_LEN + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: StartNode not layout
     */
    RectF startNodeRect = GetChildRect(listItem, startNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectStartNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can not move, StartNode not layout
     */
    DragSwiperItem(FIRSTITEM_INDEX, -START_NODE_LEN);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe start slightly
     * @tc.expected: Can move, StartNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(FIRSTITEM_INDEX, slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, startNode will not layout
    expectStartNodeRect = RectF(slightSwipeDelta - START_NODE_LEN, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe start obviously
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(FIRSTITEM_INDEX, obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step5. Swipe item slightly
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(FIRSTITEM_INDEX, -slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(FIRSTITEM_INDEX, -obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(-obviousSwipeDelta, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe item exceed
     * @tc.expected: swiperIndex_ change to SWIPER_START, curOffset_ would be START_NODE_LEN
     */
    DragSwiperItem(FIRSTITEM_INDEX, exceedSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem002
 * @tc.desc: Set endNode, List can swipe end but cannot swipe start.
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem002, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const int32_t endNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, LIST_WIDTH, ITEM_HEIGHT);
    const RectF itemNodeSwipeEndRect = RectF(-END_NODE_LEN, 0, LIST_WIDTH, ITEM_HEIGHT);
    const float slightSwipeDelta = END_NODE_LEN * SWIPER_TH;
    const float obviousSwipeDelta = END_NODE_LEN * SWIPER_TH + 1;
    const float exceedSwipeDelta = END_NODE_LEN + 1;

    /**
     * @tc.steps: step1. do nothing, verify initial rect.
     * @tc.expected: EndNode not layout
     */
    RectF endNodeRect = GetChildRect(listItem, endNodeIndex);
    RectF itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    RectF expectEndNodeRect = RectF();
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start
     * @tc.expected: Can not move, EndNode not layout
     */
    DragSwiperItem(FIRSTITEM_INDEX, END_NODE_LEN);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe end slightSwipeDelta
     * @tc.expected: Can move, EndNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(FIRSTITEM_INDEX, -slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, endNode will not layout
    expectEndNodeRect = RectF(LIST_WIDTH - slightSwipeDelta, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end obviously
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    DragSwiperItem(FIRSTITEM_INDEX, -obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item slightSwipeDelta
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(FIRSTITEM_INDEX, slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(FIRSTITEM_INDEX, obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN + obviousSwipeDelta, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe end exceed
     * @tc.expected: swiperIndex_ change to SWIPER_END, curOffset_ would be -END_NODE_LEN
     */
    DragSwiperItem(FIRSTITEM_INDEX, -exceedSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);
}

/**
 * @tc.name: SwiperItem003
 * @tc.desc: Set startNode and endNode. Drag to left or right with speed.
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem003, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    auto listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const float fastSpeed = SWIPER_SPEED_TH + 1;
    const float swipeDelta = 1;

    /**
     * @tc.steps: step1. swiperIndex_ Default is ITEM_CHILD
     */
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start fast
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(FIRSTITEM_INDEX, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(FIRSTITEM_INDEX, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end fast
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    ClearOldNodes();
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    DragSwiperItem(FIRSTITEM_INDEX, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(FIRSTITEM_INDEX, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem004
 * @tc.desc: Set startNode and endNode. if drag different ListItem, the previous item would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem004, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const float fastSpeed = SWIPER_SPEED_TH + 1;
    const float swipeDelta = 1;
    const int32_t firstItemIndex = 0;
    const int32_t secondItemIndex = 1;
    const RefPtr<ListItemPattern> firstItemPattern = GetChildPattern<ListItemPattern>(frameNode_, firstItemIndex);
    const RefPtr<ListItemPattern> secondItemPattern = GetChildPattern<ListItemPattern>(frameNode_, secondItemIndex);

    /**
     * @tc.steps: step1. Swipe first item fast
     * @tc.expected: The first item swiperIndex_ changed.
     */
    DragSwiperItem(firstItemIndex, swipeDelta, fastSpeed);
    ListItemSwipeIndex firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    ListItemSwipeIndex secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::SWIPER_START);
    EXPECT_EQ(secondSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe second item fast
     * @tc.expected: The second item swiperIndex_ changed, and first item reseted.
     */
    DragSwiperItem(secondItemIndex, swipeDelta, fastSpeed);
    firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_EQ(secondSwiperIndex, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem005
 * @tc.desc: Set startNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem005, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = -1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = 1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, START_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN + moveDelta);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, START_NODE_LEN + moveDelta * 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN);
}

/**
 * @tc.name: SwiperItem006
 * @tc.desc: Set endNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem006, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = 1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = -1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -END_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN + moveDelta);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, -END_NODE_LEN + moveDelta * 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);
}

/**
 * @tc.name: SwiperItem007
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * List can swiper right great than START_NODE_LEN
 * if great than START_NODE_LEN + deleteAreaDistance,
 * it will adjust to START_NODE_LEN + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem007, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(startFunc), nullptr, nullptr, nullptr, nullptr,
        Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    ASSERT_NE(listItemPattern, nullptr);
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: cannot exceed maxDistance
     */
    float moveDelta = 1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, maxDistance);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: cannot move
     */
    moveDelta = -1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -START_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem008
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem008, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(endFunc), nullptr, nullptr, nullptr, nullptr,
        Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: can exceed maxDistance
     */
    float moveDelta = -1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: cannot move
     */
    moveDelta = 1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, END_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem009
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem009, TestSize.Level1)
{
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(startFunc), nullptr, nullptr, nullptr, onStateChangeFunc,
        Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = 1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can continue to move
     */
    moveDelta = -1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -START_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), listItemPattern->curOffset_);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: SwiperItem010
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the left distance great than endNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem010, TestSize.Level1)
{
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(endFunc), nullptr, nullptr, nullptr, onStateChangeFunc,
        Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;
    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, -maxDistance);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), -END_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can continue to move
     */
    moveDelta = 1;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, END_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), listItemPattern->curOffset_);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: SwiperItem011
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and exitStartDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem011, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(startFunc), std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent),
        nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, START_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_TRUE(isDelete);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    itemPattern->ResetSwipeStatus();
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE + 1);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem012
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and exitEndDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem012, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(endFunc), std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent),
        nullptr, Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -END_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(FIRSTITEM_INDEX, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(FIRSTITEM_INDEX, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceedArea and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_TRUE(isDelete);

    /**
     * @tc.steps: step4. move exceed exceedArea and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    itemPattern->ResetSwipeStatus();
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -(exceedArea + 1));
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem013
 * @tc.desc: Test callback with no start node
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem013, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    itemModel.SetDeleteArea(nullptr, std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent),
        nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    HandleDragUpdate(FIRSTITEM_INDEX, 1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    HandleDragUpdate(FIRSTITEM_INDEX, 1.f);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem014
 * @tc.desc: Test callback with no end node
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem014, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    itemModel.SetDeleteArea(nullptr, std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent),
        nullptr, Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea);
    HandleDragUpdate(FIRSTITEM_INDEX, -1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(FIRSTITEM_INDEX, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(FIRSTITEM_INDEX, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed exceedArea and release
     */
    isDelete = false;
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -exceedArea);
    HandleDragUpdate(FIRSTITEM_INDEX, -1.f);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem015
 * @tc.desc: Test SetStartNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem015, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const int32_t startNodeIndex = 0;
    RefPtr<NG::UINode> startNode;
    GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT)();
    startNode = NG::ViewStackProcessor::GetInstance()->Finish();
    listItemPattern->SetStartNode(startNode);
    EXPECT_EQ(GetChildFrameNode(listItem, startNodeIndex), startNode);
    listItemPattern->SetStartNode(nullptr);
    EXPECT_EQ(listItemPattern->startNodeIndex_, -1);
}

/**
 * @tc.name: SwiperItem016
 * @tc.desc: Test SetEndNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem016, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const int32_t endNodeIndex = 0;
    RefPtr<NG::UINode> endNode;
    GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT)();
    endNode = NG::ViewStackProcessor::GetInstance()->Finish();
    listItemPattern->SetEndNode(endNode);
    EXPECT_EQ(GetChildFrameNode(listItem, endNodeIndex), endNode);
    listItemPattern->SetEndNode(nullptr);
    EXPECT_EQ(listItemPattern->endNodeIndex_, -1);
}

/**
 * @tc.name: SwiperItem017
 * @tc.desc: Test InitSwiperAction
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem017, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    listItemPattern->curOffset_ = 10.f;
    listItemPattern->OnModifyDone();
    EXPECT_EQ(listItemPattern->curOffset_, 10.f);
    layoutProperty_->UpdateListDirection(Axis::HORIZONTAL);
    listItemPattern->OnModifyDone();
    EXPECT_EQ(listItemPattern->curOffset_, 0.f);
}

/**
 * @tc.name: SwiperItem018
 * @tc.desc: Test swiperAction Attribute for ListItem, set onOffsetChangeCallback & onStateChangeCallback
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem018, TestSize.Level1)
{
    bool isDelete = false;
    Dimension offset;
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(startFunc), std::move(deleteEvent), nullptr, nullptr,
        std::move(onStateChangeFunc), Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, START_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    itemPattern->ResetSwipeStatus();
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE + 1);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);
}

/**
 * @tc.name: SwiperItem019
 * @tc.desc: Test swiperAction Attribute for ListItem, set onOffsetChangeCallback & onStateChangeCallback
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem019, TestSize.Level1)
{
    bool isDelete = false;
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(startFunc), std::move(deleteEvent), nullptr, nullptr,
        std::move(onStateChangeFunc), Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -START_NODE_LEN);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    HandleDragUpdate(FIRSTITEM_INDEX, DELETE_AREA_DISTANCE);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);
    EXPECT_EQ(offset.ConvertToPx(), -START_NODE_LEN);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);

    /**
     * @tc.steps: step4. move exceed DELETE_AREA_DISTANCE and release
     */
    auto itemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    itemPattern->ResetSwipeStatus();
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);
    EXPECT_EQ(offset.ConvertToPx(), -START_NODE_LEN);

    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -DELETE_AREA_DISTANCE - 1);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);
}

/**
 * @tc.name: SwiperItem020
 * @tc.desc: Test closeAllSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem020, TestSize.Level1)
{
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(endFunc), nullptr, nullptr, nullptr,
        std::move(onStateChangeFunc), Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    HandleDragStart(FIRSTITEM_INDEX);
    HandleDragUpdate(FIRSTITEM_INDEX, -maxDistance);
    HandleDragEnd(FIRSTITEM_INDEX);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    OnFinishFunc onFinishCallBack;
    pattern_->positionController_->CloseAllSwipeActions(std::move(onFinishCallBack));
    EXPECT_EQ(curState, SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwiperItem021
 * @tc.desc: Test swipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    auto childNode = GetChildFrameNode(frameNode_, 0);
    auto childPattern = childNode->GetPattern<ListItemPattern>();
    auto childLayoutProperty = childNode->GetLayoutProperty<ListItemLayoutProperty>();
    int32_t childrenSize = childNode->GetChildren().size();
    EXPECT_EQ(childLayoutProperty->GetEdgeEffectValue(), V2::SwipeEdgeEffect::None);

    /**
     * @tc.steps: step2. swipeAction set null.
     * @tc.expected: check whether the properties is correct.
     */
    childLayoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::Spring);
    childPattern->SetStartNode(nullptr);
    childPattern->SetEndNode(nullptr);
    EXPECT_EQ(childNode->GetChildren().size(), childrenSize - 2);
    EXPECT_EQ(childLayoutProperty->GetEdgeEffectValue(), V2::SwipeEdgeEffect::Spring);

    /**
     * @tc.steps: step3. set swipeAction.
     * @tc.expected: check whether the properties is correct.
     */
    childLayoutProperty->UpdateEdgeEffect(V2::SwipeEdgeEffect::None);
    startFunc();
    childPattern->SetStartNode(ViewStackProcessor::GetInstance()->Finish());
    endFunc();
    childPattern->SetEndNode(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(childNode->GetChildren().size(), childrenSize);
    EXPECT_EQ(childLayoutProperty->GetEdgeEffectValue(), V2::SwipeEdgeEffect::None);
}

/**
 * @tc.name: SwiperItem022
 * @tc.desc: Test Drag with startNode in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem022, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_WIDTH);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Drag up and down
     * @tc.expected: Could swipe start but could not swipe end
     */
    DragSwiperItem(FIRSTITEM_INDEX, -START_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    DragSwiperItem(FIRSTITEM_INDEX, START_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem023
 * @tc.desc: Test Drag with endNode in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem023, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_WIDTH);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Drag down and up
     * @tc.expected: Could swipe end but could not swipe start
     */
    DragSwiperItem(FIRSTITEM_INDEX, END_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    DragSwiperItem(FIRSTITEM_INDEX, -END_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
}

/**
 * @tc.name: SwiperItem024
 * @tc.desc: Test SetDeleteArea after create list done
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwiperItem024, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    itemModel.SetDeleteArea(std::move(startFunc), nullptr, nullptr, nullptr, nullptr,
        Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_HEIGHT))();
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);
    ASSERT_NE(listItemPattern, nullptr);

    /**
     * @tc.steps: step1. Set start node
     * @tc.expected: Start node changed
     */
    startFunc();
    auto startElement = ViewStackProcessor::GetInstance()->Finish();
    auto startNode = AceType::DynamicCast<FrameNode>(startElement);
    const float startDeleteDistance = DELETE_AREA_DISTANCE - 1.f;
    itemModel.SetDeleteArea(AceType::RawPtr(listItem), AceType::RawPtr(startNode), nullptr, nullptr, nullptr, nullptr,
        Dimension(startDeleteDistance), true);
    FlushLayoutTask(frameNode_);
    auto itemLayoutProperty = listItemPattern->GetLayoutProperty<ListItemLayoutProperty>();
    EXPECT_EQ(itemLayoutProperty->GetStartDeleteAreaDistance(), Dimension(startDeleteDistance));
    const int32_t startNodeIndex = 0;
    EXPECT_EQ(GetChildFrameNode(listItem, startNodeIndex), startNode);

    /**
     * @tc.steps: step2. Set end node
     * @tc.expected: End node was be setted
     */
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    endFunc();
    auto endElement = ViewStackProcessor::GetInstance()->Finish();
    auto endNode = AceType::DynamicCast<FrameNode>(endElement);
    const float endDeleteDistance = END_NODE_LEN - 1.f;
    itemModel.SetDeleteArea(AceType::RawPtr(listItem), AceType::RawPtr(endNode), nullptr, nullptr, nullptr, nullptr,
        Dimension(endDeleteDistance), false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(itemLayoutProperty->GetEndDeleteAreaDistance(), Dimension(endDeleteDistance));
    const int32_t endNodeIndex = 2;
    EXPECT_EQ(GetChildFrameNode(listItem, endNodeIndex), endNode);
}

/**
 * @tc.name: ClickJudge001
 * @tc.desc: Test ClickJudge with startNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Not expand startNode
     * @tc.expected: return true
     */
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, -10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, ITEM_HEIGHT + 10.f)));

    /**
     * @tc.steps: step2. Expand startNode
     * @tc.expected: Click not at startNode would return true
     */
    DragSwiperItem(FIRSTITEM_INDEX, START_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(-10.f, 10.f)));
    EXPECT_FALSE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(START_NODE_LEN + 1.f, 10.f)));
}

/**
 * @tc.name: ClickJudge002
 * @tc.desc: Test ClickJudge with endNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge002, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Expand endNode
     * @tc.expected: Click not at endNode would return true
     */
    DragSwiperItem(FIRSTITEM_INDEX, -END_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_FALSE(listItemPattern->ClickJudge(PointF(LIST_WIDTH - 10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(LIST_WIDTH + 10.f, 10.f)));
}

/**
 * @tc.name: ClickJudge003
 * @tc.desc: Test ClickJudge with startNode in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge003, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Not expand startNode
     * @tc.expected: return true
     */
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, -10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, ITEM_HEIGHT + 10.f)));

    /**
     * @tc.steps: step2. Expand startNode
     * @tc.expected: Click not at startNode would return true
     */
    DragSwiperItem(FIRSTITEM_INDEX, -START_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_FALSE(listItemPattern->ClickJudge(PointF(LIST_WIDTH - 10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(LIST_WIDTH + 10.f, 10.f)));
}

/**
 * @tc.name: ClickJudge004
 * @tc.desc: Test ClickJudge in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge004, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_HEIGHT);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Expand endNode
     * @tc.expected: Click not at endNode would return true
     */
    DragSwiperItem(FIRSTITEM_INDEX, END_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(-10.f, 10.f)));
    EXPECT_FALSE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(END_NODE_LEN + 1.f, 10.f)));
}

/**
 * @tc.name: ClickJudge005
 * @tc.desc: Test ClickJudge with startNode in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_WIDTH);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Not expand startNode
     * @tc.expected: return true
     */
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(-10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(ITEM_WIDTH + 10.f, 10.f)));

    /**
     * @tc.steps: step2. Expand startNode
     * @tc.expected: Click not at startNode would return true
     */
    DragSwiperItem(FIRSTITEM_INDEX, START_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, -10.f)));
    EXPECT_FALSE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, START_NODE_LEN + 1.f)));
}

/**
 * @tc.name: ClickJudge006
 * @tc.desc: Test ClickJudge with endNode in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge006, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_WIDTH);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone(frameNode_);
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, FIRSTITEM_INDEX);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, FIRSTITEM_INDEX);

    /**
     * @tc.steps: step1. Expand endNode
     * @tc.expected: Click not at endNode would return true
     */
    DragSwiperItem(FIRSTITEM_INDEX, -END_NODE_LEN);
    EXPECT_EQ(listItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_FALSE(listItemPattern->ClickJudge(PointF(10.f, LIST_HEIGHT - 10.f)));
    EXPECT_TRUE(listItemPattern->ClickJudge(PointF(10.f, LIST_HEIGHT + 10.f)));
}
} // namespace OHOS::Ace::NG
