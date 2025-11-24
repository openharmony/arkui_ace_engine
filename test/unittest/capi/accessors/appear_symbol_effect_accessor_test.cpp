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

#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "core/interfaces/native/implementation/symbol_effect_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "symbol_effect_accessor_test.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;

class AppearSymbolEffectAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIAppearSymbolEffectAccessor,
    &GENERATED_ArkUIAccessors::getAppearSymbolEffectAccessor, AppearSymbolEffectPeer> {
    void* CreatePeerInstance() override
    {
        return accessor_->construct(nullptr);
    }
};

/**
 * @tc.name: ctorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AppearSymbolEffectAccessorTest, ctorDefaultTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->type, SymbolEffectType::APPEAR);
    EXPECT_EQ(peer_->scope, std::nullopt);
    EXPECT_EQ(peer_->direction, std::nullopt);
    EXPECT_EQ(peer_->fillStyle, std::nullopt);
}

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AppearSymbolEffectAccessorTest, ctorTest, TestSize.Level1)
{
    Opt_EffectScope scope1 = Converter::ArkValue<Opt_EffectScope, Ark_EffectScope>(ARK_EFFECT_SCOPE_LAYER);
    Opt_EffectScope scope2 = Converter::ArkValue<Opt_EffectScope, Ark_EffectScope>(ARK_EFFECT_SCOPE_WHOLE);
    Opt_EffectScope scopeEmpty = Converter::ArkValue<Opt_EffectScope>(Ark_Empty());
    const std::vector<std::tuple<Opt_EffectScope*, SymbolEffectPeer*>> testPlan {
        {&scope1, PeerUtils::CreatePeer<AppearSymbolEffectPeer>(OHOS::Ace::ScopeType::LAYER)},
        {&scope2, PeerUtils::CreatePeer<AppearSymbolEffectPeer>(OHOS::Ace::ScopeType::WHOLE)},
        {&scopeEmpty, PeerUtils::CreatePeer<AppearSymbolEffectPeer>(std::nullopt)},
        {nullptr, PeerUtils::CreatePeer<AppearSymbolEffectPeer>(std::nullopt)},
    };
    for (auto [value, expected] : testPlan) {
        Ark_AppearSymbolEffect peer = accessor_->construct(value);
        ASSERT_NE(peer, nullptr);
        EXPECT_EQ(*peer, *expected);
    }
}

/**
 * @tc.name: getScopeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AppearSymbolEffectAccessorTest, getScopeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScope, nullptr);
    const std::vector<std::tuple<Ark_AppearSymbolEffect, std::optional<OHOS::Ace::ScopeType>>> testPlan {
        {peer_, OHOS::Ace::ScopeType::LAYER},
        {peer_, OHOS::Ace::ScopeType::WHOLE},
        {peer_, std::nullopt},
        {nullptr, std::nullopt},
    };
    for (auto [peer, value] : testPlan) {
        peer_->scope = value;
        Opt_EffectScope result = accessor_->getScope(peer);
        EXPECT_EQ(Converter::OptConvert<OHOS::Ace::ScopeType>(result), value);
    }
}

/**
 * @tc.name: setScopeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AppearSymbolEffectAccessorTest, setScopeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setScope, nullptr);
    const std::vector<std::tuple<
        Ark_AppearSymbolEffect, Opt_EffectScope, std::optional<OHOS::Ace::ScopeType>
    >> testPlan {
        {peer_, Converter::ArkValue<Opt_EffectScope>(ARK_EFFECT_SCOPE_LAYER), OHOS::Ace::ScopeType::LAYER},
        {peer_, Converter::ArkValue<Opt_EffectScope>(ARK_EFFECT_SCOPE_WHOLE), OHOS::Ace::ScopeType::WHOLE},
        {nullptr, Converter::ArkValue<Opt_EffectScope>(ARK_EFFECT_SCOPE_LAYER), std::nullopt},
    };
    for (auto [peer, value, expected] : testPlan) {
        peer_->scope.reset();
        accessor_->setScope(peer, &value);
        EXPECT_EQ(peer_->scope, expected);
    }
}
} // namespace OHOS::Ace::NG
