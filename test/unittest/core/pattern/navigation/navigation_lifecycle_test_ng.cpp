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
#include "mock_navigation_route.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
} // namespace

class NavigationLifecycleTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string name);
    static void SetEvent(NavDestinationLifecycle lifecycle, int8_t expectValue,
        const RefPtr<FrameNode>& destinationNode, const RefPtr<MockNavigationStack>& stack);
    static RefPtr<NavigationGroupNode> GetOrCreateNavigationNode();
};

void NavigationLifecycleTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto context = MockPipelineContext::GetCurrent();
    if (context) {
        context->stageManager_ = nullptr;
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationLifecycleTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationLifecycleTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

RefPtr<NavigationGroupNode> NavigationLifecycleTestNg::GetOrCreateNavigationNode()
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    if (!navigationNode) {
        return nullptr;
    }
    auto context = PipelineContext::GetCurrentContext();
    if (!context) {
        return nullptr;
    }
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    if (!pattern) {
        return nullptr;
    }
    pattern->SetNavigationMode(NavigationMode::STACK);
    return navigationNode;
}

void NavigationLifecycleTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

void NavigationLifecycleTestNg::SetEvent(NavDestinationLifecycle lifecycle, int8_t expectValue,
    const RefPtr<FrameNode>& destinationNode, const RefPtr<MockNavigationStack>& stack)
{
    auto eventHub = destinationNode->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_NE(eventHub, nullptr);
    std::function<void()>&& callback = [stack = stack, expectValue = expectValue]() {
        auto lifecycleIndex = stack->GetLifecycleIndex();
        EXPECT_EQ(lifecycleIndex, expectValue);
        lifecycleIndex++;
        stack->SetLifecycleIndex(lifecycleIndex);
    };
    switch (lifecycle) {
        case NavDestinationLifecycle::ON_WILL_APPEAR: {
            eventHub->SetOnWillAppear(callback);
            break;
        }
        case NavDestinationLifecycle::ON_APPEAR: {
            eventHub->SetOnAppear(std::move(callback));
            break;
        }
        case NavDestinationLifecycle::ON_WILL_SHOW: {
            eventHub->SetOnWillShow(callback);
            break;
        }
        case NavDestinationLifecycle::ON_SHOW: {
            eventHub->SetOnShown(std::move(callback));
            break;
        }
        case NavDestinationLifecycle::ON_WILL_HIDE: {
            eventHub->SetOnWillHide(callback);
            break;
        }
        case NavDestinationLifecycle::ON_HIDE: {
            eventHub->SetOnHidden(std::move(callback));
            break;
        }
        case NavDestinationLifecycle::ON_WILL_DISAPPEAR: {
            eventHub->SetOnWillDisAppear(callback);
            break;
        }
        case NavDestinationLifecycle::ON_DISAPPEAR: {
            eventHub->SetOnDisappear(std::move(callback));
            break;
        }
        default:
            break;
    }
}

RefPtr<NavDestinationGroupNode> NavigationLifecycleTestNg::CreateDestination(const std::string name)
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
    return frameNode;
}

struct TestProperty {
    std::optional<bool> isOn = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
};

/**
 * @tc.name: NavigationLifecyclePushTest001
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePushTest001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    /**
     * @tc.step1. create destinationA and set destinationA lifecycle
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationNode(navigationNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_NE(eventHub, nullptr);
    stack->SetLifecycleIndex(0);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 1, frameNode, stack);

    /**
     * @tc.steps: step2. push destinationA and sync navigation stack
     * @tc.expected:step2.
     */
    stack->UpdateAnimatedValue(false);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->FlushBuildFinishCallbacks();
    const int8_t lifecycleIndex = 2;
    EXPECT_EQ(stack->GetLifecycleIndex(), lifecycleIndex);
    stack->SetLifecycleIndex(0);

    /**
     * @tc.steps: step3. push destinationB and set lifecycle
     */
    auto frameNodeB = CreateDestination("B");
    auto patternB = AceType::DynamicCast<NavDestinationPattern>(frameNodeB->GetPattern());
    EXPECT_NE(patternB, nullptr);
    patternB->SetNavigationNode(navigationNode);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 0, frameNodeB, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, lifecycleIndex, frameNodeB, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, frameNode, stack);
    stack->Add("pageB", frameNodeB);
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    const int8_t targetLifecycle = 3;
    EXPECT_EQ(stack->GetLifecycleIndex(), targetLifecycle);
    stack->SetLifecycleIndex(0);
}

