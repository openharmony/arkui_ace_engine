/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "test/mock/base/mock_task_executor.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
} // namespace

class NavigationAnimationTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string name);
    static RefPtr<NavigationGroupNode> InitNavigation();
};

void NavigationAnimationTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto context = MockPipelineContext::GetCurrent();
    if (context) {
        context->stageManager_ = nullptr;
    }
}

void NavigationAnimationTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationAnimationTest::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
{
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { width, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

void NavigationAnimationTest::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

RefPtr<NavDestinationGroupNode> NavigationAnimationTest::CreateDestination(const std::string name)
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName(name);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = name;
    context->SetNavPathInfo(pathInfo);
    pattern->SetNavDestinationContext(context);
    return frameNode;
}

RefPtr<NavigationGroupNode> NavigationAnimationTest::InitNavigation()
{
    auto context = MockPipelineContext::GetCurrent();
    if (!context) {
        return nullptr;
    }
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    return navigationNode;
}

/**
 * @tc.name: NavigationInteractiveTest
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, NavigationInteractiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navigation and navigation stack
    */
    auto navigationNode = InitNavigation();
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps.step2.create navDestination node pageA
    */
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationTransition([](const RefPtr<NavDestinationContext>& preContext,
        const RefPtr<NavDestinationContext>& topContext, NavigationOperation operation) ->NavigationTransition {
        NavigationTransition transition;
        transition.isValid = true;
        transition.interactive = true;
        transition.transition = [](const RefPtr<NavigationTransitionProxy>& proxy) {};
        return transition;
    });

    /**
     * @tc.steps: step3. add pageA and sync navigation stack
     * @tc.expected: step3. current interactive is true
     *
     */
    auto stack = navigationPattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    auto pageA = CreateDestination("pageA");
    stack->Add("pageA", pageA);
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_NE(navigationPattern->GetTopNavigationProxy(), nullptr);
    EXPECT_TRUE(navigationPattern->GetTopNavigationProxy()->GetInteractive());

    /**
     * @tc.steps: step3. set navigation transition callback, set interactive value false
    */
    navigationPattern->GetTopNavigationProxy()->hasFinished_ = true;
    navigationPattern->isFinishInteractiveAnimation_ = true;
    navigationPattern->SetNavigationTransition([](const RefPtr<NavDestinationContext>& preContext,
        const RefPtr<NavDestinationContext>& topContext, NavigationOperation operation) -> NavigationTransition {
            NavigationTransition transition;
            transition.isValid = true;
            transition.interactive = false;
            transition.transition = [](const RefPtr<NavigationTransitionProxy>& proxy) {};
            return transition;
        });

    /**
     * @tc.steps: step4. add pageA and sync navigation stack
     * @tc.expected: step4. current interactive value is false
    */
    auto destinationB = CreateDestination("pageB");
    stack->Add("pageB", destinationB);
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_NE(navigationPattern->GetTopNavigationProxy(), nullptr);
    EXPECT_FALSE(navigationPattern->GetTopNavigationProxy()->GetInteractive());
}

/**
 * @tc.name: NavigationInteractiveTest
 * @tc.desc: Test cancel animation is correct or not
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, NavigationFinishAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation and navigation stack
    */
    auto navigationNode = InitNavigation();
    ASSERT_NE(navigationNode, nullptr);

    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set interactive false
    */
    pattern->SetNavigationTransition([](const RefPtr<NavDestinationContext>& preContext,
        const RefPtr<NavDestinationContext>& topContext, NavigationOperation operation) -> NavigationTransition {
        NavigationTransition transition;
        transition.isValid = true;
        transition.interactive = false;
        transition.transition = [](const RefPtr<NavigationTransitionProxy>& proxy) {};
        return transition;
    });
    pattern->isCustomAnimation_ = true;

    /**
     * @tc.steps: step2. push pageA, and sync navigation stack, adn fire cancelAnimation
     * @tc.expected: step3. current top stack is pageA
    */
    auto navDestinationA = CreateDestination("pageA");
    ASSERT_NE(navDestinationA, nullptr);
    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("pageA", navDestinationA);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_NE(pattern->GetTopNavigationProxy(), nullptr);
    pattern->GetTopNavigationProxy()->FireCancelAnimation();
    auto targetPage = stack->Get();
    EXPECT_TRUE(targetPage == navDestinationA);
    ASSERT_EQ(stack->Size(), 1);
}

