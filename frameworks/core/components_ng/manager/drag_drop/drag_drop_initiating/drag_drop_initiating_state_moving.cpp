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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_moving.h"

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"
#include "core/gestures/drag_event.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
void DragDropInitiatingStateMoving::HandlePanOnActionEnd(const GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_DRAG, "Trigger drag action end.");
    DragDropGlobalController::GetInstance().ResetDragDropInitiatingStatus();
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (dragDropManager->IsAboutToPreview()) {
        dragDropManager->ResetDragging();
    }
    dragDropManager->SetIsDragNodeNeedClean(false);
    dragDropManager->SetIsDisableDefaultDropAnimation(true);
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    machine->RequestStatusTransition(static_cast<int32_t>(DragDropInitiatingStatus::IDLE));
}
} // namespace OHOS::Ace::NG
