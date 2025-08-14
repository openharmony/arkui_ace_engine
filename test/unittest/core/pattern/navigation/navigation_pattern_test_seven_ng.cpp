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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string BUNDLE_NAME = "com.example.test";
const std::string MODULE_NAME = "entry";
} // namespace

class NavigationPatternTestSevenNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetForceSplitEnabled(bool enable);
    void MockPipelineContextGetTheme();
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

void NavigationPatternTestSevenNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: IsHideNavBarInForceSplitModeNeeded001
 * @tc.desc: Branch: if (primaryNodes_.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsHideNavBarInForceSplitModeNeeded001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->primaryNodes_.clear();
    property->UpdateHideNavBar(true);
    auto hide = pattern->IsHideNavBarInForceSplitModeNeeded();
    EXPECT_TRUE(hide);

    pattern->primaryNodes_.clear();
    property->UpdateHideNavBar(false);
    hide = pattern->IsHideNavBarInForceSplitModeNeeded();
    EXPECT_FALSE(hide);
}

/**
 * @tc.name: IsHideNavBarInForceSplitModeNeeded002
 * @tc.desc: Branch: if (primaryNodes_.empty()) { => false
 *                   if (node->GetNavDestinationMode() == NavDestinationMode::STANDARD) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsHideNavBarInForceSplitModeNeeded002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    dest->mode_ = NavDestinationMode::STANDARD;
    auto hide = pattern->IsHideNavBarInForceSplitModeNeeded();
    EXPECT_TRUE(hide);
}

/**
 * @tc.name: IsHideNavBarInForceSplitModeNeeded003
 * @tc.desc: Branch: if (primaryNodes_.empty()) { => false
 *                   if (node->GetNavDestinationMode() == NavDestinationMode::STANDARD) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsHideNavBarInForceSplitModeNeeded003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    dest->mode_ = NavDestinationMode::DIALOG;
    auto hide = pattern->IsHideNavBarInForceSplitModeNeeded();
    EXPECT_FALSE(hide);
}

/**
 * @tc.name: IsNavBarValid001
 * @tc.desc: Branch: return !property->GetHideNavBarValue(false) &&
 *                      (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) &&
 *                      (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0)); => false
 *                   !property->GetHideNavBarValue(false) => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsNavBarValid001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    property->UpdateHideNavBar(true);
    auto isValid = pattern->IsNavBarValid();
    EXPECT_FALSE(isValid);
}

/**
 * @tc.name: IsNavBarValid002
 * @tc.desc: Branch: return !property->GetHideNavBarValue(false) &&
 *                      (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) &&
 *                      (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0)); => false
 *                   !property->GetHideNavBarValue(false) => true
 *                   (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsNavBarValid002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    property->UpdateHideNavBar(false);
    pattern->userSetNavBarWidthFlag_ = true;
    pattern->initNavBarWidthValue_ = 0.0_vp;
    auto isValid = pattern->IsNavBarValid();
    EXPECT_FALSE(isValid);
}

/**
 * @tc.name: IsNavBarValid003
 * @tc.desc: Branch: return !property->GetHideNavBarValue(false) &&
 *                      (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) &&
 *                      (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0)); => false
 *                   !property->GetHideNavBarValue(false) => true
 *                   (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) => true
 *                   (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0)) => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsNavBarValid003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    property->UpdateHideNavBar(false);
    pattern->userSetNavBarWidthFlag_ = false;
    constexpr  Dimension ZERO_WIDTH = 0.0_vp;
    property->UpdateMaxNavBarWidth(ZERO_WIDTH);
    auto isValid = pattern->IsNavBarValid();
    EXPECT_FALSE(isValid);
}

/**
 * @tc.name: IsNavBarValid004
 * @tc.desc: Branch: return !property->GetHideNavBarValue(false) &&
 *                      (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) &&
 *                      (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0)); => true
 *                   !property->GetHideNavBarValue(false) => true
 *                   (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) => true
 *                   (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0)) => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, IsNavBarValid004, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    property->UpdateHideNavBar(false);
    pattern->userSetNavBarWidthFlag_ = false;
    constexpr  Dimension TEST_WIDTH = 500.0_vp;
    property->UpdateMaxNavBarWidth(TEST_WIDTH);
    auto isValid = pattern->IsNavBarValid();
    EXPECT_TRUE(isValid);
}

/**
 * @tc.name: ReplaceNodeWithProxyNodeIfNeeded001
 * @tc.desc: Branch: if (!proxyNode) { => false
 *                   if (property) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ReplaceNodeWithProxyNodeIfNeeded001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destProperty = dest->GetLayoutProperty();
    ASSERT_NE(destProperty, nullptr);
    destProperty->UpdateVisibility(VisibleType::INVISIBLE);

    pattern->ReplaceNodeWithProxyNodeIfNeeded(navContentNode, dest);
    EXPECT_EQ(destProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: ReplaceNodeWithProxyNodeIfNeeded002
 * @tc.desc: Branch: if (!proxyNode) { => false
 *                   if (property) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ReplaceNodeWithProxyNodeIfNeeded002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destProperty = dest->GetLayoutProperty();
    ASSERT_NE(destProperty, nullptr);
    dest->layoutProperty_ = nullptr;
    destProperty->UpdateVisibility(VisibleType::INVISIBLE);

    pattern->ReplaceNodeWithProxyNodeIfNeeded(navContentNode, dest);
    EXPECT_EQ(destProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: ReplaceNodeWithProxyNodeIfNeeded003
 * @tc.desc: Branch: if (!proxyNode) { => false
 *                   if (property) { => true
 *                   if (childIndex < 0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ReplaceNodeWithProxyNodeIfNeeded003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIndex(1);
    auto proxyNode = dest->GetOrCreateProxyNode();
    ASSERT_NE(proxyNode, nullptr);
    proxyNode->SetIndex(2, false);

    pattern->ReplaceNodeWithProxyNodeIfNeeded(navContentNode, dest);
    EXPECT_EQ(proxyNode->GetIndex(), 2);
}

/**
 * @tc.name: ReplaceNodeWithProxyNodeIfNeeded004
 * @tc.desc: Branch: if (!proxyNode) { => false
 *                   if (property) { => true
 *                   if (childIndex < 0) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ReplaceNodeWithProxyNodeIfNeeded004, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    navContentNode->AddChild(dest);
    dest->SetIndex(1);
    auto proxyNode = dest->GetOrCreateProxyNode();
    ASSERT_NE(proxyNode, nullptr);
    proxyNode->SetIndex(2, false);

    pattern->ReplaceNodeWithProxyNodeIfNeeded(navContentNode, dest);
    EXPECT_EQ(proxyNode->GetIndex(), 1);
}

/**
 * @tc.name: RestoreNodeFromProxyNodeIfNeeded001
 * @tc.desc: Branch: if (childIndex < 0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, RestoreNodeFromProxyNodeIfNeeded001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIndex(1);
    auto proxyNode = dest->GetOrCreateProxyNode();
    ASSERT_NE(proxyNode, nullptr);
    proxyNode->SetIndex(2, false);

    pattern->RestoreNodeFromProxyNodeIfNeeded(primaryContentNode, navContentNode, dest);
    EXPECT_EQ(dest->GetIndex(), 1);
}

/**
 * @tc.name: RestoreNodeFromProxyNodeIfNeeded002
 * @tc.desc: Branch: if (childIndex < 0) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, RestoreNodeFromProxyNodeIfNeeded002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto property = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIndex(1);
    auto proxyNode = dest->GetOrCreateProxyNode();
    ASSERT_NE(proxyNode, nullptr);
    proxyNode->SetIndex(2, false);
    navContentNode->AddChild(proxyNode);
    primaryContentNode->AddChild(dest);

    pattern->RestoreNodeFromProxyNodeIfNeeded(primaryContentNode, navContentNode, dest);
    EXPECT_EQ(dest->GetIndex(), 2);
    const auto& childs = navContentNode->GetChildren();
    ASSERT_EQ(childs.size(), 1);
    auto navContentFirstChildNode = *childs.begin();
    EXPECT_EQ(navContentFirstChildNode, dest);
}

/**
 * @tc.name: ReorderPrimaryNodes001
 * @tc.desc: Branch: if (childIndex < 0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ReorderPrimaryNodes001, TestSize.Level1)
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
    std::vector<WeakPtr<NavDestinationGroupNode>> nodes;
    nodes.push_back(dest);

    auto& primaryChilds = primaryContentNode->GetChildren();
    EXPECT_TRUE(primaryChilds.empty());
    pattern->ReorderPrimaryNodes(primaryContentNode, nodes);
    EXPECT_EQ(primaryChilds.size(), 1);
}

/**
 * @tc.name: ReorderPrimaryNodes002
 * @tc.desc: Branch: } else if (slot != childIndex) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ReorderPrimaryNodes002, TestSize.Level1)
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
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::vector<WeakPtr<NavDestinationGroupNode>> nodes;
    nodes.push_back(dest1);
    nodes.push_back(dest2);
    primaryContentNode->AddChild(dest2);
    primaryContentNode->AddChildAfter(dest1, dest2);

    pattern->ReorderPrimaryNodes(primaryContentNode, nodes);
    const auto& childs = primaryContentNode->GetChildren();
    EXPECT_EQ(childs.size(), 2);
    auto it = childs.begin();
    EXPECT_EQ(*it, dest1);
    it++;
    EXPECT_EQ(*it, dest2);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Branch: if (pattern->IsForceSplitSuccess()) { => true
 *                   if (pattern->IsHideNavBarInForceSplitModeNeeded()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    auto context = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    if (!context->taskExecutor_) {
        context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    }
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navProperty = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    pattern->primaryNodes_.clear();
    pattern->forceSplitSuccess_ = true;
    navProperty->UpdateHideNavBar(true);
    navBarProperty->UpdateVisibility(VisibleType::VISIBLE);

    pattern->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Branch: if (pattern->IsForceSplitSuccess()) { => true
 *                   if (pattern->IsHideNavBarInForceSplitModeNeeded()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    auto context = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    if (!context->taskExecutor_) {
        context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    }
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navProperty = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    pattern->primaryNodes_.clear();
    pattern->forceSplitSuccess_ = true;
    navProperty->UpdateHideNavBar(false);
    navBarProperty->UpdateVisibility(VisibleType::INVISIBLE);

    pattern->OnDirtyLayoutWrapperSwap(nullptr, config);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: AdjustNodeForNonDestForceSplit001
 * @tc.desc: Branch: if (forceSplitUseNavBar_) { => true
 *                   if (forceSplitSuccess_ && stackNodePairs.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, AdjustNodeForNonDestForceSplit001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navContentProperty = navContentNode->GetLayoutProperty();
    ASSERT_NE(navContentProperty, nullptr);
    auto phNode = AceType::DynamicCast<FrameNode>(navNode->GetForceSplitPlaceHolderNode());
    ASSERT_NE(phNode, nullptr);
    auto phProperty = phNode->GetLayoutProperty();
    ASSERT_NE(phProperty, nullptr);
    navBarProperty->UpdateVisibility(VisibleType::INVISIBLE);
    phProperty->UpdateVisibility(VisibleType::INVISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::VISIBLE);
    pattern->forceSplitUseNavBar_ = true;
    pattern->forceSplitSuccess_ = true;
    pattern->AdjustNodeForNonDestForceSplit(false);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: AdjustNodeForNonDestForceSplit002
 * @tc.desc: Branch: if (forceSplitUseNavBar_) { => false
 *                   if (forceSplitSuccess_ && stackNodePairs.empty()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, AdjustNodeForNonDestForceSplit002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navProperty = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    auto& pathList = stack->GetAllNavDestinationNodes();
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navContentProperty = navContentNode->GetLayoutProperty();
    ASSERT_NE(navContentProperty, nullptr);
    auto phNode = AceType::DynamicCast<FrameNode>(navNode->GetForceSplitPlaceHolderNode());
    ASSERT_NE(phNode, nullptr);
    auto phProperty = phNode->GetLayoutProperty();
    ASSERT_NE(phProperty, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    pattern->forceSplitUseNavBar_ = false;
    navProperty->UpdateHideNavBar(true);

    navBarProperty->UpdateVisibility(VisibleType::VISIBLE);
    phProperty->UpdateVisibility(VisibleType::VISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::INVISIBLE);
    // forceSplitSuccess_ => false stackNodePairs.empty() => true
    pattern->forceSplitSuccess_ = false;
    pathList.clear();
    pattern->AdjustNodeForNonDestForceSplit(false);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    phProperty->UpdateVisibility(VisibleType::VISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::INVISIBLE);
    // forceSplitSuccess_ => true stackNodePairs.empty() => false
    pattern->forceSplitSuccess_ = true;
    pathList.push_back(testPair);
    pattern->AdjustNodeForNonDestForceSplit(false);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    phProperty->UpdateVisibility(VisibleType::VISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::INVISIBLE);
    // forceSplitSuccess_ => false stackNodePairs.empty() => false
    pattern->forceSplitSuccess_ = false;
    pathList.clear();
    pathList.push_back(testPair);
    pattern->AdjustNodeForNonDestForceSplit(false);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: AdjustNodeForDestForceSplit001
 * @tc.desc: Branch: if (destNodes.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, AdjustNodeForDestForceSplit001, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navProperty = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    auto& pathList = stack->GetAllNavDestinationNodes();
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navContentProperty = navContentNode->GetLayoutProperty();
    ASSERT_NE(navContentProperty, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto primaryProperty = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(primaryProperty, nullptr);
    auto phNode = AceType::DynamicCast<FrameNode>(navNode->GetForceSplitPlaceHolderNode());
    ASSERT_NE(phNode, nullptr);
    auto phProperty = phNode->GetLayoutProperty();
    ASSERT_NE(phProperty, nullptr);
    navProperty->UpdateHideNavBar(true);

    navBarProperty->UpdateVisibility(VisibleType::VISIBLE);
    phProperty->UpdateVisibility(VisibleType::INVISIBLE);
    primaryProperty->UpdateVisibility(VisibleType::VISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::VISIBLE);
    pathList.clear();
    pattern->AdjustNodeForDestForceSplit(false);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(primaryProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: AdjustNodeForDestForceSplit002
 * @tc.desc: Branch: if (destNodes.empty()) { => false
 *                   if (primaryNodes_.empty()) { => false
 *                   if (primaryNodes_.empty() || primaryNodes_.back().Upgrade() != destNodes.back()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, AdjustNodeForDestForceSplit002, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navProperty = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    auto& pathList = stack->GetAllNavDestinationNodes();
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navContentProperty = navContentNode->GetLayoutProperty();
    ASSERT_NE(navContentProperty, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto primaryProperty = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(primaryProperty, nullptr);
    auto phNode = AceType::DynamicCast<FrameNode>(navNode->GetForceSplitPlaceHolderNode());
    ASSERT_NE(phNode, nullptr);
    auto phProperty = phNode->GetLayoutProperty();
    ASSERT_NE(phProperty, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    pathList.push_back(testPair1);
    pathList.push_back(testPair2);
    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = nullptr;
    navProperty->UpdateHideNavBar(true);

    navBarProperty->UpdateVisibility(VisibleType::VISIBLE);
    primaryProperty->UpdateVisibility(VisibleType::INVISIBLE);
    phProperty->UpdateVisibility(VisibleType::INVISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::VISIBLE);
    pattern->AdjustNodeForDestForceSplit(false);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(primaryProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: AdjustNodeForDestForceSplit003
 * @tc.desc: Branch: if (destNodes.empty()) { => false
 *                   if (primaryNodes_.empty()) { => false
 *                   if (primaryNodes_.empty() || primaryNodes_.back().Upgrade() != destNodes.back()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, AdjustNodeForDestForceSplit003, TestSize.Level1)
{
    SetForceSplitEnabled(true);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto navProperty = navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    auto& pathList = stack->GetAllNavDestinationNodes();
    auto navBarNode = AceType::DynamicCast<FrameNode>(navNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto navContentNode = AceType::DynamicCast<FrameNode>(navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navContentProperty = navContentNode->GetLayoutProperty();
    ASSERT_NE(navContentProperty, nullptr);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(navNode->GetPrimaryContentNode());
    ASSERT_NE(primaryContentNode, nullptr);
    auto primaryProperty = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(primaryProperty, nullptr);
    auto phNode = AceType::DynamicCast<FrameNode>(navNode->GetForceSplitPlaceHolderNode());
    ASSERT_NE(phNode, nullptr);
    auto phProperty = phNode->GetLayoutProperty();
    ASSERT_NE(phProperty, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    pathList.push_back(testPair1);
    pathList.push_back(testPair2);
    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->navBarIsHome_ = false;
    pattern->homeNode_ = WeakPtr(dest1);
    navProperty->UpdateHideNavBar(false);

    navBarProperty->UpdateVisibility(VisibleType::VISIBLE);
    primaryProperty->UpdateVisibility(VisibleType::INVISIBLE);
    phProperty->UpdateVisibility(VisibleType::VISIBLE);
    navContentProperty->UpdateVisibility(VisibleType::INVISIBLE);
    pattern->AdjustNodeForDestForceSplit(false);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(primaryProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(phProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
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

/**
 * @tc.name: SetBackButtonIcon001
 * @tc.desc: Test SetBackButtonIcon function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetBackButtonIcon001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonIconKey = "navigation.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetBackButtonIcon(iconSymbol, resObj, imageOption, pixMap, nameList);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResMedia(resObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), result);
}

/**
 * @tc.name: SetBackButtonIcon002
 * @tc.desc: Test SetBackButtonIconSrcAndTextRes function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetBackButtonIcon002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonIconKey = "navigation.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    std::string backButtonTextKey = "navigation.backButtonIcon.accessibilityText";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), "");
    RefPtr<ResourceObject> backButtonIconResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    RefPtr<ResourceObject> backButtonTextResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetBackButtonIconSrcAndTextRes(
        iconSymbol, backButtonIconResObj, imageOption, pixMap, nameList, true, backButtonTextResObj);

    titleBarPattern->OnColorModeChange(1);
    std::string icon;
    ResourceParseUtils::ParseResMedia(backButtonIconResObj, icon);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), icon);
    std::string text;
    ResourceParseUtils::ParseResString(backButtonIconResObj, text);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), text);
}

/**
 * @tc.name: SetBackButtonIcon003
 * @tc.desc: Test UpdateBackButtonIcon function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetBackButtonIcon003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    std::vector<std::string> nameList;
    nameList.push_back("");
    nameList.push_back("");
    std::string backButtonIconKey = "navigation.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.UpdateBackButtonIcon(nameList, frameNode, resObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResMedia(resObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), result);
}

/**
 * @tc.name: SetBackButtonIcon004
 * @tc.desc: Test UpdateBackButtonIconText function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetBackButtonIcon004, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    std::string backButtonTextKey = "navigation.backButtonIcon.accessibilityText";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), "");
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.UpdateBackButtonIconText(true, titleBarNode, resObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResString(resObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), result);
}

/**
 * @tc.name: SetBackButtonIcon005
 * @tc.desc: Test SetBackButtonIconTextRes function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetBackButtonIcon005, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    std::string imageSource = "src";
    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonTextKey = "navigation.backButtonIcon.accessibilityText";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), "");
    RefPtr<ResourceObject> backButtonTextResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetBackButtonIconTextRes(
        iconSymbol, imageSource, imageOption, pixMap, nameList, true, backButtonTextResObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResString(backButtonTextResObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonTextKey), result);
}

/**
 * @tc.name: SetBackButtonIcon006
 * @tc.desc: Test SetBackButtonIcon function with specific node.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetBackButtonIcon006, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    std::string backButtonIconKey = "navigation.backButtonIcon.icon";
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), "");
    RefPtr<ResourceObject> backButtonIconResObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    NavigationModelNG::SetBackButtonIcon(frameNode, iconSymbol, imageOption, pixMap, backButtonIconResObj);

    titleBarPattern->OnColorModeChange(1);
    std::string result;
    ResourceParseUtils::ParseResMedia(backButtonIconResObj, result);
    EXPECT_EQ(titleBarPattern->GetResCacheMapByKey(backButtonIconKey), result);
}

/**
 * @tc.name: SetNavBarWidth002
 * @tc.desc: Test SetMinNavBarWidth and SetMaxNavBarWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetNavBarWidth002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetMinNavBarWidth(resObj);
    std::string minKey = "navigation.navBarWidthRange.minNavBarWidth";
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(minKey), "");
    navigationModel.SetMaxNavBarWidth(resObj);
    std::string maxKey = "navigation.navBarWidthRange.maxNavBarWidth";
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(maxKey), "");
    navigationPattern->OnColorModeChange(1);
    CalcDimension minNavBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, minNavBarWidth);
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(minKey), minNavBarWidth.ToString());
}

/**
 * @tc.name: SetNavBarWidth003
 * @tc.desc: Test SetMinNavBarWidth and SetMaxNavBarWidth function with specific node.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetNavBarWidth003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetMinNavBarWidth(frameNode, resObj);
    std::string minKey = "navigation.navBarWidthRange.minNavBarWidth";
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(minKey), "");
    navigationModel.SetMaxNavBarWidth(frameNode, resObj);
    std::string maxKey = "navigation.navBarWidthRange.maxNavBarWidth";
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(maxKey), "");
    navigationPattern->OnColorModeChange(1);
    CalcDimension minNavBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, minNavBarWidth);
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(minKey), minNavBarWidth.ToString());
}

/**
 * @tc.name: SetNavBarWidth004
 * @tc.desc: Test SetNavBarWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetNavBarWidth004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetNavBarWidth(resObj);
    Dimension value = 250.0_vp;
    navigationPattern->initNavBarWidthValue_ = value;
    EXPECT_EQ(navigationPattern->GetInitNavBarWidth(), value);
    std::string key = "navigation.navBarWidth";
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(key), "");
    navigationPattern->OnColorModeChange(1);
    CalcDimension navBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, navBarWidth);
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(key), navBarWidth.ToString());
}

/**
 * @tc.name: SetNavBarWidth005
 * @tc.desc: Test SetNavBarWidth function with specific node.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetNavBarWidth005, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.SetNavBarWidth(frameNode, resObj);
    Dimension value = 250.0_vp;
    navigationPattern->initNavBarWidthValue_ = value;
    EXPECT_EQ(navigationPattern->GetInitNavBarWidth(), value);
    std::string key = "navigation.navBarWidth";
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(key), "");
    navigationPattern->OnColorModeChange(1);
    CalcDimension navBarWidth;
    ResourceParseUtils::ParseResDimensionVpNG(resObj, navBarWidth);
    EXPECT_EQ(navigationPattern->GetResCacheMapByKey(key), navBarWidth.ToString());
}

/**
 * @tc.name: ParseTitleHeight001
 * @tc.desc: Test ParseTitleHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, ParseTitleHeight001, TestSize.Level1)
{
    /**
     * @tc.steps1: init
     * @tc.expected: All pointer is non-null.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    std::string heighValue;
    std::string key = "navigation.title.customtitle";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    navigationModel.ParseTitleHeight(titleBarNode, resObj);
    std::string heighString = titleBarPattern->GetResCacheMapByKey(key);
    EXPECT_EQ(heighString, "0.00px");
    ResourceParseUtils::ParseResString(resObj, key);
    CalcDimension height;
    bool isValid = ResourceParseUtils::ParseResDimensionVpNG(resObj, height);
    EXPECT_EQ(isValid, false);
}

/**
 * @tc.name: SetTitleHeight002
 * @tc.desc: Test SetTitleHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, SetTitleHeight002, TestSize.Level1)
{
    /**
     * @tc.steps1: init
     * @tc.expected: All pointer is non-null.
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    CalcDimension height;
    auto heightValue = navigationModel.ParseTitleHeight(titleBarNode, resObj);
    EXPECT_EQ(height, heightValue);
    titleBarPattern->OnColorModeChange(1);
}

/**
 * @tc.name: BarItemPattern_ToJsonValue001
 * @tc.desc: Test ToJsonValue when filter.IsFastFilter() is true.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, BarItemPattern_ToJsonValue001, TestSize.Level1)
{
    auto barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 1; // Make IsFastFilter() true
    barItemPattern->ToJsonValue(json, filter);
    // Only check that function runs, as fast filter returns early
    SUCCEED();
}

/**
 * @tc.name: BarItemPattern_ToJsonValue002
 * @tc.desc: Test ToJsonValue when filter.IsFastFilter() is false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, BarItemPattern_ToJsonValue002, TestSize.Level1)
{
    auto barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);

    // Set up text node and property
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->propContent_ = u"TestLabel";
    barItemNode->SetTextNode(textNode);

    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    InspectorFilter filter; // IsFastFilter() false
    barItemPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("label"), "TestLabel");
}

/**
 * @tc.name: BarItemPattern_OnThemeScopeUpdate001
 * @tc.desc: Test OnThemeScopeUpdate with ToolbarIconStatus::ACTIVE and iconNode is SYMBOL_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, BarItemPattern_OnThemeScopeUpdate001, TestSize.Level1)
{
    auto barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);

    // Set icon node as SYMBOL_ETS_TAG
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    barItemNode->SetIconNode(iconNode);

    // Set text node
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    barItemNode->SetTextNode(textNode);

    barItemPattern->SetCurrentIconStatus(ToolbarIconStatus::ACTIVE);
    bool result = barItemPattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: BarItemPattern_OnThemeScopeUpdate002
 * @tc.desc: Test OnThemeScopeUpdate with ToolbarIconStatus::INITIAL and iconNode is not SYMBOL_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, BarItemPattern_OnThemeScopeUpdate002, TestSize.Level1)
{
    auto barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);

    // Set icon node as IMAGE_ETS_TAG (not SYMBOL_ETS_TAG)
    auto iconNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    barItemNode->SetIconNode(iconNode);

    // Set text node
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    barItemNode->SetTextNode(textNode);

    barItemPattern->SetCurrentIconStatus(ToolbarIconStatus::INITIAL);
    bool result = barItemPattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: InnerNavigationController_DeletePIPMode001
 * @tc.desc: Test DeletePIPMode with valid navigation pattern and stack.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, InnerNavigationController_DeletePIPMode001, TestSize.Level1)
{
    // Create navigation pattern
    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    // Create navigation stack
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationPattern->SetNavigationStack(navigationStack);

    // Create InnerNavigationController using std::make_unique since it's not a Referenced subclass
    auto controller = std::make_unique<InnerNavigationController>(navigationPattern, 1);
    ASSERT_NE(controller, nullptr);

    // Test DeletePIPMode
    int32_t handle = 123;
    controller->DeletePIPMode(handle);
    SUCCEED();
}

/**
 * @tc.name: NavBarNode_InitSoftTransitionPop001
 * @tc.desc: Test InitSoftTransitionPop function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, NavBarNode_InitSoftTransitionPop001, TestSize.Level1)
{
    // Create NavBarNode
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    // Test InitSoftTransitionPop
    navBarNode->InitSoftTransitionPop();

    // Verify the function executed without crashing
    auto renderContext = navBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: NavBarNode_SoftTransitionPushAction001
 * @tc.desc: Test SoftTransitionPushAction with isStart = true.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, NavBarNode_SoftTransitionPushAction001, TestSize.Level1)
{
    // Create NavBarNode
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    // Test SoftTransitionPushAction with isStart = true
    navBarNode->SoftTransitionPushAction(true);

    // Verify the function executed without crashing
    auto renderContext = navBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: NavBarNode_SoftTransitionPushAction002
 * @tc.desc: Test SoftTransitionPushAction with isStart = false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, NavBarNode_SoftTransitionPushAction002, TestSize.Level1)
{
    // Create NavBarNode
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    // Test SoftTransitionPushAction with isStart = false
    navBarNode->SoftTransitionPushAction(false);

    // Verify the function executed without crashing
    auto renderContext = navBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: NavBarNode_StartSoftTransitionPush001
 * @tc.desc: Test StartSoftTransitionPush function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, NavBarNode_StartSoftTransitionPush001, TestSize.Level1)
{
    // Create NavBarNode
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    // Test StartSoftTransitionPush
    navBarNode->StartSoftTransitionPush();

    // Verify the function executed without crashing
    auto renderContext = navBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: NavBarNode_StartSoftTransitionPop001
 * @tc.desc: Test StartSoftTransitionPop function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, NavBarNode_StartSoftTransitionPop001, TestSize.Level1)
{
    // Create NavBarNode
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navBarNode, nullptr);

    // Test StartSoftTransitionPop
    navBarNode->StartSoftTransitionPop();

    // Verify the function executed without crashing
    auto renderContext = navBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
}

/**
 * @tc.name: TitleBarNode_MarkIsInitialTitle001
 * @tc.desc: Test MarkIsInitialTitle with true and false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, TitleBarNode_MarkIsInitialTitle001, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto pattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(pattern, nullptr);

    titleBarNode->MarkIsInitialTitle(true);
    EXPECT_TRUE(pattern->isInitialTitle_);

    titleBarNode->MarkIsInitialTitle(false);
    EXPECT_FALSE(pattern->isInitialTitle_);
}

/**
 * @tc.name: TransitionWithOutAnimationTest001
 * @tc.desc: if navBar -> navDestination and mode has changed from stack to split.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, TransitionWithOutAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation group node.
     */
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(mockNavPathStack);
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. mock push to add navDestination into navigation, and check the homeNode visibility.
     */
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest"), false);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    auto homeNode = AceType::DynamicCast<FrameNode>(navigation->GetNavBarOrHomeDestinationNode());
    ASSERT_TRUE(homeNode->IsVisible());
    /**
     * @tc.steps: step3. mock layout property navigationMode, do stack sync and check the homeNode visibility.
     */
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    auto layoutProperty = navigationPattern->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_TRUE(homeNode->IsVisible());
}

