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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;


class EffectComponentModifierTest : public ModifierTestBase<GENERATED_ArkUIEffectComponentModifier,
    &GENERATED_ArkUINodeModifiers::getEffectComponentModifier, GENERATED_ARKUI_EFFECT_COMPONENT> {
};

/**
 * @tc.name: effectComponentModifierTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(EffectComponentModifierTest, effectComponentModifierTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setEffectComponentOptions, nullptr);
}

}