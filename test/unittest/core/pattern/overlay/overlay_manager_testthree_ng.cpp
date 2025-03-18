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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/frontend.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderColorProperty BORDER_COLOR_TEST = { Color::BLUE, Color::BLUE, Color::BLUE, Color::BLUE };
const NG::BorderColorProperty NEW_BORDER_COLOR_TEST = { Color::RED, Color::GREEN, Color::GRAY, Color::BLACK };
const std::string TEXT_TAG = "text";
const OffsetF MENU_OFFSET(10.0, 10.0);
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

class OverlayManagerTestThreeNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;

protected:
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerTestThreeNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerTestThreeNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

/**
 *@tc.name:CalculateMenuPosition001
 *@tc.desc:Test CalculateMenuPosition
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CalculateMenuPosition001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->isContextMenuDragHideFinished_ = true;
    RefPtr<FrameNode> menuWrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapperNode, nullptr);
    OffsetF ret = overlayManager->CalculateMenuPosition(menuWrapperNode, MENU_OFFSET);
    EXPECT_EQ(ret.GetX(), 0.0);
    EXPECT_EQ(ret.GetY(), 0.0);
    overlayManager->isContextMenuDragHideFinished_ = false;
    ret = overlayManager->CalculateMenuPosition(menuWrapperNode, MENU_OFFSET);
    EXPECT_EQ(ret.GetX(), 0.0);
    EXPECT_EQ(ret.GetY(), 0.0);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    overlayManager->menuMap_.emplace(3, std::move(mainMenu));
    ret = overlayManager->CalculateMenuPosition(menuWrapperNode, MENU_OFFSET);
    EXPECT_EQ(ret.GetX(), 0.0);
    EXPECT_EQ(ret.GetY(), 0.0);
    overlayManager->dragMoveVector_ = OffsetF(20.0, 20.0);
    ret = overlayManager->CalculateMenuPosition(menuWrapperNode, MENU_OFFSET);
    EXPECT_EQ(ret.GetX(), 0.0);
    EXPECT_EQ(ret.GetY(), 0.0);
}

/**
 *@tc.name:RemoveMenuWrapperNode001
 *@tc.desc:Test RemoveMenuWrapperNode
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveMenuWrapperNode001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto mainMenu =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(mainMenu, nullptr);
    auto childOne = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(childOne, nullptr);
    auto childTwo = FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(childTwo, nullptr);
    mainMenu->children_.push_back(childOne);
    mainMenu->children_.push_back(childTwo);
    overlayManager->RemoveMenuWrapperNode(mainMenu);
    EXPECT_EQ(mainMenu->children_.size(), 1);
}

/**
 *@tc.name:CheckPageNeedAvoidKeyboard001
 *@tc.desc:Test CheckPageNeedAvoidKeyboard
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CheckPageNeedAvoidKeyboard001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    auto child = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(child, nullptr);
    frameNode->children_.push_back(child);
    overlayManager->rootNodeWeak_ = std::move(frameNode);
    bool ret = overlayManager->CheckPageNeedAvoidKeyboard();
    EXPECT_TRUE(ret);
}

/**
 *@tc.name:RemoveFrameNodeWithOrder001
 *@tc.desc:Test RemoveFrameNodeWithOrder
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveFrameNodeWithOrder001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->dialogOrderMap_.emplace(3, true);
    overlayManager->dialogOrderMap_.emplace(1, true);
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    overlayManager->RemoveFrameNodeWithOrder(frameNode);
}

/**
 *@tc.name:RemoveEventColumn001
 *@tc.desc:Test RemoveEventColumn
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveEventColumn001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->hasEvent_ = true;
    auto frameNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    overlayManager->eventColumnNodeWeak_ = std::move(frameNode);
    overlayManager->RemoveEventColumn();
    EXPECT_TRUE(overlayManager->hasEvent_);
}

/**
 *@tc.name:MountPixelMapToWindowScene001
 *@tc.desc:Test MountPixelMapToWindowScene
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, MountPixelMapToWindowScene001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto columnNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(columnNode, nullptr);
    auto windowScene =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(windowScene, nullptr);
    overlayManager->MountPixelMapToWindowScene(columnNode, windowScene, true);
    EXPECT_TRUE(overlayManager->hasDragPixelMap_);
    overlayManager->MountPixelMapToWindowScene(columnNode, windowScene, false);
    EXPECT_TRUE(overlayManager->hasPixelMap_);
}
} // namespace OHOS::Ace::NG
