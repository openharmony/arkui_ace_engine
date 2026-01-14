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
#include "core/interfaces/native/implementation/color_shader_style_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ColorShaderStyleAccessor {
void DestroyPeerImpl(Ark_ColorShaderStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_ColorShaderStyle ConstructImpl(const Ark_ResourceColor* color)
{
    auto colorOpt = Converter::OptConvert<Color>(*color);
    return PeerUtils::CreatePeer<ColorShaderStylePeer>(colorOpt);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_ResourceColor GetColorImpl(Ark_ColorShaderStyle peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto stylePeer = reinterpret_cast<ColorShaderStylePeer*>(peer);
    CHECK_NULL_RETURN(stylePeer, {});
    if (stylePeer->colorValue.has_value()) {
        return Converter::ArkValue<Ark_ResourceColor>(stylePeer->colorValue.value());
    }
    return {};
}
void SetColorImpl(Ark_ColorShaderStyle peer,
                  const Ark_ResourceColor* color)
{
    CHECK_NULL_VOID(peer);
    auto stylePeer = reinterpret_cast<ColorShaderStylePeer*>(peer);
    CHECK_NULL_VOID(stylePeer);
    CHECK_NULL_VOID(color);
    auto colorOpt = Converter::OptConvert<Color>(*color);
    peer->colorValue = colorOpt;
}
} // ColorShaderStyleAccessor
const GENERATED_ArkUIColorShaderStyleAccessor* GetColorShaderStyleAccessor()
{
    static const GENERATED_ArkUIColorShaderStyleAccessor ColorShaderStyleAccessorImpl {
        ColorShaderStyleAccessor::DestroyPeerImpl,
        ColorShaderStyleAccessor::ConstructImpl,
        ColorShaderStyleAccessor::GetFinalizerImpl,
        ColorShaderStyleAccessor::GetColorImpl,
        ColorShaderStyleAccessor::SetColorImpl,
    };
    return &ColorShaderStyleAccessorImpl;
}
}
