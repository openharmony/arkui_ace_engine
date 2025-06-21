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

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const DirtySwapConfig configDirtySwap = { false, false, false, false, true, false };
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr int32_t NODE_ID = 1;
constexpr int32_t TARGET_ID = 3;
constexpr int32_t TWO_NUMBER = 2;
constexpr int32_t FIVE_NUMBER = 5;
constexpr int32_t TEN_NUMBER = 10;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float ZERO_FLOAT = 0.0f;
constexpr float ONE_FLOAT = 1.0f;
constexpr float TWO_FLOAT = 2.0f;
constexpr float FIVE_FLOAT = 5.0f;
constexpr float TEN_FLOAT = 10.0f;
constexpr float TWENTY_FLOAT = 20.0f;
constexpr float THIRTY_FLOAT = 30.0f;
constexpr float NEGATIVE_EIGHTEEN = -18.0f;
constexpr float NEGATIVE_EIGHT = -8.0f;
constexpr float NEGATIVE_FIVE = -5.0f;
constexpr float NEGATIVE_THIRTY = -30.0f;
constexpr float MENU_ITEM_SIZE_WIDTH = 100.0f;
constexpr float MENU_ITEM_SIZE_HEIGHT = 50.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

} // namespace
class MenuExpandTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    int32_t GetNodeId();
    RefPtr<FrameNode> menuFrameNode_;
    RefPtr<FrameNode> wrapperNode_;
    RefPtr<FrameNode> menuItemFrameNode_;
    RefPtr<FrameNode> subMenuParent_;
    RefPtr<FrameNode> subMenu_;
    RefPtr<MenuItemPattern> menuItemPattern_;
    int32_t nodeId_ = 1;
    bool isSubMenuBuilded_ = false;
};

void MenuExpandTestNg::SetUpTestCase() {
}

void MenuExpandTestNg::TearDownTestCase() {
}

void MenuExpandTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    InitMenuTestNg();
    isSubMenuBuilded_ = false;
}

void MenuExpandTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    menuFrameNode_ = nullptr;
    menuItemFrameNode_ = nullptr;
    subMenuParent_ = nullptr;
    menuItemPattern_ = nullptr;
    wrapperNode_ = nullptr;
    subMenu_ = nullptr;
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
}

int32_t MenuExpandTestNg::GetNodeId()
{
    nodeId_++;
    return nodeId_;
}

void MenuExpandTestNg::InitMenuTestNg()
{
    std::function<void()> buildFun = [this]() {
        MenuModelNG MenuModelInstance;
        MenuModelInstance.Create();
        isSubMenuBuilded_ = true;
    };
    wrapperNode_ =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    menuFrameNode_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    subMenu_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::SUB_MENU));
    menuItemFrameNode_ = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    subMenuParent_ = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    auto itemComponent = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent2 = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent3 = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    itemComponent->MountToParent(subMenuParent_);
    itemComponent2->MountToParent(subMenuParent_);
    itemComponent3->MountToParent(subMenuParent_);
    menuItemFrameNode_->MountToParent(menuFrameNode_);
    subMenuParent_->MountToParent(menuFrameNode_);
    menuFrameNode_->MountToParent(wrapperNode_);
    subMenu_->MountToParent(wrapperNode_);
    menuItemPattern_ = menuItemFrameNode_->GetPattern<MenuItemPattern>();
    ASSERT_NE(menuItemPattern_, nullptr);
    menuItemPattern_->SetSubBuilder(buildFun);
    menuItemPattern_->SetIsSubMenuShowed(false);
    auto pattern2 = subMenuParent_->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern2, nullptr);
    pattern2->SetSubBuilder(buildFun);
    pattern2->SetIsSubMenuShowed(false);
    auto menuPattern = menuFrameNode_->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetShowedSubMenu(subMenu_);
    auto subMenuPattern = subMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->SetParentMenuItem(subMenuParent_);
}

/**
 * @tc.name: MenuExpandTestNg001
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition on SetUp() step.
     * set expandingMode to EMBEDDED;
     * @tc.expected: wrapper and child pattern is not null
     */

    menuItemPattern_->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    EXPECT_EQ(menuItemPattern_->GetExpandingMode(), SubMenuExpandingMode::EMBEDDED);
    /**
     * @tc.steps: step2. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    menuItemPattern_->ShowSubMenu();
    menuItemPattern_->CloseMenu();
    EXPECT_EQ(isSubMenuBuilded_, true);
}

/**
 * @tc.name: MenuExpandTestNg002
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition on SetUp() step.
     * set expandingMode to EMBEDDED;
     * @tc.expected: wrapper and child pattern is not null
     */
    auto pattern = subMenuParent_->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;

    /**
     * @tc.steps: step2. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    pattern->ShowSubMenu();
    EXPECT_EQ(pattern->GetExpandingMode(), SubMenuExpandingMode::EMBEDDED);
    pattern->CloseMenu();
    EXPECT_EQ(isSubMenuBuilded_, true);
}

/**
 * @tc.name: MenuExpandTestNg003
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition on SetUp() step.
     * set expandingMode to EMBEDDED;
     * @tc.expected: wrapper and child pattern is not null
     */
    auto pattern = subMenuParent_->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->expandingMode_ = SubMenuExpandingMode::STACK;

    /**
     * @tc.steps: step2. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    pattern->ShowSubMenu();
    EXPECT_EQ(pattern->GetExpandingMode(), SubMenuExpandingMode::STACK);
    pattern->CloseMenu();
    EXPECT_EQ(isSubMenuBuilded_, true);
}

/**
 * @tc.name: MenuExpandTest004
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition on SetUp() step.
     * set expandingMode to STACK;
     * @tc.expected: wrapper and child pattern is not null
     */

    menuItemPattern_->expandingMode_ = SubMenuExpandingMode::STACK;
    /**
     * @tc.steps: step2. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    menuItemPattern_->ShowSubMenu();
    menuItemPattern_->CloseMenu();
    menuItemPattern_->OnHover(true);
    menuItemPattern_->OnHover(false);
    EXPECT_EQ(isSubMenuBuilded_, true);
}

/**
 * @tc.name: MenuExpandTest005
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create cascade menu condition on SetUp() step.
     * set expandingMode to STACK;
     * @tc.expected: wrapper and child pattern is not null
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto pattern = subMenuParent_->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->expandingMode_ = SubMenuExpandingMode::STACK;
    /**
     * @tc.steps: step2. prepare wrapperNode, menuNode, itemNode
     * @tc.expected: itemPattern is not null
     */
    pattern->ShowSubMenu();
    EXPECT_EQ(pattern->GetExpandingMode(), SubMenuExpandingMode::STACK);
    auto subMenuPattern = subMenu_->GetPattern<MenuPattern>();
    ASSERT_NE(subMenuPattern, nullptr);
    subMenuPattern->isSubMenuShow_ = true;

    /**
     * @tc.steps: step3. call OnModifyDone and OnDirtyLayoutWrapperSwap
     * @tc.expected: isSubMenuShow_ is false
     */
    const RefPtr<LayoutWrapperNode> layoutWrapper;
    subMenuPattern->OnModifyDone();
    subMenuPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, configDirtySwap);
    EXPECT_FALSE(subMenuPattern->isSubMenuShow_);

    /**
     * @tc.steps: step4. call SetSubMenuShow
     * @tc.expected: isSubMenuShow_ is true
     */
    subMenuPattern->SetSubMenuShow(true);
    EXPECT_TRUE(subMenuPattern->isSubMenuShow_);
}

