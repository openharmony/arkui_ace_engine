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
#include "core/pipeline/pipeline_base.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t GRID_COUNTS = 8;
constexpr uint32_t TV_MIN_GRID_COUNTS = 3;
constexpr int32_t DEFAULT_CHILD_COUNT = 5;
constexpr int32_t TARGET_ID = 3;
constexpr int32_t TARGET = 0;
constexpr int32_t NODE_ID = 1;
constexpr float TV_MAX_WIDTH = 1000.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float TARGET_SIZE_WIDTH = 50.0f;
constexpr float TARGET_SIZE_HEIGHT = 50.0f;
constexpr float MENU_SIZE_WIDTH = 150.0f;
constexpr float MENU_SIZE_HEIGHT = 150.0f;
constexpr float WIDTH = 10.0f;
constexpr float HEIGHT = 20.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
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
constexpr float ONE_HUNDRED = 100.0f;
constexpr float KEY_BOARD_TOP_POSITION = 800.0f;
constexpr float WRAPPER_RECT_HEIGHT_SMALL = 600.0f;
constexpr float WRAPPER_RECT_HEIGHT_LARGE = 1200.0f;
constexpr float WRAPPER_RECT_CENTER = 900.0f;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
} // namespace

class MenuLayout3TwoTestNg : public testing::Test {
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

void MenuLayout3TwoTestNg::SetUpTestCase() {}

void MenuLayout3TwoTestNg::TearDownTestCase() {}

void MenuLayout3TwoTestNg::SetUp()
{
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void MenuLayout3TwoTestNg::TearDown()
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

void MenuLayout3TwoTestNg::MockPipelineContextGetTheme()
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

RefPtr<FrameNode> MenuLayout3TwoTestNg::CreateTargetNodeWithMainTree()
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

RefPtr<FrameNode> MenuLayout3TwoTestNg::CreateMenuWrapperElement(MenuType type)
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

RefPtr<FrameNode> MenuLayout3TwoTestNg::GetOrCreateMenu(MenuType type)
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

RefPtr<MenuLayoutAlgorithm> MenuLayout3TwoTestNg::CreateMenuLayoutAlgorithm(MenuType type)
{
    auto menuNode = GetOrCreateMenu(type);
    CHECK_NULL_RETURN(menuNode, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(menuAlgorithmWrapper, nullptr);
    return AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
}

void MenuLayout3TwoTestNg::MountMenuItemToParent(const RefPtr<FrameNode>& parent, int32_t childCount, bool isNeedGroup)
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

void MenuLayout3TwoTestNg::InitTargetFrameNode()
{
    targetFrameNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(targetFrameNode_, nullptr);
    targetId_ = targetFrameNode_->GetId();
    targetTag_ = targetFrameNode_->GetTag();
}

void MenuLayout3TwoTestNg::InitMenuWrapperNode()
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
 * @tc.name: Initialize004
 * @tc.desc: Verify Initialize.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, Initialize004, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, InitializeLayoutRegionMargin001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, InitializeLayoutRegionMargin002, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, InitializeLayoutRegionMargin003, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, InitWrapperRect002, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "targetTag", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->AttachToFrameNode(menuNode);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->canExpandCurrentWindow_ = true;
    layoutAlgorithm->isExpandDisplay_ = true;
    layoutAlgorithm->param_.menuWindowRect = Rect(ZERO, ZERO, WIDTH, HEIGHT);
    layoutAlgorithm->InitWrapperRect(property, menuPattern);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.width_, TEN);
}

/**
 * @tc.name: InitWrapperRect003
 * @tc.desc: Verify InitWrapperRect.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, InitWrapperRect003, TestSize.Level1)
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
    layoutAlgorithm->param_.menuWindowRect = Rect(ZERO, ZERO, WIDTH, HEIGHT);
    layoutAlgorithm->InitWrapperRect(property, menuPattern);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.width_, TEN);
}

/**
 * @tc.name: GetBottomBySafeAreaManager001
 * @tc.desc: Verify GetBottomBySafeAreaManager.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, GetBottomBySafeAreaManager001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, InitSpace002, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, InitSpace003, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, Measure002, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, Measure003, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, CalculateIdealSize001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, CalculateIdealSize002, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, LayoutOtherDeviceLeftPreviewRightMenu001, TestSize.Level1)
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
 
HWTEST_F(MenuLayout3TwoTestNg, MenuLayoutAlgorithmTestNg065, TestSize.Level1)
{
    MenuLayoutAlgorithm menuLayoutAlgorithm;
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    menuLayoutAlgorithm.canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = false;
    menuLayoutAlgorithm.isUIExtensionSubWindow_ = true;
    menuLayoutAlgorithm.targetOffset_ = { TARGET_OFFSET_FIRST, TARGET_OFFSET_SECOND };
    menuLayoutAlgorithm.displayWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD_NEW, RECT_FORTH_NEW);
    menuLayoutAlgorithm.UIExtensionHostWindowRect_ = RectT(RECT_FIRST, RECT_SECOND, RECT_THIRD, RECT_FORTH);
    menuLayoutAlgorithm.ModifyOffset(menuLayoutAlgorithm.targetOffset_, menuPattern);
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    menuPattern->AttachToFrameNode(menuNode);
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TEN);
    EXPECT_EQ(menuLayoutAlgorithm.GetMenuWindowRectInfo(menuPattern).width_, TEN);
 
    menuLayoutAlgorithm.canExpandCurrentWindow_ = true;
    menuLayoutAlgorithm.isExpandDisplay_ = true;
    menuLayoutAlgorithm.ModifyOffset(menuLayoutAlgorithm.targetOffset_, menuPattern);
    EXPECT_EQ(menuLayoutAlgorithm.targetOffset_.x_, TEN);
}
 
/**
 * @tc.name: MenuLayoutAlgorithmTestNg065
 * @tc.desc: Verify CheckChildConstraintCondition.
 * @tc.type: FUNC
 */
 
HWTEST_F(MenuLayout3TwoTestNg, MenuLayoutAlgorithmTestNg066, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, isContainerModal001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, GetContainerModalOffsetY001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, CalcSubMenuMaxHeightNoPreview001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, CalcSubMenuMaxHeightWithPreview001, TestSize.Level1)
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
HWTEST_F(MenuLayout3TwoTestNg, CalcSubMenuMaxHeightConstraint001, TestSize.Level1)
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
 
/**
 * @tc.name: GetMaxGridCounts001
 * @tc.desc: Verify GetMaxGridCounts.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, GetMaxGridCounts001, TestSize.Level1)
{
    auto menuAlgorithm = CreateMenuLayoutAlgorithm(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);

    auto geometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, props);

    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->isTV_ = true;
    auto childConstraint = props->CreateChildConstraint();

    auto columnInfo = AceType::MakeRefPtr<GridColumnInfo>();
    ASSERT_NE(columnInfo, nullptr);
    auto parent = AceType::MakeRefPtr<GridContainerInfo>();
    parent->columns_ = GRID_COUNTS;
    columnInfo->parent_ = parent;
    childConstraint.maxSize.SetWidth(TV_MAX_WIDTH);
    menuAlgorithm->UpdateConstraintWidth(&layoutWrapper, childConstraint);
    EXPECT_TRUE(selectTheme->IsTV());
}

/**
 * @tc.name: UpdateConstraintBaseOnOptions001
 * @tc.desc: Verify UpdateConstraintBaseOnOptions.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, UpdateConstraintBaseOnOptions001, TestSize.Level1)
{
    auto menuAlgorithm = CreateMenuLayoutAlgorithm(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuAlgorithm, nullptr);
    auto menuNode = GetOrCreateMenu(MenuType::SELECT_OVERLAY_EXTENSION_MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);

    auto geometryNode = menuNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(MENU_SIZE_WIDTH, MENU_SIZE_HEIGHT));
    LayoutWrapperNode layoutWrapper(menuNode, geometryNode, props);

    auto selectTheme = MockPipelineContext::GetCurrent()->GetTheme<SelectTheme>();
    selectTheme->isTV_ = true;
    auto childConstraint = props->CreateChildConstraint();

    menuAlgorithm->optionPadding_ = 0.0f;
    auto columnInfo = AceType::MakeRefPtr<GridColumnInfo>();
    ASSERT_NE(columnInfo, nullptr);
    auto parent = AceType::MakeRefPtr<GridContainerInfo>();
    parent->columns_ = TV_MIN_GRID_COUNTS;
    columnInfo->parent_ = parent;
    childConstraint.maxSize.SetWidth(TV_MAX_WIDTH);
    menuAlgorithm->UpdateConstraintBaseOnOptions(&layoutWrapper, childConstraint);
    EXPECT_TRUE(selectTheme->IsTV());
}

/**
 * @tc.name: MenuKeyboardAvoidMode001
 * @tc.desc: Verify InitializeMenuAvoidKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, MenuKeyboardAvoidMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node
     */
    auto menuNode = GetOrCreateMenu(MenuType::MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    /**
     * @tc.steps: step2. get menu layout algorithm
     */
    auto layoutAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step3. call InitializeMenuAvoidKeyboard
     * @tc.expected: wrapperRect_ not change
     */
    layoutAlgorithm->InitializeMenuAvoidKeyboard(menuNode);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect());
    auto menuWrapper = menuPattern->GetMenuWrapper();
    ASSERT_NE(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    MenuParam menuParam;
    menuParam.keyboardAvoidMode = MenuKeyboardAvoidMode::TRANSLATE_AND_RESIZE;
    menuWrapperPattern->SetMenuParam(menuParam);
    /**
     * @tc.steps: step4. set keyboard avoid mode
     * @tc.expected: wrapperRect_ not change
     */
    layoutAlgorithm->InitializeMenuAvoidKeyboard(menuNode);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect());
}

