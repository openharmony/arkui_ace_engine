/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "ui/resource/resource_info.h"

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
constexpr int32_t NODE_ID = 1;

const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
const V2::ItemDivider ITEM_DIVIDER = { Dimension(5.f), Dimension(10), Dimension(20), Color(0x000000) };
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
 * @tc.name: MenuItemRemoveParentRestrictionsForFixIdeal001
 * @tc.desc: Test MenuItem RemoveParentRestrictionsForFixIdeal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemRemoveParentRestrictionsForFixIdeal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu item.
     */
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, -1, menuItemPattern);
    auto algorithm = AceType::MakeRefPtr<MenuItemLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemNode, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. LayoutCalPolicy is FIX_AT_IDEAL_SIZE and set maxSize to FULL_SCREEN_SIZE.
     * @tc.expected: childConstraint.maxSize is infinity.
     */
    LayoutConstraintF childConstraint;
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProp->layoutPolicy_ = layoutPolicyProperty;
    algorithm->RemoveParentRestrictionsForFixIdeal(layoutProp, childConstraint);
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Width()));
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Height()));
}

/**
 * @tc.name: MultiMenuRemoveParentRestrictionsForFixIdeal001
 * @tc.desc: Test MultiMenu RemoveParentRestrictionsForFixIdeal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MultiMenuRemoveParentRestrictionsForFixIdeal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create multi menu.
     */
    ScreenSystemManager::GetInstance().SetWindowInfo(FULL_SCREEN_WIDTH, 1.0, 1.0);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MULTI_MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(3, TEXT_TAG, MenuType::MULTI_MENU));
    frameNode->MountToParent(menuNode);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuNode, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. LayoutCalPolicy is FIX_AT_IDEAL_SIZE and set maxSize to FULL_SCREEN_SIZE.
     * @tc.expected: childConstraint.maxSize is infinity.
     */
    LayoutConstraintF childConstraint;
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProp->layoutPolicy_ = layoutPolicyProperty;
    algorithm->RemoveParentRestrictionsForFixIdeal(layoutWrapper.GetRawPtr(), childConstraint);
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Width()));
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Height()));
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

    algorithm->showDefaultSelectedIcon_ = true;
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    algorithm->Layout(AceType::RawPtr(menuItemNode));
    EXPECT_TRUE(props->calcLayoutConstraint_->selfIdealSize.has_value());
}

/**
 * @tc.name: MenuItemLayoutAlgorithmMeasureRow001
 * @tc.desc: Test MenuItemLayoutAlgorithm MeasureRow
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MenuItemLayoutAlgorithmMeasureRow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
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
    algorithm->isOption_ = true;

    /**
     * @tc.steps: step2. execute Measure
     * @tc.expected: prop is set as expected
     */
    LayoutConstraintF constraint;
    algorithm->MeasureRow(AceType::RawPtr(wrapperNode), menuItemNode, constraint);

    auto size = menuItemNode->GetGeometryNode()->GetFrameSize();
    algorithm->showDefaultSelectedIcon_ = true;
    algorithm->MeasureRow(AceType::RawPtr(wrapperNode), menuItemNode, constraint);
    size = menuItemNode->GetGeometryNode()->GetFrameSize();
    EXPECT_FLOAT_EQ(size.Height(), 0.0);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
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
    algorithm->isOption_ = true;
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    algorithm->isOption_ = false;
    algorithm->showDefaultSelectedIcon_ = true;
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    algorithm->isOption_ = true;
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    menuItemPattern->SetIsSelectOption(true);
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    menuItemPattern->SetIsSelectOption(false);
    menuItemPattern->SetHasOptionWidth(true);
    algorithm->Measure(AceType::RawPtr(menuItemNode));
    menuItemPattern->SetIsSelectOption(true);
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
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
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
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
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
    auto eventHub = frameNode->GetOrCreateEventHub<MenuItemEventHub>();
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

/**
 * @tc.name: CreateNavigationMenuItemTest001
 * @tc.desc: Test CreateMenuItem creates a FrameNode and sets properties correctly.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateNavigationMenuItemTest001, TestSize.Level1)
{
    OptionParam optionParam;
    optionParam.enabled = true;
    optionParam.action = [] {};

    MenuParam menuParam;
    menuParam.title = "Menu Title";

    auto menuItemNode = MenuItemModelNG::CreateMenuItem(std::move(optionParam), menuParam);
    ASSERT_NE(menuItemNode, nullptr);

    auto layoutProps = menuItemNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);

    auto eventHub = menuItemNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->IsEnabled());

    auto focusHub = menuItemNode->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_TRUE(focusHub->IsEnabled());
}

/**
 * @tc.name: ColorTypeToString
 * @tc.desc: Test MenuItemModelNG::ColorTypeToString with different types.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, ColorTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuItemModelNG instance
     * @tc.expected: Instance initialized successfully
     */
    MenuItemModelNG menuItemModel;

    /**
     * @tc.steps2: Call ColorTypeToString with FONT_COLOR
     * @tc.expected: Return "FontColor"
     */
    std::string result = menuItemModel.ColorTypeToString(MenuItemFontColorType::FONT_COLOR);
    EXPECT_EQ(result, "FontColor");

    /**
     * @tc.steps3: Call ColorTypeToString with LABEL_FONT_COLOR
     * @tc.expected: Return "LabelFontColor"
     */
    result = menuItemModel.ColorTypeToString(MenuItemFontColorType::LABEL_FONT_COLOR);
    EXPECT_EQ(result, "LabelFontColor");

    /**
     * @tc.steps4: Call ColorTypeToString with unknown type
     * @tc.expected: Return "Unknown" for type 100
     */
    MenuItemFontColorType unknownType = static_cast<MenuItemFontColorType>(100);
    result = menuItemModel.ColorTypeToString(unknownType);
    EXPECT_EQ(result, "Unknown");
}

/**
 * @tc.name: DimensionTypeToString
 * @tc.desc: Test DimensionTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, DimensionTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuItemModelNG instance
     * @tc.expected: Instance initialized successfully
     */
    MenuItemModelNG model;

    /**
     * @tc.steps2: Call DimensionTypeToString with FONT_SIZE
     * @tc.expected: Return "FontSize"
     */
    EXPECT_EQ(model.DimensionTypeToString(MenuItemFontSizeType::FONT_SIZE), "FontSize");

    /**
     * @tc.steps3: Call DimensionTypeToString with LABEL_FONT_SIZE
     * @tc.expected: Return "LabelFontSize"
     */
    EXPECT_EQ(model.DimensionTypeToString(MenuItemFontSizeType::LABEL_FONT_SIZE), "LabelFontSize");

    /**
     * @tc.steps4: Call DimensionTypeToString with unknown type
     * @tc.expected: Return "Unknown" for type 99
     */
    MenuItemFontSizeType unknownType = static_cast<MenuItemFontSizeType>(99);
    EXPECT_EQ(model.DimensionTypeToString(unknownType), "Unknown");
}

/**
 * @tc.name: StringTypeToString
 * @tc.desc: Test StringTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, StringTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuItemModelNG instance
     * @tc.expected: Instance initialized successfully
     */
    MenuItemModelNG model;

    /**
     * @tc.steps2: Call StringTypeToString with SELECT_ICON
     * @tc.expected: Return "SelectIcon"
     */
    EXPECT_EQ(model.StringTypeToString(MenuItemStringType::SELECT_ICON), "SelectIcon");

    /**
     * @tc.steps3: Call StringTypeToString with CONTENT
     * @tc.expected: Return "Content"
     */
    EXPECT_EQ(model.StringTypeToString(MenuItemStringType::CONTENT), "Content");

    /**
     * @tc.steps4: Call StringTypeToString with LABEL_INFO
     * @tc.expected: Return "LabelInfo"
     */
    EXPECT_EQ(model.StringTypeToString(MenuItemStringType::LABEL_INFO), "LabelInfo");

    /**
     * @tc.steps5: Call StringTypeToString with unknown type
     * @tc.expected: Return "Unknown" for type 99
     */
    MenuItemStringType unknownType = static_cast<MenuItemStringType>(99);
    EXPECT_EQ(model.StringTypeToString(unknownType), "Unknown");
}

