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

#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
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
 * @tc.name: NavDestinationBaseTest001
 * @tc.desc: check whether the func GetTitleBarHeightBeforeMeasure work correctlly in navBar and dest.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, NavDestinationBaseTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init model, create navigation with title and barStyle.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    auto navigationNode = CreateNavigationWithTitle(
        mockNavPathStack, options, NavigationTitleMode::MINI, "navigation");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarOfNavBar = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarOfNavBar, nullptr);
    auto titleOfNavBar = titleBarOfNavBar->GetTitle();
    ASSERT_NE(titleOfNavBar, nullptr);
    /**
     * @tc.steps: step2. create destination with barStyle.
     */
    auto navDestination = CreateNavDestinationWithTitle(options, "navDestination");
    ASSERT_NE(navDestination, nullptr);
    auto titleBarOfNavDest = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
    ASSERT_NE(titleBarOfNavDest, nullptr);
    auto titleOfNavDest = titleBarOfNavDest->GetTitle();
    ASSERT_NE(titleOfNavDest, nullptr);
    /**
     * @tc.steps: step3. check the return value of function GetTitleBarHeightBeforeMeasure.
     */
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    auto heightOfNavBarTitleBar = navBarPattern->GetTitleBarHeightBeforeMeasure();
    ASSERT_EQ(heightOfNavBarTitleBar, SINGLE_LINE_TITLEBAR_HEIGHT);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto heightOfDestTitleBar = navDestinationPattern->GetTitleBarHeightBeforeMeasure();
    ASSERT_EQ(heightOfDestTitleBar, SINGLE_LINE_TITLEBAR_HEIGHT);
}

/**
 * @tc.name: GetTitleBarHeightBeforeMeasureTest001
 * @tc.desc: check whether the func getPossible work correctlly with different title mode without subtitle.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, GetTitleBarHeightBeforeMeasureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check the value of MINI-mode title.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation");
    ASSERT_NE(navigationNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navBarPattern, nullptr);
    auto heightOfNavBarTitleBar = navBarPattern->GetTitleBarHeightBeforeMeasure();
    ASSERT_EQ(heightOfNavBarTitleBar, SINGLE_LINE_TITLEBAR_HEIGHT);
    /**
     * @tc.steps: step2. check the value of FULL-mode title.
     */
    // change mode to FULL mode
    currentMode = NavigationTitleMode::FULL;
    navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation");
    navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_EQ(navBarPattern->GetTitleBarHeightBeforeMeasure(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT);
    /**
     * @tc.steps: step3. check the value of Free-mode title.
     */
    currentMode = NavigationTitleMode::FREE;
    navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation");
    navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_EQ(navBarPattern->GetTitleBarHeightBeforeMeasure(), FULL_SINGLE_LINE_TITLEBAR_HEIGHT);
}

/**
 * @tc.name: GetTitleBarHeightBeforeMeasureTest002
 * @tc.desc: check whether the func getPossible work correctlly with subTitle
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, GetTitleBarHeightBeforeMeasureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. check the value of MINI-mode title.
     */
    auto mockNavPathStack = AceType::MakeRefPtr<MockNavigationStack>();
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    NavigationTitleMode currentMode = NavigationTitleMode::MINI;
    auto navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    auto navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    auto heightOfNavBarTitleBar = navBarPattern->GetTitleBarHeightBeforeMeasure();
    ASSERT_EQ(heightOfNavBarTitleBar, DOUBLE_LINE_TITLEBAR_HEIGHT);
    /**
     * @tc.steps: step2. check the value of FULL-mode title.
     */
    currentMode = NavigationTitleMode::FULL;
    navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_EQ(navBarPattern->GetTitleBarHeightBeforeMeasure(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
    /**
     * @tc.steps: step3. check the value of FREE-mode title.
     */
    currentMode = NavigationTitleMode::FREE;
    navigationNode = CreateNavigationWithTitle(mockNavPathStack, options, currentMode, "navigation", "subtitle");
    navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarNode());
    navBarPattern = navBarNode->GetPattern<NavDestinationPatternBase>();
    ASSERT_EQ(navBarPattern->GetTitleBarHeightBeforeMeasure(), FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
}

/**
 * @tc.name: GetTitleBarHeightBeforeMeasureTest003
 * @tc.desc: check whether the func getPossible work correctlly in navDest.
 * @tc.type: FUNC
 */
HWTEST_F(NavDestinationBaseTestNg, GetTitleBarHeightBeforeMeasureTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navdestination with only main title and do test.
     */
    NavigationTitlebarOptions options;
    options.brOptions.barStyle = BarStyle::STANDARD;
    auto navDestination = CreateNavDestinationWithTitle(options, "navDestination");
    ASSERT_NE(navDestination, nullptr);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPatternBase>();
    ASSERT_NE(navDestinationPattern, nullptr);
    ASSERT_EQ(navDestinationPattern->GetTitleBarHeightBeforeMeasure(), SINGLE_LINE_TITLEBAR_HEIGHT);
    /**
     * @tc.steps: step1. create navdestination with main title and sub title, then do test.
     */
    navDestination = CreateNavDestinationWithTitle(options, "navDestination", "subTitle");
    navDestinationPattern = navDestination->GetPattern<NavDestinationPatternBase>();
    ASSERT_EQ(navDestinationPattern->GetTitleBarHeightBeforeMeasure(), SINGLE_LINE_TITLEBAR_HEIGHT);
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
} // namespace OHOS::Ace::NG
