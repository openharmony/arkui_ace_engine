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

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class NavigationFocusTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string name);
};

void NavigationFocusTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationFocusTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationFocusTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

RefPtr<NavDestinationGroupNode> NavigationFocusTestNg::CreateDestination(const std::string name)
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

/**
 * @tc.name: NavigationFocusTest001
 * @tc.desc: Test navigation transition focusable
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = true;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;

    /**
     * @tc.steps: step2.push destination A
     * @tc.expected: step2. destinationA is focusable, navBar is not focusable
     */
    auto frameNode = CreateDestination("pageA");
    stack->Add("pageA", frameNode);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);
    auto focusHub = frameNode->GetFocusHub();
    focusHub->focusable_ = true;
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    auto topDestinationPattern = frameNode->GetPattern();
    EXPECT_TRUE(currentView == topDestinationPattern);

    /**
     * @tc.steps: step3. push pageB
     * @tc.expected: step3. destinationB is onFocus, destinationA is lostFocus
     */
    auto frameNodeB = CreateDestination("pageB");
    stack->Add("pageB", frameNodeB);
    auto nodeBHub = frameNodeB->GetFocusHub();
    EXPECT_FALSE(nodeBHub == nullptr);
    nodeBHub->focusable_ = true;
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    currentView = FocusView::GetCurrentFocusView();
    auto newTopPattern = frameNodeB->GetPattern();
    EXPECT_TRUE(currentView == newTopPattern);
}

/**
 * @tc.name: NavigationFocusTest002
 * @tc.desc: Test push lifecycle is correct without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = true;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step1. push destinationA and set destinationA not enable
     * @tc.expected: step1. current focus view is nullptr
     */
    auto frameNode = CreateDestination("pageA");
    EXPECT_FALSE(frameNode == nullptr);
    auto focusHub = frameNode->GetFocusHub();
    EXPECT_FALSE(focusHub == nullptr);
    focusHub->focusable_ = false;
    stack->Add("pageA", frameNode);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    EXPECT_TRUE(currentView == nullptr);

    /**
     * @tc.steps: step3. push destinationB, and set destinationB focusable false
     * @tc.expected: step3. current focus view is nullptr
     */
    auto frameNodeB = CreateDestination("pageB");
    EXPECT_FALSE(frameNodeB == nullptr);
    auto topFocusHub = frameNodeB->GetFocusHub();
    EXPECT_FALSE(topFocusHub == nullptr);
    topFocusHub->focusable_ = false;
    stack->Add("pageB", frameNodeB);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    currentView = FocusView::GetCurrentFocusView();
    EXPECT_TRUE(currentView == nullptr);
}

/**
 * @tc.name: NavigationFocusTest003
 * @tc.desc: test navigation is unfocusable
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = false;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step2. push destination A
     * @tc.expected: step2. destinationA is on focus
     */
    auto frameNode = CreateDestination("pageA");
    EXPECT_FALSE(frameNode == nullptr);
    stack->Add("pageA", frameNode);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    EXPECT_TRUE(currentView == nullptr);

    /**
     * @tc.steps: step3. push destinationB
     * @tc.expected: step3. destinationB is not on focus
     */
    auto frameNodeB = CreateDestination("pageB");
    EXPECT_FALSE(frameNodeB == nullptr);
    stack->Add("pageB", frameNodeB);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    currentView = FocusView::GetCurrentFocusView();
    EXPECT_TRUE(currentView == nullptr);
}

/**
 * @tc.name: NavigationFocusTest004
 * @tc.desc: test navigation mode change focus
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = true;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step2. set navigation mode split and push destinationA
     * @tc.expected: step2. push destinationA success, destinationA is focused
     */
    pattern->SetNavigationMode(NavigationMode::SPLIT);
    auto frameNode = CreateDestination("pageA");
    EXPECT_FALSE(frameNode == nullptr);
    stack->Add("pageA", frameNode);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    auto destinationPattern = frameNode->GetPattern();
    EXPECT_TRUE(currentView == destinationPattern);

    /**
     * @tc.steps: step4.request focus on navBar
     * @tc.expected: step4. navBar request focus success
     */
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    EXPECT_FALSE(navBarNode == nullptr);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    EXPECT_FALSE(navBarPattern == nullptr);
    navBarPattern->FocusViewShow();
    currentView = FocusView::GetCurrentFocusView();
    EXPECT_TRUE(currentView == navBarPattern);
    auto navBarEventHub = navBarNode->GetFocusHub();
    EXPECT_FALSE(navBarEventHub == nullptr);
    navBarEventHub->currentFocus_ = true;

    /**
     * @tc.steps: step5.set navigation mode stack
     * @tc.expected: step5. current focusView is navdestinationA
     */
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->RefreshFocusToDestination();
    currentView = FocusView::GetCurrentFocusView();
    EXPECT_TRUE(currentView == destinationPattern);
}

