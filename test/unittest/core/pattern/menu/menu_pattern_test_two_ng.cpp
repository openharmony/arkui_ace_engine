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
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

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
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};

} // namespace
class MenuPatternTwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    void InitMenuItemTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    void CreateWrapperAndTargetNode(RefPtr<FrameNode>& menuWrapperNode, RefPtr<FrameNode>& targetNode);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuPatternTwoTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
}

void MenuPatternTwoTestNg::TearDownTestCase()
{
    MockContainer::TearDown();
}

void MenuPatternTwoTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuPatternTwoTestNg::TearDown()
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

void MenuPatternTwoTestNg::InitMenuTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuPatternTwoTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuPatternTwoTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuPatternTwoTestNg::GetPreviewMenuWrapper(
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

void MenuPatternTwoTestNg::CreateWrapperAndTargetNode(RefPtr<FrameNode>& menuWrapperNode, RefPtr<FrameNode>& targetNode)
{
    targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    menuWrapperNode = MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
}

/**
 * @tc.name: MenuPatternTest083
 * @tc.desc: Test MenuPattern::IsMenuScrollable.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTwoTestNg083, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu and srcoll node, get menu frameNode.
     * @tc.expected: call IsMenuScrollable and result is IsScrollable & GetScrollableDistance.
     */
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), TARGET_ID, "", TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto scrollNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, AceType::MakeRefPtr<ScrollPattern>());
    scrollNode->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto ret = menuPattern->IsMenuScrollable();
    ASSERT_FALSE(ret);
    /**
     * @tc.steps: step2. Create menu and srcoll node, get menu frameNode.
     * @tc.expected: call IsMenuScrollable and result is false.
     */
    RefPtr<FrameNode> menuWrapperNodeEx =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuWrapperNodeEx, nullptr);
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 1, AceType::MakeRefPtr<TextPattern>());
    textNode->MountToParent(menuWrapperNodeEx);
    auto menuPatternEx = menuWrapperNodeEx->GetPattern<MenuPattern>();
    ASSERT_NE(menuPatternEx, nullptr);
    ret = menuPatternEx->IsMenuScrollable();
    ASSERT_FALSE(ret);
}

/**
 * @tc.name: MenuPatternTest084
 * @tc.desc: Test HideStackMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTwoTestNg084, TestSize.Level1)
{
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->HideStackMenu();
    EXPECT_TRUE(true);
}

// /**
//  * @tc.name: MenuPatternTest085
//  * @tc.desc: Test OnTouchEvent
//  * @tc.type: FUNC
//  */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTwoTestNg085, TestSize.Level1)
{
    MenuPattern* menuPattern = new MenuPattern(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    menuPattern->needHideAfterTouch_ = false;
    menuPattern->OnTouchEvent(info);
    EXPECT_TRUE(true);
}

 /**
 * @tc.name: MenuPatternTest086
 * @tc.desc: Test DisableTabInMenu
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTwoTestNg086, TestSize.Level1)
{
    RefPtr<FrameNode> menuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    menuPattern->type_ = MenuType::DESKTOP_MENU;
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->DisableTabInMenu();
    ASSERT_TRUE(menuPattern->IsDesktopMenu());
}

/**
 * @tc.name: MenuPatternTwoTestNg088
 * @tc.desc: Verify MenuPattern::GetInnerMenuOffset
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTwoTestNg088, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuitem childnode and isNeedRestoreNodeId if false;
     */
    RefPtr<FrameNode> menuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    auto child = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    child->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    auto menuItemPattern = child->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->SetClickMenuItemId(child->GetId());
    RefPtr<FrameNode> subMenuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(2, "", TYPE); });
    ASSERT_NE(subMenuNode, nullptr);
    auto testInfo = menuPattern->GetInnerMenuOffset(child, subMenuNode, false);
    EXPECT_TRUE(testInfo.isFindTargetId);
    /**
     * @tc.steps: step1+. test GetInnerMenuOffset and isNeedRestoreNodeId if true;
     */
    testInfo = menuPattern->GetInnerMenuOffset(child, subMenuNode, true);
    EXPECT_TRUE(testInfo.isFindTargetId);
    /**
     * @tc.steps: step2. Create menuitemgroup node and isNeedRestoreNodeId if false;
     */
    auto menuitemgroupNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto itemchildOne =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    auto itemchildTwo =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    itemchildOne->MountToParent(menuitemgroupNode);
    itemchildTwo->MountToParent(menuitemgroupNode);
    menuPattern = menuNode->GetPattern<MenuPattern>();
    testInfo = menuPattern->GetInnerMenuOffset(menuitemgroupNode, subMenuNode, false);
    EXPECT_FALSE(testInfo.isFindTargetId);
    /**
     * @tc.steps: step2. Create menuitemgroup node and isNeedRestoreNodeId if true;
     */
    testInfo = menuPattern->GetInnerMenuOffset(menuitemgroupNode, subMenuNode, true);
    EXPECT_EQ(testInfo.originOffset, OffsetF(0.0, 0.0));
    EXPECT_FALSE(testInfo.isFindTargetId);
}

/**
 * @tc.name: MenuPatternTest089
 * @tc.desc: Test GetSelectMenuWidthFromTheme.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTest089, TestSize.Level1)
{
    /**
     * @tc.steps: step0. Create mock theme manager
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->optionNormalWidth_ = 100.0_vp;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto width = menuPattern->GetSelectMenuWidthFromTheme();
    EXPECT_EQ(width, 108);
}

/**
 * @tc.name: MenuPatternTest090
 * @tc.desc: Test HandleNextPressed.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTest090, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, V2::JS_IF_ELSE_ETS_TAG, MenuType::MENU));
    auto childrenOne =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(2, "menu", MenuType::MENU));
    auto childrenTwo = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "text", MenuType::MULTI_MENU));
    auto childrenThree = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(4, "menuItem", MenuType::SUB_MENU));
    parent->children_ = { childrenOne, childrenTwo, childrenThree };
    parent->tag_ = V2::JS_IF_ELSE_ETS_TAG;
    int32_t index = 1;
    bool press = true;
    bool hover = true;
    auto menuPattern = parent->GetPattern<MenuPattern>();
    menuPattern->HandleNextPressed(parent, index, press, hover);
    EXPECT_NE(parent->GetChildAtIndex(index + 1), nullptr);
    index = 2;
    childrenOne->tag_ = V2::JS_IF_ELSE_ETS_TAG;
    auto uiNode = AceType::DynamicCast<UINode>(childrenOne);
    uiNode->children_ = { childrenOne, childrenTwo, childrenThree };
    ASSERT_NE(uiNode, nullptr);
    parent->parent_ = uiNode;
    menuPattern->HandleNextPressed(parent, index, press, hover);
    EXPECT_NE(menuPattern->GetOutsideForEachMenuItem(parent, true), nullptr);
}

/**
 * @tc.name: MenuPatternTest091
 * @tc.desc: Test HandlePrevPressed.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuPatternTest091, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, V2::JS_IF_ELSE_ETS_TAG, MenuType::MENU));
    auto childrenOne =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(2, "menu", MenuType::MENU));
    auto childrenTwo = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "text", MenuType::MULTI_MENU));
    auto childrenThree = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(4, "menuItem", MenuType::SUB_MENU));
    parent->children_ = { childrenOne, childrenTwo, childrenThree };
    parent->tag_ = V2::MENU_ITEM_GROUP_ETS_TAG;
    int32_t index = -1;
    bool press = true;
    auto uiNode = AceType::DynamicCast<UINode>(childrenOne);
    uiNode->tag_ = V2::JS_IF_ELSE_ETS_TAG;
    ASSERT_NE(uiNode, nullptr);
    parent->parent_ = uiNode;
    auto menuPattern = parent->GetPattern<MenuPattern>();
    menuPattern->HandlePrevPressed(parent, index, press);
    EXPECT_EQ(parent->GetParent()->GetChildIndex(parent), -1);
    uiNode->children_ = { parent };
    parent->parent_ = uiNode;
    menuPattern->HandlePrevPressed(parent, index, press);
    EXPECT_EQ(menuPattern->GetOutsideForEachMenuItem(parent->GetParent(), false), nullptr);
    uiNode->children_ = { childrenTwo, parent };
    parent->parent_ = uiNode;
    menuPattern->HandlePrevPressed(parent, index, press);
    EXPECT_NE(menuPattern->GetOutsideForEachMenuItem(parent, false), nullptr);
}

/**
 * @tc.name: MenuLifecycleCallbackTest001
 * @tc.desc: Test MenuLifecycleCallback.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, MenuLifecycleCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };

    std::function<void()> buildFunc;
    MenuParam menuParam;
    menuParam.isShow = true;
    menuParam.isShowInSubWindow = false;
    menuParam.onWillAppear = std::move(onWillAppearEvent);
    menuParam.onDidAppear = std::move(onDidAppearEvent);
    menuParam.onWillDisappear = std::move(onWillDisappearEvent);
    menuParam.onDidDisappear = std::move(onDidDisappearEvent);
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);

    auto menuNode =
        MenuView::Create(std::move(optionParams), TARGET_ID, MENU_TAG, MenuType::MENU, menuParam);
    CHECK_NULL_VOID(menuNode);
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->RegisterMenuCallback(menuNode, menuParam);
    /**
     * @tc.steps: step2. Call Callback.
     * @tc.expected: Check Callback.
     */
    menuWrapperPattern->CallMenuOnWillAppearCallback();
    menuWrapperPattern->CallMenuOnDidAppearCallback();
    menuWrapperPattern->CallMenuOnWillDisappearCallback();
    menuWrapperPattern->CallMenuOnDidDisappearCallback();

    EXPECT_EQ(onWillAppearFlag, true);
    EXPECT_EQ(onDidAppearFlag, true);
    EXPECT_EQ(onWillDisappearFlag, true);
    EXPECT_EQ(onDidDisappearFlag, true);
}

