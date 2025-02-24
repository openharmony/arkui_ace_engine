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
const InspectorFilter filter;
} // namespace

class ArcListScrollerTestNg : public ArcListTestNg {
public:
};

/**
 * @tc.name: ScrollToIndex001
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: Arc_list at top, ScrollTo index:0, text each ScrollAlign
     * @tc.expected: Each test arc_list does not scroll
     */
    CreateList();
    CreateListItems(20);
    CreateDone();
    EXPECT_FALSE(pattern_->IsAtTop());
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, -MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, -MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, -MID_OFFSET));

    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, -MID_OFFSET));
}

/**
 * @tc.name: ScrollToIndex002
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex002, TestSize.Level1)
{
    /**
     * @tc.cases: Arc_list at top, ScrollTo index:2, index:2 item is in the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(10);
    CreateDone();
    int32_t index = 2;
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::START, ITEM_HEIGHT * index - MID_OFFSET));
    EXPECT_TRUE(
        ScrollToIndex(index, false, ScrollAlign::CENTER, ITEM_HEIGHT * index - (LIST_HEIGHT - ITEM_HEIGHT) / 2));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, ITEM_HEIGHT * index - MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, ITEM_HEIGHT * index - MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, -MID_OFFSET));
}

/**
 * @tc.name: ScrollToIndex003
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex003, TestSize.Level1)
{
    /**
     * @tc.cases: Arc_list at top, ScrollTo index:9, index:9 item is below the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone();
    int32_t index = 9;
    float scrollToStartDistance = ITEM_HEIGHT * index; // 900.f
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::START, scrollToStartDistance - MID_OFFSET));
    EXPECT_TRUE(
        ScrollToIndex(index, false, ScrollAlign::CENTER, scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2));
    EXPECT_TRUE(ScrollToIndex(
        index, false, ScrollAlign::END, scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) + MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(
        index, false, ScrollAlign::AUTO, scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) + MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, -MID_OFFSET));
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex with ListItem
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: Arc_list at middle, ScrollTo index:0, index:0 item is above the view, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone();
    ScrollTo(ITEM_HEIGHT * 8);
    EXPECT_EQ(pattern_->GetTotalOffset(), 650.f);
    EXPECT_EQ(accessibilityProperty_->GetScrollOffSet(), pattern_->GetTotalOffset());
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    int32_t index = 0;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, -MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::END, -MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::AUTO, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, 800.f));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, 800.f));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, 800.f));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, 800.f));
}

/**
 * @tc.name: ScrollToIndex007
 * @tc.desc: Test ScrollToIndex invalid index(index < -1)
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex007, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollTo invalid index:-2, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    CreateList();
    CreateListItems(20);
    CreateDone();
    int32_t index = -2;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::AUTO, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, -MID_OFFSET));
}

/**
 * @tc.name: ScrollToIndex008
 * @tc.desc: Test ScrollToIndex with space
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex008, TestSize.Level1)
{
    /**
     * @tc.cases: Set space, ScrollTo index:12, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE)); // 10.f
    CreateListItems(16);
    CreateDone();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, 0);
    int32_t index = 12;
    float scrollToStartDistance = (ITEM_HEIGHT + SPACE) * index; // 1320.f
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::START, scrollToStartDistance - MID_OFFSET));
    EXPECT_TRUE(
        ScrollToIndex(index, false, ScrollAlign::CENTER, scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) / 2));
    EXPECT_TRUE(ScrollToIndex(
        index, false, ScrollAlign::END, scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) + MID_OFFSET));
    EXPECT_TRUE(ScrollToIndex(
        index, false, ScrollAlign::AUTO, scrollToStartDistance - (LIST_HEIGHT - ITEM_HEIGHT) + MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, -MID_OFFSET));
}

/**
 * @tc.name: ScrollToIndex009
 * @tc.desc: Test ScrollToIndex with ArcListItem
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex009, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollTo index:14, text each ScrollAlign
     * @tc.expected: Each test scroll the correct distance
     */
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER * 2);
    CreateDone();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, 0);
    int32_t index = 8;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::START, scrollableDistance - MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::CENTER, scrollableDistance - MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::END, scrollableDistance - MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, false, ScrollAlign::AUTO, scrollableDistance - MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::START, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::CENTER, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::END, -MID_OFFSET));
    EXPECT_FALSE(ScrollToIndex(index, true, ScrollAlign::AUTO, -MID_OFFSET));
}

