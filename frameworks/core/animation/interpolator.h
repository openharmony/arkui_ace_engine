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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_INTERPOLATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_INTERPOLATOR_H

#include "base/log/log.h"
#include "core/animation/animation_pub.h"
#include "core/animation/time_event.h"

namespace OHOS::Ace {

class Interpolator : public TimeEvent {
    DECLARE_ACE_TYPE(Interpolator, TimeEvent);

public:
    Interpolator() = default;
    ~Interpolator() override = default;

    // interpolate animations must have duration, and accept normalized timestamp.
    // so far, do not support play in sequence, always return 1.0, besides picture animation.
    float GetDuration() const
    {
        return duration_;
    }

    void SetDuration(float duration)
    {
        duration_ = duration;
    }

    // Interpolator use OnNormalizedTimestampChanged instead.
    void OnTimestampChanged(float timestamp, float normalizedTime, bool reverse) final
    {
        if (normalizedTime < NORMALIZED_DURATION_MIN || normalizedTime > NORMALIZED_DURATION_MAX) {
            LOGE("Interpolator only accepts normalized time, invalid time: %{public}f", normalizedTime);
            return;
        }
        // just pass normalized time to subclass.
        OnNormalizedTimestampChanged(normalizedTime, reverse);
    }

    // when a Interpolator starts, animator will notify it through this interface.
    virtual void OnNormalizedTimestampChanged(float normalized, bool reverse) = 0;

    virtual void OnInitNotify(float normalizedTime, bool reverse) = 0;

protected:
    // so far, do not support play multi interpolate animations in sequence. so always set it to 1.0
    // but do not change it to const, picture animation's duration may be not equals 1.0
    // and this variable will change to modifiable when support play animations in sequence.
    float duration_ { NORMALIZED_DURATION_MAX };
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_INTERPOLATOR_H
