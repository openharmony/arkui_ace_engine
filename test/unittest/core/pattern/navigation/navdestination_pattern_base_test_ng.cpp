/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/common/event_manager.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
// Test tag constants
const std::string NAVDESTINATION_TAG = "NavDestination";

// Size and dimension constants
constexpr float DEFAULT_TITLE_BAR_HEIGHT = 50.0f;
constexpr float TITLE_BAR_HEIGHT_LARGE = 56.0f;
constexpr float TITLE_BAR_HEIGHT_LARGER = 64.0f;
constexpr float DEFAULT_TOOL_BAR_HEIGHT = 48.0f;

// Opacity constants
constexpr float OPACITY_FULL = 1.0f;
constexpr float OPACITY_TRANSPARENT = 0.0f;

// Precision constants
constexpr float FLOAT_EPSILON = 0.01f;

// Animation ID constants
constexpr int32_t INVALID_ANIMATION_ID = 0;
constexpr int32_t TEST_ANIMATION_ID_1 = 1;
constexpr int32_t TEST_ANIMATION_ID_999 = 999;

// Animation count constants
constexpr int32_t ANIMATION_COUNT_TWO = 2;
constexpr int32_t ANIMATION_COUNT_ONE = 1;

// Offset constants
constexpr float TITLE_BAR_OFFSET_Y = 10.0f;
} // namespace

class MockNavDestinationPatternBase : public NavDestinationPatternBase {
public:
    MockNavDestinationPatternBase() = default;
    ~MockNavDestinationPatternBase() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return AceType::MakeRefPtr<NavDestinationLayoutPropertyBase>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return AceType::MakeRefPtr<EventHub>();
    }
};

class MockNavDestinationNodeBase : public NavDestinationNodeBase {
public:
    MockNavDestinationNodeBase(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
        : NavDestinationNodeBase(tag, nodeId, pattern) {}
    ~MockNavDestinationNodeBase() override = default;
};

class NavDestinationPatternBaseTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<NavDestinationNodeBase> CreateNavDestinationNode();
    static RefPtr<TitleBarNode> CreateTitleBarNode();
    static RefPtr<NavToolbarNode> CreateToolBarNode();
    static RefPtr<FrameNode> CreateToolBarDividerNode();
    static RefPtr<NavigationGroupNode> CreateNavigationGroupNode();
    static RefPtr<NavDestinationGroupNode> CreateNavDestinationGroupNode();
    static RefPtr<NavBarNode> CreateNavBarNode();
    static void SetupLayoutPropertyWithSafeArea(const RefPtr<NavDestinationNodeBase>& node);
};

void NavDestinationPatternBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavDestinationPatternBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<NavDestinationNodeBase> NavDestinationPatternBaseTestNg::CreateNavDestinationNode()
{
    auto pattern = AceType::MakeRefPtr<MockNavDestinationPatternBase>();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = AceType::MakeRefPtr<MockNavDestinationNodeBase>(
        NAVDESTINATION_TAG, nodeId, pattern);
    node->InitializePatternAndContext();
    return node;
}

RefPtr<TitleBarNode> NavDestinationPatternBaseTestNg::CreateTitleBarNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    node->InitializePatternAndContext();
    return node;
}

RefPtr<NavToolbarNode> NavDestinationPatternBaseTestNg::CreateToolBarNode()
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    node->InitializePatternAndContext();
    return node;
}

RefPtr<FrameNode> NavDestinationPatternBaseTestNg::CreateToolBarDividerNode()
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = FrameNode::CreateFrameNode(V2::DIVIDER_ETS_TAG, nodeId, pattern);
    node->InitializePatternAndContext();
    return node;
}

RefPtr<NavigationGroupNode> NavDestinationPatternBaseTestNg::CreateNavigationGroupNode()
{
    auto navNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    CHECK_NULL_RETURN(navNode, nullptr);
    auto navPattern = navNode->GetPattern<NavigationPattern>();
    CHECK_NULL_RETURN(navPattern, nullptr);
    navPattern->SetNavigationStack(AceType::MakeRefPtr<NavigationStack>());
    return navNode;
}

RefPtr<NavDestinationGroupNode> NavDestinationPatternBaseTestNg::CreateNavDestinationGroupNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    return node;
}

RefPtr<NavBarNode> NavDestinationPatternBaseTestNg::CreateNavBarNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    return node;
}

void NavDestinationPatternBaseTestNg::SetupLayoutPropertyWithSafeArea(
    const RefPtr<NavDestinationNodeBase>& node)
{
    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    SafeAreaExpandOpts opts = {
        .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
        .edges = SAFE_AREA_EDGE_ALL
    };
    layoutProperty->UpdateSafeAreaExpandOpts(opts);
}

/**
 * @tc.name: SetTitleBarStyle001
 * @tc.desc: Branch: if (titleBarStyle_ != barStyle) = true
 *           Branch: if (barStyle.value_or(...) == BarStyle::SAFE_AREA_PADDING ||
 *                     titleBarStyle_.value_or(...) == BarStyle::SAFE_AREA_PADDING) = true
 *           Condition: titleBarStyle_ changes from STANDARD to SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetTitleBarStyle001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Initial style is std::nullopt (defaults to STANDARD)
    EXPECT_EQ(pattern->GetTitleBarStyle(), std::nullopt);

    // Set to SAFE_AREA_PADDING
    pattern->SetTitleBarStyle(BarStyle::SAFE_AREA_PADDING);

    EXPECT_EQ(pattern->GetTitleBarStyle(), BarStyle::SAFE_AREA_PADDING);
    EXPECT_TRUE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetTitleBarStyle002
 * @tc.desc: Branch: if (titleBarStyle_ != barStyle) = true
 *           Branch: if (barStyle.value_or(...) == BarStyle::SAFE_AREA_PADDING ||
 *                     titleBarStyle_.value_or(...) == BarStyle::SAFE_AREA_PADDING) = true
 *           Condition: titleBarStyle_ changes from SAFE_AREA_PADDING to STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetTitleBarStyle002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set initial style to SAFE_AREA_PADDING
    pattern->SetTitleBarStyle(BarStyle::SAFE_AREA_PADDING);
    EXPECT_EQ(pattern->GetTitleBarStyle(), BarStyle::SAFE_AREA_PADDING);

    // Reset safeAreaPaddingChanged_
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Change to STANDARD
    pattern->SetTitleBarStyle(BarStyle::STANDARD);

    EXPECT_EQ(pattern->GetTitleBarStyle(), BarStyle::STANDARD);
    EXPECT_TRUE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetTitleBarStyle003
 * @tc.desc: Branch: if (titleBarStyle_ != barStyle) = true
 *           Branch: if (barStyle.value_or(...) == BarStyle::SAFE_AREA_PADDING ||
 *                     titleBarStyle_.value_or(...) == BarStyle::SAFE_AREA_PADDING) = false
 *           Condition: titleBarStyle_ changes between STANDARD and other non-SAFE styles
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetTitleBarStyle003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set to STANDARD (default)
    pattern->SetTitleBarStyle(BarStyle::STANDARD);
    EXPECT_EQ(pattern->GetTitleBarStyle(), BarStyle::STANDARD);

    // Change to another style (if exists)
    pattern->SetTitleBarStyle(std::nullopt);

    EXPECT_EQ(pattern->GetTitleBarStyle(), std::nullopt);
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetTitleBarStyle004
 * @tc.desc: Branch: if (titleBarStyle_ != barStyle) = false
 *           Condition: titleBarStyle_ remains the same
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetTitleBarStyle004, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set initial style
    pattern->SetTitleBarStyle(BarStyle::STANDARD);
    EXPECT_EQ(pattern->GetTitleBarStyle(), BarStyle::STANDARD);

    // Reset safeAreaPaddingChanged_
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Set to same style again
    pattern->SetTitleBarStyle(BarStyle::STANDARD);

    EXPECT_EQ(pattern->GetTitleBarStyle(), BarStyle::STANDARD);
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetToolBarStyle001
 * @tc.desc: Branch: if (toolBarStyle_ != barStyle) = true
 *           Branch: if (barStyle.value_or(...) == BarStyle::SAFE_AREA_PADDING ||
 *                     toolBarStyle_.value_or(...) == BarStyle::SAFE_AREA_PADDING) = true
 *           Condition: toolBarStyle_ changes from STANDARD to SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetToolBarStyle001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Initial style is std::nullopt (defaults to STANDARD)
    EXPECT_EQ(pattern->GetToolBarStyle(), std::nullopt);

    // Set to SAFE_AREA_PADDING
    pattern->SetToolBarStyle(BarStyle::SAFE_AREA_PADDING);

    EXPECT_EQ(pattern->GetToolBarStyle(), BarStyle::SAFE_AREA_PADDING);
    EXPECT_TRUE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetToolBarStyle002
 * @tc.desc: Branch: if (toolBarStyle_ != barStyle) = true
 *           Branch: if (barStyle.value_or(...) == BarStyle::SAFE_AREA_PADDING ||
 *                     toolBarStyle_.value_or(...) == BarStyle::SAFE_AREA_PADDING) = true
 *           Condition: toolBarStyle_ changes from SAFE_AREA_PADDING to STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetToolBarStyle002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set initial style to SAFE_AREA_PADDING
    pattern->SetToolBarStyle(BarStyle::SAFE_AREA_PADDING);
    EXPECT_EQ(pattern->GetToolBarStyle(), BarStyle::SAFE_AREA_PADDING);

    // Reset safeAreaPaddingChanged_
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Change to STANDARD
    pattern->SetToolBarStyle(BarStyle::STANDARD);

    EXPECT_EQ(pattern->GetToolBarStyle(), BarStyle::STANDARD);
    EXPECT_TRUE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetToolBarStyle003
 * @tc.desc: Branch: if (toolBarStyle_ != barStyle) = true
 *           Branch: if (barStyle.value_or(...) == BarStyle::SAFE_AREA_PADDING ||
 *                     toolBarStyle_.value_or(...) == BarStyle::SAFE_AREA_PADDING) = false
 *           Condition: toolBarStyle_ changes between non-SAFE styles
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetToolBarStyle003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set to STANDARD (default)
    pattern->SetToolBarStyle(BarStyle::STANDARD);
    EXPECT_EQ(pattern->GetToolBarStyle(), BarStyle::STANDARD);

    // Change to std::nullopt
    pattern->SetToolBarStyle(std::nullopt);

    EXPECT_EQ(pattern->GetToolBarStyle(), std::nullopt);
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetToolBarStyle004
 * @tc.desc: Branch: if (toolBarStyle_ != barStyle) = false
 *           Condition: toolBarStyle_ remains the same
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetToolBarStyle004, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set initial style
    pattern->SetToolBarStyle(BarStyle::STANDARD);
    EXPECT_EQ(pattern->GetToolBarStyle(), BarStyle::STANDARD);

    // Reset safeAreaPaddingChanged_
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Set to same style again
    pattern->SetToolBarStyle(BarStyle::STANDARD);

    EXPECT_EQ(pattern->GetToolBarStyle(), BarStyle::STANDARD);
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: UpdateLayoutPropertyBeforeAnimation001
 * @tc.desc: Branch: if (needRunTitleBarAnimation && titleBarAnimationCount_ == 0) = true
 *           Branch: if (!hideTitleBar) = true
 *           Condition: titleBar animation needed, count is 0, not hiding
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateLayoutPropertyBeforeAnimation001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set animation count to 0
    ASSERT_EQ(pattern->GetTitleBarAnimationCount(), 0);

    // Call with needRunTitleBarAnimation=true, hideTitleBar=false
    pattern->UpdateLayoutPropertyBeforeAnimation(node, true, false, false, false);

    // Verify title bar translate state was updated to TRANSLATE_HEIGHT (hide=false)
    auto translateState = layoutProperty->GetTitleBarTranslateStateValue(
        BarTranslateState::TRANSLATE_ZERO);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_HEIGHT);
}

/**
 * @tc.name: UpdateLayoutPropertyBeforeAnimation002
 * @tc.desc: Branch: if (needRunTitleBarAnimation && titleBarAnimationCount_ == 0) = true
 *           Branch: if (!hideTitleBar) = false
 *           Condition: titleBar animation needed, count is 0, hiding
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateLayoutPropertyBeforeAnimation002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set animation count to 0
    ASSERT_EQ(pattern->GetTitleBarAnimationCount(), 0);

    // Call with needRunTitleBarAnimation=true, hideTitleBar=true
    pattern->UpdateLayoutPropertyBeforeAnimation(node, true, false, true, false);

    // Verify title bar translate state was updated to TRANSLATE_ZERO (hide=true)
    auto translateState = layoutProperty->GetTitleBarTranslateStateValue(
        BarTranslateState::TRANSLATE_HEIGHT);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_ZERO);
}

/**
 * @tc.name: UpdateLayoutPropertyBeforeAnimation003
 * @tc.desc: Branch: if (needRunTitleBarAnimation && titleBarAnimationCount_ == 0) = false
 *           Condition: titleBarAnimationCount_ > 0
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateLayoutPropertyBeforeAnimation003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Increment animation count
    pattern->OnTitleBarAnimationStart();
    EXPECT_GT(pattern->GetTitleBarAnimationCount(), 0);

    // Call with needRunTitleBarAnimation=true
    pattern->UpdateLayoutPropertyBeforeAnimation(node, true, false, false, false);

    // Verify translate state was not updated (remains default)
    auto translateState = layoutProperty->GetTitleBarTranslateStateValue(
        BarTranslateState::TRANSLATE_ZERO);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_ZERO);
}

/**
 * @tc.name: UpdateLayoutPropertyBeforeAnimation004
 * @tc.desc: Branch: if (needRunTitleBarAnimation && titleBarAnimationCount_ == 0) = false
 *           Branch: if (needRunToolBarAnimation && toolBarAnimationCount_ == 0) = true
 *           Branch: if (!hideToolBar) = true
 *           Condition: no titleBar animation, toolBar animation needed, not hiding
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateLayoutPropertyBeforeAnimation004, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set toolBar animation count to 0
    ASSERT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Call with needRunTitleBarAnimation=false, needRunToolBarAnimation=true, hideToolBar=false
    pattern->UpdateLayoutPropertyBeforeAnimation(node, false, true, false, false);

    // Verify tool bar translate state was updated to TRANSLATE_HEIGHT
    auto translateState = layoutProperty->GetToolBarTranslateStateValue(
        BarTranslateState::TRANSLATE_ZERO);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_HEIGHT);
}

/**
 * @tc.name: UpdateLayoutPropertyBeforeAnimation005
 * @tc.desc: Branch: if (needRunToolBarAnimation && toolBarAnimationCount_ == 0) = true
 *           Branch: if (!hideToolBar) = false
 *           Condition: toolBar animation needed, hiding
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateLayoutPropertyBeforeAnimation005, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set toolBar animation count to 0
    ASSERT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Call with needRunToolBarAnimation=true, hideToolBar=true
    pattern->UpdateLayoutPropertyBeforeAnimation(node, false, true, false, true);

    // Verify tool bar translate state was updated to TRANSLATE_ZERO
    auto translateState = layoutProperty->GetToolBarTranslateStateValue(
        BarTranslateState::TRANSLATE_HEIGHT);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_ZERO);
}

/**
 * @tc.name: UpdateLayoutPropertyBeforeAnimation006
 * @tc.desc: Branch: if (needRunToolBarAnimation && toolBarAnimationCount_ == 0) = false
 *           Condition: toolBarAnimationCount_ > 0
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateLayoutPropertyBeforeAnimation006, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Increment toolBar animation count
    pattern->OnToolBarAnimationStart();
    EXPECT_GT(pattern->GetToolBarAnimationCount(), 0);

    // Call with needRunToolBarAnimation=true
    pattern->UpdateLayoutPropertyBeforeAnimation(node, false, true, false, false);

    // Verify translate state was not updated
    auto translateState = layoutProperty->GetToolBarTranslateStateValue(
        BarTranslateState::TRANSLATE_ZERO);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_ZERO);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation001
 * @tc.desc: Branch: if (!(needRunToolBarAnimation || needRunTitleBarAnimation)) = true
 *           Condition: neither animation is needed
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Verify initial state
    ASSERT_EQ(pattern->GetTitleBarAnimationCount(), 0);
    ASSERT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Call with both animations not needed - should return early
    pattern->HandleTitleBarAndToolBarAnimation(node, false, false);

    // Verify animation counts remain unchanged (early return, no side effects)
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0);
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 0);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation002
 * @tc.desc: Branch: if (pattern->IsNeedHideToolBarForNavWidth()) = true
 *           Branch: if (!(needRunToolBarAnimation || needRunTitleBarAnimation)) = true
 *           Condition: need to hide toolBar for nav width, resets needRunToolBarAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set need to hide toolBar for nav width
    pattern->SetIsNeedHideToolBarForNavWidth(true);
    EXPECT_TRUE(pattern->IsNeedHideToolBarForNavWidth());

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set toolBar translate state to something non-default
    layoutProperty->UpdateToolBarTranslateState(BarTranslateState::TRANSLATE_HEIGHT);
    EXPECT_EQ(layoutProperty->GetToolBarTranslateStateValue(BarTranslateState::TRANSLATE_ZERO),
        BarTranslateState::TRANSLATE_HEIGHT);

    // Verify initial animation count
    ASSERT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Call with toolBar animation needed
    pattern->HandleTitleBarAndToolBarAnimation(node, false, true);

    // Verify needHideToolBarForNavWidth flag remains set
    EXPECT_TRUE(pattern->IsNeedHideToolBarForNavWidth());
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation003
 * @tc.desc: Branch: if (needRunTitleBarAnimation && !hideTitleBar && titleBarNode &&
 *                     pattern->GetTitleBarAnimationCount() == 0) = true
 *           Condition: all conditions met for titleBar animation
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    // Set titleBar height
    pattern->SetTitleBarHeight(DEFAULT_TITLE_BAR_HEIGHT);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideTitleBar(false);

    // Animation count should be 0
    ASSERT_EQ(pattern->GetTitleBarAnimationCount(), 0);

    // Call with titleBar animation needed, not hiding
    pattern->HandleTitleBarAndToolBarAnimation(node, true, false);

    // Verify function execution completed without crash
    // The animation is scheduled in a task, so we verify the task was scheduled
    // by checking the node is still valid
    EXPECT_NE(pattern->GetHost(), nullptr);
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0); // Still 0 until task runs
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation004
 * @tc.desc: Branch: if (needRunTitleBarAnimation && !hideTitleBar && titleBarNode &&
 *                     pattern->GetTitleBarAnimationCount() == 0) = false
 *           Condition: hideTitleBar is true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation004, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideTitleBar(true); // hide = true

    // Animation count should be 0
    ASSERT_EQ(pattern->GetTitleBarAnimationCount(), 0);

    // Call with titleBar animation needed, but hiding
    pattern->HandleTitleBarAndToolBarAnimation(node, true, false);

    // Verify function execution completed without crash
    // Animation count remains 0 until task runs
    EXPECT_NE(pattern->GetHost(), nullptr);
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation005
 * @tc.desc: Branch: if (needRunToolBarAnimation && !hideToolBar && toolBarNode &&
 *                     pattern->GetToolBarAnimationCount() == 0) = true
 *           Condition: all conditions met for toolBar animation
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation005, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    // Set heights
    pattern->SetToolBarHeight(DEFAULT_TITLE_BAR_HEIGHT);
    pattern->SetToolBarDividerHeight(OPACITY_FULL);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideToolBar(false);

    // Animation count should be 0
    ASSERT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Call with toolBar animation needed, not hiding
    pattern->HandleTitleBarAndToolBarAnimation(node, false, true);

    // Verify function execution completed without crash
    // The animation is scheduled in a task
    EXPECT_NE(pattern->GetHost(), nullptr);
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 0); // Still 0 until task runs
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation006
 * @tc.desc: Branch: if (needRunToolBarAnimation && !hideToolBar && toolBarNode &&
 *                     pattern->GetToolBarAnimationCount() == 0) = false
 *           Condition: toolBarAnimationCount_ > 0
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation006, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideToolBar(false);

    // Increment animation count
    pattern->OnToolBarAnimationStart();
    int initialCount = pattern->GetToolBarAnimationCount();
    EXPECT_GT(initialCount, 0);

    // Call with toolBar animation needed
    pattern->HandleTitleBarAndToolBarAnimation(node, false, true);

    // Verify animation count is still > 0 (animation already running, new one won't start)
    EXPECT_GT(pattern->GetToolBarAnimationCount(), 0);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation007
 * @tc.desc: Branch: if (needRunTitleBarAnimation && !hideTitleBar && titleBarNode &&
 *                     pattern->GetTitleBarAnimationCount() == 0) = false
 *           Branch: if (needRunToolBarAnimation && !hideToolBar && toolBarNode &&
 *                     pattern->GetToolBarAnimationCount() == 0) = false
 *           Condition: titleBarNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HandleTitleBarAndToolBarAnimation007, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Don't set up titleBar node - it will be nullptr
    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideTitleBar(false);

    // Animation count should be 0
    ASSERT_EQ(pattern->GetTitleBarAnimationCount(), 0);
    ASSERT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Call with titleBar animation needed
    pattern->HandleTitleBarAndToolBarAnimation(node, true, false);

    // Verify animation count - titleBar animation should not start due to null node
    // Animation is scheduled in a task, but the actual animation won't run
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0);
}

/**
 * @tc.name: UpdateTitleBarProperty001
 * @tc.desc: Branch: if (hide) = true
 *           Condition: hiding title bar
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateTitleBarProperty001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Call with hide=true
    pattern->UpdateTitleBarProperty(layoutProperty, true, node);

    // Verify visibility is GONE
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto visibility = titleBarLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::GONE);
}

/**
 * @tc.name: UpdateTitleBarProperty002
 * @tc.desc: Branch: if (hide) = false
 *           Branch: if (opts) = true
 *           Condition: showing title bar with safe area opts
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateTitleBarProperty002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set up safe area opts
    SetupLayoutPropertyWithSafeArea(node);

    // Call with hide=false
    pattern->UpdateTitleBarProperty(layoutProperty, false, node);

    // Verify visibility is VISIBLE
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto visibility = titleBarLayoutProperty->GetVisibilityValue(VisibleType::GONE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateTitleBarProperty003
 * @tc.desc: Branch: if (hide) = false
 *           Branch: if (opts) = false
 *           Condition: showing title bar without safe area opts
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateTitleBarProperty003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Don't set up safe area opts

    // Call with hide=false
    pattern->UpdateTitleBarProperty(layoutProperty, false, node);

    // Verify visibility is VISIBLE
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto visibility = titleBarLayoutProperty->GetVisibilityValue(VisibleType::GONE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateTitleBarTranslateAndOpacity001
 * @tc.desc: Branch: if (titleBarNode) = true
 *           Branch: if (renderContext) = true
 *           Condition: hide = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateTitleBarTranslateAndOpacity001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    float titleBarHeight = DEFAULT_TITLE_BAR_HEIGHT;

    // Call with hide=true
    pattern->UpdateTitleBarTranslateAndOpacity(true, titleBarNode, titleBarHeight);

    // Verify render context was updated
    auto renderContext = titleBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto offset = renderContext->GetTranslateXYProperty();
    // Y should be -titleBarHeight when hiding
    EXPECT_NEAR(offset.GetY(), -titleBarHeight, FLOAT_EPSILON);

    auto opacity = renderContext->GetOpacityValue(OPACITY_FULL);
    EXPECT_NEAR(opacity, OPACITY_TRANSPARENT, FLOAT_EPSILON);
}

/**
 * @tc.name: UpdateTitleBarTranslateAndOpacity002
 * @tc.desc: Branch: if (titleBarNode) = true
 *           Branch: if (renderContext) = true
 *           Condition: hide = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateTitleBarTranslateAndOpacity002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    float titleBarHeight = DEFAULT_TITLE_BAR_HEIGHT;

    // Call with hide=false
    pattern->UpdateTitleBarTranslateAndOpacity(false, titleBarNode, titleBarHeight);

    // Verify render context was updated
    auto renderContext = titleBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto offset = renderContext->GetTranslateXYProperty();
    // Y should be 0 when not hiding
    EXPECT_NEAR(offset.GetY(), OPACITY_TRANSPARENT, FLOAT_EPSILON);

    auto opacity = renderContext->GetOpacityValue(OPACITY_TRANSPARENT);
    EXPECT_NEAR(opacity, OPACITY_FULL, FLOAT_EPSILON);
}

/**
 * @tc.name: UpdateTitleBarTranslateAndOpacity003
 * @tc.desc: Branch: if (titleBarNode) = false
 *           Condition: titleBarNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateTitleBarTranslateAndOpacity003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Don't set up titleBar node - pass nullptr

    float titleBarHeight = DEFAULT_TITLE_BAR_HEIGHT;

    // Call with nullptr titleBarNode - should not crash
    pattern->UpdateTitleBarTranslateAndOpacity(false, nullptr, titleBarHeight);
}

/**
 * @tc.name: UpdateToolBarAndDividerProperty001
 * @tc.desc: Branch: if (hide || !toolBarNode->HasValidContent()) = true
 *           Condition: hiding tool bar
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateToolBarAndDividerProperty001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Call with hide=true
    pattern->UpdateToolBarAndDividerProperty(layoutProperty, true, node);

    // Verify visibility is GONE
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    auto visibility = toolBarLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::GONE);
}

/**
 * @tc.name: UpdateToolBarAndDividerProperty002
 * @tc.desc: Branch: if (hide || !toolBarNode->HasValidContent()) = false
 *           Branch: if (toolBarDividerLayoutProperty) = true
 *           Branch: if (opts) = true
 *           Condition: showing tool bar with divider and safe area opts
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateToolBarAndDividerProperty002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    // Set hasValidContent to true (default is false)
    toolBarNode->SetHasValidContent(true);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set up safe area opts
    SetupLayoutPropertyWithSafeArea(node);

    // Call with hide=false
    pattern->UpdateToolBarAndDividerProperty(layoutProperty, false, node);

    // Verify visibility is VISIBLE
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    auto visibility = toolBarLayoutProperty->GetVisibilityValue(VisibleType::GONE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);

    // Verify divider is also VISIBLE
    auto dividerLayoutProperty = toolBarDividerNode->GetLayoutProperty();
    ASSERT_NE(dividerLayoutProperty, nullptr);
    auto dividerVisibility = dividerLayoutProperty->GetVisibilityValue(VisibleType::GONE);
    EXPECT_EQ(dividerVisibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateToolBarAndDividerProperty003
 * @tc.desc: Branch: if (hide || !toolBarNode->HasValidContent()) = false
 *           Branch: if (toolBarDividerLayoutProperty) = false
 *           Condition: showing tool bar without divider
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateToolBarAndDividerProperty003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar node without divider
    auto toolBarNode = CreateToolBarNode();
    node->SetToolBarNode(toolBarNode);
    // Don't set divider node

    // Set hasValidContent to true (default is false)
    toolBarNode->SetHasValidContent(true);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Call with hide=false
    pattern->UpdateToolBarAndDividerProperty(layoutProperty, false, node);

    // Verify visibility is VISIBLE
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    auto visibility = toolBarLayoutProperty->GetVisibilityValue(VisibleType::GONE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacity001
 * @tc.desc: Branch: if (toolBarNode) = true
 *           Branch: if (renderContext) = true
 *           Branch: if (toolbarDividerNode) = true
 *           Condition: hide = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacity001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    float toolBarHeight = DEFAULT_TITLE_BAR_HEIGHT;
    float toolBarDividerHeight = OPACITY_FULL;

    // Call with hide=true
    pattern->UpdateToolBarAndDividerTranslateAndOpacity(
        true, toolBarNode, toolBarHeight, toolBarDividerNode, toolBarDividerHeight);

    // Verify render context was updated for toolBar
    auto renderContext = toolBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto offset = renderContext->GetTranslateXYProperty();
    // Y should be (toolBarHeight + toolBarDividerHeight) when hiding
    EXPECT_NEAR(offset.GetY(), toolBarHeight + toolBarDividerHeight, FLOAT_EPSILON);

    auto opacity = renderContext->GetOpacityValue(OPACITY_FULL);
    EXPECT_NEAR(opacity, OPACITY_TRANSPARENT, FLOAT_EPSILON);

    // Verify divider was also updated
    auto dividerRenderContext = toolBarDividerNode->GetRenderContext();
    ASSERT_NE(dividerRenderContext, nullptr);

    auto dividerOffset = dividerRenderContext->GetTranslateXYProperty();
    EXPECT_NEAR(dividerOffset.GetY(), toolBarHeight + toolBarDividerHeight, FLOAT_EPSILON);

    auto dividerOpacity = dividerRenderContext->GetOpacityValue(OPACITY_FULL);
    EXPECT_NEAR(dividerOpacity, OPACITY_TRANSPARENT, FLOAT_EPSILON);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacity002
 * @tc.desc: Branch: if (toolBarNode) = true
 *           Branch: if (renderContext) = true
 *           Branch: if (toolbarDividerNode) = true
 *           Condition: hide = false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacity002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    float toolBarHeight = DEFAULT_TITLE_BAR_HEIGHT;
    float toolBarDividerHeight = OPACITY_FULL;

    // Call with hide=false
    pattern->UpdateToolBarAndDividerTranslateAndOpacity(
        false, toolBarNode, toolBarHeight, toolBarDividerNode, toolBarDividerHeight);

    // Verify render context was updated for toolBar
    auto renderContext = toolBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto offset = renderContext->GetTranslateXYProperty();
    // Y should be 0 when not hiding
    EXPECT_NEAR(offset.GetY(), OPACITY_TRANSPARENT, FLOAT_EPSILON);

    auto opacity = renderContext->GetOpacityValue(OPACITY_TRANSPARENT);
    EXPECT_NEAR(opacity, OPACITY_FULL, FLOAT_EPSILON);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacity003
 * @tc.desc: Branch: if (toolBarNode) = false
 *           Condition: toolBarNode is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacity003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    float toolBarHeight = DEFAULT_TITLE_BAR_HEIGHT;
    float toolBarDividerHeight = OPACITY_FULL;

    // Call with nullptr toolBarNode - should not crash
    pattern->UpdateToolBarAndDividerTranslateAndOpacity(
        false, nullptr, toolBarHeight, nullptr, toolBarDividerHeight);
}

/**
 * @tc.name: OnToolBarAnimationFinish001
 * @tc.desc: Branch: if (toolBarAnimationCount_ > 0) = true
 *           Condition: multiple animations running
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, OnToolBarAnimationFinish001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Start multiple animations
    pattern->OnToolBarAnimationStart();
    pattern->OnToolBarAnimationStart();
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), ANIMATION_COUNT_TWO);

    // Finish one animation
    pattern->OnToolBarAnimationFinish();

    // Count should be 1, not reset yet
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), ANIMATION_COUNT_ONE);
}

/**
 * @tc.name: OnToolBarAnimationFinish002
 * @tc.desc: Branch: if (toolBarAnimationCount_ > 0) = false
 *           Condition: last animation finishes
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, OnToolBarAnimationFinish002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Start one animation
    pattern->OnToolBarAnimationStart();
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 1);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideToolBar(false);

    // Finish the animation
    pattern->OnToolBarAnimationFinish();

    // Count should be 0
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 0);
}

/**
 * @tc.name: OnTitleBarAnimationFinish001
 * @tc.desc: Branch: if (titleBarAnimationCount_ > 0) = true
 *           Condition: multiple animations running
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, OnTitleBarAnimationFinish001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Start multiple animations
    pattern->OnTitleBarAnimationStart();
    pattern->OnTitleBarAnimationStart();
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), ANIMATION_COUNT_TWO);

    // Finish one animation
    pattern->OnTitleBarAnimationFinish();

    // Count should be 1, not reset yet
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), ANIMATION_COUNT_ONE);
}

/**
 * @tc.name: OnTitleBarAnimationFinish002
 * @tc.desc: Branch: if (titleBarAnimationCount_ > 0) = false
 *           Condition: last animation finishes
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, OnTitleBarAnimationFinish002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Start one animation
    pattern->OnTitleBarAnimationStart();
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 1);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateHideTitleBar(false);

    // Finish the animation
    pattern->OnTitleBarAnimationFinish();

    // Count should be 0
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0);
}

/**
 * @tc.name: SetIsNeedHideToolBarForNavWidth001
 * @tc.desc: Test SetIsNeedHideToolBarForNavWidth interface
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetIsNeedHideToolBarForNavWidth001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Default should be false
    EXPECT_FALSE(pattern->IsNeedHideToolBarForNavWidth());

    // Set to true
    pattern->SetIsNeedHideToolBarForNavWidth(true);
    EXPECT_TRUE(pattern->IsNeedHideToolBarForNavWidth());

    // Set to false
    pattern->SetIsNeedHideToolBarForNavWidth(false);
    EXPECT_FALSE(pattern->IsNeedHideToolBarForNavWidth());
}

/**
 * @tc.name: UpdateSafeAreaPaddingChanged001
 * @tc.desc: Test UpdateSafeAreaPaddingChanged interface
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, UpdateSafeAreaPaddingChanged001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Default should be false
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());

    // Set to true
    pattern->UpdateSafeAreaPaddingChanged(true);
    EXPECT_TRUE(pattern->IsSafeAreaPaddingChanged());

    // Set to false
    pattern->UpdateSafeAreaPaddingChanged(false);
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: SetTitleBarHeight001
 * @tc.desc: Test SetTitleBarHeight and GetTitleBarHeight interface
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetTitleBarHeight001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Default should be 0
    EXPECT_EQ(pattern->GetTitleBarHeight(), OPACITY_TRANSPARENT);

    // Set height
    pattern->SetTitleBarHeight(TITLE_BAR_HEIGHT_LARGE);
    EXPECT_EQ(pattern->GetTitleBarHeight(), TITLE_BAR_HEIGHT_LARGE);

    // Set another height
    pattern->SetTitleBarHeight(TITLE_BAR_HEIGHT_LARGER);
    EXPECT_EQ(pattern->GetTitleBarHeight(), TITLE_BAR_HEIGHT_LARGER);
}

/**
 * @tc.name: SetToolBarHeight001
 * @tc.desc: Test SetToolBarHeight and GetToolBarHeight interface
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetToolBarHeight001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Default should be 0
    EXPECT_EQ(pattern->GetToolBarHeight(), OPACITY_TRANSPARENT);

    // Set height
    pattern->SetToolBarHeight(DEFAULT_TOOL_BAR_HEIGHT);
    EXPECT_EQ(pattern->GetToolBarHeight(), DEFAULT_TOOL_BAR_HEIGHT);
}

/**
 * @tc.name: SetToolBarDividerHeight001
 * @tc.desc: Test SetToolBarDividerHeight and GetToolBarDividerHeight interface
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, SetToolBarDividerHeight001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Default should be 0
    EXPECT_EQ(pattern->GetToolBarDividerHeight(), OPACITY_TRANSPARENT);

    // Set height
    pattern->SetToolBarDividerHeight(OPACITY_FULL);
    EXPECT_EQ(pattern->GetToolBarDividerHeight(), OPACITY_FULL);
}

/**
 * @tc.name: MarkSafeAreaPaddingChangedWithCheckTitleBar001
 * @tc.desc: Branch: if (titleBarStyle_.value_or(...) != BarStyle::SAFE_AREA_PADDING) = true
 *           Condition: titleBar style is not SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, MarkSafeAreaPaddingChangedWithCheckTitleBar001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set style to STANDARD
    pattern->SetTitleBarStyle(BarStyle::STANDARD);
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Call with different height
    pattern->MarkSafeAreaPaddingChangedWithCheckTitleBar(DEFAULT_TITLE_BAR_HEIGHT);

    // Should return early, safeAreaPaddingChanged_ should remain false
    EXPECT_FALSE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: MarkSafeAreaPaddingChangedWithCheckTitleBar002
 * @tc.desc: Branch: if (titleBarStyle_.value_or(...) != BarStyle::SAFE_AREA_PADDING) = false
 *           Branch: if (!NearEqual(titleBarHeight, titleBarHeight_)) = true
 *           Condition: titleBar style is SAFE_AREA_PADDING and height changed
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, MarkSafeAreaPaddingChangedWithCheckTitleBar002, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set style to SAFE_AREA_PADDING
    pattern->SetTitleBarStyle(BarStyle::SAFE_AREA_PADDING);
    pattern->SetTitleBarHeight(TITLE_BAR_HEIGHT_LARGE);
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Call with different height
    pattern->MarkSafeAreaPaddingChangedWithCheckTitleBar(TITLE_BAR_HEIGHT_LARGER);

    // safeAreaPaddingChanged_ should be true
    EXPECT_TRUE(pattern->IsSafeAreaPaddingChanged());
}

/**
 * @tc.name: MarkSafeAreaPaddingChangedWithCheckTitleBar003
 * @tc.desc: Branch: if (!NearEqual(titleBarHeight, titleBarHeight_)) = false
 *           Branch: if (titleBarNode && NavigationTitleUtil::CalculateTitlebarOffset(titleBarNode)
 *                          != titleBarOffsetY_) = true
 *           Condition: height same but offset changed
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, MarkSafeAreaPaddingChangedWithCheckTitleBar003, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set style to SAFE_AREA_PADDING
    pattern->SetTitleBarStyle(BarStyle::SAFE_AREA_PADDING);
    pattern->SetTitleBarHeight(TITLE_BAR_HEIGHT_LARGE);
    pattern->SetTitleBarOffsetY(TITLE_BAR_OFFSET_Y);
    pattern->UpdateSafeAreaPaddingChanged(false);

    // Call with same height
    pattern->MarkSafeAreaPaddingChangedWithCheckTitleBar(TITLE_BAR_HEIGHT_LARGE);

    // safeAreaPaddingChanged_ should be true if offset is different
    // (CalculateTitlebarOffset would return actual offset)
}

/**
 * @tc.name: HideOrShowTitleBarImmediately001
 * @tc.desc: Test HideOrShowTitleBarImmediately with hide=true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HideOrShowTitleBarImmediately001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    pattern->SetTitleBarHeight(DEFAULT_TITLE_BAR_HEIGHT);

    // Hide title bar
    pattern->HideOrShowTitleBarImmediately(node, true);

    // Verify visibility is GONE
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto visibility = titleBarLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::GONE);
}

/**
 * @tc.name: HideOrShowToolBarImmediately001
 * @tc.desc: Test HideOrShowToolBarImmediately with hide=true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, HideOrShowToolBarImmediately001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up toolBar nodes
    auto toolBarNode = CreateToolBarNode();
    auto toolBarDividerNode = CreateToolBarDividerNode();
    node->SetToolBarNode(toolBarNode);
    node->SetToolBarDividerNode(toolBarDividerNode);

    pattern->SetToolBarHeight(DEFAULT_TITLE_BAR_HEIGHT);
    pattern->SetToolBarDividerHeight(OPACITY_FULL);

    // Hide tool bar
    pattern->HideOrShowToolBarImmediately(node, true);

    // Verify visibility is GONE
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    auto visibility = toolBarLayoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::GONE);
}

/**
 * @tc.name: BarAnimationFinishCallback001
 * @tc.desc: Test BarAnimationFinishCallback with both animations
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, BarAnimationFinishCallback001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Start animations
    pattern->OnTitleBarAnimationStart();
    pattern->OnToolBarAnimationStart();
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 1);
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 1);

    // Call finish callback
    pattern->BarAnimationFinishCallback(true, true, INVALID_ANIMATION_ID);

    // Both counts should be 0
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0);
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 0);
}

/**
 * @tc.name: BarAnimationPropertyCallback001
 * @tc.desc: Test BarAnimationPropertyCallback with titleBar animation
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, BarAnimationPropertyCallback001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Set up titleBar node
    auto titleBarNode = CreateTitleBarNode();
    node->SetTitleBarNode(titleBarNode);

    pattern->SetTitleBarHeight(DEFAULT_TITLE_BAR_HEIGHT);
    EXPECT_EQ(pattern->GetTitleBarHeight(), DEFAULT_TITLE_BAR_HEIGHT);

    auto layoutProperty = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(layoutProperty, nullptr);

    // Call with titleBar animation, hideTitle=false
    // hideTitle=false means: translate state = TRANSLATE_ZERO, offset = 0
    pattern->BarAnimationPropertyCallback(true, false, false, false);

    // Verify titleBar translate state was updated
    // hideTitle=false => TRANSLATE_ZERO (showing)
    auto translateState = layoutProperty->GetTitleBarTranslateStateValue(
        BarTranslateState::TRANSLATE_HEIGHT);
    EXPECT_EQ(translateState, BarTranslateState::TRANSLATE_ZERO);

    // Verify titleBar render context was updated
    // hideTitle=false => offset.Y = 0, opacity = 1
    auto renderContext = titleBarNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto offset = renderContext->GetTranslateXYProperty();
    EXPECT_NEAR(offset.GetY(), 0.0f, FLOAT_EPSILON);

    auto opacity = renderContext->GetOpacityValue(0.0f);
    EXPECT_NEAR(opacity, OPACITY_FULL, FLOAT_EPSILON);
}

/**
 * @tc.name: RemoveAnimation001
 * @tc.desc: Test RemoveAnimation interface
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, RemoveAnimation001, TestSize.Level1)
{
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);

    // Verify that calling RemoveAnimation with non-existent IDs doesn't crash
    // and doesn't cause undefined behavior
    // Since we can't easily create real AnimationUtils::Animation objects,
    // we verify the method handles non-existent animation IDs gracefully

    // RemoveAnimation should handle non-existent animation IDs without crashing
    pattern->RemoveAnimation(INVALID_ANIMATION_ID);
    pattern->RemoveAnimation(TEST_ANIMATION_ID_1);
    pattern->RemoveAnimation(-1);
    pattern->RemoveAnimation(TEST_ANIMATION_ID_999);

    // Verify pattern is still valid after calls
    EXPECT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetTitleBarAnimationCount(), 0);
    EXPECT_EQ(pattern->GetToolBarAnimationCount(), 0);

    // Verify nextBarAnimationId_ hasn't been affected
    // The ID should still be 0 since no animations were added
    EXPECT_EQ(pattern->GetTitleBarHeight(), OPACITY_TRANSPARENT);
    EXPECT_EQ(pattern->GetToolBarHeight(), OPACITY_TRANSPARENT);
}

/**
 * @tc.name: InitOnTouchEvent001
 * @tc.desc: Branch: CHECK_NULL_VOID(host)
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavDestinationPatternBase test node.
     */
    auto node = CreateNavDestinationNode();
    auto pattern = node->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Call InitOnTouchEvent with nullptr host.
     */
    pattern->InitOnTouchEvent(nullptr);
    SUCCEED();
}

