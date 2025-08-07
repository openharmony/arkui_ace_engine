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
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"

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


void NavigationPatternTestSixNg::SetIsPageLevelConfigEnabled(bool value, RefPtr<NavigationPattern> navigationPattern,
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
 * @tc.name: AdjustPrimaryAndProxyNodePosition001
 * @tc.desc: Branch: if (!homeIndex.has_value() || homeIndex.value() == index) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustPrimaryAndProxyNodePosition001, TestSize.Level1)
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
    std::optional<int32_t> homeIndex;
    navigationPattern->primaryNodes_.clear();
    navigationPattern->AdjustPrimaryAndProxyNodePosition(navigationPrimaryContentNode, navigationContentNode,
        destNodes, homeIndex);
    ASSERT_EQ(navigationPattern->primaryNodes_.size(), 1);
    EXPECT_EQ(navigationPattern->primaryNodes_[0], navDestination01Node);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: AdjustPrimaryAndProxyNodePosition002
 * @tc.desc: Branch: if (!homeIndex.has_value() || homeIndex.value() == index) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, AdjustPrimaryAndProxyNodePosition002, TestSize.Level1)
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
    std::optional<int32_t> homeIndex;
    homeIndex = -1;
    navigationPattern->AdjustPrimaryAndProxyNodePosition(navigationPrimaryContentNode, navigationContentNode,
        destNodes, homeIndex);
    EXPECT_EQ(navigationPattern->primaryNodes_.size(), 0);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: CreateHomeDestination001
 * @tc.desc: test for NavigationPattern::CreateHomeDestination branch coverage
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, CreateHomeDestination001, TestSize.Level1)
{
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = nullptr;
    RefPtr<UINode> customNode;
    RefPtr<NavDestinationGroupNode> homeDest;
    EXPECT_FALSE(navigationPattern->CreateHomeDestination(customNode, homeDest));

    auto mockStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->navigationStack_ = mockStack;
    EXPECT_CALL(*mockStack, CreateHomeDestination(_, _)).WillOnce(Return(false));
    EXPECT_FALSE(navigationPattern->CreateHomeDestination(customNode, homeDest));

    auto fakeNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_CALL(*mockStack, CreateHomeDestination(_, _))
        .WillOnce(DoAll(
            WithArg<1>([&](RefPtr<UINode>& node) { node = fakeNode; }),
            Return(true)));
    customNode = nullptr;
    homeDest = nullptr;
    navigationNode->propInspectorId_ = "test_navigation_id_six";
    EXPECT_TRUE(navigationPattern->CreateHomeDestination(customNode, homeDest));
    EXPECT_EQ(customNode, fakeNode);
    EXPECT_EQ(homeDest, fakeNode);
    EXPECT_TRUE(homeDest->IsHomeDestination());
    auto destPattern = AceType::DynamicCast<NavDestinationPattern>(homeDest->GetPattern());
    ASSERT_NE(destPattern, nullptr);
    EXPECT_EQ(destPattern->GetNavigationNode(), navigationNode);
    EXPECT_EQ(destPattern->GetNavigationId(), "test_navigation_id_six");
}

/**
 * @tc.name: GetTopNavdestinationJson001
 * @tc.desc: Returns an empty JSON object when hostNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, GetTopNavdestinationJson001, TestSize.Level1)
{
    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto json = navigationPattern->GetTopNavdestinationJson(false);
    EXPECT_TRUE(json != nullptr);
    EXPECT_TRUE(json->IsValid());
    EXPECT_TRUE(json->IsObject());
}

/**
 * @tc.name: GetTopNavdestinationJson002
 * @tc.desc: Returns an empty JSON object when topNavDestinationNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, GetTopNavdestinationJson002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    pattern->navigationStack_ = stack;
    auto json = pattern->GetTopNavdestinationJson(false);
    EXPECT_TRUE(json != nullptr);
    EXPECT_TRUE(json->IsValid());
    EXPECT_TRUE(json->IsObject());
}

/**
 * @tc.name: GetTopNavdestinationJson003
 * @tc.desc: Returns a normal result when needParam is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, GetTopNavdestinationJson003, TestSize.Level1)
{
    OHOS::Ace::NG::NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navPattern = navDestNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPattern, nullptr);
    navPattern->SetName("TestPage");
    navDestNode->mode_ = NavDestinationMode::STANDARD;
    navigationNode->curId_ = "test_nav_id";
    auto stack = AceType::DynamicCast<NavigationStack>(pattern->navigationStack_);
    ASSERT_NE(stack, nullptr);
    stack->Add("TestPage", navDestNode);
    auto json = pattern->GetTopNavdestinationJson(false);
    EXPECT_EQ(json->GetString("name"), "TestPage");
    EXPECT_EQ(json->GetInt("mode"), static_cast<int32_t>(NavDestinationMode::STANDARD));
    EXPECT_EQ(json->GetString("navigationId"), "test_nav_id");
    EXPECT_EQ(json->GetString("param"), "");
}

/**
 * @tc.name: GetTopNavdestinationJson004
 * @tc.desc: Returns normally (needParam = true)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, GetTopNavdestinationJson004, TestSize.Level1)
{
    OHOS::Ace::NG::NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navPattern = navDestNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPattern, nullptr);
    navPattern->SetName("TestPage");
    navPattern->UpdateSerializedParam("paramValue");
    navDestNode->mode_ = NavDestinationMode::STANDARD;
    navigationNode->curId_ = "test_nav_id";
    auto stack = AceType::DynamicCast<NavigationStack>(pattern->navigationStack_);
    ASSERT_NE(stack, nullptr);
    stack->Add("TestPage", navDestNode);
    auto json = pattern->GetTopNavdestinationJson(true);
    EXPECT_EQ(json->GetString("name"), "TestPage");
    EXPECT_EQ(json->GetInt("mode"), static_cast<int32_t>(NavDestinationMode::STANDARD));
    EXPECT_EQ(json->GetString("navigationId"), "test_nav_id");
    EXPECT_EQ(json->GetString("param"), "paramValue");
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Normal case where both theme and dividerRenderProperty are non-nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationBarTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    navigationBarTheme->toolbarDividerColor_ = Color::RED;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationBarTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationBarTheme));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navBarNode->context_ = navigationNode->context_;
    navigationNode->navBarNode_ = navBarNode;
    navigationNode->AddChild(navBarNode);
    auto dividerPattern = AceType::MakeRefPtr<Pattern>();
    auto dividerNode = FrameNode::CreateFrameNode(
        V2::DIVIDER_ETS_TAG, 23456, dividerPattern);
    dividerNode->context_ = navigationNode->context_;
    dividerNode->paintProperty_ = AceType::MakeRefPtr<OHOS::Ace::NG::DividerRenderProperty>();
    dividerNode->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    dividerNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    navBarNode->toolBarDividerNode_ = dividerNode;
    navBarNode->AddChild(dividerNode);
    ASSERT_NE(navigationNode->navBarNode_, nullptr);
    ASSERT_NE(navBarNode->toolBarDividerNode_, nullptr);
    ASSERT_NE(dividerNode->paintProperty_, nullptr);
    EXPECT_FALSE(pattern->OnThemeScopeUpdate(1));
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: FireOnNewParam001
 * @tc.desc: Normal branch, all objects are not nullptr, eventHub->FireOnNewParam is called
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, FireOnNewParam001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navPattern = navDestNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPattern, nullptr);
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>("TestPage");
    navPathInfo->SetName("paramValue");
    auto navContext = AceType::MakeRefPtr<NavDestinationContext>();
    navContext->SetNavPathInfo(navPathInfo);
    navPattern->SetNavDestinationContext(navContext);
    auto eventHub = AceType::MakeRefPtr<NavDestinationEventHub>();
    navDestNode->eventHub_ = eventHub;
    navigationNode->AddChild(navDestNode);
    navDestNode->context_ = navigationNode->context_;
    ASSERT_EQ(navPattern->GetNavDestinationContext()->GetNavPathInfo()->GetName(), "paramValue");
    ASSERT_NE(navDestNode->eventHub_, nullptr);
    pattern->FireOnNewParam(navDestNode);
    EXPECT_EQ(navPattern->GetNavDestinationContext()->GetNavPathInfo()->GetName(), "paramValue");
    EXPECT_NE(navDestNode->eventHub_, nullptr);
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ShouldFireHomeDestiationLifecycle001
 * @tc.desc: Test all lifecycle branches in SPLIT mode and isModeChange=true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShouldFireHomeDestiationLifecycle001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    // ON_SHOW
    destPattern->SetIsOnShow(false);
    EXPECT_TRUE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_SHOW, destPattern, -1, 0, true));
    destPattern->SetIsOnShow(true);
    EXPECT_FALSE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_SHOW, destPattern, -1, 0, true));

    // ON_ACTIVE
    destPattern->SetIsActive(false);
    EXPECT_TRUE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_ACTIVE, destPattern, -1, 0, true));
    destPattern->SetIsActive(true);
    EXPECT_FALSE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_ACTIVE, destPattern, -1, 0, true));

    // ON_INACTIVE
    destPattern->SetIsActive(true);
    EXPECT_TRUE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_INACTIVE, destPattern, -1, 0, true));
    destPattern->SetIsActive(false);
    EXPECT_FALSE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_INACTIVE, destPattern, -1, 0, true));

    // ON_HIDE
    destPattern->SetIsOnShow(true);
    EXPECT_TRUE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_HIDE, destPattern, -1, 0, true));
    destPattern->SetIsOnShow(false);
    EXPECT_FALSE(navigationPattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_HIDE, destPattern, -1, 0, true));

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: ShouldFireHomeDestiationLifecycle002
 * @tc.desc: Test all lifecycle branches in STACK mode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShouldFireHomeDestiationLifecycle002, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    pattern->navigationMode_ = NavigationMode::STACK;

    // ON_SHOW
    destPattern->SetIsOnShow(false);
    EXPECT_TRUE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_SHOW, destPattern, -1, 0, false));
    destPattern->SetIsOnShow(true);
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_SHOW, destPattern, -1, 0, false));
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_SHOW, destPattern, 1, 0, false));

    // ON_ACTIVE
    destPattern->SetIsActive(false);
    EXPECT_TRUE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_ACTIVE, destPattern, -1, 0, false));
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_ACTIVE, destPattern, -1, 1, false));

    // ON_INACTIVE
    destPattern->SetIsActive(true);
    EXPECT_TRUE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_INACTIVE, destPattern, -1, 0, false));
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_INACTIVE, destPattern, -1, 1, false));

    // ON_HIDE
    destPattern->SetIsOnShow(true);
    EXPECT_TRUE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_HIDE, destPattern, -1, 0, false));
    destPattern->SetIsOnShow(false);
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_HIDE, destPattern, -1, 0, false));
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_HIDE, destPattern, 1, 0, false));
}

/**
 * @tc.name: ShouldFireHomeDestiationLifecycle003
 * @tc.desc: Test default return false for unknown lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShouldFireHomeDestiationLifecycle003, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_WILL_APPEAR, destPattern, -1, 0, true));
    EXPECT_FALSE(pattern->ShouldFireHomeDestiationLifecycle(
        NavDestinationLifecycle::ON_WILL_APPEAR, destPattern, -1, 0, false));

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: NavToolbarNode_ToJsonValue_001
 * @tc.desc: Simple test for NavToolbarNode::ToJsonValue to guarantee coverage
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, NavToolbarNode_ToJsonValue_001, TestSize.Level1)
{
    auto node = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    auto pattern = node->GetPattern<NavToolbarPattern>();
    ASSERT_NE(pattern, nullptr);
    NavigationToolbarOptions options;
    BlurStyleOption blurOpt;
    blurOpt.blurStyle = BlurStyle::THIN;
    options.bgOptions.blurStyleOption = blurOpt;
    EffectOption effectOpt;
    effectOpt.adaptiveColor = AdaptiveColor::DEFAULT;
    options.bgOptions.effectOption = effectOpt;
    pattern->SetToolbarOptions(options);
    MoreButtonOptions mbOpt;
    BlurStyleOption mbBlurOpt;
    mbBlurOpt.blurStyle = BlurStyle::REGULAR;
    mbOpt.bgOptions.blurStyleOption = mbBlurOpt;
    EffectOption mbEffectOpt;
    mbEffectOpt.adaptiveColor = AdaptiveColor::DEFAULT;
    mbOpt.bgOptions.effectOption = mbEffectOpt;
    pattern->SetToolbarMoreButtonOptions(std::move(mbOpt));
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    InspectorFilter filter;
    node->ToJsonValue(json, filter);
    auto moreButtonJson = json->GetValue("moreButtonOptions");
    EXPECT_NE(moreButtonJson, nullptr);
}

/**
 * @tc.name: TitleBarNode_ToJsonValue_001
 * @tc.desc: Simple test for TitleBarNode::ToJsonValue to guarantee coverage
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, TitleBarNode_ToJsonValue_001, TestSize.Level1)
{
    auto node = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto pattern = node->GetPattern<TitleBarPattern>();
    ASSERT_NE(pattern, nullptr);
    NavigationTitlebarOptions options;
    BlurStyleOption blurOpt;
    blurOpt.blurStyle = BlurStyle::THIN;
    options.bgOptions.blurStyleOption = blurOpt;
    EffectOption effectOpt;
    effectOpt.adaptiveColor = AdaptiveColor::DEFAULT;
    options.bgOptions.effectOption = effectOpt;
    pattern->SetTitlebarOptions(options);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    InspectorFilter filter;
    node->ToJsonValue(json, filter);
    EXPECT_TRUE(json->Contains("backgroundBlurStyle"));
}

/**
 * @tc.name: Menu_ToJsonValue001
 * @tc.desc: Simple test for NavDestinationGroupNode::ToJsonValue focusing on menuOptions coverage
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, Menu_ToJsonValue001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    auto groupNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto navPattern = groupNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navPattern, nullptr);

    NavigationMenuOptions menuOptions;
    BlurStyleOption blurOpt;
    blurOpt.blurStyle = BlurStyle::THIN;
    menuOptions.mbOptions.bgOptions.blurStyleOption = blurOpt;
    navPattern->SetMenuOptions(menuOptions);

    groupNode->layoutProperty_ = AceType::MakeRefPtr<NavDestinationLayoutPropertyBase>();

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    InspectorFilter filter;
    groupNode->ToJsonValue(json, filter);

    auto menuOptionsJson = json->GetValue("menuOptions");
    ASSERT_NE(menuOptionsJson, nullptr);

    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateColorModeForNodes001
 * @tc.desc: Both continue and body execution occur in the for loop; the nodeBase branch
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, UpdateColorModeForNodes001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode("Navigation",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestNode1 = NavDestinationGroupNode::GetOrCreateGroupNode("NavDest1",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("page1", navDestNode1);
    auto navDestNode2 = NavDestinationGroupNode::GetOrCreateGroupNode("NavDest2",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("page2", navDestNode2);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigationNode->lastStandardIndex_ = 0;
    navDestNode1->NotifyColorModeChange(true);
    navDestNode2->NotifyColorModeChange(false);
    navigationNode->navBarNode_ = navDestNode1;
    navigationPattern->UpdateColorModeForNodes(std::nullopt);
    ASSERT_NE(navDestNode1, nullptr);
    ASSERT_NE(navDestNode2, nullptr);

    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateColorModeForNodes002
 * @tc.desc: nodeBase->CheckIsDarkMode() == colorMode，Return
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, UpdateColorModeForNodes002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode("Navigation",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestNode1 = NavDestinationGroupNode::GetOrCreateGroupNode("NavDest1",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("page1", navDestNode1);
    navigationNode->lastStandardIndex_ = 0;
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigationNode->navBarNode_ = navDestNode1;
    navDestNode1->NotifyColorModeChange(true);
    navigationPattern->UpdateColorModeForNodes(std::nullopt);
    ASSERT_NE(navDestNode1, nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavBarNode001
 * @tc.desc: GetNavBarNode returns NavBarNode normally (full positive path coverage)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, GetNavBarNode001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode("Navigation",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    navigationPattern->AttachToFrameNode(navigationNode);
    auto result = navigationPattern->GetNavBarNode();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, navBarNode);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: FireHomeDestinationLifecycleForTransition001
 * @tc.desc: When lifecycle == ON_WILL_SHOW, the branch is satisfied and NotifyDestinationLifecycle is triggered
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, FireHomeDestinationLifecycleForTransition001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();

    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto parentNode = FrameNode::GetOrCreateFrameNode(V2::JS_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(navigation);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    auto destNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(destNode, nullptr);
    EXPECT_CALL(*mockNavPathStack, CreateHomeDestination(_, _))
        .WillOnce(DoAll(SetArgReferee<1>(destNode), Return(true)));
    navigation->OnAttachToMainTree(true);
    auto homeDest = navigation->GetHomeDestinationNode();
    auto homeDestNode = AceType::DynamicCast<NavDestinationGroupNode>(homeDest);
    ASSERT_NE(homeDestNode, nullptr);
    auto homePattern = homeDestNode->GetPattern();
    auto homePatternNav = AceType::DynamicCast<NavDestinationPattern>(homePattern);
    ASSERT_NE(homePatternNav, nullptr);
    homePatternNav->SetIsOnShow(false);
    navigationPattern->AttachToFrameNode(navigation);
    navigationPattern->FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_WILL_SHOW);
    EXPECT_FALSE(homePatternNav->GetIsOnShow());
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: FireHomeDestinationLifecycleForTransition002
 * @tc.desc: lifecycle == ON_ACTIVE
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, FireHomeDestinationLifecycleForTransition002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto parentNode = FrameNode::GetOrCreateFrameNode(V2::JS_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(navigation);
    auto destNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(destNode, nullptr);
    EXPECT_CALL(*mockNavPathStack, CreateHomeDestination(_, _))
        .WillOnce(DoAll(SetArgReferee<1>(destNode), Return(true)));
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigation->OnAttachToMainTree(true);
    auto homeDest = navigation->GetHomeDestinationNode();
    auto homeDestNode = AceType::DynamicCast<NavDestinationGroupNode>(homeDest);
    ASSERT_NE(homeDestNode, nullptr);
    auto homePattern = homeDestNode->GetPattern();
    auto homePatternNav = AceType::DynamicCast<NavDestinationPattern>(homePattern);
    ASSERT_NE(homePatternNav, nullptr);
    homePatternNav->SetIsActive(false);
    navigationPattern->AttachToFrameNode(navigation);
    navigationPattern->FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_ACTIVE);
    EXPECT_FALSE(homePatternNav->IsActive());
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: FireHomeDestinationLifecycleForTransition003
 * @tc.desc: lifecycle == ON_INACTIVE
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, FireHomeDestinationLifecycleForTransition003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto parentNode = FrameNode::GetOrCreateFrameNode(V2::JS_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(navigation);

    auto destNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(destNode, nullptr);
    EXPECT_CALL(*mockNavPathStack, CreateHomeDestination(_, _))
        .WillOnce(DoAll(SetArgReferee<1>(destNode), Return(true)));
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigation->OnAttachToMainTree(true);
    auto homeDest = navigation->GetHomeDestinationNode();
    auto homeDestNode = AceType::DynamicCast<NavDestinationGroupNode>(homeDest);
    ASSERT_NE(homeDestNode, nullptr);
    auto homePattern = homeDestNode->GetPattern();
    auto homePatternNav = AceType::DynamicCast<NavDestinationPattern>(homePattern);
    ASSERT_NE(homePatternNav, nullptr);
    homePatternNav->SetIsActive(true);
    navigationPattern->AttachToFrameNode(navigation);
    navigationPattern->FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_INACTIVE);
    EXPECT_TRUE(homePatternNav->IsActive());
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: FireHomeDestinationLifecycleForTransition004
 * @tc.desc: lifecycle == ON_WILL_HIDE
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, FireHomeDestinationLifecycleForTransition004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto parentNode = FrameNode::GetOrCreateFrameNode(V2::JS_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(navigation);
    auto destNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(destNode, nullptr);
    EXPECT_CALL(*mockNavPathStack, CreateHomeDestination(_, _))
        .WillOnce(DoAll(SetArgReferee<1>(destNode), Return(true)));
    navigation->OnAttachToMainTree(true);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    auto homeDest = navigation->GetHomeDestinationNode();
    auto homeDestNode = AceType::DynamicCast<NavDestinationGroupNode>(homeDest);
    ASSERT_NE(homeDestNode, nullptr);
    auto homePattern = homeDestNode->GetPattern();
    auto homePatternNav = AceType::DynamicCast<NavDestinationPattern>(homePattern);
    ASSERT_NE(homePatternNav, nullptr);
    homePatternNav->SetIsOnShow(true);
    navigationPattern->AttachToFrameNode(navigation);
    navigationPattern->FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_WILL_HIDE);
    EXPECT_TRUE(homePatternNav->GetIsOnShow());
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: OnWindowHide  SyncWithJsStackIfNeeded
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, OnWindowHide001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigationPattern->AttachToFrameNode(navigationNode);
    navigationPattern->OnWindowHide();
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: OnAvoidInfoChange001
 * @tc.desc: Returns directly when isFullPageNavigation_ is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, OnAvoidInfoChange001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigationPattern->AttachToFrameNode(navigationNode);
    ContainerModalAvoidInfo info;
    navigationPattern->OnAvoidInfoChange(info);
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: OnAvoidInfoChange002
 * @tc.desc: Calls MarkAllNavDestinationDirtyIfNeeded when isFullPageNavigation_ is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, OnAvoidInfoChange002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigationPattern->AttachToFrameNode(navigationNode);
    ContainerModalAvoidInfo info;
    navigationPattern->OnAvoidInfoChange(info);
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: HideSystemBarIfNeeded001
 * @tc.desc: Returns directly when IsPageLevelConfigEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, HideSystemBarIfNeeded001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(false, navigationPattern, navigationNode, nullptr);
    navigationPattern->HideSystemBarIfNeeded();
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}
    
/**
 * @tc.name: HideSystemBarIfNeeded002
 * @tc.desc: Returns directly when IsPageLevelConfigEnabled is true and lastNode is null
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, HideSystemBarIfNeeded002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    navigationPattern->HideSystemBarIfNeeded();
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: HideSystemBarIfNeeded003
 * @tc.desc: Returns directly when IsPageLevelConfigEnabled is true, lastNode exists,
    but IsSizeMatchNavigation returns false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, HideSystemBarIfNeeded003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode("NavDest",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestNode->SetIsSizeMatchNavigation(false);
    navigationNode->AddChild(navDestNode);
    navigationPattern->HideSystemBarIfNeeded();
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: HideSystemBarIfNeeded004
 * @tc.desc: IsPageLevelConfigEnabled returns true, lastNode exists and
    IsSizeMatchNavigation returns true; main process positive path coverage
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, HideSystemBarIfNeeded004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    navigationPattern->AttachToFrameNode(navigationNode);
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode("NavDest",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestNode->SetIsSizeMatchNavigation(true);
    navigationNode->AddChild(navDestNode);
    navigationPattern->HideSystemBarIfNeeded();
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: HideSystemBarIfNeeded005
 * @tc.desc: IsPageLevelConfigEnabled returns true, lastNode exists and
    IsSizeMatchNavigation returns true, navIndicatorConfig meets the condition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, HideSystemBarIfNeeded005, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    auto navDestNode = NavDestinationGroupNode::GetOrCreateGroupNode("NavDest",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestNode->SetIsSizeMatchNavigation(true);
    navDestNode->SetNavigationIndicatorConfig(std::make_optional(false));
    navigationNode->AddChild(navDestNode);
    navigationPattern->HideSystemBarIfNeeded();
    SUCCEED();
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: SetToolbarManagerNavigationMode001
 * @tc.desc: toolbarManager_ exists, navigationMode is different from the parameter, SetNavigationMode will be called
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, SetToolbarManagerNavigationMode001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode("Navigation",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    navigationPattern->AttachToFrameNode(navigationNode);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolbarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolbarManager, nullptr);
    toolbarManager->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->toolbarManager_ = toolbarManager;
    navigationPattern->SetToolbarManagerNavigationMode(NavigationMode::SPLIT);
    EXPECT_EQ(toolbarManager->GetNavigationMode(), NavigationMode::SPLIT);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: ShowOrRestoreSystemBarIfNeeded001
 * @tc.desc: IsPageLevelConfigEnabled() == false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShowOrRestoreSystemBarIfNeeded001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    navigationNode->context_ = navigationNode->context_;
    navigationNode->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    navigationNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    SetIsPageLevelConfigEnabled(false, navigationPattern, navigationNode, nullptr);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    EXPECT_EQ(navigationPattern->pageNode_.Upgrade(), nullptr);
    navigationPattern->ShowOrRestoreSystemBarIfNeeded();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    EXPECT_EQ(navigationPattern->pageNode_.Upgrade(), nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: ShowOrRestoreSystemBarIfNeeded002
 * @tc.desc: IsPageLevelConfigEnabled() == true，GetLastStandardNodeOrNavBar() == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShowOrRestoreSystemBarIfNeeded002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    navigationPattern->pageNode_ = nullptr;
    EXPECT_EQ(navigationPattern->pageNode_.Upgrade(), nullptr);
    navigationPattern->ShowOrRestoreSystemBarIfNeeded();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: ShowOrRestoreSystemBarIfNeeded003
 * @tc.desc: statusBarConfig.has_value() == true && statusBarConfig.value().first == true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShowOrRestoreSystemBarIfNeeded003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    auto lastNode = NavDestinationGroupNode::GetOrCreateGroupNode("lastNode",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    lastNode->context_ = navigationNode->context_;
    lastNode->statusBarConfig_ = std::make_optional(std::make_pair(true, true));
    navigationPattern->pageNode_ = lastNode;
    ASSERT_TRUE(lastNode->statusBarConfig_.has_value());
    ASSERT_TRUE(lastNode->statusBarConfig_.value().first);
    navigationPattern->ShowOrRestoreSystemBarIfNeeded();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: ShowOrRestoreSystemBarIfNeeded004
 * @tc.desc: statusBarConfig.has_value() == false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShowOrRestoreSystemBarIfNeeded004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    auto lastNode = NavDestinationGroupNode::GetOrCreateGroupNode("lastNode",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    lastNode->context_ = navigationNode->context_;
    navigationPattern->pageNode_ = lastNode;
    ASSERT_FALSE(lastNode->statusBarConfig_.has_value());
    navigationPattern->ShowOrRestoreSystemBarIfNeeded();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: ShowOrRestoreSystemBarIfNeeded005
 * @tc.desc: navIndicatorConfig.has_value() == true && navIndicatorConfig.value() == true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShowOrRestoreSystemBarIfNeeded005, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    auto lastNode = NavDestinationGroupNode::GetOrCreateGroupNode("lastNode", 10005,
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    lastNode->context_ = navigationNode->context_;
    lastNode->navigationIndicatorConfig_ = std::make_optional(true);
    navigationPattern->pageNode_ = lastNode;
    ASSERT_TRUE(lastNode->navigationIndicatorConfig_.has_value());
    ASSERT_TRUE(lastNode->navigationIndicatorConfig_.value());
    navigationPattern->ShowOrRestoreSystemBarIfNeeded();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: ShowOrRestoreSystemBarIfNeeded006
 * @tc.desc: navIndicatorConfig.has_value() == false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, ShowOrRestoreSystemBarIfNeeded006, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    /**
     * @tc.steps:step2. do some modify and verify
     */
    SetIsPageLevelConfigEnabled(true, navigationPattern, navigationNode, nullptr);
    auto lastNode = NavDestinationGroupNode::GetOrCreateGroupNode("lastNode", 10006,
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    lastNode->context_ = navigationNode->context_;
    navigationPattern->pageNode_ = lastNode;
    ASSERT_FALSE(lastNode->navigationIndicatorConfig_.has_value());
    navigationPattern->ShowOrRestoreSystemBarIfNeeded();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavigationPatternTestSixNg::TearDownTestSuite();
}

/**
 * @tc.name: CustomizeExpandSafeArea001
 * @tc.desc: RunCustomizeExpandIfNeeded(host) Return false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSixNg, CustomizeExpandSafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    NavigationPatternTestSixNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->AttachToFrameNode(navigationNode);
    navigationNode->context_ = navigationNode->context_;
    navigationNode->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    navigationNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    bool result = navigationPattern->CustomizeExpandSafeArea();
    EXPECT_FALSE(result);
    NavigationPatternTestSixNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG