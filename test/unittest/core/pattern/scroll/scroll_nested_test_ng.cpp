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

#include "scroll_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float TOP_CONTENT_MAIN_SIZE = 200.f;
} // namespace

class ScrollNestedTestNg : public ScrollTestNg {
public:
    ScrollModelNG CreateNestScroll();
    void ScrollAllToBottom();

    RefPtr<FrameNode> nestNode_;
    RefPtr<ScrollPattern> nestPattern_;
};

ScrollModelNG ScrollNestedTestNg::CreateNestScroll()
{
    ScrollModelNG model;
    model.Create();
    auto proxy = model.CreateScrollBarProxy();
    model.SetScrollBarProxy(proxy);
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    nestNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    nestPattern_ = nestNode_->GetPattern<ScrollPattern>();
    return model;
}

void ScrollNestedTestNg::ScrollAllToBottom()
{
    nestPattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, Layout001, TestSize.Level1)
{
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    CreateNestScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), TOP_CONTENT_MAIN_SIZE);
    EXPECT_EQ(nestPattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);
    auto contentNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_TRUE(IsEqual(contentNode->GetGeometryNode()->GetFrameRect(),
        RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT + TOP_CONTENT_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(
        nestNode_->GetGeometryNode()->GetFrameRect(), RectF(0, TOP_CONTENT_MAIN_SIZE, SCROLL_WIDTH, SCROLL_HEIGHT)));
}

/**
 * @tc.name: NestTest001
 * @tc.desc: Test drag in nest scroll, the dragUpdate delta will affect parent by NestedScrollOptions
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest001, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateScroll();
    {
        CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
        {
            CreateContent(TOP_CONTENT_MAIN_SIZE);
            ViewStackProcessor::GetInstance()->Pop();
            ScrollModelNG nestModel = CreateNestScroll();
            nestModel.SetNestedScroll(nestedOpt);
            {
                CreateContent();
            }
        }
    }
    CreateScrollDone();
    EXPECT_EQ(nestNode_->GetGeometryNode()->GetFrameRect().GetY(), TOP_CONTENT_MAIN_SIZE);

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling parent because forward is PARENT_FIRST
     */
    float dragDelta = -10.f;
    float velocityDelta = -TOP_CONTENT_MAIN_SIZE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = -100.f;
    velocityDelta = -VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling nest because backward is SELF_FIRST
     */
    dragDelta = 100.f;
    velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling parent because nest is at top
     */
    dragDelta = 10.f;
    velocityDelta = TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: NestTest002
 * @tc.desc: Test drag in nest scroll in horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest002, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_WIDTH);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    nestModel.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(nestNode_->GetGeometryNode()->GetFrameRect().GetX(), TOP_CONTENT_MAIN_SIZE);

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling parent because forward is PARENT_FIRST
     */
    float dragDelta = -10.f;
    float velocityDelta = -TOP_CONTENT_MAIN_SIZE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = -100.f;
    velocityDelta = -HORIZONTAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling nest because backward is SELF_FIRST
     */
    dragDelta = 100.f;
    velocityDelta = HORIZONTAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta - HORIZONTAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - HORIZONTAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling parent because nest is at top
     */
    dragDelta = 10.f;
    velocityDelta = TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: NestTest003
 * @tc.desc: Test drag in nest scroll in horizontal and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, DISABLED_NestTest003, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_WIDTH);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    nestModel.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(nestNode_->GetGeometryNode()->GetFrameRect().GetX(), 0);

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling parent because forward is PARENT_FIRST
     */
    float dragDelta = 10.f;
    float velocityDelta = TOP_CONTENT_MAIN_SIZE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, -HORIZONTAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(Position(dragDelta - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = 100.f;
    velocityDelta = HORIZONTAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling nest because backward is SELF_FIRST
     */
    dragDelta = -100.f;
    velocityDelta = -HORIZONTAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta - HORIZONTAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - HORIZONTAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling parent because nest is at top
     */
    dragDelta = -10.f;
    velocityDelta = -TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: NestTest004
 * @tc.desc: Test drag in nest scroll, the dragEnd velocity will affect parent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest004, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag up the nest fast
     * @tc.expected: The nest velocity will reach to the parent, scrolling parent than scrolling nest
     */
    float dragDelta = -100.f;
    float velocityDelta = -400;
    MockAnimationManager::GetInstance().SetTicks(4);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(pattern_->IsAtBottom());
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(TickPosition(nestNode_, -100));
    EXPECT_TRUE(TickPosition(nestNode_, -200));
    EXPECT_TRUE(TickPosition(nestNode_, -300));

    /**
     * @tc.steps: step2. Scroll parent and nest to bottom, drag down the nest fast
     * @tc.expected: The nest velocity will reach to the parent, scrolling nest than scrolling parent
     */
    ScrollAllToBottom();
    dragDelta = 500.f;
    velocityDelta = 200;
    MockAnimationManager::GetInstance().SetTicks(4);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, -100));
    EXPECT_TRUE(TickPosition(nestNode_, -50));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());
    EXPECT_TRUE(Position(-200));
    EXPECT_TRUE(TickPosition(-150));
    EXPECT_TRUE(TickPosition(-100));
}

