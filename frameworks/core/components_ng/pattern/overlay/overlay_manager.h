/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <functional>
#include <stack>
#include <unordered_map>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/overlay/content_cover_param.h"
#include "core/components_ng/pattern/overlay/modal_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/group_manager.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/toast/toast_layout_property.h"
#include "core/components_ng/pattern/toast/toast_view.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace {
struct ModalUIExtensionCallbacks;
} // namespace OHOS::Ace

namespace OHOS::AAFwk {
class Want;
} // namespace OHOS::AAFwk

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
    bool focusable = false;
};

struct GatherNodeChildInfo {
    WeakPtr<FrameNode> imageNode;
    OffsetF offset;
    float width = 0.0;
    float height = 0.0;
};

// StageManager is the base class for root render node to perform page switch.
class ACE_EXPORT OverlayManager : public virtual AceType {
    DECLARE_ACE_TYPE(OverlayManager, AceType);

public:
    explicit OverlayManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
    ~OverlayManager() override
    {
        popupMap_.clear();
    }
    void ShowIndexerPopup(int32_t targetId, RefPtr<FrameNode>& customNode);
    void RemoveIndexerPopupById(int32_t targetId);
    void RemoveIndexerPopup();
    void HidePopup(int32_t targetId, const PopupInfo& popupInfo);
    RefPtr<FrameNode> HidePopupWithoutAnimation(int32_t targetId, const PopupInfo& popupInfo);
    void ShowPopup(int32_t targetId, const PopupInfo& popupInfo,
        const std::function<void(int32_t)>&& onWillDismiss = nullptr, bool interactiveDismiss = true);
    void ErasePopup(int32_t targetId);
    void HideAllPopups();
    void HideCustomPopups();
    void SetPopupHotAreas(RefPtr<FrameNode> popupNode);
    void ShowPopupAnimation(const RefPtr<FrameNode>& popupNode);
    void ShowPopupAnimationNG(const RefPtr<FrameNode>& popupNode);
    void HidePopupAnimation(const RefPtr<FrameNode>& popupNode, const std::function<void()>& finish);

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
        return popupMap_.find(targetId) != popupMap_.end();
    }

    void ErasePopupInfo(int32_t targetId)
    {
        if (popupMap_.find(targetId) != popupMap_.end()) {
            popupMap_.erase(targetId);
        }
    }

    void SetDismissDialogId(int32_t id)
    {
        dismissDialogId_ = id;
    }

    int32_t GetDismissDialogId() const
    {
        return dismissDialogId_;
    }

    void ShowMenu(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu = nullptr);
    void HideMenu(const RefPtr<FrameNode>& menu, int32_t targetId, bool isMenuOnTouch = false);
    void DeleteMenu(int32_t targetId);
    void ShowMenuInSubWindow(int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode> menu = nullptr);
    void HideMenuInSubWindow(const RefPtr<FrameNode>& menu, int32_t targetId);
    RefPtr<FrameNode> GetMenuNode(int32_t targetId);
    void HideMenuInSubWindow(bool showPreviewAnimation = true, bool startDrag = false);
    void CleanMenuInSubWindow(int32_t targetId);
    void CleanPreviewInSubWindow();
    void CleanPopupInSubWindow();
    void CleanMenuInSubWindowWithAnimation();
    void HideAllMenus();

    void ClearToastInSubwindow();
    void ClearToast();
    void ShowToast(const std::string& message, int32_t duration, const std::string& bottom, bool isRightToLeft,
        const ToastShowMode& showMode = ToastShowMode::DEFAULT, int32_t alignment = -1,
        std::optional<DimensionOffset> offset = std::nullopt);

    std::unordered_map<int32_t, RefPtr<FrameNode>> GetDialogMap()
    {
        return dialogMap_;
    };
    RefPtr<FrameNode> GetDialog(int32_t dialogId);
    RefPtr<FrameNode> SetDialogMask(const DialogProperties& dialogProps);
    // customNode only used by customDialog, pass in nullptr if not customDialog
    RefPtr<FrameNode> ShowDialog(
        const DialogProperties& dialogProps, std::function<void()>&& buildFunc, bool isRightToLeft = false);
    RefPtr<FrameNode> ShowDialogWithNode(
        const DialogProperties& dialogProps, const RefPtr<NG::UINode>& customNode, bool isRightToLeft = false);
    void ShowCustomDialog(const RefPtr<FrameNode>& customNode);
    void ShowDateDialog(const DialogProperties& dialogProps, const DatePickerSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {});
    void ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
        std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {});
    void ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {});
    void ShowCalendarDialog(const DialogProperties& dialogProps, const CalendarSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {});
    void PopModalDialog(int32_t maskId);

    void CloseDialog(const RefPtr<FrameNode>& dialogNode);
    void DeleteDialogHotAreas(const RefPtr<FrameNode>& dialogNode);

    void OpenCustomDialog(const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback);
    void CloseCustomDialog(const int32_t dialogId);

    void SetSubWindowId(int32_t subWindowId)
    {
        subWindowId_ = subWindowId;
    }
    int32_t GetSubwindowId()
    {
        return subWindowId_;
    }
    void SetMaskNodeId(int32_t dialogId, int32_t maskId)
    {
        maskNodeIdMap_[dialogId] = maskId;
    }
    bool isMaskNode(int32_t maskId);
    int32_t GetMaskNodeIdWithDialogId(int32_t dialogId);

    /**  pop overlays (if any) on back press
     *
     *   @return    true if popup was removed, false if no overlay exists
     */
    bool RemoveOverlay(bool isBackPressed, bool isPageRouter = false);
    bool RemoveDialog(const RefPtr<FrameNode>& overlay, bool isBackPressed, bool isPageRouter = false);
    bool RemoveBubble(const RefPtr<FrameNode>& overlay);
    bool RemoveMenu(const RefPtr<FrameNode>& overlay);
    bool RemoveModalInOverlay();
    bool RemoveAllModalInOverlay();
    bool RemoveOverlayInSubwindow();

    void RegisterOnHideDialog(std::function<void()> callback)
    {
        onHideDialogCallback_ = callback;
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

    RefPtr<FrameNode> GetPixelMapContentNode() const;

    RefPtr<FrameNode> GetPixelMapBadgeNode() const;

    bool GetHasFilter()
    {
        return hasFilter_;
    }

    void SetHasFilter(bool hasFilter)
    {
        hasFilter_ = hasFilter;
        hasFilterActived = true;
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
    void RemoveFilterAnimation();
    void RemoveEventColumn();
    void UpdateContextMenuDisappearPosition(const NG::OffsetF& offset);

    void ResetContextMenuDragHideFinished()
    {
        isContextMenuDragHideFinished_ = false;
        dragMoveVector_ = OffsetF(0.0f, 0.0f);
        lastDragMoveVector_ = OffsetF(0.0f, 0.0f);
    }

    void SetContextMenuDragHideFinished(bool isContextMenuDragHideFinished)
    {
        isContextMenuDragHideFinished_ = isContextMenuDragHideFinished;
    }

    bool IsContextMenuDragHideFinished() const
    {
        return isContextMenuDragHideFinished_ == true;
    }

    bool IsOriginDragMoveVector() const
    {
        return dragMoveVector_.NonOffset() && lastDragMoveVector_.NonOffset();
    }

    bool IsUpdateDragMoveVector() const
    {
        return !GetUpdateDragMoveVector().NonOffset() && !lastDragMoveVector_.NonOffset();
    }

    void UpdateDragMoveVector(const NG::OffsetF& offset)
    {
        lastDragMoveVector_ = dragMoveVector_;
        dragMoveVector_ = offset;
    }

    OffsetF GetUpdateDragMoveVector() const
    {
        return dragMoveVector_ - lastDragMoveVector_;
    }

    void BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, const NG::ContentCoverParam& contentCoverParam,
        const RefPtr<FrameNode>& targetNode, int32_t sessionId = 0);
    void OnBindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, const NG::ContentCoverParam& contentCoverParam,
        const RefPtr<FrameNode>& targetNode, int32_t sessionId = 0);
    void BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildTitleNodeFunc,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        const RefPtr<FrameNode>& targetNode);
    void OnBindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        const RefPtr<FrameNode>& targetNode);
    void CloseSheet(int32_t targetId);

    void DismissSheet();
    void DismissContentCover();

    void SetDismissTargetId(int32_t targetId)
    {
        dismissTargetId_ = targetId;
    }

    void RemoveSheetNode(const RefPtr<FrameNode>& sheetNode);

    void DestroySheet(const RefPtr<FrameNode>& sheetNode, int32_t targetId);

    RefPtr<FrameNode> GetSheetMask(const RefPtr<FrameNode>& sheetNode);

    RefPtr<FrameNode> GetModal(int32_t targetId);
    void RemoveModal(int32_t targetId);
    void DeleteModal(int32_t targetId, bool needOnWillDisappear = true);
    void PopTopModalNode();

    void DeleteModalNode(int32_t targetId, RefPtr<FrameNode>& modalNode, bool isModal, bool needOnWillDisappear);

    void RemoveSheetMask(RefPtr<FrameNode>& sheetNode, RefPtr<UINode>& rootNode);

    void BindKeyboard(const std::function<void()>& keyboardBuilder, int32_t targetId);
    void CloseKeyboard(int32_t targetId);

    RefPtr<UINode> FindWindowScene(RefPtr<FrameNode> targetNode);

    // ui extension
    int32_t CreateModalUIExtension(const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks,
        bool isProhibitBack, bool isAsyncModalBinding = false);
    void CloseModalUIExtension(int32_t sessionId);

    RefPtr<FrameNode> BindUIExtensionToMenu(const RefPtr<FrameNode>& uiExtNode,
        const RefPtr<NG::FrameNode>& targetNode,  std::string longestContent, int32_t menuSize);
    SizeF CaculateMenuSize(const RefPtr<FrameNode>& menuNode,  std::string longestContent, int32_t menuSize);
    bool ShowUIExtensionMenu(const RefPtr<NG::FrameNode>& uiExtNode, NG::RectF aiRect, std::string longestContent,
        int32_t menuSize, const RefPtr<NG::FrameNode>& targetNode);

    void MarkDirty(PropertyChangeFlag flag);
    void MarkDirtyOverlay();
    float GetRootHeight() const;

    void PlaySheetMaskTransition(RefPtr<FrameNode> maskNode, bool isTransitionIn, bool needTransparent = false);

    void PlaySheetTransition(RefPtr<FrameNode> sheetNode, bool isTransitionIn, bool isFirstTransition = true,
        bool isModeChangeToAuto = false);

    void ComputeSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode);

    void ComputeSingleGearSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode);

    void ComputeDetentsSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode);

    void SetSheetHeight(float height)
    {
        sheetHeight_ = height;
    }

    const WeakPtr<UINode>& GetRootNode() const;
    const RefPtr<GroupManager>& GetGroupManager() const;

    void ModalPageLostFocus(const RefPtr<FrameNode>& node);

    void SetCustomKeyboardOption(bool supportAvoidance)
    {
        keyboardAvoidance_ = supportAvoidance;
    }

    void SupportCustomKeyboardAvoidance(RefPtr<RenderContext> context, AnimationOption option,
        RefPtr<FrameNode> customKeyboard);

    void SetCustomKeybroadHeight(float customHeight = 0.0);

    void SetFilterActive(bool actived)
    {
        hasFilterActived = actived;
    }

    void SetDismissPopupId(int32_t targetId)
    {
        dismissPopupId_ = targetId;
    }

    void DismissPopup();

    void MountGatherNodeToRootNode(const RefPtr<FrameNode>& frameNode,
        std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    void MountGatherNodeToWindowScene(const RefPtr<FrameNode>& frameNode,
        std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo,
        const RefPtr<UINode>& windowScene);
    void RemoveGatherNode();
    void RemoveGatherNodeWithAnimation();
    RefPtr<FrameNode> GetGatherNode() const
    {
        return gatherNodeWeak_.Upgrade();
    }
    std::vector<GatherNodeChildInfo> GetGatherNodeChildrenInfo()
    {
        return gatherNodeChildrenInfo_;
    }
    void RemoveMenuBadgeNode(const RefPtr<FrameNode>& menuWrapperNode);
    void RemovePreviewBadgeNode();
    void CreateOverlayNode();
    void AddFrameNodeToOverlay(const RefPtr<NG::FrameNode>& node, std::optional<int32_t> index = std::nullopt);
    void RemoveFrameNodeOnOverlay(const RefPtr<NG::FrameNode>& node);
    void ShowNodeOnOverlay(const RefPtr<NG::FrameNode>& node);
    void HideNodeOnOverlay(const RefPtr<NG::FrameNode>& node);
    void ShowAllNodesOnOverlay();
    void HideAllNodesOnOverlay();
    RefPtr<FrameNode> GetOverlayNode()
    {
        return overlayNode_;
    }
    bool CheckPageNeedAvoidKeyboard() const;

private:
    void PopToast(int32_t targetId);

    // toast should contain id to avoid multiple delete.
    std::unordered_map<int32_t, WeakPtr<FrameNode>> toastMap_;

    /**  find/register menu node and update menu's display position
     *
     *   @return     true if process is successful
     */
    bool ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset);

    // The focus logic of overlay node (menu and dialog):
    // 1. before start show animation: lower level node set unfocusabel and lost focus;
    // 2. end show animation: overlay node get focus;
    // 3. before start hide animation: lower level node set focusable;
    // 4. end hide animation: overlay node lost focus, lower level node get focus.
    void FocusOverlayNode(const RefPtr<FrameNode>& overlayNode, bool isInSubWindow = false);
    void BlurOverlayNode(const RefPtr<FrameNode>& currentOverlay, bool isInSubWindow = false);
    void BlurLowerNode(const RefPtr<FrameNode>& currentOverlay);
    void ResetLowerNodeFocusable(const RefPtr<FrameNode>& currentOverlay);
    void PostDialogFinishEvent(const WeakPtr<FrameNode>& nodeWk);
    void OnDialogCloseEvent(const RefPtr<FrameNode>& node);

    void CloseDialogInner(const RefPtr<FrameNode>& dialogNode);

    void ShowMenuAnimation(const RefPtr<FrameNode>& menu);
    void PopMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation = true, bool startDrag = false);
    void ClearMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation = true, bool startDrag = false);
    void ShowMenuClearAnimation(const RefPtr<FrameNode>& menu, AnimationOption& option,
        bool showPreviewAnimation, bool startDrag);

    void OpenDialogAnimation(const RefPtr<FrameNode>& node);
    void CloseDialogAnimation(const RefPtr<FrameNode>& node);
    void SetDialogTransitionEffect(const RefPtr<FrameNode>& node);
    void CloseDialogMatchTransition(const RefPtr<FrameNode>& node);
    void SetContainerButtonEnable(bool isEnabled);

    void SaveLastModalNode();
    void PlayTransitionEffectIn(const RefPtr<FrameNode>& topModalNode);
    void PlayTransitionEffectOut(const RefPtr<FrameNode>& topModalNode);
    void PlayDefaultModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn);
    void DefaultModalTransition(bool isTransitionIn);
    void PlayAlphaModalTransition(const RefPtr<FrameNode>& modalNode, bool isTransitionIn);
    void FireModalPageShow();
    void FireModalPageHide();

    void SetSheetBackgroundBlurStyle(const RefPtr<FrameNode>& sheetNode, const BlurStyleOption& bgBlurStyle);

    bool ModalExitProcess(const RefPtr<FrameNode>& topModalNode);
    bool ModalPageExitProcess(const RefPtr<FrameNode>& topModalNode);
    bool SheetPageExitProcess(const RefPtr<FrameNode>& topModalNode);

    void BeforeShowDialog(const RefPtr<FrameNode>& dialogNode);
    void RemoveDialogFromMap(const RefPtr<FrameNode>& node);
    bool DialogInMapHoldingFocus();
    void PlayKeyboardTransition(RefPtr<FrameNode> customKeyboard, bool isTransitionIn);
    void FireNavigationStateChange(bool show, const RefPtr<UINode>& node = nullptr);
    RefPtr<FrameNode> GetModalNodeInStack(std::stack<WeakPtr<FrameNode>>& stack);
    void PlayBubbleStyleSheetTransition(RefPtr<FrameNode> sheetNode, bool isTransitionIn);
    void CheckReturnFocus(RefPtr<FrameNode> node);
    void MountPopup(int32_t targetId, const PopupInfo& popupInfo,
        const std::function<void(int32_t)>&& onWillDismiss = nullptr, bool interactiveDismiss = true);

    int32_t GetPopupIdByNode(const RefPtr<FrameNode>& overlay);
    bool PopupInteractiveDismiss(const RefPtr<FrameNode>& overlay);
    bool PopupCallBackOnWillDismiss(const RefPtr<FrameNode>& overlay);
    bool RemovePopupInSubwindow(const RefPtr<Pattern>& pattern, const RefPtr<FrameNode>& overlay,
        const RefPtr<UINode>& rootNode);
    bool UpdatePopupMap(int32_t targetId, const PopupInfo& popupInfo);
    void PlayDefaultModalIn(const RefPtr<FrameNode>& modalNode, const RefPtr<RenderContext>& context,
        AnimationOption option, float showHeight);
    void PlayDefaultModalOut(const RefPtr<FrameNode>& modalNode, const RefPtr<RenderContext>& context,
        AnimationOption option, float showHeight);
    void OpenToastAnimation(const RefPtr<FrameNode>& toastNode, int32_t duration);
    void OnShowMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<OverlayManager> weak,
        int32_t instanceId);
    void OnPopMenuAnimationFinished(const WeakPtr<FrameNode> menuWK, const WeakPtr<UINode> rootWeak,
        const WeakPtr<OverlayManager> weak, int32_t instanceId);
    void UpdateMenuVisibility(const RefPtr<FrameNode>& menu);

    bool CheckTopModalNode(const RefPtr<FrameNode>& topModalNode, int32_t targetId);
    void HandleModalShow(std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode,
        const NG::ContentCoverParam& contentCoverParam, int32_t targetId,
        std::optional<ModalTransition> modalTransition);
    void HandleModalPop(std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode, int32_t targetId);

    RefPtr<FrameNode> overlayNode_;
    // Key: frameNode Id, Value: index
    std::unordered_map<int32_t, int32_t> frameNodeMapOnOverlay_;
    // Key: target Id, Value: PopupInfo
    std::unordered_map<int32_t, NG::PopupInfo> popupMap_;
    // K: target frameNode ID, V: menuNode
    std::unordered_map<int32_t, RefPtr<FrameNode>> menuMap_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> dialogMap_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> customPopupMap_;
    std::unordered_map<int32_t, RefPtr<FrameNode>> customKeyboardMap_;
    std::stack<WeakPtr<FrameNode>> modalStack_;
    std::list<WeakPtr<FrameNode>> modalList_;
    std::unordered_map<int32_t, WeakPtr<FrameNode>> sheetMap_;
    WeakPtr<FrameNode> lastModalNode_; // Previous Modal Node
    float sheetHeight_ { 0.0 };
    WeakPtr<UINode> rootNodeWeak_;
    int32_t dialogCount_ = 0;
    int32_t dismissTargetId_ = 0;
    int32_t dismissDialogId_ = 0;
    std::unordered_map<int32_t, int32_t> maskNodeIdMap_;
    int32_t subWindowId_;
    bool hasPixelMap_ { false };
    bool hasFilter_ { false };
    bool hasEvent_ { false };
    bool isOnAnimation_ { false };
    WeakPtr<FrameNode> pixmapColumnNodeWeak_;
    WeakPtr<FrameNode> filterColumnNodeWeak_;
    WeakPtr<FrameNode> eventColumnNodeWeak_;
    bool isContextMenuDragHideFinished_ = false;
    OffsetF dragMoveVector_ = OffsetF(0.0f, 0.0f);
    OffsetF lastDragMoveVector_ = OffsetF(0.0f, 0.0f);

    std::function<void()> onHideDialogCallback_ = nullptr;
    CancelableCallback<void()> continuousTask_;
    std::function<bool()> backPressEvent_ = nullptr;

    std::set<WeakPtr<UINode>> windowSceneSet_;

    RefPtr<NG::ClickEvent> sheetMaskClickEvent_;
    RefPtr<GroupManager> groupManager_ = MakeRefPtr<GroupManager>();

    // native modal ui extension
    bool isProhibitBack_ = false;

    std::unordered_map<int32_t, WeakPtr<FrameNode>> uiExtNodes_;
    bool keyboardAvoidance_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(OverlayManager);

    bool hasFilterActived {false};

    int32_t dismissPopupId_ = 0;

    bool hasGatherNode_ {false};
    WeakPtr<FrameNode> gatherNodeWeak_;
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H