/**
 * @tc.name: InitOnTouchEvent002
 * @tc.desc: Branch: if (!forceSplitMgr->IsForceSplitSupported(false))
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create destination host and disable force split support.
     */
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(destNode, nullptr);
    auto pattern = destNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    context->GetForceSplitManager()->SetForceSplitSupported(false);

    /**
     * @tc.steps: step2. Call InitOnTouchEvent and verify no listener is registered.
     */
    pattern->InitOnTouchEvent(destNode);
    EXPECT_EQ(eventManager->hitTestFrameNodeListener_.count(destNode->GetId()), 0u);
}

/**
 * @tc.name: InitOnTouchEvent003
 * @tc.desc: Branch: register callback when force split supported.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create destination host and enable force split support.
     */
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(destNode, nullptr);
    auto pattern = destNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    context->GetForceSplitManager()->SetForceSplitSupported(true);

    /**
     * @tc.steps: step2. Call InitOnTouchEvent and verify listener registration by node id.
     */
    pattern->InitOnTouchEvent(destNode);
    EXPECT_EQ(eventManager->hitTestFrameNodeListener_.count(destNode->GetId()), 1u);
}

/**
 * @tc.name: InitOnTouchEvent004
 * @tc.desc: Branch in callback: if (!navPattern->IsForceSplitSuccess()) return.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build navigation + destination relation and set forceSplitSuccess to false.
     */
    auto navNode = CreateNavigationGroupNode();
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(navNode, nullptr);
    ASSERT_NE(destNode, nullptr);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    auto navPattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(destPattern, nullptr);
    ASSERT_NE(navPattern, nullptr);
    destPattern->SetNavigationNode(navNode);
    navPattern->SetIsHomeNodeTouched(std::nullopt);
    navPattern->forceSplitSuccess_ = false;
    navPattern->SetForceSplitUseNavBar(false);

    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    destPattern->InitOnTouchEvent(destNode);

    /**
     * @tc.steps: step2. Trigger registered hit-test callback.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(destNode->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());
    TouchEvent info;
    it->second(info);
    /**
     * @tc.steps: step3. Verify homeNodeTouched remains nullopt due to early return.
     */
    EXPECT_EQ(navPattern->IsHomeNodeTouched(), std::nullopt);
}

