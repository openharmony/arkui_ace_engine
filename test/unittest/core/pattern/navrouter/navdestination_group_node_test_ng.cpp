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
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_ANIMATION_ID = -1;
constexpr int32_t TRANSITION_COMBINATIONS = 6;
const std::string TITLE_BAR_NODE_MENU = "menu";

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
 * @tc.name: CreateEmpty
 * @tc.desc: cover CreateEmpty
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, CreateEmpty001, TestSize.Level1)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.CreateEmpty();
    navdestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    navdestinationModel.SetHideTitleBar(frameNode, false, false);
    navdestinationModel.SetHideBackButton(frameNode, false);
    navdestinationModel.SetBackgroundColor(Color::RED, false);
    navdestinationModel.SetBackgroundColor(Color::RED, true);
    navdestinationModel.SetBackgroundColor(frameNode, Color::RED, false);
    navdestinationModel.SetBackgroundColor(frameNode, Color::RED, true);
    NavigationTitleInfo param;
    param.hasSubTitle = true;
    param.hasMainTitle = true;
    navdestinationModel.ParseCommonTitle(frameNode, param);

    param.hasSubTitle = false;
    navdestinationModel.ParseCommonTitle(frameNode, param);

    param.hasMainTitle = false;
    navdestinationModel.ParseCommonTitle(frameNode, param);
    EXPECT_TRUE(!param.hasSubTitle && !param.hasMainTitle);
}

