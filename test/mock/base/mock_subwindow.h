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

#include "frameworks/base/subwindow/subwindow.h"

namespace OHOS::Ace {
class ACE_EXPORT MockSubwindow : public Subwindow {
    DECLARE_ACE_TYPE(MockSubwindow, Subwindow)

public:
    MOCK_METHOD0(InitContainer, void());
    MOCK_METHOD0(ResizeWindow, void());
    MOCK_METHOD0(GetRect, NG::RectF());
    MOCK_METHOD1(ShowMenu, void(const RefPtr<Component>& newComponent));
    MOCK_METHOD3(ShowMenuNG, void(const RefPtr<NG::FrameNode> menuNode, int32_t targetId, const NG::OffsetF& offset));
    MOCK_METHOD1(HideMenuNG, void(int32_t targetId));
    MOCK_METHOD0(HideMenuNG, void());
    MOCK_METHOD2(ShowPopup, void(const RefPtr<Component>& newComponent, bool disableTouchEvent));
    MOCK_METHOD2(ShowPopupNG, void(int32_t targetId, const NG::PopupInfo& popupInfo));
    MOCK_METHOD1(HidePopupNG, void(int32_t targetId));
    MOCK_METHOD0(HidePopupNG, void());
    MOCK_METHOD2(GetPopupInfoNG, void(int32_t targetId, NG::PopupInfo& popupInfo));
    MOCK_METHOD1(CancelPopup, bool(const std::string& id));
    MOCK_METHOD0(CloseMenu, void());
    MOCK_METHOD0(ClearMenu, void());
    MOCK_METHOD0(ClearMenuNG, void());
    MOCK_METHOD2(
        ShowDialogNG, RefPtr<NG::FrameNode>(const DialogProperties& dialogProps, std::function<void()>&& buildFunc));
    MOCK_METHOD0(HideSubWindowNG, void());
    MOCK_CONST_METHOD0(GetChildContainerId, int32_t());
    MOCK_METHOD0(GetShown, bool());
    MOCK_METHOD2(SetHotAreas, void(const std::vector<Rect>& rects, int32_t overlayId));
    MOCK_CONST_METHOD0(GetParentWindowRect, Rect());
    MOCK_METHOD3(ShowToast, void(const std::string& message, int32_t duration, const std::string& bottom));
    MOCK_METHOD6(ShowDialog,
        void(const std::string& title, const std::string& message, const std::vector<ButtonInfo>& buttons,
            bool autoCancel, std::function<void(int32_t, int32_t)>&& callback, const std::set<std::string>& callbacks));
    MOCK_METHOD3(ShowActionMenu, void(const std::string& title, const std::vector<ButtonInfo>& button,
                                     std::function<void(int32_t, int32_t)>&& callback));
    MOCK_METHOD1(CloseDialog, void(int32_t instanceId));
    MOCK_METHOD0(GetOverlayManager, const RefPtr<NG::OverlayManager>());
    MOCK_METHOD0(RequestFocus, void());
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_BASE_MOCK_SUBWINDOW_H
