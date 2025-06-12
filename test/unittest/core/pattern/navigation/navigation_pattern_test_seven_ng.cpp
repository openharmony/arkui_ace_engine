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
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class NavigationPatternTestSevenNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetForceSplitEnabled(bool enable);
};

RefPtr<NavigationBarTheme> NavigationPatternTestSevenNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestSevenNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return navigationBarTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestSevenNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationPatternTestSevenNg::SetForceSplitEnabled(bool enable)
{
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = enable;
}

/**
 * @tc.name: RemoveRedundantPrimaryNavDestination001
 * @tc.desc: Branch: while (primaryContentNode->GetChildren().size() > primaryNodes_.size()) { => false
 *                   if (hasRemoveNode) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, RemoveRedundantPrimaryNavDestination001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    ASSERT_TRUE(primaryContentNode->GetChildren().empty());

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));

    primaryContentNode->needSyncRenderTree_ = false;
    pattern->RemoveRedundantPrimaryNavDestination();
    EXPECT_FALSE(primaryContentNode->needSyncRenderTree_);
}

/**
 * @tc.name: RemoveRedundantPrimaryNavDestination002
 * @tc.desc: Branch: while (primaryContentNode->GetChildren().size() > primaryNodes_.size()) { => true
 *                   if (hasRemoveNode) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, RemoveRedundantPrimaryNavDestination002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    primaryContentNode->AddChild(dest);
    ASSERT_FALSE(primaryContentNode->GetChildren().empty());
    pattern->primaryNodes_.clear();
    primaryContentNode->needSyncRenderTree_ = false;
    pattern->RemoveRedundantPrimaryNavDestination();
    EXPECT_TRUE(primaryContentNode->needSyncRenderTree_);
}

/**
 * @tc.name: FirePrimaryNodesOnShowAndActive001
 * @tc.desc: Branch: if (!pattern->GetIsOnShow()) { => true
 *                   if (!pattern->IsActive()) { => true or false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesOnShowAndActive001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    destPattern->SetIsOnShow(false);
    destPattern->SetIsActive(false);

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    pattern->FirePrimaryNodesOnShowAndActive();
    EXPECT_TRUE(destPattern->GetIsOnShow());
    EXPECT_TRUE(destPattern->IsActive());

    destPattern->SetIsOnShow(false);
    destPattern->SetIsActive(true);

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    pattern->FirePrimaryNodesOnShowAndActive();
    EXPECT_TRUE(destPattern->GetIsOnShow());
    EXPECT_TRUE(destPattern->IsActive());
}

/**
 * @tc.name: FirePrimaryNodesOnShowAndActive002
 * @tc.desc: Branch: if (!pattern->GetIsOnShow()) { => false
 *                   if (!pattern->IsActive()) { => true or false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesOnShowAndActive002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    destPattern->SetIsOnShow(true);
    destPattern->SetIsActive(false);

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    pattern->FirePrimaryNodesOnShowAndActive();
    EXPECT_TRUE(destPattern->GetIsOnShow());
    EXPECT_TRUE(destPattern->IsActive());

    destPattern->SetIsOnShow(true);
    destPattern->SetIsActive(true);

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    pattern->FirePrimaryNodesOnShowAndActive();
    EXPECT_TRUE(destPattern->GetIsOnShow());
    EXPECT_TRUE(destPattern->IsActive());
}

/**
 * @tc.name: FirePrePrimaryNodesOnWillDisappear001
 * @tc.desc: Branch: if (filterNodes.find(primaryNode) != filterNodes.end()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrePrimaryNodesOnWillDisappear001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->primaryNodesToBeRemoved_.clear();
    pattern->primaryNodesToBeRemoved_.push_back(dest);
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;
    filterNodes.emplace(dest);
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrePrimaryNodesOnWillDisappear(std::move(filterNodes));
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePrePrimaryNodesOnWillDisappear002
 * @tc.desc: Branch: if (filterNodes.find(primaryNode) != filterNodes.end()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrePrimaryNodesOnWillDisappear002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->primaryNodesToBeRemoved_.clear();
    pattern->primaryNodesToBeRemoved_.push_back(dest);
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrePrimaryNodesOnWillDisappear(std::move(filterNodes));
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_WILL_DISAPPEAR);
}

/**
 * @tc.name: FirePrePrimaryNodesOnHide001
 * @tc.desc: Branch: if (!node->IsShowInPrimaryPartition() && pattern->GetIsOnShow()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrePrimaryNodesOnHide001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIsShowInPrimaryPartition(false);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    destPattern->SetIsOnShow(true);
    pattern->primaryNodesToBeRemoved_.clear();
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrePrimaryNodesOnHide();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: FirePrePrimaryNodesOnHide002
 * @tc.desc: Branch: if (!node->IsShowInPrimaryPartition() && pattern->GetIsOnShow()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrePrimaryNodesOnHide002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->primaryNodesToBeRemoved_.clear();
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));

    dest->SetIsShowInPrimaryPartition(true);
    destPattern->SetIsOnShow(true);
    destEventHub->state_ = NavDestinationState::ON_HIDDEN;
    pattern->FirePrePrimaryNodesOnHide();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);

    dest->SetIsShowInPrimaryPartition(false);
    destPattern->SetIsOnShow(false);
    destEventHub->state_ = NavDestinationState::ON_HIDDEN;
    pattern->FirePrePrimaryNodesOnHide();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);

    dest->SetIsShowInPrimaryPartition(true);
    destPattern->SetIsOnShow(false);
    destEventHub->state_ = NavDestinationState::ON_HIDDEN;
    pattern->FirePrePrimaryNodesOnHide();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: FirePrePrimaryNodesOnHide003
 * @tc.desc: Branch: if (!pattern->GetIsOnShow()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrePrimaryNodesOnHide003, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->primaryNodesToBeRemoved_.clear();
    pattern->primaryNodesToBeRemoved_.push_back(dest);

    destPattern->SetIsOnShow(false);
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrePrimaryNodesOnHide();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePrePrimaryNodesOnHide004
 * @tc.desc: Branch: if (!pattern->GetIsOnShow()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrePrimaryNodesOnHide004, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->primaryNodesToBeRemoved_.clear();
    pattern->primaryNodesToBeRemoved_.push_back(dest);

    destPattern->SetIsOnShow(true);
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrePrimaryNodesOnHide();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: FirePreTopPrimaryNodeInactiveIfNeeded001
 * @tc.desc: Branch: if (prePrimaryNodes_.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePreTopPrimaryNodeInactiveIfNeeded001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->prePrimaryNodes_.clear();
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePreTopPrimaryNodeInactiveIfNeeded002
 * @tc.desc: Branch: if (prePrimaryNodes_.empty()) { => false
 *                   if (!preTopPrimaryNode->IsActive()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePreTopPrimaryNodeInactiveIfNeeded002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    dest->SetActive(false);
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePreTopPrimaryNodeInactiveIfNeeded003
 * @tc.desc: Branch: if (prePrimaryNodes_.empty()) { => false
 *                   if (!preTopPrimaryNode->IsActive()) { => false
 *                   if (!primaryNodes_.empty()) { => false
 *                   if (navigationStack_) { => false
 *                   if (preTopPrimaryNode != topPrimaryNode && preTopPrimaryNode != topNode) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePreTopPrimaryNodeInactiveIfNeeded003, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    dest->SetActive(true);
    destPattern->SetIsActive(true);
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    pattern->primaryNodes_.clear();
    auto backupStack = pattern->navigationStack_;
    pattern->navigationStack_ = nullptr;

    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_INACTIVE);
    pattern->navigationStack_ = backupStack;
}

/**
 * @tc.name: FirePreTopPrimaryNodeInactiveIfNeeded004
 * @tc.desc: Branch: if (prePrimaryNodes_.empty()) { => false
 *                   if (!preTopPrimaryNode->IsActive()) { => false
 *                   if (!primaryNodes_.empty()) { => true
 *                   if (navigationStack_) { => false
 *                   if (preTopPrimaryNode != topPrimaryNode && preTopPrimaryNode != topNode) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePreTopPrimaryNodeInactiveIfNeeded004, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    dest->SetActive(true);
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    auto backupStack = pattern->navigationStack_;
    pattern->navigationStack_ = nullptr;
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
    pattern->navigationStack_ = backupStack;
}

/**
 * @tc.name: FirePreTopPrimaryNodeInactiveIfNeeded005
 * @tc.desc: Branch: if (prePrimaryNodes_.empty()) { => false
 *                   if (!preTopPrimaryNode->IsActive()) { => false
 *                   if (!primaryNodes_.empty()) { => false
 *                   if (navigationStack_) { => true
 *                   if (preTopPrimaryNode != topPrimaryNode && preTopPrimaryNode != topNode) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePreTopPrimaryNodeInactiveIfNeeded005, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    dest->SetActive(true);
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    pattern->primaryNodes_.clear();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->navigationStack_->navPathList_.clear();
    pattern->navigationStack_->navPathList_.push_back(testPair);
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePreTopPrimaryNodeInactiveIfNeeded006
 * @tc.desc: Branch: if (prePrimaryNodes_.empty()) { => false
 *                   if (!preTopPrimaryNode->IsActive()) { => false
 *                   if (!primaryNodes_.empty()) { => true
 *                   if (navigationStack_) { => true
 *                   if (preTopPrimaryNode != topPrimaryNode && preTopPrimaryNode != topNode) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePreTopPrimaryNodeInactiveIfNeeded006, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    dest->SetActive(true);
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(dest);
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->navigationStack_->navPathList_.clear();
    pattern->navigationStack_->navPathList_.push_back(testPair);
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePrimaryNodesLifecycle001
 * @tc.desc: Branch: if (lifecycle != NavDestinationLifecycle::ON_SHOW &&
 *                       lifecycle != NavDestinationLifecycle::ON_HIDE) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesLifecycle001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_ACTIVE);
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePrimaryNodesLifecycle002
 * @tc.desc: Branch: if (lifecycle != NavDestinationLifecycle::ON_SHOW &&
 *                       lifecycle != NavDestinationLifecycle::ON_HIDE) { => false
 *                   if (homeNode->GetIndex() >= navigation->GetLastStandardIndex()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesLifecycle002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    dest->index_ = 1;
    navNode->lastStandardIndex_ = 0;
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_SHOW);
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: FirePrimaryNodesLifecycle003
 * @tc.desc: Branch: if (lifecycle != NavDestinationLifecycle::ON_SHOW &&
 *                       lifecycle != NavDestinationLifecycle::ON_HIDE) { => false
 *                   if (homeNode->GetIndex() >= navigation->GetLastStandardIndex()) { => false
 *                   if (lifecycle == NavDestinationLifecycle::ON_SHOW) { => true
 *                   if (!pattern->GetIsOnShow()) { => true
 *                   if (idx == primaryNodes.size() - 1 && !pattern->IsActive()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesLifecycle003, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    pattern->homeNode_ = WeakPtr(dest);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    dest->index_ = 0;
    navNode->lastStandardIndex_ = 1;

    destPattern->SetIsOnShow(false);
    destPattern->SetIsActive(false);
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));

    destEventHub->state_ = NavDestinationState::ON_HIDDEN;
    pattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_SHOW);
    EXPECT_TRUE(destPattern->GetIsOnShow());
    EXPECT_TRUE(destPattern->IsActive());
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_ACTIVE);
}

/**
 * @tc.name: FirePrimaryNodesLifecycle004
 * @tc.desc: Branch: if (lifecycle != NavDestinationLifecycle::ON_SHOW &&
 *                       lifecycle != NavDestinationLifecycle::ON_HIDE) { => false
 *                   if (homeNode->GetIndex() >= navigation->GetLastStandardIndex()) { => false
 *                   if (lifecycle == NavDestinationLifecycle::ON_SHOW) { => true
 *                   if (!pattern->GetIsOnShow()) { => false
 *                   if (idx == primaryNodes.size() - 1 && !pattern->IsActive()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesLifecycle004, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    pattern->homeNode_ = WeakPtr(dest);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    dest->index_ = 0;
    navNode->lastStandardIndex_ = 1;

    destPattern->SetIsOnShow(true);
    destPattern->SetIsActive(true);
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_HIDDEN;
    pattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_SHOW);
    EXPECT_TRUE(destPattern->GetIsOnShow());
    EXPECT_TRUE(destPattern->IsActive());
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: FirePrimaryNodesLifecycle005
 * @tc.desc: Branch: if (lifecycle != NavDestinationLifecycle::ON_SHOW &&
 *                       lifecycle != NavDestinationLifecycle::ON_HIDE) { => false
 *                   if (homeNode->GetIndex() >= navigation->GetLastStandardIndex()) { => false
 *                   if (lifecycle == NavDestinationLifecycle::ON_SHOW) { => false
 *                   if (idx == 0 && pattern->IsActive()) { => true
 *                   if (pattern->GetIsOnShow()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesLifecycle005, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    pattern->homeNode_ = WeakPtr(dest);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    dest->index_ = 0;
    navNode->lastStandardIndex_ = 1;
    destPattern->SetIsOnShow(true);
    destPattern->SetIsActive(true);
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_HIDE);
    EXPECT_FALSE(destPattern->GetIsOnShow());
    EXPECT_FALSE(destPattern->IsActive());
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: FirePrimaryNodesLifecycle006
 * @tc.desc: Branch: if (lifecycle != NavDestinationLifecycle::ON_SHOW &&
 *                       lifecycle != NavDestinationLifecycle::ON_HIDE) { => false
 *                   if (homeNode->GetIndex() >= navigation->GetLastStandardIndex()) { => false
 *                   if (lifecycle == NavDestinationLifecycle::ON_SHOW) { => false
 *                   if (idx == 0 && pattern->IsActive()) { => false
 *                   if (pattern->GetIsOnShow()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, FirePrimaryNodesLifecycle006, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    pattern->homeNode_ = WeakPtr(dest);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    auto destEventHub = dest->GetOrCreateEventHub<NavDestinationEventHub>();
    ASSERT_NE(destEventHub, nullptr);
    dest->index_ = 0;
    navNode->lastStandardIndex_ = 1;
    destPattern->SetIsOnShow(false);
    destPattern->SetIsActive(false);
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    // unchanged, just for Branch Coverage
    destEventHub->state_ = NavDestinationState::ON_SHOWN;
    pattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_HIDE);
    EXPECT_FALSE(destPattern->GetIsOnShow());
    EXPECT_FALSE(destPattern->IsActive());
    EXPECT_EQ(destEventHub->state_, NavDestinationState::ON_SHOWN);
}
} // namespace OHOS::Ace::NG
