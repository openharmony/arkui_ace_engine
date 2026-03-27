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

#include "core/components_ng/pattern/navigation/navigation_model_static.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
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
    auto webNode = FrameNode::CreateFrameNode(
        V2::WEB_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
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
    EXPECT_FALSE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: RemoveJsChildImmediately006
 * @tc.desc: Test SetIsCustomNodeDeleteInTransition = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveJsChildImmediately006, TestSize.Level1)
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
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsCustomNodeDeleteInTransition(true);

    navigationNode->RemoveJsChildImmediately(preTopNavDestinationNode, false, 1);
    EXPECT_FALSE(preTopNavDestinationNode->isInDestroying_);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: HandleBackForHomeOrRelatedDestination001
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, HandleBackForHomeOrRelatedDestination001, TestSize.Level1)
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
    bool res = navigationNode->HandleBackForHomeOrRelatedDestination();
    EXPECT_FALSE(res);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: StartSoftOpacityAnimationPush001
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, StartSoftOpacityAnimationPush, TestSize.Level1)
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
    auto destNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(destNode, nullptr);
    navigationNode->StartSoftOpacityAnimationPush(destNode);
    ASSERT_NE(destNode, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SoftTransitionAnimationPush
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SoftTransitionAnimationPush001, TestSize.Level1)
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
    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preNode, nullptr);
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(curNode, nullptr);
    NavigationGroupNode::AnimationFinishCallback callback = []() { return false; };
    navigationNode->SoftTransitionAnimationPush(preNode, curNode, true, true, true, callback);
    ASSERT_NE(curNode, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetSplitPlaceholder001
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetSplitPlaceholder001, TestSize.Level1)
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
    navigationNode->SetSplitPlaceholder(navigationNode);
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

/*
 * @tc.name: RemoveDialogDestination
 * @tc.desc: Branch: if (!iter->second) false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveDialogDestination, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
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
    const int32_t testNumber = 1;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    auto fisrtChild = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(0));
    ASSERT_NE(fisrtChild, nullptr);
    navigation->hideNodes_.emplace_back(fisrtChild, true);
    auto layoutProperty = navigationContent->GetLayoutProperty();
    layoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_NORMAL);

    /**
     * @tc.steps: step3. call RemoveDialogDestination. check the flag.
     */
    navigation->RemoveDialogDestination();
    EXPECT_EQ(layoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE, PROPERTY_UPDATE_MEASURE);
}

