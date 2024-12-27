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
constexpr int32_t START_INDEX = 3;
constexpr int32_t FOOT_INDEX = 3;
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
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuItemGroupTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuItemGroupTestNg();
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

void MenuItemGroupTestNg::SetUpTestCase() {}

void MenuItemGroupTestNg::TearDownTestCase() {}

void MenuItemGroupTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void MenuItemGroupTestNg::TearDown()
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

void MenuItemGroupTestNg::InitMenuItemGroupTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

void MenuItemGroupTestNg::InitMenuItemTestNg()
{
    menuItemFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode_, nullptr);

    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);

    menuItemAccessibilityProperty_ = menuItemFrameNode_->GetAccessibilityProperty<MenuItemAccessibilityProperty>();
    ASSERT_NE(menuItemAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuItemGroupTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuItemGroupTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg001
 * @tc.desc: Test MenuItemGroup measure algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg001, TestSize.Level1)
{
    // create menu item group
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
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
    auto* layoutWrapper = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    auto props = layoutWrapper->GetLayoutProperty();
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    // set selectTheme to themeManager before using themeManager to get selectTheme
    // test measure
    algorithm->Measure(layoutWrapper);
    // @tc.expected: menu content width = item width, height = sum(item height)
    auto expectedSize = SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT * 3);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), expectedSize);

    // test layout
    algorithm->Layout(layoutWrapper);
    // @tc.expected: menu item offset y = item height * (index - 1)
    OffsetF offset;
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), offset);
        offset.AddY(MENU_SIZE_HEIGHT / 3);
    }
    parentLayoutConstraint.selfIdealSize.SetWidth(10);
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    algorithm->headerIndex_ = 0;
    algorithm->footerIndex_ = 0;
    algorithm->Measure(layoutWrapper);
    algorithm->Layout(layoutWrapper);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize().Height(), MENU_ITEM_SIZE_HEIGHT * 5);
    algorithm->needHeaderPadding_ = true;
    algorithm->LayoutHeader(layoutWrapper);
    algorithm->NeedHeaderPadding(menuItemGroup);
    algorithm->UpdateHeaderAndFooterMargin(layoutWrapper);
}

