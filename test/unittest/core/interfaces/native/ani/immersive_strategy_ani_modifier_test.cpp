/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/interfaces/ani/ani_api.h"
#include "core/interfaces/native/ani/immersive_strategy_ani_modifier.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ImmersiveStrategyAniModifierTest : public testing::Test {};

/**
 * @tc.name: GetImmersiveStrategyAniModifierStructValidity
 * @tc.desc: GetImmersiveStrategyAniModifier returns a non-null struct with a valid applyDefaultImmersiveStrategy
 *           function pointer, verifying the static-side modifier registration consumed by the arkoala ANI module.
 * @tc.type: FUNC
 */
HWTEST_F(ImmersiveStrategyAniModifierTest, GetImmersiveStrategyAniModifierStructValidity, TestSize.Level1)
{
    auto* modifier = GetImmersiveStrategyAniModifier();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->applyDefaultImmersiveStrategy, nullptr);
}
} // namespace OHOS::Ace::NG
