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
#include "core/components_ng/pattern/navigation/inner_navigation_controller.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string BAR_ITEM_ETS_TAG = "BarItem";
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const char NAVBAR_CONTENT_ETS_TAG[] = "NavBarContent";
const std::string EMPTY_STRING = "";
const int32_t RET_OK = 0;
constexpr float DEFAULT_SIZE_LENGTH = 20.0f;
constexpr float DEFAULT_SIZE_LENGTH_NEGATIVE = -20.0f;
const std::string NAV_BAR_NODE_TITLE = "title";
const std::string NAV_BAR_NODE_MENU = "menu";
const std::string NAV_BAR_NODE_BACK_BUTTON = "back_button";
const std::string NAVIGATION_GROUP_NODE = "navigation_group_node";
const std::string MENU_ITEM_ICON = "menu_item_icon";
const std::string MENU_ITEM_TEXT = "menu_item";
struct TestParameters {
    RefPtr<MockPipelineContext> pipeline = nullptr;
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
    MockPipelineContext::SetUp();
}
void NavBarTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
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
    testParameters.pipeline = MockPipelineContext::GetCurrent();
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
    auto title = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(title, nullptr);
    titleBarNode_->SetTitle(title);
    auto menu = AceType::MakeRefPtr<FrameNode>(
        NAV_BAR_NODE_MENU, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(menu, nullptr);
    navBarNode_->SetMenu(menu);
    auto backButton = AceType::MakeRefPtr<FrameNode>(
        NAV_BAR_NODE_BACK_BUTTON, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(backButton, nullptr);
    titleBarNode_->SetBackButton(backButton);
    testParameters.navigationGroupNode = AceType::MakeRefPtr<NavigationGroupNode>(NAVIGATION_GROUP_NODE,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    ASSERT_NE(testParameters.navigationGroupNode, nullptr);
    auto navigationPattern = testParameters.navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
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
    navBarNode->SetContentNode(contentNode);
    navBarNode->AddChildToGroup(frameNode);
    auto group = navBarNode->GetContentNode();
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
    auto group = navBarNode->GetContentNode();
    EXPECT_EQ(group, nullptr);
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
    barNode->ToJsonValue(json, filter);
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
    barNode->SetContentNode(nullptr);
    EXPECT_EQ(barNode->contentNode_, nullptr);
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
    auto ret = barNode->GetContentNode();
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

    auto navigationGroupNode = FrameNode::CreateFrameNode("NavigationGroupNode", 33,
        AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);

    GestureEvent info;
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    navigationPattern->InitPanEvent(gestureHub);
    auto panEvent = navigationPattern->panEvent_;
    EXPECT_NE(panEvent, nullptr);
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
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
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
    navBarNode_->UpdatePrevMenuIsCustom(true);
    auto buttonNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->MountToParent(menuNode);
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps: step3. call OnWindowSizeChanged func when the width of navBar is 0
     * @tc.expected:GetTheme function is called once
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

    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
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
    ASSERT_NE(inputEventHub->hoverEventActuator_, nullptr);
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
}

/**
 * @tc.name: NavBarNode001
 * @tc.desc: Test GetTitleString function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarNode001, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    titleBarNode->SetTitle(frameNode);
    navBarNode->SetTitleBarNode(titleBarNode);
    EXPECT_EQ(NavigationTitleUtil::GetTitleString(titleBarNode, false), "");
}

/**
 * @tc.name: NavBarNode002
 * @tc.desc: Test GetTitleString function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarNode002, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    frameNode->tag_ = V2::TEXT_ETS_TAG;
    titleBarNode->SetTitle(frameNode);
    navBarNode->SetTitleBarNode(titleBarNode);
    EXPECT_EQ(NavigationTitleUtil::GetTitleString(titleBarNode, false), "");
}

/**
 * @tc.name: NavBarNode003
 * @tc.desc: Test GetSubtitleString function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarNode003, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    titleBarNode->SetSubtitle(frameNode);
    navBarNode->SetTitleBarNode(titleBarNode);
    EXPECT_EQ(NavigationTitleUtil::GetSubtitleString(titleBarNode), "");
}

/**
 * @tc.name: NavBarNode004
 * @tc.desc: Test GetSubtitleString function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarNode004, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    frameNode->tag_ = V2::TEXT_ETS_TAG;
    titleBarNode->SetSubtitle(frameNode);
    navBarNode->SetTitleBarNode(titleBarNode);
    EXPECT_EQ(NavigationTitleUtil::GetSubtitleString(titleBarNode), "");
}

/**
 * @tc.name: NavBarNode005
 * @tc.desc: Test AddChildToGroup function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarNode005, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
    navBarNode->pattern_ = AceType::MakeRefPtr<NavigationPattern>();
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    navBarNode->SetContentNode(frameNode);
    navBarNode->AddChildToGroup(nullptr);
}

/**
 * @tc.name: NavBarNode006
 * @tc.desc: Test AddChildToGroup function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarNode006, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto barNode = AceType::MakeRefPtr<NavBarNode>(barTag, nodeId, AceType::MakeRefPtr<Pattern>());
    RefPtr<NavBarNode> navBarNode = barNode->GetOrCreateNavBarNode(barTag, nodeId, nullptr);
    EXPECT_NE(navBarNode, nullptr);
    navBarNode->pattern_ = AceType::MakeRefPtr<NavigationPattern>();
    navBarNode->AddChildToGroup(nullptr);
}

/**
 * @tc.name: NavBarPattern012
 * @tc.desc: Test OnCoordScrollStart function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern012, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = true;
    navBarPattern->titleMode_ = NavigationTitleMode::MINI;
    navBarPattern->OnCoordScrollStart();
}

/**
 * @tc.name: NavBarPattern013
 * @tc.desc: Test OnCoordScrollStart function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern013, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = false;
    navBarPattern->titleMode_ = NavigationTitleMode::FREE;
    navBarPattern->OnCoordScrollStart();
}

/**
 * @tc.name: NavBarPattern014
 * @tc.desc: Test OnCoordScrollUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern014, TestSize.Level1)
{
    float offset = 0.001;
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = true;
    navBarPattern->titleMode_ = NavigationTitleMode::MINI;
    navBarPattern->OnCoordScrollUpdate(offset);
}

/**
 * @tc.name: NavBarPattern015
 * @tc.desc: Test OnCoordScrollUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern015, TestSize.Level1)
{
    float offset = 0.001;
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = false;
    navBarPattern->titleMode_ = NavigationTitleMode::FREE;
    navBarPattern->OnCoordScrollUpdate(offset);
}

/**
 * @tc.name: NavBarPattern016
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern016, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = true;
    navBarPattern->titleMode_ = NavigationTitleMode::MINI;
    navBarPattern->OnCoordScrollEnd();
}

/**
 * @tc.name: NavBarPattern017
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern017, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = false;
    navBarPattern->titleMode_ = NavigationTitleMode::FREE;
    navBarPattern->OnCoordScrollEnd();
}

/**
 * @tc.name: NavBarPattern018
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern018, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    auto navBarpattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarpattern, nullptr);

    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    navBarNode->SetContentNode(frameNode);

    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navBarLayoutProperty->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });

    navBarpattern->OnModifyDone();
}

/**
 * @tc.name: NavBarPattern019
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern019, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    auto navBarpattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarpattern, nullptr);

    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);

    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navBarLayoutProperty->UpdateSafeAreaExpandOpts({ .type = SAFE_AREA_TYPE_NONE, .edges = SAFE_AREA_EDGE_NONE });

    navBarpattern->OnModifyDone();
}

/**
 * @tc.name: NavBarPattern020
 * @tc.desc: Test OnCoordScrollEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern020, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    auto navBarpattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarpattern, nullptr);

    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);

    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);

    navBarpattern->OnModifyDone();
}

/**
 * @tc.name: NavBarPattern021
 * @tc.desc: Test InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern021, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavBarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navBarPattern = frameNode->GetPattern<NavBarPattern>();
    EXPECT_NE(navBarPattern, nullptr);
    navBarPattern->isHideTitlebar_ = true;
    navBarPattern->titleMode_ = NavigationTitleMode::MINI;

    auto navigationGroupNode = FrameNode::CreateFrameNode("NavigationGroupNode", 33,
        AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    navigationPattern->InitPanEvent(gestureHub);
}

/**
 * @tc.name: NavBarPattern021
 * @tc.desc: Test IgnoreLayoutSafeArea function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern022, TestSize.Level1)
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    auto navBarpattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarpattern, nullptr);

    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    auto opts = navBarLayoutProperty->GetIgnoreLayoutSafeAreaValue({.type = SAFE_AREA_TYPE_NONE,
    .edges = SAFE_AREA_TYPE_NONE});
    EXPECT_EQ(opts.type, SAFE_AREA_TYPE_NONE);
    EXPECT_EQ(opts.edges, SAFE_AREA_TYPE_NONE);

    navBarLayoutProperty->UpdateIgnoreLayoutSafeArea({ .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_ALL });
    opts = navBarLayoutProperty->GetIgnoreLayoutSafeAreaValue({.type = SAFE_AREA_TYPE_NONE,
        .edges = SAFE_AREA_TYPE_NONE});
    EXPECT_EQ(opts.type, SAFE_AREA_TYPE_SYSTEM);
    EXPECT_EQ(opts.edges, SAFE_AREA_EDGE_ALL);
}

/**
 * @tc.name: NavBarPattern023
 * @tc.desc: Test GetShowMenuOffset function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern023, TestSize.Level1)
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
    auto toolBarNode = AceType::MakeRefPtr<FrameNode>(
        FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(toolBarNode, nullptr);
    navBarNode_->SetToolBarNode(toolBarNode);
    auto menuNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU); });
    ASSERT_NE(menuNode, nullptr);
    titleBarNode_->SetMenu(menuNode);
    navBarNode_->SetMenu(menuNode);
    auto buttonNode = AceType::MakeRefPtr<FrameNode>(
        FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(buttonNode, nullptr);
    buttonNode->MountToParent(menuNode);
    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
        V2::BAR_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
    ASSERT_NE(barItemNode, nullptr);
    barItemNode->MountToParent(buttonNode);
    barItemNode->SetIsMoreItemNode(true);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
    imageNode->MarkModifyDone();
    barItemNode->SetIconNode(imageNode);
    barItemNode->AddChild(imageNode);
    auto imgOffset = navBarpattern_->GetShowMenuOffset(barItemNode, menuNode);
    EXPECT_FLOAT_EQ(imgOffset.GetY(), imgOffset.GetX());
    auto layoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto imgOffset2 = navBarpattern_->GetShowMenuOffset(barItemNode, menuNode);
    EXPECT_FLOAT_EQ(imgOffset2.GetY(), imgOffset2.GetX());
}

/**
 * @tc.name: NavBarPattern024
 * @tc.desc: Test CanCoordScrollUp function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern024, TestSize.Level1)
{
    CreateNavBar();
    CreateTitlebar();
    navBarNode_->SetTitleBarNode(titleBarNode_);
    auto size = SizeF(DEFAULT_SIZE_LENGTH, 0.0f);
    auto navGeometryNode = navBarNode_->GetGeometryNode();
    ASSERT_NE(navGeometryNode, nullptr);
    navGeometryNode->SetFrameSize(size);
    auto canCoordScrollUp = navBarpattern_->CanCoordScrollUp(DEFAULT_SIZE_LENGTH);
    EXPECT_FALSE(canCoordScrollUp);
    auto canCoordScrollUp2 = navBarpattern_->CanCoordScrollUp(DEFAULT_SIZE_LENGTH_NEGATIVE);
    EXPECT_FALSE(canCoordScrollUp2);
}

/**
 * @tc.name: NavBarPattern025
 * @tc.desc: Test SetNavBarMask function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern025, TestSize.Level1)
{
    TestParameters testParameters;
    InitializationParameters(testParameters);
    auto navigationPattern = testParameters.navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);
    testParameters.theme->navBarUnfocusColor_ = Color::RED;
    navBarpattern_->SetNavBarMask(false);
    auto renderContext = navBarNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto maskProperty = renderContext->GetProgressMaskValue();
    auto isTransparent = maskProperty->GetColor() == Color::TRANSPARENT ? true : false;
    EXPECT_FALSE(isTransparent);
}

/**
 * @tc.name: NavBarPattern026
 * @tc.desc: Test SetNavBarMask function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavBarPattern026, TestSize.Level1)
{
    TestParameters testParameters;
    InitializationParameters(testParameters);
    auto navigationPattern = testParameters.navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    navigationPattern->SetNavigationMode(NavigationMode::SPLIT);
    navBarpattern_->SetNavBarMask(true);
    auto renderContext = navBarNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto maskProperty = renderContext->GetProgressMaskValue();
    auto isTransparent = maskProperty->GetColor() == Color::TRANSPARENT ? true : false;
    EXPECT_TRUE(isTransparent);
}

/**
 * @tc.name: InnerNavigationController001
 * @tc.desc: Test InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    EXPECT_EQ(innerNavigationController->GetTopHandle(), RET_OK);
}

/**
 * @tc.name: InnerNavigationController002
 * @tc.desc: Test InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", frameNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    EXPECT_EQ(innerNavigationController->GetTopHandle(), RET_OK);
}

/**
 * @tc.name: InnerNavigationController003
 * @tc.desc: Test SetInPIPMode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageTwo", frameNode));
    navigationPattern->navigationStack_->cacheNodes_ = navPathList;
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 0;
    innerNavigationController->SetInPIPMode(handle);
}

/**
 * @tc.name: InnerNavigationController004
 * @tc.desc: Test SetInPIPMode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", frameNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 33;
    innerNavigationController->SetInPIPMode(handle);
}

/**
 * @tc.name: InnerNavigationController005
 * @tc.desc: Test SetInPIPMode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageFour", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 33;
    innerNavigationController->SetInPIPMode(handle);
}

/**
 * @tc.name: InnerNavigationController006
 * @tc.desc: Test SetInPIPMode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", frameNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 2;
    innerNavigationController->SetInPIPMode(handle);
}

/**
 * @tc.name: InnerNavigationController007
 * @tc.desc: Test PopInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    bool destroy = true;
    innerNavigationController->PopInPIP(destroy);
}

/**
 * @tc.name: InnerNavigationController008
 * @tc.desc: Test PopInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController008, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", frameNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    bool destroy = true;
    innerNavigationController->PopInPIP(destroy);
}

/**
 * @tc.name: InnerNavigationController009
 * @tc.desc: Test PopInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController009, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    bool destroy = false;
    innerNavigationController->PopInPIP(destroy);
}

/**
 * @tc.name: InnerNavigationController010
 * @tc.desc: Test PushInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController010, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 0;
    innerNavigationController->PushInPIP(handle);
}

/**
 * @tc.name: InnerNavigationController012
 * @tc.desc: Test PushInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController012, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", frameNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 33;
    innerNavigationController->PushInPIP(handle);
}

/**
 * @tc.name: InnerNavigationController013
 * @tc.desc: Test PushInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController013, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 33;
    innerNavigationController->PushInPIP(handle);
}

/**
 * @tc.name: InnerNavigationController014
 * @tc.desc: Test PushInPIP function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, InnerNavigationController014, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navigationPattern = frameNode->GetPattern<NavigationPattern>();
    EXPECT_NE(navigationPattern, nullptr);
    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", frameNode));
    navigationPattern->navigationStack_->SetNavPathList(navPathList);
    auto innerNavigationController = navigationPattern->navigationController_;
    EXPECT_NE(innerNavigationController, nullptr);
    int32_t handle = 0;
    innerNavigationController->PushInPIP(handle);
}

/**
 * @tc.name: NavigationStack001
 * @tc.desc: Test GetFromPreBackup function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack001, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageOne";
    RefPtr<UINode> navDestinationNode;
    int32_t lastIndex;
    navigationStack->GetFromPreBackup(name, navDestinationNode, lastIndex);
    EXPECT_EQ(navDestinationNode, nullptr);
}

/**
 * @tc.name: NavigationStack002
 * @tc.desc: Test GetFromPreBackup function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack002, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", frameNode));
    navigationStack->SetNavPathList(navPathList);
    std::string name = "pageOne";
    RefPtr<UINode> navDestinationNode;
    int32_t lastIndex;
    navigationStack->GetFromPreBackup(name, navDestinationNode, lastIndex);
    EXPECT_EQ(navDestinationNode, nullptr);
}

/**
 * @tc.name: NavigationStack003
 * @tc.desc: Test AddCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack003, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "";
    auto frameNode = nullptr;
    navigationStack->AddCacheNode(name, frameNode);
}

/**
 * @tc.name: NavigationStack004
 * @tc.desc: Test AddCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack004, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageOne";
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    navigationStack->AddCacheNode(name, tempNode);
}

/**
 * @tc.name: NavigationStack005
 * @tc.desc: Test RemoveCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack005, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    int32_t handle = 0;
    navigationStack->RemoveCacheNode(handle);
}

/**
 * @tc.name: NavigationStack006
 * @tc.desc: Test RemoveCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack006, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    int32_t handle = 2;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", tempNode));
    navigationStack->cacheNodes_ = navPathList;
    navigationStack->RemoveCacheNode(handle);
}

/**
 * @tc.name: NavigationStack007
 * @tc.desc: Test RemoveCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack007, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    int32_t handle = 44;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageThree", tempNode));
    navigationStack->cacheNodes_ = navPathList;
    navigationStack->RemoveCacheNode(handle);
}

/**
 * @tc.name: NavigationStack008
 * @tc.desc: Test RemoveCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack008, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    NavPathList cacheNodes;
    std::string name = "";
    navigationStack->RemoveCacheNode(cacheNodes, name, nullptr);
}

/**
 * @tc.name: NavigationStack009
 * @tc.desc: Test RemoveCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack009, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    cacheNodes.emplace_back(std::make_pair("pageThree", tempNode));
    std::string name = "pageThree";
    navigationStack->RemoveCacheNode(cacheNodes, name, tempNode);
}

/**
 * @tc.name: NavigationStack010
 * @tc.desc: Test RemoveCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack010, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    cacheNodes.emplace_back(std::make_pair("pageThree", tempNode));
    std::string name = "pageOne";
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    navigationStack->RemoveCacheNode(cacheNodes, name, frameNode);
}

/**
 * @tc.name: NavigationStack011
 * @tc.desc: Test ReOrderCache function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack011, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "";
    navigationStack->ReOrderCache(name, nullptr);
}

/**
 * @tc.name: NavigationStack012
 * @tc.desc: Test ReOrderCache function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack012, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageOne";
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavigationPattern>());
    EXPECT_NE(frameNode, nullptr);
    cacheNodes.emplace_back(std::make_pair("pageThree", frameNode));
    navigationStack->cacheNodes_ = cacheNodes;
    navigationStack->ReOrderCache(name, tempNode);
}

/**
 * @tc.name: NavigationStack013
 * @tc.desc: Test ReOrderCache function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack013, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageOne";
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationStack->cacheNodes_ = cacheNodes;
    navigationStack->ReOrderCache(name, tempNode);
}

/**
 * @tc.name: NavigationStack014
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack014, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    NavPathList cacheNodes;
    std::string name = "";
    EXPECT_EQ(navigationStack->GetFromCacheNode(cacheNodes, name), nullptr);
}

/**
 * @tc.name: NavigationStack015
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack015, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    std::string name = "pageOne";
    EXPECT_NE(navigationStack->GetFromCacheNode(cacheNodes, name), nullptr);
}

/**
 * @tc.name: NavigationStack016
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack016, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    std::string name = "pageThree";
    EXPECT_EQ(navigationStack->GetFromCacheNode(cacheNodes, name), nullptr);
}

/**
 * @tc.name: NavigationStack017
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack017, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "";
    EXPECT_EQ(navigationStack->GetFromCacheNode(name), nullptr);
}

/**
 * @tc.name: NavigationStack018
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack018, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageOne";
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationStack->cacheNodes_ = cacheNodes;
    EXPECT_NE(navigationStack->GetFromCacheNode(name), nullptr);
}

/**
 * @tc.name: NavigationStack019
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack019, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageTwo";
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationStack->cacheNodes_ = cacheNodes;
    EXPECT_EQ(navigationStack->GetFromCacheNode(name), nullptr);
}

/**
 * @tc.name: NavigationStack020
 * @tc.desc: Test GetFromCacheNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack020, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationStack->cacheNodes_ = cacheNodes;
    int32_t handle = 44;
    EXPECT_NE(navigationStack->GetFromCacheNode(handle), std::nullopt);
}

/**
 * @tc.name: NavigationStack021
 * @tc.desc: Test RemoveInPreNavPathList function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack021, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    std::string name = "pageOne";
    int32_t index = -1;
    EXPECT_EQ(navigationStack->RemoveInPreNavPathList(name, nullptr), index);
}

/**
 * @tc.name: NavigationStack022
 * @tc.desc: Test RemoveInPreNavPathList function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack022, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationStack->preNavPathList_ = cacheNodes;
    std::string name = "pageOne";
    int32_t index = 0;
    EXPECT_EQ(navigationStack->RemoveInPreNavPathList(name, tempNode), index);
    navigationStack->navPathList_ = cacheNodes;
    int32_t index_ = -1;
    EXPECT_EQ(navigationStack->Get(index_), nullptr);
    int32_t indexs = 3;
    EXPECT_EQ(navigationStack->Get(indexs), nullptr);
}

/**
 * @tc.name: NavigationStack023
 * @tc.desc: Test GetFromPreBackup function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack023, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);

    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationStack->preNavPathList_ = cacheNodes;
    int32_t index = 44;
    RefPtr<UINode> navDestinationNode = nullptr;
    EXPECT_EQ(navigationStack->GetFromPreBackup("pageOne", navDestinationNode, index), true);
}

/**
 * @tc.name: NavigationStack024
 * @tc.desc: Test GetAllPathIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavBarTestNg, NavigationStack024, TestSize.Level1)
{
    auto navigationStack = std::make_shared<NavigationStack>();
    EXPECT_NE(navigationStack, nullptr);
    auto siz = navigationStack->GetAllPathIndex().size();
    EXPECT_EQ(siz, 0);
}
} // namespace OHOS::Ace::NG
