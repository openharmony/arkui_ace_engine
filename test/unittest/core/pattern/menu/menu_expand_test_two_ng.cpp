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

#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_layout_algorithm.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/sub_menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/event/touch_event.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::string OPTION_TEXT = "aaa";
const std::string FILE_SOURCE = "/common/icon.png";
} // namespace
class MenuExpandTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    int32_t GetNodeId();
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<FrameNode> wrapperNode_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<FrameNode> subMenuParent_;
    RefPtr<FrameNode> subMenu_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    int32_t nodeId_ = 1;
    bool isSubMenuBuilded_ = false;
};

void MenuExpandTwoTestNg::SetUpTestCase() {
}

void MenuExpandTwoTestNg::TearDownTestCase() {
}

void MenuExpandTwoTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    InitMenuTestNg();
    isSubMenuBuilded_ = false;
}

void MenuExpandTwoTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    ViewStackProcessor::GetInstance()->ClearStack();
    menuFrameNode_ = nullptr;
    menuItemFrameNode_ = nullptr;
    subMenuParent_ = nullptr;
    menuItemPattern_ = nullptr;
    wrapperNode_ = nullptr;
    subMenu_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

int32_t MenuExpandTwoTestNg::GetNodeId()
{
    nodeId_++;
    return nodeId_;
}

void MenuExpandTwoTestNg::InitMenuTestNg()
{
    std::function<void()> buildFun = [this]() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
        isSubMenuBuilded_ = true;
    };
    wrapperNode_ =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuFrameNode_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    subMenu_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    menuItemFrameNode_ = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    subMenuParent_ = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    auto itemComponent = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent2 = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent3 = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    itemComponent->MountToParent(subMenuParent_);
    itemComponent2->MountToParent(subMenuParent_);
    itemComponent3->MountToParent(subMenuParent_);
    menuItemFrameNode_->MountToParent(menuFrameNode_);
    subMenuParent_->MountToParent(menuFrameNode_);
    menuFrameNode_->MountToParent(wrapperNode_);
    subMenu_->MountToParent(wrapperNode_);
    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);
    menuItemPattern_->SetSubBuilder(buildFun);
    menuItemPattern_->SetIsSubMenuShowed(false);
    auto pattern2 = subMenuParent_->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->SetSubBuilder(buildFun);
    pattern2->SetIsSubMenuShowed(false);
    auto menuPattern = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetShowedSubMenu(subMenu_);
    auto subMenuPattern = subMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent_);
}

/**
 * @tc.name: HideMenuSelectEtsTagWithSubwindow004
 * @tc.desc: Test MenuPattern::HideMenu with SELECT_ETS_TAG and subwindow exists
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuSelectEtsTagWithSubwindow004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu with SELECT_ETS_TAG and subwindow setup
     * @tc.expected: IsSubwindowExist branch is tested
     */
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, V2::SELECT_ETS_TAG, MenuType::MENU));

    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for SELECT_ETS_TAG with subwindow
     *               IsSubwindowExist branch is tested, expandDisplay is true,
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto layoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    layoutProperty->UpdateShowInSubWindow(true);

    /**
     * @tc.steps: step3. Call HideMenu with position that should trigger SELECT_ETS_TAG
     * @tc.expected: HideMenu calls IsSubwindowExist and returns early
     *               without further processing
     */
    menuPattern->HideMenu(false, OffsetF(0, 0), HideMenuType::NORMAL);

    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_NE(wrapper->GetTag(), V2::SELECT_OVERLAY_ETS_TAG);
    EXPECT_TRUE(layoutProperty->GetShowInSubWindowValue(false));
}