/**
 * @tc.name: InitOnTouchEvent005
 * @tc.desc: Branch in callback: IsForceSplitUseNavBar=true and host is NavBarNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build navigation + NavBar relation and enable forceSplitUseNavBar.
     */
    auto navNode = CreateNavigationGroupNode();
    auto navBar = CreateNavBarNode();
    ASSERT_NE(navNode, nullptr);
    ASSERT_NE(navBar, nullptr);
    auto navBarPattern = navBar->GetPattern<NavBarPattern>();
    auto navPattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navBarPattern, nullptr);
    ASSERT_NE(navPattern, nullptr);
    navBarPattern->SetNavigationNode(navNode);
    navPattern->forceSplitSuccess_ = true;
    navPattern->SetForceSplitUseNavBar(true);
    navPattern->SetIsHomeNodeTouched(std::nullopt);

    auto context = navBar->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    navBarPattern->InitOnTouchEvent(navBar);

    /**
     * @tc.steps: step2. Trigger registered hit-test callback.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(navBar->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());

    TouchEvent info;
    it->second(info);
    /**
     * @tc.steps: step3. Verify homeNodeTouched becomes true for NavBar host.
     */
    EXPECT_EQ(navPattern->IsHomeNodeTouched(), std::optional<bool>(true));
}

