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

#include <cstddef>
#include <list>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "test/mock/base/mock_pixel_map.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class NavrouterModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void NavrouterModelTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}
void NavrouterModelTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void NavrouterModelTestNg::SetUp() {}
void NavrouterModelTestNg::TearDown() {}

/**
 * @tc.name: NavrouterTestNg0017
 * @tc.desc: Test NavRouterGroupNode::SetBackButtonEvent.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode.
     */
    NavRouterModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    navRouterGroupNode->OnAttachToMainTree(false);
    ASSERT_EQ(navRouterGroupNode->GetParent(), nullptr);
    auto parent = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterGroupNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterGroupNode->navDestinationNode_ = navDestinationNode;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;
    auto buttonNode = FrameNode::CreateFrameNode("buttonNode", 44, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->backButton_ = buttonNode;
    ASSERT_NE(buttonNode->GetEventHub<EventHub>(), nullptr);
    auto eventHub = AceType::MakeRefPtr<NavDestinationEventHub>();
    navDestinationNode->eventHub_ = eventHub;
    auto onBack = []() { return true; };
    eventHub->onBackPressedEvent_ = onBack;
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    parent->layoutProperty_ = layoutProperty;

    auto stack = AceType::MakeRefPtr<NavigationStack>();
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    std::pair<std::string, RefPtr<UINode>> p("test", preNavDestination);
    stack->navPathList_.push_back(p);
    parent->GetPattern<NavigationPattern>()->navigationStack_ = stack;
    navRouterGroupNode->OnAttachToMainTree(false);
}

/**
 * @tc.name: NavrouterTestNg0021
 * @tc.desc: Test NavigationPattern::TransitionWithAnimation with pop.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode.
     */
    NavRouterModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    auto parent = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navContentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navContentNode", 12, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    parent->contentNode_ = navContentNode;
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "contentNode", 23, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->contentNode_ = contentNode;
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preContentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "preContentNode", 34, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->contentNode_ = preContentNode;
    auto preDestinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 44, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto destinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 55, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 66, AceType::MakeRefPtr<ButtonPattern>());

    preNavDestination->titleBarNode_ = preDestinationTitleBarNode;
    navDestination->titleBarNode_ = destinationTitleBarNode;

    auto pattern = parent->GetPattern<NavigationPattern>();
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    pattern->navigationStack_ = stack;
    std::pair<std::string, RefPtr<UINode>> p1("23", preNavDestination);
    stack->navPathList_.push_back(p1);
    std::pair<std::string, RefPtr<UINode>> p2("22", navDestination);
    stack->navPathList_.push_back(p2);

    parent->isOnAnimation_ = true;
    auto onBackButtonEvent = [](GestureEvent&) -> bool {return true;};
    navDestination->backButtonEvent_ = onBackButtonEvent;
    bool isEntry = false;
    parent->CheckCanHandleBack(isEntry);
    bool isPop = true;
    EXPECT_TRUE(parent->isOnAnimation_);
    pattern->TransitionWithAnimation(preNavDestination, navDestination, isPop);
}

/**
 * @tc.name: NavrouterTestNg0022
 * @tc.desc: Test NavigationPattern::TransitionWithAnimation with push.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode.
     */
    NavRouterModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    auto parent = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preContentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "preContentNode", 23, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNavDestination->contentNode_ = preContentNode;
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "contentNode", 34, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->contentNode_ = contentNode;
    auto preDestinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 44, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto destinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 55, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 66, AceType::MakeRefPtr<ButtonPattern>());

    preNavDestination->titleBarNode_ = preDestinationTitleBarNode;
    navDestination->titleBarNode_ = destinationTitleBarNode;

    auto pattern = parent->GetPattern<NavigationPattern>();
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    pattern->navigationStack_ = stack;
    std::pair<std::string, RefPtr<UINode>> p1("23", preNavDestination);
    stack->navPathList_.push_back(p1);
    parent->isOnAnimation_ = true;
    std::pair<std::string, RefPtr<UINode>> p2("22", navDestination);
    stack->navPathList_.push_back(p2);
    bool isPop = false;
    EXPECT_TRUE(parent->isOnAnimation_);
    pattern->TransitionWithAnimation(preNavDestination, navDestination, isPop);
}

/**
 * @tc.name: NavrouterTestNg0023
 * @tc.desc: Test NavigationGroupNode::AddChildToGroup.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode.
     */
    NavRouterModelNG model;
    model.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    auto parent = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    parent->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "contentNode", 23, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->contentNode_ = contentNode;
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preContentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "preContentNode", 34, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNavDestination->contentNode_ = preContentNode;
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto navContentNode = FrameNode::CreateFrameNode("BackButton", 44, AceType::MakeRefPtr<ButtonPattern>());
    parent->contentNode_ = navContentNode;
    parent->navBarNode_ = navBar;
    navRouterGroupNode->navDestinationNode_ = navDestination;

    auto preDestinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 55, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto destinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 66, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 77, AceType::MakeRefPtr<ButtonPattern>());

    ASSERT_EQ(navBar->contentNode_, nullptr);
    parent->AddChildToGroup(backButton);
    ASSERT_NE(navBar->contentNode_, nullptr);
    parent->AddChildToGroup(backButton);
    ASSERT_NE(navBar->contentNode_, nullptr);
}

/**
 * @tc.name: NavrouterTestNg0024
 * @tc.desc: Test NavigationGroupNode::UpdateNavDestinationNodeWithoutMarkDirty.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "contentNode", 23, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->contentNode_ = contentNode;
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preContentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "preContentNode", 34, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNavDestination->contentNode_ = preContentNode;
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });

    auto preDestinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 55, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto destinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 66, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 77, AceType::MakeRefPtr<ButtonPattern>());

    auto pattern = navigation->GetPattern<NavigationPattern>();

    auto stack = AceType::MakeRefPtr<NavigationStack>();
    pattern->navigationStack_ = stack;
    navigation->navBarNode_ = nullptr;
    navigation->UpdateNavDestinationNodeWithoutMarkDirty(nullptr);
    EXPECT_TRUE(stack->navPathList_.empty());
    ASSERT_EQ(navigation->navBarNode_, nullptr);

    std::pair<std::string, RefPtr<UINode>> p("test", preNavDestination);
    stack->navPathList_.push_back(p);

    auto preTopNavPath = pattern->navigationStack_->GetPreTopNavPath();
    EXPECT_EQ(preTopNavPath->second, nullptr);
    navigation->UpdateNavDestinationNodeWithoutMarkDirty(nullptr);
    EXPECT_EQ(stack->navPathList_.size(), 1);
    ASSERT_EQ(navigation->navBarNode_, nullptr);
}

/**
 * @tc.name: NavrouterTestNg0025
 * @tc.desc: Test NavigationGroupNode::SetBackButtonEvent.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
    navigation->SetContentNode(navigationContentNode);
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "contentNode", 23, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->contentNode_ = contentNode;
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "preNavDestination", 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preContentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "preContentNode", 34, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNavDestination->contentNode_ = preContentNode;
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto preDestinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 55, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto destinationTitleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 66, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 77, AceType::MakeRefPtr<ButtonPattern>());
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto pattern = navigation->GetPattern<NavigationPattern>();
    /**
     * @tc.steps: step2. call navigation->SetBackButtonEvent.
     */
    navigation->navBarNode_ = nullptr;
    navDestination->titleBarNode_ = destinationTitleBarNode;
    destinationTitleBarNode->backButton_ = backButton;
    backButton->eventHub_ = eventHub;
    navDestination->eventHub_ = AceType::MakeRefPtr<NavDestinationEventHub>();
    navDestination->contentNode_ = nullptr;
    navigation->SetBackButtonEvent(navDestination);
    pattern->navigationMode_ = NavigationMode::STACK;
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    std::pair<std::string, RefPtr<UINode>> p("test0", preNavDestination);
    std::pair<std::string, RefPtr<UINode>> p2("test", preNavDestination);
    stack->navPathList_.push_back(p);
    stack->navPathList_.push_back(p2);
    pattern->navigationStack_ = stack;
    ASSERT_EQ(pattern->navigationStack_->navPathList_.size(), 2);
    ASSERT_NE(AceType::DynamicCast<NavDestinationGroupNode>(pattern->GetPreNavDestination("test", preNavDestination)),
        nullptr);
    navDestination->GetPattern<NavDestinationPattern>()->customNode_ = preNavDestination;
    GestureEvent event;
    navDestination->backButtonEvent_(event);
    auto onBack = []() { return true; };
    navDestination->GetEventHub<NavDestinationEventHub>()->onBackPressedEvent_ = onBack;
    navDestination->contentNode_ = contentNode;
    eventHub->gestureEventHub_ = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    navDestination->GetPattern<NavDestinationPattern>()->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>()); });
    navDestination->GetPattern<NavDestinationPattern>()->customNode_ = preNavDestination;
    navigation->SetBackButtonEvent(navDestination);
    navDestination->backButtonEvent_(event);
    EXPECT_TRUE(navDestination->GetEventHub<NavDestinationEventHub>()->onBackPressedEvent_());
}

