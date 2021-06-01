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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_EVALUATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_EVALUATOR_H

#include <cmath>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {

template<typename T>
class Evaluator : public AceType {
public:
    virtual T Evaluate(const T& begin, const T& end, float fraction) = 0;
};

template<typename T>
class LinearEvaluator : public Evaluator<T> {
public:
    LinearEvaluator() = default;

    ~LinearEvaluator() override = default;

    T Evaluate(const T& begin, const T& end, float fraction) override
    {
        return begin + (end - begin) * fraction;
    }
};

class ColorEvaluator : public Evaluator<Color> {
public:
    ColorEvaluator() = default;

    ~ColorEvaluator() override = default;

    Color Evaluate(const Color& begin, const Color& end, float fraction) override
    {
        // convert begin color from ARGB to linear
        double beginLinearRed = 0.0;
        double beginLinearGreen = 0.0;
        double beginLinearBlue = 0.0;
        double beginAlpha = begin.GetAlpha();
        ConvertGammaToLinear(begin, beginLinearRed, beginLinearGreen, beginLinearBlue);

        // convert end color from ARGB to linear
        double endLinearRed = 0.0;
        double endLinearGreen = 0.0;
        double endLinearBlue = 0.0;
        double endAlpha = end.GetAlpha();
        ConvertGammaToLinear(end, endLinearRed, endLinearGreen, endLinearBlue);

        // evaluate the result
        double linearRed = beginLinearRed + (endLinearRed - beginLinearRed) * fraction;
        double linearGreen = beginLinearGreen + (endLinearGreen - beginLinearGreen) * fraction;
        double linearBlue = beginLinearBlue + (endLinearBlue - beginLinearBlue) * fraction;
        double alpha = beginAlpha + (endAlpha - beginAlpha) * fraction;

        return ConvertLinearToGamma(alpha, linearRed, linearGreen, linearBlue);
    }

private:
    const double GAMMA_FACTOR = 2.2;

    double ConvertGammaToLinear(uint8_t value)
    {
        return pow(value, GAMMA_FACTOR);
    }

    void ConvertGammaToLinear(const Color& gammaColor, double& linearRed, double& linearGreen, double& linearBlue)
    {
        linearRed = ConvertGammaToLinear(gammaColor.GetRed());
        linearGreen = ConvertGammaToLinear(gammaColor.GetGreen());
        linearBlue = ConvertGammaToLinear(gammaColor.GetBlue());
    }

    uint8_t ConvertLinearToGamma(double value)
    {
        return std::clamp(static_cast<int32_t>(std::pow(value, 1.0 / GAMMA_FACTOR)), 0, UINT8_MAX);
    }

    Color ConvertLinearToGamma(double alpha, double linearRed, double linearGreen, double linearBlue)
    {
        uint8_t gammaRed = ConvertLinearToGamma(linearRed);
        uint8_t gammaGreen = ConvertLinearToGamma(linearGreen);
        uint8_t gammaBlue = ConvertLinearToGamma(linearBlue);
        uint8_t gammaAlpha = std::clamp(static_cast<int32_t>(alpha), 0, UINT8_MAX);

        return Color::FromARGB(gammaAlpha, gammaRed, gammaGreen, gammaBlue);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ANIMATION_EVALUATOR_H
