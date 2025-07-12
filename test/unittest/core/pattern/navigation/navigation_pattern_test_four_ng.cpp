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
const std::string NAVIGATION01 = "Navigation01";
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
} // namespace

class NavigationPatternTestFourNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetIsPageLevelConfigEnabled(bool value, RefPtr<NavigationPattern> navigationPattern,
        RefPtr<NavigationGroupNode> navigationNode, RefPtr<FrameNode> pageNode);
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

void NavigationPatternTestFourNg::SetIsPageLevelConfigEnabled(bool value, RefPtr<NavigationPattern> navigationPattern,
    RefPtr<NavigationGroupNode> navigationNode, RefPtr<FrameNode> pageNode)
{
    if (value) {
        auto container = Container::Current();
        ASSERT_NE(container, nullptr);
        container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
        ASSERT_NE(navigationNode, nullptr);
        auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
        navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
        ASSERT_NE(navigationPattern, nullptr);
        navigationPattern->isFullPageNavigation_ = true;
        navigationPattern->pageNode_ = pageNode;
        auto context = PipelineContext::GetCurrentContext();
        ASSERT_NE(context, nullptr);
        auto manager = context->GetWindowManager();
        ASSERT_NE(manager, nullptr);
        auto isPcOrPadFreeMultiWindow = []() { return false; };
        manager->SetIsPcOrPadFreeMultiWindowModeCallback(std::move(isPcOrPadFreeMultiWindow));
        auto isFullScreen = []() { return true; };
        manager->SetIsFullScreenWindowCallback(std::move(isFullScreen));
        auto mockContainer = MockContainer::Current();
        mockContainer->SetIsUIExtensionWindow(false);
        EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));
    } else {
        auto container = Container::Current();
        ASSERT_NE(container, nullptr);
        container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }
}

class MockPageViewportConfig : public PageViewportConfig {
    DECLARE_ACE_TYPE(MockPageViewportConfig, PageViewportConfig)
public:
    MOCK_METHOD(RefPtr<PageViewportConfig>, Clone, (), (const, override));
};

