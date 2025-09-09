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
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float START_NODE_LEN = 80.0f;
constexpr float END_NODE_LEN = 100.0f;
constexpr float SWIPER_TH = 0.25f;
constexpr float START_NODE_TH = START_NODE_LEN * SWIPER_TH;
constexpr float END_NODE_TH = END_NODE_LEN * SWIPER_TH;
constexpr float DELETE_AREA_DISTANCE = 50.0f;
constexpr float SWIPER_SPEED_TH = 1500.0f;
} // namespace

class ListSwipeTestNg : public ListTestNg {
public:
    ListItemModelNG CreateSwipeItem(
        std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect);
    void CreateSwipeItems(std::function<void()> startAction, std::function<void()> endAction,
        V2::SwipeEdgeEffect effect, int32_t itemNumber = TOTAL_ITEM_NUMBER);
    void CreateSwipeItemsWithComponentContent(const RefPtr<NG::UINode>& startBuilderNode,
        const RefPtr<NG::UINode>& endBuilderNode, V2::SwipeEdgeEffect effect, int32_t itemNumber = TOTAL_ITEM_NUMBER);
    void CreateSwipeDone();
    AssertionResult DragSwiperItem(const RefPtr<FrameNode>& frameNode, float dragDelta, float velocityDelta,
        ListItemSwipeIndex listItemSwipeIndex = ListItemSwipeIndex::ITEM_CHILD);
    void HandleDragStart(const RefPtr<FrameNode>& frameNode);
    void HandleDragUpdate(float dragDelta);
    void HandleDragEnd(float velocityDelta);

    RefPtr<FrameNode> item_;
    RefPtr<ListItemPattern> itemPattern_;

    RefPtr<FrameNode> dragItem_;
};

ListItemModelNG ListSwipeTestNg::CreateSwipeItem(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect)
{
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, effect);
    if (startAction) {
        itemModel.SetDeleteArea(std::move(startAction), nullptr, nullptr, nullptr, nullptr, Dimension(0), true);
    }
    if (endAction) {
        itemModel.SetDeleteArea(std::move(endAction), nullptr, nullptr, nullptr, nullptr, Dimension(0), false);
    }
    {
        GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
        ViewStackProcessor::GetInstance()->Pop();
    }
    return itemModel;
}

void ListSwipeTestNg::CreateSwipeItems(
    std::function<void()> startAction, std::function<void()> endAction, V2::SwipeEdgeEffect effect, int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG itemModel = CreateSwipeItem(startAction, endAction, effect);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListSwipeTestNg::CreateSwipeItemsWithComponentContent(const RefPtr<NG::UINode>& startBuilderNode,
    const RefPtr<NG::UINode>& endBuilderNode, V2::SwipeEdgeEffect effect, int32_t itemNumber)
{
    for (int32_t index = 0; index < itemNumber; index++) {
        ListItemModelNG itemModel = CreateListItem();
        itemModel.SetSwiperAction(nullptr, nullptr, nullptr, effect);
        if (startBuilderNode) {
            itemModel.SetDeleteAreaWithFrameNode(
                startBuilderNode, nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true);
        }
        if (endBuilderNode) {
            itemModel.SetDeleteAreaWithFrameNode(
                endBuilderNode, nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false);
        }
        {
            GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
}

void ListSwipeTestNg::CreateSwipeDone()
{
    CreateDone();
    item_ = GetChildFrameNode(frameNode_, 0);
    itemPattern_ = GetChildPattern<ListItemPattern>(frameNode_, 0);
}

AssertionResult ListSwipeTestNg::DragSwiperItem(
    const RefPtr<FrameNode>& frameNode, float dragDelta, float velocityDelta, ListItemSwipeIndex listItemSwipeIndex)
{
    HandleDragStart(frameNode);
    HandleDragUpdate(dragDelta);
    HandleDragEnd(velocityDelta);
    auto itemPattern = frameNode->GetPattern<ListItemPattern>();
    if (itemPattern->GetSwiperIndex() == listItemSwipeIndex) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "Actual: " << static_cast<int32_t>(itemPattern->GetSwiperIndex())
                              << " Expected: " << static_cast<int32_t>(listItemSwipeIndex);
}

void ListSwipeTestNg::HandleDragStart(const RefPtr<FrameNode>& frameNode)
{
    dragItem_ = frameNode;
    auto itemPattern = frameNode->GetPattern<ListItemPattern>();
    GestureEvent info;
    auto handleDragStart = itemPattern->panEvent_->GetActionStartEventFunc();
    handleDragStart(info);
}

void ListSwipeTestNg::HandleDragUpdate(float dragDelta)
{
    auto itemPattern = dragItem_->GetPattern<ListItemPattern>();
    auto handleDragUpdate = itemPattern->panEvent_->GetActionUpdateEventFunc();
    GestureEvent info;
    info.SetMainDelta(dragDelta);
    handleDragUpdate(info);
    FlushUITasks();
}

void ListSwipeTestNg::HandleDragEnd(float velocityDelta)
{
    auto itemPattern = dragItem_->GetPattern<ListItemPattern>();
    auto handleDragEnd = itemPattern->panEvent_->GetActionEndEventFunc();
    GestureEvent info;
    info.SetMainVelocity(velocityDelta);
    handleDragEnd(info);
    FlushUITasks();
}

/**
 * @tc.name: SwiperItem001
 * @tc.desc: Set startNode, test drag and startNode layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF startNodeRect = RectF(-START_NODE_LEN, 0, START_NODE_LEN, ITEM_MAIN_SIZE);
    RectF itemNodeRect = RectF(0, 0, WIDTH, ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe start less than threshold
     * @tc.expected: Animate back after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(START_NODE_TH, 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(START_NODE_TH, 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start greater than threshold
     * @tc.expected: Animate start after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_TH + 1);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(START_NODE_TH + 1, 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(START_NODE_TH + 1, 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, -START_NODE_TH, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(Position(item_, START_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, -(START_NODE_TH + 1), 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem002
 * @tc.desc: Set endNode, test drag and endNode layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem002, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF endNodeRect = RectF(WIDTH, 0, END_NODE_LEN, ITEM_MAIN_SIZE);
    RectF itemNodeRect = RectF(0, 0, WIDTH, ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe end less than threshold
     * @tc.expected: Animate back after drag end
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    HandleDragStart(item_);
    HandleDragUpdate(-END_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(-END_NODE_TH, 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(-END_NODE_TH, 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end greater than threshold
     * @tc.expected: Animate end after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(-(END_NODE_TH + 1));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(-(END_NODE_TH + 1), 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(-(END_NODE_TH + 1), 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_TH, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_TH + 1, 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem003
 * @tc.desc: Set startNode, SwipeEdgeEffect::None, can not over the edge
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem003, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe end
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(-START_NODE_LEN);
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe start exceed
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_LEN);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
    HandleDragUpdate(1);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
}

/**
 * @tc.name: DragSwipeItem004
 * @tc.desc: Set endNode, SwipeEdgeEffect::None, can not over the edge
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem004, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(END_NODE_LEN);
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe end exceed
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(-END_NODE_LEN);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
    HandleDragUpdate(-1);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
}

/**
 * @tc.name: DragSwipeItem005
 * @tc.desc: Set startNode, SwipeEdgeEffect::Spring, can over the edge
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem005, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::Spring);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe end
     * @tc.expected: Can over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(-10);
    EXPECT_TRUE(Position(item_, -10));
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe start exceed
     * @tc.expected: Can over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_LEN);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
    HandleDragUpdate(1);
    EXPECT_TRUE(Position(item_, START_NODE_LEN + 1));
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
}

/**
 * @tc.name: DragSwipeItem006
 * @tc.desc: Set endNode, SwipeEdgeEffect::Spring, can over the edge
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem006, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(nullptr, endFunc, V2::SwipeEdgeEffect::Spring);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(10);
    EXPECT_TRUE(Position(item_, 10));
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe end exceed
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(-END_NODE_LEN);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
    HandleDragUpdate(-1);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN - 1));
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
}

/**
 * @tc.name: DragSwipeItem_Layout001
 * @tc.desc: Test Drag with startNode in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Layout001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF startNodeRect = RectF(WIDTH, 0, START_NODE_LEN, ITEM_MAIN_SIZE);
    RectF itemNodeRect = RectF(0, 0, WIDTH, ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe start less than threshold
     * @tc.expected: Animate back after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(-START_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(-START_NODE_TH, 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(-START_NODE_TH, 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start greater than threshold
     * @tc.expected: Animate start after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(-(START_NODE_TH + 1));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(-(START_NODE_TH + 1), 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(-(START_NODE_TH + 1), 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, -START_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, START_NODE_TH, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(Position(item_, -START_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, START_NODE_TH + 1, 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_Layout002
 * @tc.desc: Test Drag with endNode in RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Layout002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF endNodeRect = RectF(-END_NODE_LEN, 0, END_NODE_LEN, ITEM_MAIN_SIZE);
    RectF itemNodeRect = RectF(0, 0, WIDTH, ITEM_MAIN_SIZE);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe end less than threshold
     * @tc.expected: Animate back after drag end
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    HandleDragStart(item_);
    HandleDragUpdate(END_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(END_NODE_TH, 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(END_NODE_TH, 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end greater than threshold
     * @tc.expected: Animate end after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(END_NODE_TH + 1);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(END_NODE_TH + 1, 0)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(END_NODE_TH + 1, 0)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, END_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, -END_NODE_TH, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(Position(item_, END_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, -(END_NODE_TH + 1), 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_Layout003
 * @tc.desc: Test Drag with startNode in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Layout003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF startNodeRect = RectF(0, -START_NODE_LEN, ITEM_MAIN_SIZE, START_NODE_LEN);
    RectF itemNodeRect = RectF(0, 0, ITEM_MAIN_SIZE, HEIGHT);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe start less than threshold
     * @tc.expected: Animate back after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(0, START_NODE_TH)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, START_NODE_TH)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start greater than threshold
     * @tc.expected: Animate start after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_TH + 1);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(0, START_NODE_TH + 1)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, START_NODE_TH + 1)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, -START_NODE_TH, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(Position(item_, START_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, -(START_NODE_TH + 1), 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_Layout004
 * @tc.desc: Test Drag with endNode in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Layout004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF endNodeRect = RectF(0, HEIGHT, ITEM_MAIN_SIZE, END_NODE_LEN);
    RectF itemNodeRect = RectF(0, 0, ITEM_MAIN_SIZE, HEIGHT);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe end less than threshold
     * @tc.expected: Animate back after drag end
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    HandleDragStart(item_);
    HandleDragUpdate(-END_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(0, -END_NODE_TH)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, -END_NODE_TH)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end greater than threshold
     * @tc.expected: Animate end after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(-(END_NODE_TH + 1));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(0, -(END_NODE_TH + 1))));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, -(END_NODE_TH + 1))));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_TH, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_TH + 1, 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_Layout005
 * @tc.desc: Test Drag with startNode in RTL and Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Layout005, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF startNodeRect = RectF(0, -START_NODE_LEN, ITEM_MAIN_SIZE, START_NODE_LEN);
    RectF itemNodeRect = RectF(0, 0, ITEM_MAIN_SIZE, HEIGHT);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe start less than threshold
     * @tc.expected: Animate back after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(0, START_NODE_TH)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, START_NODE_TH)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe start greater than threshold
     * @tc.expected: Animate start after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(START_NODE_TH + 1);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), startNodeRect + OffsetF(0, START_NODE_TH + 1)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, START_NODE_TH + 1)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, START_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, -START_NODE_TH, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(Position(item_, START_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, -(START_NODE_TH + 1), 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_Layout006
 * @tc.desc: Test Drag with endNode in RTL and Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Layout006, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    RectF endNodeRect = RectF(0, HEIGHT, ITEM_MAIN_SIZE, END_NODE_LEN);
    RectF itemNodeRect = RectF(0, 0, ITEM_MAIN_SIZE, HEIGHT);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step1. Swipe end less than threshold
     * @tc.expected: Animate back after drag end
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    HandleDragStart(item_);
    HandleDragUpdate(-END_NODE_TH);
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(0, -END_NODE_TH)));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, -END_NODE_TH)));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, 0));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe end greater than threshold
     * @tc.expected: Animate end after drag end
     */
    HandleDragStart(item_);
    HandleDragUpdate(-(END_NODE_TH + 1));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 0), endNodeRect + OffsetF(0, -(END_NODE_TH + 1))));
    EXPECT_TRUE(IsEqual(GetChildRect(item_, 1), itemNodeRect + OffsetF(0, -(END_NODE_TH + 1))));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    HandleDragEnd(0);
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_END);

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_TH, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_TH + 1, 0, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem001
 * @tc.desc: Set startNode, swipe start with velocity
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Velocity001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe start less than threshold
     * @tc.expected: Animate back after drag end
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    EXPECT_TRUE(DragSwiperItem(item_, 10, SWIPER_SPEED_TH, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe start greater than threshold
     * @tc.expected: Animate start after drag end
     */
    EXPECT_TRUE(DragSwiperItem(item_, 10, SWIPER_SPEED_TH + 1, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(Position(item_, START_NODE_LEN));

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, -10, -SWIPER_SPEED_TH, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(Position(item_, START_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, -10, -SWIPER_SPEED_TH - 1, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_Velocity002
 * @tc.desc: Set endNode, swipe end with velocity
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_Velocity002, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe end less than threshold
     * @tc.expected: Animate back after drag end
     */
    EXPECT_TRUE(DragSwiperItem(item_, -10, -SWIPER_SPEED_TH, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe end greater than threshold
     * @tc.expected: Animate end after drag end
     */
    EXPECT_TRUE(DragSwiperItem(item_, -10, -SWIPER_SPEED_TH - 1, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));

    /**
     * @tc.steps: step3. Swipe item less than threshold
     * @tc.expected: Animate back
     */
    EXPECT_TRUE(DragSwiperItem(item_, 10, SWIPER_SPEED_TH, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(Position(item_, -END_NODE_LEN));

    /**
     * @tc.steps: step4. Swipe item greater than threshold
     * @tc.expected: Animate item
     */
    EXPECT_TRUE(DragSwiperItem(item_, 10, SWIPER_SPEED_TH + 1, ListItemSwipeIndex::ITEM_CHILD));
    EXPECT_TRUE(Position(item_, 0));
}

/**
 * @tc.name: DragSwipeItem_DeleteArea001
 * @tc.desc: Set startNode, Test swiperAction Attribute for ListItem, set enterStartDeleteArea callback and
 * exitStartDeleteArea callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea001, TestSize.Level1)
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
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    itemModel.SetDeleteArea(std::move(startFunc), std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent),
        nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe start
     */
    EXPECT_TRUE(DragSwiperItem(item_, START_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_START));

    /**
     * @tc.steps: step2. Repeat entry and exit
     * @tc.expected: Trigger entry exit event
     */
    HandleDragStart(item_);
    HandleDragUpdate(DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);

    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);

    isEntry = false;
    HandleDragUpdate(DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);

    isExit = false;
    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);

    HandleDragEnd(0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move middle of DELETE_AREA_DISTANCE and release
     * @tc.expected: No trigger delete
     */
    isDelete = false;
    DragSwiperItem(item_, DELETE_AREA_DISTANCE / 2, 0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step4. move DELETE_AREA_DISTANCE and release
     * @tc.expected: Trigger delete
     */
    isDelete = false;
    DragSwiperItem(item_, DELETE_AREA_DISTANCE, 0);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: DragSwipeItem_DeleteArea002
 * @tc.desc: Set endNode, Test swiperAction Attribute for ListItem, set enterEndDeleteArea callback and
 * exitEndDeleteArea callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea002, TestSize.Level1)
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
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    itemModel.SetDeleteArea(std::move(endFunc), std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent),
        nullptr, Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();
    const float exceedArea = DELETE_AREA_DISTANCE + 1;

    /**
     * @tc.steps: step1. Swipe end
     */
    EXPECT_TRUE(DragSwiperItem(item_, -END_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_END));

    /**
     * @tc.steps: step2. Repeat entry and exit
     * @tc.expected: Trigger entry exit event
     */
    HandleDragStart(item_);
    HandleDragUpdate(-exceedArea);
    EXPECT_TRUE(isEntry);

    HandleDragUpdate(exceedArea);
    EXPECT_TRUE(isExit);

    isEntry = false;
    HandleDragUpdate(-exceedArea);
    EXPECT_TRUE(isEntry);

    isExit = false;
    HandleDragUpdate(exceedArea);
    EXPECT_TRUE(isExit);

    HandleDragEnd(0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move middle of exceedArea and release
     * @tc.expected: No trigger delete
     */
    isDelete = false;
    DragSwiperItem(item_, -exceedArea / 2, 0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step4. move exceedArea and release
     * @tc.expected: Trigger delete
     */
    isDelete = false;
    DragSwiperItem(item_, -exceedArea, 0);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: DragSwipeItem_DeleteArea003
 * @tc.desc: Set startNode, startDeleteArea, deleteAreaDistance SwipeEdgeEffect::None
 * List can swiper right great than START_NODE_LEN
 * if great than START_NODE_LEN + deleteAreaDistance,
 * it will adjust to START_NODE_LEN + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea003, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    ListItemModelNG itemModel = CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    itemModel.SetDeleteArea(
        std::move(startFunc), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    CreateSwipeDone();
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(-START_NODE_LEN);
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe start exceed
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(maxDistance);
    EXPECT_TRUE(Position(item_, maxDistance));
    HandleDragUpdate(1);
    EXPECT_TRUE(Position(item_, maxDistance));
}

/**
 * @tc.name: DragSwipeItem_DeleteArea004
 * @tc.desc: Set the swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and
 * EdgeEffect is none, List can swiper left great than endNode size, if great than endNode size +
 * deleteAreaDistance, it will adjust to endNode size + deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea004, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    ListItemModelNG itemModel = CreateSwipeItem(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    itemModel.SetDeleteArea(
        std::move(endFunc), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), false);
    CreateSwipeDone();
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(END_NODE_LEN);
    EXPECT_TRUE(Position(item_, 0));

    /**
     * @tc.steps: step2. Swipe end exceed
     * @tc.expected: Can not over the edge
     */
    HandleDragStart(item_);
    HandleDragUpdate(-maxDistance);
    EXPECT_TRUE(Position(item_, -maxDistance));
    HandleDragUpdate(-1);
    EXPECT_TRUE(Position(item_, -maxDistance));
}

/**
 * @tc.name: DragSwipeItem_DeleteArea005
 * @tc.desc: Test swiperAction Attribute for ListItem, set startNode, startDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the right distance great than startNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea005, TestSize.Level1)
{
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    itemModel.SetDeleteArea(
        std::move(startFunc), nullptr, nullptr, nullptr, onStateChangeFunc, Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();
    const float maxDistance = START_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe start greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = 1;
    HandleDragStart(item_);
    HandleDragUpdate(maxDistance);
    EXPECT_EQ(itemPattern_->curOffset_, maxDistance);
    HandleDragUpdate(moveDelta);
    EXPECT_GT(itemPattern_->curOffset_, maxDistance);
    HandleDragEnd(0);
    EXPECT_EQ(itemPattern_->curOffset_, START_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), START_NODE_LEN);

    /**
     * @tc.steps: step2. Swipe end
     * @tc.expected: Can continue to move
     */
    moveDelta = -1;
    HandleDragStart(item_);
    HandleDragUpdate(-START_NODE_LEN);
    HandleDragUpdate(moveDelta);
    EXPECT_LT(itemPattern_->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), itemPattern_->curOffset_);
    HandleDragEnd(0);
    EXPECT_EQ(itemPattern_->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: DragSwipeItem_DeleteArea006
 * @tc.desc: Test swiperAction Attribute for ListItem, set endNode, endDeleteArea, deleteAreaDistance and edge
 * effect is spring. move friction take effect when moving to the left distance great than endNode size +
 * deleteAreaDistance
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea006, TestSize.Level1)
{
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    itemModel.SetDeleteArea(
        std::move(endFunc), nullptr, nullptr, nullptr, onStateChangeFunc, Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    float moveDelta = -1;
    HandleDragStart(item_);
    HandleDragUpdate(-maxDistance);
    EXPECT_EQ(itemPattern_->curOffset_, -maxDistance);
    HandleDragUpdate(moveDelta);
    EXPECT_LT(itemPattern_->curOffset_, -maxDistance);
    EXPECT_EQ(offset.ConvertToPx(), static_cast<int32_t>(itemPattern_->curOffset_));
    HandleDragEnd(0);
    EXPECT_EQ(itemPattern_->curOffset_, -END_NODE_LEN);
    EXPECT_EQ(offset.ConvertToPx(), -END_NODE_LEN);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    /**
     * @tc.steps: step1. Swipe start
     * @tc.expected: Can continue to move
     */
    moveDelta = 1;
    HandleDragStart(item_);
    HandleDragUpdate(END_NODE_LEN);
    HandleDragUpdate(moveDelta);
    EXPECT_GT(itemPattern_->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), itemPattern_->curOffset_);
    HandleDragEnd(0);
    EXPECT_EQ(itemPattern_->curOffset_, 0);
    EXPECT_EQ(offset.ConvertToPx(), 0);
}

/**
 * @tc.name: DragSwipeItem_DeleteArea007
 * @tc.desc: Do not set startNode, test callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea007, TestSize.Level1)
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
    itemModel.SetDeleteArea(nullptr, std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent), nullptr,
        Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Repeat entry and exit
     * @tc.expected: Trigger entry exit event
     */
    HandleDragStart(item_);
    HandleDragUpdate(DELETE_AREA_DISTANCE);
    HandleDragUpdate(1);
    EXPECT_TRUE(isEntry);

    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);

    isEntry = false;
    HandleDragUpdate(DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);

    isExit = false;
    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);

    HandleDragEnd(0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     * @tc.expected: No trigger delete
     */
    isDelete = false;
    DragSwiperItem(item_, DELETE_AREA_DISTANCE / 2, 0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     * @tc.expected: Trigger delete
     */
    isDelete = false;
    HandleDragStart(item_);
    HandleDragUpdate(DELETE_AREA_DISTANCE);
    HandleDragUpdate(1);
    HandleDragEnd(0);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: DragSwipeItem_DeleteArea008
 * @tc.desc: Do not set endNode, test callback
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, DragSwipeItem_DeleteArea008, TestSize.Level1)
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
    itemModel.SetDeleteArea(nullptr, std::move(deleteEvent), std::move(enterEvent), std::move(exitEvent), nullptr,
        Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Repeat entry and exit
     * @tc.expected: Trigger entry exit event
     */
    HandleDragStart(item_);
    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    HandleDragUpdate(-1);
    EXPECT_TRUE(isEntry);

    HandleDragUpdate(DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);

    isEntry = false;
    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isEntry);

    isExit = false;
    HandleDragUpdate(DELETE_AREA_DISTANCE);
    EXPECT_TRUE(isExit);

    HandleDragEnd(0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step2. move middle of DELETE_AREA_DISTANCE and release
     * @tc.expected: No trigger delete
     */
    isDelete = false;
    DragSwiperItem(item_, -DELETE_AREA_DISTANCE / 2, 0);
    EXPECT_FALSE(isDelete);

    /**
     * @tc.steps: step3. move DELETE_AREA_DISTANCE and release
     * @tc.expected: Trigger delete
     */
    isDelete = false;
    HandleDragStart(item_);
    HandleDragUpdate(-DELETE_AREA_DISTANCE);
    HandleDragUpdate(-1);
    HandleDragEnd(0);
    EXPECT_TRUE(isDelete);
}

/**
 * @tc.name: TestSetSwipeActionByModifier
 * @tc.desc: Test SwipeEdgeEffect::None for ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, TestSetSwipeActionByModifier, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init ListItem with SwipeEdgeEffect::None
     */
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    CreateSwipeDone();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None, AceType::RawPtr(item_));

    /**
     * @tc.steps: step2. Check SwipeEdgeEffect::None effective
     * @tc.expected: SwipeEdgeEffect::None is effective
     */
    EXPECT_EQ(itemPattern_->GetEdgeEffect(), V2::SwipeEdgeEffect::None);
}

/**
 * @tc.name: ResetSwipeStatus001
 * @tc.desc: If drag different ListItem, the previous item would be reset.
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ResetSwipeStatus001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    auto secondItem = GetChildFrameNode(frameNode_, 1);
    auto secondItemPattern = GetChildPattern<ListItemPattern>(frameNode_, 1);

    /**
     * @tc.steps: step1. Swipe first item
     * @tc.expected: The first item swiperIndex_ changed.
     */
    DragSwiperItem(item_, START_NODE_LEN, 0);
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
    EXPECT_EQ(secondItemPattern->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);

    /**
     * @tc.steps: step2. Swipe second item
     * @tc.expected: The second item swiperIndex_ changed, and first item was be reset.
     */
    DragSwiperItem(secondItem, START_NODE_LEN, 0);
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_EQ(secondItemPattern->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);
}

/**
 * @tc.name: ResetSwipeStatus002
 * @tc.desc: Reset swipe status when lanes changed
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ResetSwipeStatus002, TestSize.Level1)
{
    ListModelNG model = CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe first item
     * @tc.expected: The first item swiperIndex_ changed.
     */
    EXPECT_TRUE(DragSwiperItem(item_, START_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_START));

    /**
     * @tc.steps: step2. Change lanes
     * @tc.expected: Rest status
     */
    model.SetLanes(AceType::RawPtr(frameNode_), 2);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: ResetSwipeStatus003
 * @tc.desc: Reset swipe status when scrolling
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ResetSwipeStatus003, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe first item
     * @tc.expected: The first item swiperIndex_ changed.
     */
    DragSwiperItem(item_, START_NODE_LEN, 0);
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step2. Drag list
     * @tc.expected: Rest status
     */
    DragAction(frameNode_, Offset(), -10, 0);
    EXPECT_TRUE(Position(-10));
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: ResetSwipeStatus004
 * @tc.desc: Reset swipe status when ListDirection changed
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ResetSwipeStatus004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Swipe first item
     * @tc.expected: The first item swiperIndex_ changed.
     */
    DragSwiperItem(item_, START_NODE_LEN, 0);
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step2. Change ListDirection
     * @tc.expected: Rest status
     */
    model.SetListDirection(AceType::RawPtr(frameNode_), static_cast<int32_t>(Axis::HORIZONTAL));
    FlushUITasks();
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: OtherTest001
 * @tc.desc: Test SetStartNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, OtherTest001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    const int32_t startNodeIndex = 0;
    RefPtr<NG::UINode> startNode;
    GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE)();
    startNode = NG::ViewStackProcessor::GetInstance()->Finish();
    itemPattern_->SetStartNode(startNode);
    EXPECT_EQ(GetChildFrameNode(item_, startNodeIndex), startNode);
    itemPattern_->SetStartNode(nullptr);
    EXPECT_EQ(itemPattern_->startNodeIndex_, -1);
}

/**
 * @tc.name: OtherTest002
 * @tc.desc: Test SetEndNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, OtherTest002, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    const int32_t endNodeIndex = 0;
    RefPtr<NG::UINode> endNode;
    GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE)();
    endNode = NG::ViewStackProcessor::GetInstance()->Finish();
    itemPattern_->SetEndNode(endNode);
    EXPECT_EQ(GetChildFrameNode(item_, endNodeIndex), endNode);
    itemPattern_->SetEndNode(nullptr);
    EXPECT_EQ(itemPattern_->endNodeIndex_, -1);
}

/**
 * @tc.name: OtherTest003
 * @tc.desc: Test closeAllSwipeAction
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, OtherTest003, TestSize.Level1)
{
    SwipeActionState curState = SwipeActionState::COLLAPSED;
    auto onStateChangeFunc = [&curState](SwipeActionState state) { curState = state; };
    Dimension offset;
    auto onOffsetChange = [&offset](int val) { offset = Dimension(val, DimensionUnit::VP); };
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, std::move(onOffsetChange), V2::SwipeEdgeEffect::Spring);
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    itemModel.SetDeleteArea(std::move(endFunc), nullptr, nullptr, nullptr, std::move(onStateChangeFunc),
        Dimension(DELETE_AREA_DISTANCE), false);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();
    const float maxDistance = END_NODE_LEN + DELETE_AREA_DISTANCE;

    /**
     * @tc.steps: step1. Swipe end greater than maxDistance
     * @tc.expected: Can continue to move
     */
    DragSwiperItem(item_, -maxDistance, 0);
    EXPECT_EQ(curState, SwipeActionState::EXPANDED);

    OnFinishFunc onFinishCallBack;
    pattern_->positionController_->CloseAllSwipeActions(std::move(onFinishCallBack));
    EXPECT_EQ(curState, SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: OtherTest004
 * @tc.desc: Test SetDeleteArea after create list done
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, OtherTest004, TestSize.Level1)
{
    CreateList();
    ListItemModelNG itemModel = CreateListItem();
    itemModel.SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    itemModel.SetDeleteArea(
        std::move(startFunc), nullptr, nullptr, nullptr, nullptr, Dimension(DELETE_AREA_DISTANCE), true);
    GetRowOrColBuilder(FILL_LENGTH, Dimension(ITEM_MAIN_SIZE))();
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Set start node
     * @tc.expected: Start node changed
     */
    startFunc();
    auto startElement = ViewStackProcessor::GetInstance()->Finish();
    auto startNode = AceType::DynamicCast<FrameNode>(startElement);
    const float startDeleteDistance = DELETE_AREA_DISTANCE - 1.f;
    itemModel.SetDeleteArea(AceType::RawPtr(item_), AceType::RawPtr(startNode), nullptr, nullptr, nullptr, nullptr,
        Dimension(startDeleteDistance), true);
    FlushUITasks();
    auto itemLayoutProperty = itemPattern_->GetLayoutProperty<ListItemLayoutProperty>();
    EXPECT_EQ(itemLayoutProperty->GetStartDeleteAreaDistance(), Dimension(startDeleteDistance));
    const int32_t startNodeIndex = 0;
    EXPECT_EQ(GetChildFrameNode(item_, startNodeIndex), startNode);

    /**
     * @tc.steps: step2. Set end node
     * @tc.expected: End node was be setted
     */
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    endFunc();
    auto endElement = ViewStackProcessor::GetInstance()->Finish();
    auto endNode = AceType::DynamicCast<FrameNode>(endElement);
    const float endDeleteDistance = END_NODE_LEN - 1.f;
    itemModel.SetDeleteArea(AceType::RawPtr(item_), AceType::RawPtr(endNode), nullptr, nullptr, nullptr, nullptr,
        Dimension(endDeleteDistance), false);
    FlushUITasks();
    EXPECT_EQ(itemLayoutProperty->GetEndDeleteAreaDistance(), Dimension(endDeleteDistance));
    const int32_t endNodeIndex = 2;
    EXPECT_EQ(GetChildFrameNode(item_, endNodeIndex), endNode);
}

/**
 * @tc.name: ClickJudge001
 * @tc.desc: Test ClickJudge with startNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Not expand startNode
     * @tc.expected: return true
     */
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, -10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, ITEM_MAIN_SIZE + 10.f)));

    /**
     * @tc.steps: step2. Expand startNode
     * @tc.expected: Click not at startNode would return true
     */
    EXPECT_TRUE(DragSwiperItem(item_, START_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(-10.f, 10.f)));
    EXPECT_FALSE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(START_NODE_LEN + 1.f, 10.f)));
}

/**
 * @tc.name: ClickJudge002
 * @tc.desc: Test ClickJudge with endNode
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, ClickJudge002, TestSize.Level1)
{
    CreateList();
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Expand endNode
     * @tc.expected: Click not at endNode would return true
     */
    EXPECT_TRUE(DragSwiperItem(item_, -END_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_FALSE(itemPattern_->ClickJudge(PointF(WIDTH - 10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(WIDTH + 10.f, 10.f)));
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
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Not expand startNode
     * @tc.expected: return true
     */
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, -10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, ITEM_MAIN_SIZE + 10.f)));

    /**
     * @tc.steps: step2. Expand startNode
     * @tc.expected: Click not at startNode would return true
     */
    EXPECT_TRUE(DragSwiperItem(item_, -START_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_FALSE(itemPattern_->ClickJudge(PointF(WIDTH - 10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(WIDTH + 10.f, 10.f)));
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
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Expand endNode
     * @tc.expected: Click not at endNode would return true
     */
    EXPECT_TRUE(DragSwiperItem(item_, END_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(-10.f, 10.f)));
    EXPECT_FALSE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(END_NODE_LEN + 1.f, 10.f)));
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
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Not expand startNode
     * @tc.expected: return true
     */
    EXPECT_EQ(itemPattern_->GetSwiperIndex(), ListItemSwipeIndex::ITEM_CHILD);
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(-10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(ITEM_MAIN_SIZE + 10.f, 10.f)));

    /**
     * @tc.steps: step2. Expand startNode
     * @tc.expected: Click not at startNode would return true
     */
    EXPECT_TRUE(DragSwiperItem(item_, START_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_START));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, -10.f)));
    EXPECT_FALSE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, START_NODE_LEN + 1.f)));
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
    auto endFunc = GetRowOrColBuilder(END_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItems(nullptr, endFunc, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();

    /**
     * @tc.steps: step1. Expand endNode
     * @tc.expected: Click not at endNode would return true
     */
    EXPECT_TRUE(DragSwiperItem(item_, -END_NODE_LEN, 0, ListItemSwipeIndex::SWIPER_END));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, 10.f)));
    EXPECT_FALSE(itemPattern_->ClickJudge(PointF(10.f, HEIGHT - 10.f)));
    EXPECT_TRUE(itemPattern_->ClickJudge(PointF(10.f, HEIGHT + 10.f)));
}

