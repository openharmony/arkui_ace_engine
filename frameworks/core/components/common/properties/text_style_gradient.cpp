/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 
#include "core/components/common/properties/text_style_gradient.h"
 
namespace OHOS::Ace {
 
void OptGradient::SetGradient(const std::optional<Gradient>& gradient)
{
    gradient_ = gradient;
}
 
std::optional<Gradient>& OptGradient::GetGradient()
{
    return gradient_;
}
 
void OptGradient::ResetGradient()
{
    gradient_.reset();
}
 
void OptNGGradient::SetGradient(const std::optional<NG::Gradient>& gradient)
{
    gradient_ = gradient;
}
 
std::optional<NG::Gradient>& OptNGGradient::GetGradient()
{
    return gradient_;
}
 
void OptNGGradient::ResetGradient()
{
    gradient_.reset();
}
namespace GradientConvert {
    NG::Gradient ConvertNGGradient(const Gradient& gradient)
    {
        NG::Gradient retGradient;
        retGradient.CreateGradientWithType(static_cast<NG::GradientType>(gradient.GetType()));
        if (gradient.GetType() == GradientType::LINEAR) {
            auto angle = gradient.GetLinearGradient().angle;
            if (angle.has_value()) {
                retGradient.GetLinearGradient()->angle = CalcDimension(angle.value());
            }
            auto linearX = gradient.GetLinearGradient().linearX;
            if (linearX.has_value()) {
                retGradient.GetLinearGradient()->linearX = static_cast<NG::GradientDirection>(linearX.value());
            }
            auto linearY = gradient.GetLinearGradient().linearY;
            if (linearY.has_value()) {
                retGradient.GetLinearGradient()->linearY = static_cast<NG::GradientDirection>(linearY.value());
            }
        }
        if (gradient.GetType() == GradientType::RADIAL) {
            auto radialCenterX = gradient.GetRadialGradient().radialCenterX;
            if (radialCenterX.has_value()) {
                retGradient.GetRadialGradient()->radialCenterX = CalcDimension(radialCenterX.value());
            }
            auto radialCenterY = gradient.GetRadialGradient().radialCenterY;
            if (radialCenterY.has_value()) {
                retGradient.GetRadialGradient()->radialCenterY = CalcDimension(radialCenterY.value());
            }
            auto radialVerticalSize = gradient.GetRadialGradient().radialVerticalSize;
            if (radialVerticalSize.has_value()) {
                retGradient.GetRadialGradient()->radialVerticalSize = CalcDimension(radialVerticalSize.value());
            }
            auto radialHorizontalSize = gradient.GetRadialGradient().radialHorizontalSize;
            if (radialHorizontalSize.has_value()) {
                retGradient.GetRadialGradient()->radialHorizontalSize = CalcDimension(radialHorizontalSize.value());
            }
        }
        retGradient.SetRepeat(gradient.GetRepeat());
        const auto& colorStops = gradient.GetColors();
        for (const auto& item : colorStops) {
            NG::GradientColor gradientColor;
            gradientColor.SetColor(item.GetColor());
            gradientColor.SetHasValue(item.GetHasValue());
            gradientColor.SetDimension(item.GetDimension());
            retGradient.AddColor(gradientColor);
        }
        return retGradient;
    }
 
    AnimatableDimension ToAnimatableDimension(const Dimension& dimension)
    {
        AnimatableDimension result(dimension);
        return result;
    }
 
    std::optional<Gradient> ConvertGradient(const NG::Gradient& gradient)
    {
        Gradient retGradient;
        retGradient.SetType(static_cast<GradientType>(gradient.GetType()));
        if (retGradient.GetType() == GradientType::LINEAR) {
            CHECK_NULL_RETURN(gradient.GetLinearGradient(), std::nullopt);
            auto angle = gradient.GetLinearGradient()->angle;
            if (angle.has_value()) {
                retGradient.GetLinearGradient().angle = ToAnimatableDimension(angle.value());
            }
            auto linearX = gradient.GetLinearGradient()->linearX;
            if (linearX.has_value()) {
                retGradient.GetLinearGradient().linearX = static_cast<GradientDirection>(linearX.value());
            }
            auto linearY = gradient.GetLinearGradient()->linearY;
            if (linearY.has_value()) {
                retGradient.GetLinearGradient().linearY = static_cast<GradientDirection>(linearY.value());
            }
        }
        if (retGradient.GetType() == GradientType::RADIAL) {
            CHECK_NULL_RETURN(gradient.GetRadialGradient(), std::nullopt);
            auto radialCenterX = gradient.GetRadialGradient()->radialCenterX;
            if (radialCenterX.has_value()) {
                retGradient.GetRadialGradient().radialCenterX = ToAnimatableDimension(radialCenterX.value());
            }
            auto radialCenterY = gradient.GetRadialGradient()->radialCenterY;
            if (radialCenterY.has_value()) {
                retGradient.GetRadialGradient().radialCenterY = ToAnimatableDimension(radialCenterY.value());
            }
            auto radialVerticalSize = gradient.GetRadialGradient()->radialVerticalSize;
            if (radialVerticalSize.has_value()) {
                retGradient.GetRadialGradient().radialVerticalSize = ToAnimatableDimension(radialVerticalSize.value());
            }
            auto radialHorizontalSize = gradient.GetRadialGradient()->radialHorizontalSize;
            if (radialHorizontalSize.has_value()) {
                retGradient.GetRadialGradient().radialHorizontalSize =
                    ToAnimatableDimension(radialHorizontalSize.value());
            }
        }
        retGradient.SetRepeat(gradient.GetRepeat());
        const auto& colorStops = gradient.GetColors();
        for (const auto& item : colorStops) {
            GradientColor gradientColor;
            gradientColor.SetColor(item.GetColor());
            gradientColor.SetHasValue(item.GetHasValue());
            gradientColor.SetDimension(item.GetDimension());
            retGradient.AddColor(gradientColor);
        }
        return retGradient;
    }
 
    struct PairHash {
        template <typename T, typename U>
        size_t operator() (const std::pair<T, U>& pair) const
        {
            size_t hash1 = std::hash<T>{}(pair.first);
            size_t hash2 = std::hash<U>{}(pair.second);
            return hash1 ^ (hash2 << 1);
        }
    };
 
    std::optional<NG::GradientDirection> ParseGradientDirection(const NG::Gradient& gradient)
    {
        CHECK_NULL_RETURN(gradient.GetLinearGradient(), std::nullopt);
        auto linearX = gradient.GetLinearGradient()->linearX;
        auto linearY = gradient.GetLinearGradient()->linearY;
        CHECK_NULL_RETURN(linearX.has_value() || linearY.has_value(), std::nullopt);
        std::unordered_map<std::pair<NG::GradientDirection, NG::GradientDirection>, NG::GradientDirection, PairHash>
            directionMap {
                {{NG::GradientDirection::LEFT, NG::GradientDirection::TOP}, NG::GradientDirection::LEFT_TOP},
                {{NG::GradientDirection::LEFT, NG::GradientDirection::BOTTOM}, NG::GradientDirection::LEFT_BOTTOM},
                {{NG::GradientDirection::RIGHT, NG::GradientDirection::TOP}, NG::GradientDirection::RIGHT_TOP},
                {{NG::GradientDirection::RIGHT, NG::GradientDirection::BOTTOM}, NG::GradientDirection::RIGHT_BOTTOM},
                {{NG::GradientDirection::LEFT, NG::GradientDirection::LEFT}, NG::GradientDirection::LEFT},
                {{NG::GradientDirection::RIGHT, NG::GradientDirection::RIGHT}, NG::GradientDirection::RIGHT},
                {{NG::GradientDirection::TOP, NG::GradientDirection::TOP}, NG::GradientDirection::TOP},
                {{NG::GradientDirection::BOTTOM, NG::GradientDirection::BOTTOM}, NG::GradientDirection::BOTTOM},
            };
        auto keyX = linearX.value_or(NG::GradientDirection::LEFT);
        auto keyY = linearY.value_or(NG::GradientDirection::LEFT);
        if (!linearY.has_value()) {
            keyY = linearX.value();
        }
        if (!linearX.has_value()) {
            keyX = linearY.value();
        }
        auto key = std::make_pair(keyX, keyY);
        auto it = directionMap.find(key);
        if (it != directionMap.end()) {
            return it->second;
        } else {
            return std::nullopt;
        }
    }
 
    void SetGradientDirection(NG::Gradient& newGradient, const NG::GradientDirection& direction)
    {
        switch (direction) {
            case NG::GradientDirection::LEFT:
                newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
                break;
            case NG::GradientDirection::RIGHT:
                newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
                break;
            case NG::GradientDirection::TOP:
                newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
                break;
            case NG::GradientDirection::BOTTOM:
                newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
                break;
            case NG::GradientDirection::LEFT_TOP:
                newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
                newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
                break;
            case NG::GradientDirection::LEFT_BOTTOM:
                newGradient.GetLinearGradient()->linearX = NG::GradientDirection::LEFT;
                newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
                break;
            case NG::GradientDirection::RIGHT_TOP:
                newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
                newGradient.GetLinearGradient()->linearY = NG::GradientDirection::TOP;
                break;
            case NG::GradientDirection::RIGHT_BOTTOM:
                newGradient.GetLinearGradient()->linearX = NG::GradientDirection::RIGHT;
                newGradient.GetLinearGradient()->linearY = NG::GradientDirection::BOTTOM;
                break;
            default:
                break;
        }
    }
 
    std::optional<NG::Gradient> ToNGGradient(const std::optional<Gradient>& gradient)
    {
        CHECK_NULL_RETURN(gradient.has_value(), std::nullopt);
        std::optional<NG::Gradient> result = ConvertNGGradient(gradient.value());
        return result;
    }
 
    std::optional<Gradient> ToGradient(const std::optional<NG::Gradient>& gradient)
    {
        CHECK_NULL_RETURN(gradient.has_value(), std::nullopt);
        std::optional<Gradient> result = ConvertGradient(gradient.value());
        return result;
    }
 
    RefPtr<OptGradient> ToOptGradient(const NG::Gradient& src)
    {
        auto opt = AceType::MakeRefPtr<OptGradient>();
        opt->SetGradient(ConvertGradient(src));
        return opt;
    }
 
    RefPtr<OptGradient> ToOptGradient(const Gradient& src)
    {
        auto opt = AceType::MakeRefPtr<OptGradient>();
        std::optional<Gradient> gradient = src;
        opt->SetGradient(gradient);
        return opt;
    }
 
    RefPtr<OptGradient> ToOptGradient(const std::optional<NG::Gradient>& src)
    {
        auto opt = AceType::MakeRefPtr<OptGradient>();
        if (src.has_value()) {
            opt->SetGradient(ConvertGradient(src.value()));
        }
        return opt;
    }
 
    RefPtr<OptGradient> ToOptGradient(const std::optional<Gradient>& gradient)
    {
        auto opt = AceType::MakeRefPtr<OptGradient>();
        opt->SetGradient(gradient);
        return opt;
    }
 
    RefPtr<OptNGGradient> ToOptNGGradient(const NG::Gradient& src)
    {
        auto opt = AceType::MakeRefPtr<OptNGGradient>();
        std::optional<NG::Gradient> gradient = src;
        opt->SetGradient(gradient);
        return opt;
    }
 
    RefPtr<OptNGGradient> ToOptNGGradient(const Gradient& src)
    {
        auto opt = AceType::MakeRefPtr<OptNGGradient>();
        std::optional<NG::Gradient> gradient = ConvertNGGradient(src);
        opt->SetGradient(gradient);
        return opt;
    }
 
    RefPtr<OptNGGradient> ToOptNGGradient(const std::optional<NG::Gradient>& gradient)
    {
        auto opt = AceType::MakeRefPtr<OptNGGradient>();
        opt->SetGradient(gradient);
        return opt;
    }
 
    RefPtr<OptNGGradient> ToOptNGGradient(const std::optional<Gradient>& src)
    {
        auto opt = AceType::MakeRefPtr<OptNGGradient>();
        if (src.has_value()) {
            std::optional<NG::Gradient> gradient = ConvertNGGradient(src.value());
            opt->SetGradient(gradient);
        }
        return opt;
    }
} // namespace OHOS::Ace::GradientConvert
} // namespace OHOS::Ace