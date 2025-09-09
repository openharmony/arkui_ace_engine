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
#include <iostream>
#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/mousestyle/mouse_style.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAVIGATION_ID1 = "Navigation1";
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
const InspectorFilter filter;
const std::string TEST_TAG = "test";
constexpr Dimension STACK_WIDTH = 510.0_vp;
constexpr float HEIGHT = 1000.0f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;

RefPtr<NavigationBarTheme> CreateAndBindNavigationBarTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    return navigationTheme;
}
} // namespace

using SwitchHandleFunc = std::function<void(const AbilityContextInfo&, NavDestinationSwitchInfo&)>;

class NavigationPatternTestFiveNg : public testing::Test {
public:
    static RefPtr<DialogTheme> dialogTheme_;
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateDialogNode();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    void MockPipelineContextGetTheme();

    static void TestNavSwitchHandleFunc(const AbilityContextInfo& ctxInfo, NavDestinationSwitchInfo& switchInfo)
    {
        if (innerHandleFunc_) {
            innerHandleFunc_(ctxInfo, switchInfo);
        }
    }
    static SwitchHandleFunc innerHandleFunc_;
};

SwitchHandleFunc NavigationPatternTestFiveNg::innerHandleFunc_;

void NavigationPatternTestFiveNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
{
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { width, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

void NavigationPatternTestFiveNg::MockPipelineContextGetTheme()
{
    CreateAndBindNavigationBarTheme();
}

namespace {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == DialogTheme::TypeId()) {
        return NavigationPatternTestFiveNg::dialogTheme_;
    } else if (type == NavigationBarTheme::TypeId()) {
        return NavigationPatternTestFiveNg::navigationBarTheme_;
    } else {
        return nullptr;
    }
}
} // namespace