/*
 * @tc.name: GetNavBarOrHomeDestinationNode001
 * @tc.desc: Branch: if (useHomeDestination_.has_value() && useHomeDestination_.value()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetNavBarOrHomeDestinationNode001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    navigation->useHomeDestination_ = true;
    auto node = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(node, nullptr);
    navigation->customHomeDestination_ = node;
    auto retNode = navigation->GetNavBarOrHomeDestinationNode();
    EXPECT_EQ(retNode, node);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetNavBarOrHomeDestinationNode002
 * @tc.desc: Branch: if (useHomeDestination_.has_value() && useHomeDestination_.value()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetNavBarOrHomeDestinationNode002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto node = FrameNode::GetOrCreateFrameNode(V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(node, nullptr);
    navigation->navBarNode_ = node;

    navigation->useHomeDestination_ = std::nullopt;
    auto retNode = navigation->GetNavBarOrHomeDestinationNode();
    EXPECT_EQ(retNode, node);

    navigation->useHomeDestination_ = false;
    retNode = navigation->GetNavBarOrHomeDestinationNode();
    EXPECT_EQ(retNode, node);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Branch: if (!parentCustomNode && curTag == V2::JS_VIEW_ETS_TAG) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    // create homeNavDestination
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navPattern, nullptr);
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
    EXPECT_EQ(navPattern->GetParentCustomNode().Upgrade(), parentNode);
    auto homeDest = navigation->GetHomeDestinationNode();
    EXPECT_EQ(homeDest, destNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: UpdateNavdestinationVisiblity001
 * @tc.desc: Branch: if (index == static_cast<int32_t>(destinationSize) - 1) false
 *                   if (navigationPattern->IsPrimaryNode(navDestination)) false
 *                   if (index < lastStandardIndex_) false
 *                   if (navDestination->GetPattern<NavDestinationPattern>()->GetCustomNode() != remainChild) true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, UpdateNavdestinationVisiblity001, TestSize.Level1)
{
    /*
     *@tc.steps create navNode
     */
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->isOnAnimation_ = true;
    auto layoutProperty = navDestination->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    auto navPattern = navDestination->GetPattern<NavDestinationPattern>();
    navPattern->SetCustomNode(navDestination);
    /*
     *@tc.steps test updateNavDestinationVisiblity
     */
    navigationNode->lastStandardIndex_ = -1;
    navigationNode->UpdateNavDestinationVisibility(navDestination, nullptr, 1, 10, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    /*
     *@tc.steps test if (navDestination->GetPattern<NavDestinationPattern>()->GetCustomNode() != remainChild) false
     */
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    navigationNode->UpdateNavDestinationVisibility(navDestination, navDestination, 1, 10, nullptr);
    EXPECT_EQ(layoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: IsHomeNodeAndShouldShowTest001
 * @tc.desc: Branch: if arg == nullptr
 *                   if arg == simple navDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, IsHomeNodeAndShouldShowTest001, TestSize.Level1)
{
    /*
     *@tc.steps create navNode
     */
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    /*
    *@tc.steps mock and call function
    */
    ASSERT_FALSE(navigationNode->IsHomeNodeAndShouldShow(nullptr));
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_FALSE(navigationNode->IsHomeNodeAndShouldShow(navDestination));
}

/*
 * @tc.name: GetNavigationModeTest001
 * @tc.desc: Test GetNavigationMode returns correct mode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetNavigationModeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    EXPECT_EQ(navigation->GetNavigationMode(), NavigationMode::STACK);

    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);
    EXPECT_EQ(navigation->GetNavigationMode(), NavigationMode::SPLIT);

    navigationPattern->SetNavigationMode(NavigationMode::AUTO);
    EXPECT_EQ(navigation->GetNavigationMode(), NavigationMode::AUTO);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetTopDestinationTest001
 * @tc.desc: Test GetTopDestination returns top destination from stack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetTopDestinationTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    auto stack = navigationPattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("test", navDestination);

    auto topDestination = navigation->GetTopDestination();
    EXPECT_EQ(topDestination, navDestination);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: HandleBackTest001
 * @tc.desc: Test HandleBack with non-last child
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, HandleBackTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    auto stack = navigationPattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("test", navDestination);

    bool result = navigation->HandleBack(navDestination, false, false);
    EXPECT_TRUE(result);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: HandleBackTest002
 * @tc.desc: Test HandleBack when node is last child
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, HandleBackTest002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    auto stack = navigationPattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("test", navDestination);

    bool result = navigation->HandleBack(navDestination, true, false);
    EXPECT_TRUE(result);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: FetchNavigationManagerTest001
 * @tc.desc: Test FetchNavigationManager returns manager from context
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, FetchNavigationManagerTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto navigationManager = navigation->FetchNavigationManager();
    EXPECT_NE(navigationManager, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ConfigureNavigationWithAnimationTest001
 * @tc.desc: Test ConfigureNavigationWithAnimation sets navigation manager state
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ConfigureNavigationWithAnimationTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto preNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto curNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    navigation->ConfigureNavigationWithAnimation(preNode, curNode);
    ASSERT_NE(preNode, nullptr);
    ASSERT_NE(curNode, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ResetTransitionAnimationNodeStateTest001
 * @tc.desc: Test ResetTransitionAnimationNodeState resets animation state
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ResetTransitionAnimationNodeStateTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto preNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto curNode = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    navigation->ResetTransitionAnimationNodeState(preNode, curNode);
    ASSERT_NE(preNode, nullptr);
    ASSERT_NE(curNode, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: TransitionAnimationIsValidTest001
 * @tc.desc: Test TransitionAnimationIsValid validates animation nodes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, TransitionAnimationIsValidTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto node = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    auto result = navigation->TransitionAnimationIsValid(node, false, false);
    EXPECT_NE(result, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: TransitionAnimationIsValidTest002
 * @tc.desc: Test TransitionAnimationIsValid with navBar flag
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, TransitionAnimationIsValidTest002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto node = FrameNode::CreateFrameNode(
        "test", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    auto result = navigation->TransitionAnimationIsValid(node, true, false);
    EXPECT_EQ(result, node);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: MakeUniqueAnimationIdTest001
 * @tc.desc: Test MakeUniqueAnimationId generates unique IDs
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, MakeUniqueAnimationIdTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    int32_t id1 = navigation->MakeUniqueAnimationId();
    int32_t id2 = navigation->MakeUniqueAnimationId();
    int32_t id3 = navigation->MakeUniqueAnimationId();

    EXPECT_GT(id1, 0);
    EXPECT_GT(id2, id1);
    EXPECT_GT(id3, id2);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetAnimationIdTest001
 * @tc.desc: Test GetAnimationId returns current animation ID
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetAnimationIdTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    int32_t id = navigation->MakeUniqueAnimationId();
    EXPECT_EQ(navigation->GetAnimationId(), id);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckAnimationIdValidTest001
 * @tc.desc: Test CheckAnimationIdValid validates animation ID
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckAnimationIdValidTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    int32_t animationId = navigation->MakeUniqueAnimationId();
    navDestination->UpdateAnimationId(animationId);

    bool result = navigation->CheckAnimationIdValid(navDestination, animationId);
    EXPECT_TRUE(result);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckAnimationIdValidTest002
 * @tc.desc: Test CheckAnimationIdValid with invalid ID
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckAnimationIdValidTest002, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    int32_t animationId = navigation->MakeUniqueAnimationId();
    navDestination->UpdateAnimationId(animationId);

    bool result = navigation->CheckAnimationIdValid(navDestination, animationId + 1);
    EXPECT_FALSE(result);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: NotifyPageHideTest001
 * @tc.desc: Test NotifyPageHide notifies page hide event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, NotifyPageHideTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->NotifyPageHide();
    ASSERT_NE(navigation, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: UpdateLastStandardIndexTest001
 * @tc.desc: Test UpdateLastStandardIndex updates standard index
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, UpdateLastStandardIndexTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);
    navDestination->SetNavDestinationMode(NavDestinationMode::STANDARD);

    auto stack = navigationPattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("test", navDestination);

    navigation->UpdateLastStandardIndex();
    EXPECT_EQ(navigation->GetLastStandardIndex(), 0);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CleanHideNodesTest001
 * @tc.desc: Test CleanHideNodes clears hide nodes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CleanHideNodesTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    navigation->CleanHideNodes();
    auto hideNodes = navigation->GetHideNodes();
    EXPECT_TRUE(hideNodes.empty());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetUseHomeDestinatoinTest001
 * @tc.desc: Test SetUseHomeDestinatoin and GetUseHomeDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetUseHomeDestinatoinTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->SetUseHomeDestinatoin(true);
    auto useHomeDestination = navigation->GetUseHomeDestination();
    ASSERT_TRUE(useHomeDestination.has_value());
    EXPECT_TRUE(useHomeDestination.value());

    navigation->SetUseHomeDestinatoin(false);
    useHomeDestination = navigation->GetUseHomeDestination();
    ASSERT_TRUE(useHomeDestination.has_value());
    EXPECT_FALSE(useHomeDestination.value());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetIsModeChangeTest001
 * @tc.desc: Test SetIsModeChange and GetIsModeChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetIsModeChangeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->SetIsModeChange(true);
    EXPECT_TRUE(navigation->GetIsModeChange());

    navigation->SetIsModeChange(false);
    EXPECT_FALSE(navigation->GetIsModeChange());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetNeedSetInvisibleTest001
 * @tc.desc: Test SetNeedSetInvisible and GetNeedSetInvisible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetNeedSetInvisibleTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->SetNeedSetInvisible(true);
    EXPECT_TRUE(navigation->GetNeedSetInvisible());

    navigation->SetNeedSetInvisible(false);
    EXPECT_FALSE(navigation->GetNeedSetInvisible());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetDoingModeSwitchAnimationFlagTest001
 * @tc.desc: Test SetDoingModeSwitchAnimationFlag and IsOnModeSwitchAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetDoingModeSwitchAnimationFlagTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->SetDoingModeSwitchAnimationFlag(true);
    EXPECT_TRUE(navigation->IsOnModeSwitchAnimation());

    navigation->SetDoingModeSwitchAnimationFlag(false);
    EXPECT_FALSE(navigation->IsOnModeSwitchAnimation());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CleanPushAnimationsTest001
 * @tc.desc: Test CleanPushAnimations clears push animations
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CleanPushAnimationsTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->CleanPushAnimations();
    auto& pushAnimations = navigation->GetPushAnimations();
    EXPECT_TRUE(pushAnimations.empty());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CleanPopAnimationsTest001
 * @tc.desc: Test CleanPopAnimations clears pop animations
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CleanPopAnimationsTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->CleanPopAnimations();
    auto& popAnimations = navigation->GetPopAnimations();
    EXPECT_TRUE(popAnimations.empty());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ReduceModeSwitchAnimationCntTest001
 * @tc.desc: Test ReduceModeSwitchAnimationCnt decreases counter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ReduceModeSwitchAnimationCntTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->IncreaseModeSwitchAnimationCnt();
    navigation->IncreaseModeSwitchAnimationCnt();
    EXPECT_EQ(navigation->GetModeSwitchAnimationCnt(), 2);

    navigation->ReduceModeSwitchAnimationCnt();
    EXPECT_EQ(navigation->GetModeSwitchAnimationCnt(), 1);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: IncreaseModeSwitchAnimationCntTest001
 * @tc.desc: Test IncreaseModeSwitchAnimationCnt increases counter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, IncreaseModeSwitchAnimationCntTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->IncreaseModeSwitchAnimationCnt();
    EXPECT_EQ(navigation->GetModeSwitchAnimationCnt(), 1);

    navigation->IncreaseModeSwitchAnimationCnt();
    EXPECT_EQ(navigation->GetModeSwitchAnimationCnt(), 2);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetNavigationPathInfoTest001
 * @tc.desc: Test SetNavigationPathInfo and GetNavigationPathInfo
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetNavigationPathInfoTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    const std::string moduleName = "testModule";
    const std::string pagePath = "test/page";

    navigation->SetNavigationPathInfo(moduleName, pagePath);
    EXPECT_EQ(navigation->GetNavigationPathInfo(), pagePath);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetRecoverableTest001
 * @tc.desc: Test SetRecoverable and CanRecovery
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetRecoverableTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->SetRecoverable(true);
    EXPECT_FALSE(navigation->CanRecovery());

    navigation->SetNavigationPathInfo("module", "path");
    navigation->OnInspectorIdUpdate("testId");
    EXPECT_TRUE(navigation->CanRecovery());

    navigation->SetRecoverable(false);
    EXPECT_FALSE(navigation->CanRecovery());
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetContentAndGetContentNodeTest001
 * @tc.desc: Test SetContentNode and GetContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetContentAndGetContentNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto contentNode = FrameNode::CreateFrameNode(
        "content", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetContentNode(contentNode);

    auto result = navigation->GetContentNode();
    EXPECT_EQ(result, contentNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetDividerAndGetDividerNodeTest001
 * @tc.desc: Test SetDividerNode and GetDividerNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetDividerAndGetDividerNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto dividerNode = FrameNode::CreateFrameNode(
        "divider", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetDividerNode(dividerNode);

    auto result = navigation->GetDividerNode();
    EXPECT_EQ(result, dividerNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetDragBarAndGetDragBarNodeTest001
 * @tc.desc: Test SetDragBarNode and GetDragBarNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetDragBarAndGetDragBarNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto dragBarNode = FrameNode::CreateFrameNode(
        "dragBar", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetDragBarNode(dragBarNode);

    auto result = navigation->GetDragBarNode();
    EXPECT_EQ(result, dragBarNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetPrimaryContentAndGetPrimaryContentNodeTest001
 * @tc.desc: Test SetPrimaryContentNode and GetPrimaryContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetPrimaryContentAndGetPrimaryContentNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto primaryContentNode = FrameNode::CreateFrameNode(
        "primaryContent", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetPrimaryContentNode(primaryContentNode);

    auto result = navigation->GetPrimaryContentNode();
    EXPECT_EQ(result, primaryContentNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetForceSplitPlaceHolderAndGetForceSplitPlaceHolderNodeTest001
 * @tc.desc: Test SetForceSplitPlaceHolderNode and GetForceSplitPlaceHolderNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetForceSplitPlaceHolderAndGetForceSplitPlaceHolderNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto forceSplitPlaceHolderNode = FrameNode::CreateFrameNode(
        "placeholder", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetForceSplitPlaceHolderNode(forceSplitPlaceHolderNode);

    auto result = navigation->GetForceSplitPlaceHolderNode();
    EXPECT_EQ(result, forceSplitPlaceHolderNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetRelatedPageDestAndGetRelatedPageDestNodeTest001
 * @tc.desc: Test SetRelatedPageDestNode and GetRelatedPageDestNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetRelatedPageDestAndGetRelatedPageDestNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto relatedPageDestNode = FrameNode::CreateFrameNode(
        "relatedPage", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetRelatedPageDestNode(relatedPageDestNode);

    auto result = navigation->GetRelatedPageDestNode();
    EXPECT_EQ(result, relatedPageDestNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetNavBarSetAndGetNavBarNodeTest001
 * @tc.desc: Test SetNavBarNode and GetNavBarNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetNavBarSetAndGetNavBarNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto navBarNode = FrameNode::CreateFrameNode(
        "navBar", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetNavBarNode(navBarNode);

    auto result = navigation->GetNavBarNode();
    EXPECT_EQ(result, navBarNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetHomeDestinationNodeTest001
 * @tc.desc: Test GetHomeDestinationationNode returns home destination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetHomeDestinationNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto homeDestinationNode = FrameNode::CreateFrameNode(
        "homeDest", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->customHomeDestination_ = homeDestinationNode;

    auto result = navigation->GetHomeDestinationNode();
    EXPECT_EQ(result, homeDestinationNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetCurIdTest001
 * @tc.desc: Test GetCurId returns current navigation ID
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetCurIdTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    const std::string testId = { "testNavigationId" };
    navigation->curId_ = testId;

    auto result = navigation->GetCurId();
    EXPECT_EQ(result, testId);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetPreLastStandardIndexTest001
 * @tc.desc: Test GetPreLastStandardIndex returns pre last standard index
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetPreLastStandardIndexTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->preLastStandardIndex_ = 5;
    EXPECT_EQ(navigation->GetPreLastStandardIndex(), 5);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetLastStandardIndexTest001
 * @tc.desc: Test GetLastStandardIndex returns last standard index
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetLastStandardIndexTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->lastStandardIndex_ = 3;
    EXPECT_EQ(navigation->GetLastStandardIndex(), 3);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: SetPlaceholderContentAndGetPlaceholderContentNodeTest001
 * @tc.desc: Test SetPlaceholderContentNode and GetPlaceholderContentNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, SetPlaceholderContentAndGetPlaceholderContentNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto placeholderContentNode = FrameNode::CreateFrameNode(
        "placeholderContent", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetPlaceholderContentNode(placeholderContentNode);

    auto result = navigation->GetPlaceholderContentNode();
    EXPECT_EQ(result, placeholderContentNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ResetSplitPlaceholderTest001
 * @tc.desc: Test ResetSplitPlaceholder clears split placeholder
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ResetSplitPlaceholderTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto placeholderContentNode = FrameNode::CreateFrameNode(
        "placeholderContent", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigation->SetPlaceholderContentNode(placeholderContentNode);
    navigation->splitPlaceholder_ = placeholderContentNode;

    navigation->ResetSplitPlaceholder();
    EXPECT_EQ(navigation->GetPlaceholderContentNode(), nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: GetParentDestinationNodeTest001
 * @tc.desc: Test GetParentDestinationNode returns parent destination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, GetParentDestinationNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto parentDestNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigation->parentDestinationNode_ = parentDestNode;

    auto result = navigation->GetParentDestinationNode().Upgrade();
    EXPECT_EQ(result, parentDestNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: OnInspectorIdUpdateTest001
 * @tc.desc: Test OnInspectorIdUpdate updates inspector ID
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, OnInspectorIdUpdateTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    const std::string testId = "testInspectorId";
    navigation->OnInspectorIdUpdate(testId);

    EXPECT_EQ(navigation->GetCurId(), testId);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: AddChildToGroupTest001
 * @tc.desc: Test AddChildToGroup adds child to group
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, AddChildToGroupTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto childNode = FrameNode::CreateFrameNode(
        "child", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    navigation->AddChildToGroup(childNode, 0);
    ASSERT_NE(childNode, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: ResetSystemAnimationPropertiesTest001
 * @tc.desc: Test ResetSystemAnimationProperties resets animation properties
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, ResetSystemAnimationPropertiesTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);

    navigation->ResetSystemAnimationProperties(navDestination);
    ASSERT_NE(navDestination, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: PreNodeFinishCallbackTest001
 * @tc.desc: Test PreNodeFinishCallback handles pre node finish
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, PreNodeFinishCallbackTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto preNode = FrameNode::CreateFrameNode(
        "preNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    navigation->PreNodeFinishCallback(preNode);
    ASSERT_NE(preNode, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: FireHideNodeChangeTest001
 * @tc.desc: Test FireHideNodeChange fires hide node change event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, FireHideNodeChangeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_HIDE);
    ASSERT_NE(navigation, nullptr);
    navigation->FireHideNodeChange(NavDestinationLifecycle::ON_HIDE);
    ASSERT_NE(navigation, nullptr);
    navigation->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_DISAPPEAR);
    ASSERT_NE(navigation, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: OnDetachFromMainTreeTest001
 * @tc.desc: Test OnDetachFromMainTree handles detach from main tree
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, OnDetachFromMainTreeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);

    navigation->OnDetachFromMainTree(true, context.GetRawPtr());
    ASSERT_NE(navigation, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: LoadRelatedPageIfNeededTest001
 * @tc.desc: Test LoadRelatedPageIfNeeded loads related page
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, LoadRelatedPageIfNeededTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    navigation->LoadRelatedPageIfNeeded();
    ASSERT_NE(navigation, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: AddDestinationNodeTest001
 * @tc.desc: Test AddDestinationNode adds destination node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, AddDestinationNodeTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    auto destNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(destNode, nullptr);

    navigation->AddDestinationNode(destNode);

    auto result = navigation->GetParentDestinationNode().Upgrade();
    EXPECT_EQ(result, destNode);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

/*
 * @tc.name: CheckLanguageDirectionTest001
 * @tc.desc: Test CheckLanguageDirection checks language direction
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, CheckLanguageDirectionTest001, TestSize.Level1)
{
    NavigationGroupNodeTestNg::SetUpTestCase();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);

    ASSERT_NE(navigation, nullptr);
    NavigationGroupNodeTestNg::TearDownTestCase();
}

} // namespace OHOS::Ace::NG