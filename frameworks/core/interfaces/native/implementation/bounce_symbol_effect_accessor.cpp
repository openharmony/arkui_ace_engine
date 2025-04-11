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
#include "core/interfaces/native/implementation/symbol_effect_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BounceSymbolEffectAccessor {
void DestroyPeerImpl(Ark_BounceSymbolEffect peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_BounceSymbolEffect CtorImpl(const Opt_EffectScope* scope,
                                const Opt_EffectDirection* direction)
{
    std::optional<OHOS::Ace::ScopeType> optScope;
    std::optional<OHOS::Ace::CommonSubType> optDirection;
    if (scope) {
        optScope = Converter::OptConvert<OHOS::Ace::ScopeType>(*scope);
    }
    if (direction) {
        optDirection = Converter::OptConvert<OHOS::Ace::CommonSubType>(*direction);
    }
    return PeerUtils::CreatePeer<BounceSymbolEffectPeer>(optScope, optDirection);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_EffectScope GetScopeImpl(Ark_BounceSymbolEffect peer)
{
    auto invalid = Converter::ArkValue<Opt_EffectScope>();
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Opt_EffectScope>(peer->scope);
}
void SetScopeImpl(Ark_BounceSymbolEffect peer,
                  Ark_EffectScope scope)
{
    CHECK_NULL_VOID(peer);
    peer->scope = Converter::OptConvert<OHOS::Ace::ScopeType>(scope);
}
Opt_EffectDirection GetDirectionImpl(Ark_BounceSymbolEffect peer)
{
    auto invalid = Converter::ArkValue<Opt_EffectDirection>();
    CHECK_NULL_RETURN(peer, invalid);
    return Converter::ArkValue<Opt_EffectDirection>(peer->direction);
}
void SetDirectionImpl(Ark_BounceSymbolEffect peer,
                      Ark_EffectDirection direction)
{
    CHECK_NULL_VOID(peer);
    peer->direction = Converter::OptConvert<OHOS::Ace::CommonSubType>(direction);
}
} // BounceSymbolEffectAccessor
const GENERATED_ArkUIBounceSymbolEffectAccessor* GetBounceSymbolEffectAccessor()
{
    static const GENERATED_ArkUIBounceSymbolEffectAccessor BounceSymbolEffectAccessorImpl {
        BounceSymbolEffectAccessor::DestroyPeerImpl,
        BounceSymbolEffectAccessor::CtorImpl,
        BounceSymbolEffectAccessor::GetFinalizerImpl,
        BounceSymbolEffectAccessor::GetScopeImpl,
        BounceSymbolEffectAccessor::SetScopeImpl,
        BounceSymbolEffectAccessor::GetDirectionImpl,
        BounceSymbolEffectAccessor::SetDirectionImpl,
    };
    return &BounceSymbolEffectAccessorImpl;
}
}
