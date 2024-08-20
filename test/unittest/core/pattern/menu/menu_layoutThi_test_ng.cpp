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
#include "core/pipeline/pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr int32_t TARGET = 0;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 50.0f;
constexpr float TARGET_SIZE_HEIGHT = 50.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr float KEYBOARD_HEIGHT = 600.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
} // namespace

class MenuLayout3TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> GetOrCreateMenu(MenuType type = MenuType::MENU);
    RefPtr<FrameNode> GetTargetNode()
    {
        return targetNode_;
    }
    void SetMenuNodeFrameSize(SizeF size = SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
private:
    RefPtr<FrameNode> CreateMenuWrapperElement(MenuType type);
    RefPtr<FrameNode> CreateTargetNodeWithMainTree();
    RefPtr<FrameNode> menuNode_;
    RefPtr<FrameNode> targetNode_;
    RefPtr<FrameNode> rootNode_;
};

void MenuLayout3TestNg::SetUpTestCase() {}

void MenuLayout3TestNg::TearDownTestCase() {}

void MenuLayout3TestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayout3TestNg::TearDown()
{
    MockContainer::TearDown();
    MockPipelineContext::TearDown();
    menuNode_ = nullptr;
    targetNode_ = nullptr;
    rootNode_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

RefPtr<FrameNode> MenuLayout3TestNg::CreateTargetNodeWithMainTree()
{
    rootNode_ = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode_, nullptr);
    auto targetNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(targetNode, nullptr);
    auto targetGeometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_RETURN(targetGeometryNode, nullptr);
    targetGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));
    targetNode->MountToParent(rootNode_);
    return targetNode;
}

RefPtr<FrameNode> MenuLayout3TestNg::CreateMenuWrapperElement(MenuType type)
{
    if (!targetNode_) {
        targetNode_ = CreateTargetNodeWithMainTree();
    }
    CHECK_NULL_RETURN(targetNode_, nullptr);
    MenuParam menuParam;
    menuParam.placement = Placement::BOTTOM_RIGHT;
    std::vector<OptionParam> params;
    for (int32_t i = TARGET; i < TARGET_ID; ++i) {
        OptionParam param;
        params.emplace_back(param);
    }
    auto menuWrapper = MenuView::Create(
        std::move(params), targetNode_->GetId(), targetNode_->GetTag(), type, menuParam);
    return menuWrapper;
}

RefPtr<FrameNode> MenuLayout3TestNg::GetOrCreateMenu(MenuType type)
{
    if (!menuNode_) {
        auto menuWrapperNode = CreateMenuWrapperElement(type);
        CHECK_NULL_RETURN(menuWrapperNode, nullptr);
        auto frameNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
        if (frameNode->GetTag() == V2::MENU_ETS_TAG) {
            menuNode_ = frameNode;
        }
    }
    return menuNode_;
}

void MenuLayout3TestNg::SetMenuNodeFrameSize(SizeF size)
{
    if (menuNode_) {
        auto geometryNode = menuNode_->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->SetFrameSize(size);
    }
}

/**
 * @tc.name: ModifyPreviewMenuPlacement001
 * @tc.desc: Test ModifyPreviewMenuPlacement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, ModifyPreviewMenuPlacement001, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu();
    ASSERT_NE(menuNode, nullptr);

    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto props = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    ASSERT_NE(props, nullptr);
    props->ResetMenuPlacement();
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto menuTheme = AceType::MakeRefPtr<MenuTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(menuTheme));

    menuAlgorithm->ModifyPreviewMenuPlacement(AceType::RawPtr(menuNode));
    EXPECT_EQ(menuAlgorithm->GetPlacement(), Placement::RIGHT_TOP);
}

/**
 * @tc.name: Initialize001
 * @tc.desc: Test Initialize with API12
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Initialize001, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu(MenuType::SUB_MENU);
    ASSERT_NE(menuNode, nullptr);

    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto menuTheme = AceType::MakeRefPtr<MenuTheme>();
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();

    auto props = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    ASSERT_NE(props, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillOnce(Return(menuTheme)).WillOnce(Return(selectTheme));
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    menuAlgorithm->Initialize(AceType::RawPtr(menuNode));
    EXPECT_EQ(menuAlgorithm->GetPlacement(), Placement::BOTTOM_RIGHT);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: InitializeParam001
 * @tc.desc: Test InitializeParam
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitializeParam, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);

    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto safeAreaManager = context->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    EXPECT_TRUE(safeAreaManager->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT));

    int32_t backApiVersion = context->GetMinPlatformVersion();
    context->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    menuAlgorithm->InitializeParam(menuPattern);
    EXPECT_EQ(menuAlgorithm->param_.topSecurity, PORTRAIT_TOP_SECURITY_API12.ConvertToPx());
    EXPECT_EQ(menuAlgorithm->param_.bottomSecurity, PORTRAIT_BOTTOM_SECURITY_API12.ConvertToPx());
    context->SetMinPlatformVersion(backApiVersion);

    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    menuAlgorithm->InitializeParam(menuPattern);
    EXPECT_EQ(menuAlgorithm->param_.topSecurity, LANDSCAPE_TOP_SECURITY.ConvertToPx());
    EXPECT_EQ(menuAlgorithm->param_.bottomSecurity, LANDSCAPE_BOTTOM_SECURITY.ConvertToPx());
}
} // namespace OHOS::Ace::NG
