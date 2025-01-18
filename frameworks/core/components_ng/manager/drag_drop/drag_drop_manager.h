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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H

#include <cstdint>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/interaction/interaction_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/manager/drag_drop/utils/internal_drag_action.h"
#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace {
class UnifiedData;
class GridColumnInfo;
}
namespace OHOS::Ace::NG {
enum class DragDropMgrState : int32_t {
    IDLE,
    ABOUT_TO_PREVIEW,
    DRAGGING
};

struct GatherAnimationInfo {
    float scale = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    OffsetF gatherNodeCenter;
    std::optional<BorderRadiusProperty> borderRadius;
};

class ACE_EXPORT DragDropManager : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropManager, AceType);

public:
    DragDropManager() = default;
    ~DragDropManager() override = default;

    RefPtr<DragDropProxy> CreateAndShowItemDragOverlay(
        const RefPtr<PixelMap>& pixelMap, const GestureEvent& info, const RefPtr<EventHub>& eventHub);
    RefPtr<DragDropProxy> CreateAndShowItemDragOverlay(
        const RefPtr<UINode>& customNode, const GestureEvent& info, const RefPtr<EventHub>& eventHub);
    RefPtr<DragDropProxy> CreateTextDragDropProxy();

    void AddDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        dragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void RemoveDragFrameNode(int32_t id);

    void AddGridDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        gridDragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void AddListDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        listDragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void AddTextFieldDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        textFieldDragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void SetEventStrictReportingEnabled(bool dragEventStrictReportingEnabled)
    {
        eventStrictReportingEnabled_ = dragEventStrictReportingEnabled;
    }

    bool IsEventStrictReportingEnabled()
    {
        return eventStrictReportingEnabled_;
    }

    void UpdateItemDragPosition(int32_t globalX, int32_t globalY);
    void OnDragStart(const Point& point);
    void OnDragStart(const Point& point, const RefPtr<FrameNode>& frameNode);
    void OnDragMove(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
        const RefPtr<FrameNode>& node = nullptr);
    void OnDragEnd(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
        const RefPtr<FrameNode>& node = nullptr);
    void HandleOnDragMove(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
        const RefPtr<FrameNode>& dragFrameNode);
    void HandleOnDragEnd(const DragPointerEvent& pointerEvent, const std::string& extraInfo,
        const RefPtr<FrameNode>& dragFrameNode);
    void ResetDragEndOption(
        const DragNotifyMsgCore& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent, int32_t currentId);
    void DoDragReset();
    void DoDropAction(const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent,
        const RefPtr<UnifiedData>& unifiedData, const std::string& udKey);
    void RequestDragSummaryInfoAndPrivilege();
    RefPtr<UnifiedData> RequestUDMFDataWithUDKey(const std::string& udKey);
    void TryGetDataBackGround(
        const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent,
        const std::string& udKey, int32_t count = 0);
    void OnDragDrop(RefPtr<OHOS::Ace::DragEvent>& event, const RefPtr<FrameNode>& dragFrameNode,
        const OHOS::Ace::DragPointerEvent& pointerEvent);
    void ExecuteStopDrag(const RefPtr<OHOS::Ace::DragEvent>& event, DragRet dragResult, bool useCustomAnimation,
        int32_t windowId, DragBehavior dragBehavior, const OHOS::Ace::DragPointerEvent& pointerEvent);
    void ExecuteCustomDropAnimation(const RefPtr<OHOS::Ace::DragEvent>& dragEvent, DragDropRet dragDropRet);
    void ResetDragDropStatus(const Point& point, const DragDropRet& dragDropRet, int32_t windowId);
    bool CheckRemoteData(
        const RefPtr<FrameNode>& dragFrameNode, const DragPointerEvent& pointerEvent, const std::string& udKey);
    void OnDragMoveOut(const DragPointerEvent& pointerEvent);
    void OnTextDragEnd(float globalX, float globalY, const std::string& extraInfo);
    void onDragCancel();
    void OnItemDragStart(float globalX, float globalY, const RefPtr<FrameNode>& frameNode);
    void OnItemDragMove(float globalX, float globalY, int32_t draggedIndex, DragType dragType);
    void OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex, DragType dragType);
    void onItemDragCancel();
    void AddDataToClipboard(const std::string& extraInfo);
    void GetExtraInfoFromClipboard(std::string& extraInfo);
    void RestoreClipboardData();
    void DestroyDragWindow();
    void CancelItemDrag();
    std::string GetExtraInfo();
    void SetExtraInfo(const std::string& extraInfo);
    void ClearExtraInfo();
    float GetWindowScale() const;
    void UpdateDragCursorStyle(const RefPtr<FrameNode>& frameNode, const RefPtr<OHOS::Ace::DragEvent>& event,
        const int32_t eventId = -1);
    void UpdateDragStyle(
        const DragCursorStyleCore& dragCursorStyleCore = DragCursorStyleCore::DEFAULT, const int32_t eventId = -1);
    void UpdateDragAllowDrop(const RefPtr<FrameNode>& dragFrameNode, const DragBehavior dragBehavior,
        const int32_t eventId = -1, bool isCapi = false);
    bool CheckExtraSituation(const RefPtr<FrameNode>& dragFrameNode) const;
    bool CheckInRichEditor(const RefPtr<FrameNode>& dragFrameNode) const;
    void RequireSummary();
    void ClearSummary();
    void SetSummaryMap(const std::map<std::string, int64_t>& summaryMap)
    {
        summaryMap_ = summaryMap;
    }
    void ResetRecordSize(uint32_t recordSize = 0);
    uint32_t GetRecordSize() const;
    Rect GetDragWindowRect(const Point& point);
    RefPtr<DragDropProxy> CreateFrameworkDragDropProxy();
    void HideDragPreviewOverlay();
    void HideDragPreviewWindow(int32_t containerId);
    bool IsMSDPDragging() const;
    void UpdateDragEvent(RefPtr<OHOS::Ace::DragEvent>& event, const OHOS::Ace::DragPointerEvent& pointerEvent);
    void UpdateNotifyDragEvent(
        RefPtr<NotifyDragEvent>& notifyEvent, const Point& point, const DragEventType dragEventType);
    bool CheckDragDropProxy(int64_t id) const;
    void NotifyEnterTextEditorArea();
    void FireOnEditableTextComponent(const RefPtr<FrameNode>& frameNode, DragEventType type);
    void FireOnDragLeave(const RefPtr<FrameNode>& preTargetFrameNode_, const DragPointerEvent& pointerEven,
        const std::string& extraInfo);

    bool IsWindowConsumed() const
    {
        return isWindowConsumed_;
    }

    void SetIsWindowConsumed(bool consumed)
    {
        isWindowConsumed_ = consumed;
    }

    bool IsDragged() const
    {
        return isDragged_;
    }

    void SetIsDragged(bool isDragged);

    void SetDragDampStartPoint(const Point& point)
    {
        dragDampStartPoint_ = point;
    }

    const Point& GetDragDampStartPoint() const
    {
        return dragDampStartPoint_;
    }

    void SetIsDragCancel(bool isDragCancel)
    {
        isDragCancel_ = isDragCancel;
    }

    void SetIsMouseDrag(bool isMouseDragged)
    {
        isMouseDragged_ = isMouseDragged;
    }

    void SetIsDragWindowShow(bool isDragWindowShow)
    {
        isDragWindowShow_ = isDragWindowShow;
    }

    bool IsDragWindowShow() const
    {
        return isDragWindowShow_;
    }

    void SetPreviewRect(const Rect& rect)
    {
        previewRect_ = rect;
    }

    Rect GetPreviewRect() const
    {
        return previewRect_;
    }

    void SetDragCursorStyleCore(DragCursorStyleCore dragCursorStyleCore)
    {
        dragCursorStyleCore_ = dragCursorStyleCore;
    }

    std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> GetDragAction()
    {
        return dragAction_;
    }
    
    RefPtr<FrameNode> FindTargetInChildNodes(const RefPtr<UINode> parentNode,
        std::vector<RefPtr<FrameNode>> hitFrameNodes, bool findDrop);
    
    bool CheckFrameNodeCanDrop(const RefPtr<FrameNode>& node);

    RefPtr<FrameNode> FindTargetDropNode(const RefPtr<UINode> parentNode, PointF localPoint);

    std::unordered_set<int32_t> FindHitFrameNodes(const Point& point);

    void UpdateDragListener(const Point& point);

    void NotifyDragRegisterFrameNode(std::unordered_map<int32_t, WeakPtr<FrameNode>> nodes, DragEventType dragEventType,
        RefPtr<NotifyDragEvent>& notifyEvent);

    void RegisterDragStatusListener(int32_t nodeId, const WeakPtr<FrameNode>& node);

    void UnRegisterDragStatusListener(int32_t nodeId)
    {
        nodesForDragNotify_.erase(nodeId);
    }

    void RegisterPullEventListener(int32_t uniqueIdentify, std::function<void(const DragPointerEvent&)> callback);

    void UnRegisterPullEventListener(int32_t uniqueIdentify);

    void NotifyPullEventListener(const DragPointerEvent& dragPointerEvent);

    void SetNotifyInDraggedCallback(const std::function<void(void)>& callback)
    {
        notifyInDraggedCallback_ = callback;
    }

    bool IsDragging() const
    {
        return dragDropState_ == DragDropMgrState::DRAGGING;
    }

    bool IsItemDragging() const
    {
        return dragDropState_ == DragDropMgrState::DRAGGING && draggedGridFrameNode_ != nullptr;
    }

    bool IsAboutToPreview() const
    {
        return dragDropState_ == DragDropMgrState::ABOUT_TO_PREVIEW;
    }

    void ResetDragging(DragDropMgrState dragDropMgrState = DragDropMgrState::IDLE)
    {
        dragDropState_ = dragDropMgrState;
    }

    void ResetPreTargetFrameNode(int32_t instanceId);

    void SetDraggingPressedState(bool pointerPressed)
    {
        draggingPressedState_ = pointerPressed;
    }

    bool IsDraggingPressed(int32_t currentPointerId) const;

    bool IsSameDraggingPointer(int32_t currentPointerId) const
    {
        return currentPointerId_ == currentPointerId;
    }

    void SetDraggingPointer(int32_t currentPointerId)
    {
        currentPointerId_ = currentPointerId;
    }

    static inline bool IsEditableTextComponent(const std::string& frameTag)
    {
        if (frameTag != V2::TEXTINPUT_ETS_TAG && frameTag != V2::TEXTAREA_ETS_TAG &&
            frameTag != V2::RICH_EDITOR_ETS_TAG && frameTag != V2::SEARCH_Field_ETS_TAG) {
            return false;
        }
        return true;
    }

    typedef struct DragPreviewInfo {
        double width { 0.0 };
        double height { 0.0 };
        double maxWidth { 0.0 };
        double scale { -1.0 };
        VectorF originScale { 1.0f, 1.0f };
        OffsetF originOffset;
        RefPtr<FrameNode> imageNode { nullptr };
        RefPtr<FrameNode> textNode { nullptr };
    } DragPreviewInfo;
    bool IsNeedScaleDragPreview();
    void DoDragMoveAnimate(const DragPointerEvent& pointerEvent);
    void DragMoveAnimation(const Offset& newOffset, const RefPtr<OverlayManager>& overlayManager, Point point);
    void DoDragStartAnimation(const RefPtr<OverlayManager>& overlayManager,
        const GestureEvent& event, const RefPtr<GestureEventHub>& gestureHub, bool isSubwindowOverlay = false);
    void DragStartAnimation(const Offset& newOffset, const RefPtr<OverlayManager>& overlayManager,
        const OffsetF& gatherNodeCenter, Point point = { 1, 1 });
    void SetDragResult(const DragNotifyMsgCore& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent);
    void SetDragBehavior(const DragNotifyMsgCore& notifyMessage, const RefPtr<OHOS::Ace::DragEvent>& dragEvent);
    void ResetDragPreviewInfo()
    {
        info_ = DragPreviewInfo();
    }

    void ResetPullMoveReceivedForCurrentDrag(bool isPullMoveReceivedForCurrentDrag = false)
    {
        isPullMoveReceivedForCurrentDrag_ = isPullMoveReceivedForCurrentDrag;
    }

    bool IsPullMoveReceivedForCurrentDrag() const
    {
        return isPullMoveReceivedForCurrentDrag_;
    }

    void RemoveDeadlineTimer();

    void ExecuteDeadlineTimer();

    void HandleSyncOnDragStart(DragStartRequestStatus dragStartRequestStatus);

    void SetDragMoveLastPoint(Point point) noexcept;

    void SetDelayDragCallBack(const std::function<void()>& cb) noexcept;

    DragStartRequestStatus IsDragStartNeedToBePended() const
    {
        return dragStartRequestStatus_;
    }

    bool HasDelayDragCallBack() const
    {
        return asyncDragCallback_ != nullptr;
    }

    bool IsStartAnimationFInished() const
    {
        return isStartAnimationFinished_;
    }

    void SetStartAnimation(bool flag)
    {
        isStartAnimationFinished_ = flag;
    }

    static OffsetF GetTouchOffsetRelativeToSubwindow(int32_t containerId, int32_t x = 0, int32_t y = 0);
    static RectF GetMenuPreviewRect();
    static void UpdateGatherNodeAttr(const RefPtr<OverlayManager>& overlayManager, const GatherAnimationInfo& info);
    static void UpdateGatherNodePosition(const RefPtr<OverlayManager>& overlayManager,
        const RefPtr<FrameNode>& imageNode);
    static void UpdateTextNodePosition(const RefPtr<FrameNode>& textNode, const Offset& localPoint);
    double CalcGatherNodeMaxDistanceWithPoint(const RefPtr<OverlayManager>& overlayManager, int32_t x, int32_t y);

    void SetPixelMapOffset(OffsetF pixelMapOffset)
    {
        pixelMapOffset_ = pixelMapOffset;
    }

    bool IsNeedDisplayInSubwindow();
    void ClearGatherPixelMap()
    {
        gatherPixelMaps_.clear();
    }

    void PushGatherPixelMap(const RefPtr<PixelMap>& pixelMap);
    void GetGatherPixelMap(DragDataCore& dragData, float scale, float previewWidth = 0.0f, float previewHeight = 0.0f);

    const DragPointerEvent& GetDragDropPointerEvent() const
    {
        return dragDropPointerEvent_;
    }

    void SetDragDropPointerEvent(const DragPointerEvent& dragDropPointerEvent)
    {
        dragDropPointerEvent_ = dragDropPointerEvent;
    }

    void SetIsShowBadgeAnimation(bool isShowBadgeAnimation)
    {
        isShowBadgeAnimation_ = isShowBadgeAnimation;
    }

    bool IsShowBadgeAnimation()
    {
        return isShowBadgeAnimation_;
    }

    bool IsDragWithContextMenu() const
    {
        return isDragWithContextMenu_;
    }

    void SetIsDragWithContextMenu(bool isDragWithContextMenu)
    {
        isDragWithContextMenu_ = isDragWithContextMenu;
    }

    void SetIsDragNodeNeedClean(bool isDragNodeNeedClean = false)
    {
        isDragNodeNeedClean_ = isDragNodeNeedClean;
    }

    bool IsDragNodeNeedClean() const
    {
        return isDragNodeNeedClean_;
    }

    void UpdateDragMovePosition(const NG::OffsetF& offset, bool isRedragStart = false);

    void ResetContextMenuDragPosition();

    void ResetContextMenuRedragPosition();

    OffsetF GetUpdateDragMovePosition() const
    {
        return dragTotalMovePosition_;
    }

    bool IsDropAllowed(const RefPtr<FrameNode>& dragFrameNode);
    
    void SetDragAction(const std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction>& dragAction)
    {
        dragAction_ = dragAction;
    }

    void AddNewDragAnimation();

    bool IsAllAnimationFinished();

    float GetCurrentDistance(float x, float y);

    uint32_t GetDampingOverflowCount() const
    {
        return dampingOverflowCount_;
    }

    void SetDampingOverflowCount()
    {
        dampingOverflowCount_++;
    }
    static double GetMaxWidthBaseOnGridSystem(const RefPtr<PipelineBase>& pipeline);

    RefPtr<FrameNode> GetMenuWrapperNode()
    {
        return menuWrapperNode_.Upgrade();
    }

    void SetMenuWrapperNode(const RefPtr<FrameNode>& frameNode)
    {
        menuWrapperNode_ = frameNode;
    }

    bool CheckIsNewDrag(const DragPointerEvent& pointerEvent) const;

    void RequireSummaryIfNecessary(const DragPointerEvent& pointerEvent);

    inline void ResetPullId()
    {
        summaryMap_.clear();
        parentHitNodes_.clear();
        currentPullId_ = -1;
    }

    void SetIsDisableDefaultDropAnimation(bool disableDefaultDropAnimation = false)
    {
        disableDefaultDropAnimation_ = disableDefaultDropAnimation;
    }

    bool IsDisableDefaultDropAnimation() const
    {
        return disableDefaultDropAnimation_;
    }

    void ResetDraggingStatus(const TouchEvent& touchPoint);

    void SetGrayedState(bool state)
    {
        grayedState_ = state;
    }

    bool GetGrayedState() const
    {
        return grayedState_;
    }
    
    void SetIsAnyDraggableHit(bool isAnyDraggableHit = false)
    {
        isAnyDraggableHit_ = isAnyDraggableHit;
    }

    bool IsAnyDraggableHit(const RefPtr<PipelineBase>& pipeline, int32_t pointId);

    int32_t CancelUDMFDataLoading(const std::string& key);

private:
    double CalcDragPreviewDistanceWithPoint(
        const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info);
    Offset CalcDragMoveOffset(
        const OHOS::Ace::Dimension& preserverHeight, int32_t x, int32_t y, const DragPreviewInfo& info);
    bool UpdateDragMovePositionFinished(
        bool needDoDragMoveAnimate, bool isMenuShow, const Offset& newOffset, int32_t containerId);
    void UpdateDragPreviewScale();
    bool GetDragPreviewInfo(const OHOS::Ace::RefPtr<OHOS::Ace::NG::OverlayManager>& overlayManager,
        DragPreviewInfo& dragPreviewInfo, const RefPtr<GestureEventHub>& gestureHub);
    bool IsNeedDoDragMoveAnimate(const DragPointerEvent& pointerEvent);
    const RefPtr<NG::OverlayManager> GetDragAnimationOverlayManager(int32_t containerId);
    RefPtr<FrameNode> FindDragFrameNodeByPosition(float globalX, float globalY,
        const RefPtr<FrameNode>& node = nullptr);
    void FireOnDragEvent(
        const RefPtr<FrameNode>& frameNode, const DragPointerEvent& pointerEvent,
        DragEventType type, const std::string& extraInfo);
    void FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
        const ItemDragInfo& itemDragInfo, DragEventType type, int32_t draggedIndex, int32_t insertIndex = 0);
    bool FireOnItemDropEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
        const ItemDragInfo& itemDragInfo, int32_t draggedIndex, int32_t insertIndex, bool isSuccess);
    int32_t GetItemIndex(const RefPtr<FrameNode>& frameNode, DragType dragType, float globalX, float globalY);
    void CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height);
    RefPtr<FrameNode> CreateDragRootNode(const RefPtr<UINode>& customNode);
    void ClearVelocityInfo();
    void UpdateVelocityTrackerPoint(const Point& point, bool isEnd = false);
    void PrintDragFrameNode(const OHOS::Ace::DragPointerEvent& pointerEvent, const RefPtr<FrameNode>& dragFrameNode);
    void PrintGridDragFrameNode(const float globalX, const float globalY, const RefPtr<FrameNode>& dragFrameNode);
    void FireOnDragEventWithDragType(const RefPtr<EventHub>& eventHub, DragEventType type,
        RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams);
    void NotifyDragFrameNode(
        const Point& point, const DragEventType& dragEventType, const DragRet& dragRet = DragRet::DRAG_DEFAULT);
    void TransDragWindowToDragFwk(int32_t windowContainerId);
    void ResetDragDrop(int32_t windowId, const Point& point);
    bool isDistanceLimited(const Point& point);
    bool isTimeLimited(const DragPointerEvent& pointerEvent, const Point& point);
    bool ReachMoveLimit(const DragPointerEvent& pointerEvent, const Point& point);
    bool IsUIExtensionShowPlaceholder(const RefPtr<NG::UINode>& node);
    bool IsUIExtensionComponent(const RefPtr<NG::UINode>& node);
    void HandleUIExtensionDragEvent(
        const RefPtr<FrameNode>& frameNode, const DragPointerEvent& pointerEvent, DragEventType type);
    int32_t GetWindowId();
    void AddItemDrag(const RefPtr<FrameNode>& frameNode, const RefPtr<EventHub>& eventHub);
    void RemoveItemDrag();

    std::map<int32_t, WeakPtr<FrameNode>> dragFrameNodes_;
    std::map<int32_t, WeakPtr<FrameNode>> gridDragFrameNodes_;
    std::map<int32_t, WeakPtr<FrameNode>> listDragFrameNodes_;
    std::map<int32_t, WeakPtr<FrameNode>> textFieldDragFrameNodes_;
    RefPtr<FrameNode> draggedFrameNode_;
    RefPtr<FrameNode> preTargetFrameNode_;
    RefPtr<FrameNode> draggedGridFrameNode_;
    RefPtr<FrameNode> preGridTargetFrameNode_;
    RefPtr<FrameNode> itemDragOverlayNode_;
    RefPtr<Clipboard> clipboard_;
    Point preMovePoint_ = Point(0, 0);
    uint64_t preTimeStamp_ = 0L;
    std::function<void(const std::string&)> addDataCallback_ = nullptr;
    std::function<void(const std::string&)> getDataCallback_ = nullptr;
    std::function<void(const std::string&)> deleteDataCallback_ = nullptr;
    std::string extraInfo_;
    std::unique_ptr<JsonValue> newData_ = nullptr;
    bool isDragCancel_ = false;
    std::unordered_map<int32_t, WeakPtr<FrameNode>> nodesForDragNotify_;
    std::unordered_set<int32_t> parentHitNodes_;
    std::unordered_map<int32_t, std::function<void(const DragPointerEvent&)>> pullEventListener_;
    DragCursorStyleCore dragCursorStyleCore_ = DragCursorStyleCore::DEFAULT;
    std::map<std::string, int64_t> summaryMap_;
    uint32_t recordSize_ = 0;
    int64_t currentId_ = -1;
    int32_t currentPointerId_ = -1;
    int32_t currentPullId_ = -1;
    bool draggingPressedState_ = false;

    std::function<void(void)> notifyInDraggedCallback_ = nullptr;
    bool isDragged_ = false;
    bool isMouseDragged_ = false;
    bool isWindowConsumed_ = false;
    bool isDragWindowShow_ = false;
    bool hasNotifiedTransformation_ = false;
    bool isPullMoveReceivedForCurrentDrag_ = false;
    bool isDragWindowSubWindow_ = false;
    bool isDragNodeNeedClean_ = false;
    bool isAnyDraggableHit_ = false;
    VelocityTracker velocityTracker_;
    DragDropMgrState dragDropState_ = DragDropMgrState::IDLE;
    Rect previewRect_ { -1, -1, -1, -1 };
    DragPreviewInfo info_;
    DragPointerEvent dragDropPointerEvent_;
    bool isDragFwkShow_ = true;
    OffsetF pixelMapOffset_;
    OffsetF curPointerOffset_;
    std::vector<RefPtr<PixelMap>> gatherPixelMaps_;
    bool isShowBadgeAnimation_ = true;
    bool eventStrictReportingEnabled_ = false;
    int32_t badgeNumber_ = -1;
    int32_t currentAnimationCnt_ = 0;
    int32_t allAnimationCnt_ = 0;
    bool isDragWithContextMenu_ = false;
    bool disableDefaultDropAnimation_ = false;
    Point dragDampStartPoint_ { 1, 1 };
    OffsetF dragMovePosition_ = OffsetF(0.0f, 0.0f);
    OffsetF lastDragMovePosition_ = OffsetF(0.0f, 0.0f);
    OffsetF dragTotalMovePosition_ = OffsetF(0.0f, 0.0f);
    uint32_t dampingOverflowCount_ = 0;
    std::shared_ptr<OHOS::Ace::NG::ArkUIInteralDragAction> dragAction_;
    RefPtr<GridColumnInfo> columnInfo_;
    WeakPtr<FrameNode> menuWrapperNode_;
    ACE_DISALLOW_COPY_AND_MOVE(DragDropManager);
    bool grayedState_ = false;

    Point dragMoveLastPoint_;
    DragStartRequestStatus dragStartRequestStatus_{DragStartRequestStatus::READY};
    std::function<void()> asyncDragCallback_;
    bool isStartAnimationFinished_{};
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H
