/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <cstddef>
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/error/error_code.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "base/window/foldable_window.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components/toast/toast_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/app_bar/app_bar_theme.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"
#include "core/common/app_bar_helper.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

namespace {
const NG::BorderColorProperty BORDER_COLOR_TEST = { Color::BLUE,
    Color::BLUE, Color::BLUE, Color::BLUE };
const std::string TEXT_TAG = "text";
const std::string MESSAGE = "hello world";
const std::string BOTTOMSTRING = "test";
constexpr int32_t DURATION = 2;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const OffsetF DRAG_OFFSET_BEGIN(10.0, 10.0);
const OffsetF DRAG_OFFSET_END(15.0, 15.0);
constexpr float PIXELMAP_DRAG_SCALE = 1.0f;
const double REMOVE_ANIMATION_X = 0;
const double REMOVE_ANIMATION_Y = 1;
const int32_t DEFAULT_INSTANCE_ID = 0;
const OffsetF DRAG_PREVIEW_OFFSET(5.0, 5.0);
} // namespace

class OverlayManagerExtendTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateBubbleNode(const TestProperty& testProperty);
    static RefPtr<FrameNode> CreateTargetNode();
    static void CreateSheetStyle(SheetStyle& sheetStyle);
    void CreateSheetBuilder();
    int32_t minPlatformVersion_ = 0;
};

void OverlayManagerExtendTestNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

void OverlayManagerExtendTestNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
}

void OverlayManagerExtendTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_ELEVEN);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DragBarTheme::TypeId()) {
            return AceType::MakeRefPtr<DragBarTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return AceType::MakeRefPtr<PickerTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        } else if (type == MenuTheme::TypeId()) {
            return AceType::MakeRefPtr<MenuTheme>();
        } else if (type == ToastTheme::TypeId()) {
            return AceType::MakeRefPtr<ToastTheme>();
        } else if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}
void OverlayManagerExtendTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> OverlayManagerExtendTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

/**
 * @tc.name: OverlayManagerExtendTest001
 * @tc.desc: Test OverlayManager::SetNodeBeforeAppbar.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    /**
     * @tc.steps: step2. create overlayManager and call ShowDialog.
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    /**
     * @tc.steps: step3. create a uinode and an other node and test SetNodeBeforeAppbar.
     * @tc.expected: DialogNode created successfully
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 10, AceType::MakeRefPtr<RootPattern>());
    auto childFst =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 11, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto childScd = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto childNodeFst =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 13, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    auto childNodeScd = FrameNode::CreateFrameNode(V2::APP_BAR_ETS_TAG, 14, AceType::MakeRefPtr<Pattern>());
    auto otherNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 14, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    childFst->MountToParent(rootNode);
    childScd->MountToParent(rootNode);
    childNodeFst->MountToParent(childScd);
    childNodeScd->MountToParent(childScd);
    overlayManager->SetNodeBeforeAppbar(rootNode, otherNode);
    auto child = rootNode->GetChildAtIndex(0);
    EXPECT_EQ(child->GetTag(), V2::MENU_ETS_TAG);
}

/**
 * @tc.name: OverlayManagerExtendTest002
 * @tc.desc: Test OverlayManager::UpdatePixelMapPosition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    /**
     * @tc.steps: step1+. call UpdatePixelMapPosition and isSubwindowOverlay is false.
     * @tc.expected: DialogNode created successfully
     */
    overlayManager->UpdatePixelMapPosition(false);
    overlayManager->hasPixelMap_ = true;
    overlayManager->UpdatePixelMapPosition(false);
    /**
     * @tc.steps: step2. call UpdatePixelMapPosition and isSubwindowOverlay is true.
     * @tc.expected: DialogNode created successfully
     */
    overlayManager->hasPixelMap_ = false;
    overlayManager->UpdatePixelMapPosition(true);
    overlayManager->hasPixelMap_ = true;
    overlayManager->dragMoveVector_ = DRAG_OFFSET_BEGIN;
    overlayManager->lastDragMoveVector_ = DRAG_OFFSET_BEGIN;
    overlayManager->UpdatePixelMapPosition(true);
    EXPECT_FALSE(overlayManager->IsOriginDragMoveVector());
    EXPECT_TRUE(!overlayManager->IsUpdateDragMoveVector());
    /**
     * @tc.steps: step2+. call UpdatePixelMapPosition and isSubwindowOverlay is true.
     * @tc.expected: DialogNode created successfully
     */
    overlayManager->dragMoveVector_ = DRAG_OFFSET_BEGIN;
    overlayManager->lastDragMoveVector_ = DRAG_OFFSET_END;
    overlayManager->UpdatePixelMapPosition(true);
    EXPECT_FALSE(overlayManager->IsOriginDragMoveVector());
    EXPECT_FALSE(!overlayManager->IsUpdateDragMoveVector());
}

/**
 * @tc.name: OverlayManagerExtendTest003
 * @tc.desc: Test OverlayManager::MarkDirtyOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call MarkDirtyOverlay.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto child = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, 2, AceType::MakeRefPtr<Pattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    child->MountToParent(overlayNode);
    overlayManager->MarkDirtyOverlay();
    /**
     * @tc.steps: step1+. call UpdatePixelMapPosition and isSubwindowOverlay is true.
     * @tc.expected: DialogNode created successfully
     */
    auto overlayNodeEx = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto childLast = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG, 2, AceType::MakeRefPtr<Pattern>());
    auto childEx = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 3, AceType::MakeRefPtr<Pattern>());
    childLast->MountToParent(overlayNodeEx);
    childEx->MountToParent(childLast);
    auto overlayManagerEx = AceType::MakeRefPtr<OverlayManager>(overlayNodeEx);
    overlayManagerEx->MarkDirtyOverlay();
    EXPECT_NE(overlayNode->GetLastChild(), nullptr);
}

/**
 * @tc.name: OverlayManagerExtendTest004
 * @tc.desc: Test OverlayManager::DeleteUIExtensionNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call DeleteUIExtensionNode.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto UIExtNodeFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto UIExtNodeScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto UIExtNodeThd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->uiExtNodes_.emplace(1, AceType::WeakClaim(AceType::RawPtr(UIExtNodeFst)));
    overlayManager->uiExtNodes_.emplace(2, AceType::WeakClaim(AceType::RawPtr(UIExtNodeFst)));
    overlayManager->uiExtNodes_.emplace(3, AceType::WeakClaim(AceType::RawPtr(UIExtNodeFst)));
    overlayManager->DeleteUIExtensionNode(1);
    EXPECT_EQ(overlayManager->uiExtNodes_.size(), 2);
    overlayManager->DeleteUIExtensionNode(3);
    EXPECT_EQ(overlayManager->uiExtNodes_.size(), 1);
}

/**
 * @tc.name: OverlayManagerExtendTest005
 * @tc.desc: Test1 OverlayManager::UpdatePixelMapScale.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call UpdatePixelMapScale.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    auto hub = columnNode->GetOrCreateGestureEventHub();
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    hub->SetPixelMap(pixelMap);
    float scale = PIXELMAP_DRAG_SCALE;
    overlayManager->UpdatePixelMapScale(scale);
    auto gestureHub = columnNode->GetOrCreateGestureEventHub();
    RefPtr<PixelMap> pixel = gestureHub->GetPixelMap();
    EXPECT_EQ(pixel->GetHeight(), 0);
    EXPECT_EQ(pixel->GetWidth(), 0);
}
/**
 * @tc.name: OverlayManagerExtendTest006
 * @tc.desc: Test2 OverlayManager::UpdatePixelMapScale.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call UpdatePixelMapScale.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    auto hub = columnNode->GetOrCreateGestureEventHub();
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    hub->SetPixelMap(pixelMap);
    float scale = PIXELMAP_DRAG_SCALE;
    overlayManager->UpdatePixelMapScale(scale);
    auto gestureHub = columnNode->GetOrCreateGestureEventHub();
    RefPtr<PixelMap> pixel = gestureHub->GetPixelMap();
    EXPECT_EQ(pixel->GetHeight(), 0);
    EXPECT_EQ(pixel->GetWidth(), 0);
}
/**
 * @tc.name: OverlayManagerExtendTest007
 * @tc.desc: Test OverlayManager::RemovePixelMapAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call RemovePixelMapAnimation.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    overlayManager->RemovePixelMapAnimation(true, REMOVE_ANIMATION_X, REMOVE_ANIMATION_Y);
    /**
     * @tc.steps: step2. isOnAnimation_ false and hasPixelMap_ is false call UpdatePixelMapScale.
     */
    overlayManager->SetIsOnAnimation(true);
    overlayManager->RemovePixelMapAnimation(false, REMOVE_ANIMATION_X, REMOVE_ANIMATION_Y);
    overlayManager->SetHasPixelMap(true);
    overlayManager->RemovePixelMapAnimation(true, REMOVE_ANIMATION_X, REMOVE_ANIMATION_Y);
    EXPECT_TRUE(overlayManager->GetIsOnAnimation());
    EXPECT_TRUE(overlayManager->GetHasPixelMap());
    overlayManager->SetIsOnAnimation(false);
    overlayManager->RemovePixelMapAnimation(false, REMOVE_ANIMATION_X, REMOVE_ANIMATION_Y);
    EXPECT_FALSE(overlayManager->GetIsOnAnimation());
    EXPECT_FALSE(overlayManager->GetHasPixelMap());
    /**
     * @tc.steps: step3. create pixmapColumnNodeWeak_ and reset hasPixelMap_ is true call UpdatePixelMapScale.
     */
    overlayManager->SetHasPixelMap(true);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));
    overlayManager->RemovePixelMapAnimation(true, REMOVE_ANIMATION_X, REMOVE_ANIMATION_Y);
    overlayManager->RemovePixelMapAnimation(true, REMOVE_ANIMATION_X, REMOVE_ANIMATION_Y, true);
    EXPECT_TRUE(overlayManager->GetHasPixelMap());
}

/**
 * @tc.name: OverlayManagerExtendTest008
 * @tc.desc: Test OverlayManager::BindKeyboardWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call RemovePixelMapAnimation.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    /**
     * @tc.steps: step2. isOnAnimation_ false and hasPixelMap_ is false call UpdatePixelMapScale.
     */
    auto keyboardThd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->BindKeyboardWithNode(keyboardThd, 0);
    auto keyboardFst = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    auto keyboardScd = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    overlayManager->customKeyboardMap_.emplace(1, AceType::RawPtr(keyboardFst));
    overlayManager->customKeyboardMap_.emplace(2, AceType::RawPtr(keyboardScd));
    overlayManager->BindKeyboardWithNode(keyboardThd, 1);
    overlayManager->BindKeyboardWithNode(keyboardThd, 2);
    EXPECT_NE(overlayManager->rootNodeWeak_.Upgrade(), nullptr);
}

/**
 * @tc.name: OverlayManagerExtendTest009
 * @tc.desc: Test OverlayManager::ReloadBuilderNodeConfig.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call RemovePixelMapAnimation.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    overlayManager->ReloadBuilderNodeConfig();
    EXPECT_EQ(overlayManager->GetDialogMap().size(), 0);
    /**
     * @tc.steps: step2. create dialogMap_  and call ReloadBuilderNodeConfig.
     */
    auto dialogNodeFst = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    auto dialogNodeScd = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    auto dialogNodeThd = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 3, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    overlayManager->dialogMap_.emplace(1, AceType::RawPtr(dialogNodeFst));
    overlayManager->dialogMap_.emplace(2, AceType::RawPtr(dialogNodeScd));
    overlayManager->dialogMap_.emplace(3, AceType::RawPtr(dialogNodeThd));
    overlayManager->ReloadBuilderNodeConfig();
    EXPECT_EQ(overlayManager->GetDialogMap().size(), 3);
}
/**
 * @tc.name: OverlayManagerExtendTest010
 * @tc.desc: Test OverlayManager::RemovePopupInSubwindow.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble node and overlayManager and call RemovePopupInSubwindow.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    /**
     * @tc.steps: step2. set PopupInteractiveDismiss and PopupCallBackOnWillDismiss.
     */
    bool testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_FALSE(testResult);
    bubblePattern->SetInteractiveDismiss(false);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    bubblePattern->SetInteractiveDismiss(true);
    bubblePattern->onWillDismiss_ = std::move(onWillDismiss1);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
    /**
     * @tc.steps: step3. set container.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(pipelineContext);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
}
/**
 * @tc.name: OverlayManagerExtendTest011
 * @tc.desc: Test OverlayManager::PlayTransitionEffectOut.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble node and overlayManager and call RemovePopupInSubwindow.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    /**
     * @tc.steps: step2. set PopupInteractiveDismiss and PopupCallBackOnWillDismiss.
     */
    bool testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_FALSE(testResult);
    bubblePattern->SetInteractiveDismiss(false);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    bubblePattern->onWillDismiss_ = std::move(onWillDismiss1);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
    /**
     * @tc.steps: step3. set container.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    RefPtr<Container> container = AceType::MakeRefPtr<MockContainer>(pipelineContext);
    AceEngine::Get().AddContainer(DEFAULT_INSTANCE_ID, container);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
}
/**
 * @tc.name: OverlayManagerExtendTest012
 * @tc.desc: Test OverlayManager::PlayKeyboardTransition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble node and overlayManager and call RemovePopupInSubwindow.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto layoutProperty = AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty());
    auto renderProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    /**
     * @tc.steps: step2. set PopupInteractiveDismiss and PopupCallBackOnWillDismiss.
     */
    bool testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_FALSE(testResult);
    bubblePattern->SetInteractiveDismiss(false);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    bubblePattern->onWillDismiss_ = std::move(onWillDismiss1);
    testResult = overlayManager->RemovePopupInSubwindow(bubblePattern, popupNode, rootNode);
    EXPECT_TRUE(testResult);
}

/**
 * @tc.name: OverlayManagerExtendTest013
 * @tc.desc: OverlayManager::ContextMenuSwitchDragPreviewAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create overlayManager and dragPreviewNode and call ContextMenuSwitchDragPreviewAnimation.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    auto dragPreviewNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 2, AceType::MakeRefPtr<RootPattern>());
    overlayManager->ContextMenuSwitchDragPreviewAnimation(dragPreviewNode, DRAG_PREVIEW_OFFSET);
    EXPECT_TRUE(overlayManager->menuMap_.empty());
    /**
     * @tc.steps: step1+. create overlayManager->menuMap_ and call ContextMenuSwitchDragPreviewAnimation.
     */
    auto menuNodeFst =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, TEXT_TAG, MenuType::MENU));
    overlayManager->menuMap_.emplace(1, AceType::RawPtr(menuNodeFst));
    overlayManager->ContextMenuSwitchDragPreviewAnimation(dragPreviewNode, DRAG_PREVIEW_OFFSET);
    /**
     * @tc.steps: step2. set overlayNode's child node and one of children is menuWrapper.
     */
    auto wrapperNode =
        FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG, 4, AceType::MakeRefPtr<MenuWrapperPattern>(1));
    auto otherNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 5, AceType::MakeRefPtr<RootPattern>());
    otherNode->MountToParent(overlayNode);
    wrapperNode->MountToParent(overlayNode);
    overlayManager->ContextMenuSwitchDragPreviewAnimation(dragPreviewNode, DRAG_PREVIEW_OFFSET);
    EXPECT_FALSE(overlayManager->menuMap_.empty());
    EXPECT_EQ(overlayNode->GetLastChild()->GetTag(), V2::MENU_WRAPPER_ETS_TAG);
}
/**
 * @tc.name: OverlayManagerExtendTest014
 * @tc.desc: Test OverlayManager::OnDialogCloseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and toast node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(rootNode);
    /**
     * @tc.steps: step2. create overlayManager and call ShowToast when rootElement is nullptr.
     * @tc.expected: toastMap_ is empty
     */
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnDialogCloseEvent(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    EXPECT_FALSE(dialogPattern == nullptr);
    overlayManager->OnDialogCloseEvent(dialogNode);

    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    EXPECT_FALSE(overlayManager->DialogInMapHoldingFocus());
    overlayManager->OnDialogCloseEvent(dialogNode);
    overlayManager->CloseDialog(dialogNode);
    EXPECT_TRUE(overlayManager->dialogMap_.empty());
    auto dialogLayoutProp = dialogPattern->GetLayoutProperty<DialogLayoutProperty>();
    dialogLayoutProp->UpdateShowInSubWindow(true);
    auto parentNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    dialogNode->MountToParent(parentNode);
    overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->OnDialogCloseEvent(dialogNode);
    EXPECT_FALSE(MockContainer::Current()->IsDialogContainer());
}

