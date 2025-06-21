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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
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
 * @tc.name: StartDialogTransitionPopTest001
 * @tc.desc: Test dialog pop system transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, StartDialogTransitionPopTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2. add nodes into preNavlist
     * @tc.expected: step2. size of preNavlist size is one
     */
    auto preDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    preDestination->SetIndex(0);
    std::vector<std::pair<std::string, WeakPtr<UINode>>> preNodes;
    preNodes.emplace_back(std::make_pair("pageOne", WeakPtr<UINode>(preDestination)));
    navigationStack->navPathListBeforePoped_ = preNodes;
    EXPECT_EQ(navigationStack->navPathListBeforePoped_.size(), 1);

    /**
     * @tc.steps: step3. test dialog pop transition
     * @tc.expected: step3. current transition size is one
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    navigationNode->StartDialogtransition(preDestination, nullptr, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 1);
}

/**
 * @tc.name: StartDialogTransitionPopTest002
 * @tc.desc: Test dialog pop system transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, StartDialogTransitionPopTest002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.set index and push Standrd and dialog into preNavlist
     * @tc.expected: size of preNavlist size is two
     */
    auto navDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationA->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationA->SetIndex(0);
    auto navDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationB->SetIndex(1);
    std::vector<std::pair<std::string, WeakPtr<UINode>>> preNodes;
    preNodes.emplace_back(std::make_pair("pageOne", WeakPtr<UINode>(navDestinationA)));
    preNodes.emplace_back(std::make_pair("pageTwo", WeakPtr<UINode>(navDestinationB)));
    navigationStack->navPathListBeforePoped_ = preNodes;
    EXPECT_EQ(navigationStack->navPathListBeforePoped_.size(), 2);

    /**
     * @tc.steps: step3. test dialog pop transition, pop std and dialog at the same time
     * @tc.expected: step3. current transition size is one
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    navigationNode->StartDialogtransition(navDestinationB, navDestinationA, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 1);
}

/**
 * @tc.name: StartDialogTransitionPopTest003
 * @tc.desc: Test dialog pop system transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, StartDialogTransitionPopTest003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.set index and push Standrd and dialog into preNavlist
     * @tc.expected: size of preNavlist size is three.
     */
    auto navDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationA->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationA->SetIndex(0);
    auto navDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationB->SetIndex(1);
    auto navDestinationC = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationC->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationC->SetIndex(2);
    std::vector<std::pair<std::string, WeakPtr<UINode>>> preNodes;
    preNodes.emplace_back(std::make_pair("pageOne", WeakPtr<UINode>(navDestinationA)));
    preNodes.emplace_back(std::make_pair("pageTwo", WeakPtr<UINode>(navDestinationB)));
    preNodes.emplace_back(std::make_pair("pageThree", WeakPtr<UINode>(navDestinationC)));
    navigationStack->navPathListBeforePoped_ = preNodes;
    EXPECT_EQ(navigationStack->navPathListBeforePoped_.size(), 3);

    /**
     * @tc.steps: step3. test dialog pop transition abd pop std and dialog at the same time.
     * @tc.expected: step3. current transition animation size is one.
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    navigationNode->StartDialogtransition(navDestinationC, navDestinationA, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 1);
}

/**
 * @tc.name: StartDialogTransitionPushTest001
 * @tc.desc: Test dialog push system transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, StartDialogTransitionPushTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.push page A to navDestination stack
     */
    auto curDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    curDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("dialog", curDestination);
    curDestination->SetIndex(0);

    /**
     * @tc.steps: step3. test push dialog animation.
     * @tc.expected: step3. current transition animation size is one.
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    navigationNode->StartDialogtransition(nullptr, curDestination, true);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 1);
}

/**
 * @tc.name: StartDialogTransitionPushTest002
 * @tc.desc: Test dialog push system transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, StartDialogTransitionPushTest002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2. set index and push std and dialog to stack
     */
    auto preDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preDestination->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationStack->Add("standard", preDestination);
    preDestination->SetIndex(0);
    auto curDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    curDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("dialog", curDestination);
    curDestination->SetIndex(1);

    /**
     * @tc.steps: step3. test push dialog animation.
     * @tc.expected: step3. current transition animation size is one.
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    navigationNode->StartDialogtransition(preDestination, curDestination, true);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 1);
}

/**
 * @tc.name: StartDialogTransitionPushTest003
 * @tc.desc: Test dialog push system transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, StartDialogTransitionPushTest003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2. set index and push std and two dialogs to the stack
     */
    auto preDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preDestination->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationStack->Add("standard", preDestination);
    preDestination->SetIndex(0);
    auto curDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    curDestinationA->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("dialogA", curDestinationA);
    curDestinationA->SetIndex(1);
    auto curDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    curDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("dialogB", curDestinationB);
    curDestinationB->SetIndex(2);

    /**
     * @tc.steps: step3. test push two dialogs animation.
     * @tc.expected: step3. current transition animation size is one.
     */
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    navigationNode->StartDialogtransition(preDestination, curDestinationB, true);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 1);
}

/**
 * @tc.name: TransitionWithDialogPop001
 * @tc.desc: Test dialog pop system transition with std animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, TransitionWithDialogPop001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 1, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step2. create and push navdestination nodes into stack
     */
    auto stdNavdestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(stdNavdestination, nullptr);
    stdNavdestination->SetNavDestinationMode(NavDestinationMode::STANDARD);
    stdNavdestination->SetParent(WeakPtr<UINode>(navigationContentNode));
    auto dialogDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dialogDestination, nullptr);
    dialogDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    dialogDestination->SetParent(WeakPtr<UINode>(navigationContentNode));
    std::vector<std::pair<std::string, WeakPtr<UINode>>> preNodes;
    preNodes.emplace_back(std::make_pair("pageOne", WeakPtr<UINode>(stdNavdestination)));
    preNodes.emplace_back(std::make_pair("pageTwo", WeakPtr<UINode>(dialogDestination)));
    navigationStack->navPathListBeforePoped_ = preNodes;

    /**
     * @tc.steps: step3. test pop one std and one dialog at the same time.
     * @tc.expected: step3. poped nodes' properties should match exit pop condition.
     */
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = -1;
    bool isNavBar = true;
    navigationNode->TransitionWithDialogPop(dialogDestination, navBarNode, isNavBar);
    EXPECT_FALSE(navigationNode->GetNeedSetInvisible());
    EXPECT_EQ(stdNavdestination->GetTransitionType(), PageTransitionType::EXIT_POP);
    EXPECT_FALSE(stdNavdestination->IsOnAnimation());
    EXPECT_EQ(dialogDestination->GetTransitionType(), PageTransitionType::EXIT_POP);
    EXPECT_FALSE(dialogDestination->IsOnAnimation());
}

/**
 * @tc.name: TransitionWithDialogPop002
 * @tc.desc: Test dialog pop system transition with std animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, TransitionWithDialogPop002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps: step2. create navdestination and set properties
     */
    auto stdNavdestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(stdNavdestinationA, nullptr);
    stdNavdestinationA->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationStack->Add("standardA", stdNavdestinationA);
    auto dialogDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dialogDestinationA, nullptr);
    dialogDestinationA->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("dialogA", dialogDestinationA);
    auto stdNavdestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    stdNavdestinationB->SetNavDestinationMode(NavDestinationMode::STANDARD);
    stdNavdestinationB->SetParent(WeakPtr<UINode>(navigationContentNode));
    auto dialogDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    dialogDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    dialogDestinationB->SetParent(WeakPtr<UINode>(navigationContentNode));

    /**
     * @tc.steps: step3. add navdestination nodes into stack
     */
    std::vector<std::pair<std::string, WeakPtr<UINode>>> preNodes;
    preNodes.emplace_back(std::make_pair("pageOne", WeakPtr<UINode>(stdNavdestinationA)));
    preNodes.emplace_back(std::make_pair("pageTwo", WeakPtr<UINode>(dialogDestinationA)));
    preNodes.emplace_back(std::make_pair("pageThree", WeakPtr<UINode>(stdNavdestinationB)));
    preNodes.emplace_back(std::make_pair("pageFour", WeakPtr<UINode>(dialogDestinationB)));
    navigationStack->navPathListBeforePoped_ = preNodes;
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();

    /**
     * @tc.steps: step4. test pop one std and one dialog at the same time.
     * @tc.expected: step4. properties should match enter and exit pop condition.
     */
    navigationNode->preLastStandardIndex_ = 2;
    navigationNode->lastStandardIndex_ = 0;
    navigationNode->TransitionWithDialogPop(dialogDestinationA, dialogDestinationB);
    EXPECT_EQ(stdNavdestinationA->GetTransitionType(), PageTransitionType::ENTER_POP);
    EXPECT_EQ(stdNavdestinationB->GetTransitionType(), PageTransitionType::EXIT_POP);
    EXPECT_FALSE(stdNavdestinationB->IsOnAnimation());
}