/**
 * @tc.name: NestTest005
 * @tc.desc: Set parent edge effect spring, priority scrolling parent when parent over the edge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest005, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    ScrollModelNG model = CreateScroll();
    // set parent spring
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag down nest to over top, than drag back
     * @tc.expected: Parent spring take effect, and scrolling parent first when drag back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragStart(nestNode_, Offset());
    DragUpdate(10);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(10));
    // Drag back
    DragUpdate(-5);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_LT(GetChildY(frameNode_, 0), 10);
    EXPECT_GT(GetChildY(frameNode_, 0), 5);
    float currentOffset = GetChildY(frameNode_, 0);
    DragEnd(0);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickPosition(currentOffset / TICK));
    EXPECT_TRUE(TickPosition(0));

    /**
     * @tc.steps: step2. Scroll to bottom, drag up nest to over bottom, than drag back
     * @tc.expected: Parent spring take effect, and scrolling parent first when drag back
     */
    ScrollAllToBottom();
    DragStart(nestNode_, Offset());
    DragUpdate(-10);
    EXPECT_TRUE(Position(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(Position(-10 - TOP_CONTENT_MAIN_SIZE));
    // Drag back
    DragUpdate(5);
    EXPECT_TRUE(Position(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_LT(GetChildY(frameNode_, 0), -5 - TOP_CONTENT_MAIN_SIZE);
    EXPECT_GT(GetChildY(frameNode_, 0), -10 - TOP_CONTENT_MAIN_SIZE);
    currentOffset = GetChildY(frameNode_, 0);
    DragEnd(0);
    EXPECT_TRUE(Position(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(Position(currentOffset));
    EXPECT_TRUE(TickPosition(-TOP_CONTENT_MAIN_SIZE + (currentOffset + TOP_CONTENT_MAIN_SIZE) / TICK));
    EXPECT_TRUE(TickPosition(-TOP_CONTENT_MAIN_SIZE));
}

/**
 * @tc.name: NestTest006
 * @tc.desc: Set nest edge effect spring, priority scrolling nest when nest over the edge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest006, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    // set nest spring
    nestModel.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag down nest to over top, than drag back
     * @tc.expected: Nest spring take effect, and scrolling nest first when drag back
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    GestureEvent gesture;
    DragStart(nestNode_, Offset());
    DragUpdate(10);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, 10));
    // Drag back
    DragUpdate(-5);
    EXPECT_TRUE(Position(0));
    EXPECT_LT(GetChildY(nestNode_, 0), 10);
    EXPECT_GT(GetChildY(nestNode_, 0), 5);
    float currentOffset = GetChildY(nestNode_, 0);
    DragEnd(0);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, currentOffset));
    EXPECT_TRUE(TickPosition(nestNode_, currentOffset / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, 0));

    /**
     * @tc.steps: step2. Scroll to bottom, drag up nest to over bottom, than drag back
     * @tc.expected: Nest spring take effect, and scrolling nest first when drag back
     */
    ScrollAllToBottom();
    DragStart(nestNode_, Offset());
    DragUpdate(-10);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, -10 - VERTICAL_SCROLLABLE_DISTANCE));
    // Drag back
    DragUpdate(5);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_LT(GetChildY(nestNode_, 0), -5 - VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_GT(GetChildY(nestNode_, 0), -10 - VERTICAL_SCROLLABLE_DISTANCE);
    currentOffset = GetChildY(nestNode_, 0);
    DragEnd(0);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, currentOffset));
    EXPECT_TRUE(
        TickPosition(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE + (currentOffset + VERTICAL_SCROLLABLE_DISTANCE) / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: NestTest007
 * @tc.desc: Test both PARENT_FIRST, always scrolling parent first
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest007, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::PARENT_FIRST,
    };
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling parent because forward is PARENT_FIRST
     */
    float dragDelta = -10.f;
    float velocityDelta = -TOP_CONTENT_MAIN_SIZE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = -100.f;
    velocityDelta = -VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling parent because backward is PARENT_FIRST
     */
    dragDelta = 10.f;
    velocityDelta = TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling nest because parent is at top
     */
    dragDelta = 100.f;
    velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, dragDelta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());
}

/**
 * @tc.name: NestTest008
 * @tc.desc: Test both SELF_FIRST, always scrolling nest first
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest008, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling nest because forward is SELF_FIRST
     */
    float dragDelta = -100.f;
    float velocityDelta = -VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = -10.f;
    velocityDelta = -TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling nest because backward is SELF_FIRST
     */
    dragDelta = 100.f;
    velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling parent because nest is at top
     */
    dragDelta = 10.f;
    velocityDelta = TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: NestTest009
 * @tc.desc: Test both PARALLEL, scrolling nest, also scrolling parent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest009, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARALLEL,
        .backward = NestedScrollMode::PARALLEL,
    };
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling parent and nest because forward is PARALLEL
     */
    float dragDelta = -10.f;
    float velocityDelta = -TOP_CONTENT_MAIN_SIZE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta / TICK));
    FlushLayoutTask(nestNode_);
    EXPECT_TRUE(Position(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(dragDelta + velocityDelta));
    FlushLayoutTask(nestNode_);
    EXPECT_TRUE(Position(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(pattern_->IsAtBottom());
    EXPECT_FALSE(nestPattern_->IsAtTop());
    EXPECT_FALSE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = -100.f;
    velocityDelta = -VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, -TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, -TOP_CONTENT_MAIN_SIZE + dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling parent and nest because backward is PARALLEL
     */
    dragDelta = 10.f;
    velocityDelta = TOP_CONTENT_MAIN_SIZE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, dragDelta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(Position(dragDelta - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(dragDelta + velocityDelta / TICK - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta - VERTICAL_SCROLLABLE_DISTANCE));
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(dragDelta + velocityDelta - TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(nestPattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling nest because parent is at top
     */
    dragDelta = 100.f;
    velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, dragDelta + TOP_CONTENT_MAIN_SIZE - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(
        nestNode_, dragDelta + TOP_CONTENT_MAIN_SIZE + velocityDelta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());
}

/**
 * @tc.name: NestTest010
 * @tc.desc: Test default value, both SELF_ONLY, only scrolling nest
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest010, TestSize.Level1)
{
    CreateScroll();
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    CreateNestScroll();
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling nest because forward is SELF_ONLY
     */
    float dragDelta = -100.f;
    float velocityDelta = -100000;
    MockAnimationManager::GetInstance().SetTicks(1);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step2. Drag down the nest
     * @tc.expected: Scrolling nest because backward is SELF_ONLY
     */
    dragDelta = 100.f;
    velocityDelta = 100000;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(0));
    EXPECT_TRUE(Position(nestNode_, dragDelta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(pattern_->IsAtTop());
}

/**
 * @tc.name: NestTest011
 * @tc.desc: Test onScrollDragEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest011, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    int32_t stopCount = 0;
    model.SetOnScrollStop([&stopCount]() { ++stopCount; });
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    int32_t nestStopCount = 0;
    nestModel.SetOnScrollStop([&nestStopCount]() { ++nestStopCount; });
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. Drag down child scroll
     * @tc.expected: trigger parent spring animation and onScrollStop only once
     */
    float dragDelta = 100.f;
    float velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(pattern_->IsScrollableSpringMotionRunning());
    EXPECT_TRUE(Position(dragDelta));
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(TickPosition(dragDelta / TICK));
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_EQ(nestStopCount, 1);
    EXPECT_EQ(stopCount, 1);
}

/**
 * @tc.name: NestTest012
 * @tc.desc: Test onScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest012, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    int32_t stopCount = 0;
    model.SetOnScrollStop([&stopCount]() { ++stopCount; });
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    int32_t nestStopCount = 0;
    nestModel.SetOnScrollStop([&nestStopCount]() { ++nestStopCount; });
    pattern_->currentOffset_ = -TOP_CONTENT_MAIN_SIZE;
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. trigger child fling animation to parent spring animation
     * @tc.expected: trigger child onScrollStop
     */
    GestureEvent info;
    auto dragDelta = -100.f;
    info.SetMainDelta(dragDelta);
    auto velocity = -VERTICAL_SCROLLABLE_DISTANCE * FRICTION * -FRICTION_SCALE;
    info.SetMainVelocity(velocity);
    auto nestScrollable = nestPattern_->GetScrollableEvent()->GetScrollable();
    nestScrollable->HandleDragStart(info);
    nestScrollable->HandleDragEnd(info);
    FlushLayoutTask(nestNode_);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    nestScrollable->scrollPause_ = true;
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(nestNode_);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(nestStopCount, 1);
    EXPECT_EQ(stopCount, 0);
    EXPECT_TRUE(Position(-TOP_CONTENT_MAIN_SIZE + dragDelta));
    EXPECT_TRUE(Position(nestNode_, -VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(pattern_->IsScrollableSpringMotionRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(nestNode_);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(nestStopCount, 1);
    EXPECT_EQ(stopCount, 1);
}

/**
 * @tc.name: NestTest013
 * @tc.desc: Test Fling in nested scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollNestedTestNg, NestTest013, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::PARENT_FIRST,
    };
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    int32_t startCount = 0;
    model.SetOnScrollStop([&startCount]() { ++startCount; });
    int32_t stopCount = 0;
    model.SetOnScrollStart([&stopCount]() { ++stopCount; });
    CreateContent(TOP_CONTENT_MAIN_SIZE + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_MAIN_SIZE);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    int32_t nestStartCount = 0;
    nestModel.SetOnScrollStart([&nestStartCount]() { ++nestStartCount; });
    int32_t nestStopCount = 0;
    nestModel.SetOnScrollStop([&nestStopCount]() { ++nestStopCount; });
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. trigger child fling animation to parent spring animation
     * @tc.expected: trigger child onScrollStop
     */
    nestPattern_->Fling(-300.f);
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(nestNode_);
    FlushLayoutTask(frameNode_);
    EXPECT_LT(GetChildY(frameNode_, 0), -110.f);
    EXPECT_TRUE(Position(nestNode_, 0.f));
    EXPECT_EQ(startCount, 1);
    EXPECT_EQ(stopCount, 1);
    EXPECT_EQ(nestStartCount, 1);
    EXPECT_EQ(nestStopCount, 1);
}
} // namespace OHOS::Ace::NG
