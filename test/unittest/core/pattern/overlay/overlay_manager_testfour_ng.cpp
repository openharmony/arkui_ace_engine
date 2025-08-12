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

#include <cstdint>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_rosen_render_context.h"
#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/subwindow/subwindow_manager.h"
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
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
const std::int32_t TARGET_ID = 1;
const std::int32_t TARGET_ID_NEW = 2;
const std::int32_t TARGET_ID_NEW_ONE = 101;
const std::int32_t TARGET_ID_NEW_TWO = 201;
const std::int32_t TARGET_ID_NEW_THREE = 3;
const std::int32_t ZERO = 0;
const std::int32_t ONE = 1;
const std::int32_t TWO = 2;
constexpr float SHEET_TOP_SAFE_AREA = 6.0f;
constexpr float SHEET_TOP_SAFE_AREA_NEW = 0.0f;
} // namespace

class OverlayManagerTestFourNg : public TestNG {
public:
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    void SetUp() override;
    void TearDown() override;

protected:
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerTestFourNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerTestFourNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayManagerTestFourNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme.Upgrade();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

/**
 * @tc.name: BindKeyboard001
 * @tc.desc: Test BindKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, BindKeyboard001, TestSize.Level1)
{
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(rootNode);
    overlayManager.customKeyboardMap_.insert({ ONE, frameNode });
    std::function<void()> keyboardBuilder = []() {};
    int32_t targetId = 1;
    size_t originalSize = overlayManager.customKeyboardMap_.size();
    overlayManager.BindKeyboard(keyboardBuilder, targetId);
    EXPECT_EQ(originalSize, overlayManager.customKeyboardMap_.size());
}

/**
 * @tc.name: BindKeyboardWithNode001
 * @tc.desc: Test BindKeyboardWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, BindKeyboardWithNode001, TestSize.Level1)
{
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(rootNode);
    overlayManager.customKeyboardMap_.insert({ TWO, frameNode });
    RefPtr<UINode> customNode;
    int32_t targetId = TARGET_ID;
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto targetNode = FrameNode::CreateFrameNode("tag", TARGET_ID_NEW, pattern, false);
    overlayManager.rootNodeWeak_ = targetNode;
    overlayManager.BindKeyboardWithNode(customNode, targetId);
    EXPECT_EQ(overlayManager.customKeyboardMap_.find(targetId), overlayManager.customKeyboardMap_.end());
}

/**
 * @tc.name: RemoveDialog001
 * @tc.desc: Test RemoveDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, RemoveDialog001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto overlay = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID_NEW_THREE, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(overlay, nullptr);
    bool ret = overlayManager->RemoveDialog(overlay, true, true);
    EXPECT_TRUE(ret);
    overlayManager->backPressEvent_ = []() { return false; };
    overlay->eventHub_ = AceType::MakeRefPtr<EventHub>();
    ret = overlayManager->RemoveDialog(overlay, true, false);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateCustomKeyboardPosition001
 * @tc.desc: Test UpdateCustomKeyboardPosition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, UpdateCustomKeyboardPosition001, TestSize.Level1)
{
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(rootNode);
    overlayManager.customKeyboardMap_.insert({ ONE, frameNode });
    overlayManager.customKeyboardMap_.insert({ TWO, nullptr });
    overlayManager.UpdateCustomKeyboardPosition();
    bool foundInvalidNode = false;
    for (const auto& pair : overlayManager.customKeyboardMap_) {
        if (pair.second == nullptr) {
            foundInvalidNode = true;
            break;
        }
    }
    EXPECT_TRUE(foundInvalidNode);
}

/**
 * @tc.name: RemoveMaskFromMap001
 * @tc.desc: Test RemoveMaskFromMap
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, RemoveMaskFromMap001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, ZERO, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(dialogNode, nullptr);
    overlayManager->maskNodeIdMap_.emplace(ONE, ONE);
    overlayManager->maskNodeIdMap_.emplace(ZERO, ZERO);
    overlayManager->maskNodeIdMap_.emplace(TWO, TWO);
    overlayManager->RemoveMaskFromMap(dialogNode);
    EXPECT_EQ(overlayManager->maskNodeIdMap_.size(), TWO);
}

/**
 * @tc.name: RemoveSheetNode001
 * @tc.desc: Test RemoveMaskFromMap
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, RemoveSheetNode001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID_NEW_THREE, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(sheetNode, nullptr);
    overlayManager->modalList_.clear();
    overlayManager->RemoveSheetNode(sheetNode);
    EXPECT_TRUE(overlayManager->modalList_.empty());
}

/**
 * @tc.name: PopTopModalNode001
 * @tc.desc: Test PopTopModalNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, PopTopModalNode001, TestSize.Level1)
{
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(rootNode);
    overlayManager.modalStack_.push(WeakPtr<FrameNode>(frameNode));
    overlayManager.PopTopModalNode();
    EXPECT_TRUE(overlayManager.modalStack_.empty());
}

/**
 * @tc.name: PopTopModalNode002
 * @tc.desc: Test PopTopModalNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, PopTopModalNode002, TestSize.Level1)
{
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(rootNode, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(rootNode);
    overlayManager.modalList_.push_back(WeakPtr<FrameNode>(frameNode));
    overlayManager.PopTopModalNode();
    EXPECT_TRUE(overlayManager.modalList_.empty());
}

/**
 * @tc.name: RemoveDragPixelMap001
 * @tc.desc: Test RemoveDragPixelMap
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, RemoveDragPixelMap001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    overlayManager->hasDragPixelMap_ = true;
    overlayManager->RemoveDragPixelMap();
    EXPECT_FALSE(overlayManager->hasDragPixelMap_);
    auto frameNode = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID_NEW_THREE, AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TEXT_TAG, MenuType::MENU));
    ASSERT_NE(frameNode, nullptr);
    overlayManager->hasDragPixelMap_ = true;
    overlayManager->dragPixmapColumnNodeWeak_ = std::move(frameNode);
    overlayManager->RemoveDragPixelMap();
    EXPECT_TRUE(overlayManager->hasDragPixelMap_);
    frameNode->renderContext_ = nullptr;
    overlayManager->RemoveDragPixelMap();
    EXPECT_TRUE(overlayManager->hasDragPixelMap_);
}

/**
 * @tc.name: DeleteModalNode001
 * @tc.desc: Test DeleteModalNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, DeleteModalNode001, TestSize.Level1)
{
    RefPtr<FrameNode> modalNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID,
        AceType::MakeRefPtr<ModalPresentationPattern>(TARGET_ID_NEW, ModalTransition::NONE, nullptr));
    ASSERT_NE(modalNode, nullptr);
    bool isModal = true;
    bool needOnWillDisappear = true;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.DeleteModalNode(TARGET_ID, modalNode, isModal, needOnWillDisappear);
    EXPECT_EQ(modalNode->GetPattern<SheetPresentationPattern>(), nullptr);
}

/**
 * @tc.name: DeleteModalNode002
 * @tc.desc: Test DeleteModalNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, DeleteModalNode002, TestSize.Level1)
{
    RefPtr<FrameNode> modalNode = AceType::MakeRefPtr<FrameNode>("STAGE", TARGET_ID,
        AceType::MakeRefPtr<ModalPresentationPattern>(TARGET_ID_NEW, ModalTransition::NONE, nullptr));
    ASSERT_NE(modalNode, nullptr);
    bool isModal = true;
    bool needOnWillDisappear = false;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, TARGET_ID, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.DeleteModalNode(TARGET_ID, modalNode, isModal, needOnWillDisappear);
    EXPECT_EQ(modalNode->GetPattern<SheetPresentationPattern>(), nullptr);
}

/**
 * @tc.name: CheckDeviceInLandscape001
 * @tc.desc: Test CheckDeviceInLandscape.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, CheckDeviceInLandscape001, TestSize.Level1)
{
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", TARGET_ID_NEW_ONE,
        AceType::MakeRefPtr<SheetPresentationPattern>(TARGET_ID_NEW_TWO, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    float sheetTopSafeArea = SHEET_TOP_SAFE_AREA;
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "auto";
    OverlayManagerTestFourNg::SetSheetTheme(sheetTheme);
    auto containerId = Container::CurrentId();
    auto foldableWindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldableWindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return false; });
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto host = sheetPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    ASSERT_NE(pipelineContext->GetTheme<SheetTheme>(), nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.CheckDeviceInLandscape(sheetStyle, sheetNode, sheetTopSafeArea);
    EXPECT_EQ(sheetTopSafeArea, SHEET_TOP_SAFE_AREA_NEW);
}

/**
 * @tc.name: CheckDeviceInLandscape002
 * @tc.desc: Test CheckDeviceInLandscape.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, CheckDeviceInLandscape002, TestSize.Level1)
{
    auto callback = [](const std::string&) {};
    RefPtr<FrameNode> sheetNode = AceType::MakeRefPtr<FrameNode>(V2::SHEET_PAGE_TAG, TARGET_ID,
        AceType::MakeRefPtr<SheetPresentationPattern>(TARGET_ID_NEW_TWO, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    float sheetTopSafeArea = SHEET_TOP_SAFE_AREA;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.CheckDeviceInLandscape(sheetStyle, sheetNode, sheetTopSafeArea);
    EXPECT_EQ(sheetTopSafeArea, SHEET_TOP_SAFE_AREA);
}

/**
 * @tc.name: CheckDeviceInLandscape003
 * @tc.desc: Test CheckDeviceInLandscape.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, CheckDeviceInLandscape003, TestSize.Level1)
{
    auto callback = [](const std::string&) {};
    RefPtr<FrameNode> sheetNode = AceType::MakeRefPtr<FrameNode>(V2::SHEET_PAGE_TAG, TARGET_ID,
        AceType::MakeRefPtr<SheetPresentationPattern>(TARGET_ID_NEW_TWO, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    float sheetTopSafeArea = SHEET_TOP_SAFE_AREA;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.CheckDeviceInLandscape(sheetStyle, sheetNode, sheetTopSafeArea);
    EXPECT_EQ(sheetTopSafeArea, SHEET_TOP_SAFE_AREA);
}

/**
 * @tc.name: CheckDeviceInLandscape004
 * @tc.desc: Test CheckDeviceInLandscape.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, CheckDeviceInLandscape004, TestSize.Level1)
{
    auto callback = [](const std::string&) {};
    RefPtr<FrameNode> sheetNode = AceType::MakeRefPtr<FrameNode>(V2::SHEET_PAGE_TAG, TARGET_ID,
        AceType::MakeRefPtr<SheetPresentationPattern>(TARGET_ID_NEW_TWO, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    SheetStyle sheetStyle;
    float sheetTopSafeArea = SHEET_TOP_SAFE_AREA;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.CheckDeviceInLandscape(sheetStyle, sheetNode, sheetTopSafeArea);
    EXPECT_EQ(sheetTopSafeArea, SHEET_TOP_SAFE_AREA);
}

/**
 * @tc.name: UpdateBindSheetByUIContext001
 * @tc.desc: Test UpdateBindSheetByUIContext.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, UpdateBindSheetByUIContext001, TestSize.Level1)
{
    RefPtr<FrameNode> sheetContentNode;
    SheetStyle sheetStyle;
    int32_t targetId = TWO;
    bool isPartialUpdate = true;
    SheetKey sheetKey;
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.UpdateBindSheetByUIContext(sheetContentNode, sheetStyle, targetId, isPartialUpdate);
    EXPECT_FALSE(overlayManager.CreateSheetKey(sheetContentNode, TARGET_ID, sheetKey));
}

/**
 * @tc.name: RemoveGatherNode001
 * @tc.desc: Test RemoveGatherNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, RemoveGatherNode001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.hasGatherNode_ = true;
    auto node = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    overlayManager.gatherNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(node));
    EXPECT_TRUE(overlayManager.gatherNodeWeak_.Upgrade() != nullptr);
    overlayManager.RemoveGatherNode();
    EXPECT_TRUE(overlayManager.hasGatherNode_);
}

/**
 * @tc.name: RemoveGatherNode002
 * @tc.desc: Test RemoveGatherNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, RemoveGatherNode002, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    overlayManager.hasGatherNode_ = true;
    overlayManager.RemoveGatherNode();
    EXPECT_FALSE(overlayManager.hasGatherNode_);
}

/**
 * @tc.name: ShowFilterDisappearAnimation001
 * @tc.desc: Test ShowFilterDisappearAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, ShowFilterDisappearAnimation001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    RefPtr<FrameNode> filterNode = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU); });
    overlayManager.ShowFilterDisappearAnimation(filterNode);
    auto callback = []() {};
    overlayManager.previewFilterTask_.Reset(callback);
    overlayManager.ShowFilterDisappearAnimation(filterNode);
    EXPECT_FALSE(overlayManager.previewFilterTask_);
}

/**
 * @tc.name: ShowFilterAnimation001
 * @tc.desc: Test ShowFilterAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, ShowFilterAnimation001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, TARGET_ID,
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, "Menu", MenuType::MENU); });
    ASSERT_NE(frameNode, nullptr);
    OverlayManager overlayManager(frameNode);
    RefPtr<FrameNode> columnNode = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ETS_TAG, 1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Menu", MenuType::MENU); });
    auto menuWrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 2, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    overlayManager.ShowFilterAnimation(columnNode, menuWrapperNode);
    auto menuWrapperPattern = menuWrapperNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(menuWrapperPattern, nullptr);
    menuWrapperPattern->hoverScaleInterruption_ = true;
    auto pipelineContext = menuWrapperNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto menuTheme = pipelineContext->GetTheme<NG::MenuTheme>();
    ASSERT_NE(menuTheme, nullptr);
    pipelineContext->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    menuTheme->hoverImageDelayDurationForInterrupt_ = 10;
    MockPipelineContext::GetCurrent()->FlushUITasks();
    overlayManager.ShowFilterAnimation(columnNode, menuWrapperNode);
    EXPECT_TRUE(overlayManager.previewFilterTask_);
}

/**
 * @tc.name: GetMainPipelineContext001
 * @tc.desc: Test GetMainPipelineContext
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, GetMainPipelineContext001, TestSize.Level1)
{
    DialogManager dialogManager;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    frameNode->MountToParent(node);
    bool isTargetNodeInSubwindow = false;
    auto pipelineContext = MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(pipelineContext);
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    RefPtr<MockContainer> containerOne = AceType::MakeRefPtr<MockContainer>();
    RefPtr<MockContainer> containerTwo = AceType::MakeRefPtr<MockContainer>();
    containerTwo->pipelineContext_ = AceType::RawPtr(pipelineContext);
    containerOne->isSubContainer_ = true;
    containerTwo->isSubContainer_ = false;
    MockContainer::Current()->GetMockDisplayInfo()->SetFoldStatus(FoldStatus::HALF_FOLD);
    AceEngine::Get().AddContainer(0, containerOne);
    AceEngine::Get().AddContainer(1, containerTwo);
    SubwindowManager::GetInstance()->AddParentContainerId(0, 1);
    auto context = dialogManager.GetMainPipelineContext(frameNode, isTargetNodeInSubwindow);
    EXPECT_EQ(context, pipelineContext);
}

/**
 * @tc.name: GetMainPipelineContext002
 * @tc.desc: Test GetMainPipelineContext
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFourNg, GetMainPipelineContext002, TestSize.Level1)
{
    DialogManager dialogManager;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    frameNode->MountToParent(node);
    bool isTargetNodeInSubwindow = true;
    auto pipelineContext = MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(pipelineContext);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    RefPtr<MockContainer> containerOne = AceType::MakeRefPtr<MockContainer>();
    containerOne->isSubContainer_ = true;
    MockContainer::Current()->GetMockDisplayInfo()->SetFoldStatus(FoldStatus::HALF_FOLD);
    AceEngine::Get().AddContainer(0, containerOne);
    auto context = dialogManager.GetMainPipelineContext(frameNode, isTargetNodeInSubwindow);
    EXPECT_EQ(context, AceType::Claim(pipeline));
}
} // namespace OHOS::Ace::NG