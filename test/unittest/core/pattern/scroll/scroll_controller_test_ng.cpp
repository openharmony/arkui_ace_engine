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
    CreateWithContent();
    auto controller = pattern_->GetScrollPositionController();
    controller->JumpTo(1, false, ScrollAlign::START, 0);

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(ITEM_HEIGHT * TOTAL_LINE_NUMBER), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT));

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-ITEM_HEIGHT, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT));

    /**
     * @tc.steps: step4. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    CreateWithContent();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step5. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT));

    /**
     * @tc.steps: step6. ScrollTo same currentOffset_
     * @tc.expected: JumpToPosition do not SendEventToAccessibility
     */
    pattern_->ScrollTo(-pattern_->currentOffset_);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_HEIGHT));

    /**
     * @tc.steps: step7. Test GetCurrentPosition
     */
    EXPECT_EQ(controller->GetCurrentOffset().GetY(), ITEM_HEIGHT);

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    CreateWithContent();
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step9. Test ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would to be bottom
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentPosition(SCROLL_HEIGHT - ITEM_HEIGHT * TOTAL_LINE_NUMBER));

    /**
     * @tc.steps: step10. Test ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would to be top
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step11. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualCurrentPosition(SCROLL_HEIGHT - ITEM_HEIGHT * TOTAL_LINE_NUMBER));

    /**
     * @tc.steps: step12. Test ScrollPage
     */
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step13. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    UpdateCurrentOffset(-(ITEM_HEIGHT * TOTAL_LINE_NUMBER - SCROLL_HEIGHT));
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionController002
 * @tc.desc: Test ScrollPositionController with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionController002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    auto controller = pattern_->GetScrollPositionController();
    controller->JumpTo(1, false, ScrollAlign::START, 0);

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(ITEM_HEIGHT * TOTAL_LINE_NUMBER), -1.f, Curves::LINEAR, false);
    EXPECT_TRUE(animate);
    animate = controller->AnimateTo(Dimension(1.0, DimensionUnit::PERCENT), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. jump to a position
     * @tc.expected: CurrentOffset would be to the position
     */
    pattern_->DoJump(-ITEM_WIDTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_WIDTH));

    /**
     * @tc.steps: step3. jump to the same position
     * @tc.expected: CurrentOffset would not be change
     */
    pattern_->DoJump(-ITEM_WIDTH, SCROLL_FROM_UPDATE);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_WIDTH));

    /**
     * @tc.steps: step4. ScrollBy 0
     * @tc.expected: CurrentOffset would not change
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    controller = pattern_->GetScrollPositionController();
    controller->ScrollBy(0, 0, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step5. ScrollBy a distance
     * @tc.expected: Scroll by the distance
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualCurrentPosition(-ITEM_WIDTH));

    /**
     * @tc.steps: step6. Test GetCurrentPosition
     */
    EXPECT_EQ(controller->GetCurrentOffset().GetX(), ITEM_WIDTH);

    /**
     * @tc.steps: step7. Test ScrollEdgeType::SCROLL_NONE
     * @tc.expected: CurrentOffset would not be change
     */
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::HORIZONTAL); });
    controller = pattern_->GetScrollPositionController();
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step8. Test ScrollEdgeType::SCROLL_BOTTOM
     * @tc.expected: CurrentOffset would to be bottom
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentPosition(SCROLL_WIDTH - ITEM_WIDTH * TOTAL_LINE_NUMBER));

    /**
     * @tc.steps: step9. Test ScrollEdgeType::SCROLL_TOP
     * @tc.expected: CurrentOffset would to be top
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step10. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualCurrentPosition(SCROLL_WIDTH - ITEM_WIDTH * TOTAL_LINE_NUMBER));

    /**
     * @tc.steps: step11. Test ScrollPage
     */
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step12. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    UpdateCurrentOffset(-(ITEM_WIDTH * TOTAL_LINE_NUMBER - SCROLL_WIDTH));
    EXPECT_TRUE(controller->IsAtEnd());
}

/**
 * @tc.name: ScrollPositionControlle003
 * @tc.desc: Test ScrollPositionController with Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollPositionControlle003, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::NONE); });
    auto controller = pattern_->GetScrollPositionController();

    /**
     * @tc.steps: step1. Test AnimateTo
     */
    bool animate = controller->AnimateTo(Dimension(ITEM_HEIGHT * TOTAL_LINE_NUMBER), 1.f, Curves::LINEAR, false);
    EXPECT_FALSE(animate);

    /**
     * @tc.steps: step2. ScrollToEdge AnimateTo
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualCurrentPosition(0));
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
    CreateWithContent([](ScrollModelNG model) { model.SetAxis(Axis::VERTICAL); });
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

/**
 * @tc.name: ScrollTo001
 * @tc.desc: Test ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, ScrollTo001, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) {});

    /**
     * @tc.steps: step1. ScrollTo normal position
     */
    pattern_->ScrollTo(ITEM_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT);

    /**
     * @tc.steps: step2. ScrollTo same position
     */
    pattern_->ScrollTo(ITEM_HEIGHT);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), ITEM_HEIGHT);

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
    CreateWithContent([](ScrollModelNG model) {});
    auto smooth = false;
    pattern_->isAnimationStop_ = false;
    pattern_->AnimateTo(ITEM_HEIGHT * TOTAL_LINE_NUMBER, 1.f, Curves::LINEAR, smooth);
    EXPECT_FALSE(pattern_->isAnimationStop_);
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test the canOverScroll of AnimateTo
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleControllerTestNg, AnimateTo002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) {});
    auto smooth = false;
    auto canOverScroll = false;
    pattern_->animateCanOverScroll_ = true;
    pattern_->AnimateTo(100, 1.f, Curves::LINEAR, smooth, canOverScroll);
    pattern_->StopAnimate();
    EXPECT_EQ(pattern_->animateCanOverScroll_, false);
}
} // namespace OHOS::Ace::NG
