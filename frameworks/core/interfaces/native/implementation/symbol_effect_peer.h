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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SYMBOL_EFFECT_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SYMBOL_EFFECT_PEER_H

#include <optional>
#include "core/components_ng/pattern/symbol/constants.h"

struct SymbolEffectPeer {
    OHOS::Ace::SymbolEffectType type;
    std::optional<OHOS::Ace::ScopeType> scope;
    std::optional<OHOS::Ace::CommonSubType> direction;
    std::optional<OHOS::Ace::FillStyle> fillStyle;

    SymbolEffectPeer(std::optional<OHOS::Ace::ScopeType> optScope, std::optional<OHOS::Ace::CommonSubType> optDirection)
    {
        scope = optScope;
        direction = optDirection;
    }
};

struct BounceSymbolEffectPeer : SymbolEffectPeer {
    BounceSymbolEffectPeer(
        std::optional<OHOS::Ace::ScopeType> optScope, std::optional<OHOS::Ace::CommonSubType> optDirection)
        : SymbolEffectPeer(optScope, optDirection)
    {
        type = OHOS::Ace::SymbolEffectType::BOUNCE;
    }
};

struct HierarchicalSymbolEffectPeer : SymbolEffectPeer {
    HierarchicalSymbolEffectPeer(std::optional<OHOS::Ace::FillStyle> optFillStyle)
        : SymbolEffectPeer(std::nullopt, std::nullopt)
    {
        type = OHOS::Ace::SymbolEffectType::HIERARCHICAL;
        fillStyle = optFillStyle;
    }
};

struct ScaleSymbolEffectPeer : SymbolEffectPeer {
    ScaleSymbolEffectPeer(
        std::optional<OHOS::Ace::ScopeType> optScope, std::optional<OHOS::Ace::CommonSubType> optDirection)
        : SymbolEffectPeer(optScope, optDirection)
    {
        type = OHOS::Ace::SymbolEffectType::SCALE;
    }
};

struct ReplaceSymbolEffectPeer : SymbolEffectPeer {
    ReplaceSymbolEffectPeer(std::optional<OHOS::Ace::ScopeType> optScope) : SymbolEffectPeer(optScope, std::nullopt)
    {
        type = OHOS::Ace::SymbolEffectType::REPLACE;
    }
};

struct AppearSymbolEffectPeer : SymbolEffectPeer {
    AppearSymbolEffectPeer(std::optional<OHOS::Ace::ScopeType> optScope) : SymbolEffectPeer(optScope, std::nullopt)
    {
        type = OHOS::Ace::SymbolEffectType::APPEAR;
    }
};

struct DisappearSymbolEffectPeer : SymbolEffectPeer {
    DisappearSymbolEffectPeer(std::optional<OHOS::Ace::ScopeType> optScope) : SymbolEffectPeer(optScope, std::nullopt)
    {
        type = OHOS::Ace::SymbolEffectType::DISAPPEAR;
    }
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SYMBOL_EFFECT_PEER_H
