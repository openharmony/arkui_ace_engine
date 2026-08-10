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

#include "core/components_ng/manager/gesture/active_recognizer_manager.h"

#include "base/log/log.h"
#include "core/components_ng/gestures/gesture_referee.h"

namespace OHOS::Ace::NG {
void ActiveRecognizerManager::RegisterRecognizer(
    const RefPtr<NGGestureRecognizer>& recognizer, int32_t touchId)
{
    CHECK_NULL_VOID(recognizer);
    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    if (activeRecognizers_.find(weakKey) != activeRecognizers_.end()) {
        return;
    }
    RecognizerInfo info(weakKey, touchId);
    info.lastUpdateTime = std::chrono::high_resolution_clock::now();
    activeRecognizers_[weakKey] = info;
    activeTouchIds_.insert(touchId);
}

void ActiveRecognizerManager::UpdateRecognizerState(
    const RefPtr<NGGestureRecognizer>& recognizer, RefereeState newState)
{
    CHECK_NULL_VOID(recognizer);
    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = activeRecognizers_.find(weakKey);
    if (iter == activeRecognizers_.end()) {
        return;
    }
    iter->second.lastUpdateTime = std::chrono::high_resolution_clock::now();
}

void ActiveRecognizerManager::CheckAndCleanBeforeNewTouch(int32_t newTouchId)
{
    bool isNotNeedCleanForPending = false;
    for (auto& [weakKey, info] : activeRecognizers_) {
        auto recognizer = weakKey.Upgrade();
        if (CheckPendingTimeout(recognizer, info)) {
            isNotNeedCleanForPending = true;
        }
    }
    if (isNotNeedCleanForPending) {
        return;
    }
    for (auto& [weakKey, info] : activeRecognizers_) {
        auto recognizer = weakKey.Upgrade();
        if (!recognizer) {
            continue;
        }
        auto callbackState = recognizer->GetCurrentCallbackState();
        bool hasUnclosedStart = (callbackState == CurrentCallbackState::START ||
                                 callbackState == CurrentCallbackState::UPDATE);
        if (hasUnclosedStart) {
            SendCancelToRecognizer(recognizer);
        }
        recognizer->ForceCleanRecognizer();
    }
    activeRecognizers_.clear();
    activeTouchIds_.clear();
}

bool ActiveRecognizerManager::CheckPendingTimeout(
    const RefPtr<NGGestureRecognizer>& recognizer, const RecognizerInfo& info)
{
    CHECK_NULL_RETURN(recognizer, false);
    auto currentState = recognizer->GetRefereeState();
    if (currentState != RefereeState::PENDING &&
        currentState != RefereeState::PENDING_BLOCKED) {
        return false;
    }
    auto now = std::chrono::high_resolution_clock::now();
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - info.lastUpdateTime).count();
    return durationMs < DEFAULT_PENDING_TIMEOUT_MS;
}

void ActiveRecognizerManager::SendCancelToRecognizer(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);
    TouchEvent cancelEvent;
    cancelEvent.type = TouchType::CANCEL;
    recognizer->HandleEvent(cancelEvent);
}

void ActiveRecognizerManager::RemoveRecognizer(const RefPtr<NGGestureRecognizer>& recognizer)
{
    CHECK_NULL_VOID(recognizer);
    auto weakKey = WeakPtr<NGGestureRecognizer>(recognizer);
    auto iter = activeRecognizers_.find(weakKey);
    if (iter != activeRecognizers_.end()) {
        if (iter->second.touchId != -1) {
            activeTouchIds_.erase(iter->second.touchId);
        }
        activeRecognizers_.erase(iter);
    }
}

bool ActiveRecognizerManager::HasActiveRecognizers() const
{
    return !activeRecognizers_.empty();
}

size_t ActiveRecognizerManager::GetActiveRecognizerCount() const
{
    return activeRecognizers_.size();
}

void ActiveRecognizerManager::ClearAllRecognizers()
{
    for (auto& [weakKey, info] : activeRecognizers_) {
        auto recognizer = weakKey.Upgrade();
        if (recognizer && !recognizer->IsRefereeFinished()) {
            recognizer->ForceCleanRecognizer();
        }
    }
    activeRecognizers_.clear();
    activeTouchIds_.clear();
}

void ActiveRecognizerManager::DumpRecognizerStates() const
{
    TAG_LOGD(AceLogTag::ACE_GESTURE,
        "Dump active recognizers, count: %{public}zu, touchIds: %{public}zu",
        activeRecognizers_.size(), activeTouchIds_.size());
    for (const auto& [weakKey, info] : activeRecognizers_) {
        auto recognizer = weakKey.Upgrade();
        if (!recognizer) {
            continue;
        }
        TAG_LOGD(AceLogTag::ACE_GESTURE,
            "  Recognizer: type=%{public}s, state=%{public}s, touchId=%{public}d, callback=%{public}d",
            info.recognizerType.c_str(),
            TransRefereeState(recognizer->GetRefereeState()).c_str(),
            info.touchId,
            static_cast<int32_t>(recognizer->GetCurrentCallbackState()));
    }
}

void ActiveRecognizerManager::CleanFinishedRecognizersWithStaleFingers(
    const std::unordered_map<int32_t, int32_t>& downFingerIds,
    const RefPtr<NG::GestureReferee>& currentReferee)
{
    CHECK_NULL_VOID(currentReferee);
    std::unordered_set<int32_t> allFingerIds;
    for (auto& [weakKey, info] : activeRecognizers_) {
        auto recognizer = weakKey.Upgrade();
        if (!recognizer) {
            continue;
        }
        auto touchPoints = recognizer->GetTouchPoints();
        for (const auto& [fingerId, touchEvent] : touchPoints) {
            allFingerIds.insert(fingerId);
        }
    }
    for (auto fingerId : allFingerIds) {
        if (downFingerIds.find(fingerId) != downFingerIds.end()) {
            continue;
        }
        if (currentReferee->QueryAllDone(static_cast<size_t>(fingerId))) {
            TAG_LOGD(AceLogTag::ACE_GESTURE,
                "CleanFinishedRecognizers: CleanGestureScope finger %{public}d", fingerId);
            currentReferee->CleanGestureScope(static_cast<size_t>(fingerId));
        }
    }
}

void ActiveRecognizerManager::CleanFinishedRecognizersWithStaleFingersForPost(
    const std::unordered_map<int32_t, int32_t>& downFingerIds,
    const RefPtr<NG::GestureReferee>& currentReferee)
{
    CHECK_NULL_VOID(currentReferee);
    std::unordered_set<int32_t> allFingerIds;
    for (auto& [weakKey, info] : activeRecognizers_) {
        auto recognizer = weakKey.Upgrade();
        if (!recognizer) {
            continue;
        }
        auto recognizerReferee = recognizer->GetRefereeWithStrategy().Upgrade();
        if (recognizerReferee != currentReferee) {
            continue;
        }
        auto touchPoints = recognizer->GetTouchPoints();
        for (const auto& [fingerId, touchEvent] : touchPoints) {
            allFingerIds.insert(fingerId);
        }
    }
    for (auto fingerId : allFingerIds) {
        if (downFingerIds.find(fingerId) != downFingerIds.end()) {
            continue;
        }
        if (currentReferee->QueryAllDone(static_cast<size_t>(fingerId))) {
            TAG_LOGD(AceLogTag::ACE_GESTURE,
                "CleanFinishedRecognizersForPost: CleanGestureScope finger %{public}d", fingerId);
            currentReferee->CleanGestureScope(static_cast<size_t>(fingerId));
        }
    }
}
} // namespace OHOS::Ace::NG
