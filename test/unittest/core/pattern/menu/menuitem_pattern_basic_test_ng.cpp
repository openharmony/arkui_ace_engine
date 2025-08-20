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
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuItemPatternBasicTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuItemPatternBasicTestNg();
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

void MenuItemPatternBasicTestNg::SetUpTestCase() {}

void MenuItemPatternBasicTestNg::TearDownTestCase() {}

void MenuItemPatternBasicTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuItemPatternBasicTestNg::MockPipelineContextGetTheme()
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

void MenuItemPatternBasicTestNg::TearDown()
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

void MenuItemPatternBasicTestNg::InitMenuItemPatternBasicTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuItemPatternBasicTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemPatternBasicTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemPatternBasicTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: AddSelectIcon001
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddSelectIcon001, TestSize.Level1)
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
 * @tc.name: AddSelectIcon002
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddSelectIcon002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
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

    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
}

/**
 * @tc.name: AddSelectIcon003
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddSelectIcon003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
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
    auto sourceInfo = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_TRUE(sourceInfo.has_value());
}

/**
 * @tc.name: AddSelectIcon004
 * @tc.desc: Verify AddSelectIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddSelectIcon004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
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
    // call AddSelectIcon
    itemPattern->OnModifyDone();

    EXPECT_EQ(rightRow->GetChildren().size(), 0u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto selectIconNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(selectIconNode, nullptr);
    EXPECT_EQ(selectIconNode->GetTag(), V2::IMAGE_ETS_TAG);

    itemProperty->UpdateSelectIcon(false);
    // call AddSelectIcon
    itemPattern->OnModifyDone();
    ASSERT_EQ(leftRow->GetChildren().size(), 0u);
}

/**
 * @tc.name: UpdateIcon001
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateIcon001, TestSize.Level1)
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
 * @tc.name: UpdateIcon002
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateIcon002, TestSize.Level1)
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
 * @tc.name: UpdateIcon003
 * @tc.desc: Verify UpdateIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateIcon003, TestSize.Level1)
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
 * @tc.name: AddClickableArea001
 * @tc.desc: Verify AddClickableArea.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddClickableArea001, TestSize.Level1)
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
    auto contentNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto labelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    menuItemPattern->content_ = contentNode;
    menuItemPattern->label_ = labelNode;
    menuItemPattern->AddClickableArea();
}

/**
 * @tc.name: AddClickableArea002
 * @tc.desc: Verify AddClickableArea.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddClickableArea002, TestSize.Level1)
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
 * @tc.name: UpdateText001
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateText001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    MenuItemModelNG MenuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "labelInfo";
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

    EXPECT_EQ(rightRow->GetChildren().size(), 1u);
    ASSERT_EQ(leftRow->GetChildren().size(), 1u);
    auto contentNode = AceType::DynamicCast<FrameNode>(leftRow->GetChildAtIndex(0));
    ASSERT_NE(contentNode, nullptr);
    EXPECT_EQ(contentNode->GetTag(), V2::TEXT_ETS_TAG);
    auto textLayoutProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto content = textLayoutProperty->GetContent();
    ASSERT_TRUE(content.has_value());
    EXPECT_EQ(content.value(), u"content");
}

/**
 * @tc.name: UpdateText002
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateText002, TestSize.Level1)
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
    EXPECT_EQ(content.value(), u"label");
}

/**
 * @tc.name: UpdateText003
 * @tc.desc: Verify update text when item is disabled.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateText003, TestSize.Level1)
{
    // mock theme
    MockPipelineContextGetTheme();

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
    EXPECT_EQ(content.value(), u"item content");
    auto textRenderContext = contentNode->GetRenderContext();
    EXPECT_EQ(textRenderContext->GetOpacity(), std::nullopt);
}

/**
 * @tc.name: UpdateText004
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateText004, TestSize.Level1)
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

/**
 * @tc.name: UpdateText005
 * @tc.desc: Verify UpdateText.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, UpdateText005, TestSize.Level1)
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
 * @tc.name: AddSelfHoverRegion001
 * @tc.desc: Verify AddSelfHoverRegion, IsInHoverRegions.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddSelfHoverRegion001, TestSize.Level1)
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
 * @tc.name: AddSelfHoverRegion002
 * @tc.desc: Verify AddSelfHoverRegion.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, AddSelfHoverRegion002, TestSize.Level1)
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
 * @tc.name: MenuItemPatternTestEvent001
 * @tc.desc: Test Click Event
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternTestEvent001, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg001
 * @tc.desc: Verify GetMenuWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg001, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg004
 * @tc.desc: Verify OnTouch.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg004, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg005
 * @tc.desc: Verify OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg005, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->OnHover(true);
    menuItemPattern->OnHover(false);
    EXPECT_EQ(menuItemPattern->GetBgBlendColor(), Color::TRANSPARENT);
}

/**
 * @tc.name: MenuItemPatternBasicTestNg006
 * @tc.desc: Verify OnKeyEvent,PlayBgColorAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg006, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg007
 * @tc.desc: Verify RegisterWrapperMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg007, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg012
 * @tc.desc: Verify HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg012, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
}
/**
 * @tc.name: MenuItemPatternBasicTestNg013
 * @tc.desc: Verify HandleBlurEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg013, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg014
 * @tc.desc: Verify InitFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg014, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    mainMenu->GetGeometryNode()->SetFrameSize(SizeF(100, 100));
}
/**
 * @tc.name: MenuItemPatternBasicTestNg015
 * @tc.desc: Verify GetShadowFromTheme.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg015, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg019
 * @tc.desc: Verify OnClick().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg019, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg020
 * @tc.desc: Verify OnAfterModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg020, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg022
 * @tc.desc: Verify OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg022, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg024
 * @tc.desc: Verify OnVisibleChange().
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg024, TestSize.Level1)
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
 * @tc.name: MenuItemPatternBasicTestNg026
 * @tc.desc: Verify RegisterWrapperMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg026, TestSize.Level1)
{
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->RegisterWrapperMouseEvent();
    EXPECT_EQ(menuItemNode->GetChildren().size(), 0);
}

/**
 * @tc.name: MenuItemPatternBasicTestNg029
 * @tc.desc: Verify MenuItemModelNG::Create when version is 12.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg029, TestSize.Level1)
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

/**
 * @tc.name: MenuItemPatternBasicTestNg030
 * @tc.desc: call ShowSubMenuWithAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, MenuItemPatternBasicTestNg030, TestSize.Level1)
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
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 4, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemNode->MountToParent(mainMenu);
    mainMenu->MountToParent(wrapperNode);
    subMenu->MountToParent(wrapperNode);
    
    /**
     * @tc.steps: step2. execute submenu Opacity.
     * @tc.expected: result as expected
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->menuAnimationDuration_ = 100;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    auto renderContext = subMenu->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    menuItemPattern->ShowSubMenuWithAnimation(subMenu);
    ASSERT_NE(renderContext->GetOpacity(), std::nullopt);
    EXPECT_EQ(renderContext->GetOpacity().value(), 1.0f);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    wrapperPattern->ShowSubMenuDisappearAnimation(wrapperNode, subMenu);
    ASSERT_NE(renderContext->GetOpacity(), std::nullopt);
    EXPECT_EQ(renderContext->GetOpacity().value(), 0.0f);
}

/**
 * @tc.name: RegisterAccessibilityChildActionNotify001
 * @tc.desc: Test callback function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemPatternBasicTestNg, RegisterAccessibilityChildActionNotify001, TestSize.Level1)
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
    auto menuitemAccessibilityProperty = menuItemNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(menuitemAccessibilityProperty, nullptr);
    auto callback = menuitemAccessibilityProperty->GetNotifyChildActionFunc();
    ASSERT_NE(callback, nullptr);
    auto reuslt = callback(menuItemNode, NotifyChildActionType::ACTION_CLICK);
    EXPECT_EQ(reuslt, AccessibilityActionResult::ACTION_RISE);
}
} // namespace OHOS::Ace::NG
