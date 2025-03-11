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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_route.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

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
class NavigationGroupNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void NavigationGroupNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::SetUp();
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationGroupNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/*
 * @tc.name: RemoveRedundantNavDestinationTest001
 * @tc.desc: Branch: slot == 0 && `no other extra flag set`
 *           Expect: all navDestination are deleted after RemoveRedundantNavDestination called.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveRedundantNavDestinationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
    /**
     * @tc.steps: step3. call RemoveRedundantNavDestination and check the size of navDestinations.
     */
    const int32_t slot = 0;
    bool mockHasChanged = false;
    navigation->RemoveRedundantNavDestination(navigationContent, nullptr, slot, mockHasChanged, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), 0);
    ASSERT_EQ(mockHasChanged, true);
}

/*
 * @tc.name: RemoveRedundantNavDestinationTest002
 * @tc.desc: Branch: slot == preStackSize && `no other extra flag set`
 *           Expect: all navDestination are reserved after RemoveRedundantNavDestination called.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveRedundantNavDestinationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
    /**
     * @tc.steps: step3. call RemoveRedundantNavDestination and check the size of navDestinations.
     */
    const int32_t slot = testNumber;
    bool mockHasChanged = false;
    navigation->RemoveRedundantNavDestination(navigationContent, nullptr, slot, mockHasChanged, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
    ASSERT_EQ(mockHasChanged, false);
}

/*
 * @tc.name: RemoveRedundantNavDestinationTest003
 * @tc.desc: Branch: slot != 0 && `no other extra flag set`
 *           Expect: only the first `slot` slots navDestination are reserved after RemoveRedundantNavDestination called.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveRedundantNavDestinationTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(navDestinationPattern, nullptr);
        ASSERT_EQ(navDestinationPattern->GetName(), destNameBase + std::to_string(index));
    }
    /**
     * @tc.steps: step3. call RemoveRedundantNavDestination and check the size and name of navDestinations.
     */
    const int32_t slot = 4;
    bool mockHasChanged = false;
    navigation->RemoveRedundantNavDestination(navigationContent, nullptr, slot, mockHasChanged, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), slot);
    for (int32_t index = 0; index < slot; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(navDestinationPattern, nullptr);
        ASSERT_EQ(navDestinationPattern->GetName(), destNameBase + std::to_string(index));
    }
    ASSERT_EQ(mockHasChanged, true);
}

