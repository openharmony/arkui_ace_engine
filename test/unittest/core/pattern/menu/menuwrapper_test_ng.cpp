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

#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

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
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_ITEM_TEXT = "menuItem";
const std::string MENU_ITEM_GROUP_TEXT = "menuItemGroup";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const DirtySwapConfig configDirtySwap = { false, false, false, false, true, false };
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr Dimension BORDER_RADIUS = 50.0_vp;
const BorderRadiusProperty& BORDER_RADIUS_PROPERTY = BorderRadiusProperty(BORDER_RADIUS);

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
constexpr double BORDER_RADIUS_RATE = 1.5;

const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuWrapperTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuWrapperTestNg();
    void InitMenuItemTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> GetPreviewMenuWrapper2();
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuWrapperTestNg::SetUpTestCase() {}

void MenuWrapperTestNg::TearDownTestCase() {}

void MenuWrapperTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme_ = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([menuTheme_](ThemeType type) -> RefPtr<Theme> {
        if (type == MenuTheme::TypeId()) {
            return menuTheme_;
        }
        return AceType::MakeRefPtr<SelectTheme>();
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([menuTheme_](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            if (type == MenuTheme::TypeId()) {
                return menuTheme_;
            }
            return AceType::MakeRefPtr<SelectTheme>();
        });
}

void MenuWrapperTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    menuFrameNode_ = nullptr;
    menuAccessibilityProperty_ = nullptr;
    menuItemFrameNode_ = nullptr;
    menuItemPattern_ = nullptr;
    menuItemAccessibilityProperty_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

void MenuWrapperTestNg::InitMenuWrapperTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuWrapperTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuWrapperTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuWrapperTestNg::GetPreviewMenuWrapper(
    SizeF itemSize, std::optional<MenuPreviewAnimationOptions> scaleOptions)
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    if (!(LessOrEqual(itemSize.Width(), 0.0) || LessOrEqual(itemSize.Height(), 0.0))) {
        auto itemGeometryNode = textNode->GetGeometryNode();
        CHECK_NULL_RETURN(itemGeometryNode, nullptr);
        itemGeometryNode->SetFrameSize(itemSize);
    }
    targetNode->MountToParent(rootNode);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    if (scaleOptions != std::nullopt) {
        menuParam.previewAnimationOptions = scaleOptions.value();
    }
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(customNode, nullptr);
    auto customGeometryNode = customNode->GetGeometryNode();
    CHECK_NULL_RETURN(customGeometryNode, nullptr);
    customGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    return menuWrapperNode;
}

RefPtr<FrameNode> MenuWrapperTestNg::GetPreviewMenuWrapper2()
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    targetNode->MountToParent(rootNode);
    targetNode->GetOrCreateGestureEventHub();
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(customNode, nullptr);
    auto customGeometryNode = customNode->GetGeometryNode();
    CHECK_NULL_RETURN(customGeometryNode, nullptr);
    customGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    return menuWrapperNode;
}
/**
 * @tc.name: MenuWrapperPatternTestNg001
 * @tc.desc: Verify HideMenu(Menu).
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenuFirst = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto subMenuSecond = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    mainMenu->MountToParent(wrapperNode);
    subMenuFirst->MountToParent(wrapperNode);
    subMenuSecond->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step2. excute HideMenu
     * @tc.expected: wrapper child size is 3
     */
    wrapperPattern->HideMenu(mainMenu);
    wrapperPattern->OnModifyDone();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 3);
}