/**
 * @tc.name: SetBuilderComponent01
 * @tc.desc: Test BuilderComponent of start in swipeAction.
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SetBuilderComponent01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Creat swipeItemts with component content in List.
     */
    const int32_t startNodeIndex = 0;
    const int32_t itemNodeIndex = 1;
    CreateList();
    auto startBuilder = CreateCustomNode("Start", START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItemsWithComponentContent(startBuilder, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    const RectF itemNodeInitialRect = RectF(0, 0, WIDTH, ITEM_MAIN_SIZE);
    const RectF itemNodeSwipeStartRect = RectF(START_NODE_LEN, 0, WIDTH, ITEM_MAIN_SIZE);
    const float slightSwipeDelta = START_NODE_LEN * SWIPER_TH;
    const float obviousSwipeDelta = START_NODE_LEN * SWIPER_TH + 1;

    /**
     * @tc.steps: step2. Swipe start.
     * @tc.expected: StartNode can be added and moved successfully.
     */
    DragSwiperItem(item_, slightSwipeDelta, SWIPER_SPEED_TH);
    RectF startNodeRect = GetChildRect(item_, startNodeIndex);
    RectF itemNodeRect = GetChildRect(item_, itemNodeIndex);
    RectF expectStartNodeRect = RectF(slightSwipeDelta - START_NODE_LEN, 0, START_NODE_LEN, ITEM_MAIN_SIZE);
    RectF expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    ListItemSwipeIndex swiperIndex = itemPattern_->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);

    DragSwiperItem(item_, obviousSwipeDelta, SWIPER_SPEED_TH);
    startNodeRect = GetChildRect(item_, startNodeIndex);
    itemNodeRect = GetChildRect(item_, itemNodeIndex);
    expectStartNodeRect = RectF(0, 0, START_NODE_LEN, ITEM_MAIN_SIZE);
    expectItemNodeRect = itemNodeSwipeStartRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = itemPattern_->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::SWIPER_START);

    /**
     * @tc.steps: step3. Collapse start.
     * @tc.expected: StartNode can be collapse.
     */
    DragSwiperItem(item_, -obviousSwipeDelta, SWIPER_SPEED_TH);
    startNodeRect = GetChildRect(item_, startNodeIndex);
    itemNodeRect = GetChildRect(item_, itemNodeIndex);
    expectStartNodeRect = RectF(-obviousSwipeDelta, 0, START_NODE_LEN, ITEM_MAIN_SIZE);
    expectItemNodeRect = itemNodeInitialRect;
    EXPECT_TRUE(IsEqual(startNodeRect, expectStartNodeRect));
    EXPECT_TRUE(IsEqual(itemNodeRect, expectItemNodeRect));
    swiperIndex = itemPattern_->GetSwiperIndex();
    EXPECT_EQ(swiperIndex, ListItemSwipeIndex::ITEM_CHILD);
}

