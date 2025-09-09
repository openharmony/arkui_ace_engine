/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_CURVE_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_CURVE_H

#include <functional>
#include <iomanip>
#include <math.h>
#include <sstream>

#include "ui/base/ace_type.h"
#include "ui/base/macros.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace {
class NativeCurveHelper;

constexpr double SQUARE = 2.0;
constexpr int32_t PRECISION = 2;

// The running time of the curve needs to be normalized to the interval of 0.0 to 1.0;
// Relatively, the corresponding value of the curve also needs to be normalized to the interval of 0.0 to 1.0;
class ACE_FORCE_EXPORT Curve : public AceType {
    DECLARE_ACE_TYPE(Curve, AceType);

public:
    Curve() = default;
    ~Curve() override = default;

    // Returns the value at specific time.
    // Notice: The value of time must be between 0.0 and 1.0 since the curve uses normalized timestamp.
    float Move(float time)
    {
        // time always between 0.0 and 1.0
        return MoveInternal(time);
    }

    // Each subclass needs to override this method to implement motion in the 0.0 to 1.0 time range.
    virtual float MoveInternal(float time) = 0;
    virtual const std::string ToString()
    {
        return "";
    }

    virtual const std::string ToSimpleString()
    {
        return "";
    }

    virtual bool IsEqual(const RefPtr<Curve>& curve) const
    {
        return false;
    }
};

// The reverse curve is used to convert the direction of motion.
// It uses the 1.0->0.0 motion of the child curve to achieve the reverse purpose.
class ReverseCurve final : public Curve {
    DECLARE_ACE_TYPE(ReverseCurve, Curve);

public:
    explicit ReverseCurve(const RefPtr<Curve>& curve) : curve_(curve) {}
    ~ReverseCurve() override = default;

    float MoveInternal(float time) final
    {
        if (!curve_) {
            return 0.0f;
        }

        if (time > 1.0f || time < 0.0f) {
            return curve_->MoveInternal(0.0f);
        }
        return curve_->MoveInternal(1.0f - time);
    }
private:
    const RefPtr<Curve> curve_;
};

class ComplementaryCurve final : public Curve {
    DECLARE_ACE_TYPE(ComplementaryCurve, Curve);

public:
    explicit ComplementaryCurve(const RefPtr<Curve>& curve) : curve_(curve) {}
    ~ComplementaryCurve() override = default;

    float MoveInternal(float time) final
    {
        if (!curve_) {
            return 0.0f;
        }

        if (time > 1.0f || time < 0.0f) {
            return curve_->MoveInternal(0.0f);
        }
        return 1.0f - curve_->MoveInternal(time);
    }
private:
    const RefPtr<Curve> curve_;
};

class DecelerationCurve final : public Curve {
    DECLARE_ACE_TYPE(DecelerationCurve, Curve);

public:
    float MoveInternal(float time) override
    {
        return 1.0f - std::pow(1.0f - time, SQUARE);
    }

    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        return AceType::InstanceOf<DecelerationCurve>(curve);
    }
};

class LinearCurve final : public Curve {
    DECLARE_ACE_TYPE(LinearCurve, Curve);

public:
    float MoveInternal(float time) override
    {
        if (time < fractionMin || time > fractionMax) {
            return fractionMax;
        }
        return time;
    }

    const std::string ToString() override
    {
        std::string curveString("linear");
        return curveString;
    }

    const std::string ToSimpleString() override
    {
        return ToString();
    }

    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        return AceType::InstanceOf<LinearCurve>(curve);
    }

private:
    float fractionMin = 0.0f;
    float fractionMax = 1.0f;
};

class SineCurve final : public Curve {
    DECLARE_ACE_TYPE(SineCurve, Curve);

public:
    float MoveInternal(float time) override
    {
        static constexpr float PI = 3.14f;
        return std::sin(PI * time / 2.0f); // half period
    }

    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        return AceType::InstanceOf<SineCurve>(curve);
    }
};

class ElasticsCurve final : public Curve {
    DECLARE_ACE_TYPE(ElasticsCurve, Curve);

public:
    explicit ElasticsCurve(float tension) : tension_(tension) {}
    ~ElasticsCurve() override = default;
    float MoveInternal(float time) override
    {
        float para = time - 1.0f;
        return para * para * ((tension_ + 1.0f) * para + tension_) + 1.0f;
    }

    float GetTension() const
    {
        return tension_;
    }

    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        auto other = AceType::DynamicCast<ElasticsCurve>(curve);
        if (!other) {
            return false;
        }
        return NearEqual(other->GetTension(), tension_);
    }
private:
    float tension_ = 2.0f; // Default Elastics tension.
};

enum class StepsCurvePosition {
    START,
    END,
};

class StepsCurve : public Curve {
    DECLARE_ACE_TYPE(StepsCurve, Curve);

public:
    explicit StepsCurve(int32_t steps, StepsCurvePosition position = StepsCurvePosition::START)
        : steps_(steps <= 0 ? 1 : steps), position_(position)
    {}
    ~StepsCurve() override = default;

    float MoveInternal(float time) override
    {
        if (time < fractionMin || time > fractionMax) {
            return fractionMax;
        }
        auto currentStep = static_cast<int32_t>(time * steps_);
        if (position_ == StepsCurvePosition::START && currentStep < steps_) {
            currentStep++;
        }
        return static_cast<float>(currentStep) / steps_;
    }
    const std::string ToString() override
    {
        std::string curveString("steps");
        std::string comma(",");
        curveString.append(std::string("(") + std::to_string(steps_) + comma);
        if (position_ == StepsCurvePosition::START) {
            curveString.append(std::string("start"));
        } else {
            curveString.append(std::string("end"));
        }
        curveString.append(std::string(")"));
        return curveString;
    }

    const std::string ToSimpleString() override
    {
        return ToString();
    }

    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        auto other = AceType::DynamicCast<StepsCurve>(curve);
        if (!other) {
            return false;
        }
        return other->GetSteps() == steps_ && other->GetStepsCurvePosition() == position_;
    }

    int32_t GetSteps() const
    {
        return steps_;
    }

    StepsCurvePosition GetStepsCurvePosition() const
    {
        return position_;
    }

private:
    int32_t steps_;
    const StepsCurvePosition position_;
    float fractionMin = 0.0f;
    float fractionMax = 1.0f;

    friend class NativeCurveHelper;
};

class CustomCurve final : public Curve {
    DECLARE_ACE_TYPE(CustomCurve, Curve);

public:
    explicit CustomCurve(const std::function<float(float)>& func) : interpolateFunc_(func) {}
    ~CustomCurve() override = default;
    float MoveInternal(float time) override
    {
        return interpolateFunc_ ? interpolateFunc_(time) : 1.0f;
    }
    const std::string ToString() override
    {
        return "customCallback";
    }
    const std::string ToSimpleString() override
    {
        return ToString();
    }
private:
    std::function<float(float)> interpolateFunc_;

    friend class NativeCurveHelper;
};

class ResponsiveSpringMotion final : public Curve {
    DECLARE_ACE_TYPE(ResponsiveSpringMotion, Curve);

public:
    ResponsiveSpringMotion(float response, float dampingRatio, float blendDuration = 0.0f)
        : response_(response), dampingRatio_(dampingRatio), blendDuration_(blendDuration)
    {}
    ~ResponsiveSpringMotion() override = default;
    // this MoveInterval function is not the real implementation of the function.
    // The curve should use the curve in rosen.
    float MoveInternal(float time) override
    {
        return 0.0f;
    }
    const std::string ToString() override
    {
        std::string curveString("responsive-spring-motion");
        std::string comma(",");
        curveString.append(std::string("(") + std::to_string(response_) + comma + std::to_string(dampingRatio_) +
                           comma + std::to_string(blendDuration_) + std::string(")"));
        return curveString;
    }
    const std::string ToSimpleString() override
    {
        const int32_t precision = 3;
        std::stringstream ss;
        std::string comma(",");
        ss << "responsiveSpring(" << std::fixed << std::setprecision(precision) << response_
           << comma << dampingRatio_ << comma << blendDuration_ << ")";
        return ss.str();
    }
    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        auto other = AceType::DynamicCast<ResponsiveSpringMotion>(curve);
        if (!other) {
            return false;
        }
        return NearEqual(other->GetResponse(), response_) && NearEqual(other->GetDampingRatio(), dampingRatio_) &&
               NearEqual(other->GetBlendDuration(), blendDuration_);
    }
    float GetResponse() const
    {
        return response_;
    }
    float GetDampingRatio() const
    {
        return dampingRatio_;
    }
    float GetBlendDuration() const
    {
        return blendDuration_;
    }
    float GetMinimumAmplitudeRatio() const
    {
        return minimumAmplitudeRatio_;
    }
    void UpdateMinimumAmplitudeRatio(float minimumAmplitudeRatio)
    {
        minimumAmplitudeRatio_ = minimumAmplitudeRatio;
    }
    static constexpr float DEFAULT_SPRING_MOTION_RESPONSE = 0.55f;
    static constexpr float DEFAULT_SPRING_MOTION_DAMPING_RATIO = 0.825f;
    static constexpr float DEFAULT_SPRING_MOTION_BLEND_DURATION = 0.0f;
    static constexpr float DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE = 0.15f;
    static constexpr float DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO = 0.86f;
    static constexpr float DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION = 0.25f;
    static constexpr float DEFAULT_RESPONSIVE_SPRING_AMPLITUDE_RATIO = 0.001f;

private:
    float response_;
    float dampingRatio_;
    float blendDuration_;
    float minimumAmplitudeRatio_ = DEFAULT_RESPONSIVE_SPRING_AMPLITUDE_RATIO;
};

class InterpolatingSpring final : public Curve {
    DECLARE_ACE_TYPE(InterpolatingSpring, Curve);

public:
    InterpolatingSpring(float velocity, float mass, float stiffness, float damping)
        : velocity_(velocity), mass_(mass), stiffness_(stiffness), damping_(damping)
    {}
    ~InterpolatingSpring() override = default;
    // this MoveInterval function is not the real implementation of the function.
    // The curve should use the curve in rosen.
    float MoveInternal(float time) override
    {
        return 0.0f;
    }
    const std::string ToString() override
    {
        std::string curveString("interpolating-spring");
        std::string comma(",");
        curveString.append(std::string("(") + std::to_string(velocity_) + comma + std::to_string(mass_) + comma +
                           std::to_string(stiffness_) + comma + std::to_string(damping_) + std::string(")"));
        return curveString;
    }

    const std::string ToSimpleString() override
    {
        std::stringstream ss;
        std::string comma(",");
        ss << "interSpring(" << std::fixed << std::setprecision(PRECISION) << velocity_
           << comma << mass_ << comma << stiffness_ << comma << damping_ << ")";
        return ss.str();
    }

    bool IsEqual(const RefPtr<Curve>& curve) const override
    {
        auto other = AceType::DynamicCast<InterpolatingSpring>(curve);
        if (!other) {
            return false;
        }
        return NearEqual(other->GetVelocity(), velocity_) && NearEqual(other->GetMass(), mass_) &&
               NearEqual(other->GetStiffness(), stiffness_) && NearEqual(other->GetDamping(), damping_);
    }

    float GetVelocity() const
    {
        return velocity_;
    }

    void UpdateVelocity(float velocity)
    {
        velocity_ = velocity;
    }

    float GetMass() const
    {
        return mass_;
    }

    float GetStiffness() const
    {
        return stiffness_;
    }

    float GetDamping() const
    {
        return damping_;
    }

    float GetMinimumAmplitudeRatio() const
    {
        return minimumAmplitudeRatio_;
    }

    void UpdateMinimumAmplitudeRatio(float minimumAmplitudeRatio)
    {
        minimumAmplitudeRatio_ = minimumAmplitudeRatio;
    }

    static constexpr float DEFAULT_INTERPOLATING_SPRING_MASS = 1.0f;
    static constexpr float DEFAULT_INTERPOLATING_SPRING_VELOCITY = 0.0f;
    static constexpr float DEFAULT_INTERPOLATING_SPRING_AMPLITUDE_RATIO = 0.00025f;

private:
    float velocity_ = 0.0f;
    float mass_ = 0.0f;
    float stiffness_ = 0.0f;
    float damping_ = 0.0f;
    float minimumAmplitudeRatio_ = DEFAULT_INTERPOLATING_SPRING_AMPLITUDE_RATIO;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_ANIMATION_CURVE_H
