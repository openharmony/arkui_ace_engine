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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_EXCLUSIVE_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_EXCLUSIVE_RECOGNIZER_H

#include <functional>
#include <set>
#include <type_traits>

#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"

namespace OHOS::Ace::NG {

// ExclusiveRecognizer identifies gesture exclusive.
class ACE_EXPORT ExclusiveRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(ExclusiveRecognizer, MultiFingersRecognizer);

public:
    explicit ExclusiveRecognizer(const std::vector<RefPtr<GestureRecognizer>>& recognizers)
    {
        for (const auto& recognizer : recognizers) {
            recognizer->SetGestureGroup(AceType::WeakClaim(this));
            recognizers_.emplace_back(recognizer);
        }
    }

    explicit ExclusiveRecognizer(std::list<RefPtr<GestureRecognizer>>&& recognizers)
    {
        recognizers_.swap(recognizers);
        for (auto& recognizer : recognizers_) {
            LOGE("ExclusiveRecognizer combine: %{public}s, %{public}p, %{public}zu", AceType::TypeName(recognizer),
                AceType::RawPtr(recognizer), recognizers_.size());
            recognizer->SetGestureGroup(AceType::WeakClaim(this));
        }
    }

    ~ExclusiveRecognizer() override = default;
    void OnAccepted(size_t touchId) override;
    void OnRejected(size_t touchId) override;
    void OnPending(size_t touchId) override;
    bool HandleEvent(const TouchEvent& point) override;
    void OnFlushTouchEventsBegin() override;
    void OnFlushTouchEventsEnd() override;
    void ReplaceChildren(std::list<RefPtr<GestureRecognizer>>& recognizers);

private:
    void HandleTouchDownEvent(const TouchEvent& event) override {};
    void HandleTouchUpEvent(const TouchEvent& event) override {};
    void HandleTouchMoveEvent(const TouchEvent& event) override {};
    void HandleTouchCancelEvent(const TouchEvent& event) override {};
    void BatchAdjudicate(const std::set<size_t>& touchIds, const RefPtr<GestureRecognizer>& recognizer,
        GestureDisposal disposal) override;
    void AddToReferee(size_t touchId, const RefPtr<GestureRecognizer>& recognizer) override;
    bool ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer) override;
    bool CheckNeedBlocked(const RefPtr<GestureRecognizer>& recognizer);
    void AcceptSubGesture(const RefPtr<GestureRecognizer>& recognizer);
    bool CheckAllFailed();
    void Reset();
    void ResetStatus();

    std::list<RefPtr<GestureRecognizer>> recognizers_;
    RefPtr<GestureRecognizer> activeRecognizer_;

    bool pendingReset_ = false;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_EXCLUSIVE_RECOGNIZER_H
