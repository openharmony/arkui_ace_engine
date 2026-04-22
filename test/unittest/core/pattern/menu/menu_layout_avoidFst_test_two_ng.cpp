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
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_canvas.h"

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
constexpr int32_t NODE_ID = 1;
constexpr float FULL_PHONE_WIDTH = 1260.0f;
constexpr float FULL_PHONE_HEIGHT = 2596.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float PADDING_START = 52.0f;
constexpr float PADDING_END = 52.0f;
constexpr float PADDING_TOP = 0.0f;
constexpr float PADDING_BOTTOM = 0.0f;
constexpr float TOP_SECURITY = 52.0f;
constexpr float BOTTOM_SECURITY = 13.0f;
constexpr float LEFT_SECURITY = 52.0f;
constexpr float RIGHT_SECURITY = 52.0f;
constexpr float MARGIN = 13.0f;
} // namespace

class MenuLayoutAvoid1TwoTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<MenuLayoutAlgorithm> GetMenuLayoutAlgorithm();
};

void MenuLayoutAvoid1TwoTestNg::SetUpTestCase() {}

void MenuLayoutAvoid1TwoTestNg::TearDownTestCase() {}

void MenuLayoutAvoid1TwoTestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayoutAvoid1TwoTestNg::TearDown()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

RefPtr<MenuLayoutAlgorithm> MenuLayoutAvoid1TwoTestNg::GetMenuLayoutAlgorithm()
{
    auto menuLayoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>(NODE_ID, "menu");
    menuLayoutAlgorithm->wrapperSize_ = SizeF(FULL_PHONE_WIDTH, FULL_PHONE_HEIGHT);
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, FULL_PHONE_WIDTH, FULL_PHONE_HEIGHT);
    menuLayoutAlgorithm->paddingStart_ = PADDING_START;
    menuLayoutAlgorithm->paddingEnd_ = PADDING_END;
    menuLayoutAlgorithm->paddingTop_ = PADDING_TOP;
    menuLayoutAlgorithm->paddingBottom_ = PADDING_BOTTOM;
    menuLayoutAlgorithm->param_.topSecurity = TOP_SECURITY;
    menuLayoutAlgorithm->param_.bottomSecurity = BOTTOM_SECURITY;
    menuLayoutAlgorithm->param_.leftSecurity = LEFT_SECURITY;
    menuLayoutAlgorithm->param_.rightSecurity = RIGHT_SECURITY;
    menuLayoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuLayoutAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuLayoutAlgorithm->margin_ = MARGIN;
    return menuLayoutAlgorithm;
}

/**
 * @tc.name: MenuLayoutOverHeightTestNg005
 * @tc.desc: Test Menu in Center with Top Placement Over Height.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, MenuLayoutOverHeightTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization layoutAlgorithm parameters.
     * @tc.expected: layoutAlgorithm is not null.
     */
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(
        (FULL_PHONE_WIDTH - menuLayoutAlgorithm->targetSize_.Width()) / 2,
        (FULL_PHONE_HEIGHT - menuLayoutAlgorithm->targetSize_.Height()) / 2);
    menuLayoutAlgorithm->placement_ = Placement::TOP;
    menuLayoutAlgorithm->position_ = menuLayoutAlgorithm->targetOffset_;

    /**
     * @tc.steps: step2. Initialize menuNode parameters.
     * @tc.expected: menuNode parameters is as expected.
     */
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, FULL_PHONE_HEIGHT / 2);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);
}

