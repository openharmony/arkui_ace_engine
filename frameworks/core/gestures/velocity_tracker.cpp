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

#include "core/gestures/velocity_tracker.h"

#include <chrono>

namespace OHOS::Ace {

void VelocityTracker::UpdateTouchPoint(const TouchPoint& event)
{
    currentTrackPoint_ = event;
    if (isFirstPoint_) {
        firstTrackPoint_ = event;
        lastPosition_ = event.GetOffset();
        lastTimePoint_ = event.time;
        isFirstPoint_ = false;
        return;
    }

    delta_ = event.GetOffset() - lastPosition_;

    // nanoseconds duration to seconds.
    const std::chrono::duration<double> duration = event.time - lastTimePoint_;
    if (!NearZero(duration.count())) {
        velocity_.SetOffsetPerSecond(delta_ / duration.count());
    }

    lastPosition_ = event.GetOffset();
    lastTimePoint_ = event.time;
}

} // namespace OHOS::Ace
