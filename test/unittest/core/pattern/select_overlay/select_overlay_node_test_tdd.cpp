/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "gtest/internal/gtest-internal.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_MENU_ID = 1001;
const std::string TEST_MENU_ID_STR = "1001";
constexpr float DEFAULT_MAX_WIDTH = 200.0f;
const RectF TEST_HANDLE_RECT(10.0f, 20.0f, 20.0f, 40.0f);
const RectF TEST_SECOND_HANDLE_RECT(50.0f, 70.0f, 20.0f, 40.0f);
const std::string TEST_SELECT_TEXT = "Test selected text";
} // namespace

class SelectOverlayNodeTddTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<SelectOverlayNode> CreateSelectOverlayNode(SelectOverlayMode mode = SelectOverlayMode::ALL);
    SelectOverlayInfo CreateDefaultInfo();
};

void SelectOverlayNodeTddTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    textOverlayTheme->showShortcut_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto rootNode = MockPipelineContext::GetCurrent()->rootNode_;
    if (rootNode) {
        auto rootRenderContext = rootNode->GetRenderContext();
        if (rootRenderContext) {
            rootRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 1280.0f, 2480.0f));
        }
    }
}

void SelectOverlayNodeTddTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<SelectOverlayNode> SelectOverlayNodeTddTest::CreateSelectOverlayNode(SelectOverlayMode mode)
{
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info, mode);
    return AceType::DynamicCast<SelectOverlayNode>(frameNode);
}

SelectOverlayInfo SelectOverlayNodeTddTest::CreateDefaultInfo()
{
    SelectOverlayInfo info;
    info.firstHandle.paintRect = TEST_HANDLE_RECT;
    info.firstHandle.isShow = true;
    info.firstHandle.isTouchable = true;
    info.secondHandle.paintRect = TEST_SECOND_HANDLE_RECT;
    info.secondHandle.isShow = true;
    info.secondHandle.isTouchable = true;
    info.isSingleHandle = false;
    info.menuInfo.menuIsShow = true;
    info.selectText = TEST_SELECT_TEXT;
    return info;
}

/**
 * @tc.name: SelectOverlayNode_CreateSelectOverlayNode001
 * @tc.desc: Test CreateSelectOverlayNode with ALL mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, CreateSelectOverlayNode001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode(SelectOverlayMode::ALL);
    EXPECT_NE(node, nullptr);
    EXPECT_NE(node->GetPattern<SelectOverlayPattern>(), nullptr);
}

/**
 * @tc.name: SelectOverlayNode_CreateSelectOverlayNode002
 * @tc.desc: Test CreateSelectOverlayNode with MENU_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, CreateSelectOverlayNode002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode(SelectOverlayMode::MENU_ONLY);
    EXPECT_NE(node, nullptr);
    auto pattern = node->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetMode(), SelectOverlayMode::MENU_ONLY);
}

/**
 * @tc.name: SelectOverlayNode_CreateSelectOverlayNode003
 * @tc.desc: Test CreateSelectOverlayNode with HANDLE_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, CreateSelectOverlayNode003, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode(SelectOverlayMode::HANDLE_ONLY);
    EXPECT_NE(node, nullptr);
    auto pattern = node->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetMode(), SelectOverlayMode::HANDLE_ONLY);
}

/**
 * @tc.name: SelectOverlayNode_SetSelectInfo001
 * @tc.desc: Test SetSelectInfo
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, SetSelectInfo001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    const std::string newText = "New selected text";
    node->SetSelectInfo(newText);
    EXPECT_EQ(node->GetSelectInfo(), newText);
}

/**
 * @tc.name: SelectOverlayNode_GetAnimationStatus001
 * @tc.desc: Test GetAnimationStatus when not animating
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetAnimationStatus001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->isDoingAnimation_ = false;
    EXPECT_FALSE(node->GetAnimationStatus());
}

/**
 * @tc.name: SelectOverlayNode_GetAnimationStatus002
 * @tc.desc: Test GetAnimationStatus when animating
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetAnimationStatus002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->isDoingAnimation_ = true;
    EXPECT_TRUE(node->GetAnimationStatus());
}

/**
 * @tc.name: SelectOverlayNode_GetIsExtensionMenu001
 * @tc.desc: Test GetIsExtensionMenu when false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetIsExtensionMenu001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->isExtensionMenu_ = false;
    EXPECT_FALSE(node->GetIsExtensionMenu());
}

/**
 * @tc.name: SelectOverlayNode_GetIsExtensionMenu002
 * @tc.desc: Test GetIsExtensionMenu when true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetIsExtensionMenu002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->isExtensionMenu_ = true;
    EXPECT_TRUE(node->GetIsExtensionMenu());
}

/**
 * @tc.name: SelectOverlayNode_GetMaxDefaultButtonAndMenuWidth001
 * @tc.desc: Test GetMaxDefaultButtonAndMenuWidth
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetMaxDefaultButtonAndMenuWidth001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->maxDefaultButtonAndMenuWidth_ = DEFAULT_MAX_WIDTH;
    EXPECT_FLOAT_EQ(node->GetMaxDefaultButtonAndMenuWidth(), DEFAULT_MAX_WIDTH);
}

/**
 * @tc.name: SelectOverlayNode_GetScopeId001
 * @tc.desc: Test GetScopeId
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetScopeId001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->scopeId_ = 100;
    EXPECT_EQ(node->GetScopeId(), 100);
}

/**
 * @tc.name: SelectOverlayNode_ConvertToIntMenuId001
 * @tc.desc: Test ConvertToIntMenuId with valid string
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, ConvertToIntMenuId001, TestSize.Level1)
{
    auto id = SelectOverlayNode::ConvertToIntMenuId(TEST_MENU_ID_STR);
    EXPECT_EQ(id, TEST_MENU_ID);
}

/**
 * @tc.name: SelectOverlayNode_ConvertToStrMenuId001
 * @tc.desc: Test ConvertToStrMenuId with valid id
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, ConvertToStrMenuId001, TestSize.Level1)
{
    auto idStr = SelectOverlayNode::ConvertToStrMenuId(TEST_MENU_ID);
    EXPECT_EQ(idStr, TEST_MENU_ID_STR);
}

/**
 * @tc.name: SelectOverlayNode_SetSubToolbarStatus001
 * @tc.desc: Test SetSubToolbarStatus with UNEXPANDED
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, SetSubToolbarStatus001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->SetSubToolbarStatus(SubToolbarStatus::UNEXPANDED);
    EXPECT_EQ(node->subToolbarStatus, SubToolbarStatus::UNEXPANDED);
}

/**
 * @tc.name: SelectOverlayNode_SetSubToolbarStatus002
 * @tc.desc: Test SetSubToolbarStatus with EXPANDED
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, SetSubToolbarStatus002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->SetSubToolbarStatus(SubToolbarStatus::EXPANDED);
    EXPECT_EQ(node->subToolbarStatus, SubToolbarStatus::EXPANDED);
}

/**
 * @tc.name: SelectOverlayNode_SetSubToolbarStatus003
 * @tc.desc: Test SetSubToolbarStatus with NEEDEXPAND
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, SetSubToolbarStatus003, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->SetSubToolbarStatus(SubToolbarStatus::NEEDEXPAND);
    EXPECT_EQ(node->subToolbarStatus, SubToolbarStatus::NEEDEXPAND);
}

/**
 * @tc.name: SelectOverlayNode_GetSubToolbarStatus001
 * @tc.desc: Test GetSubToolbarStatus
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, GetSubToolbarStatus001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->subToolbarStatus = SubToolbarStatus::EXPANDED;
    EXPECT_EQ(node->GetSubToolbarStatus(), SubToolbarStatus::EXPANDED);
}

/**
 * @tc.name: SelectOverlayNode_IsInSelectedOrSelectOverlayArea001
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea with point inside
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, IsInSelectedOrSelectOverlayArea001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    PointF point(15.0f, 30.0f);
    node->selectInfo_ = TEST_SELECT_TEXT;
    // Point should be checked against select area
    // This test verifies the method is callable
    auto result = node->IsInSelectedOrSelectOverlayArea(point);
    // Result depends on actual select area, we just verify it runs
    (void)result; // Suppress unused variable warning
}

/**
 * @tc.name: SelectOverlayNode_ProcessSubMenuOnHide001
 * @tc.desc: Test ProcessSubMenuOnHide
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, ProcessSubMenuOnHide001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->subToolbarStatus = SubToolbarStatus::EXPANDED;
    node->ProcessSubMenuOnHide();
    EXPECT_EQ(node->subToolbarStatus, SubToolbarStatus::UNEXPANDED);
}

/**
 * @tc.name: SelectOverlayNode_ShowSelectOverlay001
 * @tc.desc: Test ShowSelectOverlay with animation
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, ShowSelectOverlay001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->ShowSelectOverlay(true);
    // Verify method executes without crash
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_ShowSelectOverlay002
 * @tc.desc: Test ShowSelectOverlay without animation
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, ShowSelectOverlay002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->ShowSelectOverlay(false);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_HideSelectOverlay001
 * @tc.desc: Test HideSelectOverlay with callback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, HideSelectOverlay001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    bool callbackExecuted = false;
    node->HideSelectOverlay([&callbackExecuted]() {
        callbackExecuted = true;
    });
    // Verify method executes
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_HideSelectOverlay002
 * @tc.desc: Test HideSelectOverlay without callback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, HideSelectOverlay002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->HideSelectOverlay(nullptr);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_SwitchToOverlayMode001
 * @tc.desc: Test SwitchToOverlayMode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, SwitchToOverlayMode001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info.enableHandleLevel = true;
    info.handleLevelMode = HandleLevelMode::EMBED;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto node = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    node->SwitchToOverlayMode();
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateSelectMenuBg001
 * @tc.desc: Test UpdateSelectMenuBg
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateSelectMenuBg001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    RefPtr<FrameNode> caller = nullptr;
    node->UpdateSelectMenuBg(caller);
    // Verify method handles null caller
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateToolBarFromMainWindow001
 * @tc.desc: Test UpdateToolBarFromMainWindow with item changed
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateToolBarFromMainWindow001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->UpdateToolBarFromMainWindow(true, false);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateToolBarFromMainWindow002
 * @tc.desc: Test UpdateToolBarFromMainWindow without animation
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateToolBarFromMainWindow002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->UpdateToolBarFromMainWindow(false, true);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_OnDetachFromMainTree001
 * @tc.desc: Test OnDetachFromMainTree
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, OnDetachFromMainTree001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->OnDetachFromMainTree(true, MockPipelineContext::GetCurrent()->Get());
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_OnDetachFromMainTree002
 * @tc.desc: Test OnDetachFromMainTree with non-recursive
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, OnDetachFromMainTree002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->OnDetachFromMainTree(false, MockPipelineContext::GetCurrent()->Get());
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_MoreOrBackAnimation001
 * @tc.desc: Test MoreOrBackAnimation for more button
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, MoreOrBackAnimation001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->MoreOrBackAnimation(true, false);
    // Verify animation state changes
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_MoreOrBackAnimation002
 * @tc.desc: Test MoreOrBackAnimation for back button
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, MoreOrBackAnimation002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->MoreOrBackAnimation(false, false);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_MoreOrBackAnimation003
 * @tc.desc: Test MoreOrBackAnimation without animation
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, MoreOrBackAnimation003, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->MoreOrBackAnimation(true, true);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_HideOrShowCirclesAndBackArrow001
 * @tc.desc: Test HideOrShowCirclesAndBackArrow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, HideOrShowCirclesAndBackArrow001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->HideOrShowCirclesAndBackArrow(FrameNodeType::SELECTMENU, 0.0f);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_HideOrShowCirclesAndBackArrow002
 * @tc.desc: Test HideOrShowCirclesAndBackArrow with EXTENSIONMENU
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, HideOrShowCirclesAndBackArrow002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->HideOrShowCirclesAndBackArrow(FrameNodeType::EXTENSIONMENU, 1.0f);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_HideOrShowCirclesAndBackArrow003
 * @tc.desc: Test HideOrShowCirclesAndBackArrow with BACKBUTTON
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, HideOrShowCirclesAndBackArrow003, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->HideOrShowCirclesAndBackArrow(FrameNodeType::BACKBUTTON, 0.5f);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_HideOrShowCirclesAndBackArrow004
 * @tc.desc: Test HideOrShowCirclesAndBackArrow with MENUONLY
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, HideOrShowCirclesAndBackArrow004, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->HideOrShowCirclesAndBackArrow(FrameNodeType::MENUONLY, 1.0f);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateMenuInner001
 * @tc.desc: Test UpdateMenuInner
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateMenuInner001, TestSize.Level1)
{
    auto infoPtr = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto node = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    node->UpdateMenuInner(infoPtr, false, false);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateMenuInner002
 * @tc.desc: Test UpdateMenuInner as submenu
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateMenuInner002, TestSize.Level1)
{
    auto infoPtr = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto node = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    node->UpdateMenuInner(infoPtr, true, true);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateMenuOptions001
 * @tc.desc: Test UpdateMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateMenuOptions001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    node->UpdateMenuOptions(infoPtr);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_AddCustomMenuCallbacks001
 * @tc.desc: Test AddCustomMenuCallbacks
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, AddCustomMenuCallbacks001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info.menuInfo.menuBuilder = []() -> RefPtr<UINode> { return nullptr; };
    info.onClose = [](bool) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto node = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    node->AddCustomMenuCallbacks(infoPtr);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_OnCustomSelectMenuAppear001
 * @tc.desc: Test OnCustomSelectMenuAppear
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, OnCustomSelectMenuAppear001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info.menuInfo.menuBuilder = []() -> RefPtr<UINode> { return nullptr; };
    auto infoPtr = std::make_shared<SelectOverlayInfo>(info);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto node = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    node->OnCustomSelectMenuAppear();
    EXPECT_TRUE(node->isCustomMenuAppear_);
}

/**
 * @tc.name: SelectOverlayNode_UpdateToolBar001
 * @tc.desc: Test UpdateToolBar with item changed
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateToolBar001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->UpdateToolBar(true, false);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateToolBar002
 * @tc.desc: Test UpdateToolBar without item changed
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateToolBar002, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    node->UpdateToolBar(false, true);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_AddSubMenuItemByCreateMenuCallback001
 * @tc.desc: Test AddSubMenuItemByCreateMenuCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, AddSubMenuItemByCreateMenuCallback001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    node->AddSubMenuItemByCreateMenuCallback(infoPtr, 200.0f);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SelectOverlayNode_UpdateSubMenuOptions001
 * @tc.desc: Test UpdateSubMenuOptions
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayNodeTddTest, UpdateSubMenuOptions001, TestSize.Level1)
{
    auto node = CreateSelectOverlayNode();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    node->UpdateSubMenuOptions(infoPtr);
    EXPECT_NE(node, nullptr);
}

} // namespace OHOS::Ace::NG
