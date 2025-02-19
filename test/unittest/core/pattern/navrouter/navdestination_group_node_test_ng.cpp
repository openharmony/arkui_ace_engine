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
#include "test/unittest/core/pattern/navigation/mock_navigation_stack.h"
#include "test/unittest/core/pattern/navigation/mock_navigation_route.h"

#define protected public
#define private public
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_ANIMATION_ID = -1;
constexpr int32_t TRANSITION_COMBINATIONS = 6;

RefPtr<NavigationGroupNode> CreateNavigationNode(const RefPtr<MockNavigationStack>& stack)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(stack);
    return AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}

void SetNavigationToNavDestination(
    const RefPtr<NavDestinationGroupNode>& navDestination, const RefPtr<NavigationGroupNode>& navigation)
{
    CHECK_NULL_VOID(navDestination);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    navDestinationPattern->SetNavigationNode(navigation);
}
}

class NavDestinationGroupNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void NavDestinationGroupNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::SetUp();
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void NavDestinationGroupNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: SetSystemTransitionTest001
 * @tc.desc: Branch: if navDestinationTransitionDelegate_ == nullptr
 *           Expect: reset navDestinationTransitionDelegate_ to nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, SetSystemTransitionTest001, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    ASSERT_NE(navDestination, nullptr);
    ASSERT_EQ(navDestination->navDestinationTransitionDelegate_, nullptr);
    NavDestinationTransitionDelegate mockDelegate = [](NavigationOperation operation, bool isEnter) {
        return std::nullopt;
    };
    navdestinationModel.SetCustomTransition(std::move(mockDelegate));
    ASSERT_NE(navDestination->navDestinationTransitionDelegate_, nullptr);
    navdestinationModel.SetSystemTransitionType(NavigationSystemTransitionType::DEFAULT);
    ASSERT_EQ(navDestination->navDestinationTransitionDelegate_, nullptr);
}

/**
 * @tc.name: DoTransitionTest001
 * @tc.desc: Branch: if navDestinationTransitionDelegate_ == nullptr && systemTransitionType is one of
 *                   FADE, EXPLODE, SLIDE_RIGHT, SLIDE_BOTTOM
 *           Expect: do system-transition and return animationId
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoTransitionTest001, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    ASSERT_NE(navDestination, nullptr);
    auto navigationNode = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_EQ(navigationNode->animationId_, 0);
    SetNavigationToNavDestination(navDestination, navigationNode);
    ASSERT_EQ(navDestination->navDestinationTransitionDelegate_, nullptr);
    navdestinationModel.SetSystemTransitionType(NavigationSystemTransitionType::FADE);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, TRANSITION_COMBINATIONS * 1);
    navdestinationModel.SetSystemTransitionType(NavigationSystemTransitionType::EXPLODE);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, TRANSITION_COMBINATIONS * 2);
    navdestinationModel.SetSystemTransitionType(NavigationSystemTransitionType::SLIDE_BOTTOM);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, TRANSITION_COMBINATIONS * 3);
    navdestinationModel.SetSystemTransitionType(NavigationSystemTransitionType::SLIDE_RIGHT);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, TRANSITION_COMBINATIONS * 4);
}

/**
 * @tc.name: DoTransitionTest002
 * @tc.desc: Branch: if navDestinationTransitionDelegate_ == nullptr && systemTransitionType is NOT one of
 *                   FADE, EXPLODE, SLIDE_RIGHT, SLIDE_BOTTOM
 *           Expect: do default animation and return INVALID_ANIMATION_ID
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoTransitionTest002, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    ASSERT_NE(navDestination, nullptr);
    auto navigationNode = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_EQ(navigationNode->animationId_, 0);
    SetNavigationToNavDestination(navDestination, navigationNode);
    ASSERT_EQ(navDestination->navDestinationTransitionDelegate_, nullptr);
    navdestinationModel.SetSystemTransitionType(NavigationSystemTransitionType::NONE);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, 0);
}

/**
 * @tc.name: DoTransitionTest003
 * @tc.desc: Branch: if navDestinationTransitionDelegate_ != nullptr && navDestinationTransitionDelegate return array
 *           Expect: do custom transition accordingly and return animationId
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoTransitionTest003, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    ASSERT_NE(navDestination, nullptr);
    auto navigationNode = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_EQ(navigationNode->animationId_, 0);
    SetNavigationToNavDestination(navDestination, navigationNode);
    ASSERT_EQ(navDestination->navDestinationTransitionDelegate_, nullptr);
    NavDestinationTransitionDelegate mockDelegate = [](NavigationOperation operation, bool isEnter) {
        return std::vector<NavDestinationTransition>();
    };
    navdestinationModel.SetCustomTransition(std::move(mockDelegate));
    ASSERT_NE(navDestination->navDestinationTransitionDelegate_, nullptr);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_NE(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, TRANSITION_COMBINATIONS);
}

/**
 * @tc.name: DoTransitionTest004
 * @tc.desc: Branch: if navDestinationTransitionDelegate_ != nullptr && navDestinationTransitionDelegate return nullopt
 *           Expect: do system-default transition accordingly and return INVALID_ANIMATION_ID
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoTransitionTest004, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    ASSERT_NE(navDestination, nullptr);
    auto navigationNode = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_EQ(navigationNode->animationId_, 0);
    SetNavigationToNavDestination(navDestination, navigationNode);
    ASSERT_EQ(navDestination->navDestinationTransitionDelegate_, nullptr);
    NavDestinationTransitionDelegate mockDelegate = [](NavigationOperation operation, bool isEnter) {
        return std::nullopt;
    };
    navdestinationModel.SetCustomTransition(std::move(mockDelegate));
    ASSERT_NE(navDestination->navDestinationTransitionDelegate_, nullptr);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::PUSH, true), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::PUSH, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::POP, true), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::POP, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::REPLACE, true), INVALID_ANIMATION_ID);
    ASSERT_EQ(navDestination->DoTransition(NavigationOperation::REPLACE, false), INVALID_ANIMATION_ID);
    ASSERT_EQ(navigationNode->animationId_, 0);
}
} // namespace OHOS::Ace::NG