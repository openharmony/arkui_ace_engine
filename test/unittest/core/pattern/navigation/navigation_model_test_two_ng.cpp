/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#define protected public
#define private public
#include "core/components/button/button_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_container_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr char BUNDLE_NAME[] = "com.example.app";
constexpr char MODULE_NAME[] = "entry";
const CalcDimension DEFAULT_PADDING = 24.0_vp;
}

class NavigationModelTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

void NavigationModelTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationModelTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationModelTestTwoNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: Create001
 * @tc.desc: Branch: if (!useHomeDest.has_value()) { => true
 *                   if (!useHomeDest.value() && !CreateNavBarNodeIfNeeded(navigationGroupNode)) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, Create001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navNode->GetNavBarNode());
    EXPECT_EQ(navBarNode, nullptr);
    auto useHomeDest = navNode->GetUseHomeDestination();
    ASSERT_TRUE(useHomeDest.has_value());
    EXPECT_TRUE(useHomeDest.value());
}

/**
 * @tc.name: Create002
 * @tc.desc: Branch: if (!useHomeDest.has_value()) { => true
 *                   if (!useHomeDest.value() && !CreateNavBarNodeIfNeeded(navigationGroupNode)) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, Create002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create(false);
    navigationModel.SetNavigationStack();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto useHomeDest = navNode->GetUseHomeDestination();
    ASSERT_TRUE(useHomeDest.has_value());
    EXPECT_FALSE(useHomeDest.value());
}

/**
 * @tc.name: CreateBackButtonNode001
 * @tc.desc: Test CreateBackButtonNode function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, CreateBackButtonNode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    RefPtr<FrameNode> backButtonNode;
    bool result = NavigationModelNG::CreateBackButtonNode(backButtonNode);
    EXPECT_TRUE(result);
    ASSERT_NE(backButtonNode, nullptr);

    auto buttonPattern = backButtonNode->GetPattern<ButtonPattern>();
    ASSERT_NE(buttonPattern, nullptr);
    EXPECT_EQ(buttonPattern->buttonType_, ComponentButtonType::NAVIGATION);

    auto focusHub = backButtonNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->GetFocusDependence(), FocusDependence::SELF);
}

/**
 * @tc.name: UpdateBackButtonProperty001
 * @tc.desc: Test UpdateBackButtonProperty function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateBackButtonProperty001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto backButtonNode = FrameNode::CreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), buttonPattern);

    bool result = NavigationModelNG::UpdateBackButtonProperty(backButtonNode);
    EXPECT_TRUE(result);

    auto buttonLayoutProperty = backButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    ASSERT_NE(buttonLayoutProperty, nullptr);
    EXPECT_EQ(buttonLayoutProperty->GetType().value_or(ButtonType::ICON), ButtonType::NORMAL);
}

/**
 * @tc.name: SetSubtitle001
 * @tc.desc: Test SetSubtitle function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetSubtitle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    std::string subtitle = "test subtitle";
    navigationModel.SetSubtitle(subtitle);

    auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    ASSERT_NE(subTitle, nullptr);
    auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent(), UtfUtils::Str8DebugToStr16(subtitle));
}

/**
 * @tc.name: SetSubtitle002
 * @tc.desc: Test SetSubtitle with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetSubtitle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    std::string subtitle = "test subtitle";
    NavigationModelNG::SetSubtitle(&(*frameNode), subtitle);

    auto subTitle = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    ASSERT_NE(subTitle, nullptr);
    auto textLayoutProperty = subTitle->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent(), UtfUtils::Str8DebugToStr16(subtitle));
}

/**
 * @tc.name: SetEnableModeChangeAnimation001
 * @tc.desc: Test SetEnableModeChangeAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableModeChangeAnimation001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    bool isEnable = true;
    navigationModel.SetEnableModeChangeAnimation(isEnable);

    EXPECT_EQ(navigationLayoutProperty->GetEnableModeChangeAnimation().value_or(false), isEnable);
}

/**
 * @tc.name: SetEnableModeChangeAnimation002
 * @tc.desc: Test SetEnableModeChangeAnimation with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableModeChangeAnimation002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    bool isEnable = false;
    NavigationModelNG::SetEnableModeChangeAnimation(&(*frameNode), isEnable);

    EXPECT_EQ(navigationLayoutProperty->GetEnableModeChangeAnimation().value_or(true), isEnable);
}

/**
 * @tc.name: SetSplitPlaceholder001
 * @tc.desc: Test SetSplitPlaceholder with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetSplitPlaceholder001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);

    auto ph1 = FrameNode::CreateFrameNode(
        "splitPlaceholder", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetSplitPlaceholder(&(*frameNode), &(*ph1));

    auto phContentNode = navigationGroupNode->GetPlaceholderContentNode();
    EXPECT_NE(phContentNode, nullptr);
    EXPECT_EQ(navigationGroupNode->splitPlaceholder_, ph1);

    auto ph2 = FrameNode::CreateFrameNode(
        "splitPlaceholder", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetSplitPlaceholder(&(*frameNode), &(*ph2));

    EXPECT_EQ(navigationGroupNode->GetPlaceholderContentNode(), phContentNode);
    EXPECT_EQ(navigationGroupNode->splitPlaceholder_, ph2);
}

/**
 * @tc.name: ResetSplitPlaceholder001
 * @tc.desc: Test ResetSplitPlaceholder function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, ResetSplitPlaceholder001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);

    auto splitPlaceholder = FrameNode::CreateFrameNode(
        "splitPlaceholder", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetSplitPlaceholder(splitPlaceholder);
    EXPECT_EQ(navigationGroupNode->splitPlaceholder_, splitPlaceholder);

    navigationModel.ResetSplitPlaceholder();
    EXPECT_EQ(navigationGroupNode->splitPlaceholder_, nullptr);
}

/**
 * @tc.name: ResetSplitPlaceholder002
 * @tc.desc: Test ResetSplitPlaceholder with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, ResetSplitPlaceholder002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);

    auto splitPlaceholder = FrameNode::CreateFrameNode(
        "splitPlaceholder", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetSplitPlaceholder(splitPlaceholder);
    EXPECT_EQ(navigationGroupNode->splitPlaceholder_, splitPlaceholder);

    NavigationModelNG::ResetSplitPlaceholder(&(*frameNode));
    EXPECT_EQ(navigationGroupNode->splitPlaceholder_, nullptr);
}

/**
 * @tc.name: SetHideTitleBar001
 * @tc.desc: Test SetHideTitleBar function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideTitleBar001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);

    bool hideTitleBar = true;
    bool animated = false;
    navigationModel.SetHideTitleBar(hideTitleBar, animated);

    EXPECT_EQ(navBarLayoutProperty->GetHideTitleBar().value_or(false), hideTitleBar);
    EXPECT_EQ(navBarLayoutProperty->GetIsAnimatedTitleBar().value_or(true), animated);
}

/**
 * @tc.name: SetHideTitleBar002
 * @tc.desc: Test SetHideTitleBar with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideTitleBar002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);

    bool hideTitleBar = false;
    bool animated = true;
    NavigationModelNG::SetHideTitleBar(&(*frameNode), hideTitleBar, animated);

    EXPECT_EQ(navBarLayoutProperty->GetHideTitleBar().value_or(true), hideTitleBar);
    EXPECT_EQ(navBarLayoutProperty->GetIsAnimatedTitleBar().value_or(false), animated);
}

/**
 * @tc.name: SetEnableToolBarAdaptation001
 * @tc.desc: Test SetEnableToolBarAdaptation function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableToolBarAdaptation001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    bool enable = true;
    navigationModel.SetEnableToolBarAdaptation(enable);

    EXPECT_EQ(navigationLayoutProperty->GetEnableToolBarAdaptation().value_or(false), enable);
}

/**
 * @tc.name: SetEnableToolBarAdaptation002
 * @tc.desc: Test SetEnableToolBarAdaptation with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableToolBarAdaptation002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    bool enable = false;
    NavigationModelNG::SetEnableToolBarAdaptation(&(*frameNode), enable);

    EXPECT_EQ(navigationLayoutProperty->GetEnableToolBarAdaptation().value_or(true), enable);
}

/**
 * @tc.name: SetMenuItemSymbol001
 * @tc.desc: Test SetMenuItemSymbol function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetMenuItemSymbol001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);

    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    navBarPattern->SetTitleBarMenuItems(menuItems);
    int32_t addSymbol = 0;
    auto symbolFunc = [&addSymbol](WeakPtr<NG::FrameNode> symbol) {
        addSymbol++;
    };

    NavigationModelNG::SetMenuItemSymbol(&(*navigationGroupNode), std::move(symbolFunc), 0);
    std::vector<NG::BarItem> titleBarMenuItems = navBarPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    ASSERT_NE(titleBarMenuItems.at(0).iconSymbol, std::nullopt);
    titleBarMenuItems.at(0).iconSymbol.value()(nullptr);
    EXPECT_EQ(addSymbol, 1);
}

/**
 * @tc.name: SetMenuItemSymbol002
 * @tc.desc: Test SetMenuItemSymbol function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetMenuItemSymbol002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);

    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    navBarPattern->SetTitleBarMenuItems(menuItems);
    int32_t addSymbol = 0;
    auto symbolFunc = [&addSymbol](WeakPtr<NG::FrameNode> symbol) {
        addSymbol++;
    };

    NavigationModelNG::SetMenuItemSymbol(&(*navigationGroupNode), std::move(symbolFunc), 1);
    std::vector<NG::BarItem> titleBarMenuItems = navBarPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_EQ(titleBarMenuItems.at(0).iconSymbol, std::nullopt);
    EXPECT_EQ(addSymbol, 0);
}

/**
 * @tc.name: SetMenuItemAction001
 * @tc.desc: Test SetMenuItemAction function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetMenuItemAction001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);

    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    navBarPattern->SetTitleBarMenuItems(menuItems);
    int32_t callCount = 0;
    auto actionFunc = [&callCount]() {
        callCount++;
    };

    NavigationModelNG::SetMenuItemAction(&(*navigationGroupNode), std::move(actionFunc), 0);
    std::vector<NG::BarItem> titleBarMenuItems = navBarPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    ASSERT_FALSE(!titleBarMenuItems.at(0).action);
    titleBarMenuItems.at(0).action();
    EXPECT_EQ(callCount, 1);
}

/**
 * @tc.name: SetMenuItemAction002
 * @tc.desc: Test SetMenuItemAction function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetMenuItemAction002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);

    std::vector<NG::BarItem> menuItems;
    BarItem barItem01;
    barItem01.activeIcon = "ActiveAdd";
    barItem01.icon = "Add";
    barItem01.status = NG::NavToolbarItemStatus::ACTIVE;
    menuItems.push_back(barItem01);
    navBarPattern->SetTitleBarMenuItems(menuItems);
    int32_t callCount = 0;
    auto actionFunc = [&callCount]() {
        callCount++;
    };

    NavigationModelNG::SetMenuItemAction(&(*navigationGroupNode), std::move(actionFunc), 1);
    std::vector<NG::BarItem> titleBarMenuItems = navBarPattern->GetTitleBarMenuItems();
    ASSERT_EQ(titleBarMenuItems.size(), 1);
    EXPECT_TRUE(!titleBarMenuItems.at(0).action);
    EXPECT_EQ(callCount, 0);
}

/**
 * @tc.name: SetHideBackButton001
 * @tc.desc: Test SetHideBackButton function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideBackButton001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);

    bool hideBackButton = true;
    navigationModel.SetHideBackButton(hideBackButton);

    EXPECT_EQ(navBarLayoutProperty->GetHideBackButton().value_or(false), hideBackButton);
}

/**
 * @tc.name: SetHideBackButton002
 * @tc.desc: Test SetHideBackButton with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideBackButton002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);

    bool hideBackButton = false;
    NavigationModelNG::SetHideBackButton(&(*frameNode), hideBackButton);

    EXPECT_EQ(navBarLayoutProperty->GetHideBackButton().value_or(true), hideBackButton);
}

/**
 * @tc.name: SetHideToolBar001
 * @tc.desc: Test SetHideToolBar function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideToolBar001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);

    bool hideToolBar = true;
    bool animated = false;
    navigationModel.SetHideToolBar(hideToolBar, animated);

    EXPECT_EQ(navBarLayoutProperty->GetHideToolBar().value_or(false), hideToolBar);
    EXPECT_EQ(navBarLayoutProperty->GetIsAnimatedToolBar().value_or(true), animated);
}

/**
 * @tc.name: SetHideToolBar002
 * @tc.desc: Test SetHideToolBar with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideToolBar002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);

    bool hideToolBar = false;
    bool animated = true;
    NavigationModelNG::SetHideToolBar(&(*frameNode), hideToolBar, animated);

    EXPECT_EQ(navBarLayoutProperty->GetHideToolBar().value_or(true), hideToolBar);
    EXPECT_EQ(navBarLayoutProperty->GetIsAnimatedToolBar().value_or(false), animated);
}

/**
 * @tc.name: SetCustomToolBar001
 * @tc.desc: Test SetCustomToolBar function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetCustomToolBar001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto toolbarNode = navBarNode->GetToolBarNode();
    ASSERT_NE(toolbarNode, nullptr);

    auto customNode = FrameNode::CreateFrameNode(
        "customToolBar", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetCustomToolBar(customNode);
    auto childrenNode = toolbarNode->GetChildren();
    ASSERT_FALSE(childrenNode.empty());
    EXPECT_EQ(childrenNode.front(), customNode);
}

/**
 * @tc.name: SetHideItemText001
 * @tc.desc: Test SetHideItemText function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetHideItemText001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);

    bool isHideItemText = true;
    navigationModel.SetHideItemText(isHideItemText);
    EXPECT_EQ(toolBarNode->IsHideItemText(), isHideItemText);
}

/**
 * @tc.name: SetToolbarMorebuttonOptions001
 * @tc.desc: Test SetToolbarMorebuttonOptions function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetToolbarMorebuttonOptions001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    auto toobarPattern = toolBarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toobarPattern, nullptr);

    MoreButtonOptions opt;
    opt.bgOptions.color = Color::RED;
    navigationModel.SetToolbarMorebuttonOptions(std::move(opt));
    auto curOpt = toobarPattern->GetToolbarMoreButtonOptions();
    ASSERT_TRUE(curOpt.bgOptions.color.has_value());
    EXPECT_EQ(curOpt.bgOptions.color.value(), Color::RED);
}

/**
 * @tc.name: SetCustomMenu001
 * @tc.desc: Test SetCustomMenu function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetCustomMenu001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    auto customNode1 = FrameNode::CreateFrameNode(
        "customMenu", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetCustomMenu(customNode1);
    EXPECT_EQ(navBarNode->GetMenuNodeOperation().value_or(ChildNodeOperation::NONE), ChildNodeOperation::ADD);

    navigationModel.SetCustomMenu(customNode1);
    EXPECT_EQ(navBarNode->GetMenuNodeOperation().value_or(ChildNodeOperation::ADD), ChildNodeOperation::NONE);

    auto customNode2 = FrameNode::CreateFrameNode(
        "customMenu", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationModel.SetCustomMenu(customNode2);
    EXPECT_EQ(navBarNode->GetMenuNodeOperation().value_or(ChildNodeOperation::NONE), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: SetNavBarPosition001
 * @tc.desc: Test SetNavBarPosition function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetNavBarPosition001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    NavBarPosition mode = NavBarPosition::START;
    navigationModel.SetNavBarPosition(mode);

    EXPECT_EQ(navigationLayoutProperty->GetNavBarPosition().value_or(NavBarPosition::START), mode);
}

/**
 * @tc.name: SetNavBarPosition002
 * @tc.desc: Test SetNavBarPosition with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetNavBarPosition002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    NavBarPosition mode = NavBarPosition::END;
    NavigationModelNG::SetNavBarPosition(&(*frameNode), mode);

    EXPECT_EQ(navigationLayoutProperty->GetNavBarPosition().value_or(NavBarPosition::START), mode);
}

/**
 * @tc.name: SetNavigationMode001
 * @tc.desc: Test SetNavigationMode function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetNavigationMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    NavigationMode mode = NavigationMode::SPLIT;
    navigationModel.SetNavigationMode(mode);

    EXPECT_EQ(navigationLayoutProperty->GetNavigationMode().value_or(NavigationMode::AUTO), mode);
}

/**
 * @tc.name: SetIsCustomAnimation001
 * @tc.desc: Test SetIsCustomAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetIsCustomAnimation001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    bool isCustom = true;
    navigationModel.SetIsCustomAnimation(isCustom);

    EXPECT_EQ(pattern->isCustomAnimation_, isCustom);
}

/**
 * @tc.name: SetIsCustomAnimation002
 * @tc.desc: Test SetIsCustomAnimation with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetIsCustomAnimation002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    bool isCustom = false;
    NavigationModelNG::SetIsCustomAnimation(&(*frameNode), isCustom);

    EXPECT_EQ(pattern->isCustomAnimation_, isCustom);
}

/**
 * @tc.name: SetRecoverable001
 * @tc.desc: Test SetRecoverable function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetRecoverable001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);

    bool recoverable = true;
    navigationModel.SetRecoverable(recoverable);

    EXPECT_EQ(navigationGroupNode->recoverable_, recoverable);
}

/**
 * @tc.name: SetRecoverable002
 * @tc.desc: Test SetRecoverable with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetRecoverable002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);

    bool recoverable = false;
    NavigationModelNG::SetRecoverable(&(*frameNode), recoverable);

    EXPECT_EQ(navigationGroupNode->recoverable_, recoverable);
}

/**
 * @tc.name: SetEnableDragBar001
 * @tc.desc: Test SetEnableDragBar function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableDragBar001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto backupType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    navigationModel.SetEnableDragBar(true);
    EXPECT_FALSE(pattern->GetEnableDragBar());

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    navigationModel.SetEnableDragBar(true);
    EXPECT_TRUE(pattern->GetEnableDragBar());

    SystemProperties::SetDeviceType(backupType);
}

/**
 * @tc.name: SetEnableDragBar002
 * @tc.desc: Test SetEnableDragBar with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableDragBar002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto backupType = SystemProperties::GetDeviceType();
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
    NavigationModelNG::SetEnableDragBar(&(*frameNode), true);
    EXPECT_FALSE(pattern->GetEnableDragBar());

    SystemProperties::SetDeviceType(DeviceType::PHONE);
    NavigationModelNG::SetEnableDragBar(&(*frameNode), true);
    EXPECT_TRUE(pattern->GetEnableDragBar());

    SystemProperties::SetDeviceType(backupType);
}

/**
 * @tc.name: CreateForceSplitPlaceHolderIfNeeded001
 * @tc.desc: Test CreateForceSplitPlaceHolderIfNeeded function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, CreateForceSplitPlaceHolderIfNeeded001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(AceType::WeakClaim(frameNode).Upgrade());
    ASSERT_NE(navigationGroupNode, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto forceSplitMgr = context->GetForceSplitManager();
    ASSERT_NE(forceSplitMgr, nullptr);
    auto navMgr = context->GetNavigationManager();
    ASSERT_NE(navMgr, nullptr);

    auto backupSupported = forceSplitMgr->isForceSplitSupported_;
    auto backupIsRouter = forceSplitMgr->isRouter_;
    auto backupPlaceholderDisabled = navMgr->IsPlaceholderDisabled();
    auto backupRelatedPageName = forceSplitMgr->GetRelatedPageName();

    forceSplitMgr->isForceSplitSupported_ = false;
    navigationGroupNode->RemoveChild(navigationGroupNode->forceSplitPlaceHolderNode_);
    navigationGroupNode->forceSplitPlaceHolderNode_ = nullptr;
    EXPECT_TRUE(navigationModel.CreateForceSplitPlaceHolderIfNeeded(navigationGroupNode));
    EXPECT_EQ(navigationGroupNode->forceSplitPlaceHolderNode_, nullptr);

    forceSplitMgr->isForceSplitSupported_ = true;
    forceSplitMgr->isRouter_ = false;

    navMgr->SetPlaceholderDisabled(true);
    navigationGroupNode->forceSplitPlaceHolderNode_ = nullptr;
    EXPECT_TRUE(navigationModel.CreateForceSplitPlaceHolderIfNeeded(navigationGroupNode));
    EXPECT_EQ(navigationGroupNode->forceSplitPlaceHolderNode_, nullptr);

    navMgr->SetPlaceholderDisabled(false);
    forceSplitMgr->SetRelatedPageName("relatedPage");
    navigationGroupNode->forceSplitPlaceHolderNode_ = nullptr;
    EXPECT_TRUE(navigationModel.CreateForceSplitPlaceHolderIfNeeded(navigationGroupNode));
    EXPECT_EQ(navigationGroupNode->forceSplitPlaceHolderNode_, nullptr);

    forceSplitMgr->isForceSplitSupported_ = backupSupported;
    forceSplitMgr->isRouter_ = backupIsRouter;
    navMgr->SetPlaceholderDisabled(backupPlaceholderDisabled);
    forceSplitMgr->SetRelatedPageName(backupRelatedPageName);
}

/**
 * @tc.name: CreateForceSplitPlaceHolderIfNeeded002
 * @tc.desc: Test CreateForceSplitPlaceHolderIfNeeded function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, CreateForceSplitPlaceHolderIfNeeded002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(AceType::WeakClaim(frameNode).Upgrade());
    ASSERT_NE(navigationGroupNode, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto forceSplitMgr = context->GetForceSplitManager();
    ASSERT_NE(forceSplitMgr, nullptr);
    auto navMgr = context->GetNavigationManager();
    ASSERT_NE(navMgr, nullptr);

    auto backupSupported = forceSplitMgr->isForceSplitSupported_;
    auto backupIsRouter = forceSplitMgr->isRouter_;
    auto backupPlaceholderDisabled = navMgr->IsPlaceholderDisabled();
    auto backupRelatedPageName = forceSplitMgr->GetRelatedPageName();

    forceSplitMgr->isForceSplitSupported_ = true;
    forceSplitMgr->isRouter_ = false;
    forceSplitMgr->SetRelatedPageName("");
    navMgr->SetPlaceholderDisabled(false);

    auto splitPlaceholder = FrameNode::CreateFrameNode(
        "splitPlaceholder", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationGroupNode->forceSplitPlaceHolderNode_ = splitPlaceholder;

    EXPECT_TRUE(navigationModel.CreateForceSplitPlaceHolderIfNeeded(navigationGroupNode));
    EXPECT_EQ(navigationGroupNode->forceSplitPlaceHolderNode_, splitPlaceholder);

    forceSplitMgr->isForceSplitSupported_ = backupSupported;
    forceSplitMgr->isRouter_ = backupIsRouter;
    navMgr->SetPlaceholderDisabled(backupPlaceholderDisabled);
    forceSplitMgr->SetRelatedPageName(backupRelatedPageName);
}

/**
 * @tc.name: CreateForceSplitPlaceHolderIfNeeded003
 * @tc.desc: Test CreateForceSplitPlaceHolderIfNeeded function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, CreateForceSplitPlaceHolderIfNeeded003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(AceType::WeakClaim(frameNode).Upgrade());
    ASSERT_NE(navigationGroupNode, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);

    auto forceSplitMgr = context->GetForceSplitManager();
    ASSERT_NE(forceSplitMgr, nullptr);
    auto navMgr = context->GetNavigationManager();
    ASSERT_NE(navMgr, nullptr);

    auto backupSupported = forceSplitMgr->isForceSplitSupported_;
    auto backupIsRouter = forceSplitMgr->isRouter_;
    auto backupPlaceholderDisabled = navMgr->IsPlaceholderDisabled();
    auto backupRelatedPageName = forceSplitMgr->GetRelatedPageName();

    forceSplitMgr->isForceSplitSupported_ = true;
    forceSplitMgr->isRouter_ = false;
    forceSplitMgr->SetRelatedPageName("");
    navMgr->SetPlaceholderDisabled(false);

    navigationGroupNode->forceSplitPlaceHolderNode_ = nullptr;
    EXPECT_TRUE(navigationModel.CreateForceSplitPlaceHolderIfNeeded(navigationGroupNode));
    EXPECT_NE(navigationGroupNode->forceSplitPlaceHolderNode_, nullptr);

    forceSplitMgr->isForceSplitSupported_ = backupSupported;
    forceSplitMgr->isRouter_ = backupIsRouter;
    navMgr->SetPlaceholderDisabled(backupPlaceholderDisabled);
    forceSplitMgr->SetRelatedPageName(backupRelatedPageName);
}

/**
 * @tc.name: UpdateDividerColor001
 * @tc.desc: Test UpdateDividerColor function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateDividerColor001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto property = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    Color color = Color::RED;
    RefPtr<ResourceObject> res = nullptr;
    navigationModel.UpdateDividerColor(color, res);
    EXPECT_EQ(property->GetDividerColorValue(Color::GREEN), color);
}

/**
 * @tc.name: UpdateDividerStartMargin001
 * @tc.desc: Test UpdateDividerStartMargin function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateDividerStartMargin001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto property = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    CalcDimension start = 10.0_vp;
    RefPtr<ResourceObject> res = nullptr;
    navigationModel.UpdateDividerStartMargin(start, res);
    EXPECT_EQ(property->GetDividerStartMarginValue(CalcDimension()), start);
}

/**
 * @tc.name: UpdateDividerEndMargin001
 * @tc.desc: Test UpdateDividerEndMargin function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateDividerEndMargin001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto property = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);
    CalcDimension end = 10.0_vp;
    RefPtr<ResourceObject> res = nullptr;
    navigationModel.UpdateDividerEndMargin(end, res);
    EXPECT_EQ(property->GetDividerEndMarginValue(CalcDimension()), end);
}

/**
 * @tc.name: UpdateDividerVisibility001
 * @tc.desc: Test UpdateDividerVisibility function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateDividerVisibility001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationGroupNode->GetDividerNode());
    ASSERT_NE(dividerNode, nullptr);
    auto property = dividerNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);

    bool isShow = true;
    navigationModel.UpdateDividerVisibility(isShow);
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateDividerVisibility002
 * @tc.desc: Test UpdateDividerVisibility with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateDividerVisibility002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto dividerNode = AceType::DynamicCast<FrameNode>(navigationGroupNode->GetDividerNode());
    ASSERT_NE(dividerNode, nullptr);
    auto property = dividerNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);

    bool isShow = false;
    NavigationModelNG::UpdateDividerVisibility(&(*frameNode), isShow);
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: UpdateDefineColor001
 * @tc.desc: Test UpdateDefineColor function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UpdateDefineColor001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto property = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);

    navigationModel.UpdateDefineColor(false);
    EXPECT_FALSE(property->GetDefinedDividerColorValue(true));
}

/**
 * @tc.name: ResetDividerStyle001
 * @tc.desc: Test ResetDividerStyle function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, ResetDividerStyle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto property = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(property, nullptr);

    property->UpdateDefinedDividerColor(true);
    NavigationModelNG::ResetDividerStyle(&(*frameNode));
    EXPECT_FALSE(property->GetDefinedDividerColorValue(true));
}

/**
 * @tc.name: UseHomeDestination001
 * @tc.desc: Test UseHomeDestination function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, UseHomeDestination001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create(true);
    navigationModel.SetNavigationStack();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);

    navigationGroupNode->useHomeDestination_ = std::nullopt;
    EXPECT_FALSE(navigationModel.UseHomeDestination());

    navigationGroupNode->useHomeDestination_ = false;
    EXPECT_FALSE(navigationModel.UseHomeDestination());

    navigationGroupNode->useHomeDestination_ = true;
    EXPECT_TRUE(navigationModel.UseHomeDestination());
}

/**
 * @tc.name: SetEnableVisibilityLifecycleWithContentCover001
 * @tc.desc: Test SetEnableVisibilityLifecycleWithContentCover function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableVisibilityLifecycleWithContentCover001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    bool isEnable = true;
    navigationModel.SetEnableVisibilityLifecycleWithContentCover(isEnable);

    EXPECT_EQ(pattern->GetEnableVisibilityLifecycleWithContentCover(), isEnable);
}

/**
 * @tc.name: SetEnableVisibilityLifecycleWithContentCover002
 * @tc.desc: Test SetEnableVisibilityLifecycleWithContentCover with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetEnableVisibilityLifecycleWithContentCover002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    bool isEnable = false;
    NavigationModelNG::SetEnableVisibilityLifecycleWithContentCover(&(*frameNode), isEnable);
    EXPECT_EQ(pattern->GetEnableVisibilityLifecycleWithContentCover(), isEnable);
}

/**
 * @tc.name: SetBackButtonTitleResource001
 * @tc.desc: Test SetBackButtonTitleResource function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetBackButtonTitleResource001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    NavigationModelNG::SetTitleMode(&(*frameNode), NavigationTitleMode::MINI);
    std::string text = "Back";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(BUNDLE_NAME, MODULE_NAME, 0);
    NavigationModelNG::SetBackButtonTitleResource(&(*frameNode), text, resObj);

    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    ASSERT_NE(backButtonNode, nullptr);
    auto accessibilityProperty = backButtonNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityText(), text);
}

/**
 * @tc.name: SetIsCustomTitleBarSize001
 * @tc.desc: Test SetIsCustomTitleBarSize function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetIsCustomTitleBarSize001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    bool isCustom = true;
    NavigationModelNG::SetIsCustomTitleBarSize(&(*frameNode), isCustom);

    EXPECT_TRUE(titleBarLayoutProperty->GetIsCustomTitleBarSizeValue(false));
}

/**
 * @tc.name: CreateFrameNode001
 * @tc.desc: Test CreateFrameNode function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, CreateFrameNode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = NavigationModelNG::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);

    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto contentNode = navigationGroupNode->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
}

/**
 * @tc.name: SetTitlebarOptions001
 * @tc.desc: Test SetTitlebarOptions with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetTitlebarOptions001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    NavigationTitlebarOptions opt;
    opt.bgOptions.color = std::make_optional(Color(0xff0000ff));
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    opt.brOptions.barStyle = std::make_optional(BarStyle::STACK);
    opt.brOptions.paddingStart = std::make_optional(DEFAULT_PADDING);
    opt.brOptions.paddingEnd = std::make_optional(DEFAULT_PADDING);

    NavigationModelNG::SetTitlebarOptions(&(*frameNode), std::move(opt));

    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    EXPECT_NE(titleBarPattern, nullptr);

    auto options = titleBarPattern->GetTitleBarOptions();
    EXPECT_TRUE(options.bgOptions.color.has_value());
    EXPECT_EQ(options.bgOptions.color.value(), Color(0xff0000ff));

    EXPECT_TRUE(options.bgOptions.blurStyleOption.has_value());
    EXPECT_EQ(options.bgOptions.blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);

    EXPECT_TRUE(options.brOptions.barStyle.has_value());
    EXPECT_EQ(options.brOptions.barStyle.value(), BarStyle::STACK);

    EXPECT_TRUE(options.brOptions.paddingStart.has_value());
    EXPECT_EQ(options.brOptions.paddingStart.value(), DEFAULT_PADDING);
    
    EXPECT_TRUE(options.brOptions.paddingEnd.has_value());
    EXPECT_EQ(options.brOptions.paddingEnd.value(), DEFAULT_PADDING);
}

/**
 * @tc.name: SetUsrNavigationMode001
 * @tc.desc: Test SetUsrNavigationMode function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetUsrNavigationMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    NavigationMode mode = NavigationMode::STACK;
    navigationModel.SetUsrNavigationMode(mode);

    EXPECT_EQ(navigationLayoutProperty->GetUsrNavigationMode().value_or(NavigationMode::AUTO), mode);
}

/**
 * @tc.name: SetUsrNavigationMode002
 * @tc.desc: Test SetUsrNavigationMode with FrameNode parameter
 * @tc.type: FUNC
 */
HWTEST_F(NavigationModelTestTwoNg, SetUsrNavigationMode002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    NavigationMode mode = NavigationMode::SPLIT;
    NavigationModelNG::SetUsrNavigationMode(&(*frameNode), mode);

    EXPECT_EQ(navigationLayoutProperty->GetUsrNavigationMode().value_or(NavigationMode::AUTO), mode);
}
} // namespace OHOS::Ace::NG