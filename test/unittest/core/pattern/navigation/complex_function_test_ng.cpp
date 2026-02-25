/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define protected public
#define private public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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

struct NavCtx {
    RefPtr<NavigationGroupNode> navigation;
    RefPtr<NavigationPattern> pattern;
    RefPtr<FrameNode> content;
    RefPtr<MockNavigationStack> stack;
};

NavCtx CreateNavigationWithDestinations(int32_t count)
{
    NavCtx ctx;
    ctx.stack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(ctx.stack);
    ctx.navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    if (!ctx.navigation) {
        return ctx;
    }
    ctx.pattern = ctx.navigation->GetPattern<NavigationPattern>();
    if (!ctx.pattern) {
        return ctx;
    }
    for (int32_t index = 0; index < count; ++index) {
        ctx.stack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest_" + std::to_string(index)));
    }
    RunNavigationStackSync(ctx.pattern);
    ctx.content = AceType::DynamicCast<FrameNode>(ctx.navigation->GetContentNode());
    return ctx;
}

RefPtr<NavDestinationGroupNode> GetDestByIndex(const RefPtr<FrameNode>& content, int32_t index)
{
    return AceType::DynamicCast<NavDestinationGroupNode>(content ? content->GetChildAtIndex(index) : nullptr);
}
} // namespace

class NavigationGroupNodeComplexFunctTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
        EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
        MockContainer::SetUp();
        MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest001
 * @tc.desc: Cover non-navDestination child removal branch.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a navigation content tree with two destinations.
     */
    auto ctx = CreateNavigationWithDestinations(2);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    ASSERT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 2);

    /**
     * @tc.steps: step2. Add one non-navDestination child to content.
     */
    auto extraNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(extraNode, nullptr);
    ctx.content->AddChild(extraNode);
    ASSERT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 3);

    /**
     * @tc.steps: step3. Call RemoveRedundantNavDestination and verify extra child is removed.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, nullptr, 2, hasChanged, nullptr);
    EXPECT_TRUE(hasChanged);
    EXPECT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 2);
    EXPECT_EQ(ctx.content->GetChildIndex(extraNode), -1);
}

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest002
 * @tc.desc: Cover remainDestination branch when current top is not a new instance(pop path).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create four destinations and select tail node as remainChild.
     */
    auto ctx = CreateNavigationWithDestinations(4);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.pattern, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    auto remain = GetDestByIndex(ctx.content, 3);
    ASSERT_NE(remain, nullptr);
    /**
     * @tc.steps: step2. Set pop path state by marking current top as old instance.
     */
    ctx.pattern->isCurTopNewInstance_ = false;

    /**
     * @tc.steps: step3. Execute remove and verify remainChild index and flags.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, remain, 2, hasChanged, nullptr);
    EXPECT_TRUE(hasChanged);
    EXPECT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 3);
    EXPECT_FALSE(remain->NeedRemoveInPush());
    EXPECT_EQ(ctx.content->GetChildIndex(remain), 2);
}

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest003
 * @tc.desc: Cover remainDestination push path, animating NeedRemoveInPush branch and reorder after loop.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build push-new-instance scenario with remain and animating destination.
     */
    auto ctx = CreateNavigationWithDestinations(5);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.pattern, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    auto curTop = GetDestByIndex(ctx.content, 2);
    auto remain = GetDestByIndex(ctx.content, 3);
    auto animNeedRemove = GetDestByIndex(ctx.content, 4);
    ASSERT_NE(curTop, nullptr);
    ASSERT_NE(remain, nullptr);
    ASSERT_NE(animNeedRemove, nullptr);

    /**
     * @tc.steps: step2. Configure animation and NeedRemoveInPush state for tail destination.
     */
    ctx.pattern->isCurTopNewInstance_ = true;
    animNeedRemove->SetIsOnAnimation(true);
    animNeedRemove->SetNeedRemoveInPush(true);

    /**
     * @tc.steps: step3. Execute remove and verify reordered indices.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, remain, 3, hasChanged, nullptr);
    EXPECT_FALSE(hasChanged);
    EXPECT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 5);
    EXPECT_TRUE(remain->NeedRemoveInPush());

    auto animIndex = ctx.content->GetChildIndex(animNeedRemove);
    auto remainIndex = ctx.content->GetChildIndex(remain);
    auto curTopIndex = ctx.content->GetChildIndex(curTop);
    EXPECT_NE(animIndex, -1);
    EXPECT_NE(remainIndex, -1);
    EXPECT_NE(curTopIndex, -1);
    EXPECT_GT(remainIndex, animIndex);
    EXPECT_GT(curTopIndex, remainIndex);
}

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest004
 * @tc.desc: Cover animation EXIT_POP branch which should skip immediate removal.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create destination list and mark tail as EXIT_POP on animation.
     */
    auto ctx = CreateNavigationWithDestinations(3);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    auto exitPopDest = GetDestByIndex(ctx.content, 2);
    ASSERT_NE(exitPopDest, nullptr);
    exitPopDest->SetIsOnAnimation(true);
    exitPopDest->SetTransitionType(PageTransitionType::EXIT_POP);

    /**
     * @tc.steps: step2. Execute RemoveRedundantNavDestination.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, nullptr, 2, hasChanged, nullptr);
    /**
     * @tc.steps: step3. Verify EXIT_POP node is not removed immediately.
     */
    EXPECT_FALSE(hasChanged);
    EXPECT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 3);
    EXPECT_EQ(ctx.content->GetChildIndex(exitPopDest), 2);
}

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest005
 * @tc.desc: Cover hideNodes_ and PROXY branch (primary node queued for remove).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare PROXY destination and bind its primary destination.
     */
    auto ctx = CreateNavigationWithDestinations(3);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    auto primaryNode = GetDestByIndex(ctx.content, 0);
    auto proxyNode = GetDestByIndex(ctx.content, 2);
    ASSERT_NE(primaryNode, nullptr);
    ASSERT_NE(proxyNode, nullptr);
    ctx.navigation->preLastStandardIndex_ = 0;
    proxyNode->SetNavDestinationType(NavDestinationType::PROXY);
    proxyNode->SetNavDestinationMode(NavDestinationMode::DIALOG);
    proxyNode->SetPrimaryNode(primaryNode);

    /**
     * @tc.steps: step2. Execute remove to hit hideNodes/proxy branch.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, nullptr, 1, hasChanged, proxyNode);
    /**
     * @tc.steps: step3. Verify hideNodes and primaryNodesToBeRemoved are updated.
     */
    EXPECT_TRUE(hasChanged);
    ASSERT_EQ(ctx.navigation->hideNodes_.size(), 1u);
    EXPECT_EQ(ctx.navigation->hideNodes_[0].first, proxyNode);
    EXPECT_FALSE(proxyNode->GetCanReused());
    ASSERT_EQ(ctx.navigation->primaryNodesToBeRemoved_.size(), 1u);
    EXPECT_EQ(ctx.navigation->primaryNodesToBeRemoved_[0], primaryNode);
}

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest006
 * @tc.desc: Cover STANDARD node branch when preLastStandardNode equals candidate, node enters hideNodes_.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare STANDARD candidate and set preLastStandardIndex.
     */
    auto ctx = CreateNavigationWithDestinations(3);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    auto candidate = GetDestByIndex(ctx.content, 2);
    ASSERT_NE(candidate, nullptr);
    ctx.navigation->preLastStandardIndex_ = 0;

    /**
     * @tc.steps: step2. Execute remove with candidate as preLastStandardNode.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, nullptr, 2, hasChanged, candidate);
    /**
     * @tc.steps: step3. Verify candidate is moved into hideNodes.
     */
    EXPECT_FALSE(hasChanged);
    EXPECT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 3);
    ASSERT_EQ(ctx.navigation->hideNodes_.size(), 1u);
    EXPECT_EQ(ctx.navigation->hideNodes_[0].first, candidate);
}

/**
 * @tc.name: RemoveRedundantNavDestinationComplexTest007
 * @tc.desc: Cover direct removal branch when candidate index is smaller than preLastStandardIndex_.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationGroupNodeComplexFunctTestNg, RemoveRedundantNavDestinationComplexTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create destination list and set large preLastStandardIndex.
     */
    auto ctx = CreateNavigationWithDestinations(3);
    ASSERT_NE(ctx.navigation, nullptr);
    ASSERT_NE(ctx.content, nullptr);
    auto candidate = GetDestByIndex(ctx.content, 2);
    ASSERT_NE(candidate, nullptr);
    ctx.navigation->preLastStandardIndex_ = 100;

    /**
     * @tc.steps: step2. Execute RemoveRedundantNavDestination.
     */
    bool hasChanged = false;
    ctx.navigation->RemoveRedundantNavDestination(ctx.content, nullptr, 2, hasChanged, nullptr);
    /**
     * @tc.steps: step3. Verify candidate is directly removed.
     */
    EXPECT_TRUE(hasChanged);
    EXPECT_EQ(static_cast<int32_t>(ctx.content->GetChildren().size()), 2);
    EXPECT_EQ(ctx.content->GetChildIndex(candidate), -1);
}
} // namespace OHOS::Ace::NG
