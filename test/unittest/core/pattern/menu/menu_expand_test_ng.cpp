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
const std::string EMPTY_TEXT = "";
const std::string TEXT_TAG = "text";
const std::string MENU_TAG = "menu";
const std::string MENU_TOUCH_EVENT_TYPE = "1";
const DirtySwapConfig configDirtySwap = { false, false, false, false, true, false };
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
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
    subMenuPattern->SetSubMenuShow();
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
} // namespace OHOS::Ace::NG
