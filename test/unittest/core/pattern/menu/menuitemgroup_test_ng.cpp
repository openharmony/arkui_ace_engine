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
constexpr float BLUR_STYLE_SCALE = 1.5f;
constexpr float EFFECT_SATURATION = 1.2f;
constexpr float BLUR_OPTION = 0.5f;
constexpr float BRIGHTNESS = 0.8f;
constexpr float RADIUS = 10.0f;
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
    RefPtr<MenuTheme> menuTheme_ = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([menuTheme_](ThemeType type) -> RefPtr<Theme> {
        if (type == MenuTheme::TypeId()) {
            return menuTheme_;
        }
        return AceType::MakeRefPtr<SelectTheme>();
    });
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
 * @tc.name: MenuItemGroupLayoutAlgorithmTestNg007
 * @tc.desc: Test MATCH_PARENT、WRAP_CONTENT and FIX_AT_IDEAL_SIZE.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupLayoutAlgorithmTestNg007, TestSize.Level1)
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
        SizeF frameSize(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT);
        itemGeoNode->SetFrameSize(frameSize);
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        layoutWrapper->AppendChild(childWrapper);
    }
    props->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    props->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    SizeF frameSize(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT);
    auto isUpdate = algorithm->UpdateLayoutSizeBasedOnPolicy(layoutWrapper, frameSize);
    EXPECT_TRUE(isUpdate);
    props->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    props->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
    isUpdate = algorithm->UpdateLayoutSizeBasedOnPolicy(layoutWrapper, frameSize);
    EXPECT_TRUE(isUpdate);
    props->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
    props->UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    isUpdate = algorithm->UpdateLayoutSizeBasedOnPolicy(layoutWrapper, frameSize);
    EXPECT_FALSE(isUpdate);
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
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    renderContext->SetHostNode(wrapperNode);
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
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    renderContext->SetHostNode(wrapperNode);
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
    RefPtr<RenderContext> renderContext = AceType::MakeRefPtr<RenderContext>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    renderContext->SetHostNode(wrapperNode);
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

/**
 * @tc.name: UpdateMenuBackgroundStyle001
 * @tc.desc: MenuView UpdateMenuBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, UpdateMenuBackgroundStyle001, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));

    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    blurStyleOption.colorMode = ThemeColorMode::DARK;
    menuParam.blurStyleOption = blurStyleOption;

    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetBackBlurStyle(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->colorMode, ThemeColorMode::DARK);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: UpdateMenuBackgroundStyle002
 * @tc.desc: MenuView UpdateMenuBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, UpdateMenuBackgroundStyle002, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));

    MenuParam menuParam;
    EffectOption effectOption;
    effectOption.saturation = 6.0f;
    menuParam.effectOption = effectOption;

    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetBackgroundEffect(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->saturation, effectOption.saturation);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: UpdateMenuBackgroundStyle003
 * @tc.desc: MenuView UpdateMenuBackgroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, UpdateMenuBackgroundStyle003, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));

    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    effectOption.saturation = 6.0f;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetBackBlurStyle(), std::nullopt);
    ASSERT_NE(renderContext->GetBackgroundEffect(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->saturation, effectOption.saturation);

    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SetBackgroundBlurStyle001
 * @tc.desc: MenuView SetBackgroundBlurStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, SetBackgroundBlurStyle001, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    BlurStyleOption option { .blurStyle = BlurStyle::REGULAR,
        .colorMode = ThemeColorMode::LIGHT,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .scale = BLUR_STYLE_SCALE,
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color::FromARGB(128, 0, 0, 0),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundBlurStyleOption = option;
    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetBackBlurStyle(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->colorMode, ThemeColorMode::LIGHT);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SetBackgroundBlurStyle002
 * @tc.desc: MenuView SetBackgroundBlurStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, SetBackgroundBlurStyle002, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    BlurStyleOption option { .blurStyle = BlurStyle::REGULAR,
        .colorMode = ThemeColorMode::LIGHT,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .scale = BLUR_STYLE_SCALE,
        .policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color::FromARGB(128, 0, 0, 0),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundBlurStyleOption = option;
    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetBackBlurStyle(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->colorMode, ThemeColorMode::LIGHT);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SetBackgroundBlurStyle003
 * @tc.desc: MenuView SetBackgroundBlurStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, SetBackgroundBlurStyle003, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    BlurStyleOption option { .blurStyle = BlurStyle::REGULAR,
        .colorMode = ThemeColorMode::LIGHT,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .scale = BLUR_STYLE_SCALE,
        .policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color::FromARGB(128, 0, 0, 0),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundBlurStyleOption = option;
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    const auto& groupProperty = renderContext->GetOrCreateBackground();
    groupProperty->propBlurRadius = std::make_optional<Dimension>(1.0f);
    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    ASSERT_NE(renderContext->GetBackBlurStyle(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackBlurStyle()->colorMode, ThemeColorMode::LIGHT);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SetBackgroundEffect001
 * @tc.desc: MenuView SetBackgroundEffect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, SetBackgroundEffect001, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    BlurStyleOption option { .blurStyle = BlurStyle::REGULAR,
        .colorMode = ThemeColorMode::LIGHT,
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .scale = BLUR_STYLE_SCALE,
        .policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE,
        .blurType = BlurType::WITHIN_WINDOW,
        .inactiveColor = Color::FromARGB(128, 0, 0, 0),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundBlurStyleOption = option;
    EffectOption optionNew { .radius = Dimension(RADIUS, DimensionUnit::PX),
        .saturation = EFFECT_SATURATION,
        .brightness = BRIGHTNESS,
        .color = Color(Color::RED),
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = BlurOption { std::vector<float> { BLUR_OPTION, BLUR_OPTION } },
        .blurType = BlurType::BEHIND_WINDOW,
        .policy = BlurStyleActivePolicy::ALWAYS_ACTIVE,
        .inactiveColor = Color(Color::BLUE),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundEffectOption = optionNew;
    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetBackgroundEffect(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->saturation, EFFECT_SATURATION);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SetBackgroundEffect002
 * @tc.desc: MenuView SetBackgroundEffect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, SetBackgroundEffect002, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    EffectOption option { .radius = Dimension(RADIUS, DimensionUnit::PX),
        .saturation = EFFECT_SATURATION,
        .brightness = BRIGHTNESS,
        .color = Color(Color::RED),
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = BlurOption { std::vector<float> { BLUR_OPTION, BLUR_OPTION } },
        .blurType = BlurType::BEHIND_WINDOW,
        .policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE,
        .inactiveColor = Color(Color::BLUE),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundEffectOption = option;
    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(renderContext->GetBackgroundEffect(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->saturation, EFFECT_SATURATION);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: SetBackgroundEffect003
 * @tc.desc: MenuView SetBackgroundEffect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, SetBackgroundEffect003, TestSize.Level1)
{
    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MenuParam menuParam;
    BlurStyleOption blurStyleOption;
    EffectOption effectOption;
    blurStyleOption.colorMode = ThemeColorMode::LIGHT;
    menuParam.blurStyleOption = blurStyleOption;
    menuParam.effectOption = effectOption;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    EffectOption option { .radius = Dimension(RADIUS, DimensionUnit::PX),
        .saturation = EFFECT_SATURATION,
        .brightness = BRIGHTNESS,
        .color = Color(Color::RED),
        .adaptiveColor = AdaptiveColor::AVERAGE,
        .blurOption = BlurOption { std::vector<float> { BLUR_OPTION, BLUR_OPTION } },
        .blurType = BlurType::BEHIND_WINDOW,
        .policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE,
        .inactiveColor = Color(Color::BLUE),
        .isValidColor = true,
        .isWindowFocused = false };
    menuParam.backgroundEffectOption = option;
    auto renderContext = menuNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    const auto& groupProperty = renderContext->GetOrCreateBackground();
    groupProperty->propBlurRadius = std::make_optional<Dimension>(1.0f);
    MenuView::UpdateMenuBackgroundStyle(menuNode, menuParam);
    ASSERT_NE(renderContext->GetBackgroundEffect(), std::nullopt);
    EXPECT_EQ(renderContext->GetBackgroundEffect()->saturation, EFFECT_SATURATION);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: MenuItemGroupSetHeaderContentTest001
 * @tc.desc: Test MenuItemGroupPattern::SetHeaderContent with valid header content
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupSetHeaderContentTest001, TestSize.Level1)
{
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    ASSERT_NE(menuItemGroupPattern, nullptr);

    menuItemGroupPattern->headerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(menuItemGroupPattern->headerContent_, nullptr);

    std::string testText = "Test Header Content";
    menuItemGroupPattern->SetHeaderContent(testText);

    auto textLayoutProperty = menuItemGroupPattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_EQ(textLayoutProperty->GetContentValue(), UtfUtils::Str8DebugToStr16(testText));
}

/**
 * @tc.name: MenuItemGroupSetFooterContentTest001
 * @tc.desc: Test MenuItemGroupPattern::SetFooterContent with valid footer content
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, MenuItemGroupSetFooterContentTest001, TestSize.Level1)
{
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    ASSERT_NE(menuItemGroupPattern, nullptr);

    menuItemGroupPattern->footerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(menuItemGroupPattern->footerContent_, nullptr);

    std::string testText = "Test Footer Content";

    menuItemGroupPattern->SetFooterContent(testText);

    auto textLayoutProperty = menuItemGroupPattern->footerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_EQ(textLayoutProperty->GetContentValue(), UtfUtils::Str8DebugToStr16(testText));
}

/**
 * @tc.name: RemoveParentRestrictionsForFixIdeal001
 * @tc.desc: Test MenuItemGroup RemoveParentRestrictionsForFixIdeal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, RemoveParentRestrictionsForFixIdeal001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu item group.
     */
    auto menuItemGroupPattern = AceType::MakeRefPtr<MenuItemGroupPattern>();
    auto menuItemGroup = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, -1, menuItemGroupPattern);
    auto algorithm = AceType::MakeRefPtr<MenuItemGroupLayoutAlgorithm>(-1, -1, 0);
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<LayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItemGroup, geometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. LayoutCalPolicy is default and set maxSize to FULL_SCREEN_SIZE.
     * @tc.expected: childConstraint.maxSize is equal to FULL_SCREEN_SIZE.
     */
    LayoutConstraintF childConstraint;
    childConstraint.maxSize = FULL_SCREEN_SIZE;
    auto props = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(props, nullptr);
    props->UpdateLayoutConstraint(childConstraint);
    props->UpdateContentConstraint();
    LayoutPolicyProperty layoutPolicyProperty;
    props->layoutPolicy_ = layoutPolicyProperty;
    algorithm->RemoveParentRestrictionsForFixIdeal(layoutProp, childConstraint);
    EXPECT_EQ(childConstraint.maxSize.Width(), FULL_SCREEN_SIZE.Width());
    EXPECT_EQ(childConstraint.maxSize.Height(), FULL_SCREEN_SIZE.Height());

    /**
     * @tc.steps: step3. LayoutCalPolicy is FIX_AT_IDEAL_SIZE and set maxSize to FULL_SCREEN_SIZE.
     * @tc.expected: childConstraint.maxSize is infinity.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    props->layoutPolicy_ = layoutPolicyProperty;
    algorithm->RemoveParentRestrictionsForFixIdeal(layoutProp, childConstraint);
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Width()));
    EXPECT_TRUE(std::isinf(childConstraint.maxSize.Height()));
}

/**
 * @tc.name: AttachBottomDivider001
 * @tc.desc: Testing the AttachBottomDivider method without a parent container.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, AttachBottomDivider001, TestSize.Level1)
{
    MenuItemGroupPattern menuItemGroupPattern;
    menuItemGroupPattern.bottomDivider_ =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemGroupPattern>());
    auto dividerParent =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemGroupPattern>());
    ASSERT_NE(dividerParent, nullptr);
    menuItemGroupPattern.bottomDivider_->parent_ = std::move(dividerParent);
    auto node = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemGroupPattern>());
    ASSERT_NE(node, nullptr);
    auto menuItemNode =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemGroupPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    node->parent_ = std::move(menuItemNode);
    menuItemGroupPattern.frameNode_ = std::move(node);
    auto host = menuItemGroupPattern.GetHost();
    ASSERT_NE(host, nullptr);
    auto parent = host->GetParent();
    ASSERT_NE(parent, nullptr);
    menuItemGroupPattern.AttachBottomDivider();
    EXPECT_EQ(parent->GetChildIndex(node), -1);
}

/**
 * @tc.name: AttachBottomDivider002
 * @tc.desc: Testing the AttachBottomDivider method has a parent container.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, AttachBottomDivider002, TestSize.Level1)
{
    MenuItemGroupPattern menuItemGroupPattern;
    menuItemGroupPattern.bottomDivider_ =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 1, AceType::MakeRefPtr<MenuItemGroupPattern>());
    auto node = FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 2, AceType::MakeRefPtr<MenuItemGroupPattern>());
    ASSERT_NE(node, nullptr);
    auto menuItemNode =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_GROUP_ETS_TAG, 3, AceType::MakeRefPtr<MenuItemGroupPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    menuItemGroupPattern.frameNode_ = std::move(node);
    auto host = menuItemGroupPattern.GetHost();
    ASSERT_NE(host, nullptr);
    host->MountToParent(menuItemNode);
    auto parent = host->GetParent();
    ASSERT_NE(parent, nullptr);
    menuItemGroupPattern.AttachBottomDivider();
    EXPECT_EQ(parent->GetChildIndex(node), 0);
}

/**
 * @tc.name: OnColorConfigurationUpdateTest001
 * @tc.desc: Test OnColorConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, OnColorConfigurationUpdateTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create MenuItemGroupView and get frame node
     * @tc.expected: View and frame node created successfully
     */
    MenuItemGroupView menuItemGroupView;
    menuItemGroupView.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto menuItemGroupPattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(menuItemGroupPattern, nullptr);

    /**
     * @tc.steps2: Set up theme manager mock
     * @tc.expected: Theme manager returns select theme
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([=](ThemeType type) -> RefPtr<Theme> {
        return selectTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    /**
     * @tc.steps3: Create header and footer content
     * @tc.expected: Header and footer frame nodes created
     */
    menuItemGroupPattern->headerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(menuItemGroupPattern->headerContent_, nullptr);
    menuItemGroupPattern->footerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(menuItemGroupPattern->footerContent_, nullptr);

    /**
     * @tc.steps4: Get layout properties and themes
     * @tc.expected: Layout properties and themes obtained
     */
    auto headercontent = menuItemGroupPattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(headercontent, nullptr);
    auto headerpipeline = menuItemGroupPattern->headerContent_->GetContextWithCheck();
    ASSERT_NE(headerpipeline, nullptr);
    auto headermenuTheme = headerpipeline->GetTheme<SelectTheme>();
    ASSERT_NE(headermenuTheme, nullptr);

    auto footercontent = menuItemGroupPattern->footerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(footercontent, nullptr);
    auto footerpipeline = menuItemGroupPattern->footerContent_->GetContextWithCheck();
    ASSERT_NE(footerpipeline, nullptr);
    auto footermenuTheme = footerpipeline->GetTheme<SelectTheme>();
    ASSERT_NE(footermenuTheme, nullptr);

    /**
     * @tc.steps5: Set theme colors
     * @tc.expected: Theme colors set to red and blue
     */
    Color menuFontColor = Color::RED;
    Color secondaryFontColor = Color::BLUE;
    headermenuTheme->menuFontColor_ = menuFontColor;
    footermenuTheme->secondaryFontColor_ = secondaryFontColor;

    /**
     * @tc.steps6: Test with config change disabled
     * @tc.expected: Text colors not updated
     */
    g_isConfigChangePerform = false;
    EXPECT_EQ(SystemProperties::ConfigChangePerform(), false);
    menuItemGroupPattern->OnColorConfigurationUpdate();
    EXPECT_NE(headercontent->GetTextColor().value_or(Color::BLACK), headermenuTheme->GetMenuFontColor());
    EXPECT_NE(footercontent->GetTextColor().value_or(Color::BLACK), footermenuTheme->GetSecondaryFontColor());

    /**
     * @tc.steps7: Test with config change enabled
     * @tc.expected: Text colors updated to theme values
     */
    g_isConfigChangePerform = true;
    ASSERT_NE(SystemProperties::ConfigChangePerform(), false);
    menuItemGroupPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(headercontent->GetTextColor(), menuFontColor);
    EXPECT_EQ(footercontent->GetTextColor().value(), secondaryFontColor);
}

/**
 * @tc.name: MenuItemGroupViewCreateWithStringResourceObj001
 * @tc.desc: Test CreateWithStringResourceObj with HEADER types.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, CreateWithStringResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps1: Create MenuItemGroupView and get frame node
     * @tc.expected: View and frame node created successfully
     */
    MenuItemGroupView view;
    view.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps2: Create header content
     * @tc.expected: Header frame node created
     */
    pattern->headerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pattern->headerContent_, nullptr);
    auto textLayoutProperty = pattern->headerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps3: Call CreateWithStringResourceObj for header
     * @tc.expected: Resource object associated with header
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    view.CreateWithStringResourceObj(resObj, MenuItemGroupStringType::HEADER);

    /**
     * @tc.steps4: Test with empty resource cache
     * @tc.expected: Header content is empty
     */
    std::string str = "";
    std::string key = "MenuItemGroup" + MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::HEADER);
    pattern->AddResCache(key, str);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
    EXPECT_EQ(textLayoutProperty->GetContentValue(u""), u"");

    /**
     * @tc.steps5: Test with valid resource cache
     * @tc.expected: Header content updated to "TEST"
     */
    str = "TEST";
    pattern->AddResCache(key, str);
    resMgr->ReloadResources();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), UtfUtils::Str8DebugToStr16(str));
}

