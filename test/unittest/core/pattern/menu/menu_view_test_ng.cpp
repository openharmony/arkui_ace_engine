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
#include "core/components_ng/pattern/text/text_model_ng.h"
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
const std::string TEXT_TAG = "text";
constexpr int32_t TARGET_ID = 100;

} // namespace
class MenuViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    void MockPipelineContextGetTheme();
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

void MenuViewTestNg::SetUpTestCase() {}

void MenuViewTestNg::TearDownTestCase() {}

void MenuViewTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    InitMenuTestNg();
    isSubMenuBuilded_ = false;
}

void MenuViewTestNg::MockPipelineContextGetTheme()
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

void MenuViewTestNg::TearDown()
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

int32_t MenuViewTestNg::GetNodeId()
{
    nodeId_++;
    return nodeId_;
}

void MenuViewTestNg::InitMenuTestNg()
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
    menuItemFrameNode_ =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    subMenuParent_ =
        FrameNode::CreateFrameNode(V2::MENU_ITEM_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<MenuItemPattern>());
    auto itemComponent = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    auto itemComponent3 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
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
 * @tc.name: GetHasIcon001
 * @tc.desc: MenuView GetHasIcon.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, GetHasIcon001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    std::vector<OptionParam> optionParams;
    OptionParam param1;
    param1.isPasteOption = true;
    param1.icon = "";
    OptionParam param2;
    param2.isPasteOption = true;
    param2.icon = "abc";
    OptionParam param3;
    param3.isPasteOption = false;
    param3.icon = "";
    OptionParam param4;
    param4.isPasteOption = false;
    param4.icon = "abc";

    optionParams.emplace_back(param1);
    optionParams.emplace_back(param2);
    optionParams.emplace_back(param3);
    optionParams.emplace_back(param4);
    MenuParam menuParam;
    auto menuWrapperNode = MenuView::Create(std::move(optionParams), 3, "", MenuType::MENU, menuParam);
    ASSERT_NE(menuWrapperNode, nullptr);
}
/**
 * @tc.name: GetMenuPixelMap001
 * @tc.desc: MenuView GetMenuPixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, GetMenuPixelMap001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto targetNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, GetNodeId(), AceType::MakeRefPtr<TextPattern>());
    MenuParam menuParam;
    MenuView::GetMenuPixelMap(targetNode, menuParam, wrapperNode_);

    ASSERT_NE(targetNode, nullptr);
}

/**
 * @tc.name: SkipMenuTest001
 * @tc.desc: Verify bindMenu gesture event.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SkipMenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a targetNode
     */
    TextModelNG textModel;
    textModel.Create("Text");
    /**
     * @tc.steps: step2. bindMenuGesture with optionParams.
     * @tc.expected: check the menu event is not nullptr.
     */
    std::vector<OptionParam> optionParams;
    MenuParam param;
    optionParams.emplace_back("MenuItem1", "fakeIcon", nullptr);
    ViewAbstractModelNG viewAbstractModel;
    viewAbstractModel.BindMenuGesture(std::move(optionParams), nullptr, param);
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureHub->showMenu_, nullptr);
    EXPECT_NE(gestureHub->bindMenuTouch_, nullptr);
    NG::ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: SkipMenuTest002
 * @tc.desc: Verify skip function.
 * @tc.type: FUNC
 */
HWTEST_F(MenuViewTestNg, SkipMenuTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a overlayManger
     */
    auto overlayManger = AceType::MakeRefPtr<OverlayManager>(nullptr);
    /**
     * @tc.steps: step2. skip menu show with target id
     * @tc.expected: check the skip ids not empty.
     */
    overlayManger->SkipMenuShow(TARGET_ID);
    ASSERT_FALSE(overlayManger->skipTargetIds_.empty());
    /**
     * @tc.steps: step3. skip menu show with target id again
     * @tc.expected: The skip id is not added repeatedly.
     */
    overlayManger->SkipMenuShow(TARGET_ID);
    EXPECT_EQ(overlayManger->skipTargetIds_.size(), 1);
    /**
     * @tc.steps: step4. search targetId will skip
     * @tc.expected: Return true skip the menu show.
     */
    EXPECT_TRUE(overlayManger->CheckSkipMenuShow(TARGET_ID));
    /**
     * @tc.steps: step5. resume the target menu show
     * @tc.expected: Remove success and CheckSkipMenuShow return false.
     */
    overlayManger->ResumeMenuShow(TARGET_ID);
    ASSERT_TRUE(overlayManger->skipTargetIds_.empty());
    EXPECT_FALSE(overlayManger->CheckSkipMenuShow(TARGET_ID));
}
} // namespace OHOS::Ace::NG
