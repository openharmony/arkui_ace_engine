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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/symbol_effect_peer.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AppearSymbolEffectAccessor {
void DestroyPeerImpl(Ark_AppearSymbolEffect peer)
{
    delete peer;
}
Ark_AppearSymbolEffect CtorImpl(const Opt_EffectScope* scope)
{
    std::optional<OHOS::Ace::ScopeType> optScope;
    if (scope) {
        optScope = Converter::OptConvert<OHOS::Ace::ScopeType>(*scope);
    }
    return new AppearSymbolEffectPeer(optScope);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
Opt_EffectScope GetScopeImpl(Ark_AppearSymbolEffect peer)
{
    //ToDo need check
    Opt_EffectScope effectScope { INTEROP_TAG_INT32, ARK_EFFECT_SCOPE_LAYER };
    CHECK_NULL_RETURN(peer, effectScope);
    CHECK_NULL_RETURN(peer->scope, effectScope);
    switch (peer->scope.value()) {
        case OHOS::Ace::ScopeType::WHOLE:
            effectScope.value = ARK_EFFECT_SCOPE_WHOLE;
            break;
        default:
            break;
    }
    return effectScope;
}
void SetScopeImpl(Ark_AppearSymbolEffect peer, Ark_EffectScope scope)
{
    CHECK_NULL_VOID(peer);
    peer->scope = Converter::OptConvert<OHOS::Ace::ScopeType>(scope);
}
} // namespace AppearSymbolEffectAccessor
const GENERATED_ArkUIAppearSymbolEffectAccessor* GetAppearSymbolEffectAccessor()
{
    static const GENERATED_ArkUIAppearSymbolEffectAccessor AppearSymbolEffectAccessorImpl {
        AppearSymbolEffectAccessor::DestroyPeerImpl,
        AppearSymbolEffectAccessor::CtorImpl,
        AppearSymbolEffectAccessor::GetFinalizerImpl,
        AppearSymbolEffectAccessor::GetScopeImpl,
        AppearSymbolEffectAccessor::SetScopeImpl,
    };
    return &AppearSymbolEffectAccessorImpl;
}

struct AppearSymbolEffectPeer {
    virtual ~AppearSymbolEffectPeer() = default;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
