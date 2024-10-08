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

#include "test/mock/base/mock_task_executor.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/base/mock_system_bar_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string TEST_TAG = "test";
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
} // namespace

class NavigationPatternTestNgOne : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
};

void NavigationPatternTestNgOne::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationPatternTestNgOne::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void PerformTransition(const RefPtr<NavigationTransitionProxy>& proxy) {}

void HandleEnd(bool success) {}

void NavDestinationSwitchHandle(const AbilityContextInfo& abilityContextInfo,
                                NavDestinationSwitchInfo& navDestinationSwitchInfo) {}

NavigationTransition CustomNavigationAnimation(RefPtr<NavDestinationContext> fromContext,
                                               RefPtr<NavDestinationContext> toContext,
                                               NavigationOperation operation)
{
    struct NavigationTransition navigationTransition;
    navigationTransition.transition = PerformTransition;
    navigationTransition.endCallback = HandleEnd;
    return navigationTransition;
}

void NavigationPatternTestNgOne::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

void NavigationPatternTestNgOne::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: NavigationPatternTestOne_001
 * @tc.desc: Test Navigation HandleDrag
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Navigation ,then get pattern.
     */
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.width_ = 10.0;
    layoutConstraint.selfIdealSize.height_ = 10.0;
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    pattern->isDividerDraggable_ = false;
    pattern->HandleDragStart();
    EXPECT_FALSE(pattern->isInDividerDrag_);
}

