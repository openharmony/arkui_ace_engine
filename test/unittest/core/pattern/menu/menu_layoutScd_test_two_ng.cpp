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
#include "core/pipeline/pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t TARGET_ID = 3;
constexpr MenuType TYPE = MenuType::MENU;
constexpr float CURRENT_OFFSET = -0.5f;
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
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;


const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
constexpr double DIP_SCALE = 1.5;
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
constexpr float SCALE_ANIMATION_FIRST = 0.8f;

const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuLayout2TwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuLayout2TwoTestNg::SetUpTestCase() {}

void MenuLayout2TwoTestNg::TearDownTestCase() {}

void MenuLayout2TwoTestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayout2TwoTestNg::TearDown()
{
    MockContainer::TearDown();
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

RefPtr<FrameNode> MenuLayout2TwoTestNg::GetPreviewMenuWrapper(
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

void MenuLayout2TwoTestNg::MockPipelineContextGetTheme()
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


/**
 * @tc.name: SubMenuLayoutAlgorithmTestNg002
 * @tc.desc: Test SubMenuLayoutAlgorithm InitializePaddingAPI12 function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, SubMenuLayoutAlgorithmTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutSubMenuHalfScreen method
     * @tc.expected: submenu node, subMenuLayoutAlgorithm are not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();

    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);

    // create subMenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);

    // link menuItem and submenu
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
    auto result = algorithm->VerticalLayoutSubMenuHalfScreen(menuNode->GetGeometryNode()->GetFrameSize(),
        algorithm->position_.GetY(), item->GetGeometryNode()->GetFrameSize(), item, false, nullptr);
    ASSERT_EQ(result, 0.0f);
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;
    algorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    algorithm->ModifySubMenuWrapper(wrapper);
    ASSERT_EQ(algorithm->wrapperSize_, SizeF(0, 0));

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
 * @tc.name: SubMenuLayoutAlgorithmTestNg003
 * @tc.desc: Test SubMenuLayoutAlgorithm InitializePaddingAPI12 function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, SubMenuLayoutAlgorithmTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu item and submenu, set the layering parameter to false and call the
     * VerticalLayoutSubMenuHalfScreen method
     * @tc.expected: submenu node, subMenuLayoutAlgorithm are not null
     */
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();

    // create parent menu item
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);

    // create subMenuLayoutAlgorithm
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);
    ASSERT_TRUE(menuPattern);

    // associated menuItem and submenu
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
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    auto result = algorithm->VerticalLayoutSubMenuHalfScreen(menuNode->GetGeometryNode()->GetFrameSize(),
        algorithm->position_.GetY(), item->GetGeometryNode()->GetFrameSize(), item, false, nullptr);
    ASSERT_EQ(result, 0.0f);
    SizeF size_f(100, 200);
    algorithm->wrapperSize_ = size_f;
    algorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());

    /**
     * @tc.steps: step2. call the ModifySubMenuWrapper method.
     * @tc.expected: wrapperSize_ is not Data anomalies
     */
    algorithm->ModifySubMenuWrapper(wrapper);
    ASSERT_EQ(algorithm->wrapperSize_, SizeF(0, 0));

    /**
     * @tc.cases: case2. layering parameter is false.
     * @tc.expected: padding is not zero
     */
    algorithm->canExpandCurrentWindow_ = false;
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->menuLargeMargin_ = 10.0_vp;
    algorithm->InitializePaddingAPI12(wrapper);
    ASSERT_EQ(algorithm->paddingStart_, 10.0f);
    ASSERT_EQ(algorithm->paddingEnd_, 10.0f);
    ASSERT_EQ(algorithm->paddingTop_, 0.0f);
    ASSERT_EQ(algorithm->paddingBottom_, 0.0f);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg5900
 * @tc.desc: Verify Initialize and Measure when hierarchicalParameter is true.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, MenuLayoutAlgorithmTestNg5900, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menuWrapperNode and menuNode.
     * @tc.expected: menuWrapperNode and menuNode are not null.
     */
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    /**
     * @tc.steps: step2. build menu layoutwrapper and set the hierarchical parameter to true.
     * @tc.expected: no exception in the method return value.
     */
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    int32_t backApiversion = container->GetApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    container->SetApiTargetVersion(backApiversion);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg6000
 * @tc.desc: Verify Initialize and Measure when hierarchicalParameter is false.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, MenuLayoutAlgorithmTestNg6000, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a menuWrapperNode and menuNode.
     * @tc.expected: menuWrapperNode and menuNode are not null.
     */
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    /**
     * @tc.steps: step2. build menu layoutwrapper and set the hierarchical parameter to false.
     * @tc.expected: no exception in the method return value.
     */
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->canExpandCurrentWindow_ = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    int32_t backApiversion = container->GetApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    container->SetApiTargetVersion(backApiversion);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg038
 * @tc.desc: Test InitTargetSizeAndPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, MenuLayoutAlgorithmInitTarget, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm and target is null
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(nodeId, TEXT_TAG, MenuType::CONTEXT_MENU);
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(nodeId, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    menuLayoutAlgorithm->targetNodeId_ = nodeId;
    menuLayoutAlgorithm->targetTag_ = "text";
    auto target = FrameNode::GetOrCreateFrameNode("text", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(target, nullptr);

    /**
     * @tc.steps: step3. layoutWrapper, target node and the geometry node of target is not null, isContextMenu is false
     * @tc.expected: targetOffset_ is OffsetF(0.0f, 0.0f)
     */
    std::vector<SelectParam> params;
    params.push_back({ "MenuItem", "Icon" });
    auto frameNode = MenuView::Create(params, 1, EMPTY_TEXT);
    ASSERT_NE(frameNode, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode* layoutWrapper =
        new LayoutWrapperNode(frameNode, menuGeometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    geometryNode->frame_ = geometryProperty;
    target->geometryNode_ = geometryNode;
    menuLayoutAlgorithm->InitTargetSizeAndPosition(layoutWrapper, false, menuPattern);
    EXPECT_EQ(menuLayoutAlgorithm->targetOffset_, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg043
 * @tc.desc: Test Measure with preview content
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, MenuLayoutAlgorithmTestNg043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. device type is PHONE and orientation is LANDSCAPE, create menu node, preview node and
     * menuLayoutAlgorithm, then set the initial properties
     * @tc.expected: menu node, preview node and menuLayoutAlgorithm are not null
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    menuAlgorithm->Measure(&layoutWrapper);
    menuPattern->SetIsHeightModifiedBySelect(true);
    menuLayoutProperty->UpdateSelectModifiedHeight(CURRENT_OFFSET);
    /**
     * @tc.steps: step2. call Measure function
     * @tc.expected: the placement of the menu defaults to RIGHT_TOP
     */
    menuAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(menuPattern->IsHeightModifiedBySelect());
    EXPECT_TRUE(LessOrEqual(CURRENT_OFFSET, menuAlgorithm->wrapperRect_.Height() * SCALE_ANIMATION_FIRST));

    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuAlgorithm->wrapperSize_ = size_f;
    menuAlgorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());
    auto result = menuAlgorithm->VerticalLayout(size, clickPosition, true);
    EXPECT_EQ(result, clickPosition);
}

/**
 *@tc.name : IsSelectMenuShowInSubWindow001
 *@tc.desc: If menuNode is nullptr, return false
 *@tc.type: FUNC
 */

HWTEST_F(MenuLayout2TwoTestNg, IsSelectMenuShowInSubWindow001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    menuNode = nullptr;
    bool result = menuAlgorithm->IsSelectMenuShowInSubWindow(&layoutWrapper, menuNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectMenuShowInSubWindow002
 * @tc.desc: If pipelineContext is nullptr, return false
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, IsSelectMenuShowInSubWindow002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    bool result = menuAlgorithm->IsSelectMenuShowInSubWindow(&layoutWrapper, menuNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectMenuShowInSubWindow003
 * @tc.desc: If theme is nullptr, return false.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, IsSelectMenuShowInSubWindow003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme = nullptr;
    auto pipelineContext = AceType::MakeRefPtr<PipelineContext>();
    bool result = menuAlgorithm->IsSelectMenuShowInSubWindow(&layoutWrapper, menuNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectMenuShowInSubWindow004
 * @tc.desc: If menuLayoutProperty is nullptr, return false
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, IsSelectMenuShowInSubWindow004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    auto pipelineContext = AceType::MakeRefPtr<PipelineContext>();
    bool result = menuAlgorithm->IsSelectMenuShowInSubWindow(&layoutWrapper, menuNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectMenuShowInSubWindow005
 * @tc.desc: If theme->GetExpandDisplay() is false, return false
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, IsSelectMenuShowInSubWindow005, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    auto pipelineContext = AceType::MakeRefPtr<PipelineContext>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    menuLayoutProperty = AceType::MakeRefPtr<MenuLayoutProperty>();
    theme->expandDisplay_ = false;
    menuLayoutProperty->UpdateShowInSubWindow(true);
    bool result = menuAlgorithm->IsSelectMenuShowInSubWindow(&layoutWrapper, menuNode);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsSelectMenuShowInSubWindow006
 * @tc.desc: test theme->GetExpandDisplay() is true but menuLayoutProperty->GetShowInSubWindowValue(false) is false,
 * return false
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout2TwoTestNg, IsSelectMenuShowInSubWindow006, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ScreenSystemManager::GetInstance().dipScale_ = DIP_SCALE;
    ScreenSystemManager::GetInstance().screenWidth_ = FULL_SCREEN_WIDTH;
    auto context = PipelineBase::GetCurrentContext();
    if (context) {
        context->dipScale_ = DIP_SCALE;
    }
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuLayoutProperty, nullptr);

    LayoutWrapperNode layoutWrapper(menuNode, menuGeometryNode, menuLayoutProperty);
    auto pipelineContext = AceType::MakeRefPtr<PipelineContext>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    menuLayoutProperty = AceType::MakeRefPtr<MenuLayoutProperty>();
    theme->expandDisplay_ = true;
    menuLayoutProperty->UpdateShowInSubWindow(false);
    bool result = menuAlgorithm->IsSelectMenuShowInSubWindow(&layoutWrapper, menuNode);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG