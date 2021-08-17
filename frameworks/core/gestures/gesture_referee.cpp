/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/gestures/gesture_referee.h"

#include "core/gestures/gesture_recognizer.h"

namespace OHOS::Ace {

void GestureScope::AddMember(const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("gesture recognizer is null, AddMember failed.");
        return;
    }

    if (Existed(recognizer)) {
        LOGE("gesture recognizer has already been added.");
        return;
    }

    recognizer->SetRefereeState(RefereeState::DETECTING);

    switch (recognizer->GetPriority()) {
        case GesturePriority::Parallel:
            parallelRecognizers_.emplace_back(recognizer);
            break;
        case GesturePriority::High:
            highRecognizers_.emplace_back(recognizer);
            break;
        case GesturePriority::Low:
            lowRecognizers_.emplace_back(recognizer);
            break;
        default:
            LOGW("Add unknown type member %{public}d to referee", recognizer->GetPriority());
            break;
    }
}

void GestureScope::DelMember(const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGI("gesture recognizer is null, DelMember finish.");
        return;
    }

    if (!Existed(recognizer)) {
        LOGI("gesture recognizer is not existed when deleted.");
        return;
    }

    LOGD("gesture referee ready to delete member of %{public}s", AceType::TypeName(recognizer));
    RefereeState prevState = recognizer->GetRefereeState();
    recognizer->SetRefereeState(RefereeState::DETECTING);

    if (recognizer->GetPriority() == GesturePriority::Parallel) {
        parallelRecognizers_.remove(recognizer);
        return;
    }

    RemoveAndUnBlockGesture(prevState == RefereeState::PENDING, recognizer);
}

void GestureScope::HandleGestureDisposal(const RefPtr<GestureRecognizer>& recognizer, const GestureDisposal disposal)
{
    if (!Existed(recognizer)) {
        LOGE("can not find the parallel recognizer");
        return;
    }

    GesturePriority priority = recognizer->GetPriority();
    if (priority == GesturePriority::Parallel) {
        HandleParallelDisposal(recognizer, disposal);
        return;
    }

    switch (disposal) {
        case GestureDisposal::ACCEPT:
            HandleAcceptDisposal(recognizer);
            break;
        case GestureDisposal::PENDING:
            HandlePendingDisposal(recognizer);
            break;
        case GestureDisposal::REJECT:
            HandleRejectDisposal(recognizer);
            break;
        default:
            LOGW("handle known gesture disposal %{public}d", disposal);
            break;
    }

    return;
}

void GestureScope::HandleParallelDisposal(const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    if (disposal == GestureDisposal::REJECT) {
        parallelRecognizers_.remove(recognizer);
        recognizer->SetRefereeState(RefereeState::FAIL);
        recognizer->OnRejected(touchId_);
    } else if (disposal == GestureDisposal::ACCEPT) {
        parallelRecognizers_.remove(recognizer);
        recognizer->SetRefereeState(RefereeState::SUCCEED);
        recognizer->OnAccepted(touchId_);
    }
}

void GestureScope::HandleAcceptDisposal(const RefPtr<GestureRecognizer>& recognizer)
{
    if (CheckNeedBlocked(recognizer)) {
        LOGI("gesture referee ready to notify block for %{public}s", AceType::TypeName(recognizer));
        recognizer->SetRefereeState(RefereeState::BLOCKED);
        return;
    }

    LOGI("gesture referee accept %{public}s of id %{public}zu", AceType::TypeName(recognizer), touchId_);
    AcceptGesture(recognizer);
}

void GestureScope::HandlePendingDisposal(const RefPtr<GestureRecognizer>& recognizer)
{
    if (CheckNeedBlocked(recognizer)) {
        LOGI("gesture referee ready to notify block for %{public}s", AceType::TypeName(recognizer));
        recognizer->SetRefereeState(RefereeState::BLOCKED);
        return;
    }

    LOGI("gesture referee ready to notify pending for %{public}s", AceType::TypeName(recognizer));
    recognizer->SetRefereeState(RefereeState::PENDING);
    recognizer->OnPending(touchId_);
}

void GestureScope::HandleRejectDisposal(const RefPtr<GestureRecognizer>& recognizer)
{
    LOGI("gesture referee ready to notify reject for %{public}s", AceType::TypeName(recognizer));
    RefereeState prevState = recognizer->GetRefereeState();
    recognizer->SetRefereeState(RefereeState::FAIL);
    recognizer->OnRejected(touchId_);
    RemoveAndUnBlockGesture(prevState == RefereeState::PENDING, recognizer);
}

void GestureScope::RemoveAndUnBlockGesture(bool isPrevPending, const RefPtr<GestureRecognizer>& recognizer)
{
    if (recognizer->GetPriority() == GesturePriority::High) {
        highRecognizers_.remove(recognizer);
        if (highRecognizers_.empty()) {
            UnBlockGesture(lowRecognizers_);
            return;
        }

        if (isPrevPending) {
            UnBlockGesture(highRecognizers_);
        }
    } else {
        lowRecognizers_.remove(recognizer);
        if (isPrevPending) {
            UnBlockGesture(lowRecognizers_);
        }
    }
}

bool GestureScope::Existed(const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("recognizer is null, AddGestureRecognizer failed.");
        return false;
    }

    std::list<RefPtr<GestureRecognizer>> members = GetMembersByRecognizer(recognizer);
    if (members.empty()) {
        return false;
    }

    auto result = std::find(members.cbegin(), members.cend(), recognizer);
    if (result == members.cend()) {
        return false;
    }

    return true;
}

const std::list<RefPtr<GestureRecognizer>>& GestureScope::GetMembersByRecognizer(
    const RefPtr<GestureRecognizer>& recognizer)
{
    switch (recognizer->GetPriority()) {
        case GesturePriority::Low:
            return lowRecognizers_;
        case GesturePriority::High:
            return highRecognizers_;
        case GesturePriority::Parallel:
            return parallelRecognizers_;
        default:
            return lowRecognizers_;
    }
}

bool GestureScope::CheckNeedBlocked(const RefPtr<GestureRecognizer>& recognizer)
{
    if (recognizer->GetPriority() == GesturePriority::Low && !highRecognizers_.empty()) {
        LOGD("self is low priority, high recognizers are not processed");
        return true;
    }

    std::list<RefPtr<GestureRecognizer>> members = GetMembersByRecognizer(recognizer);
    auto pendingMember =
        std::find_if(std::begin(members), std::end(members), [recognizer](const RefPtr<GestureRecognizer>& member) {
            return (member != recognizer) && (member->GetRefereeState() == RefereeState::PENDING);
        });

    if (pendingMember != members.end()) {
        LOGD("detected pending gesture in members");
        return true;
    }

    return false;
}

void GestureScope::AcceptGesture(const RefPtr<GestureRecognizer>& recognizer)
{
    if (recognizer->GetPriority() == GesturePriority::Low) {
        lowRecognizers_.remove(recognizer);
        for (const auto& rejectedItem : lowRecognizers_) {
            rejectedItem->OnRejected(touchId_);
            rejectedItem->SetRefereeState(RefereeState::FAIL);
        }
        lowRecognizers_.clear();
    } else {
        highRecognizers_.remove(recognizer);
        for (const auto& rejectedItem : highRecognizers_) {
            rejectedItem->OnRejected(touchId_);
            rejectedItem->SetRefereeState(RefereeState::FAIL);
        }
        highRecognizers_.clear();

        for (const auto& rejectedItem : lowRecognizers_) {
            rejectedItem->OnRejected(touchId_);
            rejectedItem->SetRefereeState(RefereeState::FAIL);
        }
        lowRecognizers_.clear();
    }

    recognizer->SetRefereeState(RefereeState::SUCCEED);
    recognizer->OnAccepted(touchId_);
}

