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
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF = 0.5;
constexpr float FRAME_WIDTH = 300.0f;
constexpr float FRAME_HEIGHT = 400.0f;
constexpr float DEFAULT_HEIGHT = 0.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float REMOVE_CLIP_SIZE = 100000.0f;
constexpr float CONTENT_OFFSET_PERCENT = 0.2f;

RefPtr<NavDestinationNodeBase> CreateNavDestinationNodeBase()
{
    auto pattern = AceType::MakeRefPtr<NavDestinationPatternBase>();
    if (pattern) {
        return AceType::MakeRefPtr<NavDestinationNodeBase>(V2::NAVDESTINATION_VIEW_ETS_TAG, 0, pattern);
    }
    return nullptr;
}

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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
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

/**
 * @tc.name: SetToolBarMenuOptionsTest001
 * @tc.desc: Branch: if (options_.bgOptions.color.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetToolBarMenuOptionsTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationMenuOptions opt;
    opt.mbOptions.bgOptions.color = std::make_optional(Color(0xff0000ff));
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->SetToolBarMenuOptions(opt);
    EXPECT_EQ(navBarPattern->GetToolBarMenuOptions().mbOptions.bgOptions.color.value(), Color(0xff0000ff));
}

/**
 * @tc.name: SetMenuOptionsTest001
 * @tc.desc: Branch: if (options_.bgOptions.color.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, SetMenuOptionsTest001, TestSize.Level1)
{
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationMenuOptions opt;
    opt.mbOptions.bgOptions.color = std::make_optional(Color(0xff0000ff));
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->SetMenuOptions(opt);
    EXPECT_EQ(navBarPattern->GetMenuOptions().mbOptions.bgOptions.color.value(), Color(0xff0000ff));
}

/**
 * @tc.name: CalcFullClipRectForTransitionTest001
 * @tc.desc: Branch: rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                   rotateAngle_.has_value() => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcFullClipRectForTransitionTest001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcFullClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH, REMOVE_CLIP_SIZE));
}

/**
 * @tc.name: CalcFullClipRectForTransitionTest002
 * @tc.desc: Branch: rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                   rotateAngle_.has_value() => true
 *
 *           Branch: if (angle == ROTATION_90 || angle == ROTATION_270) {
 *                   angle == ROTATION_90 => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcFullClipRectForTransitionTest002, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(ROTATION_90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcFullClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(REMOVE_CLIP_SIZE, FRAME_HEIGHT));
}

/**
 * @tc.name: CalcFullClipRectForTransitionTest003
 * @tc.desc: Branch: rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                   rotateAngle_.has_value() => true
 *
 *           Branch: if (angle == ROTATION_90 || angle == ROTATION_270) {
 *                   angle == ROTATION_270 => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcFullClipRectForTransitionTest003, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(ROTATION_270);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcFullClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(REMOVE_CLIP_SIZE, FRAME_HEIGHT));
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest001
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH * HALF, REMOVE_CLIP_SIZE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest002
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest002, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH * HALF, REMOVE_CLIP_SIZE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

 /**
 * @tc.name: CalcHalfClipRectForTransitionTest003
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => false
 *                   } else if (angle == ROTATION_0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest003, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH * HALF, REMOVE_CLIP_SIZE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest004
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest004, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH * HALF, REMOVE_CLIP_SIZE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest005
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => false
 *                   if (angle == ROTATION_90) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest005, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(REMOVE_CLIP_SIZE, FRAME_HEIGHT * HALF));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest006
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => true
 *                   if (angle == ROTATION_90) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest006, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, FRAME_HEIGHT * HALF));
    EXPECT_EQ(size, SizeF(REMOVE_CLIP_SIZE, FRAME_HEIGHT * HALF));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest007
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest007, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(180);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH * HALF, REMOVE_CLIP_SIZE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest008
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => true
 *                   } else if (angle == ROTATION_180) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest008, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(180);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF, 0.0f));
    EXPECT_EQ(size, SizeF(FRAME_WIDTH * HALF, REMOVE_CLIP_SIZE));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest009
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => false
 *                   if (angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest009, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(270);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, FRAME_HEIGHT * HALF));
    EXPECT_EQ(size, SizeF(REMOVE_CLIP_SIZE, FRAME_HEIGHT * HALF));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcHalfClipRectForTransitionTest010
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 *                   if (AceApplicationInfo::GetInstance().IsRightToLeft()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcHalfClipRectForTransitionTest010, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(270);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto rect = node->CalcHalfClipRectForTransition(frameSize);
    auto offset = rect.GetOffset();
    auto size = rect.GetSize();
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(size, SizeF(REMOVE_CLIP_SIZE, FRAME_HEIGHT * HALF));
    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPushStartTest001
 * @tc.desc: Branch: if (!transitionIn) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushStartTest001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushStart(frameSize, false);
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPushStartTest002
 * @tc.desc: Branch: auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                   rotateAngle_.has_value() => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushStartTest002, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    auto isRTL = AceApplicationInfo::GetInstance().IsRightToLeft() ? -1.0f : 1.0f;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF * isRTL, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPushStartTest003
 * @tc.desc: Branch: if (angle == ROTATION_90 || angle == ROTATION_270) {
 *                   angle == ROTATION_90 => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushStartTest003, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(ROTATION_90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto isRTL = AceApplicationInfo::GetInstance().IsRightToLeft() ? -1.0f : 1.0f;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * HALF * isRTL, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPushStartTest004
 * @tc.desc: Branch: if (angle == ROTATION_90 || angle == ROTATION_270) {
 *                   angle == ROTATION_270 => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushStartTest004, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->SetPageRotateAngle(ROTATION_270);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    auto isRTL = AceApplicationInfo::GetInstance().IsRightToLeft() ? -1.0f : 1.0f;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * HALF * isRTL, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest001
 * @tc.desc: Branch: if (transitionIn) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, true);
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest002
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest002, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest003
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest003, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest004
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest004, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(180);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest005
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest005, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(180);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest006
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest006, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(270);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPushEndTest007
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPushEndTest007, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(270);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    offset = node->CalcTranslateForTransitionPushEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest001
 * @tc.desc: Branch: if (!transitionIn) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, false);
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest002
 * @tc.desc: Branch: if (!transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest002, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest003
 * @tc.desc: Branch: if (!transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest003, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest004
 * @tc.desc: Branch: if (!transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest004, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(180);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest005
 * @tc.desc: Branch: if (!transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest005, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(180);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest006
 * @tc.desc: Branch: if (!transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest006, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(-FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(270);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(-FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopStartTest007
 * @tc.desc: Branch: if (!transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopStartTest007, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    node->SetPageRotateAngle(270);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    offset = node->CalcTranslateForTransitionPopStart(frameSize, true);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * CONTENT_OFFSET_PERCENT, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest001
 * @tc.desc: Branch: if (transitionIn) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, true);
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest002
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest002, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest003
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => false
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest003, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    auto angle = node->GetPageRotateAngle();
    ASSERT_FALSE(angle.has_value());
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * HALF, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest004
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest004, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF, 0.0f));

    node->SetPageRotateAngle(180);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_WIDTH * HALF, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest005
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest005, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    node->SetPageRotateAngle(0);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_0);
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * HALF, 0.0f));

    node->SetPageRotateAngle(180);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_180);
    offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_WIDTH * HALF, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest006
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => false
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest006, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;

    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * HALF, 0.0f));

    node->SetPageRotateAngle(270);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(FRAME_HEIGHT * HALF, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CalcTranslateForTransitionPopEndTest007
 * @tc.desc: Branch: if (transitionIn) { => false
 *                   auto angle = rotateAngle_.has_value() ? rotateAngle_.value() : ROTATION_0;
 *                       rotateAngle_.has_value() => true
 *                   GetLanguageDirection()
 *                       AceApplicationInfo::GetInstance().IsRightToLeft() => true
 *                   if (angle == ROTATION_90 || angle == ROTATION_270) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcTranslateForTransitionPopEndTest007, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);

    auto frameSize = SizeF{ FRAME_WIDTH, FRAME_HEIGHT };
    bool backupValue = AceApplicationInfo::GetInstance().isRightToLeft_;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    node->SetPageRotateAngle(90);
    auto angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_90);
    auto offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_HEIGHT * HALF, 0.0f));

    node->SetPageRotateAngle(270);
    angle = node->GetPageRotateAngle();
    ASSERT_TRUE(angle.has_value());
    ASSERT_EQ(angle.value(), ROTATION_270);
    offset = node->CalcTranslateForTransitionPopEnd(frameSize, false);
    EXPECT_EQ(offset, OffsetF(-FRAME_HEIGHT * HALF, 0.0f));

    AceApplicationInfo::GetInstance().isRightToLeft_ = backupValue;
}

/**
 * @tc.name: CustomizeExpandSafeArea001
 * @tc.desc: test CustomizeExpandSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CustomizeExpandSafeArea001, TestSize.Level1)
{
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->isCustomExpandRunning_ = true;
    auto ret = node->CustomizeExpandSafeArea();
    EXPECT_EQ(false, ret);
}

/**
 * @tc.name: CustomizeExpandSafeArea002
 * @tc.desc: test CustomizeExpandSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CustomizeExpandSafeArea002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->isCustomExpandRunning_ = false;
    /**
     * @tc.steps:step2. set rotateAngle_.has_value() == false and viewportConfig_ is nullptr.
     */
    node->viewportConfig_ = nullptr;
    auto ret = node->CustomizeExpandSafeArea();
    EXPECT_EQ(false, ret);
}

/**
 * @tc.name: CustomizeExpandSafeArea003
 * @tc.desc: test CustomizeExpandSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CustomizeExpandSafeArea003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->isCustomExpandRunning_ = false;
    /**
     * @tc.steps:step2. set rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     * * @tc.expected: step2. angle == ROTATION_270.
     */
    node->SetPageRotateAngle(ROTATION_270);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    auto ret = node->CustomizeExpandSafeArea();
    EXPECT_EQ(true, ret);
}

/**
 * @tc.name: CustomizeExpandSafeArea004
 * @tc.desc: test CustomizeExpandSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CustomizeExpandSafeArea004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->isCustomExpandRunning_ = false;
    /**
     * @tc.steps:step2. set rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     * @tc.expected: step2. angle == ROTATION_90.
     */
    node->SetPageRotateAngle(ROTATION_90);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    auto ret = node->CustomizeExpandSafeArea();
    EXPECT_EQ(true, ret);
}

/**
 * @tc.name: CustomizeExpandSafeArea005
 * @tc.desc: test CustomizeExpandSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CustomizeExpandSafeArea005, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    node->isCustomExpandRunning_ = false;
    /**
     * @tc.steps:step2. set rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     * @tc.expected: step2. angle == ROTATION_180.
     */
    node->SetPageRotateAngle(ROTATION_180);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    auto ret = node->CustomizeExpandSafeArea();
    EXPECT_EQ(true, ret);
}

/**
 * @tc.name: MeasureTest001
 * @tc.desc: test Measure function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, MeasureTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == false and viewportConfig_ is nullptr.
     */
    node->viewportConfig_ = nullptr;
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    EXPECT_EQ(false, node->isRotated_);
    node->SetIsRotated(true);
    node->Measure(LayoutConstraint);
    EXPECT_EQ(true, node->isRotated_);
}

/**
 * @tc.name: MeasureTest002
 * @tc.desc: test Measure function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, MeasureTest002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and viewportConfig_ is nullptr.
     * @tc.expected: step2. angle == ROTATION_0.
     */
    node->SetPageRotateAngle(ROTATION_0);
    node->viewportConfig_ = nullptr;
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    EXPECT_EQ(false, node->isRotated_);
    node->SetIsRotated(true);
    node->Measure(LayoutConstraint);
    EXPECT_EQ(ROTATION_0, node->rotateAngle_.value());
    EXPECT_EQ(true, node->isRotated_);
}

/**
 * @tc.name: MeasureTest003
 * @tc.desc: test Measure function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, MeasureTest003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     * @tc.expected: step2. angle != ROTATION_0.
     */
    node->SetPageRotateAngle(ROTATION_180);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    EXPECT_EQ(false, node->isRotated_);
    node->SetIsRotated(true);
    node->Measure(LayoutConstraint);
    EXPECT_EQ(ROTATION_180, node->rotateAngle_.value());
    EXPECT_EQ(true, node->isRotated_);
}

/**
 * @tc.name: LayoutTest001
 * @tc.desc: test Layout function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, LayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == false and viewportConfig_ is nullptr.
     */
    node->viewportConfig_ = nullptr;
    EXPECT_EQ(true, node->isSizeMatchNavigation_);
    node->SetIsSizeMatchNavigation(false);
    node->Layout();
    EXPECT_EQ(false, node->isSizeMatchNavigation_);
}

/**
 * @tc.name: LayoutTest002
 * @tc.desc: test Layout function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, LayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     * @tc.expected: step2. angle != ROTATION_0.
     */
    node->SetPageRotateAngle(ROTATION_180);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    EXPECT_EQ(true, node->isSizeMatchNavigation_);
    node->Layout();
    EXPECT_EQ(ROTATION_180, node->rotateAngle_.value());
}

/**
 * @tc.name: LayoutTest003
 * @tc.desc: test Layout function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, LayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     * @tc.expected: step2. angle == ROTATION_0
     */
    node->SetPageRotateAngle(ROTATION_0);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    EXPECT_EQ(true, node->isSizeMatchNavigation_);
    node->SetIsSizeMatchNavigation(false);
    node->Layout();
    EXPECT_EQ(ROTATION_0, node->rotateAngle_.value());
    EXPECT_EQ(false, node->isSizeMatchNavigation_);
}

/**
 * @tc.name: AdjustLayoutConstarintIfNeededTest001
 * @tc.desc: test AdjustLayoutConstarintIfNeeded function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, AdjustLayoutConstarintIfNeededTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == false and viewportConfig_ is nullptr.
     */
    node->SetPageRotateAngle(ROTATION_0);
    node->viewportConfig_ = nullptr;
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    auto ret = node->AdjustLayoutConstarintIfNeeded(LayoutConstraint);
    EXPECT_EQ(ret.maxSize.height_, DEFAULT_ROOT_HEIGHT);
}

/**
 * @tc.name: AdjustLayoutConstarintIfNeededTest002
 * @tc.desc: test AdjustLayoutConstarintIfNeeded function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, AdjustLayoutConstarintIfNeededTest002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and viewportConfig_ is not nullptr.
     */
    node->SetPageRotateAngle(ROTATION_0);
    node->viewportConfig_ = AceType::MakeRefPtr<PageViewportConfig>();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { DEFAULT_ROOT_WIDTH, DEFAULT_ROOT_HEIGHT };
    auto ret = node->AdjustLayoutConstarintIfNeeded(LayoutConstraint);
    EXPECT_EQ(ret.minSize.height_, DEFAULT_HEIGHT);
}

/**
 * @tc.name: GetParentGlobalOffsetWithSafeAreaTest001
 * @tc.desc: test GetParentGlobalOffsetWithSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, GetParentGlobalOffsetWithSafeAreaTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true.
     */
    node->SetPageRotateAngle(ROTATION_0);
    bool checkBoundary = true;
    bool checkPosition = false;
    auto testF = node->GetParentGlobalOffsetWithSafeArea(checkBoundary, checkPosition);
    EXPECT_EQ(testF, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: GetParentGlobalOffsetWithSafeAreaTest002
 * @tc.desc: test GetParentGlobalOffsetWithSafeArea function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, GetParentGlobalOffsetWithSafeAreaTest002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == false.
     */
    bool checkBoundary = true;
    bool checkPosition = false;
    auto testF = node->GetParentGlobalOffsetWithSafeArea(checkBoundary, checkPosition);
    EXPECT_EQ(testF, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: CalcContentTranslateForDialogTest001
 * @tc.desc: test CalcContentTranslateForDialog function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcContentTranslateForDialogTest001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and angle is ROTATION_0.
     */
    auto options = TranslateOptions(0.0f, 400.0f, 0.0f);
    node->SetPageRotateAngle(ROTATION_0);
    SizeF size(400.0f, 400.0f);
    auto testF = node->CalcContentTranslateForDialog(size);
    EXPECT_EQ(testF, options);
}

/**
 * @tc.name: CalcContentTranslateForDialogTest002
 * @tc.desc: test CalcContentTranslateForDialog function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcContentTranslateForDialogTest002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and angle is ROTATION_90.
     */
    auto options = TranslateOptions(300.0f, 0.0f, 0.0f);
    node->SetPageRotateAngle(ROTATION_90);
    SizeF size(300.0f, 400.0f);
    auto testF = node->CalcContentTranslateForDialog(size);
    EXPECT_EQ(testF, options);
}

/**
 * @tc.name: CalcContentTranslateForDialogTest003
 * @tc.desc: test CalcContentTranslateForDialog function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcContentTranslateForDialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and angle is ROTATION_180.
     */
    auto options = TranslateOptions(0.0f, -400.0f, 0.0f);
    node->SetPageRotateAngle(ROTATION_180);
    SizeF size(400.0, 400.0);
    auto testF = node->CalcContentTranslateForDialog(size);
    EXPECT_EQ(testF, options);
}

/**
 * @tc.name: CalcContentTranslateForDialogTest004
 * @tc.desc: test CalcContentTranslateForDialog function
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, CalcContentTranslateForDialogTest004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavDestinationNodeBase node.
     */
    auto node = CreateNavDestinationNodeBase();
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps:step2. rotateAngle_.has_value() == true and angle is ROTATION_270.
     */
    auto options = TranslateOptions(-400.0f, 0.0f, 0.0f);
    node->SetPageRotateAngle(ROTATION_270);
    SizeF size(400.0, 400.0);
    auto testF = node->CalcContentTranslateForDialog(size);
    EXPECT_EQ(testF, options);
}

/**
 * @tc.name: NavigationStack001
 * @tc.desc: Test GetNavDesNameByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, NavigationStack001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavigationStack node.
     */
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    int32_t index = 0;
    auto ret = navigationStack->GetNavDesNameByIndex(index);
    EXPECT_EQ("", ret);
}

/**
 * @tc.name: NavigationStack002
 * @tc.desc: Test GetNavDesNameByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, NavigationStack002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavigationStack node.
     */
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    /**
     * @tc.steps:step2. index > Size().
     */
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    navigationStack->navPathList_.emplace_back(std::make_pair("pageOne", frameNode));
    EXPECT_NE(frameNode, nullptr);
    int32_t index = 20;
    auto ret = navigationStack->GetNavDesNameByIndex(index);
    EXPECT_EQ("", ret);
}

/**
 * @tc.name: NavigationStack003
 * @tc.desc: Test GetNavDesNameByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, NavigationStack003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create NavigationStack node.
     */
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    /**
     * @tc.steps:step2. index < Size().
     */
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    navigationStack->navPathList_.emplace_back(std::make_pair("pageOne", frameNode));
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    navigationStack->navPathList_.emplace_back(std::make_pair("pageTwo", tempNode));
    int32_t index = 1;
    auto ret = navigationStack->GetNavDesNameByIndex(index);
    EXPECT_EQ("pageTwo", ret);
}

/**
 * @tc.name: RemoveAnimationTest001
 * @tc.desc: Test RemoveAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, RemoveAnimationTest001, TestSize.Level1)
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
    auto navDestinationPatternBase = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPatternBase, nullptr);
    /**
     * @tc.steps:step2. add Animation to barAnimations_ and remove animaton.
     */
    AnimationOption option;
    auto propertyCallback = []() {};
    auto finishCallback = []() {};
    auto animation = AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
    EXPECT_EQ(0, navDestinationPatternBase->barAnimations_.size());
    navDestinationPatternBase->barAnimations_.emplace(101, animation);
    int32_t id = 101;
    EXPECT_EQ(1, navDestinationPatternBase->barAnimations_.size());
    navDestinationPatternBase->RemoveAnimation(id);
    EXPECT_EQ(0, navDestinationPatternBase->barAnimations_.size());
}

/**
 * @tc.name: RemoveAnimationTest002
 * @tc.desc: Test RemoveAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, RemoveAnimationTest002, TestSize.Level1)
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
    auto navDestinationPatternBase = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPatternBase, nullptr);
    /**
     * @tc.steps:step2. add Animation to barAnimations_ and don't remove animaton.
     */
    AnimationOption option;
    auto propertyCallback = []() {};
    auto finishCallback = []() {};
    auto animation = AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
    EXPECT_EQ(0, navDestinationPatternBase->barAnimations_.size());
    navDestinationPatternBase->barAnimations_.emplace(101, animation);
    int32_t id = 300;
    EXPECT_EQ(1, navDestinationPatternBase->barAnimations_.size());
    navDestinationPatternBase->RemoveAnimation(id);
    EXPECT_EQ(1, navDestinationPatternBase->barAnimations_.size());
}

/**
 * @tc.name: UpdateBarItemNodeWithItemTest001
 * @tc.desc: Test UpdateBarItemNodeWithItem function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateBarItemNodeWithItemTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. obtain barItem nodes.
     * @tc.expected: barItem node is not nullptr.
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 1, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    /**
     * @tc.steps: step2. barItem.text.has_value() == false.
     */
    BarItem barItem;
    barItem.action = []() {};
    barItem.icon = "page";
    bool isButtonEnabled = true;
    RefPtr<NavigationBarTheme> theme = AceType::MakeRefPtr<NavigationBarTheme>();
    NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, barItem, isButtonEnabled, theme);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_EQ(NavigationTitleUtil::GetSubtitleString(titleBarNode), "");
}

/**
 * @tc.name: UpdateBarItemNodeWithItemTest002
 * @tc.desc: Test UpdateBarItemNodeWithItem function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateBarItemNodeWithItemTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. obtain barItem nodes.
     * @tc.expected: barItem node is not nullptr.
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 1, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    /**
     * @tc.steps: step2. barItem.text.has_value() == true and barItem.icon.has_value() == false.
     * @tc.expected: barItem.iconSymbol.has_value() == false.
     */
    BarItem barItem;
    barItem.action = []() {};
    barItem.text = "aaaaa";
    bool isButtonEnabled = true;
    RefPtr<NavigationBarTheme> theme = AceType::MakeRefPtr<NavigationBarTheme>();
    NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, barItem, isButtonEnabled, theme);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_EQ(NavigationTitleUtil::GetSubtitleString(titleBarNode), "");
}

/**
 * @tc.name: UpdateBarItemNodeWithItemTest003
 * @tc.desc: Test UpdateBarItemNodeWithItem function.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, UpdateBarItemNodeWithItemTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. obtain barItem nodes.
     * @tc.expected: barItem node is not nullptr.
     */
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, 1, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    /**
     * @tc.steps: step2. barItem.text.value() is empty and barItem.icon.has_value() == false.
     * @tc.expected: barItem.iconSymbol.value() is nullptr.
     */
    BarItem barItem;
    barItem.text = "";
    barItem.iconSymbol = nullptr;
    bool isButtonEnabled = true;
    RefPtr<NavigationBarTheme> theme = AceType::MakeRefPtr<NavigationBarTheme>();
    NavigationTitleUtil::UpdateBarItemNodeWithItem(barItemNode, barItem, isButtonEnabled, theme);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    EXPECT_EQ(NavigationTitleUtil::GetSubtitleString(titleBarNode), "");
}
} // namespace OHOS::Ace::NG
