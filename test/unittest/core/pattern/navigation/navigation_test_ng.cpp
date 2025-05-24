/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "test/mock/base/mock_task_executor.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string NAVIGATION_TITLE = "NavigationTestNg";
const std::string TEST_TAG = "test";
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
} // namespace

class NavigationTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string name);
};

void NavigationTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
    auto context = MockPipelineContext::GetCurrent();
    if (context) {
        context->stageManager_ = nullptr;
    }
}

void NavigationTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

void NavigationTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

RefPtr<NavDestinationGroupNode> NavigationTestNg::CreateDestination(const std::string name)
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName(name);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = name;
    context->SetNavPathInfo(pathInfo);
    return frameNode;
}

struct TestProperty {
    std::optional<bool> isOn = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
};

/**
 * @tc.name: NavigationModelTest004
 * @tc.desc: Test NavigationModel SetTitle & SetSubTitle.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelTest004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationView", true);
    navigationModel.SetSubtitle("subtitle");
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
}

/**
 * @tc.name: NavigationModelTest003
 * @tc.desc: Test NavigationModel SetHideToolBar false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelTest003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navigationModel.SetHideToolBar(false);
    EXPECT_EQ(navBarLayoutProperty->GetHideToolBar().value_or(false), false);
}

/**
 * @tc.name: NavigationModelNG007
 * @tc.desc: Test NavigationPattern::CheckTopNavPathChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto narBarNode = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(narBarNode, nullptr);
    /**
     * @tc.steps: step2. construct correct arguments of navigationPattern->CheckTopNavPathChange then call it.
     * @tc.expected: check whether the properties is correct.
     */
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 102, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    narBarNode->titleBarNode_ = titleBarNode;
    preTopNavDestination->titleBarNode_ = titleBarNode;
    newTopNavDestination->titleBarNode_ = titleBarNode;
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->TransitionWithAnimation(nullptr, nullptr, false);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, nullptr, false);
    ASSERT_EQ(preTopNavDestination->transitionType_, PageTransitionType::EXIT_POP);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, false);
    ASSERT_EQ(newTopNavDestination->transitionType_, PageTransitionType::ENTER_PUSH);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, true);
    ASSERT_EQ(preTopNavDestination->transitionType_, PageTransitionType::EXIT_POP);
}

/**
 * @tc.name: NavigationModelNG008
 * @tc.desc: Test NavigationPattern::OnNavBarStateChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    ASSERT_NE(AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode()), nullptr);

    /**
     * @tc.steps: step2. construct correct condition of navigationPattern->OnNavBarStateChange then call it.
     * @tc.expected: check whether the properties is correct.
     */
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = false;
    navigationPattern->OnNavBarStateChange(true);
    ASSERT_FALSE(navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_.value());

    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = false;
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationStack_->Add("preTopNavDestination", preTopNavDestination);
    navigationPattern->OnNavBarStateChange(true);
    ASSERT_FALSE(navigationPattern->navigationStack_->Empty());

    navigationPattern->navBarVisibilityChange_ = false;
    navigationPattern->OnNavBarStateChange(false);

    navigationPattern->navBarVisibilityChange_ = true;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationPattern->OnNavBarStateChange(false);

    navigationPattern->navBarVisibilityChange_ = true;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->OnNavBarStateChange(false);
    ASSERT_FALSE(navigationPattern->navBarVisibilityChange_);

    navigationPattern->navBarVisibilityChange_ = true;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = true;
    navigationPattern->OnNavBarStateChange(false);
    ASSERT_FALSE(navigationPattern->navBarVisibilityChange_);
}