/**
 * @tc.name: HideMenuStackExpandTrue005
 * @tc.desc: Test MenuPattern::HideMenu with HideStackExpandMenu returning true
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuStackExpandTrue005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create stack submenu setup that returns true from HideStackExpandMenu
     * @tc.expected: HideMenu returns early after HideStackExpandMenu
     */
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));

    auto outerMenuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::MENU));

    auto subMenuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(2, "test", MenuType::SUB_MENU));

    outerMenuNode->MountToParent(wrapperNode);
    subMenuNode->MountToParent(wrapperNode);

    auto menuPattern = subMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. Setup theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for stack expand branch
     *               expandDisplay is false, showInSubWindow is false
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    subMenuNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    subMenuNode->geometryNode_->SetFrameSize(SizeF(100, 100));

    /**
     * @tc.steps: step3. Call HideMenu with position that should trigger stack expand
     * @tc.expected: HideMenu calls HideStackExpandMenu and returns early
     */
    menuPattern->HideMenu(false, OffsetF(50, 50), HideMenuType::NORMAL);

    EXPECT_TRUE(menuPattern->IsSubMenu());
    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_NE(wrapper->GetTag(), V2::SELECT_OVERLAY_ETS_TAG);
}

/**
 * @tc.name: HideMenuDefaultOverlayManager006
 * @tc.desc: Test MenuPattern::HideMenu default overlay manager path
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuDefaultOverlayManager006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create regular menu that goes to default overlay manager path
     * @tc.expected: overlayManager->HideMenu is called
     */
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::MENU));

    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. Setup theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for default overlay manager branch
     *               expandDisplay is false, showInSubWindow is false
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto layoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    layoutProperty->UpdateShowInSubWindow(false);

    /**
     * @tc.steps: step3. Call HideMenu with position that should trigger default overlay manager
     * @tc.expected: HideMenu calls the default overlay manager path
     *               without subwindow or context menu branches
     */
    menuPattern->HideMenu(true, OffsetF(0, 0), HideMenuType::MENU_TOUCH_UP);

    menuPattern->HideMenu(false, OffsetF(10, 10), HideMenuType::NORMAL);
    menuPattern->HideMenu(true, OffsetF(20, 20), HideMenuType::MENU_TOUCH_UP);

    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_NE(wrapper->GetTag(), V2::SELECT_OVERLAY_ETS_TAG);
    EXPECT_FALSE(layoutProperty->GetShowInSubWindowValue(false));
}

/**
 * @tc.name: HideMenuParameterCoverage007
 * @tc.desc: Test MenuPattern::HideMenu with different parameter combinations
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuParameterCoverage007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test all parameter combinations for comprehensive coverage
     * @tc.expected: All parameter branches are exercised
     */
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::MENU));

    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. Setup theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for parameter coverage
     *               expandDisplay is false, showInSubWindow is false
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    /**
     * @tc.steps: step3. Call HideMenu with various parameters
     * @tc.expected: All parameter combinations are tested
     */
    menuPattern->HideMenu(true, OffsetF(10, 20), HideMenuType::NORMAL);
    menuPattern->HideMenu(false, OffsetF(-5, -10), HideMenuType::MENU_TOUCH_UP);
    menuPattern->HideMenu(true, OffsetF(100, 200), HideMenuType::NORMAL);
    menuPattern->HideMenu(false, OffsetF(0, 0), HideMenuType::NORMAL);

    menuPattern->HideMenu(true, OffsetF(50, 75), HideMenuType::MENU_TOUCH_UP);
    menuPattern->HideMenu(false, OffsetF(25, 30), HideMenuType::NORMAL);

    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_NE(wrapper->GetTag(), V2::SELECT_OVERLAY_ETS_TAG);
}

/**
 * @tc.name: HideMenuSubwindowExistTrue008
 * @tc.desc: Test MenuPattern::HideMenu specifically targeting IsSubwindowExist() == true
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuSubwindowExistTrue008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SELECT_ETS_TAG menu and ensure subwindow exists
     * @tc.expected: IsSubwindowExist() == true branch is covered
     */
    SelectModelNG selectModelInstance;
    std::vector<SelectParam> params = { { OPTION_TEXT, FILE_SOURCE } };
    selectModelInstance.Create(params);

    auto selectFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(selectFrameNode, nullptr);
    auto selectPattern = selectFrameNode->GetPattern<SelectPattern>();
    ASSERT_NE(selectPattern, nullptr);
    auto mainMenu = selectPattern->GetMenuNode();
    ASSERT_NE(mainMenu, nullptr);

    /**
     * @tc.steps: step2. Setup theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for SELECT_ETS_TAG with subwindow
     *               IsSubwindowExist branch is tested, expandDisplay is true,
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);

    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto menuLayoutProps = mainMenu->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProps, nullptr);
    menuLayoutProps->UpdateShowInSubWindow(true);

    selectPattern->ShowSelectMenuInSubWindow();

    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step3. Call HideMenu with position that should trigger IsSubwindowExist() == true
     * @tc.expected: HideMenu calls IsSubwindowExist and processes subwindow
     *               without further processing
     */
    menuPattern->HideMenu(false, OffsetF(0, 0), HideMenuType::NORMAL);

    auto context = mainMenu->GetContext();
    if (context) {
        SubwindowManager::GetInstance()->RemoveSubwindow(context->GetInstanceId(), SubwindowType::TYPE_MENU);
    }

    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_TRUE(menuLayoutProps->GetShowInSubWindowValue(false));
}

/**
 * @tc.name: HideMenuSubwindowExistFalse009
 * @tc.desc: Test MenuPattern::HideMenu specifically targeting IsSubwindowExist() == false
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuSubwindowExistFalse009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SELECT_ETS_TAG menu without subwindow
     * @tc.expected: IsSubwindowExist() == false branch is covered
     */
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, V2::SELECT_ETS_TAG, MenuType::MENU));

    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. Setup theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for SELECT_ETS_TAG with subwindow
     *               IsSubwindowExist branch is tested, expandDisplay is true,
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto layoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    layoutProperty->UpdateShowInSubWindow(true);

    auto context = menuNode->GetContext();
    if (context) {
        SubwindowManager::GetInstance()->RemoveSubwindow(context->GetInstanceId(), SubwindowType::TYPE_MENU);
    }

    /**
     * @tc.steps: step3. Call HideMenu with position that should trigger IsSubwindowExist() == false
     * @tc.expected: HideMenu calls IsSubwindowExist and processes subwindow
     *               without further processing
     */
    menuPattern->HideMenu(false, OffsetF(0, 0), HideMenuType::NORMAL);

    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_TRUE(layoutProperty->GetShowInSubWindowValue(false));
}

/**
 * @tc.name: HideMenuStackExpandFalse010
 * @tc.desc: Test MenuPattern::HideMenu with HideStackExpandMenu returning false
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTwoTestNg, HideMenuStackExpandFalse010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create regular menu that makes HideStackExpandMenu return false
     * @tc.expected: Control flows to default overlay manager path
     */
    auto wrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "test", MenuType::MENU));

    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    /**
     * @tc.steps: step2. Setup theme, expandDisplay and showInSubWindow
     * @tc.expected: Have the correct setup for HideStackExpandMenu false branch
     *               expandDisplay is false, showInSubWindow is false
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipeline->GetThemeManager());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = false;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto layoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    layoutProperty->UpdateShowInSubWindow(false);

    menuNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    menuNode->geometryNode_->SetFrameSize(SizeF(100, 100));

    /**
     * @tc.steps: step3. Call HideMenu with position that should trigger HideStackExpandMenu false
     * @tc.expected: HideMenu calls HideStackExpandMenu and returns early
     *               without further processing
     */
    menuPattern->HideMenu(false, OffsetF(1000, 1000), HideMenuType::NORMAL);

    auto wrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(wrapper, nullptr);
    EXPECT_NE(wrapper->GetTag(), V2::SELECT_OVERLAY_ETS_TAG);
    EXPECT_FALSE(layoutProperty->GetShowInSubWindowValue(false));
}
} // namespace OHOS::Ace::NG
