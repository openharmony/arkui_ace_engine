/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_COMPATIBLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_COMPATIBLE_MANAGER_H

#include <optional>

#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
enum class StateType {
    IDLE, READY, ONGOING, END
};

class CompatibleManager {
public:
    CompatibleManager();
    bool NotifyNewEvent(const TouchEvent& event);
    std::optional<TouchEvent> EventGenerate();
    std::optional<TouchEvent> BreakGenerate();
    std::optional<TouchEvent> GetRawDownEvent() const;
    std::optional<TouchEvent> GetRawUpEvent() const;
    std::optional<TouchEvent> GetRawMoveEvent() const;
    std::optional<TouchEvent> GetGeneratedMoveEvent() const;
    StateType GetCurrentStateType() const;

    static constexpr bool INTERCEPT_EVENT = true;
    static constexpr bool NOT_INTERCEPT_EVENT = false;

private:
    class TouchState;

    void UpdateRawEvent(const TouchEvent& event);
    void UpdateDistance(float target);
    void SetState(std::unique_ptr<TouchState> newState);
    std::optional<TouchEvent> GenerateUpEvent();
    void GenerateMoveEvent();
    void ClearAllState();
    void ClearRawUpEvent();
    void ClearRawMoveEvent();
    void InitGeneratedMoveEvent();

    static constexpr float END_THRESHOLD { 0.1f };
    float remainingDistance_ { 0.0f };
    std::optional<TouchEvent> rawDownEvent_ { std::nullopt };
    std::optional<TouchEvent> rawMoveEvent_ { std::nullopt };
    std::optional<TouchEvent> rawUpEvent_ { std::nullopt };
    std::optional<TouchEvent> generatedMoveEvent_ { std::nullopt };
    std::unique_ptr<TouchState> state_;

    class TouchState {
    public:
        explicit TouchState(CompatibleManager& manager) : manager_(manager) {}
        virtual ~TouchState() = default;
        virtual bool NotifyNewEvent(const TouchEvent& event) = 0;
        virtual std::optional<TouchEvent> EventGenerate() = 0;
        virtual void start() = 0;
        virtual StateType GetType() const = 0;

    protected:
        CompatibleManager& manager_;
    };

    class IdleState : public TouchState {
    public:
        using TouchState::TouchState;
        bool NotifyNewEvent(const TouchEvent& event) override;
        std::optional<TouchEvent> EventGenerate() override;
        void start() override;
        StateType GetType() const override;
    };

    class ReadyState : public TouchState {
    public:
        using TouchState::TouchState;
        bool NotifyNewEvent(const TouchEvent& event) override;
        std::optional<TouchEvent> EventGenerate() override;
        void start() override;
        StateType GetType() const override;
    };

    class OngoingState : public TouchState {
    public:
        using TouchState::TouchState;
        bool NotifyNewEvent(const TouchEvent& event) override;
        std::optional<TouchEvent> EventGenerate() override;
        void start() override;
        StateType GetType() const override;
    };

    class EndState : public TouchState {
    public:
        using TouchState::TouchState;
        bool NotifyNewEvent(const TouchEvent& event) override;
        std::optional<TouchEvent> EventGenerate() override;
        void start() override;
        StateType GetType() const override;
    };
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_COMPATIBLE_MANAGER_H