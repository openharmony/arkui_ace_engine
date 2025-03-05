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

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;

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

RefPtr<NavigationGroupNode> CreateNavigationWithToolBar(const RefPtr<MockNavigationStack>& stack,
    NavigationToolbarOptions&& options, std::vector<NG::BarItem>&& toolBarItems)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack(stack);
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
    navigationModel.SetToolbarOptions(std::move(options));
    return AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<NavDestinationGroupNode> CreateNavDestinationWithTitle(
    NavigationTitlebarOptions options, std::optional<std::string> mainTitle, std::optional<std::string> subTitle)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    navdestinationModel.ParseCommonTitle(
        subTitle.has_value(), mainTitle.has_value(), subTitle.value_or(""), mainTitle.value_or(""));
    navdestinationModel.SetTitlebarOptions(std::move(options));
    return AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<NavDestinationGroupNode> CreateNavDestinationWithToolBar(
    NavigationToolbarOptions&& options, std::vector<NG::BarItem>&& toolBarItems)
{
    NavDestinationModelNG navdestinationModel;
    navdestinationModel.Create();
    navdestinationModel.SetToolbarConfiguration(std::move(toolBarItems));
    navdestinationModel.SetToolBarOptions(std::move(options));
    return AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
}
} // namespace

class BarStyleTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
};

void BarStyleTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

void BarStyleTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    MockContainer::Current()->SetNavigationRoute(AceType::MakeRefPtr<MockNavigationRoute>(""));
}

void BarStyleTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: BarStyleTest001
 * @tc.desc: Test whether can pass 'barStyle' when creating navigation and navDestination
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, BarStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with title and barStyle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FREE, "navigation", std::nullopt);
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarOfNavBar = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarOfNavBar, nullptr);
    auto titleOfNavBar = titleBarOfNavBar->GetTitle();
    ASSERT_NE(titleOfNavBar, nullptr);
    /**
     * @tc.steps: step3. check whether the barStyle is set correctlly.
     */
    // check the barStyle in navBar's title bar
    auto patternOfNavBarTitleBar = titleBarOfNavBar->GetPattern<TitleBarPattern>();
    ASSERT_NE(patternOfNavBarTitleBar, nullptr);
    auto navBarTitleBarStyle =
        patternOfNavBarTitleBar->GetTitleBarOptions().brOptions.barStyle.value_or(BarStyle::STANDARD);
    ASSERT_EQ(navBarTitleBarStyle, candidateBarStyle);
    // check the barStyle in navBar's pattern
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    ASSERT_EQ(navBarPattern->GetTitleBarStyle().value_or(BarStyle::STANDARD), candidateBarStyle);
    /**
     * @tc.steps: step3. create destination with barStyle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = candidateBarStyle;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", std::nullopt);
    ASSERT_NE(navDestination, nullptr);
    auto titleBarOfNavDest = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    ASSERT_NE(titleBarOfNavDest, nullptr);
    auto titleOfNavDest = titleBarOfNavDest->GetTitle();
    ASSERT_NE(titleOfNavDest, nullptr);
    /**
     * @tc.steps: step4. check whether the barStyle of dest is set correctlly.
     */
    // check the barStyle in navDestination's title bar
    auto patternOfNavDestTitleBar = titleBarOfNavDest->GetPattern<TitleBarPattern>();
    ASSERT_NE(patternOfNavDestTitleBar, nullptr);
    auto destTitleBarStyle =
        patternOfNavDestTitleBar->GetTitleBarOptions().brOptions.barStyle.value_or(BarStyle::STANDARD);
    ASSERT_EQ(destTitleBarStyle, candidateBarStyle);
    // check the barStyle in navDestination's pattern
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetTitleBarStyle().value_or(BarStyle::STANDARD), candidateBarStyle);
}

/**
 * @tc.name: SafeAreaPaddingTest002
 * @tc.desc: Test whether navBar's safe area padding set without subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::MINI, "navigationMainTitle", std::nullopt);
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPadding, nullptr);
    ASSERT_EQ(safeAreaPadding->top.value_or(CalcLength(0.0f)),
        CalcLength(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest003
 * @tc.desc: Test whether navBar's safe area padding set without subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", std::nullopt);
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPadding, nullptr);
    ASSERT_EQ(safeAreaPadding->top.value_or(CalcLength(0.0f)),
        CalcLength(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest004
 * @tc.desc: Test whether navBar's safe area padding set without subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FREE, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPadding, nullptr);
    ASSERT_EQ(safeAreaPadding->top.value_or(CalcLength(0.0f)),
        CalcLength(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest005
 * @tc.desc: Test whether navBar's safe area padding set with subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::MINI, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPadding, nullptr);
    ASSERT_EQ(safeAreaPadding->top.value_or(CalcLength(0.0f)),
        CalcLength(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest006
 * @tc.desc: Test whether navBar's safe area padding set with subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPadding, nullptr);
    ASSERT_EQ(safeAreaPadding->top.value_or(CalcLength(0.0f)),
        CalcLength(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest007
 * @tc.desc: Test whether navDest's safe area padding set with subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", std::nullopt);
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    ASSERT_NE(safeAreaPadding, nullptr);
    ASSERT_EQ(safeAreaPadding->top.value_or(CalcLength(0.0f)),
        CalcLength(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: titleBarStyleTest001
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::STANDARD && !navBar.hasSubtitle)
 *           Condition: navBar.titleBarStyle == BarStyle::STANDARD && !navBar.hasSubtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STANDARD and only mainTitle.
     */
    auto candidateBarStyle = BarStyle::STANDARD;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: titleBarStyleTest002
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::STANDARD && navBar.hasSubtitle)
 *           Condition: navBar.titleBarStyle == BarStyle::STANDARD && navBar.hasSubtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STANDARD, main title and subtitle.
     */
    auto candidateBarStyle = BarStyle::STANDARD;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: titleBarStyleTest003
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STANDARD && !navDestination.hasSubtitle)
 *           Condition: navDestination.titleBarStyle == BarStyle::STANDARD && !navDestination.hasSubtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STANDARD and only mainTitle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = BarStyle::STANDARD;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", std::nullopt);
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: titleBarStyleTest004
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STANDARD && navDestination.hasSubtitle)
 *           Condition: navDestination.titleBarStyle == BarStyle::STANDARD && navDestination.hasSubtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STANDARD and only mainTitle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = BarStyle::STANDARD;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", "navDestinationSub");
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}


/**
 * @tc.name: titleBarStyleTest010
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::STANDARD)
 *           Condition: navBar.titleBarStyle == BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STANDARD, main title and subtitle.
     */
    auto candidateBarStyle = BarStyle::STANDARD;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto geometryNode = navBarContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_NE(marginFrameOffset.GetY(), 0.0f);
}

/**
 * @tc.name: titleBarStyleTest011
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::STACK)
 *           Condition: navBar.titleBarStyle == BarStyle::STACK
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STACK, main title and subtitle.
     */
    auto candidateBarStyle = BarStyle::STACK;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto geometryNode = navBarContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_EQ(marginFrameOffset.GetY(), 0.0f);
}

/**
 * @tc.name: titleBarStyleTest012
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::SAFE_AREA_PADDING)
 *           Condition: navBar.titleBarStyle == BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING, main title and subtitle.
     */
    auto candidateBarStyle = BarStyle::SAFE_AREA_PADDING;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto geometryNode = navBarContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_EQ(marginFrameOffset.GetY(), 0.0f);
}

/**
 * @tc.name: titleBarStyleTest013
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STANDARD)
 *           Condition: navDestination.titleBarStyle == BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STANDARD and only mainTitle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = BarStyle::STANDARD;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", "navDestinationSub");
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto geometryNode = navDestinationContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_NE(marginFrameOffset.GetY(), 0.0f);
}

/**
 * @tc.name: titleBarStyleTest014
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STACK)
 *           Condition: navDestination.titleBarStyle == BarStyle::STACK
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STACK and only mainTitle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = BarStyle::STACK;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", "navDestinationSub");
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto geometryNode = navDestinationContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_EQ(marginFrameOffset.GetY(), 0.0f);
}

/**
 * @tc.name: titleBarStyleTest015
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::STANDARD && navBar.titleMode == MINI && navBar.hasSubTitle)
 *           Condition: navBar.titleBarStyle == BarStyle::STANDARD && navBar.titleMode == MINI && navBar.hasSubTitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STANDARD, main title and subtitle.
     */
    auto candidateBarStyle = BarStyle::STANDARD;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::MINI, "navigationMainTitle", "navigationSubTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto geometryNode = navBarContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_EQ(marginFrameOffset.GetY(), DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: titleBarStyleTest016
 * @tc.desc: Branch: if (navBar.titleBarStyle == BarStyle::STANDARD && navBar.titleMode == MINI && !navBar.hasSubTitle)
 *           Condition: navBar.titleBarStyle == BarStyle::STANDARD && navBar.titleMode == MINI && !navBar.hasSubTitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STANDARD, main title and subtitle.
     */
    auto candidateBarStyle = BarStyle::STANDARD;
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = candidateBarStyle;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::MINI, "navigationMainTitle", std::nullopt);
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto geometryNode = navBarContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_EQ(marginFrameOffset.GetY(), SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: titleBarStyleTest017
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STANDARD)
 *           Condition: navDestination.titleBarStyle == BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, titleBarStyleTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STANDARD and only mainTitle.
     */
    NavigationTitlebarOptions optionsOfNavDest;
    optionsOfNavDest.brOptions.barStyle = BarStyle::STANDARD;
    auto navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", "navDestinationSub");
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto geometryNode = navDestinationContent->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto marginFrameOffset = geometryNode->GetMarginFrameOffset();
    /**
     * @tc.steps: step4. property 'marginFrameOffset' should be ...
     */
    ASSERT_EQ(marginFrameOffset.GetY(), DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx());
}

/**
 * @tc.name: toolBarStyleTest001
 * @tc.desc: Branch: if (navBar.toolBarStyle == BarStyle::STANDARD)
 *           Condition: navBar.toolBarStyle == BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, toolBarStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STANDARD, main title and subtitle.
     */
    NavigationToolbarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    std::vector<BarItem> toolbarItems = { BarItem() };
    auto navigationNode = CreateNavigationWithToolBar(
        AceType::MakeRefPtr<MockNavigationStack>(), std::move(options), std::move(toolbarItems));
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: toolBarStyleTest002
 * @tc.desc: Branch: if (navBar.toolBarStyle == BarStyle::STACK)
 *           Condition: navBar.toolBarStyle == BarStyle::STACK
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, toolBarStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle STACK, main title and subtitle.
     */
    NavigationToolbarOptions options;
    options.brOptions.barStyle = BarStyle::STACK;
    std::vector<BarItem> toolbarItems = { BarItem() };
    auto navigationNode = CreateNavigationWithToolBar(
        AceType::MakeRefPtr<MockNavigationStack>(), std::move(options), std::move(toolbarItems));
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: toolBarStyleTest003
 * @tc.desc: Branch: if (navBar.toolBarStyle == BarStyle::SAFE_AREA_PADDING)
 *           Condition: navBar.toolBarStyle == BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, toolBarStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with barStyle SAFE_AREA_PADDING, main title and subtitle.
     */
    NavigationToolbarOptions options;
    options.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    std::vector<BarItem> toolbarItems = { BarItem() };
    auto navigationNode = CreateNavigationWithToolBar(
        AceType::MakeRefPtr<MockNavigationStack>(), std::move(options), std::move(toolbarItems));
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_NE(safeAreaPadding, nullptr);
}

/**
 * @tc.name: toolBarStyleTest
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STANDARD)
 *           Condition: navDestination.titleBarStyle == BarStyle::STANDARD
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, toolBarStyleTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STANDARD and only mainTitle.
     */
    NavigationToolbarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    std::vector<BarItem> toolbarItems = { BarItem() };
    auto navDestination = CreateNavDestinationWithToolBar(std::move(options), std::move(toolbarItems));
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: toolBarStyleTest
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::STACK)
 *           Condition: navDestination.titleBarStyle == BarStyle::STACK
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, toolBarStyleTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle STACK and only mainTitle.
     */
    NavigationToolbarOptions options;
    options.brOptions.barStyle = BarStyle::STACK;
    std::vector<BarItem> toolbarItems = { BarItem() };
    auto navDestination = CreateNavDestinationWithToolBar(std::move(options), std::move(toolbarItems));
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_EQ(safeAreaPadding, nullptr);
}

/**
 * @tc.name: toolBarStyleTest
 * @tc.desc: Branch: if (navDestination.titleBarStyle == BarStyle::SAFE_AREA_PADDING)
 *           Condition: navDestination.titleBarStyle == BarStyle::SAFE_AREA_PADDING
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, toolBarStyleTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navdestination with barStyle SAFE_AREA_PADDING and only mainTitle.
     */
    NavigationToolbarOptions options;
    options.brOptions.barStyle = BarStyle::SAFE_AREA_PADDING;
    std::vector<BarItem> toolbarItems = { BarItem() };
    auto navDestination = CreateNavDestinationWithToolBar(std::move(options), std::move(toolbarItems));
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. run navDestinationPattern's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    navDestinationPattern->OnModifyDone();
    auto layoutWrapper = navDestination->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    BarStyleTestNg::RunMeasureAndLayout(layoutWrapper);
    /**
     * @tc.steps: step3. check property 'safeAreaPadding'.
     */
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    const auto& safeAreaPadding = contentLayoutProperty->GetSafeAreaPaddingProperty();
    /**
     * @tc.steps: step4. property 'safeAreaPadding' should be nullptr cause no SAFE_AREA_PADDING barStyle set.
     */
    ASSERT_NE(safeAreaPadding, nullptr);
}
} // namespace OHOS::Ace::NG