/**
 * @tc.name: NavigationLifecyclePopTest002
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePopTest002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    /**
     * @tc.step1. create destinationA and set destinationA lifecycle
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step3. push destinationB and set lifecycle
     */
    auto frameNodeB = CreateDestination("B");
    stack->Add("pageB", frameNodeB);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step4. pop pageB,and sync stack
     */
    stack->Pop();
    SetEvent(NavDestinationLifecycle::ON_HIDE, 0, frameNodeB, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 1, frameNode, stack);
    const int8_t disAppearIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, disAppearIndex, frameNodeB, stack);
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    const int8_t targetLifecycle = 3;
    EXPECT_EQ(stack->GetLifecycleIndex(), targetLifecycle);
    stack->SetLifecycleIndex(0);
}

/**
 * @tc.name: NavigationLifecycleReplaceTest003
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePopTest003, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    /**
     * @tc.step1. create destinationA and set destinationA lifecycle
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step3. push destinationB and set lifecycle
     */

    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationNode(navigationNode);
    stack->Remove();
    auto frameNodeB = CreateDestination("B");
    auto patternB = AceType::DynamicCast<NavDestinationPattern>(frameNodeB->GetPattern());
    EXPECT_NE(patternB, nullptr);
    patternB->SetNavigationNode(navigationNode);
    stack->Add("pageB", frameNodeB);
    stack->UpdateReplaceValue(1);
    stack->UpdateAnimatedValue(false);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 0, frameNodeB, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, frameNode, stack);
    const int8_t showIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_SHOW, showIndex, frameNodeB, stack);
    const int8_t disAppearIndex = 3;
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, disAppearIndex, frameNode, stack);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationLifecyclePushTest004
 * @tc.desc: Test push lifecycle is correct with animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePushTest004, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navDestination
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    /**
     * @tc.step2. push and create destination A, and set destination event.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationNode(navigationNode);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 1, frameNode, stack);
    const int8_t willShowIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, willShowIndex, frameNode, stack);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto eventHub = frameNode->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->FireOnWillAppear();
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    auto lifecycleIndex = stack->GetLifecycleIndex();
    const int8_t targetIndex = 3;
    EXPECT_EQ(lifecycleIndex, targetIndex);
}

/**
 * @tc.name: NavigationLifecyclePopTest005
 * @tc.desc: Test push lifecycle is correct with animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePopTest005, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navDestination
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps:step2. create destination A and push it to stack.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->FireShowAndHideLifecycle(nullptr, frameNode, false, true);

    /**
     * @tc.steps:step3. set event in destination A
     */
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, frameNode, stack);
    const int8_t willDisappearIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, willDisappearIndex, frameNode, stack);
    const int8_t disAppearIndex = 3;
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, disAppearIndex, frameNode, stack);

    /**
     * @tc.steps: step4. sync stack
     */
    stack->Remove();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->FireShowAndHideLifecycle(nullptr, frameNode, false, true);
    auto contentNode = navigationNode->GetContentNode();
    EXPECT_NE(contentNode, nullptr);
    contentNode->RemoveChild(frameNode);
}

/**
 * @tc.name: NavigationLifecycleReplaceTest006
 * @tc.desc: Test replace lifecycle is correct with animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecycleReplaceTest006, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navDestination
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps:step2. create destination A and push it to stack.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->FireShowAndHideLifecycle(nullptr, frameNode, false, true);

    /**
     * @tc.steps: step3. create destination B and set lifecycle
     */
    auto destinationB = NavigationLifecycleTestNg::CreateDestination("B");
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationNode(navigationNode);
    auto patternB = AceType::DynamicCast<NavDestinationPattern>(destinationB->GetPattern());
    EXPECT_NE(patternB, nullptr);
    patternB->SetNavigationNode(navigationNode);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 1, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 2, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 3, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 4, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 5, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 6, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 7, frameNode, stack);

    /**
     * @tc.steps: step4. sync navigation stack
     */
    stack->Remove();
    stack->Add("B", destinationB);
    auto eventHub = destinationB->GetOrCreateEventHub<NavDestinationEventHub>();
    eventHub->FireOnWillAppear();
    stack->UpdateReplaceValue(true);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->FireShowAndHideLifecycle(frameNode, destinationB, false, true);
    auto contentNode = navigationNode->GetContentNode();
    EXPECT_NE(contentNode, nullptr);
    contentNode->RemoveChild(frameNode);
}

/**
 * @tc.name: NavigationLifecyclePushTest007
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePushTest007, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navDestination
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    /**
     * @tc.step2. push and create destination A, and set destination event.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationNode(navigationNode);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 1, frameNode, stack);
    const int8_t willShowIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, willShowIndex, frameNode, stack);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto eventHub = frameNode->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->FireOnWillAppear();
    stack->Add("pageA", frameNode);
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    auto lifecycleIndex = stack->GetLifecycleIndex();
    const int8_t targetIndex = 3;
    EXPECT_EQ(lifecycleIndex, targetIndex);
}

/**
 * @tc.name: NavigationLifecyclePopTest008
 * @tc.desc: Test pop lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecyclePopTest008, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navDestination
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps:step2. create destination A and push it to stack.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    stack->Add("pageA", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->FireShowAndHideLifecycle(nullptr, frameNode, false, true);

    /**
     * @tc.steps:step3. set event in destination A
     */
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, frameNode, stack);
    const int8_t willDisappearIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, willDisappearIndex, frameNode, stack);
    const int8_t disAppearIndex = 3;
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, disAppearIndex, frameNode, stack);

    /**
     * @tc.steps: step4. sync stack
     */
    stack->Remove();
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationLifecycleReplaceTest009
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationLifecycleReplaceTest009, TestSize.Level1)
{
    /**
     * @tc.steps:step1.create navDestination
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps:step2. create destination A and push it to stack.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    stack->Add("pageA", frameNode);
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    navigationPattern->FireShowAndHideLifecycle(nullptr, frameNode, false, false);

    /**
     * @tc.steps: step3. create destination B and set lifecycle
     */
    auto destinationB = NavigationLifecycleTestNg::CreateDestination("B");
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationNode(navigationNode);
    auto patternB = AceType::DynamicCast<NavDestinationPattern>(destinationB->GetPattern());
    EXPECT_NE(patternB, nullptr);
    patternB->SetNavigationNode(navigationNode);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 1, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 2, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 3, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 4, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 5, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 6, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 7, frameNode, stack);

    /**
     * @tc.steps: step4. sync navigation stack
     */
    stack->Remove();
    stack->Add("B", destinationB);
    auto eventHub = destinationB->GetOrCreateEventHub<NavDestinationEventHub>();
    eventHub->FireOnWillAppear();
    stack->UpdateReplaceValue(true);
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationPushReplaceTest001
 * @tc.desc: test push and replace
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationPushReplaceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);

    /**
     * @tc.steps: step2. push destination and then replace destination
     */
    navigationStack->Push("A", 0);
    navigationStack->Pop();
    navigationStack->Push("C", 0);
    navigationStack->UpdateReplaceValue(1);

    /**
     * @tc.steps: step3. sync navigation stack
     * @tc.expected: navBar is inVisible, child and stack is [C]
     */
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    EXPECT_TRUE(navigationNode->GetNeedSetInvisible());
    auto contentNode = navigationNode->GetContentNode();
    EXPECT_FALSE(contentNode == nullptr);
    auto children = contentNode->GetChildren();
    ASSERT_EQ(children.size(), 1);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(children.front());
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetName(), "C");
}

/**
 * @tc.name: NavigationPushReplaceTest002
 * @tc.desc: test push and replace when navigation stack is not null
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationPushReplaceTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);

    /**
     * @tc.steps:step2. push destination A and sync navigation stack
     * @tc.expected: step2. sync destination success. Destination A push success.
     */
    navigationStack->Push("A", 0);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(navigationStack->Size(), 1);
    auto content = navigationNode->GetContentNode();
    ASSERT_NE(content, nullptr);
    auto children = content->GetChildren();
    ASSERT_EQ(children.size(), 1);
    auto navDestinationA = AceType::DynamicCast<NavDestinationGroupNode>(children.front());
    ASSERT_NE(navDestinationA, nullptr);
    auto patternA = navDestinationA->GetPattern<NavDestinationPattern>();
    ASSERT_NE(patternA, nullptr);
    ASSERT_EQ(patternA->GetName(), "A");

    /**
     * @tc.steps: step3. push destinationB and replace destinationC, sync navigation stack
     * @tc.expected: step3. sync destination success.DestinationC push success
     */
    navigationStack->Push("B", 1);
    navigationStack->Pop();
    navigationStack->Push("C", 1);
    navigationStack->UpdateReplaceValue(1);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    children = content->GetChildren();
    ASSERT_EQ(children.size(), 2);
    auto lastChild = AceType::DynamicCast<NavDestinationGroupNode>(children.back());
    ASSERT_NE(lastChild, nullptr);
    auto lastPattern = lastChild->GetPattern<NavDestinationPattern>();
    ASSERT_NE(lastPattern, nullptr);
    ASSERT_EQ(lastPattern->GetName(), "C");
}

/**
 * @tc.name: NavigationPushReplaceTest003
 * @tc.desc: test push and replace when replace page is dialog page
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationPushReplaceTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);

    /**
     * @tc.steps: step2. push destinationA and replace Dialog B
     * @tc.expected: navBar is visible, stack has one child
     */
    navigationStack->Push("A", 0);
    navigationStack->Pop();
    auto topDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(topDestination, nullptr);
    topDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("C", topDestination);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(navigationNode->GetNeedSetInvisible(), false);
    auto content = navigationNode->GetContentNode();
    ASSERT_NE(content, nullptr);
    auto children = content->GetChildren();
    ASSERT_EQ(children.size(), 1);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(children.front());
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetName(), "C");
}

/**
 * @tc.name: NavigationPushReplaceTest004
 * @tc.desc: test push and replace when replace page is dialog page
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationPushReplaceTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);

    /**
     * @tc.steps: step2. push standard navDestination and sync navigation
     * @tc.expected: step2. navBar is not visible, and child size is one
     */
    navigationStack->Push("A", 0);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(navigationNode->GetNeedSetInvisible(), true);
    auto content = navigationNode->GetContentNode();
    ASSERT_NE(content, nullptr);
    auto children = content->GetChildren();
    ASSERT_EQ(children.size(), 1);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(children.front());
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetName(), "A");


    /**
     * @tc.steps: step2. push destinationA and replace Dialog B
     * @tc.expected: navBar is visible, stack has one child
     */
    auto lastDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(lastDestination, nullptr);
    lastDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("B", lastDestination);
    navigationStack->Pop();
    auto topDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 102, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(topDestination, nullptr);
    topDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("C", topDestination);
    navigationStack->UpdateReplaceValue(1);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(navigationNode->GetNeedSetInvisible(), true);
    children = content->GetChildren();
    ASSERT_EQ(children.size(), 2);
    auto topNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(children.back());
    ASSERT_NE(topNavDestination, nullptr);
    auto topPattern = topNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(topPattern, nullptr);
    ASSERT_EQ(topPattern->GetName(), "C");
}

/**
 * @tc.name: NavigationPushReplaceTest005
 * @tc.desc: test push and replace when replace page is dialog page
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationPushReplaceTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);

    /**
     * @tc.steps: step2.push dialog destination,and sync navigation
     * @tc.expected: step2. stack size is one,and naveBar is visible
     */
    auto topDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(topDestination, nullptr);
    topDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("A", topDestination);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto content = navigationNode->GetContentNode();
    ASSERT_NE(content, nullptr);
    auto children = content->GetChildren();
    ASSERT_EQ(children.size(), 1);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(children.front());
    ASSERT_NE(navDestination, nullptr);
    auto topPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(topPattern, nullptr);
    ASSERT_EQ(topPattern->GetName(), "A");


    /**
     * @tc.steps: step2. push destinationA and replace Dialog B
     * @tc.expected: navBar is visible, stack has one child
     */
    auto lastDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(lastDestination, nullptr);
    lastDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("B", lastDestination);
    navigationStack->Pop();
    auto newTopDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 102, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopDestination, nullptr);
    newTopDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("C", newTopDestination);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(navigationNode->GetNeedSetInvisible(), false);
    children = content->GetChildren();
    ASSERT_EQ(children.size(), 2);
    navDestination = AceType::DynamicCast<NavDestinationGroupNode>(children.back());
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetName(), "C");
}