/**
 * @tc.name: UpdateTargetValue001
 * @tc.desc: Verify UpdateTargetValue.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, UpdateTargetValue001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 350, 350 };
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->UpdateTargetValue(layoutWrapper);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(props, nullptr);
    EXPECT_EQ(props->GetTargetOffset().value().GetX(), 0);
    delete layoutWrapper;
}

/**
 * @tc.name: UpdateExpandSize001
 * @tc.desc: Verify UpdateExpandSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, UpdateExpandSize001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 350, 350 };
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuLayoutAlgorithm->UpdateExpandSize(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuLayoutAlgorithm->UpdateExpandSize(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->UpdateExpandSize(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::SIDE;
    menuLayoutAlgorithm->UpdateExpandSize(layoutWrapper, parentLayoutConstraint, menuItemNode);
    EXPECT_EQ(menuItemPattern->expandingMode_, SubMenuExpandingMode::SIDE);
    delete layoutWrapper;
}

/**
 * @tc.name: UpdatePropTargetSpace001
 * @tc.desc: Verify UpdatePropTargetSpace.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, UpdatePropTargetSpace001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(targetNode->GetId(), targetNode->GetTag(), MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuProp->UpdateMenuTargetSpace(Dimension(10));
    menuPattern->SetPreviewMode(MenuPreviewMode::NONE);
    menuLayoutAlgorithm->UpdatePropTargetSpace(menuProp, menuPattern);
    EXPECT_TRUE(menuLayoutAlgorithm->propTargetSpace_.has_value());
    menuPattern->SetPreviewMode(MenuPreviewMode::IMAGE);
    menuLayoutAlgorithm->UpdatePropTargetSpace(menuProp, menuPattern);
    EXPECT_FALSE(menuLayoutAlgorithm->propTargetSpace_.has_value());
}

/**
 * @tc.name: MenuLayoutAvoidAlgorithm001
 * @tc.desc: Verify MenuLayoutAvoidAlgorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, MenuLayoutAvoidAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialization layoutAlgorithm parameters.
     * @tc.expected: layoutAlgorithm is not null.
     */
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->targetOffset_ = OffsetF(
        (FULL_PHONE_WIDTH - menuLayoutAlgorithm->targetSize_.Width()) / 2,
        (FULL_PHONE_HEIGHT - menuLayoutAlgorithm->targetSize_.Height()) / 2);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_BOTTOM;
    menuLayoutAlgorithm->position_ = menuLayoutAlgorithm->targetOffset_;
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::RIGHT_BOTTOM;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(150.0f, 150.0f);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    EXPECT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT_BOTTOM);
    delete layoutWrapper;
}

