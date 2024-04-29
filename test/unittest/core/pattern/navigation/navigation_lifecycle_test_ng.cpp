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

#include "base/memory/ace_type.h"
#include "core/components_ng/animation/geometry_transition.h"

#define protected public
#define private public
#include "base/json/json_util.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/animation/animator.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

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
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string name);
    static void SetEvent(NavDestinationLifecycle lifecycle, int8_t expectValue,
        const RefPtr<FrameNode>& destinationNode, const RefPtr<MockNavigationStack>& stack);
};

void NavigationLifecycleTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
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

void NavigationLifecycleTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

void NavigationLifecycleTestNg::SetEvent(NavDestinationLifecycle lifecycle, int8_t expectValue,
    const RefPtr<FrameNode>& destinationNode, const RefPtr<MockNavigationStack>& stack)
{
    auto eventHub = destinationNode->GetEventHub<NavDestinationEventHub>();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();

    /**
     * @tc.step1. create destinationA and set destinationA lifecycle
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NavDestinationEventHub>();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();

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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();

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
    stack->Remove();
    auto frameNodeB = CreateDestination("B");
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();

    /**
     * @tc.step2. push and create destination A, and set destination event.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 1, frameNode, stack);
    const int8_t willShowIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, willShowIndex, frameNode, stack);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto eventHub = frameNode->GetEventHub<NavDestinationEventHub>();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();
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
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 1, frameNode, stack);
    const int8_t onAppearIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_APPEAR, onAppearIndex, destinationB, stack);
    const int8_t willShowIndex = 3;
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, willShowIndex, destinationB, stack);
    const int8_t hideIndex = 4;
    SetEvent(NavDestinationLifecycle::ON_HIDE, hideIndex, frameNode, stack);
    const int8_t willDisappearIndex = 5;
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, willDisappearIndex, frameNode, stack);
    const int8_t showIndex = 6;
    SetEvent(NavDestinationLifecycle::ON_SHOW, showIndex, destinationB, stack);
    const int8_t disAppearIndex = 7;
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, disAppearIndex, frameNode, stack);

    /**
     * @tc.steps: step4. sync navigation stack
     */
    stack->Remove();
    stack->Add("B", destinationB);
    auto eventHub = destinationB->GetEventHub<NavDestinationEventHub>();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();

    /**
     * @tc.step2. push and create destination A, and set destination event.
     */
    auto frameNode = NavigationLifecycleTestNg::CreateDestination("A");
    EXPECT_NE(frameNode, nullptr);
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, frameNode, stack);
    SetEvent(NavDestinationLifecycle::ON_APPEAR, 1, frameNode, stack);
    const int8_t willShowIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, willShowIndex, frameNode, stack);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    auto eventHub = frameNode->GetEventHub<NavDestinationEventHub>();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();
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
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree();
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
    SetEvent(NavDestinationLifecycle::ON_WILL_APPEAR, 0, destinationB, stack);
    SetEvent(NavDestinationLifecycle::ON_WILL_HIDE, 1, frameNode, stack);
    const int8_t onAppearIndex = 2;
    SetEvent(NavDestinationLifecycle::ON_APPEAR, onAppearIndex, destinationB, stack);
    const int8_t willShowIndex = 3;
    SetEvent(NavDestinationLifecycle::ON_WILL_SHOW, willShowIndex, destinationB, stack);
    const int8_t hideIndex = 4;
    SetEvent(NavDestinationLifecycle::ON_HIDE, hideIndex, frameNode, stack);
    const int8_t willDisappearIndex = 5;
    SetEvent(NavDestinationLifecycle::ON_WILL_DISAPPEAR, willDisappearIndex, frameNode, stack);
    const int8_t showIndex = 6;
    SetEvent(NavDestinationLifecycle::ON_SHOW, showIndex, destinationB, stack);
    const int8_t disAppearIndex = 7;
    SetEvent(NavDestinationLifecycle::ON_DISAPPEAR, disAppearIndex, frameNode, stack);

    /**
     * @tc.steps: step4. sync navigation stack
     */
    stack->Remove();
    stack->Add("B", destinationB);
    auto eventHub = destinationB->GetEventHub<NavDestinationEventHub>();
    eventHub->FireOnWillAppear();
    stack->UpdateReplaceValue(true);
    stack->UpdateAnimatedValue(false);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
}
}