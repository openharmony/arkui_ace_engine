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

#include <algorithm>

#include "gtest/gtest.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_application_info.h"
#include "core/components/common/properties/shadow.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
void SetApiVersion(int32_t version)
{
    MockContainer::Current()->SetApiTargetVersion(version);
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(version);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(version);
}

Ark_ShadowOptions MakeEmptyShadowOptions()
{
    Ark_ShadowOptions src = {};
    src.radius = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    src.type = Converter::ArkValue<Opt_ShadowType>(Ark_Empty());
    src.color =
        Converter::ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy>(Ark_Empty());
    src.offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    src.offsetY = Converter::ArkValue<Opt_Union_F64_Resource>(Ark_Empty());
    src.fill = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    return src;
}
} // namespace

class ConvertorTextShadowTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }

    void TearDown() override
    {
        SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    }
};

/**
 * @tc.name: DefaultShadowBlurRadiusRAIITest
 * @tc.desc: Verify DefaultShadowBlurRadius RAII saves and restores state correctly
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, DefaultShadowBlurRadiusRAIITest, TestSize.Level1)
{
    EXPECT_DOUBLE_EQ(Converter::ConverterState::defShadowBlurRadius, -1.0);
    {
        Converter::DefaultShadowBlurRadius defaultRadius(0.0);
        EXPECT_DOUBLE_EQ(Converter::ConverterState::defShadowBlurRadius, 0.0);
    }
    EXPECT_DOUBLE_EQ(Converter::ConverterState::defShadowBlurRadius, -1.0);
}

/**
 * @tc.name: ConvertTextShadowDefaultBlurRadiusTest
 * @tc.desc: Verify Convert<Shadow> with DefaultShadowBlurRadius returns Shadow with blurRadius=0.0
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowDefaultBlurRadiusTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_DOUBLE_EQ(result.GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ConvertShadowWithoutRAIILowAPITest
 * @tc.desc: API < 26, no RAII. SetBlurRadius clamps -1.0 to 0.0 internally, result is 0.0
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertShadowWithoutRAIILowAPITest, TestSize.Level1)
{
    SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto src = MakeEmptyShadowOptions();
    auto result = Converter::Convert<Shadow>(src);
    // API < 26: Shadow(-1.0) -> SetBlurRadius clamps to 0.0
    EXPECT_DOUBLE_EQ(result.GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ConvertShadowWithoutRAIIHighAPITest
 * @tc.desc: API >= 26, no RAII. SetBlurRadius keeps -1.0, result is -1.0
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertShadowWithoutRAIIHighAPITest, TestSize.Level1)
{
    SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto src = MakeEmptyShadowOptions();
    auto result = Converter::Convert<Shadow>(src);
    // API >= 26: Shadow(-1.0) -> SetBlurRadius keeps -1.0
    EXPECT_DOUBLE_EQ(result.GetBlurRadius(), -1.0);
}

/**
 * @tc.name: ConvertShadowWithRAIIHighAPITest
 * @tc.desc: API >= 26, with RAII(0.0). Shadow(0.0) -> blurRadius is 0.0, RAII takes effect
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertShadowWithRAIIHighAPITest, TestSize.Level1)
{
    SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    auto src = MakeEmptyShadowOptions();
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    // API >= 26 + RAII: Shadow(0.0) -> blurRadius is 0.0
    EXPECT_DOUBLE_EQ(result.GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ConvertTextShadowExplicitRadiusTest
 * @tc.desc: Verify Convert<Shadow> sets blurRadius when radius is explicitly provided
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowExplicitRadiusTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.radius = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(10.5);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_DOUBLE_EQ(result.GetBlurRadius(), 10.5);
}

/**
 * @tc.name: ConvertTextShadowOffsetTest
 * @tc.desc: Verify Convert<Shadow> correctly sets offsetX and offsetY
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowOffsetTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(3.0);
    src.offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(4.0);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_DOUBLE_EQ(result.GetOffset().GetX(), 3.0);
    EXPECT_DOUBLE_EQ(result.GetOffset().GetY(), 4.0);
}

/**
 * @tc.name: ConvertTextShadowTypeTest
 * @tc.desc: Verify Convert<Shadow> correctly sets ShadowType
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowTypeTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_BLUR);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_EQ(result.GetShadowType(), ShadowType::BLUR);
}

/**
 * @tc.name: ConvertTextShadowColorTest
 * @tc.desc: Verify Convert<Shadow> correctly sets color
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowColorTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.color = Converter::ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
        Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_EQ(result.GetColor(), Color::RED);
}

/**
 * @tc.name: ConvertTextShadowFillTest
 * @tc.desc: Verify Convert<Shadow> correctly sets isFilled
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowFillTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.fill = Converter::ArkValue<Opt_Boolean>(true);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_TRUE(result.GetIsFilled());
}

/**
 * @tc.name: ConvertTextShadowAllFieldsTest
 * @tc.desc: Verify Convert<Shadow> with all fields set
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowAllFieldsTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.radius = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(5.0);
    src.type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_COLOR);
    src.color = Converter::ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
        Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    src.offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.0);
    src.offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(2.0);
    src.fill = Converter::ArkValue<Opt_Boolean>(true);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_DOUBLE_EQ(result.GetBlurRadius(), 5.0);
    EXPECT_EQ(result.GetShadowType(), ShadowType::COLOR);
    EXPECT_EQ(result.GetColor(), Color::BLUE);
    EXPECT_DOUBLE_EQ(result.GetOffset().GetX(), 1.0);
    EXPECT_DOUBLE_EQ(result.GetOffset().GetY(), 2.0);
    EXPECT_TRUE(result.GetIsFilled());
}

/**
 * @tc.name: ConvertTextShadowVectorTest
 * @tc.desc: Verify Convert<vector<Shadow>> with DefaultShadowBlurRadius returns a vector with a single element
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowVectorTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.radius = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(8.0);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<std::vector<Shadow>>(src);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0].GetBlurRadius(), 8.0);
}

/**
 * @tc.name: ConvertTextShadowVectorDefaultBlurRadiusTest
 * @tc.desc: Verify Convert<vector<Shadow>> returns Shadow with blurRadius=0.0 by default
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowVectorDefaultBlurRadiusTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<std::vector<Shadow>>(src);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_DOUBLE_EQ(result[0].GetBlurRadius(), 0.0);
}

/**
 * @tc.name: ShadowConstructorWithBlurRadiusTest
 * @tc.desc: Verify Shadow(double) constructor sets blurRadius correctly
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ShadowConstructorWithBlurRadiusTest, TestSize.Level1)
{
    Shadow shadow(0.0);
    EXPECT_DOUBLE_EQ(shadow.GetBlurRadius(), 0.0);

    Shadow shadowPositive(5.5);
    EXPECT_DOUBLE_EQ(shadowPositive.GetBlurRadius(), 5.5);
}

/**
 * @tc.name: ShadowDefaultConstructorHighAPITest
 * @tc.desc: API >= 26, Shadow() default constructor keeps blurRadius=-1.0
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ShadowDefaultConstructorHighAPITest, TestSize.Level1)
{
    SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    Shadow shadow;
    EXPECT_DOUBLE_EQ(shadow.GetBlurRadius(), -1.0);
}

/**
 * @tc.name: ConvertTextShadowColorStrategyTest
 * @tc.desc: Verify Convert<Shadow> correctly sets ShadowColorStrategy
 * @tc.type: FUNC
 */
HWTEST_F(ConvertorTextShadowTest, ConvertTextShadowColorStrategyTest, TestSize.Level1)
{
    Ark_ShadowOptions src = {};
    src.color = Converter::ArkUnion<Opt_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy,
        Ark_ColoringStrategy>(ARK_COLORING_STRATEGY_AVERAGE);
    Converter::DefaultShadowBlurRadius defaultBlurRadius(0.0);
    auto result = Converter::Convert<Shadow>(src);
    EXPECT_EQ(result.GetShadowColorStrategy(), ShadowColorStrategy::AVERAGE);
}

} // namespace OHOS::Ace::NG
