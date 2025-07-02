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

#define protected public
#define private public
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAVIGATION_ID1 = "Navigation1";
const std::string PAGE1 = "Page1";
const std::string PARAM1 = "Param1";
constexpr char INTENT_PARAM_KEY[] = "ohos.insightIntent.executeParam.param";
constexpr char INTENT_NAVIGATION_ID_KEY[] = "ohos.insightIntent.pageParam.navigationId";
constexpr char INTENT_NAVDESTINATION_NAME_KEY[] = "ohos.insightIntent.pageParam.navDestinationName";

RefPtr<NavigationManager> GetNavigationManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetNavigationManager() : nullptr;
}

RefPtr<NavigationGroupNode> CreateNavigationNode(const RefPtr<MockNavigationStack>& stack)
{
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    if (!navigationPattern) {
        return nullptr;
    }
    navigationPattern->SetNavigationStack(stack);
    return navigationGroupNode;
}

std::string BuildSerializedIntentInfo(
    const std::string& navigationInspectorId, const std::string& navDestinationName, const std::string& param)
{
    auto intentJson = JsonUtil::Create(true);
    intentJson->Put(INTENT_PARAM_KEY, JsonUtil::ParseJsonString(param));
    intentJson->Put(INTENT_NAVIGATION_ID_KEY, navigationInspectorId.c_str());
    intentJson->Put(INTENT_NAVDESTINATION_NAME_KEY, navDestinationName.c_str());
    return intentJson->ToString();
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
}

void NavigationManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: RemoveNavigationDumpCallback001
 * @tc.desc: Branch: if (it != dumpMap_.end()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, RemoveNavigationDumpCallback001, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    int32_t nodeId = 101;
    int32_t depth = 1;
    navigationManager->AddNavigationDumpCallback(nodeId, depth, [](int depth) {});

    navigationManager->RemoveNavigationDumpCallback(nodeId, depth);
    EXPECT_EQ(navigationManager->dumpMap_.size(), 0);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: RemoveNavigationDumpCallback002
 * @tc.desc: Branch: if (it != dumpMap_.end()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, RemoveNavigationDumpCallback002, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    int32_t nodeId = 101;
    int32_t depth = 1;
    navigationManager->AddNavigationDumpCallback(nodeId, depth, [](int depth) {});

    navigationManager->RemoveNavigationDumpCallback(nodeId + 1, depth + 1);
    EXPECT_EQ(navigationManager->dumpMap_.size(), 1);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavigationInfo001
 * @tc.desc: Branch: if (customNode) = true
 *           Branch: if (!current) = false
 *           Branch: if (!current) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, GetNavigationInfo001, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->SetNavigationNode(AceType::WeakClaim(AceType::RawPtr(navigationGroupNode)));
    navigationGroupNode->propInspectorId_ = NAVIGATION_ID1;

    auto pipelineContext = customNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    auto navigationInfo = navigationManager->GetNavigationInfo(customNode);
    ASSERT_NE(navigationInfo, nullptr);
    EXPECT_EQ(navigationInfo->navigationId, NAVIGATION_ID1);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavigationInfo002
 * @tc.desc: Branch: if (customNode) = false
 *           Branch: if (!current) = true
 *           Branch: if (current->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) = false
 *           Branch: if (current->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) = true
 *           Branch: if (!current) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, GetNavigationInfo002, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationGroupNode->propInspectorId_ = NAVIGATION_ID1;
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navBarNode->MountToParent(navigationGroupNode);

    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    auto navigationInfo = navigationManager->GetNavigationInfo(navBarNode);
    ASSERT_NE(navigationInfo, nullptr);
    EXPECT_EQ(navigationInfo->navigationId, NAVIGATION_ID1);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavigationInfo003
 * @tc.desc: Branch: if (customNode) = false
 *           Branch: if (!current) = true
 *           Branch: if (!current) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, GetNavigationInfo003, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationGroupNode->propInspectorId_ = NAVIGATION_ID1;
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });

    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    auto navigationInfo = navigationManager->GetNavigationInfo(navBarNode);
    EXPECT_EQ(navigationInfo, nullptr);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavigationInfo004
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, GetNavigationInfo004, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    ASSERT_NE(navigationPattern->GetNavigationStack(), nullptr);
    navigationGroupNode->propInspectorId_ = NAVIGATION_ID1;
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->SetNavigationNode(AceType::WeakClaim(AceType::RawPtr(navigationGroupNode)));

    auto pipelineContext = customNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    auto navigationInfo = navigationManager->GetNavigationInfo(customNode);
    ASSERT_NE(navigationInfo, nullptr);
    EXPECT_EQ(navigationInfo->uniqueId, navigationGroupNode->GetId());
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: AddInteractiveAnimation001
 * @tc.desc: Branch: if (!isInteractive_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, AddInteractiveAnimation001, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    int32_t navigationNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigationNodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationGroupNode->propInspectorId_ = NAVIGATION_ID1;
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->isInteractive_ = true;
    navigationManager->interactiveAnimationId_ = navigationNodeId;
    navigationPattern->proxyList_.push_back(AceType::MakeRefPtr<NavigationTransitionProxy>());
    auto navigationProxy = navigationPattern->GetTopNavigationProxy();
    ASSERT_NE(navigationProxy, nullptr);
    navigationProxy->interactive_ = true;

    bool ret = navigationManager->AddInteractiveAnimation([]() {});
    EXPECT_EQ(ret, true);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: AddInteractiveAnimation002
 * @tc.desc: Branch: if (!isInteractive_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, AddInteractiveAnimation002, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    int32_t navigationNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigationNodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationGroupNode->propInspectorId_ = NAVIGATION_ID1;
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    navigationManager->isInteractive_ = false;
    navigationManager->interactiveAnimationId_ = navigationNodeId;
    navigationPattern->proxyList_.push_back(AceType::MakeRefPtr<NavigationTransitionProxy>());
    auto navigationProxy = navigationPattern->GetTopNavigationProxy();
    ASSERT_NE(navigationProxy, nullptr);
    navigationProxy->interactive_ = true;

    bool ret = navigationManager->AddInteractiveAnimation([]() {});
    EXPECT_EQ(ret, false);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: StorageNavigationRecoveryInfo001
 * @tc.desc: Branch: if (!allNavigationInfo || !allNavigationInfo->IsArray()) = false
 *           Condition: !allNavigationInfo = false, !allNavigationInfo->IsArray() = false
 *           Branch: if (!stackInfo->IsArray()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, StorageNavigationRecoveryInfo001, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto allNavigationInfo = JsonUtil::CreateArray(true);
    auto navigationInfo = JsonUtil::Create(true);
    navigationInfo->Put("id", NAVIGATION_ID1.c_str());
    auto allNavdestinationInfo = JsonUtil::CreateArray(true);
    auto navdestinationInfo = JsonUtil::Create(true);
    navdestinationInfo->Put("name", PAGE1.c_str());
    navdestinationInfo->Put("param", PARAM1.c_str());
    navdestinationInfo->Put("mode", 0);
    allNavdestinationInfo->Put(navdestinationInfo);
    navigationInfo->Put("stack", allNavdestinationInfo);
    allNavigationInfo->Put(navigationInfo);

    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    navigationManager->StorageNavigationRecoveryInfo(std::move(allNavigationInfo));
    auto recoveryInfo = navigationManager->navigationRecoveryInfo_[NAVIGATION_ID1];
    EXPECT_EQ(recoveryInfo.size(), 1);
    EXPECT_EQ(recoveryInfo[0].name, PAGE1);
    EXPECT_EQ(recoveryInfo[0].param, PARAM1);
    EXPECT_EQ(recoveryInfo[0].mode, 0);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: StorageNavigationRecoveryInfo002
 * @tc.desc: Branch: if (!allNavigationInfo || !allNavigationInfo->IsArray()) = false
 *           Condition: !allNavigationInfo = false, !allNavigationInfo->IsArray() = false
 *           Branch: if (!stackInfo->IsArray()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, StorageNavigationRecoveryInfo002, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto allNavigationInfo = JsonUtil::CreateArray(true);
    auto navigationInfo = JsonUtil::Create(true);
    navigationInfo->Put("id", NAVIGATION_ID1.c_str());
    auto allNavdestinationInfo = JsonUtil::Create(true);
    navigationInfo->Put("stack", allNavdestinationInfo);
    allNavigationInfo->Put(navigationInfo);

    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    navigationManager->StorageNavigationRecoveryInfo(std::move(allNavigationInfo));
    auto recoveryInfo = navigationManager->navigationRecoveryInfo_[NAVIGATION_ID1];
    EXPECT_EQ(recoveryInfo.size(), 0);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: StorageNavigationRecoveryInfo003
 * @tc.desc: Branch: if (!allNavigationInfo || !allNavigationInfo->IsArray()) = true
 *           Condition: !allNavigationInfo = false, !allNavigationInfo->IsArray() = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, StorageNavigationRecoveryInfo003, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto allNavigationInfo = JsonUtil::Create(true);

    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    navigationManager->StorageNavigationRecoveryInfo(std::move(allNavigationInfo));
    EXPECT_EQ(navigationManager->navigationRecoveryInfo_[NAVIGATION_ID1].size(), 0);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: StorageNavigationRecoveryInfo004
 * @tc.desc: Branch: if (!allNavigationInfo || !allNavigationInfo->IsArray()) = true
 *           Condition: !allNavigationInfo = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, StorageNavigationRecoveryInfo004, TestSize.Level1)
{
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    navigationManager->StorageNavigationRecoveryInfo(std::move(nullptr));
    EXPECT_EQ(navigationManager->navigationRecoveryInfo_[NAVIGATION_ID1].size(), 0);
    NavigationManagerTestNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckNodeNeedCacheTest001
 * @tc.desc: Branch: if navigation has no animation
 * @tc.expect: can do renderNode cached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, CheckNodeNeedCacheTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    /**
     * @tc.steps: step2. Do test.
     */
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_EQ(navigationManager->CheckNodeNeedCache(navigationGroupNode), true);
}

/**
 * @tc.name: CheckNodeNeedCacheTest002
 * @tc.desc: Branch: if navigation has sub animation
 * @tc.expect: can do renderNode cached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, CheckNodeNeedCacheTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    /**
     * @tc.steps: step2. Do test.
     */
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(navigationGroupNode->GetRenderContext());
    ASSERT_NE(mockRenderContext, nullptr);
    mockRenderContext->SetAnimationsCount(1);
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_EQ(navigationManager->CheckNodeNeedCache(navigationGroupNode), false);
}

/**
 * @tc.name: CheckNodeNeedCacheTest003
 * @tc.desc: Branch: if navigation->GetOverlayNode() && overlay has no animation
 * @tc.expect: can do renderNode cached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, CheckNodeNeedCacheTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    /**
     * @tc.steps: step2. mount overlayNode to navigation
     */
    auto overlayNode = FrameNode::CreateFrameNode(
        "overlayNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    overlayNode->isActive_ = true;
    overlayNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    navigationGroupNode->AddChild(overlayNode);
    /**
     * @tc.steps: step2. Do test, verify the target value.
     */
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_EQ(navigationManager->CheckNodeNeedCache(navigationGroupNode), true);
}

/**
 * @tc.name: CheckNodeNeedCacheTest004
 * @tc.desc: Branch: if navigation->GetOverlayNode() && overlay has animation
 * @tc.expect: can do renderNode cached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, CheckNodeNeedCacheTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    /**
     * @tc.steps: step2. mount overlayNode to navigation
     */
    auto overlayNode = FrameNode::CreateFrameNode(
        "overlayNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    overlayNode->isActive_ = true;
    overlayNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    navigationGroupNode->AddChild(overlayNode);
    auto mockRenderContext = AceType::DynamicCast<MockRenderContext>(overlayNode->GetRenderContext());
    ASSERT_NE(mockRenderContext, nullptr);
    mockRenderContext->SetAnimationsCount(1);
    /**
     * @tc.steps: step2. Do test, verify the target value.
     */
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_EQ(navigationManager->CheckNodeNeedCache(navigationGroupNode), false);
}

/**
 * @tc.name: CheckNodeNeedCacheTest005
 * @tc.desc: Branch: if navigation->child->GetTag == UIExtension
 * @tc.expect: can do renderNode cached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, CheckNodeNeedCacheTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    /**
     * @tc.steps: step2. mount UIExtension to navigation
     */
    auto uiExtensionNode = FrameNode::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    uiExtensionNode->isActive_ = true;
    uiExtensionNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    navigationGroupNode->AddChild(uiExtensionNode);
    /**
     * @tc.steps: step2. Do test, verify the target value.
     */
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_EQ(navigationManager->CheckNodeNeedCache(navigationGroupNode), false);
}


/**
 * @tc.name: CheckNodeNeedCacheTest006
 * @tc.desc: Branch: if navigation->GetOverlayNode() && overlay->GetChild->GetTag == UIExtension
 * @tc.expect: can do renderNode cached
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, CheckNodeNeedCacheTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager
     */
    NavigationManagerTestNg::SetUpTestSuite();
    auto navigationGroupNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto pipelineContext = navigationGroupNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationManager = pipelineContext->GetNavigationManager();
    /**
     * @tc.steps: step2. mount overlayNode to navigation and mount uiExtension to overlay
     */
    auto overlayNode = FrameNode::CreateFrameNode(
        "overlayNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    overlayNode->isActive_ = true;
    overlayNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    navigationGroupNode->AddChild(overlayNode);
    auto uiExtensionNode = FrameNode::CreateFrameNode(V2::UI_EXTENSION_COMPONENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>(), true);
    uiExtensionNode->isActive_ = true;
    uiExtensionNode->layoutProperty_->UpdateVisibility(VisibleType::VISIBLE);
    overlayNode->AddChild(uiExtensionNode);
        /**
     * @tc.steps: step2. Do test, verify the target value.
     */
    ASSERT_NE(navigationManager, nullptr);
    ASSERT_EQ(navigationManager->CheckNodeNeedCache(navigationGroupNode), false);
}

/**
 * @tc.name: ParseNavigationIntentInfo001
 * @tc.desc: Branch: if serializedIntentInfo is valid
 * @tc.expect: can parse serializedIntentInfo properly
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(NavigationManagerTestNg, ParseNavigationIntentInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build serialized intent info.
     */
    const std::string navigationInspectorId = "navigation";
    const std::string navDestinationName = "name";
    const std::string param = "{\"param\":\"\"}";
    const std::string serializedIntentInfo =
        BuildSerializedIntentInfo(navigationInspectorId, navDestinationName, param);
    /**
     * @tc.steps: step3. parse target serialized intentInfo and do verify.
     */
    NavigationIntentInfo intentInfo = navigationManager->ParseNavigationIntentInfo(serializedIntentInfo);
    ASSERT_EQ(intentInfo.navigationInspectorId, navigationInspectorId);
    ASSERT_EQ(intentInfo.navDestinationName, navDestinationName);
    ASSERT_EQ(intentInfo.param, param);
}

/**
 * @tc.name: ParseNavigationIntentInfo002
 * @tc.desc: Branch: if serializedIntentInfo is invalid
 * @tc.expect: no any cpp-crash
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, ParseNavigationIntentInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_NE(navigationManager, nullptr);
    /**
     * @tc.steps: step2. build an empty serialized intent info.
     */
    const auto intentJson = JsonUtil::Create(true);
    const std::string serializedIntentInfo = intentJson->ToString();
    /**
     * @tc.steps: step3. parse target serialized intentInfo and do verify.
     */
    NavigationIntentInfo intentInfo = navigationManager->ParseNavigationIntentInfo(serializedIntentInfo);
    ASSERT_EQ(intentInfo.navigationInspectorId, "");
    ASSERT_EQ(intentInfo.navDestinationName, "");
    ASSERT_EQ(intentInfo.param, "");
}

/**
 * @tc.name: FindNavigationInTargetParentTest001
 * @tc.desc: Branch: if several router and navigation exist.
 * @tc.expect: could find correct navigations by router page id after the arkui-tree built.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, FindNavigationInTargetParentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager and all create necessary uiNodes.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_TRUE(navigationManager->navigationMap_.empty());
    auto routerPageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(routerPageOne, nullptr);
    auto routerPageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(routerPageTwo, nullptr);
    auto routerPageThree = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
    AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(routerPageThree, nullptr);
    auto navigationGroupNodeOne = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeOne, nullptr);
    auto navigationGroupNodeTwo = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeTwo, nullptr);
    auto navigationGroupNodeThree = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeThree, nullptr);
    auto navigationGroupNodeFour = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeFour, nullptr);
    /**
     * @tc.steps: step2. build navigation struceture.
     */
    routerPageOne->onMainTree_ = true;
    routerPageTwo->onMainTree_ = true;
    routerPageThree->onMainTree_ = true;
    routerPageOne->AddChild(navigationGroupNodeOne);
    routerPageTwo->AddChild(navigationGroupNodeTwo);
    routerPageThree->AddChild(navigationGroupNodeThree);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 3);
    routerPageThree->AddChild(navigationGroupNodeFour);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 3);
    /**
     * @tc.steps: step3. Find navigation in target parent.
     */
    auto result = navigationManager->FindNavigationInTargetParent(routerPageOne->GetId());
    std::vector<int32_t> expected = { navigationGroupNodeOne->GetId() };
    EXPECT_EQ(result, expected);
    result = navigationManager->FindNavigationInTargetParent(routerPageTwo->GetId());
    expected = { navigationGroupNodeTwo->GetId() };
    EXPECT_EQ(result, expected);
    result = navigationManager->FindNavigationInTargetParent(routerPageThree->GetId());
    expected = { navigationGroupNodeThree->GetId(), navigationGroupNodeFour->GetId() };
    EXPECT_EQ(result, expected);
    navigationManager->navigationMap_.clear();
}