/**
 * @tc.name: NavigationInteractiveTest
 * @tc.desc: Test interactive value in cancel transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, NavigationCancelAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation node and init navigation stack
    */
    auto navigationNode = InitNavigation();
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2. set interactive value true
    */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    pattern->SetNavigationTransition([](const RefPtr<NavDestinationContext>& preContext,
        const RefPtr<NavDestinationContext> topContext,
        NavigationOperation operation) -> NavigationTransition {
            NavigationTransition transition;
            transition.interactive = true;
            transition.isValid = true;
            transition.transition = [] (const RefPtr<NavigationTransitionProxy>& proxy) {};
            return transition;
    });
    pattern->isCustomAnimation_ = true;

    /**
     * @tc.steps: step3. create destination A and sync navigation
    */
    auto stack = pattern->GetNavigationStack();
    EXPECT_NE(stack, nullptr);
    stack->UpdateRecoveryList();
    auto destinationA = CreateDestination("pageA");
    stack->Add("pageA", destinationA);
    pattern->UpdateNavPathList();
    pattern->RefreshNavDestination();
    ASSERT_NE(pattern->GetTopNavigationProxy(), nullptr);
    pattern->GetTopNavigationProxy()->CancelInteractiveAnimation();
    ASSERT_EQ(stack->Size(), 0);
}

/**
 * @tc.name: NavigationInteractiveTest
 * @tc.desc: Test interactive value in cancel transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, NavigationFinishAnimation004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation and init navigation stack
    */
    auto navigationNode = InitNavigation();
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2. set interactive false and timeout 0
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationTransition([](const RefPtr<NavDestinationContext>& preContext,
        const RefPtr<NavDestinationContext>& topContext,
        NavigationOperation operation) -> NavigationTransition {
        NavigationTransition transition;
        transition.isValid = true;
        transition.interactive = true;
        transition.timeout = 0;
        auto onTransition = [](const RefPtr<NavigationTransitionProxy>& proxy) {
        };
        transition.transition = std::move(onTransition);
        transition.endCallback = [](bool isSuccess) {};
        return transition;
    });
    pattern->isCustomAnimation_ = true;

    /**
     * @tc.steps:step3. create navDestination node, and push node to stack
     * @tc.expected: step3. get sync stack
    */
    auto navDestinationA = CreateDestination("pageA");
    ASSERT_NE(navDestinationA, nullptr);
    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("pageA", navDestinationA);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 1);
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarLayoutProperty = navBar->GetLayoutProperty();
    ASSERT_NE(navBarLayoutProperty, nullptr);
    ASSERT_NE(navBarLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    auto topDestination = AceType::DynamicCast<FrameNode>(stack->Get());
    ASSERT_NE(topDestination, nullptr);
    auto navDestinationAProperty = topDestination->GetLayoutProperty();
    ASSERT_NE(navDestinationAProperty, nullptr);
    ASSERT_EQ(navDestinationAProperty->GetVisibilityValue(), VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateTextNodeListAsRenderGroup
 * @tc.desc: Test NavDestinationGroupNode::UpdateTextNodeListAsRenderGroup
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, UpdateTextNodeListAsRenderGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    /**
     * @tc.steps: step2. call the target function.
     */
    navDestinationNode->UpdateTextNodeListAsRenderGroup(true, proxy);
}

/**
 * @tc.name: UpdateTextNodeListAsRenderGroup
 * @tc.desc: Test NavDestinationGroupNode::UpdateTextNodeListAsRenderGroup
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, UpdateTextNodeListAsRenderGroup002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    /**
     * @tc.steps: step2. call the target function.
     */
    navDestinationNode->UpdateTextNodeListAsRenderGroup(false, proxy);
}

/**
 * @tc.name: CollectTextNodeAsRenderGroup
 * @tc.desc: Test NavDestinationGroupNode::CollectTextNodeAsRenderGroup
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, CollectTextNodeAsRenderGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    /**
     * @tc.steps: step2. create contentNode for navDestination and add text node to content node.
     */
    auto navDestinationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 1,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(navDestinationContentNode, nullptr);
    navDestinationNode->AddChild(navDestinationContentNode);
    navDestinationNode->SetContentNode(navDestinationContentNode);
    auto textNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, 66, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    navDestinationContentNode->AddChild(textNode);
    /**
     * @tc.steps: step3. call the target function.
     */
    navDestinationNode->CollectTextNodeAsRenderGroup(true);
    ASSERT_NE(navDestinationNode->textNodeList_.size(), 0);
}

/**
 * @tc.name: ReleaseTextNodeList
 * @tc.desc: Test NavDestinationGroupNode::ReleaseTextNodeList
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, ReleaseTextNodeList001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestination.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 77, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    /**
     * @tc.steps: step2. create contentNode for navDestination and add text node to content node.
     */
    auto navDestinationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 1,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(navDestinationContentNode, nullptr);
    navDestinationNode->AddChild(navDestinationContentNode);
    navDestinationNode->SetContentNode(navDestinationContentNode);
    auto textNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, 88, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    navDestinationContentNode->AddChild(textNode);
    /**
     * @tc.steps: step3. collect text nodes before release.
     */
    navDestinationNode->CollectTextNodeAsRenderGroup(true);
    ASSERT_NE(navDestinationNode->textNodeList_.size(), 0);
    /**
     * @tc.steps: step4. call the target function.
     */
    navDestinationNode->ReleaseTextNodeList();
    ASSERT_EQ(navDestinationNode->textNodeList_.size(), 0);
}
}; // namespace OHOS::Ace::NG