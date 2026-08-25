/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "tabs_test_ng.h"

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"

namespace OHOS::Ace::NG {

class TabsModelLazyChildNodesTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: InitTabBarChildNodes001
 * @tc.desc: Test InitTabBarChildNodes creates internal child nodes
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, InitTabBarChildNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs without TabContent.
     */
    TabsModelNG model = CreateTabs();
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Before InitTabBarChildNodes, internal child nodes should not exist.
     */
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());
    EXPECT_FALSE(tabsNode->HasSelectedMaskNode());
    EXPECT_FALSE(tabsNode->HasUnselectedMaskNode());
    EXPECT_FALSE(tabsNode->HasIndicatorNode());

    /**
     * @tc.steps: step3. Call InitTabBarChildNodes.
     */
    TabsModelNG::InitTabBarChildNodes(AceType::Claim(tabsNode));

    /**
     * @tc.steps: step4. After InitTabBarChildNodes, internal child nodes should exist.
     */
    EXPECT_TRUE(tabsNode->HasTabBarChildNodes());
    EXPECT_TRUE(tabsNode->HasSelectedMaskNode());
    EXPECT_TRUE(tabsNode->HasUnselectedMaskNode());
    EXPECT_TRUE(tabsNode->HasIndicatorNode());

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    // TabBar should have 3 internal child nodes: selectedMask, unselectedMask, indicator
    EXPECT_GE(static_cast<int32_t>(tabBarNode->GetChildren().size()), 3);

    CreateDone();
}

/**
 * @tc.name: InitTabBarChildNodes002
 * @tc.desc: Test InitTabBarChildNodes is idempotent - calling twice does not duplicate nodes
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, InitTabBarChildNodes002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and call InitTabBarChildNodes once.
     */
    TabsModelNG model = CreateTabs();
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);

    TabsModelNG::InitTabBarChildNodes(AceType::Claim(tabsNode));
    EXPECT_TRUE(tabsNode->HasTabBarChildNodes());

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto childCountAfterFirst = static_cast<int32_t>(tabBarNode->GetChildren().size());

    /**
     * @tc.steps: step2. Call InitTabBarChildNodes again.
     * @tc.expected: No additional child nodes are created since HasXxxNode returns true.
     */
    TabsModelNG::InitTabBarChildNodes(AceType::Claim(tabsNode));
    auto childCountAfterSecond = static_cast<int32_t>(tabBarNode->GetChildren().size());
    EXPECT_EQ(childCountAfterFirst, childCountAfterSecond);

    CreateDone();
}

/**
 * @tc.name: InitTabBarChildNodes003
 * @tc.desc: Test InitTabBarChildNodes with null tabBarNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, InitTabBarChildNodes003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a TabsNode without TabBar mounted.
     */
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        pattern, true);
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Call InitTabBarChildNodes when tabBarNode is null.
     * @tc.expected: Should not crash, HasTabBarChildNodes remains false.
     */
    TabsModelNG::InitTabBarChildNodes(tabsNode);
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());
}

/**
 * @tc.name: HasTabBarChildNodes001
 * @tc.desc: Test HasTabBarChildNodes flag defaults to false
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, HasTabBarChildNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new TabsNode.
     */
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        pattern, true);
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Check HasTabBarChildNodes defaults to false.
     */
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());
}

/**
 * @tc.name: HasTabBarChildNodes002
 * @tc.desc: Test SetTabBarChildNodesInitialized sets the flag correctly
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, HasTabBarChildNodes002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new TabsNode.
     */
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        pattern, true);
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());

    /**
     * @tc.steps: step2. Set the flag to true.
     */
    tabsNode->SetTabBarChildNodesInitialized(true);
    EXPECT_TRUE(tabsNode->HasTabBarChildNodes());

    /**
     * @tc.steps: step3. Set the flag back to false.
     */
    tabsNode->SetTabBarChildNodesInitialized(false);
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());
}

/**
 * @tc.name: InitTabsNodeNoInternalChildNodes001
 * @tc.desc: Test InitTabsNode does not create internal child nodes of TabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, InitTabsNodeNoInternalChildNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs via CreateTabs (which calls InitTabsNode).
     */
    TabsModelNG model = CreateTabs();
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);

    /**
     * @tc.steps: step2. Verify TabBar exists but internal child nodes do not.
     */
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());
    EXPECT_FALSE(tabsNode->HasSelectedMaskNode());
    EXPECT_FALSE(tabsNode->HasUnselectedMaskNode());
    EXPECT_FALSE(tabsNode->HasIndicatorNode());
    // TabBar should have 0 children since no TabContent has been added
    EXPECT_EQ(static_cast<int32_t>(tabBarNode->GetChildren().size()), 0);

    CreateDone();
}

/**
 * @tc.name: LazyInitWithTabContent001
 * @tc.desc: Test that TabBar internal child nodes are created when first TabContent is added
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, LazyInitWithTabContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs without TabContent.
     */
    TabsModelNG model = CreateTabs();
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());

    /**
     * @tc.steps: step2. Add TabContent which triggers InitTabBarChildNodes in AddTabBarItem.
     */
    CreateTabContents(1);
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. After adding TabContent, internal child nodes should exist.
     */
    EXPECT_TRUE(tabsNode->HasTabBarChildNodes());
    EXPECT_TRUE(tabsNode->HasSelectedMaskNode());
    EXPECT_TRUE(tabsNode->HasUnselectedMaskNode());
    EXPECT_TRUE(tabsNode->HasIndicatorNode());

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    // TabBar should have: selectedMask + unselectedMask + indicator + 1 TabBarItem = 4
    EXPECT_EQ(static_cast<int32_t>(tabBarNode->GetChildren().size()), 4);
}

/**
 * @tc.name: LazyInitWithMultipleTabContent001
 * @tc.desc: Test that InitTabBarChildNodes is only called once with multiple TabContents
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, LazyInitWithMultipleTabContent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and add multiple TabContents.
     */
    TabsModelNG model = CreateTabs();
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_FALSE(tabsNode->HasTabBarChildNodes());

    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. After adding TabContents, internal child nodes should exist.
     */
    EXPECT_TRUE(tabsNode->HasTabBarChildNodes());

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    // TabBar should have: selectedMask + unselectedMask + indicator + TABCONTENT_NUMBER TabBarItems
    EXPECT_EQ(static_cast<int32_t>(tabBarNode->GetChildren().size()),
        3 + TABCONTENT_NUMBER);
}

/**
 * @tc.name: CreateFrameNodeNoInternalChildNodes001
 * @tc.desc: Test CreateFrameNode creates TabBar without internal child nodes
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelLazyChildNodesTestNg, CreateFrameNodeNoInternalChildNodes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call CreateFrameNode.
     */
    auto tabsNode = TabsModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(tabsNode, nullptr);
    auto tabsNodeCast = AceType::DynamicCast<TabsNode>(tabsNode);
    ASSERT_NE(tabsNodeCast, nullptr);

    /**
     * @tc.steps: step2. Verify TabBar exists but internal child nodes do not.
     */
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNodeCast->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_FALSE(tabsNodeCast->HasTabBarChildNodes());
    EXPECT_EQ(static_cast<int32_t>(tabBarNode->GetChildren().size()), 0);
}

} // namespace OHOS::Ace::NG