/**
 * @tc.name: FindNavigationInTargetParentTest002
 * @tc.desc: Branch: if several router and navigation exist.
 * @tc.expect: could remove navigations correctly.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, FindNavigationInTargetParentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get navigation manager and all create necessary uiNodes.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_TRUE(navigationManager->navigationMap_.empty());
    auto routerPageOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(routerPageOne, nullptr);
    auto routerPageTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(routerPageTwo, nullptr);
    auto routerPageThree = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ASSERT_NE(routerPageThree, nullptr);
    auto navigationGroupNodeOne = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeOne, nullptr);
    auto navigationGroupNodeTwo = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeTwo, nullptr);
    auto navigationGroupNodeThree = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeThree, nullptr);
    auto navigationGroupNodeFour = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeFour, nullptr);
    /**
     * @tc.steps: step2. build navigation struceture.
     */
    routerPageOne->onMainTree_ = true;
    routerPageTwo->onMainTree_ = true;
    routerPageThree->onMainTree_ = true;
    routerPageOne->AddChild(navigationGroupNodeOne);
    routerPageTwo->AddChild(navigationGroupNodeTwo);
    routerPageThree->AddChild(navigationGroupNodeThree);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 3);
    routerPageThree->AddChild(navigationGroupNodeFour);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 3);
    /**
     * @tc.steps: step3. test the ability of function `RemoveNavigation`.
     */
    navigationManager->RemoveNavigation(navigationGroupNodeOne->GetId());
    ASSERT_EQ(navigationManager->navigationMap_.size(), 2);
    navigationManager->RemoveNavigation(navigationGroupNodeTwo->GetId());
    ASSERT_EQ(navigationManager->navigationMap_.size(), 1);
    navigationManager->RemoveNavigation(navigationGroupNodeOne->GetId());
    ASSERT_EQ(navigationManager->navigationMap_.size(), 1);
    navigationManager->RemoveNavigation(navigationGroupNodeThree->GetId());
    ASSERT_EQ(navigationManager->navigationMap_.size(), 1);
    navigationManager->RemoveNavigation(navigationGroupNodeFour->GetId());
    ASSERT_EQ(navigationManager->navigationMap_.size(), 0);
    navigationManager->navigationMap_.clear();
}