/**
 * @tc.name: NavigationModelNG0011
 * @tc.desc: Test NavigationModelNG::SetCustomToolBar && SetToolBarItems
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    auto customNode = FrameNode::CreateFrameNode("text", 113, AceType::MakeRefPtr<TextPattern>());
    model.SetCustomToolBar(customNode);
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);

    navBarNode->propPrevToolBarIsCustom_ = true;
    model.SetCustomToolBar(customNode);
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);

    customNode =
        FrameNode::CreateFrameNode("text", navBarNode->GetToolBarNode()->GetId(), AceType::MakeRefPtr<TextPattern>());
    model.SetCustomToolBar(customNode);
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::NONE);

    std::vector<NG::BarItem> toolBarItems;
    model.SetToolBarItems(std::move(toolBarItems));
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);

    navBarNode->preToolBarNode_ = nullptr;
    model.SetToolBarItems(std::move(toolBarItems));
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: NavigationModelNG0012
 * @tc.desc: Test NavigationModelNG::SetToolbarConfiguration
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    navBarNode->propPrevToolBarIsCustom_ = true;
    std::vector<NG::BarItem> toolBarItems;
    model.SetToolbarConfiguration(std::move(toolBarItems));
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: NavigationModelNG0013
 * @tc.desc: Test NavigationContentLayoutAlgorithm::Measure
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 120, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto layoutWrapper = navigation->CreateLayoutWrapper();

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 121, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationWrapper1 = navDestination->CreateLayoutWrapper();

    ASSERT_EQ(layoutWrapper->GetTotalChildCount(), 0);
    ASSERT_NE(layoutWrapper->GetLayoutProperty(), nullptr);
    ASSERT_NE(navDestinationWrapper1->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(navDestinationWrapper1->GetLayoutAlgorithm()->GetLayoutAlgorithm(), nullptr);

    auto temp1 = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    navDestinationWrapper1->layoutAlgorithm_->layoutAlgorithm_ = temp1;

    layoutWrapper->AppendChild(navDestinationWrapper1);

    NavigationContentLayoutAlgorithm algorithm;
    algorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto navDestination2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 121, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationWrapper2 = navDestination2->CreateLayoutWrapper();
    auto temp2 = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    temp2->isShown_ = true;
    navDestinationWrapper2->layoutAlgorithm_->layoutAlgorithm_ = temp2;
    layoutWrapper->AppendChild(navDestinationWrapper2);
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(temp2->isShown_);
    temp1->isShown_ = true;
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(temp1->isShown_);
}

/**
 * @tc.name: NavigationModelNG0015
 * @tc.desc: Test NavigationModelNG::UpdateNavDestinationNodeWithoutMarkDirty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    /**
     * @tc.steps: step2. create navDestination.
     */
    auto navDestination1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 124, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 125, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 126, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination4 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 127, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination5 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 129, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination6 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 130, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination7 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 131, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto child8 = FrameNode::CreateFrameNode("NavDestination", 132, AceType::MakeRefPtr<ButtonPattern>());

    auto temp = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 133, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    /**
     * @tc.steps: step3. add element to navigationPattern->navigationStack_.
     */
    navigationPattern->navigationStack_->Add("navDestination1", navDestination1);
    navigationPattern->navigationStack_->Add("navDestination2", navDestination2);
    navigationPattern->navigationStack_->Add("navDestination3", navDestination3);

    auto pattern5 = navDestination5->GetPattern<NavDestinationPattern>();
    pattern5->customNode_ = AceType::RawPtr(navDestination5);

    pattern5->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 234, AceType::MakeRefPtr<ButtonPattern>()); });
    navDestination5->contentNode_ = FrameNode::CreateFrameNode("temp", 235, AceType::MakeRefPtr<ButtonPattern>());

    auto pattern6 = navDestination6->GetPattern<NavDestinationPattern>();
    pattern6->customNode_ = AceType::RawPtr(navDestination6);

    auto pattern7 = navDestination7->GetPattern<NavDestinationPattern>();
    pattern7->customNode_ = AceType::RawPtr(navDestination7);

    ASSERT_NE(navDestination7->GetPattern<NavDestinationPattern>()->GetCustomNode(), nullptr);
    /**
     * @tc.steps: step4. add element to navigationContentNode->children_.
     */
    navigationContentNode->children_.push_back(navDestination1);
    navigationContentNode->children_.push_back(navDestination4);
    navigationContentNode->children_.push_back(navDestination2);
    navigationContentNode->children_.push_back(navDestination5);
    navigationContentNode->children_.push_back(navDestination6);
    navigationContentNode->children_.push_back(navDestination7);
    navigationContentNode->children_.push_back(child8);

    navigation->UpdateNavDestinationNodeWithoutMarkDirty(temp);
}

