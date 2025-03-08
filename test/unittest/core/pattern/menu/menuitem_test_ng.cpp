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
#include "core/components/text_overlay/text_overlay_theme.h"
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
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;

const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
const V2::ItemDivider ITEM_DIVIDER = { Dimension(5.f), Dimension(10), Dimension(20), Color(0x000000) };

RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == TextTheme::TypeId()) {
        return AceType::MakeRefPtr<TextTheme>();
    } else if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == SelectTheme::TypeId()) {
        return AceType::MakeRefPtr<SelectTheme>();
    } else {
        return AceType::MakeRefPtr<MenuTheme>();
    }
}
} // namespace
class MenuItemTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuItemTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuItemTestNg::SetUpTestCase() {}

void MenuItemTestNg::TearDownTestCase() {}

void MenuItemTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuItemTestNg::TearDown()
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

void MenuItemTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemTestNg::GetPreviewMenuWrapper(
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

/**
 * @tc.name: MenuItemAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of menuItem.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemAccessibilityPropertyGetText001, TestSize.Level1)
{
    InitMenuItemTestNg();

    EXPECT_EQ(menuItemAccessibilityProperty_->GetText(), EMPTY_TEXT);

    auto menuItemLayoutProperty = menuItemFrameNode_->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuItemLayoutProperty, nullptr);
    menuItemLayoutProperty->UpdateContent(MENU_ITEM_TEXT);

    EXPECT_EQ(menuItemAccessibilityProperty_->GetText(), MENU_ITEM_TEXT);
}

/**
 * @tc.name: MenuItemAccessibilityPropertyIsSelected001
 * @tc.desc: Test IsSelected of menuitem.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemAccessibilityPropertyIsSelected001, TestSize.Level1)
{
    InitMenuItemTestNg();

    EXPECT_FALSE(menuItemAccessibilityProperty_->IsSelected());

    menuItemPattern_->SetSelected(true);
    EXPECT_TRUE(menuItemAccessibilityProperty_->IsSelected());
}

/**
 * @tc.name: MenuItemAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of menuitem.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitMenuItemTestNg();

    menuItemAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = menuItemAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: MenuItemGroupAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of menuItemGroup.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemGroupAccessibilityPropertyGetText001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); });
    ASSERT_NE(frameNode, nullptr);

    auto menuItemGroupPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemGroupPattern, nullptr);

    auto menuItemGroupAccessibilityProperty = frameNode->GetAccessibilityProperty<MenuItemGroupAccessibilityProperty>();
    ASSERT_NE(menuItemGroupAccessibilityProperty, nullptr);
    EXPECT_EQ(menuItemGroupAccessibilityProperty->GetText(), EMPTY_TEXT);

    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(content, nullptr);
    menuItemGroupPattern->AddHeaderContent(content);

    auto textLayoutProperty = content->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(MENU_ITEM_GROUP_TEXT);
    EXPECT_EQ(menuItemGroupAccessibilityProperty->GetText(), MENU_ITEM_GROUP_TEXT);
}

/**
 * @tc.name: MenuItemLayoutAlgorithm001
 * @tc.desc: Test MenuItemLayoutAlgorithm Measure
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::CONTEXT_MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto leftNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    auto rightNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    menuItemNode->AddChild(leftNode);
    menuItemNode->AddChild(rightNode);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto algorithm = AceType::DynamicCast<MenuItemLayoutAlgorithm>(menuItemPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
    auto props = menuItemNode->GetLayoutProperty();
    ASSERT_NE(props, nullptr);
    SizeF value(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT);
    props->UpdateMarginSelfIdealSize(value);
    props->UpdateContentConstraint();

    /**
     * @tc.steps: step2. execute Measure
     * @tc.expected: prop is set as expected
     */
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    algorithm->Layout(AceType::RawPtr(menuItemNode));

    props->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(MENU_ITEM_SIZE_WIDTH), CalcLength(MENU_ITEM_SIZE_HEIGHT)));
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    EXPECT_TRUE(props->calcLayoutConstraint_->selfIdealSize.has_value());
}

/**
 * @tc.name: MenuItemLayoutAlgorithm002
 * @tc.desc: Test MenuItemLayoutAlgorithm Measure
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemLayoutAlgorithm002, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(18);

    /**
     * @tc.steps: step1. Create menuItem.
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::CONTEXT_MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto leftNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    auto rightNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    menuItemNode->AddChild(leftNode);
    menuItemNode->AddChild(rightNode);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto algorithm = AceType::DynamicCast<MenuItemLayoutAlgorithm>(menuItemPattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
    auto props = menuItemNode->GetLayoutProperty();
    ASSERT_NE(props, nullptr);
    SizeF value(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT);
    props->UpdateMarginSelfIdealSize(value);
    props->UpdateContentConstraint();

    /**
     * @tc.steps: step2. execute Measure
     * @tc.expected: prop is set as expected
     */
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    algorithm->Layout(AceType::RawPtr(menuItemNode));

    props->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(MENU_ITEM_SIZE_WIDTH), CalcLength(MENU_ITEM_SIZE_HEIGHT)));
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    EXPECT_TRUE(props->calcLayoutConstraint_->selfIdealSize.has_value());

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: MenuItemViewTestNgCreate001
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemViewTestNgCreate001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0);

    ASSERT_TRUE(itemProperty->GetStartIcon().has_value());
    EXPECT_EQ(itemProperty->GetStartIcon().value().GetSrc(), "");
    ASSERT_TRUE(itemProperty->GetEndIcon().has_value());
    EXPECT_EQ(itemProperty->GetEndIcon().value().GetSrc(), "");
    ASSERT_TRUE(itemProperty->GetContent().has_value());
    EXPECT_EQ(itemProperty->GetContent().value(), "");
    ASSERT_TRUE(itemProperty->GetLabel().has_value());
    EXPECT_EQ(itemProperty->GetLabel().value(), "");
}

/**
 * @tc.name: MenuItemViewTestNgCreate002
 * @tc.desc: Verify Create.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemViewTestNgCreate002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.startIcon = ImageSourceInfo(IMAGE_SRC_URL);
    itemOption.endIcon = ImageSourceInfo(IMAGE_SRC_URL);
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetStartIcon().has_value());
    EXPECT_EQ(itemProperty->GetStartIcon().value().GetSrc(), IMAGE_SRC_URL);
    ASSERT_TRUE(itemProperty->GetEndIcon().has_value());
    EXPECT_EQ(itemProperty->GetEndIcon().value().GetSrc(), IMAGE_SRC_URL);
    ASSERT_TRUE(itemProperty->GetContent().has_value());
    EXPECT_EQ(itemProperty->GetContent().value(), "content");
    ASSERT_TRUE(itemProperty->GetLabel().has_value());
    EXPECT_EQ(itemProperty->GetLabel().value(), "label");
}

/**
 * @tc.name: MenuItemViewTestNg002
 * @tc.desc: Verify MenuItemModelNG methods with frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemViewTestNg002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    FrameNode *frameNode = Referenced::RawPtr(itemNode);
    CHECK_NULL_VOID(frameNode);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    MneuItemModelInstance.SetSelected(frameNode, true);
    MneuItemModelInstance.SetSelectIconSymbol(frameNode, [](WeakPtr<NG::FrameNode> weakPtr) {});
    std::vector<std::string> families = {"cursive"};
    MneuItemModelInstance.SetFontFamily(frameNode, families);

    MneuItemModelInstance.SetFontColor(frameNode, Color::RED);
    EXPECT_EQ(itemProperty->GetFontColor().value(), Color::RED);

    MneuItemModelInstance.SetFontColor(frameNode, std::nullopt);
    ASSERT_FALSE(itemProperty->GetFontColor().has_value());

    MneuItemModelInstance.SetFontSize(frameNode, Dimension(10));
    EXPECT_EQ(itemProperty->GetFontSize().value(), Dimension(10));

    MneuItemModelInstance.SetFontSize(frameNode, Dimension(0));
    EXPECT_FALSE(itemProperty->GetFontSize().has_value());

    MneuItemModelInstance.SetFontWeight(frameNode, FontWeight::BOLD);
    EXPECT_EQ(itemProperty->GetFontWeight().value(), FontWeight::BOLD);

    MneuItemModelInstance.SetFontStyle(frameNode, Ace::FontStyle::ITALIC);
    EXPECT_EQ(itemProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);

    MneuItemModelInstance.SetSelectIcon(frameNode, true);
    EXPECT_EQ(itemProperty->GetSelectIcon().value_or(false), true);

    MneuItemModelInstance.SetSelectIconSrc(frameNode, "selectIcon.png");
    EXPECT_EQ(itemProperty->GetSelectIconSrc().value_or(""), "selectIcon.png");
}

/**
 * @tc.name: MenuItemViewTestNg003
 * @tc.desc: Verify MenuItemModelNG methods with frameNode about label.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemViewTestNg003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    FrameNode *frameNode = Referenced::RawPtr(itemNode);
    CHECK_NULL_VOID(frameNode);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    std::vector<std::string> families = {"cursive"};
    MneuItemModelInstance.SetLabelFontFamily(frameNode, families);

    MneuItemModelInstance.SetLabelFontColor(frameNode, Color::RED);
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), Color::RED);

    MneuItemModelInstance.SetLabelFontColor(frameNode, std::nullopt);
    ASSERT_FALSE(itemProperty->GetLabelFontColor().has_value());

    MneuItemModelInstance.SetLabelFontSize(frameNode, Dimension(10));
    EXPECT_EQ(itemProperty->GetLabelFontSize().value(), Dimension(10));

    MneuItemModelInstance.SetLabelFontSize(frameNode, Dimension(0));
    EXPECT_FALSE(itemProperty->GetLabelFontSize().has_value());

    MneuItemModelInstance.SetLabelFontWeight(frameNode, FontWeight::BOLD);
    EXPECT_EQ(itemProperty->GetLabelFontWeight().value(), FontWeight::BOLD);

    MneuItemModelInstance.SetLabelFontStyle(frameNode, Ace::FontStyle::ITALIC);
    EXPECT_EQ(itemProperty->GetLabelItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: MenuItemPaintMethod001
 * @tc.desc: Test MenuItem GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemPaintMethod001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuItemPaintProperty> paintProp = AceType::MakeRefPtr<MenuItemPaintProperty>();
    RefPtr<MenuItemPaintMethod> paintMethod = AceType::MakeRefPtr<MenuItemPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update paint property and execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(itemNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdateDividerColor(Color::RED);
    paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdateNeedDivider(true);
    paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuItemPaintMethod002
 * @tc.desc: Test MenuItem GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemPaintMethod002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuItemPaintProperty> paintProp = AceType::MakeRefPtr<MenuItemPaintProperty>();
    RefPtr<MenuItemPaintMethod> paintMethod = AceType::MakeRefPtr<MenuItemPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update paint property and execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    renderContext->SetHostNode(itemNode);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdatePress(false);
    paintProp->UpdateHover(false);
    paintProp->UpdateNeedDivider(true);
    paintProp->UpdateDividerColor(Color::RED);
    paintProp->UpdateStrokeWidth(Dimension(1.0f, DimensionUnit::PX));
    paintProp->UpdateStartMargin(Dimension(1.0f, DimensionUnit::PX));
    paintProp->UpdateEndMargin(Dimension(1.0f, DimensionUnit::PX));
    paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuItemTestNgTextMaxLines001
 * @tc.desc: Verify MenuItem's MaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemTestNgTextMaxLines001, TestSize.Level1)
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
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    InitMenuItemTestNg();
    InitMenuItemTestNg();
    MenuModelNG menuModelInstance;
    MenuItemModelNG menuItemModelInstance;
    menuModelInstance.Create();
    menuModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto menuItemLayoutProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuItemLayoutProperty, nullptr);
    itemPattern->OnModifyDone();

    /**
     * @tc.steps: step2. get textLayoutProperty and verify maxLines setting.
     * @tc.expected: MenuItem's maxLines == MenuTheme's maxLines
     */
    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetMaxLines().value(), menuTheme->GetTextMaxLines());
}

/**
 * @tc.name: MenuItemTestNgText001
 * @tc.desc: Verify UpdateNeedDivider.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemTestNgText001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto menu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    CHECK_NULL_VOID(menu);
    auto menuProperty = menu->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->UpdateItemDivider(ITEM_DIVIDER);
    auto menuItemLayoutProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuItemLayoutProperty, nullptr);
    itemPattern->UpdateNeedDivider(true);
}

/**
 * @tc.name: MenuItemSetSelectIconSymbolNg001
 * @tc.desc: Verify MenuItemModelNG SetSelectIconSymbol.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemSetSelectIconSymbolNg001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension());
    MneuItemModelInstance.SetSelectIconSymbol([](WeakPtr<NG::FrameNode> weakPtr= nullptr) {});
    MneuItemModelInstance.SetOnChange([](bool onChange) {});
    std::vector<std::string> families = {"cursive"};
    MneuItemModelInstance.SetFontFamily(families);
    MneuItemModelInstance.SetLabelFontFamily(families);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_FALSE(itemProperty->GetFontSize().has_value());
}

/**
 * @tc.name: MenuItemSetSelectIconSymbolNg002
 * @tc.desc: Verify MenuItemModelNG SetSelectIconSymbol frameNode.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemSetSelectIconSymbolNg002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    FrameNode *frameNode = Referenced::RawPtr(itemNode);
    CHECK_NULL_VOID(frameNode);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    MneuItemModelInstance.SetSelected(frameNode, true);
    MneuItemModelInstance.SetSelectIconSymbol(frameNode, [](WeakPtr<NG::FrameNode> weakPtr = nullptr) {});
    std::vector<std::string> families = {"cursive"};
    MneuItemModelInstance.SetFontFamily(frameNode, families);

    MneuItemModelInstance.SetFontColor(frameNode, Color::RED);
    EXPECT_EQ(itemProperty->GetFontColor().value(), Color::RED);

    MneuItemModelInstance.SetFontColor(frameNode, std::nullopt);
    ASSERT_FALSE(itemProperty->GetFontColor().has_value());

    MneuItemModelInstance.SetFontSize(frameNode, Dimension(10));
    EXPECT_EQ(itemProperty->GetFontSize().value(), Dimension(10));

    MneuItemModelInstance.SetFontSize(frameNode, Dimension(0));
    EXPECT_FALSE(itemProperty->GetFontSize().has_value());

    MneuItemModelInstance.SetFontWeight(frameNode, FontWeight::BOLD);
    EXPECT_EQ(itemProperty->GetFontWeight().value(), FontWeight::BOLD);

    MneuItemModelInstance.SetFontStyle(frameNode, Ace::FontStyle::ITALIC);
    EXPECT_EQ(itemProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);

    MneuItemModelInstance.SetSelectIcon(frameNode, true);
    EXPECT_EQ(itemProperty->GetSelectIcon().value_or(false), true);

    MneuItemModelInstance.SetSelectIconSrc(frameNode, "selectIcon.png");
    EXPECT_EQ(itemProperty->GetSelectIconSrc().value_or(""), "selectIcon.png");
}

/**
 * @tc.name: MenuItemEventTest001
 * @tc.desc: Test Menuitem onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemEventTest001, TestSize.Level1)
{
    MenuItemModelNG menuitem;
    MenuItemProperties itemOption;
    menuitem.Create(itemOption);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    menuitem.SetOnChange(frameNode, [](bool onChange) {});
    EXPECT_NE(eventHub->onChange_, nullptr);
}

/**
 * @tc.name: MenuItemPattern#UpdatePasteDisabledOpacity001
 * @tc.desc: Verify UpdatePasteDisabledOpacity.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemPatternUpdatePasteDisabledOpacity001, TestSize.Level1)
{
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    menuItemModelInstance.Create(itemOption);
    menuItemModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);

    auto id = ElementRegister::GetInstance()->MakeUniqueId();
    auto option = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, id, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
    ASSERT_NE(option, nullptr);

    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else {
            return nullptr;
        }
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            if (type == TextOverlayTheme::TypeId()) {
                return AceType::MakeRefPtr<TextOverlayTheme>();
            } else if (type == SelectTheme::TypeId()) {
                return AceType::MakeRefPtr<SelectTheme>();
            } else {
                return nullptr;
            }
        });
    MenuView::CreatePasteButton(false, option, row, []() {});
    auto optionFirstChild = option->GetChildAtIndex(0);
    ASSERT_NE(optionFirstChild, nullptr);
    auto pasteButtonChildren = optionFirstChild->GetChildren();
    auto pasteButton = AceType::DynamicCast<FrameNode>(pasteButtonChildren.front());
    ASSERT_NE(pasteButton, nullptr);

    itemPattern->SetPasteButton(pasteButton);
    itemPattern->UpdatePasteDisabledOpacity(0.9f);

    auto renderContext = pasteButton->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOpacityValue(1.0), 0.9f);
}
} // namespace OHOS::Ace::NG
