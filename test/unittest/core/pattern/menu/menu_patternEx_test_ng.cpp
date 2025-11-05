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
#include "core/components_ng/layout/layout_wrapper_node.h"
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
constexpr double MENU_OFFSET_X = 10.0;
constexpr double MENU_OFFSET_Y = 10.0;
constexpr float MENU_SIZE_WIDTH = 100.0f;
constexpr float MENU_SIZE_HEIGHT = 50.0f;
} // namespace
class MenuPattern1TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuPattern1TestNg();
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

void MenuPattern1TestNg::SetUpTestCase() {}

void MenuPattern1TestNg::TearDownTestCase() {}

void MenuPattern1TestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuPattern1TestNg::TearDown()
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

void MenuPattern1TestNg::InitMenuPattern1TestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuPattern1TestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuPattern1TestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuPattern1TestNg::GetPreviewMenuWrapper(
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
 * @tc.name: MenuPatternTestNg001
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg001, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    menuPattern->RegisterOnTouch();
    EXPECT_TRUE(info.GetTouches().empty());
}

/**
 * @tc.name: MenuPatternTestNg002
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg002, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchType touchType = TouchType::UP;
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->RegisterOnTouch();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg003
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg003, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchType touchType = TouchType::UP;
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    menuPattern->RegisterOnTouch();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg004
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg004, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->RegisterOnTouch();
    EXPECT_FALSE(info.GetTouches().empty());
    EXPECT_TRUE(info.GetTouches().front().GetTouchType() == TouchType::UNKNOWN);
}

/**
 * @tc.name: MenuPatternTestNg005
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg005, TestSize.Level1)
{
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE);
    std::string type = "1";
    TouchEventInfo info(type);
    TouchType touchType = TouchType::UP;
    TouchLocationInfo locationInfo(TARGET_ID);
    locationInfo.SetTouchType(touchType);
    menuPattern->RegisterOnTouch();
    EXPECT_TRUE(info.GetTouches().empty());
    EXPECT_FALSE(info.GetTouches().front().GetTouchType() == TouchType::UP);
}

/**
 * @tc.name: MenuPatternTestNg006
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg006, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);
    MneuModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    ASSERT_TRUE(layoutProperty->GetFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(layoutProperty->GetFontWeight().has_value());
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(layoutProperty->GetFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetFontColor().value(), Color::RED);
    ASSERT_TRUE(layoutProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(layoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: MenuPatternTestNg007
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg007, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::RED);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::RED);
}

/**
 * @tc.name: MenuPatternTestNg008
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg008, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontSize(Dimension(35.0));
    MneuItemModelInstance.SetFontColor(Color::BLUE);
    MneuItemModelInstance.SetFontWeight(FontWeight::LIGHTER);
    MneuItemModelInstance.SetLabelFontSize(Dimension(40.0));
    MneuItemModelInstance.SetLabelFontColor(Color::GRAY);
    MneuItemModelInstance.SetLabelFontWeight(FontWeight::LIGHTER);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
}

/**
 * @tc.name: MenuPatternTestNg009
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg009, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemGroupView::Create();
    auto groupNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    MenuItemGroupView::Create();
    auto groupNode2 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();

    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(groupNode);
    itemNode->OnMountToParentDone();
    groupPattern->OnModifyDone();
    groupNode->MountToParent(menuNode);
    groupNode->OnMountToParentDone();
    groupNode2->MountToParent(menuNode);
    groupNode2->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::RED);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(25.0));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::RED);
}

/**
 * @tc.name: MenuPatternTestNg010
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg010, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemGroupView::Create();
    auto groupNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupNode, nullptr);
    auto groupPattern = groupNode->GetPattern<MenuItemGroupPattern>();

    MenuItemProperties itemOption;
    itemOption.content = "content";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(groupNode);
    itemNode->OnMountToParentDone();
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textNode->GetPattern<TextPattern>();
    textPattern->OnModifyDone();
    textNode->MountToParent(groupNode);
    textNode->OnMountToParentDone();
    groupPattern->OnModifyDone();
    groupNode->MountToParent(menuNode);
    groupNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_EQ(labelNode, nullptr);
}

/**
 * @tc.name: MenuPatternTestNg011
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg011, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "content";
    MneuItemModelInstance.Create(itemOption);
    MneuItemModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    // call UpdateMenuItemChildren
    menuPattern->OnModifyDone();
    itemPattern->OnModifyDone();
    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_EQ(labelNode, nullptr);
}

/**
 * @tc.name: MenuPatternTestNg012
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg012, TestSize.Level1)
{
    auto wrapperNode = MenuView::Create(CREATE_VALUE, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);
    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<MenuItemPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = CREATE_VALUE.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(u""), StringUtils::Str8ToStr16(param.text));
        if (param.icon.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.icon);
        }
    }
    std::vector<SelectParam> params;
    params.clear();
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
}

/**
 * @tc.name: MenuPatternTestNg013
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg013, TestSize.Level1)
{
    std::vector<SelectParam> params;
    auto wrapperNode = MenuView::Create(params, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    ASSERT_EQ(menuNode->GetChildren().size(), 1);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->UpdateSelectParam(CREATE_VALUE);

    ASSERT_EQ(menuPattern->GetOptions().size(), 4);
    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<MenuItemPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = CREATE_VALUE.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(u""), StringUtils::Str8ToStr16(param.text));
        if (param.icon.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.icon);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg014
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg014, TestSize.Level1)
{
    std::vector<SelectParam> params;
    auto wrapperNode = MenuView::Create(params, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);

    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
}

/**
 * @tc.name: MenuPatternTestNg015
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg015, TestSize.Level1)
{
    auto wrapperNode = MenuView::Create(CREATE_VALUE, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    menuPattern->UpdateSelectParam(CREATE_VALUE_NEW);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<MenuItemPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = CREATE_VALUE_NEW.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(u""), StringUtils::Str8ToStr16(param.text));
        if (param.icon.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.icon);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg016
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg016, TestSize.Level1)
{
    auto wrapperNode = MenuView::Create(CREATE_VALUE, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    std::vector<SelectParam> params;
    params.push_back({ "content1_new", "" });
    params.push_back({ "content2_new", "icon2_new" });
    params.push_back({ "", "" });
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 3);

    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<MenuItemPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = params.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(u""), StringUtils::Str8ToStr16(param.text));
        if (param.icon.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.icon);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg017
 * @tc.desc: Verify UpdateSelectParam.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg017, TestSize.Level1)
{
    std::vector<SelectParam> params;
    params.push_back({ "content1", "icon1" });
    params.push_back({ "content2", "" });
    params.push_back({ "", "icon3" });
    auto wrapperNode = MenuView::Create(params, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    ASSERT_EQ(menuPattern->GetOptions().size(), 3);

    menuPattern->UpdateSelectParam(CREATE_VALUE_NEW);
    ASSERT_EQ(menuPattern->GetOptions().size(), 4);

    const auto& children = menuPattern->GetOptions();
    auto childIt = children.begin();
    for (size_t i = 0; i < children.size(); i++, childIt++) {
        const auto& childNode = AceType::DynamicCast<FrameNode>(*childIt);
        ASSERT_NE(childNode, nullptr);
        auto optionPattern = childNode->GetPattern<MenuItemPattern>();
        ASSERT_NE(optionPattern, nullptr);
        ASSERT_NE(optionPattern->text_, nullptr);
        auto textProps = optionPattern->text_->GetLayoutProperty<TextLayoutProperty>();
        ASSERT_NE(textProps, nullptr);
        auto param = CREATE_VALUE_NEW.at(i);
        EXPECT_EQ(textProps->GetContent().value_or(u""), StringUtils::Str8ToStr16(param.text));
        if (param.icon.empty()) {
            ASSERT_EQ(optionPattern->icon_, nullptr);
        } else {
            ASSERT_NE(optionPattern->icon_, nullptr);
            auto imageProps = optionPattern->icon_->GetLayoutProperty<ImageLayoutProperty>();
            ASSERT_NE(imageProps, nullptr);
            auto imageSrcInfo = imageProps->GetImageSourceInfo();
            ASSERT_TRUE(imageSrcInfo.has_value());
            ASSERT_EQ(imageSrcInfo->GetSrc(), param.icon);
        }
    }
}

/**
 * @tc.name: MenuPatternTestNg018
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg018, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MneuModelInstance.Create();
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
    std::vector<SelectParam> params;
    params.push_back({ "content1", "icon1" });
    menuPattern->UpdateSelectParam(params);
    ASSERT_EQ(menuPattern->GetOptions().size(), 0);
}

/**
 * @tc.name: MenuPatternTestNg019
 * @tc.desc: Test MultiMenu and outer Menu container.
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg019, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    MenuModelNG model;
    model.Create();
    auto multiMenu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto menuWrapper = MenuView::Create(multiMenu, -1, EMPTY_TEXT);
    ASSERT_NE(menuWrapper, nullptr);
    auto outerMenu = AceType::DynamicCast<FrameNode>(menuWrapper->GetFirstChild());
    ASSERT_NE(outerMenu, nullptr);

    // backgroundColor should be reset
    ASSERT_EQ(outerMenu->GetRenderContext()->GetBackgroundColorValue(), Color::TRANSPARENT);

    // padding should be moved to inner multi menu
    auto scroll = AceType::DynamicCast<FrameNode>(outerMenu->GetFirstChild());
    ASSERT_NE(scroll, nullptr);
    auto&& padding = scroll->GetLayoutProperty()->GetPaddingProperty();
    // should have empty padding
    ASSERT_EQ(padding->ToString(), PaddingProperty().ToString());

    multiMenu->GetPattern()->BeforeCreateLayoutWrapper();
    // inner multi menu should have backgroundColor and padding set up
    ASSERT_NE(multiMenu->GetLayoutProperty()->GetPaddingProperty()->ToString(), PaddingProperty().ToString());
    ASSERT_NE(multiMenu->GetRenderContext()->GetBackgroundColor(), Color::TRANSPARENT);
    // inner menu should have no shadow
    ASSERT_EQ(multiMenu->GetRenderContext()->GetBackShadow(), ShadowConfig::NoneShadow);

    // MultiMenu should have its own layout algorithm
    auto layoutAlgorithm = multiMenu->GetPattern<MenuPattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(AceType::DynamicCast<MultiMenuLayoutAlgorithm>(layoutAlgorithm), nullptr);
}

/**
 * @tc.name: MenuPatternTestNg020
 * @tc.desc: Verify UpdateMenuItemChildren.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuModelNG and MenuItemModelNG object and set FontStyle properties of MenuModelNG.
     */
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, MenuPattern and MenuLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. not set FontStyle properties of MenuModelNG.
     */
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();

    /**
     * @tc.steps: step4. call OnModifyDone of MenuPattern to call UpdateMenuItemChildren
     */
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step5. get the FontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step5. check whether the FontStyle properties is is correct.
     */
    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(textProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: MenuPatternTest021
 * @tc.desc: Verify RegisterOnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg021, TestSize.Level1)
{
    MenuPattern* menuPattern = new MenuPattern(TARGET_ID, "", TYPE);
    const std::string tag = "tag";
    int32_t nodeId = 1;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    bool isRoot = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    const RefPtr<LayoutWrapperNode> layoutWrapper;
    std::string type = "1";
    TouchEventInfo info(type);
    TouchType touchType = TouchType::UP;
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset globalLocation(1, 1);
    locationInfo.SetTouchType(touchType);
    auto touchLocationInfo = locationInfo.SetGlobalLocation(globalLocation);
    info.touches_.emplace_back(touchLocationInfo);
    menuPattern->OnTouchEvent(info);
    menuPattern->RegisterOnTouch();
    KeyEvent keyEvent(KeyCode::KEY_ESCAPE, KeyAction::UP);
    EXPECT_FALSE(menuPattern->IsMultiMenu());
    EXPECT_FALSE(menuPattern->OnKeyEvent(keyEvent));
    menuPattern->HideMenu();
    menuPattern->HideSubMenu();
    EXPECT_FALSE(menuPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap));
    menuPattern->type_ = MenuType::SUB_MENU;
    EXPECT_FALSE(menuPattern->OnKeyEvent(keyEvent));
    menuPattern->HideMenu();
    menuPattern->HideSubMenu();
    menuPattern->RemoveParentHoverStyle();
    delete menuPattern;
    menuPattern = nullptr;
}