/**
 * @tc.name: NavigationModelNG0016
 * @tc.desc: Test NavigationModelNG::GetNavDestinationNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;

    auto result = navigation->GetNavDestinationNode(navigationContentNode);
    ASSERT_EQ(result, nullptr);
}

/**
 * @tc.name: NavigationModelNG0017
 * @tc.desc: Test NavigationModelNG::CheckCanHandleBack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;

    auto child = FrameNode::CreateFrameNode("navigationContent", 345, AceType::MakeRefPtr<ButtonPattern>());
    navigationContentNode->children_.push_back(child);

    bool isEntry = false;
    navigation->CheckCanHandleBack(isEntry);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::AUTO);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigation->CheckCanHandleBack(isEntry);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::SPLIT);
    auto child2 = FrameNode::CreateFrameNode("navigationContent", 346, AceType::MakeRefPtr<ButtonPattern>());
    navigationContentNode->children_.push_back(child2);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigation->CheckCanHandleBack(isEntry);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationModelNG0018
 * @tc.desc: Test NavigationModelNG::UpdateNavDestinationNodeWithoutMarkDirty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    /**
     * @tc.steps: step2. create navDestination.
     */
    auto navDestination1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 154, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 155, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 156, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination4 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 157, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination5 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 159, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination6 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 160, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination7 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 161, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto child8 = FrameNode::CreateFrameNode("NavDestination", 132, AceType::MakeRefPtr<ButtonPattern>());

    auto temp = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 163, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto pattern5 = navDestination5->GetPattern<NavDestinationPattern>();
    pattern5->customNode_ = AceType::RawPtr(navDestination5);

    pattern5->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 236, AceType::MakeRefPtr<ButtonPattern>()); });
    navDestination5->contentNode_ = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());

    auto pattern6 = navDestination6->GetPattern<NavDestinationPattern>();
    pattern6->customNode_ = AceType::RawPtr(navDestination6);

    auto pattern7 = navDestination7->GetPattern<NavDestinationPattern>();
    pattern7->customNode_ = AceType::RawPtr(temp);

    ASSERT_NE(navDestination7->GetPattern<NavDestinationPattern>()->GetCustomNode(), nullptr);
    /**
     * @tc.steps: step4. add element to navigationContentNode->children_.
     */
    navigationContentNode->children_.push_back(navDestination1);
    navigationContentNode->children_.push_back(navDestination4);
    navigationContentNode->children_.push_back(navDestination2);
    navigationContentNode->children_.push_back(navDestination5);
    navigationContentNode->children_.push_back(navDestination6);
    navigationContentNode->children_.push_back(navDestination7);
    navigationContentNode->children_.push_back(child8);

    navigation->UpdateNavDestinationNodeWithoutMarkDirty(temp);
}

/**
 * @tc.name: NavigationModelNG0019
 * @tc.desc: Test NavigationLayoutAlgorithm::IsAutoHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);

    auto property = AceType::MakeRefPtr<LayoutProperty>();
    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = CalcSize(std::nullopt, len);
    property->calcLayoutConstraint_ = std::move(calcLayoutConstraint);

    auto& test = property->GetCalcLayoutConstraint();
    ASSERT_NE(test, nullptr);
    ASSERT_TRUE(test->selfIdealSize.has_value());
    ASSERT_TRUE(test->selfIdealSize->Height().has_value());
    ASSERT_NE(test->selfIdealSize->Height().value().ToString().find("auto"), std::string::npos);

    NavigationLayoutAlgorithm algorithm;
    auto result = algorithm.IsAutoHeight(property);
    ASSERT_TRUE(result);

    len = CalcLength("");
    property->calcLayoutConstraint_->selfIdealSize = CalcSize(std::nullopt, len);
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);

    property->calcLayoutConstraint_->selfIdealSize = CalcSize(std::nullopt, std::nullopt);
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);

    property->calcLayoutConstraint_->selfIdealSize = std::nullopt;
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);

    property->calcLayoutConstraint_ = nullptr;
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);
}

/**
 * @tc.name: NavigationModelNG0020
 * @tc.desc: Test NavigationLayoutAlgorithm::SizeCalculationSplit
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto property = AceType::MakeRefPtr<NavigationLayoutProperty>();
    property->propHideNavBar_ = true;
    property->layoutConstraint_ = LayoutConstraintF();

    algorithm->SizeCalculationSplit(navigation, property, SizeF());
    property->propHideNavBar_ = false;
    algorithm->realNavBarWidth_ = -1.0f;
    algorithm->SizeCalculationSplit(navigation, property, SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: NavigationModelNG0021
 * @tc.desc: Test NavigationLayoutAlgorithm::CheckSizeInSplit
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto property = AceType::MakeRefPtr<NavigationLayoutProperty>();
    property->propHideNavBar_ = true;
    property->layoutConstraint_ = LayoutConstraintF();

    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->CheckSizeInSplit(0, 0, 0, 0);
    ASSERT_EQ(algorithm->realNavBarWidth_, 0.0f);

    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    algorithm->realNavBarWidth_ = 60;
    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    ASSERT_FALSE(algorithm->userSetNavBarRangeFlag_);

    algorithm->userSetMinContentFlag_ = false;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->userSetNavBarWidthFlag_ = true;
    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    ASSERT_FALSE(algorithm->userSetMinContentFlag_);

    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->realNavBarWidth_ = 0;
    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    ASSERT_FALSE(algorithm->userSetNavBarWidthFlag_);

    algorithm->realNavBarWidth_ = 60;
    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->CheckSizeInSplit(100, 0, 0, 50);
    ASSERT_FALSE(algorithm->userSetNavBarWidthFlag_);

    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = true;
    algorithm->realNavBarWidth_ = 40;
    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->CheckSizeInSplit(100, 0, 60, 50);
    ASSERT_TRUE(algorithm->userSetMinContentFlag_);
}

/**
 * @tc.name: NavigationModelNG0022
 * @tc.desc: Test NavigationLayoutAlgorithm::MeasureContentChild
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode("content", 454, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = contentNode;
    navigation->children_.push_back(contentNode);

    auto layoutWrapper = navigation->CreateLayoutWrapper();
    auto navigationLayoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();

    layoutWrapper->layoutProperty_ = navigationLayoutProperty;
    auto contentWrapper = contentNode->CreateLayoutWrapper();
    layoutWrapper->AppendChild(contentWrapper);
    contentNode->children_.push_back(FrameNode::CreateFrameNode("content", 456, AceType::MakeRefPtr<ButtonPattern>()));

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->MeasureContentChild(AceType::RawPtr(layoutWrapper), navigation, navigationLayoutProperty, SizeF());
    ASSERT_FALSE(contentNode->children_.empty());

    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength(200);
    calcLayoutConstraint->selfIdealSize = CalcSize(std::nullopt, len);
    navigationLayoutProperty->calcLayoutConstraint_ = std::move(calcLayoutConstraint);
    algorithm->MeasureContentChild(AceType::RawPtr(layoutWrapper), navigation, navigationLayoutProperty, SizeF());
    algorithm->MeasureNavBar(AceType::RawPtr(layoutWrapper), navigation, navigationLayoutProperty, SizeF());
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(20, 20);
    navigationLayoutProperty->layoutConstraint_ = LayoutConstraintF();
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(contentNode->children_.empty());
}

/**
 * @tc.name: NavigationModelNG0023
 * @tc.desc: Test NavigationLayoutAlgorithm::SetNavigationHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode("content", 454, AceType::MakeRefPtr<ButtonPattern>());

    auto layoutWrapper = navigation->CreateLayoutWrapper();

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    SizeF size;
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);

    navigationPattern->navigationStack_->Add("11", contentNode);
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::AUTO);

    navigationPattern->navigationMode_ = NavigationMode::STACK;
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::STACK);

    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationModelNG0025
 * @tc.desc: Test NavBarPattern::OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode("content", 454, AceType::MakeRefPtr<ButtonPattern>());

    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBar", 300, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBar, nullptr);
    auto navBarPattern = navBar->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RESIZE);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 301, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_EQ(titleBarNode->menu_, nullptr);
    navBar->titleBarNode_ = titleBarNode;
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RESIZE);
    auto menu = FrameNode::CreateFrameNode("menu", 302, AceType::MakeRefPtr<ButtonPattern>());
    auto barItem = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 303, []() { return AceType::MakeRefPtr<Pattern>(); });
    menu->children_.push_back(barItem);
    titleBarNode->menu_ = menu;
    barItem->isMoreItemNode_ = true;
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RECOVER);
    ASSERT_TRUE(barItem->isMoreItemNode_);
    barItem->isMoreItemNode_ = false;
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RECOVER);
    ASSERT_FALSE(barItem->isMoreItemNode_);
}

HWTEST_F(NavigationTestNg, NavigationStackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    navigationNode->AttachToMainTree(false, AceType::RawPtr(context));

    /**
     * @tc.steps: step2.add page A
     */
    auto* viewStack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = viewStack->ClaimNodeId();
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto stack = pattern->GetNavigationStack();
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto targetNode = navigationPattern->GetNavigationStack()->Get();
    ASSERT_EQ(frameNode, targetNode);

    /**
     * @tc.steps: step3. replace pageA
     */
        nodeId = viewStack->ClaimNodeId();
    auto replaceNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    stack->Pop();
    stack->Add("C", replaceNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(replaceNode, stack->Get());
}