/**
 * @tc.name: MenuExpandTestNg006
 * @tc.desc: Test ParseMenuRadius.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg006, TestSize.Level1)
{
    menuItemPattern_->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    EXPECT_EQ(menuItemPattern_->GetExpandingMode(), SubMenuExpandingMode::EMBEDDED);

    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 1, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto mainMenu = FrameNode::CreateFrameNode(
        V2::SELECT_ETS_TAG, 2, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    mainMenu->MountToParent(wrapperNode);
    auto wrapperPattern = wrapperNode->GetPattern<MenuWrapperPattern>();
    auto menuPattern = mainMenu->GetPattern<MenuPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->hasCustomRadius_ = true;
    MenuParam param;
    menuItemPattern_->ParseMenuRadius(param);
}

/**
 * @tc.name: MenuExpandTestNg007
 * @tc.desc: Test GetSelectAdjustPositions.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg007, TestSize.Level1)
{
    std::vector<Placement> currentPlacementStates = { Placement::LEFT, Placement::RIGHT, Placement::TOP,
        Placement::BOTTOM, Placement::RIGHT_TOP, Placement::RIGHT_TOP };
    SizeF childSize(TEN_FLOAT, TEN_FLOAT);
    OffsetF topPosition = OffsetF(ONE_FLOAT, TWO_FLOAT);
    OffsetF bottomPosition = OffsetF(TWO_FLOAT, TWO_FLOAT);
    MenuLayoutAlgorithm menuLayoutAlgorithm;
    auto ret =
        menuLayoutAlgorithm.GetSelectAdjustPosition(currentPlacementStates, childSize, topPosition, bottomPosition);
    EXPECT_EQ(ret.x_, ZERO_FLOAT);
    EXPECT_EQ(ret.y_, ZERO_FLOAT);
    currentPlacementStates[0] = Placement::NONE;
    ret = menuLayoutAlgorithm.GetSelectAdjustPosition(currentPlacementStates, childSize, topPosition, bottomPosition);
    EXPECT_EQ(ret.x_, ZERO_FLOAT);
    EXPECT_EQ(ret.y_, ZERO_FLOAT);
    currentPlacementStates[0] = Placement::BOTTOM;
    currentPlacementStates[1] = Placement::RIGHT_TOP;
    ret = menuLayoutAlgorithm.GetSelectAdjustPosition(currentPlacementStates, childSize, topPosition, bottomPosition);
    EXPECT_EQ(ret.x_, ZERO_FLOAT);
    EXPECT_EQ(ret.y_, ZERO_FLOAT);
}

/**
 * @tc.name: MenuExpandTestNg008
 * @tc.desc: Test UpdateChildConstraintByDevice.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg008, TestSize.Level1)
{
    RefPtr<FrameNode> outerMenuNode =
        FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU); });
    ASSERT_NE(outerMenuNode, nullptr);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(outerMenuNode);
    auto menuPattern = outerMenuNode->GetPattern<MenuPattern>();
    auto firstMenu = menuPattern->GetFirstInnerMenu();
    auto layoutProperty = firstMenu->GetLayoutProperty<MenuLayoutProperty>();
    MenuLayoutAlgorithm menuLayoutAlgorithm;
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE_FLOAT, ONE_FLOAT },
        .maxSize = { TEN_FLOAT, TEN_FLOAT },
        .percentReference = { FIVE_FLOAT, FIVE_FLOAT },
        .parentIdealSize = { TWO_FLOAT, TWO_FLOAT },
    };
    LayoutConstraintF childConstraint = {
        .minSize = { ONE_FLOAT, ONE_FLOAT },
        .maxSize = { TEN_FLOAT, TEN_FLOAT },
        .percentReference = { FIVE_FLOAT, FIVE_FLOAT },
        .parentIdealSize = { TWO_FLOAT, TWO_FLOAT },
        .selfIdealSize = { ONE_FLOAT, FIVE_FLOAT },
    };
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    theme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    menuLayoutAlgorithm.UpdateChildConstraintByDevice(menuPattern, childConstraint, layoutConstraintF);
    EXPECT_EQ(childConstraint.minSize.width_, ZERO_FLOAT);
    layoutProperty->UpdateMenuWidth(Dimension(200.0f, DimensionUnit::PX));
    menuLayoutAlgorithm.UpdateChildConstraintByDevice(menuPattern, childConstraint, layoutConstraintF);
    EXPECT_EQ(childConstraint.minSize.width_, ZERO_FLOAT);
    layoutProperty->UpdateMenuWidth(Dimension(0.0f, DimensionUnit::PX));
    menuLayoutAlgorithm.UpdateChildConstraintByDevice(menuPattern, childConstraint, layoutConstraintF);
    EXPECT_EQ(childConstraint.minSize.width_, ZERO_FLOAT);
    layoutProperty->UpdateMenuWidth(Dimension(-1.0f, DimensionUnit::PX));
    menuLayoutAlgorithm.UpdateChildConstraintByDevice(menuPattern, childConstraint, layoutConstraintF);
    EXPECT_EQ(childConstraint.minSize.width_, ZERO_FLOAT);
}

/**
 * @tc.name: MenuExpandTestNg009
 * @tc.desc: Test SetHotAreas.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg009, TestSize.Level1)
{
    MenuWrapperPattern menuWrapperPattern(1);
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    menuWrapperPattern.frameNode_ = AceType::WeakClaim(AceType::RawPtr(menuNode));
    RefPtr<LayoutWrapperNode> layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNode), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNode, nullptr);
    auto frameNodeChildOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChildOne, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNodeOne = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNodeChildOne), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNodeOne, nullptr);
    auto frameNodeChildTwo = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChildTwo, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNodeTwo = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNodeChildTwo), nullptr, AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNodeTwo, nullptr);
    auto frameNodeChildThree = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 6, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChildThree, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNodeThree = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNodeChildThree), nullptr, AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNodeThree, nullptr);
    layoutWrapperNodeOne->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapperNodeTwo->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapperNodeThree->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapperNodeOne->hostNode_ = nullptr;
    layoutWrapperNodeTwo->GetHostNode()->tag_ = V2::MENU_PREVIEW_ETS_TAG;
    layoutWrapperNode->cachedList_.push_back(layoutWrapperNodeOne);
    layoutWrapperNode->cachedList_.push_back(layoutWrapperNodeTwo);
    layoutWrapperNode->cachedList_.push_back(layoutWrapperNodeThree);
    menuWrapperPattern.isShowInSubWindow_ = false;
    menuWrapperPattern.isSelectOverlaySubWindowWrapper_ = true;
    auto layoutProps = layoutWrapperNode->GetLayoutProperty();
    ASSERT_NE(layoutProps, nullptr);
    layoutProps->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    menuWrapperPattern.SetHotAreas(layoutWrapperNode);
    ASSERT_EQ(layoutWrapperNode->cachedList_.size(), 3);
}

/**
 * @tc.name: MenuExpandTestNg010
 * @tc.desc: Test SetHotAreas.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg010, TestSize.Level1)
{
    MenuWrapperPattern menuWrapperPattern(1);
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(3, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    menuWrapperPattern.frameNode_ = AceType::WeakClaim(AceType::RawPtr(menuNode));
    auto strongFrameNode = menuWrapperPattern.frameNode_.Upgrade();
    frameNode->MountToParent(strongFrameNode);
    auto menu = AceType::DynamicCast<FrameNode>(strongFrameNode->GetChildAtIndex(0));
    ASSERT_NE(menu, nullptr);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    menuPattern->previewMode_ = MenuPreviewMode::CUSTOM;
    RefPtr<LayoutWrapperNode> layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNode), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNode, nullptr);
    auto frameNodeChildOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChildOne, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNodeOne = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNodeChildOne), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNodeOne, nullptr);
    layoutWrapperNodeOne->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapperNode->cachedList_.push_back(layoutWrapperNodeOne);
    menuWrapperPattern.isShowInSubWindow_ = false;
    menuWrapperPattern.isSelectOverlaySubWindowWrapper_ = true;
    auto layoutProps = layoutWrapperNode->GetLayoutProperty();
    ASSERT_NE(layoutProps, nullptr);
    layoutProps->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    menuWrapperPattern.SetHotAreas(layoutWrapperNode);
    ASSERT_EQ(layoutWrapperNode->cachedList_.size(), 1);
}

/**
 * @tc.name: MenuExpandTestNg011
 * @tc.desc: Test SetHotAreas.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg011, TestSize.Level1)
{
    MenuWrapperPattern menuWrapperPattern(1);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(NODE_ID, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    menuWrapperPattern.frameNode_ = AceType::WeakClaim(AceType::RawPtr(menuNode));
    auto strongFrameNode = menuWrapperPattern.frameNode_.Upgrade();
    frameNode->MountToParent(strongFrameNode);
    auto menu = AceType::DynamicCast<FrameNode>(strongFrameNode->GetChildAtIndex(0));
    ASSERT_NE(menu, nullptr);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    menuPattern->previewMode_ = MenuPreviewMode::CUSTOM;
    menuWrapperPattern.filterColumnNode_ = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(3, TEXT_TAG, MenuType::MENU));
    RefPtr<LayoutWrapperNode> layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNode), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNode, nullptr);
    auto frameNodeChildOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChildOne, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNodeOne = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNodeChildOne), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNodeOne, nullptr);
    layoutWrapperNodeOne->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapperNode->cachedList_.push_back(layoutWrapperNodeOne);
    menuWrapperPattern.isShowInSubWindow_ = false;
    menuWrapperPattern.isSelectOverlaySubWindowWrapper_ = true;
    auto layoutProps = layoutWrapperNode->GetLayoutProperty();
    ASSERT_NE(layoutProps, nullptr);
    layoutProps->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    menuWrapperPattern.SetHotAreas(layoutWrapperNode);
    ASSERT_EQ(layoutWrapperNode->cachedList_.size(), 1);
}

/**
 * @tc.name: MenuExpandTestNg012
 * @tc.desc: Test SetHotAreas.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg012, TestSize.Level1)
{
    MenuWrapperPattern menuWrapperPattern(1);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(3, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    menuWrapperPattern.frameNode_ = AceType::WeakClaim(AceType::RawPtr(menuNode));
    auto strongFrameNode = menuWrapperPattern.frameNode_.Upgrade();
    frameNode->MountToParent(strongFrameNode);
    auto menu = AceType::DynamicCast<FrameNode>(strongFrameNode->GetChildAtIndex(0));
    ASSERT_NE(menu, nullptr);
    auto menuPattern = menu->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->type_ = MenuType::CONTEXT_MENU;
    RefPtr<LayoutWrapperNode> layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNode), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNode, nullptr);
    auto frameNodeChildOne = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 4, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNodeChildOne, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapperNodeOne = AceType::MakeRefPtr<LayoutWrapperNode>(
        std::move(frameNodeChildOne), AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    ASSERT_NE(layoutWrapperNodeOne, nullptr);
    layoutWrapperNodeOne->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapperNode->cachedList_.push_back(layoutWrapperNodeOne);
    menuWrapperPattern.isShowInSubWindow_ = false;
    menuWrapperPattern.isSelectOverlaySubWindowWrapper_ = true;
    auto layoutProps = layoutWrapperNode->GetLayoutProperty();
    ASSERT_NE(layoutProps, nullptr);
    layoutProps->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    menuWrapperPattern.SetHotAreas(layoutWrapperNode);
    ASSERT_EQ(layoutWrapperNode->cachedList_.size(), 1);
}

/**
 * @tc.name: MenuExpandTestNg013
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg013, TestSize.Level1)
{
    ScreenSystemManager::GetInstance().SetWindowInfo(FULL_SCREEN_WIDTH, 1.0, 1.0);
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, 1, AceType::MakeRefPtr<MenuPattern>(3, TEXT_TAG, MenuType::MENU));
    frameNode->MountToParent(menuNode);
    auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "", MenuType::MULTI_MENU);
    auto algorithm = AceType::MakeRefPtr<MultiMenuLayoutAlgorithm>();
    ASSERT_TRUE(algorithm);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    layoutProp->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProp->UpdateContentConstraint();
    auto wrapper = new LayoutWrapperNode(menuNode, geometryNode, layoutProp);
    for (int32_t i = 0; i < 3; ++i) {
        auto itemPattern = AceType::MakeRefPtr<MenuItemPattern>();
        auto menuItem = AceType::MakeRefPtr<FrameNode>("", -1, itemPattern);
        auto itemGeoNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeoNode->SetFrameSize(SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT));
        auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(menuItem, itemGeoNode, layoutProp);
        wrapper->AppendChild(childWrapper);
    }
    auto expectedSize = SizeF(MENU_ITEM_SIZE_WIDTH, MENU_ITEM_SIZE_HEIGHT * 3);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    menuPattern->isEmbedded_ = true;
    algorithm->Measure(wrapper);
    auto firstChildWrapper = wrapper->GetAllChildrenWithBuild().front();
    ASSERT_NE(firstChildWrapper, nullptr);
    auto firstChildGeometryNode = firstChildWrapper->GetGeometryNode();
    ASSERT_NE(firstChildGeometryNode, nullptr);
    EXPECT_EQ(firstChildGeometryNode->GetFrameSize().Width(), MENU_ITEM_SIZE_WIDTH);
    delete wrapper;
}

/**
 * @tc.name: MenuExpandTestNg014
 * @tc.desc: Test GetBottomBySafeAreaManager.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg014, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "targetTag", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    auto property = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateIsRectInTarget(true);
    RefPtr<MenuPattern> menuPattern = AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "", MenuType::MENU);
    ASSERT_NE(menuPattern, nullptr);
    RefPtr<SafeAreaManager> safeAreamanager = AceType::MakeRefPtr<SafeAreaManager>();
    ASSERT_NE(safeAreamanager, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto bottom = layoutAlgorithm->GetBottomBySafeAreaManager(safeAreamanager, property, menuPattern);
    EXPECT_EQ(bottom, ZERO_FLOAT);
    safeAreamanager->keyboardHeightConsideringUIExtension_ = TWO_NUMBER;
    bottom = layoutAlgorithm->GetBottomBySafeAreaManager(safeAreamanager, property, menuPattern);
    EXPECT_EQ(bottom, TWO_FLOAT);
    safeAreamanager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    safeAreamanager->keyboardInset_.end = TEN_NUMBER;
    safeAreamanager->keyboardInset_.start = FIVE_NUMBER;
    bottom = layoutAlgorithm->GetBottomBySafeAreaManager(safeAreamanager, property, menuPattern);
    EXPECT_EQ(bottom, FIVE_FLOAT);
}

/**
 * @tc.name: MenuExpandTestNg015
 * @tc.desc: Test CheckPreviewConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg015, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_PREVIEW_ETS_TAG, 0, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "targetTag", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    Rect menuWindowRect(ONE_FLOAT, ONE_FLOAT, TEN_FLOAT, TEN_FLOAT);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->layoutRegionMargin_.left = std::nullopt;
    layoutAlgorithm->layoutRegionMargin_.right = TEN_FLOAT;
    layoutAlgorithm->CheckPreviewConstraint(frameNode, menuWindowRect);
    EXPECT_EQ(frameNode->geometryNode_->frame_.rect_.width_, ZERO_FLOAT);
}

/**
 * @tc.name: MenuExpandTestNg016
 * @tc.desc: Test LayoutNormalTopPreviewBottomMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg016, TestSize.Level1)
{
    RefPtr<GeometryNode> previewGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "menu", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    SizeF totalSize(TEN_FLOAT, TEN_FLOAT);
    float menuItemTotalHeight = FIVE_FLOAT;
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->param_.windowGlobalSizeF.height_ = FIVE_FLOAT;
    layoutAlgorithm->param_.menuWindowRect.height_ = ONE_FLOAT;
    previewGeometryNode->frame_.rect_.height_ = TEN_FLOAT;
    layoutAlgorithm->wrapperRect_.height_ = TWENTY_FLOAT;
    layoutAlgorithm->param_.topSecurity = ONE_FLOAT;
    layoutAlgorithm->param_.bottomSecurity = ONE_FLOAT;
    layoutAlgorithm->LayoutNormalTopPreviewBottomMenu(
        previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight, layoutWrapper);
    EXPECT_EQ(previewGeometryNode->frame_.rect_.width_, ZERO_FLOAT);
    previewGeometryNode->frame_.rect_.width_ = THIRTY_FLOAT;
    previewGeometryNode->frame_.rect_.height_ = THIRTY_FLOAT;
    layoutAlgorithm->wrapperRect_.height_ = TWENTY_FLOAT;
    layoutAlgorithm->param_.previewMenuGap = NEGATIVE_EIGHTEEN;
    layoutAlgorithm->LayoutNormalTopPreviewBottomMenu(
        previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight, layoutWrapper);
    EXPECT_EQ(previewGeometryNode->frame_.rect_.width_, THIRTY_FLOAT);
}

/**
 * @tc.name: MenuExpandTestNg017
 * @tc.desc: Test LayoutNormalBottomPreviewTopMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg017, TestSize.Level1)
{
    RefPtr<GeometryNode> previewGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "menu", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    SizeF totalSize(TEN_FLOAT, TEN_FLOAT);
    float menuItemTotalHeight = FIVE_FLOAT;
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->param_.windowGlobalSizeF.height_ = THIRTY_FLOAT;
    layoutAlgorithm->param_.menuWindowRect.height_ = TWENTY_FLOAT;
    previewGeometryNode->frame_.rect_.height_ = TEN_FLOAT;
    layoutAlgorithm->wrapperRect_.height_ = TWENTY_FLOAT;
    layoutAlgorithm->param_.topSecurity = ONE_FLOAT;
    layoutAlgorithm->param_.bottomSecurity = ONE_FLOAT;
    layoutAlgorithm->LayoutNormalBottomPreviewTopMenu(
        previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight, layoutWrapper);
    EXPECT_EQ(previewGeometryNode->frame_.rect_.width_, ZERO_FLOAT);
    previewGeometryNode->frame_.rect_.width_ = THIRTY_FLOAT;
    previewGeometryNode->frame_.rect_.height_ = THIRTY_FLOAT;
    layoutAlgorithm->wrapperRect_.height_ = TWENTY_FLOAT;
    layoutAlgorithm->param_.previewMenuGap = NEGATIVE_EIGHTEEN;
    layoutAlgorithm->LayoutNormalBottomPreviewTopMenu(
        previewGeometryNode, menuGeometryNode, totalSize, menuItemTotalHeight, layoutWrapper);
    EXPECT_EQ(previewGeometryNode->frame_.rect_.width_, THIRTY_FLOAT);
}

/**
 * @tc.name: MenuExpandTestNg018
 * @tc.desc: Test ComputePlacementByAlignType.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg018, TestSize.Level1)
{
    RefPtr<MenuLayoutProperty> menuProp = AceType::MakeRefPtr<MenuLayoutProperty>();
    ASSERT_NE(menuProp, nullptr);
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    menuProp->UpdateAlignType(MenuAlignType::CENTER);
    layoutAlgorithm->ComputePlacementByAlignType(menuProp);
    EXPECT_EQ(layoutAlgorithm->placement_, Placement::BOTTOM);
    menuProp->UpdateAlignType(MenuAlignType::END);
    layoutAlgorithm->ComputePlacementByAlignType(menuProp);
    EXPECT_EQ(layoutAlgorithm->placement_, Placement::BOTTOM_RIGHT);
    menuProp->UpdateAlignType(static_cast<MenuAlignType>(999));
    layoutAlgorithm->ComputePlacementByAlignType(menuProp);
    EXPECT_EQ(layoutAlgorithm->placement_, Placement::BOTTOM_RIGHT);
}

/**
 * @tc.name: MenuExpandTestNg019
 * @tc.desc: Test LayoutNormalBottomPreviewTopMenu.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg019, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "menu", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    MockContainer::SetUp();
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    auto container = MockContainer::Current();
    container->pipelineContext_ = pipelineContext;
    frameNode->instanceId_ = container->GetInstanceId();
    AceEngine::Get().AddContainer(container->GetInstanceId(), container);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    LayoutWrapper* layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF layoutConstraintF = {
        .minSize = { ONE_FLOAT, ONE_FLOAT },
        .maxSize = { TEN_FLOAT, TEN_FLOAT },
        .percentReference = { FIVE_FLOAT, FIVE_FLOAT },
        .parentIdealSize = { TWO_FLOAT, TWO_FLOAT },
    };
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->UpdateConstraintSelectHeight(layoutWrapper, layoutConstraintF);
    EXPECT_EQ(layoutConstraintF.maxSize.height_, NEGATIVE_EIGHT);
    frameNode->geometryNode_->frame_.rect_.width_ = ZERO_FLOAT;
    refLayoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(refLayoutWrapper, nullptr);
    layoutWrapper = Referenced::RawPtr(refLayoutWrapper);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutAlgorithm->wrapperRect_.width_ = THIRTY_FLOAT;
    layoutAlgorithm->wrapperRect_.x_ = THIRTY_FLOAT;
    layoutAlgorithm->targetOffset_ = OffsetF(TEN_FLOAT, TEN_FLOAT);
    layoutAlgorithm->targetSize_ = SizeF(TEN_FLOAT, TEN_FLOAT);
    layoutAlgorithm->wrapperSize_.width_ = THIRTY_FLOAT;
    layoutAlgorithm->lastPosition_ = std::make_optional(OffsetF(FIVE_FLOAT, FIVE_FLOAT));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    layoutAlgorithm->UpdateConstraintSelectHeight(layoutWrapper, layoutConstraintF);
    EXPECT_EQ(layoutConstraintF.maxSize.height_, ZERO_FLOAT);
    layoutAlgorithm->paddingEnd_ = THIRTY_FLOAT;
    layoutAlgorithm->paddingStart_ = NEGATIVE_THIRTY;
    layoutAlgorithm->targetOffset_ = OffsetF(TWENTY_FLOAT, TEN_FLOAT);
    layoutAlgorithm->holdEmbeddedMenuPosition_ = true;
    layoutWrapper->GetHostNode()->GetPattern<MenuPattern>()->isHeightModifiedBySelect_ = true;
    auto menuLayoutProps = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(menuLayoutProps, nullptr);
    menuLayoutProps->UpdateSelectModifiedHeight(TEN_FLOAT);
    layoutAlgorithm->UpdateConstraintSelectHeight(layoutWrapper, layoutConstraintF);
    EXPECT_EQ(layoutConstraintF.maxSize.height_, NEGATIVE_FIVE);
    menuLayoutProps->UpdateSelectModifiedHeight(NEGATIVE_EIGHT);
    layoutAlgorithm->UpdateConstraintSelectHeight(layoutWrapper, layoutConstraintF);
    EXPECT_EQ(layoutConstraintF.maxSize.height_, NEGATIVE_EIGHT);
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: MenuExpandTestNg020
 * @tc.desc: Test SetMenuBackGroundStyle.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg020, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, AceType::MakeRefPtr<MenuPattern>(NODE_ID, "menu", MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    frameNode->renderContext_ = AceType::MakeRefPtr<RenderContext>();
    MenuParam menuParam;
    MenuPattern menuPattern(3, "menu", MenuType::MENU);
    menuPattern.SetMenuBackGroundStyle(frameNode, menuParam);
    EXPECT_EQ(frameNode->GetRenderContext()->propBackgroundColor_, Color::TRANSPARENT);
    menuParam.backgroundColor = Color::RED;
    BlurStyleOption blurStyleInfo = { BlurStyle::NO_MATERIAL, ThemeColorMode::SYSTEM, AdaptiveColor::DEFAULT, 1.0 };
    menuParam.backgroundBlurStyleOption = blurStyleInfo;
    menuParam.backgroundEffectOption = std::make_optional(EffectOption());
    menuPattern.SetMenuBackGroundStyle(frameNode, menuParam);
    EXPECT_EQ(frameNode->GetRenderContext()->propBackgroundColor_, Color::RED);
    CalcDimension radius;
    radius.SetValue(80.0f);
    Color color = Color::FromARGB(13, 255, 255, 255);
    EffectOption effectOption = { radius, 1.0, 1.08, color };
    auto& background = frameNode->renderContext_->GetOrCreateBackground();
    ASSERT_NE(&background, nullptr);
    background->propEffectOption = effectOption;
    ASSERT_TRUE(background->propEffectOption.has_value());
    ASSERT_EQ(background->propEffectOption.value(), effectOption);
    background->propBlurRadius = 0.0_px;
    background->propBlurStyleOption = blurStyleInfo;
    menuPattern.SetMenuBackGroundStyle(frameNode, menuParam);
    EXPECT_EQ(frameNode->GetRenderContext()->GetBackBlurStyle(), blurStyleInfo);
}

/**
 * @tc.name: MenuExpandTestNg021
 * @tc.desc: Test DuplicateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg021, TestSize.Level1)
{
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(2, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    MenuParam menuParam;
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    auto duplicateMenuNode = menuPattern->DuplicateMenuNode(menuNode, menuParam);
    EXPECT_NE(duplicateMenuNode, nullptr);
    menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, NODE_ID, AceType::MakeRefPtr<MenuPattern>(5, TEXT_TAG, MenuType::MENU));
    auto menuLayoutProperty = menuNode->GetLayoutProperty<MenuLayoutProperty>();
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0.1));
    menuLayoutProperty->UpdateBorderRadius(borderRadius);
    menuPattern->DuplicateMenuNode(menuNode, menuParam);
    EXPECT_TRUE(menuLayoutProperty->GetBorderRadius().has_value());
}

/**
 * @tc.name: MenuExpandTestNg022
 * @tc.desc: Test LayoutOtherDeviceLeftPreviewRightMenuLessThan.
 * @tc.type: FUNC
 */
HWTEST_F(MenuExpandTestNg, MenuExpandTestNg022, TestSize.Level1)
{
    MenuLayoutAlgorithm menuLayoutAlgorithm;
    RefPtr<GeometryNode> previewGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<GeometryNode> menuGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    SizeF totalSize(TEN_FLOAT, TEN_FLOAT);
    menuLayoutAlgorithm.placement_ = Placement::LEFT_BOTTOM;
    menuLayoutAlgorithm.LayoutOtherDeviceLeftPreviewRightMenuLessThan(previewGeometryNode, menuGeometryNode, totalSize);
    EXPECT_EQ(previewGeometryNode->GetMarginFrameOffset().x_, ZERO_FLOAT);
    menuLayoutAlgorithm.placement_ = Placement::BOTTOM;
    menuLayoutAlgorithm.LayoutOtherDeviceLeftPreviewRightMenuLessThan(previewGeometryNode, menuGeometryNode, totalSize);
    EXPECT_EQ(previewGeometryNode->GetMarginFrameOffset().x_, ZERO_FLOAT);
    menuLayoutAlgorithm.placement_ = Placement::RIGHT_BOTTOM;
    menuLayoutAlgorithm.LayoutOtherDeviceLeftPreviewRightMenuLessThan(previewGeometryNode, menuGeometryNode, totalSize);
    EXPECT_EQ(previewGeometryNode->GetMarginFrameOffset().y_, ZERO_FLOAT);
}
} // namespace OHOS::Ace::NG
