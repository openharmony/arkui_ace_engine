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

#include "arc_list_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
struct SwipeActionItem {
    std::function<void()> builderAction;
    Dimension actionAreaDistance;
    OnDeleteEvent onDelete;
    OnEnterDeleteAreaEvent onEnterDeleteArea;
    OnExitDeleteAreaEvent onExitDeleteArea;
    OnStateChangedEvent onStateChange;
};
} // namespace

class ArcListSwipeTestNg : public ArcListTestNg {
public:
    void CreateWithSwipe(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber = TOTAL_ITEM_NUMBER);
    void CreateWithSwipeAction(
        SwipeActionItem& item, bool isStartArea, OnOffsetChangeFunc onOffsetChange, V2::SwipeEdgeEffect effect);
};

void ArcListSwipeTestNg::CreateWithSwipe(bool isStartNode, V2::SwipeEdgeEffect swipeEdgeEffect, int32_t itemNumber)
{
    CreateList();
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    for (int32_t index = 0; index < itemNumber; index++) {
        if (isStartNode) {
            CreateItemWithSwipe(startFunc, nullptr, swipeEdgeEffect);
        } else {
            CreateItemWithSwipe(nullptr, endFunc, swipeEdgeEffect);
        }
    }
    CreateDone();
}

void ArcListSwipeTestNg::CreateWithSwipeAction(
    SwipeActionItem& item, bool isStartArea, OnOffsetChangeFunc onOffsetChange, V2::SwipeEdgeEffect effect)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), effect);
    itemModel.SetDeleteArea(std::move(item.builderAction), std::move(item.onDelete), std::move(item.onEnterDeleteArea),
        std::move(item.onExitDeleteArea), std::move(item.onStateChange), item.actionAreaDistance, isStartArea);
    {
        RowModelNG rowModel;
        rowModel.Create(std::nullopt, nullptr, "");
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(ITEM_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateDone();
}

/**
 * @tc.name: SwiperItem001
 * @tc.desc: Set startNode, Arc_list can swipe start but cannot swipe end.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem001, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, LIST_WIDTH * ARC_LIST_ITER_SCALE, ITEM_HEIGHT);
    const RectF itemNodeSwipeStartRect = RectF(START_NODE_LEN, 0, LIST_WIDTH * ARC_LIST_ITER_SCALE, ITEM_HEIGHT);
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
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can not move, StartNode not layout
     */
    DragSwiperItem(listItemIndex, -START_NODE_LEN);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe start slightly
     * @tc.expected: Can move, StartNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, startNode will not layout
    expectStartNodeRect = RectF(slightSwipeDelta - START_NODE_LEN, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe start obviously
     * @tc.expected: swiperIndex_ change to SWIPER_START
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step5. Swipe item slightly
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(-obviousSwipeDelta, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe item exceed
     * @tc.expected: swiperIndex_ change to SWIPER_START, curOffset_ would be START_NODE_LEN
     */
    DragSwiperItem(listItemIndex, exceedSwipeDelta);
    startNodeRect = GetChildRect(listItem, startNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: SwiperItem002
 * @tc.desc: Set endNode, Arc_list can swipe end but cannot swipe start.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem002, TestSize.Level1)
{
    CreateWithSwipe(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    const RectF itemNodeInitialRect = RectF(0, 0, LIST_WIDTH * ARC_LIST_ITER_SCALE, ITEM_HEIGHT);
    const RectF itemNodeSwipeEndRect = RectF(-END_NODE_LEN, 0, LIST_WIDTH * ARC_LIST_ITER_SCALE, ITEM_HEIGHT);
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
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start
     * @tc.expected: Can not move, EndNode not layout
     */
    DragSwiperItem(listItemIndex, END_NODE_LEN);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF();
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step3. Swipe end slightSwipeDelta
     * @tc.expected: Can move, EndNode layout, curOffset_ will reset to Zero
     */
    DragSwiperItem(listItemIndex, -slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    // Because when curOffset_ is equal to zero, endNode will not layout
    expectEndNodeRect = RectF(LIST_WIDTH * ARC_LIST_ITER_SCALE - slightSwipeDelta, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_FALSE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end obviously
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    DragSwiperItem(listItemIndex, -obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH * ARC_LIST_ITER_SCALE - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_FALSE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item slightSwipeDelta
     * @tc.expected: swiperIndex_ unchanged
     */
    DragSwiperItem(listItemIndex, slightSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH * ARC_LIST_ITER_SCALE - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_FALSE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step6. Swipe item obviously
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, obviousSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect =
        RectF(LIST_WIDTH * ARC_LIST_ITER_SCALE - END_NODE_LEN + obviousSwipeDelta, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_FALSE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step7. Swipe end exceed
     * @tc.expected: swiperIndex_ change to SWIPER_END, curOffset_ would be -END_NODE_LEN
     */
    DragSwiperItem(listItemIndex, -exceedSwipeDelta);
    endNodeRect = GetChildRect(listItem, endNodeIndex);
    itemNodeRect = GetChildRect(listItem, itemNodeIndex);
    expectEndNodeRect = RectF(LIST_WIDTH * ARC_LIST_ITER_SCALE - END_NODE_LEN, 0, END_NODE_LEN, ITEM_HEIGHT);
    expectItemNodeRect = itemNodeSwipeEndRect;
    EXPECT_FALSE(IsEqual(endNodeRect, expectEndNodeRect));
    EXPECT_FALSE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);
}

/**
 * @tc.name: SwiperItem003
 * @tc.desc: Set startNode and endNode. Drag to left or right with speed.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem003, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    int32_t listItemIndex = 0;
    auto listItem = GetChildFrameNode(frameNode_, listItemIndex);
    auto listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
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
    DragSwiperItem(listItemIndex, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step4. Swipe end fast
     * @tc.expected: swiperIndex_ change to SWIPER_END
     */
    ClearOldNodes();
    CreateWithSwipe(false, V2::SwipeEdgeEffect::None);
    listItem = GetChildFrameNode(frameNode_, listItemIndex);
    listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    DragSwiperItem(listItemIndex, -swipeDelta, -fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step5. Swipe item fast
     * @tc.expected: swiperIndex_ change to ITEM_CHILD
     */
    DragSwiperItem(listItemIndex, swipeDelta, fastSpeed);
    swiperIndex = listItemPattern->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem004
 * @tc.desc: Set startNode and endNode. if drag different ListItem, the previous item would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem004, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
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
     * @tc.expected: The first and second item reseted.
     */
    DragSwiperItem(secondItemIndex, swipeDelta, fastSpeed);
    firstSwiperIndex = firstItemPattern->GetSwiperIndex();
    secondSwiperIndex = secondItemPattern->GetSwiperIndex();
    EXPECT_EQ(firstSwiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwiperItem005
 * @tc.desc: Set startNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem005, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, START_NODE_LEN + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN);
}

/**
 * @tc.name: SwiperItem006
 * @tc.desc: Set endNode and SwipeEdgeEffect::Spring, can continue to move when swipe exceed listItem size
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem006, TestSize.Level1)
{
    CreateWithSwipe(false, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. swipe start exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);

    /**
     * @tc.steps: step2. swipe end exceed listItem size
     * @tc.expected: Can continue to move, and because of GetFriction(), less than move distance
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN + moveDelta);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, -END_NODE_LEN + moveDelta * 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);
}

/**
 * @tc.name: SwiperItem007
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * Arc_list can swiper right great than START_NODE_LEN
 * if great than START_NODE_LEN + deleteAreaDistance,
 * it will adjust to START_NODE_LEN + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem007, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(startFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = nullptr

    };
    CreateWithSwipeAction(item, true, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    EXPECT_NE(listItemPattern, nullptr);
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: cannot exceed maxDistance
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: cannot move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_FLOAT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem008
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, Arc_list can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 *
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem008, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(endFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = nullptr

    };
    CreateWithSwipeAction(item, false, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: can exceed maxDistance
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: cannot move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
}

/**
 * @tc.name: SwiperItem009
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem009, TestSize.Level1)
{
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = std::move(startFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = std::move(onStateChangeFunc) };
    CreateWithSwipeAction(item, true, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, maxDistance);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, START_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can continue to move
     */
    moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), listItemPattern->curOffset_);
    HandleDragEnd(listItemIndex);
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
HWTEST_F(ArcListSwipeTestNg, SwiperItem010, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = std::move(endFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = std::move(onStateChangeFunc) };
    CreateWithSwipeAction(item, false, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;
    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    EXPECT_EQ(listItemPattern->curOffset_, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_LT(listItemPattern->curOffset_, -maxDistance);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, -END_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), -END_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can continue to move
     */
    moveDelta = 1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, END_NODE_LEN);
    HandleDragUpdate(listItemIndex, moveDelta);
    EXPECT_GT(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), listItemPattern->curOffset_);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(listItemPattern->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: SwiperItem011
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and exitStartDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem011, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    auto builder = GetDefaultSwiperBuilder(START_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(builder),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, true, nullptr, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_LEN);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem012
 * @tc.desc: Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and exitEndDeleteArea
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem012, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    auto builder = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionItem item = { .builderAction = std::move(builder),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, false, nullptr, V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -END_NODE_LEN);
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem013
 * @tc.desc: Test callback with no start node
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem013, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    SwipeActionItem item = { .builderAction = nullptr,
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, true, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, 1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed DELETE_AREA_DISTANCE and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, 1.f);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem014
 * @tc.desc: Test callback with no end node
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem014, TestSize.Level1)
{
    bool isDelete = false;
    bool isEntry = false;
    bool isExit = false;
    auto deleteEvent = [&isDelete]() { isDelete = true; };
    auto enterEvent = [&isEntry]() { isEntry = true; };
    auto exitEvent = [&isExit]() { isExit = true; };
    SwipeActionItem item = { .builderAction = nullptr,
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = std::move(deleteEvent),
        .onEnterDeleteArea = std::move(enterEvent),
        .onExitDeleteArea = std::move(exitEvent),
        .onStateChange = nullptr };
    CreateWithSwipeAction(item, false, nullptr, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragUpdate(listItemIndex, -1.f);
    EXPECT_TRUE(isEntry);
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    isEntry = false;
    HandleDragUpdate(listItemIndex, -exceedArea);
    EXPECT_TRUE(isEntry);
    isExit = false;
    HandleDragUpdate(listItemIndex, exceedArea);
    EXPECT_TRUE(isExit);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move exceed exceedArea and release
     */
    isDelete = false;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -exceedArea);
    HandleDragUpdate(listItemIndex, -1.f);
    HandleDragEnd(listItemIndex);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: SwiperItem015
 * @tc.desc: Test SetStartNode
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem015, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t startNodeIndex = 0;
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    RefPtr<NG::UINode> startNode;
    startFunc();
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
HWTEST_F(ArcListSwipeTestNg, SwiperItem016, TestSize.Level1)
{
    CreateWithSwipe(false, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const int32_t endNodeIndex = 0;
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    RefPtr<NG::UINode> endNode;
    endFunc();
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
HWTEST_F(ArcListSwipeTestNg, SwiperItem017, TestSize.Level1)
{
    CreateWithSwipe(true, V2::SwipeEdgeEffect::None);
    const int32_t listItemIndex = 0;
    const RefPtr<FrameNode> listItem = GetChildFrameNode(frameNode_, listItemIndex);
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

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
HWTEST_F(ArcListSwipeTestNg, SwiperItem018, TestSize.Level1)
{
    bool isDelete = false;
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = GetDefaultSwiperBuilder(START_NODE_LEN),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = [&isDelete]() { isDelete = true; },
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = [&curState](SwipeActionState state) { curState = state; } };
    CreateWithSwipeAction(item, true, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, START_NODE_LEN);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);
}

/**
 * @tc.name: SwiperItem019
 * @tc.desc: Test swiperAction Attribute for ListItem, set onOffsetChangeCallback & onStateChangeCallback
 * callback
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem019, TestSize.Level1)
{
    bool isDelete = false;
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = GetDefaultSwiperBuilder(START_NODE_LEN),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = [&isDelete]() { isDelete = true; },
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = [&curState](SwipeActionState state) { curState = state; } };
    CreateWithSwipeAction(item, false, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);

    /**
     * @tc.steps: step1. Repeat entry and exit
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -START_NODE_LEN);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(listItemPattern->curOffset_));
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    HandleDragUpdate(listItemIndex, DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE / 2);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);
    EXPECT_EQ(offset.ConvertToPx(), -START_NODE_LEN);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     */
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -DELETE_AREA_DISTANCE);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::ACTIONING);
}

/**
 * @tc.name: SwiperItem020
 * @tc.desc: Test closeAllSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem020, TestSize.Level1)
{
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    SwipeActionItem item = { .builderAction = std::move(endFunc),
        .actionAreaDistance = Dimension(DELETE_AREA_DISTANCE),
        .onDelete = nullptr,
        .onEnterDeleteArea = nullptr,
        .onExitDeleteArea = nullptr,
        .onStateChange = std::move(onStateChangeFunc) };
    CreateWithSwipeAction(item, false, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    const int32_t listItemIndex = 0;
    const RefPtr<ListItemPattern> listItemPattern = GetChildPattern<ListItemPattern>(frameNode_, listItemIndex);
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;
    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(listItemIndex);
    HandleDragUpdate(listItemIndex, -maxDistance);
    HandleDragUpdate(listItemIndex, moveDelta);
    HandleDragEnd(listItemIndex);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);
    OnFinishFunc onFinishCallBack;
    listItemPattern->CloseSwipeAction(std::move(onFinishCallBack));
    EXPECT_EQ(curState, SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwiperItem021
 * @tc.desc: Test swipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ArcListSwipeTestNg, SwiperItem021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List
     */
    auto startFunc = GetDefaultSwiperBuilder(START_NODE_LEN);
    auto endFunc = GetDefaultSwiperBuilder(END_NODE_LEN);
    ListModelNG model = CreateList();
    CreateItemWithSwipe(startFunc, endFunc, V2::SwipeEdgeEffect::None);
    CreateDone();
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
} // namespace OHOS::Ace::NG
