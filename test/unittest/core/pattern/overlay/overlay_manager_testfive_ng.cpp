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

#include <sstream>
#include "base/log/dump_log.h"

#include "test/mock/frameworks/base/subwindow/mock_subwindow.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "test/unittest/core/event/frame_node_on_tree.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/frontend.h"
#include "core/common/ace_engine.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
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
#include "core/components_ng/pattern/sheet/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/image/mock_pixel_map.h"
#include "interfaces/inner_api/ace/modal_ui_extension_config.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string TEXT_TAG = "text";
} // namespace

class OverlayManagerTestFiveNg : public TestNG {
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

void OverlayManagerTestFiveNg::SetUp()
{
    minPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->overlayManager_) {
        savedMenuManager_ = pipelineContext->overlayManager_->menuManager_;
        savedRootNodeWeak_ = pipelineContext->overlayManager_->rootNodeWeak_;
    }
}

void OverlayManagerTestFiveNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (pipelineContext && pipelineContext->overlayManager_) {
        pipelineContext->overlayManager_->menuManager_ = savedMenuManager_;
        pipelineContext->overlayManager_->rootNodeWeak_ = savedRootNodeWeak_;
        pipelineContext->overlayManager_->imageGeneratorSheetKey_ = std::nullopt;
        pipelineContext->overlayManager_->modalList_.clear();
        pipelineContext->overlayManager_->detachedProxyMap_.clear();
        pipelineContext->overlayManager_->overlayInfo_ = std::nullopt;
        pipelineContext->overlayManager_->overlayNode_ = nullptr;
        while (!pipelineContext->overlayManager_->modalStack_.empty()) {
            pipelineContext->overlayManager_->modalStack_.pop();
        }
    }
    auto mockContainer = MockContainer::Current();
    if (mockContainer) {
        mockContainer->isSubContainer_ = false;
    }
}

/**
 * @tc.name: OverlayManagerOptionsAndPopupErase001
 * @tc.desc: Test SetOverlayManagerOptions (both branches of if (overlayInfo_.has_value())) and
 *           ErasePopupInfo (both branches of if (popupMap_.find(targetId) != end)) using a fully
 *           isolated OverlayManager instance to avoid any shared-state side effects.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, OverlayManagerOptionsAndPopupErase001, TestSize.Level1)
{
    // Isolated OverlayManager (nullptr rootNode) — SetOverlayManagerOptions and ErasePopupInfo only
    // touch overlayInfo_ and popupMap_ members, not rootNode/context.
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);

    // === SetOverlayManagerOptions: false branch (overlayInfo_ nullopt -> set, return true) ===
    EXPECT_FALSE(overlayManager->overlayInfo_.has_value());
    OverlayManagerInfo info;
    info.renderRootOverlay = true;
    info.enableBackPressedEvent = true;
    EXPECT_TRUE(overlayManager->SetOverlayManagerOptions(info));
    EXPECT_TRUE(overlayManager->overlayInfo_.has_value());
    EXPECT_EQ(overlayManager->overlayInfo_->renderRootOverlay, true);
    // === SetOverlayManagerOptions: true branch (already has value -> return false, keep old) ===
    OverlayManagerInfo info2;
    info2.renderRootOverlay = false;
    info2.enableBackPressedEvent = false;
    EXPECT_FALSE(overlayManager->SetOverlayManagerOptions(info2));
    EXPECT_EQ(overlayManager->overlayInfo_->renderRootOverlay, true);
    EXPECT_EQ(overlayManager->overlayInfo_->enableBackPressedEvent, true);

    // === ErasePopupInfo: true branch (targetId exists -> erase) ===
    int32_t targetId = 987651;
    int32_t absentId = 987699;
    PopupInfo popupInfo;
    popupInfo.popupId = targetId;
    popupInfo.isCurrentOnShow = true;
    overlayManager->popupMap_[targetId] = popupInfo;
    EXPECT_NE(overlayManager->popupMap_.find(targetId), overlayManager->popupMap_.end());
    overlayManager->ErasePopupInfo(targetId);
    EXPECT_EQ(overlayManager->popupMap_.find(targetId), overlayManager->popupMap_.end());
    // === ErasePopupInfo: false branch (already absent -> no-op) ===
    overlayManager->ErasePopupInfo(targetId);
    EXPECT_EQ(overlayManager->popupMap_.find(targetId), overlayManager->popupMap_.end());
    // === ErasePopupInfo: false branch (never existed -> no-op) ===
    overlayManager->ErasePopupInfo(absentId);
    EXPECT_EQ(overlayManager->popupMap_.find(absentId), overlayManager->popupMap_.end());
}

/**
 * @tc.name: DumpMapInfo001
 * @tc.desc: Test both DumpMapInfo overloads covering all branches of if (hasTarget) in the for loop:
 *           true branch (hasTarget=true -> DumpEntry) and false branch (hasTarget=false -> GetMapNodeLog),
 *           including the null-node path where GetMapNodeLog returns "" via CHECK_NULL_RETURN.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, DumpMapInfo001, TestSize.Level1)
{
    // Isolated OverlayManager (nullptr rootNode) — DumpMapInfo only uses the passed map and
    // ElementRegister::GetInstance(), not rootNode/context.
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);
    // DumpLog::Print(depth, content) dereferences ostream_ without null check; set a valid
    // stream so the real (non-mocked) DumpLog implementation does not segfault.
    DumpLog::GetInstance().SetDumpFile(std::make_unique<std::ostringstream>());

    // === Overload 1: std::unordered_map<int32_t, RefPtr<FrameNode>> ===
    // Non-empty map with null node — covers the if/else branches (hasTarget drives the branch, not node)
    std::unordered_map<int32_t, RefPtr<FrameNode>> refMap;
    refMap[987651] = nullptr;
    // true branch: hasTarget=true -> calls DumpEntry(targetNode, targetId, nullptr)
    overlayManager->DumpMapInfo(refMap, "RefPtrMap", true);
    // false branch: hasTarget=false -> calls GetMapNodeLog(nullptr, false) -> returns ""
    overlayManager->DumpMapInfo(refMap, "RefPtrMap", false);

    // === Overload 2: std::unordered_map<int32_t, WeakPtr<FrameNode>> ===
    // Non-empty map with empty weak ptr — Upgrade() returns nullptr
    std::unordered_map<int32_t, WeakPtr<FrameNode>> weakMap;
    weakMap[987652] = WeakPtr<FrameNode>();
    // true branch: hasTarget=true -> calls DumpEntry(targetNode, targetId, nullptr)
    overlayManager->DumpMapInfo(weakMap, "WeakPtrMap", true);
    // false branch: hasTarget=false -> calls GetMapNodeLog(nullptr, false) -> returns ""
    overlayManager->DumpMapInfo(weakMap, "WeakPtrMap", false);

    // Edge case: empty map -> for loop body never executes (no crash)
    std::unordered_map<int32_t, RefPtr<FrameNode>> emptyRefMap;
    overlayManager->DumpMapInfo(emptyRefMap, "EmptyRefPtrMap", true);
    overlayManager->DumpMapInfo(emptyRefMap, "EmptyRefPtrMap", false);
    std::unordered_map<int32_t, WeakPtr<FrameNode>> emptyWeakMap;
    overlayManager->DumpMapInfo(emptyWeakMap, "EmptyWeakPtrMap", true);
    overlayManager->DumpMapInfo(emptyWeakMap, "EmptyWeakPtrMap", false);

    // Restore DumpLog ostream_ to the default (nullptr) state
    DumpLog::GetInstance().Reset();
}

/**
 * @tc.name: RemoveMenuCheckMenuManager001
 * @tc.desc: Test RemoveMenuBadgeNode and RemoveMenuInSubWindow covering both branches of
 *           if (!CheckMenuManager()): true branch (menuManager_ null -> CheckMenuManager false -> return)
 *           and false branch (menuManager_ non-null -> CheckMenuManager true -> continue past if).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemoveMenuCheckMenuManager001, TestSize.Level1)
{
    // Isolated OverlayManager (nullptr rootNode) — these methods only use menuManager_ and
    // NodeModifier, not rootNode/context (when menuManager_ is already set, CheckMenuManager
    // short-circuits to true without touching rootNode).
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(
        V2::MENU_WRAPPER_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);

    // === true branch: menuManager_ is null, rootNode is null -> CheckMenuManager returns false
    //     -> !false == true -> enter if -> return early ===
    overlayManager->menuManager_ = nullptr;
    overlayManager->RemoveMenuBadgeNode(menuWrapper);              // returns early, no crash
    EXPECT_FALSE(overlayManager->RemoveMenuInSubWindow(menuWrapper));  // returns false

    // === false branch: menuManager_ is non-null -> CheckMenuManager returns true
    //     -> !true == false -> skip if -> continue to modifier->removeXxx.
    //     Using a FrameNode (not a MenuManager) as menuManager_ so DynamicCast<MenuManager>
    //     fails inside the modifier function -> CHECK_NULL_VOID/RETURN -> safe return. ===
    overlayManager->menuManager_ = menuWrapper; // FrameNode is not MenuManager
    overlayManager->RemoveMenuBadgeNode(menuWrapper);              // passes if, DynamicCast fails, safe
    EXPECT_FALSE(overlayManager->RemoveMenuInSubWindow(menuWrapper));  // passes if, DynamicCast fails, false
}

/**
 * @tc.name: CheckPageNeedAvoidKeyboard001
 * @tc.desc: Test CheckPageNeedAvoidKeyboard covering both branches of
 *           if (child->GetTag() != V2::SHEET_WRAPPER_TAG):
 *           true branch (tag != SHEET_WRAPPER_TAG -> return true) and
 *           false branch (tag == SHEET_WRAPPER_TAG -> continue to focus check).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, CheckPageNeedAvoidKeyboard001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);

    // === false branch: last child tag == SHEET_WRAPPER_TAG -> skip if, continue to focus check ===
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto sheetWrapper = FrameNode::CreateFrameNode(
        V2::SHEET_WRAPPER_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>());
    ASSERT_NE(sheetWrapper, nullptr);
    rootNode->children_.push_back(sheetWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    // false branch: continues to DynamicCast<FrameNode> + GetFocusHub + IsCurrentFocus chain
    overlayManager->CheckPageNeedAvoidKeyboard();

    // === true branch: last child tag != SHEET_WRAPPER_TAG -> return true ===
    auto rootNode2 = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    rootNode2->children_.push_back(buttonNode);
    overlayManager->rootNodeWeak_ = rootNode2;
    EXPECT_TRUE(overlayManager->CheckPageNeedAvoidKeyboard());

    // === edge: root is null -> CHECK_NULL_RETURN(root, true) -> return true ===
    overlayManager->rootNodeWeak_ = nullptr;
    EXPECT_TRUE(overlayManager->CheckPageNeedAvoidKeyboard());

    // === edge: root has no children -> CHECK_NULL_RETURN(child, true) -> return true ===
    auto emptyRoot = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    overlayManager->rootNodeWeak_ = emptyRoot;
    EXPECT_TRUE(overlayManager->CheckPageNeedAvoidKeyboard());
}

/**
 * @tc.name: OnKeyboardAvoid001
 * @tc.desc: Test OnKeyboardAvoid for-loop covering all branches of if/else if:
 *           if true (child tag == POPUP_ETS_TAG -> MarkDirtyNode),
 *           else if true (child tag == MENU_WRAPPER_ETS_TAG -> NotifyDirtyChildren),
 *           else (child null or other tag -> no action), and edge case root null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, OnKeyboardAvoid001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);

    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    // if true: child with POPUP_ETS_TAG
    auto popupChild = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<BubblePattern>());
    // else if true: child with MENU_WRAPPER_ETS_TAG
    auto menuChild = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    // else: child with other tag (BUTTON)
    auto otherChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    rootNode->children_.push_back(popupChild);
    rootNode->children_.push_back(menuChild);
    rootNode->children_.push_back(otherChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->OnKeyboardAvoid(); // covers if true, else if true, else

    // edge: root is null -> CHECK_NULL_VOID(root) -> return
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->OnKeyboardAvoid(); // no crash
}

/**
 * @tc.name: UpdateModalUIExtensionConfig001
 * @tc.desc: Test UpdateModalUIExtensionConfig covering both branches of if (!targetModalNode):
 *           true branch (no matching modal -> return) and false branch (modal found -> set config).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, UpdateModalUIExtensionConfig001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);

    overlayManager->modalList_.clear();
    ModalUIExtensionAllowedUpdateConfig config;
    config.prohibitedRemoveByNavigation = true;
    config.prohibitedRemoveByRouter = false;

    // true branch: no matching modal -> GetModal returns null -> return
    overlayManager->UpdateModalUIExtensionConfig(999, config);

    // false branch: add a modal node with matching targetId, then call
    int32_t sessionId = 100;
    int32_t targetId = -(sessionId); // GetModal uses -(sessionId) as key
    auto modalNode = FrameNode::CreateFrameNode(V2::MODAL_PAGE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ModalPresentationPattern>(targetId, ModalTransition::NONE, nullptr));
    ASSERT_NE(modalNode, nullptr);
    overlayManager->modalList_.push_back(modalNode);
    overlayManager->UpdateModalUIExtensionConfig(sessionId, config); // false branch -> sets config
    overlayManager->modalList_.clear();
}

/**
 * @tc.name: UpdatePixelMapScale001
 * @tc.desc: Test UpdatePixelMapScale covering false branch of if (height==0||width==0) with
 *           non-zero pixelMap, and nested if/else combinations under default device dimensions
 *           (720x1280): if B false (else B), if D false (textDraggable false),
 *           else if E true (large pixelMap -> scale set) and false (small pixelMap -> unchanged).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, UpdatePixelMapScale001, TestSize.Level1)
{
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    ASSERT_NE(hub, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto mockPixelMap = AceType::DynamicCast<MockPixelMap>(pixelMap);
    ASSERT_NE(mockPixelMap, nullptr);
    hub->SetPixelMap(pixelMap);
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));

    // false branch of if (height==0||width==0): non-zero dimensions
    // small pixelMap (100x100): if B false (640>720 false), if D false, else if E false (100<240)
    ON_CALL(*mockPixelMap, GetHeight()).WillByDefault(Return(100));
    ON_CALL(*mockPixelMap, GetWidth()).WillByDefault(Return(100));
    float scale1 = 1.0f;
    overlayManager->UpdatePixelMapScale(scale1);

    // large pixelMap (500x500), textDraggable=false: else if E true (500>240) -> scale set
    ON_CALL(*mockPixelMap, GetHeight()).WillByDefault(Return(500));
    ON_CALL(*mockPixelMap, GetWidth()).WillByDefault(Return(500));
    float scale2 = 1.0f;
    overlayManager->UpdatePixelMapScale(scale2);
    EXPECT_LT(scale2, 1.0f);

    // large pixelMap (500x500), textDraggable=true: if D true (500>240, 500>480) -> scale set
    hub->SetTextDraggable(true);
    float scale3 = 1.0f;
    overlayManager->UpdatePixelMapScale(scale3);
    EXPECT_LT(scale3, 1.0f);
    hub->SetTextDraggable(false);
}

/**
 * @tc.name: UpdatePixelMapScale002
 * @tc.desc: Test UpdatePixelMapScale covering if B true branch and nested if C with modified
 *           device dimensions (width=2000, height=500): maxDeviceLength*0.5 > minDeviceLength
 *           is true, and if C (height > minDeviceLength*0.5) with large pixelMap.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, UpdatePixelMapScale002, TestSize.Level1)
{
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    auto hub = columnNode->GetOrCreateGestureEventHub();
    ASSERT_NE(hub, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto mockPixelMap = AceType::DynamicCast<MockPixelMap>(pixelMap);
    ASSERT_NE(mockPixelMap, nullptr);
    hub->SetPixelMap(pixelMap);
    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));

    // Modify device dimensions to make if B true: max(2000,500)*0.5=1000 > min=500
    int32_t savedWidth = SystemProperties::deviceWidth_;
    int32_t savedHeight = SystemProperties::deviceHeight_;
    SystemProperties::deviceWidth_ = 2000;
    SystemProperties::deviceHeight_ = 500;

    // if B true, if C true: height=300 > 500*0.5=250 -> scale set
    ON_CALL(*mockPixelMap, GetHeight()).WillByDefault(Return(300));
    ON_CALL(*mockPixelMap, GetWidth()).WillByDefault(Return(300));
    float scale1 = 1.0f;
    overlayManager->UpdatePixelMapScale(scale1);
    EXPECT_LT(scale1, 1.0f);

    // if B true, if C false: height=200 < 250 -> scale unchanged
    ON_CALL(*mockPixelMap, GetHeight()).WillByDefault(Return(200));
    ON_CALL(*mockPixelMap, GetWidth()).WillByDefault(Return(200));
    float scale2 = 1.0f;
    overlayManager->UpdatePixelMapScale(scale2);
    EXPECT_EQ(scale2, 1.0f);

    SystemProperties::deviceWidth_ = savedWidth;
    SystemProperties::deviceHeight_ = savedHeight;
}

/**
 * @tc.name: RemovePixelMapAnimation001
 * @tc.desc: Test RemovePixelMapAnimation covering code after CHECK_NULL_VOID(imageNode):
 *           if E true branch (shadow.has_value()==false -> create default shadow) with
 *           startDrag=false path reaching the full animation setup.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemovePixelMapAnimation001, TestSize.Level1)
{
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);
    // if A false: isOnAnimation_==false && hasPixelMap_==true
    overlayManager->isOnAnimation_ = false;
    overlayManager->hasPixelMap_ = true;

    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    // image child so CHECK_NULL_VOID(imageNode) passes
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(imageNode, nullptr);
    columnNode->children_.push_back(imageNode);

    auto hub = columnNode->GetOrCreateGestureEventHub();
    ASSERT_NE(hub, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto mockPixelMap = AceType::DynamicCast<MockPixelMap>(pixelMap);
    ASSERT_NE(mockPixelMap, nullptr);
    ON_CALL(*mockPixelMap, GetHeight()).WillByDefault(Return(100));
    ON_CALL(*mockPixelMap, GetWidth()).WillByDefault(Return(100));
    hub->SetPixelMap(pixelMap);

    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));

    // startDrag=false → if B false → continue past if D → reach code after CHECK_NULL_VOID(imageNode)
    // if E true: fresh imageNode has no back shadow → create default
    overlayManager->RemovePixelMapAnimation(false, 0, 0, false);
}

/**
 * @tc.name: RemovePixelMapAnimation002
 * @tc.desc: Test RemovePixelMapAnimation covering if E false branch
 *           (shadow.has_value()==true -> use existing shadow) by pre-setting a back shadow
 *           on the imageNode's RenderContext.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemovePixelMapAnimation002, TestSize.Level1)
{
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(nullptr);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->isOnAnimation_ = false;
    overlayManager->hasPixelMap_ = true;

    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(columnNode, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(imageNode, nullptr);
    // Pre-set back shadow so if E false branch is taken
    imageNode->GetRenderContext()->UpdateBackShadow(Shadow::CreateShadow(ShadowStyle::None));
    columnNode->children_.push_back(imageNode);

    auto hub = columnNode->GetOrCreateGestureEventHub();
    ASSERT_NE(hub, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto mockPixelMap = AceType::DynamicCast<MockPixelMap>(pixelMap);
    ASSERT_NE(mockPixelMap, nullptr);
    ON_CALL(*mockPixelMap, GetHeight()).WillByDefault(Return(100));
    ON_CALL(*mockPixelMap, GetWidth()).WillByDefault(Return(100));
    hub->SetPixelMap(pixelMap);

    overlayManager->pixmapColumnNodeWeak_ = AceType::WeakClaim(AceType::RawPtr(columnNode));

    // if E false: shadow already has value → skip CreateShadow
    overlayManager->RemovePixelMapAnimation(false, 0, 0, false);
}

/**
 * @tc.name: IsNeedAvoidFoldCrease001
 * @tc.desc: Test IsNeedAvoidFoldCrease when frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease001, TestSize.Level1)
{
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(nullptr, false, false, std::nullopt));
}

/**
 * @tc.name: IsNeedAvoidFoldCrease002
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    AceEngine::Get().RemoveContainer(0);
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, false, std::nullopt));
    AceEngine::Get().AddContainer(0, MockContainer::Current());
}

/**
 * @tc.name: IsNeedAvoidFoldCrease003
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is sub container and parent container is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = true;
    AceEngine::Get().RemoveContainer(-1);
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, false, std::nullopt));
    mockContainer->isSubContainer_ = savedIsSubContainer;
    AceEngine::Get().AddContainer(0, MockContainer::Current());
}

/**
 * @tc.name: IsNeedAvoidFoldCrease004
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is not sub container, expandDisplay true and sourceMode EXTEND.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    EXPECT_FALSE(OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, true, std::nullopt));
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: IsNeedAvoidFoldCrease005
 * @tc.desc: Test IsNeedAvoidFoldCrease when container is not sub container, normal case returns false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsNeedAvoidFoldCrease005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    bool result = OverlayManager::IsNeedAvoidFoldCrease(frameNode, false, false, std::nullopt);
    EXPECT_FALSE(result);
    mockContainer->isSubContainer_ = savedIsSubContainer;
}

/**
 * @tc.name: GetSubwindowKeyNodeId001
 * @tc.desc: Test GetSubwindowKeyNodeId when frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId001, TestSize.Level1)
{
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(nullptr), -1);
}

/**
 * @tc.name: GetSubwindowKeyNodeId002
 * @tc.desc: Test GetSubwindowKeyNodeId when frameNode has no DialogPattern.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), -1);
}

/**
 * @tc.name: GetSubwindowKeyNodeId003
 * @tc.desc: Test GetSubwindowKeyNodeId when IsUIExtensionSubWindow is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isUIExtensionSubWindow_ = false;
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), -1);
}

/**
 * @tc.name: GetSubwindowKeyNodeId004
 * @tc.desc: Test GetSubwindowKeyNodeId when IsUIExtensionSubWindow is true and IsModal is true.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isUIExtensionSubWindow_ = true;
    auto dialogProps = AceType::DynamicCast<DialogLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(dialogProps, nullptr);
    dialogProps->UpdateIsModal(true);
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), frameNode->GetId());
}

/**
 * @tc.name: GetSubwindowKeyNodeId005
 * @tc.desc: Test GetSubwindowKeyNodeId when IsUIExtensionSubWindow is true and IsModal is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSubwindowKeyNodeId005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::DIALOG_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(dialogPattern, nullptr);
    dialogPattern->isUIExtensionSubWindow_ = true;
    auto dialogProps = AceType::DynamicCast<DialogLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(dialogProps, nullptr);
    dialogProps->UpdateIsModal(false);
    EXPECT_EQ(OverlayManager::GetSubwindowKeyNodeId(frameNode), -1);
}

/**
 * @tc.name: GetDisplayAvailableRect001
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect001, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
    auto rect = OverlayManager::GetDisplayAvailableRect(nullptr, 0);
    EXPECT_EQ(rect.ToString(), Rect().ToString());
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetDisplayAvailableRect002
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is true and frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect002, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto rect = OverlayManager::GetDisplayAvailableRect(nullptr, 0);
    EXPECT_EQ(rect.ToString(), Rect().ToString());
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetDisplayAvailableRect003
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is true and container is not sub container.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect003, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = false;
    AceEngine::Get().AddContainer(0, mockContainer);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    Rect expectedRect(0, 0, 720, 1280);
    pipelineContext->displayAvailableRect_ = expectedRect;
    auto rect = OverlayManager::GetDisplayAvailableRect(frameNode, 0);
    EXPECT_EQ(rect.Width(), expectedRect.Width());
    EXPECT_EQ(rect.Height(), expectedRect.Height());
    mockContainer->isSubContainer_ = savedIsSubContainer;
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetDisplayAvailableRect004
 * @tc.desc: Test GetDisplayAvailableRect when IsSuperFoldDisplayDevice is true and container is sub container.
 *           Covers the false branch of if (!container->IsSubContainer()).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetDisplayAvailableRect004, TestSize.Level1)
{
    bool saved = MockSystemProperties::g_isSuperFoldDisplayDevice;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    bool savedIsSubContainer = mockContainer->isSubContainer_;
    mockContainer->isSubContainer_ = true;
    AceEngine::Get().AddContainer(0, mockContainer);
    Rect expectedRect(10, 20, 360, 640);
    MockContainer::mockDisplayAvailableRect_ = expectedRect;
    auto rect = OverlayManager::GetDisplayAvailableRect(frameNode, 0);
    EXPECT_EQ(rect.Width(), expectedRect.Width());
    EXPECT_EQ(rect.Height(), expectedRect.Height());
    EXPECT_EQ(rect.GetOffset().GetX(), expectedRect.GetOffset().GetX());
    EXPECT_EQ(rect.GetOffset().GetY(), expectedRect.GetOffset().GetY());
    mockContainer->isSubContainer_ = savedIsSubContainer;
    MockContainer::mockDisplayAvailableRect_ = Rect();
    MockSystemProperties::g_isSuperFoldDisplayDevice = saved;
}

/**
 * @tc.name: GetSafeAreaInsets001
 * @tc.desc: Test GetSafeAreaInsets when useCurrentWindow is false.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSafeAreaInsets001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto mockPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    SafeAreaInsets::Inset left{10, 50};
    SafeAreaInsets::Inset top{0, 100};
    SafeAreaInsets::Inset right{0, 0};
    SafeAreaInsets::Inset bottom{0, 200};
    SafeAreaInsets expectedInsets(left, top, right, bottom);
    EXPECT_CALL(*mockPipeline, GetSafeAreaWithoutProcess())
        .WillRepeatedly(testing::Return(expectedInsets));
    auto insets = OverlayManager::GetSafeAreaInsets(frameNode, false);
    EXPECT_EQ(insets.left_.start, left.start);
    EXPECT_EQ(insets.left_.end, left.end);
    EXPECT_EQ(insets.top_.start, top.start);
    EXPECT_EQ(insets.top_.end, top.end);
    EXPECT_EQ(insets.bottom_.start, bottom.start);
    EXPECT_EQ(insets.bottom_.end, bottom.end);
}

/**
 * @tc.name: GetSafeAreaInsets002
 * @tc.desc: Test GetSafeAreaInsets when useCurrentWindow is true with valid frameNode.
 *           Covers the true branch of if (useCurrentWindow).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSafeAreaInsets002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachContext(PipelineContext::GetCurrentContext().GetRawPtr());
    auto mockPipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(mockPipeline, nullptr);
    SafeAreaInsets::Inset left{20, 80};
    SafeAreaInsets::Inset top{5, 120};
    SafeAreaInsets::Inset right{0, 0};
    SafeAreaInsets::Inset bottom{0, 300};
    SafeAreaInsets expectedInsets(left, top, right, bottom);
    EXPECT_CALL(*mockPipeline, GetSafeAreaWithoutProcess())
        .WillRepeatedly(testing::Return(expectedInsets));
    auto insets = OverlayManager::GetSafeAreaInsets(frameNode, true);
    EXPECT_EQ(insets.left_.start, left.start);
    EXPECT_EQ(insets.left_.end, left.end);
    EXPECT_EQ(insets.top_.start, top.start);
    EXPECT_EQ(insets.top_.end, top.end);
    EXPECT_EQ(insets.bottom_.start, bottom.start);
    EXPECT_EQ(insets.bottom_.end, bottom.end);
}

/**
 * @tc.name: GetSafeAreaInsets003
 * @tc.desc: Test GetSafeAreaInsets when useCurrentWindow is true and frameNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetSafeAreaInsets003, TestSize.Level1)
{
    auto insets = OverlayManager::GetSafeAreaInsets(nullptr, true);
    EXPECT_FALSE(insets.IsValid());
}

/**
 * @tc.name: SetNodeBeforeAppbar001
 * @tc.desc: Test SetNodeBeforeAppbar when rootNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(nullptr, node, std::nullopt));
}

/**
 * @tc.name: SetNodeBeforeAppbar002
 * @tc.desc: Test SetNodeBeforeAppbar when node is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(rootNode, nullptr, std::nullopt));
}

/**
 * @tc.name: SetNodeBeforeAppbar003
 * @tc.desc: Test SetNodeBeforeAppbar when rootNode has no AtomicService child.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    rootNode->AddChild(child);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(rootNode, node, std::nullopt));
}

/**
 * @tc.name: SetNodeBeforeAppbar004
 * @tc.desc: Test SetNodeBeforeAppbar when AtomicService child has serviceContainer and GetNextNodeWithOrder
 *  returns non-null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto atomicService = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(atomicService, nullptr);
    auto serviceContainer = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(serviceContainer, nullptr);
    serviceContainer->UpdateInspectorId("AtomicServiceContainerId");
    atomicService->AddChild(serviceContainer);
    rootNode->AddChild(atomicService);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    double order = 5.0;
    auto existingNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(existingNode, nullptr);
    overlayManager->nodeIdOrderMap_[existingNode->GetId()] = 10.0;
    overlayManager->orderNodesMap_[10.0].emplace_back(existingNode);
    EXPECT_TRUE(overlayManager->SetNodeBeforeAppbar(rootNode, node, order));
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
}

/**
 * @tc.name: SetNodeBeforeAppbar005
 * @tc.desc: Test SetNodeBeforeAppbar when GetNextNodeWithOrder returns null, childNode found.
 *           Covers the else branch.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto atomicService = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(atomicService, nullptr);
    auto serviceContainer = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(serviceContainer, nullptr);
    serviceContainer->UpdateInspectorId("AtomicServiceContainerId");
    auto menubarRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(menubarRow, nullptr);
    menubarRow->UpdateInspectorId("AtomicServiceMenubarRowId");
    atomicService->AddChild(serviceContainer);
    atomicService->AddChild(menubarRow);
    rootNode->AddChild(atomicService);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(overlayManager->SetNodeBeforeAppbar(rootNode, node, std::nullopt));
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
}

/**
 * @tc.name: SetNodeBeforeAppbar006
 * @tc.desc: Test SetNodeBeforeAppbar when GetNextNodeWithOrder returns null and childNode not found.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetNodeBeforeAppbar006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto atomicService = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(atomicService, nullptr);
    auto serviceContainer = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(serviceContainer, nullptr);
    serviceContainer->UpdateInspectorId("AtomicServiceContainerId");
    atomicService->AddChild(serviceContainer);
    rootNode->AddChild(atomicService);
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    EXPECT_FALSE(overlayManager->SetNodeBeforeAppbar(rootNode, node, std::nullopt));
    overlayManager->nodeIdOrderMap_.clear();
    overlayManager->orderNodesMap_.clear();
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow001
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when rootNode is null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow002
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when rootNode has no MenuWrapper child.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto child = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child, nullptr);
    rootNode->AddChild(child);
    overlayManager->rootNodeWeak_ = rootNode;
    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow003
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when MenuWrapper child has non-matching inner children.
 *           Covers the inner loop else branch (continue).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);
    auto nonMatchingChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonMatchingChild, nullptr);
    menuWrapper->AddChild(nonMatchingChild);
    rootNode->AddChild(menuWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    EXPECT_EQ(overlayManager->GetPixelMapContentNodeForSubwindow(), nullptr);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow004
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when MenuWrapper child has MenuPreview inner child.
 *           Covers the inner loop if branch (return frameNode).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);
    auto nonMatchingChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonMatchingChild, nullptr);
    auto menuPreviewNode = FrameNode::CreateFrameNode(V2::MENU_PREVIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(menuPreviewNode, nullptr);
    menuWrapper->AddChild(nonMatchingChild);
    menuWrapper->AddChild(menuPreviewNode);
    rootNode->AddChild(menuWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    auto result = overlayManager->GetPixelMapContentNodeForSubwindow();
    EXPECT_EQ(result, menuPreviewNode);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: GetPixelMapContentNodeForSubwindow005
 * @tc.desc: Test GetPixelMapContentNodeForSubwindow when MenuWrapper child has Image inner child.
 *           Covers the inner loop if branch with IMAGE_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, GetPixelMapContentNodeForSubwindow005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto menuWrapper = FrameNode::CreateFrameNode(V2::MENU_WRAPPER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuWrapperPattern>(1));
    ASSERT_NE(menuWrapper, nullptr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(imageNode, nullptr);
    menuWrapper->AddChild(imageNode);
    rootNode->AddChild(menuWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    auto result = overlayManager->GetPixelMapContentNodeForSubwindow();
    EXPECT_EQ(result, imageNode);
    overlayManager->rootNodeWeak_ = nullptr;
}

/**
 * @tc.name: MarkDirty001
 * @tc.desc: Test MarkDirty when root is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    overlayManager->rootNodeWeak_ = nullptr;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty002
 * @tc.desc: Test MarkDirty when installationFree is false and rootNode == markNode (return early).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    pipelineContext->installationFree_ = false;
    auto rootElement = pipelineContext->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    overlayManager->rootNodeWeak_ = rootElement;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty003
 * @tc.desc: Test MarkDirty when installationFree is true, markNode is root's first child.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = true;
    pipelineContext->isSubPipeline_ = false;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto firstChild = FrameNode::CreateFrameNode(
        V2::ATOMIC_SERVICE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(firstChild, nullptr);
    auto secondChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(secondChild, nullptr);
    rootNode->AddChild(firstChild);
    rootNode->AddChild(secondChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty004
 * @tc.desc: Test MarkDirty when child is first child and not sub pipeline (skip child in for loop).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = false;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto firstChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(firstChild, nullptr);
    auto secondChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(secondChild, nullptr);
    rootNode->AddChild(firstChild);
    rootNode->AddChild(secondChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty005
 * @tc.desc: Test MarkDirty when child is sheet wrapper with sheet child.
 *           Covers sheetParent tag == SHEET_WRAPPER_TAG and sheet non-null.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = true;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto sheetWrapper = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    ASSERT_NE(sheetWrapper, nullptr);
    auto sheetChild = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(sheetChild, nullptr);
    sheetWrapper->AddChild(sheetChild);
    rootNode->AddChild(sheetWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty006
 * @tc.desc: Test MarkDirty when child is sheet wrapper without sheet child (sheet is null).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = true;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto sheetWrapper = FrameNode::CreateFrameNode(V2::SHEET_WRAPPER_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<SheetWrapperPattern>());
    ASSERT_NE(sheetWrapper, nullptr);
    rootNode->AddChild(sheetWrapper);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty007
 * @tc.desc: Test MarkDirty when rootNode != markNode and toast child exists.
 *           Covers toast loop true branch.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty007, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = false;
    auto customRoot = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(customRoot, nullptr);
    auto child1 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child1, nullptr);
    customRoot->AddChild(child1);
    overlayManager->rootNodeWeak_ = customRoot;
    auto rootElement = pipelineContext->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    auto toastChild = FrameNode::CreateFrameNode(
        V2::TOAST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ToastPattern>());
    ASSERT_NE(toastChild, nullptr);
    rootElement->AddChild(toastChild);
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    rootElement->RemoveChild(toastChild);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty008
 * @tc.desc: Test MarkDirty when rootNode != markNode and non-toast child exists.
 *           Covers toast loop false branch (tag != TOAST_ETS_TAG).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty008, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = false;
    auto customRoot = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(customRoot, nullptr);
    auto child1 = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(child1, nullptr);
    customRoot->AddChild(child1);
    overlayManager->rootNodeWeak_ = customRoot;
    auto rootElement = pipelineContext->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    auto nonToastChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(nonToastChild, nullptr);
    rootElement->AddChild(nonToastChild);
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    rootElement->RemoveChild(nonToastChild);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: MarkDirty009
 * @tc.desc: Test MarkDirty when isSubPipeline is true, first child is marked.
 *           Covers the IsSubPipeline true branch in for loop condition.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, MarkDirty009, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto savedRoot = overlayManager->rootNodeWeak_;
    bool savedInstallationFree = pipelineContext->installationFree_;
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->installationFree_ = false;
    pipelineContext->isSubPipeline_ = true;
    auto rootNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(rootNode, nullptr);
    auto firstChild = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(firstChild, nullptr);
    rootNode->AddChild(firstChild);
    overlayManager->rootNodeWeak_ = rootNode;
    overlayManager->MarkDirty(PROPERTY_UPDATE_MEASURE);
    pipelineContext->installationFree_ = savedInstallationFree;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
    overlayManager->rootNodeWeak_ = savedRoot;
}

/**
 * @tc.name: SetDetachedFreeRootProxy001
 * @tc.desc: Test SetDetachedFreeRootProxy when node is nullptr.
 *           Covers the false branch of if (node && node->GetTag() == DETACHED_FREE_ROOT_PROXY).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetDetachedFreeRootProxy001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->detachedProxyMap_.clear();
    int32_t targetId = 100;
    overlayManager->SetDetachedFreeRootProxy(nullptr, targetId);
    EXPECT_TRUE(overlayManager->detachedProxyMap_.empty());
}

/**
 * @tc.name: SetDetachedFreeRootProxy002
 * @tc.desc: Test SetDetachedFreeRootProxy when node tag != DETACHED_FREE_ROOT_PROXY.
 *           Covers the false branch (tag mismatch) of the outer if.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetDetachedFreeRootProxy002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->detachedProxyMap_.clear();
    auto node = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(node, nullptr);
    int32_t targetId = 101;
    overlayManager->SetDetachedFreeRootProxy(node, targetId);
    EXPECT_TRUE(overlayManager->detachedProxyMap_.empty());
}

/**
 * @tc.name: SetDetachedFreeRootProxy003
 * @tc.desc: Test SetDetachedFreeRootProxy when node tag == DETACHED_FREE_ROOT_PROXY and targetId not in map.
 *           Covers the true branch of outer if and false branch of inner if (not found in map).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetDetachedFreeRootProxy003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->detachedProxyMap_.clear();
    auto node = FrameNode::CreateFrameNode(
        "DetachedFreeRootProxy", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    int32_t targetId = 102;
    overlayManager->SetDetachedFreeRootProxy(node, targetId);
    EXPECT_EQ(overlayManager->detachedProxyMap_.size(), 1u);
    auto it = overlayManager->detachedProxyMap_.find(targetId);
    ASSERT_NE(it, overlayManager->detachedProxyMap_.end());
    EXPECT_EQ(it->second, node);
}

/**
 * @tc.name: SetDetachedFreeRootProxy004
 * @tc.desc: Test SetDetachedFreeRootProxy when targetId already exists in map.
 *           Covers the true branch of outer if and true branch of inner if (found in map, replace).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, SetDetachedFreeRootProxy004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->detachedProxyMap_.clear();
    int32_t targetId = 103;
    auto oldNode = FrameNode::CreateFrameNode(
        "DetachedFreeRootProxy", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(oldNode, nullptr);
    overlayManager->detachedProxyMap_[targetId] = oldNode;
    auto newNode = FrameNode::CreateFrameNode(
        "DetachedFreeRootProxy", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(newNode, nullptr);
    overlayManager->SetDetachedFreeRootProxy(newNode, targetId);
    EXPECT_EQ(overlayManager->detachedProxyMap_.size(), 1u);
    auto it = overlayManager->detachedProxyMap_.find(targetId);
    ASSERT_NE(it, overlayManager->detachedProxyMap_.end());
    EXPECT_EQ(it->second, newNode);
}

/**
 * @tc.name: ContentChangeReport001
 * @tc.desc: Test ContentChangeReport when isSubPipeline is false.
 *           Covers the false branch of if (pipeline->IsSubPipeline()).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, ContentChangeReport001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->isSubPipeline_ = false;
    auto keyNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(keyNode, nullptr);
    overlayManager->ContentChangeReport(keyNode, true);
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
}

/**
 * @tc.name: ContentChangeReport002
 * @tc.desc: Test ContentChangeReport when isSubPipeline is true and parent pipeline is null.
 *           Covers the true branch of if (pipeline->IsSubPipeline()) and
 *           the true branch of CHECK_NULL_VOID(pipeline) after GetContextByContainerId.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, ContentChangeReport002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->isSubPipeline_ = true;
    auto keyNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(keyNode, nullptr);
    overlayManager->ContentChangeReport(keyNode, false);
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
}

/**
 * @tc.name: ContentChangeReport003
 * @tc.desc: Test ContentChangeReport when isSubPipeline is false and contentChangeMgr_ is null.
 *           Covers the true branch of CHECK_NULL_VOID(mgr).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, ContentChangeReport003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    bool savedIsSubPipeline = pipelineContext->isSubPipeline_;
    pipelineContext->isSubPipeline_ = false;
    auto savedMgr = pipelineContext->contentChangeMgr_;
    pipelineContext->contentChangeMgr_ = nullptr;
    auto keyNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(keyNode, nullptr);
    overlayManager->ContentChangeReport(keyNode, true);
    pipelineContext->contentChangeMgr_ = savedMgr;
    pipelineContext->isSubPipeline_ = savedIsSubPipeline;
}

/**
 * @tc.name: RemoveOverlayManagerNode001
 * @tc.desc: Test RemoveOverlayManagerNode when overlayInfo_ has no value.
 *           Covers the false branch of if (overlayInfo_.has_value() && ...).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemoveOverlayManagerNode001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->overlayInfo_ = std::nullopt;
    overlayManager->overlayNode_ = nullptr;
    int32_t result = overlayManager->RemoveOverlayManagerNode();
    EXPECT_EQ(result, 0); // OVERLAY_EXISTS = 0
}

/**
 * @tc.name: RemoveOverlayManagerNode002
 * @tc.desc: Test RemoveOverlayManagerNode when enableBackPressedEvent is false.
 *           Covers the false branch (enableBackPressedEvent false) of the compound if.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemoveOverlayManagerNode002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    OverlayManagerInfo info;
    info.enableBackPressedEvent = false;
    overlayManager->overlayInfo_ = info;
    auto overlayNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(overlayNode, nullptr);
    overlayManager->overlayNode_ = overlayNode;
    int32_t result = overlayManager->RemoveOverlayManagerNode();
    EXPECT_EQ(result, 0); // OVERLAY_EXISTS = 0
}

/**
 * @tc.name: RemoveOverlayManagerNode003
 * @tc.desc: Test RemoveOverlayManagerNode when overlayNode_ is null.
 *           Covers the false branch (overlayNode_ null) of the compound if.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemoveOverlayManagerNode003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    OverlayManagerInfo info;
    info.enableBackPressedEvent = true;
    overlayManager->overlayInfo_ = info;
    overlayManager->overlayNode_ = nullptr;
    int32_t result = overlayManager->RemoveOverlayManagerNode();
    EXPECT_EQ(result, 0); // OVERLAY_EXISTS = 0
}

/**
 * @tc.name: RemoveOverlayManagerNode004
 * @tc.desc: Test RemoveOverlayManagerNode when GetLastChildNotRemoving returns null.
 *           Covers the true branch of CHECK_NULL_RETURN(componentNode, OVERLAY_EXISTS).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemoveOverlayManagerNode004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    OverlayManagerInfo info;
    info.enableBackPressedEvent = true;
    overlayManager->overlayInfo_ = info;
    auto overlayNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(overlayNode, nullptr);
    overlayManager->overlayNode_ = overlayNode;
    int32_t result = overlayManager->RemoveOverlayManagerNode();
    EXPECT_EQ(result, 0); // OVERLAY_EXISTS = 0, componentNode is null
}

/**
 * @tc.name: RemoveOverlayManagerNode005
 * @tc.desc: Test RemoveOverlayManagerNode when overlayNode_ has children.
 *           Covers the true branch: RemoveFrameNodeOnOverlay and return OVERLAY_REMOVE.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, RemoveOverlayManagerNode005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    OverlayManagerInfo info;
    info.enableBackPressedEvent = true;
    overlayManager->overlayInfo_ = info;
    auto overlayNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(overlayNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(childNode, nullptr);
    overlayNode->AddChild(childNode);
    overlayManager->overlayNode_ = overlayNode;
    int32_t result = overlayManager->RemoveOverlayManagerNode();
    EXPECT_EQ(result, 1); // OVERLAY_REMOVE = 1
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay001
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay when lastNode has dialog tag.
 *           Covers the true branch of if (lastNode && EMBEDDED_DIALOG_NODE_TAG.find(...)).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay001, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay002
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay when lastNode has non-dialog tag and skipModal is true.
 *           Covers the false branch of first if (tag not in EMBEDDED_DIALOG_NODE_TAG) and
 *           the false branch of second if (skipModal true → !skipModal false).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay002, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay003
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay when currentNode has no children (lastNode null).
 *           Covers the false branch of first if (lastNode null) and
 *           the false branch of second if (skipModal true).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay003, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, true);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay004
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay when skipModal false and modalStack is empty.
 *           Covers the false branch of second if (skipModal false, IsModalEmpty true → !IsModalEmpty false).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay004, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    while (!overlayManager->modalStack_.empty()) {
        overlayManager->modalStack_.pop();
    }
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay005
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay when skipModal false and modalStack is not empty.
 *           Covers the true branch of second if (!skipModal && !IsModalEmpty()).
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay005, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    auto modalNode = FrameNode::CreateFrameNode(
        V2::MODAL_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(modalNode, nullptr);
    overlayManager->modalStack_.push(WeakPtr<FrameNode>(modalNode));
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, false);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay006
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay with ALERT_DIALOG_ETS_TAG child.
 *           Covers the true branch of first if with a different EMBEDDED_DIALOG_NODE_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay006, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay007
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay with POPUP_ETS_TAG child.
 *           Covers the true branch of first if with POPUP_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay007, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, true);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsCurrentNodeProcessRemoveOverlay008
 * @tc.desc: Test IsCurrentNodeProcessRemoveOverlay with ACTION_SHEET_DIALOG_ETS_TAG child.
 *           Covers the true branch of first if with ACTION_SHEET_DIALOG_ETS_TAG.
 * @tc.type: FUNC
 */
HWTEST_F(OverlayManagerTestFiveNg, IsCurrentNodeProcessRemoveOverlay008, TestSize.Level1)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto currentNode = FrameNode::CreateFrameNode(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    ASSERT_NE(currentNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<DialogPattern>(nullptr, nullptr));
    ASSERT_NE(childNode, nullptr);
    currentNode->AddChild(childNode);
    bool result = overlayManager->IsCurrentNodeProcessRemoveOverlay(currentNode, true);
    EXPECT_TRUE(result);
}

} // namespace OHOS::Ace::NG
