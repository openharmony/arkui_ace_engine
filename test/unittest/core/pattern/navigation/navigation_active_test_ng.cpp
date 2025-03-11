/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
void RunNavigationStackSync(const RefPtr<NavigationPattern>& navigationPattern)
{
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
}
} // namespace

class NavigationActiveTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    RefPtr<NavDestinationGroupNode> CreateAndSetLifecycle(const std::string& name);
};

void NavigationActiveTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationActiveTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<NavDestinationGroupNode> NavigationActiveTestNg::CreateAndSetLifecycle(const std::string& name)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(
        NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, 101,
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); }));
    EXPECT_FALSE(navDestinationGroupNode == nullptr);
    auto pattern = navDestinationGroupNode->GetPattern<NavDestinationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetName(name);
    return navDestinationGroupNode;
}

/**
 * @tc.name: NavigationActiveTest001
 * @tc.desc: test whether active is set correctly after push operation.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationActiveTestNg, NavigationActiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with title and barStyle.
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. create a navdestination with custom node inside.
     */
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest"));
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationNodeBase>(navigationContent->GetChildAtIndex(0));
    ASSERT_NE(navDestination, nullptr);
    auto customNode = CustomNode::CreateCustomNode(-1, "customNode");
    ASSERT_NE(customNode, nullptr);
    navDestination->AddChild(customNode);
    /**
     * @tc.steps: step3. mock push without animation.
     */
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest2"), false);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(customNode->GetJsActive(), false);
}

/**
 * @tc.name: NavigationTransitionLifecycle001
 * @tc.desc: Branch: if (activeReason == NavigationActiveReason::TRANSITION)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationActiveTestNg, NavigationTransitionLifecycle001, TestSize.Level1)
{
     /**
      * @tc.steps: step1. create navigation node and add navigation node to navigationManager
      */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, 2,
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    EXPECT_FALSE(navigationNode == nullptr);
    auto elementRegister = ElementRegister::GetInstance();
    EXPECT_FALSE(elementRegister == nullptr);
    elementRegister->AddUINode(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetNavigationStack(mockNavPathStack);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    EXPECT_FALSE(navigationManager == nullptr);
    auto pageNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(pageNode == nullptr);

    /**
     * @tc.steps: step2. create navdestiantion and setActive callback
     */
    auto navDestinationNode = CreateAndSetLifecycle("pageA");
    navigationManager->AddNavigation(pageNode->GetId(), navigationNode->GetId());
    mockNavPathStack->Add("pageA", navDestinationNode);
    navigationNode->MarkModifyDone();
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(navigationPattern == nullptr);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2. fire pageA active lifecycle
     * @tc.expected: step2.navdestinationA state is active
     */
    navigationManager->FireNavigationLifecycle(pageNode, static_cast<int32_t>(NavDestinationLifecycle::ON_INACTIVE),
        static_cast<int32_t>(NavDestinationActiveReason::TRANSITION));
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(mockNavPathStack->Get());
    EXPECT_FALSE(destination == nullptr);
    auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    EXPECT_TRUE(eventHub->state_ == NavDestinationState::ON_INACTIVE);
}

/**
 * @tc.name: NavigationTransitionLifecycle002
 * @tc.desc: Branch: push destination
 * if (activeReason == NavigationActiveReason::TRANSITION)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationActiveTestNg, NavigationTransitionLifecycle002, TestSize.Level1)
{
     /**
      * @tc.steps: step1. create navigation node and add navigation node to navigationManager
      */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, 2,
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    EXPECT_FALSE(navigationNode == nullptr);
    auto elementRegister = ElementRegister::GetInstance();
    EXPECT_FALSE(elementRegister == nullptr);
    elementRegister->AddUINode(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetNavigationStack(mockNavPathStack);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    EXPECT_FALSE(navigationManager == nullptr);
    auto pageNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(pageNode == nullptr);

    /**
     * @tc.steps: step2. create navdestiantion and setActive callback
     */
    auto navDestinationNode = CreateAndSetLifecycle("pageA");
    navigationManager->AddNavigation(pageNode->GetId(), navigationNode->GetId());
    mockNavPathStack->Add("pageA", navDestinationNode);
    navigationNode->MarkModifyDone();
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(navigationPattern == nullptr);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2. check pageA state
     * @tc.expected: step2.navdestinationA state is active
     */
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(mockNavPathStack->Get());
    EXPECT_FALSE(destination == nullptr);
    auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    EXPECT_TRUE(eventHub->state_ == NavDestinationState::ON_ACTIVE);
}

/**
 * @tc.name: NavigationPageLifecycle003
 * @tc.desc: Branch: pagePattern->pageShow
 * if (isFromWindow == true)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationActiveTestNg, NavigationTransitionLifecycle003, TestSize.Level1)
{
     /**
      * @tc.steps: step1. create navigation node and add navigation node to navigationManager
      */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, 2,
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    EXPECT_FALSE(navigationNode == nullptr);
    auto elementRegister = ElementRegister::GetInstance();
    EXPECT_FALSE(elementRegister == nullptr);
    elementRegister->AddUINode(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetNavigationStack(mockNavPathStack);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    EXPECT_FALSE(navigationManager == nullptr);
    auto pageNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(pageNode == nullptr);

    /**
     * @tc.steps: step2. create navdestiantion and setActive callback
     */
    auto navDestinationNode = CreateAndSetLifecycle("pageA");
    navigationManager->AddNavigation(pageNode->GetId(), navigationNode->GetId());
    mockNavPathStack->Add("pageA", navDestinationNode);
    navigationNode->MarkModifyDone();
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(navigationPattern == nullptr);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2. fire page show,set isFromWindow true
     * @tc.expected: step2.navdestination active reason is app state change
     */
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(mockNavPathStack->Get());
    EXPECT_FALSE(destination == nullptr);
    auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->SetOnActive([](int32_t reason) {
        int32_t targetReason = static_cast<int32_t>(NavDestinationActiveReason::APP_STATE_CHANGE);
        EXPECT_TRUE(targetReason == reason);
    });
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->OnShow(true);
}

/**
 * @tc.name: NavigationPageLifecycle004
 * @tc.desc: Branch: pagePattern->pageHide
 * if (isFromWindow == true)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationActiveTestNg, NavigationTransitionLifecycle004, TestSize.Level1)
{
     /**
      * @tc.steps: step1.create navigation node and add navigation node to navigationManager
      */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG, 2,
        []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    EXPECT_FALSE(navigationNode == nullptr);
    auto elementRegister = ElementRegister::GetInstance();
    EXPECT_FALSE(elementRegister == nullptr);
    elementRegister->AddUINode(navigationNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    pattern->SetNavigationStack(mockNavPathStack);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    EXPECT_FALSE(navigationManager == nullptr);
    auto pageNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    EXPECT_FALSE(pageNode == nullptr);

    /**
     * @tc.steps: step2. create navdestiantion and setActive callback
     */
    auto navDestinationNode = CreateAndSetLifecycle("pageA");
    navigationManager->AddNavigation(pageNode->GetId(), navigationNode->GetId());
    mockNavPathStack->Add("pageA", navDestinationNode);
    navigationNode->MarkModifyDone();
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(navigationPattern == nullptr);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2. fire page show,set isFromWindow true
     * @tc.expected: step2.navdestination active reason is app state change
     */
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(mockNavPathStack->Get());
    EXPECT_FALSE(destination == nullptr);
    auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHub == nullptr);
    eventHub->SetOnActive([](int32_t reason) {
        int32_t targetReason = static_cast<int32_t>(NavDestinationActiveReason::APP_STATE_CHANGE);
        EXPECT_TRUE(targetReason == reason);
    });
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    EXPECT_FALSE(pagePattern == nullptr);
    pagePattern->OnHide(true);
}
} // namespace OHOS::Ace::NG
