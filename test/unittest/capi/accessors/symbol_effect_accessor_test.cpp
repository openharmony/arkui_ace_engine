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

class SymbolEffectAccessorTest : public AccessorTestBase<GENERATED_ArkUISymbolEffectAccessor,
    &GENERATED_ArkUIAccessors::getSymbolEffectAccessor, SymbolEffectPeer> {
};

/**
 * @tc.name: ctorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(SymbolEffectAccessorTest, ctorDefaultTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->type, SymbolEffectType::NONE);
    EXPECT_EQ(peer_->scope, std::nullopt);
    EXPECT_EQ(peer_->direction, std::nullopt);
    EXPECT_EQ(peer_->fillStyle, std::nullopt);
}

} // namespace OHOS::Ace::NG
