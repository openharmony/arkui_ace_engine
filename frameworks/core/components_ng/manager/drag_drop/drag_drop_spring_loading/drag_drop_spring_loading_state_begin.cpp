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

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_begin.h"

#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_machine.h"

namespace OHOS::Ace::NG {
void DragDropSpringLoadingStateBegin::OnEnter(std::string_view extraInfo)
{
    auto stateMachine = GetStateMachine();
    CHECK_NULL_VOID(stateMachine);
    auto frameNode = stateMachine->GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto callback = eventHub->GetCustomerOnDragSpringLoading();
    CHECK_NULL_VOID(callback);
    auto context = MakeRefPtr<DragSpringLoadingContext>();
    CHECK_NULL_VOID(context);
    auto relatedConfigurations = frameNode->GetOrCreateDragDropRelatedConfigurations();
    CHECK_NULL_VOID(relatedConfigurations);
    stateMachine->SetUserConfig(relatedConfigurations->GetOrCreateDragSpringLoadingConfiguration());
    UpdateDragSpringLoadingContext(context, extraInfo);
    callback(context);
    if (context->IsSpringLoadingAborted()) {
        if (!stateMachine->RequestStatusTransition(DragDropSpringLoadingState::CANCEL, extraInfo)) {
            stateMachine->ResetMachine();
        }
        return;
    }
    const auto& userConfig = context->GetDragSpringLoadingConfiguration();
    CHECK_NULL_VOID(userConfig);
    stateMachine->SetUserConfig(userConfig);
    auto weak = WeakPtr<DragDropSpringLoadingStateMachine>(stateMachine);
    if (userConfig->updateNotifyCount == 0) {
        stateMachine->PostDelayedTask(
            [weak, extraInfoStr = std::string(extraInfo)]() {
                auto stateMachine = weak.Upgrade();
                CHECK_NULL_VOID(stateMachine);
                if (!stateMachine->RequestStatusTransition(DragDropSpringLoadingState::END, extraInfoStr)) {
                    stateMachine->RequestStatusTransition(DragDropSpringLoadingState::CANCEL, extraInfoStr);
                }
            },
            userConfig->updateToFinishInterval, DRAG_GROP_SPRING_LOADING_TASK_NAME);
        return;
    }
    stateMachine->PostDelayedTask(
        [weak, extraInfoStr = std::string(extraInfo)]() {
            auto stateMachine = weak.Upgrade();
            CHECK_NULL_VOID(stateMachine);
            if (!stateMachine->RequestStatusTransition(DragDropSpringLoadingState::UPDATE, extraInfoStr)) {
                stateMachine->RequestStatusTransition(DragDropSpringLoadingState::CANCEL, extraInfoStr);
            }
        },
        userConfig->updateInterval, DRAG_GROP_SPRING_LOADING_TASK_NAME);
}
} // namespace OHOS::Ace::NG