RefPtr<DialogTheme> NavigationPatternTestFiveNg::dialogTheme_ = nullptr;
RefPtr<NavigationBarTheme> NavigationPatternTestFiveNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestFiveNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestFiveNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> NavigationPatternTestFiveNg::CreateDialogNode()
{
    auto contentNode = FrameNode::CreateFrameNode(
        V2::BLANK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    DialogProperties dialogProperties {
        .title = "Title",
        .content = "Content",
        .width = 300,
        .height = 200,
    };
    return DialogView::CreateDialogNode(dialogProperties, contentNode);
}

/**
 * @tc.name: CheckIfNoNeedAnimationForForceSplit001
 * @tc.desc: Branch: if (!forceSplitSuccess_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNoNeedAnimationForForceSplit001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->forceSplitSuccess_ = false;
    EXPECT_FALSE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, nullptr));
}

/**
 * @tc.name: CheckIfNoNeedAnimationForForceSplit002
 * @tc.desc: Branch: if (!forceSplitSuccess_) { => false
 *                   if (forceSplitUseNavBar_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNoNeedAnimationForForceSplit002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = true;
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, nullptr));
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(dest, nullptr));
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, dest));
    EXPECT_FALSE(pattern->CheckIfNoNeedAnimationForForceSplit(dest, dest));
}

/**
 * @tc.name: CheckIfNoNeedAnimationForForceSplit003
 * @tc.desc: Branch: if (!forceSplitSuccess_) { => false
 *                   if (forceSplitUseNavBar_) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNoNeedAnimationForForceSplit003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    dest->SetIsShowInPrimaryPartition(true);

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    EXPECT_FALSE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, nullptr));
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(dest, nullptr));
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(nullptr, dest));
    EXPECT_TRUE(pattern->CheckIfNoNeedAnimationForForceSplit(dest, dest));
}

/**
 * @tc.name: NotifyPrePrimaryNodesOnWillHide001
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyPrePrimaryNodesOnWillHide001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_SHOWN;

    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = false;
    pattern->forceSplitUseNavBar_ = false;
    pattern->NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_SHOWN);

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = true;
    pattern->NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_SHOWN);

    pattern->forceSplitSuccess_ = false;
    pattern->forceSplitUseNavBar_ = true;
    pattern->NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: NotifyPrePrimaryNodesOnWillHide002
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => false
 *                   if (filterNodes.find(node) != filterNodes.end()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyPrePrimaryNodesOnWillHide002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_SHOWN;

    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    filterNodes.emplace(dest);
    pattern->NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: NotifyPrePrimaryNodesOnWillHide003
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => false
 *                   if (filterNodes.find(node) != filterNodes.end()) { => false
 *                   if (!pattern->GetIsOnShow()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyPrePrimaryNodesOnWillHide003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
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
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_SHOWN;

    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    destPattern->SetIsOnShow(false);
    pattern->NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: NotifyPrePrimaryNodesOnWillHide004
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => false
 *                   if (filterNodes.find(node) != filterNodes.end()) { => false
 *                   if (!pattern->GetIsOnShow()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyPrePrimaryNodesOnWillHide004, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
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
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_SHOWN;

    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    destPattern->SetIsOnShow(true);
    pattern->NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_WILL_HIDE);
}

/**
 * @tc.name: NotifyCurPrimaryNodesOnWillShow001
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyCurPrimaryNodesOnWillShow001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_HIDDEN;

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = false;
    pattern->forceSplitUseNavBar_ = false;
    pattern->NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_HIDDEN);

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = true;
    pattern->NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_HIDDEN);

    pattern->forceSplitSuccess_ = false;
    pattern->forceSplitUseNavBar_ = true;
    pattern->NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: NotifyCurPrimaryNodesOnWillShow002
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => false
 *                   if (filterNodes.find(node) != filterNodes.end()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyCurPrimaryNodesOnWillShow002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_HIDDEN;

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    filterNodes.emplace(dest);
    pattern->NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: NotifyCurPrimaryNodesOnWillShow003
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => false
 *                   if (filterNodes.find(node) != filterNodes.end()) { => false
 *                   if (pattern->GetIsOnShow()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyCurPrimaryNodesOnWillShow003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
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
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_HIDDEN;

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    destPattern->SetIsOnShow(true);
    pattern->NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_HIDDEN);
}

/**
 * @tc.name: NotifyCurPrimaryNodesOnWillShow004
 * @tc.desc: Branch: if (!forceSplitSuccess_ || forceSplitUseNavBar_) { => false
 *                   if (filterNodes.find(node) != filterNodes.end()) { => false
 *                   if (pattern->GetIsOnShow()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyCurPrimaryNodesOnWillShow004, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
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
    auto eventHub = dest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->state_ = NavDestinationState::ON_HIDDEN;

    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest));
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;

    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    destPattern->SetIsOnShow(false);
    pattern->NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    EXPECT_EQ(eventHub->state_, NavDestinationState::ON_WILL_SHOW);
}

/**
 * @tc.name: StartTransition001
 * @tc.desc: Branch: if (CheckIfNoNeedAnimationForForceSplit(preDestination, topDestination)) { => true
 *                   if (isNotNeedAnimation) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, StartTransition001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto preTop = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTop, nullptr);
    preTop->SetIsShowInPrimaryPartition(true);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", preTop};
    auto curTop = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(curTop, nullptr);
    curTop->SetIsShowInPrimaryPartition(false);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", curTop};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair1);
    stack->navPathList_.push_back(testPair2);
    pattern->forceSplitSuccess_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = WeakPtr(preTop);
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(preTop));
    pattern->primaryNodes_ = pattern->prePrimaryNodes_;
    
    pattern->StartTransition(preTop, curTop, true, false, true);
    EXPECT_TRUE(pattern->prePrimaryNodes_.empty());
}

/**
 * @tc.name: StartTransition002
 * @tc.desc: Branch: if (CheckIfNoNeedAnimationForForceSplit(preDestination, topDestination)) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, StartTransition002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto preTop = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTop, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", preTop};
    auto curTop = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(curTop, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", curTop};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair1);
    stack->navPathList_.push_back(testPair2);
    pattern->forceSplitSuccess_ = false;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = nullptr;
    pattern->prePrimaryNodes_.clear();
    pattern->prePrimaryNodes_.push_back(WeakPtr(preTop));
    pattern->primaryNodes_.clear();

    pattern->StartTransition(preTop, curTop, true, false, true);
    EXPECT_TRUE(pattern->prePrimaryNodes_.empty());
}

/**
 * @tc.name: NavigationToolBarManager_001
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NavigationToolBarManager_001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    int32_t modifyDoneCallbackCount = 0;
    int32_t toolBarChangeCallback = 0;
    toolBarManager->SetModifyDoneCallback([&modifyDoneCallbackCount]() {
        modifyDoneCallbackCount++;
    });
    toolBarManager->SetToolBarChangeCallback([&toolBarChangeCallback]() {
        toolBarChangeCallback++;
    });

    // init SetUsrNavigationMode:SPLIT, expect run callback after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitToolBarManager();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    ASSERT_EQ(modifyDoneCallbackCount, 1);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationPatternTestFiveNg::RunMeasureAndLayout(layoutWrapper);

    ASSERT_EQ(modifyDoneCallbackCount, 1);
    ASSERT_EQ(toolBarChangeCallback, 4);
}

/**
 * @tc.name: NavigationToolBarManager_002
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NavigationToolBarManager_002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    // init SetUsrNavigationMode:SPLIT, expect run callback after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitToolBarManager();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationPatternTestFiveNg::RunMeasureAndLayout(layoutWrapper);

    // NavBar | Divider | NavDest
    // 240    | 1       | 239    = 480
    auto navBarInfo = toolBarManager->GetNavBarInfo();
    ASSERT_TRUE(navBarInfo.isShow);
    ASSERT_EQ(navBarInfo.width, 240);
    auto navDestInfo = toolBarManager->GetNavDestInfo();
    ASSERT_TRUE(navDestInfo.isShow);
    ASSERT_EQ(navDestInfo.width, 239);
    ASSERT_TRUE(toolBarManager->HasNavBar());
    ASSERT_TRUE(toolBarManager->HasNavDest());
}

/**
 * @tc.name: NavigationToolBarManager_003
 * @tc.desc: Test ToolbarManager SetToolBarChangeCallback and SetModifyDoneCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NavigationToolBarManager_003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    auto pipelineContext = frameNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto toolBarManager = pipelineContext->GetToolbarManager();
    ASSERT_NE(toolBarManager, nullptr);

    int32_t toolBarChangeCallback = 0;
    toolBarManager->SetToolBarChangeCallback([&toolBarChangeCallback]() {
        toolBarChangeCallback++;
    });

    // init SetUsrNavigationMode:SPLIT, expect run callback after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitToolBarManager();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationPatternTestFiveNg::RunMeasureAndLayout(layoutWrapper);

    pattern->HandleDragUpdate(16);
    ASSERT_EQ(toolBarChangeCallback, 4);
    auto navDividerInfo = toolBarManager->GetNavBarDividerInfo();
    ASSERT_EQ(navDividerInfo.width, 1);
}

/**
 * @tc.name: GetFirstNewDestinationIndex001
 * @tc.desc: Branch: if (preNodeSet.find(uiNode) != preNodeSet.end()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, GetFirstNewDestinationIndex001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATION_TITLE_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(node, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", node};
    NavPathList preList;
    preList.push_back(testPair);
    NavPathList curList;
    curList.push_back(testPair);

    EXPECT_EQ(pattern->GetFirstNewDestinationIndex(preList, curList), -1);
}

/**
 * @tc.name: GetFirstNewDestinationIndex002
 * @tc.desc: Branch: if (preNodeSet.find(uiNode) != preNodeSet.end()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, GetFirstNewDestinationIndex002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto node = FrameNode::GetOrCreateFrameNode(
        V2::NAVIGATION_TITLE_COMPONENT_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(node, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", node};
    NavPathList preList;
    NavPathList curList;
    curList.push_back(testPair);

    EXPECT_EQ(pattern->GetFirstNewDestinationIndex(preList, curList), -1);
}

/**
 * @tc.name: GetFirstNewDestinationIndex003
 * @tc.desc: Branch: first loop: if (preNodeSet.find(uiNode) != preNodeSet.end()) { => true
 *                   second loop: if (preNodeSet.find(uiNode) != preNodeSet.end()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, GetFirstNewDestinationIndex003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
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
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    NavPathList preList;
    preList.push_back(testPair1);
    NavPathList curList;
    curList.push_back(testPair1);
    curList.push_back(testPair2);

    EXPECT_EQ(pattern->GetFirstNewDestinationIndex(preList, curList), 1);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded001
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;

    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = false;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);

    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);

    pattern->forceSplitSuccess_ = false;
    pattern->homeNodeTouched_ = false;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded002
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = nullptr;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    EXPECT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded003
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    NavPathList preList;
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);

    pattern->forceSplitUseNavBar_ = true;
    pattern->homeNode_ = nullptr;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);

    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = WeakPtr(dest);
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);

    pattern->forceSplitUseNavBar_ = true;
    pattern->homeNode_ = WeakPtr(dest);
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded004
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => false
 *                   if (it != preList.end()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded004, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    pattern->needSyncWithJsStack_ = true;
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    NavPathList preList;
    preList.push_back(testPair);
    stack->navPathList_ = preList;

    pattern->forceSplitUseNavBar_ = true;
    pattern->homeNode_ = WeakPtr(dest);
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded005
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => false
 *                   if (it != preList.end()) { => false
 *                   if (!forceSplitUseNavBar_ && node == homeNode) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded005, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    auto dest3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest3, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair3{"three", dest3};
    auto dest4 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest4, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair4{"four", dest4};

    NavPathList preList;
    preList.push_back(testPair1);
    preList.push_back(testPair2);
    preList.push_back(testPair3);
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair1);
    stack->navPathList_.push_back(testPair4);

    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = WeakPtr(dest1);

    pattern->needSyncWithJsStack_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded006
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => false
 *                   if (it != preList.end()) { => false
 *                   if (!forceSplitUseNavBar_ && node == homeNode) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded006, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    auto dest3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest3, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair3{"three", dest3};
    auto dest4 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest4, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair4{"four", dest4};

    NavPathList preList;
    preList.push_back(testPair1);
    preList.push_back(testPair2);
    preList.push_back(testPair3);

    // use NavDestination as HomePage
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = WeakPtr(dest1);
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair3);
    stack->navPathList_.push_back(testPair4);
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);

    // use NavBar as HomePage
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = true;
    pattern->homeNode_ = nullptr;
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair3);
    stack->navPathList_.push_back(testPair4);
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_FALSE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded007
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => false
 *                   if (it != preList.end()) { => false
 *                   if (!forceSplitUseNavBar_ && node == homeNode) { => false
 *                   if (!forceSplitUseNavBar_ && !foundHomeNode) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded007, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    auto dest3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest3, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair3{"three", dest3};

    NavPathList preList;
    preList.push_back(testPair1);
    preList.push_back(testPair2);

    // use NavDestination as HomePage
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = false;
    pattern->homeNode_ = WeakPtr(dest1);
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair2);
    stack->navPathList_.push_back(testPair3);
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded008
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => false
 *                   if (it != preList.end()) { => false
 *                   if (!forceSplitUseNavBar_ && !foundHomeNode) { => false
 *                   if (removeIndexes.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded008, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    auto dest3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest3, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair3{"three", dest3};

    NavPathList preList;
    preList.push_back(testPair1);
    preList.push_back(testPair2);

    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = true;
    pattern->homeNode_ = nullptr;
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair3);
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    ASSERT_TRUE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: ClearSecondaryNodesIfNeeded009
 * @tc.desc: Branch: if (!forceSplitSuccess_ || !homeNodeTouched_) { => false
 *                   if (!forceSplitUseNavBar_ && !homeNode) { => false
 *                   if (curList.empty()) { => false
 *                   if (it != preList.end()) { => false
 *                   if (!forceSplitUseNavBar_ && node == homeNode) { => false
 *                   if (!forceSplitUseNavBar_ && !foundHomeNode) { => false
 *                   if (removeIndexes.empty()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, ClearSecondaryNodesIfNeeded009, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    auto dest3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest3, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair3{"three", dest3};

    NavPathList preList;
    preList.push_back(testPair1);
    preList.push_back(testPair2);

    // use NavBar as HomePage
    pattern->forceSplitSuccess_ = true;
    pattern->homeNodeTouched_ = true;
    pattern->forceSplitUseNavBar_ = true;
    pattern->homeNode_ = nullptr;
    stack->navPathList_ = preList;
    stack->navPathList_.push_back(testPair3);
    pattern->needSyncWithJsStack_ = true;
    pattern->ClearSecondaryNodesIfNeeded(std::move(preList));
    EXPECT_FALSE(pattern->needSyncWithJsStack_);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded001
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);

    manager->isForceSplitSupported_ = false;

    pattern->homeNode_ = nullptr;
    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded002
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => false
 *                   if (homeNode) { => true
 *                   if (node == homeNode) { => true
 *                   if (!homeNodeExistInCurStack) { => false
 *                   if (homeNode) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = true;

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);

    pattern->homeNode_ = WeakPtr(dest);
    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), dest);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded003
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => false
 *                   if (homeNode) { => false
 *                   if (homeNode) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    stack->navPathList_.clear();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = true;
    pattern->homeNode_ = nullptr;
    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded004
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => false
 *                   if (homeNode) { => false
 *                   if (homeNode) { => false
 *                   if (ForceSplitUtils::IsHomePageNavDestination(node)) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded004, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = true;

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);

    pattern->homeNode_ = nullptr;
    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded005
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => false
 *                   if (homeNode) { => false
 *                   if (homeNode) { => false
 *                   if (ForceSplitUtils::IsHomePageNavDestination(node)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded005, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = true;
    manager->homePageName_ = "one";

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    destPattern->SetName("one");
    dest->SetNavDestinationMode(NavDestinationMode::STANDARD);
    std::pair<std::string, RefPtr<UINode>> testPair{"one", dest};
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair);

    pattern->homeNode_ = nullptr;
    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), dest);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded006
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => false
 *                   if (homeNode) { => true
 *                   if (node == homeNode) { => false
 *                   if (!homeNodeExistInCurStack) { => true
 *                   if (homeNode) { => false
 *                   if (ForceSplitUtils::IsHomePageNavDestination(node)) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded006, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = true;

    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    pattern->homeNode_ = WeakPtr(dest1);
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair2);

    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: RecognizeHomePageIfNeeded007
 * @tc.desc: Branch: if (!IsForceSplitSupported(context)) { => false
 *                   if (homeNode) { => true
 *                   if (node == homeNode) { => false
 *                   if (!homeNodeExistInCurStack) { => true
 *                   if (homeNode) { => false
 *                   if (ForceSplitUtils::IsHomePageNavDestination(node)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, RecognizeHomePageIfNeeded007, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& stack = pattern->navigationStack_;
    ASSERT_NE(stack, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitSupported_ = true;
    manager->homePageName_ = "two";
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    std::pair<std::string, RefPtr<UINode>> testPair1{"one", dest1};
    auto dest2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest2, nullptr);
    auto destPattern2 = dest2->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern2, nullptr);
    destPattern2->SetName("two");
    std::pair<std::string, RefPtr<UINode>> testPair2{"two", dest2};
    pattern->homeNode_ = WeakPtr(dest1);
    stack->navPathList_.clear();
    stack->navPathList_.push_back(testPair2);

    pattern->RecognizeHomePageIfNeeded();
    EXPECT_EQ(pattern->homeNode_.Upgrade(), dest2);
}

/**
 * @tc.name: CheckIfNeedHideOrShowPrimaryNodes001
 * @tc.desc: Branch: if (!pattern->GetHomeNode()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNeedHideOrShowPrimaryNodes001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->homeNode_ = nullptr;
    EXPECT_FALSE(NavigationPattern::CheckIfNeedHideOrShowPrimaryNodes(pattern, 0));
}

/**
 * @tc.name: CheckIfNeedHideOrShowPrimaryNodes002
 * @tc.desc: Branch: if (!pattern->GetHomeNode()) { => false
 *                   if (primaryNodes.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNeedHideOrShowPrimaryNodes002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    pattern->homeNode_ = WeakPtr(dest1);
    pattern->primaryNodes_.clear();
    EXPECT_FALSE(NavigationPattern::CheckIfNeedHideOrShowPrimaryNodes(pattern, 0));
}

/**
 * @tc.name: CheckIfNeedHideOrShowPrimaryNodes003
 * @tc.desc: Branch: if (!pattern->GetHomeNode()) { => false
 *                   if (primaryNodes.empty()) { => false
 *                   if (homeIndex >= lastStandardIndex) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNeedHideOrShowPrimaryNodes003, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    dest1->SetIndex(1);
    pattern->homeNode_ = WeakPtr(dest1);
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest1));
    EXPECT_FALSE(NavigationPattern::CheckIfNeedHideOrShowPrimaryNodes(pattern, 0));
}

/**
 * @tc.name: CheckIfNeedHideOrShowPrimaryNodes004
 * @tc.desc: Branch: if (!pattern->GetHomeNode()) { => false
 *                   if (primaryNodes.empty()) { => false
 *                   if (homeIndex >= lastStandardIndex) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, CheckIfNeedHideOrShowPrimaryNodes004, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto dest1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest1, nullptr);
    dest1->SetIndex(1);
    pattern->homeNode_ = WeakPtr(dest1);
    pattern->primaryNodes_.clear();
    pattern->primaryNodes_.push_back(WeakPtr(dest1));
    EXPECT_TRUE(NavigationPattern::CheckIfNeedHideOrShowPrimaryNodes(pattern, 5));
}

/**
 * @tc.name: NotifyNavDestinationSwitch001
 * @tc.desc: Branch: if (IsForceSplitSupported(context) && forceSplitSuccess_ && from) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyNavDestinationSwitch001, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    auto destCtx = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(destCtx, nullptr);
    destPattern->SetNavDestinationContext(destCtx);

    std::optional<NavDestinationState> fromState;
    auto backupFunc = UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_;
    UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_ =
        NavigationPatternTestFiveNg::TestNavSwitchHandleFunc;
    NavigationPatternTestFiveNg::innerHandleFunc_ =
        [&fromState](const AbilityContextInfo& ctxInfo, NavDestinationSwitchInfo& switchInfo) {
            fromState = std::nullopt;
            if (switchInfo.from.has_value()) {
                fromState = switchInfo.from.value().state;
            }
        };

    manager->isForceSplitSupported_ = false;
    fromState = std::nullopt;
    pattern->NotifyNavDestinationSwitch(destCtx, nullptr, NavigationOperation::PUSH);
    ASSERT_TRUE(fromState.has_value());
    ASSERT_EQ(fromState.value(), NavDestinationState::ON_HIDDEN);

    manager->isForceSplitSupported_ = true;
    pattern->forceSplitSuccess_ = false;
    fromState = std::nullopt;
    pattern->NotifyNavDestinationSwitch(destCtx, nullptr, NavigationOperation::PUSH);
    ASSERT_TRUE(fromState.has_value());
    ASSERT_EQ(fromState.value(), NavDestinationState::ON_HIDDEN);

    manager->isForceSplitSupported_ = true;
    pattern->forceSplitSuccess_ = true;
    fromState = std::nullopt;
    pattern->NotifyNavDestinationSwitch(nullptr, nullptr, NavigationOperation::PUSH);
    ASSERT_FALSE(fromState.has_value());

    UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_ = backupFunc;
}

/**
 * @tc.name: NotifyNavDestinationSwitch002
 * @tc.desc: Branch: if (IsForceSplitSupported(context) && forceSplitSuccess_ && from) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestFiveNg, NotifyNavDestinationSwitch002, TestSize.Level1)
{
    NavigationPatternTestFiveNg::SetUpTestSuite();
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetNavigationManager();
    ASSERT_NE(manager, nullptr);
    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto destPattern = dest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    auto destCtx = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(destCtx, nullptr);
    destPattern->SetNavDestinationContext(destCtx);
    destPattern->SetIsOnShow(true);

    std::optional<NavDestinationState> fromState;
    auto backupFunc = UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_;
    UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_ =
        NavigationPatternTestFiveNg::TestNavSwitchHandleFunc;
    NavigationPatternTestFiveNg::innerHandleFunc_ =
        [&fromState](const AbilityContextInfo& ctxInfo, NavDestinationSwitchInfo& switchInfo) {
            fromState = std::nullopt;
            if (switchInfo.from.has_value()) {
                fromState = switchInfo.from.value().state;
            }
        };

    manager->isForceSplitSupported_ = true;
    pattern->forceSplitSuccess_ = true;
    fromState = std::nullopt;
    pattern->NotifyNavDestinationSwitch(destCtx, nullptr, NavigationOperation::PUSH);
    ASSERT_TRUE(fromState.has_value());
    ASSERT_EQ(fromState.value(), NavDestinationState::ON_SHOWN);

    UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_ = backupFunc;
}
} // namespace OHOS::Ace::NG