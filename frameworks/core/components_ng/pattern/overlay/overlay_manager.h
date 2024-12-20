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
#include "base/want/want_wrap.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/base/frame_node.h"
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
#include "interfaces/inner_api/ace/modal_ui_extension_config.h"

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
    float width = 0.0f;
    float height = 0.0f;
    float halfWidth = 0.0f;
    float halfHeight = 0.0f;
};

struct DismissTarget {
    DismissTarget() {}
    explicit DismissTarget(int32_t inputTargetId) : targetIdOfModal(inputTargetId) {}
    explicit DismissTarget(const SheetKey& index) : sheetKey(index)
    {
        targetIsSheet = true;
    }

    int32_t GetTargetId()
    {
        return targetIsSheet ? sheetKey.targetId : targetIdOfModal;
    }

    int32_t targetIdOfModal = -1;
    SheetKey sheetKey;
    bool targetIsSheet = false;
};

struct CustomKeyboardOffsetInfo {
    float finalOffset = 0.0f;
    float inAniStartOffset = 0.0f;
    float outAniEndOffset = 0.0f;
};

// StageManager is the base class for root render node to perform page switch.
class ACE_FORCE_EXPORT OverlayManager : public virtual AceType {
    DECLARE_ACE_TYPE(OverlayManager, AceType);

public:
    explicit OverlayManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
    ~OverlayManager() override;
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
    void CleanHoverImagePreviewInSubWindow(const RefPtr<FrameNode>& flexNode);
    void CleanPopupInSubWindow();
    void CleanMenuInSubWindowWithAnimation();
    void HideAllMenus();

    void ClearToastInSubwindow();
    void ClearToast();
    void ShowToast(const NG::ToastInfo& toastInfo, const std::function<void(int32_t)>& callback);
    void CloseToast(int32_t toastId, const std::function<void(int32_t)>& callback);

    void FireAutoSave(const RefPtr<FrameNode>& ContainerNode);

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
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {},
        const std::vector<ButtonInfo>& buttonInfos = std::vector<ButtonInfo>({}));
    void ShowTimeDialog(const DialogProperties& dialogProps, const TimePickerSettingData& settingData,
        std::map<std::string, PickerTime> timePickerProperty, std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {},
        const std::vector<ButtonInfo>& buttonInfos = std::vector<ButtonInfo>({}));
    void ShowTextDialog(const DialogProperties& dialogProps, const TextPickerSettingData& settingData,
        std::map<std::string, NG::DialogTextEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {},
        const std::vector<ButtonInfo>& buttonInfos = std::vector<ButtonInfo>({}));
    void ShowCalendarDialog(const DialogProperties& dialogProps, const CalendarSettingData& settingData,
        std::map<std::string, NG::DialogEvent> dialogEvent,
        std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent,
        std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = {},
        const std::vector<ButtonInfo>& buttonInfos = std::vector<ButtonInfo>({}));
    void PopModalDialog(int32_t maskId);

    void CloseDialog(const RefPtr<FrameNode>& dialogNode);
    void DeleteDialogHotAreas(const RefPtr<FrameNode>& dialogNode);

    void OpenCustomDialog(const DialogProperties& dialogProps, std::function<void(int32_t)> &&callback);
    void CloseCustomDialog(const int32_t dialogId);
    void CloseCustomDialog(const WeakPtr<NG::UINode>& node, std::function<void(int32_t)> &&callback);
    void UpdateCustomDialog(const WeakPtr<NG::UINode>& node, const DialogProperties& dialogProps,
        std::function<void(int32_t)> &&callback);

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

    void SetModalDialogDisplayId(uint64_t displayId)
    {
        if (displayId != -1ULL) {
            dialogDisplayId_ = displayId;
        }
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
    bool RemoveDragPreview(const RefPtr<FrameNode>& overlay);
    bool RemoveModalInOverlay();
    bool RemoveAllModalInOverlay(bool isRouterTransition = true);
    bool RemoveAllModalInOverlayByStack();
    bool RemoveAllModalInOverlayByList();
    bool OnRemoveAllModalInOverlayByList();
    void AfterRemoveAllModalInOverlayByList();
    bool IsModalUiextensionNode(const RefPtr<FrameNode>& topModalNode);
    bool IsProhibitedRemoveByRouter(const RefPtr<FrameNode>& topModalNode);
    bool IsProhibitedRemoveByNavigation(const RefPtr<FrameNode>& topModalNode);
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

    bool GetHasDragPixelMap() const
    {
        return hasDragPixelMap_;
    }

    void SetHasDragPixelMap(bool hasDragPixelMap)
    {
        hasDragPixelMap_ = hasDragPixelMap;
    }

    bool GetHasGatherNode()
    {
        return hasGatherNode_;
    }

    RefPtr<FrameNode> GetPixelMapNode()
    {
        return pixmapColumnNodeWeak_.Upgrade();
    }

    RefPtr<FrameNode> GetPixelMapContentNode(bool isSubwindowOverlay = false) const;

    RefPtr<FrameNode> GetPixelMapContentNodeForSubwindow() const;

    RefPtr<FrameNode> GetDragPixelMapContentNode() const;

    RefPtr<FrameNode> GetPixelMapBadgeNode() const;

    RefPtr<FrameNode> GetDragPixelMapBadgeNode() const;

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
    void MountPixelMapToWindowScene(
        const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene, bool isDragPixelMap = false);
    void MountEventToWindowScene(const RefPtr<FrameNode>& columnNode, const RefPtr<UINode>& windowScene);
    void MountPixelMapToRootNode(const RefPtr<FrameNode>& columnNode, bool isDragPixelMap = false);
    void MountEventToRootNode(const RefPtr<FrameNode>& columnNode);
    void RemovePixelMap();
    void RemovePixelMapAnimation(bool startDrag, double x, double y, bool isSubwindowOverlay = false);
    void RemoveDragPixelMap();
    void UpdatePixelMapScale(float& scale);
    void RemoveFilter();
    void RemoveFilterAnimation();
    void RemoveEventColumn();
    void UpdatePixelMapPosition(bool isSubwindowOverlay = false);
    void UpdateContextMenuDisappearPosition(const NG::OffsetF& offset, float menuScale = 1.0f,
	    bool isRedragStart = false, int32_t menuWrapperId = -1);
    void ContextMenuSwitchDragPreviewAnimation(const RefPtr<NG::FrameNode>& dragPreviewNode,
        const NG::OffsetF& offset);
    bool GetMenuPreviewCenter(NG::OffsetF& offset);

    void ResetContextMenuDragHideFinished()
    {
        isContextMenuDragHideFinished_ = false;
        dragMoveVector_ = OffsetF(0.0f, 0.0f);
        lastDragMoveVector_ = OffsetF(0.0f, 0.0f);
    }

    void ResetContextMenuRestartDragVector()
    {
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
        std::function<void()>&& shouldDismiss, std::function<void(const int32_t info)>&& onWillDismiss,
        std::function<void()>&& onWillAppear,  std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        const RefPtr<FrameNode>& targetNode);
    void OnBindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void(const int32_t info)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        const RefPtr<FrameNode>& targetNode);
    void CloseSheet(const SheetKey& sheetKey);
    void InitSheetMask(
        const RefPtr<FrameNode>& maskNode, const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle);
    bool IsModalEmpty() const
    {
        return modalStack_.empty();
    }
    bool HasModalPage();
    void DismissSheet();
    void DismissContentCover();
    void SheetSpringBack();

    void OpenBindSheetByUIContext(
        const RefPtr<FrameNode>& sheetContentNode, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange,
        std::function<void()>&& sheetSpringBack,
        std::function<void(const int32_t, const int32_t)> cleanViewContextMapCallback,
        const RefPtr<FrameNode>& targetNode);
    void UpdateBindSheetByUIContext(const RefPtr<NG::FrameNode>& sheetContentNode,
        NG::SheetStyle& sheetStyle, int32_t targetId, bool isPartialUpdate);
    void CloseBindSheetByUIContext(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t targetId);
    void SetDismissTarget(const DismissTarget& dismissTarget)
    {
        dismissTarget_ = dismissTarget;
    }
    void SetDismissSheet(int32_t sheetId)
    {
        dismissSheetId_ = sheetId;
    }
    int32_t GetDismissSheet() const
    {
        return dismissSheetId_;
    }
    void RemoveSheetNode(const RefPtr<FrameNode>& sheetNode);

    void DestroySheet(const RefPtr<FrameNode>& sheetNode, const SheetKey& sheetKey);
    void CleanSheet(const RefPtr<FrameNode>& sheetNode, const SheetKey& sheetKey);

    RefPtr<FrameNode> GetSheetMask(const RefPtr<FrameNode>& sheetNode);

    RefPtr<FrameNode> GetModal(int32_t targetId);
    void RemoveModal(int32_t targetId);
    void DeleteModal(int32_t targetId, bool needOnWillDisappear = true);
    void PopTopModalNode();

    void DeleteModalNode(int32_t targetId, RefPtr<FrameNode>& modalNode, bool isModal, bool needOnWillDisappear);

    void BindKeyboard(const std::function<void()>& keyboardBuilder, int32_t targetId);
    void BindKeyboardWithNode(const RefPtr<UINode>& keyboard, int32_t targetId);
    void CloseKeyboard(int32_t targetId);
    void UpdateCustomKeyboardPosition();

    RefPtr<UINode> FindWindowScene(RefPtr<FrameNode> targetNode);

    // ui extension
    bool HandleUIExtNodeSize(const AAFwk::Want& want, RefPtr<FrameNode> uiExtNode);
    bool HandleUIExtNodeAngle(int32_t uiExtNodeAngle, RefPtr<FrameNode> uiExtNode);
    bool HandleUIExtNodeTransform(const AAFwk::Want& want, RefPtr<FrameNode> uiExtNode);
    bool UIExtNodeAngleValid(int32_t uiExtNodeAngle);
    int32_t CreateModalUIExtension(const RefPtr<WantWrap>& want, const ModalUIExtensionCallbacks& callbacks,
        const ModalUIExtensionConfig& config);
    int32_t CreateModalUIExtension(const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks,
        const ModalUIExtensionConfig& config);
    void CloseModalUIExtension(int32_t sessionId);
    void UpdateModalUIExtensionConfig(
        int32_t sessionId, const ModalUIExtensionAllowedUpdateConfig& config);
    static ModalStyle SetUIExtensionModalStyleAndGet(bool prohibitedRemoveByRouter,
        bool isAllowAddChildBelowModalUec, bool prohibitedRemoveByNavigation);

    RefPtr<FrameNode> BuildAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions);
    RefPtr<FrameNode> CreateAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
        const RefPtr<FrameNode>& targetNode);
    bool ShowAIEntityMenu(const std::vector<std::pair<std::string, std::function<void()>>>& menuOptions,
        const RectF& aiRect, const RefPtr<FrameNode>& targetNode);
    void CloseAIEntityMenu(int32_t targetId);

    void MarkDirty(PropertyChangeFlag flag);
    void MarkDirtyOverlay();
    float GetRootHeight() const;
    float GetRootWidth() const;

    void PlaySheetMaskTransition(RefPtr<FrameNode> maskNode, bool isTransitionIn);

    void PlaySheetTransition(RefPtr<FrameNode> sheetNode, bool isTransitionIn, bool isFirstTransition = true);

    void ComputeSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode);

    void ComputeSingleGearSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode);

    void ComputeDetentsSheetOffset(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode);

    void CheckDeviceInLandscape(NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode, float& sheetTopSafeArea);

    void SetSheetHeight(float height)
    {
        sheetHeight_ = height;
    }

    const WeakPtr<UINode>& GetRootNode() const;
    const RefPtr<GroupManager>& GetGroupManager() const;

    void ModalPageLostFocus(const RefPtr<FrameNode>& node);

    void SetCustomKeyboardOption(bool supportAvoidance);

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
        const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    void MountGatherNodeToWindowScene(const RefPtr<FrameNode>& frameNode,
        const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo,
        const RefPtr<UINode>& windowScene);
    void RemoveGatherNode();
    void RemoveGatherNodeWithAnimation();
    void UpdateGatherNodeToTop();
    RefPtr<FrameNode> GetGatherNode() const
    {
        return gatherNodeWeak_.Upgrade();
    }
    const std::vector<GatherNodeChildInfo>& GetGatherNodeChildrenInfo()
    {
        return gatherNodeChildrenInfo_;
    }
    bool IsGatherWithMenu() const
    {
        return isGatherWithMenu_;
    }
    void SetIsGatherWithMenu(bool isGatherWithMenu)
    {
        isGatherWithMenu_ = isGatherWithMenu;
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
    void AvoidCustomKeyboard(int32_t targetId, float safeHeight);
    void ShowFilterAnimation(const RefPtr<FrameNode>& columnNode);
    void EraseMenuInfo(int32_t targetId)
    {
        if (menuMap_.find(targetId) != menuMap_.end()) {
            menuMap_.erase(targetId);
        }
    }

    bool IsRootExpansive() const;
    void DumpOverlayInfo() const;
    void ReloadBuilderNodeConfig();

    bool IsMenuShow() const
    {
        return isMenuShow_;
    }

    void SetIsMenuShow(bool isMenuShow);

    void SetIsAttachToCustomNode(bool isAttachToCustomNode)
    {
        isAttachToCustomNode_ = isAttachToCustomNode;
    }

    void SetIsAllowedBeCovered(bool isAllowedBeCovered = true);
    void ClearUIExtensionNode();
    void DeleteUIExtensionNode(int32_t sessionId);
    bool AddCurSessionId(int32_t curSessionId);
    void ResetRootNode(int32_t sessionId);
    void OnUIExtensionWindowSizeChange();

    RefPtr<FrameNode> GetDialogNodeWithExistContent(const RefPtr<UINode>& node);
    OffsetF CalculateMenuPosition(const RefPtr<FrameNode>& menuWrapperNode, const OffsetF& offset);
    BorderRadiusProperty GetPrepareDragFrameNodeBorderRadius() const;

private:
    void OnBindSheetInner(std::function<void(const std::string&)>&& callback,
        const RefPtr<UINode>& sheetContentNode, std::function<RefPtr<UINode>()>&& buildtitleNodeFunc,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange, std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange,
        std::function<void()>&& sheetSpringBack, const RefPtr<FrameNode>& targetNode, bool isStartByUIContext = false);
    void SetSheetProperty(
        const RefPtr<FrameNode>& sheetPageNode,
        NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& shouldDismiss, std::function<void(const int32_t)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange, std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange,
        std::function<void()>&& sheetSpringBack);
    void SaveSheePageNode(
        const RefPtr<FrameNode>& sheetPageNode, const RefPtr<UINode>& sheetContentNode,
        const RefPtr<FrameNode>& targetNode, bool isStartByUIContext);
    bool CheckTargetIdIsValid(int32_t targetId);
    RefPtr<FrameNode> CreateSheetMask(const RefPtr<FrameNode>& sheetPageNode,
        const RefPtr<FrameNode>& targetNode, NG::SheetStyle& sheetStyle);
    void UpdateSheetRender(const RefPtr<FrameNode>& sheetPageNode, NG::SheetStyle& sheetStyle, bool isPartialUpdate);
    void UpdateSheetPage(const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& sheetStyle,
        int32_t targetId, bool isStartByUIContext = false, bool isPartialUpdate = false,
        std::function<void()>&& onAppear = nullptr, std::function<void()>&& onDisappear = nullptr,
        std::function<void()>&& shouldDismiss = nullptr, std::function<void(const int32_t)>&& onWillDismiss = nullptr,
        std::function<void()>&& onWillDisappear = nullptr,
        std::function<void(const float)>&& onHeightDidChange = nullptr,
        std::function<void(const float)>&& onDetentsDidChange = nullptr,
        std::function<void(const float)>&& onWidthDidChange = nullptr,
        std::function<void(const float)>&& onTypeDidChange = nullptr,
        std::function<void()>&& sheetSpringBack = nullptr);
    SheetStyle UpdateSheetStyle(
        const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle, bool isPartialUpdate);
    void UpdateSheetProperty(const RefPtr<FrameNode>& sheetNode, NG::SheetStyle& currentStyle, bool isPartialUpdate);
    void UpdateSheetMaskBackgroundColor(const RefPtr<FrameNode>& maskNode,
        const RefPtr<RenderContext>& maskRenderContext, const SheetStyle& sheetStyle);
    void UpdateSheetMask(const RefPtr<FrameNode>& maskNode,
        const RefPtr<FrameNode>& sheetNode, const SheetStyle& sheetStyle, bool isPartialUpdate = false);
    void CleanViewContextMap(int32_t instanceId, int32_t sheetContentId)
    {
        if (cleanViewContextMapCallback_) {
            cleanViewContextMapCallback_(instanceId, sheetContentId);
        }
    }
    void CleanInvalidModalNode(const WeakPtr<FrameNode>& invalidNode);
    void PopToast(int32_t targetId);

    // toast should contain id to avoid multiple delete.
    std::unordered_map<int32_t, WeakPtr<FrameNode>> toastMap_;

    /**  find/register menu node and update menu's display position
     *
     *   @return     true if process is successful
     */
    bool ShowMenuHelper(RefPtr<FrameNode>& menu, int32_t targetId, const NG::OffsetF& offset);
    void ResetMenuWrapperVisibility(const RefPtr<FrameNode>& menuWrapper);
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

    void SetPreviewFirstShow(const RefPtr<FrameNode>& menu);
    void ShowMenuAnimation(const RefPtr<FrameNode>& menu);
    void SetPatternFirstShow(const RefPtr<FrameNode>& menu);
    void PopMenuAnimation(const RefPtr<FrameNode>& menu, bool showPreviewAnimation = true, bool startDrag = false);
    void ShowMenuDisappearTransition(const RefPtr<FrameNode>& menu);
    void ShowMenuClearAnimation(const RefPtr<FrameNode>& menuWrapper, AnimationOption& option,
        bool showPreviewAnimation, bool startDrag);
    bool IsContextMenuBindedOnOrigNode();
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
    void SetSheetBackgroundColor(const RefPtr<FrameNode>& sheetNode, const RefPtr<SheetTheme>& sheetTheme,
        const NG::SheetStyle& sheetStyle, bool isPartialUpdate = false);

    bool ModalExitProcess(const RefPtr<FrameNode>& topModalNode);
    bool ModalPageExitProcess(const RefPtr<FrameNode>& topModalNode);
    bool SheetPageExitProcess(const RefPtr<FrameNode>& topModalNode);

    void BeforeShowDialog(const RefPtr<FrameNode>& dialogNode);
    void RemoveDialogFromMap(const RefPtr<FrameNode>& node);
    void RemoveMaskFromMap(const RefPtr<FrameNode>& dialogNode);
    bool DialogInMapHoldingFocus();
    void PlayKeyboardTransition(const RefPtr<FrameNode>& customKeyboard, bool isTransitionIn);
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
    void RemoveMenuNotInSubWindow(
        const WeakPtr<FrameNode>& menuWK, const WeakPtr<UINode>& rootWeak, const WeakPtr<OverlayManager>& overlayWeak);
    bool CreateSheetKey(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t targetId,
        SheetKey& sheetKey);

    bool CheckTopModalNode(const RefPtr<FrameNode>& topModalNode, int32_t targetId);
    void HandleModalShow(std::function<void(const std::string&)>&& callback,
        std::function<RefPtr<UINode>()>&& buildNodeFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode,
        const NG::ContentCoverParam& contentCoverParam, int32_t targetId,
        std::optional<ModalTransition> modalTransition);
    void HandleModalPop(std::function<void()>&& onWillDisappear, const RefPtr<UINode> rootNode, int32_t targetId);

    int32_t ExceptComponent(const RefPtr<NG::UINode>& rootNode, RefPtr<NG::FrameNode>& overlay,
        bool isBackPressed, bool isPageRouter);
    int32_t RemoveOverlayCommon(const RefPtr<NG::UINode>& rootNode, RefPtr<NG::FrameNode>& overlay,
        RefPtr<Pattern>& pattern, bool isBackPressed, bool isPageRouter);
    int32_t WebBackward(RefPtr<NG::FrameNode>& overlay);
    void FindWebNode(const RefPtr<NG::UINode>& node, RefPtr<NG::FrameNode>& webNode, bool& isNavDestination);

    void RegisterDialogLifeCycleCallback(const RefPtr<FrameNode>& dialog, const DialogProperties& dialogProps);
    void CustomDialogRecordEvent(const DialogProperties& dialogProps);
    RefPtr<UINode> RebuildCustomBuilder(RefPtr<UINode>& contentNode);

    void DumpPopupMapInfo() const;
    void DumpMapInfo(
        std::unordered_map<int32_t, RefPtr<FrameNode>> map, const std::string mapName, bool hasTarget = true) const;
    void DumpMapInfo(
        std::unordered_map<int32_t, WeakPtr<FrameNode>> map, const std::string mapName, bool hasTarget = true) const;
    void DumpSheetMapInfo(const std::unordered_map<SheetKey, WeakPtr<FrameNode>, SheetKeyHash>& map,
        const std::string mapName) const;
    void DumpMaskNodeIdMapInfo() const;
    void DumpModalListInfo() const;
    void DumpEntry(const RefPtr<FrameNode>& targetNode, int32_t targetId, const RefPtr<FrameNode>& node) const;
    std::string GetMapNodeLog(const RefPtr<FrameNode>& node, bool hasTarget = true) const;
    bool SetNodeBeforeAppbar(const RefPtr<NG::UINode>& rootNode, const RefPtr<FrameNode>& node);
    RefPtr<FrameNode> GetOverlayFrameNode();
    void MountToParentWithService(const RefPtr<UINode>& rootNode, const RefPtr<FrameNode>& node);
    void RemoveChildWithService(const RefPtr<UINode>& rootNode, const RefPtr<FrameNode>& node);
    CustomKeyboardOffsetInfo CalcCustomKeyboardOffset(const RefPtr<FrameNode>& customKeyboard);
    void SendToAccessibility(const WeakPtr<FrameNode> node, bool isShow);
    void RemoveMenuWrapperNode(const RefPtr<UINode>& rootNode);
    void SetDragNodeNeedClean();
    RefPtr<FrameNode> GetLastChildNotRemoving(const RefPtr<UINode>& rootNode);

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
    std::unordered_map<SheetKey, WeakPtr<FrameNode>, SheetKeyHash> sheetMap_;
    std::function<void(const int32_t, const int32_t)> cleanViewContextMapCallback_ = nullptr;
    std::unordered_map<int32_t, RefPtr<NG::ClickEvent>> sheetMaskClickEventMap_; // Key: maskNodeId
    WeakPtr<FrameNode> lastModalNode_; // Previous Modal Node
    float sheetHeight_ { 0.0 };
    WeakPtr<UINode> rootNodeWeak_;
    int32_t dialogCount_ = 0;
    DismissTarget dismissTarget_;
    int32_t dismissSheetId_ = 0;
    int32_t dismissDialogId_ = 0;
    std::unordered_map<int32_t, int32_t> maskNodeIdMap_;
    int32_t subWindowId_ = -1;
    uint64_t dialogDisplayId_ = 0;
    bool hasPixelMap_ { false };
    bool hasDragPixelMap_ { false };
    bool hasFilter_ { false };
    bool hasEvent_ { false };
    bool isOnAnimation_ { false };
    WeakPtr<FrameNode> pixmapColumnNodeWeak_;
    WeakPtr<FrameNode> dragPixmapColumnNodeWeak_;
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

    bool hasGatherNode_ { false };
    bool isGatherWithMenu_ { false };
    WeakPtr<FrameNode> gatherNodeWeak_;
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo_;
    bool isMenuShow_ = false;
    bool isAttachToCustomNode_ = false;

    // Only used when CreateModalUIExtension
    // No thread safety issue due to they are all run in UI thread
    bool isAllowedBeCovered_ = true;
    // Only hasValue when isAllowedBeCovered is false
    std::set<int32_t> curSessionIds_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MANAGER_H
