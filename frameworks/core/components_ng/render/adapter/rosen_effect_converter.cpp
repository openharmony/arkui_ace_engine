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

#include "core/components_ng/render/adapter/rosen_effect_converter.h"

#include "render_service_client/core/ui_effect/property/include/rs_ui_filter_base.h"
#include "ui/properties/ui_material_structs.h"

#include "core/components/common/properties/ui_material.h"

namespace OHOS::Ace::NG {
namespace {
#if !defined(PREVIEW)
constexpr uint32_t maskBlurParams = 0b0001u;
constexpr uint32_t maskRefactorParams = 0b0001u;
constexpr uint32_t maskSdParams = 0b0111u;
constexpr uint32_t maskEnvLightParams = 0b0111u;
constexpr uint32_t maskEdLightParams = 0b0011u;
#endif
} // namespace
std::shared_ptr<Rosen::RSNGFilterBase> RosenEffectConverter::ConvertToFrostedGlassFilter(
    const FrostedGlassParam& param, float oneVpValue)
{
#if !defined(PREVIEW)
    auto filter = std::make_shared<Rosen::RSNGFrostedGlassFilter>();
    filter->Setter<Rosen::FrostedGlassBlurParamsTag>(ConvertToVector2f(param.blurParams, oneVpValue, maskBlurParams));
    filter->Setter<Rosen::FrostedGlassWeightsEmbossTag>(ConvertToVector2f(param.weightsEmboss));
    filter->Setter<Rosen::FrostedGlassWeightsEdlTag>(ConvertToVector2f(param.weightsEdl));
    filter->Setter<Rosen::FrostedGlassBgRatesTag>(ConvertToVector2f(param.bgRates));
    filter->Setter<Rosen::FrostedGlassBgKBSTag>(ConvertToVector3f(param.bgKBS));
    filter->Setter<Rosen::FrostedGlassBgPosTag>(ConvertToVector3f(param.bgPos));
    filter->Setter<Rosen::FrostedGlassBgNegTag>(ConvertToVector3f(param.bgNeg));
    filter->Setter<Rosen::FrostedGlassBgAlphaTag>(param.bgAlpha);
    filter->Setter<Rosen::FrostedGlassRefractParamsTag>(
        ConvertToVector3f(param.refractParams, oneVpValue, maskRefactorParams));
    filter->Setter<Rosen::FrostedGlassSdParamsTag>(ConvertToVector3f(param.sdParams, oneVpValue, maskSdParams));
    filter->Setter<Rosen::FrostedGlassSdRatesTag>(ConvertToVector2f(param.sdRates));
    filter->Setter<Rosen::FrostedGlassSdKBSTag>(ConvertToVector3f(param.sdKBS));
    filter->Setter<Rosen::FrostedGlassSdPosTag>(ConvertToVector3f(param.sdPos));
    filter->Setter<Rosen::FrostedGlassSdNegTag>(ConvertToVector3f(param.sdNeg));
    filter->Setter<Rosen::FrostedGlassEnvLightParamsTag>(
        ConvertToVector3f(param.envLightParams, oneVpValue, maskEnvLightParams));
    filter->Setter<Rosen::FrostedGlassEnvLightRatesTag>(ConvertToVector2f(param.envLightRates));
    filter->Setter<Rosen::FrostedGlassEnvLightKBSTag>(ConvertToVector3f(param.envLightKBS));
    filter->Setter<Rosen::FrostedGlassEnvLightPosTag>(ConvertToVector3f(param.envLightPos));
    filter->Setter<Rosen::FrostedGlassEnvLightNegTag>(ConvertToVector3f(param.envLightNeg));
    filter->Setter<Rosen::FrostedGlassEdLightParamsTag>(
        ConvertToVector2f(param.edLightParams, oneVpValue, maskEdLightParams));
    filter->Setter<Rosen::FrostedGlassEdLightAnglesTag>(ConvertToVector2f(param.edLightAngles));
    filter->Setter<Rosen::FrostedGlassEdLightDirTag>(ConvertToVector2f(param.edLightDir));
    filter->Setter<Rosen::FrostedGlassEdLightRatesTag>(ConvertToVector2f(param.edLightRates));
    filter->Setter<Rosen::FrostedGlassEdLightKBSTag>(ConvertToVector3f(param.edLightKBS));
    filter->Setter<Rosen::FrostedGlassEdLightPosTag>(ConvertToVector3f(param.edLightPos));
    filter->Setter<Rosen::FrostedGlassEdLightNegTag>(ConvertToVector3f(param.edLightNeg));
    filter->Setter<Rosen::FrostedGlassBaseVibrancyEnabledTag>(param.baseVibrancyEnabled);
    filter->Setter<Rosen::FrostedGlassSamplingScaleTag>(param.samplingScale);
    filter->Setter<Rosen::FrostedGlassDarkModeBlurParamsTag>(
        ConvertToVector2f(param.darkModeBlurParams, oneVpValue, maskBlurParams));
    filter->Setter<Rosen::FrostedGlassDarkModeWeightsEmbossTag>(ConvertToVector2f(param.darkModeWeightsEmboss));
    filter->Setter<Rosen::FrostedGlassDarkModeBgRatesTag>(ConvertToVector2f(param.darkModeBgRates));
    filter->Setter<Rosen::FrostedGlassDarkModeBgKBSTag>(ConvertToVector3f(param.darkModeBgKBS));
    filter->Setter<Rosen::FrostedGlassDarkModeBgPosTag>(ConvertToVector3f(param.darkModeBgPos));
    filter->Setter<Rosen::FrostedGlassDarkModeBgNegTag>(ConvertToVector3f(param.darkModeBgNeg));
    return filter;
#else
    return nullptr;
#endif
}

Rosen::Vector2f RosenEffectConverter::ConvertToVector2f(const std::array<float, 2>& arr)
{
    return Rosen::Vector2f { arr[0], arr[1] };
}

Rosen::Vector3f RosenEffectConverter::ConvertToVector3f(const std::array<float, 3>& arr)
{
    return Rosen::Vector3f { arr[0], arr[1], arr[2] };
}

Rosen::Vector2f RosenEffectConverter::ConvertToVector2f(
    const std::array<float, 2>& arr, float oneVpValue, uint32_t mask)
{
    float x = (mask & 0b0001u) ? (arr[0] * oneVpValue) : arr[0];
    float y = (mask & 0b0010u) ? (arr[1] * oneVpValue) : arr[1];
    return Rosen::Vector2f { x, y };
}

Rosen::Vector3f RosenEffectConverter::ConvertToVector3f(
    const std::array<float, 3>& arr, float oneVpValue, uint32_t mask)
{
    float x = (mask & 0b0001u) ? (arr[0] * oneVpValue) : arr[0];
    float y = (mask & 0b0010u) ? (arr[1] * oneVpValue) : arr[1];
    float z = (mask & 0b0100u) ? (arr[2] * oneVpValue) : arr[2];
    return Rosen::Vector3f { x, y, z };
}
} // namespace OHOS::Ace::NG