/**
 * @tc.name: UpdateEmbeddedPosition001
 * @tc.desc: Verify UpdateEmbeddedPosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, UpdateEmbeddedPosition001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 350, 350 };
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto innerNode = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU));
    ASSERT_NE(innerNode, nullptr);
    auto menuPattern = innerNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto layoutProps = menuPattern->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->propExpandingMode_ = SubMenuExpandingMode::STACK;
    auto child = menuNode->GetChildAtIndex(0);
    menuNode->RemoveChild(child);
    innerNode->MountToParent(menuNode);
    OffsetF position = { 400, 600 };
    SizeF size(50, 50);
    menuLayoutAlgorithm->UpdateEmbeddedPosition(position, menuPattern, size, menuNode);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->UpdateEmbeddedPosition(position, menuPattern, size, menuNode);
    layoutProps->propExpandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuLayoutAlgorithm->UpdateEmbeddedPosition(position, menuPattern, size, menuNode);
    menuPattern->UpdateLastPlacement(Placement::TOP);
    menuLayoutAlgorithm->UpdateEmbeddedPosition(position, menuPattern, size, menuNode);
    EXPECT_EQ(menuPattern->GetLastPlacement().value_or(Placement::NONE), Placement::TOP);
}

/**
 * @tc.name: UpdateStackHeight001
 * @tc.desc: Verify UpdateStackHeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, UpdateStackHeight001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 350, 350 };
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuItemNode->MountToParent(menuNode);
    menuLayoutAlgorithm->UpdateStackHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->UpdateStackHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuPattern->UpdateLastPlacement(Placement::TOP);
    menuLayoutAlgorithm->UpdateStackHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    EXPECT_EQ(menuPattern->GetLastPlacement().value_or(Placement::NONE), Placement::TOP);
    delete layoutWrapper;
}

/**
 * @tc.name: GetCurrentPosition001
 * @tc.desc: Verify GetCurrentPosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetCurrentPosition001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    OffsetF position = { 300, 300 };
    auto offset1 = menuLayoutAlgorithm->GetCurrentPosition(position, size, false, false);
    EXPECT_EQ(offset1, 1000.0f);

    OffsetF positionOne = { 150, 150 };
    menuLayoutAlgorithm->proptargetSize_ = { 100.0, 200.0 };
    auto offset2 = menuLayoutAlgorithm->GetCurrentPosition(positionOne, size, false, false);
    EXPECT_EQ(offset2, 118);

    OffsetF positionTwo = { 150, 150 };
    auto offset3 = menuLayoutAlgorithm->GetCurrentPosition(positionTwo, size, 400, true);
    EXPECT_EQ(offset3, 1000.0f);

    SizeF sizeThree(20.0f, 20.0f);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 350, 350 };
    menuLayoutAlgorithm->wrapperRect_ = { -4.0, -10.0, 200.0, 300.0 };
    auto offset4 = menuLayoutAlgorithm->GetCurrentPosition(position, sizeThree, 400, true);
    EXPECT_EQ(offset4, 289.0f);

    SizeF sizeFour(200.0f, 200.0f);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->wrapperRect_ = { -4.0, -10.0, 200.0, 300.0 };
    auto offset5 = menuLayoutAlgorithm->GetCurrentPosition(position, sizeFour, 400, true);
    EXPECT_EQ(offset5, 339.0f);

    SizeF sizeFive(200.0f, 200.0f);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->wrapperRect_ = { -4.0, -10.0, 200.0, 300.0 };
    auto offset6 = menuLayoutAlgorithm->GetCurrentPosition(position, sizeFive, true, true);
    EXPECT_EQ(offset6, 289.0f);
}

/**
 * @tc.name: NeedUpdateMaxHeight001
 * @tc.desc: Verify NeedUpdateMaxHeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, NeedUpdateMaxHeight001, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", NODE_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(40);
    menuLayoutAlgorithm->proptargetSize_ = { 100.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 100, 200 };
    SizeF size(150.0f, 150.0f);
    menuLayoutAlgorithm->wrapperSize_ = { 250.0, 400.0 };
    OffsetF position = { 200, 400 };
    OffsetF positionX = { 400, 400 };
    SizeF menuItemSize = { 50.0f, 40.0f };
    auto offset1 = menuLayoutAlgorithm->NeedUpdateMaxHeight(size, positionX, menuItemSize, nullptr);
    EXPECT_EQ(offset1, 2156.0f);
    auto offset2 = menuLayoutAlgorithm->NeedUpdateMaxHeight(size, position, menuItemSize, layoutWrapper);
    EXPECT_EQ(offset2, 2156.0f);
    auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(menuLayoutProperty, nullptr);
    menuLayoutProperty->layoutDirection_ = TextDirection::RTL;
    auto offset3 = menuLayoutAlgorithm->NeedUpdateMaxHeight(size, position, menuItemSize, layoutWrapper);
    EXPECT_EQ(offset3, 2156.0f);
    SizeF sizeTwo(2000.0f, 200.0f);
    auto offset4 = menuLayoutAlgorithm->NeedUpdateMaxHeight(sizeTwo, position, menuItemSize, nullptr);
    EXPECT_EQ(offset4, 2595.0f);
}

/**
 * @tc.name: GetOthersPosition001
 * @tc.desc: Verify GetOthersPosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetOthersPosition001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(40);
    menuLayoutAlgorithm->proptargetSize_ = { 100.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 100, 200 };
    menuLayoutAlgorithm->wrapperSize_ = { 1250.0, 400.0 };
    OffsetF position = { 300, 300 };
    SizeF size(150.0f, 150.0f);
    auto offset1 = menuLayoutAlgorithm->GetOthersPosition(position, size);
    EXPECT_EQ(offset1, 2595.0f);
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 70, 100);
    auto offset2 = menuLayoutAlgorithm->GetOthersPosition(position, size);
    EXPECT_EQ(offset2, 100.0f);
}

/**
 * @tc.name: MenuVerticalPanHeight001
 * @tc.desc: Verify MenuVerticalPanHeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, MenuVerticalPanHeight001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 200.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    OffsetF position = { 300, 300 };
    auto offset1 = menuLayoutAlgorithm->MenuVerticalPanHeight(position, size);
    EXPECT_EQ(offset1, 662.0f);

    OffsetF positionTwo = { 200, 120 };
    auto offset2 = menuLayoutAlgorithm->MenuVerticalPanHeight(positionTwo, size);
    EXPECT_EQ(offset2, 118);

    menuLayoutAlgorithm->propTargetOffset_ = { 400, 400 };
    auto offset3 = menuLayoutAlgorithm->MenuVerticalPanHeight(positionTwo, size);
    EXPECT_EQ(offset3, 1000);

    menuLayoutAlgorithm->propTargetOffset_ = { 400, 300 };
    OffsetF positionThree = { 400, 600 };
    auto offset4 = menuLayoutAlgorithm->MenuVerticalPanHeight(positionThree, size);
    EXPECT_EQ(offset4, 562);
}

/**
 * @tc.name: CheckHeightReason001
 * @tc.desc: Verify CheckHeightReason.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, CheckHeightReason001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 200.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    OffsetF position = { 300, 150 };
    auto offset1 = menuLayoutAlgorithm->CheckHeightReason(position, size);
    EXPECT_EQ(offset1, TargetSpaceReason::TOP);

    OffsetF positionTwo = { 200, 620 };
    auto offset2 = menuLayoutAlgorithm->CheckHeightReason(positionTwo, size);
    EXPECT_EQ(offset2, TargetSpaceReason::BOTTOM);

    OffsetF positionThr = { 200, 300 };
    auto offset3 = menuLayoutAlgorithm->CheckHeightReason(positionThr, size);
    EXPECT_EQ(offset3, TargetSpaceReason::MIDDLE);
}

/**
 * @tc.name: CheckHorizontalRange001
 * @tc.desc: Verify CheckHorizontalRange.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, CheckHorizontalRange001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 200.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    OffsetF position = { 500, 300 };
    EXPECT_FALSE(menuLayoutAlgorithm->CheckHorizontalRange(position, size));

    OffsetF positionTwo = { 10, 300 };
    EXPECT_FALSE(menuLayoutAlgorithm->CheckHorizontalRange(positionTwo, size));

    OffsetF positionThr = { 300, 300 };
    EXPECT_TRUE(menuLayoutAlgorithm->CheckHorizontalRange(positionThr, size));
}

/**
 * @tc.name: CheckVerticalRange001
 * @tc.desc: Verify CheckVerticalRange.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, CheckVerticalRange001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 200.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    OffsetF position = { 300, 500 };
    EXPECT_FALSE(menuLayoutAlgorithm->CheckVerticalRange(position, size));

    OffsetF positionTwo = { 200, 10 };
    EXPECT_FALSE(menuLayoutAlgorithm->CheckVerticalRange(positionTwo, size));

    OffsetF positionThr = { 300, 300 };
    EXPECT_TRUE(menuLayoutAlgorithm->CheckVerticalRange(positionThr, size));
}

/**
 * @tc.name: CheckFitScreen001
 * @tc.desc: Verify CheckFitScreen.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, CheckFitScreen001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 200.0, 200.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    OffsetF position = { 500, 300 };
    EXPECT_TRUE(menuLayoutAlgorithm->CheckFitScreen(position, size));

    OffsetF positionThr = { 300, 10 };
    EXPECT_TRUE(menuLayoutAlgorithm->CheckFitScreen(positionThr, size));

    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 70, 100);
    OffsetF positionTwo = { 300, 300 };
    EXPECT_FALSE(menuLayoutAlgorithm->CheckFitScreen(positionTwo, size));
}

/**
 * @tc.name: UpdateSideHeight001
 * @tc.desc: Verify UpdateSideHeight.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, UpdateSideHeight001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuNode->MountToParent(menuItemNode);
    menuPattern->parentMenuItem_ = menuItemNode;
    LayoutConstraintF parentLayoutConstraint;
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->UpdateSideHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuLayoutAlgorithm->proptargetSize_ = { 1000.0, 2000.0 };
    menuLayoutAlgorithm->UpdateSideHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    menuLayoutAlgorithm->propTargetOffset_ = { 350, 350 };
    menuLayoutAlgorithm->canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm->UpdateSideHeight(nullptr, parentLayoutConstraint, menuItemNode);
    EXPECT_EQ(parentLayoutConstraint.maxSize.Height(), 2595);
    menuLayoutAlgorithm->UpdateSideHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    EXPECT_EQ(parentLayoutConstraint.maxSize.Height(), 2595);
    auto menuLayoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(menuLayoutProperty, nullptr);
    menuLayoutProperty->layoutDirection_ = TextDirection::RTL;
    menuLayoutAlgorithm->canExpandCurrentWindow_ = false;
    auto pipelineContext = menuItemNode->GetContextWithCheck();
    pipelineContext->SetWindowModal(WindowModal::CONTAINER_MODAL);
    ASSERT_NE(pipelineContext, nullptr);
    menuLayoutAlgorithm->UpdateSideHeight(layoutWrapper, parentLayoutConstraint, menuItemNode);
    EXPECT_EQ(parentLayoutConstraint.maxSize.Height(), 2595);
    delete layoutWrapper;
}

/**
 * @tc.name: GetMeasureSize001
 * @tc.desc: Verify GetMeasureSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetMeasureSize001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    auto menuItemPattern = menuItemNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuNode->MountToParent(menuItemNode);
    menuPattern->parentMenuItem_ = menuItemNode;
    LayoutConstraintF parentLayoutConstraint;
    EXPECT_EQ(menuLayoutAlgorithm->GetMeasureSize(layoutWrapper, parentLayoutConstraint).Height(), 0);
    EXPECT_EQ(menuLayoutAlgorithm->GetMeasureSize(layoutWrapper, parentLayoutConstraint).Width(), 0);
    delete layoutWrapper;
}

/**
 * @tc.name: GetPlacementWithItem001
 * @tc.desc: Verify GetPlacementWithItem.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetPlacementWithItem001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", nullptr);
    optionParams.emplace_back("MenuItem2", "", nullptr);
    MenuParam menuParam;
    menuParam.type = MenuType::CONTEXT_MENU;
    menuParam.placement = Placement::TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuItemNode = FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, 4, AceType::MakeRefPtr<MenuItemPattern>());
    ASSERT_NE(menuItemNode, nullptr);
    menuItemNode->MountToParent(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->UpdateLastPlacement(Placement::TOP);
    EXPECT_EQ(menuLayoutAlgorithm->GetPlacementWithItem(menuItemNode), Placement::TOP);
}

/**
 * @tc.name: AddAdjustOffset001
 * @tc.desc: Verify AddAdjustOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, AddAdjustOffset001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->positionOffset_ = { 10, 10 };
    OffsetF position = { 400, 400 };
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 0);
    menuLayoutAlgorithm->placement_ = Placement::TOP_RIGHT;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 0);
    menuLayoutAlgorithm->placement_ = Placement::TOP;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 0);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 0);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::LEFT_BOTTOM;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 0);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::LEFT;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 0);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddAdjustOffset(position).GetY(), 410);
}

/**
 * @tc.name: AddCustomTargetSpace001
 * @tc.desc: Verify AddCustomTargetSpace.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, AddCustomTargetSpace001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    OffsetF position = { 400, 400 };
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 410);
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 390);
    menuLayoutAlgorithm->placement_ = Placement::TOP_RIGHT;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 390);
    menuLayoutAlgorithm->placement_ = Placement::TOP;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 390);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 400);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_BOTTOM;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 400);
    menuLayoutAlgorithm->placement_ = Placement::RIGHT;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 410);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 400);
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 390);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 400);
    menuLayoutAlgorithm->placement_ = Placement::LEFT_BOTTOM;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 390);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 400);
    menuLayoutAlgorithm->placement_ = Placement::LEFT;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 390);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 400);
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetX(), 400);
    EXPECT_EQ(menuLayoutAlgorithm->AddCustomTargetSpace(position).GetY(), 410);
}

/**
 * @tc.name: GetTargetSpaceDefaultPosition001
 * @tc.desc: Verify GetTargetSpaceDefaultPosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetTargetSpaceDefaultPosition001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    OffsetF topPosition = { 400, 400 };
    OffsetF bottomPosition = { 400, 400 };
    auto offset = menuLayoutAlgorithm->GetTargetSpaceDefaultPosition(topPosition, bottomPosition);
    EXPECT_EQ(offset.GetX(), 400.0f);
    EXPECT_EQ(offset.GetY(), 110.0f);
}

/**
 * @tc.name: CalcSubMenuMaxHeightTargetSpace001
 * @tc.desc: Verify CalcSubMenuMaxHeightTargetSpace.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, CalcSubMenuMaxHeightTargetSpace001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    OffsetF topPosition = { 400, 400 };
    OffsetF bottomPosition = { 400, 400 };
    auto offset1 = menuLayoutAlgorithm->GetTargetSpaceDefaultPosition(topPosition, bottomPosition);
    EXPECT_EQ(offset1.GetX(), 400.0f);
    EXPECT_EQ(offset1.GetY(), 110.0f);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    auto offset2 = menuLayoutAlgorithm->GetTargetSpaceDefaultPosition(topPosition, bottomPosition);
    EXPECT_EQ(offset2.GetX(), 400.0f);
    EXPECT_EQ(offset2.GetY(), 110.0f);
}

/**
 * @tc.name: FitToTargetSpaceScreen001
 * @tc.desc: Verify FitToTargetSpaceScreen.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, FitToTargetSpaceScreen001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    OffsetF position = { 400, 400 };
    SizeF size(150.0f, 150.0f);
    menuLayoutAlgorithm->flag_ = true;
    auto offset1 = menuLayoutAlgorithm->FitToTargetSpaceScreen(position, size, true);
    EXPECT_EQ(offset1.GetX(), 0.0f);
    EXPECT_EQ(offset1.GetY(), 0.0f);
    menuLayoutAlgorithm->positionOffset_ = { 10, 10 };
    menuLayoutAlgorithm->flag_ = false;
    auto offset2 = menuLayoutAlgorithm->FitToTargetSpaceScreen(position, size, true);
    EXPECT_EQ(offset2.GetX(), 410.0f);
    EXPECT_EQ(offset2.GetY(), 420.0f);
    menuLayoutAlgorithm->positionOffset_ = { 10000, 10000 };
    auto offset3 = menuLayoutAlgorithm->FitToTargetSpaceScreen(position, size, true);
    EXPECT_EQ(offset3.GetX(), 400.0f);
    EXPECT_EQ(offset3.GetY(), 410.0f);
}

/**
 * @tc.name: GetAdjustTargetSpacePosition001
 * @tc.desc: Verify GetAdjustTargetSpacePosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetAdjustTargetSpacePosition001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    std::vector<Placement> curPlaceStates1 = { Placement::NONE, Placement::RIGHT, Placement::TOP, Placement::LEFT };
    OffsetF position = { 400, 400 };
    SizeF size(150.0f, 150.0f);
    OffsetF topPosition = { 400, 400 };
    OffsetF bottomPosition = { 400, 400 };
    auto offset1 =
        menuLayoutAlgorithm->GetAdjustTargetSpacePosition(curPlaceStates1, 4, size, topPosition, bottomPosition);
    EXPECT_EQ(offset1.GetX(), 0.0f);
    EXPECT_EQ(offset1.GetY(), 0.0f);
    std::vector<Placement> curPlaceStates2 = { Placement::LEFT, Placement::RIGHT, Placement::TOP, Placement::NONE };
    SizeF size1(0.0f, 0.0f);
    OffsetF topPosition1 = { 0, 0 };
    OffsetF bottomPosition1 = { 0, 0 };
    auto offset2 =
        menuLayoutAlgorithm->GetAdjustTargetSpacePosition(curPlaceStates2, 4, size1, topPosition1, bottomPosition1);
    EXPECT_EQ(offset2.GetX(), 0.0f);
    EXPECT_EQ(offset2.GetY(), 0.0f);
    auto offset3 =
        menuLayoutAlgorithm->GetAdjustTargetSpacePosition(curPlaceStates2, 1, size, topPosition, bottomPosition);
    EXPECT_EQ(offset3.GetX(), 110.0f);
    EXPECT_EQ(offset3.GetY(), 72.0f);
}

/**
 * @tc.name: GetTargetSpacePosition001
 * @tc.desc: Verify GetTargetSpacePosition.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TwoTestNg, GetTargetSpacePosition001, TestSize.Level1)
{
    auto menuLayoutAlgorithm = GetMenuLayoutAlgorithm();
    ASSERT_TRUE(menuLayoutAlgorithm);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    SizeF size(150.0f, 150.0f);
    menuLayoutAlgorithm->placement_ = Placement::LEFT;
    auto offset1 = menuLayoutAlgorithm->GetTargetSpacePosition(size, true);
    EXPECT_EQ(offset1.GetX(), 110.0f);
    EXPECT_EQ(offset1.GetY(), 72.0f);
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
    SizeF size1(0.0f, 0.0f);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(0);
    menuLayoutAlgorithm->proptargetSize_ = { 0.0, 0.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 0, 0 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(0, 0, 0, 0);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(0.0f, 0.0f);
    auto offset2 = menuLayoutAlgorithm->GetTargetSpacePosition(size1, true);
    EXPECT_EQ(offset2.GetX(), 50.0f);
    EXPECT_EQ(offset2.GetY(), 1.0f);
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    auto offset3 = menuLayoutAlgorithm->GetTargetSpacePosition(size, true);
    EXPECT_EQ(offset3.GetX(), -25.0f);
    EXPECT_EQ(offset3.GetY(), 1.0f);
    menuLayoutAlgorithm->propTargetSpace_ = Dimension(10);
    menuLayoutAlgorithm->proptargetSize_ = { 50.0, 50.0 };
    menuLayoutAlgorithm->propTargetOffset_ = { 200, 200 };
    menuLayoutAlgorithm->wrapperRect_ = Rect(12, 72, 700, 1000);
    menuLayoutAlgorithm->wrapperSize_ = SizeF(720.0f, 1136.0f);
    menuLayoutAlgorithm->placement_ = Placement::NONE;
    auto offset4 = menuLayoutAlgorithm->GetTargetSpacePosition(size, true);
    EXPECT_EQ(offset4.GetX(), 64.0f);
    EXPECT_EQ(offset4.GetY(), 110.0f);
}
} // namespace OHOS::Ace::NG
