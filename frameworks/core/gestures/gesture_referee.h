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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_REFEREE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_REFEREE_H

#include <list>
#include <unordered_map>

#include "base/utils/singleton.h"
#include "core/gestures/gesture_recognizer.h"

namespace OHOS::Ace {

enum class GestureDisposal {
    ACCEPT = 0,
    REJECT,
};

class GestureScope {
public:
    explicit GestureScope(size_t touchId) : touchId_(touchId) {}
    ~GestureScope() = default;
    GestureScope(GestureScope&&) = default;
    GestureScope& operator=(GestureScope&&) = default;

    void AddMember(const RefPtr<GestureRecognizer>& recognizer);

    void ForceSelectRecipient();

    void ForceClose();

    void HandleGestureDisposal(const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal);

    bool IsEmpty() const
    {
        return recognizers_.empty();
    }

private:
    size_t touchId_ = 0;
    std::list<RefPtr<GestureRecognizer>> recognizers_;
};

class GestureReferee : public Singleton<GestureReferee> {
public:
    // Each gesture recognizer should add itself to the gesture scope at the beginning of the gesture sequence
    // (touch down event) for gesture adjudicating.
    void AddGestureRecognizer(size_t touchId, const RefPtr<GestureRecognizer>& recognizer);

    // Adjudicates which gesture recognizer owns the gesture sequence when the gesture sequence ends (touch up event).
    void AdjudicateGestureSequence(size_t touchId);

    // Try to clean gesture scope when receive cancel event.
    void CleanGestureScope(size_t touchId);

    // Called by the gesture recognizer when the gesture recognizer has completed the recognition of the gesture (accept
    // or reject)
    void Adjudicate(size_t touchId, const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal);

private:
    // Stores gesture recognizer collection according to Id.
    std::unordered_map<size_t, GestureScope> gestureScopes_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_GESTURE_REFEREE_H