/**
 * @tc.name: NavigationFocusTest005
 * @tc.desc: test navigation focus in no animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = true;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step2. push destinationA use no animation
     * @tc.expected: step2. current focus is on destinationA
     */
    auto frameNode = CreateDestination("frameNode");
    EXPECT_FALSE(frameNode == nullptr);
    stack->Add("pageA", frameNode);
    stack->UpdateAnimatedValue(false);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    auto navDestinationPattern = frameNode->GetPattern();
    EXPECT_TRUE(currentView == navDestinationPattern);

    /**
     * @tc.steps: step3. push destinationB use no animation
     * @tc.expected: step3. current focus is on destinationB
     */
    auto frameNodeB = CreateDestination("pageB");
    EXPECT_FALSE(frameNodeB == nullptr);
    stack->Add("pageB", frameNodeB);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    currentView = FocusView::GetCurrentFocusView();
    auto topDestination = frameNodeB->GetPattern();
    EXPECT_TRUE(topDestination == currentView);
}

/**
 * @tc.name: NavigationFocusTest006
 * @tc.desc: test navigation focus in replace animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = true;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step2. replace page to navDestinationA
     * @tc.expected: step2. current focus is on navDestinationA
     */
    auto navDestinationA = CreateDestination("pageA");
    EXPECT_FALSE(navDestinationA == nullptr);
    stack->Add("pageA", navDestinationA);
    stack->UpdateReplaceValue(1);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_FALSE(pipelineContext == nullptr);
    pipelineContext->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    auto patternA = navDestinationA->GetPattern();
    EXPECT_TRUE(currentView == patternA);

    /**
     * @tc.steps: step3. replace destinationA to destinationB
     * @tc.expected: step3. current focus is destinationB
     */
    auto destinationB = CreateDestination("pageB");
    EXPECT_FALSE(destinationB == nullptr);
    stack->Remove();
    stack->Add("pageB", destinationB);
    stack->UpdateReplaceValue(1);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    pipelineContext->FlushBuildFinishCallbacks();
    auto topNode = stack->Get();
    EXPECT_TRUE(topNode == destinationB);
    EXPECT_TRUE(stack->Size() == 1);
    currentView = FocusView::GetCurrentFocusView();
    auto patternB = destinationB->GetPattern();
    EXPECT_TRUE(currentView == patternB);
}

/**
 * @tc.name: NavigationFocusTest007
 * @tc.desc: test navigation focus in replace without animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationFocusTestNg, NavigationFocusTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation node
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
    EXPECT_FALSE(navigationNode == nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationHub = navigationNode->GetFocusHub();
    EXPECT_FALSE(navigationHub == nullptr);
    navigationHub->focusable_ = true;
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    EXPECT_FALSE(dividerNode == nullptr);
    auto dividerHub = dividerNode->GetFocusHub();
    EXPECT_FALSE(dividerHub == nullptr);
    dividerHub->focusable_ = true;
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    EXPECT_FALSE(pattern == nullptr);

    /**
     * @tc.steps: step2. replace page to navDestinationA
     * @tc.expected: step2. current focus is on navDestinationA
     */
    auto navDestinationA = CreateDestination("pageA");
    EXPECT_FALSE(navDestinationA == nullptr);
    stack->Add("pageA", navDestinationA);
    stack->UpdateReplaceValue(1);
    stack->UpdateAnimatedValue(false);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
    auto currentView = FocusView::GetCurrentFocusView();
    auto patternA = navDestinationA->GetPattern();
    EXPECT_TRUE(currentView == patternA);

    /**
     * @tc.steps: step3. replace destinationA to destinationB
     * @tc.expected: step3. current focus is destinationB
     */
    auto destinationB = CreateDestination("pageB");
    EXPECT_FALSE(destinationB == nullptr);
    stack->Remove();
    stack->Add("pageB", destinationB);
    stack->UpdateReplaceValue(1);
    stack->UpdateAnimatedValue(false);
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    context->FlushBuildFinishCallbacks();
    auto topNode = stack->Get();
    EXPECT_TRUE(topNode == destinationB);
    EXPECT_TRUE(stack->Size() == 1);
    currentView = FocusView::GetCurrentFocusView();
    auto patternB = destinationB->GetPattern();
    EXPECT_TRUE(currentView == patternB);
}
} // namespace OHOS::Ace::NG