/**
 * @tc.name: ParseCommonTitle001
 * @tc.desc: Test NavDestinationGroupNodeTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return false
 *               hasMainTitle is false
 *               !hasSubTitle is false
 *               subTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, ParseCommonTitle001, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make GetPrevTitleIsCustomValue return false
    navDestinationNode->propPrevTitleIsCustom_ = false;
    stack->Push(navDestinationNode);

    // Make sure hasMainTitle is false and !hasSubTitle is false
    NavigationTitleInfo param;
    param.hasSubTitle = true;
    param.hasMainTitle = false;
    EXPECT_FALSE(!param.hasSubTitle);
    EXPECT_FALSE(param.hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return false
    EXPECT_FALSE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    ASSERT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    navDestinationModel.ParseCommonTitle(frameNode, param);
    ASSERT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
}

/**
 * @tc.name: ParseCommonTitle002
 * @tc.desc: Test NavDestinationGroupNodeTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               HasTitleHeight return false
 *               hasMainTitle is true
 *               mainTitle is false
 *               !hasSubTitle is false
 *               subTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, ParseCommonTitle002, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto subTitle = FrameNode::CreateFrameNode("SubTitle", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->subtitle_ = subTitle;
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    stack->Push(navDestinationNode);

    // Make sure hasMainTitle is true and !hasSubTitle is false
    NavigationTitleInfo param;
    param.hasSubTitle = true;
    param.hasMainTitle = true;
    EXPECT_FALSE(!param.hasSubTitle);
    EXPECT_TRUE(param.hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    // Make sure HasTitleHeight return false
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    // Make sure mainTitle is false
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
    // subTitle is true
    auto subTitleTest = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    navDestinationModel.ParseCommonTitle(frameNode, param);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
}

/**
 * @tc.name: ParseCommonTitle003
 * @tc.desc: Test NavDestinationGroupNodeTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               HasTitleHeight return true
 *               hasMainTitle is true
 *               mainTitle is true
 *               !hasSubTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, ParseCommonTitle003, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto title = FrameNode::CreateFrameNode("SubTitle", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    // Make HasTitleHeight return true
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    titleBarLayoutProperty->propTitleHeight_ = NG::DOUBLE_LINE_TITLEBAR_HEIGHT;
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    stack->Push(navDestinationNode);

    // Make sure hasMainTitle is true and !hasSubTitle is true
    NavigationTitleInfo param;
    param.hasSubTitle = false;
    param.hasMainTitle = true;
    EXPECT_TRUE(!param.hasSubTitle);
    EXPECT_TRUE(param.hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    // Make sure HasTitleHeight return true
    auto titleBarLayoutPropertyTest = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    EXPECT_TRUE(titleBarLayoutPropertyTest->HasTitleHeight());
    // Make sure mainTitle is true
    navDestinationModel.ParseCommonTitle(frameNode, param);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
}

/**
 * @tc.name: SetMenuItems001
 * @tc.desc: Test SetMenuItems function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, SetMenuItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationGroupNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    NG::BarItem bar;
    std::vector<NG::BarItem> barItems;
    barItems.push_back(bar);

    /**
     * @tc.steps: step2. Call SetMenuItems when UpdatePrevMenuIsCustom is true.
     */
    navDestinationGroupNode->UpdatePrevMenuIsCustom(true);
    navDestinationModel.SetMenuItems(frameNode, std::move(barItems));
    EXPECT_FALSE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);

    /**
     * @tc.steps: step3. Call SetMenuItems when UpdatePrevMenuIsCustom is false.
     * and navDestinationGroupNode has no menu
     */
    navDestinationGroupNode->UpdatePrevMenuIsCustom(false);
    navDestinationModel.SetMenuItems(frameNode, std::move(barItems));
    EXPECT_FALSE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::ADD);

    /**
     * @tc.steps: step4. Call SetMenuItems when UpdatePrevMenuIsCustom is false
     * and navDestinationGroupNode has menu
     */
    navDestinationGroupNode->UpdatePrevMenuIsCustom(false);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(TITLE_BAR_NODE_MENU, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    navDestinationGroupNode->SetMenu(menuNode);
    navDestinationModel.SetMenuItems(frameNode, std::move(barItems));
    EXPECT_FALSE(navDestinationGroupNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(navDestinationGroupNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: SetCustomTitle001
 * @tc.desc: Test NavDestinationGroupNodeTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return false
 *               currentTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, SetCustomTitle001, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetPrevTitleIsCustomValue return false
    navDestinationNode->propPrevTitleIsCustom_ = false;

    auto customNode = FrameNode::CreateFrameNode("Title", 99, AceType::MakeRefPtr<CustomNodePattern>());
    EXPECT_NE(customNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    // Make sure GetPrevTitleIsCustomValue return false
    EXPECT_FALSE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    // Make sure currentTitle is false
    EXPECT_EQ(titleBarNode->GetTitle(), nullptr);
    navDestinationModel.SetCustomTitle(frameNode, customNode);
}

/**
 * @tc.name: SetCustomTitle002
 * @tc.desc: Test NavDestinationGroupNodeTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               currentTitle is true
 *               GetId is not GetId
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, SetCustomTitle002, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    // Make currentTitle true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto title = FrameNode::CreateFrameNode("Title", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto customNode = FrameNode::CreateFrameNode("Title", 99, AceType::MakeRefPtr<CustomNodePattern>());
    EXPECT_NE(customNode, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    // Make sure currentTitle is true
    auto currentTitle = titleBarNodeTest->GetTitle();
    EXPECT_NE(currentTitle, nullptr);
    // Make sure GetId is not GetId
    EXPECT_NE(currentTitle->GetId(), customNode->GetId());
    navDestinationModel.SetCustomTitle(frameNode, customNode);
}

/**
 * @tc.name: SetCustomTitle003
 * @tc.desc: Test NavDestinationGroupNodeTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               currentTitle is true
 *               GetId is GetId
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, SetCustomTitle003, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetPrevTitleIsCustomValue return true
    navDestinationNode->propPrevTitleIsCustom_ = true;
    // Make currentTitle true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto title = FrameNode::CreateFrameNode("Title", 36, AceType::MakeRefPtr<TextPattern>());
    titleBarNode->title_ = title;
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return true
    EXPECT_TRUE(navDestinationNode->GetPrevTitleIsCustomValue(false));
    // Make sure currentTitle is true
    auto currentTitle = titleBarNodeTest->GetTitle();
    EXPECT_NE(currentTitle, nullptr);
    // Make sure GetId is GetId
    EXPECT_EQ(currentTitle->GetId(), title->GetId());
    navDestinationModel.SetCustomTitle(frameNode, title);
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

/**
 * @tc.name: DoSystemFadeTransition001
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemFadeTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);

    navDestinationNode->DoSystemFadeTransition(true);
    EXPECT_TRUE(eventHub->enabled_);
}

/**
 * @tc.name: DoSystemFadeTransition002
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = true, eventHub = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemFadeTransition002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    navDestinationNode->eventHub_ = nullptr;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationNode->pattern_ = nullptr;

    navDestinationNode->DoSystemFadeTransition(true);
    EXPECT_EQ(navDestinationNode->GetOrCreateEventHub<EventHub>(), nullptr);
    navDestinationNode->pattern_ = navDestinationPattern;
}

/**
 * @tc.name: DoSystemFadeTransition003
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = true
 *           Condition: !inCurrentStack_ = true, eventHub = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemFadeTransition003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);

    navDestinationNode->DoSystemFadeTransition(true);
    EXPECT_FALSE(eventHub->enabled_);
}

/**
 * @tc.name: DoSystemSlideTransition001
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = false
 *           Branch: if ((operation == NavigationOperation::POP) ^ isEnter) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemSlideTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemSlideTransition(NavigationOperation::POP, true);
    EXPECT_TRUE(eventHub->enabled_);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::TRANSPARENT);
}

/**
 * @tc.name: DoSystemSlideTransition002
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = true, eventHub = false
 *           Branch: if ((operation == NavigationOperation::POP) ^ isEnter) = true
 *           Branch: if (!isEnter) = false
 *           Branch: if (!isEnter) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemSlideTransition002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    navDestinationNode->eventHub_ = nullptr;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationNode->pattern_ = nullptr;
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->translateXY_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(100.0f, 60.0f));

    navDestinationNode->DoSystemSlideTransition(NavigationOperation::PUSH, true);
    EXPECT_EQ(navDestinationNode->GetOrCreateEventHub<EventHub>(), nullptr);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetX(), 0.0f);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetY(), 0.0f);
    navDestinationNode->pattern_ = navDestinationPattern;
}

/**
 * @tc.name: DoSystemSlideTransition003
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = true
 *           Condition: !inCurrentStack_ = true, eventHub = true
 *           Branch: if ((operation == NavigationOperation::POP) ^ isEnter) = true
 *           Branch: if (!isEnter) = true
 *           Branch: if (!isEnter) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemSlideTransition003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->translateXY_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(100.0f, 60.0f));
    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::SLIDE_RIGHT;
    navDestinationNode->GetGeometryNode()->SetFrameSize(SizeF(200.0f, 100.0f));

    navDestinationNode->DoSystemSlideTransition(NavigationOperation::POP, false);
    EXPECT_FALSE(eventHub->enabled_);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetX(), 0.0f);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetY(), 0.0f);
}

/**
 * @tc.name: DoSystemEnterExplodeTransition001
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = false
 *           Branch: if (operation == NavigationOperation::POP) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemEnterExplodeTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemEnterExplodeTransition(NavigationOperation::PUSH);
    EXPECT_TRUE(eventHub->enabled_);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::RED);
}

/**
 * @tc.name: DoSystemEnterExplodeTransition002
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = true, eventHub = false
 *           Branch: if (operation == NavigationOperation::POP) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemEnterExplodeTransition002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    navDestinationNode->eventHub_ = nullptr;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationNode->pattern_ = nullptr;
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemEnterExplodeTransition(NavigationOperation::PUSH);
    EXPECT_EQ(navDestinationNode->GetOrCreateEventHub<EventHub>(), nullptr);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::RED);
    navDestinationNode->pattern_ = navDestinationPattern;
}

/**
 * @tc.name: DoSystemEnterExplodeTransition003
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = true
 *           Condition: !inCurrentStack_ = true, eventHub = true
 *           Branch: if (operation == NavigationOperation::POP) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemEnterExplodeTransition003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemEnterExplodeTransition(NavigationOperation::POP);
    EXPECT_FALSE(eventHub->enabled_);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::TRANSPARENT);
}

/**
 * @tc.name: DoSystemExitExplodeTransition001
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = false
 *           Branch: if (operation == NavigationOperation::POP) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemExitExplodeTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemExitExplodeTransition(NavigationOperation::PUSH);
    EXPECT_TRUE(eventHub->enabled_);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::TRANSPARENT);
}

/**
 * @tc.name: DoSystemExitExplodeTransition002
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = true, eventHub = false
 *           Branch: if (operation == NavigationOperation::POP) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemExitExplodeTransition002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    navDestinationNode->eventHub_ = nullptr;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationNode->pattern_ = nullptr;
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemExitExplodeTransition(NavigationOperation::POP);
    EXPECT_EQ(navDestinationNode->GetOrCreateEventHub<EventHub>(), nullptr);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::RED);
    navDestinationNode->pattern_ = navDestinationPattern;
}

/**
 * @tc.name: DoSystemExitExplodeTransition003
 * @tc.desc: Branch: if (!inCurrentStack_ && eventHub) = true
 *           Condition: !inCurrentStack_ = true, eventHub = true
 *           Branch: if (operation == NavigationOperation::POP) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoSystemExitExplodeTransition003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = false;
    auto eventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->SetActualForegroundColor(Color::RED);

    navDestinationNode->DoSystemExitExplodeTransition(NavigationOperation::PUSH);
    EXPECT_FALSE(eventHub->enabled_);
    EXPECT_EQ(navDestinationRenderContext->actualForegroundColor_, Color::TRANSPARENT);
}

/**
 * @tc.name: StartCustomTransitionAnimation001
 * @tc.desc: Branch: if (!hasResetProperties && isEnter) = false
 *           Condition: !hasResetProperties = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, StartCustomTransitionAnimation001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    NavDestinationTransition navDestinationTransition;
    navDestinationTransition.event = []() { };
    navDestinationTransition.onTransitionEnd = []() { };
    navDestinationTransition.duration = 100.0f;
    navDestinationTransition.delay = 100.0f;
    navDestinationTransition.curve = Curves::EASE_IN_OUT;
    bool hasResetProperties = true;

    navDestinationNode->StartCustomTransitionAnimation(navDestinationTransition, false, hasResetProperties, 100.0f);
    EXPECT_TRUE(hasResetProperties);
}

/**
 * @tc.name: StartCustomTransitionAnimation002
 * @tc.desc: Branch: if (!hasResetProperties && isEnter) = false
 *           Condition: !hasResetProperties = true, isEnter = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, StartCustomTransitionAnimation002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    NavDestinationTransition navDestinationTransition;
    navDestinationTransition.event = []() { };
    navDestinationTransition.onTransitionEnd = []() { };
    navDestinationTransition.duration = 100.0f;
    navDestinationTransition.delay = 100.0f;
    navDestinationTransition.curve = Curves::EASE_IN_OUT;
    bool hasResetProperties = false;

    navDestinationNode->StartCustomTransitionAnimation(navDestinationTransition, false, hasResetProperties, 100.0f);
    EXPECT_FALSE(hasResetProperties);
}

/**
 * @tc.name: StartCustomTransitionAnimation003
 * @tc.desc: Branch: if (!hasResetProperties && isEnter) = true
 *           Condition: !hasResetProperties = true, isEnter = true
 *           Branch: if (navigation) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, StartCustomTransitionAnimation003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->inCurrentStack_ = true;
    NavDestinationTransition navDestinationTransition;
    navDestinationTransition.event = []() { };
    navDestinationTransition.onTransitionEnd = []() { };
    navDestinationTransition.duration = 100.0f;
    navDestinationTransition.delay = 100.0f;
    navDestinationTransition.curve = Curves::EASE_IN_OUT;
    bool hasResetProperties = false;

    navDestinationNode->StartCustomTransitionAnimation(navDestinationTransition, true, hasResetProperties, 100.0f);
    EXPECT_TRUE(hasResetProperties);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    EXPECT_EQ(navDestinationPattern->GetNavigationNode(), nullptr);
}

/**
 * @tc.name: StartCustomTransitionAnimation004
 * @tc.desc: Branch: if (!hasResetProperties && isEnter) = true
 *           Condition: !hasResetProperties = true, isEnter = true
 *           Branch: if (navigation) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, StartCustomTransitionAnimation004, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navDestinationPattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigationNode));
    navDestinationNode->inCurrentStack_ = true;
    NavDestinationTransition navDestinationTransition;
    navDestinationTransition.event = []() { };
    navDestinationTransition.onTransitionEnd = []() { };
    navDestinationTransition.duration = 100.0f;
    navDestinationTransition.delay = 100.0f;
    navDestinationTransition.curve = Curves::EASE_IN_OUT;
    bool hasResetProperties = false;
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->translateXY_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(100.0f, 60.0f));

    navDestinationNode->StartCustomTransitionAnimation(navDestinationTransition, true, hasResetProperties, 100.0f);
    EXPECT_TRUE(hasResetProperties);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetX(), 0.0f);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetY(), 0.0f);
}

/**
 * @tc.name: BuildTransitionFinishCallback001
 * @tc.desc: Branch: if (!hasResetProperties && isEnter) = false
 *           Condition: !hasResetProperties = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, BuildTransitionFinishCallback001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->SetIsOnAnimation(true);
    navDestinationNode->SetInCurrentStack(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->translateXY_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(100.0f, 60.0f));
    navDestinationNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);

    auto finish = navDestinationNode->BuildTransitionFinishCallback(false, nullptr);
    finish();
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetX(), 100.0f);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetY(), 60.0f);
    EXPECT_FALSE(navDestinationNode->isOnAnimation_);
}

/**
 * @tc.name: BuildTransitionFinishCallback002
 * @tc.desc: Branch: if (extraOption) = true
 *           Branch: if (animationId != navDestination->GetAnimationId()) = false
 *           Branch: if (isSystemTransition) = true
 *           Branch: if (!navDestination->SetInCurrentStack()) = false
 *           Branch: if (navDestination->HasStandardBefore()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, BuildTransitionFinishCallback002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navDestinationPattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigationNode));
    navDestinationNode->index_ = 0;
    navigationNode->lastStandardIndex_ = 1;
    navDestinationNode->SetIsOnAnimation(true);
    navDestinationNode->SetInCurrentStack(true);
    auto navDestinationRenderContext = AceType::DynamicCast<MockRenderContext>(navDestinationNode->GetRenderContext());
    ASSERT_NE(navDestinationRenderContext, nullptr);
    navDestinationRenderContext->translateXY_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(100.0f, 60.0f));
    navDestinationNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);

    bool extraOptionCalled = false;
    auto extraOption = [&extraOptionCalled] () {
        extraOptionCalled = true;
    };
    auto finish = navDestinationNode->BuildTransitionFinishCallback(true, extraOption);
    finish();
    EXPECT_TRUE(extraOptionCalled);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetX(), 0.0f);
    EXPECT_EQ(navDestinationRenderContext->GetTranslateXYProperty().GetY(), 0.0f);
    EXPECT_EQ(navDestinationNode->GetLayoutProperty()->GetVisibility(), VisibleType::INVISIBLE);
    EXPECT_FALSE(navDestinationNode->isOnAnimation_);
}

/**
 * @tc.name: BuildTransitionFinishCallback003
 * @tc.desc: Branch: if (animationId != navDestination->GetAnimationId()) = false
 *           Branch: if (!navDestination->SetInCurrentStack()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, BuildTransitionFinishCallback003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navDestinationPattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigationNode));
    navDestinationNode->index_ = 0;
    navigationNode->lastStandardIndex_ = 1;
    navDestinationNode->SetInCurrentStack(false);
    navDestinationNode->SetIsOnAnimation(true);

    auto finish = navDestinationNode->BuildTransitionFinishCallback(true, [] () {});
    finish();
    EXPECT_TRUE(navDestinationNode->isOnAnimation_);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Branch: if (filter.IsFastFilter()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, ToJsonValue001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 1;
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("mode"), "");
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Branch: if (filter.IsFastFilter()) = false
 *           Branch: if (titleBarNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, ToJsonValue002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->propContent_ = u"MainPage";
    titleBarNode->title_ = textNode;

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("title"), "MainPage");
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Branch: if (filter.IsFastFilter()) = false
 *           Branch: if (titleBarNode) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, ToJsonValue003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("title"), "");
}

/**
 * @tc.name: TransitionTypeToString001
 * @tc.desc: Branch: case NavigationSystemTransitionType::NONE = true
 *           Branch: case NavigationSystemTransitionType::TITLE = true
 *           Branch: case NavigationSystemTransitionType::CONTENT = true
 *           Branch: case NavigationSystemTransitionType::FADE = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, TransitionTypeToString001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::NONE;

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.NONE");

    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::TITLE;

    info = JsonUtil::Create(true);
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.TITLE");

    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::CONTENT;

    info = JsonUtil::Create(true);
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.CONTENT");

    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::FADE;

    info = JsonUtil::Create(true);
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.FADE");
}

/**
 * @tc.name: TransitionTypeToString002
 * @tc.desc: Branch: case NavigationSystemTransitionType::EXPLODE = true
 *           Branch: case NavigationSystemTransitionType::SLIDE_RIGHT = true
 *           Branch: case NavigationSystemTransitionType::SLIDE_BOTTOM = true
 *           Branch: default = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, TransitionTypeToString002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::EXPLODE;

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    InspectorFilter filter;
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.EXPLODE");

    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::SLIDE_RIGHT;

    info = JsonUtil::Create(true);
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.SLIDE_RIGHT");

    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType::SLIDE_BOTTOM;

    info = JsonUtil::Create(true);
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.SLIDE_BOTTOM");

    navDestinationNode->systemTransitionType_ = NavigationSystemTransitionType(-1);

    info = JsonUtil::Create(true);
    navDestinationNode->ToJsonValue(info, filter);
    EXPECT_EQ(info->GetString("systemTransition"), "NavigationSystemTransitionType.DEFAULT");
}

/**
 * @tc.name: CheckTransitionPop001
 * @tc.desc: Branch: if (IsCacheNode()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, CheckTransitionPop001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->isCacheNode_ = true;

    bool ret = navDestinationNode->CheckTransitionPop(1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CheckTransitionPop002
 * @tc.desc: Branch: if (IsCacheNode()) = false
 *           Branch: if (animationId_ != animationId) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, CheckTransitionPop002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->isCacheNode_ = false;
    navDestinationNode->animationId_ = 0;

    bool ret = navDestinationNode->CheckTransitionPop(1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CheckTransitionPop003
 * @tc.desc: Branch: if (IsCacheNode()) = false
 *           Branch: if (animationId_ != animationId) = false
 *           Branch: if (GetTransitionType() != PageTransitionType::EXIT_POP) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, CheckTransitionPop003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->isCacheNode_ = false;
    navDestinationNode->animationId_ = 1;
    navDestinationNode->transitionType_ = PageTransitionType::ENTER;

    bool ret = navDestinationNode->CheckTransitionPop(1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CheckTransitionPop004
 * @tc.desc: Branch: if (IsCacheNode()) = false
 *           Branch: if (animationId_ != animationId) = false
 *           Branch: if (GetTransitionType() != PageTransitionType::EXIT_POP) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, CheckTransitionPop004, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->isCacheNode_ = false;
    navDestinationNode->animationId_ = 1;
    navDestinationNode->transitionType_ = PageTransitionType::EXIT_POP;

    bool ret = navDestinationNode->CheckTransitionPop(1);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DoCustomTransition001
 * @tc.desc: Branch: if (!delegate) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoCustomTransition001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->navDestinationTransitionDelegate_ = nullptr;

    int32_t ret = navDestinationNode->DoCustomTransition(NavigationOperation::PUSH, false);
    EXPECT_EQ(ret, -1);
}

/**
 * @tc.name: DoCustomTransition002
 * @tc.desc: Branch: if (!delegate) = false
 *           Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = false
 *           Branch: if (!allTransitions.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoCustomTransition002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->navDestinationTransitionDelegate_ = [](NavigationOperation operation, bool isEnter) {
        return std::nullopt;
    };
    navDestinationNode->inCurrentStack_ = true;
    auto navDestinationEventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(navDestinationEventHub, nullptr);
    navDestinationEventHub->SetEnabledInternal(true);

    int32_t ret = navDestinationNode->DoCustomTransition(NavigationOperation::PUSH, false);
    EXPECT_EQ(ret, -1);
    EXPECT_TRUE(navDestinationEventHub->enabled_);
}

/**
 * @tc.name: DoCustomTransition003
 * @tc.desc: Branch: if (!delegate) = false
 *           Branch: if (!inCurrentStack_ && eventHub) = false
 *           Condition: !inCurrentStack_ = true, eventHub = false
 *           Branch: if (!allTransitions.has_value()) = false
 *           Branch: if (transition.duration + transition.delay > longestAnimationDuration) = true
 *           Branch: if (longestAnimationDuration != INT32_MIN) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoCustomTransition003, TestSize.Level1)
{
    NavDestinationGroupNodeTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->navDestinationTransitionDelegate_ = [](NavigationOperation operation, bool isEnter) {
        std::vector<NavDestinationTransition> allTransitions;
        NavDestinationTransition transition;
        transition.event = []() { };
        transition.onTransitionEnd = []() { };
        transition.duration = 100.0f;
        transition.delay = 100.0f;
        transition.curve = Curves::EASE_IN_OUT;
        allTransitions.emplace_back(transition);
        return allTransitions;
    };
    navDestinationNode->inCurrentStack_ = false;
    navDestinationNode->eventHub_ = nullptr;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationNode->pattern_ = nullptr;

    int32_t ret = navDestinationNode->DoCustomTransition(NavigationOperation::PUSH, false);
    EXPECT_EQ(ret, -1);
    navDestinationNode->pattern_ = navDestinationPattern;
    NavDestinationGroupNodeTestNg::TearDownTestCase();
}

/**
 * @tc.name: DoCustomTransition004
 * @tc.desc: Branch: if (!delegate) = false
 *           Branch: if (!inCurrentStack_ && eventHub) = true
 *           Condition: !inCurrentStack_ = true, eventHub = true
 *           Branch: if (!allTransitions.has_value()) = false
 *           Branch: if (transition.duration + transition.delay > longestAnimationDuration) = false
 *           Branch: if (longestAnimationDuration != INT32_MIN) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationGroupNodeTestNg, DoCustomTransition004, TestSize.Level1)
{
    NavDestinationGroupNodeTestNg::SetUpTestCase();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navDestinationPattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigationNode));
    navDestinationNode->navDestinationTransitionDelegate_ = [](NavigationOperation operation, bool isEnter) {
        std::vector<NavDestinationTransition> allTransitions;
        NavDestinationTransition transition;
        transition.event = []() { };
        transition.onTransitionEnd = []() { };
        transition.duration = INT32_MIN;
        transition.delay = 0.0f;
        transition.curve = Curves::EASE_IN_OUT;
        allTransitions.emplace_back(transition);
        return allTransitions;
    };
    navDestinationNode->inCurrentStack_ = false;
    auto navDestinationEventHub = navDestinationNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(navDestinationEventHub, nullptr);
    navDestinationNode->animationId_ = 0;

    int32_t ret = navDestinationNode->DoCustomTransition(NavigationOperation::PUSH, false);
    EXPECT_EQ(ret, 1);
    NavDestinationGroupNodeTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG