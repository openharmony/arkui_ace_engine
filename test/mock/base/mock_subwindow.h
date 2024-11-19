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

#ifndef FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_SUBWINDOW_H
#define FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_SUBWINDOW_H

#include "gmock/gmock.h"

#include "base/subwindow/subwindow.h"

namespace OHOS::Ace {
class ACE_EXPORT MockSubwindow : public Subwindow {
    DECLARE_ACE_TYPE(MockSubwindow, Subwindow)

public:
    MOCK_METHOD0(InitContainer, bool());
    MOCK_METHOD0(ResizeWindow, void());
    MOCK_METHOD0(GetRect, NG::RectF());
    MOCK_METHOD0(UpdatePreviewPosition, void());
    MOCK_METHOD1(GetMenuPreviewCenter, bool(NG::OffsetF& offset));
    MOCK_METHOD1(ShowMenu, void(const RefPtr<Component>& newComponent));
    MOCK_METHOD4(ShowMenuNG, void(const RefPtr<NG::FrameNode> menuNode, const NG::MenuParam& menuParam,
                                 const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset));
    MOCK_METHOD5(ShowMenuNG,
        void(std::function<void()>&& buildFunc, std::function<void()>&& previewBuildFunc,
            const NG::MenuParam& menuParam, const RefPtr<NG::FrameNode>& targetNode, const NG::OffsetF& offset));
    MOCK_METHOD1(ShowPreviewNG, bool(bool isStartDraggingFromSubWindow));
    MOCK_METHOD0(HidePreviewNG, void());
    MOCK_METHOD2(HideMenuNG, void(const RefPtr<NG::FrameNode>& menu, int32_t targetId));
    MOCK_METHOD2(HideMenuNG, void(bool showPreviewAnimation, bool startDrag));
    MOCK_METHOD4(UpdateHideMenuOffsetNG,
        void(const NG::OffsetF& offset, float meunuScale, bool isRedragStart, int32_t menuWrapperId));
    MOCK_METHOD2(ContextMenuSwitchDragPreviewAnimationtNG, void(const RefPtr<NG::FrameNode>& dragPreviewNode,
        const NG::OffsetF& offset));
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
    MOCK_METHOD0(ClearToast, void());
    MOCK_METHOD2(ShowToast, void(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>&& callback));
    MOCK_METHOD2(CloseToast, void(int32_t toastId, std::function<void(int32_t)>&& callback));
    MOCK_METHOD6(ShowDialog,
        void(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
            bool autoCancel, std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks));
    MOCK_METHOD4(ShowDialog,
        void(const PromptDialogAttr& dialogAttr, const std::vector<ButtonInfo>& buttons,
            std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks));
    MOCK_METHOD3(ShowActionMenu, void(const std::string& title, const std::vector<ButtonInfo>& button,
                                     std::function<void(int32_t, int32_t)>&& callback));
    MOCK_METHOD1(CloseDialog, void(int32_t instanceId));
    MOCK_METHOD0(GetOverlayManager, const RefPtr<NG::OverlayManager>());
    MOCK_METHOD0(RequestFocus, void());
    MOCK_METHOD0(IsFocused, bool());
    MOCK_METHOD2(OpenCustomDialog, void(const PromptDialogAttr& dialogAttr, std::function<void(int32_t)>&& callback));
    MOCK_METHOD1(CloseCustomDialog, void(const int32_t dialogId));
    MOCK_METHOD2(CloseCustomDialog, void(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback));
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
    MOCK_METHOD0(DestroyWindow, void());
    MOCK_METHOD0(ResizeDialogSubwindow, void());
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_SUBWINDOW_H