void GestureScope::UnBlockGesture(std::list<RefPtr<GestureRecognizer>>& members)
{
    auto blockedMember = std::find_if(std::begin(members), std::end(members),
        [](const RefPtr<GestureRecognizer>& member) { return member->GetRefereeState() == RefereeState::BLOCKED; });
    if (blockedMember == members.end()) {
        LOGD("no blocked gesture in recognizers");
        return;
    }

    if ((*blockedMember)->GetDetectState() == DetectState::DETECTED) {
        LOGD("unblock and accept this gesture");
        AcceptGesture(*blockedMember);
        return;
    }

    LOGD("set the gesture %{public}s to be pending", AceType::TypeName((*blockedMember)));
    (*blockedMember)->SetRefereeState(RefereeState::PENDING);
    (*blockedMember)->OnPending(touchId_);
}

void GestureScope::ForceClose()
{
    LOGD("force close gesture scope of id %{public}zu", touchId_);
    for (const auto& rejectedItem : lowRecognizers_) {
        rejectedItem->OnRejected(touchId_);
    }
    lowRecognizers_.clear();

    for (const auto& rejectedItem : highRecognizers_) {
        rejectedItem->OnRejected(touchId_);
    }
    highRecognizers_.clear();

    for (const auto& rejectedItem : parallelRecognizers_) {
        rejectedItem->OnRejected(touchId_);
    }
    parallelRecognizers_.clear();
}

bool GestureScope::IsPending() const
{
    auto pendingMember = std::find_if(std::begin(lowRecognizers_), std::end(lowRecognizers_),
        [](const RefPtr<GestureRecognizer>& member) { return member->GetRefereeState() == RefereeState::PENDING; });
    if (pendingMember != lowRecognizers_.end()) {
        return true;
    }

    pendingMember = std::find_if(std::begin(highRecognizers_), std::end(highRecognizers_),
        [](const RefPtr<GestureRecognizer>& member) { return member->GetRefereeState() == RefereeState::PENDING; });
    if (pendingMember != highRecognizers_.end()) {
        return true;
    }

    pendingMember = std::find_if(std::begin(parallelRecognizers_), std::end(parallelRecognizers_),
        [](const RefPtr<GestureRecognizer>& member) { return member->GetRefereeState() == RefereeState::PENDING; });
    if (pendingMember != parallelRecognizers_.end()) {
        return true;
    }

    return false;
}

void GestureReferee::AddGestureRecognizer(size_t touchId, const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("recognizer is null, AddGestureRecognizer failed.");
        return;
    }
    LOGD("add gesture recognizer %{public}s into scope %{public}zu,", AceType::TypeName(recognizer), touchId);
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        iter->second.AddMember(recognizer);
    } else {
        GestureScope gestureScope(touchId);
        gestureScope.AddMember(recognizer);
        gestureScopes_.try_emplace(touchId, std::move(gestureScope));
    }
}

void GestureReferee::DelGestureRecognizer(size_t touchId, const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("recognizer is null, DelGestureRecognizer failed.");
        return;
    }
    LOGD("delete gesture recognizer %{public}s from scope %{public}zu ", AceType::TypeName(recognizer), touchId);
    const auto iter = gestureScopes_.find(touchId);
    if (iter == gestureScopes_.end()) {
        return;
    }

    iter->second.DelMember(recognizer);
}

void GestureReferee::CleanGestureScope(size_t touchId)
{
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        if (iter->second.IsPending()) {
            LOGE("gesture scope of touch id %{public}zu is pending, do not clean this.", touchId);
            return;
        }

        if (!iter->second.IsEmpty()) {
            iter->second.ForceClose();
        }
        gestureScopes_.erase(iter);
    }
}

void GestureReferee::Adjudicate(size_t touchId, const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    if (!recognizer) {
        LOGE("recognizer is null, Adjudicate failed.");
        return;
    }
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        iter->second.HandleGestureDisposal(recognizer, disposal);
        if (iter->second.IsEmpty()) {
            LOGD("clean the gesture referee of %{public}zu", touchId);
            gestureScopes_.erase(iter);
        }
    } else {
        LOGE("fail to find the gesture scope for %{public}zu session id", touchId);
    }
}

} // namespace OHOS::Ace