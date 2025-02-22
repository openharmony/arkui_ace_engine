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

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {
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
    EXPECT_LT(-(pattern_->GetTotalOffset()), dragDelta);
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
} // namespace OHOS::Ace::NG