/**
 * @tc.name: OverlayManagerExtendTest015
 * @tc.desc: Test OverlayManager::OnDialogCloseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent node and dialog node.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto dialogId = ElementRegister::GetInstance()->MakeUniqueId();
    auto dialogNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, dialogId, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    ASSERT_NE(dialogNode, nullptr);
    dialogNode->MountToParent(overlayNode);
    auto parentNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    overlayNode->MountToParent(parentNode);
    auto childNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    childNode->MountToParent(overlayNode);

    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    EXPECT_FALSE(dialogPattern == nullptr);
    auto dialogOption = dialogPattern->GetCloseAnimation().value_or(AnimationOption());
    auto onFinishEvent = []() {};
    dialogOption.SetOnFinishEvent(onFinishEvent);
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    /**
     * @tc.steps: step2. create overlayManager and call ShowToast when rootElement is nullptr.
     * @tc.expected: toastMap_ is empty
     */
    auto dialogLayoutProp = dialogPattern->GetLayoutProperty<DialogLayoutProperty>();
    dialogLayoutProp->UpdateShowInSubWindow(true);
    overlayManager->OnDialogCloseEvent(dialogNode);
    EXPECT_FALSE(MockContainer::Current()->IsDialogContainer());
}

/**
 * @tc.name: OverlayManagerExtendTest016
 * @tc.desc: Test OverlayManager::DismissPopup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create overlay node and set popup.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    overlayManager->DismissPopup();
    NG::PopupInfo PopupInfo1;
    PopupInfo1.markNeedUpdate = true;
    PopupInfo1.isCurrentOnShow = true;
    PopupInfo1.focusable = true;
    overlayManager->popupMap_.emplace(0, PopupInfo1);
    overlayManager->DismissPopup();
    EXPECT_NE(overlayManager->popupMap_[0].markNeedUpdate, true);
}

/**
 * @tc.name: OverlayManagerExtendTest017
 * @tc.desc: Test OverlayManager::PopupCallBackOnWillDismiss.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble node and overlayManager and call RemovePopupInSubwindow.
     */
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    auto testResult = overlayManager->PopupCallBackOnWillDismiss(popupNode);
    EXPECT_FALSE(testResult);
    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    bubblePattern->onWillDismiss_ = std::move(onWillDismiss1);
    testResult = overlayManager->PopupCallBackOnWillDismiss(popupNode);
    EXPECT_TRUE(testResult);
}

