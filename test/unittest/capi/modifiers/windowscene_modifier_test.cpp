/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/stubs/mock_window_scene_model.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

static constexpr int32_t PERSISTENT_ID = 10;
static constexpr auto DESTINATION_X = 5._px;
static constexpr auto DESTINATION_Y = 6._px;
static constexpr float FRACTION = 100.1f;

class WindowSceneModifierTest : public ModifierTestBase<GENERATED_ArkUIWindowSceneModifier,
      &GENERATED_ArkUINodeModifiers::getWindowSceneModifier, GENERATED_ARKUI_WINDOW_SCENE> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: setAttractionEffectTest
 * @tc.desc: test function of setAttractionEffect
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneModifierTest, setAttractionEffectTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setAttractionEffect, nullptr);
    Ark_Position destination;
    Converter::ConvContext ctx;
    destination.x = Converter::ArkValue<Opt_Length>(DESTINATION_X, &ctx);
    destination.y = Converter::ArkValue<Opt_Length>(DESTINATION_Y, &ctx);
    Opt_Position optDestination = Converter::ArkValue<Opt_Position>(destination);
    Opt_Float64 fraction = Converter::ArkValue<Opt_Float64>(FRACTION);

    modifier_->setAttractionEffect(node_, &optDestination, &fraction);
    AttractionEffect effect = WindowSceneModel::GetAttractionEffect();
    AttractionEffect effectTest;
    effectTest.fraction = FRACTION;
    effectTest.destinationX = CalcDimension(DESTINATION_X);
    effectTest.destinationY = CalcDimension(DESTINATION_Y);
    EXPECT_EQ(effect, effectTest);
}

/*
 * @tc.name: setWindowSceneOptionsTest
 * @tc.desc: test function of setWindowSceneOptions
 * @tc.type: FUNC
 */
HWTEST_F(WindowSceneModifierTest, setWindowSceneOptionsTest, TestSize.Level1)
{
    Ark_Int32 persistentId = Converter::ArkValue<Ark_Int32>(PERSISTENT_ID);
    modifier_->setWindowSceneOptions(node_, persistentId);
    int32_t id = WindowSceneModel::GetPersistentId();
    EXPECT_EQ(id, PERSISTENT_ID);
}

} // namespace OHOS::Ace::NG