/**
 * @tc.name: NavrouterTestNg0027
 * @tc.desc: Test BarItemLayoutAlgorithm::Layout.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0027, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BarItemLayoutAlgorithm>();
    auto barItem = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 11, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto textNode = FrameNode::CreateFrameNode("textNode", 22, AceType::MakeRefPtr<TextPattern>());

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(barItem)), geometryNode, layoutProperty);

    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(barItem->text_, nullptr);
    barItem->text_ = textNode;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(barItem->text_, nullptr);
}

/**
 * @tc.name: NavrouterTestNg0028
 * @tc.desc: Test TitleBarNode::FastPreviewUpdateChild.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0028, TestSize.Level1)
{
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 55, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto menu = FrameNode::CreateFrameNode("menu", 22, AceType::MakeRefPtr<TextPattern>());
    auto newChild = FrameNode::CreateFrameNode("newChild", 33, AceType::MakeRefPtr<TextPattern>());

    ASSERT_TRUE(titleBarNode->children_.empty());
    titleBarNode->FastPreviewUpdateChild(0, newChild);
    ASSERT_FALSE(titleBarNode->children_.empty());
    titleBarNode->FastPreviewUpdateChild(1, menu);
    ASSERT_EQ(titleBarNode->children_.size(), 2);
    titleBarNode->FastPreviewUpdateChild(2, newChild);
    ASSERT_EQ(titleBarNode->children_.size(), 2);
}

/**
 * @tc.name: NavrouterTestNg0029
 * @tc.desc: Test NavBarNode::AddChildToGroup && GetBarItemsString.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navBar newChild then call AddChildToGroup.
     */
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto newChild = FrameNode::CreateFrameNode("newChild", 22, AceType::MakeRefPtr<TextPattern>());

    ASSERT_EQ(navBar->contentNode_, nullptr);
    navBar->AddChildToGroup(newChild);
    ASSERT_NE(navBar->contentNode_, nullptr);
    navBar->AddChildToGroup(newChild);
    ASSERT_EQ(navBar->contentNode_->children_.size(), 1);

    /**
     * @tc.steps: step2. create menu then construct navBar->menu_->children_.
     */
    auto menu = FrameNode::CreateFrameNode("menu", 33, AceType::MakeRefPtr<TextPattern>());
    auto child1 = FrameNode::CreateFrameNode("child1", 44, AceType::MakeRefPtr<TextPattern>());
    auto barItem = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 55, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItem2 = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 66, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItem3 = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 67, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    auto barItem4 = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 68, []() { return AceType::MakeRefPtr<BarItemPattern>(); });

    auto icon = FrameNode::CreateFrameNode("icon", 77, AceType::MakeRefPtr<ImagePattern>());
    auto text = FrameNode::CreateFrameNode("text", 88, AceType::MakeRefPtr<TextPattern>());

    auto icon3 = FrameNode::CreateFrameNode("icon", 78, AceType::MakeRefPtr<ImagePattern>());
    auto text3 = FrameNode::CreateFrameNode("text", 89, AceType::MakeRefPtr<TextPattern>());

    auto icon4 = FrameNode::CreateFrameNode("icon", 80, AceType::MakeRefPtr<ImagePattern>());
    auto text4 = FrameNode::CreateFrameNode("text", 81, AceType::MakeRefPtr<TextPattern>());

    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();

    imageLayoutProperty->propImageSourceInfo_ = ImageSourceInfo();

    barItem2->icon_ = icon;
    barItem2->text_ = text;

    barItem3->icon_ = icon3;
    barItem3->text_ = text3;

    barItem4->icon_ = icon4;
    barItem4->text_ = text4;

    icon3->layoutProperty_ = imageLayoutProperty;
    text3->layoutProperty_ = textLayoutProperty;
    text->layoutProperty_ = nullptr;
    icon4->layoutProperty_ = nullptr;

    /**
     * @tc.steps: step3. call navBar->GetBarItemsString.
     */
    navBar->menu_ = menu;
    navBar->GetBarItemsString(true);
    ASSERT_TRUE(navBar->menu_->children_.empty());

    navBar->menu_->children_.push_back(child1);
    navBar->menu_->children_.push_back(barItem);
    navBar->menu_->children_.push_back(barItem2);
    navBar->menu_->children_.push_back(barItem3);
    navBar->menu_->children_.push_back(barItem4);
    navBar->GetBarItemsString(true);
    ASSERT_EQ(navBar->menu_->children_.size(), 5);
}

/**
 * @tc.name: NavrouterTestNg0030
 * @tc.desc: Test NavBarLayoutAlgorithm MeasureTitleBar.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0030, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavBarLayoutAlgorithm>();
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<NavBarLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navBar)), geometryNode, layoutProperty);

    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto text4 = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto titleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto titleLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    auto titleBarNode2 = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 23, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode2)), titleGeometryNode, titleLayoutProperty);
    auto subTitle =
        TitleBarNode::GetOrCreateTitleBarNode("subTitle", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto toolBarNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto navBarContentNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto toolBarChild = FrameNode::CreateFrameNode("text", 99, AceType::MakeRefPtr<TextPattern>());
    navBar->UpdatePrevMenuIsCustom(true);
    navBar->UpdatePrevToolBarIsCustom(true);

    LayoutConstraintF constraint;
    LayoutConstraintF constraint2;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutProperty->layoutConstraint_ = constraint;
    layoutProperty->propHideTitleBar_ = true;
    layoutProperty->contentConstraint_ = constraint2;
    // toolBarNode_ contentNode_

    navBar->contentNode_ = navBarContentNode;
    navBar->toolBarNode_ = toolBarNode;
    navBar->titleBarNode_ = titleBarNode;
    navBar->children_.push_back(text4);
    layoutWrapper->childrenMap_[0] = childWrapper;
    layoutWrapper->currentChildCount_ = 1;
    layoutProperty->propHideToolBar_ = false;

    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(layoutProperty->propHideTitleBar_.value());

    layoutProperty->propHideToolBar_ = true;
    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = Dimension();
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_TRUE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());

    layoutProperty->propHideToolBar_ = false;
    toolBarNode->children_.push_back(toolBarChild);
    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = std::nullopt;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_FALSE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());

    // subtitle_
    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = std::nullopt;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_FALSE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());

    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = std::nullopt;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_FALSE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());

    titleBarNode->GetPattern<TitleBarPattern>()->SetTempTitleBarHeightVp(5.0f);
    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = std::nullopt;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_FALSE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());

    titleBarNode->GetPattern<TitleBarPattern>()->SetTempTitleBarHeightVp(5.0f);
    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = std::nullopt;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_FALSE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());

    titleBarNode->GetPattern<TitleBarPattern>()->SetTempTitleBarHeightVp(5.0f);
    layoutProperty->propHideTitleBar_ = false;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleHeight_ = std::nullopt;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propHideTitleBar_.value());
    ASSERT_FALSE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->HasTitleHeight());
}

/**
 * @tc.name: NavrouterTestNg0034
 * @tc.desc: Test TitleBarLayoutAlgorithm::Measure.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navBar titleBarNode etc, construct layoutWrapper.
     */
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ImagePattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ImagePattern>());
    auto menu = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<ButtonPattern>());
    auto menu2 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<ButtonPattern>());
    auto subtitle = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<ButtonPattern>());
    auto title = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<TextPattern>());
    auto toolBarNode = FrameNode::CreateFrameNode("BackButton", 44, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonNode = FrameNode::CreateFrameNode("BackButton", 55, AceType::MakeRefPtr<ImagePattern>());
    auto backButtonImageNode = FrameNode::CreateFrameNode("BackButton", 66, AceType::MakeRefPtr<ImagePattern>());

    titleBarNode->backButton_ = backButton;
    ASSERT_TRUE(titleBarNode->children_.empty());
    titleBarNode->children_.push_back(backButton);

    auto layoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = titleBarNode->geometryNode_;
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode)), geometryNode, layoutProperty);

    auto backLayoutProperty = backButton2->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(backLayoutProperty, nullptr);
    auto backGeometryNode = backButton2->geometryNode_;
    ASSERT_NE(backGeometryNode, nullptr);
    auto backButtonWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(backButton2)), backGeometryNode, backLayoutProperty);
    ASSERT_NE(backButtonWrapper, nullptr);
    layoutWrapper->childrenMap_[0] = backButtonWrapper;
    layoutWrapper->currentChildCount_ = 1;
    ASSERT_EQ(titleBarNode->GetChildIndexById(titleBarNode->GetBackButton()->GetId()), 0);
    ASSERT_NE(layoutWrapper->GetOrCreateChildByIndex(0), nullptr);

    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutProperty->layoutConstraint_ = constraint;
    EXPECT_FALSE(layoutProperty->contentConstraint_);
    layoutProperty->contentConstraint_ = constraint;
    /**
     * @tc.steps: step2. set menu and change properties, test TitleBarLayoutAlgorithm::MeasureBackButton.
     * @tc.expected: check whether the properties is correct.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propTitleMode_);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutProperty->propHideBackButton_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = false;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(layoutProperty->propHideBackButton_.value());
    /**
     * @tc.steps: step3. set titleBarNode->backButton_ and change properties, test TitleBarLayoutAlgorithm::MeasureMenu.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->menu_ = menu;
    ASSERT_EQ(titleBarNode->children_.size(), 1);
    titleBarNode->children_.push_back(menu);

    auto menuLayoutProperty = menu2->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuGeometryNode = menu2->geometryNode_;
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(menu2)), menuGeometryNode, menuLayoutProperty);
    ASSERT_NE(menuWrapper, nullptr);
    layoutWrapper->childrenMap_[1] = menuWrapper;
    layoutWrapper->currentChildCount_ = 2;
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(navBar));
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(navBar->propPrevMenuIsCustom_);

    navBar->propPrevMenuIsCustom_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navBar->propPrevMenuIsCustom_.value());

    menu->children_.push_back(FrameNode::CreateFrameNode("BackButton", 30, AceType::MakeRefPtr<ButtonPattern>()));
    menu->children_.push_back(FrameNode::CreateFrameNode("BackButton", 31, AceType::MakeRefPtr<ButtonPattern>()));
    menu->children_.push_back(FrameNode::CreateFrameNode("BackButton", 32, AceType::MakeRefPtr<ButtonPattern>()));
    navBar->propPrevMenuIsCustom_ = false;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(navBar->propPrevMenuIsCustom_.value());
    /**
     * @tc.steps: step4. set title and change properties, test TitleBarLayoutAlgorithm::MeasureTitle.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->title_ = title;
    ASSERT_EQ(titleBarNode->children_.size(), 2);
    titleBarNode->children_.push_back(title);

    auto titleLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    auto titleGeometryNode = title->geometryNode_;
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(title)), titleGeometryNode, titleLayoutProperty);
    ASSERT_NE(titleWrapper, nullptr);
    layoutWrapper->childrenMap_[2] = titleWrapper;
    layoutWrapper->currentChildCount_ = 3;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_NE(titleBarNode->backButton_, nullptr);

    titleBarNode->backButton_ = nullptr;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_EQ(titleBarNode->backButton_, nullptr);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    navBar->propPrevTitleIsCustom_ = true;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = false;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navBar->propPrevTitleIsCustom_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    navBar->propPrevTitleIsCustom_ = true;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navBar->propPrevTitleIsCustom_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    navBar->propPrevTitleIsCustom_ = true;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navBar->propPrevTitleIsCustom_.value());

    navBar->propPrevTitleIsCustom_ = false;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(navBar->propPrevTitleIsCustom_.value());

    navBar->propPrevTitleIsCustom_ = false;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(navBar->propPrevTitleIsCustom_.value());
    ASSERT_TRUE(layoutProperty->propHideBackButton_.value());
    /**
     * @tc.steps: step5. set subtitle and change properties ,test TitleBarLayoutAlgorithm::MeasureSubtitle.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->subtitle_ = subtitle;
    ASSERT_EQ(titleBarNode->children_.size(), 3);
    titleBarNode->children_.push_back(subtitle);

    auto subtitleLayoutProperty = subtitle->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(subtitleLayoutProperty, nullptr);
    auto subtitleGeometryNode = subtitle->geometryNode_;
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(subtitle)), subtitleGeometryNode, subtitleLayoutProperty);
    ASSERT_NE(subtitleWrapper, nullptr);
    layoutWrapper->childrenMap_[3] = subtitleWrapper;
    layoutWrapper->currentChildCount_ = 4;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(layoutProperty->propHideBackButton_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_EQ(titleBarNode->backButton_, nullptr);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    titleBarNode->backButton_ = backButton;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_NE(titleBarNode->backButton_, nullptr);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);

    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = false;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::MINI);
    ASSERT_FALSE(layoutProperty->propHideBackButton_.value());
}

/**
 * @tc.name: NavrouterTestNg0035
 * @tc.desc: Test TitleBarLayoutAlgorithm::Layout.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navBar titleBarNode etc, construct layoutWrapper.
     */
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ImagePattern>());
    auto backButton2 = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ImagePattern>());
    auto menu = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<ButtonPattern>());
    auto menu2 = FrameNode::CreateFrameNode("BackButton", 34, AceType::MakeRefPtr<ButtonPattern>());
    auto subtitle = FrameNode::CreateFrameNode("BackButton", 35, AceType::MakeRefPtr<ButtonPattern>());
    auto title = FrameNode::CreateFrameNode("BackButton", 36, AceType::MakeRefPtr<TextPattern>());
    auto toolBarNode = FrameNode::CreateFrameNode("BackButton", 44, AceType::MakeRefPtr<ButtonPattern>());
    auto buttonNode = FrameNode::CreateFrameNode("BackButton", 55, AceType::MakeRefPtr<ImagePattern>());
    auto backButtonImageNode = FrameNode::CreateFrameNode("BackButton", 66, AceType::MakeRefPtr<ImagePattern>());

    auto layoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = titleBarNode->geometryNode_;
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode)), geometryNode, layoutProperty);

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutProperty->layoutConstraint_ = constraint;
    EXPECT_FALSE(layoutProperty->contentConstraint_);
    layoutProperty->contentConstraint_ = constraint;

    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();
    /**
     * @tc.steps: step2. set backButton and change properties, test TitleBarLayoutAlgorithm::LayoutBackButton.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->backButton_ = backButton;
    ASSERT_TRUE(titleBarNode->children_.empty());
    titleBarNode->children_.push_back(backButton);

    auto backLayoutProperty = backButton->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(backLayoutProperty, nullptr);
    auto backGeometryNode = backButton->geometryNode_;
    ASSERT_NE(backGeometryNode, nullptr);
    auto backButtonWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(backButton)), backGeometryNode, backLayoutProperty);
    ASSERT_NE(backButtonWrapper, nullptr);
    layoutWrapper->childrenMap_[0] = backButtonWrapper;
    layoutWrapper->currentChildCount_ = 1;
    ASSERT_EQ(titleBarNode->GetChildIndexById(titleBarNode->GetBackButton()->GetId()), 0);
    ASSERT_NE(layoutWrapper->GetOrCreateChildByIndex(0), nullptr);

    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(layoutProperty->propTitleMode_);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(layoutProperty->propHideBackButton_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = false;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(layoutProperty->propHideBackButton_.value());
    /**
     * @tc.steps: step3. set titleBarNode->title_ and change properties, test TitleBarLayoutAlgorithm::LayoutTitle.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->title_ = title;
    ASSERT_EQ(titleBarNode->children_.size(), 1);
    titleBarNode->children_.push_back(title);

    auto titleLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(titleLayoutProperty, nullptr);
    auto titleGeometryNode = title->geometryNode_;
    ASSERT_NE(titleGeometryNode, nullptr);
    auto titleWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(title)), titleGeometryNode, titleLayoutProperty);
    ASSERT_NE(titleWrapper, nullptr);
    layoutWrapper->childrenMap_[1] = titleWrapper;
    layoutWrapper->currentChildCount_ = 2;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_NE(titleBarNode->backButton_, nullptr);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    backLayoutProperty->propVisibility_ = VisibleType::GONE;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_EQ(backLayoutProperty->propVisibility_.value(), VisibleType::GONE);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::MINI);
    EXPECT_TRUE(layoutProperty->propHideBackButton_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FULL);
    EXPECT_TRUE(layoutProperty->propHideBackButton_.value());

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleLayoutProperty->propContent_ = u"content";
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);
    EXPECT_TRUE(algorithm->isInitialTitle_);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->isInitialTitle_ = true;
    title->layoutProperty_ = AceType::MakeRefPtr<ButtonLayoutProperty>();
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);
    EXPECT_TRUE(algorithm->isInitialTitle_);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->isInitialTitle_ = false;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);
    EXPECT_FALSE(algorithm->isInitialTitle_);
    ASSERT_EQ(titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_, 0.0f);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->isInitialTitle_ = false;
    titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_ = 5.0f;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);
    EXPECT_FALSE(algorithm->isInitialTitle_);
    ASSERT_EQ(titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_, 5.0f);
    /**
     * @tc.steps: step4. set titleBarNode->subtitle_ and change properties, test
     * TitleBarLayoutAlgorithm::LayoutSubtitle.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->subtitle_ = subtitle;
    ASSERT_EQ(titleBarNode->children_.size(), 2);
    titleBarNode->children_.push_back(subtitle);

    auto subtitleLayoutProperty = subtitle->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(subtitleLayoutProperty, nullptr);
    auto subtitleGeometryNode = subtitle->geometryNode_;
    ASSERT_NE(subtitleGeometryNode, nullptr);
    auto subtitleWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(subtitle)), subtitleGeometryNode, subtitleLayoutProperty);
    ASSERT_NE(subtitleWrapper, nullptr);
    layoutWrapper->childrenMap_[2] = subtitleWrapper;
    layoutWrapper->currentChildCount_ = 3;
    subtitleGeometryNode->frame_.rect_.height_ = 20.0f;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(layoutProperty->propHideBackButton_.value());
    ASSERT_FALSE(algorithm->isInitialTitle_);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_NE(titleBarNode->GetBackButton(), nullptr);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    titleBarNode->backButton_ = nullptr;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
    ASSERT_EQ(titleBarNode->GetBackButton(), nullptr);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->isInitialTitle_ = false;
    titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_ = 0.0f;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(algorithm->isInitialTitle_);
    ASSERT_EQ(titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_, 0.0f);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->isInitialTitle_ = false;
    titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_ = 20.0f;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(algorithm->isInitialTitle_);
    ASSERT_EQ(titleBarNode->GetPattern<TitleBarPattern>()->tempTitleOffsetY_, 20.0f);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FULL);

    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = true;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::MINI);
    ASSERT_TRUE(layoutProperty->propHideBackButton_.value());

    titleGeometryNode->frame_.rect_.height_ = 20.0f;
    layoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    layoutProperty->propHideBackButton_ = false;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::MINI);
    ASSERT_FALSE(layoutProperty->propHideBackButton_.value());

    /**
     * @tc.steps: step5. set titleBarNode->menu_ and change properties, test TitleBarLayoutAlgorithm::LayoutMenu.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->menu_ = menu;
    ASSERT_EQ(titleBarNode->children_.size(), 3);
    titleBarNode->children_.push_back(menu);

    auto menuLayoutProperty = menu2->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuGeometryNode = menu2->geometryNode_;
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(menu2)), menuGeometryNode, menuLayoutProperty);
    ASSERT_NE(menuWrapper, nullptr);
    layoutWrapper->childrenMap_[3] = menuWrapper;
    layoutWrapper->currentChildCount_ = 4;
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(navBar));
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);

    layoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::FREE);

    layoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    subtitleGeometryNode->frame_.rect_.height_ = 0.0f;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutProperty->propTitleMode_.value(), NavigationTitleMode::MINI);
    ASSERT_EQ(subtitleGeometryNode->frame_.rect_.height_, 0.0f);
}

/**
 * @tc.name: NavrouterTestNg0036
 * @tc.desc: Test NavigationStack.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigationStack.
     */
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ImagePattern>());
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    RefPtr<UINode> navDestinationNode;
    int32_t lastIndex;
    /**
     * @tc.steps: step2. call get function.
     * @tc.expected: navigationStack->navPathList_.empty() is true.
     */
    ASSERT_TRUE(navigationStack->navPathList_.empty());
    navigationStack->GetAllPathName();
    ASSERT_TRUE(navigationStack->navPathList_.empty());
    navigationStack->Get();
    ASSERT_TRUE(navigationStack->navPathList_.empty());
    navigationStack->Get("test", navDestinationNode, lastIndex);
    ASSERT_TRUE(navigationStack->navPathList_.empty());
    navigationStack->GetPre("test", backButton);
    ASSERT_TRUE(navigationStack->navPathList_.empty());
    /**
     * @tc.steps: step3. add element to navigationStack->navPathList_.
     */
    navigationStack->navPathList_.push_back({ "test", backButton });
    navigationStack->GetPre("test", backButton);
    navigationStack->navPathList_.push_back({ "test1", backButton });
    navigationStack->GetPre("test", backButton);
    navigationStack->GetPre("test2", backButton);
    navigationStack->Get("test3", navDestinationNode, lastIndex);
    navigationStack->GetAllPathName();
    navigationStack->navPathList_.clear();
    /**
     * @tc.steps: step4. call Remove function.
     * @tc.expected: navigationStack->navPathList_.empty() is true.
     */
    navigationStack->Remove();
    navigationStack->Remove("test");
    ASSERT_TRUE(navigationStack->navPathList_.empty());
    for (int i = 0; i < 3; i++) {
        std::pair<std::string, RefPtr<UINode>> p("test" + std::to_string(i), backButton);
        navigationStack->navPathList_.push_back(p);
    }
    navigationStack->Remove();
    ASSERT_FALSE(navigationStack->navPathList_.empty());
    ASSERT_EQ(navigationStack->navPathList_.size(), 2);
    for (int i = 0; i < 3; i++) {
        navigationStack->Remove("test" + std::to_string(i));
    }
    ASSERT_TRUE(navigationStack->navPathList_.empty());

    for (int i = 1; i <= 3; i++) {
        std::pair<std::string, RefPtr<UINode>> p("test" + std::to_string(i), backButton);
        navigationStack->navPathList_.push_back(p);
    }
    for (int i = 0; i <= 4; i++) {
        navigationStack->Remove("test" + std::to_string(i), backButton);
    }
    ASSERT_TRUE(navigationStack->navPathList_.empty());
}

/**
 * @tc.name: NavrouterTestNg0037
 * @tc.desc: Test NavigationStack.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigationStack.
     * @tc.expected: check whether the properties is correct.
     */
    auto backButton = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<ImagePattern>());
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto routeInfo = AceType::MakeRefPtr<RouteInfo>();
    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 2 + i; j++) {
            navigationStack->Add(
                "test" + std::to_string(j == 1 ? 0 : j), backButton, static_cast<NavRouteMode>(i), routeInfo);
        }
        navigationStack->navPathList_.clear();
    }
    ASSERT_TRUE(navigationStack->navPathList_.empty());
}

/**
 * @tc.name: NavrouterTestNg0038
 * @tc.desc: Test BarItemPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create BarItemNode.
     * @tc.expected: check whether the properties is correct.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 1, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);
    barItemPattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(barItemNode)));
    ASSERT_NE(barItemPattern->GetHost(), nullptr);

    barItemNode->icon_ = FrameNode::CreateFrameNode("icon", 2, AceType::MakeRefPtr<ImagePattern>());
    barItemNode->text_ = FrameNode::CreateFrameNode("text", 3, AceType::MakeRefPtr<TextPattern>());

    barItemPattern->UpdateBarItemActiveStatusResource();
    ASSERT_EQ(barItemPattern->status_, NavToolbarItemStatus::NORMAL);
    ASSERT_EQ(barItemPattern->iconStatus_, ToolbarIconStatus::INITIAL);
    /**
     * @tc.steps: step2. change status_ and iconStatus_.
     * @tc.expected: check whether the properties is correct.
     */
    std::cout<<"trigger change status"<< std::endl;
    barItemPattern->status_ = NavToolbarItemStatus::ACTIVE;
    barItemPattern->iconStatus_ = ToolbarIconStatus::INITIAL;
    barItemPattern->UpdateBarItemActiveStatusResource();
    ASSERT_EQ(barItemPattern->status_, NavToolbarItemStatus::ACTIVE);
    ASSERT_EQ(barItemPattern->iconStatus_, ToolbarIconStatus::ACTIVE);

    barItemPattern->UpdateBarItemActiveStatusResource();
    ASSERT_EQ(barItemPattern->status_, NavToolbarItemStatus::ACTIVE);
    ASSERT_EQ(barItemPattern->iconStatus_, ToolbarIconStatus::INITIAL);

    barItemPattern->status_ = NavToolbarItemStatus::NORMAL;
    barItemPattern->iconStatus_ = ToolbarIconStatus::ACTIVE;
    barItemPattern->UpdateBarItemActiveStatusResource();
    ASSERT_EQ(barItemPattern->status_, NavToolbarItemStatus::NORMAL);
    ASSERT_EQ(barItemPattern->iconStatus_, ToolbarIconStatus::ACTIVE);
}

/**
 * @tc.name: NavrouterTestNg0039
 * @tc.desc: Test BarItemPattern.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create BarItemNode.
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 1, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);
    barItemPattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(barItemNode)));
    ASSERT_NE(barItemPattern->GetHost(), nullptr);

    auto textNode = FrameNode::CreateFrameNode("text", 3, AceType::MakeRefPtr<TextPattern>());
    auto iconNode = FrameNode::CreateFrameNode("icon", 2, AceType::MakeRefPtr<ImagePattern>());

    barItemNode->icon_ = iconNode;
    barItemNode->text_ = textNode;

    auto layoutWrapper = barItemNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto algorithm = AceType::MakeRefPtr<BarItemLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);

    barItemNode->children_.push_back(textNode);

    auto textLayoutWrapper = textNode->CreateLayoutWrapper();
    textLayoutWrapper->GetLayoutProperty()->contentConstraint_ = LayoutConstraintF();
    layoutWrapper->GetLayoutProperty()->layoutConstraint_ = LayoutConstraintF();

    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    barItemLayoutProperty->layoutConstraint_ = LayoutConstraintF();
    barItemLayoutProperty->contentConstraint_ = LayoutConstraintF();
    ASSERT_EQ(barItemLayoutProperty, layoutWrapper->GetLayoutProperty());

    layoutWrapper->childrenMap_[0] = textLayoutWrapper;
    layoutWrapper->currentChildCount_ = 1;
    /**
     * @tc.steps: step2. create mock theme manager.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    /**
     * @tc.steps: step3. call algorithm->Measure then change isInToolbar_.
     */
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(barItemNode->isInToolbar_);

    barItemNode->isInToolbar_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(barItemNode->isInToolbar_);

    auto temp = LayoutConstraintF();
    temp.maxSize = SizeF(300, 300);
    barItemLayoutProperty->contentConstraint_ = temp;
    barItemLayoutProperty->layoutConstraint_ = temp;
    textLayoutWrapper->GetGeometryNode()->SetContentSize(SizeF(500, 500));
    ASSERT_EQ(barItemLayoutProperty->CreateChildConstraint().maxSize.Width(), 300);

    barItemNode->isInToolbar_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(barItemNode->isInToolbar_);

    temp.maxSize = SizeF(300, 300);
    barItemLayoutProperty->contentConstraint_ = temp;
    barItemLayoutProperty->layoutConstraint_ = temp;
    textLayoutWrapper->GetGeometryNode()->SetContentSize(SizeF(500, 500));
    ASSERT_EQ(barItemLayoutProperty->CreateChildConstraint().maxSize.Width(), 300);

    barItemNode->isInToolbar_ = true;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(barItemNode->isInToolbar_);
}

/**
 * @tc.name: NavrouterTestNg0040
 * @tc.desc: Test BarItemLayoutAlgorithm::Layout.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create BarItemNode.
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 1, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    ASSERT_NE(barItemPattern, nullptr);
    barItemPattern->AttachToFrameNode(AceType::WeakClaim(AceType::RawPtr(barItemNode)));
    ASSERT_NE(barItemPattern->GetHost(), nullptr);

    auto textNode = FrameNode::CreateFrameNode("text", 3, AceType::MakeRefPtr<TextPattern>());
    auto iconNode = FrameNode::CreateFrameNode("icon", 2, AceType::MakeRefPtr<ImagePattern>());

    barItemNode->icon_ = iconNode;
    barItemNode->text_ = textNode;

    auto layoutWrapper = barItemNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto algorithm = AceType::MakeRefPtr<BarItemLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);

    barItemNode->children_.push_back(textNode);
    barItemNode->children_.push_back(iconNode);

    auto textLayoutWrapper = textNode->CreateLayoutWrapper();
    textLayoutWrapper->GetLayoutProperty()->contentConstraint_ = LayoutConstraintF();
    layoutWrapper->GetLayoutProperty()->layoutConstraint_ = LayoutConstraintF();

    auto iconLayoutWrapper = iconNode->CreateLayoutWrapper();
    iconLayoutWrapper->GetLayoutProperty()->contentConstraint_ = LayoutConstraintF();

    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    barItemLayoutProperty->layoutConstraint_ = LayoutConstraintF();
    barItemLayoutProperty->contentConstraint_ = LayoutConstraintF();
    ASSERT_EQ(barItemLayoutProperty, layoutWrapper->GetLayoutProperty());

    layoutWrapper->childrenMap_[0] = textLayoutWrapper;
    layoutWrapper->childrenMap_[1] = iconLayoutWrapper;
    layoutWrapper->currentChildCount_ = 2;
    /**
     * @tc.steps: step2. create mock theme manager.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    /**
     * @tc.steps: step3. call algorithm->Layout then change isInToolbar_.
     */
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(barItemNode->isInToolbar_);

    barItemNode->isInToolbar_ = true;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(barItemNode->isInToolbar_);
}

