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
#include "core/interfaces/native/utility/peer_utils.h"

struct SymbolEffectPeer {
    using Type = OHOS::Ace::SymbolEffectType;
    using Scope = std::optional<OHOS::Ace::ScopeType>;
    using Direction = std::optional<OHOS::Ace::CommonSubType>;
    using FillStyle = std::optional<OHOS::Ace::FillStyle>;

    const Type type;
    Scope scope;
    Direction direction;
    FillStyle fillStyle;

protected:
    explicit SymbolEffectPeer(
        Type symbolEffectType = Type::NONE,
        Scope optScope = std::nullopt,
        Direction optDirection = std::nullopt,
        FillStyle optFillStyle = std::nullopt
    ) : type(symbolEffectType), scope(optScope), direction(optDirection), fillStyle(optFillStyle) {}
    virtual ~SymbolEffectPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct BounceSymbolEffectPeer : SymbolEffectPeer {
protected:
    BounceSymbolEffectPeer(Scope optScope, Direction optDirection)
        : SymbolEffectPeer(Type::BOUNCE, optScope, optDirection) {}
    ~BounceSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct HierarchicalSymbolEffectPeer : SymbolEffectPeer {
protected:
    explicit HierarchicalSymbolEffectPeer(FillStyle optFillStyle)
        : SymbolEffectPeer(Type::HIERARCHICAL, std::nullopt, std::nullopt, optFillStyle) {}
    ~HierarchicalSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct ScaleSymbolEffectPeer : SymbolEffectPeer {
protected:
    ScaleSymbolEffectPeer(Scope optScope, Direction optDirection)
        : SymbolEffectPeer(Type::SCALE, optScope, optDirection) {}
    ~ScaleSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct ReplaceSymbolEffectPeer : SymbolEffectPeer {
protected:
    explicit ReplaceSymbolEffectPeer(Scope optScope)
        : SymbolEffectPeer(Type::REPLACE, optScope) {}
    ~ReplaceSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct AppearSymbolEffectPeer : SymbolEffectPeer {
protected:
    explicit AppearSymbolEffectPeer(Scope optScope)
        : SymbolEffectPeer(Type::APPEAR, optScope) {}
    ~AppearSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct DisappearSymbolEffectPeer : SymbolEffectPeer {
protected:
    explicit DisappearSymbolEffectPeer(Scope optScope)
        : SymbolEffectPeer(Type::DISAPPEAR, optScope) {}
    ~DisappearSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

struct PulseSymbolEffectPeer : SymbolEffectPeer {
protected:
    PulseSymbolEffectPeer()
        : SymbolEffectPeer(Type::PULSE) {}
    ~PulseSymbolEffectPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_SYMBOL_EFFECT_PEER_H
