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
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

#include "interfaces/inner_api/ace_kit/include/ui/properties/ui_material_enums.h"
#include "core/interfaces/ani/ani_api.h"
#include "core/interfaces/native/ani/visual_effect_ani_modifier.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class VisualEffectAniModifierTest : public testing::Test {
public:
    void SetUp() override
    {
        savedLevel_ = g_uiMaterialLevel;
        savedSupported_ = g_isDeviceSystemMaterialSupported;
    }
    void TearDown() override
    {
        g_uiMaterialLevel = savedLevel_;
        g_isDeviceSystemMaterialSupported = savedSupported_;
    }

private:
    UiMaterialLevel savedLevel_;
    bool savedSupported_;
};

HWTEST_F(VisualEffectAniModifierTest, GetVisualEffectAniModifierStructValidity, TestSize.Level1)
{
    auto* modifier = GetVisualEffectAniModifier();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->constructMaterial, nullptr);
    ASSERT_NE(modifier->destroyMaterial, nullptr);
    ASSERT_NE(modifier->convertToECMaterial, nullptr);
    ASSERT_NE(modifier->convertToECSubMaterial, nullptr);
    ASSERT_NE(modifier->getGlobalMaterialLevel, nullptr);
    ASSERT_NE(modifier->isImmersiveMaterialSupported, nullptr);
}

HWTEST_F(VisualEffectAniModifierTest, GetGlobalMaterialLevelAllValues, TestSize.Level1)
{
    auto* modifier = GetVisualEffectAniModifier();
    ASSERT_NE(modifier, nullptr);

    g_uiMaterialLevel = UiMaterialLevel::EXQUISITE;
    EXPECT_EQ(modifier->getGlobalMaterialLevel(),
        static_cast<int32_t>(UiMaterialLevel::EXQUISITE));

    g_uiMaterialLevel = UiMaterialLevel::GENTLE;
    EXPECT_EQ(modifier->getGlobalMaterialLevel(),
        static_cast<int32_t>(UiMaterialLevel::GENTLE));

    g_uiMaterialLevel = UiMaterialLevel::SMOOTH;
    EXPECT_EQ(modifier->getGlobalMaterialLevel(),
        static_cast<int32_t>(UiMaterialLevel::SMOOTH));

    g_uiMaterialLevel = UiMaterialLevel::DEFAULT;
    EXPECT_EQ(modifier->getGlobalMaterialLevel(),
        static_cast<int32_t>(UiMaterialLevel::DEFAULT));
}

HWTEST_F(VisualEffectAniModifierTest, IsImmersiveMaterialSupportedToggle, TestSize.Level1)
{
    auto* modifier = GetVisualEffectAniModifier();
    ASSERT_NE(modifier, nullptr);

    g_isDeviceSystemMaterialSupported = true;
    EXPECT_TRUE(modifier->isImmersiveMaterialSupported());

    g_isDeviceSystemMaterialSupported = false;
    EXPECT_FALSE(modifier->isImmersiveMaterialSupported());

    g_isDeviceSystemMaterialSupported = true;
    EXPECT_TRUE(modifier->isImmersiveMaterialSupported());
}
} // namespace OHOS::Ace::NG