/**
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg002
 * @tc.desc: Test MenuItemGroup measure UpdateHeaderAndFooterMargin.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg002, TestSize.Level1)
{
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
    auto* layoutWrapper = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    algorithm->UpdateHeaderAndFooterMargin(layoutWrapper);
    menuItemGroupPattern->hasStartIcon_ = true;
    menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    layoutWrapper = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    algorithm->UpdateHeaderAndFooterMargin(layoutWrapper);
    algorithm->headerIndex_ = 0;
    algorithm->UpdateHeaderAndFooterMargin(layoutWrapper);
    algorithm->footerIndex_ = 0;
    algorithm->UpdateHeaderAndFooterMargin(layoutWrapper);
    menuItemGroupPattern->hasSelectIcon_ = false;
    menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    layoutWrapper = new LayoutWrapperNode(menuItemGroup, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    algorithm->UpdateHeaderAndFooterMargin(layoutWrapper);
    algorithm->Measure(layoutWrapper);
    auto expectedSize = SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT * 3);
}

/**
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg003
 * @tc.desc: Test MenuItemGroup measure.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg003, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    // create menu item group
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
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
    geometryNode->SetFrameSize(SizeF(100.0f, 150.0f));
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemGroup, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    auto props = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(props, nullptr);
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto layoutProp2 = AceType::MakeRefPtr<LayoutProperty>();
        layoutProp2->layoutConstraint_ = std::nullopt;
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp2);
        layoutWrapper->AppendChild(childWrapper);
    }
    algorithm->itemStartIndex_ = -1;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(algorithm->itemPosition_.find(0), algorithm->itemPosition_.end());
    EXPECT_EQ(algorithm->itemPosition_[0].second, 50.0f);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg004
 * @tc.desc: Test LayoutMenuItem.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg004, TestSize.Level1)
{
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuItemGroup->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->OnModifyDone();
    auto algorithm = AceType::MakeRefPtr<MenuItemGroupLayoutAlgorithm>(-1, -1, 0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemGroup, geometryNode, layoutProp);
    ASSERT_TRUE(layoutWrapper);

    algorithm->itemPosition_[0] = { 1.0f, 2.0f };
    algorithm->LayoutMenuItem(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(layoutWrapper->GetOrCreateChildByIndex(0));
}

/**
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg005
 * @tc.desc: Test UpdateHeaderAndFooterMargin.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg005, TestSize.Level1)
{
    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    // create menu item group
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuItemGroup->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->OnModifyDone();
    auto algorithm = AceType::MakeRefPtr<MenuItemGroupLayoutAlgorithm>(-1, -1, 0);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemGroup, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    auto footerWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    ASSERT_NE(footerWrapper, nullptr);
    auto footerLayoutProps = footerWrapper->GetLayoutProperty();
    ASSERT_NE(footerLayoutProps, nullptr);
    footerLayoutProps->margin_ = nullptr;

    algorithm->headerIndex_ = -1;
    algorithm->footerIndex_ = 0;
    algorithm->UpdateHeaderAndFooterMargin(AceType::RawPtr(layoutWrapper));
    algorithm->headerIndex_ = 0;
    algorithm->UpdateHeaderAndFooterMargin(AceType::RawPtr(layoutWrapper));
    menuItemGroupPattern->hasSelectIcon_ = true;
    algorithm->headerIndex_ = -1;
    algorithm->UpdateHeaderAndFooterMargin(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(footerLayoutProps->margin_);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
    algorithm->UpdateHeaderAndFooterMargin(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(footerLayoutProps->margin_);
}

/**
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg006
 * @tc.desc: Test NeedHeaderPadding and NeedFooterPadding.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg006, TestSize.Level1)
{
    MenuModelNG model;
    model.Create();
    auto menu = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menu, nullptr);
    auto menuPattern = menu->GetPattern<InnerMenuPattern>();
    auto menuItem = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemPattern>());
    menuPattern->itemsAndGroups_.push_back(menuItem);
    // create menu item group
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    menuItemGroup->MountToParent(menu);

    auto algorithm = AceType::MakeRefPtr<MenuItemGroupLayoutAlgorithm>(-1, -1, 0);
    ASSERT_NE(algorithm, nullptr);

    bool needHeaderPadding = algorithm->NeedHeaderPadding(menuItemGroup);
    EXPECT_EQ(needHeaderPadding, false);
    bool needFooterPadding = algorithm->NeedFooterPadding(menuItemGroup);
    EXPECT_EQ(needFooterPadding, true);
}
/**
 * @tc.name: MenuItemGroupPaintMethod001
 * @tc.desc: Test MenuItemGroup GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuItemGroupPaintProperty> paintProp = AceType::MakeRefPtr<MenuItemGroupPaintProperty>();
    RefPtr<MenuItemGroupPaintMethod> paintMethod = AceType::MakeRefPtr<MenuItemGroupPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    /**
     * @tc.steps: step2. update paint property and execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdateNeedHeaderPadding(true);
    paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdateNeedFooterPadding(true);
    paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuItemGroupPaintMethod002
 * @tc.desc: Test MenuItem GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuItemGroupPaintProperty> paintProp = AceType::MakeRefPtr<MenuItemGroupPaintProperty>();
    RefPtr<MenuItemGroupPaintMethod> paintMethod = AceType::MakeRefPtr<MenuItemGroupPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    /**
     * @tc.steps: step2. update paint property and execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdateNeedHeaderPadding(true);
    paintProp->UpdateNeedFooterPadding(true);
    paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: MenuItemGroupPaintMethod003
 * @tc.desc: Test MenuItem GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<MenuItemGroupPaintProperty> paintProp = AceType::MakeRefPtr<MenuItemGroupPaintProperty>();
    RefPtr<MenuItemGroupPaintMethod> paintMethod = AceType::MakeRefPtr<MenuItemGroupPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    /**
     * @tc.steps: step2. update paint property and execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    result(canvas);
    delete paintWrapper;
    paintWrapper = nullptr;
    paintProp->UpdateNeedHeaderPadding(true);
    paintProp->UpdateNeedFooterPadding(true);
    paintProp->UpdateNeedHeaderDivider(true);
    paintProp->UpdateNeedFooterDivider(true);
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
 * @tc.name: MenuItemGroupPaintMethod004
 * @tc.desc: Test MenuItem GetOverlayDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPaintMethod004, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));

    auto paintProp = AceType::MakeRefPtr<MenuItemGroupPaintProperty>();
    auto paintMethod = AceType::MakeRefPtr<MenuItemGroupPaintMethod>();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));

    WeakPtr<RenderContext> renderContext;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    ASSERT_NE(result, nullptr);

    auto paintProp2 = AceType::DynamicCast<MenuItemGroupPaintProperty>(paintWrapper->GetPaintProperty());
    ASSERT_NE(paintProp2, nullptr);
    paintProp2->UpdateNeedFooterPadding(true);
    paintProp2->UpdateNeedFooterDivider(false);
    paintProp2->UpdateStartMargin(Dimension(1.0f, DimensionUnit::INVALID));
    paintProp2->UpdateStrokeWidth(Dimension(1.0f, DimensionUnit::INVALID));
    paintProp2->UpdateEndMargin(Dimension(1.0f, DimensionUnit::INVALID));
    paintProp2->UpdateDividerColor(Color::FOREGROUND);
    result(canvas);
    EXPECT_EQ(paintProp2->GetStartMargin()->Unit(), DimensionUnit::INVALID);

    paintMethod = nullptr;
    result(canvas);
    delete paintWrapper;
}

/**
 * @tc.name: MenuItemGroupPattern001
 * @tc.desc: Test MenuItemGroup pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPattern001, TestSize.Level1)
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

    menuPattern->OnModifyDone();

    auto contentNode = itemPattern->GetContentNode();
    ASSERT_NE(contentNode, nullptr);
    auto textProperty = contentNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textProperty, nullptr);

    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    menuItemGroup->MountToParent(menuNode);
    menuItemGroupPattern->hasSelectIcon_ = true;
    menuItemGroupPattern->headerContent_ = contentNode;
    menuItemGroupPattern->OnMountToParentDone();
    menuItemGroupPattern->footerContent_ = contentNode;
    menuItemGroupPattern->OnMountToParentDone();
    RefPtr<NG::UINode> headerNode;
    headerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    menuItemGroupPattern->AddHeader(headerNode);
    RefPtr<NG::UINode> footerNode;
    footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    menuItemGroupPattern->AddFooter(footerNode);
    EXPECT_EQ(menuItemGroupPattern->headerIndex_, 0);
    EXPECT_EQ(menuItemGroupPattern->footerIndex_, 1);
    menuItemGroupPattern->headerIndex_ = 0;
    menuItemGroupPattern->footerIndex_ = 0;
    menuItemGroupPattern->AddHeader(headerNode);
    EXPECT_FALSE(menuItemGroupPattern->GetMenu() == nullptr);
}

/**
 * @tc.name: MenuItemGroupPattern002
 * @tc.desc: Test MenuItemGroup pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPattern002, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    RefPtr<NG::UINode> footerNode;
    footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    menuItemGroupPattern->footerIndex_ = 0;
    menuItemGroupPattern->AddFooter(footerNode);
    EXPECT_EQ(menuItemGroupPattern->footerIndex_, 0);
}

/**
 * @tc.name: MenuItemGroupPattern003
 * @tc.desc: Test MenuItemGroup pattern.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPattern003, TestSize.Level1)
{
    MenuModelNG MneuModelInstance;
    MenuItemModelNG MneuItemModelInstance;
    MneuModelInstance.Create();
    MneuModelInstance.SetFontSize(Dimension(25.0));
    MneuModelInstance.SetFontColor(Color::RED);
    MneuModelInstance.SetFontWeight(FontWeight::BOLD);

    auto menuNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(menuNode, nullptr);

    auto menuItemGroupPattern1 = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup1 = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 1, menuItemGroupPattern1);
    ASSERT_NE(menuItemGroup1, nullptr);
    menuItemGroup1->MountToParent(menuNode);

    auto menuItemGroupPattern2 = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup2 = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 2, menuItemGroupPattern2);
    ASSERT_NE(menuItemGroup2, nullptr);
    menuItemGroup2->MountToParent(menuNode);

    auto menuItemGroupPattern3 = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup3 = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 3, menuItemGroupPattern3);
    ASSERT_NE(menuItemGroup3, nullptr);
    menuItemGroup3->MountToParent(menuNode);

    bool press = true;
    int32_t index = 0;
    menuItemGroupPattern2->OnIntItemPressed(index, press);
    auto needFooterDivider = menuItemGroup1->GetPaintProperty<MenuItemGroupPaintProperty>()->propNeedFooterDivider_;
    EXPECT_EQ(needFooterDivider, false);

    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(menuItemGroup2);
    menuItemGroupPattern2->OnIntItemPressed(index, press);
    auto needHeaderDivider = menuItemGroup3->GetPaintProperty<MenuItemGroupPaintProperty>()->propNeedHeaderDivider_;
    EXPECT_EQ(needHeaderDivider, false);
}

/**
 * @tc.name: MenuItemGroupPattern004
 * @tc.desc: Test MenuItemGroupView SetHeader method.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupPattern004, TestSize.Level1)
{
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    MenuItemGroupView menuItemGroupView;
    menuItemGroupView.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    std::string headerStr = "head";
    menuItemGroupView.SetHeader(headerStr);
    ASSERT_NE(menuItemPattern->headerContent_, nullptr);
    auto layoutProps = menuItemPattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProps, nullptr);
    EXPECT_EQ(layoutProps->GetFontSize(), selectTheme->GetMenuFontSize());

    int32_t settingApiVersion = 12;
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(settingApiVersion);
    menuItemGroupView.SetHeader(headerStr);
    ASSERT_NE(menuItemPattern->headerContent_, nullptr);
    auto layoutProps2 = menuItemPattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProps2, nullptr);
    EXPECT_EQ(layoutProps2->GetFontWeight(), FontWeight::BOLD);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: AddHeaderNull
 * @tc.desc: Test MenuItemGroup pattern AddHeader with null ptr.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, AddHeaderNull, TestSize.Level1)
{
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    MenuItemGroupView menuItemGroupView;
    menuItemGroupView.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    RefPtr<NG::UINode> headerNode;
    headerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    menuItemPattern->headerContent_ = nullptr;
    menuItemPattern->headerIndex_ = -1;
    menuItemPattern->itemStartIndex_ = START_INDEX;
    menuItemPattern->AddHeader(headerNode);
    EXPECT_EQ(menuItemPattern->headerIndex_, START_INDEX);
    EXPECT_EQ(menuItemPattern->itemStartIndex_, START_INDEX + 1);
}

/**
 * @tc.name: AddFooterNormal
 * @tc.desc: Test MenuItemGroup pattern AddFooter.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, AddFooterNormal, TestSize.Level1)
{
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    MenuItemGroupView menuItemGroupView;
    menuItemGroupView.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    std::string footerStr = "foot";
    menuItemGroupView.SetFooter(footerStr);
    ASSERT_NE(menuItemPattern->footerContent_, nullptr);

    RefPtr<NG::UINode> footerNode;
    footerNode = NG::ViewStackProcessor::GetInstance()->Finish();

    frameNode->isRestoreInfoUsed_ = false;
    menuItemPattern->footerIndex_ = FOOT_INDEX;
    menuItemPattern->itemStartIndex_ = START_INDEX;
    menuItemPattern->AddFooter(footerNode);
    EXPECT_NE(menuItemPattern->footerContent_, nullptr);
    EXPECT_EQ(menuItemPattern->footerIndex_, START_INDEX);
    EXPECT_EQ(frameNode->isRestoreInfoUsed_, false);
}

/**
 * @tc.name: AddFooterNull
 * @tc.desc: Test MenuItemGroup pattern AddFooter with null ptr.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, AddFooterNull, TestSize.Level1)
{
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    MenuItemGroupView menuItemGroupView;
    menuItemGroupView.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto menuItemPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemPattern, nullptr);

    std::string footerStr = "foot";
    menuItemGroupView.SetFooter(footerStr);
    ASSERT_NE(menuItemPattern->footerContent_, nullptr);
    
    RefPtr<NG::UINode> footerNode;
    footerNode = NG::ViewStackProcessor::GetInstance()->Finish();

    menuItemPattern->footerContent_ = nullptr;
    frameNode->isRestoreInfoUsed_ = false;
    menuItemPattern->footerIndex_ = FOOT_INDEX;
    menuItemPattern->itemStartIndex_ = START_INDEX;
    menuItemPattern->AddFooter(footerNode);

    EXPECT_EQ(menuItemPattern->footerContent_, nullptr);
    EXPECT_EQ(menuItemPattern->footerIndex_, START_INDEX);
    EXPECT_EQ(frameNode->isRestoreInfoUsed_, false);
}
} // namespace OHOS::Ace::NG