/**
 * @tc.name: TransitionWithDialogPop002
 * @tc.desc: Test dialog push system transition with std animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, TransitionWithDialogPush001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 1, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step2. create navdestination and add into stack
     */
    auto stdNavdestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(stdNavdestinationB, nullptr);
    stdNavdestinationB->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationStack->Add("standardB", stdNavdestinationB);
    stdNavdestinationB->SetIndex(0);
    auto dialogDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dialogDestinationB, nullptr);
    dialogDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("dialogB", dialogDestinationB);
    dialogDestinationB->SetIndex(1);

    /**
     * @tc.steps: step3. test push one std and one dialog at the same time.
     * @tc.expected: step3. properties should match enter push condition.
     */
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationNode->preLastStandardIndex_ = -1;
    navigationNode->lastStandardIndex_ = 0;
    navigationNode->TransitionWithDialogPush(navBarNode, dialogDestinationB);
    EXPECT_EQ(stdNavdestinationB->GetTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_EQ(dialogDestinationB->GetTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_FALSE(stdNavdestinationB->IsOnAnimation());
    EXPECT_FALSE(dialogDestinationB->IsOnAnimation());
}

/**
 * @tc.name: TransitionWithDialogPush002
 * @tc.desc: Test dialog push system transition with std animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, TransitionWithDialogPush002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create navigation stack
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps: step2. create navdestination and add into stack
     */
    std::vector<NavDestinationMode> srcVec = { NavDestinationMode::STANDARD, NavDestinationMode::DIALOG,
        NavDestinationMode::STANDARD, NavDestinationMode::DIALOG };
    std::vector<std::string> names = { "A", "B", "C", "D" };
    const int32_t testNumber = 4;
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navdestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
        ASSERT_NE(navdestination, nullptr);
        navigationStack->Add(names[index], navdestination);
        navdestination->SetIndex(index);
    }
    auto stdNavdestinationA = AceType::DynamicCast<NavDestinationGroupNode>(navigationStack->Get(0));
    auto dialogDestinationA = AceType::DynamicCast<NavDestinationGroupNode>(navigationStack->Get(1));
    auto stdNavdestinationB = AceType::DynamicCast<NavDestinationGroupNode>(navigationStack->Get(2));
    auto dialogDestinationB = AceType::DynamicCast<NavDestinationGroupNode>(navigationStack->Get(3));

    /**
     * @tc.steps: step3. add navdestination nodes into preNavlist
     */
    std::vector<std::pair<std::string, WeakPtr<UINode>>> preNodes;
    preNodes.emplace_back(std::make_pair("pageOne", WeakPtr<UINode>(stdNavdestinationA)));
    preNodes.emplace_back(std::make_pair("pageTwo", WeakPtr<UINode>(dialogDestinationA)));
    navigationStack->navPathListBeforePoped_ = preNodes;
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();

    /**
     * @tc.steps: step4. test push one std and one dialog at the same time and
     *  one std and one dialog do exit push at the same time.
     * @tc.expected: step4. properties should match enter and exit push condition.
     */
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 2;
    navigationNode->TransitionWithDialogPush(dialogDestinationA, dialogDestinationB);
    EXPECT_EQ(stdNavdestinationA->GetTransitionType(), PageTransitionType::EXIT_PUSH);
    EXPECT_EQ(stdNavdestinationA->GetTransitionType(), PageTransitionType::EXIT_PUSH);
    EXPECT_EQ(stdNavdestinationB->GetTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_EQ(dialogDestinationB->GetTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_FALSE(stdNavdestinationA->IsOnAnimation());
    EXPECT_FALSE(stdNavdestinationA->IsOnAnimation());
    EXPECT_FALSE(stdNavdestinationB->IsOnAnimation());
    EXPECT_FALSE(dialogDestinationB->IsOnAnimation());
}

/**
 * @tc.name: SystemAnimation001
 * @tc.desc: Test navbar system animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, SystemAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navbar node
     */
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 1, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    navBarNode->SetTitleBarNode(titleBarNode);

    /**
     * @tc.steps: step2. do navbar system transition
     * @tc.expected: step2. properties should match enter and exit animation condition.
     */
    navBarNode->SystemTransitionPopStart(true);
    EXPECT_EQ(navBarNode->GetTransitionType(), PageTransitionType::ENTER_POP);
    navBarNode->SystemTransitionPushStart(false);
    EXPECT_EQ(navBarNode->GetTransitionType(), PageTransitionType::EXIT_PUSH);
}

