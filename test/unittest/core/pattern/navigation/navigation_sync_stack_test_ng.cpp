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
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

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

class NavigationSyncStackTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

void NavigationSyncStackTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationSyncStackTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationSyncStackTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: NavigationSyncStackTestNg001
 * @tc.desc: Test whether the id of navPathInfo is correctly updated after each stack sync
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, frameNode and pattern.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock js-stack and call stack sync.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(destNameBase + std::to_string(index)));
        ASSERT_EQ(mockNavPathStack->GetNavDestinationId(index), "undefined");
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++ index) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto pattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(pattern, nullptr);
        ASSERT_EQ(std::to_string(pattern->GetNavDestinationId()), mockNavPathStack->GetNavDestinationId(index));
    }
}

/**
 * @tc.name: NavigationSyncStackTestNg002
 * @tc.desc: Test whether the destinations were deleted correctly while doing animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    /**
     * @tc.steps: step2. sync stack.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    /**
     * @tc.steps: step3. mock stack operation, left two navDestinations in stack.
     */
    const int32_t newStackSize = 4;
    mockNavPathStack->PopToIndex(newStackSize - 1);
    ASSERT_EQ(static_cast<int32_t>(mockNavPathStack->GetAllPathIndex().size()), newStackSize);
    /**
     * @tc.steps: step4. mock property of animation. There are 5 types animation in total,
     *  Respectively are ENTER_POP, EXIT_POP, ENTER_PUSH, EXIT_PUSH, EXIT_PUSH_TO_REMOVE.
     */
    const int32_t animationTypes = 5;
    // make sure all animation-taged navdestination are not top of pre stack
    const std::vector<PageTransitionType> transitionTypes = {
        /* enter pop node, remove immediately if remove called */
        PageTransitionType::ENTER_POP,
        /* exit pop node, delay remove if remove called, because it will be removed in animation's finish callback */
        PageTransitionType::EXIT_POP,
        /* enter push node, remove immediately if remove called */
        PageTransitionType::ENTER_PUSH,
        /* general exit push node, remove immediately if remove called */
        PageTransitionType::EXIT_PUSH,
        /**
         * EXIT_PUSH_TO_REMOVE node case, delay remove if remove called,
         * because it will also be removed in animation's finish callback
         */
        PageTransitionType::EXIT_PUSH,
    };
    for (int32_t count = 0; count < animationTypes; ++ count) {
        auto navDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(newStackSize + count));
        ASSERT_NE(navDestination, nullptr);
        navDestination->SetTransitionType(transitionTypes[count]);
        navDestination->SetIsOnAnimation(true);
        if (count == animationTypes - 1) {
            navDestination->SetNeedRemoveInPush(true);
        }
    }
    /**
     * @tc.steps: step5. sync stack again. And after sync the number of navDestinations in
     *  mainTree should be last number (which is testNumber) minus removedImmediatelyNumber.
     */
    RunNavigationStackSync(navigationPattern);
}

/**
 * @tc.name: NavigationSyncStackTestNg003
 * @tc.desc: Test whether the destination was force created when NOT marked NEW_INSTANCE
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    std::string destNameBase = "dest";
    const int32_t testNumber = 3;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    /**
     * @tc.steps: step2. sync stack.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    std::vector<std::string> navDestinationIds(testNumber);
    for (int32_t index = 0; index < testNumber; ++ index) {
        navDestinationIds[index] = mockNavPathStack->GetNavDestinationId(index);
    }
    /**
     * @tc.steps: step3. mock stack operation pop and push destination with the same name
     */
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->Pop();
    }
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(destNameBase + std::to_string(index)));
    }
    // run sync again
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step4. check whether the destinations were reused. should be reused.
     */
    for (int32_t index = 0; index < testNumber; ++ index) {
        ASSERT_EQ(navDestinationIds[index], mockNavPathStack->GetNavDestinationId(index));
    }
}

/**
 * @tc.name: NavigationSyncStackTestNg004
 * @tc.desc: Test whether the destination was force created when marked NEW_INSTANCE
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    std::string destNameBase = "dest";
    const int32_t testNumber = 3;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    /**
     * @tc.steps: step2. sync stack.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    std::vector<std::string> navDestinationIds(testNumber);
    for (int32_t index = 0; index < testNumber; ++ index) {
        navDestinationIds[index] = mockNavPathStack->GetNavDestinationId(index);
    }
    /**
     * @tc.steps: step3. mock stack operation pop and push destination with the same name and NEW_INSTANCE flag
     */
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->Pop();
    }
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(
            MockNavPathInfo(destNameBase + std::to_string(index)), true, LaunchMode::NEW_INSTANCE);
    }
    ASSERT_EQ(static_cast<int32_t>(mockNavPathStack->Size()), testNumber);
    // run sync again
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step4. check whether the destinations were reused. should NOT be reused.
     */
    for (int32_t index = 0; index < testNumber; ++ index) {
        ASSERT_NE(navDestinationIds[index], mockNavPathStack->GetNavDestinationId(index));
    }
    /**
     * @tc.steps: step5. check whether the property "NeedRemoveInPush" was set correctly.
     */
    // the animating node is still remained
    int32_t navDestinationsNumber = static_cast<int32_t>(navigationContent->GetChildren().size());
    for (int32_t index = 0; index < navDestinationsNumber; ++ index) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
}

/**
 * @tc.name: NavigationSyncStackTestNg005
 * @tc.desc: Test whether the order of navDestinations is correct when doing consecutive animation
 *           with NEW_INSTANCE marked. In detail, mock operation 'pop + push with new_instance' twice
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    std::string destNameBase = "dest";
    const int32_t testNumber = 3;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(MockNavPathInfo(destNameBase + std::to_string(index)));
    }
    RunNavigationStackSync(navigationPattern);
    /**
     * after run stack sync, the order of navDestination belike:
     *  | dest1 | dest2 | dest3 | <- child of navigationContent with max index
     */
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    /**
     * @tc.steps: step2. mark the top - 1 destination needRemoveInPush and 'onAnimation'
     *  to mock the first 'pop + push with new_instance' operation
     */
    auto needRemovedDest =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(testNumber - 2));
    needRemovedDest->SetNeedRemoveInPush(true);
    needRemovedDest->SetIsOnAnimation(true);
    /**
     * @tc.steps: step3. operation stack to mock the second 'pop + push with new_instance' operation
     */
    // front stack(NavPathStack) should contains only two page, so pop twice
    mockNavPathStack->Pop();
    mockNavPathStack->Pop();
    mockNavPathStack->MockPushPath(
        MockNavPathInfo(destNameBase + std::to_string(testNumber)), true, LaunchMode::NEW_INSTANCE);
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step3. check the order of total 4(= testNumber + 1) navDestinations, it should belike:
     *  | dest1 | dest2 | dest3 | dest4 | <- child of navigationContent with max index
     *              ^       ^       ^
     *              |       |       |
     *   needRemoveInPush   |   new top of stack
     *              needRemoveInPush
     */
}
} // namespace OHOS::Ace::NG