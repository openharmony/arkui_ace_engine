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

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_idle.h"

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_machine.h"

namespace OHOS::Ace::NG {
void DragDropSpringLoadingStateIdle::OnEnter(std::string_view extraInfo)
{
    auto stateMachine = GetStateMachine();
    CHECK_NULL_VOID(stateMachine);
    auto frameNode = stateMachine->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto relatedConfigurations = frameNode->GetOrCreateDragDropRelatedConfigurations();
    CHECK_NULL_VOID(relatedConfigurations);
    const auto& config = relatedConfigurations->GetOrCreateDragSpringLoadingConfiguration();
    auto weak = AceType::WeakClaim(AceType::RawPtr(stateMachine));
    stateMachine->PostDelayedTask(
        [weak, extraInfoStr = std::string(extraInfo)]() {
            auto stateMachine = weak.Upgrade();
            CHECK_NULL_VOID(stateMachine);
            stateMachine->SetWaitingForIdleFinish(false);
            stateMachine->RequestStatusTransition(DragDropSpringLoadingState::BEGIN, extraInfoStr);
        },
        config->stillTimeLimit, DRAG_GROP_SPRING_LOADING_TASK_NAME);
}
} // namespace OHOS::Ace::NG