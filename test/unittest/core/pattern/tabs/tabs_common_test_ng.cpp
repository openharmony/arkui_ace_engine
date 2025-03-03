/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/tabs/tab_bar_item_accessibility_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
class TabsCommonTestNg : public TabsTestNg {
public:
    AssertionResult IsEqualNextFocusNode(
        FocusStep step, const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode);
};

AssertionResult TabsCommonTestNg::IsEqualNextFocusNode(
    FocusStep step, const RefPtr<FrameNode>& currentNode, const RefPtr<FrameNode>& expectNextNode)
{
    RefPtr<FocusHub> currentFocusNode = currentNode->GetOrCreateFocusHub();
    currentFocusNode->RequestFocusImmediately();
    ScopeFocusAlgorithm scopeFocusAlgorithm = pattern_->GetScopeFocusAlgorithm();
    GetNextFocusNodeFunc getNextFocusNode = scopeFocusAlgorithm.getNextFocusNode;
    WeakPtr<FocusHub> weakNextFocusNode;
    getNextFocusNode(step, currentFocusNode, weakNextFocusNode);
    RefPtr<FocusHub> nextFocusNode = weakNextFocusNode.Upgrade();
    if (expectNextNode == nullptr && nextFocusNode != nullptr) {
        return AssertionFailure() << "Next focusNode is not null";
    }
    if (expectNextNode != nullptr && nextFocusNode != expectNextNode->GetOrCreateFocusHub()) {
        return AssertionFailure() << "Next focusNode is not as expected";
    }
    return AssertionSuccess();
}

/**
 * @tc.name: FocusStep001
 * @tc.desc: Test Tabs FocusStep
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, FocusStep001, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition::START, Vertical:false
     */
    TabsModelNG model = CreateTabs(BarPosition::START);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, tabBarNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, swiperNode_, nullptr));

    /**
     * @tc.cases: from swiperNode_ to itself
     */
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, tabBarNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT_END, swiperNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT_END, swiperNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP_END, swiperNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN_END, swiperNode_, swiperNode_));
}

/**
 * @tc.name: FocusStep002
 * @tc.desc: Test Tabs FocusStep
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, FocusStep002, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition::START, Vertical:true
     */
    TabsModelNG model = CreateTabs(BarPosition::START);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, tabBarNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, swiperNode_, tabBarNode_));

    /**
     * @tc.cases: TextDirection::RTL
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, tabBarNode_, swiperNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, swiperNode_, nullptr));
}

/**
 * @tc.name: FocusStep003
 * @tc.desc: Test Tabs FocusStep
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, FocusStep003, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition::END, Vertical:false
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, tabBarNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, swiperNode_, nullptr));
}

/**
 * @tc.name: FocusStep004
 * @tc.desc: Test Tabs FocusStep
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, FocusStep004, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition::END, Vertical:true
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, tabBarNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, tabBarNode_, swiperNode_));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::TAB, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::SHIFT_TAB, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::DOWN, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, swiperNode_, tabBarNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::UP, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, swiperNode_, nullptr));

    /**
     * @tc.cases: TextDirection::RTL
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, tabBarNode_, swiperNode_));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, tabBarNode_, nullptr));

    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::RIGHT, swiperNode_, nullptr));
    EXPECT_TRUE(IsEqualNextFocusNode(FocusStep::LEFT, swiperNode_, tabBarNode_));
}

/**
 * @tc.name: TabsFocusTest001
 * @tc.desc: test onGetNextFocusNodeFunc_
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabsFocusTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::START);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Call onGetNextFocusNodeFunc_ use FocusReason::DEFAULT
     * @tc.expected: expect The function is run ok.
     */
    auto tabsFocusHub = frameNode_->GetFocusHub();
    auto nextFocusHub = tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::DEFAULT, FocusIntension::TAB);
    EXPECT_EQ(nextFocusHub, nullptr);

    /**
     * @tc.steps: step3. Call onGetNextFocusNodeFunc_ use FocusReason::FOCUS_TRAVEL and different FocusIntension
     * @tc.expected: expect The function is run ok.
     */
    auto tabBarFocusHub = tabBarNode_->GetOrCreateFocusHub();
    auto swiperFocusHub = swiperNode_->GetOrCreateFocusHub();
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::TAB), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::SELECT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::HOME), tabBarFocusHub);
    EXPECT_EQ(
        tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::SHIFT_TAB), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::END), swiperFocusHub);

    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::LEFT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::RIGHT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::DOWN), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::UP), swiperFocusHub);

    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::NONE), nullptr);

    /**
     * @tc.steps: step4. Set tabbar focusable to false, call onGetNextFocusNodeFunc_
     * @tc.expected: expect The function is run ok.
     */
    tabBarFocusHub->SetFocusable(false, false);
    nextFocusHub = tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::TAB);
    EXPECT_EQ(nextFocusHub, nullptr);
}

