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

#include "base/memory/ace_type.h"
#include "core/components_ng/animation/geometry_transition.h"

#define protected public
#define private public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "test/mock/base/mock_system_bar_style.h"
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

class NavigationCallbackTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    static RefPtr<NavigationGroupNode> GetOrCreateNavigationNode();
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string& name);
    int32_t AddNavigationCallback(NavigateChangeInfo& from, NavigateChangeInfo& to);
    void ClearChangeCallback();
    int32_t index_ = 0;
};

void NavigationCallbackTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto context = MockPipelineContext::GetCurrent();
    if (context) {
        context->stageManager_ = nullptr;
    }
    context->navigationMgr_ = AceType::MakeRefPtr<NavigationManager>();
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationCallbackTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationCallbackTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

RefPtr<NavigationGroupNode> NavigationCallbackTestNg::GetOrCreateNavigationNode()
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

void NavigationCallbackTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

int32_t NavigationCallbackTestNg::AddNavigationCallback(NavigateChangeInfo& preVal, NavigateChangeInfo& curVal)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, -1);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_RETURN(navigationManager, -1);
    int32_t callbackId = navigationManager->RegisterNavigateChangeCallback(
        [preVal, curVal, test = this](const std::string& from, const std::string& to) {
        test->index_ = 1;
    });
    return callbackId;
}

void NavigationCallbackTestNg::ClearChangeCallback()
{
    auto context = PipelineContext::GetCurrentContextSafely();
    ASSERT_NE(context, nullptr);
    auto navigationManager = context->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->changeCallbacks_.clear();
}

RefPtr<NavDestinationGroupNode> NavigationCallbackTestNg::CreateDestination(const std::string& name)
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

/**
 * @tc.name: NavigationCallbackTest001
 * @tc.desc: Test push destination from navBar callback when fullPage is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);

    /**
     * @tc.step1. set navigation push callback
     */
    auto navigationManager = context->GetNavigationManager();
    ASSERT_TRUE(navigationManager != nullptr);
    NavigateChangeInfo from = {.name = "navBar", .isSplit = false};
    NavigateChangeInfo to = {.name = "pageA", .isSplit = false};
    int32_t callbackId = AddNavigationCallback(from, to);
    EXPECT_NE(callbackId, -1);

    /**
     * @tc.step2. push pageA and set navigation is full page
     */
    stack->Push("pageA", 0);
    navigationPattern->isFullPageNavigation_ = true;
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    EXPECT_EQ(index_, 1);

    /**
     * @tc.step: step4. remove navigate callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest002
 * @tc.desc: Test push navBar to navDestination when navigation is not fullScreen
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node, and set navigation is not full screen
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
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = false;

    /**
     * @tc.steps: step3. set navigation push callback
     * @tc.expected: step3. callback id is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = {.name = "navBar", .isSplit = false};
    NavigateChangeInfo to = {.name = "pageA", .isSplit = false};
    int callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps: step4. push pageA, set navigation is full page and sync navigation stack
     * @tc.expected: step4. callback is not triggered, index is 0
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 0);

    /**
     * @tc.steps: step5.remove navigation transition callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest003
 * @tc.desc: Test push navBar to navDestination when navigation is fullScreen
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node
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
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = true;

    /**
     * @tc.steps: step3. set navigation push callback
     * @tc.expected: step3. callback id is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = {.name = "navBar", .isSplit = false};
    NavigateChangeInfo to = {.name = "pageA", .isSplit = false};
    int callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps: step4. push pageA, set navigation is full page and sync navigation stack
     * @tc.expected: step4. index is 1
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 1);

    /**
     * @tc.steps: step5.remove navigation transition callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest004
 * @tc.desc: Test push home destination from navDestination callback
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set home destination
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
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = true;
    navigationNode->customHomeDestination_ = CreateDestination("homeDestination");

    /**
     * @tc.steps: step2. add navigation transition callback
     * @tc.expected: step2. callbackId is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = { .name = "homeDestination", .isSplit = false };
    NavigateChangeInfo to = { .name = "pageA", .isSplit = false};
    int32_t callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps.step3: create navDestination B and sync navigation stack
     * @tc.expected: step3. current index is 1
     */
    stack->Push("pageA", 1);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 1);

    /**
     * @tc.steps: step4. remove navigation callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest005
 * @tc.desc: Test push destination from navDestination callback when fullPage is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = true;

    /**
     * @tc.step2. push pageA, set navigation is full page and sync navigation stack
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2. set navigation transition callback
     * @tc.expected: callbackId is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = {.name = "pageA", .isSplit = false};
    NavigateChangeInfo to = {.name = "pageB", .isSplit = false};
    int32_t callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps.step3: push navDestination B and sync navigation stack
     * @tc.expected: step3. current index is 1
     */
    stack->Push("pageB", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 1);

    /**
     * @tc.steps: step4. remove navigation callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest006
 * @tc.desc: Test push destination from navDestination callback when fullPage is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> navigationNode = AceType::DynamicCast<FrameNode>(
        ViewStackProcessor::GetInstance()->Finish());
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = false;

    /**
     * @tc.step2. push pageA, set navigation is full page and sync navigation stack
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step2. set navigation transition callback
     * @tc.expected: callbackId is not -1
     */
    index_ = 0;
    NavigateChangeInfo from;
    NavigateChangeInfo to;
    int32_t callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps.step3: push navDestination B and sync navigation stack
     * @tc.expected: step3. current index is 1
     */
    stack->Push("pageB", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 0);

    /**
     * @tc.steps: step4. remove navigation callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest007
 * @tc.desc: Test add all kinds callback push destination from homeDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node
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
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = true;

    /**
     * @tc.steps: step2. push pageA and sync navigation stack
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step3. set navigation push callback
     * @tc.expected: step3. callback id is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = {.name = "pageA", .isSplit = false};
    NavigateChangeInfo to = {.name = "pageB", .isSplit = false};
    int callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps: step4. push pageA, set navigation is full page and sync navigation stack
     * @tc.expected: step4. index is 1
     */
    stack->Push("pageB", 1);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 1);

    /**
     * @tc.steps: step5. set full page navigation false and update callback result
     */
    ClearChangeCallback();
    navigationPattern->isFullPageNavigation_ = false;
    from.name = "pageB";
    to.name = "pageA";
    callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps:step6. pop to pageA, and sync navigation stack
     */
    index_ = 0;
    stack->Pop();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 0);

    /**
     * @tc.steps: step5.remove navigation transition callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest008
 * @tc.desc: Test add fullScreen callback pop destination to navBar
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node
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
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = true;

    /**
     * @tc.steps: step2. push pageA to stack
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step3. add page callback and fullPage is true
     * @tc.expected: step3. callback id is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = {.name = "pageA", .isSplit = false};
    NavigateChangeInfo to = {.name = "navBar", .isSplit = false};
    int callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps: step4. pop page and sync navigation stack
     * @tc.expected: step4. index is 1
     */
    stack->Pop();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 1);

    /**
     * @tc.steps: step5.remove navigation transition callback
     */
    ClearChangeCallback();
}

/**
 * @tc.name: NavigationCallbackTest009
 * @tc.desc: Test callback pop destination to homeDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationCallbackTestNg, NavigationCallbackTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1.init navigation group node and set navigation home destination
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
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_TRUE(navigationPattern != nullptr);
    navigationPattern->isFullPageNavigation_ = true;
    navigationNode->customHomeDestination_ = CreateDestination("homeDestination");

    /**
     * @tc.steps: step2. push pageA to stack
     */
    stack->Push("pageA", 0);
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();

    /**
     * @tc.steps: step3. add page callback and fullPage is true
     * @tc.expected: step3. callback id is not -1
     */
    index_ = 0;
    NavigateChangeInfo from = {.name = "pageA", .isSplit = false};
    NavigateChangeInfo to = {.name = "homeDestination", .isSplit = false};
    int callbackId = AddNavigationCallback(from, to);
    ASSERT_NE(callbackId, -1);

    /**
     * @tc.steps: step4. pop page and sync navigation stack
     * @tc.expected: step4. index is 1
     */
    stack->Pop();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_EQ(index_, 1);

    /**
     * @tc.steps: step5.remove navigation transition callback
     */
    ClearChangeCallback();
}
} // namespace OHOS::Ace::NG