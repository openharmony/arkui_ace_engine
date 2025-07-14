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

#include "gtest/gtest.h"
#include "scroll_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {
class ScrollAccessibilityTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test AccessibilityProperty
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAccessibilityTestNg, AccessibilityProperty001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. scroll is at top
     */
    EXPECT_TRUE(pattern_->IsAtTop());
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step2. scroll to middle
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_FORWARD, AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step3. scroll to bottom
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_TRUE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    expectedActions = { AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Test PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAccessibilityTestNg, PerformActionTest001, TestSize.Level1)
{
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step1. ActActionScrollForward
     * @tc.expected: Scroll page down
     */
    MockAnimationManager::GetInstance().SetTicks(TICK);
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(TickPosition(-HEIGHT / TICK));
    EXPECT_TRUE(TickPosition(-HEIGHT));

    /**
     * @tc.steps: step2. ActActionScrollForward with SCROLL_HALF
     * @tc.expected: Scroll half page down
     */
    float currentOffset = pattern_->GetCurrentPosition();
    EXPECT_EQ(currentOffset, -HEIGHT);
    accessibilityProperty_->ActActionScrollForward(AccessibilityScrollType::SCROLL_HALF);
    const int32_t scrollHalf = 2;
    EXPECT_TRUE(TickPosition(currentOffset - HEIGHT / scrollHalf / TICK));
    EXPECT_TRUE(TickPosition(currentOffset - HEIGHT / scrollHalf));

    /**
     * @tc.steps: step3. ActActionScrollBackward
     * @tc.expected: Scroll page up
     */
    currentOffset = pattern_->GetCurrentPosition();
    EXPECT_EQ(currentOffset, -(HEIGHT + HEIGHT / scrollHalf));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(TickPosition(currentOffset + HEIGHT / TICK));
    EXPECT_TRUE(TickPosition(currentOffset + HEIGHT));

    /**
     * @tc.steps: step4. ActActionScrollBackward with SCROLL_HALF
     * @tc.expected: Scroll half page up
     */
    currentOffset = pattern_->GetCurrentPosition();
    EXPECT_EQ(currentOffset, -HEIGHT / scrollHalf);
    accessibilityProperty_->ActActionScrollBackward(AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(TickPosition(currentOffset / TICK));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: Test with unScrollable scroll, no scrollable distance
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAccessibilityTestNg, PerformActionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create unScrollable scroll
     * @tc.expected: No scrollable distance
     */
    CreateScroll();
    CreateContent(HEIGHT);
    CreateScrollDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(pattern_->GetScrollableDistance(), 0);

    /**
     * @tc.steps: step2. Test SetSpecificSupportAction
     */
    accessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(accessibilityProperty_->GetSupportAction(), expectedActions);

    /**
     * @tc.steps: step3. Test ActActionScrollBackward/ActActionScrollForward
     * @tc.expected: Not trigger ScrollPage
     */
    MockAnimationManager::GetInstance().SetTicks(1);
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollForward(AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollBackward(AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: PerformActionTest003
 * @tc.desc: Test with unScrollable scroll, Axis::NONE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollAccessibilityTestNg, PerformActionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create unScrollable scroll
     * @tc.expected: Axis::NONE
     */
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::NONE);
    CreateContent();
    CreateScrollDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    EXPECT_EQ(pattern_->GetScrollableDistance(), VERTICAL_SCROLLABLE_DISTANCE);

    /**
     * @tc.steps: step2. Test ActActionScrollBackward/ActActionScrollForward
     * @tc.expected: Not trigger ScrollPage
     */
    MockAnimationManager::GetInstance().SetTicks(1);
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollForward(AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(TickPosition(0));
    accessibilityProperty_->ActActionScrollBackward(AccessibilityScrollType::SCROLL_HALF);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: IsScrollable001
 * @tc.desc: Test ScrollAccessibilityProperty IsScrollable
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, IsScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollAccessibilityProperty> scrollAccessibilityProperty =
        AceType::MakeRefPtr<ScrollAccessibilityProperty>();

    /**
     * @tc.steps: step2. Set axis is not equal to NONE makes the IsScrollable function return true
     * and set scrollableDistance_ of scrollPattern greater than 0
     */
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetAxis(Axis::HORIZONTAL);
    scrollPattern->scrollableDistance_ = 2.0f;
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    WeakPtr<FrameNode> host = std::move(scrollNode);
    scrollAccessibilityProperty->host_ = host;

    /**
     * @tc.steps: step3. Calling the IsScrollable function
     * @tc.expected: The result of calling the function returns true
     */
    auto result = scrollAccessibilityProperty->IsScrollable();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsScrollable002
 * @tc.desc: Test ScrollAccessibilityProperty IsScrollable
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, IsScrollable002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollAccessibilityProperty> scrollAccessibilityProperty =
        AceType::MakeRefPtr<ScrollAccessibilityProperty>();

    /**
     * @tc.steps: step2. Set axis is not equal to NONE makes the IsScrollable function return true
     * and set scrollableDistance_ of scrollPattern to 0 or less
     */
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetAxis(Axis::HORIZONTAL);
    scrollPattern->scrollableDistance_ = -2.0f;
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    WeakPtr<FrameNode> host = std::move(scrollNode);
    scrollAccessibilityProperty->host_ = host;

    /**
     * @tc.steps: step3. Calling the IsScrollable function
     * @tc.expected: The result of calling the function returns false
     */
    auto result = scrollAccessibilityProperty->IsScrollable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsScrollable003
 * @tc.desc: Test ScrollAccessibilityProperty IsScrollable
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, IsScrollable003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollAccessibilityProperty> scrollAccessibilityProperty =
        AceType::MakeRefPtr<ScrollAccessibilityProperty>();

    /**
     * @tc.steps: step2. Set axis is equal to NONE makes the IsScrollable function return false
     * and set scrollableDistance_ of scrollPattern greater than 0
     */
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetAxis(Axis::NONE);
    scrollPattern->scrollableDistance_ = 2.0f;
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    WeakPtr<FrameNode> host = std::move(scrollNode);
    scrollAccessibilityProperty->host_ = host;

    /**
     * @tc.steps: step3. Calling the IsScrollable function
     * @tc.expected: The result of calling the function returns false
     */
    auto result = scrollAccessibilityProperty->IsScrollable();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test ScrollAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollAccessibilityProperty> scrollAccessibilityProperty =
        AceType::MakeRefPtr<ScrollAccessibilityProperty>();

    /**
     * @tc.steps: step2. Set axis is not equal to NONE
     * set scrollableDistance_ of scrollPattern greater than 0 makes the IsScrollable function return true
     * set currentOffset_ of scrollPattern less than 0 makes the IsAtTop function return false
     * and set currentOffset_ less than or equal to -scrollableDistance_ makes the IsAtBottom function return true
     */
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetAxis(Axis::FREE);
    scrollPattern->scrollableDistance_ = 2.0f;
    scrollPattern->currentOffset_ = -4.0f;
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    WeakPtr<FrameNode> host = std::move(scrollNode);
    scrollAccessibilityProperty->host_ = host;
    scrollAccessibilityProperty->supportActions_ = static_cast<uint64_t>(AceAction::ACTION_FOCUS);

    /**
     * @tc.steps: step3. Calling the SetSpecificSupportAction function
     * @tc.expected: The supportActions_ to be expectActions
     */
    auto expectActions = static_cast<uint64_t>(AceAction::ACTION_FOCUS) |
                         (1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD));

    scrollAccessibilityProperty->SetSpecificSupportAction();
    EXPECT_EQ(scrollAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction002
 * @tc.desc: Test ScrollAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetSpecificSupportAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollAccessibilityProperty> scrollAccessibilityProperty =
        AceType::MakeRefPtr<ScrollAccessibilityProperty>();

    /**
     * @tc.steps: step2. Set axis is not equal to NONE
     * set scrollableDistance_ of scrollPattern greater than 0 makes the IsScrollable function return true
     * set currentOffset_ of scrollPattern less than 0 makes the IsAtTop function return true
     * and set currentOffset_ less than or equal to -scrollableDistance_ makes the IsAtBottom function return false
     */
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetAxis(Axis::FREE);
    scrollPattern->scrollableDistance_ = 2.0f;
    scrollPattern->currentOffset_ = 1.0f;
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    WeakPtr<FrameNode> host = std::move(scrollNode);
    scrollAccessibilityProperty->host_ = host;
    scrollAccessibilityProperty->supportActions_ = static_cast<uint64_t>(AceAction::ACTION_CLICK);

    /**
     * @tc.steps: step3. Calling the SetSpecificSupportAction function
     * @tc.expected: The supportActions_ to be expectActions
     */
    auto expectActions = static_cast<uint64_t>(AceAction::ACTION_CLICK) |
                         (1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD));
    scrollAccessibilityProperty->SetSpecificSupportAction();
    EXPECT_EQ(scrollAccessibilityProperty->supportActions_, expectActions);
}

/**
 * @tc.name: SetSpecificSupportAction003
 * @tc.desc: Test ScrollAccessibilityProperty SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModelNGTestNg, SetSpecificSupportAction003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollAccessibilityProperty> scrollAccessibilityProperty =
        AceType::MakeRefPtr<ScrollAccessibilityProperty>();

    /**
     * @tc.steps: step2. Set axis is equal to NONE makes the IsScrollable function return false
     */
    RefPtr<ScrollPattern> scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->SetAxis(Axis::NONE);
    scrollPattern->scrollableDistance_ = 2.0f;
    scrollPattern->currentOffset_ = 1.0f;
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(scrollNode, nullptr);
    WeakPtr<FrameNode> host = std::move(scrollNode);
    scrollAccessibilityProperty->host_ = host;
    scrollAccessibilityProperty->supportActions_ |= static_cast<uint64_t>(AceAction::ACTION_NONE);

    /**
     * @tc.steps: step3. Calling the SetSpecificSupportAction function
     * @tc.expected: The supportActions_ is unchanged
     */
    scrollAccessibilityProperty->SetSpecificSupportAction();
    EXPECT_EQ(scrollAccessibilityProperty->supportActions_, static_cast<uint64_t>(AceAction::ACTION_NONE));
}
} // namespace OHOS::Ace::NG
