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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H

#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

struct PopupInfo {
    int32_t popupId = -1;
    WeakPtr<FrameNode> target;
    RefPtr<FrameNode> popupNode;
    bool markNeedUpdate = false;
    bool isCurrentOnShow = false;
    bool isBlockEvent = true;
    SizeF targetSize;
    OffsetF targetOffset;
};

// StageManager is the base class for root render node to perform page switch.
class ACE_EXPORT OverlayManager : public virtual AceType {
    DECLARE_ACE_TYPE(OverlayManager, AceType);

public:
    explicit OverlayManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
    ~OverlayManager() override
    {
        LOGI("OverlayManager Destructor.");
        popupMap_.clear();
    }
    void ShowIndexerPopup(int32_t targetId, RefPtr<FrameNode>& customNode);
    void RemoveIndexerPopup();
    void UpdatePopupNode(int32_t targetId, const PopupInfo& popupInfo);
    void HidePopup(int32_t targetId, const PopupInfo& popupInfo);
    void ErasePopup(int32_t targetId);
    void HideAllPopups();

    PopupInfo GetPopupInfo(int32_t targetId) const
    {
        auto it = popupMap_.find(targetId);
        if (it == popupMap_.end()) {
            return {};
        }
        return it->second;
    }

    void ShowMenu(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu = nullptr);
    void HideMenu(int32_t targetId);
    void DeleteMenu(int32_t targetId);
    void ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu = nullptr);
    void HideMenuInSubWindow(int32_t targetId);
    void HideMenuInSubWindow();
    void CleanMenuInSubWindow();
    void HideAllMenus();

    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom, bool isRightToLeft);

    // customNode only used by customDialog, pass in nullptr if not customDialog
    RefPtr<FrameNode> ShowDialog(
        const DialogProperties& dialogProps, const RefPtr<UINode>& customNode, bool isRightToLeft = false);
    void ShowDateDialog(const DialogProperties& dialogProps, std::map<std::string, PickerDate> datePickerProperty,
        bool isLunar, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    void ShowTimeDialog(const DialogProperties& dialogProps, std::map<std::string, PickerTime> timePickerProperty,
        bool isUseMilitaryTime, PickerDate dialogTitleDate, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    void ShowTextDialog(const DialogProperties& dialogProps, uint32_t selected, const Dimension& height,
        const std::vector<std::string>& getRangeVector, std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);

    void CloseDialog(const RefPtr<FrameNode>& dialogNode);

    /**  pop overlays (if any) on back press
     *
     *   @return    true if popup was removed, false if no overlay exists
     */
    bool RemoveOverlay();
    bool RemoveOverlayInSubwindow();

    void RegisterOnHideMenu(std::function<void()> callback)
    {
        onHideMenuCallback_ = callback;
    }

private:
    void PopToast(int32_t targetId);

    // toast should contain id to avoid multiple delete.
    std::unordered_map<int32_t, WeakPtr<FrameNode>> toastMap_;

    /**  find/register menu node and update menu's display position
     *
     *   @return     true if process is successful
     */
    bool ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset);

    void FocusOverlayNode(const RefPtr<FrameNode>& overlayNode, bool isInSubWindow = false);
    void BlurOverlayNode(bool isInSubWindow = false);

    void ShowMenuAnimation(const RefPtr<FrameNode>& menu, bool isInSubWindow = false);
    void PopMenuAnimation(const RefPtr<FrameNode>& menu);

    void OpenDialogAnimation(const RefPtr<FrameNode>& node);
    void CloseDialogAnimation(const RefPtr<FrameNode>& node);

    // Key: target Id, Value: PopupInfo
    std::unordered_map<int32_t, NG::PopupInfo> popupMap_;
    // K: target frameNode ID, V: menuNode
    std::unordered_map<int32_t, RefPtr<FrameNode>> menuMap_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> customPopupMap_;
    WeakPtr<UINode> rootNodeWeak_;
    CancelableCallback<void()> continuousTask_;

    std::function<void()> onHideMenuCallback_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(OverlayManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H