/**
 * @tc.name: MenuPatternTestNg022
 * @tc.desc: Verify OnTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. multi menu touch event
     * @tc.expected: menu type is multi
     */
    auto multiMenuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    TouchEventInfo multiMenuTouchEventInfo(MENU_TOUCH_EVENT_TYPE);
    multiMenuPattern->OnTouchEvent(multiMenuTouchEventInfo);
    EXPECT_TRUE(multiMenuPattern->IsMultiMenu());
    /**
     * @tc.steps: step2. select menu touch event
     * @tc.expected: menu options nums as expected
     */
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "content", "icon" });
    auto selectWrapperNode = MenuView::Create(selectParams, TARGET_ID, EMPTY_TEXT);
    ASSERT_NE(selectWrapperNode, nullptr);
    auto selectMenuNode = AceType::DynamicCast<FrameNode>(selectWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(selectMenuNode, nullptr);
    TouchEventInfo selectMenuEventInfo(MENU_TOUCH_EVENT_TYPE);
    auto selectMenuPattern = selectMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(selectMenuPattern, nullptr);
    selectMenuPattern->OnTouchEvent(selectMenuEventInfo);
    ASSERT_EQ(selectMenuPattern->GetOptions().size(), 1);
    /**
     * @tc.steps: step3. contextMenu touch event
     * @tc.expected: menu type is context
     */
    auto contextMenuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::CONTEXT_MENU);
    // excute touch down event
    TouchEventInfo contextMenuTouchDownEventInfo(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo downLocationInfo(TARGET_ID);
    Offset touchDownGlobalLocation(1, 1);
    downLocationInfo.SetTouchType(TouchType::DOWN);
    auto touchDownLocationInfo = downLocationInfo.SetGlobalLocation(touchDownGlobalLocation);
    contextMenuTouchDownEventInfo.touches_.emplace_back(touchDownLocationInfo);
    contextMenuPattern->OnTouchEvent(contextMenuTouchDownEventInfo);
    // execute touch up event
    TouchEventInfo contextMenuTouchUpEventInfo(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo upLocationInfo(TARGET_ID);
    Offset touchUpGlobalLocation(3, 3);
    upLocationInfo.SetTouchType(TouchType::UP);
    auto touchUpLocationInfo = upLocationInfo.SetGlobalLocation(touchUpGlobalLocation);
    contextMenuTouchUpEventInfo.touches_.emplace_back(touchUpLocationInfo);
    contextMenuPattern->OnTouchEvent(contextMenuTouchUpEventInfo);
    EXPECT_TRUE(contextMenuPattern->IsContextMenu());
}

/**
 * @tc.name: MenuPatternTestNg023
 * @tc.desc: Verify OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu wrapper
     * @tc.expected: wrapper node is not null and has 1 child
     */
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
    /**
     * @tc.steps: step2. execute OnKeyEvent
     * @tc.expected: result as expected
     */
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    menuPattern->type_ = MenuType::SUB_MENU;
    KeyEvent escapeKeyEvent(KeyCode::KEY_ESCAPE, KeyAction::DOWN);
    EXPECT_TRUE(menuPattern->OnKeyEvent(escapeKeyEvent));
    KeyEvent upKeyEvent(KeyCode::KEY_PLUS, KeyAction::DOWN);
    EXPECT_FALSE(menuPattern->OnKeyEvent(upKeyEvent));
}

