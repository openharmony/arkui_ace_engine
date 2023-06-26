/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"

#include <sys/time.h>

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MIN_TIME = 1.0;
constexpr int32_t MIN_DURATION = 250;
constexpr double DRAG = 0.995;
constexpr double ZERO_SPEED = 0.5;
} // namespace

void TimePickerTossAnimationController::SetStart(double y)
{
    if (toss_) {
        toss_->Stop();
    }

    yStart_ = y;
    timeStart_ = GetCurrentTime();
}

void TimePickerTossAnimationController::SetEnd(double y)
{
    if (toss_) {
        toss_->Stop();
    }

    yEnd_ = y;
    timeEnd_ = GetCurrentTime();
}

void TimePickerTossAnimationController::Stop()
{
    stopped_ = true;
    if (toss_) {
        toss_->Stop();
    }
}

bool TimePickerTossAnimationController::Play()
{
    stopped_ = false;
    auto timeDiff = timeEnd_ - timeStart_;
    if (timeDiff < MIN_TIME) {
        LOGW("toss time[%{public}lf] too small.", timeDiff);
        return false;
    }

    double speed = (yEnd_ - yStart_) / timeDiff;
    if (NearZero(speed)) {
        LOGW("toss speed is zero");
        return false;
    }

    double zeroSpeed = GreatNotEqual(speed, 0.0) ? ZERO_SPEED : -ZERO_SPEED;
    double time = zeroSpeed / speed;
    time = std::log(time) / std::log(DRAG);
    if (time < MIN_DURATION) {
        LOGW("toss time[%{public}lf] to small.", time);
        return false;
    }

    LOGD("toss play speed: %{public}lf, time: %{public}lf", speed, time);
    speed_ = speed;
    int nTime = static_cast<int>(time);
    auto weak = AceType::WeakClaim(this);
    toss_ = AceType::MakeRefPtr<PickerAnimation>(pipeline_, 0.0, time, 0, nTime, Curves::LINEAR, [weak](double value) {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        auto column = AceType::DynamicCast<TimePickerColumnPattern>(ref->column_.Upgrade());
        CHECK_NULL_VOID(column);
        double distance = std::pow(DRAG, value);
        distance = (distance - 1.0) * ref->speed_ / std::log(DRAG);
        if (!ref->IsStopped()) {
            column->UpdateToss(ref->yEnd_ + distance);
        }
    });
    toss_->AddStopCallback([weak] {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        auto column = AceType::DynamicCast<TimePickerColumnPattern>(ref->column_.Upgrade());
        CHECK_NULL_VOID(column);
        column->TossStoped();
    });
    toss_->Play();
    return true;
}

double TimePickerTossAnimationController::GetCurrentTime() const
{
    struct timeval tv = { 0 };
    int result = gettimeofday(&tv, nullptr);
    if (result != 0) {
        LOGE("toss gettimeofday failed.");
        return 0.0;
    }

    double sec = static_cast<double>(tv.tv_sec);
    double msec = static_cast<double>(tv.tv_usec / 1000.0); // usec / 1000 is msec
    return (sec * 1000 + msec);                             // sec * 1000 is msec
}
} // namespace OHOS::Ace::NG
