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
namespace ScaleSymbolEffectAccessor {
void DestroyPeerImpl(ScaleSymbolEffectPeer* peer)
{
}
Ark_ScaleSymbolEffect CtorImpl(const Opt_EffectScope* scope,
                               const Opt_EffectDirection* direction)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetScopeImpl(ScaleSymbolEffectPeer* peer)
{
    return {};
}
void SetScopeImpl(ScaleSymbolEffectPeer* peer,
                  Ark_EffectScope scope)
{
}
Ark_NativePointer GetDirectionImpl(ScaleSymbolEffectPeer* peer)
{
    return {};
}
void SetDirectionImpl(ScaleSymbolEffectPeer* peer,
                      Ark_EffectDirection direction)
{
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
