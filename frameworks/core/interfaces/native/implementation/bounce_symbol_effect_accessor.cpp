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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BounceSymbolEffectAccessor {
void DestroyPeerImpl(Ark_BounceSymbolEffect peer)
{
}
Ark_BounceSymbolEffect CtorImpl(const Opt_EffectScope* scope,
                                const Opt_EffectDirection* direction)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EffectScope GetScopeImpl(Ark_BounceSymbolEffect peer)
{
    return {};
}
void SetScopeImpl(Ark_BounceSymbolEffect peer,
                  Ark_EffectScope scope)
{
}
Ark_EffectDirection GetDirectionImpl(Ark_BounceSymbolEffect peer)
{
    return {};
}
void SetDirectionImpl(Ark_BounceSymbolEffect peer,
                      Ark_EffectDirection direction)
{
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
