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

class NGGestureRecognizer;

enum class GestureDisposal {
    ACCEPT = 0,
    REJECT,
    PENDING,
    NONE,
};

inline std::string TransGestureDisposal(GestureDisposal disposal)
{
    const char *str[] = { "ACCEPT", "REJECT", "PENDING", "NONE" };
    if (disposal >= GestureDisposal::ACCEPT && disposal <= GestureDisposal::NONE) {
        return str[static_cast<int32_t>(disposal)];
    }
    return std::string("Disposal:").append(std::to_string(static_cast<int32_t>(disposal)));
}

class GestureScope : public AceType {
    DECLARE_ACE_TYPE(GestureScope, AceType);

public:
    explicit GestureScope(size_t touchId) : touchId_(touchId) {}
    ~GestureScope() override = default;

    void AddMember(const RefPtr<NGGestureRecognizer>& recognizer);
    void DelMember(const RefPtr<NGGestureRecognizer>& recognizer);

    void Close(bool isBlocked = false);

    bool IsPending(size_t touchId);

    bool IsEmpty() const
    {
        return recognizers_.empty();
    }

    bool CheckNeedBlocked(const RefPtr<NGGestureRecognizer>& recognizer);

    void OnAcceptGesture(const RefPtr<NGGestureRecognizer>& recognizer);

    RefPtr<NGGestureRecognizer> UnBlockGesture();

    bool IsDelayClosed() const
    {
        return isDelay_;
    }

    void SetDelayClose()
    {
        isDelay_ = true;
    }

    bool HasGestureAccepted() const
    {
        return hasGestureAccepted_;
    }

    void SetQueryStateFunc(const std::function<void(size_t)>& queryStateFunc)
    {
        queryStateFunc_ = queryStateFunc;
    }
    bool QueryAllDone(size_t touchId);
    bool CheckRecognizerState();

    bool IsReady();
    bool HasFailRecognizer();
    bool IsAnySucceedRecognizerExist();
    void ForceCleanGestureScope();
    void ForceCleanGestureScopeState();
    void CleanGestureScopeState();
    void CleanGestureScopeStateVoluntarily();
    bool Existed(const RefPtr<NGGestureRecognizer>& recognizer);
private:
    std::list<WeakPtr<NGGestureRecognizer>> recognizers_;

    size_t touchId_ = 0;
    bool isDelay_ = false;
    bool hasGestureAccepted_ = false;

    std::function<void(size_t)> queryStateFunc_;
};

class GestureReferee : public virtual AceType {
    DECLARE_ACE_TYPE(GestureReferee, AceType);

public:
    GestureReferee() = default;
    ~GestureReferee() override = default;

    void AddGestureToScope(size_t touchId, const TouchTestResult& result);

    // Try to clean gesture scope when receive cancel event.
    void CleanGestureScope(size_t touchId);

    void CleanGestureStateVoluntarily(size_t touchId);

    // Called by the gesture recognizer when the gesture recognizer has completed the recognition of the gesture (accept
    // or reject)
    void Adjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal);

    bool HasGestureAccepted(size_t touchId) const;

    void SetQueryStateFunc(std::function<void(size_t)>&& queryStateFunc)
    {
        queryStateFunc_ = queryStateFunc;
    }
    bool QueryAllDone(size_t touchId);
    bool QueryAllDone();
    bool CheckEventTypeChange(SourceType type, bool isAxis = false) const;
    bool CheckSourceTypeChange(SourceType type, bool isAxis = false);
    void CleanAll(bool isBlocked = false);
    void CleanRedundanceScope();

    bool IsReady();
    bool HasFailRecognizer(int32_t touchId);
    bool IsAnySucceedRecognizerExist(int32_t touchId);
    void ForceCleanGestureReferee();
    void ForceCleanGestureRefereeState();
    void CleanGestureRefereeState(int32_t touchId);
    bool IsScopesEmpty() const;
    void SetRecognizerDelayStatus(const RecognizerDelayStatus& recognizerDelayStatus);
private:
    void RecallOnAcceptGesture();
    bool CheckRecognizerInInnerContainer(const RefPtr<NGGestureRecognizer>& recognizer);
    void HandleAcceptDisposal(const RefPtr<NGGestureRecognizer>& recognizer);
    void HandlePendingDisposal(const RefPtr<NGGestureRecognizer>& recognizer);
    void HandleRejectDisposal(const RefPtr<NGGestureRecognizer>& recognizer);

    // Stores gesture recognizer collection according to Id.
    std::unordered_map<size_t, RefPtr<GestureScope>> gestureScopes_;

    std::function<void(size_t)> queryStateFunc_;
    SourceType lastSourceType_ = SourceType::NONE;
    RecognizerDelayStatus recognizerDelayStatus_ = RecognizerDelayStatus::NONE;
    WeakPtr<NGGestureRecognizer> delayRecognizer_;
    bool lastIsAxis_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_GESTURE_REFEREE_H
