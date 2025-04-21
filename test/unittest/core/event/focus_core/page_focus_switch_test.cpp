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
#include "test/mock/core/common/mock_resource_adapter.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/unittest/core/event/focus_core/focus_test_base.h"
#include "test/unittest/core/event/focus_core/page_focus_switch_test.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/flex/flex_element.h"
#include "core/components/theme/theme_constants.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#include "core/event/focus_axis_event.h"
#include "core/event/key_event.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

struct PageFocusSwitchCase {
    std::string newPageType;
    bool isAutoFocusTransfer;
    bool isHasDefaultFocus;
    bool expectResults;
    PageFocusSwitchCase(
        const std::string& newPageType, bool isAutoFocusTransfer, bool isHasDefaultFocus, bool expectResults)
        : newPageType(newPageType), isAutoFocusTransfer(isAutoFocusTransfer), isHasDefaultFocus(isHasDefaultFocus),
          expectResults(expectResults)
    {}
};

const std::vector<PageFocusSwitchCase> PAGE_FOCUS_SWITCH_CASE = { PageFocusSwitchCase("page", true, true, true),
    PageFocusSwitchCase("page", true, false, true), PageFocusSwitchCase("dialog", true, true, true),
    PageFocusSwitchCase("menu", true, true, true), PageFocusSwitchCase("popup", true, true, true),
    PageFocusSwitchCase("modalpage", true, true, true), PageFocusSwitchCase("sheetpag", true, true, true),
    PageFocusSwitchCase("navigation", true, true, true), PageFocusSwitchCase("navbar", true, true, true),
    PageFocusSwitchCase("navdestination", true, true, true), PageFocusSwitchCase("windowscene", true, true, true) };

void PageFocusSwitchTestNG::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    GTEST_LOG_(INFO) << "PageFocusSwitchTestNG SetUpTestCase";
}

void PageFocusSwitchTestNG::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    GTEST_LOG_(INFO) << "PageFocusSwitchTestNG TearDownTestCase";
}

