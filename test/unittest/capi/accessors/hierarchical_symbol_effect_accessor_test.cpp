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

class HierarchicalSymbolEffectAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIHierarchicalSymbolEffectAccessor,
    &GENERATED_ArkUIAccessors::getHierarchicalSymbolEffectAccessor, HierarchicalSymbolEffectPeer> {
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
HWTEST_F(HierarchicalSymbolEffectAccessorTest, ctorDefaultTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->type, SymbolEffectType::HIERARCHICAL);
    EXPECT_EQ(peer_->scope, std::nullopt);
    EXPECT_EQ(peer_->direction, std::nullopt);
    EXPECT_EQ(peer_->fillStyle, std::nullopt);
}

/**
 * @tc.name: ctorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HierarchicalSymbolEffectAccessorTest, ctorTest, TestSize.Level1)
{
    Opt_EffectFillStyle style1 = Converter::ArkValue<Opt_EffectFillStyle, Ark_EffectFillStyle>(
        ARK_EFFECT_FILL_STYLE_CUMULATIVE);
    Opt_EffectFillStyle style2 = Converter::ArkValue<Opt_EffectFillStyle, Ark_EffectFillStyle>(
        ARK_EFFECT_FILL_STYLE_ITERATIVE);
    Opt_EffectFillStyle styleEmpty = Converter::ArkValue<Opt_EffectFillStyle>(Ark_Empty());
    const std::vector<std::tuple<Opt_EffectFillStyle*, SymbolEffectPeer*>> testPlan {
        {&style1, PeerUtils::CreatePeer<HierarchicalSymbolEffectPeer>(OHOS::Ace::FillStyle::CUMULATIVE)},
        {&style2, PeerUtils::CreatePeer<HierarchicalSymbolEffectPeer>(OHOS::Ace::FillStyle::ITERATIVE)},
        {&styleEmpty, PeerUtils::CreatePeer<HierarchicalSymbolEffectPeer>(std::nullopt)},
        {nullptr, PeerUtils::CreatePeer<HierarchicalSymbolEffectPeer>(std::nullopt)},
    };
    for (auto [value, expected] : testPlan) {
        Ark_HierarchicalSymbolEffect peer = accessor_->construct(value);
        ASSERT_NE(peer, nullptr);
        EXPECT_EQ(*peer, *expected);
    }
}

/**
 * @tc.name: getFillStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HierarchicalSymbolEffectAccessorTest, getFillStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFillStyle, nullptr);
    const std::vector<std::tuple<Ark_HierarchicalSymbolEffect, std::optional<OHOS::Ace::FillStyle>>> testPlan {
        {peer_, OHOS::Ace::FillStyle::CUMULATIVE},
        {peer_, OHOS::Ace::FillStyle::ITERATIVE},
        {peer_, std::nullopt},
        {nullptr, std::nullopt},
    };
    for (auto [peer, value] : testPlan) {
        peer_->fillStyle = value;
        Opt_EffectFillStyle result = accessor_->getFillStyle(peer);
        EXPECT_EQ(Converter::OptConvert<OHOS::Ace::FillStyle>(result), value);
    }
}

/**
 * @tc.name: setFillStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(HierarchicalSymbolEffectAccessorTest, setFillStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFillStyle, nullptr);
    const std::vector<std::tuple<
        Ark_HierarchicalSymbolEffect, Opt_EffectFillStyle, std::optional<OHOS::Ace::FillStyle>
    >> testPlan {
        {peer_, ArkValue<Opt_EffectFillStyle>(ARK_EFFECT_FILL_STYLE_CUMULATIVE), OHOS::Ace::FillStyle::CUMULATIVE},
        {peer_, ArkValue<Opt_EffectFillStyle>(ARK_EFFECT_FILL_STYLE_ITERATIVE), OHOS::Ace::FillStyle::ITERATIVE},
        {peer_, ArkValue<Opt_EffectFillStyle>(), std::nullopt},
        {nullptr, ArkValue<Opt_EffectFillStyle>(ARK_EFFECT_FILL_STYLE_CUMULATIVE), std::nullopt},
    };
    for (auto [peer, value, expected] : testPlan) {
        peer_->fillStyle.reset();
        accessor_->setFillStyle(peer, &value);
        EXPECT_EQ(peer_->fillStyle, expected);
    }
}
} // namespace OHOS::Ace::NG
