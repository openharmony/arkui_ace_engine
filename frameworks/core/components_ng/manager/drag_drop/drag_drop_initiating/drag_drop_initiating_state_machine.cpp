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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_idle.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_lifting.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_moving.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_press.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_ready.h"
#include "core/gestures/drag_event.h"
namespace OHOS::Ace::NG {
DragDropInitiatingStateMachine::DragDropInitiatingStateMachine(const RefPtr<FrameNode>& frameNode)
{
    currentState_ = 0;
    dragDropInitiatingParams_.frameNode = frameNode;
}

void DragDropInitiatingStateMachine::InitializeState()
{
    if (dragDropInitiatingState_.empty()) {
        dragDropInitiatingState_ =
            std::vector<RefPtr<DragDropInitiatingStateBase>>(DEFAULT_DRAG_DROP_INITIATING_STATE_SIZE);
    }
    bool needInitializeState = false;
    for (size_t i = 0; i < dragDropInitiatingState_.size(); i++) {
        if (!dragDropInitiatingState_[i]) {
            needInitializeState = true;
            break;
        }
    }
    CHECK_NULL_VOID(needInitializeState);
    dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::IDLE)] =
        MakeRefPtr<DragDropInitiatingStateIdle>(AceType::WeakClaim(this));
    dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::READY)] =
        MakeRefPtr<DragDropInitiatingStateReady>(AceType::WeakClaim(this));
    dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::PRESS)] =
        MakeRefPtr<DragDropInitiatingStatePress>(AceType::WeakClaim(this));
    dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::LIFTING)] =
        MakeRefPtr<DragDropInitiatingStateLifting>(AceType::WeakClaim(this));
    dragDropInitiatingState_[static_cast<int32_t>(DragDropInitiatingStatus::MOVING)] =
        MakeRefPtr<DragDropInitiatingStateMoving>(AceType::WeakClaim(this));
}

void DragDropInitiatingStateMachine::HandleLongPressOnAction(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleLongPressOnAction(info);
    }
}

void DragDropInitiatingStateMachine::HandleLongPressOnActionEnd(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleLongPressOnActionEnd(info);
    }
}

void DragDropInitiatingStateMachine::HandleLongPressOnActionCancel(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleLongPressOnActionCancel(info);
    }
}

void DragDropInitiatingStateMachine::HandlePreviewLongPressOnAction(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePreviewLongPressOnAction(info);
    }
}

void DragDropInitiatingStateMachine::HandlePreviewLongPressOnActionEnd(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePreviewLongPressOnActionEnd(info);
    }
}

void DragDropInitiatingStateMachine::HandlePreviewLongPressOnActionCancel(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePreviewLongPressOnActionCancel(info);
    }
}

void DragDropInitiatingStateMachine::HandlePanOnActionStart(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePanOnActionStart(info);
    }
}

void DragDropInitiatingStateMachine::HandlePanOnActionUpdate(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePanOnActionUpdate(info);
    }
}

void DragDropInitiatingStateMachine::HandlePanOnActionEnd(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePanOnActionEnd(info);
    }
}

void DragDropInitiatingStateMachine::HandlePanOnActionCancel(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePanOnActionCancel(info);
    }
}

void DragDropInitiatingStateMachine::HandlePanOnReject()
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePanOnReject();
    }
}

void DragDropInitiatingStateMachine::HandleSequenceOnActionCancel(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleSequenceOnActionCancel(info);
    }
}

void DragDropInitiatingStateMachine::HandleHitTesting(const TouchEvent& touchEvent)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleHitTesting(touchEvent);
    }
}

void DragDropInitiatingStateMachine::HandleTouchEvent(const TouchEvent& touchEvent)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleTouchEvent(touchEvent);
    }
}

void DragDropInitiatingStateMachine::HandlePullEvent(const DragPointerEvent& dragPointerEvent)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePullEvent(dragPointerEvent);
    }
}

void DragDropInitiatingStateMachine::HandleReStartDrag(const GestureEvent& info)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandleReStartDrag(info);
    }
}

void DragDropInitiatingStateMachine::HandlePreDragStatus(const PreDragStatus preDragStatus)
{
    if (DragInitStateIsNotEmpty()) {
        dragDropInitiatingState_[currentState_]->HandlePreDragStatus(preDragStatus);
    }
}

bool DragDropInitiatingStateMachine::DragInitStateIsNotEmpty()
{
    return !dragDropInitiatingState_.empty() && dragDropInitiatingState_[currentState_] ?
        true : false;
}

void DragDropInitiatingStateMachine::HandleDragStart()
{
    RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::MOVING));
}

void DragDropInitiatingStateMachine::HandleDragEnd()
{
    RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
}

void DragDropInitiatingStateMachine::TransDragWindowToFwk()
{
    RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
}

void DragDropInitiatingStateMachine::TransMenuShow(bool isMenuShow)
{
    if (currentState_ == 0) {
        return;
    }
    if (!isMenuShow) {
        RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
        return;
    }
    RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
}

void DragDropInitiatingStateMachine::SetThumbnailCallback(std::function<void(Offset)>&& callback)
{
    dragDropInitiatingParams_.getTextThumbnailPixelMapCallback = std::move(callback);
}

void DragDropInitiatingStateMachine::RequestStatusTransition(int32_t nextStatus)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "RequestStatusTransition from %{public}d to %{public}d.", currentState_, nextStatus);
    CHECK_NULL_VOID(!dragDropInitiatingState_.empty());
    if (currentState_ != nextStatus) {
        CHECK_NULL_VOID(dragDropInitiatingState_[nextStatus]);
        dragDropInitiatingState_[nextStatus]->Init(currentState_);
        currentState_ = nextStatus;
    }
}
} // namespace OHOS::Ace::NG