/**
 * @tc.name: NavigationDialogLifecycle006
 * @tc.desc: test navigation lifecycle in dialog page
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationDialogLifecycle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    auto node = GetOrCreateNavigationNode();
    auto pattern = node->GetPattern<NavigationPattern>();
    auto stack = AceType::DynamicCast<MockNavigationStack>(
        pattern->GetNavigationStack());

    /**
     * @tc.steps: step2.push standard destination
     * @tc.expected: step2. trigger lifecycle
     */
    auto navDestination = CreateDestination("pageA");
    EXPECT_FALSE(navDestination == nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 1, navDestination, stack);
    stack->Add("pageA", navDestination);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(context == nullptr);
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step2.push dialog destinationA
     * @tc.expected: step2.trigger destination lifecycle
     */
    stack->SetLifecycleIndex(0);
    auto navDestinationA = CreateDestination("pageB");
    EXPECT_FALSE(navDestinationA == nullptr);
    navDestinationA->mode_ = NavDestinationMode::DIALOG;
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 1, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 2, navDestinationA, stack);
    stack->Add("pageB", navDestinationA);
    auto navDestinationAEventHub = navDestinationA->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(navDestinationAEventHub == nullptr);
    navDestinationAEventHub->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step3. push standard destination
     * @tc.expected: step3. trigger destination lifecycle
     */
    stack->SetLifecycleIndex(0);
    auto navDestinationC = CreateDestination("pageB");
    EXPECT_FALSE(navDestinationC == nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestinationC, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 1, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 2, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 3, navDestinationC, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 4, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 5, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 6, navDestinationC, stack);
    stack->Add("pageB", navDestinationC);
    auto navDestinationEventHub = navDestinationC->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(navDestinationEventHub == nullptr);
    navDestinationEventHub->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationDialogLifecycle007
 * @tc.desc: test navigation lifecycle in dialog page
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationDialogLifecycle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    auto node = GetOrCreateNavigationNode();
    auto pattern = node->GetPattern<NavigationPattern>();
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    EXPECT_FALSE(stack == nullptr);

    /**
     * @tc.steps: step2.push standard destination
     * @tc.expected: step2. trigger lifecycle
     */
    auto navDestination = CreateDestination("pageA");
    EXPECT_FALSE(navDestination == nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 1, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 2, navDestination, stack);
    stack->Add("pageA", navDestination);
    auto navDestinationEventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(navDestinationEventHub == nullptr);
    navDestinationEventHub->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(context == nullptr);
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step2.push dialog destinationA
     * @tc.expected: step2.trigger destination lifecycle
     */
    stack->SetLifecycleIndex(0);
    auto navDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_FALSE(navDestinationA == nullptr);
    navDestinationA->mode_ = NavDestinationMode::DIALOG;
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 1, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 2, navDestinationA, stack);
    stack->Add("pageA", navDestinationA);
    auto eventHubA = navDestinationA->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHubA == nullptr);
    eventHubA->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step3. pop dialog page
     * @tc.expected: step3. trigger destination lifecycle
     */
    stack->SetLifecycleIndex(0);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 0, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 2, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 3, navDestinationA, stack);
    stack->Remove();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationDialogLifecycle008
 * @tc.desc: test navigation lifecycle in dialog page without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationDialogLifecycle008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    auto node = GetOrCreateNavigationNode();
    auto pattern = node->GetPattern<NavigationPattern>();
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    EXPECT_FALSE(stack == nullptr);

    /**
     * @tc.steps: step2.push standard destination
     * @tc.expected: step2. trigger lifecycle
     */
    auto navDestination = CreateDestination("pageA");
    EXPECT_FALSE(navDestination == nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 1, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 2, navDestination, stack);
    stack->Add("pageA", navDestination);
    stack->UpdateAnimatedValue(false);
    auto navDestinationEventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(navDestinationEventHub == nullptr);
    navDestinationEventHub->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(context == nullptr);
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step2.push dialog destinationA
     * @tc.expected: step2.trigger destination lifecycle
     */
    stack->SetLifecycleIndex(0);
    auto navDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_FALSE(navDestinationA == nullptr);
    navDestinationA->mode_ = NavDestinationMode::DIALOG;
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 1, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 2, navDestinationA, stack);
    stack->Add("pageA", navDestinationA);
    stack->UpdateAnimatedValue(false);
    auto eventHubA = navDestinationA->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHubA == nullptr);
    eventHubA->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step3. pop dialog page
     * @tc.expected: step3. trigger destination lifecycle
     */
    stack->SetLifecycleIndex(0);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 0, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 2, navDestinationA, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 3, navDestinationA, stack);
    stack->Remove();
    stack->UpdateAnimatedValue(false);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationDialogLifecycle008
 * @tc.desc: test remove destination lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationDialogLifecycle009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    auto node = GetOrCreateNavigationNode();
    auto pattern = node->GetPattern<NavigationPattern>();
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    EXPECT_FALSE(stack == nullptr);

    /**
     * @tc.steps: step2.push standard destination
     * @tc.expected: step2. trigger lifecycle
     */
    auto navDestination = CreateDestination("pageA");
    EXPECT_FALSE(navDestination == nullptr);
    navDestination->mode_ = NavDestinationMode::DIALOG;
    auto navDestinationB = CreateDestination("pageB");
    EXPECT_FALSE(navDestinationB == nullptr);
    navDestinationB->mode_ = NavDestinationMode::DIALOG;
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 1, navDestinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 2, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 3, navDestinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 4, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 5, navDestinationB, stack);
    stack->Add("pageA", navDestination);
    stack->Add("pageB", navDestinationB);
    auto navDestinationEventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(navDestinationEventHub == nullptr);
    navDestinationEventHub->FireOnWillAppear();
    auto eventHubB = navDestinationB->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHubB == nullptr);
    eventHubB->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(context == nullptr);
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step3. remove destinationA
     * @tc.steps: step3. trigger destinationA lifecycle
     */
    stack->RemoveIndex(0);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_HIDE, 1, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 2, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 3, navDestination, stack);
}

