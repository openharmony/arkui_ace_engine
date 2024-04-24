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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H

#include <functional>
#include <list>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/event/gesture_event_actuator.h"
#include "core/components_ng/gestures/recognizers/sequenced_recognizer.h"
#include "core/gestures/drag_event.h"

namespace OHOS::Ace::NG {

class GestureEventHub;
class PanRecognizer;
class LongPressRecognizer;
class FrameNode;
class OverlayManager;
class ScrollablePattern;
struct GatherNodeChildInfo;

class DragEvent : public AceType {
    DECLARE_ACE_TYPE(DragEvent, AceType)
public:
    DragEvent(GestureEventFunc&& actionStart, GestureEventFunc&& actionUpdate, GestureEventFunc&& actionEnd,
        GestureEventNoParameter&& actionCancel)
        : actionStart_(std::move(actionStart)), actionUpdate_(std::move(actionUpdate)),
          actionEnd_(std::move(actionEnd)), actionCancel_(std::move(actionCancel))
    {}
    ~DragEvent() override = default;

    const GestureEventFunc& GetActionStartEventFunc() const
    {
        return actionStart_;
    }

    const GestureEventFunc& GetActionUpdateEventFunc() const
    {
        return actionUpdate_;
    }

    const GestureEventFunc& GetActionEndEventFunc() const
    {
        return actionEnd_;
    }

    const GestureEventNoParameter& GetActionCancelEventFunc() const
    {
        return actionCancel_;
    }

private:
    GestureEventFunc actionStart_;
    GestureEventFunc actionUpdate_;
    GestureEventFunc actionEnd_;
    GestureEventNoParameter actionCancel_;
};

class ACE_EXPORT DragEventActuator : public GestureEventActuator {
    DECLARE_ACE_TYPE(DragEventActuator, GestureEventActuator)
public:
    DragEventActuator(
        const WeakPtr<GestureEventHub>& gestureEventHub, PanDirection direction, int32_t fingers, float distance);
    ~DragEventActuator() override = default;

    void ReplaceDragEvent(const RefPtr<DragEvent>& dragEvent)
    {
        if (userCallback_) {
            userCallback_.Reset();
        }
        userCallback_ = dragEvent;
    }

    void SetCustomDragEvent(const RefPtr<DragEvent>& dragEvent)
    {
        if (customCallback_) {
            customCallback_.Reset();
        }
        customCallback_ = dragEvent;
    }

    void ClearDragEvent()
    {
        if (userCallback_) {
            userCallback_.Reset();
        }
        if (customCallback_) {
            customCallback_.Reset();
        }
    }

    void OnCollectTouchTarget(const OffsetF& coordinateOffset, const TouchRestrict& touchRestrict,
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result) override;
    void SetThumbnailCallback(std::function<void(Offset)>&& callback);
    void SetFilter(const RefPtr<DragEventActuator>& actuator);
    static void UpdatePreviewPositionAndScale(const RefPtr<FrameNode>& imageNode, const OffsetF& frameOffset);
    static void CreatePreviewNode(const RefPtr<FrameNode>& frameNode, OHOS::Ace::RefPtr<FrameNode>& imageNode);
    static void SetPreviewDefaultAnimateProperty(const RefPtr<FrameNode>& imageNode);
    static void MountPixelMap(const RefPtr<OverlayManager>& overlayManager, const RefPtr<GestureEventHub>& manager,
        const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode);
    static RefPtr<PixelMap> GetPreviewPixelMap(const std::string& inspectorId, const RefPtr<FrameNode>& selfFrameNode);
    static RefPtr<PixelMap> GetPreviewPixelMapByInspectorId(const std::string& inspectorId);
    static RefPtr<PixelMap> GetScreenShotPixelMap(const RefPtr<FrameNode>& frameNode);
    static void ExecutePreDragAction(const PreDragStatus preDragStatus, const RefPtr<FrameNode>& frameNode = nullptr);
    void SetPixelMap(const RefPtr<DragEventActuator>& actuator);
    void SetEventColumn(const RefPtr<DragEventActuator>& actuator);
    void HideFilter();
    void HidePixelMap(bool startDrag = false, double x = 0, double y = 0, bool showAnimation = true);
    void HideEventColumn();
    void BindClickEvent(const RefPtr<FrameNode>& columnNode);
    void ShowPixelMapAnimation(const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& frameNode,
        bool hasContextMenu);
    void SetTextAnimation(const RefPtr<GestureEventHub>& gestureHub, const Offset& globalLocation);
    void HideTextAnimation(bool startDrag = false, double globalX = 0, double globalY = 0);
    bool GetIsBindOverlayValue(const RefPtr<DragEventActuator>& actuator);
    bool IsAllowedDrag();
    void SetTextPixelMap(const RefPtr<GestureEventHub>& gestureHub);
    static OffsetF GetFloatImageOffset(const RefPtr<FrameNode>& frameNode, const RefPtr<PixelMap>& pixelMap);
    PanDirection GetDirection() const
    {
        return direction_;
    }

    int32_t GetFingers() const
    {
        return fingers_;
    }

    float GetDistance() const
    {
        return distance_;
    }

    void StartDragTaskForWeb(const GestureEvent& info);
    void StartLongPressActionForWeb();
    void CancelDragForWeb();
    void ResetDragActionForWeb() {
        if (isReceivedLongPress_) {
            isReceivedLongPress_ = false;
        }
    }

    void SetIsNotInPreviewState(bool isNotInPreviewState)
    {
        isNotInPreviewState_ = isNotInPreviewState;
    }

    bool GetIsNotInPreviewState() const
    {
        return isNotInPreviewState_;
    }

    void SetIsDragUserReject(bool isDragUserReject)
    {
        isDragUserReject_ = isDragUserReject;
    }

    bool IsDragUserReject() const
    {
        return isDragUserReject_;
    }

    void CopyDragEvent(const RefPtr<DragEventActuator>& dragEventActuator);

    void SetGatherNodeAboveFilter(const RefPtr<DragEventActuator>& actuator);
    bool IsBelongToMultiItemNode(const RefPtr<FrameNode>& frameNode);
    bool IsSelectedItemNode(const RefPtr<UINode>& uiNode);
    void FindItemFatherNode(const RefPtr<FrameNode>& frameNode);
    bool IsNeedGather();
    static RefPtr<FrameNode> GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
        const RefPtr<DragEventActuator>& actuator, std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    static RefPtr<FrameNode> CreateGatherNode(const RefPtr<DragEventActuator>& actuator);
    static RefPtr<FrameNode> CreateImageNode(const RefPtr<FrameNode>& frameNode,
        GatherNodeChildInfo& gatherNodeChildInfo);
    static void MarkDirtyGatherNode(const RefPtr<FrameNode>& gatherNode);
    static void ResetNode(const RefPtr<FrameNode>& frameNode);
    static void MountGatherNode(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& frameNode,
        const RefPtr<FrameNode>& gatherNode, std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    static void GetFrameNodePreviewPixelMap(const RefPtr<FrameNode>& frameNode);
    void SetGatherNode(const RefPtr<FrameNode>& gatherNode);
    RefPtr<FrameNode> GetGatherNode();
    std::vector<GatherNodeChildInfo> GetGatherNodeChildrenInfo();
    void ClearGatherNodeChildrenInfo();
    void PushBackGatherNodeChild(GatherNodeChildInfo& gatherNodeChild);
    void HandleTouchUpEvent();
    void HandleTouchMoveEvent();
    void HandleTouchCancelEvent();
    RefPtr<FrameNode> GetItemFatherNode();
    RefPtr<FrameNode> GetFrameNode();

    inline static void FlushSyncGeometryNodeTasks();

    void ShowPreviewBadgeAnimation(
        const RefPtr<DragEventActuator>& dragEventActuator, const RefPtr<OverlayManager>& manager);
    static RefPtr<FrameNode> CreateBadgeTextNode(
        const RefPtr<FrameNode>& frameNode, int32_t childSize, float previewScale, bool isUsePixelMapOffset = false);
private:
    void UpdatePreviewOptionFromModifier(const RefPtr<FrameNode>& frameNode);
    void ApplyNewestOptionExecutedFromModifierToNode(
        const RefPtr<FrameNode>& optionHolderNode, const RefPtr<FrameNode>& targetNode);

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    WeakPtr<FrameNode> itemFatherNode_;
    RefPtr<DragEvent> userCallback_;
    RefPtr<DragEvent> customCallback_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<LongPressRecognizer> previewLongPressRecognizer_;
    RefPtr<SequencedRecognizer> SequencedRecognizer_;
    RefPtr<FrameNode> gatherNode_;

    RefPtr<PixelMap> textPixelMap_;
    std::function<void(GestureEvent&)> actionStart_;
    std::function<void(GestureEvent&)> longPressUpdate_;
    std::function<void()> actionCancel_;
    std::function<void(Offset)> textDragCallback_;
    GestureEvent longPressInfo_;
    bool isReceivedLongPress_ = false;
    bool isNotInPreviewState_ = false;
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo_;
    bool isSelectedItemNode_ = false;
    bool isOnBeforeLiftingAnimation = false;

    bool isDragUserReject_ = false;

    PanDirection direction_;
    int32_t fingers_ = 1;
    float distance_ = 0.0f;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H