/**
 * @tc.name: MenuWrapperPatternTestNg002
 * @tc.desc: Verify HideMenu().
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg002, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->HideMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuWrapperPatternTestNg003
 * @tc.desc: Verify HideSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    wrapperPattern->HideSubMenu();
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step2. add submenu to wrapper
     * @tc.expected: wrapper child size is 1
     */
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    mainMenu->MountToParent(wrapperNode);
    wrapperPattern->HideSubMenu();
    subMenu->MountToParent(wrapperNode);
    wrapperPattern->HideSubMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuWrapperPatternTestNg004
 * @tc.desc: Verify HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem and mouseInfo
     * @tc.expected: menuItem and mouseInfo function result as expected
     */
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetGlobalLocation(Offset(200, 200));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 100, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->SetIsSubMenuShowed(true);
    menuItemPattern->AddHoverRegions(OffsetF(0, 0), OffsetF(100, 100));
    const auto& mousePosition = mouseInfo.GetGlobalLocation();
    EXPECT_TRUE(!menuItemPattern->IsInHoverRegions(mousePosition.GetX(), mousePosition.GetY()));
    EXPECT_TRUE(menuItemPattern->IsSubMenuShowed());
    /**
     * @tc.steps: step2. Create menuWrapper
     * @tc.expected: wrapperPattern is not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    wrapperPattern->HandleMouseEvent(mouseInfo, menuItemPattern);
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step3. add submenu to wrapper
     * @tc.expected: wrapper child size is 2
     */
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto currentMenuItemNode =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 101, AceType::MakeRefPtr<MenuItemPattern>());
    auto currentMenuItemPattern = currentMenuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(currentMenuItemPattern, nullptr);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    currentMenuItemPattern->SetIsSubMenuShowed(true);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    EXPECT_EQ(wrapperNode->GetChildren().size(), 2);
    /**
     * @tc.steps: step4. execute HandleMouseEvent
     * @tc.expected: menuItemPattern IsSubMenuShowed as expected
     */
    subMenuPattern->SetParentMenuItem(currentMenuItemNode);
    wrapperPattern->HandleMouseEvent(mouseInfo, menuItemPattern);
    EXPECT_TRUE(currentMenuItemPattern->IsSubMenuShowed());
    subMenuPattern->SetParentMenuItem(menuItemNode);
    wrapperPattern->HandleMouseEvent(mouseInfo, menuItemPattern);
    EXPECT_FALSE(menuItemPattern->IsSubMenuShowed());
}

/**
 * @tc.name: MenuWrapperPatternTestNg005
 * @tc.desc: Verify OnTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create touchEventInfo
     * @tc.expected: touchEventInfo size is 1
     */
    TouchEventInfo contextMenuTouchUpEventInfo(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo upLocationInfo(TARGET_ID);
    Offset touchUpGlobalLocation(80, 80);
    upLocationInfo.SetTouchType(TouchType::MOVE);
    auto touchUpLocationInfo = upLocationInfo.SetGlobalLocation(touchUpGlobalLocation);
    contextMenuTouchUpEventInfo.touches_.emplace_back(touchUpLocationInfo);
    EXPECT_EQ(contextMenuTouchUpEventInfo.touches_.size(), 1);
    /**
     * @tc.steps: step2. update touchEventInfo, excute OnTouchEvent
     * @tc.expected: touchEventInfo size is 1
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->OnTouchEvent(contextMenuTouchUpEventInfo);
    upLocationInfo.SetTouchType(TouchType::DOWN);
    touchUpLocationInfo = upLocationInfo.SetGlobalLocation(touchUpGlobalLocation);
    contextMenuTouchUpEventInfo.touches_.clear();
    contextMenuTouchUpEventInfo.touches_.emplace_back(touchUpLocationInfo);
    wrapperPattern->OnTouchEvent(contextMenuTouchUpEventInfo);
    wrapperPattern->SetMenuStatus(MenuStatus::HIDE);
    wrapperPattern->OnTouchEvent(contextMenuTouchUpEventInfo);
    wrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    wrapperPattern->OnTouchEvent(contextMenuTouchUpEventInfo);
    EXPECT_EQ(contextMenuTouchUpEventInfo.touches_.size(), 1);
    /**
     * @tc.steps: step3. add submenu to wrapper,execute OnTouchEvent
     * @tc.expected: wrapper child size is 2
     */
    auto topMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto bottomMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    topMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    topMenu->MountToParent(wrapperNode);
    bottomMenu->GetGeometryNode()->SetFrameSize(SizeF(70, 70));
    bottomMenu->MountToParent(wrapperNode);
    subMenu->GetGeometryNode()->SetFrameSize(SizeF(70, 70));
    subMenu->MountToParent(wrapperNode);
    wrapperPattern->OnTouchEvent(contextMenuTouchUpEventInfo);
    wrapperPattern->HideMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 3);
}

