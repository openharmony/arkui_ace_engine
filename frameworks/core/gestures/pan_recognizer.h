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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_PAN_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_PAN_RECOGNIZER_H

#include <cmath>
#include <functional>
#include <map>

#include "core/gestures/multi_fingers_recognizer.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

class PanRecognizer : public MultiFingersRecognizer {
    DECLARE_ACE_TYPE(PanRecognizer, MultiFingersRecognizer);

public:
    PanRecognizer(const WeakPtr<PipelineContext>& context, int32_t fingers, Direction direction, double distance)
        : direction_(direction), distance_(distance), context_(context)
    {
        fingers_ = fingers;
    }
    ~PanRecognizer() override = default;

    void OnAccepted() override;
    void OnRejected() override;

private:
    void HandleTouchDownEvent(const TouchPoint& event) override;
    void HandleTouchUpEvent(const TouchPoint& event) override;
    void HandleTouchMoveEvent(const TouchPoint& event) override;
    void HandleTouchCancelEvent(const TouchPoint& event) override;
    bool ReconcileFrom(const RefPtr<GestureRecognizer>& recognizer) override;
    bool IsPanGestureAccept(double offset) const;
    void Reset();
    void SendCallbackMsg(const std::unique_ptr<GestureEventFunc>& callback);
    double GetOffsetInMainDirection();
    double ConvertPxToVp(double offset) const;

    const TouchRestrict& GetTouchRestrict() const
    {
        return touchRestrict_;
    }

    Direction direction_;
    double distance_ = 0.0;
    WeakPtr<PipelineContext> context_;
    std::map<int32_t, TouchPoint> touchPoints_;
    Offset averageDistance_;
    TimeStamp time_;
    bool pendingEnd_ = false;
    bool pendingCancel_ = false;
    Point globalPoint_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_GESTURES_PAN_RECOGNIZER_H
