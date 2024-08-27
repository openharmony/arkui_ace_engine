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
constexpr int32_t DEFAULT_CHILD_COUNT = 5;
constexpr int32_t TARGET_ID = 3;
constexpr int32_t TARGET = 0;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 50.0f;
constexpr float TARGET_SIZE_HEIGHT = 50.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
constexpr float KEYBOARD_HEIGHT = 600.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const Dimension CONTAINER_BORDER_WIDTH = 1.0_vp;
const Dimension CONTENT_PADDING = 4.0_vp;
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
    RefPtr<MenuLayoutAlgorithm> CreateMenuLayoutAlgorithm(MenuType type = MenuType::MENU);
    void MountMenuItemToParent(const RefPtr<FrameNode>& parent, int32_t childCount, bool isNeedGroup = false);
private:
    RefPtr<FrameNode> CreateMenuWrapperElement(MenuType type);
    RefPtr<FrameNode> CreateTargetNodeWithMainTree();
    RefPtr<FrameNode> menuWrapperNode_;
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
    menuWrapperNode_ = nullptr;
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
    if (!menuWrapperNode_) {
        menuWrapperNode_ = CreateMenuWrapperElement(type);
    }
    CHECK_NULL_RETURN(menuWrapperNode_, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode_->GetChildAtIndex(0));
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    return menuPattern->GetMenuType() == type ? menuNode : nullptr;
}

RefPtr<MenuLayoutAlgorithm> MenuLayout3TestNg::CreateMenuLayoutAlgorithm(MenuType type)
{
    auto menuNode = GetOrCreateMenu(type);
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(menuAlgorithmWrapper, nullptr);
    return AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
}

void MenuLayout3TestNg::MountMenuItemToParent(const RefPtr<FrameNode>& parent, int32_t childCount, bool isNeedGroup)
{
    CHECK_NULL_VOID(parent);
    CHECK_NULL_VOID(parent->GetTag() == V2::MENU_ETS_TAG);
    RefPtr<UINode> itemGroupNode;
    if (isNeedGroup) {
        itemGroupNode = FrameNode::GetOrCreateFrameNode(
            V2::MENU_ITEM_GROUP_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<MenuItemGroupPattern>(); });
    }
    for (int32_t i = 0; i < childCount; ++i) {
        auto itemNode = FrameNode::GetOrCreateFrameNode(
            V2::MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
        if (!itemNode) {
            continue;
        }
        if (isNeedGroup && itemGroupNode) {
            itemNode->MountToParent(itemGroupNode);
        } else {
            itemNode->MountToParent(parent);
        }
    }
    if (isNeedGroup && itemGroupNode) {
        itemGroupNode->MountToParent(parent);
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
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
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

    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
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
HWTEST_F(MenuLayout3TestNg, InitializeParam001, TestSize.Level1)
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

/**
 * @tc.name: InitWrapperRect001
 * @tc.desc: Test InitWrapperRect
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitWrapperRect001, TestSize.Level1)
{
    auto menuAlgorithm = CreateMenuLayoutAlgorithm(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);

    menuPattern->SetPreviewMode(MenuPreviewMode::IMAGE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto safeAreaManager = context->GetSafeAreaManager();
    ASSERT_NE(safeAreaManager, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    EXPECT_TRUE(safeAreaManager->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT));
    context->UpdateDisplayAvailableRect(Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    context->SetDisplayWindowRectInfo(Rect(0, 0, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    context->SetWindowModal(WindowModal::CONTAINER_MODAL);
    windowManager->SetWindowGetModeCallBack([]() -> WindowMode {
        return WindowMode::WINDOW_MODE_FLOATING;
    });

    int32_t backApiVersion = context->GetMinPlatformVersion();
    context->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    menuAlgorithm->hierarchicalParameters_ = true;
    menuAlgorithm->InitWrapperRect(props, menuPattern);
    menuAlgorithm->hierarchicalParameters_ = false;
    menuAlgorithm->InitWrapperRect(props, menuPattern);
    EXPECT_EQ(menuAlgorithm->wrapperRect_.Width(), FULL_SCREEN_WIDTH);
    EXPECT_EQ(menuAlgorithm->wrapperRect_.Height(), FULL_SCREEN_HEIGHT - KEYBOARD_HEIGHT);
    context->SetMinPlatformVersion(backApiVersion);
}

/**
 * @tc.name: InitSpace001
 * @tc.desc: Test InitSpace
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitSpace001, TestSize.Level2)
{
    auto menuAlgorithm = CreateMenuLayoutAlgorithm();
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu();
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    props->ResetMenuPlacement();
    int32_t backApiVersion = context->GetMinPlatformVersion();
    context->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    menuAlgorithm->InitSpace(props, menuPattern);
    EXPECT_TRUE(NearZero(menuAlgorithm->topSpace_));
    EXPECT_TRUE(NearZero(menuAlgorithm->bottomSpace_));
    context->SetMinPlatformVersion(backApiVersion);

    props->UpdateMenuPlacement(Placement::BOTTOM_RIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(0.0f, TARGET_SECURITY.ConvertToPx());
    menuAlgorithm->InitSpace(props, menuPattern);
    EXPECT_TRUE(NearZero(menuAlgorithm->leftSpace_));
    EXPECT_TRUE(NearZero(menuAlgorithm->rightSpace_));
}

/**
 * @tc.name: ModifyPositionToWrapper001
 * @tc.desc: Test ModifyPositionToWrapper
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, ModifyPositionToWrapper001, TestSize.Level1)
{
    auto menuAlgorithm = CreateMenuLayoutAlgorithm();
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu();
    ASSERT_NE(menuNode, nullptr);
    auto wrapper = AceType::DynamicCast<FrameNode>(menuNode->GetParent());
    ASSERT_NE(wrapper, nullptr);
    auto wrapperProps = wrapper->GetLayoutProperty();
    ASSERT_NE(wrapperProps, nullptr);

    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    context->SetWindowModal(WindowModal::CONTAINER_MODAL);
    windowManager->SetWindowGetModeCallBack([]() -> WindowMode {
        return WindowMode::WINDOW_MODE_FLOATING;
    });

    SafeAreaInsets safeAreaPosition;
    wrapperProps->UpdateSafeAreaInsets(safeAreaPosition);
    OffsetF result = OffsetF(static_cast<float>((CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx()),
        static_cast<float>((CONTAINER_BORDER_WIDTH).ConvertToPx()));
    menuAlgorithm->ModifyPositionToWrapper(AceType::RawPtr(menuNode), result);
    EXPECT_TRUE(NearZero(result.GetX()));
    EXPECT_TRUE(NearZero(result.GetY()));
}

/**
 * @tc.name: Measure001
 * @tc.desc: Test Measure
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Measure001, TestSize.Level1)
{
    auto menuAlgorithm = CreateMenuLayoutAlgorithm(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize = OptionalSizeF(1.0f, 1.0f);
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    menuPattern->SetIsSelectMenu(true);
    menuPattern->SetHasOptionWidth(true);

    MountMenuItemToParent(menuNode, DEFAULT_CHILD_COUNT);
    auto menuItem = AceType::DynamicCast<FrameNode>(menuNode->GetLastChild());
    ASSERT_NE(menuItem, nullptr);
    auto parentPattern = menuItem->GetPattern<MenuItemPattern>();
    ASSERT_NE(parentPattern, nullptr);
    parentPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    menuPattern->SetParentMenuItem(menuItem);
    auto geometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuNode, geometryNode, props);
    for (const auto& child : menuNode->GetChildren()) {
        auto menuItem = AceType::DynamicCast<FrameNode>(child);
        ASSERT_NE(menuItem, nullptr);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, menuItem->GetLayoutProperty());
        wrapper->AppendChild(childWrapper);
    }
    menuAlgorithm->Measure(AceType::RawPtr(wrapper));
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), MENU_ITEM_SIZE_WIDTH);
}
} // namespace OHOS::Ace::NG
