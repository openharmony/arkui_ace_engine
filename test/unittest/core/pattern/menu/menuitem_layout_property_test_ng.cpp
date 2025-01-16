/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
constexpr int32_t DEFAULT_SYMBOL_ID = 983242;
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
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuItemLayoutPropertyTestNg : public testing::Test {
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

void MenuItemLayoutPropertyTestNg::SetUpTestCase() {}

void MenuItemLayoutPropertyTestNg::TearDownTestCase() {}

void MenuItemLayoutPropertyTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuItemLayoutPropertyTestNg::TearDown()
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

void MenuItemLayoutPropertyTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemLayoutPropertyTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemLayoutPropertyTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: GetStartIcon001
 * @tc.desc: Verify GetStartIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetStartIcon001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetStartIcon().has_value());
    property.UpdateStartIcon(ImageSourceInfo(IMAGE_SRC_URL));
    ASSERT_TRUE(property.GetStartIcon().has_value());
    EXPECT_EQ(property.GetStartIcon().value().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: GetContent001
 * @tc.desc: Verify GetContent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetContent001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetContent().has_value());
    property.UpdateContent("content");
    ASSERT_TRUE(property.GetContent().has_value());
    EXPECT_EQ(property.GetContent().value(), "content");
}

/**
 * @tc.name: GetEndIcon001
 * @tc.desc: Verify GetEndIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetEndIcon001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetEndIcon().has_value());
    property.UpdateEndIcon(ImageSourceInfo(IMAGE_SRC_URL));
    ASSERT_TRUE(property.GetEndIcon().has_value());
    EXPECT_EQ(property.GetEndIcon().value().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: GetLabel001
 * @tc.desc: Verify GetLabel.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetLabel001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabel().has_value());
    property.UpdateLabel("label");
    ASSERT_TRUE(property.GetLabel().has_value());
    EXPECT_EQ(property.GetLabel().value(), "label");
}

/**
 * @tc.name: GetSelectIcon001
 * @tc.desc: Verify GetSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetSelectIcon001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetSelectIcon().has_value());
    property.UpdateSelectIcon(true);
    ASSERT_TRUE(property.GetSelectIcon().has_value());
    EXPECT_TRUE(property.GetSelectIcon().value());
}

/**
 * @tc.name: GetSelectIconSrc001
 * @tc.desc: Verify GetSelectIconSrc.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetSelectIconSrc001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetSelectIconSrc().has_value());
    property.UpdateSelectIconSrc("test.png");
    ASSERT_TRUE(property.GetSelectIconSrc().has_value());
    EXPECT_EQ(property.GetSelectIconSrc().value(), "test.png");
}

/**
 * @tc.name: GetFontSize001
 * @tc.desc: Verify GetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetFontSize001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetFontSize().has_value());
    property.UpdateFontSize(Dimension(25.0f));
    ASSERT_TRUE(property.GetFontSize().has_value());
    EXPECT_EQ(property.GetFontSize().value(), Dimension(25.0f));
}

/**
 * @tc.name: GetFontColor001
 * @tc.desc: Verify GetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetFontColor001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetFontColor().has_value());
    property.UpdateFontColor(Color::RED);
    ASSERT_TRUE(property.GetFontColor().has_value());
    EXPECT_EQ(property.GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: GetFontWeight001
 * @tc.desc: Verify GetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetFontWeight001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetFontWeight().has_value());
    property.UpdateFontWeight(FontWeight::BOLD);
    ASSERT_TRUE(property.GetFontWeight().has_value());
    EXPECT_EQ(property.GetFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: GetLabelFontSize001
 * @tc.desc: Verify GetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetLabelFontSize001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabelFontSize().has_value());
    property.UpdateLabelFontSize(Dimension(25.0f));
    ASSERT_TRUE(property.GetLabelFontSize().has_value());
    EXPECT_EQ(property.GetLabelFontSize().value(), Dimension(25.0f));
}

/**
 * @tc.name: GetLabelFontColor001
 * @tc.desc: Verify GetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetLabelFontColor001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabelFontColor().has_value());
    property.UpdateLabelFontColor(Color::RED);
    ASSERT_TRUE(property.GetLabelFontColor().has_value());
    EXPECT_EQ(property.GetLabelFontColor().value(), Color::RED);
}

/**
 * @tc.name: GetLabelFontWeight001
 * @tc.desc: Verify GetLabelFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetLabelFontWeight001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    EXPECT_FALSE(property.GetLabelFontWeight().has_value());
    property.UpdateLabelFontWeight(FontWeight::BOLD);
    ASSERT_TRUE(property.GetLabelFontWeight().has_value());
    EXPECT_EQ(property.GetLabelFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: Reset001
 * @tc.desc: Verify Reset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, Reset001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateStartIcon(ImageSourceInfo(IMAGE_SRC_URL));
    property.UpdateContent("content");
    property.UpdateEndIcon(ImageSourceInfo(IMAGE_SRC_URL));
    property.UpdateLabel("label");
    property.UpdateSelectIcon(true);
    property.UpdateSelectIconSrc("test.png");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    property.UpdateLabelFontSize(Dimension(25.0f));
    property.UpdateLabelFontColor(Color::RED);
    property.UpdateLabelFontWeight(FontWeight::BOLD);
    EXPECT_TRUE(property.GetStartIcon().has_value());
    EXPECT_TRUE(property.GetContent().has_value());
    EXPECT_TRUE(property.GetLabel().has_value());
    EXPECT_TRUE(property.GetEndIcon().has_value());
    EXPECT_TRUE(property.GetSelectIcon().has_value());
    EXPECT_TRUE(property.GetSelectIconSrc().has_value());
    EXPECT_TRUE(property.GetFontSize().has_value());
    EXPECT_TRUE(property.GetFontColor().has_value());
    EXPECT_TRUE(property.GetFontWeight().has_value());
    EXPECT_TRUE(property.GetLabelFontSize().has_value());
    EXPECT_TRUE(property.GetLabelFontColor().has_value());
    EXPECT_TRUE(property.GetLabelFontWeight().has_value());
    property.Reset();
    EXPECT_FALSE(property.GetStartIcon().has_value());
    EXPECT_FALSE(property.GetContent().has_value());
    EXPECT_FALSE(property.GetLabel().has_value());
    EXPECT_FALSE(property.GetEndIcon().has_value());
    EXPECT_FALSE(property.GetSelectIcon().has_value());
    EXPECT_FALSE(property.GetSelectIconSrc().has_value());
    EXPECT_FALSE(property.GetFontSize().has_value());
    EXPECT_FALSE(property.GetFontColor().has_value());
    EXPECT_FALSE(property.GetFontWeight().has_value());
    EXPECT_FALSE(property.GetLabelFontSize().has_value());
    EXPECT_FALSE(property.GetLabelFontColor().has_value());
    EXPECT_FALSE(property.GetLabelFontWeight().has_value());
}

/**
 * @tc.name: Clone001
 * @tc.desc: Verify Clone.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, Clone001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateStartIcon(ImageSourceInfo(IMAGE_SRC_URL));
    property.UpdateContent("content");
    property.UpdateEndIcon(ImageSourceInfo(IMAGE_SRC_URL));
    property.UpdateLabel("label");
    property.UpdateSelectIcon(true);
    property.UpdateSelectIconSrc("select.png");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    property.UpdateLabelFontSize(Dimension(35.0f));
    property.UpdateLabelFontColor(Color::BLUE);
    property.UpdateLabelFontWeight(FontWeight::LIGHTER);

    auto cloneProperty = AceType::DynamicCast<MenuItemLayoutProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_EQ(property.GetStartIcon().value(), cloneProperty->GetStartIcon().value());
    EXPECT_EQ(property.GetContent().value(), cloneProperty->GetContent().value());
    EXPECT_EQ(property.GetEndIcon().value(), cloneProperty->GetEndIcon().value());
    EXPECT_EQ(property.GetLabel().value(), cloneProperty->GetLabel().value());
    EXPECT_EQ(property.GetSelectIcon().value(), cloneProperty->GetSelectIcon().value());
    EXPECT_EQ(property.GetSelectIconSrc().value(), cloneProperty->GetSelectIconSrc().value());
    EXPECT_EQ(property.GetFontSize().value(), cloneProperty->GetFontSize().value());
    EXPECT_EQ(property.GetFontColor().value(), cloneProperty->GetFontColor().value());
    EXPECT_EQ(property.GetFontWeight().value(), cloneProperty->GetFontWeight().value());
    EXPECT_EQ(property.GetLabelFontSize().value(), cloneProperty->GetLabelFontSize().value());
    EXPECT_EQ(property.GetLabelFontColor().value(), cloneProperty->GetLabelFontColor().value());
    EXPECT_EQ(property.GetLabelFontWeight().value(), cloneProperty->GetLabelFontWeight().value());
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, ToJsonValue001, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateStartIcon(ImageSourceInfo(IMAGE_SRC_URL));
    property.UpdateContent("content");
    property.UpdateEndIcon(ImageSourceInfo(IMAGE_SRC_URL));
    property.UpdateLabel("label");
    property.UpdateSelectIcon(true);
    property.UpdateSelectIconSrc("select.png");
    property.UpdateFontSize(Dimension(25.0f));
    property.UpdateFontColor(Color::RED);
    property.UpdateFontWeight(FontWeight::BOLD);
    property.UpdateLabelFontSize(Dimension(35.0f));
    property.UpdateLabelFontColor(Color::BLUE);
    property.UpdateLabelFontWeight(FontWeight::LIGHTER);

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json, filter);
    auto labelFontJson = json->GetObject("labelFont");
    auto contentFontJson = json->GetObject("contentFont");
    EXPECT_EQ(json->GetString("startIcon"), IMAGE_SRC_URL);
    EXPECT_EQ(json->GetString("content"), "content");
    EXPECT_EQ(json->GetString("endIcon"), IMAGE_SRC_URL);
    EXPECT_EQ(json->GetString("labelInfo"), "label");
    EXPECT_EQ(json->GetString("selectIcon"), "select.png");
    EXPECT_EQ(contentFontJson->GetString("size"), Dimension(25.0f).ToString());
    EXPECT_EQ(json->GetString("contentFontColor"), Color::RED.ColorToString());
    EXPECT_EQ(contentFontJson->GetString("weight"), V2::ConvertWrapFontWeightToStirng(FontWeight::BOLD));
    EXPECT_EQ(labelFontJson->GetString("size"), Dimension(35.0f).ToString());
    EXPECT_EQ(json->GetString("labelFontColor"), Color::BLUE.ColorToString());
    EXPECT_EQ(labelFontJson->GetString("weight"), V2::ConvertWrapFontWeightToStirng(FontWeight::LIGHTER));
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, ToJsonValue002, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateSelectIcon(false);
    property.UpdateSelectIconSrc("select.png");

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selectIcon"), "false");
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, ToJsonValue003, TestSize.Level1)
{
    MenuItemLayoutProperty property;
    property.UpdateSelectIcon(true);

    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selectIcon"), "true");
}

/**
 * @tc.name: ToJsonValue004
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, ToJsonValue004, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectIcon(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    auto json = JsonUtil::Create(true);
    itemProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selectIcon"), "true");
}

/**
 * @tc.name: GetStartSymbol001
 * @tc.desc: Verify GetStartSymbol.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, GetStartSymbol001, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelected(false);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    auto symbolNode = FrameNode::CreateFrameNode(
        V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(symbolNode, nullptr);
    auto property = symbolNode->GetLayoutProperty<TextLayoutProperty>();

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    uint32_t symbolId = menuTheme->GetSymbolId();
    ASSERT_NE(symbolId, 0);
    property->UpdateSymbolSourceInfo(SymbolSourceInfo(symbolId));
    auto symbolProps = symbolNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(symbolProps, nullptr);
    EXPECT_EQ(symbolProps->GetStartSymbol(), nullptr);
    EXPECT_EQ(symbolProps->GetEndSymbol(), nullptr);
    leftRow = symbolNode;
    rightRow = symbolNode;
    EXPECT_NE(symbolProps->GetStartSymbol(), nullptr);
    EXPECT_NE(symbolProps->GetEndSymbol(), nullptr);
}

/**
 * @tc.name: UpdateSymbolSourceInfo001
 * @tc.desc: Verify GetSelectIconSymbol.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, UpdateSymbolSourceInfo001, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelected(false);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    auto symbolNode = FrameNode::CreateFrameNode(
        V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(symbolNode, nullptr);
    auto property = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto menuTheme = pipeline->GetTheme<MenuTheme>();
    CHECK_NULL_VOID(menuTheme);
    uint32_t symbolId = menuTheme->GetSymbolId();
    ASSERT_NE(symbolId, 0);
    auto symbolProps = symbolNode->GetLayoutProperty<MenuItemLayoutProperty>();
    MenuItemModelInstance.SetSelected(true);

    property->UpdateSymbolSourceInfo(SymbolSourceInfo(symbolId));
    EXPECT_EQ(leftRow, symbolNode);
    property->UpdateSymbolSourceInfo(SymbolSourceInfo(DEFAULT_SYMBOL_ID));
    EXPECT_NE(leftRow, symbolNode);
}

/**
 * @tc.name: SetSelectIcon001
 * @tc.desc: Verify SetSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetSelectIcon001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectIcon(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_EQ(itemProperty->GetSelectIcon().value_or(false), true);
}

/**
 * @tc.name: SetSelectIcon002
 * @tc.desc: Verify SetSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetSelectIcon002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetSelectIcon(true);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_FALSE(itemProperty->GetSelectIcon().has_value());
}

/**
 * @tc.name: SetSelectIconSrc001
 * @tc.desc: Verify SetSelectIconSrc.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetSelectIconSrc001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_EQ(itemProperty->GetSelectIconSrc().value_or(""), "selectIcon.png");
}

/**
 * @tc.name: SetSelectIconSrc002
 * @tc.desc: Verify SetSelectIconSrc.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetSelectIconSrc002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_FALSE(itemProperty->GetSelectIconSrc().has_value());
}

/**
 * @tc.name: SetFontSize
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontSize001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension());
    MneuItemModelInstance.SetSelectIconSymbol([](WeakPtr<NG::FrameNode> weakPtr) {});
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
 * @tc.name: SetFontSize002
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontSize002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension());
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_FALSE(itemProperty->GetFontSize().has_value());
}

/**
 * @tc.name: SetFontSize003
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontSize003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension(40.0));
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontSize().has_value());
    EXPECT_EQ(itemProperty->GetFontSize().value(), Dimension(40.0));
}

/**
 * @tc.name: SetFontSize004
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontSize004, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetFontSize(Dimension(40.0));
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetFontSize().has_value());
}

/**
 * @tc.name: SetFontSize005
 * @tc.desc: Verify SetFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontSize005, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    bool isSelected = false;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetSelectedChangeEvent(changeEvent);

    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);

    auto itemProperty = itemNode->GetEventHub<NG::MenuItemEventHub>();
    ASSERT_NE(itemProperty, nullptr);
    EXPECT_TRUE(itemProperty->GetSelectedChangeEvent());
}

/**
 * @tc.name: SetFontWeight001
 * @tc.desc: Verify SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontWeight001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontWeight(FontWeight::BOLD);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontWeight().has_value());
    EXPECT_EQ(itemProperty->GetFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: SetFontWeight002
 * @tc.desc: Verify SetFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontWeight002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetFontWeight(FontWeight::BOLD);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetFontWeight().has_value());
}

/**
 * @tc.name: SetFontColor001
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontColor001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontColor().has_value());
    EXPECT_EQ(itemProperty->GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: SetFontColor002
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontColor002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetFontColor(Color::RED);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetFontColor().has_value());
}

/**
 * @tc.name: SetFontColor003
 * @tc.desc: Verify SetFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontColor003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetFontColor().has_value());
    EXPECT_EQ(itemProperty->GetFontColor().value(), Color::RED);

    ViewStackProcessor::GetInstance()->Push(itemNode);
    MneuItemModelInstance.SetFontColor(std::nullopt);
    ASSERT_FALSE(itemProperty->GetFontColor().has_value());
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: SetLabelFontSize001
 * @tc.desc: Verify SetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontSize001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontSize(Dimension());
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    EXPECT_FALSE(itemProperty->GetLabelFontSize().has_value());
}

/**
 * @tc.name: SetLabelFontSize002
 * @tc.desc: Verify SetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontSize002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontSize(Dimension(40.0));
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontSize().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontSize().value(), Dimension(40.0));
}

/**
 * @tc.name: SetLabelFontSize003
 * @tc.desc: Verify SetLabelFontSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontSize003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetLabelFontSize(Dimension(40.0));
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetLabelFontSize().has_value());
}

/**
 * @tc.name: SetLabelFontWeight001
 * @tc.desc: Verify SetLabelFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontWeight001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontWeight(FontWeight::BOLD);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontWeight().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontWeight().value(), FontWeight::BOLD);
}

/**
 * @tc.name: SetLabelFontWeight002
 * @tc.desc: Verify SetLabelFontWeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontWeight002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetLabelFontWeight(FontWeight::BOLD);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetLabelFontWeight().has_value());
}

/**
 * @tc.name: SetLabelFontColor001
 * @tc.desc: Verify SetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontColor001, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontColor().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), Color::RED);
}

/**
 * @tc.name: SetLabelFontColor002
 * @tc.desc: Verify SetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontColor002, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.SetLabelFontColor(Color::RED);
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);
    ASSERT_FALSE(itemProperty->GetLabelFontColor().has_value());
}

/**
 * @tc.name: SetLabelFontColor003
 * @tc.desc: Verify SetLabelFontColor.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontColor003, TestSize.Level1)
{
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontColor(Color::RED);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_TRUE(itemProperty->GetLabelFontColor().has_value());
    EXPECT_EQ(itemProperty->GetLabelFontColor().value(), Color::RED);

    ViewStackProcessor::GetInstance()->Push(itemNode);
    MneuItemModelInstance.SetLabelFontColor(std::nullopt);
    ASSERT_FALSE(itemProperty->GetLabelFontColor().has_value());
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: SetLabelFontStyle001
 * @tc.desc: Verify SetLabelFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetLabelFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuItemModelNG object and set LabelFontStyle properties.
     */
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetLabelFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, menuItemPattern and menuItemLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps: step3. get the labelFontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step3. check whether the labelFontStyle properties is is correct.
     */
    ASSERT_TRUE(itemProperty->GetLabelItalicFontStyle().has_value());
    EXPECT_EQ(itemProperty->GetLabelItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: SetFontStyle001
 * @tc.desc: Verify SetFontStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemLayoutPropertyTestNg, SetFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuItemModelNG object and set FontStyle properties.
     */
    MenuItemModelNG MneuItemModelInstance;
    MenuItemProperties itemOption;
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, menuItemPattern and menuItemLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    /**
     * @tc.steps: step3. get the FontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step3. check whether the FontStyle properties is is correct.
     */
    ASSERT_TRUE(itemProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(itemProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}
} // namespace OHOS::Ace::NG
