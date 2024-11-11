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
#include "test/mock/core/common/mock_container.h"
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
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuItemPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuItemPatternTestNg();
    void InitMenuItemTestNg();
    void MockPipelineContextGetTheme();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuItemPatternTestNg::SetUpTestCase() {}

void MenuItemPatternTestNg::TearDownTestCase() {}

void MenuItemPatternTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuItemPatternTestNg::MockPipelineContextGetTheme()
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
        } else {
            return AceType::MakeRefPtr<MenuTheme>();
        }
    });
}

void MenuItemPatternTestNg::TearDown()
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

void MenuItemPatternTestNg::InitMenuItemPatternTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuItemPatternTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemPatternTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemPatternTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: MenuItemPatternTestNgAddSelectIcon001
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon001, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelectIcon(false);
    MenuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    MenuItemModelInstance.SetSelected(true);
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

    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon002
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon002, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelectIcon(true);
    MenuItemModelInstance.SetSelectIconSrc("");
    MenuItemModelInstance.SetSelected(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 1u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<TextTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<MenuTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon003
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon003, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelectIcon(true);
    MenuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    MenuItemModelInstance.SetSelected(false);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 1u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<TextTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<MenuTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
    EXPECT_EQ(selectIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = selectIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = selectIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
}

/**
 * @tc.name: MenuItemPatternTestNgAddSelectIcon004
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgAddSelectIcon004, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelectIcon(true);
    MenuItemModelInstance.SetSelectIconSrc("selectIcon.png");
    MenuItemModelInstance.SetSelected(false);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 1u);
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));
    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillOnce(Return(AceType::MakeRefPtr<TextTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<IconTheme>()))
        .WillOnce(Return(AceType::MakeRefPtr<MenuTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
    EXPECT_EQ(selectIconNode->GetTag(), V2::IMAGE_ETS_TAG);

    itemProperty->UpdateSelectIcon(false);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    // call AddSelectIcon
    itemPattern->OnModifyDone();
    ASSERT_EQ(leftRow->GetChildren().size(), 0u);
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateIcon001
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateIcon001, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.startIcon = ImageSourceInfo(IMAGE_SRC_URL);
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto startIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(startIconNode, nullptr);
    EXPECT_EQ(startIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = startIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = startIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateIcon002
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateIcon002, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.endIcon = ImageSourceInfo(IMAGE_SRC_URL);
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto endIconNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(endIconNode, nullptr);
    EXPECT_EQ(endIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = endIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = endIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), IMAGE_SRC_URL);

    itemProperty->UpdateEndIcon(ImageSourceInfo(IMAGE_SRC_URL));
    // call UpdateIcon
    itemPattern->OnModifyDone();
    imagePattern = endIconNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imageLayoutProperty = endIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), IMAGE_SRC_URL);
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateIcon003
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateIcon003, TestSize.Level1)
{
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.endIcon = ImageSourceInfo(IMAGE_SRC_URL);
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateIcon
    itemPattern->UpdateIcon(leftRow, false);
    itemPattern->UpdateDisabledStyle();
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateText001
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateText
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto contentNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    EXPECT_EQ(contentNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), "content");
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateText002
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    // call UpdateText
    itemPattern->OnModifyDone();

    EXPECT_EQ(leftRow->GetChildren().size(), 0u);
    ASSERT_EQ(rightRow->GetChildren().size(), 1u);
    auto labelNode = AceType::DynamicCast<FrameNode>(rightRow->GetChildAtIndex(0));
    ASSERT_NE(labelNode, nullptr);
    EXPECT_EQ(labelNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), "label");
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateText003
 * @tc.desc: Verify update text when item is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText003, TestSize.Level1)
{
    // mock theme
    MockPipelineContextGetTheme();
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();

    // create menu item
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.startIcon = ImageSourceInfo(IMAGE_SRC_URL);
    itemOption.content = "item content";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemEventHub = itemNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(itemEventHub, nullptr);
    itemEventHub->SetEnabled(false);
    // update item
    itemPattern->OnModifyDone();

    EXPECT_FALSE(itemEventHub->IsEnabled());
    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 2u);
    auto startIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(startIconNode, nullptr);
    EXPECT_EQ(startIconNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = startIconNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
    EXPECT_EQ(sourceInfo.value().GetSrc(), IMAGE_SRC_URL);

    auto contentNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(1));
    ASSERT_NE(contentNode, nullptr);
    EXPECT_EQ(contentNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), "item content");
    auto textRenderContext = contentNode->GetRenderContext();
    EXPECT_EQ(textRenderContext->GetOpacity(), selectTheme->GetDisabledFontColorAlpha());
}

/**
 * @tc.name: MenuItemPatternTestNgUpdateText004
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.labelInfo = "label";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemProperty = itemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(itemProperty, nullptr);

    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    auto rightRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(1));

    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    // call UpdateText
    itemPattern->UpdateText(leftRow, layoutProp, true);
    itemPattern->UpdateDisabledStyle();
}

HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNgUpdateText005, TestSize.Level1)
{
    // mock theme
    MockPipelineContextGetTheme();
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();

    // create menu item
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.startIcon = ImageSourceInfo(IMAGE_SRC_URL);
    itemOption.content = "item content";
    MenuItemModelInstance.Create(itemOption);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto itemEventHub = itemNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(itemEventHub, nullptr);
    itemEventHub->SetEnabled(false);
    // update item
    itemPattern->OnModifyDone();

    EXPECT_FALSE(itemEventHub->IsEnabled());
    ASSERT_EQ(itemNode->GetChildren().size(), 2u);
    auto leftRow = AceType::DynamicCast<FrameNode>(itemNode->GetChildAtIndex(0));
    EXPECT_EQ(leftRow->GetChildren().size(), 2u);

    auto itemRenderContext = itemNode->GetRenderContext();
    itemRenderContext->UpdateForegroundColor(selectTheme->GetDisabledMenuFontColor());

    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    // call UpdateText
    itemPattern->UpdateText(leftRow, layoutProp, false);
}

/**
 * @tc.name: MenuItemPatternTestEvent001
 * @tc.desc: Test Click Event
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    MenuItemModelInstance.Create(itemOption);
    MenuItemModelInstance.SetSelected(true);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto itemPattern = itemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(itemPattern, nullptr);
    auto gestureHub = itemNode->GetOrCreateGestureEventHub();
    auto clickEventActuator = gestureHub->clickEventActuator_;
    ASSERT_NE(clickEventActuator, nullptr);
    auto event = clickEventActuator->GetClickEvent();
    ASSERT_NE(event, nullptr);

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: isSelected_ is false.
     */
    GestureEvent gestureEvent;
    event(gestureEvent);
    EXPECT_FALSE(itemPattern->isSelected_);
}

/**
 * @tc.name: CustomMenuItemPattern001
 * @tc.desc: Test CustomMenuItem creation
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, CustomMenuItemPattern001, TestSize.Level1)
{
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(itemNode->GetEventHub<EventHub>());
    auto touch = itemNode->GetOrCreateGestureEventHub()->touchEventActuator_;
    ASSERT_TRUE(touch);
    ASSERT_FALSE(touch->touchEvents_.empty());
}

/**
 * @tc.name: CustomMenuItemPattern002
 * @tc.desc: Test CustomMenuItem OnTouch
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, CustomMenuItemPattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);

    pattern->lastTouchOffset_ = nullptr;
    /**
     * @tc.steps: step2. execute OnTouch
     * @tc.expected: result as expected
     */
    // execute touch down event
    TouchEventInfo info(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo locationInfo(TARGET_ID);
    Offset location(1, 1);
    locationInfo.SetTouchType(TouchType::DOWN);
    locationInfo.SetLocalLocation(location);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);

    info.touches_.pop_front();
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);

    pattern->lastTouchOffset_ = std::make_unique<Offset>(Offset(1, 0));
    info.touches_.pop_front();
    locationInfo.SetTouchType(TouchType::UP);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);

    info.touches_.pop_front();
    locationInfo.SetTouchType(TouchType::CANCEL);
    info.touches_.emplace_back(locationInfo);
    pattern->OnTouch(info);
    EXPECT_EQ(info.touches_.size(), 1);
}

