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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_MACHINE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_MACHINE_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_base.h"
#include "core/event/pointer_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace::NG {
class DragDropInitiatingStateBase;
class DragDropInitiatingStateMachine : public AceType {
    DECLARE_ACE_TYPE(DragDropInitiatingStateMachine, AceType);

public:
    DragDropInitiatingStateMachine(const RefPtr<FrameNode>& frameNode);
    ~DragDropInitiatingStateMachine() = default;

    void HandleLongPressOnAction(const GestureEvent& info);
    void HandleLongPressOnActionEnd(const GestureEvent& info);
    void HandleLongPressOnActionCancel(const GestureEvent& info);
    void HandlePreviewLongPressOnAction(const GestureEvent& info);
    void HandlePreviewLongPressOnActionEnd(const GestureEvent& info);
    void HandlePreviewLongPressOnActionCancel(const GestureEvent& info);
    void HandlePanOnActionStart(const GestureEvent& info);
    void HandlePanOnActionUpdate(const GestureEvent& info);
    void HandlePanOnActionEnd(const GestureEvent& info);
    void HandlePanOnActionCancel(const GestureEvent& info);
    void HandlePanOnReject();
    void HandleSequenceOnActionCancel(const GestureEvent& info);
    void HandleHitTesting(const TouchEvent& touchEvent);
    void HandleTouchEvent(const TouchEvent& touchEvent);
    void HandlePullEvent(const DragPointerEvent& dragPointerEvent);
    void HandleReStartDrag(const GestureEvent& info);
    void HandleDragStart();
    void HandleDragEnd();
    void TransDragWindowToFwk();

    void RequestStatusTransition(RefPtr<DragDropInitiatingStateBase> currentState, int32_t nextStatus);
    void TransMenuShow(bool isMenuShow);
    void SetThumbnailCallback(std::function<void(Offset)>&& callback);

    DragDropInitiatingParams& GetDragDropInitiatingParams()
    {
        return dragDropInitiatingParams_;
    }

    DragDropInitiatingStatus GetDragDropInitiatingStatus()
    {
        return static_cast<DragDropInitiatingStatus>(currentState_);
    }

private:
    void InitializeState();

private:
    DragDropInitiatingParams dragDropInitiatingParams_;
    int32_t currentState_ = 0;
    std::vector<RefPtr<DragDropInitiatingStateBase>> dragDropInitiatingState_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_INITIATING_STATE_MACHINE_H