/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/utils/system_properties.h"
#include "core/components/navigation_bar/navigation_bar_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string BAR_ITEM_ETS_TAG = "BarItem";
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const char NAVBAR_CONTENT_ETS_TAG[] = "NavBarContent";
const char TEXT_ETS_TAG[] = "Text";
const std::string EMPTY_STRING = "";
const int32_t RET_OK = 0;
constexpr float START = 50.0f;
constexpr float MAIN_DELTA = 80.0f;
constexpr float DEFAULT_SIZE_LENGTH = 20.0f;
const std::string NAV_BAR_NODE_TITLE = "title";
const std::string NAV_BAR_NODE_MENU = "menu";
const std::string NAV_BAR_NODE_BACK_BUTTON = "back_button";
const std::string NAVIGATION_GROUP_NODE = "navigation_group_node";
const std::string MENU_ITEM_ICON = "menu_item_icon";
const std::string MENU_ITEM_TEXT = "menu_item";
struct TestParameters {
    RefPtr<MockPipelineBase> pipeline = nullptr;
    RefPtr<NavigationBarTheme> theme = nullptr;
    RefPtr<NavBarLayoutProperty> navBarLayoutProperty = nullptr;
    RefPtr<NavigationGroupNode> navigationGroupNode = nullptr;
    NG::BarItem menuItem;
    std::vector<NG::BarItem> menuItems;
};
} // namespace

class NavBarTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void DestroyTitleBarObject();
    void CreateNavBar();
    void CreateTitlebar();
    void InitializationParameters(TestParameters& testParameters);

    RefPtr<NavBarPattern> navBarpattern_;
    RefPtr<NavBarNode> navBarNode_;
    RefPtr<TitleBarNode> titleBarNode_;
};

void NavBarTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void NavBarTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

void NavBarTestNg::CreateNavBar()
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    navBarNode_ = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode_, nullptr);
    navBarpattern_ = navBarNode_->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarpattern_, nullptr);
}

void NavBarTestNg::CreateTitlebar()
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode_, nullptr);
}

void NavBarTestNg::DestroyTitleBarObject()
{
    navBarpattern_ = nullptr;
    navBarNode_ = nullptr;
    titleBarNode_ = nullptr;
}

void NavBarTestNg::InitializationParameters(TestParameters& testParameters)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    testParameters.pipeline = MockPipelineBase::GetCurrent();
    ASSERT_NE(testParameters.pipeline, nullptr);
    testParameters.pipeline->SetThemeManager(themeManager);
    testParameters.theme = AceType::MakeRefPtr<NavigationBarTheme>();
    ASSERT_NE(testParameters.theme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(testParameters.theme));
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(SelectTheme::TypeId())).WillRepeatedly(Return(selectTheme));

    CreateNavBar();
    CreateTitlebar();

    testParameters.navBarLayoutProperty = navBarNode_->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(testParameters.navBarLayoutProperty, nullptr);
    navBarNode_->SetTitleBarNode(titleBarNode_);
    auto title = AceType::MakeRefPtr<FrameNode>(
        NAV_BAR_NODE_TITLE, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(title, nullptr);
    navBarNode_->SetTitle(title);
    auto menu = AceType::MakeRefPtr<FrameNode>(
        NAV_BAR_NODE_MENU, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menu, nullptr);
    navBarNode_->SetMenu(menu);
    auto backButton = AceType::MakeRefPtr<FrameNode>(
        NAV_BAR_NODE_BACK_BUTTON, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(backButton, nullptr);
    navBarNode_->SetBackButton(backButton);
    testParameters.navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(NAVIGATION_GROUP_NODE,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    ASSERT_NE(testParameters.navigationGroupNode, nullptr);
    auto navigationPattern = testParameters.navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::AUTO);
    navBarNode_->SetParent(testParameters.navigationGroupNode);
    testParameters.menuItem.action = []() {};
    testParameters.menuItem.icon = MENU_ITEM_ICON;
    testParameters.menuItems.push_back(testParameters.menuItem);
    navBarpattern_->SetTitleBarMenuItems(testParameters.menuItems);
}

/**
 * @tc.name: GetOrCreateNavBarNode001
 * @tc.desc: Test create nav bar node.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetOrCreateNavBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::GetFrameNode(barTag, nodeId);
    EXPECT_EQ(frameNode, nullptr);
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
}

/**
 * @tc.name: GetOrCreateNavBarNode002
 * @tc.desc: Test get nav bar node.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetOrCreateNavBarNode002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto node = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    node->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(node);
    auto frameNode = FrameNode::GetFrameNode(barTag, nodeId);
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
}

/**
 * @tc.name: AddChildToGroup001
 * @tc.desc: Test add nav bar content node child to group.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, AddChildToGroup001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto navBarNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navBarNode->SetNavBarContentNode(contentNode);
    navBarNode->AddChildToGroup(frameNode);
    auto group = navBarNode->GetNavBarContentNode();
    EXPECT_NE(group, nullptr);
}

/**
 * @tc.name: AddChildToGroup002
 * @tc.desc: Test add new content node child to group.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, AddChildToGroup002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto navBarNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<NavBarPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        NAVBAR_CONTENT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navBarNode->AddChildToGroup(frameNode);
    auto group = navBarNode->GetNavBarContentNode();
    EXPECT_EQ(group, nullptr);
}

/**
 * @tc.name: GetTitleString001
 * @tc.desc: Test get title string with error tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetTitleString001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(BAR_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitle(frameNode);
    auto ret = barNode->GetTitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetTitleString002
 * @tc.desc: Test get title string with right tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetTitleString002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string textTag = TEXT_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(textTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitle(frameNode);
    auto ret = barNode->GetTitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetSubtitleString001
 * @tc.desc: Test get sub title string with error tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetSubtitleString001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(BAR_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetSubtitle(frameNode);
    auto ret = barNode->GetSubtitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetSubtitleString002
 * @tc.desc: Test get sub title string with right tag.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetSubtitleString002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    std::string textTag = TEXT_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto frameNode = AceType::MakeRefPtr<FrameNode>(textTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetSubtitle(frameNode);
    auto ret = barNode->GetSubtitleString();
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: GetBarItemsString001
 * @tc.desc: Test get bar items string without menu.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetBarItemsString001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetBarItemsString(false);
    EXPECT_EQ(ret, EMPTY_STRING);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test to json value.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, ToJsonValue001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto json = JsonUtil::Create(true);
    barNode->ToJsonValue(json);
    EXPECT_EQ(json->GetValue("title")->GetString(), EMPTY_STRING);
    EXPECT_EQ(json->GetValue("subtitle")->GetString(), EMPTY_STRING);
    EXPECT_EQ(json->GetValue("menus")->GetString(), EMPTY_STRING);
    EXPECT_EQ(json->GetValue("toolBar")->GetString(), EMPTY_STRING);
}

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, IsAtomicNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->IsAtomicNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetBackButton001
 * @tc.desc: Test SetBackButton interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetBackButton001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetBackButton(nullptr);
    EXPECT_EQ(barNode->backButton_, nullptr);
}

/**
 * @tc.name: GetBackButton001
 * @tc.desc: Test GetBackButton interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetBackButton001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetBackButton();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetTitle001
 * @tc.desc: Test SetTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetTitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitle(nullptr);
    EXPECT_EQ(barNode->title_, nullptr);
}

/**
 * @tc.name: GetTitle001
 * @tc.desc: Test GetTitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetTitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetTitle();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetSubtitle001
 * @tc.desc: Test SetSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetSubtitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetSubtitle(nullptr);
    EXPECT_EQ(barNode->subtitle_, nullptr);
}

/**
 * @tc.name: GetSubtitle001
 * @tc.desc: Test GetSubtitle interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetSubtitle001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetSubtitle();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetMenu001
 * @tc.desc: Test SetMenu interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetMenu001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetMenu(nullptr);
    EXPECT_EQ(barNode->menu_, nullptr);
}

/**
 * @tc.name: GetMenu001
 * @tc.desc: Test GetMenu interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetMenu001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetMenu();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetTitleBarNode001
 * @tc.desc: Test SetTitleBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetTitleBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetTitleBarNode(nullptr);
    EXPECT_EQ(barNode->titleBarNode_, nullptr);
}

/**
 * @tc.name: GetTitleBarNode001
 * @tc.desc: Test GetTitleBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetTitleBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetTitleBarNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetNavBarContentNode001
 * @tc.desc: Test SetNavBarContentNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetNavBarContentNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetNavBarContentNode(nullptr);
    EXPECT_EQ(barNode->navBarContentNode_, nullptr);
}

/**
 * @tc.name: GetNavBarContentNode001
 * @tc.desc: Test GetNavBarContentNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetNavBarContentNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetNavBarContentNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetToolBarNode001
 * @tc.desc: Test SetToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetToolBarNode(nullptr);
    EXPECT_EQ(barNode->toolBarNode_, nullptr);
}

/**
 * @tc.name: GetToolBarNode001
 * @tc.desc: Test GetToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetToolBarNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: SetPreToolBarNode001
 * @tc.desc: Test SetPreToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, SetPreToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    barNode->SetPreToolBarNode(nullptr);
    EXPECT_EQ(barNode->preToolBarNode_, nullptr);
}

/**
 * @tc.name: GetPreToolBarNode001
 * @tc.desc: Test GetPreToolBarNode interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, GetPreToolBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    auto ret = barNode->GetPreToolBarNode();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: OnPrevTitleIsCustomUpdate001
 * @tc.desc: Test OnPrevTitleIsCustomUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnPrevTitleIsCustomUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    barNode->OnPrevTitleIsCustomUpdate(true);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnPrevMenuIsCustomUpdate001
 * @tc.desc: Test OnPrevMenuIsCustomUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnPrevMenuIsCustomUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    barNode->OnPrevMenuIsCustomUpdate(true);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnPrevToolBarIsCustomUpdate001
 * @tc.desc: Test OnPrevToolBarIsCustomUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnPrevToolBarIsCustomUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    barNode->OnPrevToolBarIsCustomUpdate(true);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnBackButtonNodeOperationUpdate001
 * @tc.desc: Test OnBackButtonNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnBackButtonNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnBackButtonNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnTitleNodeOperationUpdate001
 * @tc.desc: Test OnTitleNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnTitleNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnTitleNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnSubtitleNodeOperationUpdate001
 * @tc.desc: Test OnSubtitleNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnSubtitleNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnSubtitleNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnMenuNodeOperationUpdate001
 * @tc.desc: Test OnMenuNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnMenuNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnMenuNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: OnToolBarNodeOperationUpdate001
 * @tc.desc: Test OnToolBarNodeOperationUpdate interface.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, OnToolBarNodeOperationUpdate001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t ret = RET_OK;
    ChildNodeOperation value = ChildNodeOperation::ADD;
    barNode->OnToolBarNodeOperationUpdate(value);
    EXPECT_EQ(ret, RET_OK);
}

/**
 * @tc.name: NarBarPattern002
 * @tc.desc: Test InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NarBarPattern002, TestSize.Level1)
{
    std::string frameTag = FRAME_ITEM_ETS_TAG;
    CreateNavBar();
    CreateTitlebar();
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(frameTag, nodeId, AceType::MakeRefPtr<Pattern>());

    GestureEvent info;
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    navBarpattern_->InitPanEvent(gestureHub);
    auto panEvent = navBarpattern_->panEvent_;
    EXPECT_NE(panEvent, nullptr);
}

/**
 * @tc.name: NarBarPattern003
 * @tc.desc: Test HandleOnDragStart function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NarBarPattern003, TestSize.Level1)
{
    CreateNavBar();
    CreateTitlebar();

    GestureEvent startInfo;
    startInfo.SetOffsetY(START);
    navBarNode_->SetTitleBarNode(titleBarNode_);
    navBarpattern_->HandleOnDragStart(static_cast<float>(startInfo.GetOffsetY()));
    EXPECT_TRUE(startInfo.GetOffsetY() == START);
}

/**
 * @tc.name: NarBarPattern004
 * @tc.desc: Test HandleOnDragUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NarBarPattern004, TestSize.Level1)
{
    CreateNavBar();
    CreateTitlebar();

    GestureEvent updateInfo;
    updateInfo.SetOffsetY(MAIN_DELTA);
    navBarNode_->SetTitleBarNode(titleBarNode_);
    navBarpattern_->HandleOnDragUpdate(static_cast<float>(updateInfo.GetOffsetY()));
    EXPECT_TRUE(updateInfo.GetOffsetY() == MAIN_DELTA);
    navBarpattern_->HandleOnDragEnd();
}

/**
 * @tc.name: NavBarPattern005
 * @tc.desc: Test OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavBar and Titlebar
     */
    CreateNavBar();
    CreateTitlebar();
    navBarNode_->SetTitleBarNode(titleBarNode_);

    /**
     * @tc.steps: step2. Create related objects for NavBar
     */
    auto size = SizeF(DEFAULT_SIZE_LENGTH, DEFAULT_SIZE_LENGTH);
    auto navGeometryNode = navBarNode_->GetGeometryNode();
    ASSERT_NE(navGeometryNode, nullptr);
    navGeometryNode->SetFrameSize(size);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(toolBarNode, nullptr);
    navBarNode_->SetToolBarNode(toolBarNode);
    auto menuNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    titleBarNode_->SetMenu(menuNode);
    navBarNode_->SetMenu(menuNode);
    auto buttonNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->MountToParent(menuNode);
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(FRAME_ITEM_ETS_TAG, nodeId);
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);
    navBarNode_->SetIsTitleMenuNodeShowing(true);

    bool isItemActionFired = false;
    auto barItemEventHub = barItemNode->GetEventHub<BarItemEventHub>();
    ASSERT_NE(barItemEventHub, nullptr);
    barItemEventHub->SetItemAction([&]() { isItemActionFired = true; });
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step3. call OnWindowSizeChanged func when PrevMenuIsCustom is true
     * @tc.expected: Set isItemActionFired is true
     */
    navBarNode_->UpdatePrevMenuIsCustom(true);
    navBarpattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);
    EXPECT_TRUE(isItemActionFired);

    /**
     * @tc.steps: step4. call OnWindowSizeChanged func when PrevMenuIsCustom is false
     * @tc.expected: isItemActionFired is true
     */
    navBarNode_->UpdatePrevMenuIsCustom(false);
    navBarpattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);
    EXPECT_TRUE(isItemActionFired);
}

/**
 * @tc.name: NavBarPattern006
 * @tc.desc: Test OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavBar and Titlebar
     */
    CreateNavBar();
    CreateTitlebar();
    navBarNode_->SetTitleBarNode(titleBarNode_);

    /**
     * @tc.steps: step2. Create related objects for NavBar
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto toolBarNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(toolBarNode, nullptr);
    navBarNode_->SetToolBarNode(toolBarNode);
    auto menuNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menuNode, nullptr);
    titleBarNode_->SetMenu(menuNode);
    navBarNode_->SetMenu(menuNode);
    auto buttonNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->MountToParent(menuNode);
    auto barItemNode = AceType::MakeRefPtr<BarItemNode>(BAR_ITEM_ETS_TAG, nodeId);
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step3. call OnWindowSizeChanged func when the width of navBar is 0
     * @tc.expected:GetTheme function is not called
     */
    auto size = SizeF(0, 0);
    auto navGeometryNode = navBarNode_->GetGeometryNode();
    ASSERT_NE(navGeometryNode, nullptr);
    navGeometryNode->SetFrameSize(size);
    EXPECT_CALL(*themeManager, GetTheme(_)).Times(0);
    navBarpattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);

    /**
     * @tc.steps: step4. call OnWindowSizeChanged func when the width of navBar is DEFAULT_SIZE_LENGTH
     * @tc.expected:GetTheme function is called
     */
    size = SizeF(DEFAULT_SIZE_LENGTH, DEFAULT_SIZE_LENGTH);
    navGeometryNode->SetFrameSize(size);
    auto theme = AceType::MakeRefPtr<NavigationBarTheme>();
    ASSERT_NE(theme, nullptr);
    theme->toolbarLimitGridCount_ = 1;
    navBarpattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);

    /**
     * @tc.steps: step5. call OnWindowSizeChanged func when the DeviceType is TABLET
     * @tc.expected:GetTheme function is called
     */
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    navBarpattern_->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
    SystemProperties::SetDeviceType(DeviceType::PHONE);
}

/**
 * @tc.name: NavBarPattern007
 * @tc.desc: Test RegistOritationListener function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavBar
     */
    CreateNavBar();

    /**
     * @tc.steps: step2. call RegistOritationListener func when isOritationListenerRegisted_ is true
     * @tc.expected:isOritationListenerRegisted_ is true
     */
    navBarpattern_->isOritationListenerRegisted_ = true;
    navBarpattern_->RegistOritationListener();
    EXPECT_TRUE(navBarpattern_->isOritationListenerRegisted_);

    /**
     * @tc.steps: step3. call RegistOritationListener func when isOritationListenerRegisted_ is false
     * @tc.expected:isOritationListenerRegisted_ is true
     */
    navBarpattern_->isOritationListenerRegisted_ = false;
    navBarpattern_->RegistOritationListener();
    EXPECT_TRUE(navBarpattern_->isOritationListenerRegisted_);
}

/**
 * @tc.name: NavBarPattern008
 * @tc.desc: Test OnDetachFromFrameNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create NavBar
     */
    CreateNavBar();

    /**
     * @tc.steps: step2. call OnDetachFromFrameNode func when isOritationListenerRegisted_ is true
     * @tc.expected:isOritationListenerRegisted_ is false
     */
    navBarpattern_->isOritationListenerRegisted_ = true;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    navBarpattern_->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_FALSE(navBarpattern_->isOritationListenerRegisted_);
}

/**
 * @tc.name: NavBarPattern009
 * @tc.desc: Test BuildMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameters.
     */
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. Call OnModifyDone when MenuNodeOperation is REPLACE and PrevMenuIsCustom is true.
     */
    navBarNode_->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    navBarNode_->UpdatePrevMenuIsCustom(true);
    ASSERT_TRUE(navBarNode_->GetMenuNodeOperation().has_value());
    navBarpattern_->OnModifyDone();
    ASSERT_NE(titleBarNode_->GetLastChild(), nullptr);
    EXPECT_EQ(titleBarNode_->GetLastChild()->GetTag(), NAV_BAR_NODE_MENU);

    /**
     * @tc.steps: step3. Call OnModifyDone when MenuNodeOperation is NONE and PrevMenuIsCustom is true.
     */
    navBarNode_->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    ASSERT_TRUE(navBarNode_->GetMenuNodeOperation().has_value());
    navBarpattern_->OnModifyDone();
    ASSERT_NE(titleBarNode_->GetLastChild(), nullptr);
    EXPECT_EQ(titleBarNode_->GetLastChild()->GetTag(), NAV_BAR_NODE_MENU);

    /**
     * @tc.steps: step4. Call OnModifyDone when MenuNodeOperation is NONE and PrevMenuIsCustom is false.
     */
    navBarNode_->UpdatePrevMenuIsCustom(false);
    ASSERT_TRUE(navBarNode_->GetMenuNodeOperation().has_value());
    navBarpattern_->OnModifyDone();
    ASSERT_NE(titleBarNode_->GetLastChild(), nullptr);
    EXPECT_EQ(titleBarNode_->GetLastChild()->GetTag(), NAV_BAR_NODE_MENU);

    /**
     * @tc.steps: step5. Call OnModifyDone when MenuNodeOperation is REPLACE and PrevMenuIsCustom is false.
     */
    navBarNode_->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    ASSERT_TRUE(navBarNode_->GetMenuNodeOperation().has_value());
    navBarpattern_->OnModifyDone();
    ASSERT_EQ(titleBarNode_->GetLastChild(), nullptr);

    /**
     * @tc.steps: step6. Call OnModifyDone when EventHub is not enabled, DeviceOrientation is ORIENTATION_UNDEFINED,
     * HideToolBar is false, NavigationMode is AUTO, MostMenuItemCountInBar is 0, MinPlatformVersion is 0 and MenuItem
     * text is not empty.
     */
    auto navigationGroupEventHub = testParameters.navigationGroupNode->GetEventHub<EventHub>();
    ASSERT_NE(navigationGroupEventHub, nullptr);
    navigationGroupEventHub->enabled_ = false;
    auto menuNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    navBarpattern_->SetMenuNodeId(menuNodeId);
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
    testParameters.navBarLayoutProperty->UpdateHideToolBar(false);
    testParameters.theme->mostMenuItemCountInBar_ = 0;
    testParameters.pipeline->minPlatformVersion_ = 0;
    testParameters.menuItem.text = MENU_ITEM_TEXT;
    testParameters.menuItems.push_back(testParameters.menuItem);
    navBarpattern_->SetTitleBarMenuItems(testParameters.menuItems);
    navBarpattern_->OnModifyDone();
    ASSERT_EQ(titleBarNode_->GetLastChild(), nullptr);
    EXPECT_NE(navBarNode_->GetLandscapeMenu(), nullptr);

    /**
     * @tc.steps: step9. Call OnModifyDone when MostMenuItemCountInBar is 1.
     * text is not empty.
     */
    testParameters.theme->mostMenuItemCountInBar_ = 1;
    navBarpattern_->OnModifyDone();
    ASSERT_EQ(titleBarNode_->GetLastChild(), nullptr);
    EXPECT_NE(navBarNode_->GetLandscapeMenu(), nullptr);
}

/**
 * @tc.name: NavBarPattern011
 * @tc.desc: Test BuildMoreItemNodeAction and InitTitleBarButtonEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization parameters.
     */
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. Call OnModifyDone to call InitTitleBarButtonEvent.
     */
    navBarNode_->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    navBarNode_->UpdatePrevMenuIsCustom(false);
    bool isClick = false;
    testParameters.menuItem.action = [&isClick]() { isClick = !isClick; };
    testParameters.menuItems.clear();
    testParameters.menuItems.push_back(testParameters.menuItem);
    navBarpattern_->SetTitleBarMenuItems(testParameters.menuItems);
    navBarpattern_->OnModifyDone();

    /**
     * @tc.steps: step3. Test InitTitleBarButtonEvent.
     */
    /**
     * @tc.case: case1: Call hoverCallback.
     */
    auto menuNode = navBarNode_->GetLandscapeMenu();
    ASSERT_NE(menuNode, nullptr);
    auto lastMenuItemNode = AceType::DynamicCast<FrameNode>(menuNode->GetLastChild());
    ASSERT_NE(lastMenuItemNode, nullptr);
    auto inputEventHub = lastMenuItemNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputEventHub, nullptr);
    ASSERT_FALSE(inputEventHub->hoverEventActuator_->inputEvents_.empty());
    for (const auto& hoverCallback : inputEventHub->hoverEventActuator_->inputEvents_) {
        ASSERT_NE(hoverCallback, nullptr);
        (*hoverCallback)(false);
    }
    /**
     * @tc.case: case2: Call click callback when SourceDevice is KEYBOARD.
     */
    auto firstMenuItemNode = AceType::DynamicCast<FrameNode>(menuNode->GetFirstChild());
    ASSERT_NE(firstMenuItemNode, nullptr);
    auto firstGestureEventHub = firstMenuItemNode->GetOrCreateGestureEventHub();
    ASSERT_NE(firstGestureEventHub, nullptr);
    auto firstClickListener = firstGestureEventHub->clickEventActuator_->clickEvents_.back();
    ASSERT_NE(firstClickListener, nullptr);
    ASSERT_NE(firstClickListener->callback_, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::KEYBOARD);
    firstClickListener->callback_(info);
    EXPECT_FALSE(isClick);
    /**
     * @tc.case: case3: Call click callback when SourceDevice is TOUCH.
     */
    info.SetSourceDevice(SourceType::TOUCH);
    firstClickListener->callback_(info);
    EXPECT_TRUE(isClick);
}
} // namespace OHOS::Ace::NG
