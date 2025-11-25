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

#ifndef CAPI_STUBS_MOCK_SUB_WINDOW_BIND_H
#define CAPI_STUBS_MOCK_SUB_WINDOW_BIND_H
#include <gmock/gmock.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "base/subwindow/subwindow_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/capi/stubs/mock_subwindow_bind.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MockSubwindowBind : public Subwindow {
    DECLARE_ACE_TYPE(MockSubwindowBind, Subwindow)

public:
    void InitContainer() override {}
    MOCK_METHOD0(ResizeWindow, void());
    MOCK_METHOD0(ResizeWindowForMenu, void());
    MOCK_METHOD0(GetRect, NG::RectF());
    MOCK_METHOD0(UpdatePreviewPosition, void());
    MOCK_METHOD1(GetMenuPreviewCenter, bool(NG::OffsetF& offset));
    MOCK_METHOD1(ShowMenu, void(const RefPtr<Component>& newComponent));
    MOCK_METHOD1(ShowPreviewNG, bool(bool isStartDraggingFromSubWindow));
    MOCK_METHOD0(HidePreviewNG, void());
    MOCK_METHOD2(HideMenuNG, void(const RefPtr<NG::FrameNode>& menu, int32_t targetId));
    MOCK_METHOD2(HideMenuNG, void(bool showPreviewAnimation, bool startDrag));
    MOCK_METHOD4(UpdateHideMenuOffsetNG,
        void(const NG::OffsetF& offset, float meunuScale, bool isRedragStart, int32_t menuWrapperId));
    MOCK_METHOD2(ContextMenuSwitchDragPreviewAnimationtNG,
        void(const RefPtr<NG::FrameNode>& dragPreviewNode, const NG::OffsetF& offset));
    MOCK_METHOD2(ShowPopup, void(const RefPtr<Component>& newComponent, bool disableTouchEvent));
    MOCK_METHOD4(ShowPopupNG, void(int32_t targetId, const NG::PopupInfo& popupInfo,
                                  const std::function<void(int32_t)>&& onWillDismiss, bool interactiveDismiss));
    MOCK_METHOD1(HidePopupNG, void(int32_t targetId));
    MOCK_METHOD0(ClearPopupNG, void());
    MOCK_METHOD2(GetPopupInfoNG, void(int32_t targetId, NG::PopupInfo& popupInfo));
    MOCK_METHOD1(CancelPopup, bool(const std::string& id));
    MOCK_METHOD0(CloseMenu, void());
    MOCK_METHOD0(ClearMenu, void());
    MOCK_METHOD3(ClearMenuNG, void(int32_t targetId, bool inWindow, bool showAnimation));
    MOCK_METHOD2(
        ShowDialogNG, RefPtr<NG::FrameNode>(const DialogProperties& dialogProps, std::function<void()>&& buildFunc));
    MOCK_METHOD2(ShowDialogNGWithNode, RefPtr<NG::FrameNode>(const DialogProperties&, const RefPtr<NG::UINode>&));
    MOCK_METHOD1(CloseDialogNG, void(const RefPtr<NG::FrameNode>& dialogNode));
    MOCK_METHOD0(HideSubWindowNG, void());
    MOCK_CONST_METHOD0(GetChildContainerId, int32_t());
    MOCK_METHOD0(GetShown, bool());
    MOCK_METHOD2(SetHotAreas, void(const std::vector<Rect>& rects, int32_t overlayId));
    MOCK_CONST_METHOD0(GetParentWindowRect, Rect());
    MOCK_CONST_METHOD0(GetUIExtensionHostWindowRect, Rect());
    MOCK_CONST_METHOD0(GetFoldExpandAvailableRect, Rect());
    MOCK_CONST_METHOD0(CheckHostWindowStatus, bool());
    MOCK_METHOD0(ClearToast, void());
    MOCK_METHOD2(ShowToast, void(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback));
    MOCK_METHOD2(CloseToast, void(int32_t toastId, std::function<void(int32_t)>&& callback));
    MOCK_METHOD6(ShowDialog,
        void(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
            bool autoCancel, std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks));
    MOCK_METHOD4(
        ShowDialog, void(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
                        std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks));
    MOCK_METHOD3(ShowActionMenu, void(const std::string& title, const std::vector<ButtonInfo>& button,
                                     std::function<void(int32_t, int32_t)>&& callback));
    MOCK_METHOD1(CloseDialog, void(int32_t instanceId));
    MOCK_METHOD0(GetOverlayManager, const RefPtr<NG::OverlayManager>());
    MOCK_METHOD0(RequestFocus, void());
    MOCK_METHOD0(IsFocused, bool());
    MOCK_METHOD2(OpenCustomDialog, void(const PromptDialogAttr& dialogAttr, std::function<void(int32_t)>&& callback));
    MOCK_METHOD1(CloseCustomDialog, void(const int32_t dialogId));
    MOCK_METHOD2(CloseCustomDialog, void(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)>&& callback));
    MOCK_METHOD2(
        OpenCustomDialogNG, void(const DialogProperties& dialogProps, std::function<void(int32_t)>&& callback));
    MOCK_METHOD1(CloseCustomDialogNG, void(int32_t dialogId));
    MOCK_METHOD2(CloseCustomDialogNG, void(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)>&& callback));
    MOCK_METHOD3(UpdateCustomDialogNG, void(const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps,
                                           std::function<void(int32_t)>&& callback));
    MOCK_METHOD0(ResizeWindowForFoldStatus, void());
    MOCK_METHOD1(ResizeWindowForFoldStatus, void(int32_t parentContainerId));
    MOCK_METHOD0(MarkDirtyDialogSafeArea, void());
    MOCK_METHOD0(Close, bool());
    MOCK_CONST_METHOD0(IsFreeMultiWindow, bool());
    MOCK_METHOD1(OnFreeMultiWindowSwitch, void(bool enable));
    MOCK_METHOD1(RegisterFreeMultiWindowSwitchCallback, int32_t(std::function<void(bool)>&& callback));
    MOCK_METHOD1(UnRegisterFreeMultiWindowSwitchCallback, void(int32_t callbackId));
    MOCK_METHOD1(SetRect, void(const NG::RectF& rect));
    MOCK_METHOD0(IsToastSubWindow, bool());
    MOCK_METHOD0(ResizeDialogSubwindow, void());
    MOCK_METHOD0(DestroyWindow, void());
    MOCK_METHOD0(GetDisplayId, uint64_t());
    MOCK_METHOD1(IsSameDisplayWithParentWindow, bool(bool useInitializedId));
    MOCK_METHOD1(ShowSelectOverlay, bool(const RefPtr<NG::FrameNode>& overlayNode));
    MOCK_METHOD4(ShowMenuNG, void(const RefPtr<NG::FrameNode> customNode, const NG::MenuParam& menuParam,
                                 const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset));
    void ShowBindSheetNG(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<NG::UINode>(int32_t)>&& buildNodeFunc,
        std::function<RefPtr<NG::UINode>()>&& buildtitleNodeFunc, NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        const RefPtr<NG::FrameNode>& targetNode) override {}
    int32_t ShowBindSheetByUIContext(
        const RefPtr<NG::FrameNode>& sheetContentNode, std::function<void()>&& buildtitleNodeFunc,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange,
        std::function<void()>&& sheetSpringBack,
        int32_t targetId) override
    {
        return 0;
    }
    void ShowMenuNG(std::function<void()>&& buildFunc, std::function<void()>&& previewBuildFunc,
        const NG::MenuParam& menuParam, const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset) override
    {
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        RefPtr<NG::UINode> previewCustomNode;
        if (previewBuildFunc && menuParam.previewMode == MenuPreviewMode::CUSTOM) {
            previewBuildFunc();
            previewCustomNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        if (menuParam.onAppear) {
            menuParam.onAppear();
        }
        if (menuParam.onDisappear) {
            menuParam.onDisappear();
        }
        if (menuParam.aboutToAppear) {
            menuParam.aboutToAppear();
        }
        if (menuParam.aboutToDisappear) {
            menuParam.aboutToDisappear();
        }
    }

    MenuWindowState GetDetachState() override
    {
        return MenuWindowState::DEFAULT;
    }

    MOCK_METHOD2(ShowToastStatic, void(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback));
    MOCK_METHOD2(CloseToastStatic, void(int32_t toastId, std::function<void(int32_t)>&& callback));
    MOCK_METHOD2(ShowDialogStatic, void(DialogProperties& dialogProps,
        std::function<void(int32_t, int32_t)>&& callback));
    MOCK_METHOD2(ShowActionMenuStatic, void(DialogProperties& dialogProps,
        std::function<void(int32_t, int32_t)>&& callback));
    MOCK_METHOD2(OpenCustomDialogStatic, void(DialogProperties &dialogProps, std::function<void(int32_t)> &&callback));
    MOCK_METHOD(bool, SetFollowParentWindowLayoutEnabled, (bool enable));
    MOCK_METHOD(void, SwitchFollowParentWindowLayout, (bool freeMultiWindowEnable));
    MOCK_METHOD(bool, NeedFollowParentWindowLayout, ());
    MOCK_METHOD(void, AddFollowParentWindowLayoutNode, (int32_t nodeId));
    MOCK_METHOD(void, RemoveFollowParentWindowLayoutNode, (int32_t nodeId));
    MOCK_METHOD(void, SetNodeId, (int32_t nodeId));
    MOCK_METHOD(int32_t, GetNodeId, (), (const));
    MOCK_METHOD(int32_t, UpdateBindSheetByUIContext, (const RefPtr<NG::FrameNode> &, const NG::SheetStyle &, bool));
    MOCK_METHOD(int32_t, CloseBindSheetByUIContext, (const RefPtr<NG::FrameNode> &));
    MOCK_METHOD(void, SetWindowAnchorInfo, (const NG::OffsetF&, SubwindowType, int32_t));
};
} // namespace OHOS::Ace::NG

#endif // CAPI_STUBS_MOCK_SUB_WINDOW_BIND_H