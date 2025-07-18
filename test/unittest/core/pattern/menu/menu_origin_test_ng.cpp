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

#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "base/memory/ace_type.h"
#include "core/components/button/button_theme.h"
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
#include "core/components_ng/pattern/overlay/dialog_manager.h"
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
constexpr int32_t SELECTED_INDEX = 10;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_ITEM_TEXT = "menuItem";
const std::string MENU_ITEM_GROUP_TEXT = "menuItemGroup";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const DirtySwapConfig configDirtySwap = { false, false, false, false, true, false };
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr double MENU_OFFSET_X = 10.0;
constexpr double MENU_OFFSET_Y = 10.0;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
constexpr float GREATER_WINDOW_MENU_HEIGHT = 1190.0f;
constexpr float CONST_FLOAT_ZREO = 0.0f;

constexpr float OFFSET_THIRD = 200.0f;
constexpr int NODEID = 1;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const Dimension CONTAINER_OUTER_RADIUS = 16.0_vp;
constexpr double DIP_SCALE = 1.5;
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    void InitMenuTestNg();
    void InitMenuItemTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> GetImagePreviewMenuWrapper();
    RefPtr<FrameNode> GetHoverImagePreviewMenuWrapper();
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuTestNg::SetUpTestCase() {}

void MenuTestNg::TearDownTestCase() {}

void MenuTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuTestNg::TearDown()
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
    MockContainer::TearDown();
}

void MenuTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else {
            return AceType::MakeRefPtr<MenuTheme>();
        }
    });
}

void MenuTestNg::InitMenuTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuTestNg::GetPreviewMenuWrapper(
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

RefPtr<FrameNode> MenuTestNg::GetImagePreviewMenuWrapper()
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto targetGestureHub = targetNode->GetOrCreateGestureEventHub();
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    targetGestureHub->SetPixelMap(pixelMap);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto itemGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometryNode, nullptr);
    itemGeometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));

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

RefPtr<FrameNode> MenuTestNg::GetHoverImagePreviewMenuWrapper()
{
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto targetGestureHub = targetNode->GetOrCreateGestureEventHub();
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();
    targetGestureHub->SetPixelMap(pixelMap);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto itemGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(itemGeometryNode, nullptr);
    itemGeometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));

    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(customNode, nullptr);
    auto customGeometryNode = customNode->GetGeometryNode();
    CHECK_NULL_RETURN(customGeometryNode, nullptr);
    customGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));

    targetNode->MountToParent(rootNode);
    targetNode->GetOrCreateGestureEventHub();

    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    menuParam.isShowHoverImage = true;
    menuParam.hoverImageAnimationOptions = { 1.0f, 0.95f };

    auto menuWrapperNode =
        MenuView::Create(textNode, targetNode->GetId(), V2::TEXT_ETS_TAG, menuParam, true, customNode);
    return menuWrapperNode;
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: MenuItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu, get menu frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuItemEventHub = frameNode->GetOrCreateEventHub<MenuItemEventHub>();
    ASSERT_NE(menuItemEventHub, nullptr);
    auto menuItemAccessibilityProperty = frameNode->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty, nullptr);
    menuItemPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. When selectedChangeEvent onChange and subBuilder is null, call the callback function in
     *                   menuItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(menuItemAccessibilityProperty->ActActionSelect());

    /**
     * @tc.steps: step3. When selectedChangeEvent onChange and subBuilder is not null, call the callback function in
     *                   menuItemAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    bool isSelected = false;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    menuItemEventHub->SetSelectedChangeEvent(changeEvent);
    menuItemEventHub->SetOnChange(changeEvent);
    auto subBuilder = []() {};
    menuItemPattern->SetSubBuilder(subBuilder);
    EXPECT_TRUE(menuItemAccessibilityProperty->ActActionSelect());
}

/**
 * @tc.name: PerformActionTest003
 * @tc.desc: MenuItem Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, PerformActionTest003, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuItemAccessibilityProperty = frameNode->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty, nullptr);
    bool isSelected = true;
    menuItemPattern->isSelected_ = false;
    menuItemPattern->MarkIsSelected(isSelected);
    EXPECT_TRUE(menuItemAccessibilityProperty->ActActionSelect());
}

/**
 * @tc.name: MenuAccessibilityEventTestNg001
 * @tc.desc: Test Click Event for Option of Menu.
 */
HWTEST_F(MenuTestNg, MenuAccessibilityEventTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Option for Menu.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() {return AceType::MakeRefPtr<MenuItemPattern>(true, 0);});
    ASSERT_NE(frameNode, nullptr);
    auto optionPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(optionPattern, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    int testIndex = SELECTED_INDEX;
    auto selectFunc = [optionPattern, testIndex](int index) { optionPattern->index_ = testIndex; };
    auto optionEventHub = frameNode->GetOrCreateEventHub<MenuItemEventHub>();
    optionEventHub->SetOnSelect(selectFunc);
    optionPattern->RegisterOnClick();

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: index_ is SELECTED_INDEX.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    auto clickEventActuator = gestureHub->clickEventActuator_;
    ASSERT_NE(clickEventActuator, nullptr);
    auto event = clickEventActuator->GetClickEvent();
    ASSERT_NE(event, nullptr);
    GestureEvent gestureEvent;
    event(gestureEvent);
    EXPECT_EQ(optionPattern->index_, SELECTED_INDEX);
}

/**
 * @tc.name: DesktopMenuPattern001
 * @tc.desc: Test MenuPattern onModifyDone, switch between DesktopMenu and regular menu.
 */
HWTEST_F(MenuTestNg, DesktopMenuPattern001, TestSize.Level1)
{
    MenuModelNG model;
    model.Create();
    auto menu1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu1, nullptr);
    model.Create();
    auto menu2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto container = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU));
    auto mockScroll = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    mockScroll->MountToParent(container);
    menu1->MountToParent(mockScroll);
    menu2->MountToParent(mockScroll);

    auto pattern1 = menu1->GetPattern<InnerMenuPattern>();
    auto pattern2 = menu2->GetPattern<InnerMenuPattern>();
    auto containerPattern = container->GetPattern<MenuPattern>();
    containerPattern->OnModifyDone();
    pattern1->OnModifyDone();
    pattern2->OnModifyDone();
    pattern1->BeforeCreateLayoutWrapper();
    pattern2->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern1->type_, MenuType::DESKTOP_MENU);
    EXPECT_EQ(pattern2->type_, MenuType::DESKTOP_MENU);
    EXPECT_EQ(container->GetRenderContext()->GetBackShadow(), ShadowConfig::NoneShadow);

    mockScroll->RemoveChildAtIndex(1);
    pattern1->OnModifyDone();
    pattern1->BeforeCreateLayoutWrapper();
    containerPattern->OnModifyDone();
    EXPECT_EQ(pattern1->type_, MenuType::MULTI_MENU);
    Shadow shadow;
    pattern1->GetShadowFromTheme(ShadowStyle::OuterDefaultMD, shadow);
    EXPECT_EQ(container->GetRenderContext()->GetBackShadow(), shadow);
}

/**
 * @tc.name: MenuViewTestNgCreate001
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNgCreate001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), TARGET_ID, "", TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 2);

    auto firstOption = menuPattern->GetOptions()[0];
    ASSERT_NE(firstOption, nullptr);
    EXPECT_EQ(firstOption->GetTag(), V2::OPTION_ETS_TAG);
    auto firstPattern = firstOption->GetPattern<MenuItemPattern>();
    ASSERT_NE(firstPattern, nullptr);
    EXPECT_EQ(firstPattern->GetText(), "MenuItem1");
    EXPECT_EQ(firstPattern->GetIcon(), "fakeIcon");
    auto secondOption = menuPattern->GetOptions()[1];
    ASSERT_NE(secondOption, nullptr);
    EXPECT_EQ(secondOption->GetTag(), V2::OPTION_ETS_TAG);
    auto secondPattern = secondOption->GetPattern<MenuItemPattern>();
    ASSERT_NE(secondPattern, nullptr);
    EXPECT_EQ(secondPattern->GetText(), "MenuItem2");
    EXPECT_EQ(secondPattern->GetIcon(), "");
}

/**
 * @tc.name: MenuViewTestNgCreate002
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNgCreate002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.title = "Title";
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), TARGET_ID, "", TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->OnModifyDone();
    auto column = menuPattern->GetMenuColumn();
    ASSERT_NE(column, nullptr);
    auto children = column->GetChildren();
    ASSERT_EQ(children.size(), 3);
    auto titleChild = AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(0));
    ASSERT_NE(titleChild, nullptr);
    EXPECT_EQ(titleChild->GetTag(), V2::TEXT_ETS_TAG);
    auto textProperty = titleChild->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    EXPECT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), u"Title");
}

/**
 * @tc.name: MenuViewTestNgCreate003
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNgCreate003, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.positionOffset = { 10.0f, 10.0f };
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: MenuViewTestNgCreate004
 * @tc.desc: Verify Create SubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNgCreate004, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create custom node and menu node
     * @tc.expected: menuNode not null
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.positionOffset = { 10.0f, 10.0f };
    menuParam.type = MenuType::SUB_MENU;
    auto menuNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_NE(menuNode, nullptr);
    /**
     * @tc.steps: step2: get menuNode layoutProperty
     * @tc.expected: layoutProperty as expected
     */
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    EXPECT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: MenuViewTestNgCreate005
 * @tc.desc: Verify Create SubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNgCreate005, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create custom node and menuWrapper node
     * @tc.expected: menuWrapperNode not null
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    MenuParam menuParam;
    menuParam.enableHoverMode = true;
    RefPtr<NG::UINode> customNode;
    auto menuWrapperNode =
        MenuView::Create(textNode, TARGET_ID, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    /**
     * @tc.steps: step2: create custom menu node
     * @tc.expected: menuNode not null,menuWrapperNode->GetChildren() size is 1
     */
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    /**
     * @tc.steps: step3: create custom menu pattern
     * @tc.expected: enableFold is ture
     */
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    ASSERT_EQ(menuWrapperPattern->enableFold_, true);
    ASSERT_EQ(menuWrapperPattern->GetHoverMode(), true);

    /**
     * @tc.steps: step4: menu pattern SetFold
     * @tc.expected: enableFold is fasle/ture
     */
    menuWrapperPattern->SetHoverMode(true);
    ASSERT_EQ(menuWrapperPattern->enableFold_, true);
    menuWrapperPattern->SetHoverMode(false);
    ASSERT_EQ(menuWrapperPattern->enableFold_, false);
}

/**
 * @tc.name: MenuPaintMethodTestNg001
 * @tc.desc: Verify MenuPaintMethod::GetContentDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuPaintProperty> paintProp = AceType::MakeRefPtr<MenuPaintProperty>();
    RefPtr<MenuPaintMethod> paintMethod = AceType::MakeRefPtr<MenuPaintMethod>();
    PaintWrapper* paintWrapperNoMenu = GetPaintWrapper(paintProp);
    paintMethod->GetContentDrawFunction(paintWrapperNoMenu);
    delete paintWrapperNoMenu;
    paintWrapperNoMenu = nullptr;
    Testing::MockCanvas canvas;
    /**
     * @tc.steps: step2. update paint property and excute GetContentDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    paintProp->UpdateEnableArrow(true);
    paintProp->UpdateArrowPosition(OffsetF(10.0f, 10.0f));
    Placement placements[] = { Placement::TOP, Placement::BOTTOM, Placement::RIGHT, Placement::LEFT };
    for (Placement placementValue : placements) {
        paintProp->UpdateArrowPlacement(placementValue);
        PaintWrapper* paintWrapper = GetPaintWrapper(paintProp);
        auto result = paintMethod->GetContentDrawFunction(paintWrapper);
        EXPECT_NE(result, nullptr);
        result(canvas);
        delete paintWrapper;
        paintWrapper = nullptr;
    }
    /**
     * @tc.steps: step3. update enableArrow to false.
     * @tc.expected:  return value are as expected.
     */
    paintProp->UpdateEnableArrow(false);
    PaintWrapper* paintWrapper = GetPaintWrapper(paintProp);
    auto result = paintMethod->GetContentDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test on color configuration update.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(menuTheme);
    menuTheme->backgroundColor_ = Color::BLACK;
    menuPattern->OnColorConfigurationUpdate();
    auto renderContext = menuNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor(), Color::BLACK);
}

/**
 * @tc.name: MenuPreviewPatternTestNg0100
 * @tc.desc: Test MenuPreviewPattern functions.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuPreviewPatternTestNg0100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create preview node, then set the initial properties
     * @tc.expected: preview node, preview pattern are not null
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    menuTheme->previewBorderRadius_ = CONTAINER_OUTER_RADIUS;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    ASSERT_NE(previewNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapperNode, nullptr);
    previewNode->MountToParent(menuWrapperNode);
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(previewPattern, nullptr);
    const RefPtr<LayoutWrapperNode> layoutWrapper;
    previewPattern->isFirstShow_ = true;

    /**
     * @tc.steps: step2. call OnModifyDone and OnDirtyLayoutWrapperSwap
     * @tc.expected: borderRadius is CONTAINER_OUTER_RADIUS, isFirstShow_ is false and panEvent is not empty
     */
    previewPattern->OnModifyDone();
    previewPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap);
    auto renderContext = previewNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(CONTAINER_OUTER_RADIUS);
    EXPECT_EQ(renderContext->GetBorderRadius().value(), borderRadius);
    EXPECT_FALSE(previewPattern->isFirstShow_);
    auto gestureHub = previewNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    GestureEvent info;
    info.offsetY_ = 1.0;

    /**
     * @tc.steps: step3. call pan task
     * @tc.expected: menuWrapperPattern's IsHide() is false
     */
    EXPECT_FALSE(menuWrapperPattern->IsHide());

    /**
     * @tc.steps: step4. call SetFirstShow
     * @tc.expected: isFirstShow_ is true.
     */
    previewPattern->SetFirstShow();
    EXPECT_TRUE(previewPattern->isFirstShow_);
}

/**
 * @tc.name: MenuPatternTestNg0100
 * @tc.desc: Test MenuPattern functions.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuPatternTestNg0100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node, then set the initial properties
     * @tc.expected: menu node, menu pattern are not null
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE));
    ASSERT_NE(menuNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapperNode, nullptr);
    menuNode->MountToParent(menuWrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    const RefPtr<LayoutWrapperNode> layoutWrapper;
    menuPattern->isMenuShow_ = true;

    /**
     * @tc.steps: step2. call OnModifyDone and OnDirtyLayoutWrapperSwap
     * @tc.expected: sMenuShow_ is false and panEvent is not empty
     */
    menuPattern->OnModifyDone();
    menuPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap);
    EXPECT_FALSE(menuPattern->isMenuShow_);

    /**
     * @tc.steps: step3. call SetMenuShow
     * @tc.expected: isMenuShow_ is true.
     */
    menuPattern->SetMenuShow();
    EXPECT_TRUE(menuPattern->isMenuShow_);
}

/**
 * @tc.name: WidthModifiedBySelectTestNg001
 * @tc.desc: Verify the usability of the select modified flag.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get menu pattern and set the flag.
     * @tc.expected: The flag should be setted successfully.
     */
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    menuPattern->SetIsWidthModifiedBySelect(true);
    EXPECT_TRUE(menuPattern->IsWidthModifiedBySelect());
}

/**
 * @tc.name: WidthModifiedBySelectTestNg002
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    auto menuWidth = menuPattern->GetSelectMenuWidth();
    ASSERT_NE(menuWidth, 0.0);
}

/**
 * @tc.name: WidthModifiedBySelectTestNg003
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    ASSERT_NE(menuPattern, nullptr);
    auto menuWidth = menuPattern->GetSelectMenuWidth();
    ASSERT_NE(menuWidth, 0.0);
    menuPattern->ShowMenuDisappearAnimation();
}

/**
 * @tc.name: WidthModifiedBySelectTestNg004
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    ASSERT_NE(menuPattern, nullptr);
    auto menuWidth = menuPattern->GetSelectMenuWidth();
    ASSERT_NE(menuWidth, 0.0);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    menuPattern->ShowMenuDisappearAnimation();
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: WidthModifiedBySelectTestNg005
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->type_ = MenuType::SUB_MENU;
    menuWrapperNode->skipMeasureContent_ = false;
    menuPattern->SetMenuShow();
    menuPattern->ShowMenuAppearAnimation();
    EXPECT_FALSE(menuPattern->OnDirtyLayoutWrapperSwap(menuWrapperNode, configDirtySwap));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: WidthModifiedBySelectTestNg006
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->type_ = MenuType::SUB_MENU;
    menuWrapperNode->skipMeasureContent_ = false;
    menuPattern->SetMenuShow();
    menuPattern->ShowMenuAppearAnimation();
    EXPECT_FALSE(menuPattern->OnDirtyLayoutWrapperSwap(menuWrapperNode, configDirtySwap));
}

/**
 * @tc.name: WidthModifiedBySelectTestNg007
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->type_ = MenuType::SUB_MENU;
    menuWrapperNode->skipMeasureContent_ = false;
    EXPECT_FALSE(menuPattern->OnDirtyLayoutWrapperSwap(menuWrapperNode, configDirtySwap));
    menuPattern->SetMenuShow();
    auto rollbackPreviewMode = menuPattern->GetPreviewMode();
    menuPattern->SetPreviewMode(MenuPreviewMode::NONE);
    menuPattern->type_ = MenuType::SELECT_OVERLAY_EXTENSION_MENU;
    menuPattern->isExtensionMenuShow_ = false;
    menuPattern->ShowMenuAppearAnimation();
    menuPattern->SetPreviewMode(rollbackPreviewMode);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: WidthModifiedBySelectTestNg008
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->type_ = MenuType::SUB_MENU;
    menuWrapperNode->skipMeasureContent_ = false;
    menuPattern->SetPreviewMode(MenuPreviewMode::NONE);
    EXPECT_FALSE(menuPattern->OnDirtyLayoutWrapperSwap(menuWrapperNode, configDirtySwap));
    menuPattern->SetMenuShow();
    auto rollbackPreviewMode = menuPattern->GetPreviewMode();
    menuPattern->ShowMenuAppearAnimation();
    menuPattern->SetPreviewMode(rollbackPreviewMode);
}

/**
 * @tc.name: WidthModifiedBySelectTestNg009
 * @tc.desc: Verify the usability of the select menu default width property in the select pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, WidthModifiedBySelectTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select menu without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select menu should be 0.0.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, GREATER_WINDOW_MENU_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    menuPattern->type_ = MenuType::SUB_MENU;
    menuWrapperNode->skipMeasureContent_ = false;
    menuPattern->SetPreviewMode(MenuPreviewMode::NONE);
    EXPECT_FALSE(menuPattern->OnDirtyLayoutWrapperSwap(menuWrapperNode, configDirtySwap));
    menuPattern->SetMenuShow();
    auto rollbackPreviewMode = menuPattern->GetPreviewMode();
    menuPattern->type_ = MenuType::SELECT_OVERLAY_CUSTOM_MENU;
    menuPattern->ShowMenuAppearAnimation();
    menuPattern->SetPreviewMode(rollbackPreviewMode);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    EXPECT_FALSE(menuPattern->isExtensionMenuShow_);
}

/**
 * @tc.name: MenuPreviewLayoutAlgorithmTestNg0100
 * @tc.desc: Test MenuPreviewLayoutAlgorithm Measure and Layout function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuPreviewLayoutAlgorithmTestNg0100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create preview node and menuPreviewLayoutAlgorithm, then set the initial properties
     * @tc.expected: preview node, menuPreviewLayoutAlgorithm are not null
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    auto previewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(previewPattern, nullptr);
    RefPtr<MenuPreviewLayoutAlgorithm> menuPreviewlayoutAlgorithm =
        AceType::DynamicCast<MenuPreviewLayoutAlgorithm>(previewPattern->CreateLayoutAlgorithm());
    ASSERT_NE(menuPreviewlayoutAlgorithm, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    auto layoutWrapper = LayoutWrapperNode(previewNode, geometryNode, layoutProp);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    ASSERT_NE(layoutWrapper.GetLayoutProperty(), nullptr);
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step2. create menuPreviewLayoutAlgorithm Measure and Layout functions
     * @tc.expected: padding property is PREVIEW_INNER_SECURITY
     */
    menuPreviewlayoutAlgorithm->Measure(&layoutWrapper);
    menuPreviewlayoutAlgorithm->Layout(&layoutWrapper);
    PaddingProperty padding;
    ASSERT_NE(layoutProp, nullptr);
}

/**
 * @tc.name: MenuLayoutAlgorithmAPI11PaddingTest1
 * @tc.desc: Test MenuLayoutAlgorithm InitializePaddingAPI12 function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuLayoutAlgorithmAPI11PaddingTest1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutMenuHalfScreen method
     * @tc.expected: menu node, MenuLayoutAlgorithm are not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();

    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto Menu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);

    // create MenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(Menu, geometryNode, layoutProp);

    // link menuItem and menu
    ASSERT_TRUE(menuPattern);
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.type = TYPE;
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;
    algorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    ASSERT_NE(algorithm->wrapperSize_, SizeF(0, 0));
    /**
     * @tc.steps: step3. call the InitializePaddingAPI12 method.
     * @tc.expected: padding is not zero
     */
    algorithm->canExpandCurrentWindow_ = true;
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->menuMediumMargin_ = 10.0_vp;
    algorithm->InitializePaddingAPI12(wrapper);
    ASSERT_EQ(algorithm->paddingStart_, 10.0f);
    ASSERT_EQ(algorithm->paddingEnd_, 10.0f);
    ASSERT_EQ(algorithm->paddingTop_, 0.0f);
    ASSERT_EQ(algorithm->paddingBottom_, 0.0f);
}
/**
 * @tc.name: MenuLayoutAlgorithmAPI11PaddingTest2
 * @tc.desc: Test MenuLayoutAlgorithm InitializePaddingAPI12 function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuLayoutAlgorithmAPI11PaddingTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutMenuHalfScreen method
     * @tc.expected: menu node, MenuLayoutAlgorithm are not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto Menu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    // create MenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(Menu, geometryNode, layoutProp);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    // link menuItem and menu
    ASSERT_TRUE(menuPattern);
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    MenuParam menuParam;
    menuParam.type = TYPE;
    auto menuWrapperNode = MenuView::Create(textNode, TARGET_ID, "", menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;
    algorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    ASSERT_NE(algorithm->wrapperSize_, SizeF(0, 0));
    /**
     * @tc.steps: step3. call the InitializePaddingAPI12 method.
     * @tc.expected: padding is not zero
     */
    algorithm->canExpandCurrentWindow_ = false;
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->outPadding_ = 10.0_vp;
    selectTheme->menuPadding_ = 10.0_vp;
    selectTheme->menuLargeMargin_ = 10.0_vp;
    algorithm->InitializePaddingAPI12(wrapper);
    ASSERT_EQ(algorithm->optionPadding_, 10.0f);
    ASSERT_EQ(algorithm->paddingStart_, 10.0f);
    ASSERT_EQ(algorithm->paddingEnd_, 10.0f);
    ASSERT_EQ(algorithm->paddingTop_, 0.0f);
    ASSERT_EQ(algorithm->paddingBottom_, 0.0f);
}
/**
 * @tc.name: MenuLayoutAlgorithmAvoidWithPreview
 * @tc.desc: Test MenuLayoutAlgorithm LayoutOtherDeviceLeftPreviewRightMenuLessThan function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuLayoutAlgorithmAvoidWithPreview, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is TABLET, create menu node, preview node and menuLayoutAlgorithm, then set the
     * initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_HEIGHT;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    SystemProperties::SetDeviceType(DeviceType::TABLET);
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, OFFSET_THIRD));
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    menuAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_HEIGHT, FULL_SCREEN_WIDTH);
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_THIRD, OFFSET_THIRD);
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;
    auto pipelineContext = DialogManager::GetMainPipelineContext(menuNode);
    ASSERT_NE(pipelineContext, nullptr);
    /**
     * @tc.steps: step2. the window can accommodate preview, placement is LEFT_TOP, layout preview and menu
     * @tc.expected: menu and preview left border distance TARGET_SECURITY, align the menu with the top border of the
     * preview
     */
    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    layoutProperty->UpdateMenuPlacement(Placement::RIGHT_TOP);
    auto expectMenuOffset = OffsetF(-TARGET_SIZE_WIDTH, -TARGET_SIZE_HEIGHT);
    layoutProperty->UpdateMenuPlacement(Placement::LEFT_TOP);
    menuAlgorithm->placement_ = Placement::LEFT_TOP;
    menuAlgorithm->targetOffset_ = OffsetF(FULL_SCREEN_HEIGHT - OFFSET_THIRD, OFFSET_THIRD);
    menuAlgorithm->targetSecurity_ = 10.0f;
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), OffsetF(-TARGET_SIZE_WIDTH, CONST_FLOAT_ZREO));
}
/**
 * @tc.name: MenuLayoutAlgorithmNeedArrow
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuLayoutAlgorithmNeedArrow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(NODEID, TEXT_TAG, MenuType::CONTEXT_MENU);
    auto contextMenu = AceType::MakeRefPtr<FrameNode>(MENU_TAG, -1, menuPattern);
    auto menuAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, TEXT_TAG);
    ASSERT_TRUE(menuAlgorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(contextMenu, geometryNode, layoutProp);
    const SizeF menuSize = SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    /**
     * @tc.steps: step2. execute GetIfNeedArrow
     * @tc.expected: ifNeedArrow is as expected.
     */
    menuAlgorithm->GetPaintProperty(layoutWrapper)->UpdateEnableArrow(true);
    layoutProp->UpdateMenuPlacement(Placement::LEFT_TOP);
    menuAlgorithm->placement_ = Placement::LEFT_TOP;
    auto result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_TRUE(result);
    layoutProp->UpdateMenuPlacement(Placement::BOTTOM);
    menuAlgorithm->placement_ = Placement::BOTTOM;
    result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MenuLayoutAlgorithmNeedArrow002
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuLayoutAlgorithmNeedArrow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(NODEID, TEXT_TAG, MenuType::CONTEXT_MENU);
    ASSERT_NE(menuPattern, nullptr);
    auto contextMenu = AceType::MakeRefPtr<FrameNode>(MENU_TAG, -1, menuPattern);
    auto menuAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, TEXT_TAG);
    ASSERT_TRUE(menuAlgorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(contextMenu, geometryNode, layoutProp);
    const SizeF menuSize = SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    /**
     * @tc.steps: step2. execute GetIfNeedArrow
     * @tc.expected: ifNeedArrow is as expected.
     */
    menuAlgorithm->GetPaintProperty(layoutWrapper)->UpdateEnableArrow(true);
    layoutProp->UpdateMenuPlacement(Placement::RIGHT_TOP);
    menuAlgorithm->placement_ = Placement::RIGHT_TOP;
    auto result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_TRUE(result);
    layoutProp->UpdateMenuPlacement(Placement::TOP);
    menuAlgorithm->placement_ = Placement::TOP;
    result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: MenuLayoutAlgorithmNeedArrow003
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuLayoutAlgorithmNeedArrow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(NODEID, TEXT_TAG, MenuType::CONTEXT_MENU);
    ASSERT_NE(menuPattern, nullptr);
    auto contextMenu = AceType::MakeRefPtr<FrameNode>(MENU_TAG, -1, menuPattern);
    auto menuAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, TEXT_TAG);
    ASSERT_TRUE(menuAlgorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(contextMenu, geometryNode, layoutProp);
    float menuSizeWidthTest = 0.0f;
    float menuSizeHeightTest = 0.0f;
    const SizeF menuSize = SizeF(menuSizeWidthTest, menuSizeHeightTest);
    /**
     * @tc.steps: step2. execute GetIfNeedArrow
     * @tc.expected: ifNeedArrow is as expected.
     */
    menuAlgorithm->GetPaintProperty(layoutWrapper)->UpdateEnableArrow(true);
    layoutProp->UpdateMenuPlacement(Placement::LEFT_TOP);
    menuAlgorithm->placement_ = Placement::LEFT_TOP;
    auto result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_FALSE(result);
    layoutProp->UpdateMenuPlacement(Placement::BOTTOM);
    menuAlgorithm->placement_ = Placement::BOTTOM;
    result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_FALSE(result);
    layoutProp->UpdateMenuPlacement(Placement::RIGHT_TOP);
    menuAlgorithm->placement_ = Placement::RIGHT_TOP;
    result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_FALSE(result);
    layoutProp->UpdateMenuPlacement(Placement::TOP);
    menuAlgorithm->placement_ = Placement::TOP;
    result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MenuViewTestNgTextMaxLines001
 * @tc.desc: Verify MenuView's MaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNgTextMaxLines001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set font scale to 1.75.
     */
    auto context = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->fontScale_ = 1.75f;

    /**
     * @tc.steps: step2. create menu and initialize.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else {
            return AceType::MakeRefPtr<MenuTheme>();
        }
    });
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    InitMenuTestNg();
    InitMenuItemTestNg();
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem", "", nullptr);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), TARGET_ID, "", TYPE, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step2. get textLayoutProperty and verify maxLines setting.
     * @tc.expected: MenuView's maxLines == MenuTheme's maxLines
     */
    auto column = menuPattern->GetMenuColumn();
    ASSERT_NE(column, nullptr);
    auto children = column->GetChildren();
    ASSERT_EQ(children.size(), 1);
    auto optionNode = AceType::DynamicCast<FrameNode>(column->GetChildAtIndex(0));
    ASSERT_NE(optionNode, nullptr);
    auto optionPattern = optionNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(optionPattern, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(optionPattern->GetTextNode());
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetMaxLines().value(), menuTheme->GetTextMaxLines());
}

/**
 * @tc.name: MenuViewTestNg001
 * @tc.desc: Verify UpdateMenuBackgroundEffect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE));
    ASSERT_NE(menuNode, nullptr);

    menuTheme->bgBlurEffectEnable_ = 0;
    MenuView::UpdateMenuBackgroundEffect(menuNode);

    menuTheme->bgBlurEffectEnable_ = 1;
    MenuView::UpdateMenuBackgroundEffect(menuNode);
    auto renderContext = menuNode->GetRenderContext();
    auto effectOption = renderContext->GetBackgroundEffect();
    ASSERT_EQ(effectOption->color, Color::TRANSPARENT);
}

/**
 * @tc.name: MenuViewTestNg002
 * @tc.desc: Verify MenuView::Create when symbol not is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg002, TestSize.Level1)
{
    std::function<void()> action = [] {};
    std::function<void(WeakPtr<NG::FrameNode>)> symbol = [](const WeakPtr<NG::FrameNode>& node) {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.begin()->symbol = symbol;
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuViewTestNg003
 * @tc.desc: Verify MenuView::Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg003, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto customSonNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customSonNode, nullptr);

    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.isShowHoverImage = true;
    menuParam.previewAnimationOptions = { 0.5f, 2.0f };
    menuParam.borderRadius.emplace(Dimension(2));

    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));
    RefPtr<SelectTheme> selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));

    auto gestureHub = customNode->GetOrCreateGestureEventHub();
    menuTheme->doubleBorderEnable_ = 1;

    auto menuWrapperNode1 = MenuView::Create(textNode, TARGET_ID, "", menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode1, nullptr);
    ASSERT_EQ(menuWrapperNode1->GetChildren().size(), 2);

    menuTheme->doubleBorderEnable_ = 0;
    menuParam.previewAnimationOptions = { 0.5f, 0.0009f };
    customSonNode->MountToParent(customNode);
    menuParam.previewMode = MenuPreviewMode::CUSTOM;

    auto menuWrapperNode2 = MenuView::Create(textNode, TARGET_ID, "", menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode2, nullptr);
    ASSERT_EQ(menuWrapperNode2->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuViewTestNg004
 * @tc.desc: Verify SetPreviewInfoToMenu with MenuView::Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg004, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);

    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;

    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 11, AceType::MakeRefPtr<TextPattern>());
    auto targetGestureHub = targetNode->GetOrCreateGestureEventHub();

    targetNode->draggable_ = true;
    auto menuWrapperNode1 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode1, nullptr);
    ASSERT_EQ(menuWrapperNode1->GetChildren().size(), 1);

    menuParam.isShowHoverImage = false;
    menuParam.previewMode = MenuPreviewMode::CUSTOM;
    auto menuWrapperNode2 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode2, nullptr);
    ASSERT_EQ(menuWrapperNode2->GetChildren().size(), 2);

    menuParam.isShowHoverImage = true;
    targetNode->GetPattern<TextPattern>()->copyOption_ = CopyOptions::Local;
    auto menuWrapperNode3 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode3, nullptr);
    ASSERT_EQ(menuWrapperNode3->GetChildren().size(), 2);

    menuParam.previewMode = MenuPreviewMode::NONE;
    targetNode->tag_ = "UINode";
    auto menuWrapperNode4 = MenuView::Create(textNode, 11, "UINode", menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode4, nullptr);
    ASSERT_EQ(menuWrapperNode4->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuViewTestNg005
 * @tc.desc: Verify SetFilter with MenuView::Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg005, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto targetParentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetParentNode, nullptr);

    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;

    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 11, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto targetGestureHub = targetNode->GetOrCreateGestureEventHub();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);

    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->pipelineContext_ = pipeline;

    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    targetParentNode->SetDepth(1);
    targetNode->SetParent(targetParentNode);

    pipeline->GetTheme<MenuTheme>()->hasFilter_ = true;
    targetNode->GetLayoutProperty()->UpdateIsBindOverlay(true);

    auto menuWrapperNode1 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode1, nullptr);
    EXPECT_EQ(menuWrapperNode1->GetChildren().size(), 1);

    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->SetHasFilter(true);
    overlayManager->SetIsOnAnimation(true);
    container->UpdateCurrent(MIN_SUBCONTAINER_ID);

    auto menuWrapperNode2 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode2, nullptr);
    EXPECT_EQ(menuWrapperNode2->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuViewTestNg006
 * @tc.desc: Verify SetPixelMap with MenuView::Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg006, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);

    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;

    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 11, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto targetGestureHub = targetNode->GetOrCreateGestureEventHub();
    auto pixelMap = AceType::MakeRefPtr<MockPixelMap>();

    targetGestureHub->SetPixelMap(pixelMap);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);
    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    auto menuWrapperNode1 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode1, nullptr);
    EXPECT_EQ(menuWrapperNode1->GetChildren().size(), 2);

    menuParam.hasPreviewTransitionEffect = true;

    auto menuWrapperNode2 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode2, nullptr);
    EXPECT_EQ(menuWrapperNode2->GetChildren().size(), 2);

    menuParam.isShowHoverImage = true;
    menuParam.hoverImageAnimationOptions = { 1.0f, 1.0f };
    menuParam.previewAnimationOptions = { 2.0f, 2.0f };
    menuParam.hasPreviewTransitionEffect = false;

    auto menuWrapperNode3 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode3, nullptr);
    EXPECT_EQ(menuWrapperNode3->GetChildren().size(), 2);

    menuParam.previewAnimationOptions = { 1.0f, 2.0f };
    auto menuWrapperNode4 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode4, nullptr);
    EXPECT_EQ(menuWrapperNode4->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuViewTestNg003
 * @tc.desc: Test menu view init pan event.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node, menu node and preview node.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto menuWrapperNode = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(frameNode->GetId(), frameNode->GetTag(), MenuType::MENU));
    auto previewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuPreviewPattern>());
    ASSERT_NE(menuNode, nullptr);
    ASSERT_NE(previewNode, nullptr);
    menuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    auto previewEventHub = previewNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(previewEventHub, nullptr);
    auto previewGestureEventHub = previewEventHub->GetOrCreateGestureEventHub();
    ASSERT_NE(previewGestureEventHub, nullptr);
    EXPECT_TRUE(previewGestureEventHub->IsPanEventEmpty());

    /**
     * @tc.steps: step2. init menu pan event.
     */
    auto menuPreviewPattern = previewNode->GetPattern<MenuPreviewPattern>();
    ASSERT_NE(menuPreviewPattern, nullptr);
    auto hub = previewNode->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    menuPreviewPattern->InitPanEvent(gestureHub);

    /**
     * @tc.steps: step3. check menu preview pan event.
     */
    EXPECT_FALSE(previewGestureEventHub->IsPanEventEmpty());
}

/**
 * @tc.name: MenuViewTestNg008
 * @tc.desc: Verify HandleMenuMaskAndFilter with MenuView::Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg008, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto targetParentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetParentNode, nullptr);

    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;

    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 11, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto targetGestureHub = targetNode->GetOrCreateGestureEventHub();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);

    MockContainer::SetUp();
    auto container = MockContainer::Current();
    container->pipelineContext_ = pipeline;

    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    targetParentNode->SetDepth(1);
    targetNode->SetParent(targetParentNode);

    pipeline->GetTheme<MenuTheme>()->hasFilter_ = true;
    targetNode->GetLayoutProperty()->UpdateIsBindOverlay(true);

    targetNode->draggable_ = true;
    menuParam.maskEnable = true;
    auto menuWrapperNode1 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode1, nullptr);
    ASSERT_EQ(menuWrapperNode1->GetChildren().size(), 1);

    menuParam.type = MenuType::MENU;
    menuParam.maskType = NG::MenuMaskType();
    menuParam.maskType->maskColor = Color::RED;
    menuParam.maskType->maskBackGroundBlurStyle = BlurStyle::BACKGROUND_THIN;
    auto menuWrapperNode2 = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode2, nullptr);
    ASSERT_EQ(menuWrapperNode2->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuPreviewTestNg001
 * @tc.desc: Test menu view create with image preview.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuPreviewTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuWrapper with image preview
     * @tc.expected: menuWrapper node and menuWrapper pattern are not null
     */
    auto menuWrapperNode = GetImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. call IsContextMenu and GetPreviewMode
     * @tc.expected: IsContextMenu is true, GetPreviewMode is MenuPreviewMode::IMAGE
     */
    EXPECT_TRUE(menuWrapperPattern->IsContextMenu());
    EXPECT_EQ(menuWrapperPattern->GetPreviewMode(), MenuPreviewMode::IMAGE);

    /**
     * @tc.steps: step3. call GetMenu
     * @tc.expected: menuNode is not null, tag is V2::MENU_ETS_TAG
     */
    auto menuMode =  menuWrapperPattern->GetMenu();
    ASSERT_NE(menuMode, nullptr);
    EXPECT_EQ(menuMode->GetTag(), V2::MENU_ETS_TAG);

    /**
     * @tc.steps: step4. call GetPreview
     * @tc.expected: previewMode is not null, tag is V2::IMAGE_ETS_TAG
     */
    auto previewMode =  menuWrapperPattern->GetPreview();
    ASSERT_NE(previewMode, nullptr);
    EXPECT_EQ(previewMode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: MenuPreviewTestNg002
 * @tc.desc: Test menu view create with hoverimage preview.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuPreviewTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuWrapper with image preview
     * @tc.expected: menuWrapper node and menuWrapper pattern are not null
     */
    auto menuWrapperNode = GetHoverImagePreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    /**
     * @tc.steps: step2. call IsContextMenu and GetPreviewMode
     * @tc.expected: IsContextMenu is true, GetPreviewMode is MenuPreviewMode::IMAGE
     */
    EXPECT_TRUE(menuWrapperPattern->IsContextMenu());
    EXPECT_EQ(menuWrapperPattern->GetPreviewMode(), MenuPreviewMode::CUSTOM);

    /**
     * @tc.steps: step3. call GetMenu
     * @tc.expected: menuNode is not null, tag is V2::MENU_ETS_TAG
     */
    auto menuMode =  menuWrapperPattern->GetMenu();
    ASSERT_NE(menuMode, nullptr);
    EXPECT_EQ(menuMode->GetTag(), V2::MENU_ETS_TAG);

    /**
     * @tc.steps: step4. call GetPreview
     * @tc.expected: previewMode is not null, tag is V2::MENU_PREVIEW_ETS_TAG
     */
    auto previewMode =  menuWrapperPattern->GetPreview();
    ASSERT_NE(previewMode, nullptr);
    EXPECT_EQ(previewMode->GetTag(), V2::MENU_PREVIEW_ETS_TAG);

    /**
     * @tc.steps: step5. call GetHoverImagePreview
     * @tc.expected: imageMode is not null, tag is V2::IMAGE_ETS_TAG
     */
    auto ImageMode =  menuWrapperPattern->GetHoverImagePreview();
    ASSERT_NE(ImageMode, nullptr);
    EXPECT_EQ(ImageMode->GetTag(), V2::IMAGE_ETS_TAG);

    /**
     * @tc.steps: step6. call GetHoverImageCustomPreview
     * @tc.expected: customPreview node is not null, tag is V2::MENU_PREVIEW_ETS_TAG
     */
    auto customPreview =  menuWrapperPattern->GetHoverImageCustomPreview();
    ASSERT_NE(customPreview, nullptr);
    EXPECT_EQ(customPreview->GetTag(), V2::MENU_PREVIEW_ETS_TAG);
}

/**
 * @tc.name: CreateMenuTest001
 * @tc.desc: Test CreateMenu creates a FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, CreateMenuTest001, TestSize.Level1)
{
    auto menuNode = MenuModelNG::CreateMenu();
    ASSERT_NE(menuNode, nullptr);

    auto layoutProps = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
}

/**
 * @tc.name: MenuViewTestNg009
 * @tc.desc: Verify MenuView::Create when mask is true.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg009, TestSize.Level1)
{
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    auto targetParentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetParentNode, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 11, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    targetParentNode->SetDepth(1);
    targetNode->SetParent(targetParentNode);
    customNode->SetDepth(2);
    targetParentNode->SetParent(customNode);

    MenuParam menuParam;
    menuParam.type = MenuType::MENU;
    menuParam.maskEnable = true;
    menuParam.isShowInSubWindow = true;
    std::vector<OptionParam> optionParams;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetThemeManager(themeManager);

    auto container = MockContainer::Current();
    container->pipelineContext_ = pipeline;

    RefPtr<MenuTheme> menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 11, V2::TEXT_ETS_TAG, MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern->GetFilterColumnNode(), nullptr);
}

/**
 * @tc.name: MenuViewTestNg010
 * @tc.desc: Verify MenuView::Create when mask is false.
 * @tc.type: FUNC
 */
HWTEST_F(MenuTestNg, MenuViewTestNg010, TestSize.Level1)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    auto customNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(customNode, nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::MENU;
    menuParam.maskEnable = false;

    auto menuWrapperNode = MenuView::Create(textNode, 11, V2::TEXT_ETS_TAG, menuParam, true, customNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_EQ(menuWrapperPattern->GetFilterColumnNode(), nullptr);
}
} // namespace OHOS::Ace::NG