/**
 * @tc.name: MenuKeyboardAvoidMode002
 * @tc.desc: Verify MenuAvoidKeyboard with normal.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, MenuKeyboardAvoidMode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node
     */
    MockPipelineContextGetTheme();
    auto menuNode = GetOrCreateMenu(MenuType::MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    /**
     * @tc.steps: step2. get menu layout algorithm
     */
    auto layoutAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step3. The test when the top of the soft keyboard is larger than the bottom of the menu layout area
     * @tc.expected: wrapperRect_ not change
     */
    std::optional<Dimension> minKeyboardAvoidDistance = std::nullopt;
    auto wrapperRect = Rect(0.0f, 0.0f, 0.0f, WRAPPER_RECT_HEIGHT_SMALL);
    layoutAlgorithm->wrapperRect_ = wrapperRect;
    layoutAlgorithm->MenuAvoidKeyboard(menuNode, minKeyboardAvoidDistance, KEY_BOARD_TOP_POSITION);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, wrapperRect);
    /**
     * @tc.steps: step4. The test when the top of the soft keyboard is smaller than the top of the menu layout area
     * @tc.expected: wrapperRect_ not change
     */
    wrapperRect = Rect(0.0f, WRAPPER_RECT_CENTER, 0.0f, WRAPPER_RECT_HEIGHT_SMALL);
    layoutAlgorithm->wrapperRect_ = wrapperRect;
    layoutAlgorithm->MenuAvoidKeyboard(menuNode, minKeyboardAvoidDistance, KEY_BOARD_TOP_POSITION);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, wrapperRect);
    /**
     * @tc.steps: step5. The test menu need to be avoided normally
     * @tc.expected: The menu successfully avoids the soft keyboard
     */
    wrapperRect = Rect(0.0f, 0.0f, 0.0f, WRAPPER_RECT_HEIGHT_LARGE);
    layoutAlgorithm->wrapperRect_ = wrapperRect;
    minKeyboardAvoidDistance = Dimension();
    layoutAlgorithm->MenuAvoidKeyboard(menuNode, minKeyboardAvoidDistance, KEY_BOARD_TOP_POSITION);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, Rect(0.0f, 0.0f, 0.0f, KEY_BOARD_TOP_POSITION));
}

