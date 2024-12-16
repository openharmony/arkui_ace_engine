/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_AXIS_AXIS_SCROLL_ANIMATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_AXIS_AXIS_SCROLL_ANIMATOR_H
#include "base/geometry/dimension.h"
#include "base/utils/time_util.h"
#include "core/animation/curves.h"
#include "core/animation/motion.h"

namespace OHOS::Ace::NG {

using MoveCallbck = std::function<float(float)>;
constexpr int32_t AXIS_DISTANCE_THRESHOLD = 720;
constexpr int32_t AXIS_KEY_DISTANCE = 240;
constexpr float AXIS_ANIMATION_DURATION = 200.f;
constexpr float AXIS_ANIMATION_KEY_DURATION = 100.f;

class ACE_EXPORT AxisScrollMotion : public Motion {
    DECLARE_ACE_TYPE(AxisScrollMotion, Motion);

public:
    AxisScrollMotion(float startPos, float distance)
    {
        Reset(startPos, distance);
    }

    double GetCurrentPosition() override
    {
        return currentPos_;
    }

    double GetFinalPosition()
    {
        return finalPos_;
    }

    double GetCurrentVelocity() override
    {
        return 0.0;
    }

    void Reset(float startPos, float distance);

    bool IsCompleted() override;

    std::string GetMotionType() const override
    {
        return "axis scroll motion";
    }

    void Move(float offsetTime) override;

    float GetCurrentTime()
    {
        return currentTime_;
    }

    void ResetCurrentTime()
    {
        currentTime_ = 0.f;
    }

private:
    float currentPos_ = 0.f;
    float distance_ = 0.f;
    float startPos_ = 0.f;
    float finalPos_ = 0.f;
    float startTime_ = 0.f;
    float currentTime_ = 0.f;
    float endTime_ = 0.f;
    MoveCallbck moveCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLLABLE_AXIS_AXIS_SCROLL_ANIMATOR_H