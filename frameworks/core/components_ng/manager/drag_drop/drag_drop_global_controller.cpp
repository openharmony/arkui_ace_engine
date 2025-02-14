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

#include "core/components_ng/manager/drag_drop/drag_drop_global_controller.h"

#include <csignal>
#include <thread>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

DragDropGlobalController::~DragDropGlobalController() {}

DragDropGlobalController& DragDropGlobalController::GetInstance()
{
    static DragDropGlobalController singleInstance;
    return singleInstance;
}

void DragDropGlobalController::UpdateMenuShowingStatus(bool isShowing)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    isContextMenuShowing_ = isShowing;
}

void DragDropGlobalController::PublishMenuStatusWithNode(bool isShowing, const RefPtr<FrameNode>& targetNode)
{
    UpdateMenuShowingStatus(isShowing);
    if (isShowing) {
        menuLiftingTargetNode_ = targetNode;
    }
    auto frameNode = menuLiftingTargetNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = eventHub->GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto dragEventActuator = gestureHub->GetDragEventActuator();
    CHECK_NULL_VOID(dragEventActuator);
    dragEventActuator->NotifyMenuShow(isShowing);
}

bool DragDropGlobalController::IsMenuShowing() const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return isContextMenuShowing_;
}

void DragDropGlobalController::SetDragStartRequestStatus(DragStartRequestStatus dragStartRequestStatus)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    dragStartRequestStatus_ = dragStartRequestStatus;
}

DragStartRequestStatus DragDropGlobalController::GetDragStartRequestStatus()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return dragStartRequestStatus_;
}

void DragDropGlobalController::SetAsyncDragCallback(std::function<void()> asyncDragCallbac)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    asyncDragCallback_ = asyncDragCallbac;
}

std::function<void()> DragDropGlobalController::GetAsyncDragCallback()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return asyncDragCallback_;
}

void DragDropGlobalController::UpdateDragDropInitiatingStatus(const RefPtr<FrameNode>& frameNode,
    const DragDropInitiatingStatus& dragStatus)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    CHECK_NULL_VOID(frameNode);
    if (dragStatus == DragDropInitiatingStatus::MOVING) {
        currentDragNode_ = frameNode;
    }
}

bool DragDropGlobalController::IsInMoving() const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return currentDragNode_;
}

void DragDropGlobalController::ResetDragDropInitiatingStatus()
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    currentDragNode_ = nullptr;
}

void DragDropGlobalController::SetPrepareDragFrameNode(const WeakPtr<FrameNode>& prepareDragFrameNode)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    prepareDragFrameNode_ = prepareDragFrameNode;
}

const WeakPtr<FrameNode> DragDropGlobalController::GetPrepareDragFrameNode() const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return prepareDragFrameNode_;
}

void DragDropGlobalController::SetPreDragStatus(PreDragStatus preDragStatus)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    preDragStatus_ = preDragStatus;
}

PreDragStatus DragDropGlobalController::GetPreDragStatus() const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return preDragStatus_;
}

void DragDropGlobalController::UpdateDragFilterShowingStatus(bool isShowing)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    isDragFilterShowing_ = isShowing;
}

bool DragDropGlobalController::IsDragFilterShowing() const
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return isDragFilterShowing_;
}

bool DragDropGlobalController::IsOnOnDropPhase()
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    return isOnOnDropPhase_;
}

void DragDropGlobalController::SetIsOnOnDropPhase(bool isOnOnDropPhase)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    isOnOnDropPhase_ = isOnOnDropPhase;
}

bool DragDropGlobalController::RequestDragEndCallback(int32_t requestId,
    DragRet dragResult, std::function<void(const DragRet&)> stopDragCallback)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (requestId == -1 || stopDragCallback == nullptr || !isOnOnDropPhase_) {
        return false;
    }
    requestId_ = requestId;
    stopDragCallback_ = stopDragCallback;
    dragResult_ = dragResult;
    return true;
}

int32_t DragDropGlobalController::NotifyDragResult(int32_t requestId, int32_t result)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    if (requestId_ != requestId) {
        return -1;
    }
    dragResult_ = static_cast<DragRet>(result);
    return 0;
}

int32_t DragDropGlobalController::NotifyDragEndPendingDone(int32_t requestId)
{
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (requestId_ != requestId || !isOnOnDropPhase_) {
            return -1;
        }
        requestId_ = -1;
        isOnOnDropPhase_ = false;
    }
    if (stopDragCallback_) {
        stopDragCallback_(dragResult_);
    }
    stopDragCallback_ = nullptr;
    dragResult_ = DragRet::DRAG_FAIL;
    return 0;
}

} // namespace OHOS::Ace
