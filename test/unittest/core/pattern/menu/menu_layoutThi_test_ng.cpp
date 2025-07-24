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

#include "core/common/ace_engine.h"
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
constexpr int32_t CREASE_X = 0;
constexpr int32_t CREASE_Y = 1064;
constexpr int32_t CREASE_WIDTH = 2294;
constexpr int32_t CREASE_HEIGHT = 171;
constexpr int32_t CREASE_BOTTOM = 1235;
constexpr int32_t MENU_X = 100;
constexpr int32_t MENU_Y_TOP = 100;
constexpr int32_t MENU_Y_BOTTOM = 1400;
constexpr int32_t MENU_Y_MIDDLE = 1100;
constexpr int32_t NODE_ID = 1;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 50.0f;
constexpr float TARGET_SIZE_HEIGHT = 50.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
constexpr float KEYBOARD_HEIGHT = 600.0f;
constexpr float WIDTH = 10.0f;
constexpr float HEIGHT = 20.0f;
constexpr float SPACE = 30.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const Dimension CONTAINER_BORDER_WIDTH = 0.0_vp;
const Dimension CONTENT_PADDING = 4.0_vp;
constexpr float OFFSET_FIRST = 50.0f;
constexpr float OFFSET_SECOND = 100.0f;
constexpr float OFFSET_FIRST_NEW = 100.0f;
constexpr float TARGET_OFFSET_FIRST = 10.0f;
constexpr float TARGET_OFFSET_SECOND = 10.0f;
constexpr float RECT_FIRST = 10.0f;
constexpr float RECT_SECOND = 10.0f;
constexpr float RECT_THIRD = 10.0f;
constexpr float RECT_FORTH = 10.0f;
constexpr float RECT_THIRD_NEW = 20.0f;
constexpr float RECT_FORTH_NEW = 20.0f;
constexpr float TWENTY = 20.0f;
constexpr float ZERO = 0.0f;
constexpr float ONE = 1.0f;
constexpr float TWO = 2.0f;
constexpr float FIVE = 5.0f;
constexpr float TEN = 10.0f;
constexpr float FIFTY = 50.0f;
constexpr float MAX_SIZE_HEIGHT = -100.0f;
constexpr float OFFSET_X = -10.0f;
constexpr float OFFSET_X_NEW = -20.0f;
constexpr float ONE_HUNDRED = 100.0f;
const std::string MENU_TAG = "menu";
} // namespace

class MenuLayout3TestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void MockPipelineContextGetTheme();
    void InitTargetFrameNode();
    void InitMenuWrapperNode();
    RefPtr<FrameNode> GetOrCreateMenu(MenuType type = MenuType::MENU);
    RefPtr<FrameNode> GetTargetNode()
    {
        return targetNode_;
    }
    RefPtr<MenuLayoutAlgorithm> CreateMenuLayoutAlgorithm(MenuType type = MenuType::MENU);
    void MountMenuItemToParent(const RefPtr<FrameNode>& parent, int32_t childCount, bool isNeedGroup = false);
    RefPtr<FrameNode> GetPreviewMenuWrapper(
        SizeF itemSize = SizeF(0.0f, 0.0f), std::optional<MenuPreviewAnimationOptions> scaleOptions = std::nullopt);
private:
    RefPtr<FrameNode> CreateMenuWrapperElement(MenuType type);
    RefPtr<FrameNode> CreateTargetNodeWithMainTree();
    RefPtr<FrameNode> menuWrapperNode_;
    RefPtr<FrameNode> targetNode_;
    RefPtr<FrameNode> rootNode_;
    RefPtr<FrameNode> targetFrameNode_;
    RefPtr<FrameNode> wrapperNode_;
    int32_t targetId_ = 0;
    std::string targetTag_ = "";
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

void MenuLayout3TestNg::MockPipelineContextGetTheme()
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

RefPtr<FrameNode> MenuLayout3TestNg::GetPreviewMenuWrapper(
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

void MenuLayout3TestNg::InitTargetFrameNode()
{
    targetFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(targetFrameNode_, nullptr);
    targetId_ = targetFrameNode_->GetId();
    targetTag_ = targetFrameNode_->GetTag();
}

void MenuLayout3TestNg::InitMenuWrapperNode()
{
    InitTargetFrameNode();
    std::function<void()> action = [] {};
    std::vector<OptionParam> optionParams;
    optionParams.emplace_back("MenuItem1", "", action);
    optionParams.emplace_back("MenuItem2", "", action);
    MenuParam menuParam;
    wrapperNode_ = MenuView::Create(
        std::move(optionParams), targetId_, targetTag_, MenuType::SELECT_OVERLAY_EXTENSION_MENU, menuParam);
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();

    auto container = Container::Current();
    menuNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);

    auto layoutWrapper = new LayoutWrapperNode(menuNode, geometryNode, menuNode->GetLayoutProperty());
    menuAlgorithm->InitializeParam(layoutWrapper, menuPattern);
    EXPECT_EQ(menuAlgorithm->param_.topSecurity, PORTRAIT_TOP_SECURITY_API12.ConvertToPx());
    EXPECT_EQ(menuAlgorithm->param_.bottomSecurity, PORTRAIT_BOTTOM_SECURITY_API12.ConvertToPx());
    context->SetMinPlatformVersion(backApiVersion);

    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    menuAlgorithm->InitializeParam(layoutWrapper, menuPattern);
    EXPECT_EQ(menuAlgorithm->param_.topSecurity, LANDSCAPE_TOP_SECURITY.ConvertToPx());
    EXPECT_EQ(menuAlgorithm->param_.bottomSecurity, LANDSCAPE_BOTTOM_SECURITY.ConvertToPx());
    delete layoutWrapper;
    layoutWrapper = nullptr;
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

    auto nodeContainer = Container::Current();
    menuNode->instanceId_ = nodeContainer->GetInstanceId();
    AceEngine::Get().AddContainer(nodeContainer->GetInstanceId(), nodeContainer);

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
    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    context->SetWindowModal(WindowModal::CONTAINER_MODAL);
    windowManager->SetWindowGetModeCallBack([]() -> WindowMode {
        return WindowMode::WINDOW_MODE_FLOATING;
    });

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    int32_t backApiversion = container->GetApiTargetVersion();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    menuAlgorithm->canExpandCurrentWindow_ = true;
    menuAlgorithm->InitWrapperRect(props, menuPattern);
    EXPECT_EQ(menuAlgorithm->wrapperRect_.Width(), FULL_SCREEN_WIDTH);
    EXPECT_EQ(menuAlgorithm->wrapperRect_.Height(), FULL_SCREEN_HEIGHT - KEYBOARD_HEIGHT);
    container->SetApiTargetVersion(backApiversion);
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

    auto container = Container::Current();
    menuNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
    
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
    EXPECT_FALSE(NearZero(result.GetX()));
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

/**
 * @tc.name: MenuLayoutAlgorithmTestNg049
 * @tc.desc: Verify menu component is in the upper area of the screen in the hover state.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg049, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    // get menuPattern and property
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->enableFold_ = true;
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(CREASE_X, CREASE_Y, CREASE_WIDTH, CREASE_HEIGHT);
    rects.insert(rects.end(), rect);
    displayInfo->SetCurrentFoldCreaseRegion(rects);
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    
    int32_t creaseYTop = CREASE_Y;
    layoutAlgorithm->targetOffset_ = OffsetF(MENU_X, MENU_Y_TOP);
    layoutAlgorithm->position_ = OffsetF(MENU_X, MENU_Y_TOP);
    layoutAlgorithm->UpdateWrapperRectForHoverMode(property, menuPattern, 0.0);

    auto top = layoutAlgorithm->top_;
    auto left = layoutAlgorithm->left_;
    auto right = layoutAlgorithm->right_;
    auto width = layoutAlgorithm->width_;

    /**
     * @tc.steps: menu component is located in the upper half of the screen.
     * @tc.expected: menu wrapperRect is equal to the size of the security box on the upper half screen.
     */
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect(left, top, width - left - right, creaseYTop - top));

    float windowsOffsetY = 0.0f;
    layoutAlgorithm->canExpandCurrentWindow_= true;
    layoutAlgorithm->param_.windowsOffsetY = windowsOffsetY;
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect(left, top + windowsOffsetY, width - left - right, creaseYTop - top));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg050
 * @tc.desc: Verify menu component is in the lower area of the screen in the hover state.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg050, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->enableFold_ = true;

    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(CREASE_X, CREASE_Y, CREASE_WIDTH, CREASE_HEIGHT);
    rects.insert(rects.end(), rect);
    displayInfo->SetCurrentFoldCreaseRegion(rects);
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();

    int32_t creaseYBottom = CREASE_BOTTOM;

    layoutAlgorithm->targetOffset_ = OffsetF(MENU_X, MENU_Y_BOTTOM);
    layoutAlgorithm->position_ = OffsetF(MENU_X, MENU_Y_BOTTOM);
    layoutAlgorithm->UpdateWrapperRectForHoverMode(property, menuPattern, 0.0);

    auto bottom = layoutAlgorithm->bottom_;
    auto left = layoutAlgorithm->left_;
    auto right = layoutAlgorithm->right_;
    auto width = layoutAlgorithm->width_;
    auto height = layoutAlgorithm->height_;

    /**
     * @tc.steps: menu component is located in the lowwer half of the screen.
     * @tc.expected: menu wrapperRect is equal to the size of the security box on the lowwer half screen.
     */
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect(left, creaseYBottom, width - left - right,
        height - creaseYBottom - bottom));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg051
 * @tc.desc: Verify Initialize and Measure when DeviceOrientation is not PORTRAIT.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg051, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    MenuParam menuParam;

    // create menuWrapperNode to get main menu
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 1, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
    ASSERT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);

    // get menuPattern and property
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->enableFold_ = true;

    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    ASSERT_TRUE(property->GetPositionOffset().has_value());
    EXPECT_EQ(property->GetPositionOffset().value(), OffsetF());

    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    std::vector<Rect> rects;
    Rect rect;
    rect.SetRect(CREASE_X, CREASE_Y, CREASE_WIDTH, CREASE_HEIGHT);
    rects.insert(rects.end(), rect);
    displayInfo->SetCurrentFoldCreaseRegion(rects);
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();

    layoutAlgorithm->targetOffset_ = OffsetF(MENU_X, MENU_Y_MIDDLE);
    layoutAlgorithm->position_ = OffsetF(MENU_X, MENU_Y_MIDDLE);
    layoutAlgorithm->UpdateWrapperRectForHoverMode(property, menuPattern, 0.0);

    auto top = layoutAlgorithm->top_;
    auto bottom = layoutAlgorithm->bottom_;
    auto left = layoutAlgorithm->left_;
    auto right = layoutAlgorithm->right_;
    auto width = layoutAlgorithm->width_;
    auto height = layoutAlgorithm->height_;

    /**
     * @tc.steps: menu component is located in the crease area of the screen.
     * @tc.expected: menu wrapperRect is equal to the size of the security box on whole screen.
     */
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect(left, top, width - left - right, height - top - bottom));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg052
 * @tc.desc: Verify Initialize and Measure when layoutRegion is set.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg052, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto menuWrapperNode = GetPreviewMenuWrapper();
    ASSERT_NE(menuWrapperNode, nullptr);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);

    MarginProperty margin = {
        .top = CalcLength(OFFSET_SECOND),
        .bottom = CalcLength(0.0),
        .start = CalcLength(OFFSET_SECOND),
        .end = CalcLength(0.0),
    };
    menuWrapperPattern->menuParam_.layoutRegionMargin = margin;

    auto menuNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(menuGeometryNode, nullptr);
    menuGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));

    auto previewNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(1));
    auto previewGeometryNode = previewNode->GetGeometryNode();
    ASSERT_NE(previewGeometryNode, nullptr);
    previewGeometryNode->SetFrameSize(SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT));

    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);

    SizeF windowSizeF = SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    Rect windowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
    menuAlgorithm->wrapperRect_ = windowRect;
    menuAlgorithm->param_.windowGlobalSizeF = windowSizeF;
    menuAlgorithm->wrapperSize_ = windowSizeF;
    menuAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    menuAlgorithm->targetOffset_ = OffsetF(OFFSET_FIRST, OFFSET_FIRST);
    menuAlgorithm->param_.previewMenuGap = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->targetSecurity_ = TARGET_SECURITY.ConvertToPx();
    menuAlgorithm->previewScale_ = 1.0f;

    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuAlgorithm->InitializeLayoutRegionMargin(menuPattern);
    MarginPropertyF marginProperty = { OFFSET_SECOND, 0.0f, OFFSET_SECOND, 0.0f };
    EXPECT_EQ(menuAlgorithm->layoutRegionMargin_, marginProperty);

    menuAlgorithm->param_.menuWindowRect = Rect(0.0f, 0.0f, FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

    auto layoutProperty = AceType::DynamicCast<MenuLayoutProperty>(menuNode->GetLayoutProperty());
    menuAlgorithm->placement_ = Placement::TOP_LEFT;
    layoutProperty->UpdateMenuPlacement(Placement::TOP_LEFT);
    menuAlgorithm->Layout(AceType::RawPtr(menuNode));

    auto previewOffset = OffsetF(OFFSET_SECOND, OFFSET_SECOND + TARGET_SIZE_HEIGHT + TARGET_SECURITY.ConvertToPx());
    EXPECT_EQ(previewGeometryNode->GetFrameOffset(), previewOffset);
    EXPECT_EQ(menuGeometryNode->GetFrameOffset(), OffsetF(OFFSET_SECOND, OFFSET_SECOND));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg053
 * @tc.desc: Verify CheckHorizontalLayoutPreviewOffsetX
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg053, TestSize.Level1)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    auto previewGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    float ret = layoutAlgorithm->CheckHorizontalLayoutPreviewOffsetX(previewGeometryNode, menuGeometryNode, 0.0f);
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg054
 * @tc.desc: Verify UpdatePropArrowOffset
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg054, TestSize.Level1)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->placement_ = Placement::NONE;
    layoutAlgorithm->UpdatePropArrowOffset();
    EXPECT_EQ(layoutAlgorithm->propArrowOffset_.value_, 0.0);
}

