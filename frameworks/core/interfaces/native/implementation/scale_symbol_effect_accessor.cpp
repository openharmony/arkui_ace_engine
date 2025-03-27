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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "scale_symbol_effect_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScaleSymbolEffectAccessor {
void DestroyPeerImpl(Ark_ScaleSymbolEffect peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
Ark_ScaleSymbolEffect CtorImpl(const Opt_EffectScope* scope,
                               const Opt_EffectDirection* direction)
{
    auto convScore = Converter::Convert<std::optional<OHOS::Ace::ScopeType>>(*scope);
    auto convDirection = Converter::Convert<std::optional<OHOS::Ace::CommonSubType>>(*direction);
    auto peer = new ScaleSymbolEffectPeer();
    peer->effectOptions.SetEffectType(OHOS::Ace::SymbolEffectType::SCALE);
    peer->effectOptions.SetScopeType(convScore.value());
    peer->effectOptions.SetCommonSubType(convDirection.value());
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EffectScope GetScopeImpl(Ark_ScaleSymbolEffect peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_EffectScope>(ARK_EFFECT_SCOPE_LAYER));
    auto optValue = peer->effectOptions.GetScopeType();
    CHECK_NULL_RETURN(optValue, Converter::ArkValue<Ark_EffectScope>(ARK_EFFECT_SCOPE_LAYER));
    return Converter::ArkValue<Ark_EffectScope>(optValue.value());
}
void SetScopeImpl(Ark_ScaleSymbolEffect peer,
                  Ark_EffectScope scope)
{
    CHECK_NULL_VOID(peer);
    auto scopeConv = Converter::Convert<std::optional<OHOS::Ace::ScopeType>>(scope);
    if (scopeConv) {
        peer->effectOptions.SetScopeType(scopeConv.value());
    } else {
        peer->effectOptions.SetScopeType(OHOS::Ace::ScopeType::LAYER);
    }
}
Ark_EffectDirection GetDirectionImpl(Ark_ScaleSymbolEffect peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_EffectDirection>(ARK_EFFECT_DIRECTION_DOWN));
    auto optValue = peer->effectOptions.GetCommonSubType();
    CHECK_NULL_RETURN(optValue, Converter::ArkValue<Ark_EffectDirection>(ARK_EFFECT_DIRECTION_DOWN));
    return Converter::ArkValue<Ark_EffectDirection>(optValue.value());
}
void SetDirectionImpl(Ark_ScaleSymbolEffect peer,
                      Ark_EffectDirection direction)
{
    CHECK_NULL_VOID(peer);
    auto directionConv = Converter::Convert<std::optional<OHOS::Ace::CommonSubType>>(direction);
    if (directionConv) {
        peer->effectOptions.SetCommonSubType(directionConv.value());
    } else {
        peer->effectOptions.SetCommonSubType(OHOS::Ace::CommonSubType::DOWN);
    }
}
} // ScaleSymbolEffectAccessor
const GENERATED_ArkUIScaleSymbolEffectAccessor* GetScaleSymbolEffectAccessor()
{
    static const GENERATED_ArkUIScaleSymbolEffectAccessor ScaleSymbolEffectAccessorImpl {
        ScaleSymbolEffectAccessor::DestroyPeerImpl,
        ScaleSymbolEffectAccessor::CtorImpl,
        ScaleSymbolEffectAccessor::GetFinalizerImpl,
        ScaleSymbolEffectAccessor::GetScopeImpl,
        ScaleSymbolEffectAccessor::SetScopeImpl,
        ScaleSymbolEffectAccessor::GetDirectionImpl,
        ScaleSymbolEffectAccessor::SetDirectionImpl,
    };
    return &ScaleSymbolEffectAccessorImpl;
}

struct ScaleSymbolEffectPeer {
    virtual ~ScaleSymbolEffectPeer() = default;
};
}
