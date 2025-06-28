/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#define private public
#define protected public

#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/navigation/navigation_manager.h"
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
#include "test/mock/base/mock_system_bar_style.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string TEST_TAG = "test";
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;

class MockNavigationPattern : public NavigationPattern {
    DECLARE_ACE_TYPE(MockNavigationPattern, NavigationPattern);
public:
    MockNavigationPattern() : NavigationPattern() {}
    ~MockNavigationPattern() = default;

    void MarkAllNavDestinationDirtyIfNeeded(const RefPtr<FrameNode>& hostNode, bool skipCheck = false) override
    {
        NavigationPattern::MarkAllNavDestinationDirtyIfNeeded(hostNode, skipCheck);
        callTime_++;
    }

    int32_t callTime_ = 0;
};
} // namespace

class NavigationPatternTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
};

void NavigationPatternTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationPatternTestTwoNg::TearDownTestSuite()
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

void NavigationPatternTestTwoNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

void NavigationPatternTestTwoNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: NavigationPatternTestOne_001
 * @tc.desc: Test Navigation HandleDrag
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_001, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_002, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_003, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_004, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_005, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_006, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_007, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_008, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_009, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_010, TestSize.Level1)
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
    EXPECT_FALSE(navigationPattern->needSyncWithJsStack_);
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_011, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_012, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_013, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_014, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_015, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_016, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_017, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_018, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_019, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_020, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_021, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_022, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_023, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_024, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_025, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_026, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_027, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_028, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_029, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_030, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_031, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_032, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_033, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_034, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_035, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_036, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_037, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_038, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_039, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_040, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_041, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_043, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_044, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_045, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_046, TestSize.Level1)
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

/**
 * @tc.name: NavigationPatternTestOne_047
 * @tc.desc: Test Register dump
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation contentNode.
     */
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    navigationNode->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationNode->depth_ = 7;

    /**
     * @tc.steps: step2. create navDestination contentNode.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationNode->index_ = 0;
    navDestinationNode->mode_ = NavDestinationMode::STANDARD;
    navDestinationPattern->name_ = "pageOne";
    navDestinationPattern->isOnShow_ = true;
    navDestinationPattern->navDestinationId_ = 22;

    /**
     * @tc.steps: step3. check dumpString.
     */
    std::string navigationDumpInfo = "|-> Navigation ID: 11, Depth: 7, Mode: \"AUTO(SPLIT)\", NavDestinations:";
    std::string navDestinationDumpInfo =
        "| [0]{ ID: 22, Name: \"pageOne\", Mode: \"STANDARD\", IsOnShow: \"TRUE\", navDestinationType: \"DETAIL\" }";
    std::string navigationDumpString = navigationNode->ToDumpString();
    EXPECT_EQ(navigationDumpString, navigationDumpInfo);
    std::string navDestinationDumpString = navDestinationNode->ToDumpString();
    EXPECT_EQ(navDestinationDumpString, navDestinationDumpInfo);
}

/**
 * @tc.name: NavigationPatternTestOne_048
 * @tc.desc: Test Navigation Function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, NavigationPatternTestOne_048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create groupNode, stack and pattern.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps: step2. configure parameters .
     */
    auto from = AceType::MakeRefPtr<NavDestinationContext>();
    auto to = AceType::MakeRefPtr<NavDestinationContext>();
    NavigationOperation operation = NavigationOperation::PUSH;
    UIObserverHandler::GetInstance().SetHandleNavDestinationSwitchFunc(NavDestinationSwitchHandle);

    /**
     * @tc.steps: step3. Notify NavDestination Switch .
     * @tc.expected: navigationStack_ is not nullptr.
     */
    navigationPattern->NotifyNavDestinationSwitch(nullptr, to, operation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
    from->pathInfo_ = AceType::MakeRefPtr<NavPathInfo>();
    navigationPattern->NotifyNavDestinationSwitch(from, to, operation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
    navigationPattern->NotifyNavDestinationSwitch(from, nullptr, operation);
    EXPECT_TRUE(navigationPattern->navigationStack_ != nullptr);
}

/**
 * @tc.name: UpdatePreNavDesZIndex001
 * @tc.desc: Branch: if (replaceVal != 0 && preTopNavDestination && newTopNavDestination) = false
 *           Condition: replaceVal != 0 = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, UpdatePreNavDesZIndex001, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->mockReplace_->isReplace_ = 0;
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto firsthNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto firsthNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    firsthNavDestinationContext->UpdateZIndex(-1);
    firsthNavDestinationNode->renderContext_ = firsthNavDestinationContext;
    firsthNavDestinationNode->index_ = 0;
    navigationNode->hideNodes_.emplace_back(std::make_pair(firsthNavDestinationNode, true));
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preTopNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    preTopNavDestinationContext->UpdateZIndex(0);
    preTopNavDestinationNode->renderContext_ = preTopNavDestinationContext;
    preTopNavDestinationNode->index_ = 1;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    newTopNavDestinationContext->UpdateZIndex(0);
    newTopNavDestinationNode->renderContext_ = newTopNavDestinationContext;
    newTopNavDestinationNode->index_ = 2;

    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestinationNode, newTopNavDestinationNode, 0);
    EXPECT_EQ(preTopNavDestinationContext->GetZIndex(), 0);
    EXPECT_EQ(firsthNavDestinationContext->GetZIndex(), -1);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePreNavDesZIndex002
 * @tc.desc: Branch: if (replaceVal != 0 && preTopNavDestination && newTopNavDestination) = false
 *           Condition: replaceVal != 0 = true, preTopNavDestination = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, UpdatePreNavDesZIndex002, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->mockReplace_->isReplace_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto firsthNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto firsthNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    firsthNavDestinationContext->UpdateZIndex(-1);
    firsthNavDestinationNode->renderContext_ = firsthNavDestinationContext;
    firsthNavDestinationNode->index_ = 0;
    navigationNode->hideNodes_.emplace_back(std::make_pair(firsthNavDestinationNode, true));
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    newTopNavDestinationContext->UpdateZIndex(0);
    newTopNavDestinationNode->renderContext_ = newTopNavDestinationContext;
    newTopNavDestinationNode->index_ = 2;

    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestinationNode, newTopNavDestinationNode, 0);
    EXPECT_EQ(firsthNavDestinationContext->GetZIndex(), -1);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePreNavDesZIndex003
 * @tc.desc: Branch: if (replaceVal != 0 && preTopNavDestination && newTopNavDestination) = false
 *           Condition: replaceVal != 0 = true, preTopNavDestination = true, newTopNavDestination = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, UpdatePreNavDesZIndex003, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->mockReplace_->isReplace_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    auto firsthNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto firsthNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    firsthNavDestinationContext->UpdateZIndex(-1);
    firsthNavDestinationNode->renderContext_ = firsthNavDestinationContext;
    firsthNavDestinationNode->index_ = 0;
    navigationNode->hideNodes_.emplace_back(std::make_pair(firsthNavDestinationNode, true));
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preTopNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    preTopNavDestinationContext->UpdateZIndex(0);
    preTopNavDestinationNode->renderContext_ = preTopNavDestinationContext;
    preTopNavDestinationNode->index_ = 4;
    auto newTopNavDestinationNode = nullptr;

    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestinationNode, newTopNavDestinationNode, 0);
    EXPECT_EQ(preTopNavDestinationContext->GetZIndex(), 0);
    EXPECT_EQ(firsthNavDestinationContext->GetZIndex(), -1);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdatePreNavDesZIndex004
 * @tc.desc: Branch: if (replaceVal != 0 && preTopNavDestination && newTopNavDestination) = true
 *           Condition: replaceVal != 0 = true, preTopNavDestination = true, newTopNavDestination = true
 *           Branch: if (!iter->second) = true
 *           Branch: if (!iter->second) = false, if (!navDestination) = true
 *           Branch: if (!iter->second) = false, if (!navDestination) = false, if (!navDestinationContext) = true
 *           Branch: if (!iter->second) = false, if (!navDestination) = false, if (!navDestinationContext) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, UpdatePreNavDesZIndex004, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationStack->mockReplace_->isReplace_ = 1;
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationContentNode = FrameNode::CreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    navigationNode->contentNode_ = navigationContentNode;
    // Make !iter->second true
    navigationNode->hideNodes_.emplace_back(std::make_pair(nullptr, false));
    // Make !iter->second false and !navDestination true
    navigationNode->hideNodes_.emplace_back(std::make_pair(nullptr, true));
    // Make !iter->second false and !navDestination false and !navDestinationContext true
    auto thirdNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    thirdNavDestinationNode->renderContext_ = nullptr;
    thirdNavDestinationNode->index_ = 2;
    navigationNode->hideNodes_.emplace_back(std::make_pair(thirdNavDestinationNode, true));
    // Make !iter->second false and !navDestination false and !navDestinationContext false
    auto fourthNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto fourthNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    fourthNavDestinationContext->UpdateZIndex(-1);
    fourthNavDestinationNode->renderContext_ = fourthNavDestinationContext;
    fourthNavDestinationNode->index_ = 3;
    navigationNode->hideNodes_.emplace_back(std::make_pair(fourthNavDestinationNode, true));
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preTopNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    preTopNavDestinationContext->UpdateZIndex(0);
    preTopNavDestinationNode->renderContext_ = preTopNavDestinationContext;
    preTopNavDestinationNode->index_ = 4;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationContext = AceType::MakeRefPtr<MockRenderContext>();
    newTopNavDestinationContext->UpdateZIndex(0);
    newTopNavDestinationNode->renderContext_ = newTopNavDestinationContext;
    newTopNavDestinationNode->index_ = 5;

    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestinationNode, newTopNavDestinationNode, 0);
    EXPECT_EQ(preTopNavDestinationContext->GetZIndex(), -1);
    EXPECT_EQ(fourthNavDestinationContext->GetZIndex(), -2);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: DealTransitionVisibility001
 * @tc.desc: Branch: if (!renderContext->HasDisappearTransition()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, DealTransitionVisibility001, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    navDestinationNode->renderContext_ = renderContext;
    renderContext->hasDisappearTransition_ = false;
    renderContext->transitionOutCallback_ = nullptr;
    navDestinationNode->transitionType_ = PageTransitionType::EXIT_PUSH;

    navigationPattern->DealTransitionVisibility(navDestinationNode, true, false);
    EXPECT_EQ(renderContext->transitionOutCallback_, nullptr);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: DealTransitionVisibility002
 * @tc.desc: Branch: if (!renderContext->HasDisappearTransition()) = false
 *           Branch: if (isNavBar) = false
 *           Branch: if (GetTransitionType() != EXIT_PUSH) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, DealTransitionVisibility002, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    navDestinationNode->renderContext_ = renderContext;
    navDestinationNode->transitionType_ = PageTransitionType::EXIT_PUSH;
    renderContext->hasDisappearTransition_ = true;
    renderContext->transitionOutCallback_ = nullptr;
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->SetJsActive(false);
    navDestinationNode->children_.emplace_back(customNode);

    navigationPattern->DealTransitionVisibility(navDestinationNode, true, false);
    ASSERT_NE(renderContext->transitionOutCallback_, nullptr);
    renderContext->transitionOutCallback_();
    EXPECT_TRUE(customNode->GetJsActive());
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: DealTransitionVisibility003
 * @tc.desc: Branch: if (!renderContext->HasDisappearTransition()) = false
 *           Branch: if (isNavBar) = false
 *           Branch: if (GetTransitionType() != EXIT_PUSH) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, DealTransitionVisibility003, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    navDestinationNode->renderContext_ = renderContext;
    navDestinationNode->transitionType_ = PageTransitionType::ENTER;
    renderContext->hasDisappearTransition_ = true;
    renderContext->transitionOutCallback_ = nullptr;
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->SetJsActive(false);
    navDestinationNode->children_.emplace_back(customNode);

    navigationPattern->DealTransitionVisibility(navDestinationNode, true, false);
    ASSERT_NE(renderContext->transitionOutCallback_, nullptr);
    renderContext->transitionOutCallback_();
    EXPECT_FALSE(customNode->GetJsActive());
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: DealTransitionVisibility004
 * @tc.desc: Branch: if (!renderContext->HasDisappearTransition()) = false
 *           Branch: if (isNavBar) = true
 *           Branch: if (GetTransitionType() != EXIT_PUSH) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, DealTransitionVisibility004, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    navBarNode->renderContext_ = renderContext;
    navBarNode->transitionType_ = PageTransitionType::EXIT_PUSH;
    renderContext->hasDisappearTransition_ = true;
    renderContext->transitionOutCallback_ = nullptr;
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->SetJsActive(false);
    navBarNode->children_.emplace_back(customNode);

    navigationPattern->DealTransitionVisibility(navBarNode, true, true);
    ASSERT_NE(renderContext->transitionOutCallback_, nullptr);
    renderContext->transitionOutCallback_();
    EXPECT_TRUE(customNode->GetJsActive());
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: DealTransitionVisibility005
 * @tc.desc: Branch: if (!renderContext->HasDisappearTransition()) = false
 *           Branch: if (isNavBar) = true
 *           Branch: if (GetTransitionType() != EXIT_PUSH) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, DealTransitionVisibility005, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    navBarNode->renderContext_ = renderContext;
    navBarNode->transitionType_ = PageTransitionType::ENTER;
    renderContext->hasDisappearTransition_ = true;
    renderContext->transitionOutCallback_ = nullptr;
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->SetJsActive(false);
    navBarNode->children_.emplace_back(customNode);

    navigationPattern->DealTransitionVisibility(navBarNode, true, true);
    ASSERT_NE(renderContext->transitionOutCallback_, nullptr);
    renderContext->transitionOutCallback_();
    EXPECT_FALSE(customNode->GetJsActive());
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: AddToDumpManager001
 * @tc.desc: Branch: if (!node || !context) = true
 *           Condition: !node = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, AddToDumpManager001, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->frameNode_ = nullptr;
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationMgr = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationMgr, nullptr);
    navigationMgr->dumpMap_.clear();

    navigationPattern->AddToDumpManager();
    EXPECT_EQ(navigationMgr->dumpMap_.size(), 0);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: AddToDumpManager002
 * @tc.desc: Branch: if (!node || !context) = true
 *           Condition: !node = false, !context = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, AddToDumpManager002, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationMgr = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationMgr, nullptr);
    navigationMgr->dumpMap_.clear();
    auto pipeline = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;

    navigationPattern->AddToDumpManager();
    EXPECT_EQ(navigationMgr->dumpMap_.size(), 0);
    MockPipelineContext::pipeline_ = pipeline;
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: AddToDumpManager003
 * @tc.desc: Branch: if (!node || !context) = false
 *           Condition: !node = false, !context = false
 *           Branch: if (!mgr) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, AddToDumpManager003, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationMgr = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationMgr, nullptr);
    navigationMgr->dumpMap_.clear();
    pipelineContext->navigationMgr_ = nullptr;

    navigationPattern->AddToDumpManager();
    EXPECT_EQ(navigationMgr->dumpMap_.size(), 0);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: AddToDumpManager004
 * @tc.desc: Branch: if (!mgr) = false
 *           Branch: if (!pattern) = false
 *           Branch: if (!stack) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, AddToDumpManager004, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigationNodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationMgr = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationMgr, nullptr);
    navigationMgr->dumpMap_.clear();
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->children_.emplace_back(navigationNode);

    navigationPattern->AddToDumpManager();
    auto dump = navigationMgr->dumpMap_.find(
        NavigationManager::DumpMapKey(navigationNode->GetId(), navigationNode->GetDepth()));
    ASSERT_NE(dump, navigationMgr->dumpMap_.end());
    ASSERT_NE(dump->second, nullptr);
    dump->second(0);
    EXPECT_NE(navigationPattern, nullptr);
    EXPECT_NE(navigationPattern->GetNavigationStack(), nullptr);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: AddToDumpManager005
 * @tc.desc: Branch: if (!pattern) = false
 *           Branch: if (!stack) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, AddToDumpManager005, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        navigationNodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto navigationMgr = pipelineContext->GetNavigationManager();
    ASSERT_NE(navigationMgr, nullptr);
    navigationMgr->dumpMap_.clear();
    auto customNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), V2::TEXT_ETS_TAG);
    customNode->children_.emplace_back(navigationNode);

    navigationPattern->AddToDumpManager();
    auto dump = navigationMgr->dumpMap_.find(
        NavigationManager::DumpMapKey(navigationNode->GetId(), navigationNode->GetDepth()));
    ASSERT_NE(dump, navigationMgr->dumpMap_.end());
    ASSERT_NE(dump->second, nullptr);
    dump->second(0);
    EXPECT_EQ(navigationPattern->GetNavigationStack(), nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckContentNeedMeasure001
 * @tc.desc: Branch: if (!IsAutoHeight) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, CheckContentNeedMeasure001, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->calcLayoutConstraint_ = nullptr;
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 201,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationNode->SetContentNode(contentNode);
    contentNode->isFreeze_ = true;
    contentNode->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    navigationPattern->CheckContentNeedMeasure(navigationNode);
    EXPECT_EQ(contentNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckContentNeedMeasure002
 * @tc.desc: Branch: if (!IsAutoHeight) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, CheckContentNeedMeasure002, TestSize.Level1)
{
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    ASSERT_NE(navigationLayoutProperty->calcLayoutConstraint_, nullptr);
    navigationLayoutProperty->calcLayoutConstraint_->selfIdealSize =
        CalcSize(NG::CalcLength(100.0f), NG::CalcLength("auto"));
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 201,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationNode->SetContentNode(contentNode);
    contentNode->isFreeze_ = true;
    contentNode->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    navigationPattern->CheckContentNeedMeasure(navigationNode);
    EXPECT_EQ(contentNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    NavigationPatternTestTwoNg::TearDownTestSuite();
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test branch if (preNavBarPosition_.has_value() && preNavBarPosition_.value() != curNavBarPosition)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestTwoNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MockNavigationPattern & NavigationGroupNode.
     */
    NavigationPatternTestTwoNg::SetUpTestSuite();
    auto mockPattern = AceType::MakeRefPtr<MockNavigationPattern>();
    ASSERT_NE(mockPattern, nullptr);
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, [&mockPattern]() { return mockPattern; });
    ASSERT_NE(navigation, nullptr);
    auto property = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationStack, nullptr);
    auto pattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationStack(std::move(navigationStack));
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigation->navBarNode_ = navBarNode;

    /**
     * @tc.steps: step2. branch if (preNavBarPosition_.has_value() && preNavBarPosition_.value() != curNavBarPosition)
     *                   Condition: preNavBarPosition_.has_value() => false
     * @tc.expected: MarkAllNavDestinationDirtyIfNeeded won't be called.
     */
    ASSERT_FALSE(pattern->preNavBarPosition_.has_value());
    property->UpdateNavBarPosition(NavBarPosition::START);
    pattern->OnModifyDone();
    ASSERT_EQ(mockPattern->callTime_, 0);
    ASSERT_EQ(pattern->preNavBarPosition_, std::optional<NavBarPosition>(NavBarPosition::START));

    /**
     * @tc.steps: step3. branch if (preNavBarPosition_.has_value() && preNavBarPosition_.value() != curNavBarPosition)
     *                   Condition: preNavBarPosition_.has_value() => true,
     *                              preNavBarPosition_.value() != curNavBarPosition => true
     * @tc.expected: MarkAllNavDestinationDirtyIfNeeded will be called.
     */
    property->UpdateNavBarPosition(NavBarPosition::END);
    pattern->OnModifyDone();
    ASSERT_EQ(mockPattern->callTime_, 1);
    ASSERT_EQ(pattern->preNavBarPosition_, std::optional<NavBarPosition>(NavBarPosition::END));

    /**
     * @tc.steps: step3. branch if (preNavBarPosition_.has_value() && preNavBarPosition_.value() != curNavBarPosition)
     *                   Condition: preNavBarPosition_.has_value() => true,
     *                              preNavBarPosition_.value() != curNavBarPosition => false
     * @tc.expected: MarkAllNavDestinationDirtyIfNeeded won't be called.
     */
    property->UpdateNavBarPosition(NavBarPosition::END);
    pattern->OnModifyDone();
    ASSERT_EQ(mockPattern->callTime_, 1);
    ASSERT_EQ(pattern->preNavBarPosition_, std::optional<NavBarPosition>(NavBarPosition::END));
    NavigationPatternTestTwoNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG