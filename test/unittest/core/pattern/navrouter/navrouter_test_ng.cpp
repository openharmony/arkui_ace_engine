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

#include <cstddef>
#include <list>
#include <optional>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "test/mock/base/mock_pixel_map.h"
#include "base/window/drag_window.h"
#include "core/components/counter/counter_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string FONT_CONTEXT = "start";
const std::string TITLE_BAR_NODE_MENU = "menu";
} // namespace

class NavrouterTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();

protected:
    static RefPtr<FrameNode> CreateSlidingPanel(const TestProperty& testProperty);
};

void NavrouterTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}
void NavrouterTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void NavrouterTestNg::SetUp() {}
void NavrouterTestNg::TearDown() {}

void NavrouterTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: NavrouterTestNg001
 * @tc.desc: Test NavRouterGroupNode::AddChildToGroup.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNodey.
     */
    NavRouterModelNG navRouterModel;
    navRouterModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    /**
     * @tc.steps: step2. create navRouterNode then call navRouterGroupNode->AddChildToGroup.
     * @tc.expected: navRouterGroupNode->children_.empty() is false.
     */
    EXPECT_TRUE(navRouterGroupNode->children_.empty());
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    navRouterGroupNode->AddChildToGroup(navRouterNode);
    EXPECT_FALSE(navRouterGroupNode->children_.empty());
    /**
     * @tc.steps: step3. create navDestinationNode then call navRouterGroupNode->AddChildToGroup.
     * @tc.expected: navRouterGroupNode->navDestinationNode_ is not nullptr.
     */
    ASSERT_EQ(navRouterGroupNode->navDestinationNode_, nullptr);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterGroupNode->AddChildToGroup(navDestinationNode);
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);
}

/**
 * @tc.name: NavrouterTestNg002
 * @tc.desc: Test NavRouterGroupNode::OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode and construct parent_ property.
     */
    NavRouterModelNG navRouterModel;
    navRouterModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    auto navRouterPattern = AceType::DynamicCast<NavRouterPattern>(navRouterGroupNode->pattern_);
    /**
     * @tc.steps: step2. create navigationPattern and construct navigationStack_ property.
     */
    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    std::pair<std::string, RefPtr<UINode>> pair("navDestinationNode", navDestinationNode);
    stack->navPathList_.push_back(pair);
    navigationPattern->navigationStack_ = stack;
    /**
     * @tc.steps: step3. create parentNode and set isOnAnimation_ false.
     */
    auto parentNode = AceType::MakeRefPtr<NavigationGroupNode>("NavigationGroupNode", 11, navigationPattern);
    parentNode->isOnAnimation_ = false;

    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    navRouterNode->children_.push_back(navDestinationNode);
    parentNode->contentNode_ = navRouterNode;

    navRouterGroupNode->parent_ = AceType::WeakClaim<NavigationGroupNode>(AceType::RawPtr(parentNode));
    navRouterGroupNode->OnDetachFromMainTree(false);
    ASSERT_NE(navRouterGroupNode->GetParent(), nullptr);
}

/**
 * @tc.name: NavrouterTestNg003
 * @tc.desc: Test NavRouterGroupNode::OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode and construct parent_ property.
     */
    NavRouterModelNG navRouterModel;
    navRouterModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);
    auto navRouterPattern = AceType::DynamicCast<NavRouterPattern>(navRouterGroupNode->pattern_);
    /**
     * @tc.steps: step2. create navigationPattern and construct navigationStack_ property.
     */
    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    std::pair<std::string, RefPtr<UINode>> pair("navDestinationNode", navDestinationNode);
    stack->navPathList_.push_back(pair);
    navigationPattern->navigationStack_ = stack;
    /**
     * @tc.steps: step3. create parentNode and set isOnAnimation_ false.
     */
    auto parentNode = AceType::MakeRefPtr<NavigationGroupNode>("NavigationGroupNode", 11, navigationPattern);
    parentNode->isOnAnimation_ = false;

    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    navRouterNode->children_.push_back(navDestinationNode);
    parentNode->contentNode_ = navRouterNode;

    navRouterGroupNode->parent_ = AceType::WeakClaim<NavigationGroupNode>(AceType::RawPtr(parentNode));

    auto backButton = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    backButton->eventHub_ = AceType::MakeRefPtr<EventHub>();
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    titleBarNode->backButton_ = backButton;

    auto navDestination = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "NavDestinationGroupNode", 55, AceType::MakeRefPtr<NavDestinationPattern>());
    navDestination->titleBarNode_ = titleBarNode;
    navRouterGroupNode->navDestinationNode_ = navDestination;

    navRouterGroupNode->OnAttachToMainTree(false);
    ASSERT_NE(navRouterGroupNode->GetParent(), nullptr);
}

/**
 * @tc.name: NavrouterTestNg004
 * @tc.desc: Test NavRouterGroupNode::OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navRouterGroupNode and construct parent_ property.
     */
    NavRouterModelNG navRouterModel;
    navRouterModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navRouterGroupNode = AceType::DynamicCast<NavRouterGroupNode>(frameNode);
    ASSERT_NE(navRouterGroupNode, nullptr);

    auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto parentNode = AceType::MakeRefPtr<NavigationGroupNode>("NavigationGroupNode", 11, navigationPattern);
    navRouterGroupNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parentNode));
    ASSERT_NE(navRouterGroupNode->GetParent(), nullptr);
}

/**
 * @tc.name: NavrouterTestNg006
 * @tc.desc: Test NavDestinationGroupNode::AddChildToGroup.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestinationNode then call AddChildToGroup.
     * @tc.expected: navDestinationNode->children_.empty() is false.
     */
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 11, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto layoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();
    navDestinationNode->layoutProperty_ = layoutProperty;
    auto backButton = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    navDestinationNode->AddChildToGroup(backButton);
    EXPECT_FALSE(navDestinationNode->children_.empty());
    auto tempNode = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    navDestinationNode->contentNode_ = tempNode;
    navDestinationNode->AddChildToGroup(backButton);
}

/**
 * @tc.name: NavrouterTestNg007
 * @tc.desc: Test NavDestinationGroupNode::OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestinationNode then call AddChildToGroup.
     * @tc.expected: builder->executeDeepRenderDone_ is true.
     */
    auto func = []() { return FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>()); };
    auto builder = AceType::MakeRefPtr<ShallowBuilder>(func);
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    pattern->shallowBuilder_ = builder;
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "contentNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->contentNode_ = contentNode;
    navDestinationNode->OnAttachToMainTree(false);
    EXPECT_TRUE(builder->executeDeepRenderDone_);
    pattern->shallowBuilder_ = builder;
    builder->executeDeepRenderDone_ = true;
    navDestinationNode->OnAttachToMainTree(false);
    EXPECT_TRUE(builder->executeDeepRenderDone_);
    pattern->shallowBuilder_ = nullptr;
    builder->executeDeepRenderDone_ = true;
    navDestinationNode->OnAttachToMainTree(false);
    EXPECT_TRUE(builder->executeDeepRenderDone_);
}
/**
 * @tc.name: NavrouterTestNg008
 * @tc.desc: Test NavDestinationLayoutAlgorithm::Measure.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create algorithm then prepare properties.
     */
    auto algorithm = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->children_.push_back(titleBarNode);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto navDestinationLayoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;

    navDestinationLayoutProperty->layoutConstraint_ = constraint;
    navDestinationLayoutProperty->contentConstraint_ = constraint;

    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(
        AceType::WeakClaim(AceType::RawPtr(navDestinationNode)), geometryNode, navDestinationLayoutProperty);
    SizeF sizeF(5.0f, 5.0f);

    layoutWrapper->currentChildCount_ = 1;
    /**
     * @tc.steps: step2. create navDestinationNode2 geometryNode2  then call Measure.
     */
    auto navDestinationNode2 = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto navDestinationLayoutProperty2 = AceType::MakeRefPtr<NavDestinationLayoutProperty>();
    layoutWrapper->childrenMap_[0] = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navDestinationNode2)), geometryNode2, navDestinationLayoutProperty2);
    algorithm->Measure(layoutWrapper);
    ASSERT_NE(geometryNode2, nullptr);

    navDestinationLayoutProperty->propHideTitleBar_ = true;
    algorithm->Measure(layoutWrapper);
    EXPECT_TRUE(navDestinationLayoutProperty->propHideTitleBar_.value());
    auto tempNode = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->subtitle_ = tempNode;
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    algorithm->Measure(layoutWrapper);
    EXPECT_FALSE(navDestinationLayoutProperty->propHideTitleBar_.value());
}

/**
 * @tc.name: NavrouterTestNg009
 * @tc.desc: Test NavDestinationLayoutAlgorithm::Layout.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create algorithm then prepare properties.
     */
    auto algorithm = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->children_.push_back(titleBarNode);
    auto tempNode2 = FrameNode::CreateFrameNode("BackButton", 66, AceType::MakeRefPtr<ButtonPattern>());
    navDestinationNode->contentNode_ = tempNode2;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    auto navDestinationLayoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();

    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;

    navDestinationLayoutProperty->layoutConstraint_ = constraint;
    navDestinationLayoutProperty->contentConstraint_ = constraint;

    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(
        AceType::WeakClaim(AceType::RawPtr(navDestinationNode)), geometryNode, navDestinationLayoutProperty);
    SizeF sizeF(5.0f, 5.0f);

    layoutWrapper->currentChildCount_ = 1;
    /**
     * @tc.steps: step2. create navDestinationNode2 geometryNode2  then call Measure.
     */
    auto navDestinationNode2 = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto navDestinationLayoutProperty2 = AceType::MakeRefPtr<NavDestinationLayoutProperty>();
    layoutWrapper->childrenMap_[0] = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navDestinationNode2)), geometryNode2, navDestinationLayoutProperty2);
    algorithm->Layout(layoutWrapper);
    ASSERT_NE(geometryNode2, nullptr);

    navDestinationLayoutProperty->propHideTitleBar_ = true;
    algorithm->Layout(layoutWrapper);
    EXPECT_TRUE(navDestinationLayoutProperty->propHideTitleBar_.value());
    auto tempNode = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->subtitle_ = tempNode;
    navDestinationLayoutProperty->propHideTitleBar_ = false;
    algorithm->Layout(layoutWrapper);
    EXPECT_FALSE(navDestinationLayoutProperty->propHideTitleBar_.value());
}

/**
 * @tc.name: NavrouterTestNg0010
 * @tc.desc: Test NavDestinationGroupNode::OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestinationPattern then prepare properties.
     */
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);

    auto titlePattern = AceType::MakeRefPtr<TitleBarPattern>();

    auto tempNode = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    titlePattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(tempNode));
    auto titleNode = titlePattern->frameNode_.Upgrade();
    ASSERT_NE(titleNode, nullptr);
    auto list = titleNode->GetChildren();

    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, titlePattern);
    auto layoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();

    layoutProperty->propNoPixMap_ = true;
    std::string imageInfo = "imageInfo";
    layoutProperty->propImageSource_ = ImageSourceInfo(imageInfo);

    /**
     * @tc.steps: step2. create navDestinationNode then prepare properties.
     */
    navDestinationNode->layoutProperty_ = layoutProperty;
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto titlePattern2 = AceType::MakeRefPtr<TitleBarPattern>();
    auto title = AceType::MakeRefPtr<TitleBarNode>("Title", 234, titlePattern2);

    auto subTitlePattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto subTitle = AceType::MakeRefPtr<TitleBarNode>("Title", 234, subTitlePattern);

    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));
    navDestinationPattern->OnModifyDone();
    EXPECT_TRUE(layoutProperty->HasNoPixMap());
    /**
     * @tc.steps: step3. change navDestinationLayoutProperty->HasNoPixMap().
     */
    layoutProperty->propNoPixMap_ = false;
    layoutProperty->propImageSource_ = std::nullopt;
    navDestinationPattern->OnModifyDone();
    EXPECT_TRUE(layoutProperty->HasNoPixMap());
    layoutProperty->propNoPixMap_ = std::nullopt;
    navDestinationPattern->OnModifyDone();
    EXPECT_FALSE(layoutProperty->HasNoPixMap());
}

/**
 * @tc.name: NavrouterTestNg0011
 * @tc.desc: Test NavDestinationGroupNode::OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navDestinationPattern then prepare properties.
     */
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);

    auto titlePattern = AceType::MakeRefPtr<TitleBarPattern>();

    auto tempNode = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    titlePattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(tempNode));
    auto titleNode = titlePattern->frameNode_.Upgrade();
    ASSERT_NE(titleNode, nullptr);
    auto list = titleNode->GetChildren();

    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, titlePattern);

    auto subTitlePattern = AceType::MakeRefPtr<TitleBarPattern>();
    auto subTitle = AceType::MakeRefPtr<TitleBarNode>("Title", 234, subTitlePattern);
    titleBarNode->subtitle_ = subTitle;

    auto layoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();

    /**
     * @tc.steps: step2. create navDestinationNode then prepare properties.
     */
    layoutProperty->propNoPixMap_ = true;
    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    layoutProperty->propPixelMap_ = mockPixelMap;
    layoutProperty->propHideTitleBar_ = true;
    std::string imageInfo = "imageInfo";
    layoutProperty->propImageSource_ = ImageSourceInfo(imageInfo);

    navDestinationNode->layoutProperty_ = layoutProperty;
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto titlePattern2 = AceType::MakeRefPtr<TitleBarPattern>();
    auto title = AceType::MakeRefPtr<TitleBarNode>("Title", 234, titlePattern2);
    titleBarNode->title_ = title;
    navDestinationNode->propInspectorId_ = "test";

    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));
    navDestinationPattern->OnModifyDone();
    EXPECT_TRUE(layoutProperty->HasNoPixMap());
    /**
     * @tc.steps: step3. change navDestinationLayoutProperty->HasNoPixMap().
     */
    layoutProperty->propNoPixMap_ = false;
    navDestinationPattern->OnModifyDone();
    EXPECT_TRUE(layoutProperty->HasNoPixMap());
}

/**
 * @tc.name: NavrouterTestNg0015
 * @tc.desc: Test NavRouterGroupNode::CleanNodeInNavigation.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0015, TestSize.Level1)
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
    navRouterGroupNode->OnDetachFromMainTree(false);
    ASSERT_EQ(navRouterGroupNode->GetParent(), nullptr);
    /**
     * @tc.steps: step2. create parentNode and set properties.
     */
    auto parentNode = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    parentNode->isOnAnimation_ = true;
    navRouterGroupNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parentNode));
    parentNode->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navRouterGroupNode->OnDetachFromMainTree(false);
    EXPECT_TRUE(parentNode->isOnAnimation_);

    parentNode->isOnAnimation_ = false;

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    std::pair<std::string, RefPtr<UINode>> p("navDestination", navDestinationNode);
    ASSERT_NE(parentNode->GetPattern<NavigationPattern>(), nullptr);

    ASSERT_NE(parentNode->GetPattern<NavigationPattern>()->navigationStack_, nullptr);
    parentNode->GetPattern<NavigationPattern>()->navigationStack_->navPathList_.push_back(p);

    auto contentNode = NavigationGroupNode::GetOrCreateGroupNode(
        "contentNode", 33, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    contentNode->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto child = NavDestinationGroupNode::GetOrCreateGroupNode(
        "child", 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    contentNode->children_.push_back(child);
    parentNode->contentNode_ = contentNode;

    navRouterGroupNode->OnDetachFromMainTree(false);
    ASSERT_NE(child, navDestinationNode);
}
/**
 * @tc.name: NavrouterTestNg0016
 * @tc.desc: Test NavRouterGroupNode::SetDestinationChangeEvent.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0016, TestSize.Level1)
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
    /**
     * @tc.steps: step2. create parentNode and set properties.
     */
    auto parentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 11, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterGroupNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parentNode));
    navRouterGroupNode->OnAttachToMainTree(false);
    ASSERT_NE(navRouterGroupNode->GetParent(), nullptr);
    /**
     * @tc.steps: step3. prepare event then fire function.
     */
    auto parent = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 22, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterGroupNode->parent_ = AceType::WeakClaim(AceType::RawPtr(parent));
    auto layoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();
    parent->layoutProperty_ = layoutProperty;
    ASSERT_EQ(AceType::DynamicCast<NavigationGroupNode>(navRouterGroupNode->eventHub_), nullptr);
    navRouterGroupNode->eventHub_ = AceType::MakeRefPtr<NavRouterEventHub>();
    auto stack = AceType::MakeRefPtr<NavigationStack>();
    parent->GetPattern<NavigationPattern>()->navigationStack_ = stack;

    navRouterGroupNode->OnAttachToMainTree(false);
    navRouterGroupNode->GetEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    EXPECT_EQ(layoutProperty->GetNavigationModeValue(NavigationMode::AUTO), NavigationMode::AUTO);
    layoutProperty->propNavigationMode_ = NavigationMode::STACK;
    navRouterGroupNode->OnAttachToMainTree(false);
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNavDestination->titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    std::pair<std::string, RefPtr<UINode>> p("test", preNavDestination);
    stack->navPathList_.push_back(p);
    navRouterGroupNode->GetEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterGroupNode->navDestinationNode_ = navDestinationNode;
    auto tempNode = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    parent->contentNode_ = tempNode;
    ASSERT_EQ(navDestinationNode->GetTitleBarNode(), nullptr);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBarNode;

    navRouterGroupNode->OnAttachToMainTree(false);
    navRouterGroupNode->GetEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);

    navRouterGroupNode->OnAttachToMainTree(false);
    navRouterGroupNode->GetEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);

    parent->isOnAnimation_ = false;
    ASSERT_NE(parent->GetPattern<NavigationPattern>()->GetNavDestinationNode(), nullptr);
    navRouterGroupNode->navDestinationNode_ = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 20, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(
        navRouterGroupNode->navDestinationNode_, parent->GetPattern<NavigationPattern>()->GetNavDestinationNode());
    auto cur =
        AceType::DynamicCast<NavDestinationGroupNode>(parent->GetPattern<NavigationPattern>()->GetNavDestinationNode());
    cur->contentNode_ = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    cur->GetPattern<NavDestinationPattern>()->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>()); });

    AceType::DynamicCast<NavDestinationGroupNode>(navRouterGroupNode->navDestinationNode_)->titleBarNode_ =
        TitleBarNode::GetOrCreateTitleBarNode(
            "titleBarNode34", 34, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });

    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 99, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto tb = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode98", 98, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navBar->titleBarNode_ = tb;
    ASSERT_NE(navBar, nullptr);
    parent->parent_ = AceType::WeakClaim(AceType::RawPtr(navBar));

    navRouterGroupNode->OnAttachToMainTree(false);
    navRouterGroupNode->GetEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);

    parent->isOnAnimation_ = false;
    ASSERT_NE(parent->GetPattern<NavigationPattern>()->GetNavDestinationNode(), nullptr);
    navRouterGroupNode->navDestinationNode_ = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 20, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_EQ(
        navRouterGroupNode->navDestinationNode_, parent->GetPattern<NavigationPattern>()->GetNavDestinationNode());

    AceType::DynamicCast<NavDestinationGroupNode>(navRouterGroupNode->navDestinationNode_)->titleBarNode_ =
        TitleBarNode::GetOrCreateTitleBarNode(
            "titleBarNode34", 34, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    tb->renderContext_ = nullptr;
    navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(navRouterGroupNode->navDestinationNode_);
    auto backButton = FrameNode::CreateFrameNode("BackButton", 123, AceType::MakeRefPtr<ButtonPattern>());
    AceType::DynamicCast<TitleBarNode>(navDestinationNode->titleBarNode_)->backButton_ = backButton;
    navRouterGroupNode->OnAttachToMainTree(false);
    navRouterGroupNode->GetEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);
}

/**
 * @tc.name: NavrouterTestNg0017
 * @tc.desc: Test NavRouterGroupNode::SetBackButtonEvent.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0017, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0021, TestSize.Level1)
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
    parent->CheckCanHandleBack();
    bool isPop = true;
    EXPECT_TRUE(parent->isOnAnimation_);
    pattern->TransitionWithAnimation(preNavDestination, navDestination, isPop);
}

/**
 * @tc.name: NavrouterTestNg0022
 * @tc.desc: Test NavigationPattern::TransitionWithAnimation with push.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0022, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0023, TestSize.Level1)
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

    ASSERT_EQ(navBar->navBarContentNode_, nullptr);
    parent->AddChildToGroup(backButton);
    ASSERT_NE(navBar->navBarContentNode_, nullptr);
    parent->AddChildToGroup(backButton);
    ASSERT_NE(navBar->navBarContentNode_, nullptr);
}

/**
 * @tc.name: NavrouterTestNg0024
 * @tc.desc: Test NavigationGroupNode::UpdateNavDestinationNodeWithoutMarkDirty.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0024, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0025, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0027, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<BarItemLayoutAlgorithm>();
    auto barItem = AceType::MakeRefPtr<BarItemNode>("barItem", 11);
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0028, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navBar newChild then call AddChildToGroup.
     */
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto newChild = FrameNode::CreateFrameNode("newChild", 22, AceType::MakeRefPtr<TextPattern>());

    ASSERT_EQ(navBar->navBarContentNode_, nullptr);
    navBar->AddChildToGroup(newChild);
    ASSERT_NE(navBar->navBarContentNode_, nullptr);
    navBar->AddChildToGroup(newChild);
    ASSERT_EQ(navBar->navBarContentNode_->children_.size(), 1);

    /**
     * @tc.steps: step2. create menu then construct navBar->menu_->children_.
     */
    auto menu = FrameNode::CreateFrameNode("menu", 33, AceType::MakeRefPtr<TextPattern>());
    auto child1 = FrameNode::CreateFrameNode("child1", 44, AceType::MakeRefPtr<TextPattern>());
    auto barItem = AceType::MakeRefPtr<BarItemNode>("barItem", 55);
    auto barItem2 = AceType::MakeRefPtr<BarItemNode>("barItem", 66);
    auto barItem3 = AceType::MakeRefPtr<BarItemNode>("barItem", 67);
    auto barItem4 = AceType::MakeRefPtr<BarItemNode>("barItem", 68);

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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0030, TestSize.Level1)
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
    // toolBarNode_ navBarContentNode_

    navBar->navBarContentNode_ = navBarContentNode;
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
 * @tc.name: NavrouterTestNg0033
 * @tc.desc: Test TitleBarPattern::OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navBar titleBarNode etc.
     */
    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 11, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 22, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto menu = FrameNode::CreateFrameNode("menu", 34, AceType::MakeRefPtr<ButtonPattern>());
    auto subtitle = FrameNode::CreateFrameNode("subtitle", 35, AceType::MakeRefPtr<TextPattern>());
    auto title = FrameNode::CreateFrameNode("title", 36, AceType::MakeRefPtr<TextPattern>());
    auto toolBarNode = FrameNode::CreateFrameNode("toolBar", 44, AceType::MakeRefPtr<ButtonPattern>());

    auto buttonNode = FrameNode::CreateFrameNode("BackButton", 55, AceType::MakeRefPtr<ButtonPattern>());
    auto backButtonImageNode = FrameNode::CreateFrameNode("Image", 66, AceType::MakeRefPtr<ImagePattern>());

    navBar->AddChild(titleBarNode);
    auto pattern = titleBarNode->GetPattern<TitleBarPattern>();
    titleBarNode->backButton_ = buttonNode;
    titleBarNode->AddChild(titleBarNode->GetBackButton());
    titleBarNode->title_ = title;

    ASSERT_TRUE(buttonNode->children_.empty());
    backButtonImageNode->MountToParent(buttonNode);
    backButtonImageNode->MarkModifyDone();
    buttonNode->MarkModifyDone();
    /**
     * @tc.steps: step2. set properties then call pattern->OnModifyDone();.
     * @tc.expected: check whether the properties is correct.
     */
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleBarParentType_ =
        TitleBarParentType::NAV_DESTINATION;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleMode_ = NavigationTitleMode::MINI;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propHideBackButton_ = std::nullopt;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propNoPixMap_ = true;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propImageSource_ = ImageSourceInfo();
    pattern->OnModifyDone();
    ASSERT_NE(titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleBarParentType_.value(),
        TitleBarParentType::NAVBAR);

    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propImageSource_ = std::nullopt;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propHideBackButton_ = false;
    pattern->OnModifyDone();

    auto mockPixelMap = AceType::MakeRefPtr<MockPixelMap>();
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propPixelMap_ = mockPixelMap;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propHideBackButton_ = true;
    titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>()->propTitleBarParentType_ = TitleBarParentType::NAVBAR;
    navBar->GetLayoutProperty<NavBarLayoutProperty>()->propHideBackButton_ = true;
    pattern->OnModifyDone();
    EXPECT_EQ(buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->propVisibility_.value(), VisibleType::GONE);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::MakeRefPtr<NavBarLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(titleBarNode)), geometryNode, layoutProperty);
    DirtySwapConfig config;
    auto algorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithm;
    /**
     * @tc.steps: step1. call pattern->OnDirtyLayoutWrapperSwap();.
     * @tc.expected: check whether the res is correct.
     */
    config.skipMeasure = true;
    config.skipLayout = true;
    auto res = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_FALSE(res);
    config.skipMeasure = true;
    config.skipLayout = false;
    res = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_FALSE(res);
}

/**
 * @tc.name: NavrouterTestNg0034
 * @tc.desc: Test TitleBarLayoutAlgorithm::Measure.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, NavrouterTestNg0034, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0035, TestSize.Level1)
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
    titleLayoutProperty->propContent_ = "content";
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0036, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0037, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create BarItemNode.
     * @tc.expected: check whether the properties is correct.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>("BarItemNode", 1);
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create BarItemNode.
     */
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>("BarItemNode", 1);
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create BarItemNode.
     */
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>("BarItemNode", 1);
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0041, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0042, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0043, TestSize.Level1)
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
    temp->propContent_ = "content";
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0044, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0045, TestSize.Level1)
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
HWTEST_F(NavrouterTestNg, NavrouterTestNg0046, TestSize.Level1)
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
 * @tc.name: UpdateNameIfNeeded001
 * @tc.desc: Test UpdateNameIfNeede and enter pathInfo.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateNameIfNeeded001, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));
    EXPECT_TRUE(navDestinationPattern->name_.empty());

    // Make GetNavPathInfo return not NULL.
    auto context = AceType::MakeRefPtr<NG::NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>();
    context->SetNavPathInfo(navPathInfo);
    navDestinationPattern->SetNavDestinationContext(context);

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    EXPECT_NE(navDestinationPattern->GetNavPathInfo(), nullptr);
    navDestinationPattern->UpdateNameIfNeeded(hostNode);
}

/**
 * @tc.name: UpdateBackgroundColorIfNeeded001
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and enter GetNavDestinationMode returning DIALOG.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateBackgroundColorIfNeeded001, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make GetBackgroundColor->has_value return true.
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto renderContext = hostNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_FALSE(renderContext->GetBackgroundColor().has_value());

    // Make GetNavDestinationMode return DIALOG.
    hostNode->SetNavDestinationMode(NavDestinationMode::DIALOG);
    EXPECT_EQ(hostNode->GetNavDestinationMode(), NavDestinationMode::DIALOG);
    navDestinationPattern->UpdateBackgroundColorIfNeeded(hostNode);
}

/**
 * @tc.name: UpdateTitlebarVisibility001
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateTitlebarVisibility001, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    // Make titleBarNode not NULL
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    // Make opts return false
    hostNode->titleBarNode_ = titleBarNode;
    hostNode->GetLayoutProperty()->safeAreaExpandOpts_ = nullptr;

    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    auto hostTitleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    ASSERT_NE(hostTitleBarNode, nullptr);
    EXPECT_NE(hostTitleBarNode->GetLayoutProperty<TitleBarLayoutProperty>(), nullptr);
    EXPECT_EQ(hostNode->GetLayoutProperty()->GetSafeAreaExpandOpts(), nullptr);
    // There is a second branch in UpdateTitlebarVisibility
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBar().value_or(false));
    navDestinationPattern->UpdateTitlebarVisibility(hostNode);
}

/**
 * @tc.name: UpdateTitlebarVisibility002
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts return true and Expansive return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateTitlebarVisibility002, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    // Make titleBarNode not NULL
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    hostNode->titleBarNode_ = titleBarNode;
    // Make opts return true
    SafeAreaExpandOpts opts;
    hostNode->GetLayoutProperty()->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>(opts);

    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    auto hostTitleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    ASSERT_NE(hostTitleBarNode, nullptr);
    EXPECT_NE(hostTitleBarNode->GetLayoutProperty<TitleBarLayoutProperty>(), nullptr);
    auto&& hostOpts = hostNode->GetLayoutProperty()->GetSafeAreaExpandOpts();
    ASSERT_NE(hostOpts, nullptr);
    EXPECT_FALSE(hostOpts->Expansive());
    // There is a second branch in UpdateTitlebarVisibility
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBar().value_or(false));
    navDestinationPattern->UpdateTitlebarVisibility(hostNode);
}

/**
 * @tc.name: UpdateTitlebarVisibility003
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts and Expansive return true
 *           and navDestinationContentNode return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateTitlebarVisibility003, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    // Make titleBarNode not NULL
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    hostNode->titleBarNode_ = titleBarNode;
    // Make opts and Expansive return true
    SafeAreaExpandOpts opts;
    opts.type = SAFE_AREA_TYPE_SYSTEM;
    opts.edges = SAFE_AREA_EDGE_TOP;
    hostNode->GetLayoutProperty()->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>(opts);
    // Make navDestinationContentNode return false
    hostNode->contentNode_ = nullptr;

    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    auto hostTitleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    ASSERT_NE(hostTitleBarNode, nullptr);
    EXPECT_NE(hostTitleBarNode->GetLayoutProperty<TitleBarLayoutProperty>(), nullptr);
    auto&& hostOpts = hostNode->GetLayoutProperty()->GetSafeAreaExpandOpts();
    ASSERT_NE(hostOpts, nullptr);
    EXPECT_TRUE(hostOpts->Expansive());
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(hostNode->GetContentNode()), nullptr);
    // There is a second branch in UpdateTitlebarVisibility
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBar().value_or(false));
    navDestinationPattern->UpdateTitlebarVisibility(hostNode);
}

/**
 * @tc.name: UpdateTitlebarVisibility004
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts and Expansive return true
 *           and navDestinationContentNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateTitlebarVisibility004, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    // Make titleBarNode not NULL
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    hostNode->titleBarNode_ = titleBarNode;
    // Make opts and Expansive return true
    SafeAreaExpandOpts opts;
    opts.type = SAFE_AREA_TYPE_SYSTEM;
    opts.edges = SAFE_AREA_EDGE_TOP;
    hostNode->GetLayoutProperty()->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>(opts);
    // Make navDestinationContentNode return true
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
    hostNode->SetContentNode(navigationContentNode);

    EXPECT_NE(hostNode->GetLayoutProperty<NavDestinationLayoutProperty>(), nullptr);
    auto hostTitleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    ASSERT_NE(hostTitleBarNode, nullptr);
    EXPECT_NE(hostTitleBarNode->GetLayoutProperty<TitleBarLayoutProperty>(), nullptr);
    auto&& hostOpts = hostNode->GetLayoutProperty()->GetSafeAreaExpandOpts();
    ASSERT_NE(hostOpts, nullptr);
    EXPECT_TRUE(hostOpts->Expansive());
    EXPECT_NE(AceType::DynamicCast<FrameNode>(hostNode->GetContentNode()), nullptr);
    navDestinationPattern->UpdateTitlebarVisibility(hostNode);
}

/**
 * @tc.name: UpdateTitlebarVisibility005
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make GetIndex return 0.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, UpdateTitlebarVisibility005, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make GetIndex return 0
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    hostNode->index_ = 0;
    EXPECT_EQ(hostNode->GetIndex(), 0);
    navDestinationPattern->UpdateTitlebarVisibility(hostNode);
}

/**
 * @tc.name: GetBackButtonState001
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make GetHideTitleBarValue return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState001, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make GetHideTitleBarValue return true
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    navDestinationLayoutProperty->propHideTitleBar_ = true;

    EXPECT_TRUE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: GetBackButtonState002
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make parent return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState002, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make parent return false
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);

    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(hostNode->GetParent()), nullptr);
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: GetBackButtonState003
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make parent and IsRootNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState003, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make parent and IsRootNode return true
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    ASSERT_NE(navRouterNode, nullptr);
    navRouterNode->isRoot_ = true;
    navDestinationNode->parent_ = navRouterNode;

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    ASSERT_NE(parent, nullptr);
    EXPECT_TRUE(parent->IsRootNode());
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: GetBackButtonState004
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make parent return true and IsRootNode
 *           and navigationNode return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState004, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make parent return true and IsRootNode return false
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    ASSERT_NE(navRouterNode, nullptr);
    navRouterNode->isRoot_ = false;
    navDestinationNode->parent_ = navRouterNode;

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    ASSERT_NE(parent, nullptr);
    EXPECT_FALSE(parent->IsRootNode());
    // Make navigationNode return false
    EXPECT_EQ(AceType::DynamicCast<NavigationGroupNode>(parent), nullptr);
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: GetBackButtonState005
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make the logic as follows:
 *               parent is true
 *               IsRootNode return false
 *               navigationNode is true
 *               index is not 0
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState005, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr) << "2797";
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    ASSERT_NE(navDestinationNode, nullptr) << "2799";
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make parent return true and IsRootNode return false
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationNode->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    navigationNode->isRoot_ = false;
    navDestinationNode->parent_ = navigationNode;
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    ASSERT_NE(parent, nullptr);
    EXPECT_FALSE(parent->IsRootNode());
    // Make sure navigationNode return true
    RefPtr<NavigationGroupNode> navigationNodeTest = AceType::DynamicCast<NavigationGroupNode>(parent);
    ASSERT_NE(navigationNodeTest, nullptr);
    // Make sure index is not 0
    auto patternTest = navigationNodeTest->GetPattern<NavigationPattern>();
    ASSERT_NE(patternTest, nullptr);
    auto stackTest = patternTest->GetNavigationStack();
    ASSERT_NE(stackTest, nullptr);
    EXPECT_NE(stackTest->FindIndex(navDestinationPattern->name_, navDestinationPattern->customNode_, true), 0);
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: GetBackButtonState006
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make the logic as follows:
 *               parent is true
 *               IsRootNode return false
 *               navigationNode is true
 *               index is 0
 *               GetNavigationMode return not SPLIT
 *               GetHideNavBarValue return false
 *               isCustomTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState006, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make parent return true and IsRootNode return false
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    //  Make index 0
    navDestinationPattern->name_ = "Page01";
    navDestinationPattern->customNode_ = navDestinationNode;
    auto routeInfo = AceType::MakeRefPtr<RouteInfo>();
    navigationStack->Add(
        "Page01", navDestinationNode, NavRouteMode::PUSH, routeInfo);
    navigationNode->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    // Make GetNavigationMode return not SPLIT
    navigationNode->GetPattern<NavigationPattern>()->navigationMode_ = NavigationMode::AUTO;
    // Make GetHideNavBarValue return false
    navigationNode->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = false;
    navigationNode->isRoot_ = false;
    navDestinationNode->parent_ = navigationNode;
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleNode = FrameNode::CreateFrameNode("menuNode", 2, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(titleNode, nullptr);
    titleBarNode->title_ = titleNode;
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make isCustomTitle false
    navDestinationNode->propPrevTitleIsCustom_ = false;

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    ASSERT_FALSE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    ASSERT_NE(parent, nullptr);
    ASSERT_FALSE(parent->IsRootNode());
    // Make sure navigationNode return true
    RefPtr<NavigationGroupNode> navigationNodeTest = AceType::DynamicCast<NavigationGroupNode>(parent);
    ASSERT_NE(navigationNodeTest, nullptr);
    // Make sure index is 0
    auto patternTest = navigationNodeTest->GetPattern<NavigationPattern>();
    ASSERT_NE(patternTest, nullptr);
    auto stackTest = patternTest->GetNavigationStack();
    ASSERT_NE(stackTest, nullptr);
    EXPECT_EQ(stackTest->FindIndex(navDestinationPattern->name_, navDestinationPattern->customNode_, true), 0);
    // Make sure GetNavigationMode return not SPLIT
    EXPECT_NE(patternTest->GetNavigationMode(), NavigationMode::SPLIT);
    auto navigationLayoutProperty = navigationNodeTest->GetLayoutProperty<NavigationLayoutProperty>();
    // Make sure GetHideNavBarValue return false
    EXPECT_FALSE(navigationLayoutProperty->GetHideNavBarValue(false));
    // Make sure isCustomTitle false
    EXPECT_FALSE(hostNode->GetPrevTitleIsCustomValue(false));
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: GetBackButtonState007
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make the logic as follows:
 *               parent is true
 *               IsRootNode return false
 *               navigationNode is true
 *               index is 0
 *               GetNavigationMode return SPLIT
 *               GetHideNavBarValue return true
 *               isCustomTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetBackButtonState007, TestSize.Level1)
{
    // Create NavDestinationGroupNode to make GetHost return not NULL.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    // Make parent return true and IsRootNode return false
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "parentNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    //  Make index 0
    navDestinationPattern->name_ = "Page01";
    navDestinationPattern->customNode_ = navDestinationNode;
    auto routeInfo = AceType::MakeRefPtr<RouteInfo>();
    navigationStack->Add(
        "Page01", navDestinationNode, NavRouteMode::PUSH, routeInfo);
    navigationNode->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    // Make GetNavigationMode return SPLIT
    navigationNode->GetPattern<NavigationPattern>()->navigationMode_ = NavigationMode::SPLIT;
    // Make GetHideNavBarValue return true
    navigationNode->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = true;
    navigationNode->isRoot_ = false;
    navDestinationNode->parent_ = navigationNode;
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    // Make isCustomTitle true
    navDestinationNode->propPrevTitleIsCustom_ = true;

    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(navDestinationPattern->GetHost());
    ASSERT_NE(hostNode, nullptr);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBarValue(false));
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    ASSERT_NE(parent, nullptr);
    EXPECT_FALSE(parent->IsRootNode());
    // Make sure navigationNode return true
    RefPtr<NavigationGroupNode> navigationNodeTest = AceType::DynamicCast<NavigationGroupNode>(parent);
    ASSERT_NE(navigationNodeTest, nullptr);
    // Make sure index is 0
    auto patternTest = navigationNodeTest->GetPattern<NavigationPattern>();
    ASSERT_NE(patternTest, nullptr);
    auto stackTest = patternTest->GetNavigationStack();
    ASSERT_NE(stackTest, nullptr);
    EXPECT_EQ(stackTest->FindIndex(navDestinationPattern->name_, navDestinationPattern->customNode_, true), 0);
    // Make sure GetNavigationMode return SPLIT
    EXPECT_EQ(patternTest->GetNavigationMode(), NavigationMode::SPLIT);
    auto navigationLayoutProperty = navigationNodeTest->GetLayoutProperty<NavigationLayoutProperty>();
    // Make sure GetHideNavBarValue return true
    EXPECT_TRUE(navigationLayoutProperty->GetHideNavBarValue(false));
    // Make sure isCustomTitle true
    EXPECT_TRUE(hostNode->GetPrevTitleIsCustomValue(false));
    navDestinationPattern->GetBackButtonState();
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree and make node return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    // Make node return false.
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);

    ASSERT_EQ(AceType::DynamicCast<UINode>(navDestinationPattern->GetHost()), nullptr);
    navDestinationPattern->OnAttachToMainTree();
}

/**
 * @tc.name: OnAttachToMainTree002
 * @tc.desc: Test OnAttachToMainTree and make node and GetTag return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, OnAttachToMainTree002, TestSize.Level1)
{
    // Make node return true.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    RefPtr<UINode> node = AceType::DynamicCast<UINode>(navDestinationPattern->GetHost());
    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->GetTag(), V2::NAVIGATION_VIEW_ETS_TAG);
    navDestinationPattern->OnAttachToMainTree();
}

/**
 * @tc.name: OnAttachToMainTree003
 * @tc.desc: Test OnAttachToMainTree and make node and GetTag return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, OnAttachToMainTree003, TestSize.Level1)
{
    // Make node return true.
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>(
        "navDestinationNode", 11, AceType::MakeRefPtr<NavDestinationPattern>());
    ASSERT_NE(navDestinationNode, nullptr);
    navDestinationNode->tag_ = V2::NAVIGATION_VIEW_ETS_TAG;
    auto navDestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>();
    navDestinationPattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(navDestinationNode));

    RefPtr<UINode> node = AceType::DynamicCast<UINode>(navDestinationPattern->GetHost());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::NAVIGATION_VIEW_ETS_TAG);
    navDestinationPattern->OnAttachToMainTree();
}

/**
 * @tc.name: ParseCommonTitle001
 * @tc.desc: Test NavrouterTestNg and cover all conditions of hasSubTitle and hasMainTitle
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, ParseCommonTitle001, TestSize.Level1)
{
    NavDestinationModelNG navDestinationModel;
    bool hasSubTitle = true, hasMainTitle = true;
    EXPECT_FALSE(!hasSubTitle && !hasMainTitle);
    navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");

    hasSubTitle = false;
    EXPECT_FALSE(!hasSubTitle && !hasMainTitle);
    navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");

    hasMainTitle = false;
    EXPECT_TRUE(!hasSubTitle && !hasMainTitle);
    navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
}

/**
 * @tc.name: ParseCommonTitle002
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return false
 *               hasMainTitle is false
 *               !hasSubTitle is false
 *               subTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, ParseCommonTitle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    bool hasSubTitle = true, hasMainTitle = false;
    EXPECT_FALSE(!hasSubTitle);
    EXPECT_FALSE(hasMainTitle);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto titleBarNodeTest = AceType::DynamicCast<TitleBarNode>(navDestinationNodeTest->GetTitleBarNode());
    ASSERT_NE(titleBarNodeTest, nullptr);
    // Make sure GetPrevTitleIsCustomValue return false
    EXPECT_FALSE(navDestinationNodeTest->GetPrevTitleIsCustomValue(false));
    ASSERT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    bool ret = navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ParseCommonTitle003
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               HasTitleHeight return false
 *               hasMainTitle is true
 *               mainTitle is false
 *               !hasSubTitle is false
 *               subTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, ParseCommonTitle003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    bool hasSubTitle = true, hasMainTitle = true;
    EXPECT_FALSE(!hasSubTitle);
    EXPECT_TRUE(hasMainTitle);
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
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    bool ret = navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ParseCommonTitle004
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               HasTitleHeight return true
 *               hasMainTitle is true
 *               mainTitle is true
 *               !hasSubTitle is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, ParseCommonTitle004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    bool hasSubTitle = false, hasMainTitle = true;
    EXPECT_TRUE(!hasSubTitle);
    EXPECT_TRUE(hasMainTitle);
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
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
    bool ret = navDestinationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "");
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: Create001
 * @tc.desc: Test NavrouterTestNg and make navDestinationNode false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, Create001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());

    NavDestinationModelNG navDestinationModel;
    bool deepRenderCalled = false;
    auto deepRenderFunc = [&deepRenderCalled]() { deepRenderCalled = true; };
    navDestinationModel.Create(std::move(deepRenderFunc), AceType::MakeRefPtr<NavDestinationContext>());
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navDestinationNode, nullptr);
    // Make navDestinationNode false
    int32_t originNodeId = navDestinationNode->nodeId_;
    navDestinationNode->nodeId_ = originNodeId + 1;

    // Make sure navDestinationNodeTest is false
    auto parent = AceType::DynamicCast<UINode>(
        FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, navDestinationNode->nodeId_));
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(parent), nullptr);
    // Prepare for calling the deepRender defined in NavDestinationModelNG::Create()
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    ASSERT_NE(shallowBuilder, nullptr);
    EXPECT_FALSE(shallowBuilder->IsExecuteDeepRenderDone());
    shallowBuilder->ExecuteDeepRender();
    EXPECT_TRUE(deepRenderCalled);
}

/**
 * @tc.name: Create002
 * @tc.desc: Test NavrouterTestNg and make navDestinationNode true and GetContentNode return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, Create002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());

    NavDestinationModelNG navDestinationModel;
    bool deepRenderCalled = false;
    auto deepRenderFunc = [&deepRenderCalled]() { deepRenderCalled = true; };
    navDestinationModel.Create(std::move(deepRenderFunc), AceType::MakeRefPtr<NavDestinationContext>());
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navDestinationNode, nullptr);
    // Make GetContentNode return false
    navDestinationNode->contentNode_ = nullptr;

    // Make sure navDestinationNodeTest is true
    auto parent = AceType::DynamicCast<UINode>(
        FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, navDestinationNode->nodeId_));
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    EXPECT_EQ(navDestinationNodeTest->GetContentNode(), nullptr);
    // Prepare for calling the deepRender defined in NavDestinationModelNG::Create()
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    ASSERT_NE(shallowBuilder, nullptr);
    EXPECT_FALSE(shallowBuilder->IsExecuteDeepRenderDone());
    shallowBuilder->ExecuteDeepRender();
    EXPECT_TRUE(deepRenderCalled);
}

/**
 * @tc.name: Create003
 * @tc.desc: Test NavrouterTestNg and make navDestinationNode true and GetContentNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, Create003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());
    
    NavDestinationModelNG navDestinationModel;
    bool deepRenderCalled = false;
    auto deepRenderFunc = [&deepRenderCalled]() { deepRenderCalled = true; };
    navDestinationModel.Create(std::move(deepRenderFunc), AceType::MakeRefPtr<NavDestinationContext>());
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navDestinationNode, nullptr);

    // Make sure navDestinationNodeTest is true
    auto parent = AceType::DynamicCast<UINode>(
        FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, navDestinationNode->nodeId_));
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(parent);
    ASSERT_NE(navDestinationNodeTest, nullptr);
    EXPECT_NE(navDestinationNodeTest->GetContentNode(), nullptr);
    // Prepare for calling the deepRender defined in NavDestinationModelNG::Create()
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto shallowBuilder = navDestinationPattern->GetShallowBuilder();
    ASSERT_NE(shallowBuilder, nullptr);
    EXPECT_FALSE(shallowBuilder->IsExecuteDeepRenderDone());
    shallowBuilder->ExecuteDeepRender();
    EXPECT_TRUE(deepRenderCalled);
}

/**
 * @tc.name: SetCustomTitle001
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return false
 *               currentTitle is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, SetCustomTitle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    navDestinationModel.SetCustomTitle(customNode);
}

/**
 * @tc.name: SetCustomTitle002
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               currentTitle is true
 *               GetId is not GetId
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, SetCustomTitle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    navDestinationModel.SetCustomTitle(customNode);
}

/**
 * @tc.name: SetCustomTitle003
 * @tc.desc: Test NavrouterTestNg and make the logic as follows:
 *               GetPrevTitleIsCustomValue return true
 *               currentTitle is true
 *               GetId is GetId
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, SetCustomTitle003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    navDestinationModel.SetCustomTitle(title);
}

/**
 * @tc.name: SetTitleHeight001
 * @tc.desc: Test NavrouterTestNg and cover all conditions of isValid.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, SetTitleHeight001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationGroupNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    // Make sure isValid is true
    bool isValid = true;
    EXPECT_TRUE(isValid);
    navDestinationModel.SetTitleHeight(NG::DOUBLE_LINE_TITLEBAR_HEIGHT, isValid);
    // Make sure isValid is false
    isValid = false;
    EXPECT_FALSE(isValid);
    navDestinationModel.SetTitleHeight(NG::DOUBLE_LINE_TITLEBAR_HEIGHT, isValid);
}

/**
 * @tc.name: SetMenuItems001
 * @tc.desc: Test SetMenuItems function.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, SetMenuItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    MockPipelineContextGetTheme();
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
    titleBarNode->UpdatePrevMenuIsCustom(true);
    navDestinationModel.SetMenuItems(std::move(barItems));
    EXPECT_FALSE(titleBarNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);

    /**
     * @tc.steps: step3. Call SetMenuItems when UpdatePrevMenuIsCustom is false.
     * and titleBarNode has no menu
     */
    titleBarNode->UpdatePrevMenuIsCustom(false);
    navDestinationModel.SetMenuItems(std::move(barItems));
    EXPECT_FALSE(titleBarNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetMenuNodeOperationValue(), ChildNodeOperation::ADD);

    /**
     * @tc.steps: step4. Call SetMenuItems when UpdatePrevMenuIsCustom is false
     * and titleBarNode has menu
     */
    titleBarNode->UpdatePrevMenuIsCustom(false);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(TITLE_BAR_NODE_MENU, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    titleBarNode->SetMenu(menuNode);
    navDestinationModel.SetMenuItems(std::move(barItems));
    EXPECT_FALSE(titleBarNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: SetCustomMenu001
 * @tc.desc: Test SetCustomMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, SetCustomMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize parameters.
     */
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationGroupNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    RefPtr<AceType> customNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(customNode, nullptr);

    /**
     * @tc.steps: step2. Call SetCustomMenu when previous node is not custom.
     */
    navDestinationModel.SetCustomMenu(customNode);
    EXPECT_TRUE(titleBarNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetMenuNodeOperationValue(), ChildNodeOperation::ADD);

    auto menuNode = AceType::MakeRefPtr<FrameNode>(TITLE_BAR_NODE_MENU, 33, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    titleBarNode->SetMenu(menuNode);

    /**
     * @tc.steps: step3. Call SetMenuItems when previous menu exists.
     */
    titleBarNode->SetMenu(menuNode);
    navDestinationModel.SetCustomMenu(customNode);
    EXPECT_TRUE(titleBarNode->GetPrevMenuIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetMenuNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: ProcessShallowBuilder001
 * @tc.desc: Test NavrouterTestNg and make isCacheNode_ true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, ProcessShallowBuilder001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->isCacheNode_ = true;
    
    EXPECT_TRUE(navDestinationNode->isCacheNode_);
    navDestinationNode->ProcessShallowBuilder();
}

/**
 * @tc.name: GetNavDestinationCustomNode001
 * @tc.desc: Test NavrouterTestNg and make child false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetNavDestinationCustomNode001, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto customNode = FrameNode::CreateFrameNode("Title", 99, AceType::MakeRefPtr<CustomNodePattern>());
    navDestinationPattern->customNode_ = customNode;

    EXPECT_NE(navDestinationPattern->GetCustomNode(), nullptr);
    EXPECT_EQ(navDestinationNode->GetFirstChild(), nullptr);
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: GetNavDestinationCustomNode002
 * @tc.desc: Test NavrouterTestNg and make child true and two InstanceOfs false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetNavDestinationCustomNode002, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    // Make child true
    auto customNode = FrameNode::CreateFrameNode("Custom", 99, AceType::MakeRefPtr<CustomNodePattern>());
    navDestinationNode->children_.emplace_back(customNode);
    navDestinationPattern->customNode_ = navDestinationNode;

    auto navDestinationNodeTest = navDestinationPattern->GetCustomNode();
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto child = navDestinationNodeTest->GetFirstChild();
    EXPECT_NE(child, nullptr);
    EXPECT_FALSE(AceType::InstanceOf<NavDestinationGroupNode>(child));
    EXPECT_FALSE(AceType::InstanceOf<CustomNodeBase>(child));
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: GetNavDestinationCustomNode003
 * @tc.desc: Test NavrouterTestNg and make child true and the first InstanceOf true
 *               and the second InstanceOf false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetNavDestinationCustomNode003, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    // Make child true and InstanceOf<NavDestinationGroupNode> true
    auto navDestinationChildNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        102, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->children_.emplace_front(navDestinationChildNode);
    navDestinationPattern->customNode_ = navDestinationNode;

    auto navDestinationNodeTest = navDestinationPattern->GetCustomNode();
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto child = navDestinationNodeTest->GetFirstChild();
    EXPECT_NE(child, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<NavDestinationGroupNode>(child));
    EXPECT_FALSE(AceType::InstanceOf<CustomNodeBase>(child));
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: GetNavDestinationCustomNode004
 * @tc.desc: Test NavrouterTestNg and make child true and the first InstanceOf false
 *               and the second InstanceOf true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, GetNavDestinationCustomNode004, TestSize.Level1)
{
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    // Make child true and InstanceOf<NavDestinationGroupNode> true
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(201, "Custom");
    navDestinationNode->children_.emplace_front(customNode);
    navDestinationPattern->customNode_ = navDestinationNode;

    auto navDestinationNodeTest = navDestinationPattern->GetCustomNode();
    ASSERT_NE(navDestinationNodeTest, nullptr);
    auto child = navDestinationNodeTest->GetFirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_FALSE(AceType::InstanceOf<NavDestinationGroupNode>(child));
    EXPECT_TRUE(AceType::InstanceOf<CustomNodeBase>(child));
    navDestinationNode->GetNavDestinationCustomNode();
}

/**
 * @tc.name: MeasureContentChild001
 * @tc.desc: Test NavrouterTestNg and cover all conditions of IsAutoHeight.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, MeasureContentChild001, TestSize.Level1)
{
    auto algorithm = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    auto pattern = AceType::MakeRefPtr<NavDestinationPattern>();
    // Make hostNode not NULL
    auto navDestinationNode = AceType::MakeRefPtr<NavDestinationGroupNode>("navDestinationNode", 11, pattern);
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->titleBarNode_ = titleBarNode;
    navDestinationNode->children_.push_back(titleBarNode);
    // Make contentNode not NULL
    navDestinationNode->contentNode_ = titleBarNode;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    // Make navDestinationLayoutProperty not NULL
    auto navDestinationLayoutProperty = AceType::MakeRefPtr<NavDestinationLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.width_ = 20.0f;
    constraint.selfIdealSize.height_ = 30.0f;
    // Make constraint not NULL
    navDestinationLayoutProperty->layoutConstraint_ = constraint;
    navDestinationLayoutProperty->contentConstraint_ = constraint;

    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(
        AceType::WeakClaim(AceType::RawPtr(navDestinationNode)), geometryNode, navDestinationLayoutProperty);
    RefPtr<LayoutWrapperNode> titleBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(titleBarNode, geometryNode, titleBarNode->GetLayoutProperty());
    layoutWrapper->currentChildCount_ = 0;
    layoutWrapper->childrenMap_.try_emplace(layoutWrapper->currentChildCount_++, titleBarLayoutWrapper);
    // Make sure IsAutoHeight is false
    auto contentNode = navDestinationNode->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto index = navDestinationNode->GetChildIndexById(contentNode->GetId());
    EXPECT_TRUE(layoutWrapper->GetOrCreateChildByIndex(index));
    EXPECT_FALSE(NavigationLayoutAlgorithm::IsAutoHeight(navDestinationLayoutProperty));
    algorithm->Measure(layoutWrapper);

    // Make IsAutoHeight true
    navDestinationLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto& calcLayoutConstraint = navDestinationLayoutProperty->GetCalcLayoutConstraint();
    ASSERT_NE(calcLayoutConstraint, nullptr);
    auto calcSize = CalcSize();
    calcSize.height_ = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = calcSize;
    // Make sure IsAutoHeight is true
    EXPECT_TRUE(NavigationLayoutAlgorithm::IsAutoHeight(navDestinationLayoutProperty));
    algorithm->Measure(layoutWrapper);
}

/*
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test NavrouterTestNg and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });

    // Make sure navDestinationNode_ is false
    EXPECT_EQ(navRouterNode->navDestinationNode_, nullptr);
    navRouterNode->OnDetachFromMainTree(false);

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;

    EXPECT_NE(navRouterNode->navDestinationNode_, nullptr);
    // Make sure Upgrade return false
    EXPECT_EQ(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    navRouterNode->OnDetachFromMainTree(false);

    // Make Upgrade return true
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);

    EXPECT_NE(navRouterNode->navDestinationNode_, nullptr);
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_EQ(navigationPattern->GetNavigationStack(), nullptr);
    // Make sure stack is false
    navRouterNode->OnDetachFromMainTree(false);

    // Make stack true
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    
    EXPECT_NE(navRouterNode->navDestinationNode_, nullptr);
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    EXPECT_NE(navigationPattern->GetNavigationStack(), nullptr);
    navRouterNode->OnDetachFromMainTree(false);
}

/*
 * @tc.name: AddNavDestinationToNavigation001
 * @tc.desc: Test AddNavDestinationToNavigation and cover all conditions of
 *               GetNavigationMode and GetNavigationStackProvided.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, AddNavDestinationToNavigation001, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make GetNavigationMode not NavigationMode::SPLIT
    navigationPattern->navigationMode_ = NavigationMode::AUTO;

    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode()), nullptr);
    EXPECT_NE(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    navRouterNode->AddNavDestinationToNavigation();

    // Make GetNavigationMode NavigationMode::SPLIT
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    // Make GetNavigationStackProvided return true
    navigationPattern->navigationStackProvided_ = true;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    EXPECT_FALSE(!navigationPattern->GetNavigationStackProvided());
    navRouterNode->AddNavDestinationToNavigation();

    // Make GetNavigationStackProvided return false
    navigationPattern->navigationStackProvided_ = false;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    EXPECT_TRUE(!navigationPattern->GetNavigationStackProvided());
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation002
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, AddNavDestinationToNavigation002, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    // Make sure navDestination is false
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode()), nullptr);
    // Make sure routeInfo is false
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    auto routeInfo = navRouterPattern->GetRouteInfo();
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation003
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is true
 *               shallowBuilder is false
 *               destinationContent is false
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, AddNavDestinationToNavigation003, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make navDestination true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;
    
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    EXPECT_NE(currentNavDestination, navDestinationNodeTest);
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    // Make sure shallowBuilder is false
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    EXPECT_EQ(navDestinationPattern->GetShallowBuilder(), nullptr);
    // Make sure destinationContent is false
    EXPECT_EQ(navDestinationNode->GetContentNode(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation004
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is true
 *               shallowBuilder is true
 *               navRouteMode is NavRouteMode::PUSH
 *               destinationContent is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, AddNavDestinationToNavigation004, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make navDestination true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;
    // Make shallowBuilder true
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    auto deepRender = []() -> RefPtr<UINode> {
        return ViewStackProcessor::GetInstance()->Finish();
    };
    navDestinationPattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender));
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    // Make navRouteMode NavRouteMode::PUSH
    navRouterPattern->mode_ = NavRouteMode::PUSH;
    // Make destinationContent true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->contentNode_ = titleBarNode;
    
    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    EXPECT_NE(currentNavDestination, navDestinationNodeTest);
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    // Make sure shallowBuilder is true
    EXPECT_NE(navDestinationPattern->GetShallowBuilder(), nullptr);
    // Make sure navRouteMode is NavRouteMode::PUSH
    EXPECT_EQ(navRouterPattern->GetNavRouteMode(), NavRouteMode::PUSH);
    // Make sure destinationContent is true
    EXPECT_NE(navDestinationNode->GetContentNode(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}

/*
 * @tc.name: AddNavDestinationToNavigation005
 * @tc.desc: Test AddNavDestinationToNavigation and make the logic as follows:
 *               routeInfo is false
 *               navDestination is true
 *               shallowBuilder is true
 *               navRouteMode is not NavRouteMode::PUSH
 *               destinationContent is true
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterTestNg, AddNavDestinationToNavigation005, TestSize.Level1)
{
    auto navRouterNode = NavRouterGroupNode::GetOrCreateGroupNode(
        "navRouterNode", 11, []() { return AceType::MakeRefPtr<NavRouterPattern>(); });
    // Make navigationNode not NULL
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navRouterNode->weakNavigation_ = WeakPtr<NavigationGroupNode>(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    // Make navDestination true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navRouterNode->navDestinationNode_ = navDestinationNode;
    // Make shallowBuilder true
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    auto deepRender = []() -> RefPtr<UINode> {
        return ViewStackProcessor::GetInstance()->Finish();
    };
    navDestinationPattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender));
    // Make destinationContent true
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    navDestinationNode->contentNode_ = titleBarNode;

    EXPECT_NE(navRouterNode->weakNavigation_.Upgrade(), nullptr);
    auto navDestinationNodeTest = AceType::DynamicCast<NavDestinationGroupNode>(navRouterNode->GetNavDestinationNode());
    auto currentNavDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(navigationPattern->GetNavDestinationNode());
    EXPECT_NE(currentNavDestination, navDestinationNodeTest);
    auto navRouterPattern = navRouterNode->GetPattern<NavRouterPattern>();
    EXPECT_EQ(navRouterPattern->GetRouteInfo(), nullptr);
    // Make sure shallowBuilder is true
    EXPECT_NE(navDestinationPattern->GetShallowBuilder(), nullptr);
    // Make sure navRouteMode is not NavRouteMode::PUSH
    EXPECT_NE(navRouterPattern->GetNavRouteMode(), NavRouteMode::PUSH);
    // Make sure destinationContent is true
    EXPECT_NE(navDestinationNode->GetContentNode(), nullptr);
    navRouterNode->AddNavDestinationToNavigation();
}
} // namespace OHOS::Ace::NG