/**
 * @tc.name: CustomMenuItemPattern003
 * @tc.desc: Test CustomMenuItem OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, CustomMenuItemPattern003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. execute OnKeyEvent
     * @tc.expected: result as expected
     */
    KeyEvent keyEvent(KeyCode::KEY_ESCAPE, KeyAction::DOWN);
    auto ret = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(ret);

    keyEvent.code = KeyCode::KEY_ENTER;
    ret = pattern->OnKeyEvent(keyEvent);
    EXPECT_TRUE(ret);

    keyEvent.action = KeyAction::UP;
    ret = pattern->OnKeyEvent(keyEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: MenuItemPatternTestNg001
 * @tc.desc: Verify GetMenuWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    /**
     * @tc.steps: step2. execute GetMenuWrapper
     * @tc.expected: result as expected
     */
    ASSERT_EQ(menuItemPattern->GetMenuWrapper(), nullptr);
    menuItemNode->MountToParent(wrapperNode);
    ASSERT_NE(menuItemPattern->GetMenuWrapper(), nullptr);
    wrapperNode->RemoveChildAtIndex(0);
    EXPECT_EQ(wrapperNode->GetChildren().size(), 0);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    ASSERT_NE(menuItemPattern->GetMenuWrapper(), nullptr);
}

/**
 * @tc.name: MenuItemPatternTestNg002
 * @tc.desc: Verify ShowSubMenu, CloseMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition
     * @tc.expected: wrapper and child pattern is not null
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    /**
     * @tc.steps: step2. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    menuItemPattern->ShowSubMenu();
    menuItemPattern->CloseMenu();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 2);
}

/**
 * @tc.name: MenuItemPatternTestNg004
 * @tc.desc: Verify OnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create item node
     * @tc.expected: pattern is not null
     */
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    /**
     * @tc.steps: step2. execute OnTouch
     * @tc.expected: result as expected
     */
    // execute touch down event
    TouchEventInfo itemTouchDownEventInfo(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo downLocationInfo(TARGET_ID);
    Offset touchDownGlobalLocation(1, 1);
    downLocationInfo.SetTouchType(TouchType::DOWN);
    auto touchDownLocationInfo = downLocationInfo.SetGlobalLocation(touchDownGlobalLocation);
    itemTouchDownEventInfo.touches_.emplace_back(touchDownLocationInfo);
    menuItemPattern->OnTouch(itemTouchDownEventInfo);
    EXPECT_EQ(itemTouchDownEventInfo.touches_.size(), 1);
    // excute touch up event
    TouchEventInfo itemTouchUpEventInfo(MENU_TOUCH_EVENT_TYPE);
    TouchLocationInfo upLocationInfo(TARGET_ID);
    Offset touchUpGlobalLocation(3, 3);
    upLocationInfo.SetTouchType(TouchType::UP);
    auto touchUpLocationInfo = upLocationInfo.SetGlobalLocation(touchUpGlobalLocation);
    itemTouchUpEventInfo.touches_.emplace_back(touchUpLocationInfo);
    menuItemPattern->OnTouch(itemTouchUpEventInfo);
    EXPECT_EQ(itemTouchUpEventInfo.touches_.size(), 1);
    // excute touch move event
    upLocationInfo.SetTouchType(TouchType::MOVE);
    touchUpLocationInfo = upLocationInfo.SetGlobalLocation(touchUpGlobalLocation);
    itemTouchUpEventInfo.touches_.clear();
    itemTouchUpEventInfo.touches_.emplace_back(touchUpLocationInfo);
    menuItemPattern->OnTouch(itemTouchUpEventInfo);
    EXPECT_EQ(itemTouchUpEventInfo.touches_.size(), 1);
}

/**
 * @tc.name: MenuItemPatternTestNg005
 * @tc.desc: Verify OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg005, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->OnHover(true);
    menuItemPattern->OnHover(false);
    EXPECT_EQ(menuItemPattern->GetBgBlendColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: MenuItemPatternTestNg006
 * @tc.desc: Verify OnKeyEvent,PlayBgColorAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create item node
     * @tc.expected: pattern is not null
     */
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    /**
     * @tc.steps: step2. update event type, excute OnKeyEvent
     * @tc.expected: result as expected
     */
    // use longPressEvent
    KeyEvent longPressEvent(KeyCode::KEY_ESCAPE, KeyAction::LONG_PRESS);
    EXPECT_FALSE(menuItemPattern->OnKeyEvent(longPressEvent));
    // use enterEvent
    KeyEvent enterEvent(KeyCode::KEY_ENTER, KeyAction::DOWN);
    EXPECT_TRUE(menuItemPattern->OnKeyEvent(enterEvent));
    // use rightEvent
    KeyEvent rightEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    std::function<void()> buildFun = []() {};
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    EXPECT_TRUE(menuItemPattern->OnKeyEvent(rightEvent));
    // use fnEvent
    KeyEvent fnEvent(KeyCode::KEY_FN, KeyAction::DOWN);
    menuItemPattern->PlayBgColorAnimation(false);
    menuItemPattern->PlayBgColorAnimation(true);
    EXPECT_FALSE(menuItemPattern->OnKeyEvent(fnEvent));
}

/**
 * @tc.name: MenuItemPatternTestNg007
 * @tc.desc: Verify RegisterWrapperMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg007, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->RegisterWrapperMouseEvent();
    EXPECT_EQ(wrapperNode->GetChildren().size(), 1);
}

/**
 * @tc.name: MenuItemPatternTestNg008
 * @tc.desc: Verify AddSelfHoverRegion, IsInHoverRegions.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg008, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    menuItemPattern->AddSelfHoverRegion(mainMenu);
    EXPECT_EQ(menuItemPattern->hoverRegions_.size(), 1);
    EXPECT_TRUE(menuItemPattern->IsInHoverRegions(40, 40));
    EXPECT_FALSE(menuItemPattern->IsInHoverRegions(200, 200));
}

/**
 * @tc.name: MenuItemPatternTestNg009
 * @tc.desc: Verify AddSelfHoverRegion.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg009, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    auto position = menuItemPattern->GetSubMenuPosition(mainMenu);
    EXPECT_EQ(position, OffsetF(100, 0));
}

/**
 * @tc.name: MenuItemPatternTestNg010
 * @tc.desc: Verify submenu layout when the layering parameter is true.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menuWrapperNode and menuNodes.
     * @tc.expected: menuWrapperNode and menuNode are not null.
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::CONTEXT_MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    /**
     * @tc.steps: step2. Set sub menu shown and createLayoutAlgorithm.
     * @tc.expected: algorithm is not null.
     */
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(subMenuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);

    /**
     * @tc.cases: case1. the hierarchicalParameter is true.
     * @tc.expected: algorithm is not null and sub menu show correctly.
     */
    algorithm->canExpandCurrentWindow_ = true;
    subMenuPattern->SetParentMenuItem(menuItemNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->Layout(wrapper);
    ASSERT_TRUE(algorithm);

    // @tc.cases: case1. sub menu show on the right side of item
    algorithm->position_ = OffsetF(MENU_OFFSET_X + MENU_ITEM_SIZE_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(), 0);

    // @tc.cases: case2. sub menu show on the left side of item
    algorithm->position_ = OffsetF(FULL_SCREEN_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(), 0);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetY(), 0);
}

/**
 * @tc.name: MenuItemPatternTestNg011
 * @tc.desc: Verify submenu layout when the layering parameter is false.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menuWrapperNode and menuNodes.
     * @tc.expected: menuWrapperNode and menuNode are not null.
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::CONTEXT_MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    /**
     * @tc.steps: step2. Set sub menu shown and createLayoutAlgorithm.
     * @tc.expected: algorithm is not null.
     */
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(subMenuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);

    /**
     * @tc.cases: case1. the hierarchicalParameter is false.
     * @tc.expected: algorithm is not null and sub menu show correctly.
     */
    algorithm->canExpandCurrentWindow_ = false;
    subMenuPattern->SetParentMenuItem(menuItemNode);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->Layout(wrapper);
    ASSERT_TRUE(algorithm);

    // @tc.cases: case1. sub menu show on the right side of item
    algorithm->position_ = OffsetF(MENU_OFFSET_X + MENU_ITEM_SIZE_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(), 0);

    // @tc.cases: case2. sub menu show on the left side of item
    algorithm->position_ = OffsetF(FULL_SCREEN_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(), 0);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetY(), 0);
}
/**
 * @tc.name: MenuItemPatternTestNg012
 * @tc.desc: Verify HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg012, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
}
/**
 * @tc.name: MenuItemPatternTestNg013
 * @tc.desc: Verify HandleBlurEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg013, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    auto RenderContext = menuItemNode->GetRenderContext();
}
/**
 * @tc.name: MenuItemPatternTestNg014
 * @tc.desc: Verify InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg014, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
}
/**
 * @tc.name: MenuItemPatternTestNg015
 * @tc.desc: Verify GetShadowFromTheme.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg015, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(wrapperNode);
    wrapperNode->RemoveChildAtIndex(0);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    menuItemPattern->OnClick();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->OnClick();
}
/**
 * @tc.name: MenuItemPatternTestNg016
 * @tc.desc: Verify ShowSubMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg016, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
    menuItemPattern->ShowSubMenu();
    menuItemPattern->isSubMenuShowed_ = false;
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->ShowSubMenu();
}
/**
 * @tc.name: MenuItemPatternTestNg017
 * @tc.desc: Verify AddClickableArea.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition
     * @tc.expected: wrapper and child pattern is not null
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->AddClickableArea();
}
/**
 * @tc.name: MenuItemPatternTestNg018
 * @tc.desc: Verify FindTouchedEmbeddedMenuItem.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition
     * @tc.expected: wrapper and child pattern is not null
     */
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->FindTouchedEmbeddedMenuItem(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->isStackSubmenuHeader_ = true;
    menuItemPattern->OnClick();
    menuItemPattern->isExpanded_ = true;
    menuItemPattern->embeddedMenu_ = mainMenu;
    menuItemPattern->FindTouchedEmbeddedMenuItem(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
}

/**
 * @tc.name: MenuItemPatternTestNg019
 * @tc.desc: Verify OnClick().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg019, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuItemEventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(menuItemEventHub, nullptr);

    bool isSelected = true;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    menuItemEventHub->SetSelectedChangeEvent(changeEvent);
    menuItemEventHub->SetOnChange(changeEvent);
    menuItemPattern->OnClick();
}

/**
 * @tc.name: MenuItemPatternTestNg020
 * @tc.desc: Verify OnAfterModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg020, TestSize.Level1)
{
    auto mainMenu =FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    ASSERT_NE(subMenu, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    menuItemNode->MountToParent(mainMenu);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->OnAfterModifyDone();
    EXPECT_FALSE(menuItemPattern->isSelected_);
}

/**
 * @tc.name: MenuItemPatternTestNg021
 * @tc.desc: Verify UpdateSubmenuExpandingMode.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg021, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemPattern>();
    ASSERT_NE(menuItemGroupPattern, nullptr);
    RefPtr<NG::UINode> footerNode;
    footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    footerNode->tag_ = "V2::MENU_ETS_TAG";
    menuItemGroupPattern->UpdateSubmenuExpandingMode(footerNode);
    EXPECT_FALSE(menuItemGroupPattern->isSelected_);
}

/**
 * @tc.name: MenuItemPatternTestNg022
 * @tc.desc: Verify OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg022, TestSize.Level1)
{
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuItemEventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(menuItemEventHub, nullptr);

    menuItemPattern->onClickAIMenuItem_ = []() {
        return FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    };
    bool isSelected = true;
    auto changeEvent = [&isSelected](bool select) { isSelected = select; };
    menuItemEventHub->SetSelectedChangeEvent(changeEvent);
    menuItemEventHub->SetOnChange(changeEvent);
    menuItemPattern->OnClick();
    EXPECT_FALSE(menuItemPattern->isStackSubmenuHeader_);
}

/**
 * @tc.name: MenuItemPatternTestNg023
 * @tc.desc: Verify OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg023, TestSize.Level1)
{
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    ASSERT_NE(subMenu, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto subMenuParent = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(subMenuParent, nullptr);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->FindTouchedEmbeddedMenuItem(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuItemPattern->OnClick();
    menuItemPattern->isExpanded_ = true;
    menuItemPattern->embeddedMenu_ = mainMenu;
    menuItemPattern->FindTouchedEmbeddedMenuItem(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    EXPECT_FALSE(menuItemPattern->isStackSubmenuHeader_);
}

/**
 * @tc.name: MenuItemPatternTestNg024
 * @tc.desc: Verify OnVisibleChange().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg024, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    menuItemNode->MountToParent(mainMenu);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    // menuItemPattern->tag_ = "V2::MENU_ITEM_GROUP_ETS_TAG";
    menuItemPattern->OnVisibleChange(true);
    menuItemPattern->OnVisibleChange(false);
    EXPECT_EQ(menuItemPattern->GetBgBlendColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: MenuItemPatternTestNg025
 * @tc.desc: Verify OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create item node
     * @tc.expected: pattern is not null
     */
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    /**
     * @tc.steps: step2. update event type, excute OnKeyEvent
     * @tc.expected: result as expected
     */
    // use longPressEvent
    KeyEvent longPressEvent(KeyCode::KEY_ESCAPE, KeyAction::LONG_PRESS);
    EXPECT_FALSE(menuItemPattern->OnKeyEvent(longPressEvent));
    // use enterEvent
    KeyEvent enterEvent(KeyCode::KEY_ENTER, KeyAction::DOWN);
    EXPECT_TRUE(menuItemPattern->OnKeyEvent(enterEvent));
    // use rightEvent
    KeyEvent rightEvent(KeyCode::KEY_DPAD_RIGHT, KeyAction::DOWN);
    std::function<void()> buildFun = []() {};
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    EXPECT_TRUE(menuItemPattern->OnKeyEvent(rightEvent));
    menuItemPattern->SetIsSubMenuShowed(true);
    EXPECT_FALSE(menuItemPattern->OnKeyEvent(rightEvent));
    menuItemPattern->SetSubBuilder(nullptr);
    menuItemPattern->SetIsSubMenuShowed(true);
    EXPECT_FALSE(menuItemPattern->OnKeyEvent(rightEvent));
}

/**
 * @tc.name: MenuItemPatternTestNg026
 * @tc.desc: Verify RegisterWrapperMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg026, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->RegisterWrapperMouseEvent();
    EXPECT_EQ(menuItemNode->GetChildren().size(), 0);
}

/**
 * @tc.name: MenuItemPatternTestNg027
 * @tc.desc: Verify AddClickableArea.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition
     * @tc.expected: wrapper and child pattern is not null
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    std::function<void()> buildFun = []() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
    };
    auto wrapperNode =FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(wrapperNode, nullptr);
    auto mainMenu =FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    ASSERT_NE(subMenu, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto subMenuParent = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 5, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(subMenuParent, nullptr);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->ShowSubMenu();
    menuItemPattern->SetSubBuilder(buildFun);
    menuItemPattern->SetIsSubMenuShowed(false);
    auto mainMenuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->SetShowedSubMenu(subMenu);
    auto subMenuPattern = subMenu->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuItemPattern->AddClickableArea();
    EXPECT_FALSE(menuItemPattern->isSubMenuShowed_);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: MenuItemPatternTestNg028
 * @tc.desc: Verify MenuItemModelNG::Create when version is 12.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg028, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    MenuItemModelNG model;
    auto customNode = FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<Pattern>());
    model.Create(customNode);
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(itemNode);
    auto pattern = itemNode->GetPattern<CustomMenuItemPattern>();
    ASSERT_TRUE(pattern);
    ASSERT_TRUE(itemNode->GetEventHub<EventHub>());
    auto touch = itemNode->GetOrCreateGestureEventHub()->touchEventActuator_;
    ASSERT_TRUE(touch);
    ASSERT_FALSE(touch->touchEvents_.empty());
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: MenuItemPatternTestNg029
 * @tc.desc: Verify MenuItemModelNG::Create when version is 12.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternTestNg, MenuItemPatternTestNg029, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    MenuItemProperties itemOption;
    itemOption.content = "content";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuItemEventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(menuItemEventHub, nullptr);
    menuItemPattern->OnClick();
    ASSERT_TRUE(menuItemPattern->IsSelected());
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}
} // namespace OHOS::Ace::NG
