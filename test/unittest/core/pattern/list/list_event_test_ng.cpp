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
constexpr float DEVIATION_HEIGHT = 20.f;
} // namespace

class ListEventTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Handle drag not over scrollable distance
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDrag001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    Offset startOffset = Offset();
    float dragDelta = -10.f;
    float velocityDelta = -90;
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: Handle drag in Horizontal and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDrag002, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ListModelNG model = CreateList();
    model.SetListDirection(Axis::HORIZONTAL);
    CreateListItems();
    CreateDone();
    EXPECT_TRUE(Position(0));

    Offset startOffset = Offset();
    float dragDelta = 10;
    float velocityDelta = 90;
    DragAction(frameNode_, startOffset, dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-dragDelta));
    EXPECT_TRUE(TickPosition(-dragDelta - velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(-dragDelta - velocityDelta));
}

/**
 * @tc.name: HandleDragOverScroll001
 * @tc.desc: Handle drag over top in EdgeEffect::SPRING, will scroll back with animation
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDragOverScroll001, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. DragUpdate over top
     * @tc.expected: Scroll with drag
     */
    DragStart(frameNode_, Offset());
    const float dragDelta = 10.f;
    DragUpdate(dragDelta);
    EXPECT_GT(-(pattern_->GetTotalOffset()), 0);
    EXPECT_LT(-(pattern_->GetTotalOffset()), dragDelta);

    /**
     * @tc.steps: step2. DragEnd
     * @tc.expected: Scroll back with animation
     */
    float currentOffset = -(pattern_->GetTotalOffset());
    float velocityDelta = 100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickByVelocityPosition(velocityDelta, currentOffset + velocityDelta));
    EXPECT_TRUE(TickPosition((currentOffset + velocityDelta) / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: HandleDragOverScroll002
 * @tc.desc: Handle drag over bottom in EdgeEffect::SPRING, will scroll back with animation
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDragOverScroll002, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. Scroll to bottom
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step2. DragUpdate over bottom
     * @tc.expected: Scroll with drag
     */
    DragStart(frameNode_, Offset());
    const float dragDelta = -10.f;
    DragUpdate(dragDelta);
    EXPECT_LT(-(pattern_->GetTotalOffset()), -VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_GT(-(pattern_->GetTotalOffset()), -VERTICAL_SCROLLABLE_DISTANCE + dragDelta);

    /**
     * @tc.steps: step3. DragEnd
     * @tc.expected: Scroll back with animation
     */
    float currentOffset = -(pattern_->GetTotalOffset());
    float velocityDelta = -100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickByVelocityPosition(velocityDelta, currentOffset + velocityDelta));
    EXPECT_TRUE(TickPosition(
        -VERTICAL_SCROLLABLE_DISTANCE + (currentOffset + VERTICAL_SCROLLABLE_DISTANCE + velocityDelta) / TICK));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: HandleDragOverScroll003
 * @tc.desc: Handle drag over top and drag back with velocity
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDragOverScroll003, TestSize.Level1)
{
    CreateList();
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. Drag over the top
     */
    DragStart(frameNode_, Offset());
    DragUpdate(10);
    EXPECT_LT(-(pattern_->GetTotalOffset()), 10);
    EXPECT_GT(-(pattern_->GetTotalOffset()), 0);

    /**
     * @tc.steps: step2. Drag back and drag with velocity
     * @tc.expected: Inertial scrolling back
     */
    float currentOffset = -(pattern_->GetTotalOffset());
    DragUpdate(-5);
    EXPECT_LT(-(pattern_->GetTotalOffset()), currentOffset);
    EXPECT_GT(-(pattern_->GetTotalOffset()), currentOffset - 5);

    currentOffset = -(pattern_->GetTotalOffset());
    float velocityDelta = -100;
    DragEnd(velocityDelta);
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickByVelocityPosition(velocityDelta, 0));
    EXPECT_TRUE(TickByVelocityPosition(velocityDelta + currentOffset, velocityDelta + currentOffset));
}

