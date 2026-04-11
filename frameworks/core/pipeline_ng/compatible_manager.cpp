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

#include <cmath>
#include <cinttypes>
#include "core/pipeline_ng/compatible_manager.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
std::chrono::milliseconds CalculateDurationTime(const TimeStamp& begin, const TimeStamp& end)
{
    auto durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    durationTime = durationTime < std::chrono::milliseconds::zero() ? std::chrono::milliseconds::zero() : durationTime;

    return durationTime;
}

bool IsTimeout(const CompatibleManager& manager)
{
    const std::chrono::milliseconds timeoutMs { 300 };
    auto rawMoveEvent = manager.GetRawMoveEvent();
    auto rawDownEvent = manager.GetRawDownEvent();
    if (!rawDownEvent) {
        TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "IsTimeout in wrong state");
        return false;
    }

    TimeStamp lastTimeStamp = rawMoveEvent ? rawMoveEvent->GetTimeStamp() : rawDownEvent->GetTimeStamp();
    TimeStamp currentTimeStamp = std::chrono::high_resolution_clock::now();
    auto durationTime = CalculateDurationTime(lastTimeStamp, currentTimeStamp);
    return durationTime >= timeoutMs;
}

bool IsReachEnd(float remain, float threshold)
{
    return abs(remain) <= threshold;
}

CompatibleManager::CompatibleManager()
{
    state_ = std::make_unique<IdleState>(*this);
}

bool CompatibleManager::IdleState::NotifyNewEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "IdleState receive event: %{public}d", static_cast<int32_t>(event.type));
    switch (event.type) {
        case TouchType::DOWN:
            manager_.SetState(std::make_unique<CompatibleManager::ReadyState>(manager_));
            return NOT_INTERCEPT_EVENT;
        case TouchType::MOVE:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "IdleState receive unexpected move event");
            break;
        case TouchType::UP:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "IdleState receive unexpected up event");
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "IdleState receive unexpected event");
            break;
    }
    manager_.SetState(std::make_unique<CompatibleManager::IdleState>(manager_)); // unexpected event error handle
    return INTERCEPT_EVENT;
}

std::optional<TouchEvent> CompatibleManager::IdleState::EventGenerate()
{
    return std::nullopt;
}

void CompatibleManager::IdleState::start()
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "IdleState start");
    manager_.ClearAllState();
}

StateType CompatibleManager::IdleState::GetType() const
{
    return StateType::IDLE;
}

bool CompatibleManager::ReadyState::NotifyNewEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "ReadyState receive event: %{public}d", static_cast<int32_t>(event.type));
    switch (event.type) {
        case TouchType::DOWN:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "ReadyState receive unexpected down event");
            break;
        case TouchType::MOVE:
            manager_.SetState(std::make_unique<CompatibleManager::OngoingState>(manager_));
            return INTERCEPT_EVENT;
        case TouchType::UP:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "ReadyState receive unexpected up event");
            break;
        case TouchType::CANCEL:
            manager_.SetState(std::make_unique<CompatibleManager::IdleState>(manager_));
            return NOT_INTERCEPT_EVENT;
        default:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "ReadyState receive unexpected event");
            break;
    }
    manager_.SetState(std::make_unique<CompatibleManager::IdleState>(manager_)); // unexpected event error handle
    return INTERCEPT_EVENT;
}

std::optional<TouchEvent> CompatibleManager::ReadyState::EventGenerate()
{
    return std::nullopt;
}

void CompatibleManager::ReadyState::start()
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "ReadyState start");
    manager_.ClearRawUpEvent();
    manager_.ClearRawMoveEvent();
}

StateType CompatibleManager::ReadyState::GetType() const
{
    return StateType::READY;
}

bool CompatibleManager::OngoingState::NotifyNewEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "OngoingState receive event: %{public}d", static_cast<int32_t>(event.type));
    switch (event.type) {
        case TouchType::DOWN:
            manager_.SetState(std::make_unique<CompatibleManager::ReadyState>(manager_));
            return INTERCEPT_EVENT;
        case TouchType::MOVE:
            break;
        case TouchType::UP:
            break;
        case TouchType::CANCEL:
            manager_.SetState(std::make_unique<CompatibleManager::IdleState>(manager_));
            return NOT_INTERCEPT_EVENT;
        default:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "MoveState receive unexpected event");
            break;
    }
    return INTERCEPT_EVENT;
}

std::optional<TouchEvent> CompatibleManager::OngoingState::EventGenerate()
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "OngoingState generate event");
    manager_.GenerateMoveEvent();
    if (IsReachEnd(manager_.remainingDistance_, manager_.END_THRESHOLD)) {
        manager_.SetState(std::make_unique<CompatibleManager::EndState>(manager_));
    }
    return manager_.GetGeneratedMoveEvent();
}

void CompatibleManager::OngoingState::start()
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "OngoingState start");
}

StateType CompatibleManager::OngoingState::GetType() const
{
    return StateType::ONGOING;
}

bool CompatibleManager::EndState::NotifyNewEvent(const TouchEvent& event)
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "EndState receive event: %{public}d", static_cast<int32_t>(event.type));
    switch (event.type) {
        case TouchType::DOWN:
            manager_.SetState(std::make_unique<CompatibleManager::ReadyState>(manager_));
            break;
        case TouchType::MOVE:
            manager_.SetState(std::make_unique<CompatibleManager::OngoingState>(manager_));
            break;
        case TouchType::UP:
            break;
        case TouchType::CANCEL:
            manager_.SetState(std::make_unique<CompatibleManager::IdleState>(manager_));
            return NOT_INTERCEPT_EVENT;
        default:
            TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "EndState receive unexpected event");
            break;
    }
    return INTERCEPT_EVENT;
}

std::optional<TouchEvent> CompatibleManager::EndState::EventGenerate()
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "EndState generate event");
    if (manager_.GetRawUpEvent() || IsTimeout(manager_)) {
        std::optional<TouchEvent> upEvent = manager_.GenerateUpEvent();
        manager_.SetState(std::make_unique<CompatibleManager::IdleState>(manager_));
        return upEvent;
    }

    manager_.GenerateMoveEvent();
    return manager_.GetGeneratedMoveEvent();
}

void CompatibleManager::EndState::start()
{
    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "EndState start");
}

StateType CompatibleManager::EndState::GetType() const
{
    return StateType::END;
}

std::optional<TouchEvent> CompatibleManager::GenerateUpEvent()
{
    std::optional<TouchEvent> upEvent { std::nullopt };
    if (rawUpEvent_ && generatedMoveEvent_) {
        upEvent = rawUpEvent_;
        upEvent->y = generatedMoveEvent_->y;
        upEvent->SetTime(std::chrono::high_resolution_clock::now());
        return upEvent;
    }

    if (generatedMoveEvent_) {
        upEvent = generatedMoveEvent_;
        upEvent->type = TouchType::UP;
        upEvent->SetTime(std::chrono::high_resolution_clock::now());
        return upEvent;
    }

    if (rawDownEvent_) {
        upEvent = rawDownEvent_;
        upEvent->type = TouchType::UP;
        upEvent->SetTime(std::chrono::high_resolution_clock::now());
        return upEvent;
    }

    TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "GenerateUpEvent failed");
    return upEvent;
}

bool CompatibleManager::NotifyNewEvent(const TouchEvent& event)
{
    UpdateRawEvent(event);
    return state_->NotifyNewEvent(event);
}

std::optional<TouchEvent> CompatibleManager::EventGenerate()
{
    auto event = state_->EventGenerate();
    if (event) {
        event->isGenerate = true;
    }
    return event;
}

std::optional<TouchEvent> CompatibleManager::BreakGenerate()
{
    if (GetCurrentStateType() == StateType::IDLE) {
        return std::nullopt;
    }
    std::optional<TouchEvent> upEvent = GenerateUpEvent();
    if (upEvent) {
        upEvent->isGenerate = true;
    }
    SetState(std::make_unique<IdleState>(*this));
    return upEvent;
}

