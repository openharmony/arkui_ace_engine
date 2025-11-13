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

#include "core/common/ace_engine.h"
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
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";

constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float POSITION_OFFSET = 100.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;

constexpr float OFFSET_THIRD = 200.0f;
constexpr float OFFSET_FORTH = 300.0f;
constexpr float OFFSET_FIFTH = 50.0f;
constexpr int NODEID = 1;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = {"cursive"};
const std::vector<SelectParam> CREATE_VALUE = { { "content1", "icon1" }, { "content2", "" },
    { "", "icon3" }, { "", "" } };
const std::vector<SelectParam> CREATE_VALUE_NEW = { { "content1_new", "" }, { "", "icon4_new" },
    { "", "" }, { "", "icon4_new" } };
} // namespace
class MenuLayout1TwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    void InitMenuLayout1TwoTestNg();
    PaintWrapper* GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    RefPtr<MenuItemAccessibilityProperty> menuItemAccessibilityProperty_;
};

void MenuLayout1TwoTestNg::SetUpTestCase() {}

void MenuLayout1TwoTestNg::TearDownTestCase() {}

void MenuLayout1TwoTestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayout1TwoTestNg::TearDown()
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

void MenuLayout1TwoTestNg::MockPipelineContextGetTheme()
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

void MenuLayout1TwoTestNg::InitMenuLayout1TwoTestNg()
{
    menuFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", TYPE); });
    ASSERT_NE(menuFrameNode_, nullptr);

    menuAccessibilityProperty_ = menuFrameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

PaintWrapper* MenuLayout1TwoTestNg::GetPaintWrapper(RefPtr<MenuPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

RefPtr<FrameNode> MenuLayout1TwoTestNg::GetPreviewMenuWrapper(
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
 * @tc.name: MenuLayoutAlgorithmTestNg037
 * @tc.desc: Test CheckPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg037, TestSize.Level1)
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
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg038, TestSize.Level1)
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
    EXPECT_EQ(menuLayoutAlgorithm->targetOffset_, OffsetF(0.0f, 0.0f));
    delete layoutWrapper;
    layoutWrapper = nullptr;
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg039
 * @tc.desc: Test GetIfNeedArrow
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg039, TestSize.Level1)
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
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg040, TestSize.Level1)
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
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg041, TestSize.Level1)
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
 * @tc.name: MenuLayoutAlgorithmTestNg042
 * @tc.desc: Verify VerticalLayout.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg042, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    SizeF size(100, 100);
    SizeF size_f(100, 200);
    float clickPosition = 100.0f;
    menuLayoutAlgorithm->bottomSpace_ = 50.0f;
    menuLayoutAlgorithm->anchorPosition_ = {10.0f, 10.0f};
    menuLayoutAlgorithm->wrapperSize_ = size_f;
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, size_f.Width(), size_f.Height());
    auto result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition, false);
    EXPECT_FLOAT_EQ(result, clickPosition);

    result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition, true);
    EXPECT_FLOAT_EQ(result, clickPosition);

    clickPosition = 80.0f;
    result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition, false);
    EXPECT_FLOAT_EQ(result, 100.0f);

    menuLayoutAlgorithm->topSpace_ = 200.0f;
    result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition, false);
    EXPECT_EQ(menuLayoutAlgorithm->placement_, Placement::TOP);
    EXPECT_FLOAT_EQ(result, 100.0f);

    menuLayoutAlgorithm->wrapperRect_ =  Rect(0, 0, 0, 0);
    result = menuLayoutAlgorithm->VerticalLayout(size, clickPosition, false);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg044
 * @tc.desc: Verify InitCanExpandCurrentWindow.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg044, TestSize.Level1)
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
    layoutAlgorithm->InitCanExpandCurrentWindow(false, &layoutWrapper);

    menuPattern->isSelectMenu_ = true;
    layoutAlgorithm->InitCanExpandCurrentWindow(false, &layoutWrapper);
}
/**
 * @tc.name: MenuLayoutAlgorithmTestNg045
 * @tc.desc: Verify InitCanExpandCurrentWindow.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg045, TestSize.Level1)
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
    layoutAlgorithm->InitCanExpandCurrentWindow(false, &layoutWrapper);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg046
 * @tc.desc: Verify Initialize and Measure when PlatformVersionis is VERSION_TWELVE.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg046, TestSize.Level1)
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

HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg047, TestSize.Level1)
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

HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg048, TestSize.Level1)
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

HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg049, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    selectParams.push_back({ "MenuItem2", "Icon2" });
    // create select menu
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, EMPTY_TEXT);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    auto container = Container::Current();
    menuNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
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

/**
 * @tc.name: MenuLayoutAlgorithmTestNg050
 * @tc.desc: Test MultiMenu layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MenuLayoutAlgorithmTestNg050, TestSize.Level1)
{
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    PaddingProperty padding;
    padding.left = CalcLength(10.0f);
    padding.right = CalcLength(10.0f);
    padding.top = CalcLength(10.0f);
    padding.bottom = CalcLength(10.0f);
    layoutProp->UpdateSafeAreaPadding(padding);
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }

    algorithm->Layout(wrapper);

    OffsetF offset { 10.0, 10.0 };
    for (auto&& child : wrapper->GetAllChildrenWithBuild()) {
        EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), offset);
        offset.AddY(MENU_SIZE_HEIGHT / 3);
    }
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg051
 * @tc.desc: Test MultiMenu MarkChildForDelayedMeasurement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MarkChildForDelayedMeasurement01, TestSize.Level1)
{
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    PaddingProperty padding;
    padding.left = CalcLength(10.0f);
    padding.right = CalcLength(10.0f);
    padding.top = CalcLength(10.0f);
    padding.bottom = CalcLength(10.0f);
    layoutProp->UpdateSafeAreaPadding(padding);
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }

    algorithm->MarkChildForDelayedMeasurement(wrapper);
    EXPECT_EQ(algorithm->layoutPolicyChildren_.size(), 0);
    delete(wrapper);
}

/**
 * @tc.name: MarkChildForDelayedMeasurement02
 * @tc.desc: Test MultiMenu MarkChildForDelayedMeasurement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MarkChildForDelayedMeasurement02, TestSize.Level1)
{
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    PaddingProperty padding;
    padding.left = CalcLength(10.0f);
    padding.right = CalcLength(10.0f);
    padding.top = CalcLength(10.0f);
    padding.bottom = CalcLength(10.0f);
    layoutProp->UpdateSafeAreaPadding(padding);
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
        layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        layoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
        menuItem->SetLayoutProperty(layoutProperty);
        itemGeoNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProperty);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }
    LayoutConstraintF childLayoutConstraint;
    childLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    childLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    algorithm->MeasureAdaptiveLayoutChildren(wrapper, childLayoutConstraint);
    EXPECT_EQ(algorithm->layoutPolicyChildren_.size(), 3);
    delete(wrapper);
}

/**
 * @tc.name: MarkChildForDelayedMeasurement03
 * @tc.desc: Test MultiMenu MarkChildForDelayedMeasurement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MarkChildForDelayedMeasurement03, TestSize.Level1)
{
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    menuPattern->SetIsEmbedded();
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    PaddingProperty padding;
    padding.left = CalcLength(10.0f);
    padding.right = CalcLength(10.0f);
    padding.top = CalcLength(10.0f);
    padding.bottom = CalcLength(10.0f);
    layoutProp->UpdateSafeAreaPadding(padding);
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
        layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        layoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
        menuItem->SetLayoutProperty(layoutProperty);
        itemGeoNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProperty);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }
    LayoutConstraintF childLayoutConstraint;
    childLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    childLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    algorithm->MeasureAdaptiveLayoutChildren(wrapper, childLayoutConstraint);
    EXPECT_EQ(algorithm->layoutPolicyChildren_.size(), 3);
    delete(wrapper);
}

/**
 * @tc.name: MarkChildForDelayedMeasurement04
 * @tc.desc: Test MultiMenu  MarkChildForDelayedMeasurement.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, MarkChildForDelayedMeasurement04, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu.
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    /**
     * @tc.steps: step2. Create menuitem and do not set width LayoutPolicy to Match.
     */
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
        layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
        layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        layoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
        menuItem->SetLayoutProperty(layoutProperty);
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProperty);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }
    /**
     * @tc.steps: step3. expect layoutPolicyChildren_ equals number of menuitem.
     */
    LayoutConstraintF childLayoutConstraint;
    childLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    childLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    algorithm->MeasureAdaptiveLayoutChildren(wrapper, childLayoutConstraint);
    EXPECT_EQ(algorithm->layoutPolicyChildren_.size(), 3);
    delete (wrapper);
}

