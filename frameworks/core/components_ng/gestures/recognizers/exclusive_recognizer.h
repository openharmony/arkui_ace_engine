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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"

namespace OHOS::Ace::NG {

// ExclusiveRecognizer identifies gesture exclusive.
class ACE_EXPORT ExclusiveRecognizer : public RecognizerGroup {
    DECLARE_ACE_TYPE(ExclusiveRecognizer, RecognizerGroup);

public:
    explicit ExclusiveRecognizer(const std::vector<RefPtr<NGGestureRecognizer>>& recognizers)
        : RecognizerGroup(recognizers)
    {}

    explicit ExclusiveRecognizer(std::list<RefPtr<NGGestureRecognizer>>&& recognizers)
        : RecognizerGroup(std::move(recognizers))
    {}

    ~ExclusiveRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;
    void OnPending() override;
    void OnBlocked() override;

    bool HandleEvent(const TouchEvent& point) override;
    bool HandleEvent(const AxisEvent& event) override;
    GestureMode GetGestureMode() const override
    {
        return GestureMode::Exclusive;
    }

    void CleanRecognizerState() override;
    void ForceCleanRecognizer() override;

private:
    bool CheckNeedBlocked(const RefPtr<NGGestureRecognizer>& recognizer);
    void HandleTouchDownEvent(const TouchEvent& event) override {};
    void HandleTouchUpEvent(const TouchEvent& event) override {};
    void HandleTouchMoveEvent(const TouchEvent& event) override {};
    void HandleTouchCancelEvent(const TouchEvent& event) override {};
    void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) override;
    void HandleAcceptDisposal(const RefPtr<NGGestureRecognizer>& recognizer);
    void HandlePendingDisposal(const RefPtr<NGGestureRecognizer>& recognizer);
    void HandleRejectDisposal(const RefPtr<NGGestureRecognizer>& recognizer);
    RefPtr<NGGestureRecognizer> UnBlockGesture();

    bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer) override;
    void OnResetStatus() override;

    void DispatchEventToActiveRecognizers(const TouchEvent& point);
    void DispatchEventToAllRecognizers(const TouchEvent& point);

    RefPtr<NGGestureRecognizer> activeRecognizer_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_EXCLUSIVE_RECOGNIZER_H
