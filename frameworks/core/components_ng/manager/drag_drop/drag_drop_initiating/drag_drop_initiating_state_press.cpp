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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_press.h"

#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/gestures/drag_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {} // namespace
void DragDropInitiatingStatePress::HandlePreviewLongPressOnAction(const GestureEvent& info)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::LIFTING));
}

void DragDropInitiatingStatePress::HandleSequenceOnActionCancel(const GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "Drag event has been canceled.");
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    bool isMenuShow = DragDropGlobalController::GetInstance().IsMenuShowing();
    if (!isMenuShow) {
        machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
    }
}

void DragDropInitiatingStatePress::HandleOnDragStart(RefPtr<FrameNode> frameNode, const GestureEvent& info)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (!CheckStatusForPanActionBegin(frameNode, info)) {
        return;
    }
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (gestureHub->GetTextDraggable()) {
        HandleTextDragStart(frameNode, info);
        return;
    }
    dragDropManager->ResetDragging(DragDropMgrState::ABOUT_TO_PREVIEW);
    HideEventColumn();
    DragDropFuncWrapper::RecordMenuWrapperNodeForDrag(frameNode->GetId());
    auto gestureEvent = info;
    gestureHub->HandleOnDragStart(gestureEvent);
}

void DragDropInitiatingStatePress::HandlePanOnActionStart(const GestureEvent& info)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        HandleOnDragStart(frameNode, info);
    }
}

void DragDropInitiatingStatePress::HandlePanOnReject()
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger pan onReject");
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    if (manager->IsGatherWithMenu() || !params.hasGatherNode) {
        return;
    }
    auto preDragStatus = DragDropGlobalController::GetInstance().GetPreDragStatus();
    if (preDragStatus <= PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION) {
        manager->RemoveGatherNode();
    } else {
        manager->RemoveGatherNodeWithAnimation();
    }
}

void DragDropInitiatingStatePress::HandleTouchEvent(const TouchEvent& touchEvent)
{
    UpdatePointInfoForFinger(touchEvent);
}

void DragDropInitiatingStatePress::HandlePanOnActionEnd(const GestureEvent& info)
{
    OnActionEnd(info);
}

void DragDropInitiatingStatePress::Init(int32_t currentState)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger long press for 500ms.");
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto dragdropEvent = gestureHub->GetDragEventActuator();
    CHECK_NULL_VOID(dragdropEvent);
    dragdropEvent->CallTimerCallback(frameNode);
    InteractionInterface::GetInstance()->SetDraggableState(true);
    if (!params.isThumbnailCallbackTriggered && !gestureHub->GetTextDraggable()) {
        auto getPixelMapFinishCallback = [weak = AceType::WeakClaim(this)](
                                             RefPtr<PixelMap> pixelMap, bool immediately) {
            auto stateReady = weak.Upgrade();
            CHECK_NULL_VOID(stateReady);
            stateReady->PrepareFinalPixelMapForDragThroughTouch(pixelMap, immediately);
        };
        DragDropFuncWrapper::GetThumbnailPixelMap(gestureHub, getPixelMapFinishCallback, true);
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetIsShowBadgeAnimation(true);
    DragDropGlobalController::GetInstance().SetPrepareDragFrameNode(frameNode);
    if (!gestureHub->GetTextDraggable()) {
        UpdateDragPreviewOptionFromModifier();
        DragEventActuator::ExecutePreDragAction(PreDragStatus::READY_TO_TRIGGER_DRAG_ACTION, frameNode);
    }
}
} // namespace OHOS::Ace::NG