/**
 * @tc.name: NavrouterTestNg0041
 * @tc.desc: Test TitleBarLayoutAlgorithm::LayoutMenu
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto menuNode = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<ButtonPattern>());
    auto parent = NavBarNode::GetOrCreateNavBarNode("parent", 3, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutWrapper = titleBarNode->CreateLayoutWrapper();
    auto titleBarLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    layoutWrapper->layoutProperty_ = titleBarLayoutProperty;

    auto menuWrapper = menuNode->CreateLayoutWrapper();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    GeometryProperty geo;
    geo.rect_ = RectF(0, 0, 20, 20);
    geometryNode->frame_ = geo;
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    menuWrapper->geometryNode_ = geometryNode;
    titleBarNode->menu_ = menuNode;
    titleBarNode->children_.push_back(menuNode);
    layoutWrapper->AppendChild(menuWrapper);
    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->minPlatformVersion_ = 10;
    algorithm->LayoutMenu(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    algorithm->LayoutMenu(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    ASSERT_EQ(titleBarLayoutProperty->propTitleMode_.value(), NavigationTitleMode::FULL);
}

/**
 * @tc.name: NavrouterTestNg0042
 * @tc.desc: Test TitleBarLayoutAlgorithm::LayoutSubtitle
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto subtitle = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<ButtonPattern>());
    auto parent = NavBarNode::GetOrCreateNavBarNode("parent", 3, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutWrapper = titleBarNode->CreateLayoutWrapper();
    auto titleBarLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    layoutWrapper->layoutProperty_ = titleBarLayoutProperty;
    auto backButton = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<ButtonPattern>());
    backButton->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    backButton->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    titleBarNode->backButton_ = backButton;

    auto subtitleWrapper = subtitle->CreateLayoutWrapper();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    GeometryProperty geo;
    geo.rect_ = RectF(0, 0, 20, 20);
    geometryNode->frame_ = geo;
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    subtitleWrapper->geometryNode_ = geometryNode;
    titleBarNode->subtitle_ = subtitle;
    titleBarNode->children_.push_back(subtitle);
    layoutWrapper->AppendChild(subtitleWrapper);
    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->minPlatformVersion_ = 10;
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    algorithm->LayoutSubtitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->LayoutSubtitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    pipeline->minPlatformVersion_ = 9;
    algorithm->LayoutSubtitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    ASSERT_EQ(titleBarLayoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAV_DESTINATION);
}

/**
 * @tc.name: NavrouterTestNg0043
 * @tc.desc: Test TitleBarLayoutAlgorithm::LayoutTitle
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    auto title = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<TextPattern>());
    auto parent = NavDestinationGroupNode::GetOrCreateGroupNode(
        "parent", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutWrapper = titleBarNode->CreateLayoutWrapper();
    auto titleBarLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    layoutWrapper->layoutProperty_ = titleBarLayoutProperty;
    auto backButton = FrameNode::CreateFrameNode("menuNode", 4, AceType::MakeRefPtr<ButtonPattern>());
    backButton->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    backButton->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    titleBarNode->backButton_ = backButton;

    auto titleWrapper = title->CreateLayoutWrapper();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    GeometryProperty geo;
    geo.rect_ = RectF(0, 0, 20, 20);
    geometryNode->frame_ = geo;
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    titleWrapper->geometryNode_ = geometryNode;
    titleBarNode->title_ = title;
    titleBarNode->children_.push_back(title);
    layoutWrapper->AppendChild(titleWrapper);
    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    auto pipeline = PipelineContext::GetCurrentContext();
    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    backButton->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    pipeline->minPlatformVersion_ = 10;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    backButton->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    auto parent2 =
        NavBarNode::GetOrCreateNavBarNode("parent2", 5, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent2));
    parent2->propPrevTitleIsCustom_ = true;
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::MINI;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    titleBarLayoutProperty->propHideBackButton_ = true;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    pipeline->minPlatformVersion_ = 9;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    pipeline->minPlatformVersion_ = 10;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    parent2->propPrevTitleIsCustom_ = false;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    ASSERT_TRUE(parent2->propPrevTitleIsCustom_);

    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->isInitialTitle_ = true;
    auto temp = title->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(temp, nullptr);
    temp->propContent_ = u"content";
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    ASSERT_FALSE(algorithm->isInitialTitle_);

    algorithm->isInitialTitle_ = true;
    title->layoutProperty_ = nullptr;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    algorithm->isInitialTitle_ = true;
    parent2->propPrevTitleIsCustom_ = true;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);

    algorithm->isInitialTitle_ = false;
    titlePattern->tempTitleOffsetY_ = 0.0f;
    algorithm->LayoutTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, 40);
    ASSERT_FALSE(algorithm->isInitialTitle_);
}

/**
 * @tc.name: NavrouterTestNg0044
 * @tc.desc: Test TitleBarLayoutAlgorithm::LayoutBackButton
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    auto backButtonNode = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<TextPattern>());
    auto parent = NavDestinationGroupNode::GetOrCreateGroupNode(
        "parent", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutWrapper = titleBarNode->CreateLayoutWrapper();
    auto titleBarLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    layoutWrapper->layoutProperty_ = titleBarLayoutProperty;
    auto backButton = FrameNode::CreateFrameNode("menuNode", 4, AceType::MakeRefPtr<ButtonPattern>());
    backButton->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    backButton->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    titleBarNode->backButton_ = backButton;

    auto backButtonWrapper = backButtonNode->CreateLayoutWrapper();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    GeometryProperty geo;
    geo.rect_ = RectF(0, 0, 20, 20);
    geometryNode->frame_ = geo;
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    backButtonWrapper->geometryNode_ = geometryNode;
    titleBarNode->backButton_ = backButtonNode;
    titleBarNode->children_.push_back(backButtonNode);
    layoutWrapper->AppendChild(backButtonWrapper);
    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    auto pipeline = PipelineContext::GetCurrentContext();
    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->LayoutBackButton(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty);
    ASSERT_EQ(pipeline->minPlatformVersion_, 10);
}

/**
 * @tc.name: NavrouterTestNg0045
 * @tc.desc: Test TitleBarLayoutAlgorithm::MeasureTitle
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    auto title = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<TextPattern>());
    auto parent = NavDestinationGroupNode::GetOrCreateGroupNode(
        "parent", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutWrapper = titleBarNode->CreateLayoutWrapper();
    auto titleBarLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    layoutWrapper->layoutProperty_ = titleBarLayoutProperty;
    auto backButton = FrameNode::CreateFrameNode("menuNode", 4, AceType::MakeRefPtr<ButtonPattern>());
    backButton->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    backButton->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    titleBarNode->backButton_ = backButton;

    auto titleWrapper = title->CreateLayoutWrapper();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    GeometryProperty geo;
    geo.rect_ = RectF(0, 0, 20, 20);
    geometryNode->frame_ = geo;
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    titleWrapper->geometryNode_ = geometryNode;
    titleBarNode->title_ = title;
    titleBarNode->children_.push_back(title);
    layoutWrapper->AppendChild(titleWrapper);
    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    auto pipeline = PipelineContext::GetCurrentContext();
    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->MeasureTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, SizeF(40, 40), 40);

    titleBarNode->subtitle_ = FrameNode::CreateFrameNode("subTitle", 6, AceType::MakeRefPtr<TextPattern>());
    algorithm->MeasureTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, SizeF(40, 40), 40);

    parent->propPrevTitleIsCustom_ = true;
    algorithm->MeasureTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, SizeF(40, 40), 40);

    auto parent2 =
        NavBarNode::GetOrCreateNavBarNode("parent2", 5, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent2));
    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    titleBarLayoutProperty->propTitleHeight_ = Dimension();
    algorithm->MeasureTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, SizeF(40, 40), 40);
    ASSERT_EQ(titleBarLayoutProperty->propTitleBarParentType_.value(), TitleBarParentType::NAVBAR);

    parent2->propPrevTitleIsCustom_ = true;
    titleBarLayoutProperty->propTitleHeight_ = std::nullopt;
    titleBarNode->subtitle_ = nullptr;
    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    algorithm->MeasureTitle(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty, SizeF(40, 40), 40);
    ASSERT_EQ(pipeline->minPlatformVersion_, 10);
}

/**
 * @tc.name: NavrouterTestNg0046
 * @tc.desc: Test TitleBarLayoutAlgorithm::LayoutTitle
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, NavrouterTestNg0046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create titleBarNode.
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 1, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto titlePattern = titleBarNode->GetPattern<TitleBarPattern>();
    auto title = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<TextPattern>());
    auto parent = NavDestinationGroupNode::GetOrCreateGroupNode(
        "parent", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    titleBarNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutWrapper = titleBarNode->CreateLayoutWrapper();
    auto titleBarLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    layoutWrapper->layoutProperty_ = titleBarLayoutProperty;
    auto backButton = FrameNode::CreateFrameNode("menuNode", 4, AceType::MakeRefPtr<ButtonPattern>());
    backButton->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    backButton->layoutProperty_->propVisibility_ = VisibleType::VISIBLE;
    titleBarNode->backButton_ = backButton;

    auto titleWrapper = title->CreateLayoutWrapper();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    GeometryProperty geo;
    geo.rect_ = RectF(0, 0, 20, 20);
    geometryNode->frame_ = geo;
    geometryNode->parentLayoutConstraint_ = LayoutConstraintF();
    titleWrapper->geometryNode_ = geometryNode;
    titleBarNode->title_ = title;
    titleBarNode->children_.push_back(title);
    layoutWrapper->AppendChild(titleWrapper);
    auto algorithm = AceType::MakeRefPtr<TitleBarLayoutAlgorithm>();

    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->minPlatformVersion_ = 10;
    titleBarLayoutProperty->propTitleBarParentType_ = TitleBarParentType::NAV_DESTINATION;
    algorithm->GetTitleWidth(titleBarNode, titleBarLayoutProperty, SizeF());
    ASSERT_EQ(backButton->layoutProperty_->propVisibility_.value(), VisibleType::VISIBLE);

    backButton->layoutProperty_->propVisibility_ = VisibleType::INVISIBLE;
    algorithm->GetTitleWidth(titleBarNode, titleBarLayoutProperty, SizeF());
    ASSERT_EQ(backButton->layoutProperty_->propVisibility_.value(), VisibleType::INVISIBLE);

    titleBarNode->children_.push_back(backButton);
    auto backButtonWrapper = backButton->CreateLayoutWrapper();
    layoutWrapper->AppendChild(backButtonWrapper);
    algorithm->MeasureBackButton(AceType::RawPtr(layoutWrapper), titleBarNode, titleBarLayoutProperty);
    ASSERT_EQ(pipeline->minPlatformVersion_, 10);
}

/**
 * @tc.name: AccessibilityTest001
 * @tc.desc: Test navdestination "backbutton" and "more" button.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, AccessibilityTest001, TestSize.Level1)
{
    auto navdestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto backButtonNode = FrameNode::CreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 7, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->backButton_ = backButtonNode;
    navdestinationNode->titleBarNode_ = titleBarNode;
    auto titleNode = AceType::DynamicCast<TitleBarNode>(navdestinationNode->GetTitleBarNode());
    ASSERT_NE(titleNode, nullptr);
    EXPECT_NE(titleNode->GetBackButton(), nullptr);

    auto AccessibilityProperty1 = backButtonNode->GetAccessibilityProperty<AccessibilityProperty>();
    AccessibilityProperty1->SetAccessibilityGroup(true);
    AccessibilityProperty1->SetAccessibilityText("NavdestinationBackbutton");
    auto text1 = AccessibilityProperty1->GetAccessibilityText();
    EXPECT_EQ(text1, "NavdestinationBackbutton");

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(V2::BAR_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    titleBarNode->SetMenu(menuNode);
    auto AccessibilityProperty2 = menuNode->GetAccessibilityProperty<AccessibilityProperty>();
    AccessibilityProperty2->SetAccessibilityGroup(true);
    AccessibilityProperty2->SetAccessibilityText("NavdestinationMenu");
    auto text2 = AccessibilityProperty2->GetAccessibilityText();
    EXPECT_EQ(text2, "NavdestinationMenu");
}

/**
 * @tc.name: MeasureIgnoreLayoutSafeArea001
 * @tc.desc: Test Measure func when set IgnoreLayoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, MeasureIgnoreLayoutSafeArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create NavBar and property
     */
    auto algorithm = AceType::MakeRefPtr<NavBarLayoutAlgorithm>();
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<NavBarLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navBar)), geometryNode, layoutProperty);
    /**
     * @tc.steps: step2.set titleBar and toolBar to NavBar
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto text4 = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto titleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto titleLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    auto titleBarNode2 = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 23, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode2)), titleGeometryNode, titleLayoutProperty);
    auto subTitle =
        TitleBarNode::GetOrCreateTitleBarNode("subTitle", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto toolBarNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto navBarContentNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto toolBarChild = FrameNode::CreateFrameNode("text", 99, AceType::MakeRefPtr<TextPattern>());
    navBar->UpdatePrevMenuIsCustom(true);
    navBar->UpdatePrevToolBarIsCustom(true);
    navBar->GetGeometryNode()->SetFrameSize(SizeF(2000, 2000));
    /**
     * @tc.steps: step3.create layout constaint for measure task
     */
    LayoutConstraintF constraint;
    LayoutConstraintF constraint2;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutProperty->layoutConstraint_ = constraint;
    layoutProperty->propHideTitleBar_ = true;
    layoutProperty->contentConstraint_ = constraint2;
    navBar->contentNode_ = navBarContentNode;
    navBar->toolBarNode_ = toolBarNode;
    navBar->titleBarNode_ = titleBarNode;
    navBar->children_.push_back(text4);
    layoutWrapper->childrenMap_[0] = childWrapper;
    layoutWrapper->currentChildCount_ = 1;
    layoutProperty->propHideToolBar_ = false;
    /**
     * @tc.steps: step4.run measure task
     * @tc.expected: since padding, ignoreLayoutSafeArea failed and keep the same height
     */
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    PaddingProperty padding;
    padding.left = CalcLength(100.0f);
    padding.top = CalcLength(100.0f);
    layoutProperty->UpdatePadding(padding);
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
}