/**
 * @tc.name: HandleDragOverScroll004
 * @tc.desc: Handle drag over in unScrollable scroll, and set AlwaysEnabled, still can drag over
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDragOverScroll004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has no scrollable distance, and AlwaysEnabled
     * @tc.expected: Still can drag over
     */
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateListItems(1);
    CreateDone();
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_EQ(pattern_->GetScrollableDistance(), -300);

    float dragDelta = 10.f;
    DragAction(frameNode_, Offset(), dragDelta, DRAG_VELOCITY);
    EXPECT_LT(-(pattern_->GetTotalOffset()), dragDelta);
    EXPECT_GT(-(pattern_->GetTotalOffset()), 0);
    float currentOffset = -(pattern_->GetTotalOffset());
    EXPECT_TRUE(TickByVelocityPosition(DRAG_VELOCITY, currentOffset + DRAG_VELOCITY));
    EXPECT_TRUE(TickPosition((currentOffset + DRAG_VELOCITY) / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: HandleDragOverScroll005
 * @tc.desc: Handle drag over edge in EdgeEffect::FADE, can not drag over
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDragOverScroll005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EdgeEffect::FADE
     */
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step2. Drag over the top
     * @tc.expected: Can not drag over
     */
    DragAction(frameNode_, Offset(), 10, DRAG_VELOCITY);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll to bottom and drag over the bottom
     * @tc.expected: Can not drag over
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    DragAction(frameNode_, Offset(), -10, -DRAG_VELOCITY);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: HandleDragOverScroll006
 * @tc.desc: Handle drag over edge in EdgeEffect::NONE, can not drag over
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, HandleDragOverScroll006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. EdgeEffect::NONE
     */
    ListModelNG model = CreateList();
    model.SetEdgeEffect(EdgeEffect::NONE, true);
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step2. Drag over the top
     * @tc.expected: Can not drag over
     */
    DragAction(frameNode_, Offset(), 10, DRAG_VELOCITY);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll to bottom and drag over the bottom
     * @tc.expected: Can not drag over
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    DragAction(frameNode_, Offset(), -10, -DRAG_VELOCITY);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: ScrollSnapAlign001
 * @tc.desc: Test ScrollSnapAlign::START
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Make ListHeight not an integer multiple of ListItems
     * @tc.expected: Will align end when at bottom
     */
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step2. Scroll Down, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -49, velocity);
    EXPECT_TRUE(Position(-49));
    EXPECT_TRUE(TickPosition(-24.5));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step3. Scroll Down, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:1) align to start
     */
    DragAction(frameNode_, startOffset, -50, velocity);
    EXPECT_TRUE(Position(-50));
    EXPECT_TRUE(TickPosition(-75));
    EXPECT_TRUE(TickPosition(-100));

    /**
     * @tc.steps: step4. Drag end with velocity and over the edge
     * @tc.expected: Align end
     */
    DragAction(frameNode_, startOffset, -100, -500);
    EXPECT_TRUE(Position(-200));
    EXPECT_TRUE(TickPosition(-450));
    EXPECT_TRUE(TickPosition(-620));

    /**
     * @tc.steps: step5. Scroll Up, the delta is small
     * @tc.expected: The item(index:2) align to start
     */
    DragAction(frameNode_, startOffset, 1, velocity);
    EXPECT_TRUE(Position(-619));
    EXPECT_TRUE(TickPosition(-609.5));
    EXPECT_TRUE(TickPosition(-600));

    /**
     * @tc.steps: step6. Scroll Up, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, 50, velocity);
    EXPECT_TRUE(Position(-550));
    EXPECT_TRUE(TickPosition(-575));
    EXPECT_TRUE(TickPosition(-600));

    /**
     * @tc.steps: step7. Scroll Up, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:1) align to start
     */
    DragAction(frameNode_, startOffset, 51, velocity);
    EXPECT_TRUE(Position(-549));
    EXPECT_TRUE(TickPosition(-524.5));
    EXPECT_TRUE(TickPosition(-500));

    /**
     * @tc.steps: step8. Drag end with velocity and over the edge
     * @tc.expected: Align start
     */
    DragAction(frameNode_, startOffset, 100, 500);
    EXPECT_TRUE(Position(-400));
    EXPECT_TRUE(TickPosition(-150));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollSnapAlign002
 * @tc.desc: Test ScrollSnapAlign::END
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Make ListHeight not an integer multiple of ListItems
     * @tc.expected: Will align start when at top
     */
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. Scroll Down, the delta is small
     * @tc.expected: The item(index:3) align to end
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -1, velocity);
    EXPECT_TRUE(Position(-1));
    EXPECT_TRUE(TickPosition(-10.5));
    EXPECT_TRUE(TickPosition(-20));

    /**
     * @tc.steps: step3. Scroll Down, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, -49, velocity);
    EXPECT_TRUE(Position(-69));
    EXPECT_TRUE(TickPosition(-44.5));
    EXPECT_TRUE(TickPosition(-20));

    /**
     * @tc.steps: step4. Scroll Down, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:4) align to end
     */
    DragAction(frameNode_, startOffset, -50, velocity);
    EXPECT_TRUE(Position(-70));
    EXPECT_TRUE(TickPosition(-95));
    EXPECT_TRUE(TickPosition(-120));

    /**
     * @tc.steps: step5. Drag end with velocity and over the edge
     * @tc.expected: Align end
     */
    DragAction(frameNode_, startOffset, -100, -600);
    EXPECT_TRUE(Position(-220));
    EXPECT_TRUE(TickPosition(-520));
    EXPECT_TRUE(TickPosition(-620));

    /**
     * @tc.steps: step6. Scroll Up, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, 50, velocity);
    EXPECT_TRUE(Position(-570));
    EXPECT_TRUE(TickPosition(-595));
    EXPECT_TRUE(TickPosition(-620));

    /**
     * @tc.steps: step7. Scroll Up, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:3) align to end
     */
    DragAction(frameNode_, startOffset, 51, velocity);
    EXPECT_TRUE(Position(-569));
    EXPECT_TRUE(TickPosition(-544.5));
    EXPECT_TRUE(TickPosition(-520));

    /**
     * @tc.steps: step8. Drag end with velocity and over the edge
     * @tc.expected: Align start
     */
    DragAction(frameNode_, startOffset, 100, 600);
    EXPECT_TRUE(Position(-420));
    EXPECT_TRUE(TickPosition(-120));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollSnapAlign003
 * @tc.desc: Test ScrollSnapAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign003, TestSize.Level1)
{
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    /**
     * @tc.steps: step1. The middle item in the view will be align to center
     */
    const float defaultOffset = -(LIST_HEIGHT - DEVIATION_HEIGHT - ITEM_MAIN_SIZE) / 2;
    EXPECT_TRUE(Position(-defaultOffset));

    /**
     * @tc.steps: step2. Scroll Down, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -49, velocity);
    EXPECT_TRUE(Position(91));
    EXPECT_TRUE(TickPosition(115.5));
    EXPECT_TRUE(TickPosition(140));

    /**
     * @tc.steps: step3. Scroll Down, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:1) align to center
     */
    DragAction(frameNode_, startOffset, -50, velocity);
    EXPECT_TRUE(Position(90));
    EXPECT_TRUE(TickPosition(65));
    EXPECT_TRUE(TickPosition(40));

    /**
     * @tc.steps: step4. Drag end with velocity and over the edge
     * @tc.expected: Align center
     */
    DragAction(frameNode_, startOffset, -100, -1000);
    EXPECT_TRUE(Position(-60));
    EXPECT_TRUE(TickPosition(-560));
    EXPECT_TRUE(TickPosition(-760));

    /**
     * @tc.steps: step5. Scroll Up, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, 50, velocity);
    EXPECT_TRUE(Position(-710));
    EXPECT_TRUE(TickPosition(-735));
    EXPECT_TRUE(TickPosition(-760));

    /**
     * @tc.steps: step6. Scroll Up, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:4) align to start
     */
    DragAction(frameNode_, startOffset, 51, velocity);
    EXPECT_TRUE(Position(-709));
    EXPECT_TRUE(TickPosition(-684.5));
    EXPECT_TRUE(TickPosition(-660));

    /**
     * @tc.steps: step7. Drag end with velocity and over the edge
     * @tc.expected: Align center
     */
    DragAction(frameNode_, startOffset, 100, 1000);
    EXPECT_TRUE(Position(-560));
    EXPECT_TRUE(TickPosition(-60));
    EXPECT_TRUE(TickPosition(140));
}

/**
 * @tc.name: ScrollSnapAlign004
 * @tc.desc: Test ScrollSnapAlign::START without EdgeEffect.SPRING
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign004, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. Drag end with velocity and over the edge
     * @tc.expected: Align end
     */
    DragAction(frameNode_, Offset(), -100, -800);
    EXPECT_TRUE(Position(-100));
    EXPECT_TRUE(TickPosition(-350));
    EXPECT_TRUE(TickPosition(-600));

    /**
     * @tc.steps: step2. Drag end with velocity and over the edge
     * @tc.expected: Align start
     */
    DragAction(frameNode_, Offset(), 100, 800);
    EXPECT_TRUE(Position(-500));
    EXPECT_TRUE(TickPosition(-250));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollSnapAlign005
 * @tc.desc: Test ScrollSnapAlign::END without EdgeEffect.SPRING
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign005, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. Drag end with velocity and over the edge
     * @tc.expected: Align end
     */
    DragAction(frameNode_, Offset(), -100, -800);
    EXPECT_TRUE(Position(-100));
    EXPECT_TRUE(TickPosition(-350));
    EXPECT_TRUE(TickPosition(-600));

    /**
     * @tc.steps: step2. Drag end with velocity and over the edge
     * @tc.expected: Align start
     */
    DragAction(frameNode_, Offset(), 100, 800);
    EXPECT_TRUE(Position(-500));
    EXPECT_TRUE(TickPosition(-250));
    EXPECT_TRUE(TickPosition(-175));
}

/**
 * @tc.name: ScrollSnapAlign006
 * @tc.desc: Test ScrollSnapAlign::CENTER without EdgeEffect.SPRING
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign006, TestSize.Level1)
{
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    model.SetEdgeEffect(EdgeEffect::FADE, true);
    CreateListItems();
    CreateDone();

    /**
     * @tc.steps: step1. Drag end with velocity and over the edge
     * @tc.expected: Align end
     */
    DragAction(frameNode_, Offset(), -100, -800);
    EXPECT_TRUE(Position(50));
    EXPECT_TRUE(TickPosition(-350));
    EXPECT_TRUE(TickPosition(-750));

    /**
     * @tc.steps: step2. Drag end with velocity and over the edge
     * @tc.expected: Align start
     */
    DragAction(frameNode_, Offset(), 100, 800);
    EXPECT_TRUE(Position(-650));
    EXPECT_TRUE(TickPosition(-250));
    EXPECT_TRUE(TickPosition(150));
}

/**
 * @tc.name: ScrollSnapAlign007
 * @tc.desc: Test ScrollSnapAlign::START with different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign007, TestSize.Level1)
{
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateListItems(TOTAL_ITEM_NUMBER);
    SetChildrenMainSize(frameNode_, 1, { 150 });
    CreateDone();

    /**
     * @tc.steps: step1. Scroll Down, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:1) align to start
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -50, velocity);
    EXPECT_TRUE(Position(-50));
    EXPECT_TRUE(TickPosition(-75));
    EXPECT_TRUE(TickPosition(-100));

    /**
     * @tc.steps: step2. Scroll Down, the delta less than half of big item
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, -74, velocity);
    EXPECT_TRUE(Position(-174));
    EXPECT_TRUE(TickPosition(-137));
    EXPECT_TRUE(TickPosition(-100));

    /**
     * @tc.steps: step3. Scroll Down, the delta greater than half of big item
     * @tc.expected: The item(index:2) align to start
     */
    DragAction(frameNode_, startOffset, -75, velocity);
    EXPECT_TRUE(Position(-175));
    EXPECT_TRUE(TickPosition(-212.5));
    EXPECT_TRUE(TickPosition(-250));

    /**
     * @tc.steps: step4. Scroll Up, the delta less than half of big item
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, 75, velocity);
    EXPECT_TRUE(Position(-175));
    EXPECT_TRUE(TickPosition(-212.5));
    EXPECT_TRUE(TickPosition(-250));

    /**
     * @tc.steps: step5. Scroll Up, the delta greater than half of big item
     * @tc.expected: The item(index:1) align to start
     */
    DragAction(frameNode_, startOffset, 76, velocity);
    EXPECT_TRUE(Position(-174));
    EXPECT_TRUE(TickPosition(-137));
    EXPECT_TRUE(TickPosition(-100));
}