/**
 * @tc.name: ModifyTargetOffset001
 * @tc.desc: Verify ModifyTargetOffset.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, ModifyTargetOffset001, TestSize.Level1)
{
    std::optional<OffsetF> parentPosition = std::make_optional(OffsetF(OFFSET_FIRST_NEW, OFFSET_SECOND));
    MenuLayoutAlgorithm menuLayoutAlgorithm(NODE_ID, MENU_TAG, parentPosition);
    menuLayoutAlgorithm.canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = true;
    menuLayoutAlgorithm.isTargetNodeInSubwindow_ = false;
    menuLayoutAlgorithm.targetOffset_ = { TARGET_OFFSET_FIRST, TARGET_OFFSET_SECOND };
    menuLayoutAlgorithm.displayWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD_NEW, RECT_FORTH_NEW);
    ;
    menuLayoutAlgorithm.isUIExtensionSubWindow_ = false;
    menuLayoutAlgorithm.ModifyTargetOffset();
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TWENTY);
}

/**
 * @tc.name: ModifyTargetOffset002
 * @tc.desc: Verify ModifyTargetOffset.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, ModifyTargetOffset002, TestSize.Level1)
{
    std::optional<OffsetF> parentPosition = std::make_optional(OffsetF(OFFSET_FIRST_NEW, OFFSET_SECOND));
    MenuLayoutAlgorithm menuLayoutAlgorithm(NODE_ID, MENU_TAG, parentPosition);
    menuLayoutAlgorithm.canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = false;
    menuLayoutAlgorithm.isTargetNodeInSubwindow_ = false;
    menuLayoutAlgorithm.isUIExtensionSubWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = false;
    menuLayoutAlgorithm.targetOffset_ = { TARGET_OFFSET_FIRST, TARGET_OFFSET_SECOND };
    menuLayoutAlgorithm.displayWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD_NEW, RECT_FORTH_NEW);
    menuLayoutAlgorithm.UIExtensionHostWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD, RECT_FORTH);
    menuLayoutAlgorithm.ModifyTargetOffset();
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TARGET_OFFSET_FIRST);
}

/**
 * @tc.name: ModifyTargetOffset003
 * @tc.desc: Verify ModifyTargetOffset.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, ModifyTargetOffset003, TestSize.Level1)
{
    std::optional<OffsetF> parentPosition = std::make_optional(OffsetF(OFFSET_FIRST_NEW, OFFSET_SECOND));
    MenuLayoutAlgorithm menuLayoutAlgorithm(NODE_ID, MENU_TAG, parentPosition);
    menuLayoutAlgorithm.canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = true;
    menuLayoutAlgorithm.isTargetNodeInSubwindow_ = true;
    menuLayoutAlgorithm.isUIExtensionSubWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = false;
    menuLayoutAlgorithm.targetOffset_ = { TARGET_OFFSET_FIRST, TARGET_OFFSET_SECOND };
    menuLayoutAlgorithm.displayWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD_NEW, RECT_FORTH_NEW);
    menuLayoutAlgorithm.UIExtensionHostWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD, RECT_FORTH);
    menuLayoutAlgorithm.ModifyTargetOffset();
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TARGET_OFFSET_FIRST);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg055
 * @tc.desc: Verify ProcessArrowParams
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg055, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper *layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->placement_ = Placement::NONE;
    SizeF menuSize;
    layoutAlgorithm->ProcessArrowParams(layoutWrapper, menuSize);
    EXPECT_EQ(layoutAlgorithm->arrowInMenu_, false);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg056
 * @tc.desc: Verify UpdatePropArrowOffset
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg056, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper *layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->arrowPlacement_ = Placement::NONE;
    SizeF menuSize;
    layoutAlgorithm->UpdateArrowOffsetWithMenuLimit(menuSize, layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->arrowMinLimit_, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg057
 * @tc.desc: Verify ComputeMenuPositionByAlignType
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg057, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    SizeF menuSize;
    RefPtr<MenuLayoutProperty> menuProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    menuProp->layoutDirection_ = TextDirection::RTL;
    layoutAlgorithm->ComputeMenuPositionByAlignType(menuProp, menuSize);
    EXPECT_EQ(layoutAlgorithm->position_.x_, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg058
 * @tc.desc: Verify PlacementRTL
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg058, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper *layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    layoutWrapper->GetLayoutProperty()->layoutDirection_ = TextDirection::RTL;
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto placement_ = Placement::LEFT;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::RIGHT));
    placement_ = Placement::RIGHT;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::LEFT));
    placement_ = Placement::TOP_LEFT;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::TOP_RIGHT));
    placement_ = Placement::TOP_RIGHT;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::TOP_LEFT));
    placement_ = Placement::BOTTOM_LEFT;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::BOTTOM_RIGHT));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg059
 * @tc.desc: Verify PlacementRTL
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg059, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper *layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    layoutWrapper->GetLayoutProperty()->layoutDirection_ = TextDirection::RTL;
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto placement_ = Placement::NONE;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    placement_ = Placement::BOTTOM_RIGHT;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::BOTTOM_LEFT));
    placement_ = Placement::LEFT_TOP;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::RIGHT_TOP));
    placement_ = Placement::RIGHT_TOP;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::LEFT_TOP));
    placement_ = Placement::LEFT_BOTTOM;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::RIGHT_BOTTOM));
    placement_ = Placement::RIGHT_BOTTOM;
    layoutAlgorithm->PlacementRTL(layoutWrapper, placement_);
    EXPECT_EQ(static_cast<int>(placement_), static_cast<int>(Placement::LEFT_BOTTOM));
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg060
 * @tc.desc: Verify LimitContainerModalMenuRect
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg060, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    double rectWidth = 10.0f;
    double rectHeight = 15.0f;
    layoutAlgorithm->LimitContainerModalMenuRect(rectWidth, rectHeight, menuPattern);
    EXPECT_EQ(rectWidth, 10);
    EXPECT_EQ(rectHeight, 15);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg061
 * @tc.desc: Verify GetMenuMaxBottom
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg061, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    float bottom = layoutAlgorithm->GetMenuMaxBottom(menuPattern);
    EXPECT_EQ(bottom, 0.0);
    menuPattern->previewMode_ = MenuPreviewMode::IMAGE;
    bottom = layoutAlgorithm->GetMenuMaxBottom(menuPattern);
    EXPECT_EQ(bottom, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg062
 * @tc.desc: Verify GetArrowPositionWithPlacement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg062, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper *layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    SizeF menuSize;
    OffsetF childPosition = layoutAlgorithm->GetArrowPositionWithPlacement(menuSize, layoutWrapper);
    EXPECT_EQ(childPosition.x_, 0.0);
    EXPECT_EQ(childPosition.y_, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg063
 * @tc.desc: Verify AdjustPosition
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg063, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    OffsetF position;
    layoutAlgorithm->placement_ = Placement::NONE;
    OffsetF ret = layoutAlgorithm->AdjustPosition(position, WIDTH, HEIGHT, SPACE);
    EXPECT_EQ(ret.x_, 0.0);
    EXPECT_EQ(ret.y_, 0.0);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg064
 * @tc.desc: Verify CheckPlacement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg064, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    SizeF childSize;
    EXPECT_FALSE(layoutAlgorithm->CheckPlacement(childSize));
}

/**
 * @tc.name: UpdateConstraintHeight001
 * @tc.desc: Verify UpdateConstraintHeight
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, UpdateConstraintHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "menu", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);

    auto container = Container::Current();
    frameNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->lastPosition_ = std::make_optional(OffsetF(OFFSET_FIRST_NEW, OFFSET_SECOND));
    layoutAlgorithm->holdEmbeddedMenuPosition_ = true;
    layoutAlgorithm->UpdateConstraintHeight(layoutWrapper, layoutConstraintF);
    EXPECT_EQ(layoutConstraintF.maxSize.height_, MAX_SIZE_HEIGHT);
}

/**
 * @tc.name: UpdateConstraintHeight002
 * @tc.desc: Verify UpdateConstraintHeight
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, UpdateConstraintHeight002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "menu", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);

    auto container = Container::Current();
    frameNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);

    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->lastPosition_ = std::make_optional(OffsetF(OFFSET_FIRST_NEW, OFFSET_SECOND));
    layoutAlgorithm->holdEmbeddedMenuPosition_ = false;
    layoutAlgorithm->UpdateConstraintHeight(layoutWrapper, layoutConstraintF);
    EXPECT_EQ(layoutConstraintF.maxSize.height_, ZERO);
}

/**
 * @tc.name: HorizontalLayout001
 * @tc.desc: Verify HorizontalLayout
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, HorizontalLayout001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    SizeF size(TEN, TEN);
    float position = TEN;
    bool isSelectMenu = false;
    layoutAlgorithm->leftSpace_ = FIVE;
    EXPECT_EQ(layoutAlgorithm->HorizontalLayout(size, position, isSelectMenu), ZERO);
}

/**
 * @tc.name: GetPositionWithPlacement001
 * @tc.desc: Verify GetPositionWithPlacement
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, GetPositionWithPlacement001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    SizeF childSize(TEN, TEN);
    OffsetF topPosition(FIVE, FIVE);
    OffsetF bottomPosition(FIVE, FIVE);
    layoutAlgorithm->placementFuncMap_ = {
        { Placement::LEFT, &MenuLayoutAlgorithm::GetPositionWithPlacementLeft },
        { Placement::RIGHT, &MenuLayoutAlgorithm::GetPositionWithPlacementRight },
        { Placement::TOP, &MenuLayoutAlgorithm::GetPositionWithPlacementTop },
        { Placement::BOTTOM, &MenuLayoutAlgorithm::GetPositionWithPlacementBottom },
    };
    layoutAlgorithm->placement_ = Placement::LEFT;
    EXPECT_EQ(layoutAlgorithm->GetPositionWithPlacement(childSize, topPosition, bottomPosition).x_, OFFSET_X);
}

/**
 * @tc.name: SkipUpdateTargetNodeSize001
 * @tc.desc: Verify SkipUpdateTargetNodeSize
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, SkipUpdateTargetNodeSize001, TestSize.Level1)
{
    std::vector<SelectParam> selectParams;
    selectParams.push_back({ "MenuItem1", "Icon1" });
    auto menuWrapperNode = MenuView::Create(std::move(selectParams), 1, "");
    ASSERT_NE(menuWrapperNode, nullptr);
    EXPECT_EQ(menuWrapperNode->GetChildren().size(), 1);
    auto frameNode = AceType::DynamicCast<FrameNode>(menuWrapperNode->GetChildAtIndex(0));
    ASSERT_NE(frameNode, nullptr);
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MULTI_MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(frameNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->menuStatus_ = MenuStatus::INIT;
    RefPtr<FrameNode> targetNode;
    menuPattern->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    EXPECT_TRUE(layoutAlgorithm->SkipUpdateTargetNodeSize(targetNode, menuPattern));
}

/**
 * @tc.name: SelectLayoutAvoidAlgorithm001
 * @tc.desc: Verify SelectLayoutAvoidAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, SelectLayoutAvoidAlgorithm001, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    frameNode->SetLayoutProperty(prop);

    auto container = Container::Current();
    frameNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);

    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF size(TWENTY, TWENTY);
    bool didNeedArrow = true;
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    auto select = layoutAlgorithm->SelectLayoutAvoidAlgorithm(prop, menuPattern, size, didNeedArrow, layoutWrapper);
    EXPECT_EQ(select.x_, OFFSET_X_NEW);
}

/**
 * @tc.name: SelectLayoutAvoidAlgorithm002
 * @tc.desc: Verify SelectLayoutAvoidAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, SelectLayoutAvoidAlgorithm002, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    frameNode->SetLayoutProperty(prop);

    auto container = Container::Current();
    frameNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);

    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF size(TWENTY, TWENTY);
    bool didNeedArrow = true;
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->targetSize_ = SizeF(OFFSET_X, TARGET_SIZE_HEIGHT);
    layoutAlgorithm->SelectLayoutAvoidAlgorithm(prop, menuPattern, size, didNeedArrow, layoutWrapper);
    auto select = layoutAlgorithm->SelectLayoutAvoidAlgorithm(prop, menuPattern, size, didNeedArrow, layoutWrapper);
    EXPECT_EQ(select.x_, OFFSET_X_NEW);
}

/**
 * @tc.name: SelectLayoutAvoidAlgorithm003
 * @tc.desc: Verify SelectLayoutAvoidAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, SelectLayoutAvoidAlgorithm003, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    frameNode->SetLayoutProperty(prop);

    auto container = Container::Current();
    frameNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);

    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF size(TWENTY, TWENTY);
    bool didNeedArrow = true;
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->targetSize_ = SizeF(OFFSET_X, OFFSET_X);
    layoutAlgorithm->SelectLayoutAvoidAlgorithm(prop, menuPattern, size, didNeedArrow, layoutWrapper);
    auto select = layoutAlgorithm->SelectLayoutAvoidAlgorithm(prop, menuPattern, size, didNeedArrow, layoutWrapper);
    EXPECT_EQ(select.x_, OFFSET_X_NEW);
}

/**
 * @tc.name: SelectLayoutAvoidAlgorithm004
 * @tc.desc: Verify SelectLayoutAvoidAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, SelectLayoutAvoidAlgorithm004, TestSize.Level1)
{
    auto prop = AceType::MakeRefPtr<MenuLayoutProperty>();
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(1, "", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(wrapperNode);
    frameNode->SetLayoutProperty(prop);
    auto menuPattern = frameNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    SizeF size(TWENTY, TWENTY);
    bool didNeedArrow = true;
    LayoutWrapper* layoutWrapper = nullptr;
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->targetSize_ = SizeF(TARGET_SIZE_WIDTH, TARGET_SIZE_HEIGHT);
    auto select = layoutAlgorithm->SelectLayoutAvoidAlgorithm(prop, menuPattern, size, didNeedArrow, layoutWrapper);
    EXPECT_EQ(select.x_, ZERO);
}

/**
 * @tc.name: Initialize002
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Initialize002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    InitMenuWrapperNode();
    ASSERT_EQ(wrapperNode_->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
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
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    layoutAlgorithm->isExpandDisplay_ = true;
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: Initialize003
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Initialize003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    InitMenuWrapperNode();
    ASSERT_EQ(wrapperNode_->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
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
    auto menuNodeNew = layoutWrapper.GetHostNode();
    ASSERT_NE(menuNodeNew, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->isSelectMenu_ = true;
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    layoutAlgorithm->isExpandDisplay_ = true;
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: Initialize004
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Initialize004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    InitMenuWrapperNode();
    ASSERT_EQ(wrapperNode_->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
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
    auto menuNodeNew = layoutWrapper.GetHostNode();
    ASSERT_NE(menuNodeNew, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->type_ = MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU;
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    layoutAlgorithm->isExpandDisplay_ = true;
    layoutAlgorithm->Initialize(&layoutWrapper);
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->position_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->positionOffset_, OffsetF());
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: InitializeLayoutRegionMargin001
 * @tc.desc: Verify InitializeLayoutRegionMargin.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitializeLayoutRegionMargin001, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    auto menuParam = menuWrapperPattern->GetMenuParam();
    menuParam.layoutRegionMargin =
        NG::MarginProperty { .left = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .right = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .top = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .bottom = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)) };
    menuWrapperPattern->SetMenuParam(menuParam);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->InitializeLayoutRegionMargin(menuPattern);
    EXPECT_EQ(layoutAlgorithm->paddingStart_, ZERO);
}

/**
 * @tc.name: InitializeLayoutRegionMargin002
 * @tc.desc: Verify InitializeLayoutRegionMargin.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitializeLayoutRegionMargin002, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    auto menuParam = menuWrapperPattern->GetMenuParam();
    menuParam.layoutRegionMargin =
        NG::MarginProperty { .left = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .right = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .top = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .bottom = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)) };
    menuWrapperPattern->SetMenuParam(menuParam);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->wrapperSize_.width_ = FIVE;
    layoutAlgorithm->wrapperSize_.height_ = FIFTY;
    layoutAlgorithm->InitializeLayoutRegionMargin(menuPattern);
    EXPECT_EQ(layoutAlgorithm->param_.topSecurity, TEN);
}

/**
 * @tc.name: InitializeLayoutRegionMargin003
 * @tc.desc: Verify InitializeLayoutRegionMargin.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitializeLayoutRegionMargin003, TestSize.Level1)
{
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(wrapperNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto menuWrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    auto menuParam = menuWrapperPattern->GetMenuParam();
    menuParam.layoutRegionMargin =
        NG::MarginProperty { .start = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .end = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .left = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)),
            .right = std::make_optional<CalcLength>(Dimension(10, DimensionUnit::VP)) };
    menuWrapperPattern->SetMenuParam(menuParam);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->wrapperSize_.width_ = FIFTY;
    layoutAlgorithm->wrapperSize_.height_ = FIFTY;
    layoutAlgorithm->InitializeLayoutRegionMargin(menuPattern);
    EXPECT_EQ(layoutAlgorithm->layoutRegionMargin_.left, TEN);
}

/**
 * @tc.name: InitWrapperRect002
 * @tc.desc: Verify InitWrapperRect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitWrapperRect002, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "targetTag", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    layoutAlgorithm->isExpandDisplay_ = true;
    layoutAlgorithm->isTargetNodeInSubwindow_ = false;
    layoutAlgorithm->param_.menuWindowRect = Rect(ZERO, ZERO, WIDTH, HEIGHT);
    layoutAlgorithm->InitWrapperRect(property, menuPattern);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.width_, TEN);
}

/**
 * @tc.name: InitWrapperRect003
 * @tc.desc: Verify InitWrapperRect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitWrapperRect003, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "targetTag", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    auto container = Container::Current();
    menuNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
    menuPattern->AttachToFrameNode(menuNode);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    layoutAlgorithm->isExpandDisplay_ = true;
    layoutAlgorithm->isTargetNodeInSubwindow_ = true;
    layoutAlgorithm->param_.menuWindowRect = Rect(ZERO, ZERO, WIDTH, HEIGHT);
    layoutAlgorithm->InitWrapperRect(property, menuPattern);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.width_, TEN);
}

/**
 * @tc.name: GetBottomBySafeAreaManager001
 * @tc.desc: Verify GetBottomBySafeAreaManager.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, GetBottomBySafeAreaManager001, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "targetTag", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto bottom = layoutAlgorithm->GetBottomBySafeAreaManager(safeAreamanager, property, menuPattern);
    EXPECT_EQ(bottom, ZERO);
}

/**
 * @tc.name: InitSpace002
 * @tc.desc: Verify InitSpace.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitSpace002, TestSize.Level1)
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
    props->UpdateMenuPlacement(Placement::BOTTOM_RIGHT);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->targetOffset_ = OffsetF(ZERO, FIFTY);
    layoutAlgorithm->wrapperRect_ = Rect(TWENTY, TWENTY, TWENTY, TWENTY);
    layoutAlgorithm->targetSecurity_ = ZERO;
    layoutAlgorithm->paddingStart_ = TWENTY;
    layoutAlgorithm->targetSize_.width_ = ZERO;
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->InitSpace(props, menuPattern);
    EXPECT_EQ(layoutAlgorithm->leftSpace_, ZERO);
}

/**
 * @tc.name: InitSpace003
 * @tc.desc: Verify InitSpace.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, InitSpace003, TestSize.Level1)
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
    props->UpdateMenuPlacement(Placement::BOTTOM_RIGHT);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->targetOffset_ = OffsetF(ZERO, TWENTY);
    layoutAlgorithm->wrapperRect_ = Rect(ONE_HUNDRED, ONE_HUNDRED, ONE_HUNDRED, ONE_HUNDRED);
    layoutAlgorithm->targetSize_.height_ = ZERO;
    layoutAlgorithm->targetSecurity_ = ZERO;
    layoutAlgorithm->paddingTop_ = ZERO;
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->InitSpace(props, menuPattern);
    EXPECT_EQ(layoutAlgorithm->leftSpace_, ONE_HUNDRED);
}

/**
 * @tc.name: Measure002
 * @tc.desc: Verify Measure.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Measure002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    InitMenuWrapperNode();
    ASSERT_EQ(wrapperNode_->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
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
    auto menuNodeNew = layoutWrapper.GetHostNode();
    ASSERT_NE(menuNodeNew, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto pipelineContext = menuNodeNew->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->isHalfFoldHoverStatus_ = true;
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_.width_, ZERO);
}

/**
 * @tc.name: Measure003
 * @tc.desc: Verify Measure.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, Measure003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    InitMenuWrapperNode();
    ASSERT_EQ(wrapperNode_->GetChildren().size(), 1);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
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
    auto menuNodeNew = layoutWrapper.GetHostNode();
    ASSERT_NE(menuNodeNew, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto pipelineContext = menuNodeNew->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto menuPatternNew = menuNodeNew->GetPattern<MenuPattern>();
    ASSERT_NE(menuPatternNew, nullptr);
    auto menuWrapper = menuPatternNew->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->enableFold_ = true;
    pipelineContext->isHalfFoldHoverStatus_ = true;
    layoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_.width_, ZERO);
}

/**
 * @tc.name: CalculateIdealSize001
 * @tc.desc: Verify CalculateIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, CalculateIdealSize001, TestSize.Level1)
{
    InitMenuWrapperNode();
    auto menuRootNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, MENU_TAG, MenuType::MENU); });
    ASSERT_NE(menuRootNode, nullptr);
    auto menuItemFrameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode, nullptr);
    menuRootNode->AddChild(menuItemFrameNode);
    auto menuItemPattern = menuItemFrameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    RefPtr<FrameNode> childNodeOne = FrameNode::CreateFrameNode("RenderNode", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> childNodeTwo = FrameNode::CreateFrameNode("ChildNode", 0, AceType::MakeRefPtr<Pattern>());
    auto childLayoutWrapperOne = childNodeOne->CreateLayoutWrapper();
    auto childLayoutWrapperTwo = childNodeTwo->CreateLayoutWrapper();
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper.cachedList_.push_back(childLayoutWrapperOne);
    layoutWrapper.cachedList_.push_back(childLayoutWrapperTwo);
    auto pattern = layoutWrapper.GetHostNode()->GetPattern<MenuPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->builderNode_ = AceType::WeakClaim(AceType::RawPtr(childNodeOne));
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    PaddingPropertyF padding { TEN, TEN, TEN, TEN };
    SizeF idealSize(FIVE, FIVE);
    layoutAlgorithm->CalculateIdealSize(&layoutWrapper, layoutConstraintF, padding, idealSize, menuItemFrameNode);
    EXPECT_EQ(layoutWrapper.GetAllChildrenWithBuild(true).size(), 2);
}

/**
 * @tc.name: CalculateIdealSize002
 * @tc.desc: Verify CalculateIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, CalculateIdealSize002, TestSize.Level1)
{
    InitMenuWrapperNode();
    auto menuRootNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, MENU_TAG, MenuType::MENU); });
    ASSERT_NE(menuRootNode, nullptr);
    auto menuItemFrameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    ASSERT_NE(menuItemFrameNode, nullptr);
    menuRootNode->AddChild(menuItemFrameNode);
    auto menuItemPattern = menuItemFrameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode_->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, menuNode->GetLayoutProperty());
    layoutWrapper.GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    RefPtr<FrameNode> childNodeOne = FrameNode::CreateFrameNode("RenderNode", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> childNodeTwo = FrameNode::CreateFrameNode("ChildNode", 1, AceType::MakeRefPtr<Pattern>());
    auto childLayoutWrapperOne = childNodeOne->CreateLayoutWrapper();
    auto childLayoutWrapperTwo = childNodeTwo->CreateLayoutWrapper();
    layoutWrapper.cachedList_ = std::list<RefPtr<LayoutWrapper>>();
    layoutWrapper.cachedList_.push_back(childLayoutWrapperOne);
    layoutWrapper.cachedList_.push_back(childLayoutWrapperTwo);
    auto pattern = layoutWrapper.GetHostNode()->GetPattern<MenuPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->builderNode_ = AceType::WeakClaim(AceType::RawPtr(childNodeOne));
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE, ONE },
        .maxSize = { TEN, TEN },
        .percentReference = { FIVE, FIVE },
        .parentIdealSize = { TWO, TWO },
    };
    PaddingPropertyF padding { TEN, TEN, TEN, TEN };
    SizeF idealSize(FIVE, FIVE);
    layoutAlgorithm->CalculateIdealSize(&layoutWrapper, layoutConstraintF, padding, idealSize, menuItemFrameNode);
    EXPECT_EQ(layoutWrapper.GetAllChildrenWithBuild(true).size(), 2);
}

/**
 * @tc.name: LayoutOtherDeviceLeftPreviewRightMenu001
 * @tc.desc: Verify LayoutOtherDeviceLeftPreviewRightMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, LayoutOtherDeviceLeftPreviewRightMenu001, TestSize.Level1)
{
    RefPtr<GeometryNode> previewGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    SizeF totalSize(ONE, ONE);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->targetSecurity_ = ZERO;
    layoutAlgorithm->wrapperRect_.width_ = TWENTY;
    layoutAlgorithm->paddingStart_ = ZERO;
    layoutAlgorithm->paddingEnd_ = ZERO;
    layoutAlgorithm->param_.windowGlobalSizeF.height_ = FIVE;
    layoutAlgorithm->LayoutOtherDeviceLeftPreviewRightMenu(previewGeometryNode, menuGeometryNode, totalSize, TWENTY);
    EXPECT_EQ(previewGeometryNode->frame_.rect_.width_, ZERO);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg065
 * @tc.desc: Verify GetMenuWindowRectInfo.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg065, TestSize.Level1)
{
    MenuLayoutAlgorithm menuLayoutAlgorithm;
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    menuLayoutAlgorithm.canExpandCurrentWindow_ = false;
    menuLayoutAlgorithm.isExpandDisplay_ = false;
    menuLayoutAlgorithm.isUIExtensionSubWindow_ = true;
    menuLayoutAlgorithm.targetOffset_ = { TARGET_OFFSET_FIRST, TARGET_OFFSET_SECOND };
    menuLayoutAlgorithm.displayWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD_NEW, RECT_FORTH_NEW);
    menuLayoutAlgorithm.UIExtensionHostWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD, RECT_FORTH);
    menuLayoutAlgorithm.ModifyTargetOffset();
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    menuPattern->AttachToFrameNode(menuNode);
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TEN);
    EXPECT_EQ(menuLayoutAlgorithm.GetMenuWindowRectInfo(menuPattern).width_, TEN);

    menuLayoutAlgorithm.canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = true;
    menuLayoutAlgorithm.isTargetNodeInSubwindow_ = false;
    menuLayoutAlgorithm.ModifyTargetOffset();
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TEN);
}

/**
 * @tc.name: MenuLayoutAlgorithmTestNg065
 * @tc.desc: Verify CheckChildConstraintCondition.
 * @tc.type: FUNC
 */

