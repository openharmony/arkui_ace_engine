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
#include "test/unittest/core/pattern/navigation/mock_navigation_route.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr char DEST_NAME_BASE[] = "dest";
RefPtr<NavigationManager> GetNavigationManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetNavigationManager() : nullptr;
}

void RunNavigationStackSync(const RefPtr<NavigationPattern>& navigationPattern)
{
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
}

RefPtr<NavigationGroupNode> InitAndCreateNavigation(const RefPtr<MockNavigationStack>& stack)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(stack);
    return AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}
} // namespace

class NavigationManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void NavigationManagerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: NavigationManagerTest001
 * @tc.desc: Test basic ability of get navigationJsonInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. test whether can get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. test whether recoverable can be set
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = InitAndCreateNavigation(mockNavPathStack);
    ASSERT_NE(navigationNode, nullptr);
    ASSERT_EQ(navigationNode->CanRecovery(), false);
    navigationNode->OnInspectorIdUpdate("testTag");
    ASSERT_EQ(navigationNode->CanRecovery(), false);
    navigationNode->SetRecoverable(true);
    ASSERT_EQ(navigationNode->CanRecovery(), true);
    /**
     * @tc.steps: step3. test whether can get navigation recovery info
     */
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto json = navigationManager->GetNavigationJsonInfo();
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: NavigationManagerTest002
 * @tc.desc: Test getting complex navigationJsonInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build navigation
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = InitAndCreateNavigation(mockNavPathStack);
    ASSERT_NE(navigationNode, nullptr);
    const std::string navigationId = "navigationId";
    navigationNode->OnInspectorIdUpdate(navigationId);
    navigationNode->SetRecoverable(true);
    /**
     * @tc.steps: step3. mock stack operation and sync stack
     */
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(DEST_NAME_BASE + std::to_string(index)));
    }
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationNode, navigationPattern);
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    /**
     * @tc.steps: step4. mock set recovery property and check
     */
    const int32_t recoveryDestNum = 5;
    for (int32_t index = recoveryDestNum; index < testNumber; ++ index) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        navDestination->SetRecoverable(false);
    }
    for (int32_t index = 0; index < recoveryDestNum; ++ index) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        // the default value of navdestination->CanRecovery() should be true
        ASSERT_EQ(navDestination->CanRecovery(), index < recoveryDestNum ? true : false);
    }
    /**
     * @tc.steps: step5. get json info and do verify
     */
    auto json = navigationManager->GetNavigationJsonInfo();
    std::cout << "Got Json: " << json->ToString() << std::endl;
    ASSERT_NE(json, nullptr);
    ASSERT_EQ(json->IsArray(), true);
    auto navigationInfo = json->GetArrayItem(0);
    ASSERT_NE(navigationInfo, nullptr);
    auto stackInfo = navigationInfo->GetValue("stack");
    ASSERT_NE(stackInfo, nullptr);
    ASSERT_EQ(stackInfo->IsArray(), true);
    ASSERT_EQ(stackInfo->GetArraySize(), recoveryDestNum);
    for (int32_t index = 0; index < recoveryDestNum; ++ index) {
        auto destInfo = stackInfo->GetArrayItem(index);
        ASSERT_NE(destInfo, nullptr);
        auto nameInfo = destInfo->GetValue("name");
        ASSERT_NE(nameInfo, nullptr);
        ASSERT_EQ(nameInfo->IsString(), true);
        ASSERT_EQ(nameInfo->GetString(), DEST_NAME_BASE + std::to_string(index));
    }
}

/**
 * @tc.name: NavigationManagerTest003
 * @tc.desc: Test storage navigationJsonInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build navigation
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = InitAndCreateNavigation(mockNavPathStack);
    ASSERT_NE(navigationNode, nullptr);
    const std::string navigationId = "navigationId";
    navigationNode->OnInspectorIdUpdate(navigationId);
    navigationNode->SetRecoverable(true);
    /**
     * @tc.steps: step3. mock stack operation and sync stack
     */
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(DEST_NAME_BASE + std::to_string(index)));
    }
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationNode, navigationPattern);
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    /**
     * @tc.steps: step4. mock set recovery property and check
     */
    const int32_t recoveryDestNum = 5;
    for (int32_t index = recoveryDestNum; index < testNumber; ++ index) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        navDestination->SetRecoverable(false);
    }
    /**
     * @tc.steps: step5. get json info and do storage
     */
    auto json = navigationManager->GetNavigationJsonInfo();
    navigationManager->StorageNavigationRecoveryInfo(std::move(json));
    auto recoveryDests = navigationManager->GetNavigationRecoveryInfo(navigationId);
    ASSERT_EQ(static_cast<int32_t>(recoveryDests.size()), recoveryDestNum);
    for (int32_t index = 0; index < recoveryDestNum; ++ index) {
        auto name = recoveryDests[index].name;
        ASSERT_EQ(name, DEST_NAME_BASE + std::to_string(index));
    }
}

/**
 * @tc.name: NavigationManagerTest004
 * @tc.desc: Test cache navigation node animation
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build navigation
     */
    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNode->contentNode_ = contentNode;
    auto preFrameNode = AceType::DynamicCast<FrameNode>(preNode);
    navigationManager->SetNavNodeInTransition(nullptr, preFrameNode);
    navigationManager->SetPreNodeNeverSet(false);
    /**
     * @tc.steps: step3. Update previous navigation render group property
     */
    navigationManager->UpdatePreNavNodeRenderGroupProperty();
    bool preNodeNeverSet = navigationManager->preNodeNeverSet_;
    ASSERT_EQ(preNodeNeverSet, false);
}

/**
 * @tc.name: NavigationManagerTest005
 * @tc.desc: Test cache navigation node animation
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build navigation
     */
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    curNode->contentNode_ = contentNode;
    auto curFrameNode = AceType::DynamicCast<FrameNode>(curNode);
    navigationManager->SetNavNodeInTransition(curFrameNode, nullptr);
    /**
     * @tc.steps: step3. Update current navigation render group property
     */
    navigationManager->UpdateCurNavNodeRenderGroupProperty();
    bool currentNodeNeverSet = navigationManager->currentNodeNeverSet_;
    bool curNodeAnimationCached = navigationManager->curNodeAnimationCached_;
    ASSERT_EQ(currentNodeNeverSet, false);
    ASSERT_EQ(curNodeAnimationCached, false);
}

/**
 * @tc.name: NavigationManagerTest006
 * @tc.desc: Test cache navigation node animation
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build navigation
     */
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    curNode->contentNode_ = contentNode;
    auto curFrameNode = AceType::DynamicCast<FrameNode>(curNode);
    navigationManager->SetNavNodeInTransition(curFrameNode, nullptr);
    /**
     * @tc.steps: step3. Reset current navigation render group property
     */
    navigationManager->ResetCurNavNodeRenderGroupProperty();
    bool curNodeAnimationCached = navigationManager->curNodeAnimationCached_;
    bool currentNodeNeverSet = navigationManager->currentNodeNeverSet_;
    ASSERT_EQ(curNodeAnimationCached, false);
    ASSERT_EQ(currentNodeNeverSet, false);
}

/**
 * @tc.name: NavigationManagerTest007
 * @tc.desc: Test unconfig navigation and disable animation
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, NavigationManagerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build navigation
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto navigationNode = InitAndCreateNavigation(mockNavPathStack);
    ASSERT_NE(navigationNode, nullptr);
    const std::string navigationId = "navigationId";
    navigationNode->OnInspectorIdUpdate(navigationId);
    navigationNode->SetRecoverable(true);
    /**
     * @tc.steps: step3. Unconfig navigation and disable animation
     */
    auto preNode = AceType::DynamicCast<FrameNode>(navigationNode->GetNavBarNode());
    auto curNode = AceType::DynamicCast<FrameNode>(navigationNode->GetTopDestination());
    navigationManager->hasCacheNavigationNodeEnable_ = true;
    navigationNode->UnconfigureNavigationAndDisableAnimation(preNode, curNode);

    auto managerCurNode = navigationManager->curNavNode_;
    auto managerPreNode = navigationManager->preNavNode_;
    bool isInAnimation = navigationManager->IsNavigationInAnimation();
    ASSERT_EQ(managerCurNode, nullptr);
    ASSERT_EQ(managerPreNode, nullptr);
    ASSERT_EQ(isInAnimation, false);
}

/**
 * @tc.name: ButtonsRectChangeListener001
 * @tc.desc: Test the event notification mechanism of navigationManager
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, ButtonsRectChangeListener001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get navigation manager
     * @tc.expected: step1. manager has no listener.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_TRUE(navigationManager->buttonsRectChangeListeners_.empty());

    /**
     * @tc.steps: step2. Register one listener to manager.
     * @tc.expected: step2. manager has one listener.
     */
    constexpr int32_t LISTENER_ID1 = 1;
    constexpr int32_t LISTENER_ID2 = 2;
    int32_t callTimes1 = 0;
    auto listener1 = [&callTimes1]() { callTimes1++; };
    navigationManager->AddButtonsRectChangeListener(LISTENER_ID1, std::move(listener1));
    ASSERT_EQ(navigationManager->buttonsRectChangeListeners_.size(), 1);

    /**
     * @tc.steps: step3. Trigger buttonsRect change event.
     * @tc.expected: step3. listener will be notified.
     */
    navigationManager->OnContainerModalButtonsRectChange();
    ASSERT_EQ(callTimes1, 1);

    /**
     * @tc.steps: step4. Register new listener with existed listenerId.
     * @tc.expected: step4. New listener register successfully, old listener will be removed.
     */
    int32_t callTimes2 = 0;
    auto listener2 = [&callTimes2]() { callTimes2++; };
    navigationManager->AddButtonsRectChangeListener(LISTENER_ID1, std::move(listener2));
    ASSERT_EQ(navigationManager->buttonsRectChangeListeners_.size(), 1);

    /**
     * @tc.steps: step5. Trigger buttonsRect change event again.
     * @tc.expected: step5. listener2 will be notified, listener1 won't be notified.
     */
    navigationManager->OnContainerModalButtonsRectChange();
    ASSERT_EQ(callTimes1, 1);
    ASSERT_EQ(callTimes2, 1);

    /**
     * @tc.steps: step6. Remove listener with unregistered listenerId.
     * @tc.expected: step6. no listener will be removed.
     */
    navigationManager->RemoveButtonsRectChangeListener(LISTENER_ID2);
    ASSERT_EQ(navigationManager->buttonsRectChangeListeners_.size(), 1);

    /**
     * @tc.steps: step7. Remove listener with registered listenerId..
     * @tc.expected: step7. last listener will be removed.
     */
    navigationManager->RemoveButtonsRectChangeListener(LISTENER_ID1);
    ASSERT_TRUE(navigationManager->buttonsRectChangeListeners_.empty());
}


} // namespace OHOS::Ace::NG