/**
 * @tc.name: MenuKeyboardAvoidMode003
 * @tc.desc: Verify MenuAvoidKeyboard with preview.
 * @tc.type: FUNC
 */
HWTEST_F(MenuLayout3TwoTestNg, MenuKeyboardAvoidMode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create menu node
     */
    MockPipelineContextGetTheme();
    auto menuNode = GetOrCreateMenu(MenuType::MENU);
    ASSERT_NE(menuNode, nullptr);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    auto props = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(props, nullptr);
    auto menuAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    ASSERT_NE(menuAlgorithmWrapper, nullptr);
    /**
     * @tc.steps: step2. get menu layout algorithm
     */
    auto layoutAlgorithm = AceType::DynamicCast<MenuLayoutAlgorithm>(menuAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    /**
     * @tc.steps: step3. Set preview mode, make the height after the avoidance is 0
     * @tc.expected: wrapperRect_ not change
     */
    std::optional<Dimension> minKeyboardAvoidDistance = Dimension();
    auto wrapperRect = Rect(0.0f, 0.0f, 0.0f, WRAPPER_RECT_HEIGHT_LARGE);
    layoutAlgorithm->wrapperRect_ = wrapperRect;
    menuPattern->SetPreviewMode(MenuPreviewMode::IMAGE);
    layoutAlgorithm->param_.bottomSecurity = WRAPPER_RECT_HEIGHT_SMALL;
    layoutAlgorithm->MenuAvoidKeyboard(menuNode, minKeyboardAvoidDistance, KEY_BOARD_TOP_POSITION);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, wrapperRect);
    /**
     * @tc.steps: step4. Set preview mode, ,male the height after avoidance is 0, but the theme value can be avoided
     * @tc.expected: wrapperRect_ change to keyboard top position subtract theme min keyboard avoid distance
     */
    layoutAlgorithm->param_.bottomSecurity = 0.0f;
    layoutAlgorithm->param_.topSecurity = WRAPPER_RECT_HEIGHT_SMALL;
    minKeyboardAvoidDistance = Dimension(WRAPPER_RECT_HEIGHT_SMALL);
    layoutAlgorithm->MenuAvoidKeyboard(menuNode, minKeyboardAvoidDistance, KEY_BOARD_TOP_POSITION);
    auto context = menuNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto menuTheme = context->GetTheme<MenuTheme>();
    ASSERT_NE(menuTheme, nullptr);
    auto expectRect =
        Rect(0.0f, 0.0f, 0.0f, KEY_BOARD_TOP_POSITION - menuTheme->GetMinKeyboardAvoidDistance().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, expectRect);
    /**
     * @tc.steps: step5. The test preview menu need to be avoided normally
     * @tc.expected: The menu successfully avoids the soft keyboard
     */
    layoutAlgorithm->param_.topSecurity = 0.0f;
    layoutAlgorithm->MenuAvoidKeyboard(menuNode, minKeyboardAvoidDistance, KEY_BOARD_TOP_POSITION);
    expectRect = Rect(0.0f, 0.0f, 0.0f, KEY_BOARD_TOP_POSITION - WRAPPER_RECT_HEIGHT_SMALL);
    EXPECT_EQ(layoutAlgorithm->wrapperRect_, expectRect);
}
} // namespace OHOS::Ace::NG