/**
 * @tc.name: ScrollToIndex013
 * @tc.desc: Test ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ScrollToIndex013, TestSize.Level1)
{
    /**
     * @tc.cases: ScrollToIndex(1, true, ScrollAlign::AUTO)
     * @tc.expected: Each test scroll the correct distance
     */
    SizeT<Dimension> itemSize = SizeT<Dimension>(FILL_LENGTH, Dimension(1000.f));
    CreateList();
    CreateItemWithSize(4, itemSize);
    CreateDone();

    /**
     * @tc.cases: bottomOffset > topOffset > 0
     * @tc.expected: top Align
     */
    ScrollTo(800);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1100);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1100));

    /**
     * @tc.cases: bottomOffset > topOffset == 0
     * @tc.expected: top Align
     */
    ScrollTo(1000);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1000);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1000));

    /**
     * @tc.cases: bottomOffset > 0 > topOffset and |topOffset| < |bottomOffset|
     * @tc.expected: top Align
     */
    ScrollTo(1050);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1050);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1050));

    /**
     * @tc.cases: bottomOffset > 0 > topOffset and |topOffset| == |bottomOffset|
     * @tc.expected: bottom Align
     */
    ScrollTo(1300);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1300);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1300));

    /**
     * @tc.cases: bottomOffset == 0 > topOffset
     * @tc.expected: bottom Align
     */
    ScrollTo(1400);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1400);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1400));

    /**
     * @tc.cases: 0 > bottomOffset > topOffset
     * @tc.expected: bottom Align
     */
    ScrollTo(1700);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1700);
    EXPECT_TRUE(ScrollToIndex(1, true, ScrollAlign::AUTO, 1700));
}

/**
 * @tc.name: PositionController001
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, PositionController001, TestSize.Level1)
{
    const int32_t itemNumber = 20;
    CreateList();
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    /**
     * @tc.steps: step1. Verify initial value
     */
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Test ScrollBy
     */
    controller->ScrollBy(ITEM_WIDTH, ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(-ITEM_HEIGHT / 2.f));
    controller->ScrollBy(ITEM_WIDTH, -ITEM_HEIGHT, false);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));

    /**
     * @tc.steps: step3. Test ScrollPage
     */
    controller->ScrollPage(false, false);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET + ITEM_HEIGHT * VIEW_ITEM_NUMBER));
    controller->ScrollPage(true, false);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));

    /**
     * @tc.steps: step4. Test ScrollToEdge
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(IsEqualTotalOffset(MID_OFFSET + (itemNumber - VIEW_ITEM_NUMBER) * ITEM_HEIGHT));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));

    /**
     * @tc.steps: step5. Test JumpTo
     */
    controller->ScrollToIndex(1, false, ScrollAlign::START, std::nullopt);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET + ITEM_HEIGHT));
    controller->ScrollToIndex(0, false, ScrollAlign::NONE, std::nullopt);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));

    /**
     * @tc.steps: step6. Test IsAtEnd
     */
    EXPECT_FALSE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_TRUE(controller->IsAtEnd());
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP);
    EXPECT_FALSE(controller->IsAtEnd());

    /**
     * @tc.steps: step7. Test AnimateTo
     */
    EXPECT_FALSE(controller->AnimateTo(Dimension(1, DimensionUnit::PERCENT), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 0, nullptr, true));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, nullptr, true));
    RefPtr<Curve> curve;
    std::string icurveString = "spring(7.000000,1.000000,227.000000,33.000000)";
    curve = Framework::CreateCurve(icurveString);
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
    curve = Curves::EASE_IN;
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, false));
    EXPECT_TRUE(controller->AnimateTo(Dimension(1), 1.0, curve, true));
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY = 200.f;
constexpr float OFFSET_TIME = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS = 20 * 20;
} // namespace
/**
 * @tc.name: PositionController007
 * @tc.desc: Test PositionController function with Axis::VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, PositionController007, TestSize.Level1)
{
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

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
constexpr float SCROLL_FIXED_VELOCITY_008 = 400.f;
constexpr float OFFSET_TIME_008 = 200.f;
constexpr int32_t TIME_CHANGED_COUNTS_008 = 20 * 10;
} // namespace
/**
 * @tc.name: PositionController008
 * @tc.desc: Test PositionController function with ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, PositionController008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Arc_list Item
     */
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();

    /**
     * @tc.steps: step2. Set the direction to VERTICAL
     * expected: 1.The direction to VERTICAL
     *           2.The current Offset is 0
     */
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;
    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_008);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the right edge
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
     * @tc.steps: step9. index is -1.
     * @tc.expected: not scroll.
     */
    ScrollToIndex(ArcListLayoutAlgorithm::LAST_ITEM, true, ScrollAlign::START);
    EXPECT_EQ(pattern_->startIndex_, 0);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_009 = 600.f;
