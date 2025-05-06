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

#include "grid_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {
namespace {
void OnItemDragStartEvent(const ItemDragInfo&, int32_t)
{
    ButtonModelNG buttonModelNG;
    buttonModelNG.CreateWithLabel("label");
};
} // namespace

class GridEventTestNg : public GridTestNg {
public:
    void SetUp() override;
    void TearDown() override;
};
void GridEventTestNg::SetUp()
{
    GridTestNg::SetUp();
    MockAnimationManager::GetInstance().SetTicks(TICK);
}

void GridEventTestNg::TearDown()
{
    GridTestNg::TearDown();
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Handle drag not over scrollable distance
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDrag001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 600.0f);

    Offset startOffset = Offset();
    float dragDelta = -10.0f;
    float velocityDelta = -200.0f;
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: Handle drag in Horizontal and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDrag002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();
    EXPECT_TRUE(Position(0));

    Offset startOffset = Offset();
    float dragDelta = 10.0f;
    float velocityDelta = 200.0f;
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(TickPosition(-dragDelta - velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(-dragDelta - velocityDelta));
}

/**
 * @tc.name: HandleDragOverScroll001
 * @tc.desc: Handle drag over top in EdgeEffect::SPRING, will scroll back with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDragOverScroll001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. DragUpdate over top
     * @tc.expected: Scroll with drag
     */
    DragStart(frameNode_, Offset());
    const float dragDelta = 10.0f;
    DragUpdate(dragDelta);
    EXPECT_TRUE(Position(dragDelta));

    /**
     * @tc.steps: step2. DragEnd
     * @tc.expected: Scroll back with animation
     */
    float currentOffset = -(pattern_->GetTotalOffset());
    float velocityDelta = 100.0f;
    DragEnd(velocityDelta);
    EXPECT_TRUE(TickPosition(velocityDelta, currentOffset + velocityDelta));
    EXPECT_TRUE(TickPosition((currentOffset + velocityDelta) / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: HandleDragOverScroll002
 * @tc.desc: Handle drag over bottom in EdgeEffect::SPRING, will scroll back with animation
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDragOverScroll002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Scroll to bottom
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(Position(-600.0f));

    /**
     * @tc.steps: step2. DragUpdate over bottom
     * @tc.expected: Scroll with drag
     */
    DragStart(frameNode_, Offset());
    const float dragDelta = -10.0f;
    DragUpdate(dragDelta);
    EXPECT_TRUE(Position(-600.0f + dragDelta));

    /**
     * @tc.steps: step3. DragEnd
     * @tc.expected: Scroll back with animation
     */
    float currentOffset = -(pattern_->GetTotalOffset());
    float velocityDelta = -100.0f;
    DragEnd(velocityDelta);
    EXPECT_TRUE(TickPosition(velocityDelta, currentOffset + velocityDelta));
    EXPECT_TRUE(TickPosition(-600.0f + (currentOffset + 600.0f + velocityDelta) / TICK));
    EXPECT_TRUE(TickPosition(-600.0f));
}

/**
 * @tc.name: HandleDragOverScroll003
 * @tc.desc: Handle drag over top and drag back with velocity
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDragOverScroll003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, false);
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step1. Drag over the top
     */
    DragStart(frameNode_, Offset());
    DragUpdate(10.0f);
    EXPECT_TRUE(Position(10.0f));

    /**
     * @tc.steps: step2. Drag back and drag with velocity
     * @tc.expected: Inertial scrolling back
     */
    float currentOffset = -(pattern_->GetTotalOffset());
    DragUpdate(-5.0f);
    EXPECT_LT(-(pattern_->GetTotalOffset()), currentOffset);
    EXPECT_GT(-(pattern_->GetTotalOffset()), currentOffset - 5);

    currentOffset = -(pattern_->GetTotalOffset());
    float velocityDelta = -100.0f;
    DragEnd(velocityDelta);
    EXPECT_TRUE(TickPosition(velocityDelta, 0));
    EXPECT_TRUE(TickPosition(velocityDelta + currentOffset, velocityDelta + currentOffset));
}

/**
 * @tc.name: HandleDragOverScroll004
 * @tc.desc: Handle drag over in unScrollable scroll, and set AlwaysEnabled, still can drag over
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDragOverScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has no scrollable distance, and AlwaysEnabled
     * @tc.expected: Still can drag over
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateFixedItems(1);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_EQ(pattern_->GetScrollableDistance(), 0);

    float dragDelta = 10.0f;
    DragAction(frameNode_, Offset(), dragDelta, DRAG_VELOCITY);
    EXPECT_EQ(-(pattern_->GetTotalOffset()), dragDelta);
    EXPECT_GT(-(pattern_->GetTotalOffset()), 0);
    float currentOffset = -(pattern_->GetTotalOffset());
    EXPECT_TRUE(TickPosition(DRAG_VELOCITY, currentOffset + DRAG_VELOCITY));
    EXPECT_TRUE(TickPosition((currentOffset + DRAG_VELOCITY) / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: HandleDragOverScroll005
 * @tc.desc: Handle drag over edge in EdgeEffect::FADE, can not drag over
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDragOverScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EdgeEffect::FADE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step2. Drag over the top
     * @tc.expected: Can not drag over
     */
    DragAction(frameNode_, Offset(), 10.0f, DRAG_VELOCITY);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll to bottom and drag over the bottom
     * @tc.expected: Can not drag over
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    DragAction(frameNode_, Offset(), -10.0f, -DRAG_VELOCITY);
    EXPECT_TRUE(Position(-600.0f));
}

/**
 * @tc.name: HandleDragOverScroll006
 * @tc.desc: Handle drag over edge in EdgeEffect::NONE, can not drag over
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleDragOverScroll006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EdgeEffect::NONE
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateFixedItems(20);
    CreateDone();

    /**
     * @tc.steps: step2. Drag over the top
     * @tc.expected: Can not drag over
     */
    DragAction(frameNode_, Offset(), 10.0f, DRAG_VELOCITY);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll to bottom and drag over the bottom
     * @tc.expected: Can not drag over
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    DragAction(frameNode_, Offset(), -10.0f, -DRAG_VELOCITY);
    EXPECT_TRUE(Position(-600.0f));
}

/**
 * @tc.name: HandleBoxSelectDragStart
 * @tc.desc: Handle drag start for box select
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, HandleBoxSelectDragStart, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    GestureEvent info;
    info.SetRawGlobalLocation(Offset(50, 50));
    info.SetOffsetX(5);
    info.SetOffsetY(10);
    pattern_->HandleDragStart(info);
    EXPECT_TRUE(pattern_->canMultiSelect_);
    EXPECT_FALSE(pattern_->IsItemSelected(50, 50));
    pattern_->HandleDragEnd();

    GetChildPattern<GridItemPattern>(frameNode_, 0)->SetSelected(true);
    EXPECT_TRUE(pattern_->IsItemSelected(50, 50));
}

/**
 * @tc.name: OnItemDragWithAnimation001
 * @tc.desc: Test drag animation
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, OnItemDragWithAnimation001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(true);
    model.SetOnItemDragStart(OnItemDragStartEvent);
    CreateFixedItems(8);
    CreateDone();
    GestureEvent info;
    Point firstItemPoint = Point(ITEM_MAIN_SIZE * 0.5, ITEM_MAIN_SIZE / 2);
    info.SetGlobalPoint(firstItemPoint);
    std::map<int32_t, std::map<int32_t, int32_t>> matrix = { { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } } },
        { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    float itemWidth = 60.f;

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart,
     * @tc.expected: Do nothing
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_NE(eventHub_->dragDropProxy_, nullptr);
    EXPECT_NE(eventHub_->draggingItem_, nullptr);
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    /**
     * @tc.steps: step2. Trigger drag animation
     * @tc.expected: Nothing
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(itemWidth * 1.5);
    dragInfo.SetY(ITEM_MAIN_SIZE / 2);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 1);
    matrix = { { 0, { { 0, 1 }, { 1, 0 }, { 2, 2 }, { 3, 3 } } }, { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    dragInfo.SetX(itemWidth * 3.5);
    dragInfo.SetY(ITEM_MAIN_SIZE / 2);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 3);
    matrix = { { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 } } }, { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    dragInfo.SetX(itemWidth * 0.5);
    dragInfo.SetY(ITEM_MAIN_SIZE * 1.5);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 4);
    matrix = { { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } } }, { 1, { { 0, 0 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    dragInfo.SetX(itemWidth * 2.5);
    dragInfo.SetY(ITEM_MAIN_SIZE * 1.5);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 7);
    matrix = { { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } } }, { 1, { { 0, 5 }, { 1, 6 }, { 2, 7 }, { 3, 0 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);
}

/**
 * @tc.name: OnItemDragWithAnimation002
 * @tc.desc: Test drag animation
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, OnItemDragWithAnimation002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(true);
    model.SetOnItemDragStart(OnItemDragStartEvent);
    CreateFixedItems(8);
    CreateDone();
    GestureEvent info;
    Point firstItemPoint = Point(ITEM_MAIN_SIZE * 0.5, ITEM_MAIN_SIZE / 2);
    info.SetGlobalPoint(firstItemPoint);
    std::map<int32_t, std::map<int32_t, int32_t>> matrix = { { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } } },
        { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    float itemWidth = 60.f;

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart,
     * @tc.expected: Do nothing
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    /**
     * @tc.steps: step2. Trigger drag animation
     * @tc.expected: Expect every gridItem's position is correct.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(itemWidth * 1.5);
    dragInfo.SetY(ITEM_MAIN_SIZE / 2);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 1);
    auto rect = pattern_->GetItemRect(0);
    EXPECT_EQ(rect.x_, itemWidth);
    EXPECT_EQ(rect.y_, 0);
    auto rect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(rect1.x_, 0);
    EXPECT_EQ(rect1.y_, 0);
    auto rect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(rect2.x_, itemWidth * 2);
    EXPECT_EQ(rect2.y_, 0);
    auto rect3 = pattern_->GetItemRect(3);
    EXPECT_EQ(rect3.x_, itemWidth * 3);
    EXPECT_EQ(rect3.y_, 0);

    dragInfo.SetX(ITEM_MAIN_SIZE * 2.5);
    dragInfo.SetY(ITEM_MAIN_SIZE * 1.5);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 7);
    auto rect0 = pattern_->GetItemRect(0);
    EXPECT_EQ(rect0.x_, itemWidth * 3);
    EXPECT_EQ(rect0.y_, ITEM_MAIN_SIZE);
    auto rect5 = pattern_->GetItemRect(5);
    EXPECT_EQ(rect5.x_, 0);
    EXPECT_EQ(rect5.y_, ITEM_MAIN_SIZE);
    auto rect6 = pattern_->GetItemRect(6);
    EXPECT_EQ(rect6.x_, itemWidth);
    EXPECT_EQ(rect6.y_, ITEM_MAIN_SIZE);
    auto rect7 = pattern_->GetItemRect(7);
    EXPECT_EQ(rect7.x_, itemWidth * 2);
    EXPECT_EQ(rect7.y_, ITEM_MAIN_SIZE);
}

/**
 * @tc.name: OnItemDragWithAnimation003
 * @tc.desc: Test drag animation with layoutOptions
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, OnItemDragWithAnimation003, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(true);
    model.SetOnItemDragStart(OnItemDragStartEvent);
    model.SetLayoutOptions(option);
    CreateFixedItems(8);
    CreateDone();
    GestureEvent info;
    Point firstItemPoint = Point(ITEM_MAIN_SIZE * 0.5, ITEM_MAIN_SIZE / 2);
    info.SetGlobalPoint(firstItemPoint);
    std::map<int32_t, std::map<int32_t, int32_t>> matrix = { { 0, { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } } },
        { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    float itemWidth = 60.f;

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart,
     * @tc.expected: Do nothing
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);
    EXPECT_NE(eventHub_->dragDropProxy_, nullptr);
    EXPECT_NE(eventHub_->draggingItem_, nullptr);
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    /**
     * @tc.steps: step2. Trigger drag animation
     * @tc.expected: Nothing
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(itemWidth * 1.5);
    dragInfo.SetY(ITEM_MAIN_SIZE / 2);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 1);
    matrix = { { 0, { { 0, 1 }, { 1, 0 }, { 2, 2 }, { 3, 3 } } }, { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    dragInfo.SetX(itemWidth * 3.5);
    dragInfo.SetY(ITEM_MAIN_SIZE / 2);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 3);
    matrix = { { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 } } }, { 1, { { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    dragInfo.SetX(itemWidth * 0.5);
    dragInfo.SetY(ITEM_MAIN_SIZE * 1.5);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 4);
    matrix = { { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } } }, { 1, { { 0, 0 }, { 1, 5 }, { 2, 6 }, { 3, 7 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);

    dragInfo.SetX(itemWidth * 2.5);
    dragInfo.SetY(ITEM_MAIN_SIZE * 1.5);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 7);
    matrix = { { 0, { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 4 } } }, { 1, { { 0, 5 }, { 1, 6 }, { 2, 7 }, { 3, 0 } } } };
    EXPECT_EQ(pattern_->info_.gridMatrix_, matrix);
}

/**
 * @tc.name: OnItemDragWithAnimation004
 * @tc.desc: Test drag animation with layoutOptions
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, OnItemDragWithAnimation004, TestSize.Level1)
{
    GridLayoutOptions option;
    option.regularSize.rows = 1;
    option.regularSize.columns = 1;
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetEditable(true);
    model.SetSupportAnimation(true);
    model.SetOnItemDragStart(OnItemDragStartEvent);
    model.SetLayoutOptions(option);
    CreateFixedItems(8);
    CreateDone();
    GestureEvent info;
    Point firstItemPoint = Point(ITEM_MAIN_SIZE * 0.5, ITEM_MAIN_SIZE / 2);
    info.SetGlobalPoint(firstItemPoint);
    float itemWidth = 60.f;

    /**
     * @tc.steps: step1. Trigger HandleOnItemDragStart
     * @tc.expected: Do nothing
     */
    eventHub_->HandleOnItemDragStart(info);
    EXPECT_EQ(eventHub_->draggedIndex_, 0);

    /**
     * @tc.steps: step2. Trigger drag animation
     * @tc.expected: Expect every gridItem's position is correct.
     */
    ItemDragInfo dragInfo;
    dragInfo.SetX(itemWidth * 1.5);
    dragInfo.SetY(ITEM_MAIN_SIZE / 2);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 1);
    auto rect = pattern_->GetItemRect(0);
    EXPECT_EQ(rect.x_, itemWidth);
    EXPECT_EQ(rect.y_, 0);
    auto rect1 = pattern_->GetItemRect(1);
    EXPECT_EQ(rect1.x_, 0);
    EXPECT_EQ(rect1.y_, 0);
    auto rect2 = pattern_->GetItemRect(2);
    EXPECT_EQ(rect2.x_, itemWidth * 2);
    EXPECT_EQ(rect2.y_, 0);
    auto rect3 = pattern_->GetItemRect(3);
    EXPECT_EQ(rect3.x_, itemWidth * 3);
    EXPECT_EQ(rect3.y_, 0);

    dragInfo.SetX(ITEM_MAIN_SIZE * 2.5);
    dragInfo.SetY(ITEM_MAIN_SIZE * 1.5);
    eventHub_->FireOnItemDragMove(dragInfo, 0, 7);
    auto rect0 = pattern_->GetItemRect(0);
    EXPECT_EQ(rect0.x_, itemWidth * 3);
    EXPECT_EQ(rect0.y_, ITEM_MAIN_SIZE);
    auto rect5 = pattern_->GetItemRect(5);
    EXPECT_EQ(rect5.x_, 0);
    EXPECT_EQ(rect5.y_, ITEM_MAIN_SIZE);
    auto rect6 = pattern_->GetItemRect(6);
    EXPECT_EQ(rect6.x_, itemWidth);
    EXPECT_EQ(rect6.y_, ITEM_MAIN_SIZE);
    auto rect7 = pattern_->GetItemRect(7);
    EXPECT_EQ(rect7.x_, itemWidth * 2);
    EXPECT_EQ(rect7.y_, ITEM_MAIN_SIZE);
}

/**
 * @tc.name: GetOutOfScrollableOffset001
 * @tc.desc: Test GetOutOfScrollableOffset
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, GetOutOfScrollableOffset001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetMultiSelectable(true);
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    Offset offset = Offset(ITEM_MAIN_SIZE, HEIGHT + 10);
    pattern_->lastMouseMove_.SetLocalLocation(offset);
    float outOffset = pattern_->GetOutOfScrollableOffset();

    EXPECT_FLOAT_EQ(outOffset, -10.f);
}

/**
 * @tc.name: GetOutOfScrollableOffset002
 * @tc.desc: Test GetOutOfScrollableOffset with margin
 * @tc.type: FUNC
 */
HWTEST_F(GridEventTestNg, GetOutOfScrollableOffset002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetMultiSelectable(true);
    model.SetColumnsTemplate("1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    MarginProperty margin = { CalcLength(1), CalcLength(3), CalcLength(5), CalcLength(7) };
    layoutProperty_->UpdateMargin(margin);
    FlushUITasks();

    Offset offset = Offset(ITEM_MAIN_SIZE, HEIGHT + 10);
    pattern_->lastMouseMove_.SetLocalLocation(offset);
    float outOffset = pattern_->GetOutOfScrollableOffset();

    EXPECT_FLOAT_EQ(outOffset, -10.f);
}
} // namespace OHOS::Ace::NG
