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
#include "bridge/declarative_frontend/ng/entry_page_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/base/mock_system_bar_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "test";
} // namespace

class NavigationSystemBarStyleTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void NavigationSystemBarStyleTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto context = MockPipelineContext::GetCurrent();
    if (context) {
        context->stageManager_ = nullptr;
    }
}

void NavigationSystemBarStyleTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateIsFullPageNavigation001
 * @tc.desc: Test NavigationPattern.UpdateIsFullPageNavigation()
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSystemBarStyleTestNg, UpdateIsFullPageNavigation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode.
     * @tc.expected: NavigationPattern has no pageNode, is not fullPage.
     */
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(stack, nullptr);
    navigationPattern->SetNavigationStack(stack);
    EXPECT_EQ(navigationPattern->pageNode_.Upgrade(), nullptr);
    EXPECT_FALSE(navigationPattern->IsFullPageNavigation());

    /**
     * @tc.steps: step2. set FrameSize of NavigationGroupNode.
     */
    auto navGeometryNode = navigationGroupNode->GetGeometryNode();
    ASSERT_NE(navGeometryNode, nullptr);
    navGeometryNode->SetFrameSize(SizeF(400.0f, 600.0f));

    /**
     * @tc.steps: step3. create PageNode.
     */
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(1, "pages/Index", "pages", "");
    ASSERT_NE(entryPageInfo, nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(entryPageInfo);
    ASSERT_NE(pagePattern, nullptr);
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    ASSERT_NE(pageNode, nullptr);
    pageNode->SetHostPageId(1);

    /**
     * @tc.steps: step4. set FrameSize of PageNode, add NavigationGroupNode to PageNode.
     * @tc.expected: NavigationPattern has pageNode, is not fullPage.
     */
    auto pageGeometryNode = pageNode->GetGeometryNode();
    ASSERT_NE(pageGeometryNode, nullptr);
    pageGeometryNode->SetFrameSize(SizeF(400.0f, 600.0f));
    navigationGroupNode->MountToParent(pageNode);
    navigationPattern->OnAttachToMainTree();
    ASSERT_NE(navigationPattern->pageNode_.Upgrade(), nullptr);
    ASSERT_FALSE(navigationPattern->IsFullPageNavigation());

    /**
     * @tc.steps: step5. update IsFullPageNavigation.
     * @tc.expected: NavigationPattern is fullPage.
     */
    navigationPattern->UpdateIsFullPageNavigation(navigationGroupNode);
    EXPECT_TRUE(navigationPattern->IsFullPageNavigation());

    /**
     * @tc.steps: step6. change FrameSize of NavigationGroupNode, update IsFullPageNavigation.
     * @tc.expected: NavigationPattern is not fullPage.
     */
    navGeometryNode->SetFrameSize(SizeF(300.0f, 400.0f));
    navigationPattern->UpdateIsFullPageNavigation(navigationGroupNode);
    EXPECT_FALSE(navigationPattern->IsFullPageNavigation());
}

/**
 * @tc.name: IsTopNavDestination001
 * @tc.desc: Test NavigationPattern.IsTopNavDestination()
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSystemBarStyleTestNg, IsTopNavDestination001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode & NavigationPattern.
     */
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(navigationPattern->navigationStack_, nullptr);
    navigationPattern->SetNavigationStack(stack);
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);

    /**
     * @tc.steps: step2. create NavDestination1
     * @tc.expected: NavDestination1 is not top page of Navigation.
     */
    auto customNode1 = CustomNode::CreateCustomNode(1, TEST_TAG);
    auto navDestinationNode1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    customNode1->AddChild(navDestinationNode1);
    EXPECT_FALSE(navigationPattern->IsTopNavDestination(navDestinationNode1));

    /**
     * @tc.steps: step3. add NavDestination1 to stack
     * @tc.expected: NavDestination1 is top page of Navigation.
     */
    auto& pathList = stack->GetPathList();
    pathList.emplace_back("page1", customNode1);
    EXPECT_TRUE(navigationPattern->IsTopNavDestination(navDestinationNode1));

    /**
     * @tc.steps: step4. create NavDestination2, add NavDestination2 to stack
     * @tc.expected: NavDestination1 is not top page of Navigation.
     */
    auto customNode2 = CustomNode::CreateCustomNode(3, TEST_TAG);
    auto navDestinationNode2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 4, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    customNode2->AddChild(navDestinationNode2);
    pathList.emplace_back("page2", customNode2);
    EXPECT_FALSE(navigationPattern->IsTopNavDestination(navDestinationNode1));
    EXPECT_TRUE(navigationPattern->IsTopNavDestination(navDestinationNode2));
}

