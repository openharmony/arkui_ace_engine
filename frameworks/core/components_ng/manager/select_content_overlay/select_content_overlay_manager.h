/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_CONTENT_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_CONTENT_OVERLAY_MANAGER_H

#include <functional>
#include <optional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_holder.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

struct LegacyManagerCallbacks {
    std::function<void(bool, bool)> closeCallback;
    std::function<void()> selectionResetCallback;
};

enum class NodeType {
    HANDLE, TOUCH_MENU, HANDLE_WITH_MENU, RIGHT_CLICK_MENU
};

class ACE_EXPORT SelectContentOverlayManager : public virtual AceType {
    DECLARE_ACE_TYPE(SelectContentOverlayManager, AceType);

public:
    explicit SelectContentOverlayManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
    ~SelectContentOverlayManager() override = default;
    static const RefPtr<SelectContentOverlayManager> GetOverlayManager(
        const RefPtr<SelectOverlayHolder>& holder = nullptr);
    bool IsOpen();
    bool IsCreating();
    void Show(bool animation, int32_t requestCode);
    void Close(int32_t id, bool animation, CloseReason reason);
    bool CloseCurrent(bool animation, CloseReason reason);
    void CloseWithOverlayId(int32_t overlayId, CloseReason reason, bool animation);
    void ShowOptionMenu();
    void HideOptionMenu(bool noAnimation = false);
    void ToggleOptionMenu();
    void DisableMenu();
    void EnableMenu();
    void HideHandle();
    void HandleGlobalEvent(const TouchEvent& touchPoint, const NG::OffsetF& rootOffset);
    void SetHoldSelectionCallback(int32_t id, const HoldSelectionInfo& selectionInfo);
    void RemoveHoldSelectionCallback(int32_t id);
    void MarkInfoChange(SelectOverlayDirtyFlag dirtyFlag);
    void MarkSelectOverlayDirty(PropertyChangeFlag changeFlag);
    bool IsMenuShow();
    bool IsSingleHandle();
    bool IsHandlesShow();
    bool IsHandleReverse();
    void ResetSelectionRect();
    void RestartHiddenHandleTask(bool isDelay);
    void CancelHiddenHandleTask();
    const RefPtr<FrameNode> GetSelectOverlayRoot();
    RefPtr<SelectOverlayNode> GetSelectOverlayNode();
    OptionMenuType GetShowMenuType();

    std::optional<SelectOverlayInfo> GetSelectOverlayInfo()
    {
        return shareOverlayInfo_ ? *shareOverlayInfo_ : std::optional<SelectOverlayInfo>();
    }

    void SetLegacyManagerBridge(const LegacyManagerCallbacks& callbacks)
    {
        legacyManagerCallbacks_ = callbacks;
    }

    RefPtr<Pattern> GetMenuPattern();
    RefPtr<Pattern> GetHandlePattern();
    RefPtr<FrameNode> GetHandleOverlayNode();
    void NotifyUpdateToolBar(bool itemChanged);
    void SwitchToHandleMode(HandleLevelMode mode, bool forceChange = true);
    float GetHandleDiameter();
    void ConvertPointRelativeToNode(const RefPtr<FrameNode>& node, PointF& point);
    bool IsTouchAtHandle(const PointF& localPoint, const PointF& globalPoint);
    void SetHandleCircleIsShow(bool isFirst, bool isShow);
    void SetIsHandleLineShow(bool isShow);
    void MarkHandleDirtyNode(PropertyChangeFlag flag);
    bool IsHiddenHandle();
    void ConvertHandleRelativeToParent(SelectHandleInfo& info);
    void ConvertRectRelativeToParent(RectF& rect);
    void RevertRectRelativeToRoot(RectF& rect);
    OffsetF GetContainerModalOffset();
    bool IsStopBackPress() const;
    bool IsRightClickSubWindowMenu();
    bool IsSeletctOverlaySubWindowMenu();

private:
    void SetHolder(const RefPtr<SelectOverlayHolder>& holder);
    bool HasHolder(int32_t holderId);
    void SetHolderInternal(const RefPtr<SelectOverlayHolder>& holder);
    void CreateSelectOverlay(SelectOverlayInfo& info, bool animation = false);
    void CreateNormalSelectOverlay(SelectOverlayInfo& info, bool animation);
    void CreateHandleLevelSelectOverlay(SelectOverlayInfo& info, bool animation, HandleLevelMode mode);
    void UpdateExistOverlay(const SelectOverlayInfo& info, bool animation, int32_t requestCode);
    bool IsSameMouseSelectOverlay(const SelectOverlayInfo& info);
    bool CloseInternal(int32_t holderId, bool animation, CloseReason reason);
    void DestroySelectOverlayNode(const RefPtr<FrameNode>& node);
    void DestroySelectOverlayNodeWithAnimation(const RefPtr<FrameNode>& node);
    void MountNodeToRoot(const RefPtr<FrameNode>& overlayNode, bool animation, NodeType nodeType);
    void MountNodeToCaller(const RefPtr<FrameNode>& overlayNode, bool animation);
    std::function<void()> MakeMenuCallback(OptionMenuActionId actionId, const SelectOverlayInfo& info);
    SelectOverlayInfo BuildSelectOverlayInfo(int32_t requestCode);
    void UpdateStatusInfos(SelectOverlayInfo& info);
    void RegisterTouchCallback(SelectOverlayInfo& info);
    void RegisterHandleCallback(SelectOverlayInfo& info);
    void HandleSelectionEvent(const PointF& point, const TouchEvent& rawTouchEvent);
    void UpdateHandleInfosWithFlag(int32_t updateFlag);
    bool IsTouchInSelectOverlayArea(const PointF& point);
    bool IsTouchInNormalSelectOverlayArea(const PointF& point);
    bool IsTouchInHandleLevelOverlayArea(const PointF& point);
    RefPtr<UINode> FindWindowScene(RefPtr<FrameNode> targetNode);
    void ClearAllStatus();
    bool IsEnableHandleLevel();
    void NotifySelectOverlayShow(bool isCreated);
    std::list<RefPtr<UINode>>::const_iterator FindSelectOverlaySlot(
        const RefPtr<FrameNode>& root, const std::list<RefPtr<UINode>>& children);
    RefPtr<FrameNode> GetContainerModalRoot();
    void UpdateSelectOverlayInfoInternal(SelectOverlayInfo& overlayInfo);
    std::string GetOwnerDebugInfo();
    void MountMenuNodeToSubWindow(const RefPtr<FrameNode>& overlayNode, bool animation, NodeType nodeType);
    bool IsEnableSubWindowMenu();
    void UpdateRightClickSubWindowMenuProps(const RefPtr<FrameNode>& overlayNode);

    RefPtr<SelectOverlayHolder> selectOverlayHolder_;
    WeakPtr<FrameNode> selectOverlayNode_;
    WeakPtr<FrameNode> menuNode_;
    WeakPtr<FrameNode> handleNode_;
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo_;
    WeakPtr<FrameNode> rootNodeWeak_;
    int32_t selectionHoldId_ = -1;
    std::optional<HoldSelectionInfo> holdSelectionInfo_;
    LegacyManagerCallbacks legacyManagerCallbacks_;
    bool isIntercept_ = false;
    int32_t containerId_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(SelectContentOverlayManager);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_CONTENT_OVERLAY_MANAGER_H
