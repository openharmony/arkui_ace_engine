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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRADIENT_ARITHMETIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRADIENT_ARITHMETIC_H

#include "core/components_ng/animation/animatable_arithmetic.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace::NG {
class GradientArithmetic : public AnimatableArithmetic<GradientArithmetic> {
public:
    GradientArithmetic() = default;
    explicit GradientArithmetic(const Gradient& gradient) : gradientValue_(gradient) {}

    GradientArithmetic Add(const GradientArithmetic& value) const override
    {
        Gradient gradient;
        auto srcColors = gradientValue_.GetColors();
        auto destColors = value.GetGradient().GetColors();
        size_t srcColorsLength = srcColors.size();
        size_t destColorsLength = destColors.size();
        if (srcColorsLength >= destColorsLength) {
            size_t i;
            for (i = 0; i < destColorsLength; i++) {
                GradientColor gradientColor;
                gradientColor.SetLinearColor(srcColors[i].GetLinearColor() + destColors[i].GetLinearColor());
                gradientColor.SetDimension(destColors[i].GetDimension());
                gradient.AddColor(gradientColor);
            }

            for (; i < srcColorsLength; i++) {
                gradient.AddColor(srcColors[i]);
            }
        } else {
            for (size_t i = 0; i < srcColorsLength; i++) {
                GradientColor gradientColor;
                gradientColor.SetLinearColor(srcColors[i].GetLinearColor() + destColors[i].GetLinearColor());
                gradientColor.SetDimension(destColors[i].GetDimension());
                gradient.AddColor(gradientColor);
            }
        }
        return GradientArithmetic(gradient);
    }

    GradientArithmetic Minus(const GradientArithmetic& value) const override
    {
        Gradient gradient;
        auto srcColors = gradientValue_.GetColors();
        auto destColors = value.GetGradient().GetColors();
        size_t srcColorsLength = srcColors.size();
        size_t destColorsLength = destColors.size();
        if (srcColorsLength >= destColorsLength) {
            size_t i;
            for (i = 0; i < destColorsLength; i++) {
                GradientColor gradientColor;
                gradientColor.SetLinearColor(srcColors[i].GetLinearColor() - destColors[i].GetLinearColor());
                gradientColor.SetDimension(destColors[i].GetDimension());
                gradient.AddColor(gradientColor);
            }
            for (; i < srcColorsLength; i++) {
                gradient.AddColor(srcColors[i]);
            }
        } else {
            size_t i;
            for (i = 0; i < srcColorsLength; i++) {
                GradientColor gradientColor;
                gradientColor.SetLinearColor(srcColors[i].GetLinearColor() - destColors[i].GetLinearColor());
                gradientColor.SetDimension(destColors[i].GetDimension());
                gradient.AddColor(gradientColor);
            }
        }
        return GradientArithmetic(gradient);
    }

    GradientArithmetic Multiply(const float scale) const override
    {
        Gradient gradient;
        auto srcColors = gradientValue_.GetColors();
        for (size_t i = 0; i < srcColors.size(); i++) {
            GradientColor gradientColor;
            gradientColor.SetLinearColor(srcColors[i].GetLinearColor() * scale);
            gradientColor.SetDimension(srcColors[i].GetDimension());
            gradient.AddColor(gradientColor);
        }
        return GradientArithmetic(gradient);
    }

    bool IsEqual(const GradientArithmetic& value) const override
    {
        return gradientValue_ == value.GetGradient();
    }

    Gradient GetGradient() const
    {
        return gradientValue_;
    }

private:
    Gradient gradientValue_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRADIENT_ARITHMETIC_H