/**
 * @tc.name: TryForceSplitIfNeeded001
 * @tc.desc: Branch: if (!navManager->IsForceSplitSupported()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, TryForceSplitIfNeeded001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->forceSplitSuccess_ = true;
    navigationPattern->forceSplitUseNavBar_ = true;

    manager->isForceSplitSupported_ = false;
    navigationPattern->TryForceSplitIfNeeded(SizeF(400.0f, 300.0f));

    EXPECT_TRUE(navigationPattern->forceSplitSuccess_);
    EXPECT_TRUE(navigationPattern->forceSplitUseNavBar_);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: TryForceSplitIfNeeded002
 * @tc.desc: Branch: if (!navManager->IsForceSplitSupported()) { => false
 *                   if (navManager->IsForceSplitEnable()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, TryForceSplitIfNeeded002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->forceSplitSuccess_ = true;
    navigationPattern->forceSplitUseNavBar_ = true;

    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = false;
    navigationPattern->TryForceSplitIfNeeded(SizeF(400.0f, 300.0f));

    EXPECT_FALSE(navigationPattern->forceSplitSuccess_);
    EXPECT_FALSE(navigationPattern->forceSplitUseNavBar_);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: TryForceSplitIfNeeded003
 * @tc.desc: Branch: if (!navManager->IsForceSplitSupported()) { => false
 *                   if (navManager->IsForceSplitEnable()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, TryForceSplitIfNeeded003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(pageNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->forceSplitSuccess_ = false;
    navigationPattern->forceSplitUseNavBar_ = true;
    auto property = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);

    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = true;

    EXPECT_CALL(*container, IsMainWindow).Times(::testing::AtLeast(1)).WillRepeatedly(Return(true));
    navigationPattern->pageNode_ = WeakPtr(pageNode);
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto backupCallback = std::move(windowManager->windowGetModeCallback_);
    windowManager->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_UNDEFINED; };
    auto key = NavigationManager::DumpMapKey(navigationNode->GetId(), navigationNode->GetDepth());
    manager->dumpMap_[key] = [](int depth) {};
    property->UpdateHideNavBar(true);

    const Dimension NAVIGAITON_WIDTH = 605.0_vp;
    navigationPattern->TryForceSplitIfNeeded(SizeF(NAVIGAITON_WIDTH.ConvertToPx(), 300.0f));
    EXPECT_TRUE(navigationPattern->forceSplitSuccess_);
    EXPECT_FALSE(navigationPattern->forceSplitUseNavBar_);

    windowManager->windowGetModeCallback_ = std::move(backupCallback);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: TryForceSplitIfNeeded004
 * @tc.desc: Branch: if (!navManager->IsForceSplitSupported()) { => false
 *                   if (navManager->IsForceSplitEnable()) { => true
 *                   ignoreOrientation => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, TryForceSplitIfNeeded004, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
    auto pageNode = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(pageNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->forceSplitSuccess_ = false;
    navigationPattern->forceSplitUseNavBar_ = true;
    auto property = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);

    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = true;
    manager->ignoreOrientation_ = true;

    EXPECT_CALL(*container, IsMainWindow).Times(::testing::AtLeast(1)).WillRepeatedly(Return(true));
    navigationPattern->pageNode_ = WeakPtr(pageNode);
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    auto backupCallback = std::move(windowManager->windowGetModeCallback_);
    windowManager->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_UNDEFINED; };
    auto key = NavigationManager::DumpMapKey(navigationNode->GetId(), navigationNode->GetDepth());
    manager->dumpMap_[key] = [](int depth) {};
    property->UpdateHideNavBar(true);

    const Dimension NAVIGAITON_WIDTH = 605.0_vp;
    navigationPattern->TryForceSplitIfNeeded(SizeF(NAVIGAITON_WIDTH.ConvertToPx(), 300.0f));
    EXPECT_TRUE(navigationPattern->forceSplitSuccess_);
    EXPECT_FALSE(navigationPattern->forceSplitUseNavBar_);

    windowManager->windowGetModeCallback_ = std::move(backupCallback);
    NavigationPatternTestFourNg::TearDownTestSuite();
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
 * @tc.name: GenerateLastStandardPage004
 * @tc.desc: Branch: if (lastPageIndex >= 0 && (navPathList[lastPageIndex].second == nullptr ||
 *              !IsStandardPage(navPathList[lastPageIndex].second))) = true
 *           Condition: IsStandardPage(navPathList[lastPageIndex].second) = false
 *           Branch: if (!pageNode && !GenerateUINodeByIndex(lastPageIndex, pageNode)) = true
 *           Condition: !pageNode = true, !GenerateUINodeByIndex(lastPageIndex, pageNode) = true
 *           Branch: if (navigationStack_->CheckIsReplacedDestination()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GenerateLastStandardPage004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation stack
     */
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);

    /**
     * @tc.steps: step2. add dialog nodes into navPathList and try push
     * @tc.expected: step2. size of navPathList size is one
     */
    auto dialogDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    dialogDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    dialogDestination->SetIndex(0);
    NavPathList navPathList;
    // only push one dialog node to test setPathStack
    navPathList.emplace_back(PAGE01, dialogDestination);
    EXPECT_EQ(navPathList.size(), 1);
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->isReplaced = false;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);
    EXPECT_EQ(navigationStack->GetAllPathName().size(), 1);

    /**
     * @tc.steps: step3. call GenerateLastStandardPage
     * @tc.expected: step3. size of navPathList size is zero
     */
    navigationPattern->GenerateLastStandardPage(navPathList);
    EXPECT_EQ(navPathList.size(), 1);
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
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = true
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
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = false
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
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
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = false
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    navigationPattern->pageNode_ = pageNode;
    auto mockContainer = MockContainer::Current();
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled004
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = false
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
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
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = false
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    navigationPattern->isFullPageNavigation_ = false;

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(true);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled006
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = false
 *           Condition: considerSize = false
 *           Branch: if (pageNode_.Upgrade() == nullptr) = false
 *           Branch: if (manager->IsPcOrPadFreeMultiWindowMode() || container->IsUIExtensionWindow()) = true
 *           Condition: manager->IsPcOrPadFreeMultiWindowMode() = false, container->IsUIExtensionWindow() = true
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    navigationPattern->pageNode_ = pageNode;
    auto mockContainer = MockContainer::Current();
    mockContainer->SetIsUIExtensionWindow(true);
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_FALSE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: IsPageLevelConfigEnabled007
 * @tc.desc: Branch: if (!Container::GreatOrEqualAPITargetVersion(VERSION_NINETEEN)) = false
 *           Branch: if (!IsEquivalentToStackMode()) = false
 *           Branch: if (considerSize && !isFullPageNavigation_) = false
 *           Condition: considerSize = false
 *           Branch: if (pageNode_.Upgrade() == nullptr) = false
 *           Branch: if (manager->IsPcOrPadFreeMultiWindowMode() || container->IsUIExtensionWindow()) = false
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
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINETEEN));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    navigationPattern->pageNode_ = pageNode;
    auto mockContainer = MockContainer::Current();
    mockContainer->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetWindowManager();
    ASSERT_NE(manager, nullptr);
    auto isPcOrPadFreeMultiWindow = []() {
        return false;
    };
    manager->SetIsPcOrPadFreeMultiWindowModeCallback(std::move(isPcOrPadFreeMultiWindow));
    auto isFullScreenWindow = []() {
        return true;
    };
    manager->SetIsFullScreenWindowCallback(std::move(isFullScreenWindow));

    bool isPageLevelConfigEnabled = navigationPattern->IsPageLevelConfigEnabled(false);
    EXPECT_TRUE(isPageLevelConfigEnabled);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageViewportConfigIfNeeded001
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageViewportConfigIfNeeded001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    SetIsPageLevelConfigEnabled(false, navigationPattern, navigationNode, nullptr);

    RefPtr<NavDestinationGroupNode> preTopDestination = nullptr;
    RefPtr<NavDestinationGroupNode> topDestination = nullptr;
    navigationPattern->UpdatePageViewportConfigIfNeeded(preTopDestination, topDestination);
    EXPECT_EQ(navigationPattern->viewportConfig_, nullptr);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageViewportConfigIfNeeded002
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (preVisibleNodes_.empty() || newVisibleNodes.empty()) = true
 *           Condition: preVisibleNodes_.empty() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageViewportConfigIfNeeded002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);

    RefPtr<NavDestinationGroupNode> preTopDestination = nullptr;
    RefPtr<NavDestinationGroupNode> topDestination = nullptr;
    navigationPattern->UpdatePageViewportConfigIfNeeded(preTopDestination, topDestination);
    EXPECT_EQ(navigationPattern->viewportConfig_, nullptr);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageViewportConfigIfNeeded003
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (preVisibleNodes_.empty() || newVisibleNodes.empty()) = true
 *           Condition: preVisibleNodes_.empty() = false, newVisibleNodes.empty() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageViewportConfigIfNeeded003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navigationPattern->preVisibleNodes_.emplace_back(nullptr);

    RefPtr<NavDestinationGroupNode> preTopDestination = nullptr;
    RefPtr<NavDestinationGroupNode> topDestination = nullptr;
    navigationPattern->UpdatePageViewportConfigIfNeeded(preTopDestination, topDestination);
    EXPECT_EQ(navigationPattern->viewportConfig_, nullptr);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageViewportConfigIfNeeded004
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (preVisibleNodes_.empty() || newVisibleNodes.empty()) = false
 *           Condition: preVisibleNodes_.empty() = false, newVisibleNodes.empty() = false
 *           Branch: if (!preFirstVisibleNode || !curFirstVisibleNode ||
 *               preFirstVisibleNode == curFirstVisibleNode) = true
 *           Condition: !preFirstVisibleNode = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageViewportConfigIfNeeded004, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navigationPattern->preVisibleNodes_.emplace_back(nullptr);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(PAGE01, navDestination01Node);

    RefPtr<NavDestinationGroupNode> preTopDestination = nullptr;
    RefPtr<NavDestinationGroupNode> topDestination = nullptr;
    navigationPattern->UpdatePageViewportConfigIfNeeded(preTopDestination, topDestination);
    EXPECT_EQ(navigationPattern->viewportConfig_, nullptr);
    EXPECT_EQ(navDestination01Node->GetPageViewportConfig(), nullptr);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageViewportConfigIfNeeded005
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (preVisibleNodes_.empty() || newVisibleNodes.empty()) = false
 *           Condition: preVisibleNodes_.empty() = false, newVisibleNodes.empty() = false
 *           Branch: if (!preFirstVisibleNode || !curFirstVisibleNode ||
 *               preFirstVisibleNode == curFirstVisibleNode) = true
 *           Condition: !preFirstVisibleNode = false, !curFirstVisibleNode = false,
 *               preFirstVisibleNode == curFirstVisibleNode = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageViewportConfigIfNeeded005, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->preVisibleNodes_.emplace_back(navDestination01Node);
    navigationStack->navPathList_.emplace_back(PAGE01, navDestination01Node);

    RefPtr<NavDestinationGroupNode> preTopDestination = nullptr;
    RefPtr<NavDestinationGroupNode> topDestination = nullptr;
    navigationPattern->UpdatePageViewportConfigIfNeeded(preTopDestination, topDestination);
    EXPECT_EQ(navigationPattern->viewportConfig_, nullptr);
    EXPECT_EQ(navDestination01Node->GetPageViewportConfig(), nullptr);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageViewportConfigIfNeeded006
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (preVisibleNodes_.empty() || newVisibleNodes.empty()) = false
 *           Condition: preVisibleNodes_.empty() = false, newVisibleNodes.empty() = false
 *           Branch: if (!preFirstVisibleNode || !curFirstVisibleNode ||
 *               preFirstVisibleNode == curFirstVisibleNode) = false
 *           Condition: !preFirstVisibleNode = false, !curFirstVisibleNode = false,
 *               preFirstVisibleNode == curFirstVisibleNode = false
 *           Branch: if (curNodeOri == preNodeOri) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageViewportConfigIfNeeded006, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->preVisibleNodes_.emplace_back(navDestination01Node);
    auto navDestination02Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(PAGE01, navDestination02Node);

    RefPtr<NavDestinationGroupNode> preTopDestination = nullptr;
    RefPtr<NavDestinationGroupNode> topDestination = nullptr;
    navigationPattern->UpdatePageViewportConfigIfNeeded(preTopDestination, topDestination);
    EXPECT_EQ(navigationPattern->viewportConfig_, nullptr);
    EXPECT_EQ(navDestination01Node->GetPageViewportConfig(), nullptr);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GetAllNodes001
 * @tc.desc: Branch: if (navBar) = false
 *           Branch:if (!node) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GetAllNodes001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto text01Node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationStack->Add(PAGE01, text01Node);

    std::vector<WeakPtr<NavDestinationNodeBase>> invisibleNodes;
    std::vector<WeakPtr<NavDestinationNodeBase>> visibleNodes;
    navigationPattern->GetAllNodes(invisibleNodes, visibleNodes);
    EXPECT_EQ(invisibleNodes.size(), 0);
    EXPECT_EQ(visibleNodes.size(), 0);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GetAllNodes002
 * @tc.desc: Branch: if (navBar) = true
 *           Branch: if (lastStandardIndex < 0) = true
 *           Branch: if (!node) = false
 *           Branch: if (idx < lastStandardIndex) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GetAllNodes002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    navigationNode->lastStandardIndex_ = -1;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);

    std::vector<WeakPtr<NavDestinationNodeBase>> invisibleNodes;
    std::vector<WeakPtr<NavDestinationNodeBase>> visibleNodes;
    navigationPattern->GetAllNodes(invisibleNodes, visibleNodes);
    EXPECT_EQ(invisibleNodes.size(), 0);
    EXPECT_EQ(visibleNodes.size(), 2);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: GetAllNodes003
 * @tc.desc: Branch: if (navBar) = true
 *           Branch: if (lastStandardIndex < 0) = false
 *           Branch: if (!node) = false
 *           Branch: if (idx < lastStandardIndex) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, GetAllNodes003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    navigationNode->lastStandardIndex_ = 1;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);

    std::vector<WeakPtr<NavDestinationNodeBase>> invisibleNodes;
    std::vector<WeakPtr<NavDestinationNodeBase>> visibleNodes;
    navigationPattern->GetAllNodes(invisibleNodes, visibleNodes);
    EXPECT_EQ(invisibleNodes.size(), 2);
    EXPECT_EQ(visibleNodes.size(), 0);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: OnAllTransitionAnimationFinish001
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, OnAllTransitionAnimationFinish001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    SetIsPageLevelConfigEnabled(false, navigationPattern, navigationNode, nullptr);

    navigationPattern->OnAllTransitionAnimationFinish();
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    EXPECT_EQ(navigationManager->beforeOrientationChangeTasks_.size(), 0);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: OnAllTransitionAnimationFinish002
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (visibleNodes.empty()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, OnAllTransitionAnimationFinish002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);

    navigationPattern->OnAllTransitionAnimationFinish();
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    EXPECT_EQ(navigationManager->beforeOrientationChangeTasks_.size(), 0);
    NavigationPatternTestFourNg::TearDownTestSuite();
}


