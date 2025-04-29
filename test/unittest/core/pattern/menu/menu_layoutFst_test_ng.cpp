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
constexpr float POSITION_OFFSET = 100.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr double MENU_OFFSET_X = 10.0;
constexpr double MENU_OFFSET_Y = 10.0;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;

constexpr int CHILD_SIZE_X = 1;
constexpr int CHILD_SIZE_Y = 2;
constexpr int TOP_POSITION_X = 10;
constexpr int TOP_POSITION_Y = 20;
constexpr int BOTTOM_POSITION_X = 30;
constexpr int BOTTOM_POSITION_Y = 40;
constexpr float OFFSET_FIRST = 20.0f;
constexpr float OFFSET_SECOND = 5.0f;
constexpr float OFFSET_THIRD = 200.0f;
constexpr float OFFSET_FORTH = 300.0f;
constexpr float OFFSET_FIFTH = 50.0f;
constexpr float OFFSET_SIXTH = 60.0f;
constexpr int SIZE_X_SECOND = 20;
constexpr int SIZE_Y_SECOND = 20;
constexpr int OFFSET_X_THIRD = 100;
constexpr int OFFSET_Y_THIRD = 20;
constexpr int NODEID = 1;
constexpr int TOP_LEFT_X = 100;
constexpr int TOP_LEFT_Y = 18;
constexpr int TOP_RIGHT_X = 119;
constexpr int TOP_RIGHT_Y = 18;
constexpr int BOTTOM_LEFT_X = 100;
constexpr int BOTTOM_LEFT_Y = 40;
constexpr int BOTTOM_RIGHT_X = 119;
constexpr int BOTTOM_RIGHT_Y = 40;
constexpr int PLACEMENT_LEFT_X = 99;
constexpr int PLACEMENT_LEFT_Y = 29;
constexpr int PLACEMENT_LEFT_TOP_X = 99;
constexpr int PLACEMENT_LEFT_TOP_Y = 20;
constexpr int PLACEMENT_LEFT_BOTTOM_X = 99;
constexpr int PLACEMENT_LEFT_BOTTOM_Y = 38;
constexpr int PLACEMENT_RIGHT_X = 120;
constexpr int PLACEMENT_RIGHT_Y = 29;
constexpr int PLACEMENT_RIGHT_TOP_X = 120;
constexpr int PLACEMENT_RIGHT_TOP_Y = 20;
constexpr int PLACEMENT_RIGHT_BOTTOM_X = 120;
constexpr int PLACEMENT_RIGHT_BOTTOM_Y = 38;
const Dimension CONTENT_PADDING = 4.0_vp;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuLayout1TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    void InitMenuLayout1TestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuLayout1TestNg::SetUpTestCase() {}

void MenuLayout1TestNg::TearDownTestCase() {}

void MenuLayout1TestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayout1TestNg::TearDown()
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

void MenuLayout1TestNg::MockPipelineContextGetTheme()
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

