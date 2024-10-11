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
} // namespace

class BarStyleTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void BarStyleTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
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
 * @tc.name: SafeAreaPaddingTest001
 * @tc.desc: Test whether navBar's safe area padding set without subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest001, TestSize.Level1)
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
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    auto safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    /**
     * @tc.steps: step3. change title mode to FULL and do test again
     */
    navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", std::nullopt);
    navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    navigationPattern->OnModifyDone();
    navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    contentLayoutProperty = navBarContent->GetLayoutProperty();
    safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    /**
     * @tc.steps: step4. change title mode to FREE and do test again
     */
    navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FREE, "navigationMainTitle", std::nullopt);
    navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    navigationPattern->OnModifyDone();
    navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    contentLayoutProperty = navBarContent->GetLayoutProperty();
    safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(FULL_SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest002
 * @tc.desc: Test whether navBar's safe area padding set with subtitle
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
        mockNavPathStack, options, NavigationTitleMode::MINI, "navigationMainTitle", "subTitle");
    ASSERT_NE(navigationNode, nullptr);
    /**
     * @tc.steps: step2. run navigation's onModifyDone and test the layout property 'safeAreaPadding'.
     */
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->OnModifyDone();
    auto navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    ASSERT_NE(navBarContent, nullptr);
    auto contentLayoutProperty = navBarContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    auto safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    /**
     * @tc.steps: step3. change title mode to FULL and do test again
     */
    navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FULL, "navigationMainTitle", "subTitle");
    navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    navigationPattern->OnModifyDone();
    navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    contentLayoutProperty = navBarContent->GetLayoutProperty();
    safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    /**
     * @tc.steps: step4. change title mode to FREE and do test again
     */
    navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::FREE, "navigationMainTitle", "subTitle");
    navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    navigationPattern->OnModifyDone();
    navBar = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    navBarContent = AceType::DynamicCast<FrameNode>(navBar->GetContentNode());
    contentLayoutProperty = navBarContent->GetLayoutProperty();
    safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(FULL_DOUBLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}

/**
 * @tc.name: SafeAreaPaddingTest003
 * @tc.desc: Test whether navDest's safe area padding set with subtitle
 * @tc.type: FUNC
 */
HWTEST_F(BarStyleTestNg, SafeAreaPaddingTest003, TestSize.Level1)
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
    auto navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    ASSERT_NE(navDestinationContent, nullptr);
    auto contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    ASSERT_NE(contentLayoutProperty, nullptr);
    auto safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
    /**
     * @tc.steps: step2. create subtitle and do test again.
     */
    navDestination = CreateNavDestinationWithTitle(optionsOfNavDest, "navDestination", "subTitle");
    navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    navDestinationPattern->OnModifyDone();
    navDestinationContent = AceType::DynamicCast<FrameNode>(navDestination->GetContentNode());
    contentLayoutProperty = navDestinationContent->GetLayoutProperty();
    safeAreaPaddingF = contentLayoutProperty->GetOrCreateSafeAreaPadding();
    ASSERT_EQ(safeAreaPaddingF.top.value_or(0.0f), static_cast<float>(SINGLE_LINE_TITLEBAR_HEIGHT.ConvertToPx()));
}
} // namespace OHOS::Ace::NG