/**
 * @tc.name: ScrollSnapAlign008
 * @tc.desc: Test ScrollSnapAlign::END with different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign008, TestSize.Level1)
{
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    CreateListItems(TOTAL_ITEM_NUMBER);
    SetChildrenMainSize(frameNode_, 4, { 150 });
    CreateDone();

    /**
     * @tc.steps: step1. Scroll Down, the delta is small
     * @tc.expected: The item(index:3) align to end
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -1, velocity);
    EXPECT_TRUE(Position(-1));
    EXPECT_TRUE(TickPosition(-10.5));
    EXPECT_TRUE(TickPosition(-20));

    /**
     * @tc.steps: step2. Scroll Down, the delta less than half of big item
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, -74, velocity);
    EXPECT_TRUE(Position(-94));
    EXPECT_TRUE(TickPosition(-57));
    EXPECT_TRUE(TickPosition(-20));

    /**
     * @tc.steps: step3. Scroll Down, the delta greater than half of big item
     * @tc.expected: The item(index:4) align to end
     */
    DragAction(frameNode_, startOffset, -75, velocity);
    EXPECT_TRUE(Position(-95));
    EXPECT_TRUE(TickPosition(-132.5));
    EXPECT_TRUE(TickPosition(-170));

    /**
     * @tc.steps: step4. Scroll Up, the delta less than half of big item
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, 75, velocity);
    EXPECT_TRUE(Position(-95));
    EXPECT_TRUE(TickPosition(-132.5));
    EXPECT_TRUE(TickPosition(-170));

    /**
     * @tc.steps: step5. Scroll Up, the delta greater than half of big item
     * @tc.expected: The item(index:3) align to end
     */
    DragAction(frameNode_, startOffset, 76, velocity);
    EXPECT_TRUE(Position(-94));
    EXPECT_TRUE(TickPosition(-57));
    EXPECT_TRUE(TickPosition(-20));
}

/**
 * @tc.name: ScrollSnapAlign009
 * @tc.desc: Test ScrollSnapAlign::CENTER with different itemHeight
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign009, TestSize.Level1)
{
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::CENTER);
    CreateListItems(TOTAL_ITEM_NUMBER);
    SetChildrenMainSize(frameNode_, 1, { 150 });
    CreateDone();

    /**
     * @tc.steps: step1. The middle item in the view will be align to center
     */
    const float defaultOffset = -(LIST_HEIGHT - DEVIATION_HEIGHT - ITEM_MAIN_SIZE) / 2;
    EXPECT_TRUE(Position(-(defaultOffset)));

    /**
     * @tc.steps: step2. Scroll Down, the delta less than half of ITEM_MAIN_SIZE
     * @tc.expected: Align item not change
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -49, velocity);
    EXPECT_TRUE(Position(91));
    EXPECT_TRUE(TickPosition(115.5));
    EXPECT_TRUE(TickPosition(140));

    /**
     * @tc.steps: step3. Scroll Down, the delta greater than half of ITEM_MAIN_SIZE
     * @tc.expected: The item(index:1) align to center
     */
    DragAction(frameNode_, startOffset, -50, velocity);
    EXPECT_TRUE(Position(90));
    EXPECT_TRUE(TickPosition(52.5));
    EXPECT_TRUE(TickPosition(15));

    /**
     * @tc.steps: step5. Scroll Up, the delta less than half of big item
     * @tc.expected: Align item not change
     */
    DragAction(frameNode_, startOffset, -74, velocity);
    EXPECT_TRUE(Position(-59));
    EXPECT_TRUE(TickPosition(-22));
    EXPECT_TRUE(TickPosition(15));

    /**
     * @tc.steps: step6. Scroll Up, the delta greater than half of big item
     * @tc.expected: The item(index:0) align to center
     */
    DragAction(frameNode_, startOffset, -75, velocity);
    EXPECT_TRUE(Position(-60));
    EXPECT_TRUE(TickPosition(-85));
    EXPECT_TRUE(TickPosition(-110));
}