/**
 * @tc.name: MenuItemGroupViewCreateWithStringResourceObj002
 * @tc.desc: Test CreateWithStringResourceObj with FOOTER types.
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, CreateWithStringResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps1: Create MenuItemGroupView and get frame node
     * @tc.expected: View and frame node created successfully
     */
    MenuItemGroupView view;
    view.Create();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemGroupPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps2: Create footer content
     * @tc.expected: Footer frame node created
     */
    pattern->footerContent_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(pattern->footerContent_, nullptr);
    auto textLayoutProperty = pattern->footerContent_->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps3: Call CreateWithStringResourceObj for footer
     * @tc.expected: Resource object associated with footer
     */
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    view.CreateWithStringResourceObj(resObj, MenuItemGroupStringType::FOOTER);

    /**
     * @tc.steps4: Test with valid resource cache
     * @tc.expected: Footer content updated to "TEST"
     */
    std::string str = "TEST";
    std::string key = "MenuItemGroup" + MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::FOOTER);
    pattern->AddResCache(key, str);
    auto resMgr = pattern->resourceMgr_;
    ASSERT_NE(resMgr, nullptr);
    resMgr->ReloadResources();
    EXPECT_EQ(textLayoutProperty->GetContentValue(), UtfUtils::Str8DebugToStr16(str));
}

/**
 * @tc.name: StringTypeToString
 * @tc.desc: Test StringTypeToString
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupTestNg, StringTypeToString, TestSize.Level1)
{
    /**
     * @tc.steps1: Test HEADER string conversion
     * @tc.expected: Returns "Header"
     */
    std::string result1 = MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::HEADER);
    EXPECT_EQ(result1, "Header");

    /**
     * @tc.steps2: Test FOOTER string conversion
     * @tc.expected: Returns "Footer"
     */
    std::string result2 = MenuItemGroupView::StringTypeToString(MenuItemGroupStringType::FOOTER);
    EXPECT_EQ(result2, "Footer");

    /**
     * @tc.steps3: Test unknown type conversion
     * @tc.expected: Returns "Unknown" for type 100
     */
    MenuItemGroupStringType unknownType = static_cast<MenuItemGroupStringType>(100);
    std::string result3 = MenuItemGroupView::StringTypeToString(unknownType);
    EXPECT_EQ(result3, "Unknown");
}
} // namespace OHOS::Ace::NG