/**
 * @tc.name: NavigationPatternTestOne_002
 * @tc.desc: Test Navigation FireNavigationStateChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_002, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. call FireNavigationStateChange
     * @tc.expected: pattern is not nullptr.
     */
    navigationPattern->FireNavigationStateChange(AceType::DynamicCast<UINode>(navBarNode), true);
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->FireNavigationStateChange(AceType::DynamicCast<UINode>(navBarNode), false);
    EXPECT_NE(navigationPattern, nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_003
 * @tc.desc: Test Navigation FireNavigationStateChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation contentNode and navBarNode.
     * @tc.expected: check whether the properties is correct.
     */
    MockPipelineContextGetTheme();
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. call OnColorConfigurationUpdate
     * @tc.expected: pattern is not nullptr.
     */
    navigationPattern->OnColorConfigurationUpdate();
    EXPECT_NE(navigationPattern, nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_004
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_004, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto from = AceType::MakeRefPtr<NavDestinationContext>();
    auto to = AceType::MakeRefPtr<NavDestinationContext>();
    navigationPattern->NotifyNavDestinationSwitch(from, to, NavigationOperation::POP);
    ASSERT_NE(navigationStack, nullptr);
    ASSERT_EQ(navigationStack->Size(), 0);
}

/**
 * @tc.name: NavigationPatternTestOne_005
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_005, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(pattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto layoutProperty1 = hostNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty1, nullptr);
    layoutProperty1->safeAreaExpandOpts_ = nullptr;
    pattern->navigationMode_ = NavigationMode::SPLIT;
    pattern->navBarVisibilityChange_ = true;
    pattern->OnModifyDone();
    pattern->navigationMode_ = NavigationMode::AUTO;
    pattern->navBarVisibilityChange_ = true;
    pattern->OnModifyDone();
    pattern->navigationMode_ = NavigationMode::SPLIT;
    pattern->navBarVisibilityChange_ = false;
    pattern->OnModifyDone();
    pattern->navigationMode_ = NavigationMode::AUTO;
    pattern->navBarVisibilityChange_ = false;
    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->navBarVisibilityChange_);
}

/**
 * @tc.name: NavigationPatternTestOne_006
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_006, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto style = AceType::MakeRefPtr<SystemBarStyle>();
    navigationPattern->isFullPageNavigation_ = true;
    navigationPattern->navigationStack_ = nullptr;
    navigationPattern->SetSystemBarStyle(style);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_007
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_007, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->IsTopNavDestination(nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_008
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_008, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->currentFoldStatus_ = FoldStatus::UNKNOWN;
    auto ret = navigationPattern->JudgeFoldStateChangeAndUpdateState();
    EXPECT_FALSE(ret);
    navigationPattern->currentFoldStatus_ = FoldStatus::FOLDED;
    ret = navigationPattern->JudgeFoldStateChangeAndUpdateState();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: NavigationPatternTestOne_009
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_009, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->isRightToLeft_ = false;
    navigationPattern->OnLanguageConfigurationUpdate();
    EXPECT_FALSE(navigationPattern->isRightToLeft_);
    navigationPattern->isRightToLeft_ = true;
    navigationPattern->OnLanguageConfigurationUpdate();
    EXPECT_FALSE(navigationPattern->isRightToLeft_);
}

/**
 * @tc.name: NavigationPatternTestOne_010
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_010, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    navigationPattern->proxyList_.emplace_back(proxy);
    navigationPattern->needSyncWithJsStack_ = false;
    navigationPattern->isFinishInteractiveAnimation_ = false;
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_FALSE(navigationPattern->needSyncWithJsStack_);
    navigationPattern->needSyncWithJsStack_ = false;
    navigationPattern->isFinishInteractiveAnimation_ = true;
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_FALSE(navigationPattern->needSyncWithJsStack_);
    navigationPattern->needSyncWithJsStack_ = true;
    navigationPattern->isFinishInteractiveAnimation_ = false;
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_TRUE(navigationPattern->needSyncWithJsStack_);
    navigationPattern->needSyncWithJsStack_ = true;
    navigationPattern->isFinishInteractiveAnimation_ = true;
    navigationPattern->SyncWithJsStackIfNeeded();
    EXPECT_FALSE(navigationPattern->needSyncWithJsStack_);
}

/**
 * @tc.name: NavigationPatternTestOne_011
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_011, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    navigationPattern->proxyList_.emplace_back(proxy);
    string name = "name";
    navigationPattern->NotifyPageShow(name);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_012
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_012, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;
    navigation->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = true;
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, false, false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, nullptr, false, false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);

    navigationPattern->TransitionWithAnimation(nullptr, newTopNavDestination, false, false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);

    preTopNavDestination->parent_ = navigation;
    preTopNavDestination->SetContentNode(AceType::DynamicCast<UINode>(navBarNode));
    navigationPattern->TransitionWithAnimation(preTopNavDestination, nullptr, false, false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_013
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_013, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;
    navigation->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = true;
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->StartDefaultAnimation(nullptr, nullptr, false, false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);

    newTopNavDestination->mode_ = NavDestinationMode::DIALOG;
    navigationPattern->StartDefaultAnimation(nullptr, newTopNavDestination, true, true);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);

    newTopNavDestination->mode_ = NavDestinationMode::STANDARD;
    navigationPattern->isCustomAnimation_ = false;
    navigationPattern->StartDefaultAnimation(preTopNavDestination, newTopNavDestination, true, false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_014
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_014, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto layoutProperty = navigationPattern->GetLayoutProperty<NavigationLayoutProperty>();
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    navigationPattern->OnNavBarStateChange(false);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_015
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_015, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    struct DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;
    auto ret = navigationPattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NavigationPatternTestOne_016
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_016, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationPattern->UpdateContextRect(contentNode, navigation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);

    navigationPattern->navigationMode_ = NavigationMode::AUTO;
    contentNode->isOnAnimation_ = true;
    navigationPattern->UpdateContextRect(contentNode, navigation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_017
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_017, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->isDividerDraggable_ = false;
    navigationPattern->HandleDragEnd();
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_018
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_018, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 110, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 111, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->onTransition_ = CustomNavigationAnimation;
    auto ret = navigationPattern->TriggerCustomAnimation(preTopNavDestination, nullptr, true);
    EXPECT_TRUE(ret);
    ret = navigationPattern->TriggerCustomAnimation(preTopNavDestination, newTopNavDestination, true);
    EXPECT_TRUE(ret);
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    auto pipeline = navigationPattern->GetHost()->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    ret = navigationPattern->TriggerCustomAnimation(nullptr, newTopNavDestination, true);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: NavigationPatternTestOne_019
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_019, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    EXPECT_FALSE(navigationPattern->GetNavigationStackProvided());
    auto stack = navigationPattern->GetNavigationStack();
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
    ASSERT_NE(mockStack, nullptr);
    auto stateChangedCallback = mockStack->GetOnStateChangedCallback();
    ASSERT_NE(stateChangedCallback, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    mockStack->Add("A", frameNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    navigationPattern->needSyncWithJsStack_ = true;
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    ASSERT_EQ(mockStack->Size(), 1);
}

/**
 * @tc.name: NavigationPatternTestOne_020
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_020, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationParent = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 12, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationPatternParent = navigationParent->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPatternParent, nullptr);
    navigationPatternParent->navigationStack_ = nullptr;
    RefPtr<UINode> node = navigationPattern->GetHost();
    node->parent_ = navigationParent;
    navigationPattern->AttachNavigationStackToParent();
    navigationParent->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    EXPECT_TRUE(navigationPatternParent->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_021
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_021, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = nullptr;
    navigationPattern->DetachNavigationStackFromParent();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_022
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_022, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    MockPipelineContext::TearDown();
    navigationPattern->AddToDumpManager();
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_023
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_023, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    MockPipelineContext::TearDown();
    navigationPattern->RemoveFromDumpManager();
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_024
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_024, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 110, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 111, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->onTransition_ = CustomNavigationAnimation;
    navigationPattern->RecoveryToLastStack(preTopNavDestination, newTopNavDestination);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_025
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_025, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto from = AceType::MakeRefPtr<NavDestinationContext>();
    auto to = AceType::MakeRefPtr<NavDestinationContext>();
    NavigationOperation operation = NavigationOperation::PUSH;
    UIObserverHandler::GetInstance().SetHandleNavDestinationSwitchFunc(NavDestinationSwitchHandle);
    navigationPattern->NotifyNavDestinationSwitch(nullptr, to, operation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
    from->pathInfo_ = AceType::MakeRefPtr<NavPathInfo>();
    navigationPattern->NotifyNavDestinationSwitch(from, to, operation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_026
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_026, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 101,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigation->SetContentNode(contentNode);
    navigationPattern->GetTitleBarRenderContext();
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_027
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_027, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 101,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationPattern->IsTopNavDestination(contentNode);
    EXPECT_TRUE(navigationPattern->navigationStack_ == nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_028
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_028, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 110, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 111, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    struct NavigationTransition navigationTransition;
    navigationTransition.isValid = false;
    auto ret = navigationPattern->ExecuteAddAnimation(preTopNavDestination, newTopNavDestination, true,
                                           proxy, navigationTransition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NavigationPatternTestOne_029
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_029, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    struct DirtySwapConfig dirtySwapConfig;
    MockPipelineContext::TearDown();
    auto ret = navigationPattern->OnDirtyLayoutWrapperSwap(nullptr, dirtySwapConfig);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NavigationPatternTestOne_030
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_030, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(nullptr);
    EXPECT_TRUE(navigationPattern->navigationStack_ == nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_031
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_031, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    std::optional<std::pair<std::string, RefPtr<UINode>>> optPair;
    navigationPattern->FireInterceptionEvent(false, optPair);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: NavigationPatternTestOne_032
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_032, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavDestinationGroupNode> destinationNode = nullptr;
    auto ret = navigationPattern->CheckDestinationIsPush(destinationNode);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NavigationPatternTestOne_033
 * @tc.desc: Test Navigation Function, destinationNode is not nullptr and index is -1
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_033, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // create destination
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName("pageOne");
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = "pageOne";
    context->SetNavPathInfo(pathInfo);
    // set destinationNode
    RefPtr<NavDestinationGroupNode> destinationNode = frameNode;
    EXPECT_NE(destinationNode, nullptr);
    int32_t index = -1;
    destinationNode->SetIndex(index);
    auto ret = navigationPattern->CheckDestinationIsPush(destinationNode);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NavigationPatternTestOne_034
 * @tc.desc: Test Navigation Function, destinationNode is not nullptr and index is 33
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_034, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // create destination
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName("pageOne");
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = "pageOne";
    context->SetNavPathInfo(pathInfo);
    // set destinationNode
    RefPtr<NavDestinationGroupNode> destinationNode = frameNode;
    EXPECT_NE(destinationNode, nullptr);
    int32_t index = 33;
    destinationNode->SetIndex(index);
    auto ret = navigationPattern->CheckDestinationIsPush(destinationNode);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: NavigationPatternTestOne_035
 * @tc.desc: Test Navigation Function and destinationNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_035, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavDestinationGroupNode> destinationNode = nullptr;
    auto ret = navigationPattern->CheckParentDestinationIsOnhide(destinationNode);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NavigationPatternTestOne_036
 * @tc.desc: Test Navigation Function and destinationNode is not nullptr destinationNodePattern is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_036, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // create destination
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName("pageTwo");
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = "pageTwo";
    context->SetNavPathInfo(pathInfo);
    // set destinationNode
    RefPtr<NavDestinationGroupNode> destinationNode = frameNode;
    EXPECT_NE(destinationNode, nullptr);
    auto ret = navigationPattern->CheckParentDestinationIsOnhide(destinationNode);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: NavigationPatternTestOne_037
 * @tc.desc: Test Navigation Function and destinationNode is not nullptr isOnShow is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_037, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // create destination
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName("pageTwo");
    pattern->SetIsOnShow(true);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = "pageTwo";
    context->SetNavPathInfo(pathInfo);
    // set destinationNode
    RefPtr<NavDestinationGroupNode> destinationNode = frameNode;
    EXPECT_NE(destinationNode, nullptr);
    auto ret = navigationPattern->CheckParentDestinationIsOnhide(destinationNode);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NavigationPatternTestOne_038
 * @tc.desc: Test Navigation Function and navPathList is empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_038, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    int32_t lastStandardIndex = 1;
    NavPathList navPathList;
    navigationPattern->GenerateUINodeFromRecovery(lastStandardIndex, navPathList);
}

/**
 * @tc.name: NavigationPatternTestOne_039
 * @tc.desc: Test Navigation Function and navPathList is not empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_039, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    int32_t lastStandardIndex = 0;
    NavPathList navPathList;
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    navigationPattern->navigationStack_->SetFromRecovery(lastStandardIndex, false);
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    navPathList.emplace_back(std::make_pair("pageOne", frameNode));
    navigationPattern->GenerateUINodeFromRecovery(lastStandardIndex, navPathList);
}

/**
 * @tc.name: NavigationPatternTestOne_040
 * @tc.desc: Test Navigation Function and type is MAXIMIZE
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_040, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    int32_t width = 1;
    int32_t height = 2;
    WindowSizeChangeReason type = WindowSizeChangeReason::MAXIMIZE;
    navigationPattern->OnWindowSizeChanged(width, height, type);
}

/**
 * @tc.name: NavigationPatternTestOne_041
 * @tc.desc: Test Navigation Function and type is ROTATION
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_041, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    int32_t width = 1;
    int32_t height = 2;
    WindowSizeChangeReason type = WindowSizeChangeReason::ROTATION;
    navigationPattern->OnWindowSizeChanged(width, height, type);
}

/**
 * @tc.name: NavigationPatternTestOne_042
 * @tc.desc: Test Navigation Function and navigationStack_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_043, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->DumpInfo();
}

/**
 * @tc.name: NavigationPatternTestOne_044
 * @tc.desc: Test ApplyTopNavPathSystemBarStyleOrRestore Function and topNavPath is empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_044, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<WindowManager> windowManager = nullptr;
    std::optional<std::pair<std::string, RefPtr<UINode>>> topNavPath;
    auto ret = navigationPattern->ApplyTopNavPathSystemBarStyleOrRestore(windowManager, topNavPath);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NavigationPatternTestOne_045
 * @tc.desc: Test ApplyTopNavPathSystemBarStyleOrRestore Function and topNavPath is not empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_045, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<WindowManager> windowManager = nullptr;
    // set topNavPath->second is nullptr
    std::optional<std::pair<std::string, RefPtr<UINode>>> topNavPath = std::pair<std::string, RefPtr<UINode>>();
    auto ret = navigationPattern->ApplyTopNavPathSystemBarStyleOrRestore(windowManager, topNavPath);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: NavigationPatternTestOne_046
 * @tc.desc: Test ApplyTopNavPathSystemBarStyleOrRestore Function and topNavPath is not empty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNgOne, NavigationPatternTestOne_046, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<WindowManager> windowManager = nullptr;
    // set topNavPath->second is not nullptr
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    std::optional<std::pair<std::string, RefPtr<UINode>>> topNavPath =
        std::pair<std::string, RefPtr<UINode>>("preTopNavDestination", preTopNavDestination);
    auto ret = navigationPattern->ApplyTopNavPathSystemBarStyleOrRestore(windowManager, topNavPath);
    EXPECT_EQ(ret, true);
}
} // namespace OHOS::Ace::NG
