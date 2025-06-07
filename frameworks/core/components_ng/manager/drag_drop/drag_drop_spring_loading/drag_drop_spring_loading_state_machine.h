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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_MACHINE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_MACHINE_H

#include <string_view>
#include <unordered_map>

#include "ui/base/referenced.h"

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_related_configuration.h"
#include "core/components_ng/manager/drag_drop/drag_drop_spring_loading/drag_drop_spring_loading_state_base.h"

namespace OHOS::Ace::NG {
class DragDropSpringLoadingDetector;
class DragDropSpringLoadingStateMachine : public AceType {
    DECLARE_ACE_TYPE(DragDropSpringLoadingStateMachine, AceType);

public:
    DragDropSpringLoadingStateMachine();
    ~DragDropSpringLoadingStateMachine() = default;

    template<class T>
    void RegisterStateHandler(
        DragDropSpringLoadingState state, const std::vector<DragDropSpringLoadingState>& transitions)
    {
        CHECK_NULL_VOID(stateMachinePool_);
        stateMachinePool_->RegisterStateHandler<T>(state, transitions, AceType::WeakClaim(this));
    }

    void SetDetector(const WeakPtr<DragDropSpringLoadingDetector>& detector)
    {
        detector_ = detector;
    }

    DragDropSpringLoadingState GetCurrentState() const
    {
        return currentState_;
    };

    bool RequestStatusTransition(DragDropSpringLoadingState nextState, std::string_view extraInfo);

    void ResetMachine();

    bool IsInSpringLoadingState() const
    {
        return currentState_ == DragDropSpringLoadingState::BEGIN ||
               currentState_ == DragDropSpringLoadingState::UPDATE || currentState_ == DragDropSpringLoadingState::END;
    }

    bool IsWaitingForIdleFinish() const
    {
        return isWaitingForIdleFinish_;
    }

    void SetWaitingForIdleFinish(bool isWaiting)
    {
        isWaitingForIdleFinish_ = isWaiting;
    }

    void PostDelayedTask(const std::function<void()>&& task, uint32_t delay, const std::string& name);

    void Begin(std::string_view extraInfo);

    void IncrementCurrentNotifySequence()
    {
        currentNotifySequence_++;
    }

    int32_t GetCurrentNotifySequence()
    {
        return currentNotifySequence_;
    }

    void IncrementCurrentUpdateNotifyCount()
    {
        currentUpdateNotifyCount_++;
    }

    int32_t GetCurrentUpdateNotifyCount()
    {
        return currentUpdateNotifyCount_;
    }

    Point GetPoint();

    RefPtr<FrameNode> GetFrameNode();

    void SetUserConfig(const RefPtr<DragSpringLoadingConfiguration>& userConfig)
    {
        userConfig_ = userConfig;
    }

    const RefPtr<DragSpringLoadingConfiguration>& GetUserConfig() const
    {
        return userConfig_;
    }

private:
    class DragDropSpringLoadingStateMachinePool : public AceType {
        DECLARE_ACE_TYPE(DragDropSpringLoadingStateMachinePool, AceType);

    public:
        template<class T>
        bool RegisterStateHandler(DragDropSpringLoadingState state,
            const std::vector<DragDropSpringLoadingState>& transitions,
            WeakPtr<DragDropSpringLoadingStateMachine> machine)
        {
            if (states_.find(state) != states_.end()) {
                return false;
            }
            auto stateHandler = MakeRefPtr<T>(machine);
            states_[state] = { stateHandler, transitions };
            return true;
        }

        RefPtr<DragDropSpringLoadingStateBase> GetStateHandler(DragDropSpringLoadingState state) const
        {
            auto it = states_.find(state);
            return it != states_.end() ? it->second.stateHandler : nullptr;
        }

        bool IsAllowedTransition(DragDropSpringLoadingState from, DragDropSpringLoadingState to) const;

    private:
        struct StateInfo {
            RefPtr<DragDropSpringLoadingStateBase> stateHandler = nullptr;
            std::vector<DragDropSpringLoadingState> transitions;
        };
        std::unordered_map<DragDropSpringLoadingState, StateInfo> states_;
    };
    RefPtr<DragDropSpringLoadingStateMachinePool> stateMachinePool_ =
        MakeRefPtr<DragDropSpringLoadingStateMachinePool>();
    CancelableCallback<void()> timer_;
    std::optional<SingleTaskExecutor> taskExecutor_;
    DragDropSpringLoadingState currentState_ { DragDropSpringLoadingState::IDLE };
    bool isWaitingForIdleFinish_ { false };
    int32_t currentNotifySequence_ = -1;
    int32_t currentUpdateNotifyCount_ = 0;
    WeakPtr<DragDropSpringLoadingDetector> detector_;
    RefPtr<DragSpringLoadingConfiguration> userConfig_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_SPRING_LOADING_STATE_MACHINE_H