HWTEST_F(NavigationTestNg, NavigationStackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavigationStack(AceType::MakeRefPtr<MockNavigationStack>());
    /**
     * @tc.steps: step2.add page A
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<NavDestinationPattern>());
    auto stack = pattern->GetNavigationStack();
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 1);

    /**
     * @tc.steps: step3. replace pageA
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245,
        AceType::MakeRefPtr<NavDestinationPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 1);

    /**
     * @tc.steps: step4. push pageC
     */
    stack->Add("C", frameNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 2);
}

HWTEST_F(NavigationTestNg, NavigationReplaceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.add page A to stack
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.replace page A in stack
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    stack->UpdateReplaceValue(1);
    ASSERT_EQ(stack->GetReplaceValue(), 1);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.push A
     */
    stack->Add("C", frameNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);
}

HWTEST_F(NavigationTestNg, NavigationReplaceTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.add page A to stack
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Add("A", frameNode);
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.replace page A in stack
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    stack->UpdateReplaceValue(1);
    ASSERT_EQ(stack->GetReplaceValue(), 1);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step3.pop page B
     */
    stack->Remove();
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);
}

HWTEST_F(NavigationTestNg, NavigationReplaceTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.add page A to stack
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Add("A", frameNode);
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.replace page A in stack
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    stack->UpdateReplaceValue(1);
    ASSERT_EQ(stack->GetReplaceValue(), 1);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step3.pop page B
     */
    stack->Clear();
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);
}

/**
 * @tc.name: NavDestinationTest001
 * @tc.desc: Test Dialog page visibility
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavDestinationDialogTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.push page A to navDestination
     * @tc.expected: navbar is visible,page is visible
     */
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("A", navDestination);
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    auto destinationProperty = AceType::DynamicCast<NavDestinationLayoutProperty>(navDestination->GetLayoutProperty());
    EXPECT_TRUE(destinationProperty != nullptr);
    destinationProperty->UpdateHideTitleBar(true);
    EXPECT_EQ(destinationProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step2. push navdestination page B
     * @tc.expected: page A is visible, page B is visible
     */
    auto navDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    auto navDestinationBPattern = navDestinationB->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationBPattern, nullptr);
    navDestinationBPattern->SetNavigationNode(navigationNode);
    navigationStack->Add("B", navDestinationB);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto layoutPropertyB = AceType::DynamicCast<NavDestinationLayoutProperty>(navDestinationB->GetLayoutProperty());
    EXPECT_NE(layoutPropertyB, nullptr);
    layoutPropertyB->UpdateHideTitleBar(true);
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    EXPECT_EQ(layoutPropertyB->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(destinationProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step3. push standard page C
     * @tc.expected: page A is invisible, pageB is invisible, navBar is invisible, pageC is visible
     */
    auto navDestinationC = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() {
            return AceType::MakeRefPtr<NavDestinationPattern>();
        });
    auto navDestinationCPattern = navDestinationC->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationBPattern, nullptr);
    navDestinationCPattern->SetNavigationNode(navigationNode);
    auto layoutPropertyC = AceType::DynamicCast<NavDestinationLayoutProperty>(navDestinationC->GetLayoutProperty());
    EXPECT_NE(layoutPropertyC, nullptr);
    layoutPropertyC->UpdateHideTitleBar(true);
    navigationStack->Add("C", navDestinationC);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    navigationNode->hideNodes_.emplace_back(std::make_pair(navDestination, false));
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    EXPECT_EQ(layoutPropertyB->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(destinationProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(layoutPropertyC->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: NavDestinationDialogTest003
 * @tc.desc: Test window lifecycle event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavDestinationDialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation stack
    */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps: step2. push standard page C
    */
    auto navDestinationC = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("C", navDestinationC);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(navigationNode, geometryNode, navigationNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    navigationPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    auto layoutPropertyC = navDestinationC->GetLayoutProperty();
    EXPECT_NE(layoutPropertyC, nullptr);
    EXPECT_EQ(layoutPropertyC->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: NavigationSetStackTest001
 * @tc.desc: Test setting of NavigationStack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationSetStackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();

    int numOfCreatorCall = 0;
    int numOfUpdaterCall = 0;
    RefPtr<MockNavigationStack> stack;
    auto stackCreator = [&numOfCreatorCall, &stack]() -> RefPtr<MockNavigationStack> {
        numOfCreatorCall++;
        stack = AceType::MakeRefPtr<MockNavigationStack>();
        return stack;
    };
    auto stackUpdater = [&numOfUpdaterCall, &navigationModel](RefPtr<NG::NavigationStack> stack) {
        numOfUpdaterCall++;
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };

    /**
     * @tc.steps: step1. set stack's creator and updater
     * @tc.expected: check number of function calls
     */
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(stack->GetOnStateChangedCallback(), nullptr);
    EXPECT_EQ(numOfCreatorCall, 1);
    EXPECT_EQ(numOfUpdaterCall, 3);
}

/**
 * @tc.name: NavigationNewStackTest001
 * @tc.desc: Test stack operation of Navigation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationNewStackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
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

    /**
     * @tc.steps: step2. get onStateChangedCallback
     * @tc.expected: check if callback has been setted.
     */
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

    /**
     * @tc.steps: step2.add page A
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    mockStack->Add("A", frameNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    ASSERT_EQ(mockStack->Size(), 1);

    /**
     * @tc.steps: step3. replace pageA
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    mockStack->Remove();
    mockStack->Add("B", replaceNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    ASSERT_EQ(mockStack->Size(), 1);

    /**
     * @tc.steps: step4. push pageC
     */
    mockStack->Add("C", frameNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    ASSERT_EQ(mockStack->Size(), 2);
}

/**
 * @tc.name: NestedNavigationTest001
 * @tc.desc: Test case of nested Navigation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NestedNavigationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationStack, setup mock function
     */

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ScopedViewStackProcessor scopedViewStackProcessor;
    auto outerStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto innerStack = AceType::MakeRefPtr<MockNavigationStack>();
    EXPECT_CALL(*outerStack, OnAttachToParent(_)).Times(0);
    EXPECT_CALL(*innerStack, OnAttachToParent(_)).Times(1);

    /**
     * @tc.steps: step1. create outer navigation and set stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStackWithCreatorAndUpdater(
        [&outerStack]() -> RefPtr<MockNavigationStack> {
            return outerStack;
        }, [](RefPtr<NG::NavigationStack> stack) {
            auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
            ASSERT_NE(mockStack, nullptr);
        });
    auto groupNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(groupNode, nullptr);
    groupNode->AttachToMainTree(true, AceType::RawPtr(context));

    /**
     * @tc.steps: step2. create inner navigation and set stack
     */
    navigationModel.Create();
    navigationModel.SetNavigationStackWithCreatorAndUpdater(
        [&innerStack]() -> RefPtr<MockNavigationStack> {
            return innerStack;
        }, [](RefPtr<NG::NavigationStack> stack) {
            auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
            ASSERT_NE(mockStack, nullptr);
        });

    /**
     * @tc.steps: step3. attach navigation to main tree
     * @tc.expected: check number of NavigationStack's OnAttachToParent function calls
     */
    ViewStackProcessor::GetInstance()->Pop();
}

/*
 * @tc.name: NavigationInterceptionTest001
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
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

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    mockStack->SetInterceptionBeforeCallback([stack = WeakPtr<MockNavigationStack>(mockStack)]
        (const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(from, nullptr);
        ASSERT_NE(to, nullptr);
        auto info = to->GetNavPathInfo();
        ASSERT_NE(info, nullptr);
        ASSERT_EQ(info->GetName(), "A");
        ASSERT_EQ(operation, NavigationOperation::PUSH);
        ASSERT_EQ(isAnimated, true);
        auto navigationStack = stack.Upgrade();
        ASSERT_NE(navigationStack, nullptr);
        navigationStack->Remove();
        RefPtr<FrameNode> frameNode = NavigationTestNg::CreateDestination("B");
        navigationStack->Add("B", frameNode);
        navigationStack->UpdateReplaceValue(true);
        navigationStack->UpdateAnimatedValue(true);
    });

    mockStack->SetInterceptionAfterCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        EXPECT_EQ(from, nullptr);
        EXPECT_NE(to, nullptr);
        auto info = to->GetNavPathInfo();
        ASSERT_NE(info->GetName(), "B");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, false);
    });

    /**
     * @tc.steps: step3. sync navigation stack
     * @tc.expected: step3. trigger navigation interception before and after callback
     */
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
}

/**
 * @tc.name: NavigationInterceptionTest002
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
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

    /**
     * @tc.steps: step2. push A to navigation stack
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition
     */
    mockStack->SetInterceptionBeforeCallback([stack = WeakPtr<NavigationStack>(mockStack)](
        const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::POP);
        ASSERT_EQ(isAnimated, true);
        auto navigationStack = stack.Upgrade();
        ASSERT_NE(navigationStack, nullptr);
        auto frameNode = NavigationTestNg::CreateDestination("B");
        ASSERT_NE(frameNode, nullptr);
        navigationStack->Add("B", frameNode);
    });

    mockStack->SetInterceptionAfterCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        EXPECT_NE(from, nullptr);
        EXPECT_NE(to, nullptr);
        auto fromInfo = from->GetNavPathInfo();
        ASSERT_NE(fromInfo, nullptr);
        ASSERT_EQ(fromInfo->GetName(), "A");
        auto toInfo = to->GetNavPathInfo();
        ASSERT_NE(toInfo, nullptr);
        ASSERT_EQ(toInfo->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::PUSH);
        ASSERT_EQ(isAnimated, false);
    });

    /**
     * @tc.steps: step3. sync navigation stack
     * @tc.expected: step3. trigger navigation interception before and after callback
     */
    mockStack->Remove();
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
}

