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
    static void SetEvent(std::string type, int8_t expectValue,
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

void NavigationLifecycleTestNg::SetEvent(std::string type, int8_t expectValue,
    const RefPtr<FrameNode>& destinationNode, const RefPtr<MockNavigationStack>& stack)
{
    auto eventHub = destinationNode->GetEventHub<NavDestinationEventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto callback = [stack = stack, expectValue = expectValue]() {
        auto lifecycleIndex = stack->GetLifecycleIndex();
        EXPECT_EQ(lifecycleIndex, expectValue);
        lifecycleIndex++;
        stack->SetLifecycleIndex(lifecycleIndex);
    };
    if (type == "onAppear") {
        eventHub->SetOnAppear(callback);
    } else if (type == "onShown") {
        eventHub->SetOnShown(callback);
    } else if (type == "onHidden") {
        eventHub->SetOnHidden(callback);
    } else if (type == "onDisAppear") {
        eventHub->SetOnDisappear(callback);
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
    SetEvent("onAppear", 0, frameNode, stack);
    SetEvent("onShown", 1, frameNode, stack);

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
    SetEvent("onAppear", 0, frameNodeB, stack);
    SetEvent("onShown", lifecycleIndex, frameNodeB, stack);
    SetEvent("onHidden", 1, frameNode, stack);
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
    SetEvent("onHidden", 0, frameNodeB, stack);
    SetEvent("onShown", 1, frameNode, stack);
    const int8_t disAppearIndex = 2;
    SetEvent("onDisAppear", disAppearIndex, frameNodeB, stack);
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
    SetEvent("onAppear", 0, frameNodeB, stack);
    SetEvent("onHidden", 1, frameNode, stack);
    const int8_t showIndex = 2;
    SetEvent("onShown", showIndex, frameNodeB, stack);
    const int8_t disAppearIndex = 3;
    SetEvent("onDisAppear", disAppearIndex, frameNode, stack);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
}
}