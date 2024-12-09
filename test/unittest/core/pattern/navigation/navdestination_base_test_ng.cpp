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

#include "mock_navigation_stack.h"

#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
RefPtr<NavigationGroupNode> CreateNavigationWithTitle(const RefPtr<MockNavigationStack>& stack,
    NavigationTitlebarOptions options, NavigationTitleMode titleMode = NavigationTitleMode::FREE,
    std::optional<std::string> mainTitle = std::nullopt, std::optional<std::string> subTitle = std::nullopt)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetTitleMode(titleMode);
    navigationModel.ParseCommonTitle(
        subTitle.has_value(), mainTitle.has_value(), subTitle.value_or(""), mainTitle.value_or(""));
    navigationModel.SetTitlebarOptions(std::move(options));
    return AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<NavDestinationGroupNode> CreateNavDestinationWithTitle(NavigationTitlebarOptions options,
    std::optional<std::string> mainTitle = std::nullopt, std::optional<std::string> subTitle = std::nullopt)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    navdestinationModel.ParseCommonTitle(
        subTitle.has_value(), mainTitle.has_value(), subTitle.value_or(""), mainTitle.value_or(""));
    navdestinationModel.SetTitlebarOptions(std::move(options));
    return AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}
} // namespace

class NavDestinationBaseTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void NavDestinationBaseTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

void NavDestinationBaseTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: GetTitleBarStyleTest001
 * @tc.desc: check whether the func GetTitleBarStyle of base class
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, GetTitleBarStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation with barStyle and check by function.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navDestinationPatternBase1 = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPatternBase1, nullptr);
    ASSERT_EQ(navDestinationPatternBase1->GetTitleBarStyle().value_or(BarStyle::STANDARD), BarStyle::SAFE_AREA_PADDING);
    /**
     * @tc.steps: step2. create navdestination with barStyle and check by function.
     */
    auto navDestination = CreateNavDestinationWithTitle(options, "navDestination");
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPatternBase2 = navDestination->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPatternBase2, nullptr);
    ASSERT_EQ(navDestinationPatternBase2->GetTitleBarStyle().value_or(BarStyle::STANDARD), BarStyle::SAFE_AREA_PADDING);
}

/**
 * @tc.name: SetTitleBarStyleTest001
 * @tc.desc: test SetTitleBarStyle titleBarStyle_ is BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetTitleBarStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check the value of MINI-mode title.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->titleBarStyle_ = BarStyle::STANDARD;
    navBarPattern->SetTitleBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, false);
}

/**
 * @tc.name: SetTitleBarStyleTest002
 * @tc.desc: test SetTitleBarStyle titleBarStyle_ is BarStyle::STACK
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetTitleBarStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check the value of MINI-mode title.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->titleBarStyle_ = BarStyle::STACK;
    navBarPattern->SetTitleBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, false);
}

/**
 * @tc.name: SetTitleBarStyleTest003
 * @tc.desc: test SetTitleBarStyle titleBarStyle_ is BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetTitleBarStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check the value of MINI-mode title.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STACK;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->titleBarStyle_ = BarStyle::SAFE_AREA_PADDING;
    navBarPattern->SetTitleBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, true);
}

/**
 * @tc.name: SetTitleBarStyleTest004
 * @tc.desc: test SetTitleBarStyle titleBarStyle_ is BarStyle::STANDARD and barStyle is BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetTitleBarStyleTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check the value of MINI-mode title.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->titleBarStyle_ = BarStyle::STANDARD;
    navBarPattern->SetTitleBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, true);
}

/**
 * @tc.name: SetToolBarStyleTest001
 * @tc.desc: test SetToolBarStyle toolBarStyle_ is BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetToolBarStyleTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->toolBarStyle_ = BarStyle::STANDARD;
    navBarPattern->SetToolBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, false);
}

/**
 * @tc.name: SetToolBarStyleTest002
 * @tc.desc: test SetToolBarStyle toolBarStyle_ is BarStyle::STACK
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetToolBarStyleTest002, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->toolBarStyle_ = BarStyle::STACK;
    navBarPattern->SetToolBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, false);
}

/**
 * @tc.name: SetToolBarStyleTest003
 * @tc.desc: test SetToolBarStyle toolBarStyle_ is BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetToolBarStyleTest003, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STACK;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->toolBarStyle_ = BarStyle::SAFE_AREA_PADDING;
    navBarPattern->SetToolBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, true);
}

/**
 * @tc.name: SetToolBarStyleTest004
 * @tc.desc: test SetToolBarStyle toolBarStyle_ is BarStyle::STANDARD and barStyle is BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetToolBarStyleTest004, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->toolBarStyle_ = BarStyle::STANDARD;
    navBarPattern->SetToolBarStyle(options.brOptions.barStyle);
    ASSERT_EQ(navBarPattern->safeAreaPaddingChanged_, true);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimationTest001
 * @tc.desc: test HandleTitleBarAndToolBarAnimation needRunToolBarAnimation and needRunTitleBarAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, HandleTitleBarAndToolBarAnimationTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->HandleTitleBarAndToolBarAnimation(navBarNode, true, true);
}

/**
 * @tc.name: OnTitleBarAnimationFinishTest001
 * @tc.desc: test OnTitleBarAnimationFinish function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, OnTitleBarAnimationFinishTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->titleBarAnimationCount_ = 2;
    navBarPattern->OnTitleBarAnimationFinish();
}

/**
 * @tc.name: OnTitleBarAnimationFinishTest002
 * @tc.desc: test OnTitleBarAnimationFinish function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, OnTitleBarAnimationFinishTest002, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->titleBarAnimationCount_ = 0;
    navBarPattern->OnTitleBarAnimationFinish();
}

/**
 * @tc.name: OnToolBarAnimationFinishTest001
 * @tc.desc: test OnToolBarAnimationFinish function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, OnToolBarAnimationFinishTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->toolBarAnimationCount_ = 2;
    navBarPattern->OnToolBarAnimationFinish();
}

/**
 * @tc.name: OnToolBarAnimationFinishTest002
 * @tc.desc: test OnToolBarAnimationFinish function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, OnToolBarAnimationFinishTest002, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->toolBarAnimationCount_ = 0;
    navBarPattern->OnToolBarAnimationFinish();
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacityTest001
 * @tc.desc: test UpdateToolBarAndDividerTranslateAndOpacity function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacityTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    bool hide = false;
    RefPtr<NavToolbarNode> toolBarNode = nullptr;
    float toolBarHeight = 1.0;
    RefPtr<FrameNode> toolbarDividerNode = nullptr;
    float toolBarDividerHeight = 2.0;
    navBarPattern->UpdateToolBarAndDividerTranslateAndOpacity(
        hide, toolBarNode, toolBarHeight, toolbarDividerNode, toolBarDividerHeight);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacityTest002
 * @tc.desc: test UpdateToolBarAndDividerTranslateAndOpacity function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacityTest002, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    bool hide = false;
    // set toolBarNode is not nullptr
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolBarNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    float toolBarHeight = 1.0;
    RefPtr<FrameNode> toolbarDividerNode = nullptr;
    float toolBarDividerHeight = 2.0;
    navBarPattern->UpdateToolBarAndDividerTranslateAndOpacity(
        hide, toolBarNode, toolBarHeight, toolbarDividerNode, toolBarDividerHeight);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacityTest003
 * @tc.desc: test UpdateToolBarAndDividerTranslateAndOpacity function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacityTest003, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    bool hide = false;
    // set toolBarNode is not nullptr
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolBarNode->renderContext_ = nullptr;
    float toolBarHeight = 1.0;
    RefPtr<FrameNode> toolbarDividerNode = nullptr;
    float toolBarDividerHeight = 2.0;
    navBarPattern->UpdateToolBarAndDividerTranslateAndOpacity(
        hide, toolBarNode, toolBarHeight, toolbarDividerNode, toolBarDividerHeight);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacityTest004
 * @tc.desc: test UpdateToolBarAndDividerTranslateAndOpacity function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacityTest004, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    bool hide = false;
    // set toolBarNode is not nullptr
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolBarNode->renderContext_ = nullptr;
    float toolBarHeight = 1.0;
    RefPtr<FrameNode> toolbarDividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    float toolBarDividerHeight = 2.0;
    navBarPattern->UpdateToolBarAndDividerTranslateAndOpacity(
        hide, toolBarNode, toolBarHeight, toolbarDividerNode, toolBarDividerHeight);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacityTest005
 * @tc.desc: test UpdateToolBarAndDividerTranslateAndOpacity function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacityTest005, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    bool hide = false;
    // set toolBarNode is not nullptr
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolBarNode->renderContext_ = nullptr;
    float toolBarHeight = 1.0;
    RefPtr<FrameNode> toolbarDividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    toolbarDividerNode->renderContext_ = nullptr;
    float toolBarDividerHeight = 2.0;
    navBarPattern->UpdateToolBarAndDividerTranslateAndOpacity(
        hide, toolBarNode, toolBarHeight, toolbarDividerNode, toolBarDividerHeight);
}

/**
 * @tc.name: UpdateToolBarAndDividerTranslateAndOpacityTest006
 * @tc.desc: test UpdateToolBarAndDividerTranslateAndOpacity function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateToolBarAndDividerTranslateAndOpacityTest006, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    bool hide = false;
    // set toolBarNode is not nullptr
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolBarNode->renderContext_ = nullptr;
    float toolBarHeight = 1.0;
    RefPtr<FrameNode> toolbarDividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    toolbarDividerNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    float toolBarDividerHeight = 2.0;
    navBarPattern->UpdateToolBarAndDividerTranslateAndOpacity(
        hide, toolBarNode, toolBarHeight, toolbarDividerNode, toolBarDividerHeight);
}
} // namespace OHOS::Ace::NG
