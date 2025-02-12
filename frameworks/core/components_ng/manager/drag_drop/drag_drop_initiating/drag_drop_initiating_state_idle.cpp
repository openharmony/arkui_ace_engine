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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_idle.h"

#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/gestures/drag_event.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
void DragDropInitiatingStateIdle::ResetStateForHitTest(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->SetIsDragNodeNeedClean(false);
    dragDropManager->SetIsDisableDefaultDropAnimation(false);
    DragDropGlobalController::GetInstance().SetPrepareDragFrameNode(nullptr);
    DragDropGlobalController::GetInstance().SetPreDragStatus(PreDragStatus::ACTION_DETECTING_STATUS);
}

void DragDropInitiatingStateIdle::Init(int32_t currentState)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    bool isMenuShow = DragDropGlobalController::GetInstance().IsMenuShowing();
    if (!isMenuShow && currentState == static_cast<int32_t>(DragDropInitiatingStatus::PRESS) &&
        !gestureHub->GetTextDraggable()) {
        DragEventActuator::ExecutePreDragAction(PreDragStatus::ACTION_CANCELED_BEFORE_DRAG, frameNode);
    }

    AsyncDragEnd();
    ResetBorderRadiusAnimation();
    UnRegisterDragListener();
    HideEventColumn();
    HidePixelMap();
    params.Reset();
}

void DragDropInitiatingStateIdle::StartCreateSnapshotTask(int32_t fingerId)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto&& getThumbnailCallback = [weak = WeakClaim(this), weakNode = AceType::WeakClaim(RawPtr(frameNode)),
                                      fingerId]() {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        if (DragDropFuncWrapper::CheckIfNeedGetThumbnailPixelMap(frameNode, fingerId)) {
            return;
        }
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto getPixelMapFinishCallback = [weak](RefPtr<PixelMap> pixelMap, bool immediately) {
            auto stateIdle = weak.Upgrade();
            CHECK_NULL_VOID(stateIdle);
            stateIdle->PrepareFinalPixelMapForDragThroughTouch(pixelMap, immediately);
        };
        DragDropFuncWrapper::GetThumbnailPixelMap(gestureHub, getPixelMapFinishCallback, false);
    };
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    params.getThumbnailPixelMapCallback.Reset(getThumbnailCallback);
    taskExecutor.PostDelayedTask(
        params.getThumbnailPixelMapCallback, SNAPSHOT_DELAY_TIME, "ArkUIDragDropSnapShotThumbnailTimer");
}

void DragDropInitiatingStateIdle::StartPreDragDetectingStartTask()
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto&& preDragCallback = [weakNode = AceType::WeakClaim(RawPtr(frameNode))]() {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        DragEventActuator::ExecutePreDragAction(PreDragStatus::ACTION_DETECTING_STATUS, frameNode);
    };
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    params.notifyPreDragCallback.Reset(preDragCallback);
    taskExecutor.PostDelayedTask(
        params.notifyPreDragCallback, PRE_DRAG_DELAY_TIME, "ArkUIDragDropPreDragDetectingThumbnailTimer");
}

void DragDropInitiatingStateIdle::StartGatherTask()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    if (!params.isNeedGather) {
        params.showGatherCallback.Cancel();
        return;
    }
    auto&& showGatherCallback = [weakNode = AceType::WeakClaim(RawPtr(frameNode))]() {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        DragAnimationHelper::ShowGatherNodeAnimation(frameNode);
    };
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    params.showGatherCallback.Reset(showGatherCallback);
    taskExecutor.PostDelayedTask(
        params.showGatherCallback, SNAPSHOT_DELAY_TIME, "ArkUIDragDropStartGather");
}

void DragDropInitiatingStateIdle::StartPreDragStatusCallback(const TouchEvent& touchEvent)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto&& preDragStatusCallback = [weakNode = AceType::WeakClaim(RawPtr(frameNode))]() {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger long press for 350ms..");
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        if (!gestureHub->GetTextDraggable()) {
            DragEventActuator::ExecutePreDragAction(PreDragStatus::PREPARING_FOR_DRAG_DETECTION, frameNode);
        }
    };

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    params.preDragStatusCallback.Reset(preDragStatusCallback);
    taskExecutor.PostDelayedTask(
        params.preDragStatusCallback, GetCurDuration(touchEvent, DEALY_TASK_DURATION), "ArkUIPreDragLongPressTimer");
}

void DragDropInitiatingStateIdle::HandleHitTesting(const TouchEvent& touchEvent)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    ResetStateForHitTest(frameNode);
    params.triggeredSourceType = touchEvent.sourceType;
    params.idleFingerId = touchEvent.id;
    params.isNeedGather = DragDropFuncWrapper::CheckIsNeedGather(frameNode);
    RegisterDragListener();
    if (touchEvent.sourceType != SourceType::MOUSE) {
        StartCreateSnapshotTask(touchEvent.id);
        StartPreDragDetectingStartTask();
        StartGatherTask();
        StartPreDragStatusCallback(touchEvent);
    }
    machine->RequestStatusTransition(AceType::Claim(this), static_cast<int32_t>(DragDropInitiatingStatus::READY));
}

void DragDropInitiatingStateIdle::RegisterDragListener()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    eventManager->RegisterDragTouchEventListener(frameNode->GetId(),
        [weakMachine = WeakPtr<DragDropInitiatingStateMachine>(machine)](const TouchEvent& touchEvent) {
            auto machine = weakMachine.Upgrade();
            CHECK_NULL_VOID(machine);
            machine->HandleTouchEvent(touchEvent);
        });
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->RegisterPullEventListener(frameNode->GetId(),
        [weakMachine = WeakPtr<DragDropInitiatingStateMachine>(machine)](const DragPointerEvent& dragPointerEvent) {
            auto machine = weakMachine.Upgrade();
            CHECK_NULL_VOID(machine);
            machine->HandlePullEvent(dragPointerEvent);
        });
}

void DragDropInitiatingStateIdle::UnRegisterDragListener()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto nodeId = frameNode->GetId();
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    eventManager->UnRegisterDragTouchEventListener(nodeId);
    dragDropManager->UnRegisterPullEventListener(nodeId);
}

void DragDropInitiatingStateIdle::AsyncDragEnd()
{
    if (DragDropGlobalController::GetInstance().GetDragStartRequestStatus() == DragStartRequestStatus::WAITING) {
        FireCustomerOnDragEnd();
    }
}
} // namespace OHOS::Ace::NG
