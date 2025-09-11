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

#include "core/animation/spring_curve.h"
#include "core/common/container.h"

namespace OHOS::Ace {
namespace {

constexpr float DEFAULT_VALUE_THRESHOLD = 0.001f;
constexpr float VELOCITY_THRESHOLD_RATIO = 25.0f;
constexpr float DEFAULT_START_POSITION = 0.0f;
constexpr float DEFAULT_END_POSITION = 1.0f;
constexpr int32_t DEFAULT_ESTIMATE_STEPS = 100;
constexpr float FRACTION_PARAMETER_MAX = 1.0f;
constexpr float FRACTION_PARAMETER_MIN = 0.0f;
constexpr float MAX_ESTIMATE_DURATION = 1000.0f;
constexpr float HALF = 0.5f;

} // namespace

SpringCurve::SpringCurve(float velocity, float mass, float stiffness, float damping)
    : velocity_(velocity), mass_(mass), stiffness_(stiffness), damping_(damping)
{
    property_ = AceType::MakeRefPtr<SpringProperty>(mass_, stiffness_, damping_);
    valueThreshold_ = (DEFAULT_END_POSITION - DEFAULT_START_POSITION) * DEFAULT_VALUE_THRESHOLD;
    SetEndPosition(DEFAULT_END_POSITION, velocity_);
}

void SpringCurve::SetEndPosition(float endPosition, float startVelocity)
{
    startPosition_ = 0.0f;
    endPosition_ = endPosition;
    currentVelocity_ = startVelocity;
    currentPosition_ = startPosition_;
    velocityThreshold_ = valueThreshold_ * VELOCITY_THRESHOLD_RATIO;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        solution_ = SpringModel::Build(endPosition_, startVelocity, property_);
    } else {
        solution_ = SpringModel::Build(startPosition_ - endPosition_, startVelocity, property_);
    }
    if (!solution_) {
        LOGW("Create springCurve error, %{public}s", ToString().c_str());
        return;
    }
    InitEstimateDuration();
}

void SpringCurve::InitEstimateDuration()
{
    float velocity = 0.0f;
    float time = 1.0f / DEFAULT_ESTIMATE_STEPS;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        float position = 0.0f;
        for (int32_t i = 1; i < DEFAULT_ESTIMATE_STEPS; ++i) {
            position = endPosition_ - solution_->Position(time * i);
            velocity = solution_->Velocity(time * i);
            if (NearEqual(position, endPosition_, valueThreshold_) && NearZero(velocity, velocityThreshold_)) {
                estimateDuration_ = time * i;
                break;
            }
        }
        return;
    }
    // Binary search to estimate duration
    float minDuration = 0.0f;
    float maxDuration = MAX_ESTIMATE_DURATION;
    float positionChange = 0.0f;
    while (maxDuration - minDuration >= time) {
        auto duration = (minDuration + maxDuration) * HALF;
        positionChange = solution_->Position(duration);
        velocity = solution_->Velocity(duration);
        if (NearZero(positionChange, valueThreshold_) && NearZero(velocity, velocityThreshold_)) {
            maxDuration = duration;
        } else {
            minDuration = duration;
        }
    }
    estimateDuration_ = maxDuration;
}

float SpringCurve::MoveInternal(float time)
{
    if (time < FRACTION_PARAMETER_MIN || time > FRACTION_PARAMETER_MAX) {
        LOGE("SpringCurve MoveInternal: time is less than 0 or larger than 1, return 1");
        return FRACTION_PARAMETER_MAX;
    }
    CHECK_NULL_RETURN(solution_, endPosition_);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        currentPosition_ = endPosition_ - solution_->Position(time * estimateDuration_);
    } else {
        currentPosition_ = endPosition_ + solution_->Position(time * estimateDuration_);
    }
    currentVelocity_ = solution_->Velocity(time * estimateDuration_);
    if (NearEqual(currentPosition_, endPosition_, valueThreshold_) &&
        NearZero(currentVelocity_, velocityThreshold_)) {
        currentPosition_ = endPosition_;
        currentVelocity_ = 0.0f;
    }
    return currentPosition_;
}

const std::string SpringCurve::ToString()
{
    std::string curveString("spring");
    std::string comma(",");
    curveString.append(std::string("(") + std::to_string(velocity_) + comma + std::to_string(mass_)
        + comma + std::to_string(stiffness_) + comma + std::to_string(damping_) + std::string(")"));
    return curveString;
}

const std::string SpringCurve::ToSimpleString()
{
    const int32_t precision = 2;
    std::stringstream ss;
    std::string comma(",");
    ss << "spring(" << std::fixed << std::setprecision(precision) << velocity_
       << comma << mass_ << comma << stiffness_ << comma << damping_ << ")";
    return ss.str();
}
} // namespace OHOS::Ace