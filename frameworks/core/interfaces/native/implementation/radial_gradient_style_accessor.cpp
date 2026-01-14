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
#include "core/interfaces/native/implementation/radial_gradient_style_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RadialGradientStyleAccessor {
void DestroyPeerImpl(Ark_RadialGradientStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_RadialGradientStyle ConstructImpl(const Ark_RadialGradientOptions* options)
{
    CHECK_NULL_RETURN(options, nullptr);
    Gradient gradient = Converter::Convert<Gradient>(*options);
    auto peerImpl = PeerUtils::CreatePeer<RadialGradientStylePeer>(gradient);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    return reinterpret_cast<Ark_RadialGradientStyle>(peerImpl);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_RadialGradientOptions GetOptionsImpl(Ark_RadialGradientStyle peer)
{
    CHECK_NULL_RETURN(peer, {});
    if (!peer->gradientOptions.has_value()) {
        return {};
    }
    return Converter::ArkValue<Ark_RadialGradientOptions>(peer->gradientOptions.value());
}
void SetOptionsImpl(Ark_RadialGradientStyle peer,
                    const Ark_RadialGradientOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(options);
    Gradient gradient = Converter::Convert<Gradient>(*options);
    peer->gradientOptions = gradient;
}
} // RadialGradientStyleAccessor
const GENERATED_ArkUIRadialGradientStyleAccessor* GetRadialGradientStyleAccessor()
{
    static const GENERATED_ArkUIRadialGradientStyleAccessor RadialGradientStyleAccessorImpl {
        RadialGradientStyleAccessor::DestroyPeerImpl,
        RadialGradientStyleAccessor::ConstructImpl,
        RadialGradientStyleAccessor::GetFinalizerImpl,
        RadialGradientStyleAccessor::GetOptionsImpl,
        RadialGradientStyleAccessor::SetOptionsImpl,
    };
    return &RadialGradientStyleAccessorImpl;
}

}
