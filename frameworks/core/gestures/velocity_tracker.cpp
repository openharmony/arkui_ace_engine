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

#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace {
int32_t VelocityTracker::POINT_NUMBER = SystemProperties::GetVelocityTrackerPointNumber();

namespace {
static constexpr int32_t MAX_INDEX = 4;

void CheckExtremePoint(const LeastSquareImpl& axis, double extremX, uint32_t valSize)
{
    const auto& x = axis.GetXVals();
    const auto& y = axis.GetYVals();
    auto count = axis.GetTrackNum();

    // filter quiver
    if (LessNotEqual(std::fabs(y[count - 1] - y[count - 2]), 100)) { // 2: const, 100: quiver threshold
        return;
    }
    // check if extrem point exists between axis's points.
    if (GreatNotEqual(extremX, x[x.size() - valSize]) && LessNotEqual(extremX, x.back())) {
        LOGI("Extrem point %{public}f exists between tracker points.", extremX);
    }
    // dump points
    int32_t i = static_cast<int32_t>(x.size());
    for (int32_t cnt = VelocityTracker::POINT_NUMBER; i > 0 && cnt > 0; --cnt) {
        --i;
        LOGI("Last tracker points[%{public}d] x=%{public}f y=%{public}f", cnt, x[i], y[i]);
    }
}

// true for increasing, false for decreasing, nullopt for nonmonotonic
std::optional<bool> GetMononicity(const std::vector<double>& vals, uint32_t valSize)
{
    std::optional<bool> compareResult;
    for (uint32_t i = vals.size() - valSize + 1; i < vals.size(); ++i) {
        double delta = vals[i] - vals[i - 1];
        if (NearZero(delta)) {
            continue;
        }
        bool isIncreasing = Positive(delta);
        if (compareResult.value_or(isIncreasing) != isIncreasing) {
            return std::nullopt;
        }
        compareResult = isIncreasing;
    }
    return compareResult;
}

double GetLinearSlope(const LeastSquareImpl& axis)
{
    const auto& x = axis.GetXVals();
    const auto& y = axis.GetYVals();
    auto count = axis.GetTrackNum();
    int32_t index = 2;
    while (index <= MAX_INDEX && count >= index) {
        if (!NearEqual(x[count - 1], x[count - index])) {
            break;
        }
        [[maybe_unused]] auto previousIndex = count - index;
        [[maybe_unused]] auto lastIndex = count - 1;
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, SEC_PLD(,
            "GetLinearSlope points time is same y[%{public}d]: %{public}f y[%{public}d]: %{public}f x[%{public}d]: "
            "%{public}f x[%{public}d]: %{public}f"),
            SEC_PARAM(previousIndex, y[previousIndex], lastIndex, y[lastIndex], previousIndex,
            x[previousIndex], lastIndex, x[lastIndex]));
        index++;
    }
    if (index > MAX_INDEX || index > count) {
        return 0.0;
    }
    return (y[count - 1] - y[count - index]) / (x[count - 1] - x[count - index]); // 2: const
}

void CorrectMonotonicAxisVelocity(const LeastSquareImpl& axis, double& v, double extremX)
{
    const auto& yVals = axis.GetYVals();
    uint32_t valSize = std::min(static_cast<int32_t>(yVals.size()), VelocityTracker::POINT_NUMBER);
    auto mononicity = GetMononicity(yVals, valSize);
    if (!mononicity.has_value()) {
        return;
    }

    // velocity is still, no need to do correction
    if (mononicity.value() ? GreatOrEqual(v, 0) : LessOrEqual(v, 0)) {
        return;
    }

    // Do correction
    v = GetLinearSlope(axis);
    CheckExtremePoint(axis, extremX, valSize);
}

double UpdateAxisVelocity(LeastSquareImpl& axis)
{
    std::vector<double> param(VelocityTracker::LEAST_SQUARE_PARAM_NUM, 0);
    auto x = axis.GetXVals().back();
    // curve is param[0] * x^2 + param[1] * x + param[2]
    // the velocity is 2 * param[0] * x + param[1];
    double velocity = 0.0;
    if (axis.GetLeastSquareParams(param)) {
        velocity = 2 * param[0] * x + param[1];      // 2: const of formula
        double extremX = -0.5 * param[1] / param[0]; // 0.5: const of formula
        CorrectMonotonicAxisVelocity(axis, velocity, extremX);
    } else { // Use linear velocity instead
        velocity = GetLinearSlope(axis);
    }
    return velocity;
}
} // namespace

void VelocityTracker::UpdateTouchPoint(const TouchEvent& event, bool end, float range)
{
    if (end && SystemProperties::IsVelocityWithoutUpPoint()) {
        return;
    }
    if (isFirstPoint_) {
        firstTrackPoint_ = event;
        isFirstPoint_ = false;
    } else {
        delta_ = event.GetOffset() - lastPosition_;
        lastPosition_ = event.GetOffset();
    }
    TouchEvent lastTrackPoint(currentTrackPoint_);
    currentTrackPoint_ = event;
    isVelocityDone_ = false;
    std::chrono::duration<double> diffTime = event.time - lastTimePoint_;
    lastTimePoint_ = event.time;
    lastPosition_ = event.GetOffset();
    if (end) {
        Offset oriDelta;
        if (isFirstPoint_) {
            oriDelta = delta_;
        } else {
            Offset lastMoveEvent = lastTrackPoint.GetOffset();
            Offset upEvent = event.GetOffset();
            oriDelta = upEvent - lastMoveEvent;
        }
        if (oriDelta.IsZero() && (diffTime.count() < range)) {
            return;
        }
    }
    // nanoseconds duration to seconds.
    touchEventTime_.push_back(event.time);
    std::chrono::duration<double> duration = event.time - touchEventTime_[mIndex_];
    auto seconds = duration.count();
    auto timeWindowEnabled = SystemProperties::IsVelocityWithinTimeWindow();
    if (timeWindowEnabled && seconds > DURATION_LONGEST_THRESHOLD) {
        xAxis_.PopFrontPoint();
        yAxis_.PopFrontPoint();
        mIndex_++;
    }
    xAxis_.UpdatePoint(seconds, event.x);
    yAxis_.UpdatePoint(seconds, event.y);
}

void VelocityTracker::UpdateTrackerPoint(double x, double y, const TimeStamp& time, bool end)
{
    Offset trackerPoint(x, y);
    isVelocityDone_ = false;
    if (isFirstPoint_) {
        firstPointTime_ = time;
        isFirstPoint_ = false;
    } else {
        delta_ = trackerPoint - lastPosition_;
        lastPosition_ = trackerPoint;
    }
    std::chrono::duration<double> diffTime = time - lastTimePoint_;
    lastTimePoint_ = time;
    lastPosition_ = trackerPoint;
    // judge duration is 500ms.
    static const double range = 0.5;
    if (delta_.IsZero() && end && (diffTime.count() < range)) {
        return;
    }
    // nanoseconds duration to seconds.
    std::chrono::duration<double> duration = time - firstPointTime_;
    auto seconds = duration.count();
    xAxis_.UpdatePoint(seconds, x);
    yAxis_.UpdatePoint(seconds, y);
}

void VelocityTracker::UpdateVelocity()
{
    if (isVelocityDone_) {
        return;
    }
    if (xAxis_.GetTrackNum() < 2) { // Velocity is calculated from at least 2 points.
        return;
    }

    double xVelocity = UpdateAxisVelocity(xAxis_);
    double yVelocity = UpdateAxisVelocity(yAxis_);
    velocity_.SetOffsetPerSecond({ xVelocity, yVelocity });
    isVelocityDone_ = true;
}

void VelocityTracker::DumpVelocityPoints() const
{
    auto func = [](const LeastSquareImpl &axis, const char* str) {
        const auto& xVal = axis.GetXVals();
        const auto& yVal = axis.GetYVals();
        int32_t i = static_cast<int32_t>(xVal.size());
        auto baseVal = yVal[0];
        std::stringstream oss;
        oss << std::string(str);
        for (int32_t cnt = VelocityTracker::POINT_NUMBER; i > 0 && cnt > 0; --cnt) {
            --i;
            if (SystemProperties::GetDebugEnabled()) {
                TAG_LOGI(AceLogTag::ACE_GESTURE, "%{public}s last tracker point[%{public}d] x=%{public}f y=%{public}f",
                    str, cnt, xVal[i], yVal[i] - baseVal);
            } else {
                oss << " [" << std::to_string(cnt) << "] x " << std::to_string(xVal[i]) <<
                    " y " << std::to_string(yVal[i] - baseVal);
            }
        }
        TAG_LOGI(AceLogTag::ACE_GESTURE, "%{public}s", oss.str().c_str());
    };
    func(xAxis_, "xAxis");
    func(yAxis_, "yAxis");
}
} // namespace OHOS::Ace
