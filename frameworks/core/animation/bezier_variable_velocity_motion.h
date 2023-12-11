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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_BEZIER_VARIABLE_VELOCITY_MOTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_BEZIER_VARIABLE_VELOCITY_MOTION_H
#include "base/geometry/dimension.h"
#include "core/animation/curves.h"
#include "core/animation/motion.h"

namespace OHOS::Ace {

static constexpr Dimension HOT_ZONE_HEIGHT_VP_DIM = 59.0_vp;
static constexpr Dimension HOT_ZONE_WIDTH_VP_DIM = 26.0_vp;
using MotionCompleteCallbck = std::function<bool(float)>;
constexpr float UNIT_CONVERT = 1000.0f;
constexpr float MAX_SPEED = 2400.0f;

class ACE_EXPORT BezierVariableVelocityMotion : public Motion {
    DECLARE_ACE_TYPE(BezierVariableVelocityMotion, Motion);

public:
    BezierVariableVelocityMotion(float offsetPct, MotionCompleteCallbck&& complete)
        : complete_(complete), offsetPct_(offsetPct)
    {
        Reset(offsetPct_, true);
    }
    /**
     * @description: Get the roll distance
     * @return The scroll distance notified to the listener
     */
    double GetCurrentPosition() override
    {
        return Positive(offsetPct_) ? scrollOffset_ : Negative(offsetPct_) ? -scrollOffset_ : 0;
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
            return complete_(offsetPct_);
        }
        return true;
    }

    /**
     * @description: The ratio of the hot zone offset to the maximum hot zone offset is used as an input parameter of
     * bezier, resulting in an output, which is the proportion of velocity.
     * The farther away you are from the outer edge of the hot zone, the greater the velocity
     * @param {float} offsetPct
     * @return Scroll speed
     */
    double ComputeVelocity(float offsetPct)
    {
        return Curves::SHARP->MoveInternal(std::abs(offsetPct)) * MAX_SPEED;
    }

    std::string GetMotionType() const override
    {
        return "bezier variable velocity";
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
        scrollOffset_ = velocity_ * (offsetTime - lastOffsetTime_) / UNIT_CONVERT;
        lastOffsetTime_ = offsetTime;
    }

    /**
     * @description: Resets the hot spot offset to change the current speed, ultimately for variable speed scrolling
     * @param {float} offsetPct Hot Spot Offset percent. The ratio of its maximum offset to the hot zone is used as an
     * input parameter to bezier
     * @param {float} reset_time. When the animation starts, it needs to be reset
     * @return None
     */
    void Reset(float offsetPct, bool reset_time = false)
    {
        offsetPct_ = offsetPct;
        velocity_ = ComputeVelocity(offsetPct_);
        if (reset_time) {
            lastOffsetTime_ = 0.0f;
        }
    }

    /**
     * @description:  reinitialize BezierVariableVelocityMotion
     * @param {float} offsetPct
     * @return {*}
     */
    void ReInit(float offsetPct)
    {
        Reset(offsetPct, true);
    }

private:
    // Tells the listener how far they need to roll, in px
    float scrollOffset_ = 0.0f;
    MotionCompleteCallbck complete_;
    // It is used to record the current speed, and different speeds can be passed in through the reset function, so that
    // the speed can be changed
    float velocity_ = 0.0f;
    // The hot zone offset corresponds to a fixed velocity one-to-one by the bezier.
    // It is also possible to implement a generic class with velocity as an input parameter, but this is not necessary
    // at the moment
    float offsetPct_ = 0.0f;
    // Record the last time given by the move function
    float lastOffsetTime_ = 0.0f;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_BEZIER_VARIABLE_VELOCITY_MOTION_H