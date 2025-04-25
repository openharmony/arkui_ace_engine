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
namespace DisappearSymbolEffectAccessor {
void DestroyPeerImpl(Ark_DisappearSymbolEffect peer)
{
    delete peer;
}
Ark_DisappearSymbolEffect CtorImpl(const Opt_EffectScope* scope)
{
    std::optional<OHOS::Ace::ScopeType> optScope;
    if (scope) {
        optScope = Converter::OptConvert<OHOS::Ace::ScopeType>(*scope);
    }
    return new DisappearSymbolEffectPeer(optScope);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_EffectScope GetScopeImpl(Ark_DisappearSymbolEffect peer)
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
void SetScopeImpl(Ark_DisappearSymbolEffect peer,
                  Ark_EffectScope scope)
{
    CHECK_NULL_VOID(peer);
    peer->scope = Converter::OptConvert<OHOS::Ace::ScopeType>(scope);
}
} // DisappearSymbolEffectAccessor
const GENERATED_ArkUIDisappearSymbolEffectAccessor* GetDisappearSymbolEffectAccessor()
{
    static const GENERATED_ArkUIDisappearSymbolEffectAccessor DisappearSymbolEffectAccessorImpl {
        DisappearSymbolEffectAccessor::DestroyPeerImpl,
        DisappearSymbolEffectAccessor::CtorImpl,
        DisappearSymbolEffectAccessor::GetFinalizerImpl,
        DisappearSymbolEffectAccessor::GetScopeImpl,
        DisappearSymbolEffectAccessor::SetScopeImpl,
    };
    return &DisappearSymbolEffectAccessorImpl;
}

struct DisappearSymbolEffectPeer {
    virtual ~DisappearSymbolEffectPeer() = default;
};
}
