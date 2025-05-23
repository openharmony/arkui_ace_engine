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

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_detector.h"

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_begin.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_cancel.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_end.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_idle.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_machine.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_update.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double SPEED_THRESHOLD = 0.0225;
} // namespace

DragDropSpringLoadingDetector::DragDropSpringLoadingDetector()
{
    stateMachine_ = MakeRefPtr<DragDropSpringLoadingStateMachine>();
    stateMachine_->RegisterStateHandler<DragDropSpringLoadingStateIdle>(
        DragDropSpringLoadingState::IDLE, { DragDropSpringLoadingState::BEGIN });
    stateMachine_->RegisterStateHandler<DragDropSpringLoadingStateBegin>(DragDropSpringLoadingState::BEGIN,
        { DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::END, DragDropSpringLoadingState::CANCEL });
    stateMachine_->RegisterStateHandler<DragDropSpringLoadingStateUpdate>(DragDropSpringLoadingState::UPDATE,
        { DragDropSpringLoadingState::UPDATE, DragDropSpringLoadingState::END, DragDropSpringLoadingState::CANCEL });
    stateMachine_->RegisterStateHandler<DragDropSpringLoadingStateEnd>(
        DragDropSpringLoadingState::END, { DragDropSpringLoadingState::IDLE });
    stateMachine_->RegisterStateHandler<DragDropSpringLoadingStateCancel>(
        DragDropSpringLoadingState::CANCEL, { DragDropSpringLoadingState::IDLE });

    stateMachine_->SetDetector(WeakClaim(this));
}

void DragDropSpringLoadingDetector::NotifyMove(const SpringLoadingParams& params)
{
    CHECK_NULL_VOID(params.dragFrameNode);
    auto eventHub = params.dragFrameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasCustomerOnDragSpringLoading()) {
        return;
    }
    auto isMovementExceedThreshold = IsMovementExceedThreshold(params.curTimeStamp, params.movePoint);
    preMovePoint_ = params.movePoint;
    preTimeStamp_ = params.curTimeStamp;
    if (preTargetFrameNode_ != params.dragFrameNode) {
        preTargetFrameNode_ = params.dragFrameNode;
        stateMachine_->ResetMachine();
        stateMachine_->Begin(params.extraInfo);
        return;
    }
    if (isMovementExceedThreshold) {
        if (stateMachine_->GetCurrentState() == DragDropSpringLoadingState::END) {
            return;
        }
        Intercept(params.extraInfo);
        stateMachine_->Begin(params.extraInfo);
    }
}

void DragDropSpringLoadingDetector::NotifyIntercept(std::string_view extraInfo)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "SpringLoading detector intercept.");
    CHECK_NULL_VOID(preTargetFrameNode_);
    auto eventHub = preTargetFrameNode_->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasCustomerOnDragSpringLoading()) {
        return;
    }
    if (stateMachine_->IsInSpringLoadingState()) {
        if (stateMachine_->GetCurrentState() == DragDropSpringLoadingState::END) {
            stateMachine_->ResetMachine();
            return;
        }
        if (!stateMachine_->RequestStatusTransition(DragDropSpringLoadingState::CANCEL, extraInfo)) {
            stateMachine_->ResetMachine();
        }
    }

    if (stateMachine_->IsWaitingForIdleFinish()) {
        stateMachine_->ResetMachine();
    }

    preTargetFrameNode_ = nullptr;
    preMovePoint_ = Point(0, 0);
    preTimeStamp_ = 0;
}

void DragDropSpringLoadingDetector::Intercept(std::string extraInfo)
{
    if (stateMachine_->IsWaitingForIdleFinish()) {
        stateMachine_->ResetMachine();
    }
    if (stateMachine_->IsInSpringLoadingState()) {
        if (stateMachine_->GetCurrentState() != DragDropSpringLoadingState::END) {
            if (!stateMachine_->RequestStatusTransition(DragDropSpringLoadingState::CANCEL, extraInfo)) {
                stateMachine_->ResetMachine();
            }
        } else {
            stateMachine_->ResetMachine();
        }
    }
}

bool DragDropSpringLoadingDetector::IsMovementExceedThreshold(uint64_t curTimeStamp, Point curMovePoint)
{
    auto timeDelta = curTimeStamp - preTimeStamp_;
    if (timeDelta <= 0 || preTimeStamp_ == 0) {
        return false;
    };
    auto deltaX = PipelineBase::Px2VpWithCurrentDensity((curMovePoint.GetX() - preMovePoint_.GetX())) / timeDelta;
    if (deltaX >= SPEED_THRESHOLD) {
        return true;
    }
    auto deltaY = PipelineBase::Px2VpWithCurrentDensity((curMovePoint.GetY() - preMovePoint_.GetY())) / timeDelta;
    if (deltaY >= SPEED_THRESHOLD) {
        return true;
    }
    auto speedSquared = deltaX * deltaX + deltaY * deltaY;
    return speedSquared >= SPEED_THRESHOLD;
}

} // namespace OHOS::Ace::NG