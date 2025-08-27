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

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_base.h"

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_machine.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
DragSpringLoadingState DragDropSpringLoadingStateBase::ConvertDragSpringLoadingState(
    DragDropSpringLoadingState state) const
{
    switch (state) {
        case DragDropSpringLoadingState::BEGIN:
            return DragSpringLoadingState::BEGIN;
        case DragDropSpringLoadingState::UPDATE:
            return DragSpringLoadingState::UPDATE;
        case DragDropSpringLoadingState::END:
            return DragSpringLoadingState::END;
        case DragDropSpringLoadingState::CANCEL:
            return DragSpringLoadingState::CANCEL;
        default:
            return DragSpringLoadingState::CANCEL;
    }
}

void DragDropSpringLoadingStateBase::UpdateDragSpringLoadingContext(
    RefPtr<OHOS::Ace::DragSpringLoadingContext>& context, std::string_view extraInfo)
{
    CHECK_NULL_VOID(context);
    auto stateMachine = GetStateMachine();
    CHECK_NULL_VOID(stateMachine);
    stateMachine->IncrementCurrentNotifySequence();
    context->SetCurrentNotifySequence(stateMachine->GetCurrentNotifySequence());
    auto frameNode = stateMachine->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragManager);
    context->SetExtraInfos(
        eventHub->GetDragExtraParams(extraInfo.data(), stateMachine->GetPoint(), DragEventType::MOVE));
    context->SetSummary(dragManager->GetSummaryMap());
    context->SetState(ConvertDragSpringLoadingState(stateMachine->GetCurrentState()));
    context->SetDragSpringLoadingConfiguration(stateMachine->GetUserConfig());
}
} // namespace OHOS::Ace::NG