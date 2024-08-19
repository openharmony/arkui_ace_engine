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
        mockNavPathStack->Push(destNameBase + std::to_string(index));
        ASSERT_EQ(mockNavPathStack->GetNavPathId(index), "undefined");
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++ index) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto pattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(pattern, nullptr);
        ASSERT_EQ(std::to_string(pattern->GetNavDestinationId()), mockNavPathStack->GetNavPathId(index));
    }
}

/**
 * @tc.name: NavigationSyncStackTestNg002
 * @tc.desc: NOT_IMPL_YET
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
        mockNavPathStack->Push(destNameBase + std::to_string(index));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    /**
     * @tc.steps: step2. sync stack.
     */
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
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
    const int32_t removedImmediatelyNumber = 3;
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
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber - removedImmediatelyNumber);
}
} // namespace OHOS::Ace::NG