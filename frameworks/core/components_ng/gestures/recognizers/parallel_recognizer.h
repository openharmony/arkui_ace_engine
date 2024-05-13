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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PARALLEL_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PARALLEL_RECOGNIZER_H

#include <functional>

#include "base/memory/referenced.h"
#include "core/components_ng/gestures/gesture_info.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"

namespace OHOS::Ace::NG {

// ParallelRecognizer identifies events in parallel recognizers.
// For long press and double click, see: LongPressRecognizer and DoubleClickRecognizer.
class ACE_EXPORT ParallelRecognizer : public RecognizerGroup {
    DECLARE_ACE_TYPE(ParallelRecognizer, RecognizerGroup);

public:
    explicit ParallelRecognizer(const std::vector<RefPtr<NGGestureRecognizer>>& recognizers)
        : RecognizerGroup(recognizers)
    {}

    explicit ParallelRecognizer(std::list<RefPtr<NGGestureRecognizer>>&& recognizers)
        : RecognizerGroup(std::move(recognizers))
    {}

    ~ParallelRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;
    void OnPending() override;
    void OnBlocked() override;

    bool HandleEvent(const TouchEvent& point) override;
    bool HandleEvent(const AxisEvent& event) override;
    GestureMode GetGestureMode() const override
    {
        return GestureMode::Parallel;
    }

    void CleanRecognizerState() override;
    void ForceCleanRecognizer() override;

private:
    void HandleTouchDownEvent(const TouchEvent& event) override {};
    void HandleTouchUpEvent(const TouchEvent& event) override {};
    void HandleTouchMoveEvent(const TouchEvent& event) override {};
    void HandleTouchCancelEvent(const TouchEvent& event) override {};

    void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) override;

    bool ReconcileFrom(const RefPtr<NGGestureRecognizer>& recognizer) override;

    void OnResetStatus() override
    {
        RecognizerGroup::OnResetStatus();
        currentBatchRecognizer_.Reset();
    }

    RefPtr<NGGestureRecognizer> currentBatchRecognizer_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_GESTURES_RECOGNIZERS_PARALLEL_RECOGNIZER_H