/**
 * @tc.name: SwipeForward001
 * @tc.desc: Test SwipeForward
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwipeForward001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    itemPattern_->swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
    itemPattern_->SwipeForward();
    EXPECT_EQ(itemPattern_->GetSwipeActionState(), SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwipeForward002
 * @tc.desc: Test SwipeForward
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwipeForward002, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    itemPattern_->swipeActionState_ = SwipeActionState::COLLAPSED;
    itemPattern_->SwipeForward();
    EXPECT_EQ(itemPattern_->GetSwipeActionState(), SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwipeForward003
 * @tc.desc: Test SwipeForward
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwipeForward003, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    itemPattern_->swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
    itemPattern_->SwipeForward();
    EXPECT_EQ(itemPattern_->GetSwipeActionState(), SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwipeBackward001
 * @tc.desc: Test SwipeBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwipeBackward001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    itemPattern_->swiperIndex_ = ListItemSwipeIndex::SWIPER_END;
    itemPattern_->SwipeBackward();
    EXPECT_EQ(itemPattern_->GetSwipeActionState(), SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwipeBackward002
 * @tc.desc: Test SwipeBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwipeBackward002, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    itemPattern_->swipeActionState_ = SwipeActionState::COLLAPSED;
    itemPattern_->SwipeBackward();
    EXPECT_EQ(itemPattern_->GetSwipeActionState(), SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: SwipeBackward003
 * @tc.desc: Test SwipeBackward
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, SwipeBackward003, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    itemPattern_->swiperIndex_ = ListItemSwipeIndex::SWIPER_START;
    itemPattern_->SwipeBackward();
    EXPECT_EQ(itemPattern_->GetSwipeActionState(),  SwipeActionState::COLLAPSED);
}

/**
 * @tc.name: FireSwipeActionStateChange001
 * @tc.desc: Test FireSwipeActionStateChange
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, FireSwipeActionStateChange001, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    ListItemSwipeIndex newSwiperIndex = ListItemSwipeIndex::SWIPER_END;
    itemPattern_->FireSwipeActionStateChange(newSwiperIndex);
    EXPECT_EQ(itemPattern_->GetSwipeActionState(),  SwipeActionState::EXPANDED);
}

/**
 * @tc.name: FireSwipeActionStateChange002
 * @tc.desc: Test FireSwipeActionStateChange
 * @tc.type: FUNC
 */
HWTEST_F(ListSwipeTestNg, FireSwipeActionStateChange002, TestSize.Level1)
{
    CreateList();
    auto startFunc = GetRowOrColBuilder(START_NODE_LEN, ITEM_MAIN_SIZE);
    CreateSwipeItem(startFunc, nullptr, V2::SwipeEdgeEffect::None);
    CreateSwipeDone();
    ListItemSwipeIndex newSwiperIndex = ListItemSwipeIndex::SWIPER_START;
    itemPattern_->FireSwipeActionStateChange(newSwiperIndex);
    EXPECT_EQ(itemPattern_->GetSwipeActionState(), SwipeActionState::EXPANDED);
}
} // namespace OHOS::Ace::NG
