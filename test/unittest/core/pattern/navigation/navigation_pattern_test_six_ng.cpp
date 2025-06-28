/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "core/common/force_split/force_split_utils.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string PAGE01 = "Page01";
} // namespace

class NavigationPatternTestSixNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetIsPageLevelConfigEnabled(bool value, RefPtr<NavigationPattern> navigationPattern,
        RefPtr<NavigationGroupNode> navigationNode, RefPtr<FrameNode> pageNode);
};

RefPtr<NavigationBarTheme> NavigationPatternTestSixNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestSixNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return navigationBarTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestSixNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: SetNavigationWidthToolBarManager001
 * @tc.desc: Branch: if (!NearEqual(navBarWidth, navBarInfo.width)) = false
 *           Branch: if (!NearEqual(navDestWidth, navDestInfo.width)) = false
 *           Branch: if (!NearEqual(dividerWidth, dividerInfo.width)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, SetNavigationWidthToolBarManager001, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolbarManager = pipelineContext->GetToolbarManager();
    toolbarManager->navBarInfo_ = { false, 300.0f };
    toolbarManager->navDestInfo_ = { false, 300.0f };
    toolbarManager->navBarDividerInfo_ = { false, 300.0f };
    navigationPattern->toolbarManager_ = toolbarManager;

    navigationPattern->SetNavigationWidthToolBarManager(300.0f, 300.0f, 300.0f);
    EXPECT_FALSE(toolbarManager->navBarInfo_.isShow);
    EXPECT_FALSE(toolbarManager->navDestInfo_.isShow);
    EXPECT_FALSE(toolbarManager->navBarDividerInfo_.isShow);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: SetNavigationWidthToolBarManager002
 * @tc.desc: Branch: if (!NearEqual(navBarWidth, navBarInfo.width)) = true
 *           Branch: if (!NearEqual(navDestWidth, navDestInfo.width)) = true
 *           Branch: if (!NearEqual(dividerWidth, dividerInfo.width)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, SetNavigationWidthToolBarManager002, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolbarManager = pipelineContext->GetToolbarManager();
    toolbarManager->navBarInfo_ = { false, 300.0f };
    toolbarManager->navDestInfo_ = { false, 300.0f };
    toolbarManager->navBarDividerInfo_ = { false, 300.0f };
    navigationPattern->toolbarManager_ = toolbarManager;

    navigationPattern->SetNavigationWidthToolBarManager(100.0f, 100.0f, 100.0f);
    EXPECT_EQ(toolbarManager->navBarInfo_.width, 100.0f);
    EXPECT_EQ(toolbarManager->navDestInfo_.width, 100.0f);
    EXPECT_EQ(toolbarManager->navBarDividerInfo_.width, 100.0f);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: CalcNavDestinationNodeIndex001
 * @tc.desc: Branch: if (node == homeNode) = false
 *           Branch: if (node->GetNavDestinationMode() == STANDARD) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, CalcNavDestinationNodeIndex001, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);
    navDestination01Node->mode_ = NavDestinationMode::DIALOG;

    std::vector<RefPtr<NavDestinationGroupNode>> destNodes;
    int32_t homeNodeIndex = 1;
    int32_t lastStandardIndex = 1;
    navigationPattern->CalcNavDestinationNodeIndex(destNodes, homeNodeIndex, lastStandardIndex);
    EXPECT_EQ(homeNodeIndex, -1);
    EXPECT_EQ(lastStandardIndex, -1);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: CalcNavDestinationNodeIndex002
 * @tc.desc: Branch: if (node == homeNode) = true
 *           Branch: if (node->GetNavDestinationMode() == STANDARD) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, CalcNavDestinationNodeIndex002, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);
    navigationPattern->homeNode_ = WeakPtr(navDestination01Node);

    std::vector<RefPtr<NavDestinationGroupNode>> destNodes;
    int32_t homeNodeIndex = 1;
    int32_t lastStandardIndex = 1;
    navigationPattern->CalcNavDestinationNodeIndex(destNodes, homeNodeIndex, lastStandardIndex);
    EXPECT_EQ(homeNodeIndex, 0);
    EXPECT_EQ(lastStandardIndex, 0);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: AdjustNodeForDestForceSplit001
 * @tc.desc: Branch: if (destNodes.empty() || homeNodeIndex > lastStandardIndex) = true
 *           Condition: destNodes.empty() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustNodeForDestForceSplit001, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPrimaryContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->primaryContentNode_ = navigationPrimaryContentNode;

    navigationPattern->AdjustNodeForDestForceSplit(false);
    EXPECT_TRUE(navigationPattern->primaryNodes_.empty());
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: AdjustNodeForDestForceSplit002
 * @tc.desc: Branch: if (destNodes.empty() || homeNodeIndex > lastStandardIndex) = false
 *           Condition: destNodes.empty() = false, homeNodeIndex > lastStandardIndex = false
 *           Branch: if (needFireLifecycle) = false
 *           Branch: if (primaryNodes_.empty()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustNodeForDestForceSplit002, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPrimaryContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->primaryContentNode_ = navigationPrimaryContentNode;
    auto phNode = ForceSplitUtils::CreatePlaceHolderNode();
    ASSERT_NE(phNode, nullptr);
    navigationNode->forceSplitPlaceHolderNode_ = phNode;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);
    navigationPattern->homeNode_ = WeakPtr(navDestination01Node);

    navigationPattern->AdjustNodeForDestForceSplit(false);
    ASSERT_EQ(navigationPattern->primaryNodes_.size(), 1);
    EXPECT_EQ(navigationPattern->primaryNodes_[0], navDestination01Node);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: AdjustNodeForDestForceSplit003
 * @tc.desc: Branch: if (destNodes.empty() || homeNodeIndex > lastStandardIndex) = false
 *           Condition: destNodes.empty() = false, homeNodeIndex > lastStandardIndex = false
 *           Branch: if (needFireLifecycle) = true
 *           Branch: if (primaryNodes_.empty()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustNodeForDestForceSplit003, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPrimaryContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->primaryContentNode_ = navigationPrimaryContentNode;
    auto phNode = ForceSplitUtils::CreatePlaceHolderNode();
    ASSERT_NE(phNode, nullptr);
    navigationNode->forceSplitPlaceHolderNode_ = phNode;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);
    navDestination01Node->mode_ = NavDestinationMode::DIALOG;

    navigationPattern->AdjustNodeForDestForceSplit(true);
    ASSERT_EQ(navigationPattern->primaryNodes_.size(), 1);
    EXPECT_EQ(navigationPattern->primaryNodes_[0], navDestination01Node);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: AdjustPrimaryAndPlaceHolderPosition001
 * @tc.desc: Branch: if (homeNodeIndex < 0 || homeNodeIndex == lastStandardIndex) = true
 *           Condition: homeNodeIndex < 0 = true
 *           Branch: if (index >= lastStandardIndex) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustPrimaryAndPlaceHolderPosition001, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPrimaryContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->primaryContentNode_ = navigationPrimaryContentNode;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);

    std::vector<RefPtr<NavDestinationGroupNode>> destNodes;
    destNodes.push_back(navDestination01Node);
    int32_t homeNodeIndex = -1;
    int32_t lastStandardIndex = 0;
    navigationPattern->AdjustPrimaryAndPlaceHolderPosition(navigationPrimaryContentNode, navigationContentNode,
        destNodes, homeNodeIndex, lastStandardIndex);
    ASSERT_EQ(navigationPattern->primaryNodes_.size(), 1);
    EXPECT_EQ(navigationPattern->primaryNodes_[0], navDestination01Node);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: AdjustPrimaryAndPlaceHolderPosition002
 * @tc.desc: Branch: if (homeNodeIndex < 0 || homeNodeIndex == lastStandardIndex) = true
 *           Condition: homeNodeIndex < 0 = false, homeNodeIndex == lastStandardIndex = true
 *           Branch: if (index >= lastStandardIndex) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustPrimaryAndPlaceHolderPosition002, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPrimaryContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->primaryContentNode_ = navigationPrimaryContentNode;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);

    std::vector<RefPtr<NavDestinationGroupNode>> destNodes;
    destNodes.push_back(navDestination01Node);
    int32_t homeNodeIndex = 1;
    int32_t lastStandardIndex = 1;
    navigationPattern->AdjustPrimaryAndPlaceHolderPosition(navigationPrimaryContentNode, navigationContentNode,
        destNodes, homeNodeIndex, lastStandardIndex);
    EXPECT_EQ(navigationPattern->primaryNodes_.size(), 0);
    NavigationPatternTestSixNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG