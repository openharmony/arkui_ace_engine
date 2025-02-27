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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_route.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"

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
class NavigationGroupNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void NavigationGroupNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::SetUp();
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavigationGroupNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/*
 * @tc.name: RemoveRedundantNavDestinationTest001
 * @tc.desc: Branch: slot == 0 && `no other extra flag set`
 *           Expect: all navDestination are deleted after RemoveRedundantNavDestination called.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveRedundantNavDestinationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
    /**
     * @tc.steps: step3. call RemoveRedundantNavDestination and check the size of navDestinations.
     */
    const int32_t slot = 0;
    bool mockHasChanged = false;
    navigation->RemoveRedundantNavDestination(navigationContent, nullptr, slot, mockHasChanged, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), 0);
    ASSERT_EQ(mockHasChanged, true);
}

/*
 * @tc.name: RemoveRedundantNavDestinationTest002
 * @tc.desc: Branch: slot == preStackSize && `no other extra flag set`
 *           Expect: all navDestination are reserved after RemoveRedundantNavDestination called.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveRedundantNavDestinationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
    /**
     * @tc.steps: step3. call RemoveRedundantNavDestination and check the size of navDestinations.
     */
    const int32_t slot = testNumber;
    bool mockHasChanged = false;
    navigation->RemoveRedundantNavDestination(navigationContent, nullptr, slot, mockHasChanged, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
    }
    ASSERT_EQ(mockHasChanged, false);
}

/*
 * @tc.name: RemoveRedundantNavDestinationTest003
 * @tc.desc: Branch: slot != 0 && `no other extra flag set`
 *           Expect: only the first `slot` slots navDestination are reserved after RemoveRedundantNavDestination called.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeTestNg, RemoveRedundantNavDestinationTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation.
     */
    std::string destNameBase = "dest";
    const int32_t testNumber = 10;
    for (int32_t index = 0; index < testNumber; ++index) {
        mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>(destNameBase + std::to_string(index)));
    }
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    RunNavigationStackSync(navigationPattern);
    auto navigationContent = AceType::DynamicCast<FrameNode>(navigation->GetContentNode());
    ASSERT_NE(navigationContent, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), testNumber);
    for (int32_t index = 0; index < testNumber; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(navDestinationPattern, nullptr);
        ASSERT_EQ(navDestinationPattern->GetName(), destNameBase + std::to_string(index));
    }
    /**
     * @tc.steps: step3. call RemoveRedundantNavDestination and check the size and name of navDestinations.
     */
    const int32_t slot = 4;
    bool mockHasChanged = false;
    navigation->RemoveRedundantNavDestination(navigationContent, nullptr, slot, mockHasChanged, nullptr);
    ASSERT_EQ(static_cast<int32_t>(navigationContent->GetChildren().size()), slot);
    for (int32_t index = 0; index < slot; ++index) {
        auto navDestination = AceType::DynamicCast<FrameNode>(navigationContent->GetChildAtIndex(index));
        ASSERT_NE(navDestination, nullptr);
        auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
        ASSERT_NE(navDestinationPattern, nullptr);
        ASSERT_EQ(navDestinationPattern->GetName(), destNameBase + std::to_string(index));
    }
    ASSERT_EQ(mockHasChanged, true);
}
} // namespace OHOS::Ace::NG