/**
 * @tc.name: ScrollSnapAlign010
 * @tc.desc: Test LayoutProperty about ScrollSnapAlign invalid condition
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Empty ListItems
     * @tc.expected: Can not scroll snap
     */
    ListModelNG model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), 0.f);
    DragAction(frameNode_, Offset(), -100, 0);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step2. UnScrollable List
     * @tc.expected: Can not scroll snap
     */
    ClearOldNodes();
    model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::START);
    CreateListItems(1);
    CreateDone();
    DragAction(frameNode_, Offset(), -100, 0);
    EXPECT_TRUE(Position(0));

    /**
     * @tc.steps: step3. ScrollSnapAlign::NONE
     * @tc.expected: Has no Snap effect
     */
    ClearOldNodes();
    model = CreateList();
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::NONE);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    DragAction(frameNode_, Offset(), -100, 0);
    EXPECT_TRUE(Position(-(100)));
}

/**
 * @tc.name: ScrollSnapAlign011
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign011, TestSize.Level1)
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
    CreateDone();

    /**
     * @tc.steps: step2. scroll snap
     * @tc.expected: item top snap to contentEndOffset.
     */
    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -120, velocity);
    EXPECT_TRUE(Position(-20));
    EXPECT_TRUE(TickPosition(-10));
    EXPECT_TRUE(TickPosition(0));

    DragAction(frameNode_, startOffset, -80, velocity);
    EXPECT_TRUE(Position(-80));
    EXPECT_TRUE(TickPosition(-90));
    EXPECT_TRUE(TickPosition(-100));
}

/**
 * @tc.name: ScrollSnapAlign012
 * @tc.desc: Test top content offset and bottom end offset
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign012, TestSize.Level1)
{
    /**
     * @tc.steps: step3. change scroll snap to END
     * @tc.expected: item bottom snap to contentEndOffset.
     */
    const int32_t itemNumber = 20;
    const float contentStartOffset = 100;
    const float contentEndOffset = 50;
    ListModelNG model = CreateList();
    model.SetContentStartOffset(contentStartOffset);
    model.SetContentEndOffset(contentEndOffset);
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    CreateListItems(itemNumber);
    CreateDone();

    Offset startOffset = Offset();
    float velocity = 0;
    DragAction(frameNode_, startOffset, -40, velocity);
    EXPECT_TRUE(Position(60));
    EXPECT_TRUE(TickPosition(80));
    EXPECT_TRUE(TickPosition(100));

    DragAction(frameNode_, startOffset, -110, velocity);
    EXPECT_TRUE(Position(-10));
    EXPECT_TRUE(TickPosition(-30));
    EXPECT_TRUE(TickPosition(-50));
}

/**
 * @tc.name: ScrollSnapAlign013
 * @tc.desc: Test FixPredictSnapOffsetAlignCenter
 * @tc.type: FUNC
 */
HWTEST_F(ListEventTestNg, ScrollSnapAlign013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create List with ScrollSnapAlign::END
     * @tc.expected: not contentStartOffset
     */
    ListModelNG model = CreateList();
    // Make ListHeight not an integer multiple of ListItems
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT - DEVIATION_HEIGHT));
    model.SetScrollSnapAlign(V2::ScrollSnapAlign::END);
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalOffset(), 0.0f);

    /**
     * @tc.steps: step2. change ListItem height
     * @tc.expected: The item(index:2) align to end
     */
    SetChildrenMainSize(frameNode_, 0, { 200 });
    FlushLayoutTask(frameNode_, true);
    EXPECT_EQ(pattern_->GetTotalOffset(), 20.0f);
}
} // namespace OHOS::Ace::NG