/**
 * @tc.name: MeasureIgnoreLayoutSafeArea002
 * @tc.desc: Test Measure func when set IgnoreLayoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, MeasureIgnoreLayoutSafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create NavBar and property
     */
    auto algorithm = AceType::MakeRefPtr<NavBarLayoutAlgorithm>();
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<NavBarLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navBar)), geometryNode, layoutProperty);
    /**
     * @tc.steps: step2.set titleBar and toolBar to NavBar
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto text4 = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto titleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto titleLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    auto titleBarNode2 = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 23, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode2)), titleGeometryNode, titleLayoutProperty);
    auto subTitle =
        TitleBarNode::GetOrCreateTitleBarNode("subTitle", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto toolBarNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto navBarContentNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto toolBarChild = FrameNode::CreateFrameNode("text", 99, AceType::MakeRefPtr<TextPattern>());
    navBar->UpdatePrevMenuIsCustom(true);
    navBar->UpdatePrevToolBarIsCustom(true);
    navBar->GetGeometryNode()->SetFrameSize(SizeF(2000, 2000));
    /**
     * @tc.steps: step3.create layout constaint for measure task
     */
    LayoutConstraintF constraint;
    LayoutConstraintF constraint2;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutProperty->layoutConstraint_ = constraint;
    layoutProperty->propHideTitleBar_ = true;
    layoutProperty->contentConstraint_ = constraint2;
    navBar->contentNode_ = navBarContentNode;
    navBar->toolBarNode_ = toolBarNode;
    navBar->titleBarNode_ = titleBarNode;
    navBar->children_.push_back(text4);
    layoutWrapper->childrenMap_[0] = childWrapper;
    layoutWrapper->currentChildCount_ = 1;
    layoutProperty->propHideToolBar_ = false;
    /**
     * @tc.steps: step4.run measure task
     * @tc.expected: set invalid ignoreLayoutSafeArea type and keep the same height
     */
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_NONE, .edges = SAFE_AREA_EDGE_NONE });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_NONE, .edges = SAFE_AREA_EDGE_ALL });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_EDGE_ALL, .edges = SAFE_AREA_EDGE_NONE });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
}

/**
 * @tc.name: MeasureIgnoreLayoutSafeArea003
 * @tc.desc: Test Measure func when set IgnoreLayoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterModelTestNg, MeasureIgnoreLayoutSafeArea003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create NavBar and property
     */
    auto algorithm = AceType::MakeRefPtr<NavBarLayoutAlgorithm>();
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<NavBarLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navBar)), geometryNode, layoutProperty);
    /**
     * @tc.steps: step2.set titleBar and toolBar to NavBar
     */
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto text4 = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto titleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto titleLayoutProperty = AceType::MakeRefPtr<TitleBarLayoutProperty>();
    auto titleBarNode2 = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 23, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode2)), titleGeometryNode, titleLayoutProperty);
    auto subTitle =
        TitleBarNode::GetOrCreateTitleBarNode("subTitle", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto toolBarNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto navBarContentNode = FrameNode::CreateFrameNode("text", 22, AceType::MakeRefPtr<TextPattern>());
    auto toolBarChild = FrameNode::CreateFrameNode("text", 99, AceType::MakeRefPtr<TextPattern>());
    navBar->UpdatePrevMenuIsCustom(true);
    navBar->UpdatePrevToolBarIsCustom(true);
    navBar->GetGeometryNode()->SetFrameSize(SizeF(2000, 2000));
    /**
     * @tc.steps: step3.create layout constaint for measure task
     */
    LayoutConstraintF constraint;
    LayoutConstraintF constraint2;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    layoutProperty->layoutConstraint_ = constraint;
    layoutProperty->propHideTitleBar_ = true;
    layoutProperty->contentConstraint_ = constraint2;
    navBar->contentNode_ = navBarContentNode;
    navBar->toolBarNode_ = toolBarNode;
    navBar->titleBarNode_ = titleBarNode;
    navBar->children_.push_back(text4);
    layoutWrapper->childrenMap_[0] = childWrapper;
    layoutWrapper->currentChildCount_ = 1;
    layoutProperty->propHideToolBar_ = false;
    /**
     * @tc.steps: step4.run measure task
     * @tc.expected: set invalid ignoreLayoutSafeArea type and keep the same height
     */
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_NONE });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_NONE, .edges = SAFE_AREA_EDGE_TOP });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
    layoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_ALL, .edges = SAFE_AREA_EDGE_BOTTOM });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(navBar->GetGeometryNode()->GetFrameSize().Width(), 2000);
}
} // namespace OHOS::Ace::NG