/**
 * @tc.name: NavigationInterceptionTest003
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
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

    /**
     * @tc.steps: step2. push A to navigation stack
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    mockStack->UpdateReplaceValue(true);

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition
     */
    mockStack->SetInterceptionBeforeCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, true);
    });

    mockStack->SetInterceptionAfterCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, true);
    });

    /**
     * @tc.steps: step3. sync navigation stack.
     * @tc.expected: step3. trigger navigation before and after callback.
     */
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
}

/**
 * @tc.name: NavigationInterceptionTest004
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
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

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition.
     *            Remove top Destination during interception before callback.
     * @tc.expected: trigger before interception and not trigger after interception.
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    mockStack->SetInterceptionBeforeCallback([stack = WeakPtr<NavigationStack>(mockStack)]
        (const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, true);
        auto navigationStack = stack.Upgrade();
        EXPECT_NE(navigationStack, nullptr);
        navigationStack->Remove();
    });

    uint32_t times = 0;
    mockStack->SetInterceptionAfterCallback([time = &times](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        (*time)++;
    });

    /**
     * @tc.steps: step3. push destination A and sync navigation stack.
     * @tc.expected: step3. don't trigger interception after callback.times is 0.
     */
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
    EXPECT_EQ(times, 0);
}

/**
 * @tc.name: NavigationSplitPlaceholderTest001
 * @tc.desc: Test Create.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationSplitPlaceholderTest001, TestSize.Level1)
{
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    NavigationModelNG navigationModelNG;
    navigationModelNG.Create();
    navigationModelNG.SetSplitPlaceholder(columnNode);
    auto rawFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto frameNode = AceType::Claim(rawFrameNode);
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto placeholderContentNode = navigationGroupNode->GetPlaceholderContentNode();
    ASSERT_NE(placeholderContentNode, nullptr);
    ASSERT_EQ(static_cast<int32_t>(placeholderContentNode->GetChildren().size()), 1);
    auto contentFrameNode = AceType::DynamicCast<FrameNode>(placeholderContentNode);
    ASSERT_NE(contentFrameNode, nullptr);
    auto eventHub = contentFrameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_EQ(eventHub->IsEnabled(), false);
    auto focusHub = contentFrameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    ASSERT_EQ(focusHub->GetFocusable(), false);
    navigationModelNG.ResetSplitPlaceholder(rawFrameNode);
    placeholderContentNode = navigationGroupNode->GetPlaceholderContentNode();
    ASSERT_EQ(placeholderContentNode, nullptr);
    navigationModelNG.SetSplitPlaceholder(rawFrameNode, &(*columnNode));
    placeholderContentNode = navigationGroupNode->GetPlaceholderContentNode();
    ASSERT_NE(placeholderContentNode, nullptr);
    ASSERT_EQ(static_cast<int32_t>(placeholderContentNode->GetChildren().size()), 1);
}

/**
 * @tc.name: NavigationCommonTitleTest001
 * @tc.desc: Test Navigation CommonTitle.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationCommonTitleTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("Title", true);
    navigationModel.SetSubtitle("subTitle");
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
}
} // namespace OHOS::Ace::NG