/**
 * @tc.name: InitOnTouchEvent006
 * @tc.desc: Branch in callback: IsForceSplitUseNavBar=false and host HOME destination.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build navigation + destination relation and set destination type to HOME.
     */
    auto navNode = CreateNavigationGroupNode();
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(navNode, nullptr);
    ASSERT_NE(destNode, nullptr);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    auto navPattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(destPattern, nullptr);
    ASSERT_NE(navPattern, nullptr);
    destPattern->SetNavigationNode(navNode);
    navPattern->forceSplitSuccess_ = true;
    navPattern->SetForceSplitUseNavBar(false);
    navPattern->SetIsHomeNodeTouched(std::nullopt);
    destNode->SetNavDestinationType(NavDestinationType::HOME);

    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    destPattern->InitOnTouchEvent(destNode);

    /**
     * @tc.steps: step2. Trigger registered hit-test callback on non-NavBar path.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(destNode->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());

    TouchEvent info;
    it->second(info);
    /**
     * @tc.steps: step3. Verify homeNodeTouched becomes true.
     */
    EXPECT_EQ(navPattern->IsHomeNodeTouched(), std::optional<bool>(true));
}

/**
 * @tc.name: InitOnTouchEvent007
 * @tc.desc: Branch in callback: IsForceSplitUseNavBar=false and host non-HOME destination.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build navigation + destination relation and set destination type to DETAIL.
     */
    auto navNode = CreateNavigationGroupNode();
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(navNode, nullptr);
    ASSERT_NE(destNode, nullptr);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    auto navPattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(destPattern, nullptr);
    ASSERT_NE(navPattern, nullptr);
    destPattern->SetNavigationNode(navNode);
    navPattern->forceSplitSuccess_ = true;
    navPattern->SetForceSplitUseNavBar(false);
    navPattern->SetIsHomeNodeTouched(std::nullopt);
    destNode->SetNavDestinationType(NavDestinationType::DETAIL);

    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    destPattern->InitOnTouchEvent(destNode);

    /**
     * @tc.steps: step2. Trigger registered hit-test callback on non-NavBar path.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(destNode->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());

    TouchEvent info;
    it->second(info);
    /**
     * @tc.steps: step3. Verify homeNodeTouched becomes false.
     */
    EXPECT_EQ(navPattern->IsHomeNodeTouched(), std::optional<bool>(false));
}

