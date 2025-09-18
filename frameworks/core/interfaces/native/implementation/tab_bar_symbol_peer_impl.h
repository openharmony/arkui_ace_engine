/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TAB_BAR_SYMBOL_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TAB_BAR_SYMBOL_PEER_IMPL_H

#include <optional>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "symbol_glyph_modifier_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class TabBarSymbolPeerImpl : public Referenced {
public:
    TabBarSymbolPeerImpl() = default;

    void SetNormal(OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::SymbolGlyphModifierPeerImpl> normal)
    {
        normal_ = normal;
    }

    OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::SymbolGlyphModifierPeerImpl> GetNormal()
    {
        return normal_;
    }

    void SetSelected(OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::SymbolGlyphModifierPeerImpl> selected)
    {
        selected_ = selected;
    }

    OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::SymbolGlyphModifierPeerImpl> GetSelected()
    {
        return selected_;
    }

private:
    OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::SymbolGlyphModifierPeerImpl> normal_;
    OHOS::Ace::WeakPtr<OHOS::Ace::NG::GeneratedModifier::SymbolGlyphModifierPeerImpl> selected_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct TabBarSymbolPeer : public OHOS::Ace::NG::GeneratedModifier::TabBarSymbolPeerImpl {};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TAB_BAR_SYMBOL_PEER_IMPL_H
