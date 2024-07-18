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
} // namespace OHOS::Ace::NG
