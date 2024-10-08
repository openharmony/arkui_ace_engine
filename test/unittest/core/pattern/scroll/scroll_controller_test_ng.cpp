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
class ScrollControllerTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test AnimateTo without animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, AnimateTo001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    positionController_->AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    positionController_->AnimateTo(Dimension(CONTENT_MAIN_SIZE), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    positionController_->AnimateTo(Dimension(0), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test AnimateTo with smooth animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, AnimateTo002, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    bool smooth = true;
    positionController_->AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE / TICK));
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    positionController_->AnimateTo(Dimension(CONTENT_MAIN_SIZE), 0, nullptr, smooth);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-(CONTENT_MAIN_SIZE + ITEM_MAIN_SIZE) / 2));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    positionController_->AnimateTo(Dimension(0), 0, nullptr, smooth);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo003
 * @tc.desc: Test AnimateTo with duration animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, AnimateTo003, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    positionController_->AnimateTo(Dimension(ITEM_MAIN_SIZE), 1000.f, Curves::EASE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE / TICK));
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    positionController_->AnimateTo(Dimension(CONTENT_MAIN_SIZE), 1000.f, Curves::EASE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-(CONTENT_MAIN_SIZE + ITEM_MAIN_SIZE) / 2));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    positionController_->AnimateTo(Dimension(0), 1000.f, Curves::EASE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo004
 * @tc.desc: Test AnimateTo with duration animation, canOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, AnimateTo004, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can over scroll
     */
    bool canOverScroll = true;
    MockAnimationManager::GetInstance().SetTicks(5);
    positionController_->AnimateTo(Dimension(1000.f), 1000.f, Curves::EASE, false, canOverScroll);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-200.f));
    EXPECT_TRUE(TickPosition(-400.f));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(-800.f)); // Tick doesn't advance new animations created within the same tick
    EXPECT_TRUE(TickPosition(-760.f));
    EXPECT_TRUE(TickPosition(-720.f));
    EXPECT_TRUE(TickPosition(-680.f));
    EXPECT_TRUE(TickPosition(-640.f));
    EXPECT_TRUE(TickPosition(-VERTICAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: AnimateTo005
 * @tc.desc: Test AnimateTo in Horizontal Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, AnimateTo005, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), HORIZONTAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. AnimateTo the position without animation
     * @tc.expected: AnimateTo the position
     */
    positionController_->AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position with animation
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    positionController_->AnimateTo(Dimension(0), 0, nullptr, true);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo006
 * @tc.desc: Test AnimateTo in Horizontal and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, AnimateTo006, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), HORIZONTAL_SCROLLABLE_DISTANCE);
    EXPECT_TRUE(Position(-HORIZONTAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step1. AnimateTo the position without animation
     * @tc.expected: AnimateTo the position
     */
    positionController_->AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(ITEM_MAIN_SIZE - HORIZONTAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step2. AnimateTo the position with animation
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    positionController_->AnimateTo(Dimension(0), 0, nullptr, true);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(ITEM_MAIN_SIZE / TICK - HORIZONTAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(-HORIZONTAL_SCROLLABLE_DISTANCE));
}

/**
 * @tc.name: ScrollBy001
 * @tc.desc: Test ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, ScrollBy001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. ScrollBy the position
     * @tc.expected: ScrollBy the position
     */
    positionController_->ScrollBy(0, ITEM_MAIN_SIZE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. ScrollBy the position over the scroll
     * @tc.expected: ScrollBy the bottom, can not over scroll
     */
    positionController_->ScrollBy(0, CONTENT_MAIN_SIZE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step3. ScrollBy the position 0
     * @tc.expected: Not scroll
     */
    positionController_->ScrollBy(0, 0, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step4. ScrollBy the position to top
     * @tc.expected: ScrollBy the top
     */
    positionController_->ScrollBy(0, -CONTENT_MAIN_SIZE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, ScrollToEdge001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. SCROLL_BOTTOM
     * @tc.expected: Scroll to bottom with animation
     */
    positionController_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, 200.f);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-VERTICAL_SCROLLABLE_DISTANCE));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    positionController_->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, 200.f);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: Fling001
 * @tc.desc: Test Fling
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, Fling001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. Fling, the flingVelocity greater than 0
     * @tc.expected: Scroll down
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    const float finalPosition = 100.f;
    const float flingVelocity = finalPosition * FRICTION * FRICTION_SCALE;
    positionController_->Fling(flingVelocity);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-finalPosition / TICK));
    EXPECT_TRUE(TickPosition(-finalPosition));

    /**
     * @tc.steps: step2. Fling, the flingVelocity less than 0
     * @tc.expected: Scroll up
     */
    positionController_->Fling(-flingVelocity);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-finalPosition / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, ScrollPage001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. ScrollPage down
     * @tc.expected: Scroll down
     */
    positionController_->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(-SCROLL_HEIGHT));

    /**
     * @tc.steps: step2. ScrollPage up
     * @tc.expected: Scroll up
     */
    positionController_->ScrollPage(true, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: ScrollPage002
 * @tc.desc: Test ScrollPage with smooth
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, ScrollPage002, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. ScrollPage down with animation
     * @tc.expected: Scroll down with animation
     */
    bool smooth = true;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    positionController_->ScrollPage(false, smooth);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-SCROLL_HEIGHT / TICK));
    EXPECT_TRUE(TickPosition(-SCROLL_HEIGHT));

    /**
     * @tc.steps: step1. ScrollPage up with animation
     * @tc.expected: Scroll up with animation
     */
    positionController_->ScrollPage(true, smooth);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(TickPosition(-SCROLL_HEIGHT / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: GetInfo001
 * @tc.desc: Test non-action GetCurrentOffset/GetScrollDirection/IsAtEnd/GetItemRect
 * @tc.type: FUNC
 */
HWTEST_F(ScrollControllerTestNg, GetInfo001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);
    EXPECT_EQ(positionController_->GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(positionController_->GetCurrentOffset(), Offset()));
    EXPECT_FALSE(positionController_->IsAtEnd());
    EXPECT_TRUE(IsEqual(positionController_->GetItemRect(0), Rect(0, 0, SCROLL_WIDTH, CONTENT_MAIN_SIZE)));

    /**
     * @tc.steps: step1. AnimateTo the position
     */
    positionController_->AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(positionController_->GetCurrentOffset(), Offset(0, ITEM_MAIN_SIZE)));
    EXPECT_FALSE(positionController_->IsAtEnd());
    EXPECT_TRUE(
        IsEqual(positionController_->GetItemRect(0), Rect(0, -ITEM_MAIN_SIZE, SCROLL_WIDTH, CONTENT_MAIN_SIZE)));

    /**
     * @tc.steps: step2. AnimateTo bottom
     */
    positionController_->AnimateTo(Dimension(CONTENT_MAIN_SIZE), 0, nullptr, false);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(IsEqual(positionController_->GetCurrentOffset(), Offset(0, VERTICAL_SCROLLABLE_DISTANCE)));
    EXPECT_TRUE(positionController_->IsAtEnd());
    EXPECT_TRUE(IsEqual(
        positionController_->GetItemRect(0), Rect(0, -VERTICAL_SCROLLABLE_DISTANCE, SCROLL_WIDTH, CONTENT_MAIN_SIZE)));
}
} // namespace OHOS::Ace::NG