/**
 * @tc.name: SystemAnimation002
 * @tc.desc: Test navdestination system animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, SystemAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navdestination node and titlebar node
     */
    auto navdestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navdestination, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    navdestination->SetTitleBarNode(titleBarNode);

    /**
     * @tc.steps: step2. do navdestination enter push animation
     * @tc.expected: step2. properties should match enter push condition.
     */
    navdestination->SystemTransitionPushStart(true);
    EXPECT_EQ(navdestination->GetTransitionType(), PageTransitionType::ENTER_PUSH);
    EXPECT_TRUE(navdestination->IsOnAnimation());
    navdestination->SystemTransitionPushFinish(true, -1);
    EXPECT_FALSE(navdestination->IsOnAnimation());

    /**
     * @tc.steps: step3. do navdestination exit push animation
     * @tc.expected: step2. properties should match exit push condition.
     */
    navdestination->SystemTransitionPushStart(false);
    EXPECT_EQ(navdestination->GetTransitionType(), PageTransitionType::EXIT_PUSH);
    EXPECT_TRUE(navdestination->IsOnAnimation());
    navdestination->SystemTransitionPushFinish(false, -1);
    EXPECT_FALSE(navdestination->IsOnAnimation());
    auto navdestinationLayoutProperty = navdestination->GetLayoutProperty();
    ASSERT_NE(navdestinationLayoutProperty, nullptr);
}

/**
 * @tc.name: SystemAnimation003
 * @tc.desc: Test navdestination system animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, SystemAnimation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navdestination node and titlebar node
     */
    auto navdestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navdestination, nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    navdestination->SetTitleBarNode(titleBarNode);

    /**
     * @tc.steps: step2. do navdestination enter or exit pop animation
     * @tc.expected: step2. properties should match enter or exit pop condition.
     */
    navdestination->SystemTransitionPopStart(true);
    EXPECT_EQ(navdestination->GetTransitionType(), PageTransitionType::ENTER_POP);
    navdestination->SystemTransitionPopStart(false);
    EXPECT_EQ(navdestination->GetTransitionType(), PageTransitionType::EXIT_POP);
    EXPECT_TRUE(navdestination->IsOnAnimation());
    navdestination->SystemTransitionPopFinish(-1);
    EXPECT_FALSE(navdestination->IsOnAnimation());
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(backButton, nullptr);
    titleBarNode->SetBackButton(backButton);
    auto titleBarNodeRender = titleBarNode->GetRenderContext();
}

/**
 * @tc.name: BackButtonOpacityAnimation
 * @tc.desc: Test NavDestinationGroupNode::BackButtonAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, OpacityAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 1, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBar = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    navDestinationNode->titleBarNode_ = titleBar;
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto backButtonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    titleBarNode->backButton_ = backButtonNode;
    ASSERT_NE(titleBarNode->GetBackButton(), nullptr);
    navDestinationNode->BackButtonAnimation(false);
    navDestinationNode->BackButtonAnimation(true);
}

/**
 * @tc.name: TitleOpacityAnimation
 * @tc.desc: Test NavDestinationGroupNode::TitleOpacityAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, OpacityAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 1, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBar = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    navDestinationNode->titleBarNode_ = titleBar;
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    navDestinationNode->TitleOpacityAnimation(false);
    navDestinationNode->TitleOpacityAnimation(true);
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

/**
 * @tc.name: DialogAnimation001
 * @tc.desc: Test NavDestinationGroupNode::DialogAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, DialogAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    MockPipelineContextGetTheme();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    /**
     * @tc.steps: step2. mock navdestination stack.
     */
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 1, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    /**
     * @tc.steps: step3. set pre-steps of animation.
     */
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    /**
     * @tc.steps: step4. if last standard id is not changed and new top navdestination is standard
     * @tc.expected: step4. there is no animation.
     */
    auto newTopNavdestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 1, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    newTopNavdestination->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationPattern->DialogAnimation(nullptr, newTopNavdestination, false, true);
    EXPECT_FALSE(newTopNavdestination->IsOnAnimation());
}