/**
 * @tc.name: MenuWrapperPatternTestNg006
 * @tc.desc: Verify HideSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper
     * @tc.expected: wrapper pattern not null
     */
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    menuItemGroupPattern->hasSelectIcon_ = true;
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuItemGroup->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->OnModifyDone();
    auto algorithm = AceType::MakeRefPtr<MenuItemGroupLayoutAlgorithm>(-1, -1, 0);
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. create firstChildLayoutWrapper and append it to layoutWrapper
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);
    /**
     * @tc.steps: step3. add submenu to wrapper
     * @tc.expected: wrapper child size is 1
     */
    wrapperPattern->isFirstShow_ = true;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
    wrapperPattern->SetHotAreas(layoutWrapper);
}

/**
 * @tc.name: MenuWrapperPatternTestNg006
 * @tc.desc: Verify HideSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);
    /**
     * @tc.steps: step2. create firstChildLayoutWrapper and append it to layoutWrapper
     */
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);
    /**
     * @tc.steps: step3. add submenu to wrapper
     * @tc.expected: wrapper child size is 1
     */
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->isFirstShow_ = true;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
    wrapperPattern->GetMenu()->GetPattern<MenuPattern>()->SetType(MenuType::CONTEXT_MENU);
    wrapperPattern->SetHotAreas(layoutWrapper);
}

/**
 * @tc.name: MenuWrapperPatternTestNg008
 * @tc.desc: CallMenuStateChangeCallback (Menu).
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));

    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step2. execute HideMenu
     * @tc.expected: wrapper child size is 3
     */
    int32_t callNum = 0;
    std::function<void(const std::string&)> callback = [&](const std::string& param) { callNum++; };
    wrapperPattern->RegisterMenuStateChangeCallback(callback);
    wrapperPattern->CallMenuStateChangeCallback("false");
    EXPECT_EQ(callNum, 1);
}

/**
 * @tc.name: MenuWrapperPatternTestNg011
 * @tc.desc: Test Verify interaction effect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API12.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto wrapPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapPattern, nullptr);
    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset location(1, 1);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(location);
    info.touches_.emplace_back(locationInfo);
    /**
     * @tc.steps: step2. receive event and test hover event.
     */
    wrapPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapPattern->currentTouchItem_, nullptr);

    auto menuframeNode = wrapPattern->GetMenuChild(menuWrapperNode);
    EXPECT_NE(menuframeNode, nullptr);
    /**
     * @tc.steps: step3. create menuitem and test longpress event.
     */
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 100, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->InitLongPressEvent();
    ASSERT_NE(menuItemPattern->longPressEvent_, nullptr);
    GestureEvent gestureEvent;
    gestureEvent.offsetY_ = 1.0;
    (*menuItemPattern->longPressEvent_)(gestureEvent);
    ASSERT_FALSE(menuItemPattern->isSubMenuShowed_);
}
/**
 * @tc.name: MenuWrapperPatternTestNg012
 * @tc.desc: Verify HideMenu(Menu).
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::SELECT_OVERLAY_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step2. excute HideMenu
     * @tc.expected: wrapper pattern return
     */
    wrapperPattern->HideMenu(mainMenu);
    EXPECT_TRUE(mainMenu->GetTag() == V2::SELECT_OVERLAY_ETS_TAG);
}

/**
 * @tc.name: MenuWrapperPatternTestNg013
 * @tc.desc: Verify HandleInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg013, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);
    auto container =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU));
    auto mockScroll = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    auto mockContainerContext = AceType::DynamicCast<MockRenderContext>(container->GetRenderContext());
    mockContainerContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto mockMenuContext = AceType::DynamicCast<MockRenderContext>(menu->GetRenderContext());
    mockMenuContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 70.0f, 70.0f));
    mockScroll->MountToParent(container);
    menu->MountToParent(mockScroll);
    container->MountToParent(wrapperNode);

    auto menuItemNode1 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode1->MountToParent(menu);
    auto mockMenuItemContext1 = AceType::DynamicCast<MockRenderContext>(menuItemNode1->GetRenderContext());
    mockMenuItemContext1->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 30.0f, 30.0f));

    auto menuItemNode2 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode2->MountToParent(menu);
    auto mockMenuItemContext2 = AceType::DynamicCast<MockRenderContext>(menuItemNode2->GetRenderContext());
    mockMenuItemContext2->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 30.0f, 30.0f));

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetGlobalLocation(Offset(10, 10));
    Offset location(10, 10);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(location);
    info.changedTouches_.emplace_back(locationInfo);

    wrapperPattern->SetLastTouchItem(menuItemNode2);
    wrapperPattern->currentTouchItem_ = menuItemNode1;
    wrapperPattern->HandleInteraction(info);
    EXPECT_EQ(wrapperPattern->lastTouchItem_, wrapperPattern->currentTouchItem_);

    wrapperPattern->currentTouchItem_ = menuItemNode2;
    wrapperPattern->HandleInteraction(info);
    EXPECT_EQ(wrapperPattern->lastTouchItem_, wrapperPattern->currentTouchItem_);
}

/**
 * @tc.name: MenuWrapperPatternTestNg014
 * @tc.desc: Verify HandleInteraction when it is not in region.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg014, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);
    auto container =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU));
    auto mockScroll = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>());
    container->GetGeometryNode()->SetFrameSize(SizeF(200, 200));
    menu->GetGeometryNode()->SetFrameSize(SizeF(70, 70));
    mockScroll->MountToParent(container);
    menu->MountToParent(mockScroll);
    container->MountToParent(wrapperNode);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    textNode->MountToParent(menu);
    auto menuItemNode1 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode1->MountToParent(menu);

    auto menuItemNode2 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode2->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetGlobalLocation(Offset(10, 10));
    Offset location(10, 10);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(location);
    info.changedTouches_.emplace_back(locationInfo);

    wrapperPattern->SetLastTouchItem(menuItemNode2);
    wrapperPattern->currentTouchItem_ = menuItemNode1;
    wrapperPattern->HandleInteraction(info);

    container->GetGeometryNode()->SetFrameSize(SizeF(0, 0));
    menu->GetGeometryNode()->SetFrameSize(SizeF(0, 0));
    wrapperPattern->HandleInteraction(info);
    EXPECT_EQ(wrapperPattern->GetLastTouchItem(), nullptr);
}

/**
 * @tc.name: MenuWrapperPatternTestNg015
 * @tc.desc: Verify HideSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg015, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);
    model.Create();
    auto menu2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu2, nullptr);
    auto mainMenu = FrameNode::CreateFrameNode("", 1, AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        "", 11, AceType::MakeRefPtr<MenuPattern>(11, "", MenuType::SUB_MENU));

    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    wrapperPattern->HideSubMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);

    subMenu->MountToParent(wrapperNode);
    menu->MountToParent(mainMenu);
    menu2->MountToParent(subMenu);

    auto menuItemNode1 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode1->MountToParent(menu);

    auto menuItemNode2 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode2->MountToParent(menu2);

    wrapperPattern->HideSubMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);

    subMenu->MountToParent(wrapperNode);
    menu->GetLayoutProperty<MenuLayoutProperty>()->UpdateExpandingMode(SubMenuExpandingMode::STACK);
    menu2->GetLayoutProperty<MenuLayoutProperty>()->UpdateExpandingMode(SubMenuExpandingMode::STACK);
    mainMenu->GetPattern<MenuPattern>()->SetDisappearAnimation(true);
    subMenu->GetPattern<MenuPattern>()->SetDisappearAnimation(true);
    wrapperPattern->HideSubMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuWrapperPatternTestNg016
 * @tc.desc: Verify OnTouchEvent when TouchType is up.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg016, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::UP);
    info.changedTouches_.emplace_back(locationInfo);

    wrapperPattern->fingerId_ = locationInfo.fingerId_;
    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->currentTouchItem_, nullptr);
}

/**
 * @tc.name: MenuWrapperPatternTestNg017
 * @tc.desc: Verify SetHotAreas.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg017, TestSize.Level1)
{
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuItemGroup->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    auto props = layoutWrapperNode->GetLayoutProperty();

    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    SafeAreaInsets safeArea;
    props->UpdateSafeAreaInsets(safeArea);
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapperNode->AppendChild(childWrapper);
        for (int32_t i = 0; i < 1; ++i) {
            auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
            auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
            auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
            itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
            auto grandsonWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
            childWrapper->AppendChild(grandsonWrapper);
        }
    }
    auto layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->instanceId_ = MIN_SUBCONTAINER_ID;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
}

/**
 * @tc.name: MenuWrapperPatternTestNg018
 * @tc.desc: Verify HideMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg018, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);
    model.Create();
    auto menu2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu2, nullptr);
    auto mainMenuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU);
    auto mainMenu = FrameNode::CreateFrameNode("", 1, mainMenuPattern);
    auto subMenuPattern = AceType::MakeRefPtr<MenuPattern>(11, "", MenuType::SUB_MENU);
    auto subMenu = FrameNode::CreateFrameNode("", 11, subMenuPattern);

    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    wrapperPattern->HideSubMenu();

    subMenu->MountToParent(wrapperNode);
    menu->MountToParent(mainMenu);
    menu2->MountToParent(subMenu);
    menu->GetLayoutProperty<MenuLayoutProperty>()->UpdateExpandingMode(SubMenuExpandingMode::EMBEDDED);
    menu2->GetLayoutProperty<MenuLayoutProperty>()->UpdateExpandingMode(SubMenuExpandingMode::STACK);

    auto menuItemNode1 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode1->MountToParent(menu);
    auto menuItemPattern1 = menuItemNode1->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern1, nullptr);
    auto menuItemNode2 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode2->MountToParent(menu2);
    auto menuItemPattern2 = menuItemNode2->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern2, nullptr);

    wrapperPattern->IncreaseEmbeddedSubMenuCount();
    wrapperPattern->HideMenu(mainMenuPattern, mainMenu, PointF(0, 0));
    EXPECT_EQ(wrapperNode->GetChildren().size(), 2);

    wrapperPattern->HideMenu(subMenuPattern, subMenu, PointF(0, 0));
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);
    subMenu->MountToParent(wrapperNode);

    menu->GetLayoutProperty<MenuLayoutProperty>()->UpdateExpandingMode(SubMenuExpandingMode::STACK);
    wrapperPattern->HideMenu(subMenuPattern, subMenu, PointF(0, 0));
    EXPECT_EQ(wrapperNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuViewTestNg001
 * @tc.desc: Test Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuViewTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set API12.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto menuWrapperNode = GetPreviewMenuWrapper2();
    ASSERT_NE(menuWrapperNode, nullptr);
}

/**
 * @tc.name: MenuWrapperPatternTestNg019
 * @tc.desc: Verify HandleInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg019, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);
    auto container =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU));
    auto mockScroll = FrameNode::CreateFrameNode("", 2, AceType::MakeRefPtr<Pattern>());
    auto mockContainerContext = AceType::DynamicCast<MockRenderContext>(container->GetRenderContext());
    mockContainerContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 200.0f, 200.0f));
    auto mockMenuContext = AceType::DynamicCast<MockRenderContext>(menu->GetRenderContext());
    mockMenuContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 70.0f, 70.0f));
    mockScroll->MountToParent(container);
    menu->MountToParent(mockScroll);
    container->MountToParent(wrapperNode);

    auto menuItemNode1 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode1->MountToParent(menu);
    auto mockMenuItemContext1 = AceType::DynamicCast<MockRenderContext>(menuItemNode1->GetRenderContext());
    mockMenuItemContext1->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 30.0f, 30.0f));
    auto curMenuItemPattern = menuItemNode1->GetPattern<MenuItemPattern>();
    ASSERT_NE(curMenuItemPattern, nullptr);
    curMenuItemPattern->isStackSubmenuHeader_ = true;
    
    auto menuItemNode2 = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode2->MountToParent(menu);
    auto mockMenuItemContext2 = AceType::DynamicCast<MockRenderContext>(menuItemNode2->GetRenderContext());
    mockMenuItemContext2->SetPaintRectWithTransform(RectF(0.0f, 0.0f, 30.0f, 30.0f));

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetGlobalLocation(Offset(10, 10));
    Offset location(10, 10);
    locationInfo.SetTouchType(TouchType::MOVE);
    locationInfo.SetLocalLocation(location);
    info.changedTouches_.emplace_back(locationInfo);

    wrapperPattern->SetLastTouchItem(menuItemNode2);
    wrapperPattern->currentTouchItem_ = menuItemNode1;
    wrapperPattern->HandleInteraction(info);
    EXPECT_EQ(wrapperPattern->lastTouchItem_, wrapperPattern->currentTouchItem_);

    wrapperPattern->currentTouchItem_ = menuItemNode2;
    wrapperPattern->HandleInteraction(info);
    EXPECT_EQ(wrapperPattern->lastTouchItem_, wrapperPattern->currentTouchItem_);
}

/**
 * @tc.name: MenuWrapperPatternTestNg020
 * @tc.desc: Verify HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem and mouseInfo
     * @tc.expected: menuItem and mouseInfo function result as expected
     */
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetGlobalLocation(Offset(200, 200));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 100, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->SetIsSubMenuShowed(false);
    menuItemPattern->AddHoverRegions(OffsetF(0, 0), OffsetF(100, 100));
    const auto& mousePosition = mouseInfo.GetGlobalLocation();
    EXPECT_TRUE(!menuItemPattern->IsInHoverRegions(mousePosition.GetX(), mousePosition.GetY()));
    EXPECT_FALSE(menuItemPattern->IsSubMenuShowed());
    /**
     * @tc.steps: step2. Create menuWrapper
     * @tc.expected: wrapperPattern is not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    wrapperPattern->HandleMouseEvent(mouseInfo, menuItemPattern);
    ASSERT_NE(wrapperPattern, nullptr);
    /**
     * @tc.steps: step3. add submenu to wrapper
     * @tc.expected: wrapper child size is 2
     */
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto currentMenuItemNode =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 101, AceType::MakeRefPtr<MenuItemPattern>());
    auto currentMenuItemPattern = currentMenuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(currentMenuItemPattern, nullptr);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    currentMenuItemPattern->SetIsSubMenuShowed(true);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    EXPECT_EQ(wrapperNode->GetChildren().size(), 2);
    /**
     * @tc.steps: step4. execute HandleMouseEvent
     * @tc.expected: menuItemPattern IsSubMenuShowed as expected
     */
    subMenuPattern->SetParentMenuItem(currentMenuItemNode);
    wrapperPattern->HandleMouseEvent(mouseInfo, menuItemPattern);
    EXPECT_TRUE(currentMenuItemPattern->IsSubMenuShowed());
    subMenuPattern->SetParentMenuItem(menuItemNode);
    wrapperPattern->HandleMouseEvent(mouseInfo, menuItemPattern);
    EXPECT_FALSE(menuItemPattern->IsSubMenuShowed());
}

/**
 * @tc.name: MenuWrapperPatternTestNg021
 * @tc.desc: Verify OnTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg021, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->SetMenuStatus(MenuStatus::ON_HIDE_ANIMATION);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::UP);
    info.changedTouches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->currentTouchItem_, 1);
}

/**
 * @tc.name: MenuWrapperPatternTestNg022
 * @tc.desc: Verify OnTouchEvent when TouchType is up.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg022, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::DOWN);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->menuStatus_ = MenuStatus::ON_HIDE_ANIMATION;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->IsHide(), true);
}

/**
 * @tc.name: MenuWrapperPatternTestNg023
 * @tc.desc: Verify OnTouchEvent when TouchType is up.
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg023, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->IsHide(), false);
}

/**
 * @tc.name: MenuWrapperPatternTestNg024
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg024, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = nullptr;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->IsHide(), false);
}

/**
 * @tc.name: MenuWrapperPatternTestNg025
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg025, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::DOWN);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->IsHide(), false);
}

/**
 * @tc.name: MenuWrapperPatternTestNg026
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg026, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::MOVE);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->IsHide(), false);
}

/**
 * @tc.name: MenuWrapperPatternTestNg027
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg027, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->GetPattern<MenuPattern>()->SetPreviewMode(MenuPreviewMode::CUSTOM);
    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::MOVE);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);
}

/**
 * @tc.name: MenuWrapperPatternTestNg028
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg028, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);

    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);

    menu->GetPattern<MenuPattern>()->type_ = MenuType::SELECT_OVERLAY_CUSTOM_MENU;
    menu->MountToParent(wrapperNode);

    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(menu);

    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(TouchType::MOVE);
    info.touches_.emplace_back(locationInfo);

    wrapperPattern->currentTouchItem_ = menuItemNode;
    wrapperPattern->OnTouchEvent(info);
    EXPECT_EQ(wrapperPattern->GetPreviewMode(), MenuPreviewMode::NONE);
}

/**
 * @tc.name: MenuWrapperPatternTestNg029
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg029, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->isFirstShow_ = true;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
}

/**
 * @tc.name: MenuWrapperPatternTestNg030
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg030, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
}

/**
 * @tc.name: MenuWrapperPatternTestNg031
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg031, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
}

/**
 * @tc.name: MenuWrapperPatternTestNg032
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg032, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    wrapperPattern->isShowInSubWindow_ = false;
    wrapperPattern->isFirstShow_ = false;
    EXPECT_FALSE(wrapperPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
}

/**
 * @tc.name: MenuWrapperPatternTestNg033
 * @tc.desc: test SetHotAreas
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg033, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    wrapperPattern->SetHotAreas(layoutWrapper);
    EXPECT_TRUE(wrapperPattern->isShowInSubWindow_);
}

/**
 * @tc.name: MenuWrapperPatternTestNg034
 * @tc.desc: test SetHotAreas
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg034, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    wrapperPattern->isShowInSubWindow_ = false;
    wrapperPattern->SetHotAreas(layoutWrapper);
    EXPECT_FALSE(wrapperPattern->isShowInSubWindow_);
}

/**
 * @tc.name: MenuWrapperPatternTestNg035
 * @tc.desc: test SetHotAreas
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg035, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    menuPattern->previewMode_ = MenuPreviewMode::CUSTOM;
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    wrapperPattern->filterColumnNode_ = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    wrapperPattern->SetHotAreas(layoutWrapper);
    EXPECT_TRUE(wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM);
}

/**
 * @tc.name: MenuWrapperPatternTestNg036
 * @tc.desc: test SetHotAreas
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg036, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto* layoutWrapperNode = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    RefPtr<LayoutWrapper> layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, nullptr);

    MenuModelNG model;
    model.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    menuPattern->isSelectMenu_ = true;
    menuPattern->SetType(MenuType::CONTEXT_MENU);
    menuPattern->previewMode_ = MenuPreviewMode::CUSTOM;
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    menuItem->MountToParent(wrapperNode);
    auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
    itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto firstChildLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);

    layoutWrapperNode->AppendChild(firstChildLayoutWrapper);
    layoutWrapper = layoutWrapperNode->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(layoutWrapper, firstChildLayoutWrapper);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->menuStatus_ = MenuStatus::HIDE;
    wrapperPattern->SetHotAreas(layoutWrapper);
    EXPECT_TRUE(wrapperPattern->GetPreviewMode() == MenuPreviewMode::CUSTOM);
}

/**
 * @tc.name: MenuWrapperPatternTestNg037
 * @tc.desc: test IsMenuPreviewNode with previewMode.Custom
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuWrapper with customPreview
     * @tc.expected: menuWrapperNode is not null
     */
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapPattern, nullptr);

    /**
     * @tc.steps: step2. call IsMenuPreviewNode
     * @tc.expected: menu node is false, preview node is true
     */
    auto menu = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menu, nullptr);
    EXPECT_FALSE(menuWrapPattern->IsMenuPreviewNode(menu));

    auto preview = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    ASSERT_NE(preview, nullptr);
    EXPECT_TRUE(menuWrapPattern->IsMenuPreviewNode(preview));
}

/**
 * @tc.name: MenuWrapperPatternTestNg038
 * @tc.desc: test IsMenuPreviewNode with previewMode.Image
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuWrapper、menu、image
     * @tc.expected: node is not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto menuWrapPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapPattern, nullptr);

    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetPreviewMode(MenuPreviewMode::IMAGE);
    menuNode->MountToParent(wrapperNode);

    auto imageNode =
        FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, -1, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    imageNode->MountToParent(wrapperNode);

    /**
     * @tc.steps: step2. call IsMenuPreviewNode
     * @tc.expected: menu node is false, preview node is true
     */
    auto menu = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menu, nullptr);
    EXPECT_FALSE(menuWrapPattern->IsMenuPreviewNode(menu));

    auto preview = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(1));
    ASSERT_NE(preview, nullptr);
    EXPECT_TRUE(menuWrapPattern->IsMenuPreviewNode(preview));
}

/**
 * @tc.name: MenuWrapperPatternTestNg039
 * @tc.desc: test IsMenuPreviewNode without preview
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuWrapper、menu
     * @tc.expected: node is not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    mainMenu->MountToParent(wrapperNode);

    auto imageNode =
        FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, -1, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    imageNode->MountToParent(wrapperNode);

    /**
     * @tc.steps: step2. call IsMenuPreviewNode
     * @tc.expected: menu node is false, imageNode node is false
     */
    auto menuWrapPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapPattern, nullptr);
    EXPECT_FALSE(menuWrapPattern->IsMenuPreviewNode(mainMenu));
    EXPECT_FALSE(menuWrapPattern->IsMenuPreviewNode(imageNode));
}

/**
 * @tc.name: MenuWrapperPatternTestNg040
 * @tc.desc: test SetAnimationBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPatternTestNg040, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuWrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    menuWrapperPattern->SetAnimationBorderRadius(BORDER_RADIUS_RATE, BORDER_RADIUS_PROPERTY);
    auto animationInfo_ = menuWrapperPattern->GetPreviewMenuAnimationInfo();
    EXPECT_TRUE(animationInfo_.borderRadius.radiusTopLeft.has_value());
    EXPECT_EQ(animationInfo_.borderRadius.radiusTopLeft->Value(), BORDER_RADIUS.Value() * BORDER_RADIUS_RATE);
    EXPECT_TRUE(animationInfo_.borderRadius.radiusTopRight.has_value());
    EXPECT_EQ(animationInfo_.borderRadius.radiusTopRight->Value(), BORDER_RADIUS.Value() * BORDER_RADIUS_RATE);
    EXPECT_TRUE(animationInfo_.borderRadius.radiusBottomLeft.has_value());
    EXPECT_EQ(animationInfo_.borderRadius.radiusBottomLeft->Value(), BORDER_RADIUS.Value() * BORDER_RADIUS_RATE);
    EXPECT_TRUE(animationInfo_.borderRadius.radiusBottomRight.has_value());
    EXPECT_EQ(animationInfo_.borderRadius.radiusBottomRight->Value(), BORDER_RADIUS.Value() * BORDER_RADIUS_RATE);
}

/**
 * @tc.name: MenuWrapperPaintMethodTestNg001
 * @tc.desc: test overlay draw function
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPaintMethodTestNg001, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    auto paintMethod = wrapperPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    auto paintProperty = wrapperPattern->GetPaintProperty<MenuWrapperPaintProperty>();
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(wrapperNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    auto function = paintMethod->GetOverlayDrawFunction(paintWrapper);
    RSCanvas canvas;
    function(canvas);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    function(canvas);
    auto context = PipelineContext::GetCurrentContext();
    wrapperNode->context_ = AceType::RawPtr(context);
    auto pipline = wrapperNode->GetContext();
    ASSERT_NE(pipline, nullptr);
    auto menuTheme = pipline->GetTheme<MenuTheme>();
    ASSERT_NE(menuTheme, nullptr);
    menuTheme->doubleBorderEnable_ = true;
    function(canvas);
    EXPECT_NE(wrapperPattern->GetMenuStatus(), MenuStatus::SHOW);
}

/**
 * @tc.name: MenuWrapperPaintMethodTestNg002
 * @tc.desc: test PaintDoubleBorder
 * @tc.type: FUNC
 */
HWTEST_F(MenuWrapperTestNg, MenuWrapperPaintMethodTestNg002, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    auto paintMethod = AceType::DynamicCast<MenuWrapperPaintMethod>(wrapperPattern->CreateNodePaintMethod());
    ASSERT_NE(paintMethod, nullptr);
    auto paintProperty = wrapperPattern->GetPaintProperty<MenuWrapperPaintProperty>();
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(wrapperNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    Testing::MockCanvas canvas;
    wrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    paintMethod->PaintDoubleBorder(canvas, paintWrapper);
    auto menuNode = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MENU); });
    menuNode->MountToParent(wrapperNode);
    auto imageNode =
        FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, -1, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNode->MountToParent(wrapperNode);
    wrapperNode->children_.push_back(nullptr);
    paintMethod->PaintDoubleBorder(canvas, paintWrapper);
    MenuPathParams params;
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->UpdateMenuPathParams(params);
    EXPECT_CALL(canvas, ClipPath(_, _, _)).Times(AtLeast(6));
    EXPECT_CALL(canvas, Save()).Times(AtLeast(6));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawPath(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));

    paintMethod->PaintDoubleBorder(canvas, paintWrapper);
    params.didNeedArrow = true;
    menuPattern->UpdateMenuPathParams(params);
    paintMethod->PaintDoubleBorder(canvas, paintWrapper);
    const std::list<Placement> placements = { Placement::LEFT, Placement::TOP, Placement::RIGHT, Placement::BOTTOM };
    for (const auto& placement : placements) {
        params.arrowPlacement = placement;
        menuPattern->UpdateMenuPathParams(params);
        paintMethod->PaintDoubleBorder(canvas, paintWrapper);
    }
}
} // namespace OHOS::Ace::NG