/**
 * @tc.name: TransitionWithOutAnimationTest002
 * @tc.desc: if navBar -> navDestination and mode has changed from split to stack.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, TransitionWithOutAnimationTest002, TestSize.Level1)
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
     * @tc.steps: step2. mock push to add navDestination into navigation, and check the homeNode visibility.
     */
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest"), false);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    auto homeNode = AceType::DynamicCast<FrameNode>(navigation->GetNavBarOrHomeDestinationNode());
    ASSERT_TRUE(homeNode->IsVisible());
    /**
     * @tc.steps: step3. mock layout property navigationMode, do stack sync and check the homeNode visibility.
     */
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    auto layoutProperty = navigationPattern->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_FALSE(homeNode->IsVisible());
}

/**
 * @tc.name: TransitionWithOutAnimationTest003
 * @tc.desc: if navBar -> navDestination and mode NOT changed(SPLIT).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, TransitionWithOutAnimationTest003, TestSize.Level1)
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
     * @tc.steps: step2. mock push to add navDestination into navigation, and check the homeNode visibility.
     */
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest"), false);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    auto homeNode = AceType::DynamicCast<FrameNode>(navigation->GetNavBarOrHomeDestinationNode());
    ASSERT_TRUE(homeNode->IsVisible());
    /**
     * @tc.steps: step3. mock layout property navigationMode, do stack sync and check the homeNode visibility.
     */
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    auto layoutProperty = navigationPattern->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_TRUE(homeNode->IsVisible());
}

/**
 * @tc.name: TransitionWithOutAnimationTest004
 * @tc.desc: if navBar -> navDestination and mode NOT changed(STACK).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestSevenNg, TransitionWithOutAnimationTest004, TestSize.Level1)
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
     * @tc.steps: step2. mock push to add navDestination into navigation, and check the homeNode visibility.
     */
    mockNavPathStack->MockPushPath(AceType::MakeRefPtr<MockNavPathInfo>("dest"), false);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    auto homeNode = AceType::DynamicCast<FrameNode>(navigation->GetNavBarOrHomeDestinationNode());
    ASSERT_TRUE(homeNode->IsVisible());
    /**
     * @tc.steps: step3. mock layout property navigationMode, do stack sync and check the homeNode visibility.
     */
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    auto layoutProperty = navigationPattern->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_FALSE(homeNode->IsVisible());
}
} // namespace OHOS::Ace::NG
