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
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class NavrouterGroupTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
};

void NavrouterGroupTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}
void NavrouterGroupTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void NavrouterGroupTestNg::SetUp() {}
void NavrouterGroupTestNg::TearDown() {}

void NavrouterGroupTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: NavrouterTestNg001
 * @tc.desc: Test NavRouterGroupNode::AddChildToGroup.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg001, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg002, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg003, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg004, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg006, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg007, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg008, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg009, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg0010, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg0011, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg0015, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, NavrouterTestNg0016, TestSize.Level1)
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
    navRouterGroupNode->GetOrCreateEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    EXPECT_EQ(layoutProperty->GetNavigationModeValue(NavigationMode::AUTO), NavigationMode::AUTO);
    layoutProperty->propNavigationMode_ = NavigationMode::STACK;
    navRouterGroupNode->OnAttachToMainTree(false);
    auto preNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 55, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNavDestination->titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 33, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    std::pair<std::string, RefPtr<UINode>> p("test", preNavDestination);
    stack->navPathList_.push_back(p);
    navRouterGroupNode->GetOrCreateEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();

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
    navRouterGroupNode->GetOrCreateEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);

    navRouterGroupNode->OnAttachToMainTree(false);
    navRouterGroupNode->GetOrCreateEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
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
    navRouterGroupNode->GetOrCreateEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
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
    navRouterGroupNode->GetOrCreateEventHub<NavRouterEventHub>()->FireDestinationChangeEvent();
    ASSERT_NE(navRouterGroupNode->navDestinationNode_, nullptr);
}

/**
 * @tc.name: UpdateNameIfNeeded001
 * @tc.desc: Test UpdateNameIfNeede and enter pathInfo.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, UpdateNameIfNeeded001, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, UpdateBackgroundColorIfNeeded001, TestSize.Level1)
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
 * @tc.name: MountTitleBar001
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, MountTitleBar001, TestSize.Level1)
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
    // There is a second branch in MountTitleBar
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBar().value_or(false));
    bool needRunTitleBarAnimation = false;
    navDestinationPattern->MountTitleBar(hostNode, needRunTitleBarAnimation);
}

/**
 * @tc.name: MountTitleBar002
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts return true and Expansive return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, MountTitleBar002, TestSize.Level1)
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
    // There is a second branch in MountTitleBar
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBar().value_or(false));
    bool needRunTitleBarAnimation = false;
    navDestinationPattern->MountTitleBar(hostNode, needRunTitleBarAnimation);
}

/**
 * @tc.name: MountTitleBar003
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts and Expansive return true
 *           and navDestinationContentNode return false.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, MountTitleBar003, TestSize.Level1)
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
    // There is a second branch in MountTitleBar
    EXPECT_FALSE(navDestinationLayoutProperty->GetHideTitleBar().value_or(false));
    bool needRunTitleBarAnimation = false;
    navDestinationPattern->MountTitleBar(hostNode, needRunTitleBarAnimation);
}

/**
 * @tc.name: MountTitleBar004
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make opts and Expansive return true
 *           and navDestinationContentNode return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, MountTitleBar004, TestSize.Level1)
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
    bool needRunTitleBarAnimation = false;
    navDestinationPattern->MountTitleBar(hostNode, needRunTitleBarAnimation);
}

/**
 * @tc.name: MountTitleBar005
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make GetIndex return 0.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, MountTitleBar005, TestSize.Level1)
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
    bool needRunTitleBarAnimation = false;
    navDestinationPattern->MountTitleBar(hostNode, needRunTitleBarAnimation);
}

/**
 * @tc.name: GetBackButtonState001
 * @tc.desc: Test UpdateBackgroundColorIfNeeded and make GetHideTitleBarValue return true.
 * @tc.type: FUNC
 */
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState001, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState002, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState003, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState004, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState005, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState006, TestSize.Level1)
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
HWTEST_F(NavrouterGroupTestNg, GetBackButtonState007, TestSize.Level1)
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
} // namespace OHOS::Ace::NG