/**
 * @tc.name: SetSystemBarStyle001
 * @tc.desc: Test NavigationPattern.SetSystemBarStyle()
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSystemBarStyleTestNg, SetSystemBarStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode & NavigationPattern.
     * @tc.expected: NavigationPattern has backupSytle and currStyle.
     */
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(stack, nullptr);
    navigationPattern->SetNavigationStack(stack);
    navigationPattern->isFullPageNavigation_ = true;
    ASSERT_FALSE(navigationPattern->backupStyle_.has_value());
    ASSERT_FALSE(navigationPattern->currStyle_.has_value());

    /**
     * @tc.steps: step2. set SystemBarStyle callbacks of WindowManager.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    std::optional<RefPtr<SystemBarStyle>> styleForSet;
    windowManager->SetSetSystemBarStyleCallBack([&styleForSet](const RefPtr<SystemBarStyle>& style) {
        styleForSet = style;
    });
    std::optional<RefPtr<SystemBarStyle>> styleForGet = AceType::MakeRefPtr<MockSystemBarStyle>();
    windowManager->SetGetSystemBarStyleCallBack([&styleForGet]() -> RefPtr<SystemBarStyle> {
        return styleForGet.value();
    });

    /**
     * @tc.steps: step3. create newStyle1, call NavigationPattern.SetSystemBarStyle.
     * @tc.expected: backupStyle was setted to styleForSet, currStyle and styleForSet were setted to newStyle1.
     */
    std::optional<RefPtr<SystemBarStyle>> newStyle1 = AceType::MakeRefPtr<MockSystemBarStyle>();
    navigationPattern->SetSystemBarStyle(newStyle1.value());
    ASSERT_EQ(navigationPattern->backupStyle_, styleForGet);
    ASSERT_EQ(navigationPattern->currStyle_, newStyle1);
    ASSERT_EQ(styleForSet, newStyle1);

    /**
     * @tc.steps: step4. create newStyle2, call NavigationPattern.SetSystemBarStyle.
     * @tc.expected: only currStyle and styleForSet were updated to newStyle2.
     */
    std::optional<RefPtr<SystemBarStyle>> newStyle2 = AceType::MakeRefPtr<MockSystemBarStyle>();
    navigationPattern->SetSystemBarStyle(newStyle2.value());
    ASSERT_EQ(navigationPattern->backupStyle_, styleForGet);
    ASSERT_EQ(navigationPattern->currStyle_, newStyle2);
    ASSERT_EQ(styleForSet, newStyle2);
}

/**
 * @tc.name: TryRestoreSystemBarStyle001
 * @tc.desc: Test NavigationPattern.TryRestoreSystemBarStyle()
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSystemBarStyleTestNg, TryRestoreSystemBarStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationGroupNode & NavigationPattern.
     * @tc.expected: NavigationPattern has no backupSytle.
     */
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 2, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto stack = AceType::MakeRefPtr<MockNavigationStack>();
    ASSERT_NE(stack, nullptr);
    navigationPattern->SetNavigationStack(stack);
    ASSERT_FALSE(navigationPattern->backupStyle_.has_value());

    /**
     * @tc.steps: step2. set SystemBarStyle callbacks of WindowManager.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    bool funcCalled = false;
    RefPtr<SystemBarStyle> styleForSet = nullptr;
    windowManager->SetSetSystemBarStyleCallBack([&styleForSet, &funcCalled](const RefPtr<SystemBarStyle>& style) {
        styleForSet = style;
        funcCalled = true;
    });

    /**
     * @tc.steps: step3. call restore func.
     * @tc.expected: WindowManager's SetSystemBarStyleCallback won't be called.
     */
    navigationPattern->TryRestoreSystemBarStyle(windowManager);
    ASSERT_FALSE(funcCalled);
    ASSERT_EQ(styleForSet, nullptr);

    /**
     * @tc.steps: step4. set backupStyle of NavigationPattern, then call restore func.
     * @tc.expected: WindowManager's SetSystemBarStyleCallback will be called.
     */
    auto backupStyle = AceType::MakeRefPtr<MockSystemBarStyle>();
    navigationPattern->backupStyle_ = backupStyle;
    navigationPattern->TryRestoreSystemBarStyle(windowManager);
    ASSERT_TRUE(funcCalled);
    ASSERT_EQ(navigationPattern->backupStyle_, styleForSet);
}
} // namespace OHOS::Ace::NG
