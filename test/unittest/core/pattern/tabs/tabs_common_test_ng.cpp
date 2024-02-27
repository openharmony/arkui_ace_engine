/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabsCommonTestNg : public TabsTestNg {
public:
    AssertionResult IsEqualNextFocusNode(FocusStep step,
        const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode);
};

AssertionResult TabsCommonTestNg::IsEqualNextFocusNode(FocusStep step,
    const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode)
{
    RefPtr<FocusHub> currentFocusNode = currentNode->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    RefPtr<FocusHub> nextFocusNode = pattern_->GetNextFocusNode(step, currentFocusNode).Upgrade();
    if (nextFocusNode == expectNextNode->GetOrCreateFocusHub()) {
        return AssertionSuccess();
    }
    return AssertionFailure() << "Next focusNode is not as expected";
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test Tabs FocusStep
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, FocusStep001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, tabBarNode_, swiperNode_));
    // to do...
}

/**
 * @tc.name: TabBarAccessibilityProperty001
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.cases: Not set TabBarMode
     * @tc.expected: IsScrollable default is false
     */
    CreateWithItem([](TabsModelNG model) {});
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityProperty002
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.cases: Set TabBarMode::SCROLLABLE
     * @tc.expected: IsScrollable is true
     */
    CreateWithItem([](TabsModelNG model) { model.SetTabBarMode(TabBarMode::SCROLLABLE); });
    EXPECT_TRUE(tabBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityProperty003
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityProperty003, TestSize.Level1)
{
    /**
     * @tc.cases: Set TabBarMode::SCROLLABLE, but has no items
     * @tc.expected: IsScrollable is false
     */
    Create([](TabsModelNG model) { model.SetTabBarMode(TabBarMode::SCROLLABLE); });
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityProperty004
 * @tc.desc: Test the index properties of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityProperty004, TestSize.Level1)
{
    /**
     * @tc.cases: Create tabs with empty items
     * @tc.expected: Items number is zero, BeginIndex CurrentIndex EndIndex is -1
     */
    Create([](TabsModelNG model) {});
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCollectionItemCounts(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetBeginIndex(), -1);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), -1);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetEndIndex(), -1);
}

/**
 * @tc.name: TabBarAccessibilityProperty005
 * @tc.desc: Test the index properties of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityProperty005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with items
     * @tc.expected: Items number is TABCONTENT_NUMBER
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetAnimationDuration(0.f); // for SwipeToWithoutAnimation
    });
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCollectionItemCounts(), TABCONTENT_NUMBER); // 4
    EXPECT_EQ(tabBarAccessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetEndIndex(), TABCONTENT_NUMBER - 1); // 3

    /**
     * @tc.steps: step2. swipe to item(index:1)
     * @tc.expected: CurrentIndex is 1
     */
    swiperController_->SwipeTo(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), 1);
}
} // namespace OHOS::Ace::NG