/**
 * @tc.name: MenuPatternTestNg024
 * @tc.desc: Verify RemoveParentHoverStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuItem and menu
     * @tc.expected: menuItem not null
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU);
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuItemPattern);
    ASSERT_NE(menuItem, nullptr);
    /**
     * @tc.steps: step2. execute RemoveParentHoverStyle
     * @tc.expected: item IsSubMenuShowed as expected
     */
    menuPattern->SetParentMenuItem(menuItem);
    menuPattern->RemoveParentHoverStyle();
    auto itemPattern = menuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    EXPECT_FALSE(itemPattern->IsSubMenuShowed());
    menuPattern->type_ = MenuType::SUB_MENU;
    menuPattern->RemoveParentHoverStyle();
    EXPECT_FALSE(itemPattern->IsSubMenuShowed());
}

/**
 * @tc.name: MenuPatternTestNg025
 * @tc.desc: Verify MenuPattern::HideStackExpandMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MENU_ETS_TAG child and mount to a menuwrapper;
     * @tc.expected: menu is not sub menu.
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(2, "", MenuType::MENU));
    menuNode->GetGeometryNode()->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    menuNode->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    mainMenu->MountToParent(wrapperNode);
    menuNode->MountToParent(mainMenu);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    auto layoutProps = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    layoutProps->UpdateExpandingMode(SubMenuExpandingMode::STACK);
    menuPattern->HideStackExpandMenu(OffsetF(0.0f, 0.0f));
    EXPECT_FALSE(menuPattern->IsSubMenu());
    /**
     * @tc.steps: step1+. make menu change sub menu.
     */
    menuPattern->type_ = MenuType::SUB_MENU;
    menuPattern->HideStackExpandMenu(OffsetF(0.0f, 0.0f));
    EXPECT_TRUE(menuPattern->IsSubMenu());
    /**
     * @tc.steps: step1+. make menu change sub menu.
     */
    bool testResult = menuPattern->HideStackExpandMenu(OffsetF(0.0f, 0.0f));
    EXPECT_FALSE(testResult);
}

/**
 * @tc.name: MenuPatternTestNg026
 * @tc.desc: Verify HideSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu wrapper
     * @tc.expected: wrapper node is not null and has 1 child
     */
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
    /**
     * @tc.steps: step2. execute HideSubMenu
     * @tc.expected: result as expected
     */
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, menuItemPattern);
    menuPattern->SetParentMenuItem(menuItem);
    menuPattern->type_ = MenuType::SUB_MENU;
    menuPattern->SetShowedSubMenu(menuNode);
    menuPattern->HideSubMenu();
    auto itemPattern = menuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    EXPECT_FALSE(itemPattern->IsSubMenuShowed());
    ASSERT_EQ(menuPattern->GetShowedSubMenu(), nullptr);
}

/**
 * @tc.name: MenuPatternTestNg027
 * @tc.desc: Verify GetMenuWrapper,GetMainMenuPattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu wrapper and menu
     * @tc.expected: wrapper node is not null and has 1 child
     */
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    /**
     * @tc.steps: step2. create child to menu, execute GetMenuWrapper,GetMainMenuPattern,GetInnerMenuCount
     * @tc.expected: result as expected
     */
    auto multiMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MULTI_MENU));
    multiMenu->MountToParent(menuNode);
    auto multiPattern = multiMenu->GetPattern<MenuPattern>();
    ASSERT_NE(multiPattern, nullptr);
    ASSERT_NE(multiPattern->GetMenuWrapper(), nullptr);
    ASSERT_NE(multiPattern->GetMainMenuPattern(), nullptr);
    EXPECT_EQ(multiPattern->GetInnerMenuCount(), 0);
    /**
     * @tc.steps: step3. create cascade node
     * @tc.expected: wrapper node relate to child node pattern is null
     */
    auto singleMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MULTI_MENU));
    auto singleParentMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(2, "", MenuType::MENU));
    singleMenu->MountToParent(singleParentMenu);
    auto singleMenuPattern = singleMenu->GetPattern<MenuPattern>();
    ASSERT_EQ(singleMenuPattern->GetMenuWrapper(), nullptr);
}

/**
 * @tc.name: MenuPatternTestNg028
 * @tc.desc: Verify some condition in api 11.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set current api 11, create menu wrapper and menu
     * @tc.expected: menu blurStyle meet expectations
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. create option pattern.
     * @tc.expected: option bg color meet expectations
     */
    auto optionPattern = AceType::MakeRefPtr<MenuItemPattern>(true, 0);
    optionPattern->AttachToFrameNode(menuNode);
    ASSERT_NE(optionPattern, nullptr);
    EXPECT_EQ(optionPattern->GetBgColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: MenuPatternTestNg029
 * @tc.desc: Verify UpdateFontStyle.menuProperty has FontFamily.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MenuModelNG and MenuItemModelNG object and set FontStyle properties of MenuModelNG.
     */
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontStyle(Ace::FontStyle::ITALIC);

    /**
     * @tc.steps: step2. get the frameNode, MenuPattern and MenuLayoutProperty.
     * @tc.expected: step2. check whether the objects is available.
     */
    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProperty = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. not set FontStyle properties of MenuModelNG.
     */
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MneuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto menuItemLayoutProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuItemLayoutProperty, nullptr);
    itemPattern->OnModifyDone();
    itemNode->MountToParent(menuNode);
    itemNode->OnMountToParentDone();
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step4. call OnModifyDone of MenuPattern to call UpdateMenuItemChildren
     */
    menuItemLayoutProperty->UpdateLabelItalicFontStyle(Ace::FontStyle::ITALIC);
    layoutProperty->UpdateFontFamily(FONT_FAMILY_VALUE);
    menuPattern->OnModifyDone();

    /**
     * @tc.steps: step5. get the FontStyle properties of menuItemLayoutProperty.
     * @tc.expected: step5. check whether the FontStyle properties is is correct.
     */
    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetItalicFontStyle().has_value());
    EXPECT_EQ(textProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
}
/**
 * @tc.name: MenuPatternTestNg030
 * @tc.desc: Verify OnTouchEvent.Extend.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. multi menu touch event,IsMultiMenu,is ture.
     * @tc.expected: menu type is multi
     */
    auto multiMenuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    TouchEventInfo multiMenuTouchEventInfo(MENU_TOUCH_EVENT_TYPE);
    multiMenuPattern->SetType(MenuType::DESKTOP_MENU);
    multiMenuPattern->OnTouchEvent(multiMenuTouchEventInfo);
    EXPECT_FALSE(multiMenuPattern->IsMultiMenu());
    /**
     * @tc.steps: step2. select menu touch event,IsDesktopMenu is true
     * @tc.expected: menu options nums as expected
     */
    multiMenuPattern->SetType(MenuType::DESKTOP_MENU);
    multiMenuPattern->OnTouchEvent(multiMenuTouchEventInfo);
    EXPECT_TRUE(multiMenuPattern->IsDesktopMenu());
    /**
     * @tc.steps: step3. contextMenu touch event
     * @tc.expected: menu type is context
     */
    multiMenuPattern->type_ = MenuType::SELECT_OVERLAY_CUSTOM_MENU;
    multiMenuPattern->OnTouchEvent(multiMenuTouchEventInfo);
    EXPECT_TRUE(multiMenuPattern->IsSelectOverlayCustomMenu());
}
/**
 * @tc.name: MenuPatternTestNg031
 * @tc.desc: Verify HideMenu(Menu).menunode is SELECT.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    menuPattern->type_ = MenuType::CONTEXT_MENU;

    menuPattern->HideMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);
}
/**
 * @tc.name: MenuPatternTestNg032
 * @tc.desc: Verify HideMenu(Menu).wrappernode is SELECT_OVERLAY.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern1TestNg, MenuPatternTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create wrapper and child menu
     * @tc.expected: wrapper pattern not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::SELECT_OVERLAY_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    menuPattern->type_ = MenuType::CONTEXT_MENU;

    menuPattern->HideMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);
}
} // namespace OHOS::Ace::NG