/**
 * @tc.name: FamilyTypeToString
 * @tc.desc: Test FamilyTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, FamilyTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuItemModelNG instance
     * @tc.expected: Instance initialized successfully
     */
    MenuItemModelNG model;

    /**
     * @tc.steps2: Call FamilyTypeToString with FONT_FAMILY
     * @tc.expected: Return "FontFamily"
     */
    EXPECT_EQ(model.FamilyTypeToString(MenuItemFontFamilyType::FONT_FAMILY), "FontFamily");

    /**
     * @tc.steps3: Call FamilyTypeToString with LABEL_FONT_FAMILY
     * @tc.expected: Return "LabelFontFamily"
     */
    EXPECT_EQ(model.FamilyTypeToString(MenuItemFontFamilyType::LABEL_FONT_FAMILY), "LabelFontFamily");

    /**
     * @tc.steps4: Call FamilyTypeToString with unknown type
     * @tc.expected: Return "Unknown" for type 99
     */
    MenuItemFontFamilyType unknownType = static_cast<MenuItemFontFamilyType>(99);
    EXPECT_EQ(model.FamilyTypeToString(unknownType), "Unknown");
}

/**
 * @tc.name: MediaTypeToString
 * @tc.desc: Test MediaTypeToString.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, MediaTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize MenuItemModelNG instance
     * @tc.expected: Instance initialized successfully
     */
    MenuItemModelNG model;

    /**
     * @tc.steps2: Call MediaTypeToString with START_ICON
     * @tc.expected: Return "StartIcon"
     */
    EXPECT_EQ(model.MediaTypeToString(MenuItemIconType::START_ICON), "StartIcon");

    /**
     * @tc.steps3: Call MediaTypeToString with END_ICON
     * @tc.expected: Return "EndIcon"
     */
    EXPECT_EQ(model.MediaTypeToString(MenuItemIconType::END_ICON), "EndIcon");

    /**
     * @tc.steps4: Call MediaTypeToString with unknown type
     * @tc.expected: Return "Unknown" for type 99
     */
    MenuItemIconType unknownType = static_cast<MenuItemIconType>(99);
    EXPECT_EQ(model.MediaTypeToString(unknownType), "Unknown");
}

/**
 * @tc.name: CreateWithColorResourceObj001
 * @tc.desc: Test CreateWithColorResourceObj MenuItemFontColorType::FONT_COLOR.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithColorResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test environment and create MenuItemModelNG
     * @tc.expected: MenuItemModelNG created with content and label
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node and check initial font color
     * @tc.expected: Frame node obtained, font color not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetFontColor().has_value());

    /**
     * @tc.steps3: Create resource object and call CreateWithColorResourceObj
     * @tc.expected: Resource object created, method called for FONT_COLOR
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    menuItemModelInstance.CreateWithColorResourceObj(resObj, MenuItemFontColorType::FONT_COLOR);

    /**
     * @tc.steps4: Test with empty cache
     * @tc.expected: Font color remains unset
     */
    std::string key = "";
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, Color::RED.ColorToString());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_FALSE(layoutProperty->GetFontColor().has_value());

    /**
     * @tc.steps5: Test with valid cache
     * @tc.expected: Font color set to red
     */
    key = "MenuItem" + MenuItemModelNG::ColorTypeToString(MenuItemFontColorType::FONT_COLOR);
    pattern->AddResCache(key, Color::RED.ColorToString());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetFontColor().value(), Color::RED);
}

/**
 * @tc.name: CreateWithColorResourceObj002
 * @tc.desc: Test CreateWithColorResourceObj MenuItemFontColorType::LABEL_FONT_COLOR.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithColorResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial label font color
     * @tc.expected: Node obtained, label font color not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetLabelFontColor().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithColorResourceObj
     * @tc.expected: Resource obj created, method called
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    menuItemModelInstance.CreateWithColorResourceObj(resObj, MenuItemFontColorType::LABEL_FONT_COLOR);

    /**
     * @tc.steps4: Add valid cache, reload resources
     * @tc.expected: Label font color set to red
     */
    std::string key = "MenuItem" + MenuItemModelNG::ColorTypeToString(MenuItemFontColorType::LABEL_FONT_COLOR);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, Color::RED.ColorToString());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetLabelFontColor().has_value());
    EXPECT_EQ(layoutProperty->GetLabelFontColor().value(), Color::RED);
}

/**
 * @tc.name: CreateWithDimensionFpResourceObj001
 * @tc.desc: Test CreateWithDimensionFpResourceObj MenuItemFontSizeType::FONT_SIZE.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithDimensionFpResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial font size
     * @tc.expected: Node obtained, font size not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetFontSize().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithDimensionFpResourceObj
     * @tc.expected: Resource obj created, method called
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    menuItemModelInstance.CreateWithDimensionFpResourceObj(resObj, MenuItemFontSizeType::FONT_SIZE);

    /**
     * @tc.steps4: Add invalid cache, reload resources
     * @tc.expected: Cache added, font size still not set
     */
    std::string key = "MenuItem" + MenuItemModelNG::DimensionTypeToString(MenuItemFontSizeType::FONT_SIZE);
    CalcDimension result1(5.0, DimensionUnit::PERCENT);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, result1.ToString());
    result1 = CalcDimension();
    EXPECT_FALSE(result1.IsValid());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_FALSE(layoutProperty->GetFontSize().has_value());

    /**
     * @tc.steps5: Add valid cache, reload resources
     * @tc.expected: Font size set to 0.5VP
     */
    CalcDimension result2(0.5, DimensionUnit::VP);
    pattern->AddResCache(key, result2.ToString());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetFontSize().value(), result2);
}

/**
 * @tc.name: CreateWithDimensionFpResourceObj002
 * @tc.desc: Test CreateWithDimensionFpResourceObj MenuItemFontSizeType::LABEL_FONT_SIZE.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithDimensionFpResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial label font size
     * @tc.expected: Node obtained, label font size not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetLabelFontSize().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithDimensionFpResourceObj
     * @tc.expected: Resource obj created, method called
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    menuItemModelInstance.CreateWithDimensionFpResourceObj(resObj, MenuItemFontSizeType::LABEL_FONT_SIZE);

    /**
     * @tc.steps4: Add invalid cache, reload resources
     * @tc.expected: Cache added, label font size still not set
     */
    std::string key = "MenuItem" + MenuItemModelNG::DimensionTypeToString(MenuItemFontSizeType::LABEL_FONT_SIZE);
    CalcDimension result(5.0, DimensionUnit::PERCENT);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, result.ToString());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_FALSE(layoutProperty->GetLabelFontSize().has_value());

    /**
     * @tc.steps5: Add valid cache, reload resources
     * @tc.expected: Label font size set to 0.5VP
     */
    CalcDimension result2(0.5, DimensionUnit::VP);
    pattern->AddResCache(key, result2.ToString());
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetLabelFontSize().has_value());
    EXPECT_EQ(layoutProperty->GetLabelFontSize().value(), result2);
}

/**
 * @tc.name: CreateWithFontFamilyResourceObj001
 * @tc.desc: Test CreateWithFontFamilyResourceObj MenuItemFontFamilyType::FONT_FAMILY.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithFontFamilyResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial font family
     * @tc.expected: Node obtained, font family not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithFontFamilyResourceObj
     * @tc.expected: Resource obj created, method called
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "Test Sans";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::STRING);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);
    menuItemModelInstance.CreateWithFontFamilyResourceObj(resObj, MenuItemFontFamilyType::FONT_FAMILY);

    /**
     * @tc.steps4: Add cache, reload resources
     * @tc.expected: Font family set to "Test Sans"
     */
    std::string key = "MenuItem" + MenuItemModelNG::FamilyTypeToString(MenuItemFontFamilyType::FONT_FAMILY);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, "Test Sans");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetFontFamily().has_value());
}

/**
 * @tc.name: CreateWithFontFamilyResourceObj002
 * @tc.desc: Test CreateWithFontFamilyResourceObj MenuItemFontFamilyType::LABEL_FONT_FAMILY.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithFontFamilyResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial label font family
     * @tc.expected: Node obtained, label font family not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetLabelFontFamily().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithFontFamilyResourceObj
     * @tc.expected: Resource obj created, method called
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "Test Sans";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::STRING);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);
    menuItemModelInstance.CreateWithFontFamilyResourceObj(resObj, MenuItemFontFamilyType::LABEL_FONT_FAMILY);

    /**
     * @tc.steps4: Add cache, reload resources
     * @tc.expected: Label font family set to "Test Sans"
     */
    std::string key = "MenuItem" + MenuItemModelNG::FamilyTypeToString(MenuItemFontFamilyType::LABEL_FONT_FAMILY);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, "Test Sans");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetLabelFontFamily().has_value());
}

/**
 * @tc.name: CreateWithStringResourceObj001
 * @tc.desc: Test CreateWithStringResourceObj MenuItemStringType::SELECT_ICON.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithStringResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial select icon source
     * @tc.expected: Node obtained, select icon source not set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetSelectIconSrc().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithStringResourceObj
     * @tc.expected: Resource obj created, method called
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    menuItemModelInstance.CreateWithStringResourceObj(resObj, MenuItemStringType::SELECT_ICON);

    /**
     * @tc.steps4: Add empty cache, reload resources
     * @tc.expected: Cache added, select icon source still not set
     */
    std::string key = "MenuItem" + MenuItemModelNG::StringTypeToString(MenuItemStringType::SELECT_ICON);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, "");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_FALSE(layoutProperty->GetSelectIconSrc().has_value());

    /**
     * @tc.steps5: Add valid cache, reload resources
     * @tc.expected: Select icon source set to "TEST"
     */
    pattern->AddResCache(key, "TEST");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetSelectIconSrc().has_value());
    EXPECT_EQ(layoutProperty->GetSelectIconSrc().value(), "TEST");
}

/**
 * @tc.name: CreateWithStringResourceObj002
 * @tc.desc: Test CreateWithStringResourceObj MenuItemStringType::CONTENT.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithStringResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, check initial content
     * @tc.expected: Node obtained, content is set
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetContent().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithStringResourceObj
     * @tc.expected: Resource obj created, method called
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    menuItemModelInstance.CreateWithStringResourceObj(resObj, MenuItemStringType::CONTENT);

    /**
     * @tc.steps4: Add cache, reload resources
     * @tc.expected: Content updated to "TEST"
     */
    std::string key = "MenuItem" + MenuItemModelNG::StringTypeToString(MenuItemStringType::CONTENT);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    pattern->AddResCache(key, "TEST");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetContent().has_value());
    EXPECT_EQ(layoutProperty->GetContent().value(), "TEST");
}

/**
 * @tc.name: CreateWithMediaResourceObj001
 * @tc.desc: Test CreateWithMediaResourceObj MenuItemIconType::START_ICON.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithMediaResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, reset and check start icon
     * @tc.expected: Node obtained, start icon cleared
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, StartIcon, frameNode);
    EXPECT_FALSE(layoutProperty->GetStartIcon().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithMediaResourceObj
     * @tc.expected: Resource obj created, method called
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "TEST";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::STRING);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);
    menuItemModelInstance.CreateWithMediaResourceObj(resObj, MenuItemIconType::START_ICON);

    /**
     * @tc.steps4: Add empty cache, reload resources
     * @tc.expected: Start icon set (default behavior)
     */
    std::string key = "MenuItem" + MenuItemModelNG::MediaTypeToString(MenuItemIconType::START_ICON);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->AddResCache(key, "");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetStartIcon().has_value());

    /**
     * @tc.steps5: Add valid cache, reload resources
     * @tc.expected: Start icon updated with valid source
     */
    pattern->AddResCache(key, "TEST");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetStartIcon().has_value());
}

/**
 * @tc.name: CreateWithMediaResourceObj002
 * @tc.desc: Test CreateWithMediaResourceObj MenuItemIconType::END_ICON.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemTestNg, CreateWithMediaResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Initialize test env, create MenuItemModelNG
     * @tc.expected: Instance created, properties set
     */
    InitMenuItemTestNg();
    MenuItemModelNG menuItemModelInstance;
    MenuItemProperties itemOption;
    itemOption.content = "content";
    itemOption.labelInfo = "label";
    menuItemModelInstance.Create(itemOption);

    /**
     * @tc.steps2: Get frame node, reset and check start icon
     * @tc.expected: Node obtained, start icon cleared
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, StartIcon, frameNode);
    EXPECT_FALSE(layoutProperty->GetStartIcon().has_value());

    /**
     * @tc.steps3: Create resource obj, call CreateWithMediaResourceObj
     * @tc.expected: Resource obj created, method called
     */
    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "TEST";
    int32_t resourceType = static_cast<int32_t>(Kit::ResourceType::STRING);
    auto resObj = AceType::MakeRefPtr<ResourceObject>(
        1001, resourceType, std::vector<ResourceObjectParams> { param }, "testBundle", "testModule", 0);
    menuItemModelInstance.CreateWithMediaResourceObj(resObj, MenuItemIconType::END_ICON);

    /**
     * @tc.steps4: Add cache, reload resources
     * @tc.expected: End icon set to "TEST"
     */
    std::string key = "MenuItem" + MenuItemModelNG::MediaTypeToString(MenuItemIconType::END_ICON);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    pattern->AddResCache(key, "TEST");
    pattern->resourceMgr_->ReloadResources();
    EXPECT_TRUE(layoutProperty->GetEndIcon().has_value());
}
} // namespace OHOS::Ace::NG
