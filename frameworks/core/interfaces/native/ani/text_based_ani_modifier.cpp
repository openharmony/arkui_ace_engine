/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "text_based_ani_modifier.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/implementation/text_modifier_peer.h"

namespace OHOS::Ace::NG {

void* ToSymbolModifierPeer(std::function<void(OHOS::Ace::WeakPtr<NG::FrameNode>)>& symbolApply,
    void* symbolModifierAni)
{
    auto symbolPeer = PeerUtils::CreatePeer<SymbolGlyphModifierPeer>();
    symbolPeer->symbolApply = symbolApply;
    symbolPeer->symbolModifierAni = symbolModifierAni;
    return reinterpret_cast<void*>(symbolPeer);
}
void* FromSymbolModifierPeer(void* ptr)
{
    auto* symbolModifierPeer = reinterpret_cast<SymbolGlyphModifierPeer*>(ptr);
    CHECK_NULL_RETURN(symbolModifierPeer, nullptr);
    auto ret = symbolModifierPeer->symbolModifierAni;
    PeerUtils::DestroyPeer(symbolModifierPeer);
    return ret;
}

void* ToTextModifierPeer(std::function<void(OHOS::Ace::WeakPtr<NG::FrameNode>)>& textApply,
    void* textModifierAni)
{
    auto textPeer = PeerUtils::CreatePeer<TextModifierPeer>();
    textPeer->textApply = textApply;
    textPeer->textModifierAni = textModifierAni;
    return reinterpret_cast<void*>(textPeer);
}
void* FromTextModifierPeer(void* ptr)
{
    auto* textModifierPeer = reinterpret_cast<TextModifierPeer*>(ptr);
    CHECK_NULL_RETURN(textModifierPeer, nullptr);
    auto ret = textModifierPeer->textModifierAni;
    PeerUtils::DestroyPeer(textModifierPeer);
    return ret;
}

const ArkUIAniTextBasedModifier* GetTextBasedAniModifier()
{
    static const ArkUIAniTextBasedModifier impl = {
        .fromSymbolModifierPeer = OHOS::Ace::NG::FromSymbolModifierPeer,
        .toSymbolModifierPeer = OHOS::Ace::NG::ToSymbolModifierPeer,
        .fromTextModifierPeer = OHOS::Ace::NG::FromTextModifierPeer,
        .toTextModifierPeer = OHOS::Ace::NG::ToTextModifierPeer
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
