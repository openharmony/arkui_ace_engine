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

#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "core/interfaces/native/implementation/replace_symbol_effect_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

    class ReplaceSymbolEffectAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIReplaceSymbolEffectAccessor,
        &GENERATED_ArkUIAccessors::getReplaceSymbolEffectAccessor, ReplaceSymbolEffectPeer> {
    public:
    void* CreatePeerInstance() override
    {
        Opt_EffectScope scope = {};
        return accessor_->ctor(&scope);
    }
    void DestroyPeer(ReplaceSymbolEffectPeer* peer)
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
HWTEST_F(ReplaceSymbolEffectAccessorTest, scopeTest, TestSize.Level1)
{
    auto scope = Converter::ArkValue<Ark_EffectScope>(OHOS::Ace::ScopeType::WHOLE);
    accessor_->setScope(peer_, scope);
    ASSERT_NE(peer_->effectOptions, nullptr);
    auto aceScope = peer_->effectOptions->GetScopeType();
    ASSERT_EQ(aceScope, OHOS::Ace::ScopeType::WHOLE);

    Ark_EffectScope arkScope = accessor_->getScope(peer_);
    ASSERT_EQ(arkScope, ARK_EFFECT_SCOPE_WHOLE);
}

 } // namespace OHOS::Ace::NG
 