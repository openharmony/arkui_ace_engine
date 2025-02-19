/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_BASE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"
#include "core/event/pointer_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TIME_BASE = 1000 * 1000;
}
class DragDropInitiatingStateMachine;

struct DragDropInitiatingParams {
    int32_t idleFingerId = -1;
    float preScaleValue = 1.0f;
    bool isThumbnailCallbackTriggered = false;
    bool isNeedGather = false;
    RefPtr<PixelMap> preScaledPixelMap;
    std::function<void(Offset)> getTextThumbnailPixelMapCallback;
    CancelableCallback<void()> getThumbnailPixelMapCallback;
    CancelableCallback<void()> notifyPreDragCallback;
    CancelableCallback<void()> showGatherCallback;
    CancelableCallback<void()> preDragStatusCallback;
    OptionsAfterApplied optionsAfterApplied;
    WeakPtr<FrameNode> frameNode;
    SourceType triggeredSourceType;

    RefPtr<FrameNode> GetFrameNode()
    {
        return frameNode.Upgrade();
    }

    void Reset()
    {
        idleFingerId = -1;
        preScaleValue = 1.0f;
        preScaledPixelMap = nullptr;
        triggeredSourceType = SourceType::TOUCH;
        isThumbnailCallbackTriggered = false;
        isNeedGather = false;
        getTextThumbnailPixelMapCallback = nullptr;
        getThumbnailPixelMapCallback.Cancel();
        notifyPreDragCallback.Cancel();
        showGatherCallback.Cancel();
        preDragStatusCallback.Cancel();
    }
};

class DragDropInitiatingStateBase : public AceType {
    DECLARE_ACE_TYPE(DragDropInitiatingStateBase, AceType);

public:
    DragDropInitiatingStateBase(const WeakPtr<DragDropInitiatingStateMachine>& machine) : stateMachine_(machine) {};
    ~DragDropInitiatingStateBase() = default;

    virtual void HandleLongPressOnAction(const GestureEvent& info) {}
    virtual void HandleLongPressOnActionEnd(const GestureEvent& info) {}
    virtual void HandleLongPressOnActionCancel(const GestureEvent& info) {}
    virtual void HandlePreviewLongPressOnAction(const GestureEvent& info) {}
    virtual void HandlePreviewLongPressOnActionEnd(const GestureEvent& info) {}
    virtual void HandlePreviewLongPressOnActionCancel(const GestureEvent& info) {}
    virtual void HandlePanOnActionStart(const GestureEvent& info) {}
    virtual void HandlePanOnActionUpdate(const GestureEvent& info) {}
    virtual void HandlePanOnActionEnd(const GestureEvent& info) {}
    virtual void HandlePanOnActionCancel(const GestureEvent& info) {}
    virtual void HandlePanOnReject() {}
    virtual void HandleSequenceOnActionCancel(const GestureEvent& info) {}
    virtual void HandleHitTesting(const TouchEvent& touchEvent) {}
    virtual void HandleTouchEvent(const TouchEvent& touchEvent) {}
    virtual void HandlePullEvent(const DragPointerEvent& dragPointerEvent) {}
    virtual void HandleReStartDrag(const GestureEvent& info) {}
    virtual void HandleDragStart() {}

    virtual void Init(int32_t currentState) {}

protected:
    RefPtr<DragDropInitiatingStateMachine> GetStateMachine()
    {
        return stateMachine_.Upgrade();
    }

    bool IsAllowedDrag();
    void UpdateDragPreviewOptionFromModifier();
    void ResetBorderRadiusAnimation();
    void DoPixelMapScaleForDragThroughTouch(
        DragDropInitiatingParams& params, const RefPtr<PixelMap>& pixelMap, float targetScale);
    void PrepareFinalPixelMapForDragThroughTouch(const RefPtr<PixelMap>& pixelMap, bool immediately);
    void HideEventColumn();
    void HidePixelMap(bool startDrag = false, double x = 0, double y = 0, bool showAnimation = true);
    bool CheckStatusForPanActionBegin(const RefPtr<FrameNode>& frameNode, const GestureEvent& info);
    int32_t GetCurDuration(const TouchEvent& touchEvent, int32_t curDuration);
    void FireCustomerOnDragEnd();
private:
    WeakPtr<DragDropInitiatingStateMachine> stateMachine_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_BASE_H