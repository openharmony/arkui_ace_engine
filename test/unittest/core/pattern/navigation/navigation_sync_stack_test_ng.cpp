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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"

#include "core/components_ng/manager/navigation/navigation_manager.h"

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
    MockContainer::SetUp(MockPipelineContext::GetCurrent());
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
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
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
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
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
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
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
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
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
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
    ASSERT_NE(mockNavPathStack, nullptr);
    navigationModel.SetNavigationStack(mockNavPathStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    std::string destNameBase = "dest";
    const int32_t testNumber = 3;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
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
        auto info = AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index));
        info->isEntry_ = true;
        info->mode = static_cast<int32_t>(LaunchMode::NEW_INSTANCE);
        info->needBuildNewInstance = true;
        mockNavPathStack->MockPushPath(info);
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
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
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
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(testNumber)),
        true, LaunchMode::NEW_INSTANCE);
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

/**
 * @tc.name: NavigationSyncStackTestNg006
 * @tc.desc: Test interface removeByNavDestinationId
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg006, TestSize.Level1)
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
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step2. got navDestinationId
     */
    ASSERT_EQ(mockNavPathStack->Size(), testNumber);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    std::vector<std::string> allNavdestinationIds;
    for (int32_t index = 0; index < testNumber; index++) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(navDestinationPattern, nullptr);
        allNavdestinationIds.push_back(std::to_string(navDestinationPattern->GetNavDestinationId()));
    }
    for (int32_t index = 0; index < mockNavPathStack->Size(); index++) {
        auto navDestinationId = mockNavPathStack->GetNavDestinationId(index);
        ASSERT_EQ(navDestinationId, allNavdestinationIds[index]);
    }
    /**
     * @tc.steps: step3. do remove valid navDestinationId and check
     */
    auto removeRet = mockNavPathStack->MockRemoveByNavDestinationId(allNavdestinationIds.front());
    ASSERT_EQ(removeRet, true);
    ASSERT_EQ(mockNavPathStack->Size(), testNumber - 1);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber - 1);
    /**
     * @tc.steps: step4. do remove invalid navDestinationId and check
     */
    removeRet = mockNavPathStack->MockRemoveByNavDestinationId("invalid");
    ASSERT_EQ(removeRet, false);
    ASSERT_EQ(mockNavPathStack->Size(), testNumber - 1);
}

/**
 * @tc.name: NavigationSyncStackTestNg007
 * @tc.desc: Test call interface removeByNavDestinationId several times
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg007, TestSize.Level1)
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
    const int32_t testNumber = 5;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step2. got navDestinationId
     */
    ASSERT_EQ(mockNavPathStack->Size(), testNumber);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    std::vector<std::string> allNavdestinationIds;
    for (int32_t index = 0; index < testNumber; index++) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(navDestinationPattern, nullptr);
        allNavdestinationIds.push_back(std::to_string(navDestinationPattern->GetNavDestinationId()));
    }
    for (int32_t index = 0; index < mockNavPathStack->Size(); index++) {
        auto navDestinationId = mockNavPathStack->GetNavDestinationId(index);
        ASSERT_EQ(navDestinationId, allNavdestinationIds[index]);
    }
    /**
     * @tc.steps: step2. do remove several times.
     */
    const int32_t removeTimes = 3;
    for (int32_t index = 0; index < removeTimes; ++index) {
        auto removeVal = mockNavPathStack->MockRemoveByNavDestinationId(allNavdestinationIds[index]);
        ASSERT_EQ(removeVal, true);
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNumber - removeTimes);
    for (int32_t index = 0; index < testNumber - removeTimes; ++index) {
        ASSERT_EQ(mockNavPathStack->GetNavDestinationIdByIndex(index), allNavdestinationIds[index + removeTimes]);
    }
}

/**
 * @tc.name: NavigationSyncStackTestNg008
 * @tc.desc: Test interface removeByName
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg008, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNumber = 5;
    for (int32_t index = 0; index < testNumber; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step2. do remove by name.
     */
    std::vector<std::string> removeDests;
    for (int32_t index = 0; index < testNumber; index += 2) {
        removeDests.push_back(destNameBase + std::to_string(index));
    }
    for (auto name: removeDests) {
        auto removeCnt = mockNavPathStack->MockRemoveByName(name);
        ASSERT_EQ(removeCnt, 1);
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNumber - static_cast<int32_t>(removeDests.size()));
}

/**
 * @tc.name: NavigationSyncStackTestNg009
 * @tc.desc: Test interface removeByName
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg009, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t sameNameCnt = 3;
    for (int32_t index = 0; index < sameNameCnt; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase));
    }
    const int32_t diffNameCnt = 2;
    for (int32_t index = 0; index < diffNameCnt; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    RunNavigationStackSync(navigationPattern);
    /**
     * @tc.steps: step2. do remove by name.
     */
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffNameCnt + sameNameCnt);
    ASSERT_EQ(mockNavPathStack->Size(), diffNameCnt + sameNameCnt);
    auto removeCnt = mockNavPathStack->MockRemoveByName(destNameBase);
    ASSERT_EQ(removeCnt, sameNameCnt);
    ASSERT_EQ(mockNavPathStack->Size(), diffNameCnt);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffNameCnt);
}

/**
 * @tc.name: NavigationSyncStackTestNg010
 * @tc.desc: Test interface removeByName, but with invalid Name
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg010, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 3;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. do remove by invalid name.
     */
    auto removeCnt = mockNavPathStack->MockRemoveByName(destNameBase);
    ASSERT_EQ(removeCnt, 0);
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
}

/**
 * @tc.name: NavigationSyncStackTestNg011
 * @tc.desc: Test interface removeByIndexes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg011, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 5;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. do remove by indexes.
     */
    RunNavigationStackSync(navigationPattern);
    const std::vector<int32_t> removeIndexes = {1, 2, 3};
    auto removeCnt = mockNavPathStack->MockRemoveByInexes(removeIndexes);
    ASSERT_EQ(removeCnt, static_cast<int32_t>(removeIndexes.size()));
    ASSERT_EQ(mockNavPathStack->Size(), testNum - static_cast<int32_t>(removeIndexes.size()));
}

/**
 * @tc.name: NavigationSyncStackTestNg012
 * @tc.desc: Test interface removeByIndexes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg012, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 5;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. do remove by indexes.
     */
    RunNavigationStackSync(navigationPattern);
    const std::vector<int32_t> removeIndexes = {1, 1, 1};
    auto removeCnt = mockNavPathStack->MockRemoveByInexes(removeIndexes);
    ASSERT_EQ(removeCnt, 1);
    ASSERT_EQ(mockNavPathStack->Size(), testNum - 1);
}

/**
 * @tc.name: NavigationSyncStackTestNg013
 * @tc.desc: Test interface removeByIndexes, complex case
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg013, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 5;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. do remove by indexes.
     */
    RunNavigationStackSync(navigationPattern);
    const std::vector<int32_t> invalidIndexes = {-1, -1, -1};
    auto removeCnt = mockNavPathStack->MockRemoveByInexes(invalidIndexes);
    ASSERT_EQ(removeCnt, 0);
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
}

/**
 * @tc.name: NavigationSyncStackTestNg014
 * @tc.desc: Test interface popToIndex invalid index
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg014, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 5;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNum);
    /**
     * @tc.steps: step3. do popToIndex, run sync stack and verify again.
     */
    const int32_t popToIndex = -1;
    mockNavPathStack->MockPopToIndex(popToIndex);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNum);
}

/**
 * @tc.name: NavigationSyncStackTestNg015
 * @tc.desc: Test interface popToIndex
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg015, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 5;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNum);
    /**
     * @tc.steps: step3. do popToIndex, run sync stack and verify again.
     */
    const int32_t popToIndex = 1;
    mockNavPathStack->MockPopToIndex(popToIndex);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), popToIndex + 1);
}

/**
 * @tc.name: NavigationSyncStackTestNg016
 * @tc.desc: Test interface popToName
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg016, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t testNum = 5;
    for (int32_t index = 0; index < testNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), testNum);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNum);
    /**
     * @tc.steps: step3. do popToIndex, run sync stack and verify again.
     */
    const int32_t popToIndex = 1;
    auto allNames = mockNavPathStack->GetAllPathName();
    ASSERT_EQ(static_cast<int32_t>(allNames.size()), testNum);
    const std::string popToName = allNames[popToIndex];
    auto returnVal = mockNavPathStack->MockPopToName(popToName);
    ASSERT_EQ(returnVal, popToIndex);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), popToIndex + 1);
}

/**
 * @tc.name: NavigationSyncStackTestNg017
 * @tc.desc: Test interface popToName
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg017, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase));
    const int32_t diffDestNum = 3;
    for (int32_t index = 0; index < diffDestNum; ++ index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), 1 + diffDestNum);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), 1 + diffDestNum);
    /**
     * @tc.steps: step3. do popToIndex, run sync stack and verify again.
     */
    const int32_t popToIndex = 0;
    auto allNames = mockNavPathStack->GetAllPathName();
    ASSERT_EQ(static_cast<int32_t>(allNames.size()), 1 + diffDestNum);
    const std::string popToName = allNames[popToIndex];
    auto returnVal = mockNavPathStack->MockPopToName(popToName);
    ASSERT_EQ(returnVal, popToIndex);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), 1);
}

/**
 * @tc.name: NavigationSyncStackTestNg019
 * @tc.desc: Test interface popToName with invalid name
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg019, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    const int32_t diffDestNum = 3;
    for (int32_t index = 0; index < diffDestNum; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), diffDestNum);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum);
    /**
     * @tc.steps: step3. do popToIndex, run sync stack and verify again.
     */
    const std::string popToName = destNameBase;
    auto removeSize = mockNavPathStack->MockPopToName(popToName);
    ASSERT_EQ(removeSize, -1);
    RunNavigationStackSync(navigationPattern);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum);
}

/**
 * @tc.name: NavigationSyncStackTestNg020
 * @tc.desc: Test interface moveToTop
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg020, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase));
    const int32_t diffDestNum = 3;
    for (int32_t index = 0; index < diffDestNum; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), diffDestNum + 1);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum + 1);
    /**
     * @tc.steps: step3. do moveToTop, run sync stack and verify again.
     */
    const std::string moveToName = destNameBase;
    auto returnVal = mockNavPathStack->MockMoveToTop(moveToName);
    ASSERT_EQ(returnVal, 0);
    auto allNames = mockNavPathStack->GetAllPathName();
    ASSERT_EQ(static_cast<int32_t>(allNames.size()), diffDestNum + 1);
    ASSERT_EQ(allNames.back(), moveToName);
    RunNavigationStackSync(navigationPattern);
    auto topNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetLastChild());
    ASSERT_NE(topNavDestination, nullptr);
    auto navDestinationPattern = topNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetName(), moveToName);
}


/**
 * @tc.name: NavigationGetPathStackTestNg001
 * @tc.desc: Test interface getPathStack with empty path stack
 *           Condition: this.pathArray.length() == 0
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationGetPathStackTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern, but do not push destination into stack.
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
    ASSERT_EQ(mockNavPathStack->Size(), 0);
    /**
     * @tc.steps: step2. sync stack and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), 0);
    /**
     * @tc.steps: step3. do getPathStack, test whether get the correct array of pathStack.
     */
    auto returnPathArray = mockNavPathStack->MockGetPathStack();
    auto realLength = returnPathArray.size();
    ASSERT_EQ(realLength, 0);
}

/**
 * @tc.name: NavigationGetPathStackTestNg002
 * @tc.desc: Test interface getPathStack after several navDestination page is push
 *           Condition: this.pathArray.length() != 0
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationGetPathStackTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern, and push some destination page into stack.
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
    ASSERT_EQ(mockNavPathStack->Size(), 0);
    const std::string destNameBase = "dest";
    const int32_t diffDestNum = 5;
    for (int32_t index = 0; index < diffDestNum; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), diffDestNum);
    /**
     * @tc.steps: step2. sync stack and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum);
    /**
     * @tc.steps: step3. do getPathStack, test whether get the correct array of pathStack.
     */
    auto returnPathArray = mockNavPathStack->MockGetPathStack();
    auto realLength = returnPathArray.size();
    ASSERT_EQ(realLength, diffDestNum);
    for (int32_t index = 0; index < realLength; index++) {
        auto realName = returnPathArray[index]->GetName();
        ASSERT_EQ(realName, destNameBase + std::to_string(index));
        auto isEntry = returnPathArray[index]->GetIsEntry();
        ASSERT_EQ(isEntry, false);
    }
}

/**
 * @tc.name: NavigationSetPathStackTestNg001
 * @tc.desc: Test interface setPathStack with empty path info.
 *           Condition: this.setPathStack(empty)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSetPathStackTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern, and push some destination page into stack.
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
    ASSERT_EQ(mockNavPathStack->Size(), 0);
    const std::string destNameBase = "dest";
    const int32_t diffDestNum = 5;
    for (int32_t index = 0; index < diffDestNum; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), diffDestNum);
    /**
     * @tc.steps: step2. sync stack and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum);
    /**
     * @tc.steps: step3. do setPathStack, test whether get the correct array of pathStack.
     */
    std::vector<RefPtr<MockNavPathInfo>> newPathArray;
    newPathArray.clear();
    mockNavPathStack->MockSetPathStack(newPathArray);
    ASSERT_EQ(mockNavPathStack->Size(), 0);

    /**
     * @tc.steps: step4. sync again and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), 1);
}

/**
 * @tc.name: NavigationSetPathStackTestNg002
 * @tc.desc: Test interface setPathStack with several path infos.
 *           Condition: this.setPathStack(newPathArray)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSetPathStackTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, stack, frameNode and pattern, but do not push destination into stack.
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
    ASSERT_EQ(mockNavPathStack->Size(), 0);
    const std::string destNameBase = "dest";
    const int32_t diffDestNum = 5;
    for (int32_t index = 0; index < diffDestNum; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), diffDestNum);
    /**
     * @tc.steps: step2. sync stack and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum);
    /**
     * @tc.steps: step3. do setPathStack, test whether get the correct array of pathStack.
     */
    std::vector<RefPtr<MockNavPathInfo>> newPathArray;
    const std::string setNameBase = "set";
    const int32_t setDestNum = 6;
    for (int32_t index = 0; index < setDestNum; ++index) {
        newPathArray.push_back(AceType::MakeRefPtr<MockNavPathInfo>(setNameBase + std::to_string(index)));
    }
    mockNavPathStack->MockSetPathStack(newPathArray);
    ASSERT_EQ(mockNavPathStack->Size(), setDestNum);

    /**
     * @tc.steps: step4. sync stack again and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), setDestNum);
}

/**
 * @tc.name: NavigationSyncStackTestNg021
 * @tc.desc: Test interface moveToTop with invalid name
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationSyncStackTestNg021, TestSize.Level1)
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
    const std::string destNameBase = "dest";
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase));
    const int32_t diffDestNum = 3;
    for (int32_t index = 0; index < diffDestNum; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    ASSERT_EQ(mockNavPathStack->Size(), diffDestNum + 1);
    /**
     * @tc.steps: step2. sync stack 1st and do verify.
     */
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = navigationNode->GetContentNode();
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), diffDestNum + 1);
    /**
     * @tc.steps: step3. do moveToTop, run sync stack and verify again.
     */
    const std::string moveToName = destNameBase + "invalid";
    auto returnVal = mockNavPathStack->MockMoveToTop(moveToName);
    ASSERT_EQ(returnVal, -1);
    auto allNames = mockNavPathStack->GetAllPathName();
    ASSERT_EQ(static_cast<int32_t>(allNames.size()), diffDestNum + 1);
    ASSERT_NE(allNames.back(), moveToName);
    RunNavigationStackSync(navigationPattern);
    auto topNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(navigationContent->GetLastChild());
    ASSERT_NE(topNavDestination, nullptr);
    auto navDestinationPattern = topNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_NE(navDestinationPattern->GetName(), moveToName);
}

/**
 * @tc.name: GetFromCacheNodeTest
 * @tc.desc: no branch
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, GetFromCacheNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationNode and Stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    
    /**
     * @tc.steps: step2. add Node to cacheNode
     */
    auto navNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navNode->nodeId_ = 11;
    mockNavPathStack->cacheNodes_.emplace_back(std::make_pair("pageA", navNode));
    
    auto navNode2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navNode2->nodeId_ = 22;
    mockNavPathStack->cacheNodes_.emplace_back(std::make_pair("pageB", navNode2));
    
    auto navNode3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 102, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navNode3->nodeId_ = 33;
    mockNavPathStack->cacheNodes_.emplace_back(std::make_pair("pageC", navNode3));
    
    /**
     * @tc.steps: step3. test GetFromCacheNode
     */
    auto tmp = mockNavPathStack->GetFromCacheNode(11);
    RefPtr<UINode> retNode = nullptr;
    if (tmp) {
        retNode = tmp.value().second;
    }
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(retNode);
    ASSERT_EQ(navNode, navDestination);
    
    auto ret = mockNavPathStack->GetFromCacheNode(12);
    ASSERT_EQ(ret, std::nullopt);
}

/**
 * @tc.name: AddCacheNode
 * @tc.desc: branch if(name.empty() || uiNode == nullptr)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, AddCacheNodeTest1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationNode and Stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    
    /**
     * @tc.steps: step2. test addCacheNode
     */
    mockNavPathStack->AddCacheNode("null", nullptr);
    ASSERT_EQ(mockNavPathStack->cacheNodes_.empty(), true);
}

/**
 * @tc.name: AddCacheNode
 * @tc.desc: branch if (navDestination)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, AddCacheNodeTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationNode and Stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    
    /**
     * @tc.steps: step2. test addCacheNode
     */
    auto navNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 104, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navNode->nodeId_ = 11;
    ASSERT_EQ(navNode->IsCacheNode(), false);
    mockNavPathStack->AddCacheNode("pageA", navNode);
    ASSERT_NE(mockNavPathStack->cacheNodes_.empty(), true);
    ASSERT_NE(navNode->IsCacheNode(), true);
}

/**
 * @tc.name: NavigationAutoCleanTest001
 * @tc.desc: Test auto clean clears invisible destinations when stackSizeLimit is exceeded.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationAutoCleanTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation with five destinations.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    const int32_t stackSize = 5;
    const int32_t stackSizeLimit = 2;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    /**
     * @tc.steps: step2. limit active page nodes to two.
     * @tc.expected: the first three destinations are cleaned and marked autoCleaned.
     */
    navigationPattern->config_.stackSizeLimit = stackSizeLimit;
    ASSERT_EQ(navigationPattern->GetAutoCleanRestoreMinIndex(stackSize - 1, stackSize), stackSize - stackSizeLimit);
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    ASSERT_EQ(static_cast<int32_t>(navPathList.size()), stackSize);
    for (int32_t index = 0; index < stackSize - stackSizeLimit; ++index) {
        EXPECT_EQ(navPathList[index].second, nullptr);
        EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(index));
    }
    for (int32_t index = stackSize - stackSizeLimit; index < stackSize; ++index) {
        EXPECT_NE(navPathList[index].second, nullptr);
        EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(index));
    }
}

/**
 * @tc.name: NavigationAutoCleanTest002
 * @tc.desc: Test auto cleaned destinations are recreated and the saved state flag is cleared.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationAutoCleanTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation and auto clean old destinations.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    const int32_t stackSize = 3;
    const int32_t cleanLimit = 2;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    navigationPattern->config_.stackSizeLimit = cleanLimit;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    ASSERT_TRUE(mockNavPathStack->IsAutoCleaned(0));
    mockNavPathStack->SaveStateToJsCallback(0, "dest0", 0, "{\"count\":1}");

    /**
     * @tc.steps: step2. enlarge limit and process restore.
     * @tc.expected: cleaned destination nodes are recreated and autoCleaned state is cleared.
     */
    navigationPattern->config_.stackSizeLimit = stackSize;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(0));
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    ASSERT_EQ(static_cast<int32_t>(navPathList.size()), stackSize);
    for (int32_t index = 0; index < stackSize; ++index) {
        EXPECT_NE(navPathList[index].second, nullptr);
        EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(index));
        EXPECT_EQ(mockNavPathStack->GetAutoCleanedState(index), "");
    }
}

/**
 * @tc.name: NavigationAutoCleanTest003
 * @tc.desc: Test auto cleaned destinations before lastStandardIndex are not recreated.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationAutoCleanTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation and auto clean old destinations.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    const int32_t stackSize = 5;
    const int32_t cleanLimit = 2;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    navigationPattern->config_.stackSizeLimit = cleanLimit;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    for (int32_t index = 0; index < stackSize - cleanLimit; ++index) {
        ASSERT_TRUE(mockNavPathStack->IsAutoCleaned(index));
    }

    /**
     * @tc.steps: step2. enlarge limit and restore from index 2.
     * @tc.expected: only autoCleaned destinations with index >= lastStandardIndex are recreated.
     */
    const int32_t lastStandardIndex = 2;
    navigationPattern->config_.stackSizeLimit = stackSize;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(lastStandardIndex));
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    for (int32_t index = 0; index < lastStandardIndex; ++index) {
        EXPECT_EQ(navPathList[index].second, nullptr);
        EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(index));
    }
    for (int32_t index = lastStandardIndex; index < stackSize; ++index) {
        EXPECT_NE(navPathList[index].second, nullptr);
        EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(index));
    }
}

/**
 * @tc.name: NavigationAutoCleanTest004
 * @tc.desc: Test auto clean defers an animating destination and marks it when pending clean is cleared.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationAutoCleanTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation and mark one invisible destination animating.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    const int32_t stackSize = 4;
    const int32_t stackSizeLimit = 1;
    const int32_t animatingIndex = 1;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto animatingDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[animatingIndex].second));
    ASSERT_NE(animatingDestination, nullptr);
    animatingDestination->SetIsOnAnimation(true);

    /**
     * @tc.steps: step2. process auto clean while the destination is animating.
     * @tc.expected: the animating destination is kept and marked pendingToClean.
     */
    navigationPattern->config_.stackSizeLimit = stackSizeLimit;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    auto animatingPattern = animatingDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(animatingPattern, nullptr);
    EXPECT_NE(navPathList[animatingIndex].second, nullptr);
    EXPECT_TRUE(animatingPattern->GetPendingToClean());
    EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(animatingIndex));
    EXPECT_EQ(navigationPattern->pendingToCleanCount_, 1);

    /**
     * @tc.steps: step3. simulate transition finish callback clearing pendingToClean.
     * @tc.expected: JS stack autoCleaned flag is marked and pending count is cleared.
     */
    animatingPattern->SetPendingToClean(false);
    EXPECT_FALSE(animatingPattern->GetPendingToClean());
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(animatingIndex));
    EXPECT_EQ(navigationPattern->pendingToCleanCount_, 0);
}

/**
 * @tc.name: NavigationAutoCleanTest005
 * @tc.desc: Test onSaveState saves state to stack and onRestoreState receives the saved state.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationAutoCleanTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create destination and fire onSaveState.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest0"));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    ASSERT_EQ(static_cast<int32_t>(navPathList.size()), 1);
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[0].second));
    ASSERT_NE(destination, nullptr);
    auto eventHub = destination->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    const std::string savedState = "{\"title\":\"page\"}";
    eventHub->SetOnSaveState([savedState]() { return savedState; });
    eventHub->FireOnSaveState();
    EXPECT_EQ(mockNavPathStack->GetAutoCleanedState(0), savedState);

    /**
     * @tc.steps: step2. mark the destination autoCleaned and restore it.
     * @tc.expected: onRestoreState receives the saved state and the stack state is cleared.
     */
    std::string restoredState;
    eventHub->SetOnRestoreState([&restoredState](const std::string& state) { restoredState = state; });
    auto destinationPattern = destination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destinationPattern, nullptr);
    mockNavPathStack->MarkAutoCleanedFlag(destinationPattern->GetNavDestinationId());
    bool isStandard = false;
    ASSERT_TRUE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 0, isStandard));
    EXPECT_EQ(restoredState, savedState);
    EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(0));
    EXPECT_EQ(mockNavPathStack->GetAutoCleanedState(0), "");
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest001
 * @tc.desc: Test SetNavigationConfiguration with recyclePagesOnLowMemory=true registers memory notification.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);
    EXPECT_TRUE(navigationPattern->configInitialed_);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto& nodes = context->nodesToNotifyMemoryLevel_;
    bool found = false;
    for (auto nodeId : nodes) {
        if (nodeId == navigationNode->GetId()) {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest002
 * @tc.desc: Test SetNavigationConfiguration with recyclePagesOnLowMemory=false does not register.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_FALSE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest003
 * @tc.desc: Test re-setting config to recyclePagesOnLowMemory=false unregisters notification.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);

    NG::NavigationConfiguration config2;
    config2.stackSizeLimit = 5;
    config2.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config2);
    EXPECT_FALSE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest004
 * @tc.desc: Test re-setting config to recyclePagesOnLowMemory=true does not re-register (already registered).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);

    NG::NavigationConfiguration config2;
    config2.stackSizeLimit = 5;
    config2.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config2);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest005
 * @tc.desc: Test OnNotifyMemoryLevel with valid low memory level triggers RecyclePagesOnLowMemory.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest005, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    navigationPattern->OnNotifyMemoryLevel(1);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest006
 * @tc.desc: Test OnNotifyMemoryLevel with invalid level does not trigger recycling.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest006, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    for (int32_t invalidLevel : {0, 3, 4, 7, 100, -1}) {
        navigationPattern->OnNotifyMemoryLevel(invalidLevel);
    }
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest007
 * @tc.desc: Test OnNotifyMemoryLevel does nothing when recyclePagesOnLowMemory is false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest007, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->config_.recyclePagesOnLowMemory = false;
    navigationPattern->OnNotifyMemoryLevel(1);
    EXPECT_FALSE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest008
 * @tc.desc: Test OnNotifyMemoryLevel with all valid memory levels (1,2,5,6).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest008, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    for (int32_t validLevel : {1, 2, 5, 6}) {
        navigationPattern->OnNotifyMemoryLevel(validLevel);
    }
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest009
 * @tc.desc: Test RecyclePagesOnLowMemory recycles invisible destinations before lastStandardIndex.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest009, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 5;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    ASSERT_EQ(static_cast<int32_t>(navPathList.size()), stackSize);
    navigationNode->lastStandardIndex_ = 3;
    navigationPattern->RecyclePagesOnLowMemory();

    for (int32_t index = 0; index < 3; ++index) {
        EXPECT_EQ(navPathList[index].second, nullptr);
        EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(index));
    }
    for (int32_t index = 3; index < stackSize; ++index) {
        EXPECT_NE(navPathList[index].second, nullptr);
        EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(index));
    }
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest010
 * @tc.desc: Test RecyclePagesOnLowMemory defers animating destination with pendingToClean.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest010, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 4;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    const int32_t animatingIndex = 1;
    auto animatingDest = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[animatingIndex].second));
    ASSERT_NE(animatingDest, nullptr);
    animatingDest->SetIsOnAnimation(true);

    navigationNode->lastStandardIndex_ = 3;
    navigationPattern->RecyclePagesOnLowMemory();

    auto animatingPattern = animatingDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(animatingPattern, nullptr);
    EXPECT_NE(navPathList[animatingIndex].second, nullptr);
    EXPECT_TRUE(animatingPattern->GetPendingToClean());
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest011
 * @tc.desc: Test RegisterMemoryLevelNotification and UnregisterMemoryLevelNotification.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest011, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto nodeId = navigationNode->GetId();

    navigationPattern->RegisterMemoryLevelNotification();
    auto& nodes = context->nodesToNotifyMemoryLevel_;
    bool found = false;
    for (auto id : nodes) {
        if (id == nodeId) {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);

    navigationPattern->UnregisterMemoryLevelNotification();
    found = false;
    for (auto id : nodes) {
        if (id == nodeId) {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest012
 * @tc.desc: Test OnDetachFromMainTree calls UnregisterMemoryLevelNotification.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest012, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto nodeId = navigationNode->GetId();
    navigationPattern->OnDetachFromMainTree();
    bool found = false;
    for (auto id : context->nodesToNotifyMemoryLevel_) {
        if (id == nodeId) {
            found = true;
            break;
        }
    }
    EXPECT_FALSE(found);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest013
 * @tc.desc: Test RestoreAutoCleanedDestination sets isStandard=true for STANDARD mode destination.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest013, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest0"));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    ASSERT_EQ(static_cast<int32_t>(navPathList.size()), 1);
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[0].second));
    ASSERT_NE(destination, nullptr);
    auto destPattern = destination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    destination->SetNavDestinationMode(NavDestinationMode::STANDARD);
    mockNavPathStack->MarkAutoCleanedFlag(destPattern->GetNavDestinationId());
    bool isStandard = false;
    ASSERT_TRUE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 0, isStandard));
    EXPECT_TRUE(isStandard);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest014
 * @tc.desc: Test RestoreAutoCleanedDestination sets isStandard=false for DIALOG mode destination.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest014, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest0"));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    ASSERT_EQ(static_cast<int32_t>(navPathList.size()), 1);
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[0].second));
    ASSERT_NE(destination, nullptr);
    auto destPattern = destination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    destination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    mockNavPathStack->MarkAutoCleanedFlag(destPattern->GetNavDestinationId());
    bool isStandard = true;
    ASSERT_TRUE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 0, isStandard));
    EXPECT_FALSE(isStandard);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest015
 * @tc.desc: Test ProcessAutoCleanAndRestore stops at STANDARD destination when restoring.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest015, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    const int32_t cleanLimit = 1;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationPattern->config_.stackSizeLimit = cleanLimit;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    for (int32_t index = 0; index < stackSize - cleanLimit; ++index) {
        ASSERT_TRUE(mockNavPathStack->IsAutoCleaned(index));
    }

    navigationPattern->config_.stackSizeLimit = stackSize;
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto dest2 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[2].second));
    ASSERT_NE(dest2, nullptr);
    dest2->SetNavDestinationMode(NavDestinationMode::STANDARD);

    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(0));
    EXPECT_NE(navPathList[2].second, nullptr);
    EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(2));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest016
 * @tc.desc: Test RecyclePagesOnLowMemory with preTopNavPath_ keeps remainDestination.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest016, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 4;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto remainDest = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[1].second));
    ASSERT_NE(remainDest, nullptr);

    navigationPattern->preTopNavPath_ = std::make_pair("dest1", navPathList[1].second);
    navigationNode->lastStandardIndex_ = 3;
    navigationPattern->RecyclePagesOnLowMemory();

    auto remainPattern = remainDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(remainPattern, nullptr);
    EXPECT_NE(navPathList[1].second, nullptr);
    EXPECT_TRUE(remainPattern->GetPendingToClean());
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest017
 * @tc.desc: Test RecyclePagesOnLowMemory with no destinations recycles nothing.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest017, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationNode->lastStandardIndex_ = 0;
    navigationPattern->RecyclePagesOnLowMemory();
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    EXPECT_EQ(static_cast<int32_t>(navPathList.size()), 0);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest018
 * @tc.desc: Test RecyclePagesOnLowMemory skips null entries in navPathList.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest018, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    navPathList[0].second = nullptr;

    navigationNode->lastStandardIndex_ = 2;
    navigationPattern->RecyclePagesOnLowMemory();

    auto dest1 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[1].second));
    EXPECT_EQ(navPathList[1].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(1));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest019
 * @tc.desc: Test SetNavigationConfiguration after init with stackSizeLimit<=0 resets it.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest019, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_EQ(navigationPattern->config_.stackSizeLimit, 5);

    NG::NavigationConfiguration config2;
    config2.stackSizeLimit = -1;
    config2.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config2);
    EXPECT_EQ(navigationPattern->config_.stackSizeLimit, -1);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest020
 * @tc.desc: Test SetNavigationConfiguration after init with stackSizeLimit>0 does not reset it.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest020, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_EQ(navigationPattern->config_.stackSizeLimit, 5);

    NG::NavigationConfiguration config2;
    config2.stackSizeLimit = 10;
    config2.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config2);
    EXPECT_EQ(navigationPattern->config_.stackSizeLimit, 5);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest021
 * @tc.desc: Test SetNavigationConfiguration after init: false->true does not update config.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest021, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_FALSE(navigationPattern->config_.recyclePagesOnLowMemory);

    NG::NavigationConfiguration config2;
    config2.stackSizeLimit = 5;
    config2.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config2);
    EXPECT_FALSE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest022
 * @tc.desc: Test SetNavigationConfiguration after init: same false value does not trigger unregister.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest022, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 5;
    config.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config);

    NG::NavigationConfiguration config2;
    config2.stackSizeLimit = 5;
    config2.recyclePagesOnLowMemory = false;
    navigationPattern->SetNavigationConfiguration(config2);
    EXPECT_FALSE(navigationPattern->config_.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest023
 * @tc.desc: Test RecyclePagesOnLowMemory with no preTopNavPath_ (no remainDestination).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest023, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationPattern->preTopNavPath_.reset();
    navigationNode->lastStandardIndex_ = 2;
    navigationPattern->RecyclePagesOnLowMemory();

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest024
 * @tc.desc: Test RecyclePagesOnLowMemory with IsFullScreenOverlay=true uses overlayNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest024, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto dest0 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[0].second));
    ASSERT_NE(dest0, nullptr);
    dest0->SetIsFullScreenOverlay(true);

    navigationNode->lastStandardIndex_ = 2;
    navigationPattern->RecyclePagesOnLowMemory();

    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest025
 * @tc.desc: Test RecyclePagesOnLowMemory with lastStandardIndex=0 (nothing to recycle).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest025, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationNode->lastStandardIndex_ = 0;
    navigationPattern->RecyclePagesOnLowMemory();

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    for (int32_t index = 0; index < stackSize; ++index) {
        EXPECT_NE(navPathList[index].second, nullptr);
    }
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest026
 * @tc.desc: Test RecyclePagesOnLowMemory with lastStandardIndex=-1 (nothing to recycle).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest026, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationNode->lastStandardIndex_ = -1;
    navigationPattern->RecyclePagesOnLowMemory();

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    for (int32_t index = 0; index < stackSize; ++index) {
        EXPECT_NE(navPathList[index].second, nullptr);
    }
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest027
 * @tc.desc: Test RecyclePagesOnLowMemory with CanRecovery=false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest027, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto dest0 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[0].second));
    ASSERT_NE(dest0, nullptr);
    dest0->SetRecoverable(false);

    navigationNode->lastStandardIndex_ = 2;
    navigationPattern->RecyclePagesOnLowMemory();

    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
    EXPECT_FALSE(mockNavPathStack->GetAutoCleanedCanRecovery(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest028
 * @tc.desc: Test RestoreAutoCleanedDestination with index < 0 returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest028, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    bool isStandard = false;
    EXPECT_FALSE(navigationPattern->RestoreAutoCleanedDestination(navPathList, -1, isStandard));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest029
 * @tc.desc: Test RestoreAutoCleanedDestination with index >= size returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest029, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    bool isStandard = false;
    EXPECT_FALSE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 99, isStandard));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest030
 * @tc.desc: Test RestoreAutoCleanedDestination with !IsAutoCleaned returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest030, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest0"));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    bool isStandard = false;
    EXPECT_FALSE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 0, isStandard));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest031
 * @tc.desc: Test RestoreAutoCleanedDestination with explicit stackIndex >= 0.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest031, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest0"));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto destination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[0].second));
    ASSERT_NE(destination, nullptr);
    auto destPattern = destination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    mockNavPathStack->MarkAutoCleanedFlag(destPattern->GetNavDestinationId());
    bool isStandard = false;
    EXPECT_TRUE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 0, isStandard, 0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest032
 * @tc.desc: Test RestoreAutoCleanedDestination with stackIndex not autoCleaned returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest032, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    bool isStandard = false;
    EXPECT_FALSE(navigationPattern->RestoreAutoCleanedDestination(navPathList, 0, isStandard, 0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest033
 * @tc.desc: Test ProcessAutoCleanAndRestore with DIALOG mode destination continues iterating.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest033, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    const int32_t cleanLimit = 1;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto dest2 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[2].second));
    ASSERT_NE(dest2, nullptr);
    dest2->SetNavDestinationMode(NavDestinationMode::DIALOG);

    auto dest1 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[1].second));
    ASSERT_NE(dest1, nullptr);
    dest1->SetNavDestinationMode(NavDestinationMode::STANDARD);

    navigationPattern->config_.stackSizeLimit = cleanLimit;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    for (int32_t index = 0; index < stackSize - cleanLimit; ++index) {
        ASSERT_TRUE(mockNavPathStack->IsAutoCleaned(index));
    }

    navigationPattern->config_.stackSizeLimit = stackSize;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(0));
    EXPECT_NE(navPathList[2].second, nullptr);
    EXPECT_FALSE(mockNavPathStack->IsAutoCleaned(2));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest034
 * @tc.desc: Test ProcessAutoCleanAndRestore with pendingToClean destination clears it.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest034, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    const int32_t cleanLimit = 1;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto dest2 = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(navPathList[2].second));
    ASSERT_NE(dest2, nullptr);
    auto dest2Pattern = dest2->GetPattern<NavDestinationPattern>();
    ASSERT_NE(dest2Pattern, nullptr);

    dest2Pattern->SetPendingToClean(true);
    EXPECT_TRUE(dest2Pattern->GetPendingToClean());

    navigationPattern->config_.stackSizeLimit = cleanLimit;
    ASSERT_TRUE(navigationPattern->ProcessAutoCleanAndRestore(stackSize - 1));
    EXPECT_FALSE(dest2Pattern->GetPendingToClean());
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest035
 * @tc.desc: Test ProcessAutoCleanAndRestore returns false when NeedRestoreOrAutoClean is false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest035, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->config_.stackSizeLimit = 0;
    EXPECT_FALSE(navigationPattern->ProcessAutoCleanAndRestore(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest036
 * @tc.desc: Test RegisterMemoryLevelNotification with null host does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest036, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterMemoryLevelNotification();
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest037
 * @tc.desc: Test UnregisterMemoryLevelNotification with null host does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest037, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->UnregisterMemoryLevelNotification();
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest038
 * @tc.desc: Test RecyclePagesOnLowMemory with null navigationStack_ does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest038, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto savedStack = navigationPattern->navigationStack_;
    navigationPattern->navigationStack_ = nullptr;
    navigationPattern->RecyclePagesOnLowMemory();
    navigationPattern->navigationStack_ = savedStack;
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest039
 * @tc.desc: Test OnNotifyMemoryLevel each valid level independently triggers RecyclePagesOnLowMemory.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest039, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    navigationNode->lastStandardIndex_ = 2;

    navigationPattern->OnNotifyMemoryLevel(1);
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest040
 * @tc.desc: Test OnNotifyMemoryLevel with MEMORY_LEVEL_CRITICAL(2) triggers RecyclePagesOnLowMemory.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest040, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    navigationNode->lastStandardIndex_ = 2;

    navigationPattern->OnNotifyMemoryLevel(2);
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest041
 * @tc.desc: Test OnNotifyMemoryLevel with MEMORY_LEVEL_BACKGROUND_LOW(5) triggers RecyclePagesOnLowMemory.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest041, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    navigationNode->lastStandardIndex_ = 2;

    navigationPattern->OnNotifyMemoryLevel(5);
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest042
 * @tc.desc: Test OnNotifyMemoryLevel with MEMORY_LEVEL_BACKGROUND_CRITICAL(6) triggers RecyclePagesOnLowMemory.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest042, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    navigationPattern->config_.recyclePagesOnLowMemory = true;
    navigationNode->lastStandardIndex_ = 2;

    navigationPattern->OnNotifyMemoryLevel(6);
    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest043
 * @tc.desc: Test SetNavigationConfiguration with recyclePagesOnLowMemory=true and stackSizeLimit=0.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest043, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    NG::NavigationConfiguration config;
    config.stackSizeLimit = 0;
    config.recyclePagesOnLowMemory = true;
    navigationPattern->SetNavigationConfiguration(config);
    EXPECT_TRUE(navigationPattern->config_.recyclePagesOnLowMemory);
    EXPECT_EQ(navigationPattern->config_.stackSizeLimit, 0);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest044
 * @tc.desc: Test NavigationConfiguration default values.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest044, TestSize.Level1)
{
    NG::NavigationConfiguration config;
    EXPECT_EQ(config.stackSizeLimit, 0);
    EXPECT_FALSE(config.needClearContentStack);
    EXPECT_FALSE(config.recyclePagesOnLowMemory);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest045
 * @tc.desc: Test RecyclePagesOnLowMemory recycled=true updates contentNode dirty flag.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest045, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    const int32_t stackSize = 3;
    for (int32_t index = 0; index < stackSize; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest" + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto contentNode = navigationNode->GetContentNode();
    ASSERT_NE(contentNode, nullptr);

    navigationNode->lastStandardIndex_ = 2;
    navigationPattern->RecyclePagesOnLowMemory();

    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_TRUE(mockNavPathStack->IsAutoCleaned(0));
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest046
 * @tc.desc: Test RecyclePagesOnLowMemory with navDestination that is not NavDestinationGroupNode (null cast).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest046, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto& navPathList = mockNavPathStack->GetAllNavDestinationNodes();
    auto plainNode = FrameNode::CreateFrameNode("plain", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(plainNode, nullptr);
    navPathList.emplace_back(std::make_pair("plain", plainNode));

    navigationNode->lastStandardIndex_ = 1;
    navigationPattern->RecyclePagesOnLowMemory();

    EXPECT_NE(navPathList[0].second, nullptr);
}

/**
 * @tc.name: NavigationRecycleOnLowMemoryTest047
 * @tc.desc: Test ProcessAutoCleanAndRestore with empty navPathList returns false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationSyncStackTestNg, NavigationRecycleOnLowMemoryTest047, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->config_.stackSizeLimit = 5;
    EXPECT_FALSE(navigationPattern->ProcessAutoCleanAndRestore(0));
}
} // namespace OHOS::Ace::NG
