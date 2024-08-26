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

namespace OHOS::Ace::NG {
namespace {} // namespace

class ScrolleControllerTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: ScrollPositionController001
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();
    controller->ScrollToIndex(1, false, ScrollAlign::START, std::nullopt);

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(600.f), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step4. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    ClearOldNodes();
    CreateScroll();
    CreateContent();
    CreateDone();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step5. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    controller->ScrollBy(ITEM_MAIN_SIZE, ITEM_MAIN_SIZE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step6. ScrollTo same currentOffset_
     * @tc.expected: JumpToPosition do not SendEventToAccessibility
     */
    pattern_->ScrollTo(-pattern_->currentOffset_);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step7. Test GetTotalOffset
     */
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    ClearOldNodes();
    CreateScroll();
    CreateContent();
    CreateDone();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step9. Test ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would to be bottom
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step10. Test ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would to be top
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step11. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400.f);

    /**
     * @tc.steps: step12. Test ScrollPage
     */
    controller->ScrollPage(true, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step13. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollTo(CONTENT_MAIN_SIZE);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionController002
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();
    controller->ScrollToIndex(1, false, ScrollAlign::START, std::nullopt);

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(600.f), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step4. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateDone();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step5. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    controller->ScrollBy(ITEM_MAIN_SIZE, ITEM_MAIN_SIZE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step6. Test GetCurrentPosition
     */
    EXPECT_EQ(controller->GetCurrentOffset().GetX(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step7. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateDone();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would to be bottom
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), CONTENT_MAIN_SIZE - SCROLL_WIDTH);

    /**
     * @tc.steps: step9. Test ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would to be top
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step10. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 240.f);

    /**
     * @tc.steps: step11. Test ScrollPage
     */
    controller->ScrollPage(true, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step12. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollTo(CONTENT_MAIN_SIZE);
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionControlle003
 * @tc.desc: Test ScrollPositionController with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionControlle003, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::NONE);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(600.f), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. ScrollToEdge AnimateTo
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY = 200.f;
constexpr float OFFSET_TIME = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS = 20;
} // namespace
/**
 * @tc.name: ScrollPositionController004
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController004, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent(800.f);
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY);
    int32_t offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY);
    offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_005 = 300.f;
constexpr float OFFSET_TIME_005 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_005 = 30;
} // namespace
/**
 * @tc.name: ScrollPositionController005
 * @tc.desc: Test ScrollPositionController with ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_005);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_005);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_005);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_005);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_005;
    for (int i = 0; i < TIME_CHANGED_COUNTS_005; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_005;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_005);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_005);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_005;
    for (int i = 0; i < TIME_CHANGED_COUNTS_005; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_005;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step9. ScrollTo invalid position
     * @tc.expected: ScrollTo zero position
     */
    pattern_->ScrollTo(-1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_006 = 400.f;
constexpr float OFFSET_TIME_006 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_006 = 40;
} // namespace
/**
 * @tc.name: ScrollPositionController006
 * @tc.desc: Test ScrollPositionController with ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_006);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_006);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_006);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_006);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_006;
    for (int i = 0; i < TIME_CHANGED_COUNTS_006; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_006;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_006);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_006);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_006;
    for (int i = 0; i < TIME_CHANGED_COUNTS_006; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_006;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step9. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateDone();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_007 = 500.f;
constexpr float OFFSET_TIME_007 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_007 = 50;
} // namespace
/**
 * @tc.name: ScrollPositionController007
 * @tc.desc: Test ScrollPositionController with SCROLL_NONE
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_007);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_007);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_007);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_007);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_007;
    for (int i = 0; i < TIME_CHANGED_COUNTS_007; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_007;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_007);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_007);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_007;
    for (int i = 0; i < TIME_CHANGED_COUNTS_007; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_007;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    ClearOldNodes();
    model = CreateScroll();
    model.SetAxis(Axis::HORIZONTAL);
    CreateContent();
    CreateDone();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_008 = 600.f;
constexpr float OFFSET_TIME_008 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_008 = 60;
} // namespace
/**
 * @tc.name: ScrollPositionController008
 * @tc.desc: Test ScrollPositionController with DoJump
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_008);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_008);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_008;
    for (int i = 0; i < TIME_CHANGED_COUNTS_008; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_008;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step9. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-ITEM_MAIN_SIZE, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_009 = 700.f;
constexpr float OFFSET_TIME_009 = 200.f;
constexpr int32_t TIME_CHANGED_COUNTS_009 = 70;
} // namespace
/**
 * @tc.name: ScrollPositionController009
 * @tc.desc: Test ScrollPositionController with AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::VERTICAL);
    CreateContent();
    CreateDone();
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step3. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_009);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_009);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step9. Test AnimateTo
     * expected: animate is true
     */
    bool animate = controller->AnimateTo(Dimension(600.f), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);

    /**
     * @tc.steps: step9. Test AnimateTo
     * expected: animate is false
     */
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);
}

/**
 * @tc.name: ScrollTo001
 * @tc.desc: Test ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollTo001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. ScrollTo normal position
     */
    pattern_->ScrollTo(ITEM_MAIN_SIZE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step2. ScrollTo same position
     */
    pattern_->ScrollTo(ITEM_MAIN_SIZE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_MAIN_SIZE);

    /**
     * @tc.steps: step3. ScrollTo invalid position
     * @tc.expected: ScrollTo zero position
     */
    pattern_->ScrollTo(-1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, AnimateTo001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateDone();
    auto smooth = false;
    pattern_->isAnimationStop_ = false;
    pattern_->AnimateTo(600.f, 1.f, Curves::LINEAR, smooth);
    EXPECT_FALSE(pattern_->isAnimationStop_);
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test the canOverScroll of AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, AnimateTo002, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateDone();
    auto smooth = false;
    auto canOverScroll = false;
    pattern_->animateCanOverScroll_ = true;
    pattern_->AnimateTo(100, 1.f, Curves::LINEAR, smooth, canOverScroll);
    pattern_->StopAnimate();
    EXPECT_EQ(pattern_->animateCanOverScroll_, false);
}
} // namespace OHOS::Ace::NG
