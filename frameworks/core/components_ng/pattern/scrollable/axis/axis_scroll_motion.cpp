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

#include "core/components_ng/pattern/scrollable/axis/axis_scroll_motion.h"

#include "base/utils/time_util.h"

namespace OHOS::Ace::NG {

void AxisScrollMotion::Reset(float startPos, float distance)
{
    startPos_ = startPos;
    distance_ = distance;
    startTime_ = currentTime_;
    currentPos_ = startPos;
    finalPos_ = startPos + distance;
    endTime_ = startTime_ + AXIS_ANIMATION_DURATION;
    if (LessOrEqual(std::abs(distance), AXIS_DISTANCE_THRESHOLD)) {
        moveCallback_ = [endTime = endTime_, startTime = startTime_, startPos = startPos_, finalPos = finalPos_,
                            distance](float offsetTime) -> float {
            auto currentPos = startPos + distance * ((offsetTime - startTime) / (endTime - startTime));
            if ((LessOrEqual(startPos, finalPos) && GreatNotEqual(currentPos, finalPos)) ||
                (GreatOrEqual(startPos, finalPos) && LessNotEqual(currentPos, finalPos))) {
                currentPos = finalPos;
            }
            return currentPos;
        };
    } else {
        moveCallback_ = [endTime = endTime_, startTime = startTime_, startPos = startPos_, finalPos = finalPos_,
                            distance](float offsetTime) -> float {
            auto currentPos = startPos;
            if (LessOrEqual((offsetTime - startTime), AXIS_ANIMATION_KEY_DURATION)) {
                currentPos += (offsetTime - startTime) *
                              (distance + (Positive(distance) ? -AXIS_KEY_DISTANCE : AXIS_KEY_DISTANCE)) /
                              AXIS_ANIMATION_KEY_DURATION;
            } else {
                currentPos += (distance + (Positive(distance) ? -AXIS_KEY_DISTANCE : AXIS_KEY_DISTANCE)) +
                              (offsetTime - startTime - AXIS_ANIMATION_KEY_DURATION) *
                                  (Positive(distance) ? AXIS_KEY_DISTANCE : -AXIS_KEY_DISTANCE) /
                                  (endTime - startTime - AXIS_ANIMATION_KEY_DURATION);
            }
            if ((LessOrEqual(startPos, finalPos) && GreatNotEqual(currentPos, finalPos)) ||
                (GreatOrEqual(startPos, finalPos) && LessNotEqual(currentPos, finalPos))) {
                currentPos = finalPos;
            }
            return currentPos;
        };
    }
}

bool AxisScrollMotion::IsCompleted()
{
    if (GreatOrEqual(std::abs(currentTime_), std::abs(endTime_))) {
        currentTime_ = 0.f;
        return true;
    }
    return false;
}

void AxisScrollMotion::Move(float offsetTime)
{
    currentTime_ = offsetTime;
    currentPos_ = moveCallback_(offsetTime);
}

} // namespace OHOS::Ace::NG