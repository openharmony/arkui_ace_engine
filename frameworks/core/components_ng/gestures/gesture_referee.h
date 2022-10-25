/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_REFEREE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_REFEREE_H

#include <list>
#include <set>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/singleton.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

class GestureRecognizer;

enum class GestureDisposal {
    ACCEPT = 0,
    REJECT,
    PENDING,
    NONE,
};

class GestureScope : public AceType {
    DECLARE_ACE_TYPE(GestureScope, AceType);

public:
    explicit GestureScope(size_t touchId) : touchId_(touchId) {}
    ~GestureScope() override = default;

    void AddMember(const RefPtr<GestureRecognizer>& recognizer);
    void DelMember(const RefPtr<GestureRecognizer>& recognizer);

    void Close();

    bool IsPending();

    bool IsEmpty() const
    {
        return recognizers_.empty();
    }

    bool CheckNeedBlocked(const RefPtr<GestureRecognizer>& recognizer);

    void OnAcceptGesture(const RefPtr<GestureRecognizer>& recognizer);

    RefPtr<GestureRecognizer> UnBlockGesture();

    bool IsDelayClosed() const
    {
        return isDelay_;
    }

    void SetDelayClose()
    {
        isDelay_ = true;
    }

private:
    bool Existed(const RefPtr<GestureRecognizer>& recognizer);
    std::list<WeakPtr<GestureRecognizer>> recognizers_;

    size_t touchId_ = 0;
    bool isDelay_ = false;
};

class GestureReferee : public virtual AceType {
    DECLARE_ACE_TYPE(GestureReferee, AceType);

public:
    GestureReferee() = default;
    ~GestureReferee() override = default;

    void AddGestureToScope(size_t touchId, const TouchTestResult& result);

    // Try to clean gesture scope when receive cancel event.
    void CleanGestureScope(size_t touchId);

    // Called by the gesture recognizer when the gesture recognizer has completed the recognition of the gesture (accept
    // or reject)
    void Adjudicate(const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal);

private:
    void HandleAcceptDisposal(const RefPtr<GestureRecognizer>& recognizer);
    void HandlePendingDisposal(const RefPtr<GestureRecognizer>& recognizer);
    void HandleRejectDisposal(const RefPtr<GestureRecognizer>& recognizer);

    // Stores gesture recognizer collection according to Id.
    std::unordered_map<size_t, RefPtr<GestureScope>> gestureScopes_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_REFEREE_H