void CompatibleManager::UpdateRawEvent(const TouchEvent& event)
{
    TouchEvent newEvent = event;
    newEvent.SetTime(std::chrono::high_resolution_clock::now());
    switch (event.type) {
        case TouchType::DOWN:
            rawDownEvent_ = newEvent;
            break;
        case TouchType::MOVE:
            UpdateDistance(event.y);  // update distance before update rawMoveEvent_
            rawMoveEvent_ = newEvent;
            break;
        case TouchType::UP:
            rawUpEvent_ = newEvent;
            break;
        default:
            break;
    }
}

void CompatibleManager::SetState(std::unique_ptr<TouchState> newState)
{
    newState->start();
    state_ = std::move(newState);
}

void CompatibleManager::UpdateDistance(float target)
{
    if (!rawDownEvent_) {
        TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW, "UpdateDistance failed, rawDownEvent is null");
        return;
    }
    if (rawMoveEvent_) {
        remainingDistance_ += (target - rawMoveEvent_->y);
    } else {
        remainingDistance_ += (target - rawDownEvent_->y);
    }

    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "UpdateDistance, target: %{public}f, remainingDistance: %{public}f", target,
        remainingDistance_);
}

std::optional<TouchEvent> CompatibleManager::GetRawDownEvent() const
{
    return rawDownEvent_;
}

std::optional<TouchEvent> CompatibleManager::GetRawMoveEvent() const
{
    return rawMoveEvent_;
}

std::optional<TouchEvent> CompatibleManager::GetRawUpEvent() const
{
    return rawUpEvent_;
}

std::optional<TouchEvent> CompatibleManager::GetGeneratedMoveEvent() const
{
    return generatedMoveEvent_;
}

void CompatibleManager::InitGeneratedMoveEvent()
{
    if (generatedMoveEvent_) {
        return;
    }

    if (!rawMoveEvent_ || !rawDownEvent_) {
        TAG_LOGE(AceLogTag::ACE_INPUTKEYFLOW,
            "InitGeneratedMoveEvent failed, is in wrong state, rawMoveEvent or rawDownEvent is null");
        return;
    }

    generatedMoveEvent_ = rawMoveEvent_;
    generatedMoveEvent_->y = rawDownEvent_->y;
}

float GetNextStep(float remainingDistance, float endThreshold, const std::chrono::milliseconds& durationTime)
{
    const float dampingFactor{ -0.040f };
    auto durationTimeMs = durationTime.count();
    float alpha = 1.0f - std::exp(dampingFactor * durationTimeMs);
    float step = (abs(remainingDistance) <= endThreshold) ? remainingDistance : (alpha * remainingDistance);

    TAG_LOGD(AceLogTag::ACE_INPUTKEYFLOW, "GetNextStep, remainingDistance: %{public}f, step: %{public}f, "
        "durationTime: %{public}" PRIu64, remainingDistance, step, static_cast<uint64_t>(durationTimeMs));

    return step;
}

void CompatibleManager::GenerateMoveEvent()
{
    const std::chrono::milliseconds maxDurationMs{ 33 };
    InitGeneratedMoveEvent();
    TimeStamp CurrentTimeStamp = std::chrono::high_resolution_clock::now();
    auto durationTime = CalculateDurationTime(generatedMoveEvent_->GetTimeStamp(), CurrentTimeStamp);
    durationTime = std::min(durationTime, maxDurationMs);
    float step = GetNextStep(remainingDistance_, END_THRESHOLD, durationTime);
    generatedMoveEvent_->y += step;
    generatedMoveEvent_->SetTime(CurrentTimeStamp);
    remainingDistance_ -= step;
}

void CompatibleManager::ClearAllState()
{
    rawDownEvent_ = std::nullopt;
    rawMoveEvent_ = std::nullopt;
    rawUpEvent_ = std::nullopt;
    generatedMoveEvent_ = std::nullopt;
    remainingDistance_ = 0.0f;
}

void CompatibleManager::ClearRawUpEvent()
{
    rawUpEvent_ = std::nullopt;
}

void CompatibleManager::ClearRawMoveEvent()
{
    rawMoveEvent_ = std::nullopt;
}

StateType CompatibleManager::GetCurrentStateType() const
{
    return state_->GetType();
}
} // namespace OHOS::Ace::NG
