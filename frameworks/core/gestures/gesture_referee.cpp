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

namespace OHOS::Ace {

void GestureScope::AddMember(const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("recognizer is null, AddMember failed.");
        return;
    }
    recognizers_.emplace_back(recognizer);
}

void GestureScope::ForceSelectRecipient()
{
    // Forcibly select the first one as the recipient when no gesture recognizer requests adjudication during the
    // entire gesture sequence. In this case, recognizers must not be empty.
    if (recognizers_.empty()) {
        LOGE("the recognizer collection is empty");
        return;
    }
    recognizers_.front()->OnAccepted(touchId_);
    recognizers_.pop_front();
    for (const auto& rejectedItem : recognizers_) {
        rejectedItem->OnRejected(touchId_);
    }
    recognizers_.clear();
}

void GestureScope::HandleGestureDisposal(const RefPtr<GestureRecognizer>& recognizer, const GestureDisposal disposal)
{
    if (!recognizer) {
        LOGE("recognizer is null, AddGestureRecognizer failed.");
        return;
    }
    if (recognizers_.empty()) {
        LOGE("the recognizer collection is empty");
        return;
    }
    auto result = std::find(recognizers_.cbegin(), recognizers_.cend(), recognizer);
    if (result == recognizers_.cend()) {
        LOGE("can not find the recognizer");
        return;
    }
    // First erases the find object.
    recognizers_.erase(result);
    // Handles recognizer callback.
    if (disposal == GestureDisposal::REJECT) {
        recognizer->OnRejected(touchId_);
    } else {
        recognizer->OnAccepted(touchId_);
        for (const auto& rejectedItem : recognizers_) {
            rejectedItem->OnRejected(touchId_);
        }
        recognizers_.clear();
    }
}

void GestureScope::ForceClose()
{
    if (recognizers_.empty()) {
        return;
    }
    for (const auto& rejectedItem : recognizers_) {
        rejectedItem->OnRejected(touchId_);
    }
    recognizers_.clear();
}

void GestureReferee::AddGestureRecognizer(size_t touchId, const RefPtr<GestureRecognizer>& recognizer)
{
    if (!recognizer) {
        LOGE("recognizer is null, AddGestureRecognizer failed.");
        return;
    }
    LOGD("add gesture recognizer into scope, %{private}p", AceType::RawPtr(recognizer));
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        iter->second.AddMember(recognizer);
    } else {
        GestureScope gestureScope(touchId);
        gestureScope.AddMember(recognizer);
        gestureScopes_.try_emplace(touchId, std::move(gestureScope));
    }
}

void GestureReferee::AdjudicateGestureSequence(size_t touchId)
{
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
        if (!iter->second.IsEmpty()) {
            iter->second.ForceSelectRecipient();
        }
        gestureScopes_.erase(iter);
    }
}

void GestureReferee::CleanGestureScope(size_t touchId)
{
    const auto iter = gestureScopes_.find(touchId);
    if (iter != gestureScopes_.end()) {
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
    } else {
        LOGE("fail to find the gesture scope for %{public}zu session id", touchId);
    }
}

} // namespace OHOS::Ace