void MenuLayout1TestNg::InitMenuLayout1TestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuLayout1TestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuLayout1TestNg::GetPreviewMenuWrapper(
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
 * @tc.name: MenuLayoutAlgorithmTestNg0
 * @tc.desc: Verify positionOffset of Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg0, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->isSelectMenu_ = true;
    layoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg1
 * @tc.desc: Verify positionOffset of measure.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg1, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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
    layoutAlgorithm->GetPaintProperty(&layoutWrapper)->UpdateEnableArrow(true);
    RefPtr<LayoutWrapperNode> wrapperChild =
        AceType::MakeRefPtr<LayoutWrapperNode>(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.cachedList_.push_back(wrapperChild);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    Placement placements[] = { Placement::TOP, Placement::BOTTOM, Placement::RIGHT, Placement::LEFT,
        Placement::TOP_LEFT, Placement::BOTTOM_LEFT, Placement::LEFT_BOTTOM, Placement::LEFT_TOP,
        Placement::RIGHT_BOTTOM, Placement::RIGHT_TOP, Placement::TOP_RIGHT, Placement::BOTTOM_RIGHT };
    for (Placement placementValue : placements) {
        layoutAlgorithm->arrowPlacement_ = placementValue;
        layoutAlgorithm->UpdatePropArrowOffset();
    }
    layoutAlgorithm->propArrowOffset_.value_ = 1.0;
    layoutAlgorithm->UpdatePropArrowOffset();
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->isSelectMenu_ = true;
    layoutAlgorithm->targetTag_ = EMPTY_TEXT;
    layoutAlgorithm->Layout(&layoutWrapper);
    layoutAlgorithm->LayoutArrow(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg001
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(50, 100);
    SizeF size_f(100, 200);
    float clickPosition = 50.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, clickPosition);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg002
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg002, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(50, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, size_f.Width() - size.Width());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg003
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg003, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(70, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Width() - size.Width());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg004
 * @tc.desc: Verify HorizontalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg004, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 60.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    auto result = menuLayoutAlgorithm->HorizontalLayout(size, clickPosition);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg005
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg005, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, clickPosition);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg006
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg006, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    /**
     * @tc.steps: step1. build follows the click position and wrapper size when there is not enough space at the bottom.
     */
    SizeF size(100, 100);
    float clickPosition = 150.0f;
    menuLayoutAlgorithm->wrapperSize_.SetHeight(200.0f);
    menuLayoutAlgorithm->wrapperRect_.SetHeight(200.0f);

    /**
     * @tc.steps: step2. returns to the wrapper height minus the menu height.
     */
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Height() - size.Height());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg007
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg007, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 150);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, menuLayoutAlgorithm->wrapperSize_.Height() - size.Height());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg008
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg008, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 200);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg009
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg009, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode =
        MenuView::Create(std::move(optionParams), 1, "", MenuType::SELECT_OVERLAY_EXTENSION_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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

    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    layoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg010
 * @tc.desc: Verify Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg010, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    OffsetF offset(10, 10);
    menuLayoutAlgorithm->position_ = offset;
    const std::string tag = "tag";
    int32_t nodeId = 1;
    RefPtr<Pattern> pattern = AceType::MakeRefPtr<Pattern>();
    bool isRoot = false;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<FrameNode> frameNode = AceType::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(nodeId, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);
    wrapperBuilder->OnGetOrCreateWrapperByIndex(nodeId);
    auto children = wrapperBuilder->OnExpandChildLayoutWrapper();
    auto layoutWrapper_ = wrapperBuilder->GetOrCreateWrapperByIndex(nodeId);
    menuLayoutAlgorithm->Layout(layoutWrapper);
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), 10);
    delete layoutWrapper;
    layoutWrapper = nullptr;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg011
 * @tc.desc: Verify positionOffset of Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg011, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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

    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    layoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg012
 * @tc.desc: Verify positionOffset of Layout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg012, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam = { "", { POSITION_OFFSET, POSITION_OFFSET } };
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(POSITION_OFFSET, POSITION_OFFSET));

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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

    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF(POSITION_OFFSET, POSITION_OFFSET));
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
    layoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(geometryNode->GetMarginFrameOffset(), OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg013
 * @tc.desc: Verify ComputeMenuPositionByAlignType.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg013, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    selectParams.push_back({ "MenuItem2", "Icon2" });
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    SizeF targetSize(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    property->UpdateTargetSize(targetSize);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    /**
     * @tc.cases: case1. the menu align type is start.
     */
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType::START);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), 0);

    /**
     * @tc.cases: case2. the menu align type is center.
     */
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType::CENTER);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    float expectResult = -25.0f;
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), expectResult);

    /**
     * @tc.cases: case3. the menu align type is end.
     */
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType::END);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    expectResult = -50.0f;
    EXPECT_EQ(menuLayoutAlgorithm->position_.GetX(), expectResult);
    property->UpdateLayoutDirection(TextDirection::LTR);
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
    /**
     * @tc.cases: case4. the menu align type is others.
     */
    menuLayoutAlgorithm->position_ = OffsetF(0, 0);
    property->UpdateAlignType(MenuAlignType(3));
    menuLayoutAlgorithm->ComputeMenuPositionByAlignType(property, menuSize);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg014
 * @tc.desc: Verify ComputeMenuPositionByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg014, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    selectParams.push_back({ "MenuItem2", "Icon2" });
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    property->UpdateLayoutConstraint(parentLayoutConstraint);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));

    /**
     * @tc.cases: case1. parameter is valid, return the valid offset.
     */
    property->UpdateOffset(
        DimensionOffset(Dimension(MENU_OFFSET_X, DimensionUnit::VP), Dimension(MENU_OFFSET_Y, DimensionUnit::VP)));
    auto resultOffset = menuLayoutAlgorithm->ComputeMenuPositionByOffset(property, geometryNode);
    EXPECT_EQ(resultOffset, OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));

    /**
     * @tc.cases: case2. parameter property is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->ComputeMenuPositionByOffset(nullptr, geometryNode);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case3. parameter geometryNode is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->ComputeMenuPositionByOffset(property, nullptr);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg015
 * @tc.desc: Verify ComputeMenuPositionByOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg015, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    selectParams.push_back({ "MenuItem2", "Icon2" });
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    property->UpdateLayoutConstraint(parentLayoutConstraint);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->isSelectMenu_ = true;
    SizeF size(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);

    /**
     * @tc.cases: case1. parameter property is nullptr, return OffsetF(0.0, 0.0).
     */
    auto resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(nullptr, menuPattern, size);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case2. parameter menuPattern is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, nullptr, size);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case3. menu property has placement value and has targetSize.
     */
    property->UpdateMenuPlacement(Placement::RIGHT);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT;
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(POSITION_OFFSET, POSITION_OFFSET);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, menuPattern, size);
    float expectOffsetX = POSITION_OFFSET + TARGET_SIZE_WIDTH + TARGET_SECURITY.ConvertToPx();
    float expectOffsetY = MENU_SIZE_HEIGHT / 2;
    EXPECT_EQ(resultOffset, OffsetF(expectOffsetX, expectOffsetY));

    /**
     * @tc.cases: case4. target size is (0.0, 0.0)
     */
    menuLayoutAlgorithm->targetSize_ = SizeF(0.0f, 0.0f);
    resultOffset = menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(property, menuPattern, size);
    EXPECT_EQ(resultOffset, OffsetF(0, FULL_SCREEN_HEIGHT - MENU_SIZE_HEIGHT));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg016
 * @tc.desc: Test MultiMenu layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg016, TestSize.Level1)
{
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);

    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
    }

    algorithm->Layout(wrapper);
    // default padding from theme is zero, so the offset on the first child is zero.
    OffsetF offset;
    for (auto&& child : wrapper->GetAllChildrenWithBuild()) {
        EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), offset);
        offset.AddY(MENU_SIZE_HEIGHT / 3);
    }
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg017
 * @tc.desc: Verify GetPositionWithPlacement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    auto result = menuLayoutAlgorithm->GetPositionWithPlacement(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg018
 * @tc.desc: Verify GetPositionWithPlacement with targetNodeId, targetTag
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetNodeId, targetTag
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    const std::string tag = "tag";
    MenuLayoutAlgorithm menu(NODEID, tag);
    auto result = menu.GetPositionWithPlacement(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), 0);
    EXPECT_EQ(result.GetY(), 0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg019
 * @tc.desc: Verify AddTargetSpace with placement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, placement is BOTTOM_LEFT
     * @tc.expected: result y offset is add 8vp space
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    auto result = menuLayoutAlgorithm->AddTargetSpace(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST, OFFSET_FIRST + TARGET_SECURITY.ConvertToPx()));

    /**
     * @tc.steps: step2. create menuLayoutAlgorithm, placement is TOP_LEFT
     * @tc.expected: result y offset is reduce 8vp space
     */
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
    result = menuLayoutAlgorithm->AddTargetSpace(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST, OFFSET_FIRST - TARGET_SECURITY.ConvertToPx()));

    /**
     * @tc.steps: step3. create menuLayoutAlgorithm, placement is RIGHT_TOP
     * @tc.expected: result x offset is add 8vp space
     */
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
    result = menuLayoutAlgorithm->AddTargetSpace(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST + TARGET_SECURITY.ConvertToPx(), OFFSET_FIRST));

    /**
     * @tc.steps: step4. create menuLayoutAlgorithm, placement is LEFT_TOP
     * @tc.expected: result x offset is reduce 8vp space
     */
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
    result = menuLayoutAlgorithm->AddTargetSpace(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST - TARGET_SECURITY.ConvertToPx(), OFFSET_FIRST));

    /**
     * @tc.steps: step5. create menuLayoutAlgorithm, placement is NONE
     * @tc.expected: the offset of the result is consistent with when the placement is BOTTOM_LEFT
     */
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    result = menuLayoutAlgorithm->AddTargetSpace(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST, OFFSET_FIRST + TARGET_SECURITY.ConvertToPx()));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg020
 * @tc.desc: Verify AddOffset with placement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, placement is BOTTOM_LEFT
     * @tc.expected: result x and y offset is add position offset
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    menuLayoutAlgorithm->positionOffset_ = OffsetF(OFFSET_SECOND, OFFSET_SECOND);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    auto result = menuLayoutAlgorithm->AddOffset(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST + OFFSET_SECOND, OFFSET_FIRST + OFFSET_SECOND));

    /**
     * @tc.steps: step2. create menuLayoutAlgorithm, placement is TOP_LEFT
     * @tc.expected: result x offset add position offset and y offset is reduce position offset
     */
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
    result = menuLayoutAlgorithm->AddOffset(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST + OFFSET_SECOND, OFFSET_FIRST - OFFSET_SECOND));

    /**
     * @tc.steps: step3. create menuLayoutAlgorithm, placement is RIGHT_TOP
     * @tc.expected: result x offset add position offset and y offset is add position offset
     */
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
    result = menuLayoutAlgorithm->AddOffset(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST + OFFSET_SECOND, OFFSET_FIRST + OFFSET_SECOND));

    /**
     * @tc.steps: step4. create menuLayoutAlgorithm, placement is LEFT_TOP
     * @tc.expected: result x offset reduce position offset and y offset is add position offset
     */
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
    result = menuLayoutAlgorithm->AddOffset(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST - OFFSET_SECOND, OFFSET_FIRST + OFFSET_SECOND));

    /**
     * @tc.steps: step5. create menuLayoutAlgorithm, placement is NONE
     * @tc.expected: the offset of the result is consistent with when the placement is BOTTOM_LEFT
     */
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    result = menuLayoutAlgorithm->AddOffset(OffsetF(OFFSET_FIRST, OFFSET_FIRST));
    EXPECT_EQ(result, OffsetF(OFFSET_FIRST + OFFSET_SECOND, OFFSET_FIRST + OFFSET_SECOND));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg021
 * @tc.desc: Verify GetPositionWithPlacementTop.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition
     * @tc.expected: step1. position is topPosition
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementTop(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), TOP_POSITION_X);
    EXPECT_EQ(result.GetY(), TOP_POSITION_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg022
 * @tc.desc: Verify GetPositionWithPlacementTopLeft.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition and targetOffset
     * @tc.expected: step1. position is (targetOffset_.GetX(), targetOffset_.GetY() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementTopLeft(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), TOP_LEFT_X);
    EXPECT_EQ(result.GetY(), TOP_LEFT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg023
 * @tc.desc: Verify GetPositionWithPlacementTopRight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition and targetOffset
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width() - childSize.Width(),
     * targetOffset_.GetY() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementTopRight(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), TOP_RIGHT_X);
    EXPECT_EQ(result.GetY(), TOP_RIGHT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg024
 * @tc.desc: Verify GetPositionWithPlacementBottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition
     * @tc.expected: step1. position is bottomPosition
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementBottom(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), BOTTOM_POSITION_X);
    EXPECT_EQ(result.GetY(), BOTTOM_POSITION_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg025
 * @tc.desc: Verify GetPositionWithPlacementBottomLeft.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX(), targetOffset_.GetY() + targetSize_.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementBottomLeft(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), BOTTOM_LEFT_X);
    EXPECT_EQ(result.GetY(), BOTTOM_LEFT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg026
 * @tc.desc: Verify GetPositionWithPlacementBottomRight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width() - childSize.Width(),
     * targetOffset_.GetY() + targetSize_.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementBottomRight(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), BOTTOM_RIGHT_X);
    EXPECT_EQ(result.GetY(), BOTTOM_RIGHT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg027
 * @tc.desc: Verify GetPositionWithPlacementLeft.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() - childSize.Width(),
     * targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0)
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementLeft(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_LEFT_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_LEFT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg028
 * @tc.desc: Verify GetPositionWithPlacementLeftTop.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() - childSize.Width(),
     * targetOffset_.GetY())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementLeftTop(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_LEFT_TOP_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_LEFT_TOP_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg029
 * @tc.desc: Verify GetPositionWithPlacementLeftBottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() - childSize.Width(),
     * targetOffset_.GetY() + targetSize_.Height() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementLeftBottom(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_LEFT_BOTTOM_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_LEFT_BOTTOM_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg030
 * @tc.desc: Verify GetPositionWithPlacementRight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width(),
     * targetOffset_.GetY() + targetSize_.Height() / 2.0 - childSize.Height() / 2.0)
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementRight(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_RIGHT_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_RIGHT_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg031
 * @tc.desc: Verify GetPositionWithPlacementRightTop.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width(),
     * targetOffset_.GetY())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementRightTop(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_RIGHT_TOP_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_RIGHT_TOP_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg032
 * @tc.desc: Verify GetPositionWithPlacementRightBottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm, set childSize, topPosition, bottomPosition, targetOffset and
     * targetSize
     * @tc.expected: step1. position is (targetOffset_.GetX() + targetSize_.Width(),
     * targetOffset_.GetY() + targetSize_.Height() - childSize.Height())
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF childSize(CHILD_SIZE_X, CHILD_SIZE_Y);
    OffsetF topPosition(TOP_POSITION_X, TOP_POSITION_Y);
    OffsetF bottomPosition(BOTTOM_POSITION_X, BOTTOM_POSITION_Y);
    OffsetF offset(OFFSET_X_THIRD, OFFSET_Y_THIRD);
    menuLayoutAlgorithm->targetOffset_ = offset;
    SizeF size(SIZE_X_SECOND, SIZE_Y_SECOND);
    menuLayoutAlgorithm->targetSize_ = size;
    auto result = menuLayoutAlgorithm->GetPositionWithPlacementRightBottom(childSize, topPosition, bottomPosition);
    EXPECT_EQ(result.GetX(), PLACEMENT_RIGHT_BOTTOM_X);
    EXPECT_EQ(result.GetY(), PLACEMENT_RIGHT_BOTTOM_Y);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg033
 * @tc.desc: Test SubMenu layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg033, TestSize.Level1)
{
    // create parent menu item
    MockPipelineContextGetTheme();
    auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    auto item = AceType::MakeRefPtr<FrameNode>("MenuItem", -1, itemPattern);
    // set parent item size
    auto itemGeometryNode = item->GetGeometryNode();
    ASSERT_TRUE(itemGeometryNode);
    item->GetGeometryNode()->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));

    // create submenu
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::SUB_MENU);
    auto subMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::DynamicCast<SubMenuLayoutAlgorithm>(menuPattern->CreateLayoutAlgorithm());
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(subMenu, geometryNode, layoutProp);
    // link parent menu item and sub menu
    ASSERT_TRUE(menuPattern);
    menuPattern->SetParentMenuItem(item);
    item->GetGeometryNode()->SetFrameOffset(OffsetF(MENU_OFFSET_X, MENU_OFFSET_Y));
    algorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    algorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    // @tc.cases: case1. sub menu show on the right side of item
    algorithm->position_ = OffsetF(MENU_OFFSET_X + MENU_ITEM_SIZE_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);

    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(), TARGET_SIZE_WIDTH);

    // @tc.cases: case2. sub menu show on the left side of item
    algorithm->position_ = OffsetF(FULL_SCREEN_WIDTH, MENU_OFFSET_Y);
    algorithm->Layout(wrapper);

    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetX(), TARGET_SIZE_WIDTH);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetMarginFrameOffset().GetY(), 0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg034
 * @tc.desc: Test MultiMenuLayoutAlgorithm::Measure
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg034, TestSize.Level1)
{
    // set screen width for grid column
    ScreenSystemManager::GetInstance().SetWindowInfo(FULL_SCREEN_WIDTH, 1.0, 1.0);
    // create multi menu
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize = OptionalSizeF(1.0f, 1.0f);
    layoutProp->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProp->UpdateContentConstraint();
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    // create menu item
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
    }

    algorithm->Measure(wrapper);
    // @tc.expected: menu content width = item width, height = sum(item height)
    auto expectedSize = SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT * 3);
    EXPECT_EQ(wrapper->GetGeometryNode()->GetContentSize().Height(), expectedSize.Height());
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    menuPattern->isEmbedded_ = true;
    algorithm->Measure(wrapper);
    EXPECT_TRUE(LessNotEqual(parentLayoutConstraint.selfIdealSize.Width().value(), MIN_MENU_WIDTH.ConvertToPx()));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg035
 * @tc.desc: Test GetChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF size(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);

    /**
     * @tc.steps: step2. the placement of menuLayoutAlgorithm is Placement::NONE
     * @tc.expected: GetChildPosition get result offset is menu defaultPositon
     */
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(POSITION_OFFSET, POSITION_OFFSET);
    auto resultOffset = menuLayoutAlgorithm->GetChildPosition(size, false);
    float expectOffsetX = MENU_SIZE_WIDTH / 2;
    float expectOffsetY = MENU_SIZE_HEIGHT / 2;
    EXPECT_EQ(resultOffset, OffsetF(expectOffsetX, expectOffsetY));

    /**
     * @tc.steps: step3. the placement of menuLayoutAlgorithm is Placement::BOTTOM_LEFT
     * @tc.expected: GetChildPosition get result offset is adjust position
     */
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH / 2, TARGET_SIZE_HEIGHT);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(OFFSET_THIRD, OFFSET_FORTH);
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, OFFSET_THIRD, OFFSET_FORTH);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(OFFSET_SIXTH, 0.0f);

    resultOffset = menuLayoutAlgorithm->GetChildPosition(size);
    EXPECT_EQ(resultOffset, OffsetF(OFFSET_FIFTH, POSITION_OFFSET + TARGET_SECURITY.ConvertToPx()));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg036
 * @tc.desc: Test FitToScreen
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF size(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);

    /**
     * @tc.steps: step2. the placement of menuLayoutAlgorithm is Placement::NONE and need arrow
     * @tc.expected: FitToScreen get result offset is (0.0f, 0.0f)
     */
    OffsetF position = OffsetF(POSITION_OFFSET, POSITION_OFFSET);
    menuLayoutAlgorithm->positionOffset_ = OffsetF(OFFSET_FIRST, OFFSET_FIRST);
    menuLayoutAlgorithm->arrowPlacement_ = Placement::NONE;
    auto resultOffset = menuLayoutAlgorithm->FitToScreen(position, size, true);
    EXPECT_EQ(resultOffset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg037
 * @tc.desc: Test CheckPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);
    SizeF size(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);

    /**
     * @tc.steps: step2. the placement of menuLayoutAlgorithm is Placement::BOTTOM_LEFT and menu position is normal
     * @tc.expected: CheckPosition result is true
     */
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    OffsetF position = OffsetF(POSITION_OFFSET, OFFSET_FORTH);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(OFFSET_THIRD, OFFSET_THIRD);
    auto result = menuLayoutAlgorithm->CheckPosition(position, size);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. the placement of menuLayoutAlgorithm is Placement::TOP_LEFT and menu position is normal
     * @tc.expected: CheckPosition result is true
     */
    position = OffsetF(POSITION_OFFSET, OFFSET_FIFTH);
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
    result = menuLayoutAlgorithm->CheckPosition(position, size);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. the placement of menuLayoutAlgorithm is Placement::LEFT_TOP and menu position is normal
     * @tc.expected: CheckPosition result is true
     */
    position = OffsetF(OFFSET_FIFTH, OFFSET_THIRD);
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
    result = menuLayoutAlgorithm->CheckPosition(position, size);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step5. the placement of menuLayoutAlgorithm is Placement::NONE
     * @tc.expected: CheckPosition result is false
     */
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    result = menuLayoutAlgorithm->CheckPosition(position, size);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step6. the placement of menuLayoutAlgorithm is Placement::BOTTOM_LEFT and menu position is not normal
     * @tc.expected: CheckPosition result is false
     */
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    position = OffsetF(POSITION_OFFSET, FULL_SCREEN_HEIGHT);
    result = menuLayoutAlgorithm->CheckPosition(position, size);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg038
 * @tc.desc: Test InitTargetSizeAndPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm and target is null
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(nodeId, TEXT_TAG, MenuType::CONTEXT_MENU);
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(nodeId, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    menuLayoutAlgorithm->InitTargetSizeAndPosition(nullptr, true, menuPattern);
    menuLayoutAlgorithm->targetNodeId_ = nodeId;
    menuLayoutAlgorithm->targetTag_ = "text";
    auto target = FrameNode::GetOrCreateFrameNode("text", nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(target, nullptr);

    /**
     * @tc.steps: step2. target is null but the geometry node of target is null
     */
    menuLayoutAlgorithm->InitTargetSizeAndPosition(nullptr, true, menuPattern);

    /**
     * @tc.steps: step3. layoutWrapper, target node and the geometry node of target is not null, isContextMenu is false
     * @tc.expected: targetOffset_ is OffsetF(0.0f, 0.0f)
     */
    std::vector<SelectParam> params;
    params.push_back({ "MenuItem", "Icon" });
    auto frameNode = MenuView::Create(params, 1, EMPTY_TEXT);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    layoutProp->UpdateLayoutConstraint(parentLayoutConstraint);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode* layoutWrapper =
        new LayoutWrapperNode(frameNode, menuGeometryNode, layoutProp);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    GeometryProperty geometryProperty;
    geometryProperty.rect_ = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    geometryNode->frame_ = geometryProperty;
    target->geometryNode_ = geometryNode;
    menuLayoutAlgorithm->InitTargetSizeAndPosition(layoutWrapper, false, menuPattern);
    EXPECT_EQ(menuLayoutAlgorithm->targetOffset_, OffsetF(0.0f, 0.0f));

    /**
     * @tc.steps: step4. layoutWrapper, target and the geometry node of target is not null, isContextMenu and
     * isContainerModal is true
     * @tc.expected: targetOffset_ is as expected
     */
    MockPipelineContext::GetCurrent()->SetWindowModal(WindowModal::CONTAINER_MODAL);
    MockPipelineContext::GetCurrent()->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    MockPipelineContext::GetCurrent()->windowManager_->SetWindowGetModeCallBack(
        []() -> WindowMode { return WindowMode::WINDOW_MODE_FLOATING; });

    menuLayoutAlgorithm->InitTargetSizeAndPosition(layoutWrapper, true, menuPattern);
    EXPECT_EQ(menuLayoutAlgorithm->targetOffset_, OffsetF(-CONTENT_PADDING.ConvertToPx(), 0.0f));
    delete layoutWrapper;
    layoutWrapper = nullptr;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg039
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(NODEID, TEXT_TAG, MenuType::CONTEXT_MENU);
    auto contextMenu = AceType::MakeRefPtr<FrameNode>(MENU_TAG, -1, menuPattern);
    auto menuAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, TEXT_TAG);
    ASSERT_TRUE(menuAlgorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(contextMenu, geometryNode, layoutProp);
    const SizeF menuSize = SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    /**
     * @tc.steps: step2. execute GetIfNeedArrow
     * @tc.expected: ifNeedArrow is as expected.
     */
    menuAlgorithm->GetPaintProperty(layoutWrapper)->UpdateEnableArrow(true);
    auto result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_FALSE(result);
    menuAlgorithm->placement_ = Placement::LEFT;
    result = menuAlgorithm->GetIfNeedArrow(layoutWrapper, menuSize);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg040
 * @tc.desc: Test UpdatePropArrowOffset
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto menuAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, TEXT_TAG);
    ASSERT_TRUE(menuAlgorithm);
    std::unordered_set<Placement> placements = { Placement::TOP, Placement::TOP_LEFT, Placement::TOP_RIGHT,
        Placement::BOTTOM, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT, Placement::LEFT, Placement::LEFT_TOP,
        Placement::LEFT_BOTTOM, Placement::RIGHT, Placement::RIGHT_TOP, Placement::RIGHT_BOTTOM };
    std::unordered_set<Placement> offsetCondition1 = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM };
    std::unordered_set<Placement> offsetCondition2 = { Placement::TOP_LEFT, Placement::BOTTOM_LEFT, Placement::LEFT_TOP,
        Placement::RIGHT_TOP };
    std::unordered_set<Placement> offsetCondition3 = { Placement::TOP_RIGHT, Placement::BOTTOM_RIGHT,
        Placement::LEFT_BOTTOM, Placement::RIGHT_BOTTOM };
    /**
     * @tc.steps: step2. input unit is px, execute UpdatePropArrowOffset
     * @tc.expected: propArrowOffset_ is as expected.
     */
    menuAlgorithm->propArrowOffset_ = Dimension(10, DimensionUnit::PX);
    menuAlgorithm->UpdatePropArrowOffset();
    EXPECT_EQ(menuAlgorithm->propArrowOffset_, Dimension(10, DimensionUnit::PX));
    /**
     * @tc.steps: step3. input unit is percent, execute UpdatePropArrowOffset
     * @tc.expected: propArrowOffset_ is as expected.
     */
    menuAlgorithm->propArrowOffset_ = Dimension(0.5, DimensionUnit::PERCENT);
    menuAlgorithm->UpdatePropArrowOffset();
    EXPECT_EQ(menuAlgorithm->propArrowOffset_, Dimension(0.5, DimensionUnit::PERCENT));
    /**
     * @tc.steps: step4. input is invalid, execute UpdatePropArrowOffset
     * @tc.expected: propArrowOffset_ is as expected.
     */
    for (Placement placementValue : placements) {
        menuAlgorithm->propArrowOffset_ = Dimension(-1, DimensionUnit::PX);
        menuAlgorithm->arrowPlacement_ = placementValue;
        menuAlgorithm->UpdatePropArrowOffset();
        if (offsetCondition1.find(placementValue) != offsetCondition1.end()) {
            EXPECT_EQ(menuAlgorithm->propArrowOffset_, ARROW_HALF_PERCENT_VALUE);
        }
        if (offsetCondition2.find(placementValue) != offsetCondition2.end()) {
            EXPECT_EQ(menuAlgorithm->propArrowOffset_, ARROW_ZERO_PERCENT_VALUE);
        }
        if (offsetCondition3.find(placementValue) != offsetCondition3.end()) {
            EXPECT_EQ(menuAlgorithm->propArrowOffset_, ARROW_ONE_HUNDRED_PERCENT_VALUE);
        }
    }
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg041
 * @tc.desc: Test GetArrowPositionWithPlacement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menuLayoutAlgorithm
     * @tc.expected: menuLayoutAlgorithm is not null
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MENU);
    auto menu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* layoutWrapper = new LayoutWrapperNode(menu, geometryNode, layoutProp);

    auto menuAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, TEXT_TAG);
    ASSERT_TRUE(menuAlgorithm);
    const SizeF menuSize = SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    std::unordered_set<Placement> placements = { Placement::TOP, Placement::TOP_LEFT, Placement::TOP_RIGHT,
        Placement::BOTTOM, Placement::BOTTOM_LEFT, Placement::BOTTOM_RIGHT, Placement::LEFT, Placement::LEFT_TOP,
        Placement::LEFT_BOTTOM, Placement::RIGHT, Placement::RIGHT_TOP, Placement::RIGHT_BOTTOM };
    std::unordered_set<Placement> positionCondition1 = { Placement::TOP, Placement::TOP_LEFT, Placement::TOP_RIGHT };
    std::unordered_set<Placement> positionCondition2 = { Placement::BOTTOM, Placement::BOTTOM_LEFT,
        Placement::BOTTOM_RIGHT };
    std::unordered_set<Placement> positionCondition3 = { Placement::LEFT, Placement::LEFT_TOP, Placement::LEFT_BOTTOM };
    std::unordered_set<Placement> positionCondition4 = { Placement::RIGHT, Placement::RIGHT_TOP,
        Placement::RIGHT_BOTTOM };
    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    auto radius = selectTheme->GetMenuBorderRadius().ConvertToPx();
    auto arrowMinLimit = radius + ARROW_WIDTH.ConvertToPx() / 2.0;
    /**
     * @tc.steps: step2. execute GetArrowPositionWithPlacement
     * @tc.expected: arrowPosition is as expected.
     */
    for (Placement placementValue : placements) {
        menuAlgorithm->propArrowOffset_ = Dimension(0.5, DimensionUnit::PX);
        menuAlgorithm->arrowPlacement_ = placementValue;
        auto result = menuAlgorithm->GetArrowPositionWithPlacement(menuSize, layoutWrapper);
        EXPECT_EQ(menuAlgorithm->propArrowOffset_, Dimension(0.5, DimensionUnit::PX));
        auto arrowOffsetValue = (menuAlgorithm->propArrowOffset_).ConvertToPx();
        EXPECT_EQ(menuAlgorithm->arrowOffset_, arrowOffsetValue);
        arrowOffsetValue  = arrowMinLimit + arrowOffsetValue;
        if (positionCondition1.find(placementValue) != positionCondition1.end()) {
            EXPECT_EQ(result, OffsetF(arrowOffsetValue, menuSize.Height() + ARROW_HIGHT.ConvertToPx()));
        }
        if (positionCondition2.find(placementValue) != positionCondition2.end()) {
            EXPECT_EQ(result, OffsetF(arrowOffsetValue, 0));
        }
        if (positionCondition3.find(placementValue) != positionCondition3.end()) {
            EXPECT_EQ(result, OffsetF(menuSize.Width() + ARROW_HIGHT.ConvertToPx(), arrowOffsetValue));
        }
        if (positionCondition4.find(placementValue) != positionCondition4.end()) {
            EXPECT_EQ(result, OffsetF(0, arrowOffsetValue));
        }
    }
}
/**
 * @tc.name: MenuLayoutAlgorithmTestNg044
 * @tc.desc: Verify InitCanExpandCurrentWindow.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg044, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();

    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam = { "", { POSITION_OFFSET, POSITION_OFFSET } };
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(POSITION_OFFSET, POSITION_OFFSET));

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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
    layoutAlgorithm->Measure(&layoutWrapper);
    layoutAlgorithm->Layout(&layoutWrapper);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);

    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    layoutAlgorithm->InitCanExpandCurrentWindow(false);

    menuPattern->isSelectMenu_ = true;
    layoutAlgorithm->InitCanExpandCurrentWindow(false);
}
/**
 * @tc.name: MenuLayoutAlgorithmTestNg045
 * @tc.desc: Verify InitCanExpandCurrentWindow.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg045, TestSize.Level1)
{
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam = { "", { POSITION_OFFSET, POSITION_OFFSET } };
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF(POSITION_OFFSET, POSITION_OFFSET));

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
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
    layoutAlgorithm->Measure(&layoutWrapper);
    layoutAlgorithm->Layout(&layoutWrapper);
    layoutAlgorithm->InitCanExpandCurrentWindow(false);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg046
 * @tc.desc: Verify Initialize and Measure when PlatformVersionis is VERSION_TWELVE.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg046, TestSize.Level1)
{
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

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg047
 * @tc.desc: Verify Initialize and Measure when PlatformVersionis is VERSION_ELEVEN.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg047, TestSize.Level1)
{
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

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg048
 * @tc.desc: Verify Initialize and Measure when DeviceOrientation is not PORTRAIT.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg048, TestSize.Level1)
{
    SystemProperties::orientation_ = DeviceOrientation::ORIENTATION_UNDEFINED;
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

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN);
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper.GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg049
 * @tc.desc: Verify SelectLayoutAvoidAlgorithm.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout1TestNg, MenuLayoutAlgorithmTestNg049, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    selectParams.push_back({ "MenuItem2", "Icon2" });
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    auto menuWeakNode = WeakPtr<FrameNode>(menuNode);
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProperty = AceType::MakeRefPtr<MenuLayoutProperty>();
    LayoutWrapperNode layoutWrapper(menuWeakNode, geometryNode, layoutProperty);

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    property->UpdateLayoutConstraint(parentLayoutConstraint);

    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODEID, "menu");
    ASSERT_NE(menuLayoutAlgorithm, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->isSelectMenu_ = true;
    SizeF size(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);

    /**
     * @tc.cases: case1. parameter property is nullptr, return OffsetF(0.0, 0.0).
     */
    auto resultOffset = menuLayoutAlgorithm->SelectLayoutAvoidAlgorithm(nullptr, menuPattern,
        size, false, &layoutWrapper);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case2. parameter menuPattern is nullptr, return OffsetF(0.0, 0.0).
     */
    resultOffset = menuLayoutAlgorithm->SelectLayoutAvoidAlgorithm(property, nullptr,
        size, false, &layoutWrapper);
    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));

    /**
     * @tc.cases: case3. targetSize_ has width or height greater than 0.
     */
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(POSITION_OFFSET, POSITION_OFFSET);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    resultOffset = menuLayoutAlgorithm->SelectLayoutAvoidAlgorithm(property, menuPattern,
        size, false, &layoutWrapper);
    float expectOffsetX = POSITION_OFFSET;
    float expectOffsetY = POSITION_OFFSET + TARGET_SIZE_HEIGHT + TARGET_SECURITY.ConvertToPx();
    EXPECT_EQ(resultOffset, OffsetF(expectOffsetX, expectOffsetY));

    /**
     * @tc.cases: case4. targetSize_ is (0.0, 0.0).
     */
    menuLayoutAlgorithm->targetSize_ = SizeF(0.0f, 0.0f);
    resultOffset = menuLayoutAlgorithm->SelectLayoutAvoidAlgorithm(property, menuPattern,
        size, false, &layoutWrapper);

    EXPECT_EQ(resultOffset, OffsetF(0.0, 0.0));
}
} // namespace OHOS::Ace::NG
