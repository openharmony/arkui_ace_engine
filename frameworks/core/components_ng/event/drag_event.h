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
#include "core/components/common/properties/decoration.h"

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

    const GestureEventFunc& GetLongPressEventFunc() const
    {
        return actionLongPress_;
    }

    void SetLongPressEventFunc(GestureEventFunc&& actionLongPress)
    {
        actionLongPress_ = std::move(actionLongPress);
    }

    const std::vector<KeyCode>& GetPressedKeyCodes() const
    {
        return pressedKeyCodes_;
    }

    void SetPressedKeyCodes(const std::vector<KeyCode>& pressedKeyCodes)
    {
        pressedKeyCodes_ = pressedKeyCodes;
    }

private:
    GestureEventFunc actionStart_;
    GestureEventFunc actionUpdate_;
    GestureEventFunc actionEnd_;
    GestureEventNoParameter actionCancel_;
    GestureEventFunc actionLongPress_;
    std::vector<KeyCode> pressedKeyCodes_;
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

    bool HasDragEvent() const
    {
        return static_cast<bool>(userCallback_);
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
        const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result,
        ResponseLinkResult& responseLinkResult) override;
    void SetThumbnailCallback(std::function<void(Offset)>&& callback);
    void SetFilter(const RefPtr<DragEventActuator>& actuator);
    static void UpdatePreviewPositionAndScale(
        const RefPtr<FrameNode>& imageNode, const OffsetF& frameOffset, float scale = -1.0f);
    static void UpdatePreviewAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode);
    static void UpdateGatherAnimatePosition(
        std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo, const OffsetF& GatherNodeOffset);
    static void CreatePreviewNode(const RefPtr<FrameNode>& frameNode, OHOS::Ace::RefPtr<FrameNode>& imageNode);
    static void SetPreviewDefaultAnimateProperty(const RefPtr<FrameNode>& imageNode);
    static void MountPixelMap(const RefPtr<OverlayManager>& overlayManager, const RefPtr<GestureEventHub>& manager,
        const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& textNode, bool isDragPixelMap = false);
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
    void SetDragDampStartPointInfo(const Point& point, int32_t pointerId);
    void HandleDragDampingMove(const Point& point, int32_t pointerId, bool isRedragStart = false);
    void SetTextPixelMap(const RefPtr<GestureEventHub>& gestureHub);
    void RestartDragTask(const GestureEvent& info);
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

    bool IsNotNeedShowPreviewForWeb(const RefPtr<FrameNode>& frameNode);
    void StartDragTaskForWeb(const GestureEvent& info);
    void StartLongPressActionForWeb(bool isFloatImage = true);
    void CancelDragForWeb();
    void ResetDragActionForWeb() {
        if (isReceivedLongPress_) {
            isReceivedLongPress_ = false;
        }
        isFloatImage_ = true;
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

    void SetIsDefaultOnDragStartExecuted(bool defaultOnDragStartExecuted)
    {
        defaultOnDragStartExecuted_ = defaultOnDragStartExecuted;
    }

    bool IsDefaultOnDragStartExecuted() const
    {
        return defaultOnDragStartExecuted_;
    }

    const OptionsAfterApplied& GetOptionsAfterApplied()
    {
        return optionsAfterApplied_;
    }

    void CopyDragEvent(const RefPtr<DragEventActuator>& dragEventActuator);

    void SetGatherNodeAboveFilter(const RefPtr<DragEventActuator>& actuator);
    bool IsBelongToMultiItemNode(const RefPtr<FrameNode>& frameNode);
    bool IsSelectedItemNode(const RefPtr<UINode>& uiNode);
    void FindItemParentNode(const RefPtr<FrameNode>& frameNode);
    bool IsNeedGather() const;
    static RefPtr<FrameNode> GetOrCreateGatherNode(const RefPtr<NG::OverlayManager>& overlayManager,
        const RefPtr<DragEventActuator>& actuator, std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    static RefPtr<FrameNode> CreateGatherNode(const RefPtr<DragEventActuator>& actuator);
    static RefPtr<FrameNode> CreateImageNode(
        const RefPtr<FrameNode>& frameNode, GatherNodeChildInfo& gatherNodeChildInfo);
    static void MarkDirtyGatherNode(const RefPtr<FrameNode>& gatherNode);
    static void ResetNode(const RefPtr<FrameNode>& frameNode);
    static void MountGatherNode(const RefPtr<OverlayManager>& overlayManager, const RefPtr<FrameNode>& frameNode,
        const RefPtr<FrameNode>& gatherNode, const std::vector<GatherNodeChildInfo>& gatherNodeChildrenInfo);
    static void GetFrameNodePreviewPixelMap(const RefPtr<FrameNode>& frameNode);
    void SetGatherNode(const RefPtr<FrameNode>& gatherNode);
    RefPtr<FrameNode> GetGatherNode() const;
    const std::vector<GatherNodeChildInfo>& GetGatherNodeChildrenInfo() const;
    void ClearGatherNodeChildrenInfo();
    void PushBackGatherNodeChild(GatherNodeChildInfo& gatherNodeChild);
    void AddTouchListener(const TouchRestrict& touchRestrict) override;
    void HandleTouchUpEvent();
    void HandleTouchMoveEvent();
    void HandleTouchCancelEvent();
    const RefPtr<FrameNode> GetItemParentNode() const;
    RefPtr<FrameNode> GetFrameNode();
    static void PrepareShadowParametersForDragData(const RefPtr<FrameNode>& frameNode,
       std::unique_ptr<JsonValue>& arkExtraInfoJson, float scale);
    static void PrepareRadiusParametersForDragData(const RefPtr<FrameNode>& frameNode,
        std::unique_ptr<JsonValue>& arkExtraInfoJson);
    static void ParseShadowInfo(Shadow& shadow, std::unique_ptr<JsonValue>& arkExtraInfoJson);
    static std::optional<Shadow> GetDefaultShadow();
    static std::optional<BorderRadiusProperty> GetDefaultBorderRadius();

    inline static void FlushSyncGeometryNodeTasks();

    void ShowPreviewBadgeAnimation(
        const RefPtr<DragEventActuator>& dragEventActuator, const RefPtr<OverlayManager>& manager);
    static RefPtr<FrameNode> CreateBadgeTextNode(
        const RefPtr<FrameNode>& frameNode, int32_t childSize, float previewScale, bool isUsePixelMapOffset = false);

    void GetThumbnailPixelMapAsync(const RefPtr<GestureEventHub>& gestureHub);
    void SetResponseRegionFull();
    void ResetResponseRegion();
    static void ResetDragStatus();
    void PrepareFinalPixelMapForDragThroughTouch(RefPtr<PixelMap> pixelMap, bool immediately);
    void DoPixelMapScaleForDragThroughTouch(RefPtr<PixelMap> pixelMap, float targetScale);
    RefPtr<PixelMap> GetPreScaledPixelMapForDragThroughTouch(float& preScale);
    void ResetPreScaledPixelMapForDragThroughTouch();

private:
    void UpdatePreviewOptionFromModifier(const RefPtr<FrameNode>& frameNode);
    void UpdatePreviewOptionDefaultAttr(const RefPtr<FrameNode>& frameNode);
    static void SetImageNodeInitAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode);
    static void SetImageNodeFinishAttr(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& imageNode);
    static void ApplyNewestOptionExecutedFromModifierToNode(
        const RefPtr<FrameNode>& optionHolderNode, const RefPtr<FrameNode>& targetNode);
    // check global dragging status
    bool IsGlobalStatusSuitableForDragging();
    // check the current node's status to decide if it can initiate one drag operation
    bool IsCurrentNodeStatusSuitableForDragging(
        const RefPtr<FrameNode>& frameNode, const TouchRestrict& touchRestrict);
    bool IsSelfAndParentDragForbidden(const RefPtr<FrameNode>& frameNode);
    std::optional<EffectOption> BrulStyleToEffection(const std::optional<BlurStyleOption>& blurStyleOp);
    float RadiusToSigma(float radius);
    void RecordMenuWrapperNodeForDrag(int32_t targetId);

private:
    WeakPtr<GestureEventHub> gestureEventHub_;
    WeakPtr<FrameNode> itemParentNode_;
    RefPtr<DragEvent> userCallback_;
    RefPtr<DragEvent> customCallback_;
    RefPtr<PanRecognizer> panRecognizer_;
    RefPtr<LongPressRecognizer> longPressRecognizer_;
    RefPtr<LongPressRecognizer> previewLongPressRecognizer_;
    RefPtr<SequencedRecognizer> SequencedRecognizer_;
    RefPtr<FrameNode> gatherNode_;
    RefPtr<TouchEventImpl> touchListener_;

    RefPtr<PixelMap> textPixelMap_;
    RefPtr<PixelMap> preScaledPixelMap_;
    std::function<void(GestureEvent&)> actionStart_;
    std::function<void(GestureEvent&)> longPressUpdate_;
    std::function<void()> actionCancel_;
    std::function<void(Offset)> textDragCallback_;
    GestureEvent longPressInfo_;
    bool isReceivedLongPress_ = false;
    bool isFloatImage_ = true;
    bool isNotInPreviewState_ = false;
    std::vector<GatherNodeChildInfo> gatherNodeChildrenInfo_;
    std::vector<DimensionRect> responseRegion_;
    bool isSelectedItemNode_ = false;
    bool isOnBeforeLiftingAnimation = false;
    bool isDragPrepareFinish_ = false;

    bool isDragUserReject_ = false;
    bool defaultOnDragStartExecuted_ = false;
    bool isResponseRegionFull_ = false;
    OptionsAfterApplied optionsAfterApplied_;

    PanDirection direction_;
    int32_t fingers_ = 1;
    float distance_ = 0.0f;
    float preScaleValue_ = 1.0f;
    bool isRedragStart_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_DRAG_EVENT_H
