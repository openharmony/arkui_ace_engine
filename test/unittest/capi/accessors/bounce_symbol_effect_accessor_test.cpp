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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "symbol_effect_accessor_test.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;

class BounceSymbolEffectAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIBounceSymbolEffectAccessor,
    &GENERATED_ArkUIAccessors::getBounceSymbolEffectAccessor, BounceSymbolEffectPeer> {
    void* CreatePeerInstance() override
    {
        return accessor_->construct(nullptr, nullptr);
    }
};

/**
 * @tc.name: ctorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BounceSymbolEffectAccessorTest, ctorDefaultTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->type, SymbolEffectType::BOUNCE);
    EXPECT_EQ(peer_->scope, std::nullopt);
    EXPECT_EQ(peer_->direction, std::nullopt);
    EXPECT_EQ(peer_->fillStyle, std::nullopt);
}

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BounceSymbolEffectAccessorTest, ctorTest, TestSize.Level1)
{
    Opt_EffectScope scope1 = Converter::ArkValue<Opt_EffectScope, Ark_EffectScope>(ARK_EFFECT_SCOPE_LAYER);
    Opt_EffectScope scope2 = Converter::ArkValue<Opt_EffectScope, Ark_EffectScope>(ARK_EFFECT_SCOPE_WHOLE);
    Opt_EffectScope scopeEmpty = Converter::ArkValue<Opt_EffectScope>(Ark_Empty());
    Opt_EffectDirection direction1 = Converter::ArkValue<Opt_EffectDirection, Ark_EffectDirection>(
        ARK_EFFECT_DIRECTION_DOWN);
    Opt_EffectDirection direction2 = Converter::ArkValue<Opt_EffectDirection, Ark_EffectDirection>(
        ARK_EFFECT_DIRECTION_UP);
    Opt_EffectDirection directionEmpty = Converter::ArkValue<Opt_EffectDirection>(Ark_Empty());
    const std::vector<std::tuple<Opt_EffectScope*, Opt_EffectDirection*, SymbolEffectPeer*>> testPlan {
        {&scope1, &direction1,
            PeerUtils::CreatePeer<BounceSymbolEffectPeer>(OHOS::Ace::ScopeType::LAYER, CommonSubType::DOWN)},
        {&scope2, &direction2,
            PeerUtils::CreatePeer<BounceSymbolEffectPeer>(OHOS::Ace::ScopeType::WHOLE, CommonSubType::UP)},
        {&scopeEmpty, &direction1,
            PeerUtils::CreatePeer<BounceSymbolEffectPeer>(std::nullopt, CommonSubType::DOWN)},
        {&scope2, &directionEmpty,
            PeerUtils::CreatePeer<BounceSymbolEffectPeer>(OHOS::Ace::ScopeType::WHOLE, std::nullopt)},
        {nullptr, &direction1,
            PeerUtils::CreatePeer<BounceSymbolEffectPeer>(std::nullopt, CommonSubType::DOWN)},
        {&scope2, nullptr,
            PeerUtils::CreatePeer<BounceSymbolEffectPeer>(OHOS::Ace::ScopeType::WHOLE, std::nullopt)},
    };
    for (auto [value1, value2, expected] : testPlan) {
        Ark_BounceSymbolEffect peer = accessor_->construct(value1, value2);
        ASSERT_NE(peer, nullptr);
        EXPECT_EQ(*peer, *expected);
    }
}

/**
 * @tc.name: getScopeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BounceSymbolEffectAccessorTest, getScopeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getScope, nullptr);
    const std::vector<std::tuple<Ark_BounceSymbolEffect, std::optional<OHOS::Ace::ScopeType>>> testPlan {
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
HWTEST_F(BounceSymbolEffectAccessorTest, setScopeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setScope, nullptr);
    const std::vector<std::tuple<
        Ark_BounceSymbolEffect, Ark_EffectScope, std::optional<OHOS::Ace::ScopeType>
    >> testPlan {
        {peer_, ARK_EFFECT_SCOPE_LAYER, OHOS::Ace::ScopeType::LAYER},
        {peer_, ARK_EFFECT_SCOPE_WHOLE, OHOS::Ace::ScopeType::WHOLE},
        {nullptr, ARK_EFFECT_SCOPE_WHOLE, std::nullopt},
    };
    for (auto [peer, value, expected] : testPlan) {
        peer_->scope.reset();
        auto optVal = Converter::ArkValue<Opt_EffectScope>(value);
        accessor_->setScope(peer, &optVal);
        EXPECT_EQ(peer_->scope, expected);
    }
}

/**
 * @tc.name: getDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BounceSymbolEffectAccessorTest, getDirectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getDirection, nullptr);
    const std::vector<std::tuple<Ark_BounceSymbolEffect, std::optional<OHOS::Ace::CommonSubType>>> testPlan {
        {peer_, OHOS::Ace::CommonSubType::DOWN},
        {peer_, OHOS::Ace::CommonSubType::UP},
        {peer_, std::nullopt},
        {nullptr, std::nullopt},
    };
    for (auto [peer, value] : testPlan) {
        peer_->direction = value;
        Opt_EffectDirection result = accessor_->getDirection(peer);
        EXPECT_EQ(Converter::OptConvert<OHOS::Ace::CommonSubType>(result), value);
    }
}

/**
 * @tc.name: setDirectionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BounceSymbolEffectAccessorTest, setDirectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setDirection, nullptr);
    const std::vector<std::tuple<
        Ark_BounceSymbolEffect, Ark_EffectDirection, std::optional<OHOS::Ace::CommonSubType>
    >> testPlan {
        {peer_, ARK_EFFECT_DIRECTION_DOWN, OHOS::Ace::CommonSubType::DOWN},
        {peer_, ARK_EFFECT_DIRECTION_UP, OHOS::Ace::CommonSubType::UP},
        {nullptr, ARK_EFFECT_DIRECTION_DOWN, std::nullopt},
    };
    for (auto [peer, value, expected] : testPlan) {
        peer_->direction.reset();
        auto optVal = Converter::ArkValue<Opt_EffectDirection>(value);
        accessor_->setDirection(peer, &optVal);
        EXPECT_EQ(peer_->direction, expected);
    }
}
} // namespace OHOS::Ace::NG
