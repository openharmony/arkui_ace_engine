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

#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/frontend.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_manager.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_presentation_property.h"
#include "core/components_ng/pattern/sheet/sheet_style.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const NG::BorderColorProperty BORDER_COLOR_TEST = { Color::BLUE, Color::BLUE, Color::BLUE, Color::BLUE };

class AutoSaveTestPattern : public Pattern {
    DECLARE_ACE_TYPE(AutoSaveTestPattern, Pattern);
public:
    bool CheckAutoSave() override
    {
        return true;
    }
};
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
    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
        ElementRegister::GetInstance()->Clear();
    }

protected:
    int32_t minPlatformVersion_ = 0;
    RefPtr<AceType> savedMenuManager_;
    WeakPtr<UINode> savedRootNodeWeak_;
};

void OverlayManagerTestThreeNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->overlayManager_) {
        savedMenuManager_ = pipelineContext->overlayManager_->menuManager_;
        savedRootNodeWeak_ = pipelineContext->overlayManager_->rootNodeWeak_;
    }
}

void OverlayManagerTestThreeNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->overlayManager_) {
        pipelineContext->overlayManager_->menuManager_ = savedMenuManager_;
        pipelineContext->overlayManager_->rootNodeWeak_ = savedRootNodeWeak_;
        pipelineContext->overlayManager_->imageGeneratorSheetKey_ = std::nullopt;
        pipelineContext->overlayManager_->modalList_.clear();
        pipelineContext->overlayManager_->detachedProxyMap_.clear();
    }
    auto mockContainer = MockContainer::Current();
    if (mockContainer) {
        mockContainer->isSubContainer_ = false;
    }
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
    overlayManager->CheckMenuManager();
    auto menuManager = AceType::DynamicCast<MenuManager>(overlayManager->menuManager_);
    ASSERT_NE(menuManager, nullptr);
    menuManager->menuMap_.emplace(3, std::move(mainMenu));
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
    overlayManager->CheckMenuManager();
    auto menuManager = AceType::DynamicCast<MenuManager>(overlayManager->menuManager_);
    ASSERT_NE(menuManager, nullptr);
    menuManager->RemoveMenuWrapperNode(mainMenu, pipelineContext);
    EXPECT_EQ(mainMenu->children_.size(), 1);
}

