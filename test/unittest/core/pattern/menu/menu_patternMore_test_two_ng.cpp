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

#include "test/mock/base/mock_system_properties.h"
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
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_paint_property.h"
#include "core/components_ng/pattern/menu/menu_divider/menu_divider_pattern.h"
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
const std::string TEXT_TAG = "text";
const InspectorFilter filter;
constexpr int32_t TARGET_ID = 3;
constexpr float TARGET_FONT = 25.0f;
constexpr MenuType TYPE = MenuType::MENU;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
const V2::ItemDivider ITEM_DIVIDER = { Dimension(5.f), Dimension(10), Dimension(20), Color(0x000000) };
const std::string MENU_TAG = "menu";
} // namespace
class MenuPattern2TwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuPattern2TwoTestNg();
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

void MenuPattern2TwoTestNg::SetUpTestCase() {}

void MenuPattern2TwoTestNg::TearDownTestCase() {}

void MenuPattern2TwoTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuPattern2TwoTestNg::TearDown()
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

void MenuPattern2TwoTestNg::InitMenuPattern2TwoTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuPattern2TwoTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuPattern2TwoTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuPattern2TwoTestNg::GetPreviewMenuWrapper(
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

void CheckTestResultTwo(RefPtr<MenuItemPattern> itemPattern)
{
    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    ASSERT_TRUE(textProperty->GetContent().has_value());
    EXPECT_EQ(textProperty->GetContent().value(), u"content");
    ASSERT_TRUE(textProperty->GetFontSize().has_value());
    EXPECT_EQ(textProperty->GetFontSize().value(), Dimension(TARGET_FONT));
    ASSERT_TRUE(textProperty->GetFontWeight().has_value());
    EXPECT_EQ(textProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(textProperty->GetTextColor().has_value());
    EXPECT_EQ(textProperty->GetTextColor().value(), Color::RED);

    auto labelNode = itemPattern->GetLabelNode();
    ASSERT_NE(labelNode, nullptr);
    auto labelProperty = labelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(labelProperty, nullptr);
    ASSERT_TRUE(labelProperty->GetContent().has_value());
    EXPECT_EQ(labelProperty->GetContent().value(), u"label");
    ASSERT_TRUE(labelProperty->GetFontSize().has_value());
    EXPECT_EQ(labelProperty->GetFontSize().value(), Dimension(TARGET_FONT));
    ASSERT_TRUE(labelProperty->GetFontWeight().has_value());
    EXPECT_EQ(labelProperty->GetFontWeight().value(), FontWeight::BOLD);
    ASSERT_TRUE(labelProperty->GetTextColor().has_value());
    EXPECT_EQ(labelProperty->GetTextColor().value(), Color::RED);
}

/**
 * @tc.name: UpdateMenuBorderAndBackgroundBlur001
 * @tc.desc: Verify UpdateMenuBorderAndBackgroundBlur
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, UpdateMenuBorderAndBackgroundBlur001, TestSize.Level1)
{
    auto outterMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(outterMenuNode, nullptr);
    auto menuPattern = outterMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto renderContext = outterMenuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
            selectTheme->menuNormalBorderColor_ = Color::RED;
            return selectTheme;
        } else {
            return AceType::MakeRefPtr<MenuTheme>();
        }
    });

    menuPattern->UpdateMenuBorderAndBackgroundBlur();
    auto borderColor = renderContext->GetBorderColor();
    EXPECT_TRUE(borderColor.has_value());
    EXPECT_EQ(borderColor.value().leftColor.value_or(Color::TRANSPARENT),  Color::RED);
}

/**
 * @tc.name: UpdateMenuBorderAndBackgroundBlur002
 * @tc.desc: Verify UpdateMenuBorderAndBackgroundBlur
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, UpdateMenuBorderAndBackgroundBlur002, TestSize.Level1)
{
    auto outterMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(outterMenuNode, nullptr);
    auto menuPattern = outterMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto renderContext = outterMenuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLUE);
    renderContext->UpdateBorderColor(borderColor);

    BorderWidthProperty borderWidth;
    renderContext->UpdateBorderWidth(borderWidth);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
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

    menuPattern->UpdateMenuBorderAndBackgroundBlur();
    auto borderColor1 = renderContext->GetBorderColor();
    EXPECT_TRUE(borderColor1.has_value());
    EXPECT_EQ(borderColor1.value().leftColor.value_or(Color::TRANSPARENT),  Color::BLUE);
}

/**
 * @tc.name: InitDefaultBorder001
 * @tc.desc: Verify InitDefaultBorder
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, InitDefaultBorder001, TestSize.Level1)
{
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2,
            AceType::MakeRefPtr<InnerMenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    auto menuPattern = innerMenuNode->GetPattern<InnerMenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
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
    auto renderContext = innerMenuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    menuPattern->InitDefaultBorder(innerMenuNode);
    EXPECT_TRUE(renderContext->GetBorderColor().has_value());
}

/**
 * @tc.name: SetMenuBackGroundStyle001
 * @tc.desc: Verify SetMenuBackGroundStyle
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, SetMenuBackGroundStyle001, TestSize.Level1)
{
    auto outterMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(outterMenuNode, nullptr);
    auto menuPattern = outterMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    menuParam.backgroundBlurStyleOption = blurStyleOption;

    EffectOption option;
    option.radius = Dimension();
    menuParam.backgroundEffectOption = option;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuPattern->SetMenuBackGroundStyle(outterMenuNode, menuParam);
}

/**
 * @tc.name: ShowStackSubMenuAnimation001
 * @tc.desc: Verify ShowStackSubMenuAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, ShowStackSubMenuAnimation001, TestSize.Level1)
{
    auto mainMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenuNode, nullptr);
    auto subMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(subMenuNode, nullptr);
    
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->MountToParent(subMenuNode);
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    innerMenuNode->MountToParent(scrollNode);
    
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto titleFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(titleFrameNode, nullptr);
    titleFrameNode->MountToParent(innerMenuNode);
    auto menuItem = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItem, nullptr);
    menuItem->MountToParent(innerMenuNode);

    auto menuPattern = subMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->ShowStackSubMenuAnimation(mainMenuNode, subMenuNode);

    auto titlePattern = titleFrameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(titlePattern, nullptr);
    auto titleContentNode = titlePattern->GetContentNode();
    ASSERT_NE(titleContentNode, nullptr);
    auto textProperty = titleContentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    EXPECT_EQ(textProperty->GetFontWeight(), FontWeight::BOLD);
}

/**
 * @tc.name: ShowStackMainMenuAnimation001
 * @tc.desc: Verify ShowStackMainMenuAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, ShowStackMainMenuAnimation001, TestSize.Level1)
{
    auto mainMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenuNode, nullptr);
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->MountToParent(mainMenuNode);
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    innerMenuNode->MountToParent(scrollNode);

    auto subMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(subMenuNode, nullptr);
    auto subMenuPattern = subMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->translateYForStack_ = 10.0f;

    auto menuWrapperNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() {return AceType::MakeRefPtr<MenuWrapperPattern>(1);});
    ASSERT_NE(menuWrapperNode, nullptr);
    auto previewNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(previewNode, nullptr);
    mainMenuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    subMenuNode->MountToParent(menuWrapperNode);
    subMenuPattern->ShowStackMainMenuAnimation(mainMenuNode, subMenuNode, menuWrapperNode);

    auto innerMenuContext = innerMenuNode->GetRenderContext();
    ASSERT_NE(innerMenuContext, nullptr);
    EXPECT_EQ(innerMenuContext->GetOpacity(), 0.4f);
}

/**
 * @tc.name: ShowStackSubMenuDisappearAnimation001
 * @tc.desc: Verify ShowStackSubMenuDisappearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, ShowStackSubMenuDisappearAnimation001, TestSize.Level1)
{
    auto mainMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenuNode, nullptr);
    auto subMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(subMenuNode, nullptr);
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->MountToParent(subMenuNode);
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    innerMenuNode->MountToParent(scrollNode);
    
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    MenuItemModelNG MneuItemModelInstance;
    MneuItemModelInstance.Create(itemOption);
    auto titleFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(titleFrameNode, nullptr);
    titleFrameNode->MountToParent(innerMenuNode);
    auto menuItem = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItem, nullptr);
    menuItem->MountToParent(innerMenuNode);

    auto menuPattern = subMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->ShowStackSubMenuDisappearAnimation(mainMenuNode, subMenuNode);
    auto titlePattern = titleFrameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(titlePattern, nullptr);
    auto titleContentNode = titlePattern->GetContentNode();
    ASSERT_NE(titleContentNode, nullptr);
    auto textProperty = titleContentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);
    EXPECT_EQ(textProperty->GetFontWeight(), FontWeight::MEDIUM);
}

/**
 * @tc.name: ShowStackMainMenuDisappearAnimation001
 * @tc.desc: Verify ShowStackMainMenuDisappearAnimation
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, ShowStackMainMenuDisappearAnimation001, TestSize.Level1)
{
    auto mainMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenuNode, nullptr);
    auto scrollNode = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    ASSERT_NE(scrollNode, nullptr);
    scrollNode->MountToParent(mainMenuNode);
    auto innerMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(innerMenuNode, nullptr);
    innerMenuNode->MountToParent(scrollNode);

    auto subMenuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(subMenuNode, nullptr);
    auto mainMenuPattern = mainMenuNode->GetPattern<MenuPattern>();
    ASSERT_NE(mainMenuPattern, nullptr);
    mainMenuPattern->originMenuYForStack_ = 10.0f;
    mainMenuPattern->originPreviewYForStack_ = 10.0f;

    auto menuWrapperNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() {return AceType::MakeRefPtr<MenuWrapperPattern>(1);});
    ASSERT_NE(menuWrapperNode, nullptr);
    auto previewNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(previewNode, nullptr);
    mainMenuNode->MountToParent(menuWrapperNode);
    previewNode->MountToParent(menuWrapperNode);
    subMenuNode->MountToParent(menuWrapperNode);
    AnimationOption option = AnimationOption();
    mainMenuPattern->ShowStackMainMenuDisappearAnimation(mainMenuNode, subMenuNode, option);

    auto innerMenuContext = innerMenuNode->GetRenderContext();
    ASSERT_NE(innerMenuContext, nullptr);
    EXPECT_EQ(innerMenuContext->GetOpacity(), 1.0f);
}

/**
 * @tc.name: OnColorConfigurationUpdate
 * @tc.desc: Verify OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, OnColorConfigurationUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init pipeline and create menu.
     * @tc.expected: step1. All pointers non-null.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    std::vector<SelectParam> selectParam = { { "content1", "icon1" }, { "content2", "" }, { "", "icon3" }, { "", "" } };
    auto wrapperNode = MenuView::Create(selectParam, TARGET_ID, "");
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layout = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(layout, nullptr);
    auto pipeline = menuNode->GetContextWithCheck();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<SelectTheme>();
    ASSERT_NE(theme, nullptr);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    theme->menuFontColor_ = Color::RED;
    theme->menuBlendBgColor_ = true;
    theme->backgroundColor_ = Color::RED;

    /**
     * @tc.steps: step2. Color config change, user sets font & disables bg.
     * @tc.expected: step2. Font color keeps user's value.
     */
    g_isConfigChangePerform = true;
    menuPattern->isDisableMenuBgColorByUser_ = true;
    layout->UpdateFontColorSetByUser(true);
    menuPattern->OnColorConfigurationUpdate();
    EXPECT_NE(layout->GetFontColor().value_or(Color::TRANSPARENT), theme->GetMenuFontColor());

    /**
     * @tc.steps: step3. Color config change, use theme font & bg.
     * @tc.expected: step3. Font color uses theme.
     */
    menuPattern->isDisableMenuBgColorByUser_ = false;
    layout->UpdateFontColorSetByUser(false);
    menuPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(layout->GetFontColor().value_or(Color::TRANSPARENT), theme->GetMenuFontColor());

    /**
     * @tc.steps: step4. No config change, user disables bg.
     * @tc.expected: step4. Bg color unchanged.
     */
    g_isConfigChangePerform = false;
    menuPattern->isDisableMenuBgColorByUser_ = true;
    layout->UpdateFontColorSetByUser(true);
    menuPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT), theme->GetBackgroundColor());

    /**
     * @tc.steps: step5. No config change, use theme bg.
     * @tc.expected: step5. Bg color uses theme.
     */
    menuPattern->isDisableMenuBgColorByUser_ = false;
    layout->UpdateFontColorSetByUser(false);
    menuPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT), theme->GetBackgroundColor());

    /**
     * @tc.steps: step6. Blend bg enabled, recheck bg color.
     * @tc.expected: step6. Still matches theme.
     */
    theme->menuBlendBgColor_ = true;
    menuPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT), theme->GetBackgroundColor());
}

/**
 * @tc.name: BuildDivider
 * @tc.desc: Verify BuildDivider
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, BuildDivider, TestSize.Level1)
{
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->BuildDivider();
    EXPECT_FALSE(menuPattern->buildDividerTaskAdded_);
}

/**
 * @tc.name: AddBuildDividerTask
 * @tc.desc: Verify AddBuildDividerTask
 * @tc.type: FUNC
 */
HWTEST_F(MenuPattern2TwoTestNg, AddBuildDividerTask, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(TARGET_FONT));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);
    MneuModelInstance.SetItemDivider(ITEM_DIVIDER, DividerMode::FLOATING_ABOVE_MENU);
    MneuModelInstance.SetItemGroupDivider(ITEM_DIVIDER, DividerMode::FLOATING_ABOVE_MENU);  // add divider

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

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
    itemPattern->OnAttachToMainTree();
    menuPattern->OnAttachToMainTree();
    EXPECT_TRUE(menuPattern->buildDividerTaskAdded_);

    MockPipelineContext::GetCurrent()->FlushBuildFinishCallbacks();
    EXPECT_FALSE(menuPattern->buildDividerTaskAdded_);
}
} // namespace OHOS::Ace::NG
