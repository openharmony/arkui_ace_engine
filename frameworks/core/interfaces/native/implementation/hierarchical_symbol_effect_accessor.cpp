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
namespace HierarchicalSymbolEffectAccessor {
void DestroyPeerImpl(Ark_HierarchicalSymbolEffect peer)
{
    delete peer;
}
Ark_HierarchicalSymbolEffect CtorImpl(const Opt_EffectFillStyle* fillStyle)
{
    std::optional<OHOS::Ace::FillStyle> optFillStyle;
    if (fillStyle) {
        optFillStyle = Converter::OptConvert<OHOS::Ace::FillStyle>(*fillStyle);
    }
    return new HierarchicalSymbolEffectPeer(optFillStyle);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_EffectFillStyle GetFillStyleImpl(Ark_HierarchicalSymbolEffect peer)
{
    //ToDo need check
    Opt_EffectFillStyle effectFillStyle = { INTEROP_TAG_INT32, ARK_EFFECT_FILL_STYLE_CUMULATIVE };
    CHECK_NULL_RETURN(peer, effectFillStyle);
    CHECK_NULL_RETURN(peer->fillStyle, effectFillStyle);
    switch (peer->fillStyle.value()) {
        case OHOS::Ace::FillStyle::ITERATIVE:
            effectFillStyle.value = ARK_EFFECT_FILL_STYLE_ITERATIVE;
            break;
        default:
            break;
    }
    return effectFillStyle;
}
void SetFillStyleImpl(Ark_HierarchicalSymbolEffect peer,
                      Ark_EffectFillStyle fillStyle)
{
    CHECK_NULL_VOID(peer);
    peer->fillStyle = Converter::OptConvert<OHOS::Ace::FillStyle>(fillStyle);
}
} // HierarchicalSymbolEffectAccessor
const GENERATED_ArkUIHierarchicalSymbolEffectAccessor* GetHierarchicalSymbolEffectAccessor()
{
    static const GENERATED_ArkUIHierarchicalSymbolEffectAccessor HierarchicalSymbolEffectAccessorImpl {
        HierarchicalSymbolEffectAccessor::DestroyPeerImpl,
        HierarchicalSymbolEffectAccessor::CtorImpl,
        HierarchicalSymbolEffectAccessor::GetFinalizerImpl,
        HierarchicalSymbolEffectAccessor::GetFillStyleImpl,
        HierarchicalSymbolEffectAccessor::SetFillStyleImpl,
    };
    return &HierarchicalSymbolEffectAccessorImpl;
}

struct HierarchicalSymbolEffectPeer {
    virtual ~HierarchicalSymbolEffectPeer() = default;
};
}
