/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
namespace {
bool removeOverlayFlag = false;
} // namespace
void OverlayManager::ShowToast(const NG::ToastInfo& toastInfo, std::function<void(int32_t)>& callback)
{}

void OverlayManager::ClearToastInSubwindow() {}

void OverlayManager::ClearToast() {}

void OverlayManager::PopToast(int32_t toastId) {}

void OverlayManager::ShowPopup(int32_t targetId, const PopupInfo& popupInfo) {}

void OverlayManager::HidePopup(int32_t targetId, const PopupInfo& popupInfo) {}

void OverlayManager::ErasePopup(int32_t targetId) {}

void OverlayManager::HideAllPopups() {}

void OverlayManager::HideCustomPopups() {};

bool OverlayManager::ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset)
{
    return true;
}

void OverlayManager::ShowMenu(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu) {}

// subwindow only contains one menu instance.
void OverlayManager::ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu) {}

void OverlayManager::HideMenu(const RefPtr<FrameNode>& menu, int32_t targetId, bool isMenuOnTouch) {}

void OverlayManager::HideAllMenus() {}

void OverlayManager::DeleteMenu(int32_t targetId) {}

void OverlayManager::CleanMenuInSubWindow(int32_t targetId) {}

RefPtr<FrameNode> OverlayManager::ShowDialog(
    const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft)
{
    return nullptr;
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
    std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
    std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent, const std::vector<ButtonInfo>& buttonInfos)
{}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    removeOverlayFlag = (dialogNode != nullptr);
}

bool OverlayManager::RemoveOverlay(bool isBackPressed, bool isPageRouter)
{
    return removeOverlayFlag;
}

bool OverlayManager::RemoveOverlayInSubwindow()
{
    return removeOverlayFlag;
}

void OverlayManager::ShowIndexerPopup(int32_t targetId, RefPtr<FrameNode>& customNode)
{
    customPopupMap_[targetId] = customNode;
}

void OverlayManager::RemoveIndexerPopupById(int32_t targetId) {}

void OverlayManager::BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
    std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
    std::function<void()>&& onDisappear, int32_t targetId)
{}

void OverlayManager::MarkDirty(PropertyChangeFlag flag) {}

void OverlayManager::BindKeyboard(const std::function<void()>& keybordBuilder, int32_t targetId) {}
void OverlayManager::CloseKeyboard(int32_t targetId) {}
void OverlayManager::GetPixelMapContentNode(bool isSubwindowOverlay) {}
} // namespace OHOS::Ace::NG
