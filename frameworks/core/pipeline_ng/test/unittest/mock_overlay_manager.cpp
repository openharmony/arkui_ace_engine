/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
}
void OverlayManager::ShowToast(
    const std::string& message, int32_t duration, const std::string& bottom, bool isRightToLeft)
{}

void OverlayManager::PopToast(int32_t toastId) {}

void OverlayManager::UpdatePopupNode(int32_t targetId, const PopupInfo& popupInfo) {}

void OverlayManager::HidePopup(int32_t targetId, const PopupInfo& popupInfo) {}

void OverlayManager::HideAllPopups() {}

bool OverlayManager::ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset)
{
    return true;
}

void OverlayManager::ShowMenu(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu) {}

// subwindow only contains one menu instance.
void OverlayManager::ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu) {}

void OverlayManager::HideMenu(int32_t targetId) {}

void OverlayManager::HideAllMenus() {}

void OverlayManager::DeleteMenu(int32_t targetId) {}

void OverlayManager::CleanMenuInSubWindow() {}

RefPtr<FrameNode> OverlayManager::ShowDialog(
    const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft)
{
    return nullptr;
}

void OverlayManager::ShowDateDialog(const DialogProperties& dialogProps,
    std::map<std::string, PickerDate> datePickerProperty, bool isLunar,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{}

void OverlayManager::ShowTimeDialog(const DialogProperties& dialogProps,
    std::map<std::string, PickerTime> timePickerProperty, bool isUseMilitaryTime, PickerDate dialogTitleDate,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{}

void OverlayManager::ShowTextDialog(const DialogProperties& dialogProps, uint32_t selected, const Dimension& height,
    const std::vector<std::string>& getRangeVector, std::map<std::string, NG::DialogTextEvent> dialogEvent,
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{}

void OverlayManager::CloseDialog(const RefPtr<FrameNode>& dialogNode)
{
    removeOverlayFlag = (dialogNode != nullptr);
}

bool OverlayManager::RemoveOverlay()
{
    return removeOverlayFlag;
}
} // namespace OHOS::Ace::NG