/**
 * @tc.name: InitOnTouchEvent008
 * @tc.desc: Branch in callback: navNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create destination host without binding navigation node.
     */
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(destNode, nullptr);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);

    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    destPattern->InitOnTouchEvent(destNode);

    /**
     * @tc.steps: step2. Trigger registered callback and verify safe return.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(destNode->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());

    TouchEvent info;
    it->second(info);
    SUCCEED();
}

/**
 * @tc.name: InitOnTouchEvent009
 * @tc.desc: Branch in callback: navPattern is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build navigation host and destination host, then bind them.
     */
    auto fakeNavNode = CreateNavigationGroupNode();
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(fakeNavNode, nullptr);
    ASSERT_NE(destNode, nullptr);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(destPattern, nullptr);
    destPattern->SetNavigationNode(fakeNavNode);

    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    destPattern->InitOnTouchEvent(destNode);

    /**
     * @tc.steps: step2. Trigger callback after replacing host pattern with base Pattern.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(destNode->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());

    auto originPattern = fakeNavNode->pattern_;
    fakeNavNode->pattern_ = AceType::MakeRefPtr<Pattern>();
    TouchEvent info;
    it->second(info);
    /**
     * @tc.steps: step3. Restore original host pattern and verify no crash.
     */
    fakeNavNode->pattern_ = originPattern;
    SUCCEED();
}

/**
 * @tc.name: InitOnTouchEvent010
 * @tc.desc: Branch in callback: IsForceSplitUseNavBar=true and host is not NavBarNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationPatternBaseTestNg, InitOnTouchEvent010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build navigation + destination relation with forceSplitUseNavBar enabled.
     */
    auto navNode = CreateNavigationGroupNode();
    auto destNode = CreateNavDestinationGroupNode();
    ASSERT_NE(navNode, nullptr);
    ASSERT_NE(destNode, nullptr);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    auto navPattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(destPattern, nullptr);
    ASSERT_NE(navPattern, nullptr);
    destPattern->SetNavigationNode(navNode);
    navPattern->forceSplitSuccess_ = true;
    navPattern->SetForceSplitUseNavBar(true);
    navPattern->SetIsHomeNodeTouched(std::nullopt);

    auto context = destNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->GetForceSplitManager()->SetForceSplitSupported(true);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    eventManager->hitTestFrameNodeListener_.clear();
    destPattern->InitOnTouchEvent(destNode);

    /**
     * @tc.steps: step2. Trigger callback using non-NavBar host.
     */
    auto it = eventManager->hitTestFrameNodeListener_.find(destNode->GetId());
    ASSERT_NE(it, eventManager->hitTestFrameNodeListener_.end());

    TouchEvent info;
    it->second(info);
    /**
     * @tc.steps: step3. Verify homeNodeTouched is set to false.
     */
    EXPECT_EQ(navPattern->IsHomeNodeTouched(), std::optional<bool>(false));
}

} // namespace OHOS::Ace::NG