HWTEST_F(MenuLayout3TestNg, MenuLayoutAlgorithmTestNg066, TestSize.Level1)
{
    MenuLayoutAlgorithm menuLayoutAlgorithm;
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    EXPECT_TRUE(menuLayoutAlgorithm.CheckChildConstraintCondition(menuPattern));
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    EXPECT_TRUE(menuLayoutAlgorithm.CheckChildConstraintCondition(menuPattern));
    menuPattern->type_ = MenuType::MULTI_MENU;
    EXPECT_FALSE(menuLayoutAlgorithm.CheckChildConstraintCondition(menuPattern));
    menuPattern->type_ = MenuType::SUB_MENU;
    menuPattern->parentMenuItem_ = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::SIDE;
    menuPattern->parentMenuItem_->pattern_ = menuItemPattern;
    EXPECT_TRUE(menuLayoutAlgorithm.CheckChildConstraintCondition(menuPattern));
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    EXPECT_FALSE(menuLayoutAlgorithm.CheckChildConstraintCondition(menuPattern));
}

/**
 * @tc.name: isContainerModal001
 * @tc.desc: Verify isContainerModal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, isContainerModal001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto menuRootNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, MENU_TAG, MenuType::MENU); });
    ASSERT_NE(menuRootNode, nullptr);
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    EXPECT_FALSE(layoutAlgorithm->isContainerModal(menuRootNode));
}
 
/**
 * @tc.name: GetContainerModalOffsetY001
 * @tc.desc: Verify GetContainerModalOffsetY.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, GetContainerModalOffsetY001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto menuRootNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, MENU_TAG, MenuType::MENU); });
    ASSERT_NE(menuRootNode, nullptr);
    EXPECT_TRUE(NearZero(layoutAlgorithm->GetContainerModalOffsetY(menuRootNode)));
}
 
/**
 * @tc.name: CalcSubMenuMaxHeightNoPreview001
 * @tc.desc: Verify CalcSubMenuMaxHeightNoPreview.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, CalcSubMenuMaxHeightNoPreview001, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu(MenuType::MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
 
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    
    MountMenuItemToParent(menuNode, DEFAULT_CHILD_COUNT);
    auto menuItem = AceType::DynamicCast<FrameNode>(menuNode->GetLastChild());
    ASSERT_NE(menuItem, nullptr);
 
    menuPattern->UpdateLastPlacement(Placement::BOTTOM_RIGHT);
    menuAlgorithm->CalcSubMenuMaxHeightNoPreview(menuItem, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::BOTTOM_RIGHT);
 
    auto parentItemGeometryNode = menuItem->GetGeometryNode();
    ASSERT_NE(parentItemGeometryNode, nullptr);
    parentItemGeometryNode->SetFrameSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    menuAlgorithm->CalcSubMenuMaxHeightNoPreview(menuItem, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::BOTTOM_RIGHT);
 
    menuPattern->UpdateLastPlacement(Placement::TOP_RIGHT);
    menuAlgorithm->CalcSubMenuMaxHeightNoPreview(menuItem, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::TOP_RIGHT);
}
 
/**
 * @tc.name: CalcSubMenuMaxHeightWithPreview001
 * @tc.desc: Verify CalcSubMenuMaxHeightWithPreview.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, CalcSubMenuMaxHeightWithPreview001, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu(MenuType::MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
 
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    
    MountMenuItemToParent(menuNode, DEFAULT_CHILD_COUNT);
    auto menuItem = AceType::DynamicCast<FrameNode>(menuNode->GetLastChild());
    ASSERT_NE(menuItem, nullptr);
 
    menuPattern->UpdateLastPlacement(Placement::BOTTOM_RIGHT);
    menuAlgorithm->CalcSubMenuMaxHeightWithPreview(menuNode, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::BOTTOM_RIGHT);
 
    menuPattern->UpdateLastPlacement(Placement::TOP_RIGHT);
    menuAlgorithm->CalcSubMenuMaxHeightWithPreview(menuNode, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::TOP_RIGHT);
 
    menuPattern->UpdateLastPlacement(Placement::RIGHT);
    menuAlgorithm->CalcSubMenuMaxHeightWithPreview(menuNode, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::RIGHT);
 
    menuPattern->UpdateLastPlacement(Placement::RIGHT);
    menuAlgorithm->canExpandCurrentWindow_ = false;
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->SetWindowModal(WindowModal::CONTAINER_MODAL);
    menuAlgorithm->CalcSubMenuMaxHeightWithPreview(menuNode, parentLayoutConstraint, 0.0f, 0.0f, 0.0f);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::RIGHT);
}
 
/**
 * @tc.name: CalcSubMenuMaxHeightConstraint001
 * @tc.desc: Verify CalcSubMenuMaxHeightConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TestNg, CalcSubMenuMaxHeightConstraint001, TestSize.Level1)
{
    auto menuNode = GetOrCreateMenu(MenuType::MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
 
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    auto menuAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(menuAlgorithm, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    props->UpdateLayoutConstraint(parentLayoutConstraint);
    props->UpdateContentConstraint();
    
    MountMenuItemToParent(menuNode, DEFAULT_CHILD_COUNT);
    auto menuItem = AceType::DynamicCast<FrameNode>(menuNode->GetLastChild());
    ASSERT_NE(menuItem, nullptr);
 
    menuPattern->UpdateLastPlacement(Placement::BOTTOM_RIGHT);
    menuPattern->SetPreviewMode(MenuPreviewMode::IMAGE);
    menuAlgorithm->CalcSubMenuMaxHeightConstraint(parentLayoutConstraint, menuItem);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::BOTTOM_RIGHT);
 
    menuAlgorithm->canExpandCurrentWindow_ = false;
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->SetWindowModal(WindowModal::CONTAINER_MODAL);
    menuPattern->UpdateLastPlacement(Placement::RIGHT);
    menuAlgorithm->CalcSubMenuMaxHeightConstraint(parentLayoutConstraint, menuItem);
    EXPECT_EQ(menuPattern->GetLastPlacement(), Placement::RIGHT);
}
} // namespace OHOS::Ace::NG