/**
 * @tc.name: TabsFocusTest002
 * @tc.desc: test onGetNextFocusNodeFunc_
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabsFocusTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. Call onGetNextFocusNodeFunc_ use different FocusIntension
     * @tc.expected: expect The function is run ok.
     */
    auto tabsFocusHub = frameNode_->GetFocusHub();
    auto tabBarFocusHub = tabBarNode_->GetOrCreateFocusHub();
    auto swiperFocusHub = swiperNode_->GetOrCreateFocusHub();
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::TAB), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::SELECT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::HOME), swiperFocusHub);
    EXPECT_EQ(
        tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::SHIFT_TAB), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::END), tabBarFocusHub);

    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::LEFT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::RIGHT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::DOWN), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::UP), tabBarFocusHub);
}

/**
 * @tc.name: TabsFocusTest003
 * @tc.desc: test onGetNextFocusNodeFunc_
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabsFocusTest003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::START);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Call onGetNextFocusNodeFunc_ use different FocusIntension
     * @tc.expected: expect The function is run ok.
     */
    auto tabsFocusHub = frameNode_->GetFocusHub();
    auto tabBarFocusHub = tabBarNode_->GetOrCreateFocusHub();
    auto swiperFocusHub = swiperNode_->GetOrCreateFocusHub();
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::LEFT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::RIGHT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::DOWN), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::UP), tabBarFocusHub);

    /**
     * @tc.steps: step3. Set direction to RTL, call onGetNextFocusNodeFunc_ use different FocusIntension
     * @tc.expected: expect The function is run ok.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::LEFT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::RIGHT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::DOWN), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::UP), tabBarFocusHub);
}

/**
 * @tc.name: TabsFocusTest004
 * @tc.desc: test onGetNextFocusNodeFunc_
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabsFocusTest004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Call onGetNextFocusNodeFunc_ use different FocusIntension
     * @tc.expected: expect The function is run ok.
     */
    auto tabsFocusHub = frameNode_->GetFocusHub();
    auto tabBarFocusHub = tabBarNode_->GetOrCreateFocusHub();
    auto swiperFocusHub = swiperNode_->GetOrCreateFocusHub();
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::LEFT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::RIGHT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::DOWN), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::UP), swiperFocusHub);

    /**
     * @tc.steps: step3. Set direction to RTL, call onGetNextFocusNodeFunc_ use different FocusIntension
     * @tc.expected: expect The function is run ok.
     */
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::LEFT), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::RIGHT), tabBarFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::DOWN), swiperFocusHub);
    EXPECT_EQ(tabsFocusHub->onGetNextFocusNodeFunc_(FocusReason::FOCUS_TRAVEL, FocusIntension::UP), swiperFocusHub);
}

/**
 * @tc.name: TabBarAccessibilityProperty001
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.cases: Not set TabBarMode
     * @tc.expected: IsScrollable default is false
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityProperty002
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.cases: Set TabBarMode::SCROLLABLE
     * @tc.expected: IsScrollable is true
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemWidth = 200.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_TRUE(tabBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityProperty003
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty003, TestSize.Level1)
{
    /**
     * @tc.cases: Set TabBarMode::SCROLLABLE, but has no items
     * @tc.expected: IsScrollable is false
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabsDone(model);
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityProperty004
 * @tc.desc: Test the index properties of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty004, TestSize.Level1)
{
    /**
     * @tc.cases: Create tabs with empty items
     * @tc.expected: Items number is zero, BeginIndex CurrentIndex EndIndex is -1
     */
    TabsModelNG model = CreateTabs();
    CreateTabsDone(model);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCollectionItemCounts(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetBeginIndex(), -1); // default
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), -1);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetEndIndex(), -1);
}

/**
 * @tc.name: TabBarAccessibilityProperty005
 * @tc.desc: Test the index properties of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with items
     * @tc.expected: Items number is TABCONTENT_NUMBER
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCollectionItemCounts(), TABCONTENT_NUMBER); // 4
    EXPECT_EQ(tabBarAccessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), 0);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetEndIndex(), TABCONTENT_NUMBER - 1); // 3

    /**
     * @tc.steps: step2. swipe to item(index:1)
     * @tc.expected: CurrentIndex is 1
     */
    ChangeIndex(1);
    EXPECT_EQ(tabBarAccessibilityProperty_->GetCurrentIndex(), 1);
}