HWTEST_F(PageFocusSwitchTestNG, FocusWindowTestNG001, TestSize.Level1)
{
    int32_t caseNum = 1;
    bool initResult = InitFocusTestBaseNG();
    EXPECT_TRUE(initResult);
    for (const auto& testCase : PAGE_FOCUS_SWITCH_CASE) {
        // get newPageType and creat node tree
        if (testCase.newPageType == "Page") {
            // creat root node
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            // creat node
            auto oldpagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
            auto oldPageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, oldpagePattern);
            auto oldFocusHub = oldPageNode->GetOrCreateFocusHub();
            rootNode->AddChild(oldPageNode);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newpagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
            auto newPageNode = FrameNodeOnTree::CreateFrameNode(V2::PAGE_ETS_TAG, -1, newpagePattern);
            auto newFocusHub = newPageNode->GetOrCreateFocusHub();
            oldPageNode->AddChild(newPageNode);
            // set default focus
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            // check old node lost focus ,new node get focus
            auto currentFocusNode = focusManager_->GetFocusManager(newPageNode);
            EXPECT_EQ(oldPageNode, currentFocusNode);
            EXPECT_NE(newPageNode, currentFocusNode);
        } else if (testCase.newPageType == "dialog") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto dialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
            auto oldDialogNode = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, -1, dialogPattern);
            auto oldFocusHub = oldDialogNode->GetOrCreateFocusHub();
            rootNode->AddChild(oldDialogNode);
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newdialogPattern = AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr);
            auto newDialogNode = FrameNodeOnTree::CreateFrameNode(V2::DIALOG_ETS_TAG, -1, newdialogPattern);
            auto newFocusHub = newDialogNode->GetOrCreateFocusHub();
            oldDialogNode->AddChild(newDialogNode);

            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newDialogNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldDialogNode, currentFocusNode);
            EXPECT_NE(newDialogNode, currentFocusNode);

        } else if (testCase.newPageType == "menu") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto menuPattern = AceType::MakeRefPtr<MenuPattern>(-1, "Menu", MenuType::MENU);
            auto oldMenuNode = FrameNodeOnTree::CreateFrameNode(V2::MENU_ETS_TAG, -1, menuPattern);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldMenuNode->GetOrCreateFocusHub();
            rootNode->AddChild(oldMenuNode);
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newMenuNode = FrameNodeOnTree::CreateFrameNode(V2::MENU_ETS_TAG, -1, menuPattern);
            auto newFocusHub = newMenuNode->GetOrCreateFocusHub();
            oldMenuNode->AddChild(newMenuNode);
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newMenuNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldMenuNode, currentFocusNode);
            EXPECT_NE(newMenuNode, currentFocusNode);
        } else if (testCase.newPageType == "popup") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto bubblePattern = AceType::MakeRefPtr<BubblePattern>();
            auto oldPopupNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, -1, bubblePattern);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldPopupNode->GetOrCreateFocusHub();
            rootNode->AddChild(oldPopupNode);
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newPopupNode = FrameNodeOnTree::CreateFrameNode(V2::POPUP_ETS_TAG, -1, bubblePattern);
            auto newFocusHub = newPopupNode->GetOrCreateFocusHub();
            oldPopupNode->AddChild(newPopupNode);
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newPopupNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldPopupNode, currentFocusNode);
            EXPECT_NE(newPopupNode, currentFocusNode);
        } else if (testCase.newPageType == "modalpage") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto modalPattern = AceType::MakeRefPtr<ModalPresentationPattern>(-1, ModalTransition::DEFAULT, nullptr);
            auto oldModelpageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPattern);
            rootNode->AddChild(oldModelpageNode);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldModelpageNode->GetOrCreateFocusHub();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newModelpageNode = FrameNodeOnTree::CreateFrameNode(V2::MODAL_PAGE_TAG, -1, modalPattern);
            oldModelpageNode->AddChild(newModelpageNode);
            auto newFocusHub = newModelpageNode->GetOrCreateFocusHub();
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newModelpageNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldModelpageNode, currentFocusNode);
            EXPECT_NE(newModelpageNode, currentFocusNode);
        } else if (testCase.newPageType == "sheetpag") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto sheetPattern = AceType::MakeRefPtr<SheetPresentationPattern>(-1, "", nullptr);
            auto oldSheetpageNode = FrameNodeOnTree::CreateFrameNode(V2::SHEET_PAGE_TAG, -1, sheetPattern);
            rootNode->AddChild(oldSheetpageNode);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldSheetpageNode->GetOrCreateFocusHub();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newSheetpageNode = FrameNodeOnTree::CreateFrameNode(V2::SHEET_PAGE_TAG, -1, sheetPattern);
            oldSheetpageNode->AddChild(newSheetpageNode);
            auto newFocusHub = newSheetpageNode->GetOrCreateFocusHub();
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newSheetpageNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldSheetpageNode, currentFocusNode);
            EXPECT_NE(newSheetpageNode, currentFocusNode);
        } else if (testCase.newPageType == "navigation") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto navigationPattern = AceType::MakeRefPtr<NavigationPattern>();
            auto oldNavigationNode =
                FrameNodeOnTree::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, -1, navigationPattern);
            rootNode->AddChild(oldNavigationNode);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldNavigationNode->GetOrCreateFocusHub();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newNavigationNode =
                FrameNodeOnTree::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, -1, navigationPattern);
            oldNavigationNode->AddChild(newNavigationNode);
            auto newFocusHub = newNavigationNode->GetOrCreateFocusHub();
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newNavigationNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldNavigationNode, currentFocusNode);
            EXPECT_NE(newNavigationNode, currentFocusNode);

        } else if (testCase.newPageType == "navbar") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto navbarPattern = AceType::MakeRefPtr<NavBarPattern>();
            auto oldNavbarNode = FrameNodeOnTree::CreateFrameNode(V2::NAVBAR_ETS_TAG, -1, navbarPattern);
            rootNode->AddChild(oldNavbarNode);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldNavbarNode->GetOrCreateFocusHub();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newNavbarNode = FrameNodeOnTree::CreateFrameNode(V2::NAVBAR_ETS_TAG, -1, navbarPattern);
            oldNavbarNode->AddChild(newNavbarNode);
            auto newFocusHub = newNavbarNode->GetOrCreateFocusHub();
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newNavbarNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldNavbarNode, currentFocusNode);
            EXPECT_NE(newNavbarNode, currentFocusNode);
        } else if (testCase.newPageType == "navdestination") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto navdestinationPattern = AceType::MakeRefPtr<NavDestinationPattern>(nullptr);
            auto oldNavdestinationNode =
                FrameNodeOnTree::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, -1, navdestinationPattern);
            rootNode->AddChild(oldNavdestinationNode);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldNavdestinationNode->GetOrCreateFocusHub();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newNavdestinationNode =
                FrameNodeOnTree::CreateFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, -1, navdestinationPattern);
            oldNavdestinationNode->AddChild(newNavdestinationNode);
            auto newFocusHub = newNavdestinationNode->GetOrCreateFocusHub();
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newNavdestinationNode);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldNavdestinationNode, currentFocusNode);
            EXPECT_NE(newNavdestinationNode, currentFocusNode);

        } else if (testCase.newPageType == "windowscene") {
            auto rootNode = FrameNodeOnTree::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
            auto rootFocusHub = rootNode->GetOrCreateFocusHub();
            auto windowscenePattern = AceType::MakeRefPtr<Pattern>();
            auto oldWindowscene = FrameNodeOnTree::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, -1, windowscenePattern);
            rootNode->AddChild(oldWindowscene);
            auto focusManager = PipelineContext::GetCurrentContext()->GetFocusManager();
            auto oldFocusHub = oldWindowscene->GetOrCreateFocusHub();
            if (testCase.isAutoFocusTransfer) {
                auto delegate = EngineHelper::GetCurrentDelegateSafely();
                CHECK_NULL_VOID(delegate);
                delegate->SetAutoFocusTransfer(testCase.isAutoFocusTransfer);
            }
            auto newWindowscene = FrameNodeOnTree::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, -1, windowscenePattern);
            auto newFocusHub = newWindowscene->GetOrCreateFocusHub();
            oldWindowscene->AddChild(newWindowscene);
            if (testCase.isHasDefaultFocus) {
                oldFocusHub->SetDefaultFocusNode(newFocusHub);
            }
            auto currentFocusNode = focusManager_->GetFocusManager(newWindowscene);
            CHECK_NULL_VOID(currentFocusNode);
            EXPECT_EQ(oldWindowscene, currentFocusNode);
            EXPECT_NE(newWindowscene, currentFocusNode);
        }
        ++caseNum;
    }
}
} // namespace OHOS::Ace::NG
