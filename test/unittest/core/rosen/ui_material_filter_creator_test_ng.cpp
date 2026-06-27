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

#define private public
#define protected public

#include "core/components_ng/render/ui_material_filter_creator.h"
#include "core/components/common/properties/ui_material.h"

#include "render_service_client/core/ui_effect/property/include/rs_ui_filter_base.h"
#include "render_service_client/core/ui_effect/property/include/rs_ui_shader_base.h"

#undef private
#undef protected

#include "ui/base/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Color COLOR_WITH_ALPHA = Color::FromARGB(128, 255, 0, 0);
const Color COLOR_ZERO_ALPHA = Color::FromARGB(0, 255, 0, 0);
constexpr float DEFAULT_DIP_SCALE = 1.0f;
constexpr float EXPECTED_EMBOSS_RESET_X = 0.0f;
constexpr float EXPECTED_EMBOSS_RESET_Y = 0.0f;
} // namespace

class UiMaterialFilterCreatorTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void UiMaterialFilterCreatorTestNg::SetUp() {}
void UiMaterialFilterCreatorTestNg::TearDown() {}

ImmersiveMaterialConfig CreateGentleMaterialConfig(const Color& materialColor)
{
    ImmersiveMaterialConfig config;
    config.key.level = UiMaterialLevel::GENTLE;
    config.key.style = UiMaterialStyle::REGULAR;
    config.key.transparency = UiMaterialTransparency::GENTLE_THIN;
    config.key.colorMode = ColorMode::LIGHT;
    config.materialColor = materialColor;
    config.dipScale = DEFAULT_DIP_SCALE;
    return config;
}

ImmersiveMaterialConfig CreateECSubMaterialConfig(const Color& materialColor)
{
    ImmersiveMaterialConfig config;
    config.key.level = UiMaterialLevel::GENTLE;
    config.key.style = UiMaterialStyle::REGULAR_EC_SUB;
    config.key.transparency = UiMaterialTransparency::GENTLE_THIN;
    config.key.colorMode = ColorMode::LIGHT;
    config.materialColor = materialColor;
    config.dipScale = DEFAULT_DIP_SCALE;
    return config;
}

