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
} // namespace OHOS::Ace::NG