/**
 *@tc.name:EraseMenuInfoFromWrapper001
 *@tc.desc:Test EraseMenuInfoFromWrapper
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, EraseMenuInfoFromWrapper001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(targetId));
    overlayManager->CheckMenuManager();
    auto menuManager = AceType::DynamicCast<MenuManager>(overlayManager->menuManager_);
    ASSERT_NE(menuManager, nullptr);
    menuManager->menuMap_[targetId] = menuWrapper;
    menuManager->EraseMenuInfoFromWrapper(menuWrapper);
    EXPECT_EQ(menuManager->menuMap_[targetId], nullptr);
    menuManager->menuMap_[targetId] = menuWrapper;
    auto menuWrapper2 = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(targetId));
    menuManager->EraseMenuInfoFromWrapper(menuWrapper2);
    EXPECT_NE(menuManager->menuMap_[targetId], nullptr);
    menuManager->menuMap_[targetId] = nullptr;
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
    overlayManager->nodeIdOrderMap_.emplace(3, true);
    overlayManager->nodeIdOrderMap_.emplace(1, true);
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

/**
 *@tc.name:UpdateTipsStatus001
 *@tc.desc:Test UpdateTipsStatus of OverlayManager
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, UpdateTipsStatus001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t targetId = 1;
    bool isInContinus = true;
    // check tipsStatusList_
    EXPECT_EQ(overlayManager->tipsStatusList_.size(), 0);
    overlayManager->UpdateTipsStatus(targetId, isInContinus);
    EXPECT_EQ(overlayManager->tipsStatusList_.size(), 1);
    EXPECT_EQ(overlayManager->GetTipsStatus(targetId), isInContinus);
    isInContinus = false;
    overlayManager->UpdateTipsStatus(targetId, isInContinus);
    EXPECT_EQ(overlayManager->GetTipsStatus(targetId), isInContinus);
}

/**
 *@tc.name:EraseTipsStatus001
 *@tc.desc:Test EraseTipsStatus of OverlayManager
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, EraseTipsStatus001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t targetId = 1;
    bool isInContinus = true;
    overlayManager->UpdateTipsStatus(targetId, isInContinus);
    EXPECT_EQ(overlayManager->tipsStatusList_.size(), 1);
    overlayManager->EraseTipsStatus(targetId);
    EXPECT_EQ(overlayManager->tipsStatusList_.size(), 0);
}

/**
 *@tc.name:GetTipsStatus001
 *@tc.desc:Test GetTipsStatus of OverlayManager
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, GetTipsStatus001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t targetId = 1;
    bool isInContinus = true;
    overlayManager->UpdateTipsStatus(targetId, isInContinus);
    bool result = overlayManager->GetTipsStatus(targetId);
    EXPECT_EQ(result, isInContinus);
    int32_t nonExistentTargetId = 2;
    result = overlayManager->GetTipsStatus(nonExistentTargetId);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: PopTipsBubble1
 * @tc.desc: Test PopBubble function.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, PopTipsBubble1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(targetNode, nullptr);
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(popupNode, nullptr);
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(overlayNode, nullptr);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    bubblePattern->PopBubble(true);
    EXPECT_EQ(overlayManager->GetTipsStatus(1), false);
}

/**
 *@tc.name:UpdateContextMenuDisappearPositionCheckMenuManagerFalse001
 *@tc.desc:Test UpdateContextMenuDisappearPosition when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, UpdateContextMenuDisappearPositionCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->UpdateContextMenuDisappearPosition(OffsetF(0.0f, 0.0f), 1.0f, false, 1);
}

/**
 *@tc.name:CalculateMenuPositionCheckMenuManagerFalse001
 *@tc.desc:Test CalculateMenuPosition when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CalculateMenuPositionCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    OffsetF ret = overlayManager->CalculateMenuPosition(nullptr, OffsetF(0.0f, 0.0f));
    EXPECT_EQ(ret.GetX(), 0.0f);
    EXPECT_EQ(ret.GetY(), 0.0f);
}

/**
 *@tc.name:GetMenuPreviewCenterCheckMenuManagerFalse001
 *@tc.desc:Test GetMenuPreviewCenter when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, GetMenuPreviewCenterCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    NG::OffsetF offset;
    bool ret = overlayManager->GetMenuPreviewCenter(offset);
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:ContextMenuSwitchDragPreviewAnimationCheckMenuManagerFalse001
 *@tc.desc:Test ContextMenuSwitchDragPreviewAnimation when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, ContextMenuSwitchDragPreviewAnimationCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->ContextMenuSwitchDragPreviewAnimation(nullptr, OffsetF(0.0f, 0.0f));
}

/**
 *@tc.name:RegisterMenuLifeCycleCallbackCheckMenuManagerFalse001
 *@tc.desc:Test RegisterMenuLifeCycleCallback when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RegisterMenuLifeCycleCallbackCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    std::function<void(const MenuLifeCycleEvent&)> callback = [](const MenuLifeCycleEvent&) {};
    overlayManager->RegisterMenuLifeCycleCallback(1, std::move(callback));
}

/**
 *@tc.name:UnRegisterMenuLifeCycleCallbackCheckMenuManagerFalse001
 *@tc.desc:Test UnRegisterMenuLifeCycleCallback when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, UnRegisterMenuLifeCycleCallbackCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->UnRegisterMenuLifeCycleCallback(1);
}

/**
 *@tc.name:GetMenuLifeCycleCallbackCheckMenuManagerFalse001
 *@tc.desc:Test GetMenuLifeCycleCallback when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, GetMenuLifeCycleCallbackCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto& ret = overlayManager->GetMenuLifeCycleCallback(1);
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:HideAllMenusWithoutAnimationCheckMenuManagerFalse001
 *@tc.desc:Test HideAllMenusWithoutAnimation when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, HideAllMenusWithoutAnimationCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->HideAllMenusWithoutAnimation(false);
}

/**
 *@tc.name:ShowMenuCheckMenuManagerFalse001
 *@tc.desc:Test ShowMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, ShowMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->ShowMenu(1, OffsetF(0.0f, 0.0f), menu);
}

/**
 *@tc.name:ShowMenuInSubWindowCheckMenuManagerFalse001
 *@tc.desc:Test ShowMenuInSubWindow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, ShowMenuInSubWindowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->ShowMenuInSubWindow(1, OffsetF(0.0f, 0.0f), menu);
}

/**
 *@tc.name:HideMenuInSubWindowWithNodeCheckMenuManagerFalse001
 *@tc.desc:Test HideMenuInSubWindowWithNode when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, HideMenuInSubWindowWithNodeCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->HideMenuInSubWindow(menu, 1);
}

/**
 *@tc.name:HideMenuInSubWindowWithAnimCheckMenuManagerFalse001
 *@tc.desc:Test HideMenuInSubWindowWithAnim when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, HideMenuInSubWindowWithAnimCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->HideMenuInSubWindow(true, true);
}

/**
 *@tc.name:GetMenuNodeWithExistContentCheckMenuManagerFalse001
 *@tc.desc:Test GetMenuNodeWithExistContent when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, GetMenuNodeWithExistContentCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto ret = overlayManager->GetMenuNodeWithExistContent(nullptr);
    EXPECT_EQ(ret, nullptr);
}

/**
 *@tc.name:GetMenuNodeCheckMenuManagerFalse001
 *@tc.desc:Test GetMenuNode when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, GetMenuNodeCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto ret = overlayManager->GetMenuNode(1);
    EXPECT_EQ(ret, nullptr);
}

/**
 *@tc.name:HideMenuCheckMenuManagerFalse001
 *@tc.desc:Test HideMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, HideMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->HideMenu(menu, 1, false, HideMenuType::NORMAL);
}

/**
 *@tc.name:HideAllMenusCheckMenuManagerFalse001
 *@tc.desc:Test HideAllMenus when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, HideAllMenusCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->HideAllMenus();
}

/**
 *@tc.name:DeleteMenuCheckMenuManagerFalse001
 *@tc.desc:Test DeleteMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, DeleteMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->DeleteMenu(1);
}

/**
 *@tc.name:CleanMenuInSubWindowWithAnimationCheckMenuManagerFalse001
 *@tc.desc:Test CleanMenuInSubWindowWithAnimation when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CleanMenuInSubWindowWithAnimationCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->CleanMenuInSubWindowWithAnimation();
}

/**
 *@tc.name:CleanHoverImagePreviewInSubWindowCheckMenuManagerFalse001
 *@tc.desc:Test CleanHoverImagePreviewInSubWindow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CleanHoverImagePreviewInSubWindowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto flexNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->CleanHoverImagePreviewInSubWindow(flexNode);
}

/**
 *@tc.name:CleanPreviewInSubWindowCheckMenuManagerFalse001
 *@tc.desc:Test CleanPreviewInSubWindow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CleanPreviewInSubWindowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->CleanPreviewInSubWindow();
}

/**
 *@tc.name:CleanMenuInSubWindowCheckMenuManagerFalse001
 *@tc.desc:Test CleanMenuInSubWindow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CleanMenuInSubWindowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->CleanMenuInSubWindow(1);
}

/**
 *@tc.name:IsMenuShowCheckMenuManagerFalse001
 *@tc.desc:Test IsMenuShow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, IsMenuShowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    bool ret = overlayManager->IsMenuShow();
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:RemoveMenuCheckMenuManagerFalse001
 *@tc.desc:Test RemoveMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto overlay = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    bool ret = overlayManager->RemoveMenu(overlay);
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:PublishMenuStatusCheckMenuManagerFalse001
 *@tc.desc:Test PublishMenuStatus when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, PublishMenuStatusCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->PublishMenuStatus(true, menuNode);
}

/**
 *@tc.name:SetIsMenuShowCheckMenuManagerFalse001
 *@tc.desc:Test SetIsMenuShow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, SetIsMenuShowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menuNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->SetIsMenuShow(true, menuNode);
}

/**
 *@tc.name:RemoveMenuFilterCheckMenuManagerFalse001
 *@tc.desc:Test RemoveMenuFilter when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveMenuFilterCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menuWrapper = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    overlayManager->RemoveMenuFilter(menuWrapper, true);
}

/**
 *@tc.name:BuildAIEntityMenuCheckMenuManagerFalse001
 *@tc.desc:Test BuildAIEntityMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, BuildAIEntityMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    auto ret = overlayManager->BuildAIEntityMenu(menuOptions);
    EXPECT_EQ(ret, nullptr);
}

/**
 *@tc.name:CreateAIEntityMenuCheckMenuManagerFalse001
 *@tc.desc:Test CreateAIEntityMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CreateAIEntityMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    auto targetNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    auto ret = overlayManager->CreateAIEntityMenu(menuOptions, targetNode);
    EXPECT_EQ(ret, nullptr);
}

/**
 *@tc.name:ShowAIEntityMenuCheckMenuManagerFalse001
 *@tc.desc:Test ShowAIEntityMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, ShowAIEntityMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    std::vector<std::pair<std::string, std::function<void()>>> menuOptions;
    auto targetNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, 3, AceType::MakeRefPtr<ButtonPattern>());
    bool ret = overlayManager->ShowAIEntityMenu(menuOptions, RectF(), targetNode);
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:CloseAIEntityMenuCheckMenuManagerFalse001
 *@tc.desc:Test CloseAIEntityMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CloseAIEntityMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->CloseAIEntityMenu(1);
}

/**
 *@tc.name:IsGatherWithMenuCheckMenuManagerFalse001
 *@tc.desc:Test IsGatherWithMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, IsGatherWithMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    bool ret = overlayManager->IsGatherWithMenu();
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:SetIsGatherWithMenuCheckMenuManagerFalse001
 *@tc.desc:Test SetIsGatherWithMenu when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, SetIsGatherWithMenuCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->SetIsGatherWithMenu(true);
}

/**
 *@tc.name:RemoveMenuBadgeNodeCheckMenuManagerFalse001
 *@tc.desc:Test RemoveMenuBadgeNode when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveMenuBadgeNodeCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menuWrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    overlayManager->RemoveMenuBadgeNode(menuWrapperNode);
}

/**
 *@tc.name:ShowFilterAnimationCheckMenuManagerFalse001
 *@tc.desc:Test ShowFilterAnimation when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, ShowFilterAnimationCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto columnNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));

    auto menuWrapperNode = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    overlayManager->ShowFilterAnimation(columnNode, menuWrapperNode);
}

/**
 *@tc.name:EraseMenuInfoCheckMenuManagerFalse001
 *@tc.desc:Test EraseMenuInfo when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, EraseMenuInfoCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->EraseMenuInfo(1);
}

/**
 *@tc.name:RemoveMenuInSubWindowCheckMenuManagerFalse001
 *@tc.desc:Test RemoveMenuInSubWindow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, RemoveMenuInSubWindowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    auto menuWrapper = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, 3, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    bool ret = overlayManager->RemoveMenuInSubWindow(menuWrapper);
    EXPECT_FALSE(ret);
}

/**
 *@tc.name:SkipMenuShowCheckMenuManagerFalse001
 *@tc.desc:Test SkipMenuShow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, SkipMenuShowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->SkipMenuShow(1);
}

/**
 *@tc.name:ResumeMenuShowCheckMenuManagerFalse001
 *@tc.desc:Test ResumeMenuShow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, ResumeMenuShowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->ResumeMenuShow(1);
}

/**
 *@tc.name:CheckSkipMenuShowCheckMenuManagerFalse001
 *@tc.desc:Test CheckSkipMenuShow when menuManager is null.
 *@tc.type:FUNC
 */

HWTEST_F(OverlayManagerTestThreeNg, CheckSkipMenuShowCheckMenuManagerFalse001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuManager_ = nullptr;
    overlayManager->rootNodeWeak_ = nullptr;
    bool ret = overlayManager->CheckSkipMenuShow(1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: FireAutoSave001
 * @tc.desc: Test FireAutoSave when containerNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->FireAutoSave(nullptr);
}

/**
 * @tc.name: FireAutoSave002
 * @tc.desc: Test FireAutoSave when NeedRequestAutoSave returns false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto containerNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(containerNode, nullptr);
    overlayManager->FireAutoSave(containerNode);
}

/**
 * @tc.name: FireAutoSave003
 * @tc.desc: Test FireAutoSave when NeedRequestAutoSave returns true and IsSubContainer is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto containerNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<AutoSaveTestPattern>());
    ASSERT_NE(containerNode, nullptr);
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = true;
    overlayManager->FireAutoSave(containerNode);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: FireAutoSave004
 * @tc.desc: Test FireAutoSave when NeedRequestAutoSave returns true, IsSubContainer is false,
 *           and nodeTag is not SHEET_PAGE_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto containerNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<AutoSaveTestPattern>());
    ASSERT_NE(containerNode, nullptr);
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    overlayManager->FireAutoSave(containerNode);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: FireAutoSave005
 * @tc.desc: Test FireAutoSave when NeedRequestAutoSave returns true, IsSubContainer is false,
 *           nodeTag is SHEET_PAGE_TAG, and sheetHasInstanceId is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    overlayManager->FireAutoSave(sheetNode);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: FireAutoSave006
 * @tc.desc: Test FireAutoSave when NeedRequestAutoSave returns true, IsSubContainer is false,
 *           nodeTag is SHEET_PAGE_TAG, sheetHasInstanceId is true, and targetNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t targetId = ElementRegister::GetInstance()->MakeUniqueId();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(targetId, "NonExistentTag", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.instanceId = 1;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    overlayManager->FireAutoSave(sheetNode);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: FireAutoSave007
 * @tc.desc: Test FireAutoSave when NeedRequestAutoSave returns true, IsSubContainer is false,
 *           nodeTag is SHEET_PAGE_TAG, sheetHasInstanceId is true, and targetNode is non-null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, FireAutoSave007, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t targetId = ElementRegister::GetInstance()->MakeUniqueId();
    const std::string targetTag = "TargetTag";
    auto targetNode = FrameNode::CreateFrameNode(
        targetTag, targetId, AceType::MakeRefPtr<AutoSaveTestPattern>());
    ASSERT_NE(targetNode, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(targetId, targetTag, std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.instanceId = 1;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    overlayManager->FireAutoSave(sheetNode);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: IsDescendantOfOverlay001
 * @tc.desc: Test IsDescendantOfOverlay when node has no parent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, IsDescendantOfOverlay001, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(OverlayManager::IsDescendantOfOverlay(node));
}

/**
 * @tc.name: IsDescendantOfOverlay002
 * @tc.desc: Test IsDescendantOfOverlay when parent tag is OVERLAY_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, IsDescendantOfOverlay002, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(
        V2::OVERLAY_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    parent->AddChild(child);
    EXPECT_TRUE(OverlayManager::IsDescendantOfOverlay(child));
}

/**
 * @tc.name: IsDescendantOfOverlay003
 * @tc.desc: Test IsDescendantOfOverlay when parent tag is ORDER_OVERLAY_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, IsDescendantOfOverlay003, TestSize.Level1)
{
    auto parent = FrameNode::CreateFrameNode(V2::ORDER_OVERLAY_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    parent->AddChild(child);
    EXPECT_TRUE(OverlayManager::IsDescendantOfOverlay(child));
}

/**
 * @tc.name: IsDescendantOfOverlay004
 * @tc.desc: Test IsDescendantOfOverlay when grandparent tag is OVERLAY_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, IsDescendantOfOverlay004, TestSize.Level1)
{
    auto grandparent = FrameNode::CreateFrameNode(
        V2::OVERLAY_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(grandparent, nullptr);
    auto parent = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    grandparent->AddChild(parent);
    parent->AddChild(child);
    EXPECT_TRUE(OverlayManager::IsDescendantOfOverlay(child));
}

/**
 * @tc.name: IsDescendantOfOverlay005
 * @tc.desc: Test IsDescendantOfOverlay when no ancestor has overlay tag.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, IsDescendantOfOverlay005, TestSize.Level1)
{
    auto grandparent = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(grandparent, nullptr);
    auto parent = FrameNode::CreateFrameNode(
        V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    grandparent->AddChild(parent);
    parent->AddChild(child);
    EXPECT_FALSE(OverlayManager::IsDescendantOfOverlay(child));
}

/**
 * @tc.name: ResetDetachedFreeRootProxy001
 * @tc.desc: Test ResetDetachedFreeRootProxy when detachedProxyMap_ is empty.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, ResetDetachedFreeRootProxy001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->detachedProxyMap_.clear();
    overlayManager->ResetDetachedFreeRootProxy(1);
    EXPECT_TRUE(overlayManager->detachedProxyMap_.empty());
}

/**
 * @tc.name: ResetDetachedFreeRootProxy002
 * @tc.desc: Test ResetDetachedFreeRootProxy when targetId is found in non-empty map.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, ResetDetachedFreeRootProxy002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t targetId = 100;
    auto node = FrameNode::CreateFrameNode(
        "DetachedFreeRootProxy", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    overlayManager->detachedProxyMap_[targetId] = node;
    EXPECT_EQ(overlayManager->detachedProxyMap_.size(), 1);
    overlayManager->ResetDetachedFreeRootProxy(targetId);
    EXPECT_EQ(overlayManager->detachedProxyMap_.count(targetId), 0);
    overlayManager->detachedProxyMap_.clear();
}

/**
 * @tc.name: ResetDetachedFreeRootProxy003
 * @tc.desc: Test ResetDetachedFreeRootProxy when targetId is not found in non-empty map.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, ResetDetachedFreeRootProxy003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    int32_t existingId = 100;
    int32_t nonExistingId = 200;
    auto node = FrameNode::CreateFrameNode(
        "DetachedFreeRootProxy", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    overlayManager->detachedProxyMap_[existingId] = node;
    EXPECT_EQ(overlayManager->detachedProxyMap_.size(), 1);
    overlayManager->ResetDetachedFreeRootProxy(nonExistingId);
    EXPECT_EQ(overlayManager->detachedProxyMap_.count(existingId), 1);
    EXPECT_EQ(overlayManager->detachedProxyMap_.count(nonExistingId), 0);
    overlayManager->detachedProxyMap_.clear();
}

/**
 * @tc.name: CloseImageGeneratorSheet001
 * @tc.desc: Test CloseImageGeneratorSheet when imageGeneratorSheetKey_ has no value.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
    overlayManager->modalList_.clear();
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CloseImageGeneratorSheet002
 * @tc.desc: Test CloseImageGeneratorSheet when modalList_ is empty (sheetNode stays null).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->imageGeneratorSheetKey_ = SheetKey(true, 100, 200);
    overlayManager->modalList_.clear();
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_FALSE(ret);
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
}

/**
 * @tc.name: CloseImageGeneratorSheet003
 * @tc.desc: Test CloseImageGeneratorSheet when modalList_ has a null weak pointer.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->imageGeneratorSheetKey_ = SheetKey(true, 100, 200);
    overlayManager->modalList_.clear();
    WeakPtr<FrameNode> nullWeak;
    overlayManager->modalList_.emplace_back(nullWeak);
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_FALSE(ret);
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
    overlayManager->modalList_.clear();
}

/**
 * @tc.name: CloseImageGeneratorSheet004
 * @tc.desc: Test CloseImageGeneratorSheet when modalList_ has a non-sheet-tag modal node.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->imageGeneratorSheetKey_ = SheetKey(true, 100, 200);
    overlayManager->modalList_.clear();
    auto nonSheetNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonSheetNode, nullptr);
    overlayManager->modalList_.emplace_back(AceType::WeakClaim(AceType::RawPtr(nonSheetNode)));
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_FALSE(ret);
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
    overlayManager->modalList_.clear();
}

/**
 * @tc.name: CloseImageGeneratorSheet005
 * @tc.desc: Test CloseImageGeneratorSheet when modalList_ has a sheet node with mismatched id.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->imageGeneratorSheetKey_ = SheetKey(true, 999, 200);
    overlayManager->modalList_.clear();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalList_.emplace_back(AceType::WeakClaim(AceType::RawPtr(sheetNode)));
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_FALSE(ret);
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
    overlayManager->modalList_.clear();
}

/**
 * @tc.name: CloseImageGeneratorSheet006
 * @tc.desc: Test CloseImageGeneratorSheet when matching sheet node found without mask parent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->isDismissProcess_ = true;
    int32_t sheetId = sheetNode->GetId();
    overlayManager->imageGeneratorSheetKey_ = SheetKey(true, sheetId, 200);
    overlayManager->modalList_.clear();
    overlayManager->modalList_.emplace_back(AceType::WeakClaim(AceType::RawPtr(sheetNode)));
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_TRUE(ret);
    EXPECT_FALSE(overlayManager->imageGeneratorSheetKey_.has_value());
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
    overlayManager->modalList_.clear();
}

/**
 * @tc.name: CloseImageGeneratorSheet007
 * @tc.desc: Test CloseImageGeneratorSheet when matching sheet node found with mask parent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestThreeNg, CloseImageGeneratorSheet007, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->isDismissProcess_ = true;
    auto maskNode = FrameNode::CreateFrameNode(
        "test_mask", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(maskNode, nullptr);
    sheetNode->SetParent(AceType::WeakClaim(AceType::RawPtr(maskNode)));
    maskNode->renderContext_ = nullptr;
    int32_t sheetId = sheetNode->GetId();
    overlayManager->imageGeneratorSheetKey_ = SheetKey(true, sheetId, 200);
    overlayManager->modalList_.clear();
    overlayManager->modalList_.emplace_back(AceType::WeakClaim(AceType::RawPtr(sheetNode)));
    bool ret = overlayManager->CloseImageGeneratorSheet();
    EXPECT_TRUE(ret);
    EXPECT_FALSE(overlayManager->imageGeneratorSheetKey_.has_value());
    overlayManager->imageGeneratorSheetKey_ = std::nullopt;
    overlayManager->modalList_.clear();
    sheetNode->SetParent(WeakPtr<UINode>(), false);
}
} // namespace OHOS::Ace::NG