/**
 * @tc.name: TabBarAccessibilityProperty006
 * @tc.desc: Test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TabBarMode::SCROLLABLE and middle
     * @tc.expected: tabBar is at middle
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemWidth = 200.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    tabBarPattern_->visibleItemPosition_.clear();
    EXPECT_FALSE(tabBarPattern_->IsAtTop());
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction
     * @tc.expected: Check actions value
     */
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_TRUE(tabBarPattern_->CanScroll());
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: TabBarAccessibilityProperty007
 * @tc.desc: test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TabBarMode::SCROLLABLE and top
     * @tc.expected: tabBar is at top
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->visibleItemPosition_[3] = { 1.f, TABS_WIDTH + 1.f };
    EXPECT_TRUE(tabBarPattern_->IsAtTop());
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction
     * @tc.expected: Check actions value
     */
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_FORWARD };
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: TabBarAccessibilityProperty008
 * @tc.desc: Test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TabBarMode::SCROLLABLE and bottom
     * @tc.expected: tabBar is at bottom
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->visibleItemPosition_[0] = { -1.f, TABS_WIDTH - 1.f };
    EXPECT_FALSE(tabBarPattern_->IsAtTop());
    EXPECT_TRUE(tabBarPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction
     * @tc.expected: Check actions value
     */
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = { AceAction::ACTION_SCROLL_BACKWARD };
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: TabBarAccessibilityProperty009
 * @tc.desc: test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set TabBarMode::SCROLLABLE and top and bottom
     * @tc.expected: tabBar is at top and bottom
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(tabBarPattern_->IsAtTop());
    EXPECT_TRUE(tabBarPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction
     * @tc.expected: Check actions value
     */
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: TabBarAccessibilityProperty010
 * @tc.desc: Test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarAccessibilityProperty010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default is TabBarMode::FIXED
     * @tc.expected: tabBar is FIXED
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FALSE(tabBarAccessibilityProperty_->IsScrollable());

    /**
     * @tc.steps: step2. Call SetSpecificSupportAction
     * @tc.expected: Check actions value
     */
    tabBarAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> expectedActions = {};
    EXPECT_EQ(tabBarAccessibilityProperty_->GetSupportAction(), expectedActions);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TabBar AccessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, PerformActionTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. When tabBar TabBarMode is FIXED and child is null, call the callback function in
     *                   tabBarAccessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step2. When tabBar TabBarMode is SCROLLABLE and child is null, call the callback function in
     *                   tabBarAccessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step3. When tabBar TabBarMode is SCROLLABLE and child is not null, call the callback function in
     *                   tabBarAccessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step4. When tabBar TabBarMode is FIXED and child is not null, call the callback function in
     *                   tabBarAccessibilityProperty_.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty_->ActActionScrollBackward());
}

/**
 * @tc.name: TabBarItemAccessibilityProperty001
 * @tc.desc: Test TabBarItemAccessibilityProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarItemAccessibilityProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with items.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Call ToJsonValue function.
     * @tc.expected: label is default tab bar name.
     */
    auto tabBarItem = AceType::DynamicCast<FrameNode>(GetChildFrameNode(tabBarNode_, 0));
    auto accessibilityProperty = tabBarItem->GetAccessibilityProperty<TabBarItemAccessibilityProperty>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    accessibilityProperty->ToJsonValue(json, filter);
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultTabBarName = tabTheme->GetDefaultTabBarName();
    EXPECT_EQ(json->GetString("label"), defaultTabBarName);
}

/**
 * @tc.name: TabBarItemAccessibilityProperty002
 * @tc.desc: Test TabBarItemAccessibilityProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TabsCommonTestNg, TabBarItemAccessibilityProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabs with builder.
     */
    TabsModelNG model = CreateTabs();
    const std::string textTest = "text_test";
    const std::u16string textU16Test = u"text_test";
    TabContentModelNG tabContentModel = CreateTabContent();
    auto tabBarItemFunc = [textU16Test]() {
        TextModelNG model;
        model.Create(textU16Test);
    };
    tabContentModel.SetTabBar(textTest, "", std::nullopt, std::move(tabBarItemFunc), true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Call ToJsonValue function.
     * @tc.expected: check label value.
     */
    auto tabBarItem = AceType::DynamicCast<FrameNode>(GetChildFrameNode(tabBarNode_, 0));
    auto accessibilityProperty = tabBarItem->GetAccessibilityProperty<TabBarItemAccessibilityProperty>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    accessibilityProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("label"), textTest);
}
} // namespace OHOS::Ace::NG
