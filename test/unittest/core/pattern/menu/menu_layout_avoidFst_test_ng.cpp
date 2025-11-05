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
constexpr int32_t NODE_ID = 1;
constexpr float FULL_PHONE_WIDTH = 1260.0f;
constexpr float FULL_PHONE_HEIGHT = 2596.0f;
constexpr float TARGET_SIZE_WIDTH = 100.0f;
constexpr float TARGET_SIZE_HEIGHT = 100.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
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

class MenuLayoutAvoid1TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<MenuLayoutAlgorithm> GetMenuLayoutAlgorithm();
};

void MenuLayoutAvoid1TestNg::SetUpTestCase() {}

void MenuLayoutAvoid1TestNg::TearDownTestCase() {}

void MenuLayoutAvoid1TestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayoutAvoid1TestNg::TearDown()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

RefPtr<MenuLayoutAlgorithm> MenuLayoutAvoid1TestNg::GetMenuLayoutAlgorithm()
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
 * @tc.name: MenuLayoutNormalTestNg001
 * @tc.desc: Test Menu in Center with RightBottom Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Initialize menuNode parameters.
     * @tc.expected: menuNode parameters is as expected.
     */
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
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() - menuSize.Height());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT_BOTTOM);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg002
 * @tc.desc: Test Menu in Center with Right Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest002, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::RIGHT;
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
    menuParam.placement = Placement::RIGHT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() / 2 - menuSize.Height() / 2);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg003
 * @tc.desc: Test Menu in Center with RightTop Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest003, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
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
    menuParam.placement = Placement::RIGHT_TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT_TOP);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg004
 * @tc.desc: Test Menu in Center with LeftBottom Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest004, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::LEFT_BOTTOM;
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
    menuParam.placement = Placement::LEFT_BOTTOM;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() - menuSize.Width() -
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() - menuSize.Height());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::LEFT_BOTTOM);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg005
 * @tc.desc: Test Menu in Center with Left Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest005, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::LEFT;
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
    menuParam.placement = Placement::LEFT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() - menuSize.Width() -
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() / 2 - menuSize.Height() / 2);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::LEFT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg006
 * @tc.desc: Test Menu in Center with LeftTop Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest006, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
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
    menuParam.placement = Placement::LEFT_TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() - menuSize.Width() -
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::LEFT_TOP);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg007
 * @tc.desc: Test Menu in Center with TopRight Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest007, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::TOP_RIGHT;
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
    menuParam.placement = Placement::TOP_RIGHT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() -
        menuSize.Width(), menuLayoutAlgorithm->targetOffset_.GetY() -
        menuSize.Height() - menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::TOP_RIGHT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg008
 * @tc.desc: Test Menu in Center with Top Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest008, TestSize.Level1)
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
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() / 2 -
        menuSize.Width() / 2, menuLayoutAlgorithm->targetOffset_.GetY() -
        menuSize.Height() - menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::TOP);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg009
 * @tc.desc: Test Menu in Center with TopLeft Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest009, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
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
    menuParam.placement = Placement::TOP_LEFT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX(), menuLayoutAlgorithm->targetOffset_.GetY() -
        menuSize.Height() - menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::TOP_LEFT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg010
 * @tc.desc: Test Menu in Center with BottomRight Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest010, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
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
    menuParam.placement = Placement::BOTTOM_RIGHT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() -
        menuSize.Width(), menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM_RIGHT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg011
 * @tc.desc: Test Menu in Center with Bottom Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest011, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM;
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
    menuParam.placement = Placement::BOTTOM;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() / 2 -
        menuSize.Width() / 2, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutNormalTestNg012
 * @tc.desc: Test Menu in Center with BottomLeft Placement Normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutNormalTest012, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
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
    menuParam.placement = Placement::BOTTOM_LEFT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX(), menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM_LEFT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverWidthTestNg001
 * @tc.desc: Test Menu in Center with RightBottom Placement Over Width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverWidthTest001, TestSize.Level1)
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

    /**
     * @tc.steps: step2. Initialize menuNode parameters.
     * @tc.expected: menuNode parameters is as expected.
     */
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
    SizeF menuSize(FULL_PHONE_WIDTH / 2, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->param_.leftSecurity, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM_RIGHT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverWidthTestNg002
 * @tc.desc: Test Menu in Center with Right Placement Over Width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverWidthTest002, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::RIGHT;
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
    menuParam.placement = Placement::RIGHT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(FULL_PHONE_WIDTH / 2, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() / 2 -
        menuSize.Width() / 2, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverWidthTestNg003
 * @tc.desc: Test Menu in Center with RightTop Placement Over Width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverWidthTest003, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::RIGHT_TOP;
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
    menuParam.placement = Placement::RIGHT_TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(FULL_PHONE_WIDTH / 2, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->wrapperRect_.Width() - menuLayoutAlgorithm->param_.rightSecurity -
        menuSize.Width(), menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM_LEFT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverWidthTestNg004
 * @tc.desc: Test Menu in Center with LeftBottom Placement Over Width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverWidthTest004, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::LEFT_BOTTOM;
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
    menuParam.placement = Placement::LEFT_BOTTOM;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(FULL_PHONE_WIDTH / 2, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->param_.leftSecurity, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM_RIGHT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverWidthTestNg005
 * @tc.desc: Test Menu in Center with Left Placement Over Width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverWidthTest005, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::LEFT;
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
    menuParam.placement = Placement::LEFT;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(FULL_PHONE_WIDTH / 2, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() / 2 -
        menuSize.Width() / 2, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverWidthTestNg006
 * @tc.desc: Test Menu in Center with LeftTop Placement Over Width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverWidthTest006, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::LEFT_TOP;
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
    menuParam.placement = Placement::LEFT_TOP;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::CONTEXT_MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuProp = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF menuSize(FULL_PHONE_WIDTH / 2, MENU_SIZE_HEIGHT);
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(menuGeometryNode, nullptr);
    LayoutWrapperNode* layoutWrapper = new LayoutWrapperNode(menuNode, menuGeometryNode, menuProp);
    ASSERT_NE(layoutWrapper, nullptr);
    menuLayoutAlgorithm->InitSpace(menuProp, menuPattern);

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->wrapperRect_.Width() - menuLayoutAlgorithm->param_.rightSecurity -
        menuSize.Width(), menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() + menuLayoutAlgorithm->targetSecurity_);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::BOTTOM_LEFT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverHeightTestNg001
 * @tc.desc: Test Menu in Center with BottomRight Placement Over Height.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverHeightTest001, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_RIGHT;
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
    menuParam.placement = Placement::BOTTOM_RIGHT;
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

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() - menuSize.Height());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT_BOTTOM);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverHeightTestNg002
 * @tc.desc: Test Menu in Center with Bottom Placement Over Height.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverHeightTest002, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM;
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
    menuParam.placement = Placement::BOTTOM;
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

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY() +
        menuLayoutAlgorithm->targetSize_.Height() / 2 - menuSize.Height() / 2);
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverHeightTestNg003
 * @tc.desc: Test Menu in Center with BottomLeft Placement Over Height.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverHeightTest003, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::BOTTOM_LEFT;
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
    menuParam.placement = Placement::BOTTOM_LEFT;
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

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT_TOP);
    ASSERT_EQ(afterPosition, expectedPosition);
}

/**
 * @tc.name: MenuLayoutOverHeightTestNg004
 * @tc.desc: Test Menu in Center with TopLeft Placement Over Height.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayoutAvoid1TestNg, MenuLayoutOverHeightTest004, TestSize.Level1)
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
    menuLayoutAlgorithm->placement_ = Placement::TOP_LEFT;
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
    menuParam.placement = Placement::TOP_LEFT;
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

    /**
     * @tc.steps: step3. Afer menuLayoutAvoidAlgorithm avoid placement.
     * @tc.expected: position and placement is as expected.
     */
    auto expectedPosition = OffsetF(
        menuLayoutAlgorithm->targetOffset_.GetX() + menuLayoutAlgorithm->targetSize_.Width() +
        menuLayoutAlgorithm->targetSecurity_, menuLayoutAlgorithm->targetOffset_.GetY());
    auto afterPosition =
        menuLayoutAlgorithm->MenuLayoutAvoidAlgorithm(menuProp, menuPattern, menuSize, false, layoutWrapper);
    delete layoutWrapper;
    ASSERT_EQ(menuLayoutAlgorithm->placement_, Placement::RIGHT_TOP);
    ASSERT_EQ(afterPosition, expectedPosition);
}
} // namespace OHOS::Ace::NG