/**
 * @tc.name: OverlayManagerExtendTest018
 * @tc.desc: Test OverlayManager::CloseCustomDialog.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create root node and overlayManager and call CloseCustomDialog.
     */
    auto overlayNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(overlayNode);
    overlayManager->CloseCustomDialog(1);
    /**
     * @tc.steps: step1+. create root node and overlayManager and call CloseCustomDialog.
     */
    overlayManager->CloseCustomDialog(-1);
    /**
     * @tc.steps: step2. create dialogMap_  and call ReloadBuilderNodeConfig.
     */
    auto dialogNodeFst = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    auto dialogNodeScd = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    auto dialogNodeThd = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, 3, AceType::MakeRefPtr<DialogPattern>(AceType::MakeRefPtr<DialogTheme>(), nullptr));
    overlayManager->dialogMap_.emplace(1, AceType::RawPtr(dialogNodeFst));
    overlayManager->dialogMap_.emplace(2, AceType::RawPtr(dialogNodeScd));
    overlayManager->dialogMap_.emplace(3, AceType::RawPtr(dialogNodeThd));
    overlayManager->CloseCustomDialog(0);
    EXPECT_EQ(overlayManager->dialogMap_.end(), overlayManager->dialogMap_.find(0));
    /**
     * @tc.steps: step2+. create dialogMap_  and call ReloadBuilderNodeConfig.
     */
    overlayManager->CloseCustomDialog(-1);
    EXPECT_EQ(overlayManager->dialogMap_.end(), overlayManager->dialogMap_.find(-1));
}

/**
 * @tc.name: OverlayManagerExtendTest019
 * @tc.desc: Test OverlayManager::RemoveBubble.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, OverlayManagerExtendTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create overlay node and create popup node.
     */
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto popupNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    auto testResult = overlayManager->RemoveBubble(popupNode);
    /**
     * @tc.steps: step2. set CallOnWillDismiss or set SetInteractiveDismiss is true.
     */
    auto bubblePattern = popupNode->GetPattern<BubblePattern>();
    std::function<void(int32_t)> onWillDismiss1 = [](int32_t reason) {};
    bubblePattern->SetInteractiveDismiss(false);
    testResult = overlayManager->RemoveBubble(popupNode);
    EXPECT_TRUE(testResult);
    bubblePattern->SetInteractiveDismiss(true);
    bubblePattern->onWillDismiss_ = std::move(onWillDismiss1);
    testResult = overlayManager->RemoveBubble(popupNode);
    EXPECT_TRUE(testResult);
    /**
     * @tc.steps: step3. set popupMap_.
     */
    NG::PopupInfo PopupInfo1;
    PopupInfo1.popupNode = popupNode;
    overlayManager->popupMap_.emplace(0, PopupInfo1);

    auto popupNodeEx =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    NG::PopupInfo PopupInfo2;
    PopupInfo2.popupNode = popupNodeEx;
    overlayManager->popupMap_.emplace(1, PopupInfo2);
    testResult = overlayManager->RemoveBubble(popupNodeEx);
    EXPECT_TRUE(testResult);
}

/**
 * @tc.name: ShowToastTest001
 * @tc.desc: Test OverlayManager::ShowToast when callback is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, ShowToastTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create toastInfo
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    /**
     * @tc.steps: step3. run ShowToast
     * @tc.expected: toastMap_ is not empty
     */
    overlayManager->ShowToast(toastInfo, nullptr);
    EXPECT_FALSE(overlayManager->toastMap_.empty());
}

/**
 * @tc.name: ShowToastTest002
 * @tc.desc: Test OverlayManager::ShowToast
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, ShowToastTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create toastInfo and callback function.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto callback = [](int32_t callbackId) {
        /**
         * @tc.steps: step4. get callbackId.
         * @tc.expected: callbackId great or equal 0
         */
        EXPECT_TRUE(GreatOrEqual(callbackId, 0));
    };

    /**
     * @tc.steps: step3. run ShowToast.
     * @tc.expected: toastMap_ is not empty
     */
    overlayManager->ShowToast(toastInfo, callback);
    EXPECT_FALSE(overlayManager->toastMap_.empty());
}

/**
 * @tc.name: CloseToastTest001
 * @tc.desc: Test OverlayManager::ShowToast->CloseToast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, CloseToastTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create toastInfo and callback function.
     */
    auto toastInfo =
        NG::ToastInfo { .message = MESSAGE, .duration = DURATION, .bottom = BOTTOMSTRING, .isRightToLeft = true };
    toastInfo.shadow = ShadowConfig::DefaultShadowL;
    auto callback = [overlayManager](int32_t callbackId) {
        /**
         * @tc.steps: step4. get callbackId.
         * @tc.expected: callbackId great or equal 0
         */
        EXPECT_TRUE(GreatOrEqual(callbackId, 0));

        /**
         * @tc.steps: step5. create closeCallback function.
         */
        auto closeCallback = [](int32_t errorCode) {
            /**
             * @tc.steps: step7. get closeCallback errorCode.
             * @tc.expected: errorCode is ERROR_CODE_NO_ERROR
             */
            EXPECT_EQ(errorCode, ERROR_CODE_NO_ERROR);
        };

        /**
         * @tc.steps: step6. run CloseToast.
         * @tc.expected: toastMap_ is empty
         */
        auto toastId = callbackId >> 3; // 3 : Move 3 bits to the right to get toastId
        overlayManager->CloseToast(toastId, closeCallback);
        EXPECT_TRUE(overlayManager->toastMap_.empty());
    };

    /**
     * @tc.steps: step3. run ShowToast.
     */
    overlayManager->ShowToast(toastInfo, callback);
}

/**
 * @tc.name: CloseToastTest002
 * @tc.desc: Test OverlayManager::CloseToast.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, CloseToastTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get overlay manager instance.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. create closeCallback function.
     */
    auto closeCallback = [](int32_t errorCode) {
        /**
         * @tc.steps: step4. get closeCallback errorCode.
         * @tc.expected: errorCode is ERROR_CODE_TOAST_NOT_FOUND
         */
        EXPECT_EQ(errorCode, ERROR_CODE_TOAST_NOT_FOUND);
    };

    /**
     * @tc.steps: step3. run CloseToast.
     */
    overlayManager->CloseToast(1, closeCallback);
}

/**
 * @tc.name: GetRelativeContainerNode001
 * @tc.desc: Test GetRelativeContainerNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetRelativeContainerNode001, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetRelativeContainerNode();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetRelativeContainerNode002
 * @tc.desc: Test GetRelativeContainerNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetRelativeContainerNode002, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetRelativeContainerNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetDragPixelMapContentNodeTest001
 * @tc.desc: Test GetDragPixelMapContentNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetDragPixelMapContentNodeTest001, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetDragPixelMapContentNode();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetDragPixelMapContentNodeTest002
 * @tc.desc: Test GetDragPixelMapContentNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetDragPixelMapContentNodeTest002, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto framNodeFirstChild = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(framNodeFirstChild, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    rootNode->children_.push_front(framNodeFirstChild);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetDragPixelMapContentNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetDragPixelMapContentNodeTest003
 * @tc.desc: Test GetDragPixelMapContentNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetDragPixelMapContentNodeTest003, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto framNodeFirstChild = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(framNodeFirstChild, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    rootNode->children_.push_front(framNodeFirstChild);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetDragPixelMapContentNode();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetDragPixelMapContentNodeTest004
 * @tc.desc: Test GetDragPixelMapContentNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetDragPixelMapContentNodeTest004, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetDragPixelMapContentNode();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetDragPixelMapBadgeNodeTest001
 * @tc.desc: Test GetDragPixelMapBadgeNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetDragPixelMapBadgeNodeTest001, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(frameNode, nullptr);
    frameNode->children_.push_front(rootNode);
    auto textRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    ASSERT_NE(textRow, nullptr);
    textRow->children_.push_front(frameNode);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    columnNode->children_.push_back(textRow);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetDragPixelMapBadgeNode();
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: GetDragPixelMapBadgeNodeTest002
 * @tc.desc: Test GetDragPixelMapBadgeNode.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerExtendTestNg, GetDragPixelMapBadgeNodeTest002, TestSize.Level1)
{
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(rootNode, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    columnNode->children_.push_front(rootNode);
    overlayManager->dragPixmapColumnNodeWeak_ = columnNode;
    auto result = overlayManager->GetDragPixelMapBadgeNode();
    EXPECT_EQ(result, nullptr);
}
}