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
#include "tab_bar_symbol_peer_impl.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TabBarSymbolAccessor {
void DestroyPeerImpl(Ark_TabBarSymbol peer)
{
    auto peerImpl = reinterpret_cast<TabBarSymbolPeerImpl *>(peer);
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
Ark_TabBarSymbol ConstructImpl()
{
    auto peerImpl = Referenced::MakeRefPtr<TabBarSymbolPeerImpl>();
    peerImpl->IncRefCount();
    return reinterpret_cast<TabBarSymbolPeer *>(Referenced::RawPtr(peerImpl));
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_SymbolGlyphModifier GetNormalImpl(Ark_TabBarSymbol peer)
{
    auto peerImpl = reinterpret_cast<TabBarSymbolPeerImpl *>(peer);
    CHECK_NULL_RETURN(peerImpl, nullptr);
    auto glyphModifier = peerImpl->GetNormal().Upgrade();
    CHECK_NULL_RETURN(glyphModifier, nullptr);
    return reinterpret_cast<SymbolGlyphModifierPeer *>(Referenced::RawPtr(glyphModifier));
}
void SetNormalImpl(Ark_TabBarSymbol peer,
                   Ark_SymbolGlyphModifier normal)
{
    auto peerImpl = reinterpret_cast<TabBarSymbolPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto glyphModifier = reinterpret_cast<SymbolGlyphModifierPeer *>(normal);
    CHECK_NULL_VOID(glyphModifier);
    peerImpl->SetNormal(AceType::WeakClaim(glyphModifier));
}
Opt_SymbolGlyphModifier GetSelectedImpl(Ark_TabBarSymbol peer)
{
    auto optModifier = Converter::ArkValue<Opt_SymbolGlyphModifier>();
    auto peerImpl = reinterpret_cast<TabBarSymbolPeerImpl*>(peer);
    CHECK_NULL_RETURN(peerImpl, optModifier);
    auto glyphModifier = peerImpl->GetSelected().Upgrade();
    CHECK_NULL_RETURN(glyphModifier, optModifier);
    auto glyphModifierValue = reinterpret_cast<SymbolGlyphModifierPeer*>(Referenced::RawPtr(glyphModifier));
    return Converter::ArkValue<Opt_SymbolGlyphModifier>(glyphModifierValue);
}
void SetSelectedImpl(Ark_TabBarSymbol peer,
                     const Opt_SymbolGlyphModifier* selected)
{
    auto peerImpl = reinterpret_cast<TabBarSymbolPeerImpl*>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto glyphModifierOpt = Converter::OptConvertPtr<Ark_SymbolGlyphModifier>(selected);
    if (glyphModifierOpt) {
        auto glyphModifier = reinterpret_cast<SymbolGlyphModifierPeer*>(glyphModifierOpt.value());
        CHECK_NULL_VOID(glyphModifier);
        peerImpl->SetSelected(AceType::WeakClaim(glyphModifier));
    } else {
        peerImpl->SetSelected(nullptr);
    }
}
} // TabBarSymbolAccessor
const GENERATED_ArkUITabBarSymbolAccessor* GetTabBarSymbolAccessor()
{
    static const GENERATED_ArkUITabBarSymbolAccessor TabBarSymbolAccessorImpl {
        TabBarSymbolAccessor::DestroyPeerImpl,
        TabBarSymbolAccessor::ConstructImpl,
        TabBarSymbolAccessor::GetFinalizerImpl,
        TabBarSymbolAccessor::GetNormalImpl,
        TabBarSymbolAccessor::SetNormalImpl,
        TabBarSymbolAccessor::GetSelectedImpl,
        TabBarSymbolAccessor::SetSelectedImpl,
    };
    return &TabBarSymbolAccessorImpl;
}

}