constexpr float OFFSET_TIME_009 = 100.f;
constexpr int32_t TIME_CHANGED_COUNTS_009 = 20 * 60;
} // namespace
/**
 * @tc.name: PositionController009
 * @tc.desc: Test PositionController function with ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, PositionController009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Arc_list Item
     */
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();

    /**
     * @tc.steps: step2. Set the direction to VERTICAL
     * expected: 1.The direction to VERTICAL
     *           2.The current Offset is 0
     */
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_009);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the right edge
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
    offsetTime = OFFSET_TIME_009;
    for (int i = 0; i < TIME_CHANGED_COUNTS_009; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_009;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step8. bottomOffset > topOffset == 0
     * expected: top Align
     */
    pattern_->ScrollTo(1000);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetTotalOffset(), 1000);
}

namespace {
constexpr float SCROLL_FIXED_VELOCITY_010 = 800.f;
constexpr float OFFSET_TIME_010 = 400.f;
constexpr int32_t TIME_CHANGED_COUNTS_010 = 20 * 40;
} // namespace
/**
 * @tc.name: PositionController010
 * @tc.desc: Test PositionController function with ScrollToIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, PositionController010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Arc_list Item
     */
    constexpr int32_t itemNumber = 20;
    ListModelNG model = CreateList();

    /**
     * @tc.steps: step2. Set the direction to VERTICAL
     * expected: 1.The direction to VERTICAL
     *           2.The current Offset is 0
     */
    CreateListItems(itemNumber);
    CreateDone();
    auto controller = pattern_->positionController_;

    EXPECT_EQ(controller->GetScrollDirection(), Axis::VERTICAL);

    /**
     * @tc.steps: step3. Scroll to the left edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_LEFT, SCROLL_FIXED_VELOCITY_010);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step4. Scroll to the right edge
     * expected: Return fixed verify
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_RIGHT, SCROLL_FIXED_VELOCITY_010);
    EXPECT_FALSE(pattern_->fixedVelocityMotion_);

    /**
     * @tc.steps: step5. Scroll to the bottom edge
     * expected: 1.Return fixed verify
     * expected: 2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY_010);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY_010);

    /**
     * @tc.steps: step6. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the bottom edge
     */
    int32_t offsetTime = OFFSET_TIME_010;
    for (int i = 0; i < TIME_CHANGED_COUNTS_010; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_010;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());

    /**
     * @tc.steps: step7. Scroll to the top edge
     * expected: 1.Fixed Verify is is non-zero.
     *           2.The current Velocity is equal to the set fixed velocity
     */
    controller->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, SCROLL_FIXED_VELOCITY_010);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), SCROLL_FIXED_VELOCITY_010);

    /**
     * @tc.steps: step8. 1. Set offset time
     *                   2. Set changed count
     *                   3. Flush layout
     * expected: Scroll to the top edge
     */
    offsetTime = OFFSET_TIME_010;
    for (int i = 0; i < TIME_CHANGED_COUNTS_010; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME_010;
        FlushLayoutTask(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtTop());

    /**
     * @tc.steps: step1. When has animator_ and not stop, call OnScrollCallback.
     * @tc.expected: Would stop.
     */
    pattern_->AnimateTo(1, 0, nullptr, true);
    EXPECT_FALSE(pattern_->AnimateStoped());
    double offset = 100.0;
    pattern_->OnScrollPosition(offset, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    pattern_->OnScrollCallback(100.f, SCROLL_FROM_START);
    EXPECT_TRUE(pattern_->scrollAbort_);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));
    EXPECT_TRUE(pattern_->AnimateStoped());
}

/**
 * @tc.name: Pattern002
 * @tc.desc: Test list_pattern AnimateTo function
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, Pattern002, TestSize.Level1)
{
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();

    pattern_->AnimateTo(1, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(2, 0, nullptr, true);
    EXPECT_NE(pattern_->springAnimation_, nullptr);

    pattern_->StopAnimate();
    pattern_->AnimateTo(3, 0, nullptr, false);
    EXPECT_NE(pattern_->curveAnimation_, nullptr);
}

/**
 * @tc.name: Pattern012
 * @tc.desc: Test ScrollToNode
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, Pattern012, TestSize.Level1)
{
    // test ScrollToNode
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto listItem = GetChildFrameNode(frameNode_, 5);
    bool ret = pattern_->ScrollToNode(listItem);
    EXPECT_TRUE(ret);

    // test GetTotalHeight
    ClearOldNodes();
    CreateList();
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.f);
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    EXPECT_EQ(pattern_->GetTotalHeight(), 0.f);

    // test ToJsonValue/FromJson
    ClearOldNodes();
    CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    auto json = JsonUtil::Create(true);
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetBool("multiSelectable"), false);
    EXPECT_EQ(json->GetInt("startIndex"), -1);
    EXPECT_EQ(json->GetDouble("itemStartPos"), 0);
    EXPECT_TRUE(NearEqual(json->GetDouble("friction"), ARC_LIST_FRICTION));
    pattern_->FromJson(json);
    EXPECT_TRUE(IsEqualTotalOffset(-MID_OFFSET));
}

/**
 * @tc.name: Pattern013
 * @tc.desc: Test ScrollTo and ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, Pattern013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Arc_list and Set lanes
     */
    int32_t itemNumber = 10;
    SizeT<Dimension> itemSize = SizeT<Dimension>(FILL_LENGTH, FILL_LENGTH);
    ListModelNG model = CreateList();
    model.SetScrollBar(DisplayMode::OFF);
    CreateItemWithSize(itemNumber, itemSize);
    CreateDone();

    /**
     * @tc.steps: step2. swipe forward 3 listItem
     */
    ScrollTo(3 * LIST_HEIGHT);

    /**
     * @tc.steps: step3. swipe backward 2.5 listItem
     */
    pattern_->ScrollBy(-2.5 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);
    float offsetX = LIST_WIDTH * (1 - ARC_LIST_ITER_SCALE) / 2.0;
    float offsetY = LIST_HEIGHT * (1 - ARC_LIST_ITER_SCALE);
    EXPECT_FALSE(IsEqual(pattern_->GetItemRect(0),
        Rect(offsetX, -LIST_HEIGHT / 2.0, LIST_WIDTH * ARC_LIST_ITER_SCALE, LIST_HEIGHT * ARC_LIST_ITER_SCALE)));

    /**
     * @tc.steps: step4. swipe forward 3 listItem
     */
    pattern_->ScrollBy(3 * LIST_HEIGHT);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. swipe backward 2.5 listItem
     */
    ScrollTo(LIST_HEIGHT);
    EXPECT_FALSE(IsEqual(pattern_->GetItemRect(1),
        Rect(offsetX, -offsetY, LIST_WIDTH * ARC_LIST_ITER_SCALE, LIST_HEIGHT * ARC_LIST_ITER_SCALE)));

    /**
     * @tc.cases: bottomOffset == topOffset > 0
     * @tc.expected: top Align
     */
    ScrollTo(400);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400);
    // assert false, because scale, total offset must add scale delta.
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_FALSE((GreatNotEqual(pattern_->GetTotalOffset(), 400)));

    /**
     * @tc.cases: 0 > bottomOffset == topOffset
     * @tc.expected: top Align
     */
    ScrollTo(1200);
    ScrollToIndex(1, true, ScrollAlign::AUTO);
    EXPECT_FALSE((GreatNotEqual(pattern_->GetTotalOffset(), 1200)));

    /**
     * @tc.cases: JumpIndex == StartIndex == EndIndex
     * @tc.expected: top Align
     */
    ScrollTo(800);
    ScrollToIndex(1, false, ScrollAlign::AUTO);
    EXPECT_EQ(pattern_->GetTotalOffset(), 400);
}