/*
 * @tc.name: RemoveJsChildImmediately001
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveJsChildImmediately001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    container->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preTopNavDestinationNode->SetDestroying(false);

    navigationNode->RemoveJsChildImmediately(preTopNavDestinationNode, false, 1);
    EXPECT_FALSE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: RemoveJsChildImmediately002
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if (preUseCustomTransition || !preNavdestination->CheckTransitionPop(preAnimationId)) = true
 *           Condition: preUseCustomTransition = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveJsChildImmediately002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    container->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preTopNavDestinationNode->SetDestroying(false);

    navigationNode->RemoveJsChildImmediately(preTopNavDestinationNode, true, 1);
    EXPECT_FALSE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: RemoveJsChildImmediately003
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if (preUseCustomTransition || !preNavdestination->CheckTransitionPop(preAnimationId)) = true
 *           Condition: preUseCustomTransition = false, !preNavdestination->CheckTransitionPop(preAnimationId) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveJsChildImmediately003, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    container->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preTopNavDestinationNode->SetIsCacheNode(true);
    preTopNavDestinationNode->SetDestroying(false);

    navigationNode->RemoveJsChildImmediately(preTopNavDestinationNode, false, 1);
    EXPECT_FALSE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: RemoveJsChildImmediately004
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if (preUseCustomTransition || !preNavdestination->CheckTransitionPop(preAnimationId)) = false
 *           Condition: preUseCustomTransition = false, !preNavdestination->CheckTransitionPop(preAnimationId) = false
 *           Branch: if (preNode->HasSkipNode()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveJsChildImmediately004, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    container->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preTopNavDestinationNode->SetIsCacheNode(false);
    preTopNavDestinationNode->animationId_ = 1;
    preTopNavDestinationNode->SetTransitionType(PageTransitionType::EXIT_POP);
    auto webNode = FrameNode::CreateFrameNode(V2::WEB_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    preTopNavDestinationNode->children_.emplace_back(webNode);
    preTopNavDestinationNode->SetDestroying(false);

    navigationNode->RemoveJsChildImmediately(preTopNavDestinationNode, false, 1);
    EXPECT_FALSE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: RemoveJsChildImmediately005
 * @tc.desc: Branch: if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) = false
 *           Branch: if (preUseCustomTransition || !preNavdestination->CheckTransitionPop(preAnimationId)) = false
 *           Condition: preUseCustomTransition = false, !preNavdestination->CheckTransitionPop(preAnimationId) = false
 *           Branch: if (preNode->HasSkipNode()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveJsChildImmediately005, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    container->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preTopNavDestinationNode->SetIsCacheNode(false);
    preTopNavDestinationNode->animationId_ = 1;
    preTopNavDestinationNode->SetTransitionType(PageTransitionType::EXIT_POP);
    preTopNavDestinationNode->SetDestroying(false);

    navigationNode->RemoveJsChildImmediately(preTopNavDestinationNode, false, 1);
    EXPECT_TRUE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow001
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = true
 *           Condition: !context->GetInstallationFree() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = false;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow002
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = true
 *           Condition: !context->GetInstallationFree() = false, !result = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(false);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow003
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = false
 *           Condition: !context->GetInstallationFree() = false, !result = false
 *           Branch: if (navigationStack->GetSize() != 1 || isHasParentNavigation ||
 *               !overlayManager->IsModalEmpty() || pageSize != 1) = false
 *           Condition: navigationStack->GetSize() != 1 = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow003, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->size_ = 0;
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow004
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = false
 *           Condition: !context->GetInstallationFree() = false, !result = false
 *           Branch: if (navigationStack->GetSize() != 1 || isHasParentNavigation ||
 *               !overlayManager->IsModalEmpty() || pageSize != 1) = false
 *           Condition: navigationStack->GetSize() != 1 = false, isHasParentNavigation = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow004, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->size_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto parentNavigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto parentNavigationPattern = parentNavigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(parentNavigationPattern, nullptr);
    auto parentNavigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    parentNavigationPattern->SetNavigationStack(parentNavigationStack);
    navigationNode->parent_ = parentNavigationNode;
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow005
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = false
 *           Condition: !context->GetInstallationFree() = false, !result = false
 *           Branch: if (navigationStack->GetSize() != 1 || isHasParentNavigation ||
 *               !overlayManager->IsModalEmpty() || pageSize != 1) = false
 *           Condition: navigationStack->GetSize() != 1 = false, isHasParentNavigation = false,
 *               !overlayManager->IsModalEmpty() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow005, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->size_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->modalStack_.push(nullptr);
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow006
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = false
 *           Condition: !context->GetInstallationFree() = false, !result = false
 *           Branch: if (navigationStack->GetSize() != 1 || isHasParentNavigation ||
 *               !overlayManager->IsModalEmpty() || pageSize != 1) = false
 *           Condition: navigationStack->GetSize() != 1 = false, isHasParentNavigation = false,
 *               !overlayManager->IsModalEmpty() = false, pageSize != 1 = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow006, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->size_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow007
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = false
 *           Condition: !context->GetInstallationFree() = false, !result = false
 *           Branch: if (navigationStack->GetSize() != 1 || isHasParentNavigation ||
 *               !overlayManager->IsModalEmpty() || pageSize != 1) = false
 *           Condition: navigationStack->GetSize() != 1 = false, isHasParentNavigation = false,
 *               !overlayManager->IsModalEmpty() = false, pageSize != 1 = false
 *           Branch: if (!isLastNavdesNeedIntercept) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow007, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->size_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto stageManager = pipelineContext->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    stageManager->stageNode_ = stageNode;
    stageManager->stageNode_->children_.emplace_back(nullptr);
    navigationPattern->navigationMode_ = NavigationMode::AUTO;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_FALSE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckIsNeedForceExitWindow008
 * @tc.desc: Branch: if (!context->GetInstallationFree() || !result) = false
 *           Condition: !context->GetInstallationFree() = false, !result = false
 *           Branch: if (navigationStack->GetSize() != 1 || isHasParentNavigation ||
 *               !overlayManager->IsModalEmpty() || pageSize != 1) = false
 *           Condition: navigationStack->GetSize() != 1 = false, isHasParentNavigation = false,
 *               !overlayManager->IsModalEmpty() = false, pageSize != 1 = false
 *           Branch: if (!isLastNavdesNeedIntercept) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckIsNeedForceExitWindow008, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->size_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->installationFree_ = true;
    auto stageNode = FrameNode::CreateFrameNode(V2::STAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto stageManager = pipelineContext->GetStageManager();
    ASSERT_NE(stageManager, nullptr);
    stageManager->stageNode_ = stageNode;
    stageManager->stageNode_->children_.emplace_back(nullptr);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    auto windowManager = pipelineContext->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool hasBack = false;
    windowManager->windowPerformBackCallback_ = [&hasBack]() {
        hasBack = true;
    };

    navigationNode->CheckIsNeedForceExitWindow(true);
    EXPECT_TRUE(hasBack);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ToJsonValue001
 * @tc.desc: Branch: if (titleBarNode) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ToJsonValue001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    navigationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("title"), "");
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ToJsonValue002
 * @tc.desc: Branch: if (titleBarNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ToJsonValue002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->propContent_ = u"Page01";
    titleBarNode->title_ = textNode;
    navBarNode->titleBarNode_ = titleBarNode;
    navigationNode->navBarNode_ = navBarNode;

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    navigationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("title"), "Page01");
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ToDumpString001
 * @tc.desc: Branch: case NavigationMode::STACK = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ToDumpString001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;

    string dump = navigationNode->ToDumpString();
    EXPECT_NE(dump.find("Mode: \"STACK\""), string::npos);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ToDumpString002
 * @tc.desc: Branch: case case NavigationMode::SPLIT = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ToDumpString002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::SPLIT;

    string dump = navigationNode->ToDumpString();
    EXPECT_NE(dump.find("Mode: \"SPLIT\""), string::npos);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ToDumpString003
 * @tc.desc: Branch: case NavigationMode::AUTO = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ToDumpString003, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::AUTO;

    string dump = navigationNode->ToDumpString();
    EXPECT_NE(dump.find("Mode: \"AUTO"), string::npos);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ToDumpString004
 * @tc.desc: Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ToDumpString004, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode(-1);

    string dump = navigationNode->ToDumpString();
    EXPECT_NE(dump.find("Mode: \"INVALID\""), string::npos);
    NavigationGroupNodeTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG