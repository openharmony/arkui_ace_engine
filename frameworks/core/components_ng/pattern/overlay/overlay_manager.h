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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H

#include <functional>
#include <unordered_map>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
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
    void RemoveIndexerPopupById(int32_t targetId);
    void RemoveIndexerPopup();
    void UpdatePopupNode(int32_t targetId, const PopupInfo& popupInfo);
    void HidePopup(int32_t targetId, const PopupInfo& popupInfo);
    void ErasePopup(int32_t targetId);
    void HideAllPopups();
    void HideCustomPopups();

    PopupInfo GetPopupInfo(int32_t targetId) const
    {
        auto it = popupMap_.find(targetId);
        if (it == popupMap_.end()) {
            return {};
        }
        return it->second;
    }

    bool HasPopupInfo(int32_t targetId) const
    {
        if (popupMap_.find(targetId) != popupMap_.end()) {
            return true;
        }
        return false;
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
        const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft = false);
    void ShowCustomDialog(const RefPtr<FrameNode>& customNode);
    void ShowDateDialog(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    void ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
        std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    void ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);
    void ShowCalendarDialog(const DialogProperties& dialogProps, const CalendarSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent);

    void CloseDialog(const RefPtr<FrameNode>& dialogNode);

    /**  pop overlays (if any) on back press
     *
     *   @return    true if popup was removed, false if no overlay exists
     */
    bool RemoveOverlay(bool isBackPressed, bool isPageRouter = false);
    bool RemoveModalInOverlay();
    bool RemoveAllModalInOverlay();
    bool RemoveOverlayInSubwindow();

    void RegisterOnHideMenu(std::function<void()> callback)
    {
        onHideMenuCallback_ = callback;
    }

    void RegisterOnShowMenu(const std::function<void()>& callback)
    {
        onShowMenuCallback_ = callback;
    }

    void RegisterOnHideDialog(std::function<void()> callback)
    {
        onHideDialogCallback_ = callback;
    }

    void CallOnShowMenuCallback()
    {
        if (onShowMenuCallback_) {
            onShowMenuCallback_();
        }
    }

    void CallOnHideMenuCallback()
    {
        if (onHideMenuCallback_) {
            onHideMenuCallback_();
        }
    }

    void CallOnHideDialogCallback()
    {
        if (onHideDialogCallback_) {
            onHideDialogCallback_();
        }
    }

    void SetBackPressEvent(std::function<bool()> event)
    {
        backPressEvent_ = event;
    }

    bool FireBackPressEvent() const
    {
        if (backPressEvent_) {
            return backPressEvent_();
        }
        return false;
    }

#ifdef ENABLE_DRAG_FRAMEWORK
    bool GetHasPixelMap()
    {
        return hasPixelMap_;
    }

    void SetHasPixelMap(bool hasPixelMap)
    {
        hasPixelMap_ = hasPixelMap;
    }

    RefPtr<FrameNode> GetPixelMapNode()
    {
        return pixmapColumnNodeWeak_.Upgrade();
    }

    bool GetHasFilter()
    {
        return hasFilter_;
    }

    void SetHasFilter(bool hasFilter)
    {
        hasFilter_ = hasFilter;
    }

    bool GetHasEvent()
    {
        return hasEvent_;
    }

    void SetHasEvent(bool hasEvent)
    {
        hasEvent_ = hasEvent;
    }

    bool GetIsOnAnimation()
    {
        return isOnAnimation_;
    }

    void SetIsOnAnimation(bool isOnAnimation)
    {
        isOnAnimation_ = isOnAnimation;
    }

    void SetFilterColumnNode(const RefPtr<FrameNode>& columnNode)
    {
        filterColumnNodeWeak_ = columnNode;
    }
    void MountFilterToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene);
    void MountPixelMapToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene);
    void MountEventToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene);
    void MountPixelMapToRootNode(const RefPtr<FrameNode>& columnNode);
    void MountEventToRootNode(const RefPtr<FrameNode>& columnNode);
    void RemovePixelMap();
    void RemovePixelMapAnimation(bool startDrag, double x, double y);
    void UpdatePixelMapScale(float& scale);
    void RemoveFilter();
    void RemoveEventColumn();
#endif // ENABLE_DRAG_FRAMEWORK
    void BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, int32_t targetId);

    void BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, int32_t targetId);

    void DestroySheet(const RefPtr<FrameNode>& sheetNode, int32_t targetId);

    static void DestroySheetMask(const RefPtr<FrameNode>& sheetNode);

    void DeleteModal(int32_t targetId);

    RefPtr<UINode> FindWindowScene(RefPtr<FrameNode> targetNode);

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

    void SetShowMenuAnimation(const RefPtr<FrameNode>& menu, bool isInSubWindow = false);
    void PopMenuAnimation(const RefPtr<FrameNode>& menu);

    void OpenDialogAnimation(const RefPtr<FrameNode>& node);
    void CloseDialogAnimation(const RefPtr<FrameNode>& node);

    void SaveLastModalNode();
    void PlayDefaultModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn);
    void DefaultModalTransition(bool isTransitionIn);
    void PlayAlphaModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn);
    void FireModalPageShow();
    void FireModalPageHide();

    void PlaySheetTransition(RefPtr<FrameNode> sheetNode, bool isTransitionIn, bool isFirstTransition = true);

    void ComputeSheetOffset(NG::SheetStyle& sheetStyle);
    bool ModalExitProcess(const RefPtr<FrameNode>& topModalNode);

    void BeforeShowDialog(const RefPtr<FrameNode>& dialogNode);
    void RemoveDialogFromMap(const RefPtr<FrameNode>& node);
    bool DialogInMapHoldingFocus();

    // Key: target Id, Value: PopupInfo
    std::unordered_map<int32_t, NG::PopupInfo> popupMap_;
    // K: target frameNode ID, V: menuNode
    std::unordered_map<int32_t, RefPtr<FrameNode>> menuMap_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> dialogMap_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> customPopupMap_;
    std::stack<WeakPtr<FrameNode>> modalStack_;
    std::list<WeakPtr<FrameNode>> modalList_;
    WeakPtr<FrameNode> lastModalNode_;
    float sheetHeight_ {0.0};
    WeakPtr<UINode> rootNodeWeak_;
#ifdef ENABLE_DRAG_FRAMEWORK
    bool hasPixelMap_ {false};
    bool hasFilter_ {false};
    bool hasEvent_ {false};
    bool isOnAnimation_ {false};
    WeakPtr<FrameNode> pixmapColumnNodeWeak_;
    WeakPtr<FrameNode> filterColumnNodeWeak_;
    WeakPtr<FrameNode> eventColumnNodeWeak_;
#endif // ENABLE_DRAG_FRAMEWORK

    std::function<void()> onHideMenuCallback_ = nullptr;
    std::function<void()> onHideDialogCallback_ = nullptr;
    std::function<void()> onShowMenuCallback_;
    CancelableCallback<void()> continuousTask_;
    std::function<bool()> backPressEvent_ = nullptr;

    std::set<WeakPtr<UINode>> windowSceneSet_;

    ACE_DISALLOW_COPY_AND_MOVE(OverlayManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H