/**
 * @tc.name: AddNavigationTest001
 * @tc.desc: Branch: if iter == navigationMaps_.end() == true when find pageId
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, AddNavigationTest001, TestSize.Level1)
{
    auto navigationManager = GetNavigationManager();
    ASSERT_TRUE(navigationManager->navigationMap_.empty());
    int32_t routerPageId = 1;
    auto navigationGroupNodeOne = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeOne, nullptr);
    navigationManager->AddNavigation(routerPageId, navigationGroupNodeOne);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 1);
    navigationManager->navigationMap_.clear();
}

/**
 * @tc.name: AddNavigationTest002
 * @tc.desc: Branch: if iter == navigationMaps_.end() == false when find pageId
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, AddNavigationTest002, TestSize.Level1)
{
    auto navigationManager = GetNavigationManager();
    ASSERT_TRUE(navigationManager->navigationMap_.empty());
    int32_t routerPageId = 1;
    auto navigationGroupNodeOne = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeOne, nullptr);
    navigationManager->AddNavigation(routerPageId, navigationGroupNodeOne);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 1);
    auto navigationGroupNodeTwo = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNodeTwo, nullptr);
    navigationManager->AddNavigation(routerPageId, navigationGroupNodeTwo);
    ASSERT_EQ(navigationManager->navigationMap_.size(), 1);
    ASSERT_NE(navigationManager->navigationMap_.find(routerPageId), navigationManager->navigationMap_.end());
    ASSERT_EQ(navigationManager->navigationMap_[routerPageId].size(), 2);
    navigationManager->navigationMap_.clear();
}

/**
 * @tc.name: GetNavigationByInspectorIdTest001
 * @tc.desc: Branch: if input arg inspectorId is valid in navigationMap_
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, GetNavigationByInspectorIdTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigationManager and mock properties.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_TRUE(navigationManager->navigationMap_.empty());
    const int32_t routerPageId = 1;
    const std::string navigationInspectorId = "navigationOne";
    auto navigationGroupNode = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNode, nullptr);
    navigationGroupNode->curId_ = navigationInspectorId;
    ASSERT_EQ(navigationGroupNode->GetCurId(), navigationInspectorId);
    navigationManager->AddNavigation(routerPageId, navigationGroupNode);
    /**
     * @tc.steps: step2. do verify, reset properties and verify again.
     */
    ASSERT_FALSE(navigationManager->navigationMap_.empty());
    ASSERT_EQ(navigationManager->GetNavigationByInspectorId(navigationInspectorId), navigationGroupNode);
    navigationManager->navigationMap_.clear();
}