/**
 * @tc.name: GetMaxWidthTest01
 * @tc.desc: Test MultiMenu  GetMaxWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, GetMaxWidthTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu.
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    /**
     * @tc.steps: step2. Create menuitem and do not set width LayoutPolicy.
     */
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(50.0f * (i + 1), MENU_SIZE_HEIGHT / 3));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }
    LayoutConstraintF childLayoutConstraint;
    childLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    childLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    /**
     * @tc.steps: step3. expect maxWidth equals to max width of menuitem.
     */
    auto maxWidth = algorithm->GetChildrenMaxWidth(wrapper, childLayoutConstraint);
    EXPECT_FLOAT_EQ(maxWidth, 150.0f);
    delete (wrapper);
}

/**
 * @tc.name: GetMaxWidthTest02
 * @tc.desc: Test MultiMenu  GetMaxWidth.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout1TwoTestNg, GetMaxWidthTest02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menu.
     */
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto multiMenu = AceType::MakeRefPtr<FrameNode>("", -1, menuPattern);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto* wrapper = new LayoutWrapperNode(multiMenu, geometryNode, layoutProp);
    /**
     * @tc.steps: step2. Create menuitem and set width LayoutPolicy to MATCH_PARENT.
     */
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
        layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        menuItem->SetLayoutProperty(layoutProperty);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
        multiMenu->AddChild(menuItem);
    }
    /**
     * @tc.steps: step3. expect maxWidth equals to 0.0f if width LayoutPolicy to MATCH_PARENT.
     */
    LayoutConstraintF childLayoutConstraint;
    childLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    childLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    childLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    auto maxWidth = algorithm->GetChildrenMaxWidth(wrapper, childLayoutConstraint);
    EXPECT_FLOAT_EQ(maxWidth, 0.0f);
    delete (wrapper);
}
} // namespace OHOS::Ace::NG