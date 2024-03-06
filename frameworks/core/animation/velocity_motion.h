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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_VELOCITY_MOTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_VELOCITY_MOTION_H
#include "core/animation/motion.h"

namespace OHOS::Ace {
using MotionCompleteCallback = std::function<bool(float)>;
constexpr float OFFSET_UNIT_CONVERT = 1000.0f;

class ACE_EXPORT VelocityMotion : public Motion {
    DECLARE_ACE_TYPE(VelocityMotion, Motion);

public:
    VelocityMotion(MotionCompleteCallback&& complete)
        : complete_(std::move(complete))
    {
        lastOffsetTime_ = 0.0f;
    }

    /**
     * @description: Get the roll distance
     * @return The scroll distance notified to the listener
     */
    double GetCurrentPosition() override
    {
        return scrollOffset_;
    }

    double GetCurrentVelocity() override
    {
        return velocity_;
    }
    /**
     * @description: By adding a callback, it is up to the listener to decide whether to stop the motion
     * @return True stop
     */
    bool IsCompleted() override
    {
        if (complete_) {
            return complete_(scrollOffset_);
        }
        return true;
    }

    std::string GetMotionType() const override
    {
        return "velocity";
    }

    /**
     * @description: Each subclass of scrollable component should override this method to perform motion in each
     * timestamp. This function is called in motion's OnTimestampChanged function, where inform the listener of the
     * distance of rolling
     * @param {float} offsetTime Time offset, continuously growing, with irregular intervals
     * @return None
     */
    void Move(float offsetTime) override
    {
        scrollOffset_ = velocity_ * (offsetTime - lastOffsetTime_) / OFFSET_UNIT_CONVERT;
        lastOffsetTime_ = offsetTime;
    }

    /**
     * @description:  Set velocity
     * @param {float} velocity
     * @return None
     */
    void SetVelocity(const float velocity)
    {
        velocity_ = velocity;
    }

    /**
     * @description:  Init scroll status
     * @return None
     */
    void Init()
    {
        scrollOffset_ = 0.0f;
        lastOffsetTime_ = 0.0f;
    }

private:
    // Tells the listener how far they need to roll, in px
    float scrollOffset_ = 0.0f;
    MotionCompleteCallback complete_;
    // It is used to record the current speed, and different speeds can be passed in through the reset function, so that
    // the speed can be changed
    float velocity_ = 0.0f;
    // Record the last time given by the move function
    float lastOffsetTime_ = 0.0f;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_VELOCITY_MOTION_H