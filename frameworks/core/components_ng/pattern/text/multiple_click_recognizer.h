/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_MULTIPLE_CLICK_RECOGNIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_MULTIPLE_CLICK_RECOGNIZER_H

#include "base/geometry/dimension.h"
#include "base/thread/cancelable_callback.h"
#include "base/memory/ace_type.h"
#include "base/utils/type_definition.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {
class MultipleClickRecognizer : public AceType {
    DECLARE_ACE_TYPE(MultipleClickRecognizer, AceType);

public:
    MultipleClickRecognizer() = default;
    ~MultipleClickRecognizer() = default;
    void Start(const GestureEvent& event);
    void StartCounting(const GestureEvent& event);
    bool IsSingleClick() const;
    bool IsDoubleClick() const;
    bool IsTripleClick() const;
    bool IsValidClick(const GestureEvent& event) const;
    void Stop()
    {
        clickCountTask_.Cancel();
        lastClickPosition_.Reset();
        lastClickTimeStamp_ = TimeStamp();
    }

    bool IsRunning() const
    {
        return clickCountTask_;
    }

    int32_t GetClickTimes() const
    {
        return clickTimes_;
    }

    void SetInterval(float intervalTime)
    {
        maxIntervalTime_ = intervalTime;
    }

    void SetMaxDistance(const Dimension& distance)
    {
        maxDeltaDistance_ = distance;
    }

    const Offset& GetBeginLocalLocation()
    {
        return beginLocalLocation_;
    }

    const Offset& GetBeginGlobalLocation()
    {
        return beginGlobalLocation_;
    }

private:
    CancelableCallback<void()> clickCountTask_;
    int32_t clickTimes_ = 1;
    TimeStamp lastClickTimeStamp_;
    Offset lastClickPosition_ = Offset(Infinity<double>(), Infinity<double>());
    float minIntervalTime_ = 0.0f;
    float maxIntervalTime_ = 300.0f;
    Dimension maxDeltaDistance_ = 15.0_vp;
    Offset beginLocalLocation_;
    Offset beginGlobalLocation_;
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_MULTIPLE_CLICK_RECOGNIZER_H