/**
 * @tc.name: OnAllTransitionAnimationFinish003
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled()) = false
 *           Branch: if (visibleNodes.empty()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, OnAllTransitionAnimationFinish003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);

    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto refCount = tempNode->RefCount();
    navigationPattern->OnAllTransitionAnimationFinish();
    EXPECT_EQ(refCount, tempNode->RefCount());
}

/**
 * @tc.name: UpdatePageLevelConfigForSizeChanged001
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled(false)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageLevelConfigForSizeChanged001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    SetIsPageLevelConfigEnabled(false, navigationPattern, navigationNode, nullptr);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination01Node->layoutProperty_, nullptr);
    navDestination01Node->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    navigationStack->Add(PAGE01, navDestination01Node);
    navigationPattern->UpdatePageLevelConfigForSizeChanged();
    EXPECT_EQ(navDestination01Node->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageLevelConfigForSizeChanged002
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled(false)) = false
 *           Branch: if (runningTransitionCount_ > 0) = true
 *           Branch: if (isFullPageNavigation_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageLevelConfigForSizeChanged002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navigationPattern->runningTransitionCount_ = 1;
    navigationPattern->isFullPageNavigation_ = true;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination01Node->layoutProperty_, nullptr);
    navDestination01Node->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    navigationStack->Add(PAGE01, navDestination01Node);
    navigationPattern->UpdatePageLevelConfigForSizeChanged();
    EXPECT_EQ(navDestination01Node->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageLevelConfigForSizeChanged003
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled(false)) = false
 *           Branch: if (runningTransitionCount_ > 0) = true
 *           Branch: if (isFullPageNavigation_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageLevelConfigForSizeChanged003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navigationPattern->runningTransitionCount_ = 1;
    navigationPattern->isFullPageNavigation_ = false;
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination01Node->layoutProperty_, nullptr);
    navDestination01Node->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    navigationStack->Add(PAGE01, navDestination01Node);
    navigationPattern->UpdatePageLevelConfigForSizeChanged();
    EXPECT_EQ(navDestination01Node->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageLevelConfigForSizeChanged004
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled(false)) = false
 *           Branch: if (runningTransitionCount_ > 0) = false
 *           Branch: if (!lastNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageLevelConfigForSizeChanged004, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navigationPattern->UpdatePageLevelConfigForSizeChanged();
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageLevelConfigForSizeChanged005
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled(false)) = false
 *           Branch: if (runningTransitionCount_ > 0) = false
 *           Branch: if (!lastNode) = false
 *           Branch: if (statusBarConfig.has_value()) = false
 *           Branch: if (navIndicatorConfig.has_value()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageLevelConfigForSizeChanged005, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navigationPattern->UpdatePageLevelConfigForSizeChanged();
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePageLevelConfigForSizeChanged006
 * @tc.desc: Branch: if (!IsPageLevelConfigEnabled(false)) = false
 *           Branch: if (runningTransitionCount_ > 0) = false
 *           Branch: if (!lastNode) = false
 *           Branch: if (statusBarConfig.has_value()) = true
 *           Branch: if (navIndicatorConfig.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePageLevelConfigForSizeChanged006, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, pageNode);
    navBarNode->SetStatusBarConfig(std::make_pair(true, true));
    navBarNode->SetNavigationIndicatorConfig(true);
    navigationPattern->UpdatePageLevelConfigForSizeChanged();
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePrimaryContentIfNeeded001
 * @tc.desc: Branch: property->UpdateVisibility(primaryNodes_.empty() ? VisibleType::INVISIBLE : VisibleType::VISIBLE);
 *                   => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePrimaryContentIfNeeded001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto primaryContentNode = FrameNode::CreateFrameNode(
        V2::PRIMARY_CONTENT_NODE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NavigationContentPattern>());
    ASSERT_NE(primaryContentNode, nullptr);
    auto property = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    navigationPattern->primaryNodes_.clear();
    std::vector<WeakPtr<NavDestinationGroupNode>> prePrimaryNodes;
    navigationPattern->UpdatePrimaryContentIfNeeded(primaryContentNode, prePrimaryNodes);

    EXPECT_EQ(property->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePrimaryContentIfNeeded002
 * @tc.desc: Branch: property->UpdateVisibility(primaryNodes_.empty() ? VisibleType::INVISIBLE : VisibleType::VISIBLE);
 *                   => false
 *                   if (prePrimaryNodes.size() != primaryNodes_.size()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePrimaryContentIfNeeded002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto primaryContentNode = FrameNode::CreateFrameNode(
        V2::PRIMARY_CONTENT_NODE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NavigationContentPattern>());
    ASSERT_NE(primaryContentNode, nullptr);
    auto property = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::vector<WeakPtr<NavDestinationGroupNode>> prePrimaryNodes;
    navigationPattern->primaryNodes_.clear();
    navigationPattern->primaryNodes_.push_back(WeakPtr(dest1));
    navigationPattern->primaryNodes_.push_back(WeakPtr(dest2));
    primaryContentNode->needSyncRenderTree_ = false;
    navigationPattern->UpdatePrimaryContentIfNeeded(primaryContentNode, prePrimaryNodes);

    EXPECT_EQ(property->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_TRUE(primaryContentNode->needSyncRenderTree_);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePrimaryContentIfNeeded003
 * @tc.desc: Branch: property->UpdateVisibility(primaryNodes_.empty() ? VisibleType::INVISIBLE : VisibleType::VISIBLE);
 *                   => false
 *                   if (prePrimaryNodes.size() != primaryNodes_.size()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, UpdatePrimaryContentIfNeeded003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
        auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto primaryContentNode = FrameNode::CreateFrameNode(
        V2::PRIMARY_CONTENT_NODE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NavigationContentPattern>());
    ASSERT_NE(primaryContentNode, nullptr);
    auto property = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::vector<WeakPtr<NavDestinationGroupNode>> prePrimaryNodes{ WeakPtr(dest1), WeakPtr(dest2) };
    navigationPattern->primaryNodes_ = prePrimaryNodes;
    primaryContentNode->needSyncRenderTree_ = false;
    navigationPattern->UpdatePrimaryContentIfNeeded(primaryContentNode, prePrimaryNodes);

    EXPECT_EQ(property->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_FALSE(primaryContentNode->needSyncRenderTree_);
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckIfNoNeedAnimationForForceSplit001
 * @tc.desc: Branch: if (!forceSplitSuccess_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, CheckIfNoNeedAnimationForForceSplit001, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->forceSplitSuccess_ = false;
    EXPECT_FALSE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckIfNoNeedAnimationForForceSplit002
 * @tc.desc: Branch: if (!forceSplitSuccess_) { => false
 *                   if (forceSplitUseNavBar_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, CheckIfNoNeedAnimationForForceSplit002, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = true;
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckIfNoNeedAnimationForForceSplit003
 * @tc.desc: Branch: if (!forceSplitSuccess_) { => false
 *                   if (forceSplitUseNavBar_) { => false
 *                   return (preDestination && preDestination->IsShowInPrimaryPartition()) ||
 *                       (topDestination && topDestination->IsShowInPrimaryPartition()); => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFourNg, CheckIfNoNeedAnimationForForceSplit003, TestSize.Level1)
{
    NavigationPatternTestFourNg::SetUpTestSuite();
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIsShowInPrimaryPartition(true);
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(dest, nullptr));
    NavigationPatternTestFourNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG