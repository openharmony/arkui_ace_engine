/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/button/button_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_event_hub.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr Color FRONT_COLOR = Color(0xff0000ff);
const std::string BAR_ITEM_ETS_TAG = "BarItem";
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const std::string EMPTY_STRING = "";
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
class ToolBarTestNg : public testing::Test {
public:
    static RefPtr<ButtonTheme> buttonTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static void MockPipelineContextGetTheme();
    void CreateNavBar();
    void CreateTitlebar();
    void CreateToolbar();
    void InitializationParameters(TestParameters& testParameters);
    void SetUp() override;
    void TearDown() override;
    void InitToolBarItemInfos(std::vector<NG::BarItem>& toolBarItems);
    void UpdateBarItemNodeWithItem(const RefPtr<NavToolbarNode>& toolBarNode, std::vector<NG::BarItem>& toolBarItems);
    RefPtr<NavToolbarPattern> toolBarPattern_;
    RefPtr<NavToolbarNode> toolBarNode_;
    RefPtr<NavBarPattern> navBarpattern_;
    RefPtr<NavBarNode> navBarNode_;
    RefPtr<TitleBarNode> titleBarNode_;
};

RefPtr<ButtonTheme> ToolBarTestNg::buttonTheme_ = nullptr;

void ToolBarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == ButtonTheme::TypeId()) {
            return buttonTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void ToolBarTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();

    buttonTheme_ = nullptr;
}

void ToolBarTestNg::SetUp()
{
    toolBarPattern_ = AceType::MakeRefPtr<NavToolbarPattern>();
    toolBarNode_ = AceType::MakeRefPtr<NavToolbarNode>("tag", 1);
}

void ToolBarTestNg::TearDown()
{
    toolBarPattern_ = nullptr;
    toolBarNode_ = nullptr;
}

void ToolBarTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

void ToolBarTestNg::CreateNavBar()
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    auto navBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    navBarNode_ = NavBarNode::GetOrCreateNavBarNode(
        barTag, navBarNodeId, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(navBarNode_, nullptr);
    navBarpattern_ = navBarNode_->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarpattern_, nullptr);
}

void ToolBarTestNg::CreateTitlebar()
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode_, nullptr);
}

void ToolBarTestNg::CreateToolbar()
{
    std::string barTag = BAR_ITEM_ETS_TAG;
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    toolBarNode_ = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolBarNode_, nullptr);
}

void ToolBarTestNg::InitializationParameters(TestParameters& testParameters)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    testParameters.pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(testParameters.pipeline, nullptr);
    testParameters.pipeline->SetThemeManager(themeManager);
    testParameters.theme = AceType::MakeRefPtr<NavigationBarTheme>();
    ASSERT_NE(testParameters.theme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(testParameters.theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(testParameters.theme));
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(SelectTheme::TypeId())).WillRepeatedly(Return(selectTheme));

    CreateNavBar();
    CreateTitlebar();
    CreateToolbar();

    testParameters.navBarLayoutProperty = navBarNode_->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(testParameters.navBarLayoutProperty, nullptr);
    navBarNode_->SetTitleBarNode(titleBarNode_);
    auto title = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(title, nullptr);
    titleBarNode_->SetTitle(title);
    navBarNode_->SetToolBarNode(toolBarNode_);
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

void ToolBarTestNg::InitToolBarItemInfos(std::vector<NG::BarItem>& toolBarItems)
{
    bool isEnabled = true;
    std::function<void()> menuAction = [&isEnabled]() {
        isEnabled = !isEnabled;
    };
    BarItem toolBarItemOne = {
        .text = "toolBarItemOne",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemOne);
    BarItem toolBarItemTwo = {
        .text = "toolBarItemTwo",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemTwo);
    BarItem toolBarItemThree = {
        .text = "toolBarItemThree",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemThree);
    BarItem toolBarItemFour = {
        .text = "toolBarItemFour",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemFour);
    BarItem toolBarItemFive = {
        .text = "toolBarItemFive",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemFive);
    BarItem toolBarItemSix = {
        .text = "toolBarItemSix",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemSix);
}

void ToolBarTestNg::UpdateBarItemNodeWithItem(const RefPtr<NavToolbarNode>& toolBarNode,
    std::vector<NG::BarItem>& toolBarItems)
{
    for (const auto& barItem : toolBarItems) {
        int32_t barItemNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
            V2::BAR_ITEM_ETS_TAG, barItemNodeId, []() { return AceType::MakeRefPtr<BarItemPattern>(); });
        if (barItem.text.has_value() && !barItem.text.value().empty()) {
            int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
            auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextPattern>());
            auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateContent(barItem.text.value());
            textLayoutProperty->UpdateFontSize(10.0_vp);
            textLayoutProperty->UpdateTextColor(Color(0xE6000000));
            textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
            barItemNode->SetTextNode(textNode);
            barItemNode->AddChild(textNode);
        }
        if (barItem.icon.has_value() && !barItem.icon.value().empty()) {
            int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
            ImageSourceInfo info(barItem.icon.value());
            auto iconNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, nodeId, AceType::MakeRefPtr<ImagePattern>());
            auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(imageLayoutProperty);
            auto theme = NavigationGetTheme();
            CHECK_NULL_VOID(theme);
            auto iconSize = theme->GetMenuIconSize();
            imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(iconSize), CalcLength(iconSize)));
            iconNode->MarkModifyDone();
            barItemNode->SetIconNode(iconNode);
            barItemNode->AddChild(iconNode);
        }
        if (barItem.action) {
            auto eventHub = barItemNode->GetOrCreateEventHub<BarItemEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->SetItemAction(barItem.action);
        }
        auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
        barItemNode->MarkModifyDone();
        toolBarNode->AddChild(barItemNode);
    }
}

/**
 * @tc.name: ToolBarPatternTest001
 * @tc.desc: Test the CreateLayoutAlgorithm and IsAtomicNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test the CreateLayoutAlgorithm function.
     * @tc.expected: result is not empty.
     */
    auto result = toolBarPattern_->CreateLayoutAlgorithm();
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step2. Test the IsAtomicNode function.
     * @tc.expected: result is false.
     */
    auto atomicNode = toolBarPattern_->IsAtomicNode();
    EXPECT_FALSE(atomicNode);
}

/**
 * @tc.name: ToolbarNodeTest001
 * @tc.desc: Test the SetToolbarContainerNode, GetToolbarContainerNode and IsAtomicNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolbarNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test the SetToolbarContainerNode and GetToolbarContainerNode function.
     * @tc.expected: result is empty.
     */
    RefPtr<UINode> customNode = nullptr;
    toolBarNode_->SetToolbarContainerNode(customNode);
    auto result = toolBarNode_->GetToolbarContainerNode();
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step2. Test the IsAtomicNode function.
     * @tc.expected: result is false.
     */
    auto atomicNode = toolBarNode_->IsAtomicNode();
    EXPECT_FALSE(atomicNode);
}

/**
 * @tc.name: ToolbarNodeTest002
 * @tc.desc: Test the GetOrCreateToolbarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolbarNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialization.
     */
    std::string tag = "tag";
    int32_t nodeId = 1;
    std::function<RefPtr<Pattern>(void)> patternCreator;

    /**
     * @tc.steps: step2. Test the GetOrCreateToolbarNode function.
     * @tc.expected: result is not empty.
     */
    auto result = toolBarNode_->GetOrCreateToolbarNode(tag, nodeId, patternCreator);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: ToolBarPatternTest002
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest002, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest003
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest003, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest004
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest004, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest005
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest005, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest006
 * @tc.desc: Test the SetDefaultBackgroundColorIfNeeded function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest006, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    navToolbarPattern->options_.bgOptions.color = std::make_optional(FRONT_COLOR);
    navToolbarPattern->SetDefaultBackgroundColorIfNeeded(frameNode);
}

/**
 * @tc.name: ToolBarPatternTest007
 * @tc.desc: Test the InitLongPressEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest007, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);

    auto barItemNode = BarItemNode::GetOrCreateBarItemNode(
            V2::BAR_ITEM_ETS_TAG, 1000, []() { return AceType::MakeRefPtr<Pattern>(); });
    barItemNode->SetIconNode(imageNode);
    barItemNode->SetTextNode(textNode);

    navToolbarPattern->InitLongPressEvent(gestureHub);
    auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
    EXPECT_NE(longPressRecognizer, nullptr);
    EXPECT_NE(longPressRecognizer->onActionEnd_, nullptr);
}

/**
 * @tc.name: ToolBarPatternTest008
 * @tc.desc: Test the HandleLongPressActionEnd function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest008, TestSize.Level1)
{
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 201, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    auto navToolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);

    auto gestureHub = toolbarNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(imageNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);

    navToolbarPattern->dialogNode_ =
        FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<NavToolbarPattern>());
    ASSERT_NE(navToolbarPattern->dialogNode_, nullptr);
    navToolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(navToolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternTest009
 * @tc.desc: Test the SetToolbarOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest009, TestSize.Level1)
{
    auto frameNode =
        FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.brOptions.textHideOptions = true;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
}

/**
 * @tc.name: ToolBarPatternTest010
 * @tc.desc: Test the SetToolbarOptions function and check value.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest010, TestSize.Level1)
{
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    EXPECT_NE(toolbarNode, nullptr);
    auto navToolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    opt.brOptions.textHideOptions = true;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
    navToolbarPattern->OnModifyDone();
    EXPECT_EQ(
        navToolbarPattern->options_.bgOptions.color, FRONT_COLOR);
    EXPECT_EQ(
        navToolbarPattern->options_.bgOptions.blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(
        navToolbarPattern->options_.brOptions.textHideOptions, true);
}

/**
 * @tc.name: ToolBarPatternTest011
 * @tc.desc: Test the SetToolbarOptions function and check value.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest011, TestSize.Level1)
{
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    EXPECT_NE(toolbarNode, nullptr);
    auto navToolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
    navToolbarPattern->OnModifyDone();
    EXPECT_EQ(
        navToolbarPattern->options_.brOptions.textHideOptions, false);
}
/**
 * @tc.name: ToolBarPatternTest012
 * @tc.desc: Test the SetToolbarOptions function and check value.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternTest012, TestSize.Level1)
{
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    EXPECT_NE(toolbarNode, nullptr);
    auto navToolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.brOptions.textHideOptions = false;
    navToolbarPattern->SetToolbarOptions(std::move(opt));
    navToolbarPattern->OnModifyDone();
    EXPECT_EQ(
        navToolbarPattern->options_.brOptions.textHideOptions, false);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation001
 * @tc.desc: Test HandleTitleBarAndToolBarAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, HandleTitleBarAndToolBarAnimation001, TestSize.Level1)
{
    TestParameters testParameters;
    InitializationParameters(testParameters);
    auto navBarLayoutProperty = navBarNode_->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(navBarLayoutProperty, nullptr);
    navBarLayoutProperty->UpdateHideTitleBar(false);
    navBarLayoutProperty->UpdateHideToolBar(false);
    bool needRunTitleBarAnimation = true;
    bool needRunToolBarAnimation = true;
    navBarpattern_->HandleTitleBarAndToolBarAnimation(navBarNode_, needRunTitleBarAnimation, needRunToolBarAnimation);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode_->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_EQ(titleBarLayoutProperty->propVisibility_, VisibleType::VISIBLE);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode_->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    EXPECT_EQ(toolBarLayoutProperty->propVisibility_, VisibleType::GONE);
}

/**
 * @tc.name: HandleTitleBarAndToolBarAnimation002
 * @tc.desc: Test HandleTitleBarAndToolBarAnimation function when hide bar item text.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, HandleTitleBarAndToolBarAnimation002, TestSize.Level1)
{
    TestParameters testParameters;
    InitializationParameters(testParameters);
    auto navBarLayoutProperty = navBarNode_->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    ASSERT_NE(navBarLayoutProperty, nullptr);
    navBarLayoutProperty->UpdateHideTitleBar(false);
    navBarLayoutProperty->UpdateHideToolBar(false);
    bool needRunTitleBarAnimation = true;
    bool needRunToolBarAnimation = true;
    navBarpattern_->HandleTitleBarAndToolBarAnimation(navBarNode_, needRunTitleBarAnimation, needRunToolBarAnimation);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode_->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_EQ(titleBarLayoutProperty->propVisibility_, VisibleType::VISIBLE);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode_->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);

    auto toolbarPattern = toolBarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    NavigationToolbarOptions opt;
    opt.brOptions.textHideOptions = true;
    toolbarPattern->SetToolbarOptions(std::move(opt));
    toolbarPattern->OnModifyDone();

    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    EXPECT_EQ(toolBarLayoutProperty->propVisibility_, VisibleType::GONE);
}

/**
 * @tc.name: SetIsHideItemText001
 * @tc.desc: Test the SetIsHideItemText function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, SetIsHideItemText001, TestSize.Level1)
{
    bool hideText = true;
    bool showText = false;
    toolBarNode_->SetIsHideItemText(hideText);
    bool result = toolBarNode_->isHideItemText_;
    EXPECT_EQ(result, hideText);
    toolBarNode_->SetIsHideItemText(showText);
    result = toolBarNode_->isHideItemText_;
    EXPECT_EQ(result, showText);
}

/**
 * @tc.name: IsHideTextTest001
 * @tc.desc: Test the IsHideText function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, IsHideTextTest001, TestSize.Level1)
{
    bool hideText = true;
    bool showText = false;
    toolBarNode_->SetIsHideItemText(hideText);
    bool result = toolBarNode_->IsHideItemText();
    EXPECT_EQ(result, hideText);
    toolBarNode_->SetIsHideItemText(showText);
    result = toolBarNode_->IsHideItemText();
    EXPECT_EQ(result, showText);
}

/**
 * @tc.name: IsHideTextTest002
 * @tc.desc: Test the IsHideText function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, IsHideTextTest002, TestSize.Level1)
{
    bool hideText = true;
    bool showText = false;
    toolBarNode_->SetIsHideItemText(showText);
    bool result = toolBarNode_->IsHideItemText();
    EXPECT_EQ(result, showText);
    toolBarNode_->SetIsHideItemText(hideText);
    result = toolBarNode_->IsHideItemText();
    EXPECT_EQ(result, hideText);
}

/**
 * @tc.name: HideOrShowTitleBarImmediately001
 * @tc.desc: Test HideOrShowTitleBarImmediately function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, HideOrShowTitleBarImmediately001, TestSize.Level1)
{
    TestParameters testParameters;
    InitializationParameters(testParameters);
    navBarpattern_->HideOrShowTitleBarImmediately(navBarNode_, true);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode_->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_EQ(titleBarLayoutProperty->propVisibility_, VisibleType::GONE);
}

/**
 * @tc.name: HideOrShowToolBarImmediately001
 * @tc.desc: Test HideOrShowToolBarImmediately function.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, HideOrShowToolBarImmediately001, TestSize.Level1)
{
    TestParameters testParameters;
    InitializationParameters(testParameters);
    navBarpattern_->HideOrShowToolBarImmediately(navBarNode_, true);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode_->GetToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    ASSERT_NE(toolBarLayoutProperty, nullptr);
    EXPECT_EQ(toolBarLayoutProperty->propVisibility_, VisibleType::GONE);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest001
 * @tc.desc: Test the HandleLongPressEvent function with fontScale 1.75 and more than five toolbar nodes.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 1.75.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 1.75f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create more than five toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    std::vector<NG::BarItem> toolBarItems;
    InitToolBarItemInfos(toolBarItems);
    EXPECT_EQ(toolBarItems.size(), 6);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest002
 * @tc.desc: Test the HandleLongPressEvent function with fontScale 2.0 and more than five toolbar nodes.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 2.0.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 2.0f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create more than five toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    std::vector<NG::BarItem> toolBarItems;
    InitToolBarItemInfos(toolBarItems);
    EXPECT_EQ(toolBarItems.size(), 6);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest003
 * @tc.desc: Test the HandleLongPressEvent function with fontScale 3.2 and more than five toolbar nodes.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 3.2.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 3.2f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create more than five toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    std::vector<NG::BarItem> toolBarItems;
    InitToolBarItemInfos(toolBarItems);
    EXPECT_EQ(toolBarItems.size(), 6);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest004
 * @tc.desc: Test the HandleLongPressEvent function with fontScale 1.75 and single toolbar node.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 1.75.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 1.75f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create single toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    std::vector<NG::BarItem> toolBarItems;
    bool isEnabled = true;
    std::function<void()> menuAction = [&isEnabled]() {
        isEnabled = !isEnabled;
    };
    BarItem toolBarItemOne = {
        .text = "toolBarItemOne",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemOne);
    EXPECT_EQ(toolBarItems.size(), 1);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest005
 * @tc.desc: Test the HandleLongPressEvent function with fontScale 2.0 and single toolbar node.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 2.0.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 2.0f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create single toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    std::vector<NG::BarItem> toolBarItems;
    bool isEnabled = true;
    std::function<void()> menuAction = [&isEnabled]() {
        isEnabled = !isEnabled;
    };
    BarItem toolBarItemOne = {
        .text = "toolBarItemOne",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemOne);
    EXPECT_EQ(toolBarItems.size(), 1);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest006
 * @tc.desc: Test the HandleLongPressEvent function with fontScale 3.2 and single toolbar node.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 3.2.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 3.2f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create single toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    std::vector<NG::BarItem> toolBarItems;
    bool isEnabled = true;
    std::function<void()> menuAction = [&isEnabled]() {
        isEnabled = !isEnabled;
    };
    BarItem toolBarItemOne = {
        .text = "toolBarItemOne",
        .icon = "file://data/data/com.example.test/res/example.svg",
        .isEnabled = isEnabled,
        .action = menuAction };
    toolBarItems.push_back(toolBarItemOne);
    EXPECT_EQ(toolBarItems.size(), 1);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest007
 * @tc.desc: Test the HandleLongPressEvent function with toolbar options.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 1.75.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 1.75f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create more than five toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    opt.brOptions.textHideOptions = true;
    toolbarPattern->SetToolbarOptions(std::move(opt));
    toolbarPattern->OnModifyDone();
    EXPECT_EQ(
        toolbarPattern->options_.bgOptions.color, FRONT_COLOR);
    EXPECT_EQ(
        toolbarPattern->options_.bgOptions.blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(
        toolbarPattern->options_.brOptions.textHideOptions, true);

    std::vector<NG::BarItem> toolBarItems;
    InitToolBarItemInfos(toolBarItems);
    EXPECT_EQ(toolBarItems.size(), 6);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 0.0f;
    info.globalLocation_.deltaY_ = 0.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}


/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest008
 * @tc.desc: Test the HandleLongPressEvent function with toolbar options.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 1.75.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 3.5f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create more than five toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    opt.brOptions.textHideOptions = true;
    toolbarPattern->SetToolbarOptions(std::move(opt));
    toolbarPattern->OnModifyDone();
    EXPECT_EQ(
        toolbarPattern->options_.bgOptions.color, FRONT_COLOR);
    EXPECT_EQ(
        toolbarPattern->options_.bgOptions.blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(
        toolbarPattern->options_.brOptions.textHideOptions, true);

    std::vector<NG::BarItem> toolBarItems;
    InitToolBarItemInfos(toolBarItems);
    EXPECT_EQ(toolBarItems.size(), 6);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 1.0f;
    info.globalLocation_.deltaY_ = 1.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}


/**
 * @tc.name: ToolBarPatternHandleLongPressEventTest009
 * @tc.desc: Test the HandleLongPressEvent function with toolbar options.
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, ToolBarPatternHandleLongPressEventTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init relative params and set font scale to 1.75.
     */
    ToolBarTestNg::MockPipelineContextGetTheme();
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->fontScale_ = 0.75f;
    TestParameters testParameters;
    InitializationParameters(testParameters);

    /**
     * @tc.steps: step2. create toolBar and initialize children component. create more than five toolBar node.
     */
    auto containerNode = FrameNode::GetOrCreateFrameNode(
        "Container", 101, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    ASSERT_NE(containerNode, nullptr);
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "Toolbar", 301, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolbarNode, nullptr);
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    
    NavigationToolbarOptions opt;
    opt.bgOptions.color = std::make_optional(FRONT_COLOR);
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    opt.brOptions.textHideOptions = true;
    toolbarPattern->SetToolbarOptions(std::move(opt));
    toolbarPattern->OnModifyDone();
    EXPECT_EQ(
        toolbarPattern->options_.bgOptions.color, FRONT_COLOR);
    EXPECT_EQ(
        toolbarPattern->options_.bgOptions.blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);
    EXPECT_EQ(
        toolbarPattern->options_.brOptions.textHideOptions, true);

    std::vector<NG::BarItem> toolBarItems;
    InitToolBarItemInfos(toolBarItems);
    EXPECT_EQ(toolBarItems.size(), 6);
    UpdateBarItemNodeWithItem(toolbarNode, toolBarItems);
    toolbarPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call HandleLongPressEvent.
     * @tc.expected: dialog_ == nullptr
     */
    GestureEvent info;
    info.globalLocation_.deltaX_ = 1.0f;
    info.globalLocation_.deltaY_ = 1.0f;
    toolbarPattern->HandleLongPressEvent(info);
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. call HandleLongPressActionEnd.
     * @tc.expected: dialog_ == nullptr
     */
    toolbarPattern->HandleLongPressActionEnd();
    EXPECT_EQ(toolbarPattern->dialogNode_, nullptr);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Branch: if (LessNotEqual(scale, GetDialogBigFontSizeScale())) = false
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, OnModifyDone001, TestSize.Level1)
{
    auto containerNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    auto pipelineContext = containerNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() + 1.0f;
    auto accessibilityProperty = containerNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);

    toolbarPattern->OnModifyDone();
    EXPECT_EQ(accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Branch: if (LessNotEqual(scale, GetDialogBigFontSizeScale())) = true
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, OnModifyDone002, TestSize.Level1)
{
    auto containerNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    auto pipelineContext = containerNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->fontScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale() - 1.0f;
    auto accessibilityProperty = containerNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);

    toolbarPattern->OnModifyDone();
    EXPECT_NE(accessibilityProperty->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);
}

/**
 * @tc.name: InitDragEvent001
 * @tc.desc: Branch: if (toolBarPattern->dialogNode_ && index >= 0 && index < totalCount) = true
 *           Condition: toolBarPattern->dialogNode_ = true, index >= 0 = true, index < totalCount = true
 *           Branch: if (!toolBarPattern->moveIndex_.has_value()) = false
 *           Branch: if (toolBarPattern->moveIndex_ != index) = true
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, InitDragEvent001, TestSize.Level1)
{
    ToolBarTestNg::SetUpTestSuite();
    auto containerNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    // Make toolBarItemNode not NULL
    auto toolBarItem1Node = FrameNode::GetOrCreateFrameNode(V2::BAR_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    toolBarItem1Node->isActive_ = true;
    auto geometryNode = toolBarItem1Node->GetGeometryNode();
    geometryNode->SetFrameWidth(100);
    geometryNode->SetFrameHeight(50);
    containerNode->children_.emplace_front(toolBarItem1Node);
    // Make toolBarPattern->dialogNode_ true
    auto dialogNode = FrameNode::GetOrCreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    toolbarPattern->dialogNode_ = dialogNode;
    toolbarPattern->moveIndex_ = -1;
    auto renderContext = toolBarItem1Node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);
    buttonTheme_->clickedColor_ = Color::GREEN;

    auto gestureHub = containerNode->GetOrCreateGestureEventHub();
    toolbarPattern->InitDragEvent(gestureHub);
    ASSERT_NE(gestureHub->GetDragEventActuator(), nullptr);
    ASSERT_NE(gestureHub->GetDragEventActuator()->userCallback_, nullptr);
    auto actionUpdate = gestureHub->GetDragEventActuator()->userCallback_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info;
    actionUpdate(info);
    EXPECT_EQ(toolbarPattern->moveIndex_, 0);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::GREEN);
    ToolBarTestNg::TearDownTestSuite();
}

/**
 * @tc.name: InitDragEvent002
 * @tc.desc: Branch: if (toolBarPattern->dialogNode_ && index >= 0 && index < totalCount) = true
 *           Condition: toolBarPattern->dialogNode_ = true, index >= 0 = true, index < totalCount = true
 *           Branch: if (!toolBarPattern->moveIndex_.has_value()) = true
 *           Branch: if (toolBarPattern->moveIndex_ != index) = false
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, InitDragEvent002, TestSize.Level1)
{
    ToolBarTestNg::SetUpTestSuite();
    auto containerNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    // Make toolBarItemNode not NULL
    auto toolBarItem1Node = FrameNode::GetOrCreateFrameNode(V2::BAR_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    toolBarItem1Node->isActive_ = true;
    auto geometryNode = toolBarItem1Node->GetGeometryNode();
    geometryNode->SetFrameWidth(100);
    geometryNode->SetFrameHeight(50);
    containerNode->children_.emplace_front(toolBarItem1Node);
    // Make toolBarPattern->dialogNode_ true
    auto dialogNode = FrameNode::GetOrCreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    toolbarPattern->dialogNode_ = dialogNode;
    toolbarPattern->moveIndex_ = 0;
    auto renderContext = toolBarItem1Node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateBackgroundColor(Color::BLUE);
    buttonTheme_->clickedColor_ = Color::GREEN;

    auto gestureHub = containerNode->GetOrCreateGestureEventHub();
    toolbarPattern->InitDragEvent(gestureHub);
    ASSERT_NE(gestureHub->GetDragEventActuator(), nullptr);
    ASSERT_NE(gestureHub->GetDragEventActuator()->userCallback_, nullptr);
    auto actionUpdate = gestureHub->GetDragEventActuator()->userCallback_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info;
    actionUpdate(info);
    EXPECT_EQ(toolbarPattern->moveIndex_, 0);
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::BLUE);
    ToolBarTestNg::TearDownTestSuite();
}

/**
 * @tc.name: InitDragEvent003
 * @tc.desc: Branch: if (toolBarPattern->dialogNode_ && index >= 0 && index < totalCount) = true
 *           Condition: toolBarPattern->dialogNode_ = false
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, InitDragEvent003, TestSize.Level1)
{
    ToolBarTestNg::SetUpTestSuite();
    auto containerNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto toolbarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TOOL_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolbarNode->SetToolbarContainerNode(containerNode);
    auto toolbarPattern = toolbarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolbarPattern, nullptr);
    // Make toolBarItemNode not NULL
    auto toolBarItem1Node = FrameNode::GetOrCreateFrameNode(V2::BAR_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    toolBarItem1Node->isActive_ = true;
    auto geometryNode = toolBarItem1Node->GetGeometryNode();
    geometryNode->SetFrameWidth(100);
    geometryNode->SetFrameHeight(50);
    containerNode->children_.emplace_front(toolBarItem1Node);
    toolbarPattern->moveIndex_ = -1;

    auto gestureHub = containerNode->GetOrCreateGestureEventHub();
    toolbarPattern->InitDragEvent(gestureHub);
    ASSERT_NE(gestureHub->GetDragEventActuator(), nullptr);
    ASSERT_NE(gestureHub->GetDragEventActuator()->userCallback_, nullptr);
    auto actionUpdate = gestureHub->GetDragEventActuator()->userCallback_->GetActionUpdateEventFunc();
    ASSERT_NE(actionUpdate, nullptr);
    GestureEvent info;
    actionUpdate(info);
    EXPECT_EQ(toolbarPattern->moveIndex_, -1);
    ToolBarTestNg::TearDownTestSuite();
}

/**
 * @tc.name: SetToolbarMoreButtonOptionsTest001
 * @tc.desc: Branch: if (options_.bgOptions.blurStyleOption.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, SetToolbarMoreButtonOptionsTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    MoreButtonOptions opt;
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    opt.bgOptions.blurStyleOption = blurStyleOption;
    navToolbarPattern->SetToolbarMoreButtonOptions(std::move(opt));
    EXPECT_EQ(
        navToolbarPattern->GetToolbarMoreButtonOptions().bgOptions.blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);
}

/**
 * @tc.name: SetToolbarMoreButtonOptionsTest002
 * @tc.desc: Branch: if (options_.bgOptions.effectOption.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(ToolBarTestNg, SetToolbarMoreButtonOptionsTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("BackButton", 33, AceType::MakeRefPtr<NavToolbarPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto navToolbarPattern = frameNode->GetPattern<NavToolbarPattern>();
    EXPECT_NE(navToolbarPattern, nullptr);
    MoreButtonOptions opt;
    EffectOption effectOption;
    effectOption.adaptiveColor = AdaptiveColor::DEFAULT;
    opt.bgOptions.effectOption = effectOption;
    navToolbarPattern->SetToolbarMoreButtonOptions(std::move(opt));
    EXPECT_EQ(
        navToolbarPattern->GetToolbarMoreButtonOptions().bgOptions.effectOption->adaptiveColor, AdaptiveColor::DEFAULT);
}
} // namespace OHOS::Ace::NG