/**
 * @tc.name: ConvertToUiMaterialFilter_AlphaGreaterThanZero
 * @tc.desc: When materialColor has alpha > 0, WeightsEmboss and DarkModeWeightsEmboss should be reset to {0, 0}
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialFilterCreatorTestNg, ConvertToUiMaterialFilter_AlphaGreaterThanZero, TestSize.Level1)
{
    auto config = CreateGentleMaterialConfig(COLOR_WITH_ALPHA);
    auto filter = UiMaterialFilterCreator::ConvertToUiMaterialFilter(config);
    ASSERT_NE(filter, nullptr);
    auto glassFilter = std::static_pointer_cast<Rosen::RSNGFrostedGlassFilter>(filter);
    ASSERT_NE(glassFilter, nullptr);
    auto weightsEmboss = glassFilter->Getter<Rosen::FrostedGlassWeightsEmbossTag>()->Get();
    EXPECT_TRUE(NearEqual(weightsEmboss[0], EXPECTED_EMBOSS_RESET_X));
    EXPECT_TRUE(NearEqual(weightsEmboss[1], EXPECTED_EMBOSS_RESET_Y));
    auto darkModeWeightsEmboss = glassFilter->Getter<Rosen::FrostedGlassDarkModeWeightsEmbossTag>()->Get();
    EXPECT_TRUE(NearEqual(darkModeWeightsEmboss[0], EXPECTED_EMBOSS_RESET_X));
    EXPECT_TRUE(NearEqual(darkModeWeightsEmboss[1], EXPECTED_EMBOSS_RESET_Y));
}

/**
 * @tc.name: ConvertToUiMaterialFilter_AlphaEqualsZero
 * @tc.desc: When materialColor has alpha == 0, WeightsEmboss setter should not be invoked; filter retains original
 *           values
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialFilterCreatorTestNg, ConvertToUiMaterialFilter_AlphaEqualsZero, TestSize.Level1)
{
    auto config = CreateGentleMaterialConfig(COLOR_ZERO_ALPHA);
    auto filter = UiMaterialFilterCreator::ConvertToUiMaterialFilter(config);
    ASSERT_NE(filter, nullptr);
    auto glassFilter = std::static_pointer_cast<Rosen::RSNGFrostedGlassFilter>(filter);
    ASSERT_NE(glassFilter, nullptr);
    auto weightsEmboss = glassFilter->Getter<Rosen::FrostedGlassWeightsEmbossTag>()->Get();
    auto darkModeWeightsEmboss = glassFilter->Getter<Rosen::FrostedGlassDarkModeWeightsEmbossTag>()->Get();
    EXPECT_TRUE(NearEqual(weightsEmboss[0], EXPECTED_EMBOSS_RESET_X));
    EXPECT_TRUE(NearEqual(weightsEmboss[1], EXPECTED_EMBOSS_RESET_Y));
    EXPECT_TRUE(NearEqual(darkModeWeightsEmboss[0], EXPECTED_EMBOSS_RESET_X));
    EXPECT_TRUE(NearEqual(darkModeWeightsEmboss[1], EXPECTED_EMBOSS_RESET_Y));
    auto materialColorRs = glassFilter->Getter<Rosen::FrostedGlassMaterialColorTag>()->Get();
    EXPECT_TRUE(NearEqual(materialColorRs[3], 0.0f / 255.0f));
}

/**
 * @tc.name: ConvertToUiMaterialFilter_MaterialColorApplied
 * @tc.desc: MaterialColor should be correctly converted and applied to FrostedGlassMaterialColorTag
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialFilterCreatorTestNg, ConvertToUiMaterialFilter_MaterialColorApplied, TestSize.Level1)
{
    auto config = CreateGentleMaterialConfig(COLOR_WITH_ALPHA);
    auto filter = UiMaterialFilterCreator::ConvertToUiMaterialFilter(config);
    ASSERT_NE(filter, nullptr);
    auto glassFilter = std::static_pointer_cast<Rosen::RSNGFrostedGlassFilter>(filter);
    ASSERT_NE(glassFilter, nullptr);
    auto materialColorRs = glassFilter->Getter<Rosen::FrostedGlassMaterialColorTag>()->Get();
    float expectColorRed = COLOR_WITH_ALPHA.GetRed() / 255.0f;
    float expectColorGreen = COLOR_WITH_ALPHA.GetGreen() / 255.0f;
    float expectColorBlue = COLOR_WITH_ALPHA.GetBlue() / 255.0f;
    float expectColorAlpha = COLOR_WITH_ALPHA.GetAlpha() / 255.0f;
    EXPECT_TRUE(NearEqual(materialColorRs[0], expectColorRed));
    EXPECT_TRUE(NearEqual(materialColorRs[1], expectColorGreen));
    EXPECT_TRUE(NearEqual(materialColorRs[2], expectColorBlue));
    EXPECT_TRUE(NearEqual(materialColorRs[3], expectColorAlpha));
}

/**
 * @tc.name: ConvertToUiMaterialFilter_InvalidKeyReturnsNull
 * @tc.desc: When key is not found in MATERIAL_PARAM_MAP, ConvertToUiMaterialFilter should return nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialFilterCreatorTestNg, ConvertToUiMaterialFilter_InvalidKeyReturnsNull, TestSize.Level1)
{
    ImmersiveMaterialConfig config;
    config.key.level = UiMaterialLevel::GENTLE;
    config.key.style = UiMaterialStyle::ULTRA_THICK;
    config.key.transparency = UiMaterialTransparency::NONE;
    config.key.colorMode = ColorMode::LIGHT;
    config.materialColor = COLOR_WITH_ALPHA;
    config.dipScale = DEFAULT_DIP_SCALE;
    auto filter = UiMaterialFilterCreator::ConvertToUiMaterialFilter(config);
    EXPECT_EQ(filter, nullptr);
}

/**
 * @tc.name: ConvertToUiMaterialECSubShader_AlphaGreaterThanZero
 * @tc.desc: When materialColor alpha > 0 in ECSubShader, EffectWeightsEmboss should be reset to {0, 0}
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialFilterCreatorTestNg, ConvertToUiMaterialECSubShader_AlphaGreaterThanZero, TestSize.Level1)
{
    auto config = CreateECSubMaterialConfig(COLOR_WITH_ALPHA);
    auto shader = UiMaterialFilterCreator::ConvertToUiMaterialECSubShader(config);
    ASSERT_NE(shader, nullptr);
    auto glassEffect = std::static_pointer_cast<Rosen::RSNGFrostedGlassEffect>(shader);
    ASSERT_NE(glassEffect, nullptr);
    auto weightsEmboss = glassEffect->Getter<Rosen::FrostedGlassEffectWeightsEmbossTag>()->Get();
    EXPECT_TRUE(NearEqual(weightsEmboss[0], EXPECTED_EMBOSS_RESET_X));
    EXPECT_TRUE(NearEqual(weightsEmboss[1], EXPECTED_EMBOSS_RESET_Y));
}

/**
 * @tc.name: ConvertToUiMaterialECSubShader_AlphaEqualsZero
 * @tc.desc: When materialColor alpha == 0 in ECSubShader, EffectWeightsEmboss setter should not be invoked
 * @tc.type: FUNC
 */
HWTEST_F(UiMaterialFilterCreatorTestNg, ConvertToUiMaterialECSubShader_AlphaEqualsZero, TestSize.Level1)
{
    auto config = CreateECSubMaterialConfig(COLOR_ZERO_ALPHA);
    auto shader = UiMaterialFilterCreator::ConvertToUiMaterialECSubShader(config);
    ASSERT_NE(shader, nullptr);
    auto glassEffect = std::static_pointer_cast<Rosen::RSNGFrostedGlassEffect>(shader);
    ASSERT_NE(glassEffect, nullptr);
    auto materialColorRs = glassEffect->Getter<Rosen::FrostedGlassEffectMaterialColorTag>()->Get();
    EXPECT_TRUE(NearEqual(materialColorRs[3], 0.0f / 255.0f));
}
} // namespace OHOS::Ace::NG
