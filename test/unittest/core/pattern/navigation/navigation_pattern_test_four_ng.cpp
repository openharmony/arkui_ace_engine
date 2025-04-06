/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
const std::string NAVIGATION01 = "Navigation01";
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
namespace {
} // namespace

class NavigationPatternTestFourNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

RefPtr<NavigationBarTheme> NavigationPatternTestFourNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestFourNg::SetUpTestSuite()
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

void NavigationPatternTestFourNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GenerateUINodeByIndex001
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = true
 *           Condition: parentNode_.Upgrade() = true
 *           Branch: if (node) = true
 *           Branch: if (navigationNode && navDestinationPattern) = false
 *           Condition: navigationNode = true, navDestinationPattern = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationPattern->parentNode_ = WeakPtr<UINode>(columnNode);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationNode->pattern_ = nullptr;

    RefPtr<UINode> uiNode = navDestinationNode;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    navDestinationNode->pattern_ = navDestinationPattern;
    EXPECT_NE(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    EXPECT_EQ(navDestinationPattern->GetNavigationNode(), nullptr);
    EXPECT_EQ(navDestinationPattern->GetNavigationId(), "");
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex002
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = true
 *           Condition: parentNode_.Upgrade() = false, !host = true
 *           Branch: if (node) = true
 *           Branch: if (navigationNode && navDestinationPattern) = false
 *           Condition: navigationNode = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->parentNode_ = nullptr;
    navigationPattern->frameNode_ = nullptr;
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);

    RefPtr<UINode> uiNode = navDestinationNode;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    EXPECT_EQ(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    EXPECT_EQ(navDestinationPattern->GetNavigationNode(), nullptr);
    EXPECT_EQ(navDestinationPattern->GetNavigationId(), "");
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex003
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = false
 *           Condition: parentNode_.Upgrade() = false, !host = false
 *           Branch: if ((context && !context->GetInstallationFree()) || !context) = true
 *           Condition: context = true, !context->GetInstallationFree() = true
 *           Branch: if (node) = true
 *           Branch: if (navigationNode && navDestinationPattern) = false
 *           Condition: navigationNode = true, navDestinationPattern = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->parentNode_ = nullptr;
    auto  pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = false;
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navigationNode->propInspectorId_ = NAVIGATION01;

    RefPtr<UINode> uiNode = navDestinationNode;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    EXPECT_EQ(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    EXPECT_NE(navDestinationPattern->GetNavigationNode(), nullptr);
    EXPECT_EQ(navDestinationPattern->GetNavigationId(), NAVIGATION01);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex004
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = false
 *           Condition: parentNode_.Upgrade() = false, !host = false
 *           Branch: if ((context && !context->GetInstallationFree()) || !context) = false
 *           Condition: context = false, !context = true
 *           Branch: if (node) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex004, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->parentNode_ = nullptr;
    MockPipelineContext::pipeline_ = nullptr;

    RefPtr<UINode> uiNode = nullptr;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    EXPECT_EQ(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex005
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = false
 *           Condition: parentNode_.Upgrade() = false, !host = false
 *           Branch: if ((context && !context->GetInstallationFree()) || !context) = false
 *           Condition: context = true, !context->GetInstallationFree() = false, !context = false
 *           Branch: if (curTag == V2::JS_VIEW_ETS_TAG) = false
 *           Branch: if (curTag == V2::JS_VIEW_ETS_TAG) = true
 *           Branch: if (pattern && parentCustomNode) = false
 *           Condition: pattern = false
 *           Branch: if (node) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex005, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->parentNode_ = nullptr;
    auto  pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto jsViewNode = FrameNode::GetOrCreateFrameNode(V2::JS_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode->MountToParent(jsViewNode);
    navigationNode->MountToParent(columnNode);
    navigationNode->pattern_ = nullptr;

    RefPtr<UINode> uiNode = nullptr;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    navigationNode->pattern_ = navigationPattern;
    EXPECT_EQ(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex006
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = false
 *           Condition: parentNode_.Upgrade() = false, !host = false
 *           Branch: if ((context && !context->GetInstallationFree()) || !context) = false
 *           Condition: context = true, !context->GetInstallationFree() = false, !context = false
 *           Branch: if (curTag == V2::JS_VIEW_ETS_TAG) = false
 *           Branch: if (pattern && parentCustomNode) = false
 *           Condition: pattern = true, parentCustomNode = false
 *           Branch: if (node) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex006, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->parentNode_ = nullptr;
    auto  pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationNode->MountToParent(columnNode);

    RefPtr<UINode> uiNode = nullptr;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    EXPECT_EQ(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex007
 * @tc.desc: Branch: if (parentNode_.Upgrade() || !host) = false
 *           Condition: parentNode_.Upgrade() = false, !host = false
 *           Branch: if ((context && !context->GetInstallationFree()) || !context) = false
 *           Condition: context = true, !context->GetInstallationFree() = false, !context = false
 *           Branch: if (curTag == V2::JS_VIEW_ETS_TAG) = true
 *           Branch: if (pattern && parentCustomNode) = true
 *           Condition: pattern = true, parentCustomNode = true
 *           Branch: if (node) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateUINodeByIndex007, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->parentNode_ = nullptr;
    auto  pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto jsViewNode = FrameNode::GetOrCreateFrameNode(V2::JS_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationNode->MountToParent(jsViewNode);

    RefPtr<UINode> uiNode = nullptr;
    navigationPattern->GenerateUINodeByIndex(0, uiNode);
    EXPECT_NE(navigationPattern->GetParentCustomNode(), WeakPtr<UINode>(nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateLastStandardPage001
 * @tc.desc: Branch: if (!pageNode && !GenerateUINodeByIndex(lastPageIndex, pageNode)) = false
 *           Condition: !pageNode = false
 *           Branch: if (!isExistedNode && navDestinationNode && navigationStack_->GetIsForceSet(lastPageIndex)) = false
 *           Condition: !isExistedNode = false
 *           Branch: if (navDestinationNode && GetNavDestinationMode() == NavDestinationMode::STANDARD) = false
 *           Condition: navDestinationNode = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateLastStandardPage001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navPathList.emplace_back(PAGE01, textNode);
    navigationStack->Add(PAGE01, textNode);

    navigationPattern->GenerateLastStandardPage(navPathList);
    EXPECT_EQ(navPathList.size(), 1);
    EXPECT_EQ(navigationStack->Size(), 1);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateLastStandardPage002
 * @tc.desc: Branch: if (!pageNode && !GenerateUINodeByIndex(lastPageIndex, pageNode)) = false
 *           Condition: !pageNode = true, !GenerateUINodeByIndex(lastPageIndex, pageNode) = false
 *           Branch: if (!isExistedNode && navDestinationNode && GetIsForceSet(lastPageIndex)) = false
 *           Condition: !isExistedNode = true, navDestinationNode = true, GetIsForceSet(lastPageIndex) = false
 *           Branch: if (navDestinationNode && GetNavDestinationMode() == NavDestinationMode::STANDARD) = true
 *           Condition: navDestinationNode = true, GetNavDestinationMode() == NavDestinationMode::STANDARD = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateLastStandardPage002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationRoute = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(navigationRoute);
    NavPathList navPathList;
    navPathList.emplace_back(PAGE01, nullptr);
    navigationStack->Add(PAGE01, nullptr);

    navigationPattern->GenerateLastStandardPage(navPathList);
    EXPECT_EQ(navPathList.size(), 1);
    EXPECT_EQ(navigationStack->Size(), 1);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateLastStandardPage003
 * @tc.desc: Branch: if (!pageNode && !GenerateUINodeByIndex(lastPageIndex, pageNode)) = true
 *           Condition: !pageNode = true, !GenerateUINodeByIndex(lastPageIndex, pageNode) = true
 *           Branch: if (navigationStack_->CheckIsReplacedDestination()) = true
 *           Branch: if (navigationStack_->CheckIsReplacedDestination()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateLastStandardPage003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    navPathList.emplace_back(PAGE01, nullptr);
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->isReplaced = true;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);

    navigationPattern->GenerateLastStandardPage(navPathList);
    EXPECT_EQ(navPathList.size(), 0);
    EXPECT_EQ(navigationStack->Size(), 1);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: MarkAllNavDestinationDirtyIfNeeded001
 * @tc.desc: Branch: if (!skipCheck) = false
 *           Branch: if (!navDestination) = true
 *           Branch: if (!navDestination) = false
 *           Branch: if (!navDestination->IsVisible()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, MarkAllNavDestinationDirtyIfNeeded001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto text01Node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationContentNode->children_.emplace_back(text01Node);
    auto navDestination02Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination02Node->layoutProperty_, nullptr);
    navDestination02Node->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE);
    navigationContentNode->children_.emplace_back(navDestination02Node);
    navDestination02Node->needForceMeasure_ = false;

    navigationPattern->MarkAllNavDestinationDirtyIfNeeded(navigationNode, true);
    EXPECT_TRUE(navDestination02Node->needForceMeasure_);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: MarkAllNavDestinationDirtyIfNeeded002
 * @tc.desc: Branch: if (!skipCheck) = true
 *           Branch: if (!avoidInfoMgr->NeedAvoidContainerModal()) = false
 *           Branch: if (!navDestination) = false
 *           Branch: if (!navDestination->IsVisible()) = false
 *           Branch: if (titleBarNode) = false
 *           Branch: if (titleBarNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, MarkAllNavDestinationDirtyIfNeeded002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto avoidInfoMgr = pipelineContext->GetAvoidInfoManager();
    ASSERT_NE(avoidInfoMgr, nullptr);
    avoidInfoMgr->avoidInfo_.needAvoid = true;
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBar01Node = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestination01Node->titleBarNode_ = titleBar01Node;
    navigationContentNode->children_.emplace_back(navDestination01Node);
    auto navDestination02Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationContentNode->children_.emplace_back(navDestination02Node);
    ASSERT_NE(navDestination01Node->layoutProperty_, nullptr);
    navDestination01Node->layoutProperty_->CleanDirty();
    titleBar01Node->layoutProperty_->CleanDirty();
    navDestination02Node->layoutProperty_->CleanDirty();

    navigationPattern->MarkAllNavDestinationDirtyIfNeeded(navigationNode, false);
    EXPECT_FALSE(navDestination02Node->needForceMeasure_);
    EXPECT_EQ(navDestination01Node->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    EXPECT_EQ(titleBar01Node->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_EQ(navDestination02Node->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: MarkAllNavDestinationDirtyIfNeeded003
 * @tc.desc: Branch: if (!skipCheck) = true
 *           Branch: if (!avoidInfoMgr->NeedAvoidContainerModal()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, MarkAllNavDestinationDirtyIfNeeded003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination01Node->layoutProperty_, nullptr);
    navDestination01Node->layoutProperty_->UpdateVisibility(VisibleType::INVISIBLE);
    navigationContentNode->children_.emplace_back(navDestination01Node);
    navDestination01Node->needForceMeasure_ = false;

    navigationPattern->MarkAllNavDestinationDirtyIfNeeded(navigationNode, false);
    EXPECT_FALSE(navDestination01Node->needForceMeasure_);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: FireNavigationLifecycle001
 * @tc.desc: Branch: if (!navigation) = true
 *           Branch: if (!navigation) = false
 *           Branch: if (!pattern) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, FireNavigationLifecycle001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    int32_t columnId = ElementRegister::GetInstance()->MakeUniqueId();
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    int32_t column01Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto column01Node = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        column01Id, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    column01Node->MountToParent(columnNode);
    int32_t navigation02Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigation02Node = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigation02Id, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigation02Pattern = navigation02Node->GetPattern<NavigationPattern>();
    ASSERT_NE(navigation02Pattern, nullptr);
    auto navigation02Stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigation02Pattern->SetNavigationStack(navigation02Stack);
    navigation02Node->pattern_ = nullptr;
    navigation02Node->MountToParent(columnNode);
    auto pipelineContext = columnNode->GetContextRefPtr();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    std::vector<int32_t> navigationIds;
    navigationIds.emplace_back(column01Id);
    navigationIds.emplace_back(navigation02Id);
    navigationManager->navigationMaps_[columnId] = navigationIds;

    NavigationPattern::FireNavigationLifecycle(columnNode,
        NavDestinationLifecycle::ON_ACTIVE, NavDestinationActiveReason::TRANSITION);
    EXPECT_EQ(navigation02Node->GetPattern<NavigationPattern>(), nullptr);
    navigation02Node->pattern_ = navigation02Pattern;
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: FireNavigationLifecycle002
 * @tc.desc: Branch: if (!pattern) = false
 *           Branch: if (navigationStack) = true
 *           Branch: if (navigationStack) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, FireNavigationLifecycle002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    int32_t columnId = ElementRegister::GetInstance()->MakeUniqueId();
    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    int32_t navigation01Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigation01Node = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigation01Id, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigation01Pattern = navigation01Node->GetPattern<NavigationPattern>();
    ASSERT_NE(navigation01Pattern, nullptr);
    int32_t navigation02Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigation02Node = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigation02Id, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigation02Pattern = navigation02Node->GetPattern<NavigationPattern>();
    ASSERT_NE(navigation02Pattern, nullptr);
    auto navigation02Stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigation02Pattern->SetNavigationStack(navigation02Stack);
    navigation02Node->MountToParent(columnNode);
    auto pipelineContext = columnNode->GetContextRefPtr();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    std::vector<int32_t> navigationIds;
    navigationIds.emplace_back(navigation01Id);
    navigationIds.emplace_back(navigation02Id);
    navigationManager->navigationMaps_[columnId] = navigationIds;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigation02Stack->Add(PAGE01, navDestination01Node);
    auto navDestination01EventHub = navDestination01Node->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(navDestination01EventHub, nullptr);
    int32_t onWillDisAppearCalled = false;
    navDestination01EventHub->onWillDisAppear_ = [&onWillDisAppearCalled]() { onWillDisAppearCalled = true; };

    NavigationPattern::FireNavigationLifecycle(columnNode,
        NavDestinationLifecycle::ON_WILL_DISAPPEAR, NavDestinationActiveReason::TRANSITION);
    EXPECT_TRUE(onWillDisAppearCalled);
    auto navigation01Stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigation01Pattern->SetNavigationStack(navigation01Stack);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: CalcRotateAngleWithDisplayOrientation001
 * @tc.desc: Branch: if (curOri == targetOri) = true
 *           Branch: if (curOri == targetOri) = false
 *           Branch: if (!IsValidDisplayOrientation(curOri) || !IsValidDisplayOrientation(targetOri)) = true
 *           Condition: !IsValidDisplayOrientation(curOri) = true
 *           Condition: !IsValidDisplayOrientation(curOri) = false, !IsValidDisplayOrientation(targetOri) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, CalcRotateAngleWithDisplayOrientation001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);

    auto rotationAngle = navigationPattern->CalcRotateAngleWithDisplayOrientation(
        DisplayOrientation::PORTRAIT, DisplayOrientation::PORTRAIT);
    EXPECT_EQ(rotationAngle, std::nullopt);

    rotationAngle = navigationPattern->CalcRotateAngleWithDisplayOrientation(
        DisplayOrientation(-1), DisplayOrientation::PORTRAIT);
    EXPECT_EQ(rotationAngle, std::nullopt);

    rotationAngle = navigationPattern->CalcRotateAngleWithDisplayOrientation(
        DisplayOrientation::PORTRAIT, DisplayOrientation(-1));
    EXPECT_EQ(rotationAngle, std::nullopt);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: CalcRotateAngleWithDisplayOrientation002
 * @tc.desc: Branch: if (curOri == targetOri) = false
 *           Branch: if (!IsValidDisplayOrientation(curOri) || !IsValidDisplayOrientation(targetOri)) = false
 *           Branch: if (rotationAngle < 0) = false
 *           Branch: if (rotationAngle < 0) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, CalcRotateAngleWithDisplayOrientation002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);

    auto rotationAngle = navigationPattern->CalcRotateAngleWithDisplayOrientation(
        DisplayOrientation::PORTRAIT, DisplayOrientation::LANDSCAPE);
    EXPECT_EQ(rotationAngle, 270);

    rotationAngle = navigationPattern->CalcRotateAngleWithDisplayOrientation(
        DisplayOrientation::PORTRAIT_INVERTED, DisplayOrientation::LANDSCAPE_INVERTED);
    EXPECT_EQ(rotationAngle, 270);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsEquivalentToStackMode001
 * @tc.desc: Branch: if (userNavMode == NavigationMode::STACK || hideNavBar) = true
 *           Condition: userNavMode == NavigationMode::STACK = true
 *           Condition: userNavMode == NavigationMode::STACK = false, hideNavBar = true
 *           Branch: if (userNavMode == NavigationMode::STACK || hideNavBar) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsEquivalentToStackMode001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    bool isEquivalentToStackMode = navigationPattern->IsEquivalentToStackMode();
    EXPECT_TRUE(isEquivalentToStackMode);

    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::SPLIT;
    navigationLayoutProperty->propHideNavBar_ = true;
    isEquivalentToStackMode = navigationPattern->IsEquivalentToStackMode();
    EXPECT_TRUE(isEquivalentToStackMode);

    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::SPLIT;
    navigationLayoutProperty->propHideNavBar_ = false;
    navigationNode->navBarNode_ = nullptr;
    isEquivalentToStackMode = navigationPattern->IsEquivalentToStackMode();
    EXPECT_FALSE(isEquivalentToStackMode);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled001
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled002
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::SPLIT;
    navigationLayoutProperty->propHideNavBar_ = false;
    navigationNode->navBarNode_ = nullptr;

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled003
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = false
 *           Condition: considerSize = false
 *           Branch: if (pageNode_.Upgrade() == nullptr) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    navigationPattern->pageNode_ = pageNode;
    auto mockContainer = MockContainer::Current();
    EXPECT_CALL(*mockContainer, IsPcOrPadFreeMultiWindowMode()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockContainer, IsFullScreenWindow()).WillRepeatedly(Return(true));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled004
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = false
 *           Condition: considerSize = true, !isFullPageNavigation_ = false
 *           Branch: if (pageNode_.Upgrade() == nullptr) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled004, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    navigationPattern->isFullPageNavigation_ = true;
    navigationPattern->pageNode_ = nullptr;

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(true);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled005
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled005, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    navigationPattern->isFullPageNavigation_ = false;

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(true);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled006
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = false
 *           Condition: considerSize = false
 *           Branch: if (pageNode_.Upgrade() == nullptr) = false
 *           Branch: if (container->IsPcOrPadFreeMultiWindowMode() || container->IsUIExtensionWindow()) = true
 *           Condition: container->IsPcOrPadFreeMultiWindowMode() = false, container->IsUIExtensionWindow() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled006, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    navigationPattern->pageNode_ = pageNode;
    auto mockContainer = MockContainer::Current();
    EXPECT_CALL(*mockContainer, IsPcOrPadFreeMultiWindowMode()).WillRepeatedly(Return(false));
    mockContainer->SetIsUIExtensionWindow(true);
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockContainer, IsFullScreenWindow()).WillRepeatedly(Return(true));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled007
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_EIGHTEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = false
 *           Condition: considerSize = false
 *           Branch: if (pageNode_.Upgrade() == nullptr) = false
 *           Branch: if (container->IsPcOrPadFreeMultiWindowMode() || container->IsUIExtensionWindow()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, IsPageLevelConfigEnabled007, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    navigationPattern->pageNode_ = pageNode;
    auto mockContainer = MockContainer::Current();
    EXPECT_CALL(*mockContainer, IsPcOrPadFreeMultiWindowMode()).WillRepeatedly(Return(false));
    mockContainer->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));
    EXPECT_CALL(*mockContainer, IsFullScreenWindow()).WillRepeatedly(Return(true));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_TRUE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG