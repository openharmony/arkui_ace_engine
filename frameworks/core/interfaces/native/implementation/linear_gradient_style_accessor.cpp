/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/linear_gradient_style_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace LinearGradientStyleAccessor {
void DestroyPeerImpl(Ark_LinearGradientStyle peer)
{
    auto peerImpl = reinterpret_cast<LinearGradientStylePeer*>(peer);
}
Ark_LinearGradientStyle ConstructImpl(const Ark_LinearGradientOptions* options)
{
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    auto repeat = Converter::OptConvert<bool>(options->repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto linear = gradient.GetLinearGradient();
    std::optional<float> degreeOpt;
    constexpr float DEFAULT_ANGLE = 180.0f;
    Converter::ConvertAngleWithDefault(options->angle, degreeOpt, DEFAULT_ANGLE);
    if (degreeOpt) {
        linear->angle = CalcDimension(degreeOpt.value(), DimensionUnit::PX);
        degreeOpt.reset();
    }
    auto direction = Converter::OptConvert<GradientDirection>(options->direction);
    if (direction) {
        Converter::AssignLinearGradientDirection(linear, direction.value());
    }
    Converter::AssignGradientColors(&gradient, &options->colors);
    auto peerImpl = PeerUtils::CreatePeer<LinearGradientStylePeer>(gradient);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    return reinterpret_cast<Ark_LinearGradientStyle>(peerImpl);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LinearGradientOptions GetOptionsImpl(Ark_LinearGradientStyle peer)
{
    CHECK_NULL_RETURN(peer, {});
    if (!peer->gradientOptions.has_value()) {
        return {};
    }
    return Converter::ArkValue<Ark_LinearGradientOptions>(peer->gradientOptions.value());
}
void SetOptionsImpl(Ark_LinearGradientStyle peer,
                    const Ark_LinearGradientOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(options);
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    auto repeat = Converter::OptConvert<bool>(options->repeating);
    if (repeat) {
        gradient.SetRepeat(repeat.value());
    }
    auto linear = gradient.GetLinearGradient();
    std::optional<float> degreeOpt;
    constexpr float DEFAULT_ANGLE = 180.0f;
    Converter::ConvertAngleWithDefault(options->angle, degreeOpt, DEFAULT_ANGLE);
    if (degreeOpt) {
        linear->angle = CalcDimension(degreeOpt.value(), DimensionUnit::PX);
        degreeOpt.reset();
    }
    auto direction = Converter::OptConvert<GradientDirection>(options->direction);
    if (direction) {
        Converter::AssignLinearGradientDirection(linear, direction.value());
    }
    Converter::AssignGradientColors(&gradient, &options->colors);
    peer->gradientOptions = gradient;
}
} // LinearGradientStyleAccessor
const GENERATED_ArkUILinearGradientStyleAccessor* GetLinearGradientStyleAccessor()
{
    static const GENERATED_ArkUILinearGradientStyleAccessor LinearGradientStyleAccessorImpl {
        LinearGradientStyleAccessor::DestroyPeerImpl,
        LinearGradientStyleAccessor::ConstructImpl,
        LinearGradientStyleAccessor::GetFinalizerImpl,
        LinearGradientStyleAccessor::GetOptionsImpl,
        LinearGradientStyleAccessor::SetOptionsImpl,
    };
    return &LinearGradientStyleAccessorImpl;
}

}