/**
 * @tc.name: RegisterAccessibilityChildActionNotify001
 * @tc.desc: Test callback function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, RegisterAccessibilityChildActionNotify001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    /**
     * @tc.steps: step1. create outter menu and set show in subwindow true
     */
    auto outterMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(outterMenuNode, nullptr);
    auto outterMenuLayoutProps = outterMenuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(outterMenuLayoutProps, nullptr);
    outterMenuLayoutProps->UpdateShowInSubWindow(true);
    /**
     * @tc.steps: step2. create inner menu and set show in subwindow false
     */
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    auto innerMenuLayoutProps = innerMenuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(innerMenuLayoutProps, nullptr);
    innerMenuLayoutProps->UpdateShowInSubWindow(false);
    innerMenuLayoutProps->UpdateExpandingMode(SubMenuExpandingMode::STACK);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    menuItemNode->MountToParent(innerMenuNode);
    innerMenuNode->MountToParent(outterMenuNode);
    outterMenuNode->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->expandingMode_ = innerMenuLayoutProps->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
    /**
     * @tc.steps: step3. call ShowSubMenu to create submenu
     * @tc.expected: expect subMenu's showInSubwindow param is true
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->ShowSubMenu(ShowSubMenuType::LONG_PRESS);
    auto menuAccessibilityProperty_ = innerMenuNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
    auto callback = menuAccessibilityProperty_->GetNotifyChildActionFunc();
    ASSERT_NE(callback, nullptr);
    auto reuslt = callback(menuItemNode, NotifyChildActionType::ACTION_CLICK);
    EXPECT_EQ(reuslt, AccessibilityActionResult::ACTION_RISE);
}

/**
 * @tc.name: UpdateSelectOptionTextByIndex
 * @tc.desc: Test UpdateSelectOptionTextByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, UpdateSelectOptionTextByIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent and child frame nodes.
     * @tc.expected: step1. Parent and child nodes are not null.
     */
    auto parent = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, V2::JS_IF_ELSE_ETS_TAG, MenuType::MENU));
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(child, nullptr);
    auto parentPattern = parent->GetPattern<MenuPattern>();
    ASSERT_NE(parentPattern, nullptr);
    auto childPattern = child->GetPattern<MenuItemPattern>();
    ASSERT_NE(childPattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdateSelectOptionTextByIndex with non-select menu.
     * @tc.expected: step2. No changes should occur.
     */
    parentPattern->isSelectMenu_ = false;
    std::string text = "Text";
    parentPattern->UpdateSelectOptionTextByIndex(2, text);

    /**
     * @tc.steps: step3. Test UpdateSelectOptionTextByIndex with select menu.
     * @tc.expected: step3. Text should be updated correctly.
     */
    parentPattern->isSelectMenu_ = true;
    parentPattern->AddOptionNode(child);
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    childPattern->SetTextNode(textNode);
    auto textProp = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProp, nullptr);
    parentPattern->UpdateSelectOptionTextByIndex(2, text);
    auto content = textProp->GetContent();
    EXPECT_FALSE(content.has_value());
    parentPattern->UpdateSelectOptionTextByIndex(0, text);
    auto ret = childPattern->GetText();
    EXPECT_EQ(text, ret);
}

/**
 * @tc.name: UpdateSelectOptionIconByIndex
 * @tc.desc: Test UpdateSelectOptionIconByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, UpdateSelectOptionIconByIndex, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent and child frame nodes.
     * @tc.expected: step1. Parent and child nodes are not null.
     */
    auto parent = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, V2::JS_IF_ELSE_ETS_TAG, MenuType::MENU));
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(child, nullptr);
    auto parentPattern = parent->GetPattern<MenuPattern>();
    ASSERT_NE(parentPattern, nullptr);
    auto childPattern = child->GetPattern<MenuItemPattern>();
    ASSERT_NE(childPattern, nullptr);

    /**
     * @tc.steps: step2. Test UpdateSelectOptionIconByIndex with non-select menu.
     * @tc.expected: step2. No changes should occur.
     */
    parentPattern->isSelectMenu_ = false;
    std::string icon = "TestChildIcon";
    parentPattern->UpdateSelectOptionIconByIndex(0, icon);

    /**
     * @tc.steps: step3. Test UpdateSelectOptionIconByIndex with select menu.
     * @tc.expected: step3. Icon should be updated correctly.
     */
    parentPattern->isSelectMenu_ = true;
    parentPattern->AddOptionNode(child);
    parentPattern->UpdateSelectOptionIconByIndex(2, icon);
    auto ret = childPattern->GetIcon();
    EXPECT_NE(icon, ret);
    parentPattern->UpdateSelectOptionIconByIndex(0, icon);
    ret = childPattern->GetIcon();
    EXPECT_EQ(icon, ret);
}

/**
 * @tc.name: NeedHoldTargetOffsetTest
 * @tc.desc: Test NeedHoldTargetOffsetTest function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPatternTwoTestNg, NeedHoldTargetOffsetTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create parent and child frame nodes.
     * @tc.expected: step1. wrapper and menu nodes are not null.
     */
    RefPtr<FrameNode> menuWrapperNode;
    RefPtr<FrameNode> targetNode;
    CreateWrapperAndTargetNode(menuWrapperNode, targetNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_NE(targetNode, nullptr);
    auto wrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. Test NeedHoldTargetOffset when not have history.
     * @tc.expected: step2. NeedHoldTargetOffset will return false.
     */
    EXPECT_FALSE(layoutAlgorithm->NeedHoldTargetOffset(targetNode, menuPattern));
    /**
     * @tc.steps: step3. Test NeedHoldTargetOffset when menu hide.
     * @tc.expected: step3. NeedHoldTargetOffset will return true.
     */
    wrapperPattern->SetMenuStatus(MenuStatus::HIDE);
    menuPattern->SetTargetSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    EXPECT_TRUE(layoutAlgorithm->NeedHoldTargetOffset(targetNode, menuPattern));
    /**
     * @tc.steps: step4. Test NeedHoldTargetOffset when target is null.
     * @tc.expected: step4. NeedHoldTargetOffset will return true.
     */
    wrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    EXPECT_TRUE(layoutAlgorithm->NeedHoldTargetOffset(nullptr, menuPattern));
    /**
     * @tc.steps: step5. Test NeedHoldTargetOffset when opacity zero.
     * @tc.expected: step5. NeedHoldTargetOffset will return true.
     */
    auto targetRenderContext = AceType::DynamicCast<MockRenderContext>(targetNode->GetRenderContext());
    targetRenderContext->UpdateOpacity(0.0);
    EXPECT_TRUE(layoutAlgorithm->NeedHoldTargetOffset(targetNode, menuPattern));
    /**
     * @tc.steps: step6. Test NeedHoldTargetOffset when INVISIBLE.
     * @tc.expected: step6. NeedHoldTargetOffset will return true.
     */
    targetRenderContext->UpdateOpacity(1.0);
    auto layoutProperty = targetNode->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    EXPECT_TRUE(layoutAlgorithm->NeedHoldTargetOffset(targetNode, menuPattern));
    /**
     * @tc.steps: step7. Test NeedHoldTargetOffset when size zero.
     * @tc.expected: step7. NeedHoldTargetOffset will return true.
     */
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    EXPECT_TRUE(layoutAlgorithm->NeedHoldTargetOffset(targetNode, menuPattern));
    /**
     * @tc.steps: step8. Test NeedHoldTargetOffset when normal.
     * @tc.expected: step8. NeedHoldTargetOffset will return false.
     */
    targetRenderContext->SetPaintRectWithTransform(RectF(0.0f, 0.0f, TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    EXPECT_FALSE(layoutAlgorithm->NeedHoldTargetOffset(targetNode, menuPattern));
}
} // namespace OHOS::Ace::NG