/**
 * @tc.name: NavigationDialogLifecycle010
 * @tc.desc: test remove standard destination lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationDialogLifecycle010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    auto node = GetOrCreateNavigationNode();
    auto pattern = node->GetPattern<NavigationPattern>();
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    EXPECT_FALSE(stack == nullptr);

    /**
     * @tc.steps: step2.push standard destination
     * @tc.expected: step2. trigger lifecycle
     */
    auto navDestination = CreateDestination("pageA");
    EXPECT_FALSE(navDestination == nullptr);
    auto navDestinationB = CreateDestination("pageB");
    EXPECT_FALSE(navDestinationB == nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 1, navDestinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 2, navDestinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 3, navDestinationB, stack);
    stack->Add("pageA", navDestination);
    stack->Add("pageB", navDestinationB);
    auto navDestinationEventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(navDestinationEventHub == nullptr);
    navDestinationEventHub->FireOnWillAppear();
    auto eventHubB = navDestinationB->GetOrCreateEventHub<NavDestinationEventHub>();
    EXPECT_FALSE(eventHubB == nullptr);
    eventHubB->FireOnWillAppear();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(context == nullptr);
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step3. remove destinationA
     * @tc.expected: step3. trigger destinationA lifecycle
     */
    stack->RemoveIndex(0);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 1, navDestination, stack);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
}

/**
 * @tc.name: NavigationDialogLifecycle011
 * @tc.desc: test remove standard and dialog destination lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(NavigationLifecycleTestNg, NavigationDialogLifecycle011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    auto node = GetOrCreateNavigationNode();
    auto pattern = node->GetPattern<NavigationPattern>();
    auto stack = AceType::DynamicCast<MockNavigationStack>(pattern->GetNavigationStack());
    EXPECT_FALSE(stack == nullptr);

    /**
     * @tc.steps: step2.push standard destination
     * @tc.expected: step2. trigger lifecycle
     */
    auto navDestination = CreateDestination("pageA");
    EXPECT_FALSE(navDestination == nullptr);
    auto navDestinationB = CreateDestination("pageB");
    EXPECT_FALSE(navDestinationB == nullptr);
    navDestinationB->mode_ = NavDestinationMode::DIALOG;
    auto navDestinationC = CreateDestination("pageC");
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 0, navDestinationC, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 1, navDestinationC, stack);
    stack->Add("pageA", navDestination);
    stack->Add("pageB", navDestinationB);
    stack->Add("pageC", navDestinationC);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(context == nullptr);
    context->FlushBuildFinishCallbacks();

    /**
     * @tc.steps: step3. remove destinationA
     * @tc.expected: step3. trigger destinationA lifecycle
     */
    stack->RemoveIndex(1);
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, 0, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 1, navDestinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 2, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, 3, navDestinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_SHOW, 4, navDestination, stack);
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, 5, navDestinationB, stack);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
}
}