/**
 * @tc.name: Pattern017
 * @tc.desc: Test UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, Pattern017, TestSize.Level1)
{
    CreateList();
    CreateListItems(16);
    CreateDone();
    EXPECT_EQ(pattern_->startIndex_, -1);
    // because scale, so end index must bigger than no scale.
    EXPECT_FALSE(pattern_->endIndex_ > 3);
    EXPECT_EQ(pattern_->currentOffset_, 0);

    pattern_->ScrollPage(false, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_EQ(pattern_->endIndex_, 2);
    EXPECT_EQ(pattern_->currentOffset_, -MID_OFFSET);

    pattern_->ScrollPage(true, false);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->startIndex_, 0);
    EXPECT_FALSE(pattern_->endIndex_ > 3);
    EXPECT_EQ(pattern_->currentOffset_, -MID_OFFSET);

    pattern_->ScrollPage(false, true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->finalPosition_, -MID_OFFSET + 400);
}

/**
 * @tc.name: PostListItemPressStyleTask_scroll001
 * @tc.desc: Test arc_list layout with PostListItemPressStyleTask scroll.
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, PostListItemPressStyleTask_scroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init List.
     */
    ListModelNG model = CreateList();
    CreateListItems(TOTAL_ITEM_NUMBER);
    CreateDone();
    int cur = 0;
    for (auto& child : pattern_->itemPosition_) {
        child.second.id += cur;
        cur++;
    }

    auto listItemNode = GetChildFrameNode(frameNode_, 0);
    auto listItemNodeId = listItemNode->GetId();
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(listItemNode);
    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_PRESSED);
    RefPtr<NodePaintMethod> paint = pattern_->CreateNodePaintMethod();
    RefPtr<ListPaintMethod> listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    for (auto child : listPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_FALSE(child.second.isPressed);
        }
    }

    stateStyleMgr->PostListItemPressStyleTask(UI_STATE_NORMAL);
    paint = pattern_->CreateNodePaintMethod();
    listPaint = AceType::DynamicCast<ListPaintMethod>(paint);
    for (auto child : listPaint->itemPosition_) {
        if (child.second.id == listItemNodeId) {
            EXPECT_FALSE(child.second.isPressed);
        }
    }
}

/**
 * @tc.name: ChildrenMainSize001
 * @tc.desc: Test childrenMainSize layout
 * @tc.type: FUNC
 */
HWTEST_F(ArcListScrollerTestNg, ChildrenMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollable list, change some items height
     * @tc.expected: Items height are unequal
     */
    ListModelNG model = CreateList();
    auto childrenSize = model.GetOrCreateListChildrenMainSize();
    childrenSize->UpdateDefaultSize(ITEM_HEIGHT);
    childrenSize->ChangeData(2, 3, { 50.f, 100.f, 200.f });
    childrenSize->ChangeData(15, 3, { 50.f, 100.f, 200.f });
    CreateListItems(2); // ITEM_HEIGHT
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(100.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(10);
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(50.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(100.f)));
    CreateItemWithSize(1, SizeT<Dimension>(FILL_LENGTH, Dimension(200.f)));
    CreateListItems(3);
    CreateDone();
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(2), 50.f);
    EXPECT_EQ(pattern_->childrenSize_->GetChildSize(17), 200.f);

    /**
     * @tc.steps: step2. ScrollToIndex, index:3 is in the view
     */
    int32_t index = 3;
    EXPECT_TRUE(ScrollToIndex(index, false, ScrollAlign::CENTER, -150.f));
}
} // namespace OHOS::Ace::NG