/**
 * @tc.name: GetNavigationByInspectorIdTest002
 * @tc.desc: Branch: if input arg inspectorId is invalid in navigationMap_
 * @tc.type: FUNC
 */
HWTEST_F(NavigationManagerTestNg, GetNavigationByInspectorIdTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigationManager and mock properties.
     */
    auto navigationManager = GetNavigationManager();
    ASSERT_TRUE(navigationManager->navigationMap_.empty());
    const int32_t routerPageId = 1;
    const std::string navigationInspectorId = "navigationOne";
    auto navigationGroupNode = CreateNavigationNode(AceType::MakeRefPtr<MockNavigationStack>());
    ASSERT_NE(navigationGroupNode, nullptr);
    navigationGroupNode->curId_ = navigationInspectorId;
    ASSERT_EQ(navigationGroupNode->GetCurId(), navigationInspectorId);
    navigationManager->AddNavigation(routerPageId, navigationGroupNode);
    /**
     * @tc.steps: step2. do verify, reset properties and verify again.
     */
    ASSERT_FALSE(navigationManager->navigationMap_.empty());
    const std::string wrongNavigationId = "wrongId";
    ASSERT_NE(navigationManager->GetNavigationByInspectorId(wrongNavigationId), navigationGroupNode);
    ASSERT_EQ(navigationManager->GetNavigationByInspectorId(wrongNavigationId), nullptr);
    navigationManager->navigationMap_.clear();
}
} // namespace OHOS::Ace::NG