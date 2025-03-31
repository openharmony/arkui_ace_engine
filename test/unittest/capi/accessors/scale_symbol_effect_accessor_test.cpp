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

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class ScaleSymbolEffectAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIScaleSymbolEffectAccessor,
    &GENERATED_ArkUIAccessors::getScaleSymbolEffectAccessor, ScaleSymbolEffectPeer> {
public:
    void* CreatePeerInstance() override
    {
        Opt_EffectScope scope = {};
        Opt_EffectDirection direction = {};
        return accessor_->ctor(&scope, &direction);
    }
    void DestroyPeer(ScaleSymbolEffectPeer* peer)
    {
        finalyzer_(peer);
        peer = nullptr;
    }
};
 
/**
 * @tc.name: scopeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScaleSymbolEffectAccessorTest, scopeTest, TestSize.Level1)
{
    auto scope = Converter::ArkValue<Ark_EffectScope>(OHOS::Ace::ScopeType::WHOLE);
    accessor_->setScope(peer_, scope);
    ASSERT_TRUE(peer_->scope.has_value());
    auto aceScope = peer_->scope.value();
    ASSERT_EQ(aceScope, OHOS::Ace::ScopeType::WHOLE);

    Ark_EffectScope arkScope = accessor_->getScope(peer_);
    ASSERT_EQ(arkScope, ARK_EFFECT_SCOPE_WHOLE);
}

/**
 * @tc.name: directionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScaleSymbolEffectAccessorTest, directionTest, TestSize.Level1)
{
    auto direction = Converter::ArkValue<Ark_EffectDirection>(OHOS::Ace::CommonSubType::UP);
    accessor_->setDirection(peer_, direction);
    ASSERT_TRUE(peer_->direction.has_value());
    auto aceDirection = peer_->direction.value();
    ASSERT_EQ(aceDirection, OHOS::Ace::CommonSubType::UP);

    Ark_EffectDirection arkDirection = accessor_->getDirection(peer_);
    ASSERT_EQ(arkDirection, ARK_EFFECT_DIRECTION_UP);
}

} // namespace OHOS::Ace::NG
 