/**
 * @tc.name: DialogAnimation002
 * @tc.desc: Test NavDestinationGroupNode::DialogAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, DialogAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    MockPipelineContextGetTheme();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    NavigationModelNG navigationModel;
    navigationModel.Create();
    /**
     * @tc.steps: step2. mock navdestination stack.
     */
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step3. set pre-steps of animation.
     */
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto stack = navigationPattern->GetNavigationStack();
    stack->UpdateReplaceValue(1);
    /**
     * @tc.steps: step4. test dialog do replace animation
     * @tc.expected: step4. replace value should be updated to zero after replace animation.
     */
    auto preTopNavdestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 1, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto replaceNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 2, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preTopNavdestination->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navigationStack->Add("A", preTopNavdestination);
    navigationPattern->DialogAnimation(preTopNavdestination, replaceNode, true, true);
    EXPECT_EQ(stack->GetReplaceValue(), 0);
}

/**
 * @tc.name: IsNeedContentTransition
 * @tc.desc: Test NavDestinationGroupNode::IsNeedContentTransition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, IsNeedContentTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);

    auto navDestinationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 1,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(navDestinationContentNode, nullptr);
    navDestinationNode->AddChild(navDestinationContentNode);
    navDestinationNode->SetContentNode(navDestinationContentNode);
    auto textNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, 66, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    navDestinationContentNode->AddChild(textNode);

    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::DEFAULT);
    bool ret = navDestinationNode->IsNeedContentTransition();
    ASSERT_EQ(ret, true);
    navDestinationNode->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::CONTENT);
    ret = navDestinationNode->IsNeedContentTransition();
    ASSERT_EQ(ret, true);
    navDestinationNode->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::CONTENT);
    ret = navDestinationNode->IsNeedContentTransition();
    ASSERT_EQ(ret, true);
    navDestinationNode->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::NONE);
    ret = navDestinationNode->IsNeedContentTransition();
    ASSERT_EQ(ret, false);
}

/**
 * @tc.name: TransitionContentInValid
 * @tc.desc: Test NavDestinationGroupNode::TransitionContentInValid
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, TransitionContentInValid001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);

    auto navDestinationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 1,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(navDestinationContentNode, nullptr);
    navDestinationNode->AddChild(navDestinationContentNode);
    navDestinationNode->SetContentNode(navDestinationContentNode);
    auto textNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, 66, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    navDestinationContentNode->AddChild(textNode);

    navDestinationNode->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::NONE);
    bool ret = navDestinationNode->TransitionContentInValid();
    ASSERT_EQ(ret, true);

    navDestinationNode->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::CONTENT);
    ret = navDestinationNode->TransitionContentInValid();
    ASSERT_EQ(ret, false);

    navDestinationNode->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::CONTENT);
    ret = navDestinationNode->TransitionContentInValid();
    ASSERT_EQ(ret, false);
}

/**
 * @tc.name: IsNeedTitleTransition
 * @tc.desc: Test NavDestinationGroupNode::IsNeedTitleTransition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationAnimationTest, IsNeedTitleTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);

    auto navDestinationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 1,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(navDestinationContentNode, nullptr);
    navDestinationNode->AddChild(navDestinationContentNode);
    navDestinationNode->SetContentNode(navDestinationContentNode);
    auto textNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, 66, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    navDestinationContentNode->AddChild(textNode);

    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::DEFAULT);
    bool ret = navDestinationNode->IsNeedTitleTransition();
    ASSERT_EQ(ret, true);

    navDestinationNode->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::TITLE);
    ret = navDestinationNode->IsNeedTitleTransition();
    ASSERT_EQ(ret, true);

    navDestinationNode->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::TITLE);
    ret = navDestinationNode->IsNeedTitleTransition();
    ASSERT_EQ(ret, false);

    navDestinationNode->SetNavDestinationMode(NavDestinationMode::STANDARD);
    navDestinationNode->SetSystemTransitionType(NavigationSystemTransitionType::NONE);
    ret = navDestinationNode->IsNeedTitleTransition();
    ASSERT_EQ(ret, false);
}
}; // namespace OHOS::Ace::NG